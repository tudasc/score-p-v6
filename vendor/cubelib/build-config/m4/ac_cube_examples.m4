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


#
#
# Simple check for mpirun to make backend examples and tests running under mpi. 

AC_DEFUN([AC_SCOREP_FRONTEND_EXAMPLES],
[

    AS_IF([ test "x$WITH_CPP_LIB" = "xyes"],[ 
	NOMPI_CUBE_FRONTEND_EXAMPLES_SRC="cube_example.cpp cube_values_example.cpp"
	NOMPI_CUBE_FRONTEND_EXAMPLES_EXE="cube_example.cpp.exe cube_values_example.cpp.exe"
	if test "x$MPICXX" != "x"; then
	    MPI_CUBE_FRONTEND_EXAMPLES_SRC=""
	    MPI_CUBE_FRONTEND_EXAMPLES_EXE=""
	fi
])


    NOMPI_FRONTEND_APPS_EXE="$NOMPI_CUBE_FRONTEND_EXAMPLES_EXE"
    MPI_FRONTEND_APPS_EXE="$MPI_CUBE_FRONTEND_EXAMPLES_EXE"





    AC_SUBST([NOMPI_CUBE_FRONTEND_EXAMPLES_SRC])
    AC_SUBST([NOMPI_CUBE_FRONTEND_EXAMPLES_EXE])
    AC_SUBST([MPI_CUBE_FRONTEND_EXAMPLES_SRC])
    AC_SUBST([MPI_CUBE_FRONTEND_EXAMPLES_EXE])

    AC_SUBST([NOMPI_FRONTEND_APPS_EXE])
    AC_SUBST([MPI_FRONTEND_APPS_EXE])





])


AC_DEFUN([AC_CUBE_EXAMPLES],
[
    AC_SCOREP_FRONTEND_EXAMPLES

])




