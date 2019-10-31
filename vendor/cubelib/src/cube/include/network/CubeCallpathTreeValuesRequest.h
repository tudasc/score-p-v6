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
 *  @brief   Declaration of the class cube::CallpathTreeValuesRequest
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_CALLPATHTREEVALUESREQUEST_H
#define CUBE_CALLPATHTREEVALUESREQUEST_H

#include <vector>

#include "CubeMetric.h"
#include "CubeNetworkRequest.h"
#include "CubeSysres.h"
#include "cube_network_types.h"

namespace cube
{
// Forward declarations
class Cnode;
class Value;

/*-------------------------------------------------------------------------*/
/**
 *  @class   cube::CallpathTreeValuesRequest
 *  @ingroup CUBE_lib.network
 *  @brief   Request calltree values from a Cube server
 **/
/*-------------------------------------------------------------------------*/

class CallpathTreeValuesRequest
    : public NetworkRequest
{
    public:
        /// @brief Client-side factory method.
        ///
        /// @param[in] metric_selections
        ///     The selected metrics.
        /// @param[in] sysres_selections
        ///     The selected system resources.
        /// @param[in] inclusive_values
        ///     Reference to a container to be used for the data returned as
        ///     inclusive values. The container will be cleared before new data
        ///     is added.
        /// @param[in] exclusive_values
        ///     Reference to a container to be used for the data returned as
        ///     exclusive values. The container will be cleared before new data
        ///     is added.
        /// @return
        ///     Pointer to network request.
        ///
        static NetworkRequestPtr
        create(const list_of_metrics&      metric_selections,
               const list_of_sysresources& sysres_selections,
               value_container&            inclusive_values,
               value_container&            exclusive_values);

        /// @brief Server-side factory method.
        ///
        /// @return Pointer to network request.
        ///
        static NetworkRequestPtr
        create();

        /// @brief Virtual destructor.
        ///
        virtual
        ~CallpathTreeValuesRequest();

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
        /// @brief Client-side constructor.
        ///
        /// @param[in] metric_selections
        ///     The selected metrics.
        /// @param[in] sysres_selections
        ///     The selected system resources.
        /// @param[in] inclusive_values
        ///     Reference to a container to be used for the data returned as
        ///     inclusive values. The container will be cleared before new data
        ///     is added.
        /// @param[in] exclusive_values
        ///     Reference to a container to be used for the data returned as
        ///     exclusive values. The container will be cleared before new data
        ///     is added.
        ///
        CallpathTreeValuesRequest(const list_of_metrics&      metric_selections,
                              const list_of_sysresources& sysres_selections,
                              value_container&            inclusive_values,
                              value_container&            exclusive_values);

        /// @brief Server-side constructor
        ///
        CallpathTreeValuesRequest();

        /// Metric selections
        list_of_metrics mMetricSelections;

        /// System resource selections
        list_of_sysresources mSysresSelections;

        /// Inclusive values container
        value_container* mInclusiveValues;

        /// Exclusive values container
        value_container* mExclusiveValues;
};
}    /* namespace cube */

#endif    /* ! CUBE_CALLTREEVALUESREQUEST_H */
