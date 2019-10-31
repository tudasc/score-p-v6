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
 *  @brief   Definition of the class cube::DefineMetricRequest.
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeDefineMetricRequest.h"

#include <cassert>
#include <string>

#include "CubeClientCallbackData.h"
#include "CubeClientConnection.h"
#include "CubeIoProxy.h"
#include "CubeNetworkProxy.h"
#include "CubeNetworkRequest.h"
#include "CubeSerializable.h"
#include "CubeSerializablesFactory.h"
#include "CubeServerCallbackData.h"
#include "CubeServerConnection.h"

using namespace std;
using namespace cube;

DefineMetricRequest::~DefineMetricRequest()
{
}


NetworkRequestPtr
DefineMetricRequest::create( Metric& metric )
{
    return NetworkRequest::Ptr( new DefineMetricRequest( metric ) );
}


string
DefineMetricRequest::getName() const
{
    return "DefineMetric";
}


NetworkRequest::id_t
DefineMetricRequest::getId() const
{
    return DEFINE_METRIC_REQUEST;
}


void
DefineMetricRequest::sendRequestPayload( ClientConnection& connection,
                                         ClientCallbackData* ) const
{
    /// @pre mMetric needs to be set.
    assert( mMetric );

    mMetric->serialize( connection );

    #if defined( CUBE_PROXY_DEBUG )
    cerr << *mMetric << endl;
    #endif
}


void
DefineMetricRequest::receiveRequestPayload( ServerConnection&   connection,
                                            ServerCallbackData* data )
{
    /// @pre CallbackData needs to be valid.
    assert( data );

    /// @pre Cube must be set.
    assert( data->getCube() );
    CubeProxy& cubeProxy = *data->getCube();

    try
    {
        // define dummy Metric from connection stream
        mMetric = Metric::create( connection, cubeProxy );
    }
    catch ( const std::exception& e )
    {
        throw UnrecoverableNetworkError( e.what() );
    }
}


void
DefineMetricRequest::processRequest( ServerCallbackData* data )
{
    /// @pre CallbackData needs to be valid.
    assert( data );

    /// @pre Cube must be set.
    assert( data->getCube() );
    CubeProxy& cubeProxy = *data->getCube();

    // define dummy Metric from connection stream
    if ( !mMetric )
    {
        throw RecoverableNetworkError( "Metric definition failed." );
    }

    Metric* dummy = mMetric;
    mMetric = NULL;

    try
    {
        mMetric = cubeProxy.defineMetric( dummy->get_disp_name(),
                                          dummy->get_uniq_name(),
                                          dummy->get_dtype(),
                                          dummy->get_uom(),
                                          dummy->get_val(),
                                          dummy->get_url(),
                                          dummy->get_descr(),
                                          dummy->get_parent(),
                                          dummy->get_type_of_metric(),
                                          dummy->get_expression(),
                                          dummy->get_init_expression(),
                                          dummy->get_aggr_plus_expression(),
                                          dummy->get_aggr_minus_expression(),
                                          dummy->get_aggr_aggr_expression(),
                                          dummy->isRowWise(),
                                          dummy->isGhost() ? CUBE_METRIC_GHOST : CUBE_METRIC_NORMAL );
        delete dummy;
    }
    catch ( const std::exception& e )
    {
        throw RecoverableNetworkError( e.what() );
    }
    #if defined( CUBE_PROXY_DEBUG )
    cerr << *mMetric << endl;
    #endif
}


void
DefineMetricRequest::sendResponsePayload( ServerConnection& connection,
                                          ServerCallbackData* ) const
{
    assert( mMetric );
    mMetric->serialize( connection );
}


void
DefineMetricRequest::receiveResponsePayload( ClientConnection&   connection,
                                             ClientCallbackData* data )
{
    assert( data );
    CubeNetworkProxy& cubeProxy = *data->getCube();

    Serializable* object =
        MySerializablesFactory::getInstance().create( connection,
                                                      cubeProxy );
    assert( object );
    Metric* metric = dynamic_cast< Metric* >( object );
    assert( metric );
    assert( metric->get_id() == mMetric->get_id() );
    cubeProxy.addMetric( *metric );
}


NetworkRequestPtr
DefineMetricRequest::create()
{
    return NetworkRequest::Ptr( new DefineMetricRequest() );
}


DefineMetricRequest::DefineMetricRequest( Metric& metric )
    : mMetric( &metric )
{
}


DefineMetricRequest::DefineMetricRequest()
    : mMetric( NULL )
{
}
