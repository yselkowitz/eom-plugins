# Slideshow Shuffle plugin
plugindir = $(libdir)/eom/plugins
plugin_in_files = slideshowshuffle.eom-plugin.desktop.in

plugin_PYTHON = \
	slideshowshuffle.py

%.eom-plugin: %.eom-plugin.desktop.in $(INTLTOOL_MERGE) $(wildcard $(top_srcdir)/po/*po) ; $(AM_V_GEN)$(INTLTOOL_MERGE) $(top_srcdir)/po $< $@ -d -u -c $(top_builddir)/po/.intltool-merge-cache

plugin_DATA = $(plugin_in_files:.eom-plugin.desktop.in=.eom-plugin)

EXTRA_DIST = $(plugin_in_files)

CLEANFILES = $(plugin_DATA)
DISTCLEANFILES = $(plugin_DATA)

-include $(top_srcdir)/git.mk
