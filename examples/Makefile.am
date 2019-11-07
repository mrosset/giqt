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

AUTOMAKE_OPTIONS = gnu

bin_SCRIPTS = hello.scm hello.lisp hello.js hello.py

CLEANFILES = $(bin_SCRIPTS)

do_sed = sed -e 's,[@]GUILE[@],$(GUILE),g'	\
		-e 's,[@]LIBDIR[@],$(libdir),g' \
		-e 's,[@]SBCL[@],$(SBCL),g' \
		-e 's,[@]GJS[@],$(GJS),g' \
		-e 's,[@]PYTHON[@],$(PYTHON),g' \
		-e 's,[@]CCACHEDIR[@],$(ccachedir),g'

do_subst = $(do_sed) < "$(srcdir)/$<" > "$@"; chmod +x "$@"

run_example = $(top_builddir)/pre-inst-env $(top_builddir)/examples/$<

hello.scm: hello.scm.in Makefile
	$(do_subst)

hello.js: hello.js.in Makefile
	$(do_subst)

hello.lisp: hello.lisp.in Makefile
	$(do_subst)

hello.py: hello.py.in Makefile
	$(do_subst)

run-guile: hello.scm
	$(run_example)

run-lisp: hello.lisp
	$(run_example)

run-js: hello.js
	$(run_example)

run-python: hello.py
	$(run_example)

run-all: run-guile run-python run-js run-lisp

run: run-guile
