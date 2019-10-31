/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016-2019                                                **
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
 *  @file    CubeMetricTreeValuesRequest.cpp
 *  @ingroup CUBE_lib.network
 *  @brief   Definition of the class MetricTreeValuesRequest
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeMetricTreeValuesRequest.h"

#include <cassert>
#include <iostream>
#include <string>
#include <utility>

#include "CubeClientConnection.h"
#include "CubeCnode.h"
#include "CubeError.h"
#include "CubeIoProxy.h"
#include "CubeServerCallbackData.h"
#include "CubeServerConnection.h"
#include "CubeTypes.h"
#include "CubeValue.h"
#include "CubeValues.h"

using namespace cube;
using namespace std;

namespace cube
{
MetricTreeValuesRequest::~MetricTreeValuesRequest()
{
}


NetworkRequestPtr
MetricTreeValuesRequest::create( const list_of_cnodes&       cnode_selections,
                                 const list_of_sysresources& sysres_selections,
                                 value_container&            inclusive_values,
                                 value_container&            exclusive_values )
{
    return NetworkRequest::Ptr( new MetricTreeValuesRequest( cnode_selections,
                                                             sysres_selections,
                                                             inclusive_values,
                                                             exclusive_values ) );
}


NetworkRequestPtr
MetricTreeValuesRequest::create( const list_of_regions&      region_selections,
                                 const list_of_sysresources& sysres_selections,
                                 value_container&            inclusive_values,
                                 value_container&            exclusive_values )
{
    return NetworkRequest::Ptr( new MetricTreeValuesRequest( region_selections,
                                                             sysres_selections,
                                                             inclusive_values,
                                                             exclusive_values ) );
}


string
MetricTreeValuesRequest::getName() const
{
    return "MetricTreeValues";
}


NetworkRequest::id_t
MetricTreeValuesRequest::getId() const
{
    return METRIC_TREE_VALUES_REQUEST;
}


void
MetricTreeValuesRequest::sendRequestPayload( ClientConnection& connection,
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
}


void
MetricTreeValuesRequest::receiveRequestPayload( ServerConnection&   connection,
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
}


void
MetricTreeValuesRequest::processRequest( ServerCallbackData* data )
{
    mInclusiveValues = new value_container();
    mExclusiveValues = new value_container();

    /// @pre Valid CallbackData.
    assert( data );

    /// @pre Valid Cube object.
    assert( data->getCube() );

    try
    {
        if ( mCnodeSelections.size() > 0 )
        {
            data->getCube()->getMetricTreeValues( mCnodeSelections,
                                                  mSysresSelections,
                                                  *mInclusiveValues,
                                                  *mExclusiveValues );
        }
        else
        {
            data->getCube()->getMetricTreeValues( mRegionSelections,
                                                  mSysresSelections,
                                                  *mInclusiveValues,
                                                  *mExclusiveValues );
        }
    }
    catch ( const std::exception& e )
    {
        throw RecoverableNetworkError( e.what() );
    }
}


void
MetricTreeValuesRequest::sendResponsePayload( ServerConnection& connection,
                                              ServerCallbackData* ) const
{
    // Send number of values
    connection << uint64_t( mInclusiveValues->size() );

    for ( size_t i = 0; i < mInclusiveValues->size(); ++i )
    {
        connection << uint32_t( ( *mInclusiveValues )[ i ]->myDataType() );
        ( *mInclusiveValues )[ i ]->toStream( connection );
    }

    for ( size_t i = 0; i < mExclusiveValues->size(); ++i )
    {
        connection << uint32_t( ( *mExclusiveValues )[ i ]->myDataType() );
        ( *mExclusiveValues )[ i ]->toStream( connection );
    }

    deleteAndResize( *mInclusiveValues, 0 );
    deleteAndResize( *mExclusiveValues, 0 );

    delete mInclusiveValues;
    delete mExclusiveValues;
}


void
MetricTreeValuesRequest::receiveResponsePayload( ClientConnection& connection,
                                                 ClientCallbackData* )
{
    /// @pre Valid inclusive value vector
    assert( mInclusiveValues );

    /// @pre Valid exclusive value vector
    assert( mExclusiveValues );

    uint64_t num_entries = connection.get< uint64_t >();

    // initialize value vectors
    mInclusiveValues->resize( num_entries );
    for ( size_t i = 0; i < num_entries; ++i )
    {
        uint32_t datatype_id = connection.get< uint32_t >();
        ( *mInclusiveValues )[ i ] = selectValueOnDataType( DataType( datatype_id ) );
        ( *mInclusiveValues )[ i ]->fromStream( connection );
    }
    mExclusiveValues->resize( num_entries );
    for ( size_t i = 0; i < num_entries; ++i )
    {
        uint32_t datatype_id = connection.get< uint32_t >();
        ( *mExclusiveValues )[ i ] = selectValueOnDataType( DataType( datatype_id ) );
        ( *mExclusiveValues )[ i ]->fromStream( connection );
    }
}


MetricTreeValuesRequest::MetricTreeValuesRequest(
    const list_of_cnodes&       cnode_selections,
    const list_of_sysresources& sysres_selections,
    value_container&            inclusive_values,
    value_container&            exclusive_values )
    : mCnodeSelections( cnode_selections ),
    mSysresSelections( sysres_selections ),
    mInclusiveValues( &inclusive_values ),
    mExclusiveValues( &exclusive_values )
{
}


MetricTreeValuesRequest::MetricTreeValuesRequest(
    const list_of_regions&      region_selections,
    const list_of_sysresources& sysres_selections,
    value_container&            inclusive_values,
    value_container&            exclusive_values )
    : mRegionSelections( region_selections ),
    mSysresSelections( sysres_selections ),
    mInclusiveValues( &inclusive_values ),
    mExclusiveValues( &exclusive_values )
{
}


MetricTreeValuesRequest::MetricTreeValuesRequest()
    : mInclusiveValues( NULL ),
    mExclusiveValues( NULL )
{
}


NetworkRequestPtr
MetricTreeValuesRequest::create()
{
    return NetworkRequest::Ptr( new MetricTreeValuesRequest() );
}
}    /* namespace cube */
