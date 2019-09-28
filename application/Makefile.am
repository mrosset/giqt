## Makefile.am
## Copyright (C) 2017-2018 Michael Rosset <mike.rosset@gmail.com>

## This file is part of giqt

## giqt is free software: you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by the
## Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.

## giqt is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
## See the GNU General Public License for more details.

## You should have received a copy of the GNU General Public License along
## with this program.  If not, see <http://www.gnu.org/licenses/>.

AM_CPPFLAGS = -std=gnu++11 -Wall -Werror -Wno-write-strings

libgiqt_application_LTLIBRARIES = libgiqt-application.la
libgiqt_applicationdir = $(libexecdir)/giqt/

libgiqt_application_la_SOURCES  = qt-application.cpp qt-application.h
libgiqt_application_la_SOURCES += qt-widget.cpp qt-widget.h
libgiqt_application_la_SOURCES += qt-label.cpp qt-label.h
libgiqt_application_la_SOURCES += qt-window.cpp qt-window.h
libgiqt_application_la_SOURCES += util.cpp util.h

libgiqt_application_la_CPPFLAGS  = $(AM_CPPFLAGS)
libgiqt_application_la_CPPFLAGS += $(GIO_CFLAGS)
libgiqt_application_la_CPPFLAGS += $(GTK_CFLAGS)
libgiqt_application_la_CPPFLAGS += $(GLIB_CFLAGS)
libgiqt_application_la_CPPFLAGS += $(GOBJECT_CFLAGS)
libgiqt_application_la_CPPFLAGS += $(QT_WIDGET_CFLAGS)
libgiqt_application_la_CPPFLAGS += $(QT_WEBENGINE_WIDGETS_CFLAGS)
libgiqt_application_la_CPPFLAGS += $(QT_WEBENGINE_CFLAGS)

libgiqt_application_la_LIBADD  = $(GIO_LIBS)
libgiqt_application_la_LIBADD += $(GTK_LIBS)
libgiqt_application_la_LIBADD += $(GLIB_LIBS)
libgiqt_application_la_LIBADD += $(GOBJECT_LIBS)
libgiqt_application_la_LIBADD += $(QT_WIDGET_LIBS)
libgiqt_application_la_LIBADD += $(QT_WEBENGINE_WIDGETS_LIBS)
libgiqt_application_la_LIBADD += $(QT_WEBENGINE_LIBS)

libgiqt_application_la_LDFLAGS = -avoid-version -no-undefined

-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS =
INTROSPECTION_SCANNER_ARGS = --add-include-path=$(srcdir) --warn-all \
	--include GObject-2.0 \
	--include Gio-2.0 \
	--include Gtk-3.0 \
	--pkg=gtk+-3.0 --pkg=gio-2.0

INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir)

introspection_sources  =
introspection_sources += qt-application.h
introspection_sources += qt-window.h
introspection_sources += qt-widget.h
introspection_sources += qt-label.h

Qt-1.0.gir: libgiqt-application.la Makefile.am
Qt_1_0_INCLUDES =
Qt_1_0_gir_CFLAGS = $(libgiqt_la_CPPFLAGS)
Qt_1_0_gir_LIBS = libgiqt-application.la
Qt_1_0_gir_FILES = $(introspection_sources)
INTROSPECTION_GIRS += Qt-1.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES = $(gir_DATA) $(typelib_DATA)
