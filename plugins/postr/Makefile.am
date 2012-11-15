# Postr plugin
plugindir = $(libdir)/eom/plugins

INCLUDES = \
	-I$(top_srcdir) 				\
	$(EOM_CFLAGS) 					\
	$(WARN_CFLAGS)					\
	-DEOM_LOCALEDIR=\""$(prefix)/$(DATADIRNAME)/locale"\"

plugin_LTLIBRARIES = libpostr.la

libpostr_la_SOURCES = \
	eom-postr-plugin.h				\
	eom-postr-plugin.c

libpostr_la_LDFLAGS = \
	$(PLUGIN_LIBTOOL_FLAGS)				\
	$(EOM_LIBS)

# Plugin Info

plugin_in_files = postr.eom-plugin.desktop.in

%.eom-plugin: %.eom-plugin.desktop.in $(INTLTOOL_MERGE) $(wildcard $(top_srcdir)/po/*po) ; $(AM_V_GEN)$(INTLTOOL_MERGE) $(top_srcdir)/po $< $@ -d -u -c $(top_builddir)/po/.intltool-merge-cache

plugin_DATA = $(plugin_in_files:.eom-plugin.desktop.in=.eom-plugin)

EXTRA_DIST = $(plugin_in_files)

CLEANFILES = $(plugin_DATA)
DISTCLEANFILES = $(plugin_DATA)

-include $(top_srcdir)/git.mk
