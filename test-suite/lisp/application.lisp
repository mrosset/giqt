;; it's easier to use quicklisp for prototyping
(load "~/quicklisp/setup.lisp")
(ql:quickload :prove)
(ql:quickload :cl-gobject-introspection)

(in-package :cl-user)
(defpackage giqt-test
  (:use :cl
        :prove))
(in-package :giqt-test)

;; TODO: remove the need for quicklisp
;; (require 'asdf)
;; (require 'sb-posix)

;; (asdf:load-asd (concatenate 'string
;;                             (sb-posix:getcwd)
;;                             "/cl-gobject-introspection/cl-gobject-introspection.asd"))

;; cl-gobject-introspection requires these packages
;;
;; cl-alexandria
;; cl-cffi
;; cl-iterate
;; cl-trivial-garbage

;; (require :cl-gobject-introspection)

(plan 3)

;; TODO: GApplication's are not trivial. Instead of bootstraping with an
;; Application class. Bootstrap using Windows and gtk_main?
(let* ((qt (gir:require-namespace "Qt"))
       (application (gir:invoke (qt "Application" 'new))))
  (is "0.0.1-alpha" (gir:invoke (application 'version)))
  (is "5.12.2" (gir:invoke (qt "Application" 'qt_version)))
  (is "org.unknown" (gir:property application 'application-id))
  ;; (gir:invoke (application 'start))
)

(finalize)
