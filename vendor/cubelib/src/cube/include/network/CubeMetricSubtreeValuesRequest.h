/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016                                                     **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/*-------------------------------------------------------------------------*/
/**
 *  @file
 *  @ingroup CUBE_lib.network
 *  @brief   Declaration of the class cube::MetricSubtreeValuesRequest
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_METRICSUBTREEVALUESREQUEST_H
#define CUBE_METRICSUBTREEVALUESREQUEST_H

#include "CubeCnode.h"
#include "CubeNetworkRequest.h"
#include "CubeRegion.h"
#include "CubeSysres.h"

namespace cube
{
// Forward declarations
class IdIndexMap;
class Metric;
class Value;

/*-------------------------------------------------------------------------*/
/**
 *  @class   cube::MetricSubtreeValuesRequest
 *  @ingroup CUBE_lib.network
 *  @brief   Request inclusive and exclusive values for a subtree of the
 *   Metric tree.
 **/
/*-------------------------------------------------------------------------*/

class MetricSubtreeValuesRequest
    : public NetworkRequest
{
    public:
        /// @brief Virtual destructor.
        ///
        virtual
        ~MetricSubtreeValuesRequest();

        /// Client-side factory method.
        ///
        /// @param cnode_selections
        ///     The selected cnodes
        /// @param sysres_selections
        ///     The selected system resources
        /// @param root_metric
        ///     Root of the subtree
        /// @param depth
        ///     Depth of the subtree
        /// @param metric_id_indices
        ///     Associative container for id to index mappings
        /// @param inclusive_value
        ///     List of inclusive values
        /// @param exclusive_value
        ///     List of exclusive values
        /// @return
        ///     Pointer to created request
        ///
        static NetworkRequestPtr
        create(const list_of_cnodes&       cnode_selections,
               const list_of_sysresources& sysres_selections,
               Metric&                     root_metric,
               size_t                      depth,
               IdIndexMap&                 metric_id_indices,
               value_container*            inclusive_value,
               value_container*            exclusive_value);

        /// @brief Client-side factory method.
        ///
        /// @param region_selections
        ///     The selected region
        /// @param sysres_selections
        ///     The selected system resources
        /// @param root_metric
        ///     Root of the subtree
        /// @param depth
        ///     Depth of the subtree
        /// @param metric_id_indices
        ///     Associative container for id to index mappings
        /// @param inclusive_value
        ///     List of inclusive values
        /// @param exclusive_value
        ///     List of exclusive values
        /// @return
        ///     Pointer to created request
        ///
        static NetworkRequestPtr
        create(const list_of_regions&      region_selections,
               const list_of_sysresources& sysres_selections,
               Metric&                     root_metric,
               size_t                      depth,
               IdIndexMap&                 metric_id_indices,
               value_container*            inclusive_value,
               value_container*            exclusive_value);

        /// @brief Server-side factory method.
        ///
        /// @return Pointer to created request
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
        /// @brief Client-side constructor used by factory method
        ///
        /// @param cnode_selections
        ///     The selected cnodes
        /// @param sysres_selections
        ///     The selected system resources
        /// @param root_metric
        ///     Root of the subtree
        /// @param depth
        ///     Depth of the subtree
        /// @param metric_id_indices
        ///     Associative container for id to index mappings
        /// @param inclusive_value
        ///     List of inclusive values
        /// @param exclusive_value
        ///     List of exclusive values
        /// @return
        ///     Pointer to created request
        ///
        MetricSubtreeValuesRequest(const list_of_cnodes&       cnode_selections,
                                   const list_of_sysresources& sysres_selections,
                                   Metric&                     root_metric,
                                   size_t                      depth,
                                   IdIndexMap&                 metric_id_indices,
                                   value_container*            inclusive_values,
                                   value_container*            exclusive_values);

        /// @brief Client-side constructor used by factory method.
        ///
        /// @param region_selections
        ///     The selected region
        /// @param sysres_selections
        ///     The selected system resources
        /// @param root_metric
        ///     Root of the subtree
        /// @param depth
        ///     Depth of the subtree
        /// @param metric_id_indices
        ///     Associative container for id to index mappings
        /// @param inclusive_value
        ///     List of inclusive values
        /// @param exclusive_value
        ///     List of exclusive values
        /// @return
        ///     Pointer to created request
        ///
        MetricSubtreeValuesRequest(
            const list_of_regions&      region_selections,
            const list_of_sysresources& sysres_selections,
            Metric&                     root_metric,
            size_t                      depth,
            IdIndexMap&                 metric_id_indices,
            value_container*            inclusive_values,
            value_container*            exclusive_values);

        /// @brief Server-side constructor.
        ///
        MetricSubtreeValuesRequest();

        /// Root metric
        Metric* mRootMetric;

        /// Subtree depth
        size_t mDepth;

        /// Cnode selections
        list_of_cnodes mCnodeSelections;

        /// Region selections
        list_of_regions mRegionSelections;

        /// Sysres selections
        list_of_sysresources mSysresSelections;

        /// Metric IDs
        IdIndexMap* mMetricIds;

        /// Inclusive values
        value_container* mInclusiveValues;

        /// Exclusive values
        value_container* mExclusiveValues;
};
}    /* namespace cube */

#endif    /* ! CUBE_METRICSUBTREEVALUESREQUEST_H */
