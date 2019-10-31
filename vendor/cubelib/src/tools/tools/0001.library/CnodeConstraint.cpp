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
#include "CnodeConstraint.h"

#include <sstream>

#include "CnodeSubForest.h"
#include "PrintableCCnode.h"
#include "CCnode.h"
#include "CnodeMetric.h"
#include "CubeRegion.h"
#include "CubeCnode.h"

#include "RegionConstraint.h"

using namespace cube;
using namespace std;

CnodeConstraint::CnodeConstraintTraversal::CnodeConstraintTraversal(
    CnodeConstraint* constraint,
    bool             auto_initialize_tests )
    : Traversal(),
      auto_initialize_tests( auto_initialize_tests ), constraint( constraint )
{
}

Traversal_Type
CnodeConstraint::CnodeConstraintTraversal::get_type() const
{
    return TRAVERSE_UNORDERED;
}

bool
CnodeConstraint::CnodeConstraintTraversal::is_constant() const
{
    return true;
}

void
CnodeConstraint::CnodeConstraintTraversal::node_handler(
    CnodeSubTree* tree )
{
    Cnode* reference_node = tree->get_reference_node();
    if ( constraint->is_skipable( tree ) )
    {
        return;
    }
    if ( auto_initialize_tests )
    {
        constraint->test( string( "\"" )
                          + reference_node->get_callee()->get_name() +  "\"" );
    }
    constraint->cnode_handler( reference_node );
}

CnodeConstraint::CnodeConstraint( CnodeSubForest* forest,
                                  bool            auto_initialize_tests )
    : TreeConstraint( forest ),
      traversal( CnodeConstraintTraversal( ( CnodeConstraint* ) this,
                                           auto_initialize_tests ) )
{
}

CnodeConstraint::~CnodeConstraint()
{
}

void
CnodeConstraint::check()
{
    TreeConstraint::check();
    traversal.run( get_forest() );
    finish();
}

void
CnodeConstraint::skip( std::string reason, Cnode* node,
                       Constraint_CnodeOutputMode output_mode )
{
    add_to_skipped( node );
    AbstractConstraint::skip( build_header( node, output_mode ) + reason );
}

void
CnodeConstraint::fail( std::string reason, Cnode* node,
                       Constraint_CnodeOutputMode output_mode )
{
    add_to_failed( node );
    AbstractConstraint::fail( build_header( node, output_mode ) + reason );
}

string
CnodeConstraint::build_header( Cnode*                     node,
                               Constraint_CnodeOutputMode output_mode )
{
    stringstream ss;
    if ( ( output_mode & CNODE_OUTPUT_MODE_BASIC )
         == CNODE_OUTPUT_MODE_BASIC )
    {
        ss << "In call node with id " << node->get_id() << " (Name: "
           << node->get_callee()->get_name() << ")" << endl;
    }
    if ( ( output_mode & CNODE_OUTPUT_MODE_BACKTRACE )
         == CNODE_OUTPUT_MODE_BACKTRACE )
    {
        PrintableCCnode* pccnode = dynamic_cast<PrintableCCnode*>( node );
        if ( pccnode != NULL )
        {
            pccnode->print_callpath( vector<CnodeMetric*>(), ss );
        }
        else
        {
            ss << "  Warning: Could not print out backtrace!" << endl;
        }
    }
    if ( ( output_mode & CNODE_OUTPUT_MODE_TREE_REROOTED )
         == CNODE_OUTPUT_MODE_TREE_REROOTED )
    {
        PrintableCCnode* pccnode = dynamic_cast<PrintableCCnode*>( node );
        if ( pccnode != NULL )
        {
            pccnode->print( vector<CnodeMetric*>(), ss );
        }
        else
        {
            ss << "  Warning: Could not print out re-rooted tree output!" << endl;
        }
    }
    return ss.str();
}
