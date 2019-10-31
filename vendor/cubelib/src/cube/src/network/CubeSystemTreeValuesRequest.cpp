/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016-2019                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2014-2015                                                **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  Copyright (c) 2014-2015                                                **
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
 *  @brief   Definition of the class SystemTreeValues
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeSystemTreeValuesRequest.h"

#include <cassert>
#include <string>

#include "CubeClientConnection.h"
#include "CubeCnode.h"
#include "CubeError.h"
#include "CubeIoProxy.h"
#include "CubeServerCallbackData.h"
#include "CubeServerConnection.h"
#include "CubeSysres.h"
#include "CubeTypes.h"
#include "CubeValue.h"
#include "CubeValues.h"

using namespace std;
using namespace cube;

SystemTreeValuesRequest::~SystemTreeValuesRequest()
{
}


NetworkRequestPtr
SystemTreeValuesRequest::create( const list_of_metrics& metric_selections,
                                 const list_of_cnodes&  cnode_selections,
                                 value_container&       inclusive_values,
                                 value_container&       exclusive_values )
{
    return NetworkRequest::Ptr( new SystemTreeValuesRequest( metric_selections,
                                                             cnode_selections,
                                                             inclusive_values,
                                                             exclusive_values ) );
}


NetworkRequestPtr
SystemTreeValuesRequest::create( const list_of_metrics& metric_selections,
                                 const list_of_regions& region_selections,
                                 value_container&       inclusive_values,
                                 value_container&       exclusive_values )
{
    return NetworkRequest::Ptr( new SystemTreeValuesRequest( metric_selections,
                                                             region_selections,
                                                             inclusive_values,
                                                             exclusive_values ) );
}


NetworkRequestPtr
SystemTreeValuesRequest::create()
{
    return NetworkRequest::Ptr( new SystemTreeValuesRequest() );
}


string
SystemTreeValuesRequest::getName() const
{
    return "SystemTreeValues";
}


NetworkRequest::id_t
SystemTreeValuesRequest::getId() const
{
    return SYSTEM_TREE_VALUES_REQUEST;
}


void
SystemTreeValuesRequest::sendRequestPayload( ClientConnection& connection,
                                             ClientCallbackData* ) const
{
    #if defined( CUBE_PROXY_DEBUG )
    cerr << "Metric selections:" << endl;
    for ( list_of_metrics::const_iterator it = mMetricSelections.begin();
          it != mMetricSelections.end(); ++it )
    {
        cerr << " id=" << it->first->get_uniq_name()
             << " kind="
             << ( it->second == CUBE_CALCULATE_EXCLUSIVE ? "EX" : "IN" )
             << endl;
    }
    cerr << "Cnode selections:" << endl;
    for ( list_of_cnodes::const_iterator it = mCnodeSelections.begin();
          it != mCnodeSelections.end(); ++it )
    {
        cerr << " id=" << it->first->get_id()
             << " kind="
             << ( it->second == CUBE_CALCULATE_EXCLUSIVE ? "EX" : "IN" )
             << endl;
    }
    cerr << "Region selections:" << endl;
    for ( list_of_regions::const_iterator it = mRegionSelections.begin();
          it != mRegionSelections.end(); ++it )
    {
        cerr << " id=" << it->first->get_name()
             << " kind="
             << ( it->second == CUBE_CALCULATE_EXCLUSIVE ? "EX" : "IN" )
             << endl;
    }
    #endif

    // Send Metric selections
    connection << uint32_t( mMetricSelections.size() );
    for ( size_t i = 0; i < mMetricSelections.size(); ++i )
    {
        connection << mMetricSelections[ i ].first->get_id();
        connection << uint8_t( mMetricSelections[ i ].second );
    }

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
        connection << uint8_t( mRegionSelections[ i ].first->is_subroutines() );
    }
}


void
SystemTreeValuesRequest::receiveRequestPayload( ServerConnection&   connection,
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
        uint8_t is_sub  = connection.get< uint8_t >();
        if ( is_sub )
        {
            region->set_as_subroutines();
        }

        mRegionSelections.push_back( make_pair( region,
                                                CalculationFlavour( flavour ) ) );
    }
}


void
SystemTreeValuesRequest::processRequest( ServerCallbackData* data )
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
            data->getCube()->getSystemTreeValues( mMetricSelections,
                                                  mCnodeSelections,
                                                  *mInclusiveValues,
                                                  *mExclusiveValues );
        }
        else
        {
            data->getCube()->getSystemTreeValues( mMetricSelections,
                                                  mRegionSelections,
                                                  *mInclusiveValues,
                                                  *mExclusiveValues );

            // reset potential is_subroutines() flags
            for ( list_of_regions::const_iterator it = mRegionSelections.begin();
                  it != mRegionSelections.end(); ++it )
            {
                it->first->unset_as_subroutines();
            }
        }
    }
    catch ( const std::exception& e )
    {
        throw RecoverableNetworkError( e.what() );
    }
}


void
SystemTreeValuesRequest::sendResponsePayload( ServerConnection& connection,
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
SystemTreeValuesRequest::receiveResponsePayload( ClientConnection& connection,
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


SystemTreeValuesRequest::SystemTreeValuesRequest(
    const list_of_metrics& metric_selections,
    const list_of_cnodes&  cnode_selections,
    value_container&       inclusive_values,
    value_container&       exclusive_values )
    : mMetricSelections( metric_selections ),
    mCnodeSelections( cnode_selections ),
    mInclusiveValues( &inclusive_values ),
    mExclusiveValues( &exclusive_values )
{
}


SystemTreeValuesRequest::SystemTreeValuesRequest(
    const list_of_metrics& metric_selections,
    const list_of_regions& region_selections,
    value_container&       inclusive_values,
    value_container&       exclusive_values )
    : mMetricSelections( metric_selections ),
    mRegionSelections( region_selections ),
    mInclusiveValues( &inclusive_values ),
    mExclusiveValues( &exclusive_values )
{
    #if defined( CUBE_PROXY_DEBUG )
    cerr << "Metric selections:" << endl;
    for ( list_of_metrics::const_iterator it = metric_selections.begin();
          it != metric_selections.end(); ++it )
    {
        cerr << " id=" << it->first->get_uniq_name()
             << " kind="
             << ( it->second == CUBE_CALCULATE_EXCLUSIVE ? "EX" : "IN" )
             << endl;
    }
    cerr << "Region selections:" << endl;
    for ( list_of_regions::const_iterator it = region_selections.begin();
          it != region_selections.end(); ++it )
    {
        cerr << " id=" << it->first->get_name()
             << " kind="
             << ( it->second == CUBE_CALCULATE_EXCLUSIVE ? "EX" : "IN" )
             << endl;
    }
    #endif
}


SystemTreeValuesRequest::SystemTreeValuesRequest()
    : mInclusiveValues( NULL ),
    mExclusiveValues( NULL )
{
}
