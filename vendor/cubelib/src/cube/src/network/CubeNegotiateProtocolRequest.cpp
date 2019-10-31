/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016-2019                                                **
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
 *  @brief   Definition of the class cube::NegotiateProtocolRequest.
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeNegotiateProtocolRequest.h"

#include "CubeClientConnection.h"
#include "CubeCountedPtr.h"
#include "CubeError.h"
#include "CubeNetworkRequest.h"
#include "CubeServerConnection.h"

using namespace std;

namespace cube
{
NetworkRequestPtr
NegotiateProtocolRequest::create()
{
    return NetworkRequest::Ptr( new NegotiateProtocolRequest() );
}


NegotiateProtocolRequest::NegotiateProtocolRequest()
{
}


NegotiateProtocolRequest::~NegotiateProtocolRequest()
{
}


string
NegotiateProtocolRequest::getName() const
{
    return "NegotiateProtocol";
}


NetworkRequest::id_t
NegotiateProtocolRequest::getId() const
{
    return NEGOTIATE_PROTOCOL_REQUEST;
}


void
NegotiateProtocolRequest::sendRequestPayload( ClientConnection& connection,
                                              ClientCallbackData* ) const
{
    connection << connection.getMaxProtocolVersion();
}


void
NegotiateProtocolRequest::receiveResponsePayload( ClientConnection& connection,
                                                  ClientCallbackData* )
{
    uint32_t negotiatedProtocol = 0;

    connection >> negotiatedProtocol;
    if ( negotiatedProtocol == 0 )
    {
        throw UnrecoverableNetworkError( "Protocol negotiation failed." );
    }

    connection.setProtocolVersion( negotiatedProtocol );

    cerr << "Negotiated protocol: " << negotiatedProtocol << endl;
}


void
NegotiateProtocolRequest::sendResponsePayload( ServerConnection& connection,
                                               ServerCallbackData* ) const
{
    connection << connection.getMaxProtocolVersion();
}


void
NegotiateProtocolRequest::receiveRequestPayload( ServerConnection& connection,
                                                 ServerCallbackData* )
{
    uint32_t clientProtocolVersion = 0;
    uint32_t serverProtocolVersion = connection.getMaxProtocolVersion();

    connection >> clientProtocolVersion;

    uint32_t min_version = min( serverProtocolVersion, clientProtocolVersion );

    connection.setProtocolVersion( min_version );

    cerr << "Negotiated protocol version: " << min_version << endl;
}
}    /* namespace cube */
