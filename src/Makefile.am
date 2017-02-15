bin_PROGRAMS = GtkPass

BUILT_SOURCES = \
  gtkpass-resources.h \
  gtkpass-resources.c

GtkPass_SOURCES = \
  $(BUILT_SOURCES) \
  main.cpp

GtkPass_CPPFLAGS = \
  $(GTKMM_CFLAGS)

GtkPass_LDADD = \
  $(GTKMM_LIBS) \
  $(SODIUM_LIBS)

resource_files = $(shell glib-compile-resources --sourcedir=$(top_srcdir)/data --generate-dependencies $(top_srcdir)/data/gtkpass.gresource.xml)

gtkpass-resources.c: $(top_srcdir)/data/gtkpass.gresource.xml $(resource_files) ; glib-compile-resources --target=$@ --sourcedir=$(top_srcdir)/data --generate-source --c-name gtkpass $(top_srcdir)/data/gtkpass.gresource.xml

gtkpass-resources.h: $(top_srcdir)/data/gtkpass.gresource.xml $(resource_files) ; glib-compile-resources --target=$@ --sourcedir=$(top_srcdir)/data --generate-header --c-name gtkpass $(top_srcdir)/data/gtkpass.gresource.xml

CLEANFILES = \
  $(BUILT_SOURCES)
