AC_INIT([Pong], [1.1], [hugh.stuckless@hotmail.com])
AC_CONFIG_SRCDIR([src/main.cpp])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_CONDITIONAL([WINDOWS], [test "$target_os" = "mingw32"])
AC_PROG_CXX
AC_PROG_INSTALL
if test "$target_os" = "mingw32"; then
  AC_CHECK_LIB([raylib], [main], , [AC_MSG_ERROR([libraylib not found])])
  LDFLAGS="$LDFLAGS -L$abs_top_srcdir/lib"
else
  AC_CHECK_LIB([raylib], [main], , [AC_MSG_ERROR([libraylib not found])])
fi
AC_CHECK_HEADER([raylib.h], , [AC_MSG_ERROR([raylib.h not found])])
AC_CONFIG_FILES([
    Makefile
    src/Makefile
])
AC_OUTPUT