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
 * \file CubeLocation.h
 * \brief Provides a relevant description of a location.
 */

#ifndef CUBE_LOCATION_H
#define CUBE_LOCATION_H


#include "CubeSysres.h"
#include "CubeTypes.h"
/*
 *----------------------------------------------------------------------------
 *
 * class Thread
 *
 *****************----------------------------------------------------------------------------
 */


namespace cube
{
class Connection;

inline bool
operator==( const Location& a,
            const Location& b );

/**
 * Thread is a basics kind of system resources. It doesn't return any "children"
 */
class Location : public Sysres
{
public:

    Location( const std::string& name,
              int                rank,
              LocationGroup*     proc,
              LocationType       type = cube::CUBE_LOCATION_TYPE_CPU_THREAD,
              uint32_t           id = 0,
              uint32_t           sysid = 0 );

    /// @brief
    ///     Create a location object via Cube connection
    /// @param connection
    ///     Active Cube connection.
    /// @param cubeProxy
    ///     Cube proxy for internal cross-referencing.
    ///
    static Serializable*
    create( Connection&      connection,
            const CubeProxy& cubeProxy );

    /// @brief
    ///     Send definition data to a remote process via a Cube connection.
    /// @param connection
    ///     Active Cube connection.
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
    LocationType
    get_type() const
    {
        return type;
    }

    inline
    LocationGroup*
    get_parent() const
    {
        return ( LocationGroup* )Vertex::get_parent();
    }




    void
    writeXML( std::ostream& out,
              bool          cube3export = false  ) const;  // /< Writes a xml-representation of a thread in a .cube file.


    static
    LocationType
    getLocationType( std::string );

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
    Location( Connection&      connection,
              const CubeProxy& cubeProxy );

private:
    int          rank;
    LocationType type;
};


inline bool
operator==( const Location& a, const Location& b )
{
    int _a = a.get_rank();
    int _b = b.get_rank();
    return _a == _b;
}




inline bool
operator<( const Location& a, const Location& b )
{
    int _a = a.get_rank();
    int _b = b.get_rank();
    return _a < _b;
}
}



#endif
