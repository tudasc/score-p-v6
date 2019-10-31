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
 *  @brief   Declaration of the class cube::MetricTreeValuesRequest
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_METRICTREEVALUESREQUEST_H
#define CUBE_METRICTREEVALUESREQUEST_H

#include "CubeCnode.h"
#include "CubeNetworkRequest.h"
#include "CubeRegion.h"
#include "CubeSysres.h"

namespace cube
{
// Forward declarations
class Metric;
class Value;

/*-------------------------------------------------------------------------*/
/**
 *  @class   cube::MetricTreeValuesRequest
 *  @ingroup CUBE_lib.network
 *  @brief   Request the inclusive and exclusive values for the metric tree.
 **/
/*-------------------------------------------------------------------------*/

class MetricTreeValuesRequest
    : public NetworkRequest
{
    public:
        /// @brief Virtual destructor.
        ///
        virtual
        ~MetricTreeValuesRequest();

        /// Client-side factory method.
        ///
        /// @param[in] cnode_selections
        ///     The selected cnode.
        /// @param[in] sysres_selections
        ///     The selected system resources.
        /// @param[in] options
        ///     The options to fine-tune the behavior of the call.
        /// @param[in] inclusive_values
        ///     Reference to a container to be used for the data returned as
        ///     inclusive values. The container will be cleared before new data
        ///     is added.
        /// @param[in] exclusive_values
        ///     Reference to a container to be used for the data returned as
        ///     exclusive values. The container will be cleared before new data
        ///     is added.
        /// @return
        ///     Pointer to created request.
        ///
        static NetworkRequestPtr
        create(const list_of_cnodes&       cnode_selections,
               const list_of_sysresources& sysres_selections,
               value_container&            inclusive_values,
               value_container&            exclusive_values);

        /// @brief Client-side factory method.
        ///
        /// @param[in] root_metric
        ///     The root of the metric tree to query.
        /// @param[in] cnode_selections
        ///     The selected cnode.
        /// @param[in] sysres_selections
        ///     The selected system resources.
        /// @param[in] options
        ///     The options to fine-tune the behavior of the call.
        /// @param[in] inclusive_values
        ///     Reference to a container to be used for the data returned as
        ///     inclusive values. The container will be cleared before new data
        ///     is added.
        /// @param[in] exclusive_values
        ///     Reference to a container to be used for the data returned as
        ///     exclusive values. The container will be cleared before new data
        ///     is added.
        /// @return
        ///     Pointer to created request.
        ///
        static NetworkRequestPtr
        create(const list_of_regions&      regions_selections,
               const list_of_sysresources& sysres_selections,
               value_container&            inclusive_values,
               value_container&            exclusive_values);

        /// @brief Server-side factory method.
        ///
        /// @return
        ///     Pointer to network request.
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

        /// @brief Server-side callback to execute after reception.
        ///
        /// @param data
        ///     Callback data structure.
        ///
        virtual void
        processRequest(ServerCallbackData* data);

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
        /// @brief Private client-side constructor.
        ///
        /// @param[in]  cnode_selections
        ///     The selected cnode.
        /// @param[in]  sysres_selections
        ///     The selected system resources.
        /// @param[out] inclusive_values
        ///     Reference to a container to be used for the data returned as
        ///     inclusive values. The container will be cleared before new data
        ///     is added.
        /// @param[out] exclusive_values
        ///     Reference to a container to be used for the data returned as
        ///     exclusive values. The container will be cleared before new data
        ///     is added.
        ///
        MetricTreeValuesRequest(const list_of_cnodes&       cnode_selections,
                                const list_of_sysresources& sysres_selections,
                                value_container&            inclusive_values,
                                value_container&            exclusive_values);

        /// @brief Private client-side constructor.
        ///
        /// @param[in] region_selections
        ///     The selected regions.
        /// @param[in] sysres_selections
        ///     The selected system resources.
        /// @param[out] inclusive_values Reference to a container to be used for the data returned as inclusive values. The container will be cleared before new data is added..
        /// @param[out] exclusive_values Reference to a container to be used for the data returned as exclusive values. The container will be cleared before new data is added..
        ///
        MetricTreeValuesRequest(const list_of_regions&      region_selections,
                                const list_of_sysresources& sysres_selections,
                                value_container&            inclusive_values,
                                value_container&            exclusive_values);

        /// @brief Private server-side constructor.
        ///
        MetricTreeValuesRequest();

        /// Cnode selections
        list_of_cnodes mCnodeSelections;

        /// Region selections
        list_of_regions mRegionSelections;

        /// Sysres selections
        list_of_sysresources mSysresSelections;

        /// Inclusive values
        value_container* mInclusiveValues;

        /// Exclusive values
        value_container* mExclusiveValues;
};
}    /* namespace cube */

#endif    /* ! CUBE_METRICTREEVALUESREQUEST_H */
