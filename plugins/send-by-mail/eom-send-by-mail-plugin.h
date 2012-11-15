/* SendByMail  -- Send images per email
 *
 * Copyright (C) 2009 The Free Software Foundation
 *
 * Author: Felix Riemann  <friemann@gnome.org>
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef __EOM_SEND_BY_MAIL_PLUGIN_H__
#define __EOM_SEND_BY_MAIL_PLUGIN_H__

#include <glib.h>
#include <glib-object.h>
#include <eom/eom-plugin.h>

G_BEGIN_DECLS

/*
 * Type checking and casting macros
 */
#define EOM_TYPE_SEND_BY_MAIL_PLUGIN		(eom_send_by_mail_plugin_get_type ())
#define EOM_SEND_BY_MAIL_PLUGIN(o)		(G_TYPE_CHECK_INSTANCE_CAST ((o), EOM_TYPE_SEND_BY_MAIL_PLUGIN, EomStatusbarDatePlugin))
#define EOM_SEND_BY_MAIL_PLUGIN_CLASS(k)	G_TYPE_CHECK_CLASS_CAST((k),      EOM_TYPE_SEND_BY_MAIL_PLUGIN, EomStatusbarDatePluginClass))
#define EOM_IS_SEND_BY_MAIL_PLUGIN(o)	        (G_TYPE_CHECK_INSTANCE_TYPE ((o), EOM_TYPE_SEND_BY_MAIL_PLUGIN))
#define EOM_IS_SEND_BY_MAIL_PLUGIN_CLASS(k)	(G_TYPE_CHECK_CLASS_TYPE ((k),    EOM_TYPE_SEND_BY_MAIL_PLUGIN))
#define EOM_SEND_BY_MAIL_PLUGIN_GET_CLASS(o)	(G_TYPE_INSTANCE_GET_CLASS ((o),  EOM_TYPE_SEND_BY_MAIL_PLUGIN, EomStatusbarDatePluginClass))

/* Private structure type */
typedef struct _EomSendByMailPluginPrivate	EomSendByMailPluginPrivate;

/*
 * Main object structure
 */
typedef struct _EomSendByMailPlugin		EomSendByMailPlugin;

struct _EomSendByMailPlugin
{
	EomPlugin parent_instance;
};

/*
 * Class definition
 */
typedef struct _EomSendByMailPluginClass	EomSendByMailPluginClass;

struct _EomSendByMailPluginClass
{
	EomPluginClass parent_class;
};

/*
 * Public methods
 */
GType	eom_send_by_mail_plugin_get_type		(void) G_GNUC_CONST;

/* All the plugins must implement this function */
G_MODULE_EXPORT GType register_eom_plugin (GTypeModule *module);

G_END_DECLS

#endif /* __EOM_SEND_BY_MAIL_PLUGIN_H__ */
