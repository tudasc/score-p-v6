/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2015-2016                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2009-2014                                                **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  Copyright (c) 2014                                                     **
**  RWTH Aachen University, JARA-HPC                                       **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


#ifndef CUBE_SELECTIONS_H
#define CUBE_SELECTIONS_H

namespace cube
{
/// \brief Indicating the mode of expansion for a selected dimension.
enum ExpansionMode
{
    CUBE_NODE_INCLUSIVE,
    CUBE_NODE_EXCLUSIVE,
    CUBE_NODE_DIFFERENCE,
};

/** \class Selection
 *  \brief Selection class to reduce clutter in the \a CubeSlicer interface.
 */
template <class T>
struct Selection
{
    /** \brief Explicit constructor for dimension selection
     *
     * \param treenode Selected node in the dimension.
     * \param mode Selected mode.
     */
    Selection( const T&      treenode,
               ExpansionMode mode ) :
        mNode( treenode ), mExpansion( mode )
    {
    };

    const T&      mNode;      ///< Selected tree node in the dimension
    ExpansionMode mExpansion; ///< Selected expansion mode for the treenode
};

/** \class Selections
 *  \brief Container class to enable clutter-free selection of zero, one, or multiple nodes of a dimension.
 *
 *  \note The empty selection indicates that all root nodes should be selected.
 */
template <class T>
struct Selections
{
    /** \brief Explicit constructor for empty selections
     */
    Selections();

    /** \brief Explicit constructor for a single selection
     *
     * \param[in] selection Selection to be added to the container
     */
    Selections( const Selection< T > selection )
    {
        mSelections.push_back( selection );
    }

    /** \brief Explicit contstructor for a single selection with selection parameters.
     *
     * \param treenode Selected node in the dimension.
     * \param mode Selected mode.
     */
    Selections( const T&      treenode,
                ExpansionMode mode )
    {
        mSelections.push_back( Selections<T>( treenode, mode ) );
    }

    /** \brief Add \a Selection to the container
     *
     * \param[in] selection Selection to be added to the container
     */
    void
    add( const Selections< T > selection )
    {
        mSelections.push_back( selection );
    }

    /** \brief Check number of selections in the container
     *
     * \return Number of selected nodes
     */
    size_t
    numSelections() const
    {
        return mSelections.size();
    }

private:
    /// Selection container
    std::vector< Selection< T > > mSelections;
};
}

#endif // CUBE_SELECTIONS_H
