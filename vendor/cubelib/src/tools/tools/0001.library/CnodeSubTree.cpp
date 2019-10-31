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
#include "CnodeSubTree.h"

#include <vector>
#include <queue>

#include "CubeError.h"
#include "PrintableCCnode.h"
#include "Traversal.h"

using namespace cube;
using namespace std;

CnodeSubTree::CnodeSubTree( PrintableCCnode* pccnode )
{
    mark_of_death  = false;
    parent         = NULL;
    reference_node = pccnode;
    int number_of_children = pccnode->num_children();
    for ( int i = 0; i < number_of_children; ++i )
    {
        add_child( new CnodeSubTree( pccnode->get_child( i ) ) );
    }
}

CnodeSubTree::CnodeSubTree( CnodeSubTree const& copy )
{
    mark_of_death  = false;
    parent         = NULL;
    reference_node = copy.reference_node;
    int number_of_children = copy.childv.size();
    for ( int i = 0; i < number_of_children; ++i )
    {
        add_child( new CnodeSubTree( *( copy.get_child( i ) ) ) );
    }
}

CnodeSubTree::~CnodeSubTree()
{
    unsigned int number_of_children = num_children();
    for ( unsigned int i = 0; i < number_of_children; ++i )
    {
        delete get_child( i );
    }
}

unsigned int
CnodeSubTree::num_children()
const
{
    return childv.size();
}

CnodeSubTree*
CnodeSubTree::get_child( unsigned int id )
const
{
    return childv.at( id );
}

PrintableCCnode*
CnodeSubTree::get_reference_node()
const
{
    return reference_node;
}

void
CnodeSubTree::add_child( CnodeSubTree* child )
{
    childv.push_back( child );
    child->parent = this;
}

void
CnodeSubTree::remove_child( CnodeSubTree* child )
{
    for ( vector<CnodeSubTree*>::iterator it = childv.begin();
          it != childv.end(); ++it )
    {
        if ( *it == child )
        {
            childv.erase( it );
            break;
        }
    }
    delete child;
}

void
CnodeSubTree::remove_child( unsigned int id )
{
    delete ( childv.at( id ) );
    childv.erase( childv.begin() + id );
}

void
CnodeSubTree::cut()
{
    mark_of_death = true;
}

void
CnodeSubTree::traverse( Traversal* t )
{
    t->initialize_tree( this );
    switch ( t->get_type() )
    {
        case TRAVERSE_PREORDER:
            preorder_traverse( t );
            break;
        case TRAVERSE_POSTORDER:
            postorder_traverse( t );
            break;
        case TRAVERSE_BREADTH_FIRST:
            t->node_handler( this );
            bf_traverse( t );
            break;
        default:
            throw Error( "Unknown traversal type." );
    }
    t->finalize_tree( this );
}

void
CnodeSubTree::postorder_traverse( Traversal* t )
{
    if ( mark_of_death )
    {
        return;
    }
    vector<CnodeSubTree*>::iterator child = childv.begin();
    while ( child != childv.end() && t->has_stopped() == false )
    {
        ( *child )->postorder_traverse( t );
        if ( ( *child )->mark_of_death )
        {
            child = childv.erase( child );
        }
        else
        {
            ++child;
        }
    }
    if ( t->has_stopped() == false )
    {
        t->node_handler( this );
    }
}

void
CnodeSubTree::preorder_traverse( Traversal* t )
{
    if ( mark_of_death )
    {
        return;
    }
    t->node_handler( this );
    if ( mark_of_death )
    {
        return;
    }
    vector<CnodeSubTree*>::iterator child = childv.begin();
    while ( child != childv.end() && t->has_stopped() == false )
    {
        ( *child )->preorder_traverse( t );
        if ( ( *child )->mark_of_death )
        {
            child = childv.erase( child );
        }
        else
        {
            ++child;
        }
    }
}

/*
 * XXX: not working yet!
 */
void
CnodeSubTree::bf_traverse( Traversal* t )
{
    queue<CnodeSubTree*> queue;
    queue.push( this );
    while ( queue.empty() == false && t->has_stopped() == false )
    {
        CnodeSubTree* node = queue.front();
        queue.pop();
        t->node_handler( node );
        for ( vector<CnodeSubTree*>::const_iterator child = node->childv.begin();
              child != node->childv.end(); ++child )
        {
            queue.push( *child );
        }
    }
}
