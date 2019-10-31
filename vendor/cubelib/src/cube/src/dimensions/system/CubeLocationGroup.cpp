/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2016                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2009-2015                                                **
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



/**
 *
 * \file CubeLocationGroup.cpp
 * \brief Defines a method to save a xml-representation of a location group in a .cubex file.
 ********************************************/

#include "config.h"

#include <cassert>
#include <iostream>
#include <sstream>

#include "CubeConnection.h"
#include "CubeError.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeProxy.h"
#include "CubeServices.h"
#include "CubeSystemTreeNode.h"

using namespace std;
using namespace cube;
using namespace services;


LocationGroup::LocationGroup( const std::string& name,
                              SystemTreeNode*    stn,
                              int                rank,
                              LocationGroupType  type,
                              uint32_t           id,
                              uint32_t           sysid )
    : Sysres( name, id, sysid ), rank( rank ), type( type )
{
    kind   = CUBE_LOCATION_GROUP;
    parent = stn;
    if ( stn != NULL )
    {
        stn->add_location_group( this );
    }
    else
    {
        throw RuntimeError( "Location Group cannot have NULL as a parent value in the system tree node." );
    }
}
// /< Thread does have a rank.


std::string
LocationGroup::get_type_as_string() const
{
    switch ( get_type() )
    {
        case cube::CUBE_LOCATION_GROUP_TYPE_PROCESS:
            return "process";
        case cube::CUBE_LOCATION_GROUP_TYPE_METRICS:
            return "metrics";
        default:
            return "not supported";
    }
}


LocationGroupType
LocationGroup::getLocationGroupType( string type )
{
    if ( type.compare( "process" ) == 0 )
    {
        return cube::CUBE_LOCATION_GROUP_TYPE_PROCESS;
    }
    if ( type.compare( "metrics" ) == 0 )
    {
        return cube::CUBE_LOCATION_GROUP_TYPE_METRICS;
    }
    throw AnchorSyntaxError( "Location group type " + type + " is not supported!" );
}


void
LocationGroup::writeXML( ostream& out,
                         bool     cube3export ) const
{
    if ( cube3export )
    {
        out << indent() << "    <process Id=\"" << get_id() << "\">" <<  '\n';
    }
    else
    {
        out << indent() << "    <locationgroup Id=\"" << get_id() << "\">" <<  '\n';
    }
    out << indent() << "      <name>" << escapeToXML( get_name() ) << "</name>" <<  '\n';
    out << indent() << "      <rank>" << get_rank() << "</rank>" <<  '\n';
    if ( !cube3export )
    {
        out << indent() << "    <type>" << get_type_as_string() << "</type>" <<  '\n';
    }
    writeAttributes( out,  indent() + "    ", cube3export  );
    for ( unsigned int i = 0; i < num_children(); ++i )
    {
        const Location* thrd = get_child( i );
        thrd->writeXML( out, cube3export  );
    }
    if ( cube3export )
    {
        out << indent() << "    </process>" <<  '\n';
    }
    else
    {
        out << indent() << "    </locationgroup>" <<  '\n';
    }
}


Serializable*
cube::LocationGroup::create( Connection&      connection,
                             const CubeProxy& cubeProxy )
{
    return new LocationGroup( connection, cubeProxy );
}

void
cube::LocationGroup::pack( Connection& connection ) const
{
    Sysres::pack( connection );

    connection << int64_t( get_parent() ? get_parent()->get_sys_id() : int64_t( -1 ) );
    connection << int32_t( rank );
    connection << uint32_t( type );
}

std::string
cube::LocationGroup::get_serialization_key() const
{
    return get_static_serialization_key();
}

std::string
cube::LocationGroup::get_static_serialization_key()
{
    return "LocationGroup";
}

cube::LocationGroup::LocationGroup( Connection&      connection,
                                    const CubeProxy& cubeProxy )
    : Sysres( connection, cubeProxy )
{
    int64_t parent_id = connection.get<int64_t>();
    assert( parent_id == -1 || parent_id < ( int64_t )( cubeProxy.getSystemResources().size() ) );
    set_parent( parent_id == -1 ? NULL : cubeProxy.getSystemResources()[ parent_id ] );

    rank = connection.get<int32_t>();
    type = LocationGroupType( connection.get<uint32_t>() );
}

void
cube::LocationGroup::set_parent( Vertex* vertex )
{
    parent = vertex;
    if ( vertex == NULL )
    {
        return;
    }
    static_cast<SystemTreeNode*>( parent )->add_location_group( this );
}
