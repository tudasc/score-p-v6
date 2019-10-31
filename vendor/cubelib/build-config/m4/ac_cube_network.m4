##*************************************************************************##
##  CUBE        http://www.scalasca.org/                                   ##
##*************************************************************************##
##  Copyright (c) 2016                                                     ##
##  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          ##
##                                                                         ##
##  This software may be modified and distributed under the terms of       ##
##  a BSD-style license.  See the COPYING file in the package base         ##
##  directory for details.                                                 ##
##*************************************************************************##


dnl Require all listed headers to be available
dnl $1 space separated list of headers to check
dnl $2 output variable to set to yes/no, depending on header availability
dnl
AC_DEFUN([AX_REQUIRE_HEADERS],[
    $2=yes
    for header_file in $1; do
        AC_CHECK_HEADER([$header_file],[],[$2=no])
    done
])

dnl Enable the build of the POSIX socket network layer
dnl
AC_DEFUN([AC_CUBE_POSIX_SOCKET],[

    AC_ARG_ENABLE([posix-socket],
                  AS_HELP_STRING([--enable-posix-socket], [Enable POSIX socket [default=yes]]),
                  [enable_posix_socket=$enableval],
                  [enable_posix_socket="yes"])

    AS_IF([test "x$enable_networking" != "no" && test "x$enable_posix_socket" = "xyes"],
          [AX_REQUIRE_HEADERS([arpa/inet.h netdb.h netinet/in.h sys/socket.h sys/errno.h sys/types.h sys/wait.h unistd.h],
                              [enable_posix_socket])])

    AS_IF([test "x$enable_posix_socket" = "xyes"],
         [AC_DEFINE([HAVE_POSIX_SOCKET],[1],[Define if POSIX socket headers are available])
          AC_SUBST([HAVE_POSIX_SOCKET])
          cube_have_working_socket=yes])

    AFS_SUMMARY([POSIX socket], [$enable_posix_socket])
])

dnl Configure the network layer for Cube
dnl
AC_DEFUN([AC_CUBE_NETWORK],[

    AC_ARG_ENABLE([networking],
                  AS_HELP_STRING([--enable-networking], [Enable Cube client/server support [default=yes]]),
                  [enable_networking=$enableval],
                  [enable_networking="yes"])

    AS_IF([test "x$enable_networking" = "xyes"],
          [AC_CUBE_POSIX_SOCKET])

       AS_IF([test "x$cube_have_working_socket" = "xyes"],
             [AC_DEFINE([HAVE_CUBE_NETWORKING],[1],[Define if Cube networking is available])
              AC_SUBST([HAVE_CUBE_NETWORKING])],
             [enable_networking="no"])

    AM_CONDITIONAL([ENABLE_POSIX_SOCKET],    [test "x$enable_posix_socket" = "xyes"])
    AM_CONDITIONAL([ENABLE_CUBE_NETWORKING], [test "x$enable_networking"   = "xyes"])
    
    AFS_SUMMARY([Networking],   [$enable_networking])

])
    
