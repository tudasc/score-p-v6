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
 * \file CubeCnode.cpp
 * \brief Defines the methods to deal with the elements of a call tree.
 */

#include "config.h"

#include "CubeCnode.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

#include "CubeConnection.h"
#include "CubeRegion.h"
#include "CubeServices.h"
#include "CubeProxy.h"

using namespace std;
using namespace cube;
using namespace services;
/**

 * Created an element of a call tree.
 *
 * As a friend class of "Region" is might call "add_excl_cnode".
 */

Cnode::Cnode( Region*            _callee,
              const std::string& _mod,
              int                _line,
              Cnode*             _parent,
              uint32_t           id ) :
    SerializableVertex( _parent, id ), callee( _callee ), mod( _mod ), line( _line ), is_hidden( false )
{
    //SerializableVertex::set_parent(parent);
    common_remapping_cnode = NULL;
    no_remapping           = true;
    callee->add_excl_cnode( this );
    collected_whole_tree = false;

    Cnode* cur_parent   = _parent;
    bool   is_recursive = false;
    while ( cur_parent != NULL )
    {
        if ( cur_parent->get_callee() == _callee )
        {
            is_recursive = true;
            break;
        }

        cur_parent = cur_parent->get_parent();
    }

    if ( is_recursive == false )
    {
        _callee->add_incl_cnode( this );
    }
}


Cnode::~Cnode()
{
}


Region*
Cnode::get_caller() const
{
    if ( get_parent() == NULL )
    {
        return NULL;
    }
    return get_parent()->get_callee();
}



const Cnode*
Cnode::get_remapping_cnode( int64_t process_rank ) const
{
    if ( no_remapping && common_remapping_cnode == NULL )
    {
        return this;
    }
    if ( common_remapping_cnode != NULL )
    {
        return common_remapping_cnode;
    }
    std::map<int64_t, const Cnode*>::const_iterator iter = remapping_cnodes.find( process_rank );
    if ( iter == remapping_cnodes.end() )
    {
        return NULL;
    }
    return ( *iter ).second;
}

int64_t
Cnode::get_cluster_normalization( int64_t process_rank ) const
{
    std::map<int64_t, int64_t>::const_iterator iter = cluster_normalization.find( process_rank );
    if ( iter == cluster_normalization.end() )
    {
        return 0;
    }
    return ( *iter ).second;
}

void
Cnode::set_remapping_cnode( const Cnode* r_cnode )
{
    common_remapping_cnode = r_cnode;
}


void
Cnode::set_remapping_cnode( int64_t process_rank, const Cnode* r_cnode,
                            int64_t _cluster_normalization )
{
    no_remapping                          = false;
    remapping_cnodes[ process_rank ]      = r_cnode;
    cluster_normalization[ process_rank ] = _cluster_normalization;
}



void
Cnode::add_num_parameter( string key, double param )
{
    pair<string, double> _parameter;
    _parameter.first  = key;
    _parameter.second = param;
    num_parameters.push_back( _parameter );
}



void
Cnode::add_str_parameter( string key, string param )
{
    pair<string, string> _parameter;
    _parameter.first  = key;
    _parameter.second = param;
    str_parameters.push_back( _parameter );
}




void
Cnode::set_as_leaf()
{
    for ( unsigned i = 0; i < num_children(); ++i )
    {
        Cnode* child = get_child( i );
        child->hide();
    }
}



void
Cnode::hide( bool recursive )
{
    is_hidden = true;

    // hide also all children
    if ( recursive )
    {
        for ( unsigned i = 0; i < num_children(); ++i )
        {
            Cnode* child = get_child( i );
            child->hide();
        }
    }
}




/**
 * \details Writes with deep search algorithm.
 */
void
Cnode::writeXML( ostream& out, bool cube3export ) const
{
    out << indent() << "    <cnode id=\"" << get_id() << "\" ";
    if ( get_line() != -1 )
    {
        out << "line=\"" << get_line() << "\" ";
    }
    if ( get_mod() != "" )
    {
        out << "mod=\"" << escapeToXML( get_mod() ) << "\" ";
    }
    out << "calleeId=\"" << get_callee()->get_id() << "\">" <<  '\n';

    for ( unsigned i = 0; i < num_parameters.size(); ++i )
    {
        out << indent() << "        <parameter partype=\"numeric\" parkey=\"" << escapeToXML( num_parameters[ i ].first ) << "\" parvalue=\"" << num_parameters[ i ].second  << "\"/>" <<  '\n';
    }
    for ( unsigned i = 0; i < str_parameters.size(); ++i )
    {
        out << indent() << "        <parameter partype=\"string\" parkey=\"" << escapeToXML( str_parameters[ i ].first.c_str() )  << "\" parvalue=\""  << escapeToXML( str_parameters[ i ].second.c_str() )   << "\"/>" <<  '\n';
    }


    writeAttributes( out,  indent() + "        ", cube3export );

    for ( unsigned int i = 0; i < num_children(); ++i )
    {
        Cnode* child = get_child( i );
        if ( cube3export )
        {
            if ( child->isVisible() ) // only visible children get saved.  (coz data of hidden children is stored in excl value of parent)
            {
                child->writeXML( out );
            }
        }
        else
        {
            child->writeXML( out ); // in the case of cube4 all children get stored.
        }
    }

    out << indent() << "    </cnode>\n";
}


bool
Cnode::weakEqual( Cnode* _c )
{
    if ( get_mod() != _c->get_mod() ||
         !( *( get_callee() ) == *( _c->get_callee() ) ) ||
         get_line() != _c->get_line()
         )
    {
        return false;
    }
    return true;
}



void
Cnode::fill_whole_tree_vector()
{
    whole_subtree = get_sub_tree_vector();
}

std::vector<Cnode*>&
Cnode::get_sub_tree_vector()
{
//     whole_subtree.push_back(this);
    for ( unsigned i = 0; i < num_children(); i++ )
    {
        whole_subtree.push_back( get_child( i ) );
        std::vector<Cnode*>& _vec = get_child( i )->get_sub_tree_vector();
        for ( std::vector<Cnode*>::const_iterator _iter = _vec.begin(); _iter != _vec.end(); ++_iter )
        {
            whole_subtree.push_back( *_iter );
        }
    }
    collected_whole_tree = true;
    return whole_subtree;
}





namespace cube
{
static
bool
equalParametersAndAttributes( const Cnode& a, const Cnode& b )
{
    bool                                                params_equal = true;
    const std::vector<std::pair<std::string, double> >& a_num_params = a.numeric_parameters();
    const std::vector<std::pair<std::string, double> >& b_num_params = b.numeric_parameters();
    if ( a_num_params.size() != b_num_params.size() )
    {
        return false;
    }

    for ( std::vector < std::pair < std::string, double> >::const_iterator iter1 = a_num_params.begin(); iter1 != a_num_params.end(); ++iter1 )
    {
        params_equal = false;
        for ( std::vector < std::pair < std::string, double> >::const_iterator iter2 = b_num_params.begin(); iter2 != b_num_params.end(); ++iter2 )
        {
            if ( iter1->first == iter2->first )
            {
                if ( iter1->second == iter2->second )
                {
                    params_equal = true;
                    continue;
                }
                else
                {
                    return false;
                }
            }
        }
        if ( !params_equal )
        {
            return false;
        }
    }

    const std::vector<std::pair<std::string, std::string> >& a_str_params = a.string_parameters();
    const std::vector<std::pair<std::string, std::string> >& b_str_params = b.string_parameters();
    if ( a_str_params.size() != b_str_params.size() )
    {
        return false;
    }
    for ( std::vector < std::pair < std::string, std::string> >::const_iterator iter1 = a_str_params.begin(); iter1 != a_str_params.end(); ++iter1 )
    {
        params_equal = false;
        for ( std::vector < std::pair < std::string, std::string> >::const_iterator iter2 = b_str_params.begin(); iter2 != b_str_params.end(); ++iter2 )
        {
            if ( iter1->first == iter2->first )
            {
                if ( iter1->second == iter2->second )
                {
                    params_equal = true;
                    continue;
                }
                else
                {
                    return false;
                }
            }
        }
        if ( !params_equal )
        {
            return false;
        }
    }
    return params_equal && a.equalAttributes( b );
}



bool
operator==( const Cnode& a, const Cnode& b )
{
    if ( a.get_level() != b.get_level()
         ||
         a.get_mod() != b.get_mod()
         ||
         !( *a.get_callee() == *b.get_callee() )
         ||
         a.get_line() != b.get_line()
         ||
         !equalParametersAndAttributes( a, b )
         )
    {
        return false;
    }

    Cnode* pa = a.get_parent();
    Cnode* pb = b.get_parent();
    if ( pa != NULL && pb != NULL )
    {
        return *pa == *pb;
    }
    else
    {
        return pa == pb;
    }
}

void
Cnode::pack( Connection& connection ) const
{
    SerializableVertex::pack( connection );

    connection << uint32_t( get_callee()->get_id() );
    connection << get_mod();
    connection << int32_t( get_line() );
    connection << int64_t( get_parent() ? get_parent()->get_id() : int64_t( -1 ) );
    //connection << int64_t( common_remapping_cnode ? common_remapping_cnode->get_id() : int64_t( -1 ) );
    connection << uint8_t( is_hidden ? 1 : 0 );
    connection << uint8_t( no_remapping ? 1 : 0 );
}

Serializable*
Cnode::create( Connection&      connection,
               const CubeProxy& cubeProxy )
{
    return new Cnode( connection,
                      cubeProxy.getCnodes(),
                      cubeProxy.getRegions() );
}
}

cube::Cnode::Cnode( Connection&                  connection,
                    const std::vector< Cnode* >  existingCnodes,
                    const std::vector< Region* > existingRegions )
    : SerializableVertex( connection )
{
    uint32_t callee_id = connection.get<uint32_t>();
    assert( callee_id < existingRegions.size() );
    callee = existingRegions[ callee_id ];

    connection >> mod;
    line = connection.get<int32_t>();

    int64_t parent_id = connection.get<int64_t>();
    assert( parent_id == -1 || parent_id < ( int64_t )( existingCnodes.size() ) );
    set_parent( parent_id == -1 ? NULL : existingCnodes[ parent_id ] );
    // int64_t remapping_cnode_id = connection.get<int64_t>(); // see pack()
    // assert( remapping_cnode_id == -1 || remapping_cnode_id < ( int64_t )( existingCnodes.size() ) );
    // common_remapping_cnode = ( remapping_cnode_id == -1 ? NULL : existingCnodes[ remapping_cnode_id ] );
    common_remapping_cnode = NULL;
    is_hidden              = connection.get<uint8_t>();
    no_remapping           = connection.get<uint8_t>();
}

std::string
cube::Cnode::get_static_serialization_key()
{
    return "Cnode";
}

std::string
Cnode::get_serialization_key() const
{
    return get_static_serialization_key();
}
