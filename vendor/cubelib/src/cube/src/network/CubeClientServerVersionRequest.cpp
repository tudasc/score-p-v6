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
 *  @brief   Definition of the class cube::ClientServerVersionRequest
 **/
/*-------------------------------------------------------------------------*/


#include "config.h"

#include "CubeClientServerVersionRequest.h"

#include <cassert>
#include <iostream>
#include <string>

#include "CubeClientConnection.h"
#include "CubeCountedPtr.h"
#include "CubeNegotiateProtocolRequest.h"
#include "CubeNetworkRequest.h"
#include "CubeServerConnection.h"

using namespace std;

namespace cube
{
NetworkRequestPtr
ClientServerVersionRequest::create()
{
    return NetworkRequest::Ptr( new ClientServerVersionRequest() );
}


string
ClientServerVersionRequest::getName() const
{
    return "ClientServerVersion";
}


NetworkRequest::id_t
ClientServerVersionRequest::getId() const
{
    return GET_VERSION_STRING_REQUEST;
}


void
ClientServerVersionRequest::sendRequestPayload( ClientConnection& connection,
                                                ClientCallbackData* ) const
{
    connection << connection.getInfoString();
}


void
ClientServerVersionRequest::receiveRequestPayload(
    ServerConnection& connection,
    ServerCallbackData* )
{
    string clientVersion;
    connection >> clientVersion;

    cerr << "Client version: " << clientVersion << endl;
}


void
ClientServerVersionRequest::sendResponsePayload( ServerConnection& connection,
                                                 ServerCallbackData* ) const
{
    connection << connection.getInfoString();
}


void
ClientServerVersionRequest::receiveResponsePayload(
    ClientConnection& connection,
    ClientCallbackData* )
{
    string serverVersion;
    connection >> serverVersion;

    cerr << "Server version: " << serverVersion << endl;
}


ClientServerVersionRequest::ClientServerVersionRequest()
{
}


ClientServerVersionRequest::~ClientServerVersionRequest()
{
}
}    /* namespace cube */
