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
 *  @brief   Declaration of the class Socket.
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_SOCKET_H
#define CUBE_SOCKET_H

#include <string>

#include "cube_network_types.h"

namespace cube
{
/*-------------------------------------------------------------------------*/
/**
 *  @class   Socket
 *  @ingroup CUBE_lib.network
 *  @brief   Abstract base class for socket communication in Cube.
 **/
/*-------------------------------------------------------------------------*/
class Socket
{
    public:
        typedef SocketPtr (* SocketFactoryMethod)();


        static SocketFactoryMethod const DEFAULT_SOCKET_FACTORY;

        /// @name Construction and destruction
        /// @{

        /// @brief Create a new Socket object.
        ///
        static SocketPtr
        create();

        /// @brief Set factory method for new Socket objects.
        ///
        static void
        setSocketFactory(SocketFactoryMethod factory);

        /// @brief Empty virtual destructor to allow derived classes
        ///
        virtual
        ~Socket()
        {
        }

        /// @}
        /// @name Client interface
        /// @{

        /// @brief Client-side call establish a connection.
        ///
        /// @param address
        ///     Server address (DN or IP)
        /// @param port
        ///     Port server listens on.
        ///
        virtual void
        connect(const std::string& address,
                int                port) = 0;

        /// @brief Disconnect communication.
        ///
        virtual void
        disconnect() = 0;

        /// @}
        /// @name Server interface
        /// @{

        /// @brief Server-side setup of communication channel.
        ///
        /// @param port
        ///     Port to listen on
        ///
        virtual void
        listen(int port) = 0;

        /// @brief Block until a new incoming connection is accepted.
        ///
        virtual void
        accept() = 0;

        /// @brief Shutdown server-side socket connection.
        ///
        virtual void
        shutdown() = 0;

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
             size_t      num_bytes) = 0;

        /// @brief Receive data from remote communication partner.
        ///
        /// @param buffer
        ///     Receive buffer.
        /// @param num_bytes
        ///     Length of receive buffer.
        /// @return
        ///     Number of bytes received.
        ///
        virtual size_t
        receive(void*  buffer,
                size_t num_bytes) = 0;

        /// @}
        /// @name Connection status
        /// @{

        /// @brief Check connection status.
        ///
        /// @return
        ///     True, if socket connection is established,
        ///     false, otherwise.
        ///
        virtual bool
        isConnected() = 0;


        /// @brief Check server socket status.
        ///
        /// @return
        ///     True if server is listening on a socket.
        ///
        virtual bool
        isListening() = 0;

        /// @}
        /// @name Object information
        /// @{

        /// @brief Get Socket information
        ///
        /// @return
        ///     Information string.
        ///
        virtual std::string
        getInfoString() = 0;

        /// @brief Returns the hostname of the machine.
        ///
        /// @return
        ///     Hostname of the machine.
        ///
        virtual std::string
        getHostname() = 0;

        /// @}


    private:
        /// @brief Pointer to Socket factory method
        ///
        static SocketFactoryMethod mSocketFactory;
};
}    /* namespace cube */

#endif    /* CUBE_SOCKET_H */
