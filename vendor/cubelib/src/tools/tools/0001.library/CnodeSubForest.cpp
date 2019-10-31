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
#include "CnodeSubForest.h"
#include "CubeError.h"
#include "MdAggrCube.h"
#include "PrintableCCnode.h"

using namespace cube;
using namespace std;

void
CnodeSubForest::GenerateNodeList::node_handler( CnodeSubTree* node )
{
    nodes.push_back( node );
}

CnodeSubForest::CnodeSubForest( vector<CnodeSubTree*> trees,
                                MdAggrCube*           cube )
    : cube( cube ), roots( trees )
{
}

CnodeSubForest::CnodeSubForest( CnodeSubForest const& copy )
    : cube( copy.cube )
{
    int number_of_roots = copy.roots.size();
    roots = vector<CnodeSubTree*>( number_of_roots );
    for ( int i = 0; i < number_of_roots; ++i )
    {
        roots[ i ] = new CnodeSubTree( *( copy.roots[ i ] ) );
    }
}

CnodeSubForest::CnodeSubForest( MdAggrCube* _cube )
    : cube( _cube )
{
    vector<Cnode*> _nodes          = cube->get_root_cnodev();
    int            number_of_roots = _nodes.size();
    roots = vector<CnodeSubTree*>( number_of_roots );
    for ( int i = 0; i < number_of_roots; ++i )
    {
        Cnode*           cnode     = _nodes[ i ];
        PrintableCCnode* printable = dynamic_cast<PrintableCCnode*>( cnode );
        if ( printable == NULL )
        {
            throw RuntimeError(
                      "Could not cast Cnode* like type to PrintableCCnode*" );
        }
        roots[ i ] = new CnodeSubTree( printable );
    }
}

CnodeSubForest::~CnodeSubForest()
{
    for ( vector<CnodeSubTree*>::iterator it = roots.begin();
          it != roots.end(); ++it )
    {
        delete ( *it );
    }
}

void
CnodeSubForest::traverse( Traversal* t )
{
    t->initialize( this );
    switch ( t->get_type() )
    {
        case TRAVERSE_UNORDERED:
            if ( nodes.empty() == true )
            {
                CnodeSubForest::GenerateNodeList gen_nodelist( nodes );
                traverse( &gen_nodelist );
            }
            for ( vector<CnodeSubTree*>::iterator it = nodes.begin();
                  it != nodes.end(); ++it )
            {
                if ( t->has_stopped() )
                {
                    break;
                }
                t->node_handler( *it );
            }
            break;
        case TRAVERSE_ROOTS:
            for ( vector<CnodeSubTree*>::iterator it = roots.begin();
                  it != roots.end(); ++it )
            {
                if ( t->has_stopped() )
                {
                    break;
                }
                t->node_handler( *it );
            }
            break;
        case TRAVERSE_PREORDER:
        case TRAVERSE_POSTORDER:
        case TRAVERSE_BREADTH_FIRST:
            for ( vector<CnodeSubTree*>::iterator it = roots.begin();
                  it != roots.end(); ++it )
            {
                if ( t->has_stopped() )
                {
                    break;
                }
                ( *it )->traverse( t );
            }
            break;
        default:
            throw Error( "Unknown traversal type." );
    }
    t->finalize( this );

    if ( t->is_constant() == false )
    {
        nodes.clear();
    }
}
