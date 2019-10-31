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
 *  @brief   Declaration of the class cube::SerializablesFactory.
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_SERIALIZABLESFACTORY_H
#define CUBE_SERIALIZABLESFACTORY_H

#include <map>
#include <string>

#include "CubeSerializable.h"
#include "CubeSingleton.h"

namespace cube
{
class Connection;
class CubeProxy;
class SerializablesFactory;


/*-------------------------------------------------------------------------*/
/**
 *  @class   cube::SerializablesFactory
 *  @ingroup CUBE_lib.network
 *  @brief   A flexible factory to create serialized objects from a stream.
 *
 *  TODO Provide long description for cube::SerializablesFactory.
 **/
/*-------------------------------------------------------------------------*/

typedef cube::Singleton< SerializablesFactory,
                         NoLocking > MySerializablesFactory;

class SerializablesFactory
{
    public:


        /// @brief Factory callback function type.
        typedef Serializable* (* callback_t)(Connection&,
                                             const CubeProxy&);

        /// @brief Container for callback functions.
        typedef std::map< std::string, callback_t > container_t;

        /// @brief Default constructor implicitly registering known factory
        ///     methods.
        ///
        SerializablesFactory();


        /// @brief Creates a serializable object from a Cube connection stream.
        ///
        /// @param connection
        ///     Active Cube connection.
        /// @param cubeProxy,
        ///     Cube proxy for internal cross-referencing of objects.
        /// @return
        ///     Concrete object of a derived class of cube::Serializable.
        ///
        Serializable*
        create(Connection&      connection,
               const CubeProxy& cubeProxy) const;

        /// @brief Register a factory callback for a given key.
        ///
        /// @param key
        ///     Identifier for factory callback.
        /// @param callback
        ///     Callback function that creates a concrete object.
        /// @return
        ///     Pointer to a concrete object.
        ///
        bool
        registerCallback(const std::string& key,
                         callback_t         callback);

        /// @brief Unregister a factory callback for certain key.
        ///
        /// @param key
        ///     Identifier of callback to be unregistered.
        /// @return
        ///     True if callback was registered and successfully unregistered.
        ///
        bool
        unregisterCallback(const std::string& key);


    private:
        /// @brief Registry of factory callbacks
        container_t mRegistry;
};
}    /* namespace cube */

#endif    /* ! CUBE_SERIALIZABLESFACTORY_H */
