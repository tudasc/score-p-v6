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
 *  @ingroup CUBE_lib.base
 *  @brief   Definition of the class cube::CubeIoProxy
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeIoProxy.h"

#include <cassert>
#include <iostream>

#include "Cube.h"
#include "CubeCartesian.h"
#include "CubeIdIndexMap.h"
#include "CubeIdentObject.h"
#include "CubeServices.h"
#include "CubeTypes.h"

using namespace std;
using namespace cube;

#undef CUBE_PROXY_ROWWISE

namespace
{
/**
 * @brief Select reading flavour based on metric type
 * @param metricType
 * @return Recommended reading flavour
 */
cube::CalculationFlavour
selectReadingFlavour( cube::TypeOfMetric metricType )
{
    switch ( metricType )
    {
        case cube::CUBE_METRIC_EXCLUSIVE:
        case cube::CUBE_METRIC_PREDERIVED_EXCLUSIVE:
        case cube::CUBE_METRIC_POSTDERIVED:

            return cube::CUBE_CALCULATE_EXCLUSIVE;

        case cube::CUBE_METRIC_INCLUSIVE:
        case cube::CUBE_METRIC_PREDERIVED_INCLUSIVE:

            return cube::CUBE_CALCULATE_INCLUSIVE;

        default:

            return cube::CUBE_CALCULATE_EXCLUSIVE;
    }
}


bool
hasPostDerivedMetrics( const cube::list_of_metrics& metrics )
{
    for ( cube::list_of_metrics::const_iterator it = metrics.begin();
          it != metrics.end(); ++it )
    {
        if ( it->first->get_type_of_metric() == cube::CUBE_METRIC_POSTDERIVED )
        {
            return true;
        }
    }

    return false;
}

#if defined( CUBE_PROXY_DEBUG )
void
printValues( const char*              prefix,
             cube::id_t               id,
             double                   inclusive,
             double                   exclusive,
             cube::CalculationFlavour flavour )
{
    cerr << prefix << " " << id
         << " in=" << inclusive
         << " ex=" << exclusive
         << " flavor="
         << ( flavour == cube::CUBE_CALCULATE_EXCLUSIVE ? "EX" : "IN" )
         << endl;
}
#endif

/// @brief Enumerate all ids with their indices in depth-first order
///
/// @param[in]  root_vertex     Root vertex of the subtree to process
/// @param[in]  depth           Depth of the subtree to process
/// @param[out] vertex_id_indices   Associative array with id to index mapping
///
void
createIdIndexMapping( cube::Vertex& root_vertex,
                      size_t depth,
                      cube::IdIndexMap& vertex_id_indices,
                      std::map<size_t, cube::Vertex*>& vertices
                      )
{
    vertex_id_indices.insert( root_vertex.get_id(), vertex_id_indices.size() );
    vertices[ root_vertex.get_id() ] = &root_vertex;
    if ( depth > 0 )
    {
        for ( vector< cube::Vertex* >::iterator it =
                  root_vertex.get_children().begin();
              it != root_vertex.get_children().end(); ++it )
        {
            {       // special case: if tree is metric tree, ignore VOID-metrics
                Metric* metric = dynamic_cast<Metric*> ( *it );
                // todo: replace with metric->isInactive, waiting for bugfix (returns false for VOID-metrics)
                if ( metric && std::strcmp( metric->get_val().c_str(), "VOID" ) == 0 )
                {
                    continue;
                }
            }

            ::createIdIndexMapping( **it,
                                    depth - 1,
                                    vertex_id_indices,
                                    vertices
                                    );
        }
    }
}
}

// --- helper functions --

ostream&
operator<<( ostream&                     os,
            const cube::list_of_metrics& selections )
{
    os << "METRIC selections {\n";
    for ( cube::list_of_metrics::const_iterator it = selections.begin();
          it != selections.end(); ++it )
    {
        os << "  \"" << it->first->get_uniq_name()
           << "\" : \""
           << ( it->second == cube::CUBE_CALCULATE_EXCLUSIVE
             ? "exclusive"
             : "inclusive" )
           << "\"\n}";
    }

    return os;
}


ostream&
operator<<( ostream&                    os,
            const cube::list_of_cnodes& selections )
{
    os << "CNODE selections {\n";
    for ( cube::list_of_cnodes::const_iterator it = selections.begin();
          it != selections.end(); ++it )
    {
        os << "  " << it->first->get_id()
           << " : \""
           << ( it->second == cube::CUBE_CALCULATE_EXCLUSIVE
             ? "exclusive"
             : "inclusive" )
           << "\"\n}";
    }

    return os;
}


ostream&
operator<<( ostream&                     os,
            const cube::list_of_regions& selections )
{
    os << "REGION selections {\n";
    for ( cube::list_of_regions::const_iterator it = selections.begin();
          it != selections.end(); ++it )
    {
        os << "  \"" << it->first->get_name()
           << "\" : \""
           << ( it->second == cube::CUBE_CALCULATE_EXCLUSIVE
             ? "exclusive"
             : "inclusive" )
           << "\"\n}";
    }

    return os;
}


ostream&
operator<<( ostream&                          os,
            const cube::list_of_sysresources& selections )
{
    os << "SYSRESOURCE selections {\n";
    for ( cube::list_of_sysresources::const_iterator it = selections.begin();
          it != selections.end(); ++it )
    {
        os << "  \"" << it->first->get_name()
           << "\" : \""
           << ( it->second == cube::CUBE_CALCULATE_EXCLUSIVE
             ? "exclusive"
             : "inclusive" )
           << "\"\n}";
    }

    return os;
}


// --- class definition

CubeIoProxy::CubeIoProxy()
    : CubeProxy(),
    mCube( new Cube() )
{
}

CubeIoProxy::CubeIoProxy( cube::Cube* cube )
    : CubeProxy(),
    mCube( cube )
{
}


CubeIoProxy::~CubeIoProxy()
{
    delete mCube;
}


void
CubeIoProxy::openReport()
{
    mCube->openCubeReport( getUrl().getPath() );

    defineAttribute( "cubename", mCube->get_cubename() );
    defineAttribute( "metrictree title", mCube->get_metrics_title() );
    defineAttribute( "calltree title", mCube->get_calltree_title() );
    defineAttribute( "flattree title", "Regions" );
    defineAttribute( "systemtree title", mCube->get_systemtree_title() );
}


void
CubeIoProxy::openReport( const string& filename )
{
    setUrlPath( filename );

    openReport();
}


void
CubeIoProxy::closeReport()
{
    mCube->closeCubeReport();
    setInitialized( false );
}


Metric*
CubeIoProxy::defineMetric( const string&   disp_name,
                           const string&   uniq_name,
                           const string&   dtype,
                           const string&   unit_of_measure,
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
                           const bool      row_wise,
                           VizTypeOfMetric visibility )
{
    Metric* metric = mCube->def_met( disp_name,
                                     uniq_name,
                                     dtype,
                                     unit_of_measure,
                                     val,
                                     url,
                                     descr,
                                     parent,
                                     type_of_metric,
                                     expression,
                                     init_expression,
                                     aggr_plus_expression,
                                     aggr_minus_expression,
                                     aggr_aggr_expression,
                                     row_wise,
                                     visibility );
    #if defined( CUBE_PROXY_DEBUG )
    cerr << *metric << endl;
    #endif

    return metric;
}


Metric*
CubeIoProxy::getMetric( const string& uniq_name ) const
{
    return mCube->get_met( uniq_name );
}


void
CubeIoProxy::defineAttribute( const string& key,
                              const string& value )
{
    mCube->def_attr( key, value );
}


string
CubeIoProxy::getAttribute( const string& key ) const
{
    return mCube->get_attr( key );
}


const vector< Metric* >&
CubeIoProxy::getMetrics() const
{
    return mCube->get_metv();
}


const vector< Cnode* >&
CubeIoProxy::getCnodes() const
{
    return mCube->get_cnodev();
}


const vector< Location* >&
CubeIoProxy::getLocations() const
{
    return mCube->get_locationv();
}


void
CubeIoProxy::getMetricTreeValues( const list_of_regions&      region_selections,
                                  const list_of_sysresources& sysres_selections,
                                  vector< Value* >&           inclusive_values,
                                  vector< Value* >&           exclusive_values )
{
    // CalculationFlavour   reading_flavour = CUBE_CALCULATE_INCLUSIVE;
    const vector< Metric* > metrics     = mCube->get_metv();
    size_t                  num_metrics = metrics.size();

    deleteAndResize( exclusive_values, num_metrics );
    deleteAndResize( inclusive_values, num_metrics );

    // @todo Parallelize assignment loop.
    for ( size_t i = 0; i < num_metrics; ++i )
    {
        // read inclusive values directly from cube
        inclusive_values[ i ] = mCube->get_sev_adv( region_selections,
                                                    sysres_selections,
                                                    metrics[ i ],
                                                    CUBE_CALCULATE_INCLUSIVE );

        // initialize exclusive values with inclusive values
        exclusive_values[ i ] = inclusive_values[ i ]->copy();

        #if defined( CUBE_PROXY_DEBUG )
        ::printValues( "Reading inclusive metric",
                       metrics[ i ]->get_id(),
                       inclusive_values[ i ]->getDouble(),
                       exclusive_values[ i ]->getDouble(),
                       CUBE_CALCULATE_INCLUSIVE );
        #endif
    }

    // Calculate exclusive values
    for ( size_t i = num_metrics - 1; i < num_metrics; --i )
    {
        Metric* metric_parent = metrics[ i ]->get_parent();

        // if current metric has a parent, subtract metrics's inclusive value
        // from its parents inclusive value
        if ( metric_parent )
        {
            *exclusive_values[ metric_parent->get_id() ] -=
                inclusive_values[ i ];
        }
        #if defined( CUBE_PROXY_DEBUG )
        ::printValues( "Computing exclusive metric",
                       metrics[ i ]->get_id(),
                       inclusive_values[ i ]->getDouble(),
                       exclusive_values[ i ]->getDouble(),
                       CUBE_CALCULATE_INCLUSIVE );
        #endif
    }
}


void
CubeIoProxy::getCallpathTreeValues(
    const list_of_metrics&      metric_selections,
    const list_of_sysresources& sysres_selections,
    vector< Value* >&           inclusive_values,
    vector< Value* >&           exclusive_values )
{
    CalculationFlavour     reading_flavour    = CUBE_CALCULATE_INCLUSIVE;
    const vector< Cnode* > cnodes             = mCube->get_cnodev();
    size_t                 num_cnodes         = cnodes.size();
    bool                   compute_complement = ::hasPostDerivedMetrics(
        metric_selections ) ? false : true;

    deleteAndResize( exclusive_values, num_cnodes );
    deleteAndResize( inclusive_values, num_cnodes );

    // check which values to read and which to compute
    // Current heuristic is to take the storage type of the first selected metric
    if ( metric_selections.size() > 0 )
    {
        reading_flavour = ::selectReadingFlavour( metric_selections.at(
                                                      0 ).first->get_type_of_metric() );
    }

    // @todo Parallelize assignment loop.
    for ( size_t i = 0; i < num_cnodes; ++i )
    {
        // read exclusive values directly from cube
        exclusive_values[ i ] = mCube->get_sev_adv( metric_selections,
                                                    sysres_selections,
                                                    cnodes[ i ],
                                                    reading_flavour );

        // initialize inclusive values with exclusive values
        if ( compute_complement )
        {
            #if defined( CUBE_PROXY_DEBUG )
            cerr << "Computing inclusive values" << endl;
            #endif
            inclusive_values[ i ] = exclusive_values[ i ]->copy();
        }
        else
        {
            #if defined( CUBE_PROXY_DEBUG )
            cerr << "Reading inclusive values" << endl;
            #endif
            inclusive_values[ i ] = mCube->get_sev_adv( metric_selections,
                                                        sysres_selections,
                                                        cnodes[ i ],
                                                        CUBE_CALCULATE_INCLUSIVE );
        }

        #if defined( CUBE_PROXY_DEBUG )
        ::printValues( "Callpath values",
                       cnodes[ i ]->get_id(),
                       inclusive_values[ i ]->getDouble(),
                       exclusive_values[ i ]->getDouble(), reading_flavour );
        #endif
    }

    if ( compute_complement )
    {
        if ( reading_flavour == CUBE_CALCULATE_EXCLUSIVE )
        {
            for ( size_t i = num_cnodes - 1; i < num_cnodes; --i )
            {
                Cnode* cnode_parent = cnodes[ i ]->get_parent();

                // if current cnode has a parent, add cnode's inclusive value
                // to its parents inclusive value
                if ( cnode_parent )
                {
                    *inclusive_values[ cnode_parent->get_id() ] +=
                        inclusive_values[ i ];
                }
                #if defined( CUBE_PROXY_DEBUG )
                ::printValues( "Computing inclusive callpath",
                               cnodes[ i ]->get_id(),
                               inclusive_values[ i ]->getDouble(),
                               exclusive_values[ i ]->getDouble(),
                               reading_flavour );
                #endif
            }
        }
        else
        {
            for ( size_t i = num_cnodes - 1; i < num_cnodes; --i )
            {
                Cnode* cnode_parent = cnodes[ i ]->get_parent();

                // if current cnode has a parent, subtract cnode's inclusive
                // value from its parents inclusive value
                if ( cnode_parent )
                {
                    *exclusive_values[ cnode_parent->get_id() ] -=
                        inclusive_values[ i ];
                }
                #if defined( CUBE_PROXY_DEBUG )
                ::printValues( "Computing exclusive callpath",
                               cnodes[ i ]->get_id(),
                               inclusive_values[ i ]->getDouble(),
                               exclusive_values[ i ]->getDouble(),
                               reading_flavour );
                #endif
            }
        }
    }
}

void
CubeIoProxy::getCallpathSubtreeValues(
    const list_of_metrics&      metric_selections,
    const list_of_sysresources& sysres_selections,
    Cnode&                      root_cnode,
    size_t                      depth,
    IdIndexMap&                 cnode_id_indices,
    value_container*            inclusive_values,
    value_container*            exclusive_values )
{
    std::map<size_t, cube::Vertex*> cnodes;
    // enumerate metrics
    cnode_id_indices.clear();
    ::createIdIndexMapping( root_cnode, depth, cnode_id_indices, cnodes );
    size_t num_cnodes = cnode_id_indices.size();

    // reset value vectors
    if ( inclusive_values != CUBE_PROXY_VALUES_IGNORE )
    {
        deleteAndResize( *inclusive_values, num_cnodes );
    }

    if ( exclusive_values != CUBE_PROXY_VALUES_IGNORE )
    {
        deleteAndResize( *exclusive_values, num_cnodes );
    }

    for ( IdIndexMap::iterator idIndex = cnode_id_indices.begin();
          idIndex != cnode_id_indices.end(); ++idIndex )
    {
        if ( sysres_selections.size() == 0 ) // = all system nodes
        {
            // read inclusive values directly from cube
            ( *inclusive_values )[ idIndex.getIndex() ] =
                mCube->get_sev_adv( metric_selections,
                                    static_cast<cube::Cnode*>( cnodes[ idIndex.getId() ] ),
                                    CUBE_CALCULATE_INCLUSIVE );
            // initialize exclusive values with inclusive values
            ( *exclusive_values )[ idIndex.getIndex() ] =
                mCube->get_sev_adv( metric_selections,
                                    static_cast<cube::Cnode*>( cnodes[ idIndex.getId() ] ),
                                    CUBE_CALCULATE_EXCLUSIVE );
        }
        else
        {
            // read inclusive values directly from cube
            ( *inclusive_values )[ idIndex.getIndex() ] =
                mCube->get_sev_adv( metric_selections,
                                    sysres_selections,
                                    static_cast<cube::Cnode*>( cnodes[ idIndex.getId() ] ),
                                    CUBE_CALCULATE_INCLUSIVE );
            // initialize exclusive values with inclusive values
            ( *exclusive_values )[ idIndex.getIndex() ] =
                mCube->get_sev_adv( metric_selections,
                                    sysres_selections,
                                    static_cast<cube::Cnode*>( cnodes[ idIndex.getId() ] ),
                                    CUBE_CALCULATE_EXCLUSIVE );
        }


        #if defined( CUBE_PROXY_DEBUG )
        cerr << "Reading Cnode " << cnodes[ idIndex.getId() ]->get_id()
             << endl;
        #endif
    }
}


void
CubeIoProxy::getFlatTreeValues( const list_of_metrics&      metric_selections,
                                const list_of_sysresources& sysres_selections,
                                vector< Value* >&           inclusive_values,
                                vector< Value* >&           exclusive_values,
                                vector< Value* >&           difference_values )
{
    // Set up regions
    // @todo Check: Does this work without enumeration?
    const vector< Region* >& regions     = mCube->get_regv();
    size_t                   num_regions = regions.size();

    deleteAndResize( inclusive_values, num_regions );
    deleteAndResize( exclusive_values, num_regions );
    deleteAndResize( difference_values, num_regions );

    // @todo Parallelize assignment loop.
    for ( size_t i = 0; i < num_regions; ++i )
    {
        if ( sysres_selections.size() > 0 )
        {
            // read inclusive values directly from cube
            inclusive_values[ i ] = mCube->get_sev_adv( metric_selections,
                                                        sysres_selections,
                                                        regions[ i ],
                                                        CUBE_CALCULATE_INCLUSIVE );

            // read exclusive values directly from cube
            // @todo: Can this be improved by using additional functions like
            // get_vrsev in AggrCube?
            exclusive_values[ i ] = mCube->get_sev_adv( metric_selections,
                                                        sysres_selections,
                                                        regions[ i ],
                                                        CUBE_CALCULATE_EXCLUSIVE );
        }
        else // if system tree is right of the flat tree
        {
            // the functions above could also be called with sysres_selections = inclusive root elements, but
            // this is much slower
            inclusive_values[ i ] = mCube->get_sev_adv( metric_selections,
                                                        regions[ i ],
                                                        CUBE_CALCULATE_INCLUSIVE );

            exclusive_values[ i ] = mCube->get_sev_adv( metric_selections,
                                                        regions[ i ],
                                                        CUBE_CALCULATE_EXCLUSIVE );
        }

        // difference_values[ i ] = inclusive_values[ i ] - exclusive_values[ i ];
        if ( inclusive_values[ i ] != NULL )
        {
            difference_values[ i ] = inclusive_values[ i ]->copy();
            if ( exclusive_values[ i ] != NULL )
            {
                *difference_values[ i ] -= exclusive_values[ i ];
            }
        }

        #if defined( CUBE_PROXY_DEBUG )
        cerr << "Reading region " << regions[ i ]->get_id() << " "
             << inclusive_values[ i ]->getDouble() << " "
             << exclusive_values[ i ]->getDouble() << " "
             << difference_values[ i ]->getDouble() << " "
             << endl;
        #endif
    }
}


void
CubeIoProxy::getSystemTreeValues( const list_of_metrics& metric_selections,
                                  const list_of_cnodes&  cnode_selectionst,
                                  vector< Value* >&      inclusive_values,
                                  vector< Value* >&      exclusive_values )
{
    const vector< Sysres* > sysnodes     = mCube->get_sysv();
    size_t                  num_sysnodes = sysnodes.size();
        #if defined( CUBE_PROXY_DEBUG )
    CalculationFlavour reading_flavour = CUBE_CALCULATE_INCLUSIVE;
        #endif
    bool                useRowWiseInterface = true;
    Value**             values              = NULL;
    vector< Location* > locations           = getLocations();
    size_t              numLocations        = locations.size();

    deleteAndResize( exclusive_values, num_sysnodes );
    deleteAndResize( inclusive_values, num_sysnodes );

    list_of_cnodes cnode_selections = cnode_selectionst;
    if ( cnode_selections.size() == 0 )
    {
        // Call tree selection is the inclusive root node(s)
        const std::vector<Cnode*>& root_nodes = mCube->get_root_cnodev();
        for ( size_t i = 0; i < root_nodes.size(); i++ )
        {
            cnode_pair cp;
            cp.first  = root_nodes.at( i );
            cp.second = cube::CUBE_CALCULATE_INCLUSIVE;
            cnode_selections.push_back( cp );
        }
    }

    if ( metric_selections.size() != 0 )
    {
        #if defined( CUBE_PROXY_DEBUG )
        reading_flavour = ::selectReadingFlavour( metric_selections.at(
                                                      0 ).first->get_type_of_metric() );
            #endif
        if ( ::hasPostDerivedMetrics( metric_selections ) )
        {
            useRowWiseInterface = false;
        }
    }

    if ( useRowWiseInterface )
    {
        #if defined( CUBE_PROXY_DEBUG )
        cerr << "Using row-wise interface" << endl;
        #endif
        values = mCube->get_sevs_adv( metric_selections,
                                      cnode_selections );

        for ( size_t i = 0; i < numLocations; ++i )
        {
            exclusive_values[ locations[ i ]->get_sys_id() ] = values[ i ]->copy();
            inclusive_values[ locations[ i ]->get_sys_id() ] = values[ i ]->copy();
        }
    }

    // @todo Parallelize assignment loop.
    for ( size_t i = 0; i < num_sysnodes; ++i )
    {
        // make sure that pointers are not null
        assert( sysnodes[ i ] );

        // make sure that object ids are in the correct range
        assert( sysnodes[ i ]->get_sys_id() < exclusive_values.size() );

        if ( useRowWiseInterface )
        {
            // initialize remaining system resource entries
            if ( !exclusive_values[ sysnodes[ i ]->get_sys_id() ] )
            {
                exclusive_values[ sysnodes[ i ]->get_sys_id() ] =
                    selectValueOnType( values[ 0 ] );
            }
            if ( !inclusive_values[ sysnodes[ i ]->get_sys_id() ] )
            {
                inclusive_values[ sysnodes[ i ]->get_sys_id() ] =
                    selectValueOnType( values[ 0 ] );
            }
        }
        else
        {
            // use library call to compute exclusive values
            exclusive_values[ sysnodes[ i ]->get_sys_id() ] =
                mCube->get_sev_adv( metric_selections,
                                    cnode_selections,
                                    sysnodes[ i ],
                                    CUBE_CALCULATE_EXCLUSIVE );

            // use library call to compute inclusive values
            inclusive_values[ sysnodes[ i ]->get_sys_id() ] =
                mCube->get_sev_adv( metric_selections,
                                    cnode_selections,
                                    sysnodes[ i ],
                                    CUBE_CALCULATE_INCLUSIVE );
        }

        #if defined( CUBE_PROXY_DEBUG )
        ::printValues( "Reading system resource",
                       sysnodes[ i ]->get_sys_id(),
                       exclusive_values[ sysnodes[ i ]->get_sys_id() ]->getDouble(),
                       inclusive_values[ sysnodes[ i ]->get_sys_id() ]->getDouble(),
                       reading_flavour );
        #endif
    }

    if ( useRowWiseInterface )
    {
        services::delete_row_of_values( values, numLocations );

        for ( size_t i = num_sysnodes - 1; i < num_sysnodes; --i )
        {
            Sysres* sysnode_parent = sysnodes[ i ]->get_parent();

            // if current cnode has a parent, add cnode's inclusive value to its parents inclusive value
            if ( sysnode_parent )
            {
                assert( inclusive_values[ sysnode_parent->get_sys_id() ] );
                *inclusive_values[ sysnode_parent->get_sys_id() ] +=
                    inclusive_values[ i ];
                #if defined( CUBE_PROXY_DEBUG )
                cerr << "Adding inclusive sysres "
                     << sysnodes[ i ]->get_sys_id()
                     << " value=" << inclusive_values[ i ]->getDouble()
                     << " to parent " << sysnode_parent->get_sys_id()
                     << " value="
                     << inclusive_values[ sysnode_parent->get_sys_id() ]->
                    getDouble()
                     << endl;
                #endif
            }
        }
    }
}


void
CubeIoProxy::getSystemTreeValues( const list_of_metrics& metric_selections,
                                  const list_of_regions& region_selections,
                                  vector< Value* >&      inclusive_values,
                                  vector< Value* >&      exclusive_values )
{
    const vector< Sysres* > sysnodes     = mCube->get_sysv();
    size_t                  num_sysnodes = sysnodes.size();

    deleteAndResize( exclusive_values, num_sysnodes );
    deleteAndResize( inclusive_values, num_sysnodes );

    list_of_metrics metric_selectionst = metric_selections;

    if ( region_selections.size() > 0 ) // system tree is on the right
    {
        list_of_regions region_selectionst = region_selections;
        mCube->get_system_tree_sevs_adv( metric_selectionst, region_selectionst,
                                         inclusive_values, exclusive_values );
    }
    else
    {
        mCube->get_system_tree_sevs_adv( metric_selectionst, inclusive_values, exclusive_values );
    }
}


const vector< cube::Region* >&
CubeIoProxy::getRegions() const
{
    return mCube->get_regv();
}


void
CubeIoProxy::rerootCnode( Cnode& cnode )
{
    mCube->reroot_cnode( &cnode );
}


void
CubeIoProxy::pruneCnode( Cnode& cnode )
{
    mCube->prune_cnode( &cnode );
}


void
CubeIoProxy::setCnodeAsLeaf( Cnode& cnode )
{
    mCube->set_cnode_as_leaf( &cnode );
}


const vector< Cnode* >&
CubeIoProxy::getRootCnodes() const
{
    return mCube->get_root_cnodev();
}


const vector< Metric* >&
CubeIoProxy::getRootMetrics() const
{
    return mCube->get_root_metv();
}


const std::vector< Cartesian* >&
CubeIoProxy::getCartesians() const
{
    return mCube->get_cartv();
}


const std::map< std::string, std::string >&
CubeIoProxy::getAttributes() const
{
    return mCube->get_attrs();
}


const std::vector< std::string >&
CubeIoProxy::getMirrors()
{
    return mCube->get_mirrors();
}


const std::vector< Sysres* >&
CubeIoProxy::getSystemResources() const
{
    return mCube->get_sysv();
}


void
CubeIoProxy::getMetricSubtreeValues(
    const list_of_cnodes&       cnode_selections,
    const list_of_sysresources& sysres_selections,
    Metric&                     root_metric,
    size_t                      depth,
    IdIndexMap&                 metric_id_indices,
    value_container*            inclusive_values,
    value_container*            exclusive_values )
{
    std::map<size_t, Vertex*> metrics;
    metric_id_indices.clear();
    ::createIdIndexMapping( root_metric, depth, metric_id_indices, metrics );
    size_t num_metrics = metric_id_indices.size();

    // reset value vectors
    deleteAndResize( *inclusive_values, num_metrics );
    deleteAndResize( *exclusive_values, num_metrics );

    if ( metrics.size() == 0 )
    {
        return;
    }

    if ( cnode_selections.size() == 0 && sysres_selections.size() == 0 )
    {   // special case: metric tree is on the left
        // get_sev_adv with 2 parameters is ~ 5 times faster than get_sev_adv in else
        for ( IdIndexMap::iterator idIndex = metric_id_indices.begin();
              idIndex != metric_id_indices.end(); ++idIndex )
        {
            ( *inclusive_values )[ idIndex.getIndex() ] =
                mCube->get_sev_adv( static_cast<cube::Metric*>( metrics[ idIndex.getId() ] ), CUBE_CALCULATE_INCLUSIVE );
            ( *exclusive_values )[ idIndex.getIndex() ] =
                mCube->get_sev_adv( static_cast<cube::Metric*>( metrics[ idIndex.getId() ] ), CUBE_CALCULATE_EXCLUSIVE );
        }
    }
    else if ( sysres_selections.size() == 0 )
    {   // special case: metric tree is on the middle
        for ( IdIndexMap::iterator idIndex = metric_id_indices.begin();
              idIndex != metric_id_indices.end(); ++idIndex )
        {
            ( *inclusive_values )[ idIndex.getIndex() ] =
                mCube->get_sev_adv( cnode_selections, static_cast<cube::Metric*>( metrics[ idIndex.getId() ] ), CUBE_CALCULATE_INCLUSIVE );
            ( *exclusive_values )[ idIndex.getIndex() ] =
                mCube->get_sev_adv( cnode_selections, static_cast<cube::Metric*>( metrics[ idIndex.getId() ] ), CUBE_CALCULATE_EXCLUSIVE );
        }
    }
    else if ( cnode_selections.size() == 0 )
    {   // special case: metric tree is on the middle
        for ( IdIndexMap::iterator idIndex = metric_id_indices.begin();
              idIndex != metric_id_indices.end(); ++idIndex )
        {
            ( *inclusive_values )[ idIndex.getIndex() ] =
                mCube->get_sev_adv( sysres_selections, static_cast<cube::Metric*>( metrics[ idIndex.getId() ] ), CUBE_CALCULATE_INCLUSIVE );
            ( *exclusive_values )[ idIndex.getIndex() ] =
                mCube->get_sev_adv( sysres_selections, static_cast<cube::Metric*>( metrics[ idIndex.getId() ] ), CUBE_CALCULATE_EXCLUSIVE );
        }
    }
    else
    {
        for ( IdIndexMap::iterator idIndex = metric_id_indices.begin();
              idIndex != metric_id_indices.end(); ++idIndex )
        {
            // read inclusive values directly from cube
            ( *inclusive_values )[ idIndex.getIndex() ] =
                mCube->get_sev_adv( cnode_selections,
                                    sysres_selections,
                                    static_cast<cube::Metric*>( metrics[ idIndex.getId() ] ),
                                    CUBE_CALCULATE_INCLUSIVE );
            ( *exclusive_values )[ idIndex.getIndex() ] =
                mCube->get_sev_adv( cnode_selections,
                                    sysres_selections,
                                    static_cast<cube::Metric*>( metrics[ idIndex.getId() ] ),
                                    CUBE_CALCULATE_EXCLUSIVE );
        }
    }
}


void
CubeIoProxy::getMetricSubtreeValues(
    const list_of_regions&      region_selections,
    const list_of_sysresources& sysres_selections,
    Metric&                     root_metric,
    size_t                      depth,
    IdIndexMap&                 metric_id_indices,
    value_container*            inclusive_values,
    value_container*            exclusive_values )
{
    std::map<size_t, cube::Vertex*> metrics;
    // enumerate metrics
    metric_id_indices.clear();
    ::createIdIndexMapping( root_metric, depth, metric_id_indices, metrics );
    size_t num_metrics = metric_id_indices.size();

    // reset value vectors
    if ( inclusive_values != CUBE_PROXY_VALUES_IGNORE )
    {
        deleteAndResize( *inclusive_values, num_metrics );
    }

    if ( exclusive_values != CUBE_PROXY_VALUES_IGNORE )
    {
        deleteAndResize( *exclusive_values, num_metrics );
    }

//     vector< Metric* > metrics = getMetrics();

    for ( IdIndexMap::iterator idIndex = metric_id_indices.begin();
          idIndex != metric_id_indices.end(); ++idIndex )
    {
        if ( region_selections.size() == 0 && sysres_selections.size() == 0 )
        {
            ( *inclusive_values )[ idIndex.getIndex() ] =
                mCube->get_sev_adv( static_cast<cube::Metric*>( metrics[ idIndex.getId() ] ), CUBE_CALCULATE_INCLUSIVE );
            ( *exclusive_values )[ idIndex.getIndex() ] =
                mCube->get_sev_adv( static_cast<cube::Metric*>( metrics[ idIndex.getId() ] ), CUBE_CALCULATE_EXCLUSIVE );
        }
        else if ( region_selections.size() == 0 )
        {
            ( *inclusive_values )[ idIndex.getIndex() ] =
                mCube->get_sev_adv( sysres_selections, static_cast<cube::Metric*>( metrics[ idIndex.getId() ] ), CUBE_CALCULATE_INCLUSIVE );
            ( *exclusive_values )[ idIndex.getIndex() ] =
                mCube->get_sev_adv( sysres_selections, static_cast<cube::Metric*>( metrics[ idIndex.getId() ] ), CUBE_CALCULATE_EXCLUSIVE );
        }
        else if ( sysres_selections.size() == 0 )
        {
            ( *inclusive_values )[ idIndex.getIndex() ] =
                mCube->get_sev_adv( region_selections, static_cast<cube::Metric*>( metrics[ idIndex.getId() ] ), CUBE_CALCULATE_INCLUSIVE );
            ( *exclusive_values )[ idIndex.getIndex() ] =
                mCube->get_sev_adv( region_selections, static_cast<cube::Metric*>( metrics[ idIndex.getId() ] ), CUBE_CALCULATE_EXCLUSIVE );
        }
        else
        {
            if ( inclusive_values != CUBE_PROXY_VALUES_IGNORE )
            {
                // read inclusive values directly from cube
                ( *inclusive_values )[ idIndex.getIndex() ] =
                    mCube->get_sev_adv( region_selections,
                                        sysres_selections,
                                        static_cast<cube::Metric*>( metrics[ idIndex.getId() ] ),
                                        CUBE_CALCULATE_INCLUSIVE );
            }

            if ( exclusive_values != CUBE_PROXY_VALUES_IGNORE )
            {
                // initialize exclusive values with inclusive values
                ( *exclusive_values )[ idIndex.getIndex() ] =
                    mCube->get_sev_adv( region_selections,
                                        sysres_selections,
                                        static_cast<cube::Metric*>( metrics[ idIndex.getId() ] ),
                                        CUBE_CALCULATE_EXCLUSIVE );
            }
        }

        #if defined( CUBE_PROXY_DEBUG )
        cerr << "Reading metric " << static_cast<cube::Metric*>( metrics[ idIndex.getId() ] )->get_id()
             << ": " << static_cast<cube::Metric*>( metrics[ idIndex.getId() ] )->get_uniq_name()
             << endl;
        #endif
    }
}


void
CubeIoProxy::setMemoryStrategy( CubeStrategy strategy )
{
    mCube->setGlobalMemoryStrategy( strategy );
}


void
CubeIoProxy::defineMirror( const string& url )
{
    mCube->def_mirror( url );
}


void
CubeIoProxy::saveCopy( const string& filename )
{
    // create a copy of the current
    Cube* newCube = new Cube( *mCube, cube::CUBE_DEEP_COPY );

    newCube->writeCubeReport( filename );
    delete newCube;
}


const vector< Metric* >&
CubeIoProxy::getGhostMetrics() const
{
    return mCube->get_ghost_metv();
}


const Cartesian&
CubeIoProxy::getCartesian( size_t cartesianId ) const
{
    return *( mCube->get_cart )( cartesianId );
}


size_t
CubeIoProxy::getNumCartesians() const
{
    return mCube->get_cartv().size();
}


const vector< LocationGroup* >&
CubeIoProxy::getLocationGroups() const
{
    return mCube->get_location_groupv();
}


const vector< SystemTreeNode* >&
CubeIoProxy::getSystemTreeNodes() const
{
    return mCube->get_stnv();
}


const vector< SystemTreeNode* >&
CubeIoProxy::getRootSystemTreeNodes() const
{
    return mCube->get_root_stnv();
}


void
CubeIoProxy::getMetricTreeValues( const list_of_cnodes&       cnode_selections,
                                  const list_of_sysresources& sysres_selections,
                                  vector< Value* >&           inclusive_values,
                                  vector< Value* >&           exclusive_values )
{
    // CalculationFlavour   reading_flavour = CUBE_CALCULATE_INCLUSIVE;
    const vector< Metric* > metrics     = mCube->get_metv();
    size_t                  num_metrics = metrics.size();

    deleteAndResize( exclusive_values, num_metrics );
    deleteAndResize( inclusive_values, num_metrics );

    // @todo Parallelize assignment loop.
    for ( size_t i = 0; i < num_metrics; ++i )
    {
        if ( std::strcmp( metrics[ i ]->get_val().c_str(), "VOID" ) == 0 )
        {
            continue;
        }

        // read inclusive values directly from cube
        inclusive_values[ i ] = mCube->get_sev_adv( cnode_selections,
                                                    sysres_selections,
                                                    metrics[ i ],
                                                    CUBE_CALCULATE_INCLUSIVE );

        // initialize exclusive values with inclusive values
        exclusive_values[ i ] = inclusive_values[ i ]->copy();

        #if defined( CUBE_PROXY_DEBUG )
        cerr << "Reading metric " << metrics[ i ]->get_id() << ": "
             << metrics[ i ]->get_uniq_name()
             << " in=" << inclusive_values[ i ]->getDouble()
             << " ex=" << exclusive_values[ i ]->getDouble()
             << endl;
        #endif
    }

    // Calculate exclusive values
    for ( size_t i = num_metrics - 1; i < num_metrics; --i )
    {
        Metric* metric_parent = metrics[ i ]->get_parent();

        // if current metric has a parent, subtract metrics's inclusive value from its parents inclusive value
        if ( metric_parent )
        {
            *exclusive_values[ metric_parent->get_id() ] -=
                inclusive_values[ i ];
        }
        #if defined( CUBE_PROXY_DEBUG )
        cerr << "Computing exclusive metric " << metrics[ i ]->get_id()
             << " in=" << inclusive_values[ i ]->getDouble()
             << " ex=" << exclusive_values[ i ]->getDouble()
             << endl;
        #endif
    }
}


const ProgressStatus&
CubeIoProxy::getOperationProgressStatus() const
{
    return *( mCube->get_operation_progress()->get_progress_status() );
}


bool
CubeIoProxy::hasCubePlDriver() const
{
    return mCube && mCube->get_cubepl_driver();
}


cubeplparser::CubePLDriver&
CubeIoProxy::getCubePlDriver()
{
    assert( hasCubePlDriver() );

    return *mCube->get_cubepl_driver();
}


bool
CubeIoProxy::hasCubePlMemoryManager() const
{
    return mCube && mCube->get_cubepl_memory_manager();
}


CubePLMemoryManager&
CubeIoProxy::getCubePlMemoryManager()
{
    assert( hasCubePlMemoryManager() );

    return *mCube->get_cubepl_memory_manager();
}

bool
CubeIoProxy::isCubePlExpressionValid( std::string& _to_test, std::string& error_message )
{
    return mCube->test_cubepl_expression( _to_test, error_message );
}
