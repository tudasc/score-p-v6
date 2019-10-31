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
 * \file CubeVertex.h
 * \brief Provides an element of a tree.
 */
#ifndef CUBE_VERTEX_H
#define CUBE_VERTEX_H

#include <string>
#include <vector>
#include <map>
#include <ostream>

#include "CubeIdentObject.h"


/*
 *----------------------------------------------------------------------------
 *
 * class Vertex
 *
 *******************************----------------------------------------------------------------------------
 */

namespace cube
{
/**
 * Every element of a tree has an ID. Therefore is Vertex a kind of IdenObject.
 */
class Vertex : public IdentObject
{
public:

    Vertex( Vertex*  parent,
            uint32_t id = 0 );

    Vertex( uint32_t id = 0 )
        : IdentObject( id ),
        parent( NULL ),
        total_number_of_children( 0 )
    {
    }

    virtual
    ~Vertex()
    {
    }

    inline
    std::string
    indent() const
    {
        return std::string( 2 * get_level(), ' ' );
    }                                                                       ///< By printing is a proper level of indent

    inline
    unsigned int
    num_children() const
    {
        return childv.size();
    }                                                           ///< How many undertrees ?

    inline
    Vertex*
    get_parent() const
    {
        return parent;
    }                                            ///< Root element?

    inline
    std::vector<Vertex*>&
    get_children()
    {
        return childv;
    }

    /// set attributes
    void
    def_attr( const std::string& key,
              const std::string& value );

    /// get attribute
    std::string
    get_attr( const std::string& key ) const;

    const std::map<std::string, std::string>&
    get_attrs() const;

    Vertex*
    get_child( unsigned int i ) const;

    const std::vector<Vertex*>&
    get_children() const;                       ///< Returns a reference to the vector of its children

    int
    get_level() const;     /// Recursiv calculation of a level in the tree hierarchy . Moved from private are for development of student M.Meyer

    inline
    uint64_t
    total_num_children() const
    {
        return total_number_of_children;
    };


    bool
    equalAttributes( const Vertex& ) const;


    virtual void
    set_parent( Vertex* vertex );

protected:

    /**
     * Generate human-readable output of internal state
     * @param stream Reference to output stream
     * @return Reference to modified output stream
     */
    virtual std::ostream&
    output( std::ostream& stream ) const;


    void
    writeAttributes( std::ostream&      out,
                     const std::string& indent,
                     bool               cube3export = false
                     ) const;

    void
    add_child( Vertex* vertex );

    std::map<std::string, std::string> attrs;       ///< attributes <key, value>
//     std::map<std::string, unsigned> children_counter;

    std::vector<Vertex*> childv;
    Vertex*              parent;
    uint64_t             total_number_of_children; // including all sublings...
};
}

#endif
