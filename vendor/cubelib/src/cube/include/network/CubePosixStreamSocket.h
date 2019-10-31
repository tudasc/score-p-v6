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
 *  @brief   Declaration of the class PosixStreamSocket.
 *
 *  This header file provides the declaration of the class PosixStreamSocket.
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_POSIX_STREAM_SOCKET_H
#define CUBE_POSIX_STREAM_SOCKET_H

#include "CubeSocket.h"

#if defined(HAVE_POSIX_SOCKET)

#include <string>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

namespace cube
{
/*-------------------------------------------------------------------------*/
/**
 *  @class   PosixStreamSocket
 *  @ingroup CUBE_lib.network
 *  @brief   Cube socket implementation using POSIX stream sockets.
 **/
/*-------------------------------------------------------------------------*/
class PosixStreamSocket
    : public Socket
{
    public:
        /// @name Construction and destruction
        /// @{

        /// @brief Create a PosixStreamSocket
        static SocketPtr
        create();

        /// @brief Virtual destructor closing internal sockets if open.
        ///
        virtual
        ~PosixStreamSocket();

        /// @}
        /// @name Client interface
        /// @{

        /// @brief Client-side call to connection to a server address and port.
        ///
        /// @param address
        ///     Text representation of server address.
        /// @param port
        ///     Port number to connect to.
        ///
        /// @note Throws NetworkError exception if socket acquisition fails.
        ///
        virtual void
        connect(const std::string& address,
                int                port);

        /// @brief Close the internal connection socket.
        ///
        virtual void
        disconnect();

        /// @}
        /// @name Server interface
        /// @{

        /// @brief Listen for incoming connections.
        ///
        /// @param port
        ///     Network port to listen for connection requests.
        ///
        /// @note Throws NetworkError exception if socket acquisition fails.
        ///
        virtual void
        listen(int port);

        /// @brief Block until a new incoming connection was accepted.
        ///
        virtual void
        accept();


        /// @brief Disconnect server socket.
        ///
        virtual void
        shutdown();

        /// @}
        /// @name Data transfer
        /// @{

        /// @brief Send data to remote communication partner.
        ///
        /// @param buffer
        ///     Payload
        /// @param num_bytes
        ///     Number of bytes in the payload
        ///
        virtual size_t
        send(const void* buffer,
             size_t      num_bytes);

        /// @brief Receive data from remote communication partner.
        ///
        /// @param buffer
        ///     Payload
        /// @param num_bytes
        ///     Number of bytes in the payload.
        ///
        virtual size_t
        receive(void*  buffer,
                size_t num_bytes);

        /// @}
        /// @name Connection status
        /// @{

        virtual bool
        isConnected();

        virtual bool
        isListening();

        /// @}
        /// @name Socket information
        /// @{

        virtual std::string
        getHostname();

        std::string
        getInfoString();

        /// @}


    protected:
        /// @name Construction and destruction
        /// @{

        /// @brief Default constructor.
        ///
        PosixStreamSocket();

        /// @}


    private:
        /// @brief Socket descriptor for communication between client and server.
        ///
        int mConnection;

        /// @brief Socket descriptor for server to listen for incoming connections.
        ///
        int mServerSocket;

        /// @brief Hostname of the machine the Socket is created on.
        ///
        std::string mHostname;
};
}    /* namespace cube */


#endif
#endif    /* CUBE_POSIX_STREAM_SOCKET_H */
