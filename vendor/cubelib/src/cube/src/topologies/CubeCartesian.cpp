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
 * \file CubeCartesian.cpp
 * \brief Defines a class and methods to handle a topology of a application.
 */
/************************************************
             Cartesian.cpp

************************************************/

#include "config.h"

#include "CubeCartesian.h"

#include <iostream>

#include "CubeConnection.h"
#include "CubeError.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeProxy.h"
#include "CubeServices.h"
#include "CubeSysres.h"
#include "CubeSystemTreeNode.h"
#include "CubeTypes.h"

using namespace std;
using namespace cube;


cube::Cartesian::Cartesian( Connection&      connection,
                            const CubeProxy& proxy )
{
    connection >> name;

    uint32_t ndims;
    connection >> ndims;
    this->ndims = ndims;

    for ( size_t i = 0; i < ndims; i++ )
    {
        uint32_t dimension_size;
        connection >> dimension_size;
        dimv.push_back( dimension_size );

        uint8_t dimension_periodicy;
        connection >> dimension_periodicy;
        periodv.push_back( dimension_periodicy == 1 ? true : false );
    }
    uint32_t numSysres = connection.get<uint32_t>();
    for ( uint32_t i = 0; i < numSysres; ++i )
    {
        uint32_t sys_id = connection.get<uint32_t>();
        assert( sys_id < proxy.getSystemResources().size() );
        Sysres* sysres = proxy.getSystemResources()[ sys_id ];
        assert( sysres );
        vector<long> coords;
        for ( size_t j = 0; j < ndims; ++j )
        {
            coords.push_back( connection.get<uint64_t>() );
        }
        sys2coordv.insert( make_pair( sysres, coords ) );
    }
}

void
cube::Cartesian::pack( Connection& connection ) const
{
    connection << name;
    connection << uint32_t( ndims );
    for ( size_t i = 0; i < ndims; i++ )
    {
        connection << uint32_t( dimv[ i ] );
        connection << uint8_t( periodv[ i ] ? 1 : 0 );
    }
    connection << uint32_t( sys2coordv.size() );
    for ( TopologyMap::const_iterator it = sys2coordv.begin();
          it != sys2coordv.end(); ++it )
    {
        assert( ndims == it->second.size() );
        connection << uint32_t( it->first->get_sys_id() );
        for ( size_t i = 0; i < ndims; ++i )
        {
            connection << uint64_t( it->second[ i ] );
        }
    }
}

std::string
cube::Cartesian::get_serialization_key() const
{
    return get_static_serialization_key();
}

std::string
cube::Cartesian::get_static_serialization_key()
{
    return "Cartesian";
}

/**
 * Sets a thread "sys" at  coordinates "coordtv"
 */
void
Cartesian::def_coords( const Sysres* sys, const vector<long>& coordv )
{
    sys2coordv.insert( TopologyMap::value_type( sys, coordv ) );
}






/**
 * Sets the name of the topology.
 */
void
Cartesian::set_name( const std::string& _name )
{
    name = _name;
}




bool
Cartesian::set_namedims( const std::vector<std::string> _namedims )
{
    if ( _namedims.size() == ndims )
    {
        namedims = _namedims;
        return true;
    }
    else
    {
        return false;
    }
}


bool
Cartesian::set_dim_name( const int _dim, const std::string& _name )
{
    if ( _dim >= 0 && _dim < ( int )ndims )
    {
        if ( _dim <= ( int )namedims.size() )
        {
            namedims.resize( _dim + 1 ); // resize vector to store name if needed
        }
        namedims[ _dim ] = _name;
        return true;
    }
    else
    {
        return false;
    }
}

const std::string
Cartesian::get_dim_name( const int dim )
{
    if ( dim >= 0 && dim < ( int )ndims )
    {
        return ( dim < ( int )namedims.size() ) ? namedims[ dim ] : "";
    }
    else
    {
        cerr << "Dimension index " << dim << " is bigger than number of dimensions " << ndims << endl;
        cerr << "Return empty string" << endl;
        return "";
    }
}


/**
 * Gets a coordinates of given resource.
 */

const vector<long>&
Cartesian::get_coordv( Sysres* sys ) const
{
    TopologyMap::const_iterator itr;
    itr = sys2coordv.find( sys );
    if ( itr != sys2coordv.end() )
    {
        return itr->second;
    }
    else
    {
        throw RuntimeError( "Cartesian::get_coordv(): coordinates for the given resource not found!" );
    }
}


/**
 * Gets a coordinates of given resource.
 */

const vector<vector<long> >
Cartesian::get_all_coordv( Sysres* sys ) const
{
    vector< vector < long > > to_return;

    TopologyMap::const_iterator                                    it;
    pair<TopologyMap::const_iterator, TopologyMap::const_iterator> ret;


    ret = sys2coordv.equal_range( sys );

    if ( ret.first  != ret.second )
    {
        for ( it = ret.first; it != ret.second; ++it )
        {
            to_return.push_back( ( *it ).second );
        }
        return to_return;
    }
    else
    {
        throw RuntimeError( "Cartesian::get_coordv(): coordinates for the given resource not found!" );
    }
}



Cartesian*
Cartesian::clone( const std::vector<Thread*>& thrdv )
{
    Cartesian* copy = new Cartesian( ndims, dimv, periodv );
    copy->name     = name;
    copy->namedims = namedims;
    for ( TopologyMap::iterator itr = sys2coordv.begin(); itr != sys2coordv.end(); ++itr )
    {
        const Sysres& systemp = *( ( *itr ).first );


        Sysres*                         tmp_sys = NULL;
        vector<Thread*>::const_iterator itr2    = thrdv.begin();
        while ( tmp_sys == NULL &&  itr2 < thrdv.end() )
        {
            if ( ( *itr2 )->get_id() == systemp.get_id() )
            {
                tmp_sys = ( *itr2 );
            }
            ++itr2;
        }

        if ( tmp_sys == NULL )
        {
            throw RuntimeError( "Cloning topology is impossible, target threads are incompatble." );
        }

        copy->sys2coordv.insert(  TopologyMap::value_type( tmp_sys, ( *itr ).second ) );
    }
    return copy;
}


/**
 * Prints a xml-format of a cartesian topology.
 */
void
Cartesian::writeXML( ostream& out, bool cube3_export  ) const
{
// cout << " SAVE TOPOLOGY "  << endl;
//     int    sys_res = 0;
    string indent = "    ";
    out << indent << "  <cart ";
    if ( name != "" )
    {
        out << "name=\"" << services::escapeToXML( name ) << "\" ";
    }
    out << " ndims=\"" << ndims << "\">" <<  '\n';

    if ( ndims != dimv.size() || ndims != periodv.size() )
    {
        throw RuntimeError( "Cartesian::writeXML(): inconsistent dimensions defined!" );
    }


    for ( unsigned int i = 0; i < ndims; ++i )
    {
        out << indent << "    <dim ";
        if ( namedims.size() > 0 )
        {
            out <<  "name=\"" << services::escapeToXML( namedims[ i ] ) << "\" ";
        }
        out << "size=\"" << dimv[ i ] << "\" periodic=\""
            << ( periodv[ i ] ? "true" : "false" ) << "\"/>" <<  '\n';
    }

    TopologyMap::const_iterator s;
    std::pair<
        TopologyMap::const_iterator,
        TopologyMap::const_iterator > range;
    TopologyMap::const_iterator       range_iter;



    map<int, const Sysres*> id_order;
    s = sys2coordv.begin();
//     const Sysres*                                                    sys = s->first;

    // sort sys2coordv and store it in id_order
    for ( s = sys2coordv.begin(); s != sys2coordv.end(); ++s )
    {
        const Sysres* sys = s->first;


        if ( sys->isSystemTreeNode() )
        {
            SystemTreeNode* stn = ( SystemTreeNode* )sys;
            id_order[ stn->get_id() ] = stn;
        }
        else if ( sys->isLocationGroup() )
        {
            LocationGroup* lg = ( LocationGroup* )sys;
            id_order[ lg->get_id() ] = lg;
        }
        else if ( sys->isLocation() )
        {
            Location* loc = ( Location* )sys;
            id_order[ loc->get_id() ] = loc;
        }
        else
        {
            throw RuntimeError( "Cartesian::writeXML() [1]: unknown system resource defined" );
        }
    }

// output each coordinate
    map<int, const Sysres*>::iterator i;
    for ( i = id_order.begin(); i != id_order.end(); ++i )
    {
        range = sys2coordv.equal_range( i->second );
        for ( range_iter = range.first; range_iter != range.second; ++range_iter )
        {
            const Sysres* sys = range_iter->first;
            vector<long>  pt  = range_iter->second;

            if ( !cube3_export )
            {
                if ( sys->isSystemTreeNode() )
                {
                    SystemTreeNode* stn = ( SystemTreeNode* )sys;
                    out << indent << "    <coord stnId=\"" << stn->get_id() << "\">";
                }
                else if ( sys->isLocationGroup() )
                {
                    LocationGroup* lg = ( LocationGroup* )sys;
                    out << indent << "    <coord lgId=\"" << lg->get_id() << "\">";
                }
                else if ( sys->isLocation() )
                {
                    Location* loc = ( Location* )sys;
                    out << indent << "    <coord locId=\"" << loc->get_id() << "\">";
                }
                else
                {
                    throw RuntimeError( "Cartesian::writeXML() [2]: unknown system resource defined" );
                }
            }
            else
            {
                if ( sys->isMachine() )
                {
                    Machine* mach = ( Machine* )sys;
                    out << indent << "    <coord machId=\"" << mach->get_id() << "\">";
                }
                else if ( sys->isNode() )
                {
                    Node* node = ( Node* )sys;
                    out << indent << "    <coord nodeId=\"" << node->get_id() << "\">";
                }
                else if ( sys->isProcess() )
                {
                    Process* proc = ( Process* )sys;
                    ;
                    out << indent << "    <coord procId=\"" << proc->get_id() << "\">";
                }
                else if ( sys->isThread() )
                {
                    Thread* thrd = ( Thread* )sys;
                    out << indent << "    <coord thrdId=\"" << thrd->get_id() << "\">";
                }
                else
                {
                    throw RuntimeError( "Cartesian::writeXML() [2]: unknown system resource defined" );
                }
            }
            for ( unsigned int j = 0; j < pt.size(); ++j )
            {
                if ( j < pt.size() - 1 )
                {
                    out << pt[ j ] << " ";          // no space at the end
                }
                else
                {
                    out << pt[ j ];
                }
            }
            out << "</coord>" << '\n';
        }
    }
    out << indent << "  </cart>" << '\n';
}

/**
   Compare topologies step by step.
   <ol>
    <li> Equal number of dimensions?
    <li> Equal number of elements and periodicity in every dimension?
    <li> For every element of the first topology look for the same element in second one and compare coordinates.
   </ol>
 */
bool
Cartesian::operator==( const Cartesian& b )
{
    if ( this->get_ndims() != b.get_ndims() )
    {
        return false;                                // check dimensionality
    }
    for ( signed i = 0; i < this->get_ndims(); ++i ) // check property of every dimension
    {
        if ( ( this->get_dimv() )[ i ] != ( b.get_dimv() )[ i ] )
        {
            return false;                                             // number of points is equal?
        }
        if ( ( this->get_periodv() )[ i ] != ( b.get_periodv() )[ i ] )
        {
            return false;                                                    // periodicity is equal?
        }
    }
    TopologyMap::const_iterator iter_a;
    TopologyMap::const_iterator iter_b;
    for ( iter_a = ( this->get_cart_sys() ).begin();
          iter_a != ( this->get_cart_sys() ).end(); ++iter_a ) // through first topology
    {
        pair<
            TopologyMap::const_iterator,
            TopologyMap::const_iterator> ret;

        ret = ( b.get_cart_sys() ).equal_range( iter_a->first );   // fins same Thread in second topology.

        if ( ret.first == ret.second )
        {
            return false;                                     // found?
        }
        bool all_not_equal = true;
        for ( iter_b = ret.first; iter_b != ret.second; ++iter_b )
        {
//         if ((iter_a->first)->get_id() != (iter_b->first)->get_id()) return false;
            for ( signed i = 0; i < this->get_ndims(); ++i ) // check coordinates
            {
                if ( iter_a->second[ i ] != iter_b->second[ i ] )
                {
                    all_not_equal = all_not_equal && false;
                }
            }
        }
        if ( all_not_equal ) // we didnt find any threads in target topology wih the same coordinates
        {
            return false;
        }
    }
    return true; // all checks are passed, topology is equal, return true.
}

Serializable*
cube::Cartesian::create( Connection&      connection,
                         const CubeProxy& cubeProxy )
{
    return new Cartesian( connection, cubeProxy );
}
