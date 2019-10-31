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
 * \file CubeLocation.cpp
 * \brief Defines a xml-output of a location description in a .cube file.
 *
 ********************************************/

#include "config.h"

#include "CubeLocation.h"

#include <cassert>
#include <iostream>
#include <sstream>

#include "CubeConnection.h"
#include "CubeError.h"
#include "CubeProxy.h"
#include "CubeServices.h"

using namespace std;
using namespace cube;
using namespace services;


Location::Location( const std::string& name,
                    int                rank,
                    LocationGroup*     proc,
                    LocationType       type,
                    uint32_t           id,
                    uint32_t           sysid )
    : Sysres( ( Sysres* )proc, name, id, sysid ), rank( rank ), type( type )
{
    kind = CUBE_LOCATION;
}








std::string
Location::get_type_as_string() const
{
    switch ( get_type() )
    {
        case cube::CUBE_LOCATION_TYPE_CPU_THREAD:
            return "thread";
        case cube::CUBE_LOCATION_TYPE_GPU:
            return "gpu";
        case cube::CUBE_LOCATION_TYPE_METRIC:
            return "metric";
        default:
            return "not supported";
    }
}


LocationType
Location::getLocationType( std::string type )
{
    if ( type.compare( "thread" ) == 0 )
    {
        return cube::CUBE_LOCATION_TYPE_CPU_THREAD;
    }
    if ( type.compare( "gpu" ) == 0 )
    {
        return cube::CUBE_LOCATION_TYPE_GPU;
    }
    if ( type.compare( "metric" ) == 0 )
    {
        return cube::CUBE_LOCATION_TYPE_METRIC;
    }
    throw AnchorSyntaxError( "Location type " + type + " is not supported!" );
}


void
Location::writeXML( ostream& out,
                    bool     cube3export  ) const
{
    if ( cube3export )
    {
        out << indent() << "    <thread Id=\"" << get_id() << "\">" <<  '\n';
    }
    else
    {
        out << indent() << "    <location Id=\"" << get_id() << "\">" <<  '\n';
    }
    out << indent() << "      <name>" << escapeToXML( get_name() ) << "</name>\n";
    out << indent() << "      <rank>" << get_rank() << "</rank>\n";
    if ( !cube3export )
    {
        out << indent() << "    <type>" << get_type_as_string() << "</type>" <<  '\n';
    }
    writeAttributes( out,  indent() + "    ", cube3export  );
    if ( cube3export )
    {
        out << indent() << "    </thread>\n";
    }
    else
    {
        out << indent() << "    </location>\n";
    }
}


Serializable*
cube::Location::create( Connection&      connection,
                        const CubeProxy& cubeProxy )
{
    return new Location( connection, cubeProxy );
}

void
cube::Location::pack( Connection& connection ) const
{
    Sysres::pack( connection );

    connection << int64_t( get_parent() ? get_parent()->get_sys_id() : int64_t( -1 ) );
    connection << int32_t( rank );
    connection << uint32_t( type );
}

cube::Location::Location( Connection&      connection,
                          const CubeProxy& cubeProxy )
    : Sysres( connection, cubeProxy )
{
    int64_t parent_id = connection.get<int64_t>();
    assert( parent_id == -1 || parent_id < ( int64_t )( cubeProxy.getSystemResources().size() ) );
    set_parent( parent_id == -1 ? NULL : cubeProxy.getSystemResources()[ parent_id ] );

    rank = connection.get<int32_t>();
    type = LocationType( connection.get<uint32_t>() );
}

std::string
cube::Location::get_serialization_key() const
{
    return get_static_serialization_key();
}

std::string
cube::Location::get_static_serialization_key()
{
    return "Location";
}
