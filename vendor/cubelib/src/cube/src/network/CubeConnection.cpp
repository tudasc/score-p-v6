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
 *  @brief   Definition of the class cube::Connection.
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeConnection.h"

#include <string>

#include "CubeProtocol.h"
#include "CubeSocket.h"
#include "cubelib-version.h"

using namespace std;

namespace cube
{
void
Connection::disconnect()
{
    if (!mSocket.get())
    {
        throw InvalidSocket("Cannot disconnect invalid socket.");
    }

    mSocket->disconnect();
}


Connection::Connection(SocketPtr socket)
    : mSocket(socket),
      mProtocol(new Protocol()),
      mEnableByteSwap(false)
{
}


void
Connection::send(const void* data,
                 size_t      num_bytes)
{
    if (!mSocket.get())
    {
        throw InvalidSocket("Cannot write to invalid socket.");
    }

    mSocket->send(data, num_bytes);
}


size_t
Connection::receive(void*  data,
                    size_t num_bytes)
{
    if (!mSocket.get())
    {
        throw InvalidSocket("Cannot read from invalid socket.");
    }

    return mSocket->receive(data, num_bytes);
}


Connection::~Connection()
{
    if (mProtocol)
    {
        delete mProtocol;
    }
}


bool
Connection::isEstablished()
{
    if (mSocket.get())
    {
        return mSocket->isConnected();
    }

    return false;
}


string
Connection::getInfoString()
{
    if (mSocket.get())
    {
        return CUBELIB_FULL_NAME " (" CUBELIB_REVISION ") ["
               + mSocket->getInfoString() + "]";
    }
    else
    {
        return CUBELIB_FULL_NAME " (" CUBELIB_REVISION
               ") [No Socket initialized]";
    }
}


NetworkRequestPtr
Connection::createRequest(request_id_t  requestId,
                          request_seq_t sequenceNo)
{
    return mProtocol->createRequest(requestId, sequenceNo);
}


void
Connection::setProtocolVersion(protocol_version_t version)
{
    mProtocol->setVersion(version);
}


protocol_version_t
Connection::getProtocolVersion() const
{
    return mProtocol->getVersion();
}


protocol_version_t
Connection::getMaxProtocolVersion() const
{
    return mProtocol->getMaxVersion();
}
}    /* namespace cube */
