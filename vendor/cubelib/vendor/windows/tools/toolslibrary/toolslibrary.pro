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


CONFIG	+= exceptions warn_on  release 
TEMPLATE = lib
TARGET = 
CUBE +=
CUBE_SRC = ../../../../src/cube
TOOLS_LIBRARY_SRC = ../../../../src/tools/tools/0001.library
COMMON_SRC = ../../../../src/tools/
DEPENDPATH += $${COMMON_SRC} $${COMMON_SRC}/common_inc  
INCLUDEPATH += $${COMMON_SRC} $${COMMON_SRC}/common_inc   $${CUBE_SRC}/../../vpath/src/  $${CUBE_SRC}/../ \
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
	 ${CUBE_SRC}/include/ \
	 ${MINGW}/opt/include \
	 "C:/Program Files (x86)/GnuWin32/include" 
	 
LIBS += -L../../cube/release -lcube -L../common/release -lcommon 
RESOURCES =



QMAKE_CXXFLAGS=-fexceptions

QT +=

# Input{
HEADERS += \
$${TOOLS_LIBRARY_SRC}/AbridgeTraversal.h \
$${TOOLS_LIBRARY_SRC}/AbstractConstraint.h \
$${TOOLS_LIBRARY_SRC}/AggregatedMetric.h \
$${TOOLS_LIBRARY_SRC}/Blacklist.h \
$${TOOLS_LIBRARY_SRC}/CCnode.h \
$${TOOLS_LIBRARY_SRC}/CMetricCnodeConstraint.h \
$${TOOLS_LIBRARY_SRC}/CRegion.h \
$${TOOLS_LIBRARY_SRC}/Cacheable.h \
$${TOOLS_LIBRARY_SRC}/CnodeConstraint.h \
$${TOOLS_LIBRARY_SRC}/CnodeInfo.h \
$${TOOLS_LIBRARY_SRC}/CnodeMetric.h \
$${TOOLS_LIBRARY_SRC}/CnodeSubForest.h \
$${TOOLS_LIBRARY_SRC}/CnodeSubTree.h \
$${TOOLS_LIBRARY_SRC}/ComputeTraversal.h \
$${TOOLS_LIBRARY_SRC}/CowTree.h \
$${TOOLS_LIBRARY_SRC}/DiffPrintTraversal.h \
$${TOOLS_LIBRARY_SRC}/InfoObj.h \
$${TOOLS_LIBRARY_SRC}/MdAggrCube.h \
$${TOOLS_LIBRARY_SRC}/MdTraversal.h \
$${TOOLS_LIBRARY_SRC}/MultiMdAggrCube.h \
$${TOOLS_LIBRARY_SRC}/PrintableCCnode.h \
$${TOOLS_LIBRARY_SRC}/RegionConstraint.h \
$${TOOLS_LIBRARY_SRC}/RegionInfo.h \
$${TOOLS_LIBRARY_SRC}/Traversal.h \
$${TOOLS_LIBRARY_SRC}/TreeConstraint.h \
$${TOOLS_LIBRARY_SRC}/VisitorsMetric.h 



SOURCES += \ 
$${TOOLS_LIBRARY_SRC}/AbridgeTraversal.cpp \
$${TOOLS_LIBRARY_SRC}/AbstractConstraint.cpp \
$${TOOLS_LIBRARY_SRC}/AggregatedMetric.cpp \
$${TOOLS_LIBRARY_SRC}/Blacklist.cpp \
$${TOOLS_LIBRARY_SRC}/CCnode.cpp \
$${TOOLS_LIBRARY_SRC}/CMetricCnodeConstraint.cpp \
$${TOOLS_LIBRARY_SRC}/CRegion.cpp \
$${TOOLS_LIBRARY_SRC}/Cacheable.cpp \
$${TOOLS_LIBRARY_SRC}/CnodeConstraint.cpp \
$${TOOLS_LIBRARY_SRC}/CnodeInfo.cpp \
$${TOOLS_LIBRARY_SRC}/CnodeMetric.cpp \
$${TOOLS_LIBRARY_SRC}/CnodeSubForest.cpp \
$${TOOLS_LIBRARY_SRC}/CnodeSubTree.cpp \
$${TOOLS_LIBRARY_SRC}/ComputeTraversal.cpp \
$${TOOLS_LIBRARY_SRC}/CowTree.cpp \
$${TOOLS_LIBRARY_SRC}/DiffPrintTraversal.cpp \
$${TOOLS_LIBRARY_SRC}/MdAggrCube.cpp \
$${TOOLS_LIBRARY_SRC}/MdTraversal.cpp \
$${TOOLS_LIBRARY_SRC}/MultiMdAggrCube.cpp \
$${TOOLS_LIBRARY_SRC}/PrintableCCnode.cpp \
$${TOOLS_LIBRARY_SRC}/RegionConstraint.cpp \
$${TOOLS_LIBRARY_SRC}/RegionInfo.cpp \
$${TOOLS_LIBRARY_SRC}/Traversal.cpp \
$${TOOLS_LIBRARY_SRC}/TreeConstraint.cpp \
$${TOOLS_LIBRARY_SRC}/VisitorsMetric.cpp 

# Additional dependencies
# PRE_TARGETDEPS += $CUBE/lib/libcube4.a



# Hack for IBM AIX
aix-g++ {
  QMAKE_CXXFLAGS_RELEASE += -O0
}
aix-g++-64 {
  QMAKE_CXXFLAGS_RELEASE += -O0
}
