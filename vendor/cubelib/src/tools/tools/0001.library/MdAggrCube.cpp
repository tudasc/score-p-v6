/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2018                                                **
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



#include "config.h"
#include "MdAggrCube.h"

#include "CnodeSubForest.h"
#include "AggregatedMetric.h"
#include "VisitorsMetric.h"
#include "CnodeMetric.h"
#include "PrintableCCnode.h"


#include "CCnode.h"
#include "CRegion.h"

#include "Cube.h"
#include "AggrCube.h"
#include "CubeError.h"
#include "CubeRegion.h"
#include "CubeMachine.h"
#include "CubeNode.h"
#include "CubeProcess.h"
#include "CubeThread.h"
#include "CubeCartesian.h"

using namespace cube;
using namespace std;

MdAggrCube::MdAggrCube()
    : AggrCube(), original_address( NULL )
{
}

MdAggrCube::MdAggrCube( Cube& copy,
                        int   cache_size )
    : AggrCube()
{
    map<Metric*, Metric* > metric_map_copy2new;
    map<Region*, Region* > region_map_copy2new;
    map<Cnode*,  Cnode*  > cnode_map_copy2new;


    // Copy metrics vector.
    for ( vector<Metric*>::const_iterator m = copy.get_metv().begin(); m != copy.get_metv().end(); ++m )
    {
        metric_map_copy2new[ *m ] =
            def_met( ( *m )->get_disp_name(), ( *m )->get_uniq_name(), ( *m )->get_dtype(),
                     ( *m )->get_uom(), ( *m )->get_val(), ( *m )->get_url(), ( *m )->get_descr(),
                     ( ( *m )->get_parent() == NULL ? NULL : metric_map_copy2new[ ( *m )->get_parent() ] ),
                     ( *m )->get_id() );
    }
    // Copy region vector.
    for ( vector<Region*>::const_iterator r = copy.get_regv().begin(); r != copy.get_regv().end(); ++r )
    {
        region_map_copy2new[ *r ] =
            def_region( ( *r )->get_name(), ( *r )->get_mangled_name(), ( *r )->get_paradigm(), ( *r )->get_role(), ( *r )->get_begn_ln(), ( *r )->get_end_ln(),
                        ( *r )->get_url(), ( *r )->get_descr(), ( *r )->get_mod(), ( *r )->get_id(),
                        cache_size );
    }
    // Copy callnode vector
    for ( vector<Cnode*>::const_iterator c = copy.get_cnodev().begin(); c != copy.get_cnodev().end(); ++c )
    {
        cnode_map_copy2new[ *c ] =
            def_cnode( region_map_copy2new[ ( *c )->get_callee() ], ( *c )->get_mod(),
                       ( *c )->get_line(),
                       ( ( *c )->get_parent() == NULL ? NULL : cnode_map_copy2new[ ( *c )->get_parent() ] ),
                       ( *c )->get_id(), cache_size );
    }


    map<SystemTreeNode*, SystemTreeNode*> stn_map;
    const std::vector<SystemTreeNode*>    _stns  =    copy.get_root_stnv();
    std::vector<SystemTreeNode*>          _stns2 = _stns;

    for ( size_t i = 0; i < _stns2.size(); i++ )
    {
        SystemTreeNode* _stn   = _stns2[ i ];
        SystemTreeNode* my_stn = def_system_tree_node( _stn, stn_map );
        for ( unsigned int j = 0; j < _stn->num_children(); j++ )
        {
            _stns2.push_back( _stn->get_child( j ) );
        }

        // create mapping _machine -> my_machine
        stn_map[ _stn ] = my_stn;
    }


    map<LocationGroup*, LocationGroup*> lg_map;
    std::vector<LocationGroup*>         _lgs =    copy.get_procv();
    for ( vector<LocationGroup*>::iterator lg_iter = _lgs.begin(); lg_iter != _lgs.end(); ++lg_iter )
    {
        LocationGroup* _lg   = *lg_iter;
        LocationGroup* my_lg = def_location_group( _lg, stn_map );
        // create mapping _process -> my_process
        lg_map[ _lg ] = my_lg;
    }

    map<Location*, Location*> locs_map;
    std::vector<Location*>    _locations =    copy.get_locationv();
    for ( vector<Location*>::iterator loc_iter = _locations.begin(); loc_iter != _locations.end(); ++loc_iter )
    {
        Location* _location   = *loc_iter;
        Location* my_location = def_location( _location, lg_map );
        // create mapping _thread -> my_thread
        locs_map[ _location ] = my_location;
    }


    // Copy the cartesian vector.
    vector<Cartesian*> _topos = copy.get_cartv();
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

    for ( vector<Metric*>::const_iterator m = copy.get_metv().begin(); m != copy.get_metv().end(); ++m )
    {
        for ( vector<Cnode*>::const_iterator c = copy.get_cnodev().begin(); c != copy.get_cnodev().end(); ++c )
        {
            for ( vector<Thread*>::const_iterator t = copy.get_thrdv().begin(); t != copy.get_thrdv().end(); ++t )
            {
                set_sev( metric_map_copy2new[ *m ], cnode_map_copy2new[ *c ], locs_map[ *t ],
                         copy.get_sev( *m, *c, *t ) );
            }
        }
    }
    original_address = &copy;
}

MdAggrCube::~MdAggrCube()
{
    for ( map< string, CnodeMetric* >::iterator it = cnode_metrics.begin();
          it != cnode_metrics.end(); ++it )
    {
        delete it->second;
    }
}

CnodeMetric*
MdAggrCube::add_cnode_metric( CnodeMetric* metric )
{
    CnodeMetric* already_there = NULL;
    metric->register_with( this );
    string                              metric_str = metric->stringify();
    map<string, CnodeMetric*>::iterator it         = cnode_metrics.find( metric_str );
    if ( it != cnode_metrics.end() )
    {
        already_there = it->second;
    }

    if ( already_there == NULL )
    {
        cnode_metrics.insert( pair<string, CnodeMetric*>(
                                  metric_str, metric ) );
        return metric;
    }
    else
    {
        delete metric;
        return already_there;
    }
}

CnodeMetric*
MdAggrCube::get_cnode_metric( std::string metric_str )
{
    map<string, CnodeMetric*>::iterator it = cnode_metrics.find( metric_str );
    if ( it == cnode_metrics.end() )
    {
        string::size_type pos = 0;
        if ( ( pos = metric_str.find( "@" ) ) != string::npos )
        {
            string handler = metric_str.substr( 0, pos );
            if ( handler == "basic" )
            {
                return add_cnode_metric(
                    new AggregatedMetric( metric_str ) );
            }
            else if ( handler == "visitors" )
            {
                return add_cnode_metric(
                    new VisitorsMetric( metric_str ) );
            }
            else
            {
                throw RuntimeError( "Do not know how to handle type " + handler );
            }
        }

        return add_cnode_metric( new AggregatedMetric( metric_str ) );
    }
    else
    {
        return it->second;
    }
}

CnodeSubForest*
MdAggrCube::get_forest()
{
    return new CnodeSubForest( this );
}

CubeMapping*
MdAggrCube::get_cube_mapping( unsigned int id )
const
{
    if ( id >= get_number_of_cubes() )
    {
        throw RuntimeError( "Invalid Mapping requested." );
    }
    return NULL;
}

unsigned int
MdAggrCube::get_number_of_cubes()
const
{
    return 1;
}

Region*
MdAggrCube::def_region( const string& name,
                        const string& mangled_name,
                        const string& paradigm,
                        const string& role,
                        long          begln,
                        long          endln,
                        const string& url,
                        const string& descr,
                        const string& mod,
                        uint32_t      id,
                        int           cache_size )
{
    Region* reg = new CRegion( name, mangled_name, paradigm, role, begln, endln, url, descr, mod, id,
                               cache_size );
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

Cnode*
MdAggrCube::def_cnode( Region*       callee,
                       const string& mod,
                       int           line,
                       Cnode*        parent,
                       uint32_t      id,
                       int           cache_size )
{
    Cnode* cnode = new PrintableCCnode( callee, mod, line, parent, id,
                                        cache_size );
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
    else if ( cnodev[ id ] )
    {
        throw RuntimeError( "Cnode with this ID exists" );
    }

    cnodev[ id ]     = cnode;
    fullcnodev[ id ] = cnode;
    cur_cnode_id     = fullcnodev.size();

    return cnode;
}
