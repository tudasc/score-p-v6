/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2018-2019                                                **
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
 *  @brief   Definition of the class cube::MetricSubtreeValuesRequest
 **/
/*-------------------------------------------------------------------------*/


#include "config.h"

#include "CubeMetricSubtreeValuesRequest.h"

#include <cassert>

#include "CubeClientCallbackData.h"
#include "CubeClientConnection.h"
#include "CubeCnode.h"
#include "CubeError.h"
#include "CubeIdIndexMap.h"
#include "CubeIoProxy.h"
#include "CubeMetric.h"
#include "CubeNetworkProxy.h"
#include "CubeRegion.h"
#include "CubeServerCallbackData.h"
#include "CubeServerConnection.h"

using namespace std;

namespace cube
{
NetworkRequestPtr
MetricSubtreeValuesRequest::create( const list_of_cnodes&       cnode_selections,
                                    const list_of_sysresources& sysres_selections,
                                    Metric&                     root_metric,
                                    size_t                      depth,
                                    IdIndexMap&                 metric_id_indices,
                                    value_container*            inclusive_values,
                                    value_container*            exclusive_values )
{
    return NetworkRequest::Ptr( new MetricSubtreeValuesRequest( cnode_selections,
                                                                sysres_selections,
                                                                root_metric,
                                                                depth,
                                                                metric_id_indices,
                                                                inclusive_values,
                                                                exclusive_values ) );
}


NetworkRequestPtr
MetricSubtreeValuesRequest::create(
    const list_of_regions&      region_selections,
    const list_of_sysresources& sysres_selections,
    Metric&                     root_metric,
    size_t                      depth,
    IdIndexMap&                 metric_id_indices,
    value_container*            inclusive_values,
    value_container*            exclusive_values )
{
    return NetworkRequest::Ptr( new MetricSubtreeValuesRequest( region_selections,
                                                                sysres_selections,
                                                                root_metric,
                                                                depth,
                                                                metric_id_indices,
                                                                inclusive_values,
                                                                exclusive_values ) );
}


NetworkRequestPtr
MetricSubtreeValuesRequest::create()
{
    return NetworkRequest::Ptr( new MetricSubtreeValuesRequest() );
}


std::string
MetricSubtreeValuesRequest::getName() const
{
    return "MetricSubtreeValuesRequest";
}


NetworkRequest::id_t
MetricSubtreeValuesRequest::getId() const
{
    return METRIC_SUBTREE_VALUES_REQUEST;
}


void
MetricSubtreeValuesRequest::sendRequestPayload( ClientConnection& connection,
                                                ClientCallbackData* ) const
{
    // Send Cnode selections
    connection << uint32_t( mCnodeSelections.size() );
    for ( size_t i = 0; i < mCnodeSelections.size(); ++i )
    {
        connection << mCnodeSelections[ i ].first->get_id();
        connection << uint8_t( mCnodeSelections[ i ].second );
    }

    // Send Region selections
    connection << uint32_t( mRegionSelections.size() );
    for ( size_t i = 0; i < mRegionSelections.size(); ++i )
    {
        connection << mRegionSelections[ i ].first->get_id();
        connection << uint8_t( mRegionSelections[ i ].second );
    }

    // Send system resource selections
    connection << uint32_t( mSysresSelections.size() );
    for ( size_t i = 0; i < mSysresSelections.size(); ++i )
    {
        connection << mSysresSelections[ i ].first->get_sys_id();
        connection << uint8_t( mSysresSelections[ i ].second );
    }

    // Send Root Metric ID
    connection << mRootMetric->get_id();

    // Send Depth
    connection << mDepth;

    // Send inclusive value indicator
    connection << uint8_t( mInclusiveValues ? 1 : 0 );

    // Send inclusive value indicator
    connection << uint8_t( mExclusiveValues ? 1 : 0 );
}


void
MetricSubtreeValuesRequest::receiveRequestPayload(
    ServerConnection&   connection,
    ServerCallbackData* data )
{
    /// @pre Valid CallbackData object.
    assert( data );

    /// @pre Valid Cube file
    assert( data->getCube() );

    // Receive Cnode selections
    uint32_t numCnodeSelections = connection.get< uint32_t >();
    for ( size_t i = 0; i < numCnodeSelections; ++i )
    {
        uint32_t cnode_id = connection.get< uint32_t >();
        assert( cnode_id < data->getCube()->getCnodes().size() );

        Cnode* cnode = data->getCube()->getCnodes()[ cnode_id ];

        uint8_t flavour = connection.get< uint8_t >();

        mCnodeSelections.push_back( make_pair( cnode,
                                               CalculationFlavour( flavour ) ) );
    }

    // Receive Region selections
    uint32_t numRegionSelections = connection.get< uint32_t >();
    for ( size_t i = 0; i < numRegionSelections; ++i )
    {
        uint32_t region_id = connection.get< uint32_t >();
        assert( region_id < data->getCube()->getRegions().size() );
        Region* region = data->getCube()->getRegions()[ region_id ];

        uint8_t flavour = connection.get< uint8_t >();

        mRegionSelections.push_back( make_pair( region,
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

    // Receive Root Metric ID
    id_t root_metric_id = connection.get< id_t >();

    // Receive Depth
    mDepth = connection.get< size_t >();

    try
    {
        mRootMetric = data->getCube()->getMetrics()[ root_metric_id ];
    }
    catch ( std::exception& e )
    {
        throw RecoverableNetworkError( e.what() );
    }
    bool getInclusiveValues = connection.get< uint8_t >();
    bool getExclusiveValues = connection.get< uint8_t >();

    mMetricIds = new IdIndexMap();

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

    try
    {
        if ( mRegionSelections.size() > 0 )
        {
            data->getCube()->getMetricSubtreeValues( mRegionSelections,
                                                     mSysresSelections,
                                                     *mRootMetric,
                                                     mDepth,
                                                     *mMetricIds,
                                                     mInclusiveValues,
                                                     mExclusiveValues );
        }
        else
        {
            data->getCube()->getMetricSubtreeValues( mCnodeSelections,
                                                     mSysresSelections,
                                                     *mRootMetric,
                                                     mDepth,
                                                     *mMetricIds,
                                                     mInclusiveValues,
                                                     mExclusiveValues );
        }
    }
    catch ( cube::Error& theError )
    {
        cerr << theError << endl;
    }
}


void
MetricSubtreeValuesRequest::sendResponsePayload( ServerConnection& connection,
                                                 ServerCallbackData* ) const
{
    connection << uint64_t( mMetricIds->size() );

    for ( IdIndexMap::iterator it = mMetricIds->begin();
          it != mMetricIds->end();
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
MetricSubtreeValuesRequest::receiveResponsePayload(
    ClientConnection& connection,
    ClientCallbackData* )
{
    size_t numValues = connection.get< uint64_t >();

    for ( size_t i = 0; i < numValues; ++i )
    {
        uint32_t id    = connection.get< uint32_t >();
        size_t   index = connection.get< uint64_t >();

        mMetricIds->insert( id, index );
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


MetricSubtreeValuesRequest::MetricSubtreeValuesRequest(
    const list_of_cnodes&       cnode_selections,
    const list_of_sysresources& sysres_selections,
    Metric&                     root_metric,
    size_t                      depth,
    IdIndexMap&                 metric_id_indices,
    value_container*            inclusive_values,
    value_container*            exclusive_values )
    : mRootMetric( &root_metric ),
    mDepth( depth ),
    mCnodeSelections( cnode_selections ),
    mSysresSelections( sysres_selections ),
    mMetricIds( &metric_id_indices ),
    mInclusiveValues( inclusive_values ),
    mExclusiveValues( exclusive_values )
{
}


MetricSubtreeValuesRequest::MetricSubtreeValuesRequest(
    const list_of_regions&      region_selections,
    const list_of_sysresources& sysres_selections,
    Metric&                     root_metric,
    size_t                      depth,
    IdIndexMap&                 metric_id_indices,
    value_container*            inclusive_values,
    value_container*            exclusive_values )
    : mRootMetric( &root_metric ),
    mDepth( depth ),
    mRegionSelections( region_selections ),
    mSysresSelections( sysres_selections ),
    mMetricIds( &metric_id_indices ),
    mInclusiveValues( inclusive_values ),
    mExclusiveValues( exclusive_values )
{
}


MetricSubtreeValuesRequest::MetricSubtreeValuesRequest()
    : mRootMetric( NULL ),
    mDepth( 0 ),
    mMetricIds( NULL ),
    mInclusiveValues( NULL ),
    mExclusiveValues( NULL )
{
}


MetricSubtreeValuesRequest::~MetricSubtreeValuesRequest()
{
}
}    /* namespace cube */
