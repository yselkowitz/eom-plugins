#ifndef __EOM_MAP_PLUGIN_H__
#define __EOM_MAP_PLUGIN_H__

#include <glib.h>
#include <glib-object.h>
#include <eom/eom-plugin.h>

G_BEGIN_DECLS

/*
 * Type checking and casting macros
 */
#define EOM_TYPE_MAP_PLUGIN		(eom_map_plugin_get_type ())
#define EOM_MAP_PLUGIN(o)		(G_TYPE_CHECK_INSTANCE_CAST ((o), EOM_TYPE_MAP_PLUGIN, EomMapPlugin))
#define EOM_MAP_PLUGIN_CLASS(k)		(G_TYPE_CHECK_CLASS_CAST((k),     EOM_TYPE_MAP_PLUGIN, EomMapPluginClass))
#define EOM_IS_MAP_PLUGIN(o)		(G_TYPE_CHECK_INSTANCE_TYPE ((o), EOM_TYPE_MAP_PLUGIN))
#define EOM_IS_MAP_PLUGIN_CLASS(k)	(G_TYPE_CHECK_CLASS_TYPE ((k),    EOM_TYPE_MAP_PLUGIN))
#define EOM_MAP_PLUGIN_GET_CLASS(o)	(G_TYPE_INSTANCE_GET_CLASS ((o),  EOM_TYPE_MAP_PLUGIN, EomMapPluginClass))

/* Private structure type */
typedef struct _EomMapPluginPrivate	EomMapPluginPrivate;

/*
 * Main object structure
 */
typedef struct _EomMapPlugin		EomMapPlugin;

struct _EomMapPlugin
{
	EomPlugin parent_instance;
};

/*
 * Class definition
 */
typedef struct _EomMapPluginClass	EomMapPluginClass;

struct _EomMapPluginClass
{
	EomPluginClass parent_class;
};

/*
 * Public methods
 */
GType	eom_map_plugin_get_type		(void) G_GNUC_CONST;

/* All the plugins must implement this function */
G_MODULE_EXPORT GType register_eom_plugin (GTypeModule *module);

G_END_DECLS

#endif /* __EOM_MAP_PLUGIN_H__ */
