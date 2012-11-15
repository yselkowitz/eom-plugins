#ifndef __EOM_POSTR_PLUGIN_H__
#define __EOM_POSTR_PLUGIN_H__

#include <glib.h>
#include <glib-object.h>
#include <eom/eom-plugin.h>

G_BEGIN_DECLS

/*
 * Type checking and casting macros
 */
#define EOM_TYPE_POSTR_PLUGIN		(eom_postr_plugin_get_type ())
#define EOM_POSTR_PLUGIN(o)		(G_TYPE_CHECK_INSTANCE_CAST ((o), EOM_TYPE_POSTR_PLUGIN, EomPostrPlugin))
#define EOM_POSTR_PLUGIN_CLASS(k)	(G_TYPE_CHECK_CLASS_CAST((k),     EOM_TYPE_POSTR_PLUGIN, EomPostrPluginClass))
#define EOM_IS_POSTR_PLUGIN(o)	        (G_TYPE_CHECK_INSTANCE_TYPE ((o), EOM_TYPE_POSTR_PLUGIN))
#define EOM_IS_POSTR_PLUGIN_CLASS(k)	(G_TYPE_CHECK_CLASS_TYPE ((k),    EOM_TYPE_POSTR_PLUGIN))
#define EOM_POSTR_PLUGIN_GET_CLASS(o)	(G_TYPE_INSTANCE_GET_CLASS ((o),  EOM_TYPE_POSTR_PLUGIN, EomPostrPluginClass))

/* Private structure type */
typedef struct _EomPostrPluginPrivate	EomPostrPluginPrivate;

/*
 * Main object structure
 */
typedef struct _EomPostrPlugin		EomPostrPlugin;

struct _EomPostrPlugin
{
	EomPlugin parent_instance;
};

/*
 * Class definition
 */
typedef struct _EomPostrPluginClass	EomPostrPluginClass;

struct _EomPostrPluginClass
{
	EomPluginClass parent_class;
};

/*
 * Public methods
 */
GType	eom_postr_plugin_get_type		(void) G_GNUC_CONST;

/* All the plugins must implement this function */
G_MODULE_EXPORT GType register_eom_plugin (GTypeModule *module);

G_END_DECLS

#endif /* __EOM_POSTR_PLUGIN_H__ */
