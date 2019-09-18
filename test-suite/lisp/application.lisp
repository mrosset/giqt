;; This is probably all wrong
(load "~/quicklisp/setup.lisp")
(ql:quickload :cl-gobject-introspection)

(defvar *qt* (gir:require-namespace "Qt"))
;; we may need to init gtk at some point so keep this here
;; (gir:invoke (*gtk* 'init) nil)
(let* ((application (gir:invoke (*qt* "Application" 'new)))
      (expect "0.0.1-alpha")
      (got (gir:invoke (application 'version))))
  (when (not (string= expect got))
    (error (format nil "expected version ~A got ~A" expect got))))
