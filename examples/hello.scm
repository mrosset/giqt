#!/usr/bin/guile -s
!#
;; hello.scm
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

(use-modules (g-golf))

(gi-import "Gio")
(gi-import "Qt")

(for-each (lambda (x)
            (gi-import-by-name "Gtk" x))
          '("Widget" "init" "main"))

(gtk-init #f #f)
(let ((app (make <qt-application> #:application-id "org.examples.scheme"))
      (window (make <qt-widget>))
      (line-edit (make <qt-line-edit>))
      (label (make <qt-label> #:label "Hello GNU! from scheme"))
      (view (make <qt-web-view>))
      (button (make <qt-button>))
      )
  (gtk-container-add window view)
  (gtk-container-add window label)
  (gtk-container-add window button)
  (gtk-container-add window line-edit)
  (qt-web-view-load-uri view "http://gnu.org")
  (gtk-widget-grab-focus line-edit)
  (gtk-widget-show-all window)
  (g-application-run app 0 #f))
