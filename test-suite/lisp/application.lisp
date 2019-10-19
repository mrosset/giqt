;; it's easier to use quicklisp for prototyping
(unless (find-package :ql)
  (load "~/quicklisp/setup.lisp"))
(require 'asdf)
(require 'cffi)
(require 'sb-posix)
(require 'prove)

(pushnew #p"/opt/via/lib/" cffi:*foreign-library-directories*
         :test #'equal)

(asdf:load-system :cl-gobject-introspection)

(in-package :cl-user)
(defpackage giqt-test
  (:use :cl
        :prove))
(in-package :giqt-test)

(plan 3)

(let* ((qt (gir:require-namespace "Qt"))
       (application (gir:invoke (qt "Application" 'new))))
  (is "0.0.1-alpha" (gir:invoke (application 'version)))
  (is 5 (gir:invoke (qt 'major_version)))
  (is "org.unknown" (gir:property application 'application-id)))

(finalize)
