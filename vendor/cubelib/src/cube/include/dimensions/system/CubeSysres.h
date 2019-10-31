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
**  Copyright (c) 2015                                                     **
**  RWTH Aachen University, JARA-HPC                                       **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


#ifndef CUBE_SYSRES_H
#define CUBE_SYSRES_H

/*-------------------------------------------------------------------------*/
/**
 *  @file
 *  @ingroup CUBE_lib.base
 *  @brief   Declaration of the class cube::Sysres
 **/
/*-------------------------------------------------------------------------*/

#include <vector>
#include <string>
#include <iostream>

#include "CubeSerializableVertex.h"
#include "CubeTypes.h"

namespace cube
{
// Forward declaration
class Connection;
class CubeProxy;

/**
 * @class Sysres
 * @brief Procides a general system resource with a tree-like hierarchy.
 *   Every Sysres has unique system id (sysid) and name.
 */
class Sysres : public SerializableVertex
{
public:

    Sysres( const std::string& name,
            uint32_t           id = 0,
            uint32_t           sysid = 0 )
        : SerializableVertex( id ), name( name ), sys_id( sysid )
    {
        kind                 = CUBE_UNKNOWN;
        collected_whole_tree = false;
    }
    Sysres( Sysres*            parent,
            const std::string& name,
            uint32_t           id = 0,
            uint32_t           sysid = 0 )
        : SerializableVertex( parent, id ), kind( CUBE_UNKNOWN ), name( name ), sys_id( sysid )
    {
        collected_whole_tree = false;
    }

    Sysres( const Sysres& copy )
        :  SerializableVertex( copy.get_parent(), copy.get_id() ), kind( copy.kind ), name( copy.name ), sys_id( copy.sys_id )
    {
        collected_whole_tree = false;
        for ( unsigned i = 0; i < copy.num_children(); ++i )
        {
            add_child( copy.get_child( i ) );
        }
    }


    /// @copydoc Serializable::pack
    virtual void
    pack( cube::Connection& connection ) const;


    inline
    const std::string&
    get_name() const
    {
        return name;
    }                                            // /< Name of the resource.

    inline
    void
    set_name( std::string newname )
    {
        name = newname;
    }                                                     // /< Set a name.

    inline
    uint32_t
    get_sys_id() const
    {
        return sys_id;
    }


    inline
    sysres_kind
    get_kind() const
    {
        return kind;
    };

    inline
    bool
    isMachine() const
    {
        return ( kind == CUBE_SYSTEM_TREE_NODE ) && ( get_parent() == NULL );
    };

    inline
    bool
    isNode() const
    {
        return ( kind == CUBE_SYSTEM_TREE_NODE ) && ( get_parent() != NULL );
    };

    inline
    bool
    isProcess() const
    {
        return kind == CUBE_LOCATION_GROUP;
    };

    inline
    bool
    isThread() const
    {
        return kind == CUBE_LOCATION;
    };

    inline
    bool
    isSystemTreeNode() const
    {
        return kind == CUBE_SYSTEM_TREE_NODE;
    };

    inline
    bool
    isLocationGroup() const
    {
        return kind == CUBE_LOCATION_GROUP;
    };

    inline
    bool
    isLocation() const
    {
        return kind == CUBE_LOCATION;
    };

    inline
    bool
    isUnknown() const
    {
        return kind == CUBE_UNKNOWN;
    };



/**
 * This sysres is a part of which sysres?
 */

    inline
    Sysres*
    get_parent() const
    {
        return static_cast<Sysres*>( Vertex::get_parent() );
    }
/**
 * This sysres contains i-th sysres.... which is ?
 */

    inline
    Sysres*
    get_child( unsigned int i ) const
    {
        return static_cast<Sysres*>( Vertex::get_child( i ) );
    }

    const std::vector<cube::Sysres*>&
    get_whole_subtree() const
    {
        return whole_subtree;
    }

    inline
    void
    whole_tree_is_collected()
    {
        collected_whole_tree = true;
    };

    inline
    bool
    is_whole_tree_collected() const
    {
        return collected_whole_tree;
    }

    inline
    void
    fill_whole_tree_vector()
    {
        whole_subtree = get_sub_tree_vector();
    }


    virtual
    std::vector<cube::Sysres*>&
    get_sub_tree_vector()
    {
        if ( isLocation() )
        {
            whole_subtree.push_back( this );
        }
        else
        {
            for ( unsigned i = 0; i < num_children(); i++ )
            {
                std::vector<Sysres*>& _vec = get_child( i )->get_sub_tree_vector();
                for ( std::vector<Sysres*>::const_iterator _iter = _vec.begin(); _iter != _vec.end(); ++_iter )
                {
                    whole_subtree.push_back( *_iter );
                }
            }
        }
        collected_whole_tree = true;
        return whole_subtree;
    };



protected:
    /// @brief
    ///     Constructs a Sysres object via a Cube connection.
    /// @param connection
    ///     Active Cube connection.
    /// @param cubeProxy
    ///     Cube proxy for internal cross-referencing.
    ///
    /// @note
    ///     This constructor is called by the derived classes.
    ///
    Sysres( Connection&      connection,
            const CubeProxy& cubeProxy );


    sysres_kind kind;
    std::string name;
    uint32_t    sys_id;

    std::vector<Sysres*> whole_subtree;                              // used to calculate inclusive value by exclusive metric
    bool                 collected_whole_tree;
};
}

#endif
