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
 *  @file
 *  @ingroup CUBE_lib.network
 *  @brief   Definition of the class cube::CallpathTreeValuesRequest
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeCallpathTreeValuesRequest.h"

#include <cassert>
#include <string>

#include "CubeClientConnection.h"
#include "CubeCnode.h"
#include "CubeError.h"
#include "CubeIoProxy.h"
#include "CubeServerCallbackData.h"
#include "CubeServerConnection.h"
#include "CubeTypes.h"
#include "CubeValue.h"
#include "CubeValues.h"

using namespace std;
using namespace cube;

NetworkRequestPtr
CallpathTreeValuesRequest::create()
{
    return NetworkRequest::Ptr( new CallpathTreeValuesRequest() );
}


string
CallpathTreeValuesRequest::getName() const
{
    return "CallTreeValues";
}


NetworkRequest::id_t
CallpathTreeValuesRequest::getId() const
{
    return CALL_TREE_VALUES_REQUEST;
}


void
CallpathTreeValuesRequest::sendRequestPayload( ClientConnection& connection,
                                               ClientCallbackData* ) const
{
    // Send Metric selections
    connection << uint32_t( mMetricSelections.size() );
    for ( size_t i = 0; i < mMetricSelections.size(); ++i )
    {
        connection << mMetricSelections[ i ].first->get_id();
        connection << uint8_t( mMetricSelections[ i ].second );
    }

    // Send Sysres selections
    connection << uint32_t( mSysresSelections.size() );
    for ( size_t i = 0; i < mSysresSelections.size(); ++i )
    {
        connection << mSysresSelections[ i ].first->get_id();
        connection << uint8_t( mSysresSelections[ i ].second );
    }
}


void
CallpathTreeValuesRequest::receiveRequestPayload( ServerConnection&   connection,
                                                  ServerCallbackData* data )
{
    /// @pre Valid CallbackData object.
    assert( data );

    /// @pre Valid Cube file
    assert( data->getCube() );

    // Receive metric selections
    uint32_t numMetricSelections = connection.get< uint32_t >();
    for ( size_t i = 0; i < numMetricSelections; ++i )
    {
        uint32_t metric_id = connection.get< uint32_t >();
        assert( metric_id < data->getCube()->getMetrics().size() );
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
}


void
CallpathTreeValuesRequest::processRequest( ServerCallbackData* data )
{
    mInclusiveValues = new value_container();
    mExclusiveValues = new value_container();

    /// @pre Valid CallbackData.
    assert( data );

    /// @pre Valid Cube object.
    assert( data->getCube() );

    try
    {
        data->getCube()->getCallpathTreeValues( mMetricSelections,
                                                mSysresSelections,
                                                *mInclusiveValues,
                                                *mExclusiveValues );
    }
    catch ( const std::exception& e )
    {
        throw RecoverableNetworkError( e.what() );
    }
}


void
CallpathTreeValuesRequest::sendResponsePayload( ServerConnection& connection,
                                                ServerCallbackData* ) const
{
    // Send value type first (all values have the same type)
    connection << uint32_t( ( *mInclusiveValues )[ 0 ]->myDataType() );

    // Send number of values
    connection << uint64_t( mInclusiveValues->size() );

    for ( size_t i = 0; i < mInclusiveValues->size(); ++i )
    {
        ( *mInclusiveValues )[ i ]->toStream( connection );
    }

    for ( size_t i = 0; i < mExclusiveValues->size(); ++i )
    {
        ( *mExclusiveValues )[ i ]->toStream( connection );
    }

    deleteAndResize( *mInclusiveValues, 0 );
    deleteAndResize( *mExclusiveValues, 0 );

    delete mInclusiveValues;
    delete mExclusiveValues;
}


void
CallpathTreeValuesRequest::receiveResponsePayload(
    ClientConnection& connection,
    ClientCallbackData* )
{
    /// @pre Valid inclusive value vector
    assert( mInclusiveValues );

    /// @pre Valid exclusive value vector
    assert( mExclusiveValues );

    uint32_t datatype_id = connection.get< uint32_t >();
    uint64_t num_entries = connection.get< uint64_t >();

    // initialize value vectors
    mInclusiveValues->resize( num_entries );
    for ( size_t i = 0; i < num_entries; ++i )
    {
        ( *mInclusiveValues )[ i ] = selectValueOnDataType( DataType( datatype_id ) );
        ( *mInclusiveValues )[ i ]->fromStream( connection );
    }
    mExclusiveValues->resize( num_entries );
    for ( size_t i = 0; i < num_entries; ++i )
    {
        ( *mExclusiveValues )[ i ] = selectValueOnDataType( DataType( datatype_id ) );
        ( *mExclusiveValues )[ i ]->fromStream( connection );
    }
}


CallpathTreeValuesRequest::CallpathTreeValuesRequest(
    const list_of_metrics&      metric_selections,
    const list_of_sysresources& sysres_selections,
    value_container&            inclusive_values,
    value_container&            exclusive_values )
    : mMetricSelections( metric_selections ),
    mSysresSelections( sysres_selections ),
    mInclusiveValues( &inclusive_values ),
    mExclusiveValues( &exclusive_values )
{
}


CallpathTreeValuesRequest::CallpathTreeValuesRequest()
    : mInclusiveValues( NULL ),
    mExclusiveValues( NULL )
{
}


CallpathTreeValuesRequest::~CallpathTreeValuesRequest()
{
}


NetworkRequestPtr
cube::CallpathTreeValuesRequest::create(
    const list_of_metrics&      metric_selections,
    const list_of_sysresources& sysres_selections,
    value_container&            inclusive_values,
    value_container&            exclusive_values )
{
    return NetworkRequest::Ptr( new CallpathTreeValuesRequest( metric_selections,
                                                               sysres_selections,
                                                               inclusive_values,
                                                               exclusive_values ) );
}
