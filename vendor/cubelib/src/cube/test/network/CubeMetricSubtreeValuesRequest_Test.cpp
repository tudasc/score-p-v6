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
 *  @ingroup CUBE_lib.network.testing
 *  @brief   Unit tests for MetricSubtreeValuesRequest
 **/
/*-------------------------------------------------------------------------*/

#include <config.h>

#include "CubeMetricSubtreeValuesRequest.h"

#include <deque>
#include <string>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "CubeClientCallbackData.h"
#include "CubeClientConnection.h"
#include "CubeCnode.h"
#include "CubeError.h"
#include "CubeIdIndexMap.h"
#include "CubeIoProxy.h"
#include "CubeMetric.h"
#include "CubeServerCallbackData.h"
#include "CubeServerConnection.h"
#include "CubeSocket.h"
#include "CubeSysres.h"
#include "CubeSystemTreeNode.h"

using namespace cube;
using namespace std;
using namespace testing;

// --- Stubs ---------------------------------------------------------

class ClientConnectionStub
    : public ClientConnection
{
public:
    ClientConnectionStub()
        : ClientConnection( SocketPtr( 0 ) )
    {
    }

    void
    send( const void* buffer,
          size_t      size )
    {
        for ( size_t i = 0; i < size; ++i )
        {
            mBuffer.push_back( static_cast< const uint8_t* >( buffer )[ i ] );
        }
    }

    deque< uint8_t > mBuffer;
};


class ServerConnectionStub
    : public ServerConnection
{
public:
    ServerConnectionStub()
        : ServerConnection( SocketPtr( 0 ), 0 )
    {
    }

    ServerConnectionStub( const ClientConnectionStub& rhs )
        : ServerConnection( SocketPtr( 0 ), 0 )
    {
        mBuffer = rhs.mBuffer;

        // skip request header
        for ( size_t i = 0; i < sizeof( NetworkRequest::marker_t )
              + sizeof( NetworkRequest::id_t )
              + sizeof( NetworkRequest::sequence_t )
              + sizeof( NetworkRequest::marker_t ); ++i )
        {
            mBuffer.pop_front();
        }
    }

    size_t
    receive( void*  buffer,
             size_t size )
    {
        for ( size_t i = 0; i < size; ++i )
        {
            static_cast< uint8_t* >( buffer )[ i ] = mBuffer.front();
            mBuffer.pop_front();
        }

        return size;
    }

    deque< uint8_t > mBuffer;
};


class CubeIoProxyStub
    : public CubeIoProxy
{
public:

    MOCK_CONST_METHOD0( getCnodes, const vector< Cnode* >&( ) );
    MOCK_CONST_METHOD0( getRegions, const vector< Region* >&( ) );
    MOCK_CONST_METHOD0( getSystemResources, const vector< Sysres* >&( ) );
    MOCK_CONST_METHOD0( getMetrics, const vector< Metric* >&( ) );
    MOCK_CONST_METHOD0( closeReport, void() );
};

// --- Fixtures ------------------------------------------------------

class RequestT
    : public Test
{
public:
    virtual void
    SetUp()
    {
        arbitraryText   = "arbitrary";
        arbitraryNumber = 4711;
        depthZero       = 0;
        idZero          = 0;

        Cnode*  parentCnodeNull  = static_cast< Cnode* >( 0 );
        Sysres* parentSysresNull = static_cast< Sysres* >( 0 );

        Region* temporaryRegion = setupRegion();
        Cnode*  temporaryCnode  = setupCnode( temporaryRegion,
                                              parentCnodeNull );
        cnodeSelection.push_back( make_pair( temporaryCnode,
                                             CUBE_CALCULATE_INCLUSIVE ) );

        Sysres* temporarySysres = setupSysres( parentSysresNull );
        sysresSelection.push_back( make_pair( temporarySysres,
                                              CUBE_CALCULATE_INCLUSIVE ) );

        rootMetric = setupMetric();

        clientCallbackData = new ClientCallbackData();
        serverCallbackData = new ServerCallbackData();

        serverCallbackData->setCube( &cubeIoProxyStub );

        ON_CALL( cubeIoProxyStub, getCnodes() )
        .WillByDefault( ReturnRef( mStubCnodes ) );
        ON_CALL( cubeIoProxyStub, getRegions() )
        .WillByDefault( ReturnRef( mStubRegions ) );
        ON_CALL( cubeIoProxyStub, getMetrics() )
        .WillByDefault( ReturnRef( mStubMetrics ) );
        ON_CALL( cubeIoProxyStub, getSystemResources() )
        .WillByDefault( ReturnRef( mStubSysres ) );
    }

    virtual void
    TearDown()
    {
        delete clientCallbackData;
        delete serverCallbackData;
    }

    string                    arbitraryText;
    size_t                    arbitraryNumber;
    list_of_cnodes            cnodeSelection;
    list_of_sysresources      sysresSelection;
    vector< Cnode* >          mStubCnodes;
    vector< Region* >         mStubRegions;
    vector< Metric* >         mStubMetrics;
    vector< Sysres* >         mStubSysres;
    value_container           inclusiveValues;
    value_container           exclusiveValues;
    Metric*                   rootMetric;
    IdIndexMap                idIndexMap;
    ClientCallbackData*       clientCallbackData;
    ServerCallbackData*       serverCallbackData;
    size_t                    depthZero;
    size_t                    idZero;
    NiceMock<CubeIoProxyStub> cubeIoProxyStub;


private:
    Region*
    setupRegion()
    {
        Region* region = new Region( arbitraryText, arbitraryText,
                                     arbitraryText, arbitraryText,
                                     arbitraryNumber, arbitraryNumber,
                                     arbitraryText, arbitraryText,
                                     arbitraryText, idZero );
        mStubRegions.push_back( region );

        return region;
    }

    Cnode*
    setupCnode( Region* arbitraryRegion,
                Cnode*  noParentCnode )
    {
        Cnode* cnode = new cube::Cnode( arbitraryRegion, arbitraryText,
                                        arbitraryNumber, noParentCnode,
                                        idZero );
        mStubCnodes.push_back( cnode );

        return cnode;
    }

    Sysres*
    setupSysres( Sysres* noParentSysres )
    {
        Sysres* sysres = new SystemTreeNode( arbitraryText, arbitraryText,
                                             arbitraryText,
                                             static_cast< SystemTreeNode* >( 0 ),
                                             idZero, idZero );
        mStubSysres.push_back( sysres );

        return sysres;
    }

    Metric*
    setupMetric()
    {
        Metric* metric = Metric::create( arbitraryText, arbitraryText, "DOUBLE",
                                         "sec", arbitraryText, arbitraryText,
                                         arbitraryText, NULL, NULL,
                                         CUBE_METRIC_INCLUSIVE, idZero,
                                         arbitraryText, arbitraryText,
                                         arbitraryText, arbitraryText,
                                         arbitraryText,
                                         false, CUBE_METRIC_NORMAL );
        mStubMetrics.push_back( metric );

        return metric;
    }
};


// --- Tests ---------------------------------------------------------

TEST_F( RequestT, packsAndUnpacksSameRequestData )
{
    size_t zero( 0 );
    NetworkRequestPtr clientRequest =
        MetricSubtreeValuesRequest::create( cnodeSelection,
                                            sysresSelection,
                                            *rootMetric,
                                            depthZero,
                                            idIndexMap,
                                            &inclusiveValues,
                                            &exclusiveValues );
    ClientConnectionStub clientConnectionStub;
    clientRequest->sendRequest( clientConnectionStub,
                                clientCallbackData );

    ServerConnectionStub serverConnectionStub( clientConnectionStub );
    NetworkRequestPtr    serverRequest = MetricSubtreeValuesRequest::create();

    serverRequest->receiveRequest( serverConnectionStub,
                                   serverCallbackData );

    ASSERT_EQ( zero, serverConnectionStub.mBuffer.size() );
}
