## Makefile.am
## Copyright (C) 2017-2019 Michael Rosset <mike.rosset@gmail.com>

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


ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

SUBDIRS = application examples

if ENABLE_GUILE
SUBDIRS += test-suite/scheme
endif

if ENABLE_SBCL
SUBDIRS += test-suite/lisp
endif

EXTRA_DIST = m4/introspection.m4

EXAMPLES  = run-guile run-guile-gtk
EXAMPLES += run-lisp run-lisp-gtk
EXAMPLES += run-js run-python

guix: guix.scm
	guix build -f $<

$(EXAMPLES): all
	$(MAKE) -C examples $@

run-all: run-guile run-python run-js run-lisp

run: run-guile-gtk
