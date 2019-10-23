(load (string-append
                 (dirname (current-filename))
                 "/guix/nongnu/packages/qt.scm"))

(use-modules ((guix licenses) #:prefix license:)
             (gnu packages autotools)
             (gnu packages base)
             (gnu packages compression)
             (gnu packages glib)
             (gnu packages gtk)
             (gnu packages guile)
             (gnu packages guile-xyz)
             (gnu packages lisp)
             (gnu packages gnome)
             (gnu packages gettext)
             (gnu packages python)
             (gnu packages texinfo)
             (gnu packages pkg-config)
             (guix build-system gnu)
             (guix build-system trivial)
             (guix git-download)
             (guix utils)
             (guix download)
             (nongnu packages qt)
             (guix packages))

(define-public g-golf
  (let ((texinfo-6.6
         (package (inherit texinfo)
                  (name "texinfo")
                  (version "6.6")
                  (source (origin
                            (method url-fetch)
                            (uri (string-append "mirror://gnu/texinfo/texinfo-"
                                                version ".tar.xz"))
                            (sha256
                             (base32
                              "0rixv4c301djr0d0cnsxs8c1wjndi6bf9vi5axz6mwjkv80cmfcv")))))))

    (let ((commit "4beaad6d2c1ea63bf2b832a47bd91b34dfdf693a"))
      (package
        (name "g-golf")
        (version (git-version "1" "1" commit))
        (source (origin
                  (method git-fetch)
                  (uri (git-reference
                        (url "https://git.savannah.gnu.org/git/g-golf.git")
                        (commit commit)))
                  (file-name (git-file-name name version))
                  (sha256
                   (base32
                    "0q8nyncf2lmhl1m1skyv6phryp3rpkb5fxxy4r7fslq480x689yj"))))
        (build-system gnu-build-system)
        (native-inputs
         `(("autoconf" ,autoconf)
           ("automake" ,automake)
           ("texinfo" ,texinfo-6.6)
           ("gettext" ,gettext-minimal)
           ("libtool" ,libtool)
           ("clutter" ,clutter) ;; probably want to remove this clutter?
           ;; FIXME: clutter is only required for tests
           ("pkg-config" ,pkg-config)))
        (inputs
         `(("guile" ,guile-2.2)
           ("guile-lib" ,guile-lib)
           ("glib" ,glib)
           ("gobject-introspection" ,gobject-introspection)))
        (arguments
         `(#:tests? #t
           #:modules ((ice-9 popen)
                    (ice-9 rdelim)
                    ,@%gnu-build-system-modules)
           #:phases
           (modify-phases %standard-phases
             (add-before 'configure 'setenv
               (lambda _
                 (setenv "GUILE_AUTO_COMPILE" "0")
                 #t))
              (add-before 'build 'substitute-libs
                (lambda* (#:key inputs #:allow-other-keys)
                  (let* ((get (lambda* (x #:optional (path ""))
                                (string-append (assoc-ref inputs x) "/lib/" path)))
                         (gi (get "gobject-introspection" "libgirepository-1.0.so"))
                         (glib (get "glib" "libglib-2.0.so"))
                         (gobject (get "glib" "libgobject-2.0.so")))
                    (substitute* "g-golf/init.scm"
                                (("libgirepository-1.0") gi)
                                (("libglib-2.0") glib)
                                (("libgobject-2.0") gobject))
                    #t)))
              (add-after 'install 'install-guile-modules
                (lambda* (#:key inputs outputs #:allow-other-keys)
                  (let* ((out (assoc-ref outputs "out"))
                         (guile (assoc-ref inputs "guile"))
                         (effective (read-line (open-pipe* OPEN_READ
                                                           "guile" "-c"
                                                           "(display (effective-version))")))
                         (go-path (string-append out "/lib/guile/" effective "/site-ccache"))
                         (scm-path (string-append out "/share/guile/site/" effective)))
                    (mkdir-p go-path)
                    (mkdir-p scm-path)
                    (copy-recursively (string-append out
                                                     "/lib/g-golf/guile/" effective "/site-ccache")
                                      go-path)
                    (copy-recursively (string-append out
                                                     "/share/g-golf")
                                      scm-path)))))))
        ;; (native-search-paths
        ;;  (list (search-path-specification
        ;;         (file-type 'directory)
        ;;         (separator ":")
        ;;         (variable "LD_LIBRARY_PATH")
        ;;         (files '("lib")))))
        (home-page "https://www.gnu.org/software/g-golf/")
        (synopsis "G-Golf is a Guile Object Library for GNOME")
        (description "G-Golf low level API comprises a binding to - (most of) the
GObject Introspection and (some of) the GObject and Glib libraries, as well as
additional (G-Golf) utilities - used to import GObject libraries and build
their corresponding G-Golf high level API.")
        (license license:lgpl3+)))))

(define-public giqt
  (let ((commit "8af4618124f707558a1e00b1b7dbef044e8c4311"))
    (package (name "giqt")
             (version "0.0.1-alpha")
             (source (origin (method git-fetch)
                             (uri (git-reference (url "https://github.com/mrosset/giqt.git")
                                                 (commit commit)))
                             (file-name (git-file-name name version))
                             (sha256 (base32 "03vmsdfg3yb4ns9flv2vdb903iyavzcvn641jkpcnl10hisii7jh"))))
             (build-system gnu-build-system)
             (native-inputs `(("autoconf" ,autoconf)
                              ("automake" ,automake)
                              ("pkg-config" ,pkg-config)
                              ("libtool" ,libtool)))
             (inputs `(("glib" ,glib)
                       ("python" ,python)
                       ("guile" ,guile-2.2)
                       ("guile-lib" ,guile-lib)
                       ("sbcl" ,sbcl)
                       ("gtk+" ,gtk+)
                       ("gobject" ,gobject-introspection)
                       ("g-golf" ,g-golf)
                       ("qt" ,qt)))
             (synopsis "GObject bindings for QT")
             ;; (native-search-paths
             ;;  (list (search-path-specification
             ;;         (file-type 'directory)
             ;;         (separator ":")
             ;;         (variable "GI_TYPELIB_PATH")
             ;;         (files '("lib/girepository-1.0")))))
             (description "GIQT allows creating QT programs with the same programming interfaces as GTK")
             (home-page "https://github.com/mrosset/giqt")
             (license license:gpl3+))))

giqt
