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
 *  @brief   Declaration of the class cube::NegotiateProtocolRequest
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_NEGOTIATEPROTOCOLREQUEST_H
#define CUBE_NEGOTIATEPROTOCOLREQUEST_H

#include <string>

#include "cube_network_types.h"
#include <CubeNetworkRequest.h>

namespace cube
{
// forward declarations
class ClientCallbackData;
class ServerCallbackData;

/*-------------------------------------------------------------------------*/
/**
 *  @class   cube::NegotiateProtocolRequest
 *  @ingroup CUBE_lib.network
 *  @brief   Negotiate protocol version between client and server
 **/
/*-------------------------------------------------------------------------*/

class NegotiateProtocolRequest
    : public NetworkRequest
{
    public:
        /// Virtual destructor
        virtual
        ~NegotiateProtocolRequest();

        /// @brief Client- and server-side factory method.
        ///
        /// @return
        ///     Pointer to created request.
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
        /// @brief Stream information from client to server.
        ///
        /// @param[in,out] connection
        ///     Reference to connection on client.
        /// @param[in,out] data
        ///     Pointer to callback data.
        ///
        virtual void
        sendRequestPayload(ClientConnection&   connection,
                           ClientCallbackData* data) const;

        /// @brief Receive information from client on server.
        ///
        /// @param[in,out] connection
        ///     Reference to connection on client.
        /// @param[in,out] data
        ///     Pointer to callback data.
        ///
        virtual void
        sendResponsePayload(ServerConnection&   connection,
                            ServerCallbackData* data) const;

        /// @brief Stream information from server to client.
        ///
        /// @param[in,out] connection
        ///     Reference to connection on client.
        /// @param[in,out] data
        ///     Pointer to callback data.
        ///
        virtual void
        receiveResponsePayload(ClientConnection&   connection,
                               ClientCallbackData* data);

        /// @brief Receive information from server on client.
        ///
        /// @param[in,out] connection
        ///     Reference to connection on client.
        /// @param[in,out] data Pointer to callback data.
        ///
        virtual void
        receiveRequestPayload(ServerConnection&   connection,
                              ServerCallbackData* data);


    private:
        /// @brief Private constructor.
        ///
        NegotiateProtocolRequest();

        friend class ClientConnection;
        friend class Protocol;
};
}    /* namespace cube */

#endif    /* !CUBE_NEGOTIATEPROTOCOLREQUEST_H */
