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
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/



/**
 * \file CubeLocationGroup.h
 * \brief Provides a relevant description of a locations group.
 */

#ifndef CUBE_LOCATION_GROUP_H
#define CUBE_LOCATION_GROUP_H


#include "CubeError.h"
#include "CubeLocation.h"
#include "CubeSysres.h"
#include "CubeSystemTreeNode.h"
#include "CubeTypes.h"



namespace cube
{
class Connection;
class CubeProxy;

inline bool
operator==( const LocationGroup& a,
            const LocationGroup& b );

/**
 * Thread is a basics kind of system resources. It doesn't return any "children"
 */
class LocationGroup : public Sysres
{
public:

    LocationGroup( const std::string& name,
                   SystemTreeNode*    stn,
                   int                rank,
                   LocationGroupType  type = cube::CUBE_LOCATION_GROUP_TYPE_PROCESS,
                   uint32_t           id = 0,
                   uint32_t           sysid = 0 );

    /// @brief
    ///     Create a location group object via Cube connection
    /// @param connection
    ///     Active Cube connection.
    /// @param cubeProxy
    ///     Cube proxy for internal cross-referencing.
    ///
    static Serializable*
    create( Connection&      connection,
            const CubeProxy& cubeProxy );

    /// @copydoc Serializable::pack
    ///
    void
    pack( Connection& connection ) const;

    /// @copydoc Serializable::get_serialization_key
    ///
    virtual std::string
    get_serialization_key() const;

    /// @copydoc Serializable::get_serialization_key
    ///
    static std::string
    get_static_serialization_key();

    ///< Thread does have a rank.
    inline
    int
    get_rank() const
    {
        return rank;
    }

    std::string
    get_type_as_string() const;

    inline
    LocationGroupType
    get_type() const
    {
        return type;
    }

    /// @note Override Vertex::set_parent() to add this
    /// as group rather than child of system-tree node.
    virtual void
    set_parent( Vertex* vertex );

    inline
    SystemTreeNode*
    get_parent() const
    {
        return ( SystemTreeNode* )Vertex::get_parent();
    }

    inline
    Location*
    get_child( unsigned int i ) const
    {
        return ( Location* )Vertex::get_child( i );
    }


    // / returns treu, if ids of all children are gapless monoton increasing. Used on the calculation optimisation

    inline
    bool
    isContinous()
    {
        return false;
    }





    void
    writeXML( std::ostream& out,
              bool          cube3export = false  ) const;    // /< Writes a xml-representation of a thread in a .cube file.


    static
    LocationGroupType
    getLocationGroupType( std::string );

protected:

    /// @brief
    ///     Constructs a Location object via a Cube connection.
    /// @param connection
    ///     Active Cube connection.
    /// @param cubeProxy
    ///     Cube proxy for internal cross-referencing.
    ///
    /// @note
    ///     This constructor is called by the factory method.
    ///
    LocationGroup( Connection&      connection,
                   const CubeProxy& cubeProxy );

private:
    int               rank;
    LocationGroupType type;
};


inline bool
operator==( const LocationGroup& a, const LocationGroup& b )
{
    int         _a  = a.get_rank();
    int         _b  = b.get_rank();
    std::string __a = a.get_name();
    std::string __b = b.get_name();

    return ( _a == _b ) && ( __a.compare( __b ) == 0 );
}




inline bool
operator<( const LocationGroup& a, const LocationGroup& b )
{
    int _a = a.get_rank();
    int _b = b.get_rank();
    return _a < _b;
}
}



#endif
