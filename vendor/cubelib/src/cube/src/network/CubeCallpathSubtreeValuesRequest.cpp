/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016-2019                                                **
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
 *  @brief   Definition of the class cube::CallpathSubtreeValuesRequest
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeCallpathSubtreeValuesRequest.h"

#include <cassert>
#include <vector>

#include "CubeClientCallbackData.h"
#include "CubeClientConnection.h"
#include "CubeCnode.h"
#include "CubeIdIndexMap.h"
#include "CubeIoProxy.h"
#include "CubeMetric.h"
#include "CubeServerCallbackData.h"
#include "CubeServerConnection.h"
#include "CubeSysres.h"
#include "CubeTypes.h"
#include "cube_network_types.h"

using namespace std;

namespace cube
{
NetworkRequestPtr
CallpathSubtreeValuesRequest::create(
    const list_of_metrics&      metric_selections,
    const list_of_sysresources& sysres_selections,
    Cnode&                      root_cnode,
    size_t                      depth,
    IdIndexMap&                 cnode_id_indices,
    value_container*            inclusive_values,
    value_container*            exclusive_values )
{
    return NetworkRequest::Ptr( new CallpathSubtreeValuesRequest(
                                    metric_selections,
                                    sysres_selections,
                                    root_cnode,
                                    depth,
                                    cnode_id_indices,
                                    inclusive_values,
                                    exclusive_values ) );
}


NetworkRequestPtr
CallpathSubtreeValuesRequest::create()
{
    return NetworkRequest::Ptr( new CallpathSubtreeValuesRequest() );
}


std::string
CallpathSubtreeValuesRequest::getName() const
{
    return "SubCallTreeValuesRequest";
}


NetworkRequest::id_t
CallpathSubtreeValuesRequest::getId() const
{
    return SUB_CALL_TREE_VALUES_REQUEST;
}


void
CallpathSubtreeValuesRequest::sendRequestPayload( ClientConnection& connection,
                                                  ClientCallbackData* ) const
{
    // Send Metric selections
    connection << uint32_t( mMetricSelections.size() );
    for ( size_t i = 0; i < mMetricSelections.size(); ++i )
    {
        connection << mMetricSelections[ i ].first->get_id();
        connection << uint8_t( mMetricSelections[ i ].second );
    }

    // Send system resource selections
    connection << uint32_t( mSysresSelections.size() );
    for ( size_t i = 0; i < mSysresSelections.size(); ++i )
    {
        connection << mSysresSelections[ i ].first->get_sys_id();
        connection << uint8_t( mSysresSelections[ i ].second );
    }

    // Send Root Cnode ID
    connection << mRootCnode->get_id();

    // Send Depth
    connection << mDepth;

    // Send inclusive value indicator
    connection << uint8_t( mInclusiveValues ? 1 : 0 );

    // Send inclusive value indicator
    connection << uint8_t( mExclusiveValues ? 1 : 0 );
}


void
CallpathSubtreeValuesRequest::receiveRequestPayload(
    ServerConnection&   connection,
    ServerCallbackData* data )
{
    /// @pre Valid CallbackData object.
    assert( data );

    /// @pre Valid Cube file
    assert( data->getCube() );

    // Receive Metric selections
    uint32_t numMetricSelections = connection.get< uint32_t >();
    for ( size_t i = 0; i < numMetricSelections; ++i )
    {
        uint32_t metric_id = connection.get< uint32_t >();
        assert( metric_id < data->getCube()->getCnodes().size() );

        Metric* metric = data->getCube()->getMetrics()[ metric_id ];

        uint8_t flavour = connection.get< uint8_t >();

        mMetricSelections.push_back( make_pair( metric,
                                                CalculationFlavour( flavour ) ) );
    }

    // Receive system resource selections
    uint32_t numSysresSelections = connection.get< uint32_t >();
    for ( size_t i = 0; i < numSysresSelections; i++ )
    {
        uint32_t sysres_id = connection.get< uint32_t >();
        assert( sysres_id < data->getCube()->getSystemResources().size() );
        Sysres* sysres = data->getCube()->getSystemResources()[ sysres_id ];

        uint8_t flavour = connection.get< uint8_t >();

        mSysresSelections.push_back( make_pair( sysres,
                                                CalculationFlavour( flavour ) ) );
    }

    // Receive Root Cnode ID
    id_t root_cnode_id = connection.get< id_t >();

    // Receive Depth
    mDepth = connection.get< size_t >();

    try
    {
        mRootCnode = data->getCube()->getCnodes()[ root_cnode_id ];
    }
    catch ( std::exception& e )
    {
        throw RecoverableNetworkError( e.what() );
    }
    bool getInclusiveValues = connection.get< uint8_t >();
    bool getExclusiveValues = connection.get< uint8_t >();

    mCnodeIds = new IdIndexMap();

    if ( getInclusiveValues )
    {
        mInclusiveValues = new value_container;
    }
    else
    {
        mInclusiveValues = CUBE_PROXY_VALUES_IGNORE;
    }

    if ( getExclusiveValues )
    {
        mExclusiveValues = new value_container;
    }
    else
    {
        mExclusiveValues = CUBE_PROXY_VALUES_IGNORE;
    }
}


void
CallpathSubtreeValuesRequest::processRequest( ServerCallbackData* data )
{
    try
    {
        data->getCube()->getCallpathSubtreeValues( mMetricSelections,
                                                   mSysresSelections,
                                                   *mRootCnode,
                                                   mDepth,
                                                   *mCnodeIds,
                                                   mInclusiveValues,
                                                   mExclusiveValues );
    }
    catch ( cube::Error& theError )
    {
        cerr << theError.what() << endl;
    }
}


void
CallpathSubtreeValuesRequest::sendResponsePayload(
    ServerConnection& connection,
    ServerCallbackData* )
const
{
    connection << uint64_t( mCnodeIds->size() );

    for ( IdIndexMap::iterator it = mCnodeIds->begin();
          it != mCnodeIds->end();
          ++it )
    {
        connection << it.getId();
        connection << uint64_t( it.getIndex() );
    }

    if ( mInclusiveValues != CUBE_PROXY_VALUES_IGNORE )
    {
        for ( size_t i = 0; i < mInclusiveValues->size(); ++i )
        {
            connection << uint32_t( ( *mInclusiveValues )[ i ]->myDataType() );
            ( *mInclusiveValues )[ i ]->toStream( connection );
        }
    }

    if ( mExclusiveValues != CUBE_PROXY_VALUES_IGNORE )
    {
        for ( size_t i = 0; i < mExclusiveValues->size(); ++i )
        {
            connection << uint32_t( ( *mExclusiveValues )[ i ]->myDataType() );
            ( *mExclusiveValues )[ i ]->toStream( connection );
        }
    }
}


void
CallpathSubtreeValuesRequest::receiveResponsePayload(
    ClientConnection& connection,
    ClientCallbackData* )
{
    size_t numValues = connection.get< uint64_t >();

    for ( size_t i = 0; i < numValues; ++i )
    {
        uint32_t id    = connection.get< uint32_t >();
        size_t   index = connection.get< uint64_t >();

        mCnodeIds->insert( id, index );
    }

    if ( mInclusiveValues != CUBE_PROXY_VALUES_IGNORE )
    {
        mInclusiveValues->resize( numValues );
        for ( size_t i = 0; i < numValues; ++i )
        {
            uint32_t datatype_id = connection.get< uint32_t >();
            ( *mInclusiveValues )[ i ] =
                selectValueOnDataType( DataType( datatype_id ) );
            ( *mInclusiveValues )[ i ]->fromStream( connection );
        }
    }
    if ( mExclusiveValues != CUBE_PROXY_VALUES_IGNORE )
    {
        mExclusiveValues->resize( numValues );
        for ( size_t i = 0; i < numValues; ++i )
        {
            uint32_t datatype_id = connection.get< uint32_t >();
            ( *mExclusiveValues )[ i ] =
                selectValueOnDataType( DataType( datatype_id ) );
            ( *mExclusiveValues )[ i ]->fromStream( connection );
        }
    }
}


CallpathSubtreeValuesRequest::CallpathSubtreeValuesRequest(
    const list_of_metrics&      metric_selections,
    const list_of_sysresources& sysres_selections,
    Cnode&                      root_cnode,
    size_t                      depth,
    IdIndexMap&                 cnode_id_indices,
    value_container*            inclusive_values,
    value_container*            exclusive_values )
    : mRootCnode( &root_cnode ),
    mDepth( depth ),
    mMetricSelections( metric_selections ),
    mSysresSelections( sysres_selections ),
    mCnodeIds( &cnode_id_indices ),
    mInclusiveValues( inclusive_values ),
    mExclusiveValues( exclusive_values )
{
}


CallpathSubtreeValuesRequest::CallpathSubtreeValuesRequest()
    : mRootCnode( NULL ),
    mDepth( 0 ),
    mCnodeIds( NULL ),
    mInclusiveValues( NULL ),
    mExclusiveValues( NULL )
{
}


CallpathSubtreeValuesRequest::~CallpathSubtreeValuesRequest()
{
}
}    // namespace cube
