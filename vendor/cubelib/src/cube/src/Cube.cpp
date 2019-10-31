/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2019                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2009-2015                                                **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/**
 * \file Cube.cpp
 * \brief Defines methods of the class cube and IO-interface.
 *
 */

// PGI compiler replaces all ofstream.open() calls by open64 and then cannot find a propper one. Result -> compilation error
#if !defined( __PGI ) && !defined( __CRAYXT )  && !defined( __CRAYXE )
#define _FILE_OFFSET_BITS 64
#endif
#include "config.h"
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <UTILS_Debug.h>

#include "CubePlatformsCompat.h"
#include "CubeZfstream.h"
#include "CubeIstream.h"
#include "CubeTypes.h"
#include "CubeSysres.h"

#include "CubeMachine.h"
#include "CubeNode.h"
#include "CubeProcess.h"
#include "CubeThread.h"

#include "CubeCartesian.h"
#include "CubeRegion.h"
#include "CubeCnode.h"
#include "CubeMetric.h"
#include "CubeInclusiveMetricBuildInType.h"
#include "CubeExclusiveMetricBuildInType.h"
#include "CubeInclusiveMetric.h"
#include "CubeExclusiveMetric.h"
#include "CubePostDerivedMetric.h"
#include "CubePreDerivedInclusiveMetric.h"
#include "CubePreDerivedExclusiveMetric.h"
#include "CubeCustomPreDerivedInclusiveMetric.h"
#include "CubeCustomPreDerivedExclusiveMetric.h"
#include "CubeEnumerators.h"


#include "CubeFileFinder.h"
#include "CubeLayoutDetector.h"
#include "CubeStrategies.h"

#include "CubeDriver.h"
#include "CubePL1Driver.h"
#include "CubePL2MemoryManager.h"
#include "CubePL1MemoryManager.h"
#include "CubePL0Driver.h"
#include "CubePL0MemoryManager.h"
#include "CubeServices.h"
#include "CubeError.h"

#include "Cube.h"


using namespace std;
using namespace cube;






Cube::Cube( CubeEnforceSaving _enforce_saving )
    : cur_cnode_id( 0 ),
    cur_metric_id( 0 ),
    cur_region_id( 0 ),
    cur_stn_id( 0 ),
    cur_location_group_id( 0 ),
    cur_location_id( 0 )
{
    cubepl_memory_manager = new CubePL2MemoryManager();
    cubepl_driver         = new cubeplparser::CubePL1Driver( this );

    char* _cubepl_metrics_verbose_execution_value = getenv( "CUBEPL_VERBOSE_METRICS" );
    cubepl_metric_verbose_execution = ( _cubepl_metrics_verbose_execution_value != NULL )
                                      ?
                                      _cubepl_metrics_verbose_execution_value
                                      :
                                      "";

    disable_clustering = true;
    ghost_metv.clear();
    mode_read_only = false;
    initialized    =   false;
    set_post_initialization( true );
    enforce_saving     = _enforce_saving;
    cubename           = "";
    filefinder         = LayoutDetector::getDefaultFileFinderForWriting();
    operation_progress = new OperationProgress();
}




Cube::Cube( Cube&             _cube,
            CubeCopyFlag      copy_flag,
            CubeEnforceSaving _enforce_saving
            )
    : cur_cnode_id( 0 ),
    cur_metric_id( 0 ),
    cur_region_id( 0 ),
    cur_stn_id( 0 ),
    cur_location_group_id( 0 ),
    cur_location_id( 0 )
{
    operation_progress    = new OperationProgress();
    cubepl_memory_manager = new CubePL2MemoryManager();
    cubepl_driver         = new cubeplparser::CubePL1Driver( this );

    char* _cubepl_metrics_verbose_execution_value = getenv( "CUBEPL_VERBOSE_METRICS" );
    cubepl_metric_verbose_execution = ( _cubepl_metrics_verbose_execution_value != NULL )
                                      ?
                                      _cubepl_metrics_verbose_execution_value
                                      :
                                      "";


    disable_clustering = true;
    initialized        =   false;

    ghost_metv.clear();
    mode_read_only = false;
    set_post_initialization( true );
    enforce_saving = _enforce_saving;

    filefinder = LayoutDetector::getDefaultFileFinderForWriting();



    attrs = _cube.attrs;

    std::map<std::string, std::string>::const_iterator _iter = attrs.find( "CLUSTERING" );
    if ( _iter != attrs.end() )
    {
        attrs[ "CLUSTERING" ] = "OFF"; // disable clustering coz copy contains expanded call tree
    }


    mirror_urlv = _cube.mirror_urlv;

    map<Metric*, Metric*> met_map;

    vector<Metric*> _metrics = _cube.get_metv();
    for ( vector<Metric*>::iterator m_iter = _metrics.begin(); m_iter != _metrics.end(); ++m_iter )
    {
        Metric* _met = *m_iter;
        if ( _met == NULL )
        {
            continue;
        }
        if ( _met->isInactive()  )
        {
            continue;
        }
        Metric* my_met = def_met( _met, met_map );
        // create mapping _met -> my_met
        met_map[ _met ] = my_met;
    }
    vector<Metric*> _gh_metrics = _cube.get_ghost_metv();
    for ( vector<Metric*>::iterator m_iter = _gh_metrics.begin(); m_iter != _gh_metrics.end(); ++m_iter )
    {
        Metric* _met = *m_iter;
        if ( _met == NULL )
        {
            continue;
        }
        if ( _met->isInactive()  )
        {
            continue;
        }
        Metric* my_met = def_met( _met, met_map );
        // create mapping _met -> my_met
        met_map[ _met ] = my_met;
    }

    map<Region*, Region*> region_map;
    vector<Region*>       _regions = _cube.get_regv();

    for ( vector<Region*>::iterator r_iter = _regions.begin(); r_iter != _regions.end(); ++r_iter )
    {
        Region* _reg   = *r_iter;
        Region* my_reg = def_region( _reg );
        // create mapping _reg -> my_reg
        region_map[ _reg ] = my_reg;
    }

    map<Cnode*, Cnode*> cnodes_map;
    vector<Cnode*>      _cnodes = _cube.get_cnodev();

    for ( vector<Cnode*>::iterator c_iter = _cnodes.begin(); c_iter != _cnodes.end(); ++c_iter )
    {
        Cnode* _cnode = *c_iter;

        if ( _cnode->isHidden() ) // do not store hidden cnodes.
        {
            continue;
        }

        Cnode*                                                my_cnode  = def_cnode( _cnode, cnodes_map, region_map );
        std::vector < std::pair < std::string, double> >      _num_pars = _cnode->get_num_parameters();
        std::vector < std::pair < std::string, std::string> > _str_pars = _cnode->get_str_parameters();

        for ( std::vector < std::pair < std::string, double> >::iterator _n_iter = _num_pars.begin(); _n_iter != _num_pars.end(); ++_n_iter )
        {
            my_cnode->add_num_parameter( ( *_n_iter ).first, ( *_n_iter ).second );
        }
        for ( std::vector < std::pair < std::string, std::string> >::iterator _s_iter = _str_pars.begin(); _s_iter != _str_pars.end(); ++_s_iter )
        {
            my_cnode->add_str_parameter( ( *_s_iter ).first, ( *_s_iter ).second );
        }
        cnodes_map[ _cnode ] = my_cnode;
        // create mapping _cnode -> my_cnode
    }


    map<SystemTreeNode*, SystemTreeNode*> stn_map;
    const std::vector<SystemTreeNode*>    _stns  =    _cube.get_root_stnv();
    std::vector<SystemTreeNode*>          _stns2 = _stns;

    for ( size_t i = 0; i < _stns2.size(); ++i )
    {
        SystemTreeNode* _stn   = _stns2[ i ];
        SystemTreeNode* my_stn = def_system_tree_node( _stn, stn_map );
        for ( unsigned int j = 0; j < _stn->num_children(); ++j )
        {
            _stns2.push_back( _stn->get_child( j ) );
        }

        // create mapping _machine -> my_machine
        stn_map[ _stn ] = my_stn;
    }


    map<LocationGroup*, LocationGroup*> lg_map;
    std::vector<LocationGroup*>         _lgs =    _cube.get_procv();
    for ( vector<LocationGroup*>::iterator lg_iter = _lgs.begin(); lg_iter != _lgs.end(); ++lg_iter )
    {
        LocationGroup* _lg   = *lg_iter;
        LocationGroup* my_lg = def_location_group( _lg, stn_map );
        // create mapping _process -> my_process
        lg_map[ _lg ] = my_lg;
    }

    map<Location*, Location*> locs_map;
    std::vector<Location*>    _locations =    _cube.get_locationv();
    for ( vector<Location*>::iterator loc_iter = _locations.begin(); loc_iter != _locations.end(); ++loc_iter )
    {
        Location* _location   = *loc_iter;
        Location* my_location = def_location( _location, lg_map );
        // create mapping _thread -> my_thread
        locs_map[ _location ] = my_location;
    }

    // Copy the cartesian vector.
    vector<Cartesian*> _topos = _cube.get_cartv();
    for ( vector<Cartesian*>::const_iterator topo_iter = _topos.begin(); topo_iter != _topos.end(); ++topo_iter )
    {
        Cartesian* _topo = def_cart( ( *topo_iter )->get_ndims(), ( *topo_iter )->get_dimv(), ( *topo_iter )->get_periodv() );
        _topo->set_name( ( *topo_iter )->get_name() );
        _topo->set_namedims( ( *topo_iter )->get_namedims() );
        TopologyMap           _sys_coords = ( *topo_iter )->get_cart_sys();
        TopologyMap::iterator _siter;
        for ( _siter = _sys_coords.begin(); _siter != _sys_coords.end(); ++_siter )
        {
            Sysres*           _sys = ( Sysres* )( ( *_siter ).first );
            std::vector<long> _v   = ( *_siter ).second;
            if ( _sys->isSystemTreeNode() )
            {
                _topo->def_coords( stn_map[ ( SystemTreeNode* )_sys ], _v );
            }
            if ( _sys->isLocationGroup() )
            {
                _topo->def_coords( lg_map[ ( LocationGroup* )_sys ], _v );
            }
            if ( _sys->isLocation() )
            {
                _topo->def_coords( locs_map[ ( Location* )_sys ], _v );
            }
        }
    }

    initialize();
    setup_cubepl_memory();
    compile_derived_metric_expressions();
    set_post_initialization( false );

    if ( copy_flag == CUBE_DEEP_COPY ) // data should be copied too
    {
        vector<Metric*> _metrics       = _cube.get_metv();
        vector<Metric*> _ghost_metrics = _cube.get_ghost_metv();
        for ( vector<Metric*>::iterator m_iter = _ghost_metrics.begin(); m_iter != _ghost_metrics.end(); ++m_iter ) // add ghist metrics
        {
            if ( *m_iter != NULL )
            {
                _metrics.push_back( *m_iter );
            }
        }

        vector<Cnode*> _cnodes = _cube.get_cnodev();
        for ( vector<Metric*>::iterator m_iter = _metrics.begin(); m_iter != _metrics.end(); ++m_iter )
        {
            Metric* _met = *m_iter;
            if ( _met == NULL )
            {
                continue;
            }
            if ( _met->get_type_of_metric() != CUBE_METRIC_EXCLUSIVE &&  _met->get_type_of_metric() != CUBE_METRIC_INCLUSIVE  )
            {
                continue; // we do not copy data from derivedc metrics.
            }
            CalculationFlavour cf = ( _met->get_type_of_metric() == CUBE_METRIC_EXCLUSIVE ) ?  cube::CUBE_CALCULATE_EXCLUSIVE : cube::CUBE_CALCULATE_INCLUSIVE;
            if ( _met->isInactive() )
            {
                continue;
            }
            for ( vector<Cnode*>::iterator c_iter = _cnodes.begin(); c_iter != _cnodes.end(); ++c_iter )
            {
                Cnode* _cnode = *c_iter;
                if ( _cnode->isVisible() ) // do not store hidden elements and cnodes. Their value is in value of parent
                {
                    char* _val = _cube.get_sevs_raw( _met, cube::CUBE_CALCULATE_INCLUSIVE,  _cnode, cf );
                    if ( _val != NULL )
                    {
                        set_sevs_raw( met_map[ _met ], cnodes_map[ _cnode ],  _val );
                    }
                }
            }
        }
    }
}



void
Cube::openCubeReport( std::string _cubename, bool _disable_clustering )
{
    char* clustering_env = getenv( "CUBELIB_ENABLE_CLUSTERING" );
    if ( clustering_env == NULL )
    {
        disable_clustering = _disable_clustering;
    }
    else
    {
        std::string env = clustering_env;
        disable_clustering = ( env.compare( "false" ) == 0 ||
                               env.compare( "0" ) == 0 ||
                               env.compare( "no" ) == 0 );
    }
    closeCubeReport();
    operation_progress->init();
    cubename = _cubename;
    set_post_initialization( true );


    cubename = services::remove_dotted_path( cubename );


    if ( services::is_cube3_name( cubename ) || services::is_cube3_gzipped_name( cubename ) )
    {
        mode_read_only = false;

        filefinder = LayoutDetector::getVirtualFileFinder();

        int ffile = open(  cubename.c_str(), O_RDONLY  );
        if ( ( off_t )0 != lseek( ffile, 0, SEEK_CUR ) )
        {
            cerr << "Cannot seek to the metadata of cube " <<  cubename << endl;
            throw FatalError( "Cannot seek to the metadata of cube " + cubename );
        }



        struct stat _stat;
        if ( 0 != fstat( ffile, &_stat ) )
        {
            cerr << "Cannot seek to the metadata of cube " <<  cubename << endl;
            throw FatalError( "Cannot seek to the metadata of cube " + cubename );
        }







#if defined( FRONTEND_CUBE_COMPRESSED ) || defined ( FRONTEND_CUBE_COMPRESSED_READONLY )
        size_t     _size = gzifstream::probe( ffile, _stat.st_size );
        gzifstream in( ffile, ios::in | ios::binary, _size );

#else
        size_t      _size = _stat.st_size;
        CubeIstream in( _size );
        in.open(  cubename.c_str(), ios::in | ios::binary );
        in.seekg( 0 );
#endif
//      ifstream in;

        in >> *this;
        in.close();
    }
    else
    {
        mode_read_only = true;
        filefinder     = LayoutDetector::getFileFinder( cubename );
        fileplace_t anchor = filefinder->getAnchor();
#if defined( FRONTEND_CUBE_COMPRESSED ) || defined( FRONTEND_CUBE_COMPRESSED_READONLY )
        int ffile = open(  anchor.first.c_str(), O_RDONLY  );
        if ( -1 == ffile )
        {
            throw IOError( services::cube_errno() );
        }
        if ( ( off_t )anchor.second.first != lseek( ffile, anchor.second.first, SEEK_CUR ) )
        {
            cerr << "Cannot seek to the metadata of cube " <<  cubename << endl;
            throw FatalError( "Cannot seek to the metadata of cube " + cubename );
        }
        size_t     _size = gzifstream::probe( ffile, anchor.second.second );
        gzifstream in( ffile, ios::in | ios::binary, _size );
#else
        CubeIstream in( anchor.second.second );
        in.open( anchor.first.c_str(), ios::in | ios::binary );
        if ( !in.is_open() )
        {
            throw IOError(  services::cube_errno() );
        }
        in.seekg( anchor.second.first );
#endif
        in >> *this;
        in.close();
    }
    create_metrics_data_containers();
    initialize();
    setup_cubepl_memory();
    compile_derived_metric_expressions();
    set_post_initialization( false );
}




Cube::~Cube()
{
    if ( is_initialized() )
    {
        closeCubeReport();
    }

    delete cubepl_memory_manager;
    delete cubepl_driver;
    delete operation_progress;
}


void
Cube::closeCubeReport()
{
    cubepl_memory_manager->get_memory_initializer()->memory_init();
    for ( unsigned int i = 0; i < metv.size(); ++i )
    {
        delete metv[ i ];
    }
    metv.clear();
    for ( unsigned int i = 0; i < ghost_metv.size(); ++i )
    {
        delete ghost_metv[ i ];
    }
    ghost_metv.clear();
    for ( unsigned int i = 0; i < regv.size(); ++i )
    {
        delete regv[ i ];
    }
    regv.clear();
    for ( unsigned int i = 0; i < fullcnodev.size(); ++i )
    {
        delete fullcnodev[ i ];
    }
    cnodev.clear();
    root_cnodev.clear();

    for ( std::map<const Cnode*, uint8_t>::iterator iter = remapping_cnodev.begin(); iter != remapping_cnodev.end(); ++iter )
    {
        delete ( *iter ).first;
    }


    for ( unsigned int i = 0; i < stnv.size(); ++i )
    {
        delete stnv[ i ];
    }
    stnv.clear();
    root_stnv.clear();

    for ( unsigned int i = 0; i < location_groupv.size(); ++i )
    {
        delete location_groupv[ i ];
    }
    location_groupv.clear();
    for ( unsigned int i = 0; i < locationv.size(); ++i )
    {
        delete locationv[ i ];
    }
    locationv.clear();
    for ( unsigned int i = 0; i < cartv.size(); ++i )
    {
        delete cartv[ i ];
    }
    cartv.clear();
    delete filefinder;
    filefinder = NULL;

    cur_cnode_id          = 0;
    cur_metric_id         = 0;
    cur_region_id         = 0;
    cur_stn_id            = 0;
    cur_location_group_id = 0;
    cur_location_id       = 0;
    initialized           = false;
}


void
Cube::writeCubeReport( std::string name,
                       bool        write_ghost_metrics )
{
    try
    {
        if ( services::is_path( cubename ) )
        {
            cubename = services::remove_dotted_path( cubename );
            services::create_path_for_file( cubename );
        }
#if defined( FRONTEND_CUBE_COMPRESSED )
        gzofstream out;
#else
        ofstream out;
        // we write meta part always uncompressed so far - till compression in cubew is implemented
#endif

        fileplace_t anchor = filefinder->getAnchor();
        if ( services::is_path( anchor.first.c_str() ) )
        {
            services::create_path_for_file( anchor.first.c_str() );
        }
        out.open( anchor.first.c_str(), ios::binary );
        out.seekp( anchor.second.first );
        writeXML_header( out, false, write_ghost_metrics );
        writeXML_closing( out );
        out.close();
        name = services::remove_dotted_path( name );
        writeMetricsData( services::get_cube4_name( name ) );
    }
    catch ( const FinalizeFilesError& error )
    {
        cerr << error.what() << endl;
        cerr << "Clean up...";
        if ( remove( string( name + ".cubex" ).c_str() ) != 0 )
        {
            perror( "" );
        }
        else
        {
            cerr << "done." << endl;
        }
    }
}



void
Cube::writeMetricsData( std::string name )
{
    for ( unsigned int i = 0; i < metv.size(); ++i )
    {
        if ( metv[ i ] != NULL )
        {
            metv[ i ]->writeData();
        }
    }
    for ( unsigned int i = 0; i < ghost_metv.size(); ++i )
    {
        if ( ghost_metv[ i ] != NULL )
        {
            ghost_metv[ i ]->writeData();
        }
    }
    filefinder->finalizeFiles( name );
}



void
Cube::setGlobalMemoryStrategy( CubeStrategy strategy )
{
    for ( unsigned int i = 0; i < metv.size(); ++i )
    {
        if ( metv[ i ] != NULL )
        {
            setMetricMemoryStrategy( metv[ i ], strategy );
        }
    }
    for ( unsigned int i = 0; i < ghost_metv.size(); ++i )
    {
        if ( ghost_metv[ i ] != NULL )
        {
            setMetricMemoryStrategy( ghost_metv[ i ], strategy );
        }
    }
}

void
Cube::setMetricMemoryStrategy( Metric* met,  CubeStrategy strategy )
{
    met->setStrategy( strategy );
}


void
Cube::dropRowInAllMetrics( Cnode* cnode )
{
    for ( unsigned int i = 0; i < metv.size(); ++i )
    {
        if ( metv[ i ] != NULL )
        {
            dropRowInMetric( metv[ i ], cnode );
        }
    }
    for ( unsigned int i = 0; i < ghost_metv.size(); ++i )
    {
        if ( ghost_metv[ i ] != NULL )
        {
            dropRowInMetric( ghost_metv[ i ], cnode );
        }
    }
}




void
Cube::dropRowInMetric( Metric* met, Cnode* cnode )
{
    met->dropRow( cnode );
}



void
Cube::dropAllRowsInMetric( Metric* met )
{
    met->dropAllRows();
}

void
Cube::dropAllRowsInAllMetrics()
{
    for ( unsigned int i = 0; i < metv.size(); ++i )
    {
        if ( metv[ i ] != NULL )
        {
            dropAllRowsInMetric( metv[ i ] );
        }
    }
    for ( unsigned int i = 0; i < ghost_metv.size(); ++i )
    {
        if ( ghost_metv[ i ] != NULL )
        {
            dropAllRowsInMetric( ghost_metv[ i ] );
        }
    }
}



void
Cube::check_special_cube( Metric* met )
{
    if ( met->get_data_type() == CUBE_DATA_TYPE_SCALE_FUNC )
    {
        // ScaleFuncValues should be exclusive in a cube as they
        // usually have bogus machine/thread values, thus we use this
        // flag to enable special widgets on load
        def_attr( "ScaleFuncPresent", "1" );
    }
}


void
Cube::def_attr( const string& key, const string& value )
{
    attrs[ key ] = value;
}

string
Cube::get_attr( const std::string& key ) const
{
    map<std::string, std::string>::const_iterator it = attrs.find( key );
    if ( it != attrs.end() )
    {
        return it->second;
    }

    return string();
}

void
Cube::def_mirror( const std::string& url )
{
    mirror_urlv.push_back( url );
}

const vector<string>&
Cube::get_mirrors() const
{
    return mirror_urlv;
}

Metric*
Cube::def_met( const string&   disp_name,
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
               VizTypeOfMetric is_ghost
               )
{
    return def_met( disp_name, uniq_name, dtype, uom, val, url,
                    descr, parent, cur_metric_id, type_of_metric, expression, init_expression, aggr_plus_expression, aggr_minus_expression, aggr_aggr_expression, threadwise, is_ghost );
}

Metric*
Cube::def_met( const string&   disp_name,
               const string&   uniq_name,
               const string&   dtype,
               const string&   uom,
               const string&   val,
               const string&   url,
               const string&   descr,
               Metric*         parent,
               uint32_t        id,
               TypeOfMetric    type_of_metric,
               const string&   expression,
               const string&   init_expression,
               const string&   aggr_plus_expression,
               const string&   aggr_minus_expression,
               const string&   aggr_aggr_expression,
               const bool      threadwise,
               VizTypeOfMetric is_ghost )
{
    Metric* met = Metric::create( disp_name,
                                  uniq_name,
                                  dtype,
                                  uom,
                                  val,
                                  url,
                                  descr,
                                  filefinder,
                                  parent,
                                  type_of_metric,
                                  id,
                                  expression,
                                  init_expression,
                                  aggr_plus_expression,
                                  aggr_minus_expression,
                                  aggr_aggr_expression,
                                  threadwise,
                                  is_ghost );

    if ( met != NULL && (
             met->get_type_of_metric() == CUBE_METRIC_POSTDERIVED ||
             met->get_type_of_metric() == CUBE_METRIC_PREDERIVED_INCLUSIVE ||
             met->get_type_of_metric() == CUBE_METRIC_PREDERIVED_EXCLUSIVE )
         )
    {
        met->setMemoryManager( cubepl_memory_manager );

        if ( !postcompilation_of_derived_metrics )
        {
            std::string derived_metric_error;
            std::string derived_metric_init_error;
            std::string derived_metric_aggr_plus_error;
            std::string derived_metric_aggr_minus_error;
            std::string derived_metric_aggr_aggr_error;

            std::string cubepl_program            = string( "<cubepl>" ) + expression + string( "</cubepl>" );
            std::string cubepl_init_program       = string( "<cubepl>" ) + init_expression + string( "</cubepl>" );
            std::string cubepl_aggr_plus_program  = string( "<cubepl>" ) + aggr_plus_expression + string( "</cubepl>" );
            std::string cubepl_aggr_minus_program = string( "<cubepl>" ) + aggr_minus_expression + string( "</cubepl>" );
            std::string cubepl_aggr_aggr_program  = string( "<cubepl>" ) + aggr_aggr_expression + string( "</cubepl>" );

            if ( cubepl_driver->test( cubepl_program, derived_metric_error ) &&
                 cubepl_driver->test( cubepl_init_program, derived_metric_init_error ) &&
                 cubepl_driver->test( cubepl_aggr_plus_program, derived_metric_aggr_plus_error ) &&
                 cubepl_driver->test( cubepl_aggr_minus_program, derived_metric_aggr_minus_error ) &&
                 cubepl_driver->test( cubepl_aggr_aggr_program, derived_metric_aggr_aggr_error )
                 )
            {
                if ( aggr_aggr_expression != "" )
                {
                    stringstream       strin5( cubepl_aggr_aggr_program );
                    GeneralEvaluation* formula5 = cubepl_driver->compile( &strin5, &cerr );
                    UTILS_DEBUG_ONLY(
                        if ( formula5 != NULL  && services::is_metric_present( cubepl_metric_verbose_execution,  uniq_name ) )
                    {
                        std::cout << "CubePL expression for the operator \"aggr\" of metric " << uniq_name << ":" << std::endl;
                        formula5->print();
                        std::cout << std::endl;
                        formula5->set_verbose_execution(  services::is_metric_present( cubepl_metric_verbose_execution,  uniq_name )  );
                    }
                        )
                    met->setAggrAggrEvaluation( formula5 );
                }
                if ( aggr_plus_expression != "" )
                {
                    stringstream       strin4( cubepl_aggr_plus_program );
                    GeneralEvaluation* formula4 = cubepl_driver->compile( &strin4, &cerr );
                    UTILS_DEBUG_ONLY(
                        if ( formula4 != NULL  && services::is_metric_present( cubepl_metric_verbose_execution,  uniq_name ) )
                    {
                        std::cout << "CubePL expression for the operator \"+\" of metric " << uniq_name << ":" << std::endl;
                        formula4->print();
                        std::cout << std::endl;
                        formula4->set_verbose_execution(  services::is_metric_present( cubepl_metric_verbose_execution,  uniq_name )  );
                    }
                        )
                    met->setAggrPlusEvaluation( formula4 );
                }
                if ( aggr_minus_expression != "" )
                {
                    stringstream       strin3( cubepl_aggr_minus_program );
                    GeneralEvaluation* formula3 = cubepl_driver->compile( &strin3, &cerr );
                    UTILS_DEBUG_ONLY(
                        if ( formula3 != NULL && services::is_metric_present( cubepl_metric_verbose_execution,  uniq_name ) )
                    {
                        std::cout << "CubePL expression for the operator \"-\" of metric " << uniq_name << ":" << std::endl;
                        formula3->print();
                        std::cout << std::endl;
                        formula3->set_verbose_execution(  services::is_metric_present( cubepl_metric_verbose_execution,  uniq_name )  );
                    }
                        )
                    met->setInitEvaluation( formula3 );
                }
                stringstream       strin2( cubepl_init_program );
                GeneralEvaluation* formula2 = cubepl_driver->compile( &strin2, &cerr );
                UTILS_DEBUG_ONLY(
                    if ( formula2 != NULL && services::is_metric_present( cubepl_metric_verbose_execution,  uniq_name ) )
                {
                    std::cout << "CubePL initialization expression of metric " << uniq_name << ":" << std::endl;
                    formula2->print();
                    std::cout << std::endl;
                    formula2->set_verbose_execution(  services::is_metric_present( cubepl_metric_verbose_execution,  uniq_name )  );
                }
                    )
                met->setInitEvaluation( formula2 );
                stringstream       strin1( cubepl_program );
                GeneralEvaluation* formula1 = cubepl_driver->compile( &strin1, &cerr );
                UTILS_DEBUG_ONLY(
                    if ( formula1 != NULL && services::is_metric_present( cubepl_metric_verbose_execution,  uniq_name ) )
                {
                    std::cout << "CubePL expression of metric " << uniq_name << ":" << std::endl;
                    formula1->print();
                    std::cout << std::endl;
                    formula1->set_verbose_execution(  services::is_metric_present( cubepl_metric_verbose_execution,  uniq_name )  );
                }
                    )

                if ( formula1 == NULL )
                {
                    cerr << "Metric " << uniq_name << " has an empty CubePL expression. Ignore." << endl;
                    delete met;
                    return NULL;
                }
                met->setEvaluation( formula1 );
            }
            else
            {     // cannot create metric, cou compilerr reported an error (??? )
                cerr << " Cannot create prederived inclusive metric with an expression : " << endl << expression <<  endl << " and and init expression " << init_expression << endl << "because of the following error: " <<  derived_metric_error << " " << derived_metric_init_error << endl;
                return NULL;
            }
        }
    }

    if ( met != NULL )
    {
        // check if we have a special cube that needs to be marked
        check_special_cube( met );
        if ( !met->isGhost() )
        {
            if ( parent == NULL )
            {
                root_metv.push_back( met );
            }

            if ( metv.size() <= id )
            {
                metv.resize( id + 1 );
            }
            else if ( metv[ id ] )
            {
                throw RuntimeError( "Metric with this ID exists" );
            }
            metv[ id ]    = met;
            cur_metric_id = metv.size();
        }
        else                                                                                        // add ghost metrics into another vector.
        {
            ghost_metv.push_back( met );
            cur_metric_id++;
        }
        if ( !postcompilation_of_derived_metrics )
        {
            create_metrics_data_containers( met );
            met->initialize();
        }
        // calles virtual functions. therefore should be here...
    }
    return met;
}



Metric*
Cube::def_met( Metric* _met, map<Metric*, Metric*>& met_map )
{
    const string& disp_name             = _met->get_disp_name();
    const string& uniq_name             = _met->get_uniq_name();
    const string& dtype                 = _met->get_dtype();
    const string& uom                   = _met->get_uom();
    const string& val                   = _met->get_val();
    const string& url                   = _met->get_url();
    const string& descr                 = _met->get_descr();
    Metric*       parent                = met_map[ _met->get_parent() ];
    TypeOfMetric  type_of_metric        = _met->get_type_of_metric();
    const string& expression            = _met->get_expression();
    const string& init_expression       = _met->get_init_expression();
    const string& aggr_plus_expression  = _met->get_aggr_plus_expression();
    const string& aggr_minus_expression = _met->get_aggr_minus_expression();
    const string& aggr_aggr_expression  = _met->get_aggr_aggr_expression();

    return def_met( disp_name,
                    uniq_name,
                    dtype,
                    uom,
                    val,
                    url,
                    descr,
                    parent,
                    _met->get_id(),
                    type_of_metric,
                    expression,
                    init_expression,
                    aggr_plus_expression,
                    aggr_minus_expression,
                    aggr_aggr_expression,
                    _met->isRowWise(),
                    _met->get_viz_type() );
}







Region*
Cube::def_region( const string& name,
                  const string& mangled_name,
                  const string& paradigm,
                  const string& role,
                  long          begln,
                  long          endln,
                  const string& url,
                  const string& descr,
                  const string& mod )
{
    return def_region( name, mangled_name, paradigm, role, begln, endln, url, descr, mod, cur_region_id );
}

Region*
Cube::def_region( const string& name,
                  const string& mangled_name,
                  const string& paradigm,
                  const string& role,
                  long          begln,
                  long          endln,
                  const string& url,
                  const string& descr,
                  const string& mod,
                  uint32_t      id )
{
    Region* reg = new Region( name, mangled_name, paradigm, role, begln, endln, url, descr, mod, id );

    if ( regv.size() <= id )
    {
        regv.resize( id + 1 );
    }
    else if ( regv[ id ] )
    {
        throw RuntimeError( "Region with this ID exists" );
    }

    regv[ id ]    = reg;
    cur_region_id = regv.size();

    return reg;
}



Region*
Cube::def_region( Region* _reg )
{
    const string& name         = _reg->get_name();
    const string& mangled_name = _reg->get_mangled_name();
    const string& paradigm     = _reg->get_paradigm();
    const string& role         = _reg->get_role();
    const long    begln        = _reg->get_begn_ln();
    const long    endln        = _reg->get_end_ln();
    const string& url          = _reg->get_url();
    const string& descr        = _reg->get_descr();
    const string& mod          = _reg->get_mod();

    return def_region( name, mangled_name,  paradigm, role, begln, endln, url, descr, mod, _reg->get_id() );
}





Cnode*
Cube::def_cnode( Region* callee, Cnode* parent )
{
    return def_cnode( callee, "", -1, parent, cur_cnode_id );
}

Cnode*
Cube::def_cnode( Region*       callee,
                 const string& mod,
                 int           line,
                 Cnode*        parent,
                 uint32_t      id )
{
    if ( id == ( uint32_t )( -1 ) )
    {
        id = cur_cnode_id;                                                                                            // automatical id assignment.
    }
    Cnode* cnode = new Cnode( callee, mod, line, parent, id );
    if ( !parent )
    {
        root_cnodev.push_back( cnode );
    }
    callee->add_cnode( cnode );
    if ( cnodev.size() <= id )
    {
        cnodev.resize( id + 1 );
        fullcnodev.resize( id + 1 );
    }
    else
    if ( cnodev[ id ] )
    {
        throw RuntimeError( "Cnode with this ID exists" );
    }
    cnodev[ id ]     = cnode;
    fullcnodev[ id ] = cnode;
    cur_cnode_id     = cnodev.size();
    return cnode;
}



Cnode*
Cube::def_cnode( Cnode* _cnode, map<Cnode*, Cnode*>& cnodes_map, map<Region*, Region*>& regions_map, bool copy_id )
{
    Region*       callee = regions_map[ _cnode->get_callee() ];
    const string& mod    = _cnode->get_mod();
    const long    line   = _cnode->get_line();
    Cnode*        parent = cnodes_map[ _cnode->get_parent() ];
    return def_cnode( callee, mod, line, parent, ( copy_id ) ? _cnode->get_id() : ( uint32_t )( -1 ) );
}






Machine*
Cube::def_mach( const string& name, const string& desc )
{
    return def_mach( name, desc, cur_stn_id );
}

Machine*
Cube::def_mach( const string& name,
                const string& desc,
                uint32_t      id )
{
    std::string _class = "machine";
    return def_system_tree_node( name, desc, _class, NULL, id );
}



Machine*
Cube::def_mach( Machine* _mach )
{
    const string& name = _mach->get_name();
    const string& desc = _mach->get_desc();
    return def_mach( name, desc, _mach->get_id() );
}





Node*
Cube::def_node( const string& name, Machine* mach )
{
    return def_node( name,  mach, cur_stn_id );
}

Node*
Cube::def_node( const string& name,
                Machine*      mach,
                uint32_t      id )
{
    std::string _class = "node";
    return def_system_tree_node( name, "", _class, mach, id );
}



Node*
Cube::def_node( Node* _node, map<Machine*, Machine*>& machines_map )
{
    const string name = _node->get_name();
    Machine*     mach = machines_map[ _node->get_parent() ];

    return def_node( name, mach, _node->get_id() );
}




Process*
Cube::def_proc( const string& name, int rank, Node* node )
{
    return def_proc( name, rank, node, cur_location_group_id );
}

Process*
Cube::def_proc( const string& name,
                int           rank,
                Node*         node,
                uint32_t      id )
{
    return def_location_group( name, rank, cube::CUBE_LOCATION_GROUP_TYPE_PROCESS, node, id );
}


Process*
Cube::def_proc( Process* _process, map<Node*, Node*>& nodes_map )
{
    const string name = _process->get_name();
    const int    rank = _process->get_rank();
    Node*        node = nodes_map[ _process->get_parent() ];

    return def_proc( name, rank,  node, _process->get_id() );
}






Thread*
Cube::def_thrd( const string& name, int rank, Process* proc )
{
    return def_thrd( name, rank, proc, cur_location_id );
}

Thread*
Cube::def_thrd( const string& name,
                int           rank,
                Process*      proc,
                uint32_t      id )
{
    return def_location( name, rank, cube::CUBE_LOCATION_TYPE_CPU_THREAD, proc, id );
}


Thread*
Cube::def_thrd( Thread* _thread, map<Process*, Process*>& processes_map )
{
    const string name    = _thread->get_name();
    const int    rank    = _thread->get_rank();
    Process*     process = processes_map[ _thread->get_parent() ];

    return def_thrd( name, rank, process, _thread->get_id() );
}






SystemTreeNode*
Cube::def_system_tree_node( const string&   name,
                            const string&   desc,
                            const string&   stn_class,
                            SystemTreeNode* parent )
{
    return def_system_tree_node( name, desc, stn_class, parent,  cur_stn_id );
}

SystemTreeNode*
Cube::def_system_tree_node( const string&   name,
                            const string&   desc,
                            const string&   stn_class,
                            SystemTreeNode* parent,
                            uint32_t        id )
{
    SystemTreeNode* stn = new SystemTreeNode( name, desc, stn_class, parent, id, sysv.size() );

    if ( stnv.size() <= id )
    {
        stnv.resize( id + 1 );
    }
    else if ( stnv[ id ] )
    {
        throw RuntimeError( "SystemTreeNode with this ID exists" );
    }

    stnv[ id ] = stn;
    if ( parent == NULL )
    {
        root_stnv.push_back( stn );
    }
    else
    {
        non_root_stnv.push_back( stn );
    }

    if ( stn_class.compare( "machine" ) == 0 )
    {
        machv.push_back( stn );
    }
    if ( stn_class.compare( "node" ) == 0 )
    {
        nodev.push_back( stn );
    }




    cur_stn_id = stnv.size();
    sysv.push_back( stn );

    return stn;
}



SystemTreeNode*
Cube::def_system_tree_node( SystemTreeNode* _stn, map<SystemTreeNode*, SystemTreeNode*>& nodes_map  )
{
    const string&   name    = _stn->get_name();
    const string&   desc    = _stn->get_desc();
    const string&   _class  = _stn->get_class();
    SystemTreeNode* _parent = nodes_map[ _stn->get_parent() ];
    return def_system_tree_node( name, desc, _class, _parent, cur_stn_id );
}






LocationGroup*
Cube::def_location_group( const string& name,  int rank, LocationGroupType type, SystemTreeNode* node )
{
    return def_location_group( name, rank, type, node, cur_location_group_id );
}

LocationGroup*
Cube::def_location_group( const string&     name,
                          int               rank,
                          LocationGroupType type,
                          SystemTreeNode*   node,
                          uint32_t          id )
{
    LocationGroup* lg = new LocationGroup( name, node, rank, type, id, sysv.size() );

    if ( location_groupv.size() <= id )
    {
        location_groupv.resize( id + 1 );
    }
    else if ( location_groupv[ id ] )
    {
        throw RuntimeError( "Process with this ID exists" );
    }

    location_groupv[ id ] = lg;
    cur_location_group_id = location_groupv.size();
    sysv.push_back( lg );

    return lg;
}


LocationGroup*
Cube::def_location_group( LocationGroup* _group, map<SystemTreeNode*, SystemTreeNode*>& nodes_map )
{
    const string      name = _group->get_name();
    const int         rank = _group->get_rank();
    LocationGroupType type = _group->get_type();
    SystemTreeNode*   node = nodes_map[ _group->get_parent() ];

    return def_location_group( name, rank, type, node, cur_location_group_id );
}




Location*
Cube::def_location( const string& name, int rank, LocationType type, LocationGroup* parent )
{
    return def_location( name, rank, type, parent, cur_location_id );
}

Location*
Cube::def_location( const string&  name,
                    int            rank,
                    LocationType   type,
                    LocationGroup* parent,
                    uint32_t       id )
{
    // one starts to fill the cube with values - therefore no changes in Calnode/Systree dimensions are allowed
    Location* loc = new Location( name, rank, parent, type, id, sysv.size() );

    if ( locationv.size() <= id )
    {
        locationv.resize( id + 1 );
    }
    else if ( locationv[ id ] )
    {
        throw RuntimeError( "Location with this ID already exists" );
    }

    locationv[ id ] = loc;
    cur_location_id = locationv.size();
    sysv.push_back( loc );

    return loc;
}


Location*
Cube::def_location( Location* _location, map<LocationGroup*, LocationGroup*>& locgroups_map )
{
    const string   name   = _location->get_name();
    const int      rank   = _location->get_rank();
    LocationType   type   = _location->get_type();
    LocationGroup* parent = locgroups_map[ _location->get_parent() ];

    return def_location( name, rank, type, parent, cur_location_id );
}











Cartesian*
Cube::def_cart( long ndims, const vector<long>& dimv,
                const vector<bool>& periodv )
{
    Cartesian* newc = new Cartesian( ndims, dimv, periodv );
    cartv.push_back( newc );
    return newc;
}






const Cartesian*
Cube::get_cart( int i ) const
{
    if ( cartv.size() > 0 )
    {
        return cartv[ i ];
    }
    else
    {
        return NULL;
    }
}

void
Cube::def_coords( Cartesian* cart, const Sysres* sys,
                  const vector<long>& coordv )
{
    cart->def_coords( sys, coordv );
}




Metric*
Cube::get_met( const std::string& _uniq_name ) const
{
    for ( std::vector<Metric*>::const_iterator iter = metv.begin(); iter != metv.end(); ++iter )
    {
        if ( *iter == NULL )
        {
            continue;
        }
        if ( ( ( ( *iter )->get_uniq_name() ).compare( _uniq_name ) ) == 0 )
        {
            return *iter;
        }
    }
    for ( std::vector<Metric*>::const_iterator iter = ghost_metv.begin(); iter != ghost_metv.end(); ++iter )
    {
        if ( *iter == NULL )
        {
            continue;
        }
        if ( ( ( ( *iter )->get_uniq_name() ).compare( _uniq_name ) ) == 0 )
        {
            return *iter;
        }
    }
    // didn't find any metrics
    return NULL;
}


Metric*
Cube::get_met( uint32_t _id, bool filed_id ) const
{
    for ( std::vector<Metric*>::const_iterator iter = metv.begin(); iter != metv.end(); ++iter )
    {
        if ( *iter == NULL )
        {
            continue;
        }
        if ( !filed_id )
        {
            if ( ( ( *iter )->get_id() ) == _id )
            {
                return *iter;
            }
        }
        else
        {
            if ( ( ( *iter )->get_filed_id() ) == _id )
            {
                return *iter;
            }
        }
    }
    for ( std::vector<Metric*>::const_iterator iter = ghost_metv.begin(); iter != ghost_metv.end(); ++iter )
    {
        if ( *iter == NULL )
        {
            continue;
        }
        if ( !filed_id )
        {
            if ( ( ( *iter )->get_id() ) == _id )
            {
                return *iter;
            }
        }
        else
        {
            if ( ( ( *iter )->get_filed_id() ) == _id )
            {
                return *iter;
            }
        }
    }
    // didn't find any metrics
    return NULL;
}
// ------------------ SEVERITIES PART START --------------------------------

vector<Cnode* >
Cube::get_optimal_sequence( Metric* metric )
{
    return metric->get_optimal_sequence( get_cnodev() );
}




void
Cube::create_metrics_data_containers()
{
    collect_whole_subtree_for_callpaths();
    collect_whole_subtree_for_systemtree();
    for ( std::vector<Metric*>::const_iterator miter = get_metv().begin(); miter != get_metv().end(); ++miter )
    {
        if ( *miter != NULL )
        {
            create_metrics_data_containers( *miter );
        }
    }
    for ( std::vector<Metric*>::const_iterator miter = get_ghost_metv().begin(); miter != get_ghost_metv().end(); ++miter )
    {
        if ( *miter != NULL )
        {
            create_metrics_data_containers( *miter );
        }
    }
}


void
Cube::create_metrics_data_containers( Metric* met )
{
    uint32_t ncid = fullcnodev.size();
    uint32_t ntid = locationv.size();
    met->set_dimensions( cnodev, root_cnodev, root_stnv, stnv, location_groupv, locationv, sysv );
    met->create_data_container( ncid, ntid );
    assign_ids( met );
}

void
Cube::collect_whole_subtree_for_callpaths()
{
    for ( std::vector<Cnode*>::iterator citer = root_cnodev.begin(); citer != root_cnodev.end(); ++citer )
    {
        Cnode* _c = *citer;
        if ( _c->is_whole_tree_collected() )
        {
            continue;
        }
        _c->fill_whole_tree_vector();
    }
}

void
Cube::collect_whole_subtree_for_systemtree()
{
    for ( std::vector<SystemTreeNode*>::iterator siter = root_stnv.begin(); siter != root_stnv.end(); ++siter )
    {
        SystemTreeNode* _s = *siter;
        if ( _s->is_whole_tree_collected() )
        {
            continue;
        }
        _s->fill_whole_tree_vector();
    }
}



// -------------------ANALYSIS PART  END -------------------------


// ------------------- ID ASSIGNATION START -----------------------
void
Cube::assign_ids( Metric* met )
{
    this->assign_id_metrics();
    this->create_calltree_ids( met );                                                                                            // caltree depending, system is always exclusive and 0
    this->create_system_ids();                                                                                                   // caltree depending, system is always exclusive and 0
}

void
Cube::assign_id_metrics()
{
}


void
Cube::create_calltree_ids( Metric* met )
{
    IDdeliverer*         ids                 = new IDdeliverer();
    row_of_objects_t*    _row                = NULL;
    std::vector<Cnode*>* _roots_to_enumerate = NULL;
    if ( is_clustering_on() )
    {
        _roots_to_enumerate = &original_root_cnodev;
    }
    else
    {
        _roots_to_enumerate = &root_cnodev;
    }
    for ( std::vector<Cnode*>::iterator c_iter = _roots_to_enumerate->begin(); c_iter < _roots_to_enumerate->end(); ++c_iter )
    {
        _row = met->create_calltree_id_maps( ids, ( *c_iter ), _row );
    }

    delete ids;
    delete _row;
}


void
Cube::create_system_ids()
{
    return;                                                                                            // currently no spezial dealing with Thread IDs is needed.
}





// -------------- Call tree modification calls


void
Cube::reroot_cnode( Cnode* _cnode )
{
    if ( _cnode == NULL )                                                                                            // ignore everything, if the parameter it NULL
    {
        cerr << "Call Cube::reroot_cnode( Cnode* _cnode) with _cnode== NULL" << endl;
        return;
    }

    // add whole subtree into map of "bein future tree"
    std::map<cube::Cnode*, bool> future_tree;
    std::list<cube::Cnode*>      future_tree_list;
    future_tree[ _cnode ] = true;
    future_tree_list.push_back( _cnode );
    for ( std::list<cube::Cnode*>::iterator iter = future_tree_list.begin(); iter != future_tree_list.end(); ++iter )
    {
        const cube::Cnode* _c = *iter;
        for ( size_t child_i = 0; child_i < _c->num_children(); ++child_i )
        {
            future_tree_list.push_back( _c->get_child( child_i ) );
            future_tree[ _c->get_child( child_i ) ] = true;
        }
    }


    // Now one has to hide all elements from cnodev , which are not marked as part of future tree
    // Element are not getting lost, coz cnodevfull keeps all elements and delete operator acts on it.
    std::map<cube::Cnode*, bool>::iterator map_it = future_tree.end();
    for ( vector<Cnode*>::iterator _it = cnodev.begin(); _it != cnodev.end(); ++_it )
    {
        map_it = future_tree.find( *_it );

        if ( map_it == future_tree.end() )
        {
            ( *_it )->hide( false );
        }
    }

    root_cnodev.clear();
    root_cnodev.push_back( _cnode );
    _cnode->set_parent( NULL );
}




void
Cube::prune_cnode( Cnode* _cnode )
{
    if ( _cnode == NULL )                                                                                            // ignore everything, if the parameter it NULL
    {
        cerr << "Call Cube::prune_cnode( Cnode* _cnode) with _cnode== NULL" << endl;
        return;
    }
    if ( _cnode->get_parent() == NULL )                                                                                            // if it is a root already, do nothing
    {
        vector<Cnode*>::iterator it = find( root_cnodev.begin(), root_cnodev.end(), _cnode );
        ( *it )->hide();                                                                                            // hide it and all its children (needed to avoid not necesarry storing if copied)
        root_cnodev.erase( it );
    }
    else                                                                                            // parent doesnt
    {
        _cnode->hide();                                                                             // hide it and all its children (needed to avoid not necesarry storing if copied)
    }
}



void
Cube::set_cnode_as_leaf( Cnode* _cnode )
{
    if ( _cnode == NULL )                                                                                            // ignore everything, if the parameter it NULL
    {
        cerr << "Call Cube::set_cnode_as_leaf( Cnode* _cnode) with _cnode== NULL" << endl;
        return;
    }

    _cnode->set_as_leaf();
}






// -------------------- ID ASSIGNATION END -------------------------




void
Cube::write( const string& filename )
{
    ofstream out;
    out.open( filename.c_str() );
    if ( !out.good() )
    {
        throw RuntimeError( "Cube::write(string): file name doesn't exist" );
    }
    out << *this;
    out.close();
}

int
Cube::max_num_thrd() const
{
    unsigned int ret = 0;
    for ( unsigned int i = 0; i < stnv.size(); ++i )
    {
        int _num_of_groups = stnv[ i ]->num_groups();
        for ( int j = 0; j < _num_of_groups; ++j )
        {
            const LocationGroup* p = stnv[ i ]->get_location_group( j );
            if ( p->num_children() > ret )
            {
                ret = p->num_children();
            }
        }
    }
    return ret;
}
/**
 * \details Gives a root metric.
 */
Metric*
Cube::get_root_met( Metric* met )
{
    if ( met == NULL )
    {
        return 0;
    }
    while ( met->get_parent() != NULL )
    {
        met = met->get_parent();
    }
    return met;
}
/**
 * \details Gives not NULL only if cn exists in a cube..
 */
Cnode*
Cube::get_cnode( Cnode& cn ) const
{
    const vector<Cnode*>& _cnodev = get_cnodev();
    for ( unsigned int i = 0; i < _cnodev.size(); ++i )
    {
        if ( *_cnodev[ i ] == cn )
        {
            return _cnodev[ i ];
        }
    }
    return NULL;
}
/**
 * \details Gives not NULL only if mach exists in a cube..
 */
Machine*
Cube::get_mach( Machine& mach ) const
{
    const vector<Machine*>& _root_stnv = get_machv();
    for ( unsigned int i = 0; i < _root_stnv.size(); ++i )
    {
        if ( *_root_stnv[ i ] == mach )
        {
            return _root_stnv[ i ];
        }
    }
    return NULL;
}

/**
 * \details Gives not NULL only if node exists in a cube..
 */
Node*
Cube::get_node( Node& node ) const
{
    const vector<Node*>& _nodev = get_nodev();
    for ( unsigned int i = 0; i < _nodev.size(); ++i )
    {
        if ( *_nodev[ i ] == node )
        {
            return _nodev[ i ];
        }
    }
    return NULL;
}



void
Cube::writeXML_header( ostream& out, bool cube3_export, bool write_ghost_metrics )
{
    if ( cube3_export && !system_tree_cube3_compatibility_check() )
    {
        throw Cube3SystemTreeMismatchError( "System tree cannot be represented in cube3 format." );
    }



    const vector<Cnode*>&          cnv      = get_root_cnodev();
    const vector<SystemTreeNode*>& _stnv    = get_root_stnv();
    const vector<Metric*>&         _rmetv   = get_root_metv();
    const vector<Region*>&         rv       = get_regv();
    const map<string, string>&     _attrs   = get_attrs();
    const vector<string>&          _mirrors = get_mirrors();




    if ( !cube3_export )
    {
        def_attr( CUBELIB_LIBRARY_VERSION_KEY, CUBELIB_FULL_NAME " r" CUBELIB_REVISION_STRING );
        def_attr( CUBEPL_VERSION_KEY, CUBEPL_VERSION );
        def_attr( CUBELIB_VERSION_KEY, CUBELIB_VERSION );
        def_attr( CUBELIB_ANCHOR_VERSION_KEY, CUBELIB_ANCHOR_VERSION );
    }

    // xml header
    out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << '\n' << '\n';
    if ( cube3_export )
    {
        out << "<cube " << "version=\"3.0\">" << '\n';
    }
    else
    {
        out << "<cube " << "version=\"4.5\">" << '\n';
    }


    // metadata info
    map<string, string>::const_iterator ai;
    for ( ai = _attrs.begin(); ai != _attrs.end(); ++ai )
    {
        if ( (
                 ai->first.compare( CUBELIB_LIBRARY_VERSION_KEY ) == 0
                 ||
                 ai->first.compare( CUBEPL_VERSION_KEY ) == 0
                 ||
                 ai->first.compare( CUBELIB_VERSION_KEY ) == 0
                 ||
                 ai->first.compare( CUBELIB_ANCHOR_VERSION_KEY ) == 0
                 )
             && cube3_export )
        {
            continue;
        }
        out << "  <attr " << "key=" << "\"" << services::escapeToXML( ai->first ) << "\" "
            << "value=" << "\"" << services::escapeToXML( ai->second ) << "\"/>" << '\n';
    }
    // mirrored URLs
    out << "  <doc>" << '\n';
    out << "    <mirrors>" << '\n';
    for ( unsigned int i = 0; i < _mirrors.size(); ++i )
    {
        out << "      <murl>" << services::escapeToXML( _mirrors[ i ] ) << "</murl>" << '\n';
    }
    out << "    </mirrors>" << '\n';
    out << "  </doc>" << '\n';


    // metrics
    out << "  <metrics";
    if ( get_metrics_title() != "" )
    {
        out << " title=\"" << services::escapeToXML( get_metrics_title() ) << "\"";
    }
    out << ">" << '\n';
    for ( unsigned int i = 0; i < _rmetv.size(); i++ )                                                                                            // write metrics
    {
        if ( _rmetv[ i ] == NULL )
        {
            continue;
        }
        if ( !_rmetv[ i ]->isInactive() )
        {
            _rmetv[ i ]->writeXML( out, cube3_export );
        }
    }
    if ( write_ghost_metrics )
    {
        for ( unsigned int i = 0; i < ghost_metv.size(); i++ )                                                                                        // write metrics
        {
            if ( ghost_metv[ i ] == NULL )
            {
                continue;
            }
            if ( !ghost_metv[ i ]->isInactive() )
            {
                ghost_metv[ i ]->writeXML( out, cube3_export );
            }
        }
    }
    out << "  </metrics>"  << '\n';

    // programfor
    out << "  <program";
    if ( get_calltree_title() != "" )
    {
        out << " title=\"" << services::escapeToXML( get_calltree_title() ) << "\"";
    }
    out << ">" << '\n';

    for ( unsigned int i = 0; i < rv.size(); ++i )     // write regions
    {
        rv[ i ]->writeXML( out, cube3_export  );
    }

    for ( unsigned int i = 0; i < cnv.size(); ++i )    // write cnodes
    {
        cnv[ i ]->writeXML( out, cube3_export );
    }

    out << "  </program>"   << '\n';

    // system
    out << "  <system";
    if ( get_systemtree_title() != "" )
    {
        out << " title=\"" << services::escapeToXML( get_systemtree_title() ) << "\"";
    }
    out << ">" << '\n';
    for ( unsigned int i = 0; i < _stnv.size(); ++i )     // write system resources
    {
        _stnv[ i ]->writeXML( out, cube3_export );
    }

    // topologies
    out << "    <topologies>" << '\n';
    for ( unsigned int i = 0; i < get_cartv().size(); ++i ) // write topologies
    {
        get_cart( i )->writeXML( out, cube3_export  );
    }
    out << "    </topologies>" << '\n';

    out << "  </system>" << '\n';
    return;
}


void
Cube::writeXML_data( ostream& out )
{
    out << "<severity>"   << '\n';

    for ( unsigned int i = 0; i < metv.size(); ++i )
    {
        if ( metv[ i ] == NULL )
        {
            continue;
        }
        if ( !metv[ i ]->isInactive() )
        {
            metv[ i ]->writeXML_data( out, cnodev, locationv );
        }
    }
    out << "</severity>"  << '\n';
}

void
Cube::writeXML_closing( ostream& out )
{
    out << "</cube>"      << '\n';
}






std::string
Cube::get_statistic_name()
{
    return get_attr( "statisticfile" );
}




bool
Cube::is_flat_tree_enabled()
{
    std::string res = get_attr( "statisticfile" );
    return ( res == "" || res  == "yes" ) ? true : false;
}


uint32_t
Cube::get_number_void_processes() const
{
    uint32_t num_void_procs = 0;
    for ( size_t i = 0; i < location_groupv.size(); ++i )
    {
        LocationGroup* proc  = location_groupv[ i ];
        std::string    _name = proc->get_name();
        if ( _name.find( "VOID" ) != string::npos )
        {
            num_void_procs++;
        }
    }
    return num_void_procs;
}

uint32_t
Cube::get_number_void_threads() const
{
    uint32_t num_void_thrds = 0;
    for ( size_t i = 0; i < locationv.size(); ++i )
    {
        LocationGroup* proc = locationv[ i ]->get_parent();
        if ( proc->get_name().find( "VOID" ) != string::npos )
        {
            num_void_thrds++;
        }
    }
    return num_void_thrds;
}




void
Cube::select_cubepl_engine( string version )
{
    enum CubePlVersionKey { Version0 = 0, Version1 = 1, Version2 = 2 };
    CubePlVersionKey _version = Version2;                          // default;
    if ( version.compare( "1.1" ) == 0 )
    {
        _version = Version2;
    }
    else
    if ( version.compare( "1.0" ) == 0 )
    {
        _version = Version1;
    }
    else
    if ( version.compare( "0.0" ) == 0 )
    {
        _version = Version0;
    }
    else
    {
        throw CubePLUnsupportedVersionError( version );
    }

    switch ( _version )
    {
        case Version0:
            delete cubepl_memory_manager;
            delete cubepl_driver;
            cubepl_memory_manager = new CubePL0MemoryManager();
            cubepl_driver         = new cubeplparser::CubePL0Driver( this );
            break;
        case Version2:
            delete cubepl_memory_manager;
            cubepl_memory_manager = new CubePL2MemoryManager();
            break;
        case Version1:
        default:
            break;
    }
}

bool
Cube::test_cubepl_expression( std::string& expression,
                              std::string& error_code )

{
    return cubepl_driver->test( expression, error_code );
}



void
Cube::setup_cubepl_memory()
{
    cubepl_memory_manager->get_memory_initializer()->memory_setup( this );
}



void
Cube::compile_derived_metric_expressions()
{
    std::string errors;

    vector<Metric*> _metv;
    for ( vector<Metric*>::iterator iter = metv.begin(); iter != metv.end(); ++iter )
    {
        if ( *iter == NULL )
        {
            continue;
        }
        _metv.push_back( *iter );
    }
    for ( vector<Metric*>::iterator iter = ghost_metv.begin(); iter != ghost_metv.end(); ++iter )
    {
        if ( *iter == NULL )
        {
            continue;
        }
        _metv.push_back( *iter );
    }



    for ( vector<Metric*>::iterator iter = _metv.begin(); iter != _metv.end(); ++iter )
    {
        Metric*     met = *iter;
        std::string derived_metric_init_error;

        if (
            met->get_type_of_metric() == CUBE_METRIC_POSTDERIVED
            ||
            met->get_type_of_metric() == CUBE_METRIC_PREDERIVED_EXCLUSIVE
            ||
            met->get_type_of_metric() == CUBE_METRIC_PREDERIVED_INCLUSIVE
            )
        {
            met->setMemoryManager( cubepl_memory_manager );
            std::string init_expression     = met->get_init_expression();
            std::string cubepl_init_program = string( "<cubepl>" ) + init_expression + string( "</cubepl>" );
            if (
                cubepl_driver->test( cubepl_init_program, derived_metric_init_error )
                )
            {
                stringstream       strin2( cubepl_init_program );
                GeneralEvaluation* formula2 = cubepl_driver->compile( &strin2, &cerr );
                UTILS_DEBUG_ONLY(
                    if ( formula2 != NULL && services::is_metric_present( cubepl_metric_verbose_execution,  met->get_uniq_name() ) )
                {
                    std::cout << "CubePL initialization expression of metric " << met->get_uniq_name() << ":" << std::endl;
                    formula2->print();
                    std::cout << std::endl;
                    formula2->set_verbose_execution(  services::is_metric_present( cubepl_metric_verbose_execution,  met->get_uniq_name() )  );
                }
                    )
                met->setInitEvaluation( formula2 );
            }
            else
            {                                                                                            // cannot create metric, cou compilerr reported an error (??? )
                cerr << " Error in the compilation of expression for metric " << met->get_uniq_name() << ": " << std::endl;
                cerr << " Cannot compile an initialization expression : " << endl << init_expression <<  endl << "because of the following error: " <<  derived_metric_init_error << endl;

                errors += "Error in: ";
                errors += met->get_uniq_name();
                errors += " : ";
                errors += derived_metric_init_error;
                errors += "\n\n";
            }
        }
    }

    for ( vector<Metric*>::iterator iter = _metv.begin(); iter != _metv.end(); ++iter )
    {
        Metric*     met = *iter;
        std::string derived_metric_error;
        if (
            met->get_type_of_metric() == CUBE_METRIC_POSTDERIVED
            ||
            met->get_type_of_metric() == CUBE_METRIC_PREDERIVED_EXCLUSIVE
            ||
            met->get_type_of_metric() == CUBE_METRIC_PREDERIVED_INCLUSIVE
            )
        {
            std::string expression     = met->get_expression();
            std::string cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
            if ( cubepl_driver->test( cubepl_program, derived_metric_error )
                 )
            {
                stringstream       strin1( cubepl_program );
                GeneralEvaluation* formula1 = cubepl_driver->compile( &strin1, &cerr );
                UTILS_DEBUG_ONLY(
                    if ( formula1 != NULL && services::is_metric_present( cubepl_metric_verbose_execution,  met->get_uniq_name() ) )
                {
                    std::cout << "CubePL expression of metric " << met->get_uniq_name() << ":" << std::endl;
                    formula1->print();
                    std::cout << std::endl;
                    formula1->set_verbose_execution( services::is_metric_present( cubepl_metric_verbose_execution,  met->get_uniq_name() )  );
                }
                    )
                if ( formula1 == NULL )
                {
                    cerr << "Warning: Metric " << met->get_uniq_name() << " has an empty CubePL expression. It will return only 0." << endl;
                }
                met->setEvaluation( formula1 );
            }
            else
            {                                                                                            // cannot create metric, cou compilerr reported an error (??? )
                cerr << " Error in the compilation of expression for metric : " << met->get_uniq_name() << endl;
                cerr << " Cannot compile  an expression : " << endl << expression <<  endl << "because of the following error: " <<  derived_metric_error << endl;

                errors += "Error in: ";
                errors += met->get_uniq_name();
                errors += " : ";
                errors += derived_metric_error;
                errors += "\n\n";
            }
        }
    }

    for ( vector<Metric*>::iterator iter = _metv.begin(); iter != _metv.end(); ++iter )
    {
        Metric*     met = *iter;
        std::string derived_metric_error;
        if (
            met->get_type_of_metric() == CUBE_METRIC_PREDERIVED_EXCLUSIVE
            ||
            met->get_type_of_metric() == CUBE_METRIC_PREDERIVED_INCLUSIVE
            )
        {
            std::string expression     = met->get_aggr_plus_expression();
            std::string cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
            if ( cubepl_driver->test( cubepl_program, derived_metric_error )
                 )
            {
                stringstream       strin1( cubepl_program );
                GeneralEvaluation* formula1 = cubepl_driver->compile( &strin1, &cerr );
                UTILS_DEBUG_ONLY(
                    if ( formula1 != NULL && services::is_metric_present( cubepl_metric_verbose_execution,  met->get_uniq_name() ) )
                {
                    std::cout << "CubePL expression for the operator \"+\" of metric " << met->get_uniq_name() << ":" << std::endl;
                    formula1->print();
                    std::cout << std::endl;
                    formula1->set_verbose_execution( services::is_metric_present( cubepl_metric_verbose_execution,  met->get_uniq_name() )  );
                }
                    )
                met->setAggrPlusEvaluation( formula1 );
            }
            else
            {                                                                                            // cannot create metric, cou compilerr reported an error (??? )
                cerr << " Error in the compilation of plus-aggregation expression for metric : " << met->get_uniq_name() << endl;
                cerr << " Cannot compile  an expression : " << endl << expression <<  endl << "because of the following error: " <<  derived_metric_error << endl;

                errors += "Error in: ";
                errors += met->get_uniq_name();
                errors += " : ";
                errors += derived_metric_error;
                errors += "\n\n";
            }

            expression     = met->get_aggr_aggr_expression();
            cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
            if ( cubepl_driver->test( cubepl_program, derived_metric_error )
                 )
            {
                stringstream       strin1( cubepl_program );
                GeneralEvaluation* formula1 = cubepl_driver->compile( &strin1, &cerr );
                UTILS_DEBUG_ONLY(
                    if ( formula1 != NULL && services::is_metric_present( cubepl_metric_verbose_execution,  met->get_uniq_name() ) )
                {
                    std::cout << "CubePL expression for the operator \"+\" of metric " << met->get_uniq_name() << ":" << std::endl;
                    formula1->print();
                    std::cout << std::endl;
                    formula1->set_verbose_execution( services::is_metric_present( cubepl_metric_verbose_execution,  met->get_uniq_name() )  );
                }
                    )
                met->setAggrAggrEvaluation( formula1 );
            }
            else
            {                                                                                            // cannot create metric, cou compilerr reported an error (??? )
                cerr << " Error in the compilation of aggr-aggregation expression for metric : " << met->get_uniq_name() << endl;
                cerr << " Cannot compile  an expression : " << endl << expression <<  endl << "because of the following error: " <<  derived_metric_error << endl;

                errors += "Error in: ";
                errors += met->get_uniq_name();
                errors += " : ";
                errors += derived_metric_error;
                errors += "\n\n";
            }
        }
        if (
            met->get_type_of_metric() == CUBE_METRIC_PREDERIVED_INCLUSIVE
            )
        {
            std::string expression     = met->get_aggr_minus_expression();
            std::string cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
            if ( cubepl_driver->test( cubepl_program, derived_metric_error )
                 )
            {
                stringstream       strin1( cubepl_program );
                GeneralEvaluation* formula1 = cubepl_driver->compile( &strin1, &cerr );
                UTILS_DEBUG_ONLY(
                    if ( formula1 != NULL && services::is_metric_present( cubepl_metric_verbose_execution,  met->get_uniq_name() ) )
                {
                    std::cout << "CubePL expression for the operator \"-\" of metric " <<  met->get_uniq_name() << ":" << std::endl;
                    formula1->print();
                    std::cout << std::endl;
                    formula1->set_verbose_execution( services::is_metric_present( cubepl_metric_verbose_execution,  met->get_uniq_name() )  );
                }
                    )

                met->setAggrMinusEvaluation( formula1 );
            }
            else
            {                                                                                            // cannot create metric, cou compilerr reported an error (??? )
                cerr << " Error in the compilation of minus-aggregation expression for metric : " << met->get_uniq_name() << endl;
                cerr << " Cannot compile  an expression : " << endl << expression <<  endl << "because of the following error: " <<  derived_metric_error << endl;

                errors += "Error in: ";
                errors += met->get_uniq_name();
                errors += " : ";
                errors += derived_metric_error;
                errors += "\n\n";
            }
        }
    }

    // now initialize all metrics
    for ( vector<Metric*>::iterator iter = _metv.begin(); iter != _metv.end(); ++iter )
    {
        Metric* met = *iter;
        met->initialize();
    }
}




vector<string>
Cube::get_misc_data()
{
    return filefinder->getAllData();
}


vector<char>
Cube::get_misc_data( string& dataname )
{
    int   ffile  = -1;
    char* buffer = NULL;
    try
    {
        fileplace_t data = filefinder->getMiscData( dataname );
        ffile = open(  data.first.c_str(), O_RDONLY  );
        if ( ffile == -1 )
        {
            throw NoFileInTarError( "Cannot find file " + dataname );
        }
        if ( ( off_t )data.second.first != lseek( ffile, data.second.first, SEEK_CUR ) )
        {
            cerr << "Cannot seek to the miscellaneous data " << dataname << " in the cube " <<  cubename << endl;
            close( ffile );
            throw FatalError( "Cannot seek to the metadata " + dataname + " of cube " + cubename );
        }
        buffer = new char[ data.second.second ];                                                                                            // we extend the buffer for one symbol to create a legal C-like string, with 0 at the end
        memset( buffer, 0, data.second.second );
        if ( ( int )data.second.second != read( ffile, buffer, data.second.second ) )
        {
            cerr << "Error while reading miscellaneous data " << dataname << " stored in the cube " <<  cubename << endl;
            close( ffile );
            throw RuntimeError( "Error while reading miscellaneous data " + dataname + " of cube " + cubename );
        }
        close( ffile );
        vector<char> to_return( buffer, buffer + data.second.second );
        delete[] buffer;
        return to_return;
    }
    catch ( const NoFileInTarError& err )
    {
        close( ffile );
        delete[] buffer;
        vector<char> to_return;
        return to_return;
    }
}

void
Cube::write_misc_data( string& dataname, const char* buffer, size_t len )
{
    fileplace_t data  = filefinder->getMiscData( dataname );
    FILE*       ffile = fopen( data.first.c_str(), "wb+" );
    if ( ffile == NULL )
    {
        perror( "Error opening file" );
        cerr << "Cannot create file "  <<  data.first.c_str() << "  to store the miscellaneous data " << dataname << " in the cube " <<  cubename << endl;
        throw FatalError( "Cannot store the metadata " + dataname + " of cube " + cubename );
    }
    if ( fseeko( ffile, data.second.first, SEEK_SET ) != 0 )
    {
        cerr << "Cannot seek to the miscellaneous data " << dataname << " in the cube " <<  cubename << endl;
        fclose( ffile );
        throw FatalError( "Cannot seek to the metadata " + dataname + " of cube " + cubename );
    }
    if ( len != fwrite( buffer, 1, len, ffile ) )
    {
        cerr << "Error while reading miscellaneous data " << dataname << " stored in the cube " <<  cubename << endl;
        fclose( ffile );
        throw RuntimeError( "Error while reading miscellaneous data " + dataname + " of cube " + cubename );
    }
    fclose( ffile );
}

void
Cube::write_misc_data( string& dataname, vector<char>& data )
{
    char* tmp = new char[ data.size() ];
    for ( size_t i = 0; i < data.size(); ++i )
    {
        tmp[ i ] = data[ i ];
    }
    write_misc_data( dataname, tmp, data.size() );
    delete[] tmp;
}



namespace cube
{
/**
 * \details Writes a xml .cube file. First general header, then structure of every dimension and then the data.
 */
ostream&
operator<<( ostream& out,  Cube& cube )
{
    try
    {
        cube.writeXML_header( out, true );
        cube.writeXML_data( out );
        cube.writeXML_closing( out );
    }
    catch ( const Cube3SystemTreeMismatchError& error )
    {
        cerr << error.what() << endl;
        throw;
    }
    return out;
}
/**
 * \details Let "driver" to read the xml .cube file and creates a cube.
 */
cube::CubeIstream&
operator>>( cube::CubeIstream& in, Cube& cb )
{
    cubeparser::Driver* driver = NULL;
    try {
        driver = new cubeparser::Driver();
        driver->parse_stream( in, cb );
    }
    catch ( const RuntimeError& error )
    {
        cerr << error.what() << endl;
        delete driver;
        driver = NULL;
        throw;
    }
    delete driver;

    cb.setGlobalMemoryStrategy( cube::CUBE_ALL_IN_MEMORY_STRATEGY );

    return in;
}

/**
 * \details Let "driver" to read the xml .cube file and creates a cube.
 */
std::istream&
operator>>( std::istream& in, Cube& cb )
{
    cube::CubeIstream   _in( in );
    cubeparser::Driver* driver = NULL;
    try {
        driver = new cubeparser::Driver();
        driver->parse_stream( _in, cb );
    }
    catch ( const RuntimeError& error )
    {
        cerr << error.what() << endl;
        delete driver;
        driver = NULL;
        throw;
    }
    delete driver;

    cb.setGlobalMemoryStrategy( cube::CUBE_ALL_IN_MEMORY_STRATEGY );

    return in;
}


bool
Cube::system_tree_cube3_compatibility_check()
{
    const vector<SystemTreeNode*>& _stnv = get_non_root_stnv();
    for ( vector<SystemTreeNode*>::const_iterator iter = _stnv.begin(); iter != _stnv.end(); ++iter )
    {
        if ( ( *iter )->get_parent() == NULL )
        {
            throw RuntimeError( "Non root system tree node has a NULL parent. Something is wrong." );
        }
        if ( ( *iter )->get_parent()->get_parent() != NULL )                                                                                                // case, if it is more than 2 level.
        {
            return false;
        }
        if ( ( *iter )->num_children() != 0 )                                                                                                // case, if it there are subsystem tree nodes. Processes are stored in groups.
        {
            return false;
        }
    }
    return true;
}
}
