##*************************************************************************##
##  CUBE        http://www.scalasca.org/                                   ##
##*************************************************************************##
##  Copyright (c) 1998-2019                                                ##
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



AC_PREREQ([2.69])
AC_INIT([CubeLib], m4_esyscmd([../vendor/common/build-config/generate-package-version.sh ../build-config/VERSION]), [scalasca@fz-juelich.de],[cubelib],[http://www.scalasca.org])
AC_SUBST([LIBRARY_INTERFACE_VERSION], m4_esyscmd([../vendor/common/build-config/generate-library-version.sh ../build-config/VERSION]))
AC_DEFINE_UNQUOTED([LIBRARY_INTERFACE_VERSION], ["$LIBRARY_INTERFACE_VERSION"], [Interface version number])
adl_RECURSIVE_EVAL([${libexecdir}/${PACKAGE}], [PKGLIBEXECDIR])
AC_DEFINE_UNQUOTED([PKGLIBEXECDIR],
                   ["${PKGLIBEXECDIR}"],
                   [Directory where ]AC_PACKAGE_NAME[ executables to be run by other programs rather than by users are installed])
adl_RECURSIVE_EVAL([${bindir}], [BINDIR])
AC_SUBST([BINDIR])
adl_RECURSIVE_EVAL([${includedir}], [INCLUDEDIR])
AC_SUBST([INCLUDEDIR])
adl_RECURSIVE_EVAL([${libdir}/${PACKAGE}], [PKGLIBDIR])
AC_SUBST([PKGLIBDIR])
adl_RECURSIVE_EVAL([${libdir}${backend_suffix}/${PACKAGE}], [BACKEND_PKGLIBDIR])
AC_SUBST([BACKEND_PKGLIBDIR])
adl_RECURSIVE_EVAL([${datadir}/${PACKAGE}], [PKGDATADIR])
AC_SUBST([PKGDATADIR])
AC_DEFINE_UNQUOTED([PKGDATADIR],
                  ["${PKGDATADIR}"],
                   [Directory where ]AC_PACKAGE_NAME[ data is stored])
adl_RECURSIVE_EVAL([${docdir}], [DOCDIR])
AC_SUBST([DOCDIR])

## Where to find auxiliary build tools & local macros
AC_CONFIG_AUX_DIR([../build-config])
AC_CONFIG_MACRO_DIRS([../build-config/m4 ../vendor/common/build-config/m4])





## Define frontend-specific environment variables
AC_ARG_VAR(CXX_FOR_BUILD, [C++ compiler command for the frontend build])
AC_ARG_VAR(CPPFLAGS_FOR_BUILD, [(Objective) C/C++ preprocessor flags for the frontend build, e.g. -I<include dir> if you have headers in a nonstandard directory <include dir>])
AC_ARG_VAR(CXXFLAGS_FOR_BUILD, [C++ compiler flags for the frontend build])
AC_ARG_VAR(LDFLAGS_FOR_BUILD, [linker flags for the frontend build, e.g. -L<lib dir> if you have libraries in a nonstandard directory <lib dir>])
AC_ARG_VAR(LIBS_FOR_BUILD, [libraries to pass to the linker for the frontend build, e.g. -l<library>])


## Convert compilers & flags
AS_IF([ test "x${ac_scorep_cross_compiling}" = "xyes" ],[
AC_SCOREP_CONVERT_FOR_BUILD_COMPILER([CXX])
AC_SCOREP_CONVERT_FOR_BUILD_COMPILER([CC])
AC_SCOREP_CONVERT_FOR_BUILD_FLAGS([CPPFLAGS])
AC_SCOREP_CONVERT_FOR_BUILD_FLAGS([CFLAGS])
AC_SCOREP_CONVERT_FOR_BUILD_FLAGS([CXXFLAGS])
AC_SCOREP_CONVERT_FOR_BUILD_FLAGS([LDFLAGS])
AC_SCOREP_CONVERT_FOR_BUILD_FLAGS([LIBS])
])
## Set up Automake
AM_INIT_AUTOMAKE([1.13.4 -Wall foreign color-tests tar-pax])
AM_SILENT_RULES([yes])
AM_PROG_AR

## Initialize configuration summary
AFS_PACKAGE_BUILD_INIT([frontend])
AFS_SUMMARY_INIT

## Set up Libtool
LT_PREREQ([2.4.6])
LT_INIT([])
AC_SUBST([LIBTOOL_DEPS])

## Set convenience variables for macros
ac_scorep_frontend=yes


##--- Package-specific configuration ----------------------------------------

AC_SUBST([FRONTEND_CXX], [${CXX}])
AC_SUBST([FRONTEND_CC], [${CC}])

## Checks for programs
AC_PROG_CXX
AC_SCOREP_PROG_CC_C99([], [AC_MSG_ERROR([No ISO C99 support in C compiler.])])
AM_PROG_CC_C_O
AX_CXX_INTTYPE_MACROS
AC_LANG([C++])
AM_PROG_LEX
AC_PROG_YACC


dnl Use the most recent C++ standard that is supported by the code.
dnl We can fall back to older versions.
AX_CXX_COMPILE_STDCXX_14([], optional)
if test "$HAVE_CXX14" -ne 1; then
    AX_CXX_COMPILE_STDCXX_11([], mandatory)
fi
	


AFS_DEBUG_OPTION
AC_CUBE_IO_BUFFERSIZE
AC_CUBE_STRATEGY_SELECTION

# check for network availability
AC_CUBE_NETWORK

AC_SEARCH_LIBS([trunc], [m])
AC_SEARCH_LIBS([ceil], [m])
AC_SCOREP_POSIX_FUNCTIONS
AC_CHECK_FUNCS_ONCE([readlink])



AC_CUBE_CONSTUCT_LIST_OF_LIB_DIRS
AC_CUBE_FRONTEND_SELECTION
AC_CUBE_LIBZ_FRONTEND_SELECTION
AC_SCOREP_CONFIG_SELECTION_REPORT([frontend])

## Setup Testing
AX_GTEST([../vendor/gtest])
AX_GMOCK([../vendor/gmock])
# disable backend tests (as there is no backend)
AM_CONDITIONAL([BACKEND_TEST_RUNS], [test 1 -eq 0])

#check for examples
AC_CUBE_EXAMPLES


dnl Predicate to use HARDCODE_LIBDIR_FLAG_* only if linker needs it.
AS_IF([test "x${hardcode_into_libs}" = "xyes"],
      [ac_scorep_hardcode_into_libs=1],
      [ac_scorep_hardcode_into_libs=0])
AC_SUBST([HARDCODE_INTO_LIBS], [${ac_scorep_hardcode_into_libs}])
dnl Flag to hardcode libdir into a binary during linking, C version.
AC_SUBST([HARDCODE_LIBDIR_FLAG_CC], [${hardcode_libdir_flag_spec}])
dnl Flag to hardcode libdir into a binary during linking, C++ version.
AC_SUBST([HARDCODE_LIBDIR_FLAG_CXX], [${hardcode_libdir_flag_spec_CXX}])
dnl The ${wl} part of the HARDCODE_LIBDIR_FLAG_* defines.
AC_SUBST([HARDCODE_LIBDIR_WL], [${wl}])
dnl The ${aix_libpath} part of the HARDCODE_LIBDIR_FLAG_* defines. Only available on AIX.
AC_SUBST([HARDCODE_LIBDIR_AIX_LIBPATH], [${aix_libpath}])


AC_SUBST([SYS_LIB_DLSEARCH_PATH_SPEC], [${sys_lib_dlsearch_path_spec}])

AC_CUBELIB_ERROR_CODES
AX_CXX_INTTYPE_MACROS


AC_CONFIG_HEADERS([../src/cubelib-config-frontend.h])


CC="$CUBE_SCOREP $CC"
CXX="$CUBE_SCOREP $CXX"



AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([../examples/Makefile.frontend])
AC_CONFIG_FILES([../src/tools/tools/0002.Config/cubelib_config_data_]AFS_PACKAGE_BUILD_name[.cpp:../src/tools/tools/0002.Config/cubelib_config_data_build.cpp.in])


AC_CONFIG_FILES([../test/test0.0/run_test_0.0.sh
                 ], \
                [chmod +x ../test/test0.0/run_test_0.0.sh
                ])
AC_CONFIG_FILES([../test/test0.0/cube_unite_test0.0.cpp
                 ])
AC_CONFIG_FILES([../test/test0.1/run_test_0.1.sh
                 ], \
                [chmod +x ../test/test0.1/run_test_0.1.sh
                ])
AC_CONFIG_FILES([../test/test0.2/run_test_0.2.sh
                 ], \
                [chmod +x ../test/test0.2/run_test_0.2.sh
                ])
AC_CONFIG_FILES([../test/test0.4/run_test_0.4.sh
                 ], \
                [chmod +x ../test/test0.4/run_test_0.4.sh
                ])
AC_CONFIG_FILES([../test/test1.1/run_test_1.1.sh
                 ], \
                [chmod +x ../test/test1.1/run_test_1.1.sh
                ])
AC_CONFIG_FILES([../test/test1.2/run_test_1.2.sh
                 ], \
                [
                 chmod +x ../test/test1.2/run_test_1.2.sh
                ])
AC_CONFIG_FILES([../test/test1.3/run_test_1.3.sh
                 ], \
                [
                 chmod +x ../test/test1.3/run_test_1.3.sh
                ])
AC_CONFIG_FILES([../test/test2/run_test_2.sh
                 ], \
                [
                 chmod +x ../test/test2/run_test_2.sh
                ])
AC_CONFIG_FILES([../test/test7/run_test_7.sh
                 ], \
                [
                 chmod +x ../test/test7/run_test_7.sh
                ])
AC_CONFIG_FILES([../test/test8/run_test_8.sh
                 ], \
                [
                 chmod +x ../test/test8/run_test_8.sh
                ])
AC_CONFIG_FILES([../test/test9/run_test_9.sh
                 ], \
                [
                 chmod +x ../test/test9/run_test_9.sh
                ])
AC_CONFIG_FILES([../test/test10/run_test_10.sh
                 ], \
                [
                 chmod +x ../test/test10/run_test_10.sh
                ])
AC_CONFIG_FILES([../test/test11/run_test_11.sh
                 ], \
                [
                 chmod +x ../test/test11/run_test_11.sh
                ])
AC_CONFIG_FILES([../test/test12/run_test_12.sh
                 ], \
                [
                 chmod +x ../test/test12/run_test_12.sh
                ])
AC_CONFIG_FILES([../test/test13/run_test_13.sh
                 ], \
                [
                 chmod +x ../test/test13/run_test_13.sh
                ])
AC_CONFIG_FILES([../test/test14/run_test_14.sh
                 ], \
                [
                 chmod +x ../test/test14/run_test_14.sh
                ])
AC_CONFIG_FILES([../test/test15/run_test_15.sh
                 ], \
                [
                 chmod +x ../test/test15/run_test_15.sh
                ])
AC_CONFIG_FILES([../test/test16/run_test_16.sh
                 ], \
                [
                 chmod +x ../test/test16/run_test_16.sh
                ])
AC_CONFIG_FILES([../test/test17/run_test_17.sh
                 ], \
                [
                 chmod +x ../test/test17/run_test_17.sh
                ])
AC_CONFIG_FILES([../test/test18/run_test_18.sh
                 ], \
                [
                 chmod +x ../test/test18/run_test_18.sh
                ])
AC_CONFIG_FILES([../test/test19/run_test_19.sh
                 ], \
                [
                 chmod +x ../test/test19/run_test_19.sh
                ])
AC_CONFIG_FILES([../test/test20/run_test_20.sh
                 ], \
                [
                 chmod +x ../test/test20/run_test_20.sh
                ])
AC_CONFIG_FILES([../test/test21/run_test_21.sh
                 ], \
                [
                 chmod +x ../test/test21/run_test_21.sh
                ])
AC_CONFIG_FILES([../test/test22/run_test_22.sh
                 ], \
                [
                 chmod +x ../test/test22/run_test_22.sh
                ])
AC_CONFIG_FILES([../test/test23/run_test_23.sh
                 ], \
                [
                 chmod +x ../test/test23/run_test_23.sh
                ])
AC_CONFIG_FILES([../test/test24/run_test_24.sh
                 ], \
                [
                 chmod +x ../test/test24/run_test_24.sh
                ])
AC_CONFIG_FILES([../test/test25/run_test_25.sh
                 ], \
                [
                 chmod +x ../test/test25/run_test_25.sh
                ])
AC_CONFIG_FILES([../test/test26/run_test_26.sh
                 ], \
                [
                 chmod +x ../test/test26/run_test_26.sh
                ])
AC_CONFIG_FILES([../test/test27/run_test_27.sh
                 ], \
                [
                 chmod +x ../test/test27/run_test_27.sh
                ])
AC_CONFIG_FILES([../test/test28/run_test_28.sh
                 ], \
                [
                 chmod +x ../test/test28/run_test_28.sh
                ])
AC_CONFIG_FILES([../test/test29/run_test_29.sh
                 ], \
                [
                 chmod +x ../test/test29/run_test_29.sh
                ])
AC_CONFIG_FILES([../test/test30/run_test_30.sh
                 ], \
                [
                 chmod +x ../test/test30/run_test_30.sh
                ])
AC_CONFIG_FILES([../test/test31/run_test_31.sh
                 ], \
                [
                 chmod +x ../test/test31/run_test_31.sh
                ])
AS_IF([ test "x$CUBE_DUMP_R_SELECTED" == "xyes" ],[
        AC_CONFIG_FILES([../test/test32/run_test_32.sh
                 ], \
                [
                 chmod +x ../test/test32/run_test_32.sh
                ])
])
AC_CONFIG_FILES([../test/test33_CubeProxy/run_io_test.sh
                 ], \
                [
                 chmod +x ../test/test33_CubeProxy/run_io_test.sh
                ])
AC_CONFIG_FILES([../test/test33_CubeProxy/run_network_test.sh
                 ], \
                [
                 chmod +x ../test/test33_CubeProxy/run_network_test.sh
                ])
AC_CONFIG_FILES([../test/test33_CubeProxy/cube_selftest_CubeProxy_io.cpp]
                [../test/test33_CubeProxy/cube_selftest_CubeProxy_network.cpp])
AC_OUTPUT
