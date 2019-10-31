/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2017-2019                                                **
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
 *  @brief   Implementation of the class NetworkRequest.
 *
 *  Implementation of the abstract base class NetworkRequest.
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeNetworkRequest.h"

#include <iostream>
#include <limits>

#include "CubeClientConnection.h"
#include "CubeError.h"
#include "CubeServerConnection.h"

using namespace std;
using namespace cube;

namespace
{
/// @brief Marker for the start of the request header.
///
/// @note uint32_t representation of ASCII string 'CUBE'
///
static const NetworkRequest::marker_t REQUEST_HEADER_START = 0x43554245;

/// @brief Marker for the end of the request header and the beginning of
///     the payload.
///
/// @note uint32_t representation of ASCII string '-CC-'
///
static const NetworkRequest::marker_t REQUEST_HEADER_END = 0x2d43432d;

/// @brief Marker for the end of the request payload
///
/// @note uint32_t representation of ASCII string 'EBUC'
///
static const NetworkRequest::marker_t REQUEST_PAYLOAD_END = 0x45423543;
}

NetworkRequest::sequence_t
NetworkRequest::getSequenceNumber() const
{
    return mSequenceNo;
}


void
NetworkRequest::setSequenceNumber( sequence_t seqNo )
{
    mSequenceNo = seqNo;
}


void
NetworkRequest::resetRequestCounter()
{
    mNumRequests = 0;
}


bool
NetworkRequest::isRegistered()
{
    return mId != NetworkRequest::UNREGISTERED;
}


NetworkRequest::NetworkRequest()
    : mId( UNREGISTERED ),
    mSequenceNo( ++mNumRequests )
{
}


NetworkRequest::~NetworkRequest()
{
}


void
NetworkRequest::sendRequest( ClientConnection&   connection,
                             ClientCallbackData* data ) const
{
    /// 1. Send 'StartOfHeader' marker
    connection << ::REQUEST_HEADER_START;

    /// 2. Send request ID
    connection << this->getId();

    /// 3. Send sequence Number
    connection << this->getSequenceNumber();

    /// 4. Send 'EndOfHeader' marker
    connection << ::REQUEST_HEADER_END;

    /// 5. Send the request payload
    this->sendRequestPayload( connection, data );

    /// 6. Send 'EndOfPayload' marker
    connection << ::REQUEST_PAYLOAD_END;
}


NetworkRequest::Ptr
NetworkRequest::createFromStream( ServerConnection& connection )
{
    marker_t marker;

    /// 1. Receive StartOfHeader marker
    connection >> marker;
    #if defined( CUBE_NETWORK_DEBUG )
    cerr << "HeaderStart: " << marker << endl;
    #endif
    if ( marker != ::REQUEST_HEADER_START )
    {
        throw UnrecoverableNetworkError(
                  "Malformed request header: Incorrect start marker." );
    }

    /// 2. Receive request ID
    NetworkRequest::id_t reqId;
    connection >> reqId;

    /// 3. Receive sequence number
    NetworkRequest::sequence_t seqNo;
    connection >> seqNo;

    /// 4. Receive EndOfHeader marker
    connection >> marker;
    #if defined( CUBE_NETWORK_DEBUG )
    cerr << "HeaderEnd: " << marker << endl;
    #endif
    if ( marker != ::REQUEST_HEADER_END )
    {
        throw UnrecoverableNetworkError(
                  "Malformed request header: Incorrect end marker." );
    }

    // Create request object and return it.
    return connection.createRequest( reqId, seqNo );
}


void
NetworkRequest::receiveRequest( ServerConnection&   connection,
                                ServerCallbackData* data )
{
    /// Full header is already received by server routine

    this->receiveRequestPayload( connection, data );

    /// Receive 'EndOfPayload' marker
    marker_t marker;
    connection >> marker;
    #if defined( CUBE_NETWORK_DEBUG )
    cerr << "PayloadEnd: " << marker << endl;
    #endif
    if ( marker != ::REQUEST_PAYLOAD_END )
    {
        throw UnrecoverableNetworkError(
                  "Malformed request payload: Incorrect end marker." );
    }
}


void
NetworkRequest::processRequest( ServerCallbackData* )
{
}


void
NetworkRequest::sendResponse( ServerConnection&   connection,
                              ServerCallbackData* data ) const
{
    /** @internal
     * ID is not needed in the response, as either in synchronous mode
     * the client knows the type is expects, and in asynchronous mode
     * the sequence number should be sufficient to retrieve the original
     * request object.
     */

    /// 1. Send StartOfHeader
    connection << ::REQUEST_HEADER_START;

    /// 2. Send ACK = REQUEST_OK
    connection << uint32_t( REQUEST_OK );

    /// 3. Send sequence number
    connection << this->getSequenceNumber();

    /// 4. Send EndOfHeader
    connection << ::REQUEST_HEADER_END;

    /// 5. Send response payload
    this->sendResponsePayload( connection, data );

    /// @todo Maybe think of a more general way to handle disconnect?
    if ( connection.isEstablished() )
    {
        /// 6. Send EndOfPayload
        connection << ::REQUEST_PAYLOAD_END;
    }
}


void
NetworkRequest::sendErrorResponse( ServerConnection&          connection,
                                   NetworkRequestResponseCode responseCode,
                                   const string&              errorMessage ) const
{
    /** @internal
     * ID is not needed in the response, as either in synchronous mode
     * the client knows the type is expects, and in asynchronous mode
     * the sequence number should be sufficient to retrieve the original
     * request object.
     */

    /// 1. Send StartOfHeader
    connection << ::REQUEST_HEADER_START;

    /// 2. Send ACK = REQUEST_ERROR_RECOVERABLE
    connection << uint32_t( responseCode );

    /// 3. Send sequence number
    connection << this->getSequenceNumber();

    /// 4. Send EndOfHeader
    connection << ::REQUEST_HEADER_END;

    /// 5. Send response payload
    connection << errorMessage;

    /// @todo Maybe think of a more general way to handle disconnect?
    if ( connection.isEstablished() )
    {
        /// 6. Send EndOfPayload
        connection << ::REQUEST_PAYLOAD_END;
    }
}


void
NetworkRequest::receiveResponse( ClientConnection&   connection,
                                 ClientCallbackData* data )
{
    marker_t marker;

    /// 1. Receive StartOfHeader marker
    connection >> marker;
    if ( marker != ::REQUEST_HEADER_START )
    {
        throw UnrecoverableNetworkError(
                  "Malformed response header. Incorrect start marker." );
    }

    /// 2. Receive request acknowledgment
    uint32_t ACK;
    connection >> ACK;

    /// 3. Receive sequence number
    NetworkRequest::sequence_t seqNo;
    connection >> seqNo;

    if ( seqNo != this->getSequenceNumber() )
    {
        cerr << "WARNING: Out-of-order response! Received sequence number #"
             << seqNo << ", but expected #" << this->getSequenceNumber()
             << endl;
    }

    /// 4. Receive EndOfHeader marker
    connection >> marker;
    if ( marker != ::REQUEST_HEADER_END )
    {
        throw UnrecoverableNetworkError(
                  "Malformed response header. Incorrect end marker." );
    }

    /// 5. Handling of recoverable errors.
    if ( ACK == REQUEST_OK )
    {
        this->receiveResponsePayload( connection, data );
    }
    else if ( ACK == REQUEST_ERROR_RECOVERABLE )
    {
        string errorMessage;
        connection >> errorMessage;
        throw RecoverableNetworkError( errorMessage );
    }
    else if ( ACK == REQUEST_ERROR_UNRECOVERABLE )
    {
        string errorMessage;
        connection >> errorMessage;
        throw UnrecoverableNetworkError( errorMessage );
    }

    /// @todo Maybe think of a more general way to handle disconnect?
    if ( connection.isEstablished() )
    {
        /// 6. Receive EndOfPayload marker
        connection >> marker;
        if ( marker != ::REQUEST_PAYLOAD_END )
        {
            throw UnrecoverableNetworkError(
                      "Malformed response payload. Incorrect end marker." );
        }
    }
}


void
NetworkRequest::sendRequestPayload( ClientConnection& /*connection*/,
                                    ClientCallbackData*    /*data*/ ) const
{
}


void
NetworkRequest::receiveRequestPayload( ServerConnection& /*connection*/,
                                       ServerCallbackData*    /*data*/ )
{
}


void
NetworkRequest::sendResponsePayload( ServerConnection& /*connection*/,
                                     ServerCallbackData*    /*data*/ ) const
{
}


void
NetworkRequest::receiveResponsePayload( ClientConnection& /*connection*/,
                                        ClientCallbackData*    /*data*/ )
{
}


NetworkRequest::sequence_t NetworkRequest::mNumRequests = 0;

const NetworkRequest::id_t NetworkRequest::UNREGISTERED =
    numeric_limits< NetworkRequest::id_t >::max();
