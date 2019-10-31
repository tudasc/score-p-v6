/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016                                                     **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/*-------------------------------------------------------------------------*/
/**
 *  @file
 *  @ingroup CUBE_lib.network
 *  @brief   Definition of static methods of the class Socket.
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeSocket.h"

#include "CubeError.h"
#if defined(HAVE_POSIX_SOCKET)
#include "CubePosixStreamSocket.h"
#endif

using namespace cube;

SocketPtr
Socket::create()
{
    if (mSocketFactory)
    {
        return (*mSocketFactory)();
    }
    else
    {
        throw Error("No valid Socket factory available.");
    }
}


void
Socket::setSocketFactory(SocketFactoryMethod factory)
{
    mSocketFactory = factory;
}


#if defined(HAVE_POSIX_SOCKET)
    Socket::SocketFactoryMethod Socket::mSocketFactory =
        PosixStreamSocket::create;
    Socket::SocketFactoryMethod const Socket::DEFAULT_SOCKET_FACTORY =
        PosixStreamSocket::create;
#else
    Socket::SocketFactoryMethod Socket::mSocketFactory         = NULL;
    Socket::SocketFactoryMethod const Socket::DEFAULT_SOCKET_FACTORY = NULL;
#endif
