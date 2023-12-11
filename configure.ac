## configure.ac

AC_PREREQ([2.71]) dnl could propbable be lower
AC_INIT([t3],[0.2.1],[klmanion@gmail.com])
AC_CONFIG_AUX_DIR([config])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CC
AC_LANG([C])

PKG_CHECK_MODULES([SDL], [sdl2 >= 2.0.0],
		  [CFLAGS="$CFLAGS $SDL_CFLAGS" LIBS="$LIBS $SDL_LIBS"],
		  AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!]))

AC_CHECK_LIB([m], [sin],
	     [LIBS="$LIBS -lm"],
	     AC_MSG_ERROR([could not find math]))

#PKG_CHECK_MODULES([bsd], [sys/cdefs.h],
#	     [CFLAGS="$CFLAGS -isystem /usr/include/bsd -DLIBBSD_OVERLAY"
#	      LIBS="$LIBS -lbsd"],
#	     AC_MSG_ERROR([could not find libbsd]))

AC_CHECK_LIB([bsd], [getopt_long],
	     [CFLAGS="$CFLAGS -isystem /usr/include/bsd -DLIBBSD_OVERLAY"
	      LIBS="$LIBS -lbsd"],
	     AC_MSG_ERROR([could not find libbsd]))


AC_CHECK_INCLUDES_DEFAULT
AC_PROG_EGREP

AC_FUNC_MALLOC

AC_CONFIG_FILES([
 Makefile
 src/Makefile
])

AC_OUTPUT

