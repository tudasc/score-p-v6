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
 * \file CubeDeepSearchEnumerator.cpp
 * \brief Implements methods of the object DeepSearchEnumerator.
 */

#include "config.h"
#include "CubeDeepSearchEnumerator.h"
#include "CubeVertex.h"

using namespace cube;
using namespace std;

row_of_objects_t*
DeepSearchEnumerator::traverse( row_of_objects_t* row,  Vertex* root )
{
    if ( root == 0 )
    {
        return row;             // no children any more ;
    }
    row->push_back( root );
    for ( unsigned i = 0; i < root->num_children(); ++i )
    {
        row = traverse( row, root->get_child( i ) );
    }
    return row;
}



