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

dnl automake
AM_INIT_AUTOMAKE([-Wall gnu silent-rules color-tests serial-tests])
AM_SILENT_RULES([yes])

dnl programs
AC_PROG_CXX
AM_PROG_AR
AC_PROG_LN_S
AC_PROG_INSTALL
AC_PROG_MKDIR_P
AC_DISABLE_STATIC

dnl libtool
LT_INIT([dlopen])

GUILE_PROGS

dnl python
AM_PATH_PYTHON([3.7])

PKG_CHECK_MODULES(GI_INTROSPECTION, [gobject-introspection-1.0])
PKG_CHECK_MODULES(GOBJECT, [gobject-2.0])
PKG_CHECK_MODULES(GLIB, [glib-2.0])
PKG_CHECK_MODULES(GIO, [gio-2.0])
PKG_CHECK_MODULES(GTK, [gtk+-3.0])
PKG_CHECK_MODULES(QT_WIDGET, [Qt5Widgets])
PKG_CHECK_MODULES(QT_WEBENGINE_WIDGETS, [Qt5WebEngineWidgets])
PKG_CHECK_MODULES(QT_WEBENGINE, [Qt5WebEngine])
PKG_CHECK_MODULES(G_GOLF, [g-golf-1.0])
PKG_CHECK_MODULES(GUILE_LIB, [guile-lib-1.0])

GOBJECT_INTROSPECTION_CHECK([1.30.0])

AC_CONFIG_FILES([
Makefile
test-suite/scheme/Makefile
test-suite/lisp/Makefile
application/Makefile
])

AC_CONFIG_FILES([pre-inst-env], [chmod +x pre-inst-env])
AC_CONFIG_FILES([examples/hello.scm], [chmod +x examples/hello.scm])
AC_CONFIG_FILES([examples/hello.py], [chmod +x examples/hello.py])

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

AC_MSG_NOTICE([summary of pkg-config libraries:

  glib:                ${GLIB_LIBS}
])
