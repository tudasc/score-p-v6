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
 * \file CubeObjectsEnumerator.cpp
 * \brief Implements methods of the object ObjectsEnumerator.
 */

#include "config.h"
#include "CubeObjectsEnumerator.h"
#include "CubeVertex.h"

using namespace cube;

row_of_objects_t*
ObjectsEnumerator::get_objects_to_enumerate( Vertex* root, row_of_objects_t* row )
{
//     calltree_strides.clear();
    if ( row == 0 )
    {
        row = new row_of_objects_t();
    }
    row = traverse( row, root );
    return row;
}





// ------------------ protected part -----------------------------


row_of_objects_t*
ObjectsEnumerator::traverse( row_of_objects_t* row,  Vertex* root )
{
    if ( root == 0 )
    {
        return row;             // no children any more ;
    }

    if ( row->size() <= root->get_id() )
    {
        row->resize( root->get_id() + 1 );
    }

    ( *row )[ ( root->get_id() ) ] = root;
    for ( unsigned i = 0; i < root->num_children(); ++i )
    {
        row = traverse( row, root->get_child( i ) );
    }

    return row;
}






