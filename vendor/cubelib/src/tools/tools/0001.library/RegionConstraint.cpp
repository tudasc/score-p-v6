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
#include "RegionConstraint.h"
#include "CnodeConstraint.h"

#include <sstream>


#include "MdAggrCube.h"
#include "CnodeMetric.h"
#include "CnodeSubTree.h"
#include "CnodeSubForest.h"
#include "PrintableCCnode.h"

#include "CubeRegion.h"
#include "CubeError.h"

using namespace cube;
using namespace std;

RegionConstraint::RegionConstraintTraversal::RegionConstraintTraversal(
    RegionConstraint* constraint,
    bool              auto_initialize_tests )
    : Traversal(),
      constraint( constraint ),
      auto_initialize_tests( auto_initialize_tests )
{
}

Traversal_Type
RegionConstraint::RegionConstraintTraversal::get_type() const
{
    return TRAVERSE_UNORDERED;
}

bool
RegionConstraint::RegionConstraintTraversal::is_constant() const
{
    return true;
}

void
RegionConstraint::RegionConstraintTraversal::node_handler(
    CnodeSubTree* tree )
{
    Region* region = tree->get_reference_node()->get_callee();
    if ( visited_regions.find( region ) != visited_regions.end()
         || constraint->is_skipable( tree ) )
    {
        return;
    }
    if ( auto_initialize_tests )
    {
        constraint->test( string( "\"" ) + region->get_name() + "\"" );
    }
    constraint->region_handler( region );
    visited_regions.insert( region );
}

RegionConstraint::RegionConstraint( CnodeSubForest* forest,
                                    bool            auto_initialize_tests )
    : TreeConstraint( forest ),
      traversal( RegionConstraintTraversal( ( RegionConstraint* ) this,
                                            auto_initialize_tests ) )
{
}

RegionConstraint::~RegionConstraint()
{
}

void
RegionConstraint::check()
{
    TreeConstraint::check();
    traversal.run( get_forest() );
    finish();
}

void
RegionConstraint::skip( std::string reason, Region* region )
{
    add_to_skipped( region );
    AbstractConstraint::skip( build_header( region ) + reason );
}

void
RegionConstraint::fail( std::string reason, Region* region )
{
    add_to_failed( region );
    AbstractConstraint::fail( build_header( region ) + reason );
}

string
RegionConstraint::build_header( Region* region )
{
    stringstream ss;
    ss << "In region with id " << region->get_id() << " (Name: "
       << region->get_name() << ")" << endl;
    return ss.str();
}
