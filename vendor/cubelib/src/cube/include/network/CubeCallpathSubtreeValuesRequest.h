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
 *  @brief   Declaration of the class cube::CallpathSubtreeValuesRequest.
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_CALLPATHSUBTREEVALUESREQUEST_H
#define CUBE_CALLPATHSUBTREEVALUESREQUEST_H

#include "CubeCnode.h"
#include "CubeMetric.h"
#include "CubeNetworkRequest.h"
#include "CubeSysres.h"

namespace cube
{
// Forward declarations
class Cnode;
class IdIndexMap;
class Value;

/*-------------------------------------------------------------------------*/
/**
 *  @class   cube::CallpathSubtreeValuesRequest
 *  @ingroup CUBE_lib.network
 *  @brief   Retrieve the inclusive and/or exclusive values for a Cnode subtree.
 **/
/*-------------------------------------------------------------------------*/

class CallpathSubtreeValuesRequest
    : public NetworkRequest
{
    public:
        /// @brief Virtual destructor.
        ///
        virtual
        ~CallpathSubtreeValuesRequest();

        /// Client-side factory method.
        ///
        /// @param metric_selections
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
        create(const list_of_metrics&      metric_selections,
               const list_of_sysresources& sysres_selections,
               Cnode&                      root_cnode,
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
        /// @brief Client-side constructor used by factory method
        ///
        /// @param cnode_selections
        ///     The selected cnodes
        /// @param sysres_selections
        ///     The selected system resources
        /// @param root_cnode
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
        CallpathSubtreeValuesRequest(const list_of_metrics&      metric_selections,
                                 const list_of_sysresources& sysres_selections,
                                 Cnode&                      root_cnode,
                                 size_t                      depth,
                                 IdIndexMap&                 metric_id_indices,
                                 value_container*            inclusive_values,
                                 value_container*            exclusive_values);

        /// @brief Server-side constructor.
        ///
        CallpathSubtreeValuesRequest();

        /// Root metric
        Cnode* mRootCnode;

        /// Subtree depth
        size_t mDepth;

        /// Cnode selections
        list_of_metrics mMetricSelections;

        /// Region selections
        list_of_regions mRegionSelections;

        /// Sysres selections
        list_of_sysresources mSysresSelections;

        /// Metric IDs
        IdIndexMap* mCnodeIds;

        /// Inclusive values
        value_container* mInclusiveValues;

        /// Exclusive values
        value_container* mExclusiveValues;
};
}    // namespace cube

#endif    // ! CUBE_CALLSUBTREEVALUESREQUEST_H
