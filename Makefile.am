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

SUBDIRS = application test-suite/scheme test-suite/lisp

EXTRA_DIST = m4/introspection.m4

guix: guix.scm
	guix build -f $<

run-guile: check
	./pre-inst-env examples/hello.scm

run-lisp: check
	./pre-inst-env examples/hello.lisp

run-js:
	./pre-inst-env examples/hello.js

run-python:
	./pre-inst-env examples/hello.py

run-all: check run-guile run-python run-js run-lisp

run: check run-guile run-lisp
