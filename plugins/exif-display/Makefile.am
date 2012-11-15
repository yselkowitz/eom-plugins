# ExifDisplay plugin
plugindir = $(libdir)/eom/plugins

INCLUDES = \
	-I$(top_srcdir)/src 				\
	$(EOM_CFLAGS) 					\
	$(WARN_CFLAGS)					\
	$(EXIFDISPLAY_CFLAGS)				\
	-DEOM_LOCALEDIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DEOM_PLUGINDIR=\""$(plugindir)"\"

plugin_LTLIBRARIES = libexif-display.la

libexif_display_la_SOURCES = \
	eom-exif-display-plugin.h			\
	eom-exif-display-plugin.c

libexif_display_la_LDFLAGS = \
	$(PLUGIN_LIBTOOL_FLAGS)

libexif_display_la_LIBADD = $(EOM_LIBS)			\
	$(EXIFDISPLAY_LIBS)

# Plugin Info

plugin_in_files = exif-display.eom-plugin.desktop.in

UI_FILES = exif-display.ui exif-display-config.ui
ui_DATA = $(UI_FILES)
uidir = $(plugindir)/exif-display

%.eom-plugin: %.eom-plugin.desktop.in $(INTLTOOL_MERGE) $(wildcard $(top_srcdir)/po/*po) ; $(AM_V_GEN)$(INTLTOOL_MERGE) $(top_srcdir)/po $< $@ -d -u -c $(top_builddir)/po/.intltool-merge-cache

plugin_DATA = $(plugin_in_files:.eom-plugin.desktop.in=.eom-plugin)

EXTRA_DIST = $(plugin_in_files) $(UI_FILES)

CLEANFILES = $(plugin_DATA)
DISTCLEANFILES = $(plugin_DATA)

-include $(top_srcdir)/git.mk
