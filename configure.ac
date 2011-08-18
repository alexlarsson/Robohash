AC_PREREQ(2.53)

AC_INIT([librobohash], [0.1], [http://robohash.org])

AC_PROG_CC
AM_PROG_CC_C_O
AC_DISABLE_STATIC
AC_PROG_LIBTOOL
AC_CHECK_PROG(PYTHON, python, python)

AC_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE([1.11 no-define no-dist-gzip dist-bzip2 tar-ustar foreign])

pkg_modules="glib-2.0 gdk-pixbuf-2.0"
PKG_CHECK_MODULES(ROBOHASH, [$pkg_modules])
AC_SUBST(ROBOHASH_CFLAGS)
AC_SUBST(ROBOHASH_LIBS)
AC_OUTPUT([
        Makefile
	librobohash.pc
])
