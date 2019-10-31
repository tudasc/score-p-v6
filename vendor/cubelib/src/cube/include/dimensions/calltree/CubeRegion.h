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
 * \file CubeRegion.h
 * \brief Provides a description of a region of the source code.
 */
#ifndef CUBE_REGION_H
#define CUBE_REGION_H


#include <functional>
#include <iosfwd>

#include "CubeSerializableVertex.h"
#include "CubeTypes.h"

/*
 *----------------------------------------------------------------------------
 *
 * class Region
 *
 *******************************----------------------------------------------------------------------------
 */

namespace cube
{
class Connection;

bool
operator==( const Region& a,
            const Region& b );

/**
 * Functions contain Loops, Loops contains blocks and so on. Heterogen treelike structure.
 */
class Region : public SerializableVertex
{
public:
/**
 * Regions is defined by name, startline and endline of the source code, url as online help
 */
    Region( const std::string& name,
            const std::string& mangled_name,
            const std::string& paradigm,
            const std::string& role,
            long               begln,
            long               endln,
            const std::string& url,
            const std::string& descr,
            const std::string& mod,
            uint32_t           id = 0 );

    /// @brief
    ///     Define a new cube::Region from data received through a cube::Connection
    /// @param connection
    ///     Active Cube connection.
    /// @return
    ///     Pointer to new region.
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

    inline
    std::string
    get_name()  const
    {
        return name;
    }

    inline
    std::string
    get_mangled_name()  const
    {
        return mangled_name;
    }

    inline
    std::string
    get_paradigm()  const
    {
        return paradigm;
    }

    inline
    std::string
    get_role()  const
    {
        return role;
    }

    inline
    std::string
    get_url()   const
    {
        return url;
    }

    inline
    std::string
    get_descr() const
    {
        return descr;
    }

    inline
    std::string
    get_mod()   const
    {
        return mod;
    }

    inline
    long
    get_begn_ln()      const
    {
        return begln;
    }

    inline
    long
    get_end_ln()        const
    {
        return endln;
    }




    inline
    void
    set_name( std::string nm )
    {
        name = nm;
    }

    inline                                             /**< Sets the name of the region after it is created. Needed by cube4_canonize */
    void
    set_mangled_name( std::string nm )
    {
        mangled_name = nm;
    }

    inline                                             /**< Sets the name of the region after it is created. Needed by cube4_canonize */
    void
    set_paradigm( std::string pm )
    {
        paradigm = pm;
    }

    inline                                             /**< Sets the name of the region after it is created. Needed by cube4_canonize */
    void
    set_role( std::string rl )
    {
        role = rl;
    }

    inline                                              /**< Sets the name of the region after it is created. Needed by cube4_canonize */
    void
    set_url( std::string rl )
    {
        url = rl;
    }

    inline                                              /**< Sets the url of the region after it is created. Needed by cube4_canonize */
    void
    set_descr( std::string dscr )
    {
        descr = dscr;
    }

    inline                                            /**< Sets the description of the region after it is created. Needed by cube4_canonize */
    void
    set_mod( std::string md )
    {
        mod = md;
    }

    inline                                           /**< Sets the mode of the region after it is created. Needed by cube4_canonize */
    void
    set_begn_ln( int ln )
    {
        begln = ln;
    }                                                 /**< Sets the begin line of source code of the region after it is created. Needed by cube4_canonize */

    inline
    void
    set_end_ln( int ln )
    {
        endln = ln;
    }                                                 /**< Sets the end line of the source code of the region after it is created. Needed by cube4_canonize */


    inline
    int
    num_children()     const
    {
        return cnodev.size();
    }

    void
    add_cnode( Cnode* cnode );

    inline
    const std::vector<Cnode*>&
    get_cnodev() const
    {
        return cnodev;
    }

    inline
    const std::vector<Cnode*>&
    get_excl_cnodev() const
    {
        return excl_cnodev;
    }

    inline
    const std::vector<Cnode*>&
    get_incl_cnodev() const
    {
        return incl_cnodev;
    }

    void
    writeXML( std::ostream& out,
              bool          cube3_export = false ) const;


    inline
    void
    set_as_subroutines()
    {
        subroutines_of_region = true;
    }

    inline                                                            // /< sets an internal poiner in cnode, to
    void
    unset_as_subroutines()
    {
        subroutines_of_region = false;
    }

    inline                                                              // /< sets an internal poiner in cnode, to
    bool
    is_subroutines()
    {
        return subroutines_of_region == true;
    }


private:

    /// @brief
    ///     Constructs a Region object via a Cube connection.
    /// @param connection
    ///     Active Cube connection.
    ///
    /// @note
    ///     This constructor is called by the factory method.
    ///
    Region( Connection& connection );

    friend class Cnode; // /< Cnodes are friends, They may call private members.


    inline
    void
    add_incl_cnode( Cnode* cnode )
    {
        incl_cnodev.push_back( cnode );
    }

    inline
    void
    add_excl_cnode( Cnode* cnode )
    {
        excl_cnodev.push_back( cnode );
    }

    std::string         name;
    std::string         mangled_name;
    std::string         paradigm;
    std::string         role;
    long                begln;
    long                endln;
    std::string         url;
    std::string         descr;
    std::string         mod;
    std::vector<Cnode*> cnodev;

    bool subroutines_of_region;


    std::vector<Cnode*> excl_cnodev; // /< call paths calling this region
    std::vector<Cnode*> incl_cnodev; // /< call paths calling this region without recursive calls
};




inline bool
operator<( const Region& a, const Region& b )
{
    return a.get_name() < b.get_name();
}

inline bool
operator==( const Region& a, const std::string b )
{
    return a.get_name() == b ? true : false;
}



template <class T>
class GenLess : public std::binary_function<T, T, bool>
{
public:
    bool
    operator()( const T a, const T b ) const
    {
        return *a < *b;
    }
};
}




#endif
