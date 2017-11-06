## configure.ac

AC_PREREQ([2.69]) dnl could propbable be lower
AC_INIT([t3], [0.1], [klmanion@gmail.com])
AC_CONFIG_AUX_DIR([config])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CC
AC_LANG_C

## Check for SDL
SDL_VERSION=2.0.7
AM_PATH_SDL2($SDL_VERSION,
			 [CFLAGS="$CFLAGS $SDL_CFLAGS"; LIBS="$LIBS $SDL_LIBS"],
			 AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!])
)

AC_HEADER_STDC

AC_FUNC_MALLOC

AC_CONFIG_FILES([
 Makefile
 src/Makefile
])

AC_OUTPUT

