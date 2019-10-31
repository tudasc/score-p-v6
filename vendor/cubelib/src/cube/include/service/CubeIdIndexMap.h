/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016                                                     **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/*-------------------------------------------------------------------------*/
/**
 *  @file
 *  @ingroup CUBE_lib.service
 *  @brief   Declaration of the class IdIndexMap.
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_IDINDEXMAP_H
#define CUBE_IDINDEXMAP_H

#include <map>

#include "CubeTypes.h"

namespace cube
{
/*-------------------------------------------------------------------------*/
/**
 *  @class   cube::IdIndexMap
 *  @ingroup CUEB_lib.service
 *  @brief   A container for ID to index translations used in subtree queries.
 *
 **/
/*-------------------------------------------------------------------------*/

class IdIndexMap
{
    public:


        // --- Type definitions -----------------------------

        typedef std::map< uint32_t, size_t > container_t;

        // --- Iterators ------------------------------------

        class iterator
            : public std::iterator< std::bidirectional_iterator_tag,
                                    std::size_t >
        {
            public:
                /// @name Constructors & destructor
                /// @{

                iterator();

                /// @}
                /// @name Lookup
                /// @{

                /// @brief Get id of the mapping pointed to by iterator.
                ///
                /// @return
                ///     ID
                ///
                uint32_t
                getId() const;

                /// @brief Get index of the mapping pointed to by iterator.
                ///
                /// @return
                ///     index
                ///
                size_t
                getIndex() const;

                /// @}
                /// @name Increment/Decrement interface
                /// @{

                /// @brief Prefix increment operator.
                ///
                /// @return
                ///     Element after increment.
                ///
                iterator&
                operator++();

                /// @brief Postfix increment operator.
                ///
                /// @return
                ///     Element before increment.
                ///
                iterator
                operator++(int);

                /// @brief Prefix decrement operator.
                ///
                /// @return
                ///     Element after decrement.
                ///
                iterator&
                operator--();

                /// @brief Postfix decrement operator.
                ///
                /// @return
                ///     Element before decrement.
                ///
                iterator
                operator--(int);

                /// @}
                /// @name Comparison.
                /// @{

                /// @brief Inequality comparison
                ///
                /// @return
                ///     true, if @a rhs does not point to the same element,
                ///     false, otherwise.
                ///
                bool
                operator!=(const iterator& rhs) const;

                /// @brief Equality comparison
                ///
                /// @return
                ///     true, if @a rhs points to the same element,
                ///     false, otherwise.
                ///
                bool
                operator==(const iterator& rhs) const;

                /// @}


            private:
                /// @name Constructors & destructor
                /// @{

                iterator(container_t::const_iterator iterator);

                /// @}

                /// @brief Iterator to associated container
                container_t::const_iterator mIterator;

                friend class IdIndexMap;
        };


        // --- Public methods -------------------------------

        /// @name Capacity
        /// @}

        /// @brief Query whether the container is empty or not.
        ///
        /// @return true, if empty, false otherwise.
        ///
        bool
        empty() const;

        /// @brief Query the number of elements in the container.
        ///
        /// @return number of elements stored in the container.
        ///
        std::size_t
        size() const;

        /// @}
        /// @name Modifiers
        /// @{

        /// @brief Insert a mapping from id to index.
        ///
        /// @param[in]  id      Id of the object
        /// @param[in]  index   Index of the object
        ///
        void
        insert(uint32_t id,
               size_t   index);


        /// @brief Erase all mappings
        ///
        void
        clear();

        /// @}
        /// @name Lookup
        /// @{

        /// @brief Return the index for a given id.
        ///
        /// @param[in]  id  ID of object
        ///
        /// @return Mapped index for given id.
        size_t
        getIndex(uint32_t id) const;

        /// @}
        /// @name Iterators
        /// @{

        /// @brief Get iterator to first element of the map.
        ///
        /// @return Iterator pointing to first element of the map
        ///
        iterator
        begin() const;

        /// @brief Get iterator to end of the map.
        ///
        /// @return Iterator pointing to invalid element after last element of the map.
        ///
        iterator
        end() const;

        /// @}


    private:
        /// Container for mappings
        container_t mMappings;
};
}    /* namespace cube */

#endif    /* ! CUBE_IDINDEXMAP_H */
