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
 *  @brief   Definition of the class cube:DisconnectRequest.
 **/
/*-------------------------------------------------------------------------*/


#include "config.h"

#include "CubeDisconnectRequest.h"

#include <string>

#include "CubeClientConnection.h"
#include "CubeCountedPtr.h"
#include "CubeNetworkRequest.h"
#include "CubeServerConnection.h"

using namespace std;

namespace cube
{
NetworkRequestPtr
DisconnectRequest::create()
{
    return NetworkRequest::Ptr( new DisconnectRequest() );
}


string
DisconnectRequest::getName() const
{
    return "Disconnect";
}


NetworkRequest::id_t
DisconnectRequest::getId() const
{
    return DISCONNECT_REQUEST;
}


void
DisconnectRequest::receiveRequestPayload( ServerConnection& connection,
                                          ServerCallbackData* )
{
    mConnection = &connection;
}


void
DisconnectRequest::receiveResponsePayload( ClientConnection& connection,
                                           ClientCallbackData* )
{
    mConnection = &connection;
}


DisconnectRequest::DisconnectRequest()
    : mConnection( NULL )
{
}


DisconnectRequest::~DisconnectRequest()
{
    if ( mConnection )
    {
        mConnection->disconnect();
    }
}
}    /* namespace cube */
