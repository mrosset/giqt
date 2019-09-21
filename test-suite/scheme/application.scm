;; application.scm
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

(use-modules (oop goops)
             (g-golf)
             (unit-test)
             (ice-9 threads))

(gi-import "Gio")
(gi-import "Qt")

;; (setenv "QT_XCB_FORCE_SOFTWARE_OPENGL" "1")
;; (setenv "QTWEBENGINEPROCESS_PATH" "/gnu/store/829z6gb6nvlrik5xx8zxxjdxim71sc8i-qtwebengine-5.11.3/lib/qt5/libexec/QtWebEngineProcess")

(define-class <test-application> (<test-case>))

(define-method (test-version (self <test-application>))
  (let ((app (make <qt-application> #:application-id "org.qt.test")))
    (assert-equal "0.0.1-alpha" (qt-application-version app))
    (assert-equal "5.12.2" (qt-application-qt-version))
    (make-thread application-run app)
    (sleep 2)))

(exit-with-summary (run-all-defined-test-cases))
