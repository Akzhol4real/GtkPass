AC_PREREQ([2.69])
AC_INIT([GtkPass], [0.1.0], [https://github.com/Darth-Revan/GtkPass/issues])

AC_CONFIG_AUX_DIR([aux_build])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11 dist-xz foreign subdir-objects])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_PROG_CC
AC_PROG_CXX

# check for compiler flags
AX_CHECK_COMPILE_FLAG([-std=c++11], AX_APPEND_FLAG("-std=c++11", [CXXFLAGS]), [
  echo "ERROR! Compiler does not support C++11."
  exit -1
])
AX_CHECK_COMPILE_FLAG([-Wall], AX_APPEND_FLAG("-Wall", [CXXFLAGS]))
AX_CHECK_COMPILE_FLAG([-pedantic], AX_APPEND_FLAG("-pedantic", [CXXFLAGS]))
AX_CHECK_COMPILE_FLAG([-Werror], AX_APPEND_FLAG("-Werror", [CXXFLAGS]))

# check for libraries
PKG_CHECK_MODULES([GTKMM], [gtkmm-3.0], [], AC_MSG_ERROR([Failed to find gtkmm-3.0!]))
PKG_CHECK_MODULES([SODIUM], [libsodium], [], AC_MSG_ERROR([Failed to find libsodium!]))

# GNOME/Gtk stuff
GLIB_COMPILE_RESOURCES=`$PKG_CONFIG --variable glib_compile_resources gio-2.0`
AC_SUBST(GLIB_COMPILE_RESOURCES)
APPSTREAM_XML

AC_CONFIG_FILES([
  Makefile
  src/Makefile
  data/Makefile
])
AC_OUTPUT
