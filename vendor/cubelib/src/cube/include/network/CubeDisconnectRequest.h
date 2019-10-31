/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016                                                     **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2014                                                     **
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


/*-------------------------------------------------------------------------*/
/**
 *  @file
 *  @ingroup CUBE_lib.network
 *  @brief   Declaration of the class cube::DisconnectRequest.
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_DISCONNECTREQUEST_H
#define CUBE_DISCONNECTREQUEST_H

#include "CubeNetworkRequest.h"

namespace cube
{
// forward declarations
class ClientCallbackData;
class ServerCallbackData;

/*-------------------------------------------------------------------------*/
/**
 *  @class   cube::DisconnectRequest
 *  @ingroup CUBE_lib.network
 *  @brief   Network request to disconnect client and server.
 **/
/*-------------------------------------------------------------------------*/

class DisconnectRequest
    : public NetworkRequest
{
    public:
        /// Virtual destructor
        virtual
        ~DisconnectRequest();

        /// @brief Client- and server-side factory method.
        ///
        /// @return Pointer to created request.
        ///
        static NetworkRequestPtr
        create();

        /// @brief Get the name of this request type.
        ///
        /// @return
        ///     String representation of request name.
        ///
        virtual std::string
        getName() const;

        /// @brief Get the unique network request ID.
        ///
        /// @return
        ///     Unique request Id defined in %cube::NetworkRequestId
        ///
        virtual NetworkRequest::id_t
        getId() const;


    protected:
        /// @brief Stream information from client to server
        ///
        /// @param[in,out] connection
        ///     Reference to connection on client.
        /// @param[in,out] data
        ///     Pointer to callback data.
        ///
        virtual void
        receiveRequestPayload(ServerConnection&   connection,
                              ServerCallbackData* data);

        /// @brief Receive information from server on client.
        ///
        /// @param[in,out] connection
        ///     Reference to connection on client.
        /// @param[in,out] data Pointer to callback data.
        ///
        virtual void
        receiveResponsePayload(ClientConnection&   connection,
                               ClientCallbackData* data);


    private:
        /// @brief Private constructor.
        ///
        DisconnectRequest();

        /// @brief Connection to disconnect
        ///
        Connection* mConnection;

        friend class ClientConnection;
        friend class Protocol;
};
}    /* namespace cube */

#endif    /* !CUBE_DISCONNECTREQUEST_H */
