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
 *  @brief   Definition of the class cube::DefineMetricRequest
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_DEFINEMETRICREQUEST_H
#define CUBE_DEFINEMETRICREQUEST_H

#include "CubeNetworkRequest.h"

namespace cube
{
class ClientCallbackData;
class ClientConnection;
class Metric;
class ServerCallbackData;
class ServerConncetion;

/*-------------------------------------------------------------------------*/
/**
 *  @class   cube::DefineMetricRequest
 *  @ingroup CUBE_lib.network
 *  @brief   Cube network request to define a metric on the client.
 *
 *  The cube::DefineMetricRequest is used when the Client (GUI) defines a
 *  new metric, a.k.a. a derived metric. The definition data is transferred
 *  to the server, where the metric is defined. The result is transferred
 *  back to the client.
 **/
/*-------------------------------------------------------------------------*/

class DefineMetricRequest
    : public NetworkRequest
{
    public:
        /// @brief Virtual destructor
        ///
        virtual
        ~DefineMetricRequest();

        /// @brief Client-side factory method.
        ///
        /// @param[in] metric
        ///     Reference to the new cube::Metric object.
        /// @return
        ///     Pointer to created request.
        ///
        static NetworkRequestPtr
        create(Metric& metric);

        /// @brief Server-side factory method.
        ///
        /// @return
        ///     Pointer to create request.
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
        /// @param[inout] connection
        ///     Reference to connection on client.
        /// @param[inout] data
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
        /// @brief Client-side constructor.
        ///
        /// @param[in] metric
        ///     Reference to new cube::Metric object.
        ///
        DefineMetricRequest(Metric& metric);

        /// @brief Default constructor for server-side factory.
        ///
        DefineMetricRequest();

        /// Reference to the new Metric to define.
        Metric* mMetric;

        friend class ClientConnection;
        friend class Protocol;
};
}    /* namespace cube */

#endif    /* ! CUBE_DEFINEMETRICREQUEST_H */
