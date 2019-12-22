dnl configure.ac
dnl Copyright (C) 2017-2019 Michael Rosset <mike.rosset@gmail.com>

dnl This file is part of giqt

dnl giqt is free software: you can redistribute it and/or modify it
dnl under the terms of the GNU General Public License as published by the
dnl Free Software Foundation, either version 3 of the License, or
dnl (at your option) any later version.

dnl giqt is distributed in the hope that it will be useful, but
dnl WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
dnl See the GNU General Public License for more details.

dnl You should have received a copy of the GNU General Public License along
dnl with this program.  If not, see <http://www.gnu.org/licenses/>.

dnl autoconf
AC_INIT([giqt],[0.0.1-alpha],[mike.rosset@gmail.com])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIRS([m4])

dnl Force the compiler to run once and do all the basic checks
dnl if you don't, it will do the test on the first invocation
dnl below and so your pretty section titles won't work as well
AC_CHECK_HEADERS(iostream)

dnl Small macro to print out a nice, pretty section title.
dnl this macro can be found at https://www.edwardrosten.com/code/autoconf/ex_13/configure.ac
define(SECTION_TITLE,
[
        echo >& AS_MESSAGE_FD
        echo '   $1   ' | sed -e's/./-/g' >&AS_MESSAGE_FD
        echo '   $1' >& AS_MESSAGE_FD
        echo '   $1   ' | sed -e's/./-/g' >&AS_MESSAGE_FD
])

dnl optional enabled
AC_ARG_ENABLE([guile], AS_HELP_STRING([--disable-guile], [Disable guile tests]))
AC_ARG_ENABLE([sbcl], AS_HELP_STRING([--disable-sbcl], [Disable sbcl tests]))

dnl automake
AM_INIT_AUTOMAKE([-Wall gnu silent-rules color-tests serial-tests])
AM_SILENT_RULES([yes])

dnl programs
SECTION_TITLE([Checking for programs])
AC_PROG_CXX
AM_PROG_AR
AC_PROG_LN_S
AC_PROG_INSTALL
AC_PROG_MKDIR_P
AC_DISABLE_STATIC

dnl guile
AS_IF([test "x$enable_guile" != "xno"], [
SECTION_TITLE([Checking for Guile libraries])
PKG_CHECK_MODULES(G_GOLF, [g-golf-1.0])
PKG_CHECK_MODULES(GUILE_LIB, [guile-lib-1.0])
GUILE_PROGS
])

dnl sbcl
AS_IF([test "x$enable_sbcl" != "xno"], [
SECTION_TITLE([Checking for SBCL program])
AC_PATH_PROG(SBCL, sbcl, no)
AC_SUBST(SBCL)
if test "$SBCL" = "no"; then
   AC_MSG_ERROR([program sbcl is required])
fi
])

AM_CONDITIONAL([ENABLE_GUILE], [test x$enable_guile != xno])
AM_CONDITIONAL([ENABLE_SBCL], [test x$enable_sbcl != xno])

dnl libtool
LT_INIT([dlopen])

dnl python
AM_PATH_PYTHON([3.7])

SECTION_TITLE([Checking for GJS program])
AC_PATH_PROG(GJS, gjs-console, no)
AC_SUBST(GJS)

if test "GJS" = "no"; then
   AC_MSG_ERROR([program gjs-console is required])
fi

SECTION_TITLE([Checking for GTK/GLIB libraries])
PKG_CHECK_MODULES(GI_INTROSPECTION, [gobject-introspection-1.0])
PKG_CHECK_MODULES(GOBJECT, [gobject-2.0])
PKG_CHECK_MODULES(GLIB, [glib-2.0])
PKG_CHECK_MODULES(GIO, [gio-2.0])
PKG_CHECK_MODULES(GTK, [gtk+-3.0])
GOBJECT_INTROSPECTION_CHECK([1.30.0])

SECTION_TITLE([Checking for QT libraries])
PKG_CHECK_MODULES(QT_WIDGET, [Qt5Widgets])
PKG_CHECK_MODULES(QT_WEBENGINE_WIDGETS, [Qt5WebEngineWidgets])
PKG_CHECK_MODULES(QT_WEBENGINE, [Qt5WebEngine])

AC_CONFIG_FILES([
Makefile
test-suite/scheme/Makefile
test-suite/lisp/Makefile
application/Makefile
examples/Makefile
])

AC_CONFIG_FILES([pre-inst-env], [chmod +x pre-inst-env])

AC_OUTPUT

AC_MSG_NOTICE([summary of build options:

  version:              ${VERSION}
  Host/Target system:   ${host}
  Build system:         ${build}
  Install prefix:       ${prefix}
  Compiler:             ${CXX}
  CFlags:               ${CFLAGS}
  Library types:        Shared=${enable_shared}, Static=${enable_static}
])

AC_MSG_NOTICE([summary of programs:

  sbcl:                ${SBCL}
  guile:               ${GUILE}
  shell:               ${SHELL}
  guild:               ${GUILD}
  python:              ${PYTHON}
  gjs-console:         ${GJS}
])

AC_MSG_NOTICE([summary of pkg-config libraries:

  glib:                ${GLIB_LIBS}
  qtwidgets:           ${QT_WIDGET_LIBS}
])
