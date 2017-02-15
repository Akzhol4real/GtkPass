AM_CPPFLAGS = \
  -I$(topsrcdir)/src/

TESTS = \
  GtkPassTest

GtkPassTest_SOURCES = \
  catch.hpp \
  mainTest.cpp

GtkPassTest_LDADD = \
  $(SODIUM_LIBS)

noinst_PROGRAMS = \
  $(TESTS)
