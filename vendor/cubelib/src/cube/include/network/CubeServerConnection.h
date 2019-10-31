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
 *  @brief   Declaration of the class ClientConnection.
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_SERVER_CONNECTION_H
#define CUBE_SERVER_CONNECTION_H

#include "CubeConnection.h"
#include "CubeCountedPtr.h"
#include "cube_network_types.h"

namespace cube
{
/*-------------------------------------------------------------------------*/
/**
 *  @class   ClientConnection
 *  @ingroup CUBE_lib.network
 *  @brief   RAII-enabled class to enable communication to a Cube server.
 *
 *  The connection is established on creation of the object through the
 *  factory method. Interaction with the object is only available through
 *  a reference counted pointer type. The connection is shut down after
 *  the last reference to the connection is destroyed.
 **/
/*-------------------------------------------------------------------------*/

class ServerConnection
    : public Connection
{
    public:
        /// Type name for the connection pointer
        typedef ServerConnectionPtr Ptr;


        /// @brief Establish a server connection that listens on a specific port.
        ///
        /// @param socket
        ///     Socket object to use for connection
        /// @param port
        ///     Port to listen to
        ///
        static Ptr
        create(SocketPtr socket,
               size_t    port);

        /// @brief Shutting down the server connection.
        ///
        virtual
        ~ServerConnection();

        /// @brief Waiting for and accepting an incoming client connection.
        ///
        void
        accept();

        /// @brief Create a request from the incoming connection stream.
        ///
        /// @return
        ///     Point to a request object
        ///
        NetworkRequestPtr
        createRequestFromStream();

        /// @brief Indicator whether a server socket is set up.
        ///
        /// @return
        ///     True, if server socket is set up on a specific port,
        ///     false, otherwise.
        ///
        bool
        isListening() const;

        /// @brief Stop listening on the server socket.
        ///
        void
        stopListening();


    protected:
        /// @brief Construct server object listening on the given port.
        ///
        /// @param Socket
        ///     Socket object to use for connection
        /// @param port
        ///     Port to listen for incoming client connections.
        ///
        ServerConnection(SocketPtr socket,
                         size_t    port);
};
}    /* namespace cube */

#endif    /* CUBE_SERVER_CONNECTION_H */
