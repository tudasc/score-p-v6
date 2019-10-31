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



#include "config.h"
#include "CCnode.h"

#include "CubeCnode.h"
#include <iostream>

using namespace cube;
using namespace std;

CCnode::CCnode( Region*       callee,
                const string& mod,
                int           line,
                Cnode*        parent,
                uint32_t      id,
                int           cache_size )
    : Cnode( callee, mod, line, parent, id ), Cacheable( cache_size )
{   /// Just calls the constructors of its super classes.
}

unsigned int
CCnode::size()
const
{   /// Recursivly calls size on it's sub-nodes to obtain the total
    /// number of descendents of this node.
    unsigned int sum = num_children();
    for ( unsigned int i = 0; i < num_children(); ++i )
    {
        sum += dynamic_cast<CCnode*>( get_child( i ) )->size();
    }
    return sum;
}
