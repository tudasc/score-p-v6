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
#include "ComputeTraversal.h"

#include "CnodeSubForest.h"
#include "CnodeSubTree.h"
#include "CCnode.h"
#include "CnodeMetric.h"
#include "MultiMdAggrCube.h"
#include "PrintableCCnode.h"

using namespace cube;
using namespace std;

ComputeTraversal::ComputeTraversal( vector<string> metrics )
    : MdTraversal( metrics ), mappings(NULL)
{
}

void
ComputeTraversal::initialize( CnodeSubForest* forest )
{
    MdTraversal::initialize( forest );
    MultiMdAggrCube* cube = dynamic_cast<MultiMdAggrCube*>( forest->get_reference_cube() );
    if ( cube == NULL )
    {
        mappings = NULL;
    }
    else
    {
        mappings = &( cube->get_mappings() );
    }
}

void
ComputeTraversal::node_handler( CnodeSubTree* node )
{
    CCnode* ccnode = node->get_reference_node();
    if ( mappings == NULL )
    {
        for ( vector<CnodeMetric*>::iterator md = cnode_metrics.begin();
              md != cnode_metrics.end(); ++md )
        {
            ( *md )->compute( ccnode );
        }
    }
    else
    {
        for ( vector<CnodeMetric*>::iterator md = cnode_metrics.begin();
              md != cnode_metrics.end(); ++md )
        {
            for ( vector<CubeMapping*>::const_iterator mapping = mappings->begin();
                  mapping != mappings->end(); ++mapping )
            {
                ( *md )->compute( ccnode, *mapping );
            }
        }
    }
}
