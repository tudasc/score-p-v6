##*************************************************************************##
##  Copyright (c) 2016                                                     ##
##  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          ##
##                                                                         ##
##  This software may be modified and distributed under the terms of       ##
##  a BSD-style license.  See the COPYING file in the package base         ##
##  directory for details.                                                 ##
##*************************************************************************##


# AX_GMOCK
# --------
# Configures the Google C++ Testing Framework. Requires the path to the
# top-level GTest source directory relative to the location of the calling
# configure.ac.
#
# List of provided automake substitutions:
#  `GMOCK_PATH`::      Top-level GTest source directory
#  `GMOCK_CPPFLAGS`::  Preprocessor flags to be used when compiling tests
#  `GMOCK_CXXFLAGS`::  C++ compiler flags to be used when compiling tests
#  `GMOCK_LIBS`::      Libraries/linker flags to be used when linking tests
#
# List of provided automake conditionals:
#  `HAVE_GMOCK_TYPED_TESTS`::  Enabled if all features required by typed tests
#                              are supported by the C++ compiler, disabled
#                              otherwise
#
AC_DEFUN([AX_GMOCK], [
    m4_ifblank([$1],
        [m4_fatal([Path to GMock directory relative to configure.ac required])])
    AC_REQUIRE([AC_PROG_CXX])
    AC_REQUIRE([AX_PTHREAD])
    AC_REQUIRE([AX_GTEST])

    AS_VAR_SET([gmock_cppflags], ["-I$srcdir/$1/include"])

    AC_SUBST([GMOCK_PATH],     ["$1"])
    AC_SUBST([GMOCK_CPPFLAGS], ["$gmock_cppflags"])
    AC_SUBST([GMOCK_CXXFLAGS], ["$PTHREAD_CFLAGS"])
    AC_SUBST([GMOCK_LIBS],     ["$PTHREAD_LIBS"])
])

