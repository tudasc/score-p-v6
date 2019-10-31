/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016-2019                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2014-2015                                                **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  Copyright (c) 2014-2015                                                **
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
 *  @brief   Definition of the class cube::PosixStreamSocket
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#if defined( HAVE_POSIX_SOCKET )

#include "CubePosixStreamSocket.h"

#include <cstdlib>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "CubeError.h"
#include "CubeServices.h"

using namespace std;

namespace
{
/// @brief Return either IPv4 or IPv6 address.
///
/// @param address
///     Initial address structure.
/// @return
///     Pointer to IPv4 or IPv6 depending on input structure.
///
void*
getSocketAddress( const struct sockaddr* address )
{
    // return IPv4 address if available
    if ( address->sa_family == AF_INET6 )
    {
        return &( ( ( struct sockaddr_in* )address )->sin_addr );
    }

    // return IPv6 address else
    return &( ( ( struct sockaddr_in6* )address )->sin6_addr );
}
}    // namespace

namespace cube
{
PosixStreamSocket::PosixStreamSocket()
    : mConnection( -1 ),
    mServerSocket( -1 )
{
}


PosixStreamSocket::~PosixStreamSocket()
{
    // close open socket for connection
    if ( -1 != mConnection )
    {
        close( mConnection );
    }

    // close open socket for server-side listening
    if ( -1 != mServerSocket )
    {
        close( mServerSocket );
    }
}


string
PosixStreamSocket::getHostname()
{
    return mHostname;
}


string
PosixStreamSocket::getInfoString()
{
    return "POSIX";
}


void
PosixStreamSocket::connect( const string& address,
                            int           port )
{
    struct addrinfo hints, * server_info, * p;
    int             result = 0;

    memset( &hints, 0, sizeof( hints ) );
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ( ( result =
               getaddrinfo( address.c_str(),
                            services::numeric2string( port ).c_str(),
                            &hints, &server_info ) ) != 0 )
    {
        throw UnrecoverableNetworkError( strerror( errno ) );
    }

    for ( p = server_info; p != NULL; p = p->ai_next )
    {
        if ( ( mConnection =
                   socket( p->ai_family, p->ai_socktype, p->ai_protocol ) ) == -1 )
        {
            continue;
        }

        if ( ::connect( mConnection, p->ai_addr, p->ai_addrlen ) == -1 )
        {
            close( mConnection );
            continue;
        }

        // break after successful acquisition of socket
        break;
    }

    if ( p == NULL )
    {
        throw UnrecoverableNetworkError( strerror( errno ) );
    }

    freeaddrinfo( server_info );
}


void
PosixStreamSocket::disconnect()
{
    if ( -1 != mConnection )
    {
        close( mConnection );
        mConnection = -1;
    }
}


void
PosixStreamSocket::listen( int port )
{
    int             result = 0, yes = 1;
    struct addrinfo hints, * server_info, * p;
    memset( &hints, 0, sizeof( hints ) );
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE;

    if ( ( result =
               getaddrinfo( NULL, services::numeric2string( port ).c_str(), &hints,
                            &server_info ) ) != 0 )
    {
        throw UnrecoverableNetworkError( strerror( errno ) );
    }

    char host[ 1024 ];
    char service[ 128 ];
    result = getnameinfo( server_info->ai_addr,
                          sizeof( struct sockaddr ),
                          host,
                          sizeof( host ),
                          service,
                          sizeof( service ),
                          0 );
    mHostname = host;

    for ( p = server_info; p != NULL; p = p->ai_next )
    {
        mServerSocket = socket( p->ai_family, p->ai_socktype, p->ai_protocol );
        if ( -1 == mServerSocket )
        {
            continue;
        }

        if ( setsockopt( mServerSocket, SOL_SOCKET, SO_REUSEADDR, &yes,
                         sizeof( int ) ) == -1 )
        {
            throw UnrecoverableNetworkError( strerror( errno ) );
        }

        if ( ::bind( mServerSocket, p->ai_addr, p->ai_addrlen ) == -1 )
        {
            close( mServerSocket );
            continue;
        }

        // break after successful acquisition of socket
        break;
    }

    if ( p == NULL )
    {
        throw UnrecoverableNetworkError( "Failed to create socket." );
    }

    freeaddrinfo( server_info );

    if ( ::listen( mServerSocket, 10 ) == -1 )
    {
        throw UnrecoverableNetworkError( strerror( errno ) );
    }
}


void
PosixStreamSocket::accept()
{
    while ( 1 )
    {
        struct sockaddr_storage their_addr;
        socklen_t               sin_size = sizeof( their_addr );


        if ( ( mConnection =
                   ::accept( mServerSocket,
                             ( struct sockaddr* )&their_addr,
                             &sin_size ) ) == -1 )
        {
            continue;
        }
        else
        {
            break;
        }
    }
}


size_t
PosixStreamSocket::send( const void* buffer,
                         size_t      num_bytes )
{
    int bytes_sent  = 0;
    int total_bytes = 0;
    int flags       = 0;

    while ( total_bytes < ( int )num_bytes )
    {
        bytes_sent = ::send( mConnection, buffer, num_bytes, flags );
        if ( bytes_sent < 0 )
        {
            throw UnrecoverableNetworkError( strerror( errno ) );
        }
        else
        {
            total_bytes += bytes_sent;
        }
    }

    return bytes_sent;
}


size_t
PosixStreamSocket::receive( void*  buffer,
                            size_t num_bytes )
{
    int bytes_received = 0;
    int total_bytes    = 0;
    int flags          = 0;

    while ( total_bytes < ( int )num_bytes )
    {
        bytes_received = ::recv( mConnection, static_cast<char*>( buffer ) + total_bytes, num_bytes - total_bytes, flags );
        if ( bytes_received < 0 )
        {
            throw UnrecoverableNetworkError( strerror( errno ) );
        }
        else
        {
            total_bytes += bytes_received;
        }
    }

    return bytes_received;
}


bool
PosixStreamSocket::isConnected()
{
    return mConnection != -1;
}


void
PosixStreamSocket::shutdown()
{
    close( mServerSocket );
    mServerSocket = -1;
}


SocketPtr
PosixStreamSocket::create()
{
    return SocketPtr( new PosixStreamSocket() );
}


bool
PosixStreamSocket::isListening()
{
    return mServerSocket != -1;
}
}    /* namespace cube */

#endif
