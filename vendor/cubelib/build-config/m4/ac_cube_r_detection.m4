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



AC_DEFUN([AC_SCOREP_R_OPTION],
[
AS_IF([test "x$CUBE_DUMP_R_SELECTED" = "xyes"],[

	AC_PATH_PROG(R_PATH, R, "")
	AC_PATH_PROG(RSCRIPT_PATH, Rscript, "")
	AS_IF([test "x$R_PATH" != "x" -a "x$RSCRIPT_PATH" != "x"],[
		CUBE_DUMP_R_AVAILABLE="yes"

		R_INSIDE_PATH=`$RSCRIPT_PATH -e 'find.package("RInside")' 2>&1 | head -n 1`
		result=`echo $R_INSIDE_PATH | grep Error`
	    	AS_IF([test -z "$result"],[
			R_INSIDE_PATH=`echo ${R_INSIDE_PATH#*\"} | tr -d '"'`
			AC_SUBST([R_INSIDE_PATH])
		],[CUBE_DUMP_R_AVAILABLE="no"])

		#redirect error when the packages is not in the system
		R_CPP_PATH=`$RSCRIPT_PATH -e 'find.package("Rcpp")' 2>&1 | head -n 1`
		result=`echo $R_CPP_PATH | grep Error`
	    	AS_IF([test -z "$result"],[
			R_CPP_PATH=`echo ${R_CPP_PATH#*\"} | tr -d '"'`
			AC_SUBST([R_CPP_PATH])
		],[CUBE_DUMP_R_AVAILABLE="no"])

		#R_INCLUDE_PATH=`echo "#include <R.h>" > /tmp/temp.cpp && R CMD COMPILE /tmp/temp.cpp && rm /tmp/temp.cpp /tmp/temp.o`
		#echo $R_INCLUDE_PATH
		#R_INCLUDE_PATH=`echo ${R_INCLUDE_PATH#*-I}`
		#temp=`awk '{print $1;}' <<< $R_INCLUDE_PATH`
		#echo $temp
		#temp=`echo $R_INCLUDE_PATH | awk '{print $1;}'`
		#echo $temp
		#temp=`set -- $R_INCLUDE_PATH && echo $1`
		#echo $temp
	#	echo ${R_INCLUDE_PATH%-D*}
	#	R_INCLUDE_PATH=`echo ${R_INCLUDE_PATH%-D*}`
	#	echo ${R_INCLUDE_PATH%-D*}
		#R_INCLUDE_PATH=`echo $R_INCLUDE_PATH | cut -d ' ' -f 1`
		#AC_SUBST([R_INCLUDE_PATH])
		R_CPPFLAGS=`$R_PATH CMD config --cppflags`
		R_LDFLAGS=`$R_PATH CMD config --ldflags`
		AC_SUBST([R_CPPFLAGS])
		AC_SUBST([R_LDFLAGS])
	],[
	    CUBE_DUMP_R_AVAILABLE="no"
	])], 
	[
	CUBE_DUMP_R_AVAILABLE="no"
	]
)


AC_SUBST([CUBE_DUMP_R_AVAILABLE])

])
