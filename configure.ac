AC_INIT([eflfocustest], 1.0)
AM_INIT_AUTOMAKE([subdir-objects])

AC_PROG_CC
AM_PROG_CC_STDC
AC_HEADER_STDC

PKG_CHECK_MODULES([elm], [
    elementary >= 1.18.1
    efl >= 1.18.1
    ecore-input-evas >= 1.18.1
    ] )

AC_OUTPUT([
Makefile
src/Makefile
])
