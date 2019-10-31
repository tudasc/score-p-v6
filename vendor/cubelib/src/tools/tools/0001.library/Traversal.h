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



#ifndef TRAVERSAL_H_GUARD_
#define TRAVERSAL_H_GUARD_

/**
 * @file    Traversal.h
 * @brief   This file contains an abstract base class for all kinds of
 *          Traversals.
 */

namespace cube
{
class CnodeSubForest;
class CnodeSubTree;

/**
 * @enum    Traversal_Type
 * @brief   Type of the traversal. Indicates the order in which the tree is
 *          traversed.
 *
 * Used to indicate how a Forest of Trees should be traversed. Possible values
 * are TRAVERSE_PREORDER, TRAVERSE_POSTORDER, TRAVERSE_BREADTH_FIRST,
 * TRAVERSE_UNORDERED and TRAVERSE_ROOTS.
 *
 * Please note, that the implementation of the Traversal_Type handling is not
 * contained in the CnodeSubForest and CnodeSubTree classes, not in Traversal.
 */
typedef enum Traversal_Type
{
    TRAVERSE_PREORDER,
    TRAVERSE_POSTORDER,
    TRAVERSE_BREADTH_FIRST,
    TRAVERSE_UNORDERED,
    TRAVERSE_ROOTS
} Traversal_Type;

/**
 * @class   Traversal
 * @brief   Abstract base class. Contains a number of hooks that are called
 *          when traversing the tree.
 *
 * This is an abstract base class common to all traversals. It consists out
 *  of a methods that you may or may not implement in a derived class and that
 *  are guaranteed to be called at certain times during traversing the tree.
 *
 * One method, that specifies the type of the traversal must be implemented in
 *  any derived classes. This class, hence, is abstract.
 *
 * This class basically is only a collection of methods, merely an interface
 * CnodeSubForest and CnodeSubTree can rely on. Therefore, the classes
 * CnodeSubForest and CnodeSubTree are friends of the Traversal class.
 */
class Traversal
{
public:
    /**
     * @fn Traversal()
     *
     * Initializes some variables in the Traversal class. Always call this when
     * you extend the Traversal class!
     */
    Traversal();

    /**
     * @fn virtual ~Traversal()
     *
     * Destroys the instance.
     */
    virtual
    ~Traversal();

    /**
     * @fn virtual Traversal_Type get_type() const
     *
     * (Abstract method) Simply returns the Traversal_Type.
     */
    virtual Traversal_Type
    get_type() const = 0;

    /**
     * @fn virtual bool is_constant() const
     *
     * Returns whether the function modifies the tree while traversing it or
     * not. The default implementation just returns false.
     *
     * The Forest class may rely on this.
     */
    virtual bool
    is_constant() const;

    /**
     * @fn void run(CnodeSubForest* forest)
     *
     * This is just a convenience method that runs the traversal on a certain
     * forest. It is equivalent to forest->run(this).
     *
     * @param forest The forest, the traversal will be run on.
     */
    void
    run( CnodeSubForest* forest );

    /**
     * @fn bool has_stopped() const
     *
     * Returns either true when the STOP flag is set or false if this is not
     * the case. See Traversal::stop_traversing for more details about this
     * flag.
     */
    inline bool
    has_stopped() const
    {
        return traversal_stopped;
    }

    /**
     * @fn const CnodeSubTree* get_current_node() const
     *
     * Returns the current node traversed.
     */
    inline const CnodeSubTree*
    get_current_node() const
    {
        return const_cast<const CnodeSubTree*>(current_node);
    }

protected:
    friend class CnodeSubForest;
    friend class CnodeSubTree;

    /**
     * @fn virtual void initialize(CnodeSubForest* forest)
     *
     * This function is called once for every forest, the traversal is applied
     * on, before traversing any of the trees within the forest. It is provided
     * with a pointer to the instance of CnodeSubForest, the traversal is
     * applied on.
     *
     * @param forest The forest the traversal is run on.
     */
    virtual void
    initialize( CnodeSubForest* forest );

    /**
     * @fn virtual void initialize_tree(CnodeSubTree* tree)
     *
     * This function is called once for every tree within the forest, the
     * traversal is applied on and gets a pointer to the root of the tree that
     * is traversed right after this function is called.
     *
     * @param tree The tree the traversal is run on next.
     */
    virtual void
    initialize_tree( CnodeSubTree* tree );

    /**
     * @fn virtual void node_handler(CnodeSubTree* node)
     *
     * This function is called once for each node within a tree which is part
     * of the forest, the traversal is applied on. It gets a pointer to the
     * currently traversed node.
     *
     * @param node The current node.
     */
    virtual void
    node_handler( CnodeSubTree* node );

    /**
     * @fn virtual void finalize_tree(CnodeSubTree* tree)
     *
     * Similarly to initialize_tree, this function is called once for each
     * tree within the forest the traversal is applied on and gets a pointer
     * to the root of a specific tree. It is however called right after the
     * traversal for that tree is finished.
     *
     * @param tree The tree the traversal just was run on.
     */
    virtual void
    finalize_tree( CnodeSubTree* tree );

    /**
     * @fn virtual void finalize(CnodeSubForest* forest)
     *
     * This function is called once for every forest, the traversal is applied
     * on, after traversing all of the trees within the forest. It is provided
     * with a pointer to the instance of CnodeSubForest, the traversal is
     * applied on.
     *
     * @param forest The forest the traversal was run on.
     */
    virtual void
    finalize( CnodeSubForest* forest );

    /**
     * @fn void stop_traversing()
     *
     * When you call this method, you indicate that you are not interested
     * in any further nodes. This method sets the STOP flag. After calling this
     * function, it is guaranteed that the method Traversal::node_handler won't
     * be called anymore. The method Traversal::finalize_tree is called for the
     * tree that is currently processed. Then the function Traversal::finalize
     * is called. If you choose to reset the flag in Traversal::finalize_tree
     * using Traversal::unstop_traversing, the next tree in the forest will be
     * processed as usual.
     *
     * The flag is also reset when the Traversal is bound to a new
     * CnodeSubForest, i.e. the default implementation of initialize resets the
     * flag.
     */
    void
    stop_traversing();

    /**
     * @fn void unstop_traversing()
     *
     * Resets the STOP flag. The only place were this function should be used
     * is within the Traversal::finalize_tree function! For more details, see
     * Traversal::stop_traversing.
     */
    void
    unstop_traversing();

private:
    inline void
    set_current_node( CnodeSubTree* node )
    {
        current_node = node;
    }
    bool          traversal_stopped;
    CnodeSubTree* current_node;
};
}

#endif
