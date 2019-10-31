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
 *  @brief   Declaration of the class Connection
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_CONNECTION_H
#define CUBE_CONNECTION_H

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "CubeNetworkRequest.h"
#include "CubeOperator.h"
#include "CubeSerializable.h"
#include "CubeValues.h"
#include "cube_network_types.h"

namespace cube
{
class Socket;
class Protocol;

/*-------------------------------------------------------------------------*/
/**
 *  @class   Connection
 *  @ingroup CUBE_lib.network
 *  @brief   Abstract base class to derived client and server connection classes.
 *
 *  This base class to ClientConnection and ServerConnection implements
 *  common functionality, such as sending and receiving data.
 **/
/*-------------------------------------------------------------------------*/

class Connection
{
    public:
        /// @brief Type name for the connection pointer.
        ///
        typedef ConnectionPtr Ptr;

        /// @brief Virtual destructor.
        ///
        virtual
        ~Connection();

        /// @brief Stream operator for sending data.
        ///
        /// @param value
        ///     Value to be sent
        ///
        template< typename T >
        void
        operator<<(const T& value);

        /// @brief Stream operator for receiving data.
        ///
        /// @param value
        ///     Value to be received
        ///
        template< typename T >
        void
        operator>>(T& value);


        /// @brief Convenience function to get a single datatype variable from
        ///     the stream.
        ///
        /// @return
        ///     Variable of a given type
        ///
        template< typename T >
        T
        get();

        /// @brief Indicator whether a connection between client and server is
        ///     established.
        ///
        /// @return
        ///     @a true if connection is established, @a false otherwise.
        ///
        bool
        isEstablished();

        /// @brief Disconnect established client/server connection.
        ///
        void
        disconnect();

        /// @brief Return a string containing information about this connection
        ///     object.
        ///
        /// @return
        ///     Version string
        ///
        std::string
        getInfoString();

        /// @brief Set protocol version (incl. registration of appropriate
        ///     request callbacks).
        ///
        /// @param version
        ///     Protocol version number
        ///
        void
        setProtocolVersion(protocol_version_t version);

        /// @brief Get protocol version currently set up.
        ///
        /// @return
        ///     Protocol version set up in current session.
        ///
        protocol_version_t
        getProtocolVersion() const;

        /// @brief Get the maximum protocol version available with this
        ///     connection.
        ///
        /// @return
        ///     Maximum protocol version supported by this implementation.
        ///
        protocol_version_t
        getMaxProtocolVersion() const;

        /// @brief Create a request using its registration id.
        ///
        /// @param requestId
        ///     Id of the registered request type.
        /// @return
        ///     Pointer to the request.
        ///
        NetworkRequestPtr
        createRequest(request_id_t  requestId,
                      request_seq_t sequenceNo = 0);


    protected:
        /// @brief Construct connection object using given Socket.
        ///
        /// @param socket
        ///     Socket object to use
        ///
        Connection(SocketPtr socket);

        /// @brief Send a contiguous buffer via established connection.
        ///
        /// @param data
        ///     Contiguous data buffer.
        /// @param num_bytes
        ///     Number of bytes to be sent out of data buffer.
        ///
        virtual void
        send(const void* buffer,
             size_t      num_bytes);

        /// @brief Receive a contiguous buffer over established connection.
        ///
        /// @param data
        ///     Contiguous data buffer.
        /// @param num_bytes
        ///     Number of bytes to be received into data buffer
        /// @return
        ///     Number of bytes received (may be less that @a num_bytes)
        ///
        virtual size_t
        receive(void*  buffer,
                size_t num_bytes);

        /// @brief Switch little-/big-endian byte swap on/off.
        ///
        void
        enableByteSwap(bool enable)
        {
            mEnableByteSwap = enable;
        }

        /// @brief Socket communication object
        ///
        SocketPtr mSocket;

        /// @brief Protocol used for this connection
        ///
        Protocol* mProtocol;


    private:
        /// @brief Dynamic byte swap policy
        ///
        bool mEnableByteSwap;
};


template< typename T >
inline void
Connection::operator<<(const T& value)
{
    if (mEnableByteSwap)
    {
        T swapped = value;
        ByteSwapOperator< T >::apply(swapped);
        this->send(&swapped, sizeof(value));
    }
    else
    {
        this->send(&value, sizeof(value));
    }
}


template< typename T >
inline void
Connection::operator>>(T& value)
{
    this->receive(&value, sizeof(value));
    if (mEnableByteSwap)
    {
        ByteSwapOperator< T >::apply(value);
    }
}


template< >
inline void
Connection::operator<<(const std::string& value)
{
    uint64_t length = value.size() + 1;

    *this << length;
    this->send(value.c_str(), (length) * sizeof(char));
}


template< >
inline void
Connection::operator>>(std::string& str)
{
    // receive length
    uint64_t length = this->get< uint64_t >();
    assert(length > 0);

    // receive string buffer (incl. null-termination!)
    char* buffer = 0;
    buffer = (char*)malloc((length) * sizeof(char));
    this->receive(buffer, (length) * sizeof(char));
    str = buffer;
    free(buffer);
}


template< >
inline void
Connection::operator<<(const cube::Value& value)
{
    // Values can be composed of multiple different basic values
    // Therefore they have to handle themselves.
    value.toStream(*this);
}


template< >
inline void
Connection::operator>>(cube::Value& value)
{
    value.fromStream(*this);
}


template< typename T >
inline T
Connection::get()
{
    T var;
    *this >> var;

    return var;
}
}    /* namespace cube */

#endif    /* !CUBE_CONNECTION_H */
