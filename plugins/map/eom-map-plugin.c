#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gmodule.h>
#include <glib/gi18n-lib.h>

#define HAVE_EXIF 1
#include <eom/eom-exif-util.h>
#include <eom/eom-thumb-view.h>
#include <eom/eom-image.h>
#include <eom/eom-window.h>
#include <eom/eom-sidebar.h>
#include "eom-map-plugin.h"

#include <math.h>
#include <string.h>
#include <champlain/champlain.h>
#include <champlain-gtk/champlain-gtk.h>
#include <clutter-gtk/clutter-gtk.h>
#include <libexif/exif-data.h>

#define WINDOW_DATA_KEY "EomMapWindowData"

EOM_PLUGIN_REGISTER_TYPE (EomMapPlugin, eom_map_plugin)

#define FACTOR 2.0

typedef struct {
	/* Handlers ids */
	guint selection_changed_id;
	guint thumbnail_changed_id;

	GtkWidget *viewport;
	ChamplainView *map;

	GtkWidget *jump_to_button;

	ChamplainMarkerLayer *layer;
	ChamplainLabel *marker;
} WindowData;

static void
free_window_data (WindowData *data)
{
	g_return_if_fail (data != NULL);

	eom_debug (DEBUG_PLUGINS);

	g_free (data);
}

static void
eom_map_plugin_init (EomMapPlugin *plugin)
{
	eom_debug_message (DEBUG_PLUGINS, "EomMapPlugin initializing");
	gtk_clutter_init (NULL, NULL);
}

static void
eom_map_plugin_finalize (GObject *object)
{
	eom_debug_message (DEBUG_PLUGINS, "EomMapPlugin finalizing");

	G_OBJECT_CLASS (eom_map_plugin_parent_class)->finalize (object);
}

static ChamplainLabel *
create_champlain_label (EomImage *image)
{
	ClutterActor *thumb, *marker;
	GdkPixbuf* thumbnail = eom_image_get_thumbnail (image);

	marker = champlain_label_new ();
	thumb = gtk_clutter_texture_new ();

	if (thumbnail) {
		gfloat width, height;

		gtk_clutter_texture_set_from_pixbuf (GTK_CLUTTER_TEXTURE (thumb),
						     thumbnail,
						     NULL);
		/* Clip the thumbnail to cut the border */
		width = gdk_pixbuf_get_width (thumbnail);
		height = gdk_pixbuf_get_height (thumbnail);

		clutter_actor_set_clip (thumb, 3, 3, (width / FACTOR) - 7,
			(height / FACTOR) - 7);
		width = clutter_actor_get_width (thumb) / FACTOR;
		height = clutter_actor_get_height (thumb) / FACTOR;
		clutter_actor_set_size (thumb, width, height);
	}

	champlain_label_set_image (CHAMPLAIN_LABEL (marker), thumb);

	if (thumbnail)
		g_object_unref (thumbnail);

	return CHAMPLAIN_LABEL (marker);
}

static gboolean
get_coordinates (EomImage *image,
		 gdouble *latitude,
		 gdouble *longitude)
{
	ExifData *exif_data;
	gchar buffer[32];
	gdouble lon, lat;
	gfloat hour, min, sec;

	exif_data = eom_image_get_exif_info (image);

	if (exif_data) {

		eom_exif_data_get_value (exif_data,
					 EXIF_TAG_GPS_LONGITUDE,
					 buffer,
					 32);
		if (strlen (buffer) < 5) {
			exif_data_unref (exif_data);
			return FALSE;
		}

		sscanf (buffer, "%f, %f, %f", &hour, &min, &sec);
		lon = hour;
		lon += min / 60.0;
		lon += sec / 3600.0;

		eom_exif_data_get_value (exif_data,
					 EXIF_TAG_GPS_LONGITUDE_REF,
					 buffer,
					 32);
		if (strcmp (buffer, "W") == 0)
			lon *= -1;

		eom_exif_data_get_value (exif_data,
					 EXIF_TAG_GPS_LATITUDE,
					 buffer,
					 32);
		if (strlen (buffer) < 5) {
			exif_data_unref (exif_data);
			return FALSE;
		}

		sscanf (buffer, "%f, %f, %f", &hour, &min, &sec);
		lat = hour;
		lat += min / 60.0;
		lat += sec / 3600.0;

		eom_exif_data_get_value (exif_data,
					 EXIF_TAG_GPS_LATITUDE_REF,
					 buffer,
					 32);
		if (strcmp (buffer, "S") == 0)
			lat *= -1;

		*longitude = lon;
		*latitude = lat;

		exif_data_unref (exif_data);
		return TRUE;
	}
	return FALSE;
}

static void
create_marker (EomImage *image,
	       WindowData *data)
{
	gdouble lon, lat;

	data->marker = NULL;
	gtk_widget_set_sensitive (data->jump_to_button, FALSE);

	if (!image)
		return;

	if (!eom_image_has_data (image, EOM_IMAGE_DATA_EXIF) &&
	    !eom_image_load (image, EOM_IMAGE_DATA_EXIF, NULL, NULL))
		return;

	if (get_coordinates (image, &lat, &lon)) {
		data->marker = create_champlain_label (image);

		gtk_widget_set_sensitive (data->jump_to_button, TRUE);
		champlain_location_set_location (CHAMPLAIN_LOCATION (data->marker),
						    lat,
						    lon);
		champlain_marker_layer_add_marker (data->layer, CHAMPLAIN_MARKER(data->marker));
	}

}

static void
thumbnail_changed_cb (EomImage* image,
		      WindowData* data)
{
	gdouble lon, lat;

	if (eom_image_get_thumbnail (image)) {
		create_marker (image, data);
		if (data->marker) {
			g_object_get (data->marker,
				      "latitude", &lat,
				      "longitude", &lon,
				      NULL);
			champlain_view_center_on (CHAMPLAIN_VIEW (data->map),
						  lat,
						  lon);
		}

		g_signal_handler_disconnect (image,
					     data->thumbnail_changed_id);
	}
}

static void
selection_changed_cb (EomThumbView *view,
		      WindowData *data)
{
	EomImage *image;

	if (!eom_thumb_view_get_n_selected (view))
		return;

	image = eom_thumb_view_get_first_selected_image (view);

	g_return_if_fail (image != NULL);

	if (data->marker)
		clutter_actor_remove_child (CLUTTER_ACTOR (data->layer),
					  CLUTTER_ACTOR (data->marker));

	data->thumbnail_changed_id = g_signal_connect (G_OBJECT (image),
						       "thumbnail-changed",
						       G_CALLBACK (thumbnail_changed_cb),
						       data);

	/* Call the callback because images that are already in the
	 * thumbview don't emit thumbnail_changed
	 */
	thumbnail_changed_cb (image, data);

	g_object_unref (image);
}

static void
jump_to (GtkWidget *widget,
	 WindowData *data)
{
	gdouble lat, lon;

	if (!data->marker)
		return;

	g_object_get (data->marker,
		      "latitude", &lat,
		      "longitude", &lon,
		      NULL);

	champlain_view_center_on (data->map, lat, lon);
}

static void
zoom_in (GtkWidget *widget,
	 ChamplainView *view)
{
	champlain_view_zoom_in (view);
}

static void
zoom_out (GtkWidget *widget,
	  ChamplainView *view)
{
	champlain_view_zoom_out (view);
}

static void
impl_activate (EomPlugin *plugin,
	       EomWindow *window)
{
	GtkWidget *sidebar, *thumbview, *vbox, *bbox, *button, *viewport;
	GtkWidget *embed;
	WindowData *data;
	ClutterActor *scale;

	eom_debug (DEBUG_PLUGINS);

	data = g_new0 (WindowData, 1);
	g_object_set_data_full (G_OBJECT (window),
				WINDOW_DATA_KEY,
				data,
				(GDestroyNotify) free_window_data);

	/* This is a workaround until bug 590692 is fixed. */
	viewport = gtk_frame_new (NULL);
	gtk_frame_set_shadow_type (GTK_FRAME (viewport), GTK_SHADOW_ETCHED_IN);
	/*viewport = gtk_viewport_new (NULL, NULL);
	gtk_viewport_set_shadow_type (GTK_VIEWPORT (viewport),
				      GTK_SHADOW_ETCHED_IN);*/

	embed = gtk_champlain_embed_new ();
	data->map = gtk_champlain_embed_get_view (GTK_CHAMPLAIN_EMBED (embed));
	g_object_set (G_OBJECT (data->map),
		"zoom-level", 3,
		"kinetic-mode", TRUE,
		NULL);
	scale = champlain_scale_new ();
	champlain_scale_connect_view (CHAMPLAIN_SCALE (scale), data->map);
	/* align to the bottom left */
	champlain_view_bin_layout_add (data->map, scale,
		CLUTTER_BIN_ALIGNMENT_START,
		CLUTTER_BIN_ALIGNMENT_END);
	gtk_container_add (GTK_CONTAINER (viewport), embed);

	vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	bbox = gtk_toolbar_new ();

	button = GTK_WIDGET (gtk_tool_button_new (NULL, NULL));
	gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (button), "go-jump-symbolic");
	gtk_widget_set_tooltip_text (button, _("Jump to current image's location"));
	g_signal_connect (button,
			  "clicked",
			  G_CALLBACK (jump_to),
			  data);
	gtk_container_add (GTK_CONTAINER (bbox), button);
	data->jump_to_button = button;

	button = GTK_WIDGET (gtk_separator_tool_item_new ());
	gtk_container_add (GTK_CONTAINER (bbox), button);

	button = GTK_WIDGET (gtk_tool_button_new (NULL, NULL));
	gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (button), "zoom-in-symbolic");
	gtk_widget_set_tooltip_text (button, _("Zoom in"));
	g_signal_connect (button,
			  "clicked",
			  G_CALLBACK (zoom_in),
			  data->map);
	gtk_container_add (GTK_CONTAINER (bbox), button);

	button = GTK_WIDGET (gtk_tool_button_new (NULL, NULL));
	gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (button), "zoom-out-symbolic");
	gtk_widget_set_tooltip_text (button, _("Zoom out"));
	g_signal_connect (button,
			  "clicked",
			  G_CALLBACK (zoom_out),
			  data->map);
	gtk_container_add (GTK_CONTAINER (bbox), button);

	data->layer = champlain_marker_layer_new_full(CHAMPLAIN_SELECTION_SINGLE);
	champlain_view_add_layer (CHAMPLAIN_VIEW (data->map), CHAMPLAIN_LAYER(data->layer));

	sidebar = eom_window_get_sidebar (window);
	data->viewport = vbox;
	gtk_box_pack_start (GTK_BOX (vbox), bbox, FALSE, FALSE, 0);
	gtk_widget_set_vexpand (viewport, TRUE);
	gtk_container_add (GTK_CONTAINER (vbox), viewport);
	eom_sidebar_add_page (EOM_SIDEBAR (sidebar), _("Map"), vbox);
	gtk_widget_show_all (vbox);

	thumbview = eom_window_get_thumb_view (window);
	data->selection_changed_id = g_signal_connect (G_OBJECT (thumbview),
						       "selection-changed",
						       G_CALLBACK (selection_changed_cb),
						       data);

	/* Call the callback because if the plugin is activated after
	 *  the image is loaded, selection_changed isn't emited
	 */
	selection_changed_cb (EOM_THUMB_VIEW (thumbview), data);
}

static void
impl_deactivate (EomPlugin *plugin,
		 EomWindow *window)
{
	WindowData *data;
	GtkWidget *sidebar, *thumbview;

	eom_debug (DEBUG_PLUGINS);

	data = g_object_get_data (G_OBJECT (window), WINDOW_DATA_KEY);
	g_return_if_fail (data != NULL);

	sidebar = eom_window_get_sidebar (window);
	eom_sidebar_remove_page (EOM_SIDEBAR (sidebar), data->viewport);

	thumbview = eom_window_get_thumb_view (window);
	g_signal_handler_disconnect (thumbview, data->selection_changed_id);

	g_object_set_data (G_OBJECT (window), WINDOW_DATA_KEY, NULL);
}

static void
eom_map_plugin_class_init (EomMapPluginClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	EomPluginClass *plugin_class = EOM_PLUGIN_CLASS (klass);

	object_class->finalize = eom_map_plugin_finalize;

	plugin_class->activate = impl_activate;
	plugin_class->deactivate = impl_deactivate;
}
