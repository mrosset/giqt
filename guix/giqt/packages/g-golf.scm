(define-module (giqt packages g-golf))

(use-modules ((guix licenses) #:prefix license:)
             (guix utils)
             (gnu packages autotools)
             (gnu packages gettext)
             (gnu packages glib)
             (gnu packages gnome)
             (gnu packages guile)
             (gnu packages guile-xyz)
             (gnu packages pkg-config)
             (gnu packages texinfo)
             (guix build-system gnu)
             (guix download)
             (guix git-download)
             (guix packages))

(define-public g-golf
  (let ((commit "14e2b1491f40fdffe22704cf2b60405d0f818818"))
    (package
      (name "g-golf")
      (version (git-version "1" "568" commit))
      (source (origin
                (method git-fetch)
                (uri (git-reference
                      (url "https://git.savannah.gnu.org/git/g-golf.git")
                      (commit commit)))
                (file-name (git-file-name name version))
                (sha256
                 (base32
                  "1bd7705mdjixr3f7yqari1h6qfsbink9pzvf95kcccc6nm80hjzf"))))
      (build-system gnu-build-system)
      (native-inputs
       `(("autoconf" ,autoconf)
         ("automake" ,automake)
         ("texinfo" ,texinfo)
         ("gettext" ,gettext-minimal)
         ("libtool" ,libtool)
         ("pkg-config" ,pkg-config)))
      (inputs
       `(("guile" ,guile-2.2)
         ("guile-lib" ,guile-lib)
         ("glib" ,glib)))
      (propagated-inputs
       `(("gobject-introspection" ,gobject-introspection)
         ("clutter" ,clutter)))
      (arguments
       `(#:tests? #f
         #:phases
         (modify-phases %standard-phases
           (add-before 'configure 'setenv
             (lambda _
               (setenv "GUILE_AUTO_COMPILE" "0")
               #t))
           (add-before 'build 'substitute-libs
             (lambda* (#:key inputs #:allow-other-keys)
               (let* ((get (lambda (key path)
                             (string-append (assoc-ref inputs key) "/lib/" path)))
                      (gi (get "gobject-introspection" "libgirepository-1.0.so"))
                      (glib (get "glib" "libglib-2.0.so"))
                      (gobject (get "glib" "libgobject-2.0.so")))
                 (substitute* "g-golf/init.scm"
                   (("libgirepository-1.0") gi)
                   (("libglib-2.0") glib)
                   (("libgobject-2.0") gobject))
                 #t)))
           (add-after 'install 'rebase-guile-modules
             (lambda* (#:key outputs inputs #:allow-other-keys)
               (let* ((out (assoc-ref outputs "out"))
                      (version ,(version-major+minor (package-version guile-2.2)))
                      (init.scm (string-append out "/share/guile/g-golf/init.scm"))
                      (init.go (string-append out "/lib/guile/"
                                              version
                                              "/site-ccache/g-golf/init.go")))
                 ;; Because g-golf does not use the same prefix as guile re-base
                 ;; sitedir and siteccachdir to match guile's site path.
                 (rename-file (string-append out "/lib/g-golf/guile") (string-append out "/lib/guile"))
                 (rename-file (string-append out "/share/g-golf") (string-append out "/share/guile"))
                 ;; Substitute libg-golf with absolute library path
                 (substitute* init.scm
                   (("\"libg-golf\"") (format #f  "~s" (string-append out "/lib/libg-golf"))))
                 ;; Recompile init.go with the new absolute library path
                 (invoke "guild" "compile" init.scm "-o" init.go)
                 #t))))))
      (home-page "https://www.gnu.org/software/g-golf/")
      (synopsis "G-Golf is a Guile Object Library for GNOME")
      (description "G-Golf low level API comprises a binding to - (most of) the
GObject Introspection and (some of) the GObject and Glib libraries, as well as
additional (G-Golf) utilities - used to import GObject libraries and build
their corresponding G-Golf high level API.")
      (license license:lgpl3+))))
