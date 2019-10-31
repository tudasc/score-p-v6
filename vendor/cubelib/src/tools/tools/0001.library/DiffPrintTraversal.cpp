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
#include "DiffPrintTraversal.h"

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <limits>

#include "MdAggrCube.h"
#include "CnodeSubForest.h"
#include "CnodeSubTree.h"
#include "MdAggrCube.h"
#include "AggregatedMetric.h"
#include "PrintableCCnode.h"
#include "CCnode.h"

#include "CubeCnode.h"
#include "CubeRegion.h"

using namespace cube;
using namespace std;

DiffPrintTraversal::DiffPrintTraversal( vector<string> metrics,
                                        ostream&       stream )
    : MdTraversal( metrics ), stream( stream )
{
}

void
DiffPrintTraversal::initialize( CnodeSubForest* forest )
{
    MdTraversal::initialize( forest );
    cube                    = forest->get_reference_cube();
    number_of_metrics_cubes = forest->get_root()->get_reference_node()
                              ->print_headers( cnode_metrics, stream );
    stream << "Diff-Calltree" << endl;
}

void
DiffPrintTraversal::node_handler( CnodeSubTree* node )
{
    int              number_of_children          = node->num_children();
    PrintableCCnode* ref_tree                    = node->get_reference_node();
    int              number_of_ref_tree_children = ref_tree->num_children();

    // Print out information about node:
    ref_tree->print_values( cnode_metrics, stream, number_of_metrics_cubes );
    stream << ref_tree->treeindent() << ref_tree->get_callee()->get_name() << endl;

    // If some of the children are within the CCnode tree, but not within the
    // CnodeSubTree, we summarize informations about them and show them.
    // Otherwise, we just return here.
    if ( number_of_ref_tree_children == number_of_children
         || number_of_ref_tree_children == 0 )
    {
        return;
    }

    int j   = 0;
    int sum = 0;
    for ( size_t i = 0; i < cnode_metrics.size(); ++i )
    {
        sum += number_of_metrics_cubes[ i ];
    }
    vector<double>   values = vector<double>( sum, 0. );
    CnodeSubTree*    current_child;
    PrintableCCnode* current_child_ref_node;

    if ( number_of_children == 0 )
    {
        current_child          = NULL;
        current_child_ref_node = NULL;
    }
    else
    {
        current_child          = node->get_child( j );
        current_child_ref_node = current_child->get_reference_node();
    }

    int number_of_aggregated_nodes = 0;

    for ( int i = 0; i < number_of_ref_tree_children; ++i )
    {
        PrintableCCnode* current_ref_tree_child = ref_tree->get_child( i );

        if ( current_child_ref_node == current_ref_tree_child )
        {
            ++j;
            if ( j < number_of_children )
            {
                current_child          = node->get_child( j );
                current_child_ref_node = current_child->get_reference_node();
            }
            else
            {
                current_child          = NULL;
                current_child_ref_node = NULL;
            }
        }
        else
        {
            int          offset                  = 0;
            unsigned int number_of_cnode_metrics = cnode_metrics.size();
            number_of_aggregated_nodes += current_ref_tree_child->size();
            for ( unsigned int k = 0; k < number_of_cnode_metrics; ++k )
            {
                unsigned int      number_of_cubes = number_of_metrics_cubes[ k ];
                CnodeMetric*      md              = cnode_metrics[ k ];
                AggregatedMetric* bmd;
                if ( ( bmd = dynamic_cast<AggregatedMetric*>( md ) ) != NULL )
                {
                    CnodeMetric* metric_desc = bmd;
                    if ( bmd->get_inclusion_mode() == EXCL )
                    {
                        bmd->make_inclusive();
                        metric_desc = cube->get_cnode_metric( bmd->stringify() );
                        bmd->make_exclusive();
                    }
                    for ( unsigned int l = 0; l < number_of_cubes; ++l )
                    {
                        values[ offset + l ] += metric_desc->compute( current_ref_tree_child, l );
                    }
                }
                else
                {
                    cerr << "Could not cast " << md->stringify() << endl;
                    for ( unsigned int l = 0; l < number_of_cubes; ++l )
                    {
                        values[ offset + l ] = numeric_limits<double>::quiet_NaN();
                    }
                }
                offset += number_of_cubes;
            }
        }
    }

    ref_tree->print_values( cnode_metrics, stream, number_of_metrics_cubes,
                            values );
    stream << ref_tree->treeindent( ref_tree->get_level() + 1 ) << "***** Aggregated "
           << number_of_ref_tree_children - number_of_children
           << " siblings (+" << number_of_aggregated_nodes << " children) within "
           << ref_tree->get_callee()->get_name() << endl;
}
