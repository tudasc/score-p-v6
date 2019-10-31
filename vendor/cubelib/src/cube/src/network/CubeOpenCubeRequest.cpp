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
 *  @brief   Definition of the class cube::CubeOpenCubeRequest
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeOpenCubeRequest.h"

#include <cassert>
#include <string>

#include "CubeCartesian.h"
#include "CubeClientCallbackData.h"
#include "CubeClientConnection.h"
#include "CubeConnection.h"
#include "CubeError.h"
#include "CubeIoProxy.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeMachine.h"
#include "CubeNetworkProxy.h"
#include "CubeNode.h"
#include "CubeProcess.h"
#include "CubeProxy.h"
#include "CubeSerializablesFactory.h"
#include "CubeServerCallbackData.h"
#include "CubeServerConnection.h"
#include "CubeSystemTreeNode.h"
#include "CubeThread.h"
#include "cube_network_types.h"

using namespace std;

// --- Helper functions --------------------------------------------------

namespace cube
{
namespace detail
{
template< class T >
static void
sendVectorOfSerializables( cube::Connection&   connection,
                           const vector< T* >& serializeableObjects )
{
    uint64_t numElements = serializeableObjects.size();
    connection << numElements;

    for ( typename vector< T* >::const_iterator it =
              serializeableObjects.begin();
          it != serializeableObjects.end(); ++it )
    {
        ( *it )->serialize( connection );
    }
}


void
addElement( CubeNetworkProxy& cubeProxy,
            Metric&           metric )
{
    cubeProxy.addMetric( metric );
}


void
addElement( CubeNetworkProxy& cubeProxy,
            Region&           region )
{
    cubeProxy.addRegion( region );
}


void
addElement( CubeNetworkProxy& cubeProxy,
            Cnode&            cnode )
{
    cubeProxy.addCnode( cnode );
}


void
addElement( CubeNetworkProxy& cubeProxy,
            Sysres&           sysres )
{
    cubeProxy.addSystemResource( sysres );
}


void
addElement( CubeNetworkProxy& cubeProxy,
            Cartesian&        cartesian )
{
    cubeProxy.addCartesian( cartesian );
}


template< class TargetType >
void
receiveVectorOfSerializables( Connection&       connection,
                              CubeNetworkProxy& cubeProxy )
{
    uint64_t numElements = connection.get< uint64_t >();
    for ( uint64_t i = 0; i < numElements; ++i )
    {
        Serializable* object = MySerializablesFactory::getInstance().create(
            connection,
            cubeProxy );
        assert( object );
        TargetType* typed_object = dynamic_cast< TargetType* >( object );
        assert( typed_object );
        addElement( cubeProxy, *typed_object );
    }
}


void
sendMetrics( ServerConnection& connection,
             CubeIoProxy&      cubeProxy )
{
    sendVectorOfSerializables( connection, cubeProxy.getMetrics() );
}


void
receiveMetrics( ClientConnection& connection,
                CubeNetworkProxy& cubeProxy )
{
    receiveVectorOfSerializables< Metric >( connection, cubeProxy );
}


void
sendRegions( ServerConnection& connection,
             CubeIoProxy&      cubeProxy )
{
    sendVectorOfSerializables( connection, cubeProxy.getRegions() );
}


void
receiveRegions( ClientConnection& connection,
                CubeNetworkProxy& cubeProxy )
{
    receiveVectorOfSerializables< Region >( connection, cubeProxy );
}


void
sendCnodes( ServerConnection& connection,
            CubeIoProxy&      cubeProxy )
{
    sendVectorOfSerializables( connection, cubeProxy.getCnodes() );
}


void
receiveCnodes( ClientConnection& connection,
               CubeNetworkProxy& cubeProxy )
{
    receiveVectorOfSerializables< Cnode >( connection, cubeProxy );
}


void
sendSystemResources( ServerConnection& connection,
                     CubeIoProxy&      cubeProxy )
{
    sendVectorOfSerializables( connection, cubeProxy.getSystemResources() );
}


void
receiveSystemResources( ClientConnection& connection,
                        CubeNetworkProxy& cubeProxy )
{
    receiveVectorOfSerializables< Sysres >( connection, cubeProxy );
}


void
sendCartesians( ServerConnection& connection,
                CubeIoProxy&      cubeProxy )
{
    sendVectorOfSerializables( connection, cubeProxy.getCartesians() );
}


void
receiveCartesians( ClientConnection& connection,
                   CubeNetworkProxy& cubeProxy )
{
    receiveVectorOfSerializables< Cartesian >( connection, cubeProxy );
}


void
sendAttributes( ServerConnection& connection,
                CubeIoProxy&      cubeProxy )
{
    uint64_t numAttributes = cubeProxy.getAttributes().size();
    connection << numAttributes;
    for ( map< string, string >::const_iterator it =
              cubeProxy.getAttributes().begin();
          it != cubeProxy.getAttributes().end(); ++it )
    {
        connection << it->first;
        connection << it->second;
    }
}


void
receiveAttributes( ClientConnection& connection,
                   CubeNetworkProxy& cubeProxy )
{
    uint64_t numAttributes = connection.get< uint64_t >();
    for ( uint64_t i = 0; i < numAttributes; ++i )
    {
        string key;
        connection >> key;
        string value;
        connection >> value;
        cubeProxy.defineAttribute( key, value );
    }
}


void
sendMirrors( ServerConnection& connection,
             CubeIoProxy&      cubeProxy )
{
    uint64_t numMirrors = cubeProxy.getMirrors().size();
    connection << numMirrors;
    for ( vector< string >::const_iterator it =
              cubeProxy.getMirrors().begin();
          it != cubeProxy.getMirrors().end(); ++it )
    {
        connection << *it;
    }
}


void
receiveMirrors( ClientConnection& connection,
                CubeNetworkProxy& cubeProxy )
{
    uint64_t numMirrors = connection.get< uint64_t >();
    for ( uint64_t i = 0; i < numMirrors; ++i )
    {
        string mirror;
        connection >> mirror;
        cubeProxy.defineMirror( mirror );
    }
}
} // namespace detail
} // namespace cube

using namespace cube;
using namespace cube::detail;

/// --- Construction & destruction ---------------------------------------

NetworkRequestPtr
OpenCubeRequest::create( const string& fileName )
{
    return NetworkRequest::Ptr( new OpenCubeRequest( fileName ) );
}


NetworkRequestPtr
OpenCubeRequest::create()
{
    return NetworkRequest::Ptr( new OpenCubeRequest() );
}


OpenCubeRequest::OpenCubeRequest()
{
}


OpenCubeRequest::OpenCubeRequest( const string& fileName )
    : mFileName( fileName )
{
}


OpenCubeRequest::~OpenCubeRequest()
{
}


/// --- Request identification -------------------------------------------

string
OpenCubeRequest::getName() const
{
    return "OpenCube";
}


NetworkRequest::id_t
OpenCubeRequest::getId() const
{
    return OPEN_CUBE_REQUEST;
}


/// --- Connection interface ---------------------------------------------

void
OpenCubeRequest::sendRequestPayload( ClientConnection& connection,
                                     ClientCallbackData* ) const
{
    connection << mFileName;
}


void
OpenCubeRequest::receiveRequestPayload( ServerConnection& connection,
                                        ServerCallbackData* )
{
    connection >> mFileName;
}


void
OpenCubeRequest::processRequest( ServerCallbackData* data )
{
    assert( data );
    data->setCube( new CubeIoProxy() );
    assert( data->getCube() );

    try
    {
        data->getCube()->openReport( mFileName );
    }
    catch ( const std::exception& e )
    {
        throw RecoverableNetworkError( e.what() );
    }
    cerr << "Opened Cube report: "
         << data->getCube()->getAttribute( "cubename" ) << endl;
}

void
OpenCubeRequest::sendResponsePayload( ServerConnection&   connection,
                                      ServerCallbackData* data ) const
{
    assert( data );
    assert( data->getCube() );
    CubeIoProxy& cubeProxy = *data->getCube();

    /// The response payload includes definition data for the following
    /// entities:
    /// - Metrics
    sendMetrics( connection, cubeProxy );

    /// - Regions
    sendRegions( connection, cubeProxy );

    /// - Cnodes
    sendCnodes( connection, cubeProxy );

    /// - SystemResources
    sendSystemResources( connection, cubeProxy );

    /// - Cartesian topologies
    sendCartesians( connection, cubeProxy );

    /// - Attributes
    sendAttributes( connection, cubeProxy );

    /// - Mirrors
    sendMirrors( connection, cubeProxy );
}


void
OpenCubeRequest::receiveResponsePayload( ClientConnection&   connection,
                                         ClientCallbackData* data )
{
    assert( data );
    assert( data->getCube() );
    CubeNetworkProxy& cubeProxy = *data->getCube();

    /// The response payload includes definition data for the following
    /// entities:
    /// - Metrics
    receiveMetrics( connection, cubeProxy );

    /// - Regions
    receiveRegions( connection, cubeProxy );

    /// - Cnodes
    receiveCnodes( connection, cubeProxy );

    /// - System resources
    receiveSystemResources( connection, cubeProxy );

    /// - Cartesian topologies
    receiveCartesians( connection, cubeProxy );

    /// - Attributes
    receiveAttributes( connection, cubeProxy );

    /// - Mirrors
    receiveMirrors( connection, cubeProxy );
}
