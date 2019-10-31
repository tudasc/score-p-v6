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
 *  @file    CubeProtocol_Test.cpp
 *  @ingroup Cube_lib_network_tests
 *  @brief   Unit tests for cube::Protocol
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeProtocol.h"
#include "CubeNetworkRequest.h"

#include <string>

#include <gtest/gtest.h>

#include "CubeError.h"

using namespace cube;
using namespace std;
using namespace testing;

class CubeProtocol : public Test
{
public:
    Protocol protocol;
};

TEST_F( CubeProtocol, isInitializedAsZero ) {
    ASSERT_EQ( protocol.getVersion(), 0 );
}

#ifndef __PGIC__
TEST_F( CubeProtocol, throwsNetworkErrorIfSetToUnsupportedVersion ) {
 ASSERT_THROW( protocol.setVersion( protocol.getMaxVersion() + 1 ) , cube::UnrecoverableNetworkError);
}
#endif

TEST_F( CubeProtocol, initiallySupportsProtocolNegotiationRequest ) {
    ASSERT_EQ( protocol.createRequest( NEGOTIATE_PROTOCOL_REQUEST, 0)->getId(), NEGOTIATE_PROTOCOL_REQUEST );
}

TEST_F( CubeProtocol, initiallySupportsDisconnectRequest ) {
    ASSERT_EQ( protocol.createRequest( DISCONNECT_REQUEST, 0 )->getId(), DISCONNECT_REQUEST );
}
#ifndef __PGIC__ 
TEST_F( CubeProtocol, throwsNetworkErrorOnCreatingUnregisteredRequest ) {
    ASSERT_THROW( protocol.createRequest( NUM_NETWORK_REQUESTS, 0 ), cube::UnrecoverableNetworkError );
}
#endif