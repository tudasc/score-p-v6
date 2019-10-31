/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2016                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2009-2015                                                **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/




/**
 * \file commoncalltree_calls.h
 * \brief provides calls  for cube_commoncalltree tool
 *
 */

#ifndef COMMON_CALLTREE_CALLS
#define COMMON_CALLTREE_CALLS 0

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <algorithm>

#include "Cube.h"
#include "CubeCnode.h"
#include "CubeMachine.h"
#include "CubeMetric.h"
#include "CubeRegion.h"
#include "CubeServices.h"
#include "algebra4-internals.h"

namespace cube
{
// / Used to specify, if an inclusive or an exclusive value is being calculated
enum InclusionMarker { CUBE_CALLPATH_INCLUDE = 1234, CUBE_CALLPATH_EXCLUDE = 0 };


typedef struct
{
    Cnode*   callpath;
    uint64_t stride;
} StridedPair;

typedef std::vector< StridedPair >               StridedCallTree;
typedef std::vector< StridedCallTree >           StridedForrest;
typedef std::map< cube::Cnode*, InclusionMarker> MarkedCallTree;
typedef std::vector< MarkedCallTree>             MarkedForrest;

bool
CallPathAlphaLess( Vertex* a,
                   Vertex* b );
bool
CallPathAlphaEqual( Vertex* a,
                    Vertex* b );


void
create_common_calltree(  Cube&           outCube,
                         Cube&           inCube,
                         CubeMapping&    mapping,
                         MarkedCallTree& markers );

void
fill_with_data(  Cube&           outCube,
                 Cube&           inCube,
                 CubeMapping&    mapping,
                 MarkedCallTree& markers );


MarkedForrest
align_trees( StridedForrest&                       trees,
             std::vector< std::vector< size_t > >& running_indices );

uint64_t
update_strided_tree( Cnode*           cnode,
                     StridedCallTree& tree );


StridedCallTree
get_strided_tree( Cube& inCube );



void
cube_common_calltree( Cube**   incubes,
                      Cube**   outcubes,
                      uint64_t num );


void
print_strided_tree( StridedCallTree& tree );

void
print_alligned_forrest( MarkedForrest&  markers,
                        StridedForrest& trees );
} /* namespace cube*/




#endif
