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



AC_DEFUN([AC_CUBE_FIND_SCOREP],
[
AC_ARG_WITH( scorep, [AS_HELP_STRING([--with-scorep=path], [ Defined path to Score-P binary])],[ CUBE_SCOREP=$withval; TRY_SCOREP=yes],[CUBE_SCOREP=])

AS_IF([test "x$TRY_SCOREP" == "xyes"],[

AS_IF([ test "x$CUBE_SCOREP" == "x" || test "x$CUBE_SCOREP" == "xyes"], [

AC_PATH_PROG([CUBE_SCOREP], [scorep], [], [$PATH])

AS_IF([ test "x$CUBE_SCOREP" == "x"], [
HMI_INSTRUMENTATION=""
])
])
AC_MSG_NOTICE([Using ScoreP : $CUBE_SCOREP ]) 
])

AC_SUBST([CUBE_SCOREP])

])
