/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016                                                     **
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
 *  @brief   Definition of the class ClientConnection.
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeClientConnection.h"

#include <iostream>
#include <string.h>

#include "CubeClientServerVersionRequest.h"
#include "CubeDisconnectRequest.h"
#include "CubeError.h"
#include "CubeNegotiateProtocolRequest.h"
#include "CubeNetworkRequest.h"
#include "CubeSocket.h"
#include "CubeUrl.h"

using namespace std;

namespace cube
{
ClientConnection::Ptr
ClientConnection::create(SocketPtr     socket,
                         const string& url_string)
{
    return ClientConnection::Ptr(new ClientConnection(socket, url_string));
}


ClientConnection::ClientConnection(SocketPtr socket)
    : Connection(socket)
{
}


ClientConnection::ClientConnection(SocketPtr     socket,
                                   const string& url_string)
    : Connection(socket)
{
    // decode URL
    Url url(url_string);

    // connect socket
    mSocket->connect(url.getHost(), url.getPort());

    // send 64-bit value of one, to check for endianness on server
    uint64_t one = 1;
    *this << one;

    // Negotiate Protocol with server
    NetworkRequestPtr request = createRequest(NEGOTIATE_PROTOCOL_REQUEST);
    request->sendRequest(*this, 0);
    request->receiveResponse(*this, 0);

    NetworkRequestPtr reqVersion = createRequest(GET_VERSION_STRING_REQUEST);
    reqVersion->sendRequest(*this, 0);
    reqVersion->receiveResponse(*this, 0);
}


ClientConnection::~ClientConnection()
{
    // send disconnect request
    if (this->isEstablished())
    {
        NetworkRequestPtr request = createRequest(DISCONNECT_REQUEST);
        request->sendRequest(*this, 0);
        try
        {
            request->receiveResponse(*this, 0);
        }
        catch (NetworkError& theError)
        {
            cerr << theError << endl;
        }
        // disconnect socket at end of lifetime
        mSocket->disconnect();
    }
}
}    /* namespace cube */
