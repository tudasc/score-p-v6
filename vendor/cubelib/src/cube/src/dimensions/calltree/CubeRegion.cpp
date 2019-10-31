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
**  Copyright (c) 2015                                                     **
**  RWTH Aachen University, JARA-HPC                                       **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/



/**
 * \file CubeRegion.cpp
 * \brief  Defines a xml-representation of a region in a .cube file.
 ********************************************/

#include "config.h"
#include <iostream>
#include <sstream>

#include "CubeConnection.h"
#include "CubeRegion.h"
#include "CubeServices.h"

using namespace std;
using namespace cube;
using namespace services;

Region::Region( const std::string& name,
                const std::string& mangled_name,
                const std::string& paradigm,
                const std::string& role,
                long               begln,
                long               endln,
                const std::string& url,
                const std::string& descr,
                const std::string& mod,
                uint32_t           id )
    : SerializableVertex( id ), name( name ), mangled_name( mangled_name ), paradigm( paradigm ), role( role ), begln( begln ), endln( endln ),
    url( url ), descr( descr ), mod( mod )
{
    subroutines_of_region = false;
}



void
Region::add_cnode( Cnode* cnode )
{
    for ( unsigned int i = 0; i < cnodev.size(); ++i )
    {
        if ( cnode == cnodev[ i ] )
        {
            return;
        }
    }
    cnodev.push_back( cnode );
}

void
Region::writeXML( ostream& out, bool cube3export ) const
{
    out << "    <region id=\"" << get_id() << "\" " << "mod=\""
        << escapeToXML( get_mod() )  << "\" "  << "begin=\"" << get_begn_ln() << "\" "
        << "end=\"" << get_end_ln() <<  "\">" <<  '\n';
    out << "      <name>"
        << escapeToXML( get_name() )
        << "</name>" <<  '\n';
    if ( !cube3export )
    {
        out << "      <mangled_name>"
            << escapeToXML( get_mangled_name() )
            << "</mangled_name>" <<  '\n';
        out << "      <paradigm>"
            << escapeToXML( get_paradigm() )
            << "</paradigm>" <<  '\n';
        out << "      <role>"
            << escapeToXML( get_role() )
            << "</role>" <<  '\n';
    }
    out << "      <url>" << escapeToXML( get_url() ) << "</url>" <<  '\n';
    out << "      <descr>"
        << escapeToXML( get_descr() )
        << "</descr>" <<  '\n';
    writeAttributes( out, "      ", cube3export  );
    out << "    </region>" <<  '\n';
}


namespace cube
{
bool
operator==( const Region& a, const Region& b )
{
    return ( a.get_name() == b.get_name() )
           &&
           ( a.get_mod() == b.get_mod() )
           &&
           ( a.get_begn_ln() == b.get_begn_ln() )
           &&
           ( a.get_end_ln() == b.get_end_ln() )
    ;
}
}

void
cube::Region::pack( Connection& connection ) const
{
    SerializableVertex::pack( connection );

    connection << name;
    connection << mangled_name;
    connection << paradigm;
    connection << role;
    connection << int64_t( begln );
    connection << int64_t( endln );
    connection << url;
    connection << descr;
    connection << mod;
    connection << uint8_t( subroutines_of_region ? 1 : 0 );
}

Serializable*
cube::Region::create( Connection& connection,
                      const CubeProxy& )
{
    return new Region( connection );
}

cube::Region::Region( Connection& connection )
    : SerializableVertex( connection )
{
    connection >> name;
    connection >> mangled_name;
    connection >> paradigm;
    connection >> role;
    begln = connection.get<int64_t>();
    endln = connection.get<int64_t>();
    connection >> url;
    connection >> descr;
    connection >> mod;
    subroutines_of_region = connection.get<uint8_t>();
}

std::string
cube::Region::get_serialization_key() const
{
    return get_static_serialization_key();
}

std::string
cube::Region::get_static_serialization_key()
{
    return "Region";
}
