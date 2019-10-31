##*************************************************************************##
##  CUBE        http://www.scalasca.org/                                   ##
##*************************************************************************##
##  Copyright (c) 1998-2017                                                ##
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





AC_DEFUN([AC_SCOREP_CONFIG_SELECTION_REPORT], [

XEND=$1

AFS_SUMMARY([Cube C++ Library], [$WITH_CPP_LIB])
AFS_SUMMARY([Cube Tools], [$WITH_TOOLS])



AFS_SUMMARY([Frontend zlib compression ], [$MSG_FRONTEND_COMPRESSION] )
AS_IF([test "x$MSG_FRONTEND_COMPRESSION" != "xno" ],[
AFS_SUMMARY([  zlib headers ], [$FRONTEND_LIBZ_HEADERS] )
AFS_SUMMARY([  zlib library ], [$FRONTEND_LIBZ_LDFLAGS $FRONTEND_LIBZ_LIBS] )
])

AS_IF([ test "x$MSG_FRONTEND_COMPRESSION" = "xreadonly" ],[
AFS_SUMMARY([  Notice], [Front end part of cube (c++ cube library, tools and GUI) can read compressed cube files, but write only uncompressed cube files.])
])

AS_IF([ test "x$MSG_FRONTEND_COMPRESSION" = "xfull" ],[
AFS_SUMMARY([  Notice],[Front end part of cube (c++ cube library, tools and GUI) can read and write compressed cube files.])
])

AFS_SUMMARY([  zlib compression flags ], [$COMPRESSION] )


AS_IF([test "x$CUBE_DUMP_R_SELECTED" = "xyes"],
[
	AFS_SUMMARY([Use R for cube_dump], [$CUBE_DUMP_R_AVAILABLE])
	AS_IF( [test "x$CUBE_DUMP_R_AVAILABLE" = "xyes" ],
		[
		AFS_SUMMARY([  With R], [$R_PATH])
		AFS_SUMMARY([  With Rscript], [$RSCRIPT_PATH])
		AFS_SUMMARY([  R compiler flags], [$R_CPPFLAGS])
		AFS_SUMMARY([  R linker flags], [$R_LDFLAGS])
		AFS_SUMMARY([  RInside path ], [$R_INSIDE_PATH] )
		AFS_SUMMARY([  Rcpp path], [$R_CPP_PATH] )
		],
		[AFS_SUMMARY([  Notice],[R, Rscript, RInside and Rcpp are necessary])]
	)
])

AS_IF([ test "x$ENABLE_MAKEFILE_RULES_FOR_REGENERATION" = "xyes" ],[
AFS_SUMMARY([Regenerate parsers:], [yes])
])
AS_IF( [test "x$CUBE_DEFAULT_ALL_IN_MEMORY" != "x" ],
		[
		AFS_SUMMARY([Data loading strategy ], [Keep all in memory, load on demand])
		])
AS_IF( [test "x$CUBE_DEFAULT_ALL_IN_MEMORY_PRELOAD" != "x" ],
		[
		AFS_SUMMARY([Data loading strategy ], [Keep all in memory, preloaded])
		])
AS_IF( [test "x$CUBE_DEFAULT_MANUAL" != "x" ],
		[
		AFS_SUMMARY([Data loading strategy ], [Manual loading])
		])
AS_IF( [test "x$CUBE_DEFAULT_LAST_N" != "x" ],
		[
		AFS_SUMMARY([Data loading strategy ], [Keep last $CUBE_N_LAST_ROWS rows in memory])
		])

AS_IF([ test "x$CUBE_SCOREP" != "x" ], [
AFS_SUMMARY([C++ compiler used],[$CUBE_SCOREP $CXX])
],[
AFS_SUMMARY([C++ compiler used],[$CXX])
])
AFS_SUMMARY([ Compiler flags used],[$CXXFLAGS_FOR_BUILD $FRONTEND_CXXFLAGS])

])





AC_DEFUN([AC_CUBE_FRONTEND_SELECTION], [
AC_SCOREP_CUBE_INITIALIZE_FRONTEND_SELECTION

AC_SCOREP_CUBE_CUBELIB_SELECTION
AC_SCOREP_CUBE_TOOLS_SELECTION
AC_SCOREP_CUBE_R_SELECTION
AC_CUBE_FIND_SCOREP
AC_CUBE_TESTS

# put here this conditionals.... in future it has to go away
AM_CONDITIONAL([HAVE_LEX], [test "x${LEX}" != "x:"])
AM_CONDITIONAL([WITH_CPP_LIB], [test "x$WITH_CPP_LIB" == "xyes"])
AM_CONDITIONAL([WITH_TOOLS], [test "x$WITH_TOOLS" == "xyes"])
AM_CONDITIONAL([CUBE_DUMP_WITH_R], [test "x$CUBE_DUMP_R_AVAILABLE" = "xyes"])
AM_CONDITIONAL([CUBE_COMPRESSION_FRONTEND], [test "x$MSG_FRONTEND_COMPRESSION" = "xyes"])

AFS_AM_CONDITIONAL([ENABLE_MAKEFILE_RULES_FOR_REGENERATION], [test "x$ENABLE_MAKEFILE_RULES_FOR_REGENERATION" = "xyes"], [false])

])



AC_DEFUN([AC_SCOREP_CUBE_CUBELIB_SELECTION], [
AC_ARG_WITH(cubelib, [AS_HELP_STRING([--with-cubelib | --without-cubelib], [Enables (default) or disables building and installation of the cube c++ library.])],[],[])

AS_IF([ test "x$with_cubelib" = "xyes" ], [
WITH_CPP_LIB="yes"
])

AS_IF( [ test "x$with_cubelib" = "xno" || test "x$without_cubelib" = "xyes" ], [
WITH_CPP_LIB="no"
WITH_TOOLS="no"
WITH_GUI="no"
])


AS_IF([test "x$WITH_CPP_LIB" = "xyes"],[
AM_PROG_LEX
AC_PROG_YACC
AC_SCOREP_PARSER_SELECTION
])
AM_CONDITIONAL([HAVE_LEX], [test "x${LEX}" != "x:"])
AC_SUBST(WITH_CPP_LIB)
AM_CONDITIONAL([WITH_CPP_LIB], [test "x$WITH_CPP_LIB" == "xyes"])
])



AC_DEFUN([AC_SCOREP_CUBE_TOOLS_SELECTION], [
AC_ARG_WITH(tools, [AS_HELP_STRING([--with-tools | --without-tools], [Enables (default) or disables building and installation of cube tools.])],[],[])


AS_IF([ test "x$with_tools" = "xyes" ], [
WITH_CPP_LIB="yes"
WITH_TOOLS="yes"
])

AS_IF([ test "x$with_tools" = "xno"  || test "x$without_tools" = "xyes" ], [
WITH_TOOLS="no"
])
AC_SUBST(WITH_TOOLS)
AM_CONDITIONAL([WITH_TOOLS], [test "x$WITH_TOOLS" == "xyes"])
])




AC_DEFUN([AC_SCOREP_CUBE_R_SELECTION], [
AC_ARG_WITH(cube_dump_r, [AS_HELP_STRING([--with-cube-dump-r | --without-cube-dump-r], [Enables (default) or disables support for R matrix output in Cube dump tool])], [], [with_cube_dump_r=yes])

AS_IF( [ test "x$with_cube_dump_r" = "xyes" ], [
CUBE_DUMP_R_SELECTED="yes"
])
AS_IF( [ test "x$with_cube_dump_r" = "xno" || test "x$without_cube_dump_r" = "xyes" ], [
CUBE_DUMP_R_SELECTED="no"
])

AC_SCOREP_R_OPTION

AM_CONDITIONAL([CUBE_DUMP_WITH_R], [test "x$CUBE_DUMP_R_AVAILABLE" = "xyes"])
])




AC_DEFUN([AC_SCOREP_CUBE_INITIALIZE_FRONTEND_SELECTION], [

WITH_CPP_LIB="yes"
WITH_TOOLS="yes"
WITH_GUI="yes"
WITH_C_WRITER="yes"

])






AC_DEFUN([AC_SCOREP_PARSER_SELECTION], [

AC_ARG_WITH(system-parser, [AS_HELP_STRING([--with-system-parser ],
	      [Generates all parsers of cube library using system own template (if found flex&bison) instead of using the own shipped version of pregenerated parsers. Apply this option if you have some errors in Cube4Parser.cpp, Cube4Scanner.cpp, CubePL1Parser.cpp, CubePL1Scanner.cpp, CubePL0Parser.cpp or CubePL0Scanner.cpp])], [], [])


WITH_SYSTEM_PARSER="no"
AS_IF( [ test "x$with_system_parser" = "xyes" ], [
WITH_SYSTEM_PARSER="yes"
])

AC_SCOREP_CUBE_PARSER_SELECTION


])




AC_DEFUN([AC_SCOREP_CUBE_PARSER_SELECTION], [

AM_PROG_LEX
AC_PROG_YACC


ENABLE_MAKEFILE_RULES_FOR_REGENERATION=no
AS_IF([ test "x$WITH_SYSTEM_PARSER" = "xyes" ],[
AC_MSG_NOTICE([ Remove pregenerated sources to invoke syntax parsers generation. ])
rm  $srcdir/../src/cube/src/syntax/Cube4Scanner.cpp
rm  $srcdir/../src/cube/src/syntax/cubepl/CubePL1Scanner.cpp
rm  $srcdir/../src/cube/src/syntax/cubepl/CubePL0Scanner.cpp
rm  $srcdir/../src/tools/tools/0031.ReMap2/ReMapScanner.cc
rm  $srcdir/../src/cube/src/syntax/Cube4Parser.cpp
rm  $srcdir/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp
rm  $srcdir/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp
rm  $srcdir/../src/tools/tools/0031.ReMap2/ReMapParser.cc
ENABLE_MAKEFILE_RULES_FOR_REGENERATION=yes
])



AC_MSG_NOTICE([ Use $LEX as a lexical analyzer. ])
AC_MSG_NOTICE([ Use $YACC as a syntax parser. ])


])




AC_DEFUN([AC_CUBE_CONSTUCT_LIST_OF_LIB_DIRS], [

sufix=""
   case "x${build_cpu}" in
    "xx86")
        sufix="32"
        ;;
    "xx86_64")
        sufix="64"
        ;;
    "xppc32")
        sufix="32"
        ;;
    "xppc64")
        sufix="64"
        ;;
    "xia64")
        sufix="64"
        ;;
    "xia32")
        sufix="32"
        ;;
    "xpowerpc64")
        sufix="64"
        ;;
    "xpowerpc32")
        sufix="32"
        ;;
    "xmips64")
        sufix="64"
        ;;
    "xmips32")
        sufix="32"
        ;;
   esac
if test "x$sufix" = "x"; then
LIBDIRS_LIST="/lib/ /usr/lib/ "
else
LIBDIRS_LIST="/lib/ /lib$sufix/ /usr/lib/ /usr/lib$sufix/ "
fi


])

