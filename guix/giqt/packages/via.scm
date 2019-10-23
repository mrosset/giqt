(define-module (gnu packages via))

(define-public via
  (package (name "via")
           (version "0.0.2-alpha")
           (source (origin (method url-fetch)
                           (uri "https://github.com/mrosset/via/releases/download/0.0.1-alpha/via-f1ec5aef42e5f7456d8792ea66537ae8ebdc1be9")
                           (sha256 (base32 "1b9hjfgyinz8xicyp1qmbfpc980z6yrhlwk6060y2cpzyx9fq8n7"))))
           (build-system trivial-build-system)
           (arguments
            `(#:modules ((guix build utils))
              #:builder
              (begin
                (use-modules (guix build utils))
                (copy-file (assoc-ref %build-inputs "source") "./via")
                (chmod "via" #o755)
                (install-file "via" (string-append %output "/bin"))
                #t)))
           (home-page "https://github.com/mrosset/via")
           (synopsis "via system package manager")
           (description "via system package manager")
           (license (list license:gpl3+))))
