#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "eom-postr-plugin.h"

#include <gmodule.h>
#include <glib/gi18n-lib.h>

#include <eom/eom-debug.h>
#include <eom/eom-thumb-view.h>
#include <eom/eom-image.h>

#define WINDOW_DATA_KEY "EomPostrWindowData"
#define MENU_PATH "/MainMenu/ToolsMenu/ToolsOps_2"

EOM_PLUGIN_REGISTER_TYPE(EomPostrPlugin, eom_postr_plugin)

typedef struct
{
	GtkActionGroup *ui_action_group;
	guint ui_id;
} WindowData;

static void
postr_cb (GtkAction	*action,
	  EomWindow *window)
{
	GtkWidget *thumbview = eom_window_get_thumb_view (window);
	GList *images, *i;
	gchar *cmd = g_strdup ("postr ");

	images = eom_thumb_view_get_selected_images (EOM_THUMB_VIEW (thumbview));

	for (i = g_list_first (images); i; i = i->next) {
		EomImage *image = (EomImage *) i->data;
		GFile *imgfile;
		gchar *imgpath;

		imgfile = eom_image_get_file (image);
		imgpath = g_file_get_path (imgfile);

		if (G_LIKELY (imgpath != NULL))
			cmd = g_strconcat (cmd, "\"", imgpath, "\"", " ", NULL);

		g_free (imgpath);
		g_object_unref (imgfile);
	}

	g_spawn_command_line_async (cmd, NULL);
}

static const GtkActionEntry action_entries[] =
{
	{ "RunPostr",
	  "postr",
	  N_("Upload to Flickr"),
	  NULL,
	  N_("Upload your pictures to Flickr"),
	  G_CALLBACK (postr_cb) }
};

static void
free_window_data (WindowData *data)
{
	g_return_if_fail (data != NULL);

	eom_debug (DEBUG_PLUGINS);

	g_object_unref (data->ui_action_group);

	g_free (data);
}

static void
eom_postr_plugin_init (EomPostrPlugin *plugin)
{
	eom_debug_message (DEBUG_PLUGINS, "EomPostrPlugin initializing");
}

static void
eom_postr_plugin_finalize (GObject *object)
{
	eom_debug_message (DEBUG_PLUGINS, "EomPostrPlugin finalizing");

	G_OBJECT_CLASS (eom_postr_plugin_parent_class)->finalize (object);
}

static void
impl_activate (EomPlugin *plugin,
	       EomWindow *window)
{
	GtkUIManager *manager;
	WindowData *data;

	eom_debug (DEBUG_PLUGINS);

	data = g_new (WindowData, 1);
	manager = eom_window_get_ui_manager (window);

	data->ui_action_group = gtk_action_group_new ("EomPostrPluginActions");

	gtk_action_group_set_translation_domain (data->ui_action_group,
						 GETTEXT_PACKAGE);
	gtk_action_group_add_actions (data->ui_action_group,
				      action_entries,
				      G_N_ELEMENTS (action_entries),
				      window);

	gtk_ui_manager_insert_action_group (manager,
					    data->ui_action_group,
					    -1);

	data->ui_id = gtk_ui_manager_new_merge_id (manager);

	g_object_set_data_full (G_OBJECT (window),
				WINDOW_DATA_KEY,
				data,
				(GDestroyNotify) free_window_data);

	gtk_ui_manager_add_ui (manager,
			       data->ui_id,
			       MENU_PATH,
			       "RunPostr",
			       "RunPostr",
			       GTK_UI_MANAGER_MENUITEM,
			       FALSE);
}

static void
impl_deactivate	(EomPlugin *plugin,
		 EomWindow *window)
{
	GtkUIManager *manager;
	WindowData *data;

	eom_debug (DEBUG_PLUGINS);

	manager = eom_window_get_ui_manager (window);

	data = (WindowData *) g_object_get_data (G_OBJECT (window),
						 WINDOW_DATA_KEY);
	g_return_if_fail (data != NULL);

	gtk_ui_manager_remove_ui (manager,
				  data->ui_id);

	gtk_ui_manager_remove_action_group (manager,
					    data->ui_action_group);

	g_object_set_data (G_OBJECT (window),
			   WINDOW_DATA_KEY,
			   NULL);
}

static void
impl_update_ui (EomPlugin *plugin,
		EomWindow *window)
{
	WindowData *data;

	eom_debug (DEBUG_PLUGINS);

	data = (WindowData *) g_object_get_data (G_OBJECT (window),
						 WINDOW_DATA_KEY);
}

static void
eom_postr_plugin_class_init (EomPostrPluginClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	EomPluginClass *plugin_class = EOM_PLUGIN_CLASS (klass);

	object_class->finalize = eom_postr_plugin_finalize;

	plugin_class->activate = impl_activate;
	plugin_class->deactivate = impl_deactivate;
	plugin_class->update_ui = impl_update_ui;
}
