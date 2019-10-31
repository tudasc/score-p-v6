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


#ifndef CUBE_CLIENT_CONNECTION_H
#define CUBE_CLIENT_CONNECTION_H

#include <string>

#include <CubeConnection.h>
#include <CubeCountedPtr.h>

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

class ClientConnection
    : public Connection
{
    public:
        /// Type name for the connection pointer
        typedef ClientConnectionPtr Ptr;


        /// @brief Factory method to establish a connection
        ///
        /// @param socket
        ///     Socket object to use for connection
        /// @param url_string
        ///     URL-encoded server address
        /// @return
        ///     Pointer to connection object.
        ///
        static Ptr
        create(SocketPtr          socket,
               const std::string& url_string);


    protected:
        /// @brief Protected constructor to ensure use of factory method.
        ///
        ClientConnection(SocketPtr socket);

        /// @brief Shutting down the client connection.
        ///
        virtual
        ~ClientConnection();

        /// @brief Establish a connection to a remote server.
        ///
        /// @param socket
        ///     Socket object to use for communication
        /// @param url_string
        ///     URL-encoded server address.
        ///
        ClientConnection(SocketPtr          socket,
                         const std::string& url_string);


    private:
        /// Pointer-class needs to be able to call protected destructor
        friend class CountedPtr< ClientConnection >;
};
}    // namespace cube

#endif    // CUBE_CLIENT_CONNECTION_H
