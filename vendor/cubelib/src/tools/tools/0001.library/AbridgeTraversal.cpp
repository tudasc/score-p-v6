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
#include "AbridgeTraversal.h"

#include <string>
#include <vector>

#include "CnodeSubForest.h"
#include "CnodeSubTree.h"
#include "MdAggrCube.h"
#include "PrintableCCnode.h"
#include "CCnode.h"
#include "CnodeMetric.h"

using namespace cube;
using namespace std;

AbridgeTraversal::AbridgeTraversal( string                metric,
                                    double                threshold,
                                    Abridge_ThresholdType type )
    : MdTraversal( vector<string>( 1, metric ) ), threshold( threshold ),
      type( type )
{
}

void
AbridgeTraversal::initialize( CnodeSubForest* forest )
{
    MdTraversal::initialize( forest );
    number_of_cubes = forest->get_reference_cube()->get_number_of_cubes();
}

void
AbridgeTraversal::initialize_tree( CnodeSubTree* root )
{
    MdTraversal::initialize_tree( root );
    if ( type == THRTYPE_ROOT_RELATIVE )
    {
        tree_threshold = 0;
        for ( unsigned int i = 0; i < number_of_cubes; ++i )
        {
            tree_threshold +=
                cnode_metrics[ 0 ]->compute( root->get_reference_node(), i );
        }
        tree_threshold /= number_of_cubes;
        tree_threshold *= threshold;
    }
    else
    {
        tree_threshold = threshold;
    }
}

void
AbridgeTraversal::node_handler( CnodeSubTree* node )
{
    MdTraversal::node_handler( node );

    if ( type == THRTYPE_CUMSUM )
    {
        unsigned int     number_of_children = node->num_children();
        unsigned int     funcs              = 0;
        double           total_sum          = 0., cumsum = 0.;
        map<int, int>    sorted2unsorted;
        map<int, double> unsorted_metric_sev;

        for ( unsigned int i = 0; i < number_of_children; ++i )
        {
            int    idx = 0;
            double val = 0.0;
            for ( unsigned int j = 0; j < number_of_cubes; ++j )
            {
                val += cnode_metrics[ 0 ]->compute( node->get_reference_node(), j );
            }
            unsorted_metric_sev[ i ] = val;
            total_sum               += val;

            for ( unsigned int j = 0; j <= i; ++j )
            {
                if ( unsorted_metric_sev[ sorted2unsorted[ j ] ] < unsorted_metric_sev[ i ] )
                {
                    break;
                }
                else
                {
                    idx = j;
                }
            }

            for ( int j = i; j >= idx; --j )
            {
                sorted2unsorted[ j ] = sorted2unsorted[ j - 1 ];
            }

            sorted2unsorted[ idx ] = i;
        }

        while ( cumsum < ( 1 - threshold ) * total_sum
                && funcs < number_of_children )
        {
            cumsum += unsorted_metric_sev[ sorted2unsorted[ funcs ] ];
            ++funcs;
        }

        vector<CnodeSubTree*> children_to_remove;
        for ( unsigned int i = funcs; i < number_of_children; ++i )
        {
            children_to_remove.push_back( node->get_child( sorted2unsorted[ i ] ) );
        }

        for ( vector<CnodeSubTree*>::iterator it = children_to_remove.begin();
              it != children_to_remove.end(); ++it )
        {
            node->remove_child( *it );
        }
    }
    else
    {
        for ( unsigned int i = 0; i < number_of_cubes; ++i )
        {
            if ( cnode_metrics[ 0 ]->compute( node->get_reference_node(), i )
                 > tree_threshold )
            {
                return;
            }
        }
        node->cut();
    }
}
