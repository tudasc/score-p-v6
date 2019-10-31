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


#ifndef COWTREE_CPP_GUARD_
#define COWTREE_CPP_GUARD_

#include "config.h"

#include "CowTree.h"

#include "CubeError.h"

#include <map>
#include <vector>

using namespace cube;
using namespace std;

template < typename T >
map<const CowNode<T>*, typename CowNode<T>::MetaTree*>
CowNode<T>::root_to_meta_node;

template < typename T >
const typename CowNode<T>::preorder_iterator&
CowNode<T>::end_iterator
    = typename
      CowNode<T>::preorder_iterator::preorder_iterator();

template < typename T >
CowNode<T>::MetaTree::MetaTree( const CowNode< T >*              root,
                                typename CowNode< T >::MetaTree* parent )
    : root( root ), parent( parent ), reference_counter( 0 )
{
    if ( parent != NULL )
    {
        ( parent->children ).push_back( this );
    }
}

template < typename T >
CowNode<T>::MetaTree::~MetaTree()
{
    if ( parent == NULL )
    {
        for ( typename vector<typename CowNode<T>::MetaTree*>::iterator it
                  = children.begin(); it != children.end(); ++it )
        {
            ( *it )->parent = NULL;
        }
    }
    else
    {
        for ( typename vector<typename CowNode<T>::MetaTree*>::iterator it
                  = parent->children.begin(); it != parent->children.end(); ++it )
        {
            if ( *it == this )
            {
                parent->children.erase( it );
                break;
            }
        }
        for ( typename vector<typename CowNode<T>::MetaTree*>::iterator it
                  = children.begin(); it != children.end(); ++it )
        {
            parent->children.push_back( *it );
        }
    }
}

template < typename T >
inline typename CowNode< T >::MetaTree *
CowNode< T >::MetaTree::get_parent() const
{
    return parent;
}

template < typename T >
inline const CowNode<T>*
CowNode<T>::MetaTree::get_root() const
{
    return root;
}

template < typename T >
inline bool CowNode<T>::MetaTree::is_deletable() const
{
    return children.empty() && reference_counter == 0;
}

template < typename T >
inline typename CowNode<T>::MetaTree *
CowNode<T>::MetaTree::get_child( unsigned int id ) const
{
    return children.at( id );
}

template < typename T >
inline unsigned int CowNode<T>::MetaTree::numof_children() const
{
    return children.size();
}

template < typename T >
bool
CowNode<T>::preorder_iterator::operator==(
    const typename CowNode<T>::preorder_iterator& it )
{
    return equals( it );
}

template < typename T >
bool
CowNode<T>::preorder_iterator::operator!=(
    const typename CowNode<T>::preorder_iterator& it )
{
    return !equals( it );
}

template < typename T >
T&
CowNode<T>::preorder_iterator::operator*()
{
    return current->get();
}

template < typename T >
CowNode<T>::preorder_iterator::preorder_iterator()
    : current( NULL ), context( NULL )
{
}

template < typename T >
CowNode<T>::preorder_iterator::preorder_iterator( CowNode<T>* root_node )
    : current( root_node )
{
    if ( root_node->is_referenced() )
    {
        throw RuntimeError( "Can't create an iterator from a non-root node "
                            "without knowing it's context." );
    }
    context = root_node->get_meta_tree_node( root_node );
    push_node_children( root_node );
}

template < typename T >
CowNode<T>::preorder_iterator::preorder_iterator(
    CowNode<T>*                          node,
    const typename CowNode<T>::MetaTree* context )
    : current( node ), context( context )
{
    push_node_children( node );
}

template < typename T >
CowNode<T>::preorder_iterator::preorder_iterator(
    const typename CowNode<T>::preorder_iterator& pre_it )
    : current( pre_it.current ),
      context( pre_it.context ), node_stack( pre_it.node_stack )
{
}

template < typename T >
typename CowNode<T>::preorder_iterator&
CowNode<T>::preorder_iterator::operator++()
{
    if ( this->node_stack.empty() )
    {
        if ( this->current == NULL )
        {
            throw RuntimeError( "Can't increment iterator, because it is already "
                                "at the end." );
        }
        else
        {
            this->current = NULL;
        }
    }
    else
    {
        this->current = this->node_stack.top();
        this->node_stack.pop();
        push_node_children( this->current );
    }
    return *this;
}

template < typename T >
inline CowNode<T>* CowNode<T>::preorder_iterator::get_current_node() const
{
    return current;
}

template < typename T >
void CowNode<T>::preorder_iterator::skip_children()
{
    int number_of_children = get_current_node()->numof_children();
    while ( number_of_children-- > 0 )
    {
        node_stack.pop();
    }
}

template < typename T >
inline void CowNode<T>::preorder_iterator::push_node_children( CowNode<T>* node )
{
    unsigned int nc = this->current->numof_children();
    for ( unsigned int id = nc; id > 0; --id )
    {
        this->node_stack.push( this->current->get_child( id - 1 ) );
    }
}

template < typename T >
inline bool CowNode<T>::preorder_iterator::equals(
    const typename CowNode<T>::preorder_iterator & it )
{
    return ( context == it.context ||
             ( node_stack.empty() && it.node_stack.empty() ) )
           && current == it.current;
}

template < typename T >
CowNode<T>::CowNode( T& object )
    : object( object ), reference_counter( 0 )
{
    add_meta_tree_node( this );
}

template < typename T >
CowNode<T>::CowNode( T&                object,
                     CowNode<T>*       parent,
                     const CowNode<T>* root )
    : object( object ), reference_counter( 0 )
{
    parent->add_child( this, get_meta_tree_node( root ) );
}

template < typename T >
CowNode<T>::CowNode( CowNode<T>* copy )
    : object( copy->object ), reference_counter( 0 ), children( copy->children )
{
    if ( copy->is_referenced() )
    {
        throw RuntimeError( "Can't copy a non-root node without knowing it's "
                            "context." );
    }

    const typename CowNode<T>::MetaTree * context
        = add_meta_tree_node( this, copy );

    for ( typename vector<CowNode<T>*>::iterator it = children.begin();
          it != children.end(); ++it )
    {
        ( *it )->init_parent( this, context );
    }
}

template < typename T >
CowNode<T>::CowNode( CowNode<T>*                          copy,
                     const typename CowNode<T>::MetaTree* context )
    : object( copy->object ), reference_counter( 0 ), children( copy->children )
{
}

template < typename T >
CowNode<T>::~CowNode()
{
    if ( is_referenced() )
    {
        throw RuntimeError( "Can't destroy a CowNode as long as it is "
                            "referenced by some other node! Use remove_child on the parent " \
                            "node." );
    }

    if ( has_context() ) // If this is a root node.
    {
        const typename CowNode<T>::MetaTree * context = get_meta_tree_node( this );
        remove_parent( context );
        root_to_meta_node.erase( root_to_meta_node.find( this ) );
        delete context;
    }
    for ( typename vector<CowNode<T>*>::iterator it = children.begin();
          it != children.end(); ++it )
    {
        if ( ( *it )->is_referenced() == false )
        {
            delete *it;
        }
    }
}

template < typename T >
inline unsigned int
CowNode<T>::numof_children() const
{
    return children.size();
}

template < typename T >
inline bool
CowNode<T>::is_referenced() const
{
    return reference_counter > 0;
}

template < typename T >
inline CowNode<T>*
CowNode<T>::get_child( unsigned int id ) const
{
#ifdef COWTREE_UNSAFE_GETCHILD
    return children[ id ];
#else
    return children.at( id );
#endif
}

template < typename T >
CowNode<T>*
CowNode<T>::add_child( CowNode<T>*                          child,
                       const typename CowNode<T>::MetaTree* context )
{
    CowNode<T>* parent = make_private( context );
    child->set_parent( parent, context );
    parent->children.push_back( child );
    return parent;
}

template < typename T >
CowNode<T>*
CowNode<T>::replace_child( CowNode<T>* child,
                           CowNode<T>* replacement, const typename CowNode<T>::MetaTree* context )
{
    CowNode<T>* parent = make_private( context );
    for ( typename vector<CowNode<T>*>::iterator it = parent->children.begin();
          it != parent->children.end(); ++it )
    {
        if ( *it == child )
        {
            child->remove_parent( context );
            replacement->set_parent( parent, context );
            *it = replacement;
            return parent;
        }
    }
    throw RuntimeError( "Could not find node in replace_child!" );
}

template < typename T >
CowNode<T>*
CowNode<T>::remove_child( unsigned int                         child_id,
                          const typename CowNode<T>::MetaTree* context )
{
    CowNode<T>* parent = make_private( context );
    CowNode<T>* child  = parent->get_child( child_id );
    child->remove_parent( context );
    if ( child->is_referenced() == 0 )
    {
        delete child;
    }
    parent->children.erase( parent->children.begin() + child_id );
    return parent;
}

template < typename T >
CowNode<T>*
CowNode<T>::remove_child( CowNode<T>*                          child,
                          const typename CowNode<T>::MetaTree* context )
{
    int number_of_children = numof_children();
    for ( int i = 0; i < number_of_children; ++i )
    {
        if ( children[ i ] == child )
        {
            return remove_child( i, context );
        }
    }

    throw RuntimeError( "Could not find requested child "
                        "within remove_child." );
}

template < typename T >
inline CowNode<T>*
CowNode<T>::get_parent(
    const typename CowNode<T>::MetaTree* meta_node ) const
{
    CowNode<T>* node = get_parent_noexc( meta_node );
    if ( node == NULL )
    {
        throw RuntimeError( "Could not find parent cnode in get_parent." );
    }
    else
    {
        return node;
    }
}

template < typename T >
CowNode<T>*
CowNode<T>::get_parent_noexc(
    const typename CowNode<T>::MetaTree* meta_node ) const
{
    if ( is_referenced() == false )
    {
        return NULL;
    }
#ifdef COWTREE_FAST_LOOKUP
    // Without COWTREE_FAST_LOOKUP you may get better error detection, but once
    // the tree code works, it should do no harm.
    else if ( is_private() )
    {
        return parent.begin()->second;
    }
#endif
    typename map< const typename CowNode<T>::MetaTree*, CowNode<T>* >::const_iterator it;
    it = parent_map.end();
    while ( meta_node != NULL
            && ( it = parent_map.find( meta_node ) ) == parent_map.end() )
    {
        meta_node = meta_node->get_parent();
    }

    if ( it == parent_map.end() )
    {
        return NULL;
    }
    else
    {
        return it->second;
    }
}

template < typename T >
inline T&
CowNode<T>::get() const
{
    return object;
}

template < typename T >
inline void
CowNode<T>::init_parent( CowNode<T>*                          new_parent,
                         const typename CowNode<T>::MetaTree* context )
{
    typename map<const typename CowNode<T>::MetaTree*, CowNode<T>*>::iterator it
        = parent_map.find( context );
    if ( it == parent_map.end() )
    {
        parent_map.insert( pair<const typename CowNode<T>::MetaTree*, CowNode<T>*>(
                               context, new_parent ) );
        reference();
    }
}

template < typename T >
inline void
CowNode<T>::set_parent( CowNode<T>*                          new_parent,
                        const typename CowNode<T>::MetaTree* context )
{
    typename map<const typename CowNode<T>::MetaTree*, CowNode<T>*>::iterator it
        = parent_map.find( context );

    if ( it == parent_map.end() )
    {
        parent_map.insert( pair<const typename CowNode<T>::MetaTree*, CowNode<T>*>(
                               context, new_parent ) );
        reference();
    }
    else
    {
        it->second = new_parent;
    }
}

template < typename T >
inline void
CowNode<T>::remove_parent(
    const typename CowNode<T>::MetaTree* context )
{
    typename CowNode<T>::preorder_iterator it
        = typename
          CowNode<T>::preorder_iterator::preorder_iterator( this,
                                                            context );
    for (; it != end(); ++it )
    {
        CowNode<T>* current = it.get_current_node();
        CowNode<T>* parent  = current->get_parent_noexc( context );
        if ( parent != NULL )
        {
            unsigned int number_of_meta_children = context->numof_children();
            for ( unsigned int id = 0; id < number_of_meta_children; ++id )
            {
                current->init_parent( parent, context->get_child( id ) );
            }
            current->parent_map.erase( context );
            current->unreference();
        }
        else if ( current->is_referenced() )
        {
            it.skip_children();
        }
    }
}

template < typename T >
CowNode<T>*
CowNode<T>::make_private(
    const typename CowNode<T>::MetaTree* context )
{
    if ( is_private() )
    {
        return this;
    }
    else
    {
        CowNode<T>* copy   = new CowNode<T>( this, context );
        CowNode<T>* parent = get_parent( context );
        parent->replace_child( this, copy, context );
        return copy;
    }
}

template < typename T >
inline bool
CowNode<T>::has_context() const
{
    return root_to_meta_node.find( this ) != root_to_meta_node.end();
}

template < typename T >
inline const typename CowNode<T>::MetaTree*
CowNode<T>::add_meta_tree_node( const CowNode<T>* new_root,
                                const CowNode<T>* derived_from_root )
{
    typename CowNode<T>::MetaTree * new_node;
    if ( derived_from_root != NULL )
    {
        new_node = new typename CowNode<T>::MetaTree(
            new_root, get_meta_tree_node( derived_from_root ) );
    }
    else
    {
        new_node = new typename CowNode<T>::MetaTree( new_root );
    }
    root_to_meta_node.insert(
        pair<const CowNode<T>*, typename CowNode<T>::MetaTree*>(
            new_root, new_node ) );
    return new_node;
}

template < typename T >
inline typename CowNode<T>::MetaTree*
CowNode<T>::get_meta_tree_node( const CowNode<T>* root )
const
{
    typename map<const CowNode<T>*, typename CowNode<T>::MetaTree*>::iterator it
        = root_to_meta_node.find( root );
    if ( it == root_to_meta_node.end() )
    {
        throw RuntimeError( "Unknown context in get_meta_tree_node." );
    }
    return it->second;
}

template < typename T >
inline unsigned int
CowNode<T>::numof_references() const
{
    return reference_counter;
}

template < typename T >
inline typename CowNode<T>::preorder_iterator
CowNode<T>::begin() const
{
    if ( this->is_referenced() )
    {
        throw RuntimeError( "Can't create an iterator on a non-root node "
                            "without knowing the context." );
    }
    typename CowNode<T>::preorder_iterator it
        = typename
          CowNode<T>::preorder_iterator::preorder_iterator(
        ( CowNode<T>* ) this );
    return it;
}

template < typename T >
inline const typename CowNode<T>::preorder_iterator&
CowNode<T>::end()
{
    return CowNode<T>::end_iterator;
}

template < typename T >
inline void
CowNode<T>::reference()
{
    ++reference_counter;
}

template < typename T >
inline void
CowNode<T>::unreference()
{
    --reference_counter;
}

template < typename T >
inline bool
CowNode<T>::is_private()
{
    return reference_counter <= 1;
}

#endif
