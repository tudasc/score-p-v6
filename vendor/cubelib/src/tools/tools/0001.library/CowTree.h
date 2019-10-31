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



#ifndef COWTREE_H_GUARD_
#define COWTREE_H_GUARD_

/**
 * @file    CowTree.h
 * @brief   Contains a flexible copy-on-write data structure for trees and
 *          some iterators.
 */

#include <iterator>
#include <map>
#include <stack>
#include <vector>

namespace cube
{
template < typename T >
class CowNode;

template < typename T >
class CowNode
{
public:
    class MetaTree
    {
public:
        MetaTree( const CowNode<T>*              root,
                  typename CowNode<T>::MetaTree* parent = NULL );
        ~MetaTree();
        inline const CowNode<T>*
        get_root() const;

        inline typename CowNode<T>::MetaTree*
        get_parent() const;
        inline bool
        is_deletable() const;
        inline unsigned int
        numof_children() const;

        inline typename CowNode<T>::MetaTree*
        get_child(
            unsigned int id ) const;
        inline void
        reference();
        inline void
        unreference();

private:
        const CowNode<T>* root;
        typename CowNode<T>::MetaTree * parent;
        std::vector<typename CowNode<T>::MetaTree*> children;
        int                                         reference_counter;
    };

    class preorder_iterator
    {
public:
        preorder_iterator();
        preorder_iterator( CowNode<T>* root_node );
        preorder_iterator( CowNode<T>*                          node,
                           const typename CowNode<T>::MetaTree* context );
        preorder_iterator( const preorder_iterator& pre_it );
        bool
        operator==( const preorder_iterator& it );
        bool
        operator!=( const preorder_iterator& it );
        T&
        operator*();
        preorder_iterator&
        operator++();

        inline CowNode<T>*
        get_current_node() const;
        void
        skip_children();

private:
        inline void
        push_node_children( CowNode<T>* node );
        inline bool
        equals( const preorder_iterator& it );

        CowNode<T>* current;
        const typename CowNode<T>::MetaTree * context;
        std::stack<CowNode<T>*> node_stack;
    };

#if 0
    class postorder_iterator : public CowNode<T>::abstract_iterator
    {
public:
        postorder_iterator( CowNode<T>* root_node );
        postorder_iterator( CowNode<T>* node,
                            CowNode<T>* context );
        postorder_iterator( const postorder_iterator& post_it );
        postorder_iterator&
        operator++();
    };
#endif

    CowNode( T& reference_object );
    CowNode( T&                reference_object,
             CowNode<T>*       parent,
             const CowNode<T>* root );
    CowNode( CowNode<T>* copy );
    ~CowNode();

    inline unsigned int
    numof_children() const;
    inline bool
    is_referenced() const;

    inline CowNode<T>*
    get_child( unsigned int id ) const;

    CowNode<T>*
    add_child( CowNode<T>*                          child,
               const typename CowNode<T>::MetaTree* context );

    CowNode<T>*
    replace_child( CowNode<T>*                          child,
                   CowNode<T>*                          replacement,
                   const typename CowNode<T>::MetaTree* context );

//      CowNode<T>* relocate_child(CowNode<T>* child,
//            const CowNode<T>* this_context,
//            CowNode<T>* new_parent, const CowNode<T>* new_context);
    CowNode<T>*
    remove_child( unsigned int                         child_id,
                  const typename CowNode<T>::MetaTree* context );

    CowNode<T>*
    remove_child( CowNode<T>*                          child,
                  const typename CowNode<T>::MetaTree* context );

    CowNode<T>*
    get_parent(
        const typename CowNode<T>::MetaTree* meta_node ) const;
    inline T&
    get() const;

    inline typename CowNode<T>::MetaTree*
    get_meta_tree_node( const CowNode<T>* root ) const;
    inline unsigned int
    numof_references() const;

    inline typename CowNode<T>::preorder_iterator
    begin() const;

    inline const typename CowNode<T>::preorder_iterator&
    end();

private:
    CowNode( CowNode<T>*                          copy,
             const typename CowNode<T>::MetaTree* context );
    /**
     * @fn CowNode<T>* make_private(const CowNode<T>* context)
     *
     * Makes sure, you get a private pointer to this instance.
     */
    CowNode<T>*
    make_private( const typename CowNode<T>::MetaTree* context );
    inline bool
    has_context() const;

    inline const typename CowNode<T>::MetaTree*
    add_meta_tree_node( const CowNode<T>* new_root,
                        const CowNode<T>* derived_from_root = NULL );
    inline void
    drop_meta_tree_node( const CowNode<T>* root );
    inline void
    init_parent( CowNode<T>*                          parent,
                 const typename CowNode<T>::MetaTree* context );

    inline CowNode<T>*
    get_parent_noexc(
        const typename CowNode<T>::MetaTree* context ) const;
    inline void
    set_parent( CowNode<T>*                          new_parent,
                const typename CowNode<T>::MetaTree* context );
    inline void
    remove_parent( const typename CowNode<T>::MetaTree* context );
    inline void
    reference();
    inline void
    unreference();
    inline bool
    is_private();

    T&                                                          object;
    unsigned int                                                reference_counter;
    std::map<const typename CowNode<T>::MetaTree*, CowNode<T>*> parent_map;
    std::vector<CowNode<T>*>                                    children;

    static std::map<const CowNode<T>*, typename CowNode<T>::MetaTree*>
                          root_to_meta_node;
    static const typename CowNode<T>::preorder_iterator & end_iterator;
};
}

#include "CowTree.cpp"

#endif
