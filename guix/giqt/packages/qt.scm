(define-module (giqt packages qt))

(use-modules (gnu packages cups)
	     (gnu packages linux)
	     ((guix licenses) #:prefix license:)
	     (gnu packages bison)
	     (gnu packages compression)
	     (gnu packages databases)
	     (gnu packages flex)
	     (gnu packages fontutils)
	     (gnu packages freedesktop)
	     (gnu packages gl)
	     (gnu packages glib)
	     (gnu packages gperf)
	     (gnu packages gstreamer)
	     (gnu packages gtk)
	     (gnu packages icu4c)
	     (gnu packages image)
	     (gnu packages maths)
	     (gnu packages ninja)
	     (gnu packages nss)
	     (gnu packages pciutils)
	     (gnu packages pcre)
	     (gnu packages perl)
	     (gnu packages pkg-config)
	     (gnu packages pulseaudio)
	     (gnu packages python)
	     (gnu packages ruby)
	     (gnu packages re2c)
	     (gnu packages sqlite)
	     (gnu packages tls)
	     (gnu packages vulkan)
	     (gnu packages xdisorg)
	     (gnu packages xml)
	     (gnu packages xorg)
	     (guix build-system gnu)
	     (guix download)
	     (guix packages)
	     (guix utils))

(define-public qt
  (package
    (name "qt")
    (version "5.14.0")
    (outputs '("out" "examples"))
    (source (origin
	     (method url-fetch)
	     (uri
	       (string-append
		 "http://download.qt.io/official_releases/qt/"
		 (version-major+minor version)
		 "/" version
		 "/single/qt-everywhere-src-"
		 version ".tar.xz"))
	     (sha256
	      (base32
	       "1fm8frpl4f2h7rsrh0ysn3k9i94yw4xpbl11hssp178z9v6pg6my"))
	     (modules '((guix build utils)))
	     (snippet
	      '(begin
		;; The following snippets are copied from their mondular-qt counterparts.
		(for-each
		  (lambda (dir)
		    (delete-file-recursively (string-append "qtbase/src/3rdparty/" dir)))
		  (list "double-conversion" "freetype" "harfbuzz-ng"
			"libpng" "libjpeg" "pcre2" "sqlite" "xcb"
			"zlib"))
		(for-each
		  (lambda (dir)
		    (delete-file-recursively dir))
		  (list "qtimageformats/src/3rdparty"
			"qtmultimedia/examples/multimedia/spectrum/3rdparty"
			"qtwayland/examples"
			"qtscxml/tests/3rdparty"))
		;; Tests depend on this example, which depends on the 3rd party code.
		(substitute* "qtmultimedia/examples/multimedia/multimedia.pro"
		  (("spectrum") "#"))
		(substitute* "qtxmlpatterns/tests/auto/auto.pro"
		  (("qxmlquery") "# qxmlquery")
		  (("xmlpatterns ") "# xmlpatterns"))
		(substitute* "qtwebglplugin/tests/plugins/platforms/platforms.pro"
		  (("webgl") "# webgl"))
		(substitute* "qtscxml/tests/auto/auto.pro"
		  (("scion") "#"))
		(substitute* "qtnetworkauth/tests/auto/auto.pro"
		  (("oauth1 ") "# oauth1 "))
		(substitute* "qtremoteobjects/tests/auto/qml/qml.pro"
		  (("integration") "# integration")
		  (("usertypes") "# usertypes"))
		#t))))
    (build-system gnu-build-system)
    (propagated-inputs
     `(("mesa" ,mesa)))
    (inputs
     `(("alsa-lib" ,alsa-lib)
       ("bluez" ,bluez)
       ("cups" ,cups)
       ("dbus" ,dbus)
       ("double-conversion" ,double-conversion)
       ("expat" ,expat)
       ("fontconfig" ,fontconfig)
       ("freetype" ,freetype)
       ("glib" ,glib)
       ("gstreamer" ,gstreamer)
       ("gst-plugins-base" ,gst-plugins-base)
       ("harfbuzz" ,harfbuzz)
       ("icu4c" ,icu4c)
       ("jasper" ,jasper)
       ("libinput" ,libinput-minimal)
       ("libjpeg" ,libjpeg)
       ("libmng" ,libmng)
       ("libpci" ,pciutils)
       ("libpng" ,libpng)
       ("libtiff" ,libtiff)
       ("libwebp" ,libwebp)
       ("libx11" ,libx11)
       ("libxcomposite" ,libxcomposite)
       ("libxcursor" ,libxcursor)
       ("libxext" ,libxext)
       ("libxfixes" ,libxfixes)
       ("libxi" ,libxi)
       ("libxinerama" ,libxinerama)
       ("libxkbcommon" ,libxkbcommon)
       ("libxml2" ,libxml2)
       ("libxrandr" ,libxrandr)
       ("libxrender" ,libxrender)
       ("libxslt" ,libxslt)
       ("libxtst" ,libxtst)
       ("mtdev" ,mtdev)
       ("mariadb" ,mariadb)
       ("nss" ,nss)
       ("openssl" ,openssl)
       ("postgresql" ,postgresql)
       ("pcre2" ,pcre2)
       ("sqlite" ,sqlite-with-column-metadata)
       ("udev" ,eudev)
       ("unixodbc" ,unixodbc)
       ("wayland" ,wayland)
       ("xcb-util" ,xcb-util)
       ("xcb-util-image" ,xcb-util-image)
       ("xcb-util-keysyms" ,xcb-util-keysyms)
       ("xcb-util-renderutil" ,xcb-util-renderutil)
       ("xcb-util-wm" ,xcb-util-wm)
       ("zlib" ,zlib)))
    (native-inputs
     `(("bison" ,bison)
       ("flex" ,flex)
       ("gperf" ,gperf)
       ("perl" ,perl)
       ("pkg-config" ,pkg-config)
       ("python" ,python-2)
       ("ninja" ,ninja)
       ("ruby" ,ruby)
       ("re2c" ,re2c)
       ("vulkan-headers" ,vulkan-headers)
       ("which" ,(@ (gnu packages base) which))))
    (arguments
     `(#:parallel-build? #t
       #:phases
       (modify-phases %standard-phases
	 (add-after 'configure 'patch-bin-sh
	   (lambda _
	     (substitute* '("qtbase/configure"
			    "qtbase/mkspecs/features/qt_functions.prf"
			    "qtbase/qmake/library/qmakebuiltins.cpp")
			  (("/bin/sh") (which "sh")))
	     #t))
	 (replace 'configure
	   (lambda* (#:key outputs #:allow-other-keys)
	     (let ((out      (assoc-ref outputs "out"))
		   (examples (assoc-ref outputs "examples")))
	       (substitute* '("configure" "qtbase/configure")
		 (("/bin/pwd") (which "pwd")))
	       (substitute* "qtbase/src/corelib/global/global.pri"
		 (("/bin/ls") (which "ls")))
	       (setenv "MAKEFLAGS" "-sw")
	       (setenv "PYTHONDONTWRITEBYTECODE" "1")
	       (setenv "NINJAFLAGS" "-k1")
	       (invoke
		 "./configure"
		 "-prefix" out
		 "-docdir" (string-append out "/share/doc/qt5")
		 "-headerdir" (string-append out "/include/qt5")
		 "-archdatadir" (string-append out "/lib/qt5")
		 "-datadir" (string-append out "/share/qt5")
		 "-examplesdir" (string-append
				  examples "/share/doc/qt5/examples") ; 151Mob
		 "-opensource"
		 "-confirm-license"
		 "-debug"
		 ;; Do not build examples; for the time being, we
		 ;; prefer to save the space and build time.
		 "-no-compile-examples"
		 "-nomake" "examples"
		 ;; Most "-system-..." are automatic, but some use
		 ;; the bundled copy by default.
		 "-system-sqlite"
		 "-system-harfbuzz"
		 "-system-pcre"
		 ;; explicitly link with openssl instead of dlopening it
		 "-openssl-linked"
		 ;; explicitly link with dbus instead of dlopening it
		 "-dbus-linked"
		 ;; "-no-webengine-pulseaudio"
		 ;; don't use the precompiled headers
		 ;; "-no-pch"
		 ;; drop special machine instructions not supported
		 ;; on all instances of the target
		 ,@(if (string-prefix? "x86_64"
				       (or (%current-target-system)
					   (%current-system)))
		       '()
		       '("-no-sse2"))
		 "-no-mips_dsp"
		 "-no-mips_dspr2")
	       ))))))
      (native-search-paths
       (list (search-path-specification
	      (variable "QMAKEPATH")
	      (files '("lib/qt5")))
	     (search-path-specification
	      (variable "QML2_IMPORT_PATH")
	      (files '("lib/qt5/qml")))
	     (search-path-specification
	      (variable "QT_PLUGIN_PATH")
	      (files '("lib/qt5/plugins")))
	     (search-path-specification
	      (variable "XDG_DATA_DIRS")
	      (files '("share")))
	     (search-path-specification
	      (variable "XDG_CONFIG_DIRS")
	      (files '("etc/xdg")))))
      (home-page "https://www.qt.io/")
      (synopsis "Cross-platform GUI library")
      (description "Qt is a cross-platform application and UI framework for
  developers using C++ or QML, a CSS & JavaScript like language.")
      (license (list license:lgpl2.1 license:lgpl3))

    ;; Qt 4: 'QBasicAtomicPointer' leads to build failures on MIPS;
    ;; see <http://hydra.gnu.org/build/112828>.
    ;; Qt 5: assembler error; see <http://hydra.gnu.org/build/112526>.
    (supported-systems (delete "mips64el-linux" %supported-systems))))
