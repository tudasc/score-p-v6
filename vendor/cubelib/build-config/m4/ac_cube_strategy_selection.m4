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


AC_DEFUN([AC_CUBE_STRATEGY_SELECTION],
[
AC_ARG_WITH(strategy, [AS_HELP_STRING([--with-strategy ], [Selects the data loading strategy (keepall (default), preload, manual, lastn)])],[STRATEGY=$withval],[STRATEGY=keepall])
AC_ARG_WITH(nrows, [AS_HELP_STRING([--with-nrows ], [Sets number of kept rows])],[CUBE_N_LAST_ROWS=$withval],[])
AS_IF([test "x$STRATEGY" = "xkeepall"],[
AC_MSG_NOTICE([ Select 'all rows in memory, on demand' as a data loading strategy ])
CUBE_DEFAULT_ALL_IN_MEMORY=1
AC_DEFINE_UNQUOTED(CUBE_DEFAULT_ALL_IN_MEMORY, 1, [Select 'all rows in memory, on demand' as a data loading strategy])
AC_SUBST([CUBE_DEFAULT_ALL_IN_MEMORY])
],
[
AS_IF([test "x$STRATEGY" = "xpreload"],[
AC_MSG_NOTICE([ Select 'all rows in memory, preloaded' as a data loading strategy ])
CUBE_DEFAULT_ALL_IN_MEMORY_PRELOAD=1
AC_DEFINE_UNQUOTED(CUBE_DEFAULT_ALL_IN_MEMORY_PRELOAD, 1, [Select 'all rows in memory, preloaded' as a data loading strategy])
AC_SUBST([CUBE_DEFAULT_ALL_IN_MEMORY_PRELOAD])
],
[
AS_IF([test "x$STRATEGY" = "xmanual"],[
AC_MSG_NOTICE([ Select 'manual load' as a data loading strategy ])
CUBE_DEFAULT_MANUAL=1
AC_DEFINE_UNQUOTED(CUBE_DEFAULT_MANUAL, 1, [Select 'manual load' as a data loading strategy])
AC_SUBST([CUBE_DEFAULT_MANUAL])
],
[
AS_IF([test "x$STRATEGY" = "xlastn"],[
AC_MSG_NOTICE([ Select last N rows in memory' as a data loading strategy ])
CUBE_DEFAULT_LAST_N=1
AC_DEFINE_UNQUOTED(CUBE_DEFAULT_LAST_N, 1, [Select 'last N rows in memory' as a data loading strategy])
AC_SUBST([CUBE_DEFAULT_LAST_N])
AS_IF([test "x$CUBE_N_LAST_ROWS" != "x"],[

AS_IF([ test $CUBE_N_LAST_ROWS -eq $CUBE_N_LAST_ROWS 2> /dev/null ],[], 
[
AC_MSG_ERROR([ Unknown number format  "$CUBE_N_LAST_ROWS" ])
]
)
AC_MSG_NOTICE([ Select number of kept rows as $CUBE_N_LAST_ROWS])
AC_DEFINE_UNQUOTED(CUBE_N_LAST_ROWS, $CUBE_N_LAST_ROWS , [Select number of kept rows as $CUBE_N_LAST_ROWS])
AC_SUBST([CUBE_N_LAST_ROWS])
])
],
[AC_MSG_ERROR([ Unknown data loading strategy "$STRATEGY" ])
])
])
])
])
])

