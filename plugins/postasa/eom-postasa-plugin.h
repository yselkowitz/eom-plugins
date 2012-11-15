/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*- */

/* Postasa -- PicasaWeb Uploader plugin
 *
 * Copyright (C) 2009 The Free Software Foundation
 *
 * Author: Richard Schwarting <aquarichy@gmail.com>
 * Initially based on Postr code by: Lucas Rocha
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

#ifndef __EOM_POSTASA_PLUGIN_H__
#define __EOM_POSTASA_PLUGIN_H__

#include <glib.h>
#include <glib-object.h>
#include <eom/eom-plugin.h>

G_BEGIN_DECLS

/*
 * Type checking and casting macros
 */
#define EOM_TYPE_POSTASA_PLUGIN		(eom_postasa_plugin_get_type ())
#define EOM_POSTASA_PLUGIN(o)		(G_TYPE_CHECK_INSTANCE_CAST ((o), EOM_TYPE_POSTASA_PLUGIN, EomPostasaPlugin))
#define EOM_POSTASA_PLUGIN_CLASS(k)	(G_TYPE_CHECK_CLASS_CAST((k),     EOM_TYPE_POSTASA_PLUGIN, EomPostasaPluginClass))
#define EOM_IS_POSTASA_PLUGIN(o)	        (G_TYPE_CHECK_INSTANCE_TYPE ((o), EOM_TYPE_POSTASA_PLUGIN))
#define EOM_IS_POSTASA_PLUGIN_CLASS(k)	(G_TYPE_CHECK_CLASS_TYPE ((k),    EOM_TYPE_POSTASA_PLUGIN))
#define EOM_POSTASA_PLUGIN_GET_CLASS(o)	(G_TYPE_INSTANCE_GET_CLASS ((o),  EOM_TYPE_POSTASA_PLUGIN, EomPostasaPluginClass))

/* Private structure type */
typedef struct _EomPostasaPluginPrivate	EomPostasaPluginPrivate;

/*
 * Main object structure
 */
typedef struct _EomPostasaPlugin		EomPostasaPlugin;

struct _EomPostasaPlugin
{
	EomPlugin parent_instance;
	EomPostasaPluginPrivate *priv;
};

/*
 * Class definition
 */
typedef struct _EomPostasaPluginClass	EomPostasaPluginClass;

struct _EomPostasaPluginClass
{
	EomPluginClass parent_class;
};

/*
 * Public methods
 */
GType	eom_postasa_plugin_get_type		(void) G_GNUC_CONST;

/* All the plugins must implement this function */
G_MODULE_EXPORT GType register_eom_plugin (GTypeModule *module);

G_END_DECLS

#endif /* __EOM_POSTASA_PLUGIN_H__ */
