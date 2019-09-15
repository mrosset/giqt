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

libgiqt_application_LTLIBRARIES = libgiqt-application.la
libgiqt_applicationdir = $(libexecdir)/giqt/

libgiqt_application_la_SOURCES =  qt-application.c qt-application.h

libgiqt_application_la_CFLAGS =  $(AM_CFLAGS)
libgiqt_application_la_CFLAGS += $(GLIB_CFLAGS)

libgiqt_application_la_LDFLAGS = -avoid-version -no-undefined

-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS =
INTROSPECTION_SCANNER_ARGS = --add-include-path=$(srcdir) --warn-all \
	--include GObject-2.0 \
	--namespace QtApplication

INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir)

introspection_sources = qt-application.h

QtApplication-1.0.gir: libgiqt-application.la
QtApplication_1_0_INCLUDES =
QtApplictaion_1_0_gir_CFLAGS = $(libgiqt_la_CFLAGS)
QtApplictaion_1_0_gir_LIBS = libgiqt-application.la
QtApplication_1_0_gir_LIBS = libgiqt-application.la
QtApplication_1_0_gir_FILES = $(introspection_sources)
INTROSPECTION_GIRS += QtApplication-1.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES = $(gir_DATA) $(typelib_DATA)
