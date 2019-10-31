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


CONFIG	+= exceptions console rtti warn_on  release 
TEMPLATE = app
CUBE +=
CUBE_SRC = ../../../../src/cube
TOOLS_LIBRARY_SRC = ../../../../src/tools/tools/0001.library
COMMON_SRC = ../../../../src/tools/

CUBE_TOOL_SRC = ../../../../src/tools/tools/0011.Inclusify
DEPENDPATH += $${COMMON_SRC} $${COMMON_SRC}/common_inc  
INCLUDEPATH += $${CUBE_TOOL_SRC} $${COMMON_SRC}/common_inc   $${CUBE_SRC}/../../vpath/src/  $${CUBE_SRC}/../ \
     $${CUBE_SRC}/include/service\
	 $${CUBE_SRC}/include/service/cubelayout \
	 $${CUBE_SRC}/include/service/cubelayout/layout \
	 $${CUBE_SRC}/include/service/cubelayout/readers \
	 $${CUBE_SRC}/include/dimensions/metric \
	 $${CUBE_SRC}/include/dimensions/metric/strategies \
	 $${CUBE_SRC}/include/dimensions/metric/data \
	 $${CUBE_SRC}/include/dimensions/metric/cache \
	 $${CUBE_SRC}/include/dimensions/metric/data/rows \
	 $${CUBE_SRC}/include/dimensions/metric/matrix \
	 $${CUBE_SRC}/include/dimensions/metric/index \
	 $${CUBE_SRC}/include/dimensions/metric/value \
	 $${CUBE_SRC}/include/dimensions/metric/value/trafo \
	 $${CUBE_SRC}/include/dimensions/metric/value/trafo/single_value \
	 $${CUBE_SRC}/include/dimensions/calltree \
	 $${CUBE_SRC}/include/dimensions/system \
	 $${CUBE_SRC}/include/dimensions \
	 $${CUBE_SRC}/include/network \
	 $${CUBE_SRC}/include/syntax \
	 $${CUBE_SRC}/include/syntax/cubepl/evaluators \
	 $${CUBE_SRC}/include/syntax/cubepl/evaluators/nullary \
	 $${CUBE_SRC}/include/syntax/cubepl/evaluators/nullary/statements \
	 $${CUBE_SRC}/include/syntax/cubepl/evaluators/unary \
	 $${CUBE_SRC}/include/syntax/cubepl/evaluators/unary/functions/single_argument \
	 $${CUBE_SRC}/include/syntax/cubepl/evaluators/unary/functions/two_arguments \
	 $${CUBE_SRC}/include/syntax/cubepl/evaluators/unary/functions/lambda_calcul \
	 $${CUBE_SRC}/include/syntax/cubepl/evaluators/binary \
	 $${CUBE_SRC}/include/syntax/cubepl \
	 $${CUBE_SRC}/include/derivated \
	 $${CUBE_SRC}/include/topologies \
	 $${CUBE_SRC}/include/ \
	 ${MINGW}/opt/include \
	 "C:/Program Files (x86)/GnuWin32/include" 
	 
LIBS += -L../../cube/release -lcube
RESOURCES =


QMAKE_CXXFLAGS=-fexceptions

QT +=

# Input{
HEADERS += 



SOURCES += \
   $${CUBE_TOOL_SRC}/cube4_inclusify.cpp 
   


# Hack for IBM AIX
aix-g++ {
  QMAKE_CXXFLAGS_RELEASE += -O0
}
aix-g++-64 {
  QMAKE_CXXFLAGS_RELEASE += -O0
}
