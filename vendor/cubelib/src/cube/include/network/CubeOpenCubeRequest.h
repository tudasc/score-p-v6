/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016                                                     **
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
 *  @brief   Declaration of the class OpenCubeRequest
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_OPENCUBEREQUEST_H
#define CUBE_OPENCUBEREQUEST_H

#include <string>

#include "CubeNetworkRequest.h"

namespace cube
{
/*-------------------------------------------------------------------------*/
/**
 *  @class   cube::OpenCubeRequest
 *  @ingroup CUBE_lib.network
 *  @brief   Network request to open a remote Cube file.
 **/
/*-------------------------------------------------------------------------*/

class OpenCubeRequest
    : public NetworkRequest
{
    public:
        /// Virtual Destructor
        virtual
        ~OpenCubeRequest();

        /// @brief Client-side factory method.
        ///
        /// @param fileName
        ///     Fully-qualified name of the Cube file
        /// @return
        ///     Pointer to request
        ///
        static NetworkRequestPtr
        create(const std::string& fileName);

        /// @brief Server-side factory method.
        ///
        /// @return
        ///     Pointer to request
        ///
        static NetworkRequestPtr
        create();

        /// @brief Get the name of this request type.
        ///
        /// @return
        ///     String representation of request name.
        ///
        virtual std::string
        getName() const;

        /// @brief Get the unique network request ID.
        ///
        /// @return
        ///     Unique request Id defined in %cube::NetworkRequestId
        ///
        virtual id_t
        getId() const;

        /// @brief Server-side callback to execute after reception.
        ///
        /// @param data
        ///     Callback data structure.
        ///
        virtual void
        processRequest(ServerCallbackData* data);

    protected:
        /// @brief Stream information from client to server.
        ///
        /// @param[in,out] connection
        ///     Reference to connection on client.
        /// @param[in,out] data
        ///     Pointer to callback data.
        ///
        virtual void
        sendRequestPayload(ClientConnection&   connection,
                           ClientCallbackData* data) const;

        /// @brief Receive information from client on server.
        ///
        /// @param[in,out] connection
        ///     Reference to connection on client.
        /// @param[in,out] data
        ///     Pointer to callback data.
        ///
        virtual void
        receiveRequestPayload(ServerConnection&   connection,
                              ServerCallbackData* data);

        /// @brief Stream information from server to client.
        ///
        /// @param[in,out] connection
        ///     Reference to connection on client.
        /// @param[in,out] data
        ///     Pointer to callback data.
        ///
        virtual void
        sendResponsePayload(ServerConnection&   connection,
                            ServerCallbackData* data) const;

        /// @brief Receive information from server on client.
        ///
        /// @param[in,out] connection
        ///     Reference to connection on client.
        /// @param[in,out] data Pointer to callback data.
        ///
        virtual void
        receiveResponsePayload(ClientConnection&   connection,
                               ClientCallbackData* data);


    private:
        /// @brief Server-side constructor hidden from public access.
        ///
        OpenCubeRequest();

        /// @brief Client-side constructor hidden from public access.
        ///
        OpenCubeRequest(const std::string& fileName);

        /// @brief Filename to be opened on the server side.
        std::string mFileName;
};
}    /* namespace cube */

#endif    /* !CUBE_OPENCUBEREQUEST_H */
