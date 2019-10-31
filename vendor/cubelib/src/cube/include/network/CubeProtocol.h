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
 *  @brief   Declaration of the class cube::Protocol.
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_PROTOCOL_H
#define CUBE_PROTOCOL_H

#include <map>
#include <numeric>
#include <string>
#include <vector>

#include "CubeNetworkRequest.h"
#include "cube_network_types.h"

namespace cube
{
/*-------------------------------------------------------------------------*/
/**
 *  @class   cube::Protocol
 *  @ingroup CUBE_lib.network
 *  @brief   Set of network request handlers.
 **/
/*-------------------------------------------------------------------------*/

class Protocol
{
    public:
        /// Vector type for network request factory methods
        typedef std::vector< NetworkRequest::factory_method_t > factory_vector_t;

        /// Integer type for protocol version numbers
        typedef protocol_version_t version_t;


        /// Indicator for a protocol in uninitialized state
        static const version_t UNINITIALIZED;

        /// @brief Default constructor.
        ///
        Protocol();

        /// @brief Virtual destructor
        ///
        virtual
        ~Protocol();

        /// @brief Set protocol version and register corresponding requests.
        ///
        /// @param version
        ///     Version number to be set.
        ///
        void
        setVersion(version_t version);

        /// @brief Get version currently set.
        ///
        /// @return
        ///     Currently set version
        ///
        version_t
        getVersion() const;

        /// @brief Get the highest protocol version supported.
        ///
        /// @return
        ///     Protocol version
        ///
        version_t
        getMaxVersion() const;

        /// @brief Create a network request by its registration id.
        ///
        /// @param id
        ///     Identification number of request
        /// @return
        ///     Pointer to network request
        ///
        NetworkRequest::Ptr
        createRequest(NetworkRequest::id_t       id,
                      NetworkRequest::sequence_t sequenceNo) const;

        /// @brief Create a network request by its factory method.
        ///
        /// @param method
        ///     Factory method to be used
        /// @return
        ///     Pointer to network request
        ///
        NetworkRequest::Ptr
        createRequest(NetworkRequest::id_t) const;


    protected:
        /// @brief Register a given request factory method.
        ///
        /// @param method
        ///     Factory method to register
        ///
        void
        registerRequest(NetworkRequest::factory_method_t method);

        /// @brief Reset all internal data structures.
        ///
        void
        reset();


    private:
        /// Vector of factory methods
        factory_vector_t mFactory;

        /// Current protocol version
        version_t mVersion;
};
}    /* namespace cube */

#endif    /* !CUBE_PROTOCOL_H */
