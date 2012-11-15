/* Exif-display -- display information about digital pictures
 *
 * Copyright (C) 2009 The Free Software Foundation
 *
 * Author: Emmanuel Touzery  <emmanuel.touzery@free.fr>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef __EOM_EXIF_DISPLAY_PLUGIN_H__
#define __EOM_EXIF_DISPLAY_PLUGIN_H__

#include <glib.h>
#include <glib-object.h>
#include <eom/eom-plugin.h>

G_BEGIN_DECLS

/*
 * Type checking and casting macros
 */
#define EOM_TYPE_EXIF_DISPLAY_PLUGIN		(eom_fit_to_width_plugin_get_type ())
#define EOM_EXIF_DISPLAY_PLUGIN(o)		(G_TYPE_CHECK_INSTANCE_CAST ((o), EOM_TYPE_EXIF_DISPLAY_PLUGIN, EomStatusbarDatePlugin))
#define EOM_EXIF_DISPLAY_PLUGIN_CLASS(k)	G_TYPE_CHECK_CLASS_CAST((k),      EOM_TYPE_EXIF_DISPLAY_PLUGIN, EomStatusbarDatePluginClass))
#define EOM_IS_EXIF_DISPLAY_PLUGIN(o)	        (G_TYPE_CHECK_INSTANCE_TYPE ((o), EOM_TYPE_EXIF_DISPLAY_PLUGIN))
#define EOM_IS_EXIF_DISPLAY_PLUGIN_CLASS(k)	(G_TYPE_CHECK_CLASS_TYPE ((k),    EOM_TYPE_EXIF_DISPLAY_PLUGIN))
#define EOM_EXIF_DISPLAY_PLUGIN_GET_CLASS(o)	(G_TYPE_INSTANCE_GET_CLASS ((o),  EOM_TYPE_EXIF_DISPLAY_PLUGIN, EomStatusbarDatePluginClass))

/* Private structure type */
typedef struct _EomExifDisplayPluginPrivate	EomExifDisplayPluginPrivate;

/*
 * Main object structure
 */
typedef struct _EomExifDisplayPlugin		EomExifDisplayPlugin;

struct _EomExifDisplayPlugin
{
	EomPlugin parent_instance;
};

/*
 * Class definition
 */
typedef struct _EomExifDisplayPluginClass	EomExifDisplayPluginClass;

struct _EomExifDisplayPluginClass
{
	EomPluginClass parent_class;
};

/*
 * Public methods
 */
GType	eom_exif_display_plugin_get_type		(void) G_GNUC_CONST;

/* All the plugins must implement this function */
G_MODULE_EXPORT GType register_eom_plugin (GTypeModule *module);

G_END_DECLS

#endif /* __EOM_EXIF_DISPLAY_PLUGIN_H__ */
