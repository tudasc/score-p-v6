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
 * \file CubeSystemTreeNode.cpp
 * \brief Defines a function for xml-representation of the general system tree node.
 ********************************************/

#include <cassert>
#include "config.h"
#include <iostream>

#include "CubeConnection.h"
#include "CubeLocationGroup.h"
#include "CubeProxy.h"
#include "CubeServices.h"
#include "CubeSystemTreeNode.h"

using namespace std;
using namespace cube;
using namespace services;

SystemTreeNode::~SystemTreeNode()
{
}


std::vector<Sysres*>&
SystemTreeNode::get_sub_tree_vector()
{
//     whole_subtree.push_back(this);
    for ( unsigned i = 0; i < num_children(); i++ )
    {
        std::vector<Sysres*>& _vec = get_child( i )->get_sub_tree_vector();
        for ( std::vector<Sysres*>::const_iterator _iter = _vec.begin(); _iter != _vec.end(); ++_iter )
        {
            whole_subtree.push_back( *_iter );
        }
    }
    for ( unsigned i = 0; i < num_groups(); i++ )
    {
        std::vector<Sysres*>& _vec = get_location_group( i )->get_sub_tree_vector();
        for ( std::vector<Sysres*>::const_iterator _iter = _vec.begin(); _iter != _vec.end(); ++_iter )
        {
            whole_subtree.push_back( *_iter );
        }
    }
    collected_whole_tree = true;
    return whole_subtree;
}


void
SystemTreeNode::writeXML( std::ostream& out,
                          bool          cube3export ) const
{
    if ( cube3export )
    {
        if ( get_parent() == NULL )
        {
            out << indent() << "    <machine Id=\"" << get_id() << "\">" <<  '\n';
        }
        else
        {
            out << indent() << "    <node Id=\"" << get_id() << "\">" <<  '\n';
        }
    }
    else
    {
        out << indent() << "    <systemtreenode Id=\"" << get_id() << "\">" <<  '\n';
    }

    out << indent() << "      <name>" << escapeToXML( get_name() ) << "</name>" <<  '\n';
    if ( !cube3export )
    {
        out << indent() << "    <class>" << get_class() << "</class>" <<  '\n';
        if ( !get_desc().empty() || get_desc() != "" )
        {
            out << indent() << "      <descr>" << escapeToXML( get_desc() ) << "</descr>" <<  '\n';
        }
    }
    else  // export to cube3
    if ( get_parent() == NULL )   // only for machine
    {
        if ( !get_desc().empty() || get_desc() != "" )
        {
            out << indent() << "      <descr>" << escapeToXML( get_desc() ) << "</descr>" <<  '\n';
        }
    }


    writeAttributes( out,  indent() + "      ", cube3export  );

    for ( unsigned int i = 0; i < groups.size(); ++i )
    {
        const LocationGroup* lg = groups[ i ];
        lg->writeXML( out, cube3export  );
    }
    for ( unsigned int i = 0; i < num_children(); ++i )
    {
        const SystemTreeNode* node = get_child( i );
        node->writeXML( out, cube3export );
    }
    if ( cube3export )
    {
        if ( get_parent() == NULL )
        {
            out << indent() << "    </machine>" <<  '\n';
        }
        else
        {
            out << indent() << "    </node>" <<  '\n';
        }
    }
    else
    {
        out << indent() << "    </systemtreenode>" <<  '\n';
    }
}

Serializable*
cube::SystemTreeNode::create( Connection&      connection,
                              const CubeProxy& cubeProxy )
{
    return new SystemTreeNode( connection, cubeProxy );
}

void
cube::SystemTreeNode::pack( Connection& connection ) const
{
    Sysres::pack( connection );

    connection << int64_t( get_parent() ? get_parent()->get_sys_id() : int64_t( -1 ) );
    connection << desc;
    connection << stn_class;

    /// @note
    ///     The groups vector is a forward reference to objects
    ///     that are likely not yet available and therefore cannot
    ///     be filled at construction time. These references need
    ///     to be recreated by the respective constructors of the
    ///     location groups.
}

cube::SystemTreeNode::SystemTreeNode( Connection&      connection,
                                      const CubeProxy& cubeProxy )
    : Sysres( connection, cubeProxy )
{
    int64_t parent_id = connection.get<int64_t>();
    assert( parent_id == -1 || parent_id < ( int64_t )( cubeProxy.getSystemResources().size() ) );
    set_parent( parent_id == -1 ? NULL : cubeProxy.getSystemResources()[ parent_id ] );

    connection >> desc;
    connection >> stn_class;

    /// @note
    ///     The groups vector is a forward reference to objects
    ///     that are likely not yet available and therefore cannot
    ///     be filled at construction time. These references need
    ///     to be recreated by the respective constructors of the
    ///     location groups.
}

std::string
cube::SystemTreeNode::get_serialization_key() const
{
    return get_static_serialization_key();
}

std::string
cube::SystemTreeNode::get_static_serialization_key()
{
    return "SystemTreeNode";
}
