##*************************************************************************##
##  CUBE        http://www.scalasca.org/                                   ##
##*************************************************************************##
##  Copyright (c) 1998-2016                                                ##
##  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          ##
##                                                                         ##
##  Copyright (c) 2009-2015                                                ##
##  German Research School for Simulation Sciences GmbH,                   ##
##  Laboratory for Parallel Programming                                    ##
##                                                                         ##
##  This software may be modified and distributed under the terms of       ##
##  a BSD-style license.  See the COPYING file in the package base         ##
##  directory for details.                                                 ##
##*************************************************************************##



AC_DEFUN([AC_CUBE_IO_BUFFERSIZE],
[
AC_ARG_WITH(buffersize, [AS_HELP_STRING([--with-buffersize ], [Sets a buffersize for I/O operations])],[IO_BUFFERSIZE=$withval],[IO_BUFFERSIZE=])
AS_IF([test "x$IO_BUFFERSIZE" != "x"],[
AC_MSG_NOTICE([ Set buffersize ($IO_BUFFERSIZE bytes) for I/O operatons.  ])
IO_BUFFERSIZE_MACRO="-DIO_BUFFERSIZE=$IO_BUFFERSIZE"
],
[
AC_MSG_NOTICE([ Set default value for buffersize (1Mb) for I/O operatons. ])
])
AC_SUBST([IO_BUFFERSIZE_MACRO])
])

