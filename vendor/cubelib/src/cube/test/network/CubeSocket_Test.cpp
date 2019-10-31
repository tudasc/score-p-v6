/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2017                                                     **
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
 *  @brief   Unit test for the class Socket
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeSocket.h"

#include <string>

#include <gtest/gtest.h>

#include "CubeError.h"

using namespace cube;
using namespace std;
using namespace testing;

#ifndef __PGIC__
TEST( SocketFactory, throwsIfNoFactoryConfigured )
{
    Socket::setSocketFactory( 0 );

    ASSERT_THROW( Socket::create(), std::exception );

    Socket::setSocketFactory( Socket::DEFAULT_SOCKET_FACTORY );
}

TEST( SocketFactory, createsValidDefaultSocket )
{
    SocketPtr socket = Socket::create();

    ASSERT_NE( static_cast<Socket*>( 0 ), socket.get() );
}

#endif