/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2019                                                **
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



#include "config.h"
#include "Traversal.h"

#include "CnodeSubForest.h"

using namespace cube;

Traversal::Traversal()
    : traversal_stopped( false ), current_node( 0 )
{
}

Traversal::~Traversal()
{
}

bool
Traversal::is_constant()
const
{
    return false;
}

void
Traversal::run( CnodeSubForest* forest )
{
    forest->traverse( this );
}

void
Traversal::initialize( CnodeSubForest* )
{
    traversal_stopped = false;
}

void
Traversal::initialize_tree( CnodeSubTree* )
{
}

void
Traversal::node_handler( CnodeSubTree* )
{
}

void
Traversal::finalize_tree( CnodeSubTree* )
{
}

void
Traversal::finalize( CnodeSubForest* )
{
}

void
Traversal::stop_traversing()
{
    traversal_stopped = true;
}

void
Traversal::unstop_traversing()
{
    traversal_stopped = false;
}
