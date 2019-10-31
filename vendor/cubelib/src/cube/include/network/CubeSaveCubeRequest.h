/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016                                                     **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2015                                                     **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  Copyright (c) 2015                                                     **
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
 *  @brief   Declaration of the class cube::SaveCubeRequest
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_SAVECUBEREQUEST_H
#define CUBE_SAVECUBEREQUEST_H

#include "CubeNetworkRequest.h"

namespace cube
{
/*-------------------------------------------------------------------------*/
/**
 *  @class   cube::SaveCubeRequest
 *  @ingroup CUBE_lib.network
 *  @brief   Creates a server-side copy of the current Cube report
 **/
/*-------------------------------------------------------------------------*/

class SaveCubeRequest
    : public NetworkRequest
{
    public:
        /// @brief Virtual destructor.
        virtual
        ~SaveCubeRequest();

        /// @brief Client-side factory method.
        ///
        /// @param[in] filename
        ///     Full path and name of the new remote file.
        /// @return
        ///     Pointer to created request.
        ///
        static NetworkRequestPtr
        create(const std::string& filename);

        /// @brief Server-side factory method.
        ///
        /// @return
        ///     Pointer to created request.
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
        virtual NetworkRequest::id_t
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
        /// @brief Private constructor.
        ///
        /// @param[in] filename
        ///     Full path and name of the remote file.
        ///
        SaveCubeRequest(const std::string& filename);

        /// @brief Default constructor.
        ///
        SaveCubeRequest();

        /// Remote filename
        std::string mFilename;
};
}    /* namespace cube */

#endif    /* ! CUBE_SAVECUBEREQUEST_H */
