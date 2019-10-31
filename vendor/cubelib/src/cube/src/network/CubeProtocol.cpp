/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016-2017                                                **
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
 *  @brief   Definition of the class Protocol
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeProtocol.h"

#include <cassert>
#include <iostream>
#include <limits>
#include <map>

#include "CubeCallpathSubtreeValuesRequest.h"
#include "CubeCallpathTreeValuesRequest.h"
#include "CubeClientServerVersionRequest.h"
#include "CubeCloseCubeRequest.h"
#include "CubeDefineMetricRequest.h"
#include "CubeDisconnectRequest.h"
#include "CubeError.h"
#include "CubeFlatTreeValuesRequest.h"
#include "CubeMetricSubtreeValuesRequest.h"
#include "CubeMetricTreeValuesRequest.h"
#include "CubeNegotiateProtocolRequest.h"
#include "CubeOpenCubeRequest.h"
#include "CubeSaveCubeRequest.h"
#include "CubeSystemTreeValuesRequest.h"

using namespace std;

namespace cube
{
Protocol::Protocol()
{
    mFactory.resize( NUM_NETWORK_REQUESTS );
    setVersion( 0 );
}


Protocol::~Protocol()
{
}


void
Protocol::registerRequest( NetworkRequest::factory_method_t method )
{
    NetworkRequest::Ptr p = ( *method )();

    if ( mFactory.at( p->getId() ) )
    {
        // entry is not NULL
        cerr
            << "WARNING: Ignoring duplicate registration of network request "
            << p->getName() << endl;
    }
    else
    {
        assert( mFactory.size() == NUM_NETWORK_REQUESTS );
        mFactory[ p->getId() ] = method;
    }
}


void
Protocol::reset()
{
    mFactory.clear();
    mFactory.resize( NUM_NETWORK_REQUESTS );
}


void
Protocol::setVersion( version_t version )
{
    if ( ( version == 0 ) || ( version != mVersion ) )
    {
        // Clear existing list of request factory methods
        reset();

        /**
         * List of protocol versions supporting specific request types
         * ===========================================================
         */
        switch ( version )
        {
            // Initial protocol before client-server negotiation
            case 0:
                /**
                 * Protocol 0 (Initial Protocol):
                 * ------------------------------
                 */

                registerRequest( NegotiateProtocolRequest::create );
                registerRequest( ClientServerVersionRequest::create );
                registerRequest( DisconnectRequest::create );
                break;

            case 1:
                /**
                 * Protocol 1:
                 * -----------
                 */

                registerRequest( NegotiateProtocolRequest::create );
                registerRequest( ClientServerVersionRequest::create );
                registerRequest( DisconnectRequest::create );
                registerRequest( OpenCubeRequest::create );
                registerRequest( CloseCubeRequest::create );
                registerRequest( SaveCubeRequest::create );
                registerRequest( DefineMetricRequest::create );
                registerRequest( MetricTreeValuesRequest::create );
                registerRequest( MetricSubtreeValuesRequest::create );
                registerRequest( CallpathTreeValuesRequest::create );
                registerRequest( FlatTreeValuesRequest::create );
                registerRequest( SystemTreeValuesRequest::create );
                registerRequest( CallpathSubtreeValuesRequest::create );
                break;

            /// @note Update getMaxVersion() if a new protocol version is added.
            default:
                throw UnrecoverableNetworkError( "Unsupported protocol version" );
        }

        // reset request counter
        NetworkRequest::resetRequestCounter();

        // save
        mVersion = version;
    }
}


Protocol::version_t
Protocol::getVersion() const
{
    return mVersion;
}


NetworkRequest::Ptr
Protocol::createRequest( NetworkRequest::id_t       reqNo,
                         NetworkRequest::sequence_t seqNo ) const
{
    if ( ( reqNo >= mFactory.size() ) || ( mFactory.at( reqNo ) == NULL ) )
    {
        throw UnrecoverableNetworkError( "Use of unregistered request type" );
    }

    NetworkRequest::Ptr request = ( *mFactory.at( reqNo ) )();
    if ( seqNo != 0 )
    {
        request->setSequenceNumber( seqNo );
    }

    return request;
}


Protocol::version_t
Protocol::getMaxVersion() const
{
    // return currently highest protocol version
    return 1;
}


const Protocol::version_t Protocol::UNINITIALIZED =
    numeric_limits< Protocol::version_t >::max();
}    /* namespace cube */
