/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2018-2019                                                **
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
 *  @brief   Implementation for the class cube::CubeNetworkProxy
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeNetworkProxy.h"

#if defined( CUBE_PROXY_DEBUG )
    #include <iostream>
#endif

#include <stdexcept>
#include <string>
#include <vector>

#include "CubeCallpathSubtreeValuesRequest.h"
#include "CubeCallpathTreeValuesRequest.h"
#include "CubeClientCallbackData.h"
#include "CubeClientConnection.h"
#include "CubeCloseCubeRequest.h"
#include "CubeDefineMetricRequest.h"
#include "CubeError.h"
#include "CubeFlatTreeValuesRequest.h"
#include "CubeMetricSubtreeValuesRequest.h"
#include "CubeMetricTreeValuesRequest.h"
#include "CubeOpenCubeRequest.h"
#include "CubePL1Driver.h"
#include "CubePL2MemoryManager.h"
#include "CubeSaveCubeRequest.h"
#include "CubeSocket.h"
#include "CubeSystemTreeValuesRequest.h"


using namespace std;
using namespace cube;

/// Convenience macro to avoid code duplication
///
#define EXECUTE_REQUEST( request )                 \
    try                                          \
    {                                            \
        this->executeRequest( request );           \
    }                                            \
    catch ( const UnrecoverableNetworkError& err ) \
    {                                            \
        throw FatalError( err.what() );            \
    }

CubeNetworkProxy::CubeNetworkProxy( const string& url_string )
    : CubeProxy(),
    mConnection( ClientConnection::create( Socket::create(),
                                           url_string ) ),
    mCbData( new ClientCallbackData() )
{
    this->mPLDriver        = new cubeplparser::CubePL1Driver( NULL );
    this->mPLMemoryManager = new CubePL2MemoryManager();

    mCbData->setCube( this );
}


CubeNetworkProxy::~CubeNetworkProxy()
{
}


void
CubeNetworkProxy::openReport()
{
    NetworkRequestPtr OpenRequest = OpenCubeRequest::create( getUrl().getPath() );

    EXECUTE_REQUEST( OpenRequest );
}


void
CubeNetworkProxy::openReport( const string& filename )
{
    setUrlPath( filename );

    openReport();
}


void
CubeNetworkProxy::closeReport()
{
    NetworkRequestPtr CloseRequest = CloseCubeRequest::create();

    EXECUTE_REQUEST( CloseRequest );
    setInitialized( false );
}


Metric*
CubeNetworkProxy::defineMetric( const string&   disp_name,
                                const string&   uniq_name,
                                const string&   dtype,
                                const string&   uom,
                                const string&   val,
                                const string&   url,
                                const string&   descr,
                                Metric*         parent,
                                TypeOfMetric    type_of_metric,
                                const string&   expression,
                                const string&   init_expression,
                                const string&   aggr_plus_expression,
                                const string&   aggr_minus_expression,
                                const string&   aggr_aggr_expression,
                                const bool      threadwise,
                                VizTypeOfMetric visibility )
{
    Metric* metric = Metric::create( disp_name,
                                     uniq_name,
                                     dtype,
                                     uom,
                                     val,
                                     url,
                                     descr,
                                     NULL,
                                     parent,
                                     type_of_metric,
                                     mMetrics.size(),
                                     expression,
                                     init_expression,
                                     aggr_plus_expression,
                                     aggr_minus_expression,
                                     aggr_aggr_expression,
                                     threadwise,
                                     visibility );

    if ( metric )
    {
        NetworkRequest::Ptr request = DefineMetricRequest::create( *metric );
        try
        {
            executeRequest( request );
        }
        catch ( NetworkError& theError )
        {
            delete metric;

            return NULL;
        }
    }

    Metric* defined_metric = this->getMetric( metric->get_uniq_name() );
    if ( !defined_metric )
    {
        delete metric;

        throw FatalError( "New metric not found in metric data after creation." );
    }

    #if defined( CUBE_PROXY_DEBUG )
    cerr << *defined_metric << endl;
    #endif

    delete metric;

    return defined_metric;
}


Metric*
CubeNetworkProxy::getMetric( const string& uniq_name ) const
{
    map< string, Metric* >::const_iterator it = mMetricDict.find( uniq_name );
    if ( it != mMetricDict.end() )
    {
        return it->second;
    }
    else
    {
        return NULL;
    }
}


void
CubeNetworkProxy::defineAttribute( const string& key,
                                   const string& value )
{
    mAttributes[ key ] = value;
}


string
CubeNetworkProxy::getAttribute( const string& key ) const
{
    map< string, string >::const_iterator it = mAttributes.find( key );
    if ( it != mAttributes.end() )
    {
        return it->second;
    }

    return "";
}


void
CubeNetworkProxy::defineMirror( const string& url )
{
    mMirrors.push_back( url );
}


const vector< Metric* >&
CubeNetworkProxy::getMetrics() const
{
    return mMetrics;
}


const vector< Cnode* >&
CubeNetworkProxy::getCnodes() const
{
    return mCnodes;
}


void
CubeNetworkProxy::saveCopy( const string& filename )
{
    NetworkRequest::Ptr request = SaveCubeRequest::create( filename );

    EXECUTE_REQUEST( request );
}


const vector< Location* >&
CubeNetworkProxy::getLocations() const
{
    return mLocations;
}


void
CubeNetworkProxy::getMetricTreeValues(
    const list_of_cnodes&       cnode_selections,
    const list_of_sysresources& sysres_selections,
    vector< Value* >&           inclusive_values,
    vector< Value* >&           exclusive_values )
{
    NetworkRequest::Ptr request =
        MetricTreeValuesRequest::create( cnode_selections,
                                         sysres_selections,
                                         inclusive_values,
                                         exclusive_values );

    EXECUTE_REQUEST( request );
}


void
CubeNetworkProxy::getMetricTreeValues(
    const list_of_regions&      region_selections,
    const list_of_sysresources& sysres_selections,
    vector< Value* >&           inclusive_values,
    vector< Value* >&           exclusive_values )
{
    NetworkRequest::Ptr request =
        MetricTreeValuesRequest::create( region_selections,
                                         sysres_selections,
                                         inclusive_values,
                                         exclusive_values );

    EXECUTE_REQUEST( request );
}


void
CubeNetworkProxy::getMetricSubtreeValues(
    const list_of_cnodes&       cnode_selections,
    const list_of_sysresources& sysres_selections,
    Metric&                     root_metric,
    size_t                      depth,
    IdIndexMap&                 metric_id_indices,
    value_container*            inclusive_values,
    value_container*            exclusive_values )
{
    NetworkRequest::Ptr request =
        MetricSubtreeValuesRequest::create( cnode_selections,
                                            sysres_selections,
                                            root_metric,
                                            depth,
                                            metric_id_indices,
                                            inclusive_values,
                                            exclusive_values );

    EXECUTE_REQUEST( request );
}


void
CubeNetworkProxy::getMetricSubtreeValues(
    const list_of_regions&      region_selections,
    const list_of_sysresources& sysres_selections,
    Metric&                     root_metric,
    size_t                      depth,
    IdIndexMap&                 metric_id_indices,
    value_container*            inclusive_values,
    value_container*            exclusive_values )
{
    NetworkRequest::Ptr request =
        MetricSubtreeValuesRequest::create( region_selections,
                                            sysres_selections,
                                            root_metric,
                                            depth,
                                            metric_id_indices,
                                            inclusive_values,
                                            exclusive_values );

    EXECUTE_REQUEST( request );
}


void
CubeNetworkProxy::getCallpathTreeValues(
    const list_of_metrics&      metric_selections,
    const list_of_sysresources& sysres_selections,
    vector< Value* >&           inclusive_values,
    vector< Value* >&           exclusive_values )
{
    NetworkRequest::Ptr request =
        CallpathTreeValuesRequest::create( metric_selections,
                                           sysres_selections,
                                           inclusive_values,
                                           exclusive_values );

    EXECUTE_REQUEST( request );
}


void
CubeNetworkProxy::getCallpathSubtreeValues(
    const list_of_metrics&      metric_selections,
    const list_of_sysresources& sysres_selections,
    Cnode&                      root_cnode,
    size_t                      depth,
    IdIndexMap&                 cnode_id_indices,
    value_container*            inclusive_values,
    value_container*            exclusive_values )
{
    NetworkRequest::Ptr request =
        CallpathSubtreeValuesRequest::create( metric_selections,
                                              sysres_selections,
                                              root_cnode,
                                              depth,
                                              cnode_id_indices,
                                              inclusive_values,
                                              exclusive_values );

    EXECUTE_REQUEST( request );
}


void
CubeNetworkProxy::getFlatTreeValues(
    const list_of_metrics&      metric_selections,
    const list_of_sysresources& sysres_selections,
    vector< Value* >&           inclusive_values,
    vector< Value* >&           exclusive_values,
    vector< Value* >&           difference_values )
{
    NetworkRequest::Ptr request =
        FlatTreeValuesRequest::create( metric_selections,
                                       sysres_selections,
                                       inclusive_values,
                                       exclusive_values,
                                       difference_values );

    EXECUTE_REQUEST( request );
}


void
CubeNetworkProxy::getSystemTreeValues( const list_of_metrics& metric_selections,
                                       const list_of_cnodes&  cnode_selections,
                                       vector< Value* >&      inclusive_values,
                                       vector< Value* >&      exclusive_values )
{
    NetworkRequest::Ptr request =
        SystemTreeValuesRequest::create( metric_selections,
                                         cnode_selections,
                                         inclusive_values,
                                         exclusive_values );

    EXECUTE_REQUEST( request );
}


void
CubeNetworkProxy::getSystemTreeValues( const list_of_metrics& metric_selections,
                                       const list_of_regions& region_selections,
                                       vector< Value* >&      inclusive_values,
                                       vector< Value* >&      exclusive_values )
{
    NetworkRequest::Ptr request =
        SystemTreeValuesRequest::create( metric_selections,
                                         region_selections,
                                         inclusive_values,
                                         exclusive_values );

    EXECUTE_REQUEST( request );
}


const vector< cube::Region* >&
CubeNetworkProxy::getRegions() const
{
    return mRegions;
}


void
CubeNetworkProxy::rerootCnode( Cnode& )
{
    /// @todo Reroot Cnode request!
    throw FatalError( "Function not implemented for remote files." );
}


void
CubeNetworkProxy::pruneCnode( Cnode& )
{
    /// @todo prune Cnode request!
    throw FatalError( "Function not implemented for remote files." );
}


void
CubeNetworkProxy::setCnodeAsLeaf( Cnode& )
{
    /// @todo cnode2leaf request
    throw FatalError( "Function not implemented for remote files." );
}


const vector< Cnode* >&
CubeNetworkProxy::getRootCnodes() const
{
    return mRootCnodes;
}


const vector< Metric* >&
CubeNetworkProxy::getRootMetrics() const
{
    return mRootMetrics;
}


void
CubeNetworkProxy::addCartesian( Cartesian& cartesian )
{
    this->mCartesians.push_back( &cartesian );
}


const std::vector< Cartesian* >&
CubeNetworkProxy::getCartesians() const
{
    return this->mCartesians;
}


const std::map< std::string, std::string >&
CubeNetworkProxy::getAttributes() const
{
    return mAttributes;
}


const std::vector< std::string >&
CubeNetworkProxy::getMirrors()
{
    return mMirrors;
}


void
CubeNetworkProxy::setMemoryStrategy( CubeStrategy )
{
    /// @todo Do we need to forward this to the server?
}


const vector< Metric* >&
CubeNetworkProxy::getGhostMetrics() const
{
    return mGhostMetrics;
}


const Cartesian&
CubeNetworkProxy::getCartesian( size_t cartesianId ) const
{
    if ( cartesianId >= mCartesians.size() )
    {
        throw std::out_of_range( "Cartesian topology ID is out of range." );
    }

    return *mCartesians[ cartesianId ];
}


size_t
CubeNetworkProxy::getNumCartesians() const
{
    return mCartesians.size();
}


const vector< LocationGroup* >&
CubeNetworkProxy::getLocationGroups() const
{
    return mLocationGroups;
}


const vector< SystemTreeNode* >&
CubeNetworkProxy::getSystemTreeNodes() const
{
    return mSystemTreeNodes;
}


const vector< SystemTreeNode* >&
CubeNetworkProxy::getRootSystemTreeNodes() const
{
    return mRootSystemTreeNodes;
}


void
CubeNetworkProxy::addMetric( Metric& metric )
{
    mMetrics.push_back( &metric );
    if ( metric.isGhost() )
    {
        mGhostMetrics.push_back( &metric );
    }
    if ( metric.get_parent() == NULL )
    {
        mRootMetrics.push_back( &metric );
    }
    mMetricDict[ metric.get_uniq_name() ] = &metric;
}


void
CubeNetworkProxy::addCnode( Cnode& cnode )
{
    mCnodes.push_back( &cnode );
    if ( cnode.get_parent() == NULL )
    {
        mRootCnodes.push_back( &cnode );
    }
}


void
CubeNetworkProxy::addRegion( Region& region )
{
    mRegions.push_back( &region );
}


void
CubeNetworkProxy::addLocation( Location& location )
{
    mLocations.push_back( &location );
    mSystemResources.push_back( &location );
}


void
CubeNetworkProxy::addLocationGroup( LocationGroup& group )
{
    mLocationGroups.push_back( &group );
    mSystemResources.push_back( &group );
}


void
CubeNetworkProxy::addSystemTreeNode( SystemTreeNode& systemTreeNode )
{
    mSystemTreeNodes.push_back( &systemTreeNode );
    if ( systemTreeNode.get_parent() == NULL )
    {
        mRootSystemTreeNodes.push_back( &systemTreeNode );
    }
    mSystemResources.push_back( &systemTreeNode );
}


const std::vector< Sysres* >&
CubeNetworkProxy::getSystemResources() const
{
    return mSystemResources;
}


void
CubeNetworkProxy::executeRequest( NetworkRequest::Ptr request )
{
    mOperationProgress.start_step( 0., 1. );
    mOperationProgress.progress_step( "Sending request..." );
    request->sendRequest( *mConnection, mCbData );
    mOperationProgress.progress_step( "Receiving response..." );
    request->receiveResponse( *mConnection, mCbData );
    mOperationProgress.finish_step( "Finished" );
}


void
CubeNetworkProxy::addSystemResource( Sysres& systemResource )
{
    switch ( systemResource.get_kind() )
    {
        case CUBE_MACHINE:
        case CUBE_NODE:
        case CUBE_SYSTEM_TREE_NODE:
            addSystemTreeNode( *static_cast< SystemTreeNode* >( &systemResource ) );
            break;

        case CUBE_PROCESS:
        case CUBE_LOCATION_GROUP:
            addLocationGroup( *static_cast< LocationGroup* >( &systemResource ) );
            break;

        case CUBE_THREAD:
        case CUBE_LOCATION:
            addLocation( *static_cast< Location* >( &systemResource ) );
            break;

        case CUBE_UNKNOWN:
        default:
            throw UnrecoverableNetworkError(
                      "Cannot create unknown system resource kind." );
    }
}


const ProgressStatus&
CubeNetworkProxy::getOperationProgressStatus() const
{
    return *mOperationProgress.get_progress_status();
}


bool
CubeNetworkProxy::hasCubePlDriver() const
{
    return mPLDriver != NULL;
}


cubeplparser::CubePLDriver&
CubeNetworkProxy::getCubePlDriver()
{
    if ( !hasCubePlDriver() )
    {
        throw FatalError( "CubePL driver not set." );
    }

    return *mPLDriver;
}


bool
CubeNetworkProxy::hasCubePlMemoryManager() const
{
    return mPLMemoryManager != NULL;
}


CubePLMemoryManager&
CubeNetworkProxy::getCubePlMemoryManager()
{
    if ( hasCubePlMemoryManager() )
    {
        throw FatalError( "CubePL Memory Manager not set." );
    }

    return *mPLMemoryManager;
}

bool
cube::CubeNetworkProxy::isCubePlExpressionValid( std::string& _to_test, std::string& error_message )
{
    return mPLDriver->test( _to_test, error_message );
}
