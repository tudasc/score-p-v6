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
 * \file CubeWideSearchEnumerator.cpp
 * \brief Implements methods of the object WideSearchEnumerator.
 */

#include "config.h"

#include "CubeWideSearchEnumerator.h"
#include "CubeVertex.h"

using namespace cube;

row_of_objects_t*
WideSearchEnumerator::traverse( row_of_objects_t* row,  Vertex* root )
{
    if ( root == 0 )
    {
        return row;                                                 // no children any more ;
    }
    if ( root->get_parent() == 0 )
    {
        row->push_back( root );                                     // root has to be added specially.
    }
    for ( unsigned i = 0; i < root->num_children(); ++i )
    {
        row->push_back( root->get_child( i ) );
    }
    for ( unsigned i = 0; i < root->num_children(); ++i )
    {
        row = traverse( row, root->get_child( i ) );
    }
    return row;
}

