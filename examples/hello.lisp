#!/usr/bin/sbcl --script

;; hello.lisp
;; Copyright (C) 2017-2019 Michael Rosset <mike.rosset@gmail.com>

;; This file is part of giqt

;; giqt is free software: you can redistribute it and/or modify it
;; under the terms of the GNU General Public License as published by the
;; Free Software Foundation, either version 3 of the License, or
;; (at your option) any later version.

;; giqt is distributed in the hope that it will be useful, but
;; WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
;; See the GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License along
;; with this program.  If not, see <http://www.gnu.org/licenses/>.

(load "~/quicklisp/setup.lisp")
(ql:quickload :cl-gobject-introspection)

(defvar *gtk* (gir:require-namespace "Gtk"))

;; FIXME: when using GApplication we should not need to init GTK
(gir:invoke (*gtk* 'init) '())

(let* ((qt (gir:require-namespace "Qt"))
       (application (gir:invoke (qt "Application" 'new)))
       (label (gir:invoke (qt "Label" 'new) "Hello GNU, from lisp!"))
       (button (gir:invoke (qt "Button" 'new)))
       (window (gir:invoke (qt "Widget" 'new)))
       )
  (gir:invoke (window 'add) label)
  (gir:invoke (window 'add) button)
  (gir:connect button
	       :clicked (lambda (x)
			  (gir:invoke (label 'set-text)
				      "Button Clicked!")))
  (gir:connect application
	       :activate (lambda (x)
			   (gir:invoke (window 'show-all))))
  (gir:invoke (application 'start))
  )
