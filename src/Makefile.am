AM_CXXFLAGS = \
  -DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
  -DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
  -DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

bin_PROGRAMS = GtkPass
TESTS = GtkPassTest

BUILT_SOURCES = \
  gtkpass-resources.h \
  gtkpass-resources.c

GtkPass_SOURCES = \
  $(BUILT_SOURCES) \
  main.cpp \
  RandomGenerator.h \
  RandomGenerator.cpp \
  Application.h \
  Application.cpp \
  MainWindow.h \
  MainWindow.cpp

GtkPass_CPPFLAGS = \
  $(GTKMM_CFLAGS)

GtkPass_LDADD = \
  $(GTKMM_LIBS) \
  $(SODIUM_LIBS)

GtkPassTest_SOURCES = \
  catch.hpp \
  RandomGenerator.h \
  RandomGenerator.cpp \
  testMain.cpp \
  RandomGenerator_Test.cpp

GtkPassTest_LDADD = \
  $(SODIUM_LIBS)

noinst_PROGRAMS = \
  $(TESTS)

resource_files = $(shell glib-compile-resources --sourcedir=$(top_srcdir)/data --generate-dependencies $(top_srcdir)/data/gtkpass.gresource.xml)

gtkpass-resources.c: $(top_srcdir)/data/gtkpass.gresource.xml $(resource_files) ; glib-compile-resources --target=$@ --sourcedir=$(top_srcdir)/data --generate-source --c-name gtkpass $(top_srcdir)/data/gtkpass.gresource.xml

gtkpass-resources.h: $(top_srcdir)/data/gtkpass.gresource.xml $(resource_files) ; glib-compile-resources --target=$@ --sourcedir=$(top_srcdir)/data --generate-header --c-name gtkpass $(top_srcdir)/data/gtkpass.gresource.xml

CLEANFILES = \
  $(BUILT_SOURCES)
