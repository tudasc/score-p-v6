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
#include "TreeConstraint.h"

#include "PrintableCCnode.h"
#include "CCnode.h"
#include "CnodeSubForest.h"
#include "CnodeSubTree.h"

#include "CubeCnode.h"
#include "CubeRegion.h"
#include "CubeError.h"

using namespace std;
using namespace cube;

TreeConstraint::TreeConstraint( CnodeSubForest* forest )
    : forest( forest )
{
}

TreeConstraint::~TreeConstraint()
{
}

void
TreeConstraint::set_forest( CnodeSubForest* new_forest )
{
    forest = new_forest;
}

void
TreeConstraint::check()
{
    if ( forest == NULL )
    {
        throw RuntimeError( "Can't apply constraint to NULL forest." );
    }

    AbstractConstraint* constraint      = this;
    TreeConstraint*     tree_constraint = NULL;
    do
    {
        constraint      = constraint->get_parent();
        tree_constraint = dynamic_cast<TreeConstraint*>( constraint );
    }
    while ( constraint != NULL && tree_constraint == NULL );

    if ( tree_constraint != NULL )
    {
        std::set<Cnode*> skipable_cnodes
            = tree_constraint->get_skipable_cnodes();
        skipable_cnodes.insert( skipable_cnodes.begin(), skipable_cnodes.end() );
        std::set<Region*> skipable_regions
            = tree_constraint->get_skipable_regions();
        skipable_regions.insert( skipable_regions.begin(), skipable_regions.end() );
    }
}

bool
TreeConstraint::is_skipable( CnodeSubTree* node ) const
{
    return is_skipable( node->get_reference_node() )
           || is_skipable( node->get_reference_node()->get_callee() );
}

bool
TreeConstraint::is_skipable( Cnode* node ) const
{
    return skipped_cnodes.find( node ) != skipped_cnodes.end();
}

bool
TreeConstraint::is_skipable( Region* region ) const
{
    return skipped_regions.find( region ) != skipped_regions.end();
}

void
TreeConstraint::add_to_skipped( Cnode* node )
{
    skipped_cnodes.insert( node );
}

void
TreeConstraint::add_to_failed( Cnode* node )
{
    failed_cnodes.insert( node );
}

void
TreeConstraint::add_to_skipped( Region* region )
{
    skipped_regions.insert( region );
}

void
TreeConstraint::add_to_failed( Region* region )
{
    failed_regions.insert( region );
}

std::set<Cnode*>
TreeConstraint::get_skipable_cnodes() const
{
    std::set<Cnode*> skipable = skipped_cnodes;
    skipable.insert( failed_cnodes.begin(), failed_cnodes.end() );
    return skipable;
}

std::set<Region*>
TreeConstraint::get_skipable_regions() const
{
    std::set<Region*> skipable = skipped_regions;
    skipable.insert( failed_regions.begin(), failed_regions.end() );
    return skipable;
}

CnodeSubForest*
TreeConstraint::get_forest() const
{
    return forest;
}
