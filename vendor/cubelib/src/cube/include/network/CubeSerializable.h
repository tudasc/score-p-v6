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
**  Copyright (c) 2015                                                     **
**  RWTH Aachen University, JARA-HPC                                       **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/*-------------------------------------------------------------------------*/
/**
 *  @file
 *  @ingroup CUBE_lib.network
 *  @brief   Declaration of the class cube::Serializable.
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_SERIALIZABLE_H
#define CUBE_SERIALIZABLE_H

#include <string>

namespace cube
{
// Forward declarations
class Connection;
class CubeProxy;

/*-------------------------------------------------------------------------*/
/**
 *  @class   cube::Serializable
 *  @ingroup CUBE_lib.network
 *  @brief   A serialization interface for objects in Cube.
 **/
/*-------------------------------------------------------------------------*/

class Serializable
{
    public:
        /// @name Construction & destruction
        /// @{

        /// @brief
        ///     Virtual destructor
        ///
        virtual ~Serializable()
        {
        }

        /// @}
        /// @name Serialization
        /// @{

        /// @brief
        ///     Public interface to serialization
        ///
        void
        serialize(Connection& connection) const;


    protected:
        /// @brief
        ///     Pack data to be serialized
        /// @param connection
        ///     Active Cube connection.
        ///
        /// @note
        ///     The implementation for a specific class needs to
        ///     call the implementation for its base class prior.
        virtual void
        pack(Connection& connection) const = 0;

        /// @name
        ///     Returns a key used to identify the correct factory method.
        /// @return
        ///     Serialization key.
        ///
        /// @todo Could this be better fixed by the CRTP?
        ///
        virtual std::string
        get_serialization_key() const = 0;

        /// @}
};
}    /* namespace cube */

#endif    /* ! CUBE_SERIALIZABLE_H */
