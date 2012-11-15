# Postasa plugin
plugindir = $(libdir)/eom/plugins

INCLUDES = \
	-I$(top_srcdir) 				\
	$(EOM_CFLAGS) 					\
	$(WARN_CFLAGS)					\
	$(POSTASA_CFLAGS) 				\
	-DEOM_LOCALEDIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DEOM_PLUGINDIR=\""$(plugindir)"\"

plugin_LTLIBRARIES = libpostasa.la

libpostasa_la_SOURCES = \
	eom-postasa-plugin.h				\
	eom-postasa-plugin.c

libpostasa_la_LDFLAGS = \
	$(PLUGIN_LIBTOOL_FLAGS)				\
	$(EOM_LIBS)

libpostasa_la_LIBADD = $(EOM_LIBS)			\
	$(POSTASA_LIBS)


# Plugin Info

plugin_in_files = postasa.eom-plugin.desktop.in

UI_FILES = postasa-config.xml postasa-uploads.xml
ui_DATA = $(UI_FILES)
uidir = $(plugindir)/postasa

%.eom-plugin: %.eom-plugin.desktop.in $(INTLTOOL_MERGE) $(wildcard $(top_srcdir)/po/*po) ; $(AM_V_GEN)$(INTLTOOL_MERGE) $(top_srcdir)/po $< $@ -d -u -c $(top_builddir)/po/.intltool-merge-cache

plugin_DATA = $(plugin_in_files:.eom-plugin.desktop.in=.eom-plugin)

EXTRA_DIST = $(plugin_in_files) $(UI_FILES)

CLEANFILES = $(plugin_DATA)
DISTCLEANFILES = $(plugin_DATA)

-include $(top_srcdir)/git.mk
