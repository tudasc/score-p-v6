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
 * \file CubeIdentObject.h
 * \brief Provides an object with an internal ID.
 */

#ifndef CUBE_IDENTOBJECT_H
#define CUBE_IDENTOBJECT_H

#include <inttypes.h>
#include <ostream>
#include <string>

namespace cube
{

/*-------------------------------------------------------------------------*/
/**
 *  @class   cube::IdentObject
 *  @ingroup CUBE_lib.base
 *  @brief   Cube base class for identifiable objects.
 **/
/*-------------------------------------------------------------------------*/

class IdentObject
{
public:
    IdentObject( uint32_t id = 0 ) : m_id( id ), m_filed_id( id )
    {
    }

    virtual
    ~IdentObject()
    {
    }

    inline
    void
    set_id( uint32_t id )
    {
        m_id = id;
    }                                       // /< Set an ID.

    inline
    uint32_t
    get_id() const
    {
        return m_id;
    }                                        // /< Gets the ID of the object.


    inline
    void
    set_filed_id( uint32_t id )
    {
        m_filed_id = id;
    }                                       // /< Set an ID.

    inline
    uint32_t
    get_filed_id() const
    {
        return m_filed_id;
    }                                        // /< Gets the ID of the object.






    static
    bool
    id_compare( IdentObject* a, IdentObject* b )
    {
        return ( a->get_id() ) < ( b->get_id() );
    }


protected:
    /**
     * Generate human-readable output of internal state
     * @param stream Reference to output stream
     * @return Reference to modified output stream
     */
    virtual std::ostream&
    output( std::ostream& stream ) const;

    uint32_t m_id;       // /< The ID of the object.
    uint32_t m_filed_id; // /< Not the "internal" ID , but assigned in some meta description,

    friend std::ostream& operator<<( std::ostream& tream, const IdentObject& object );

};


std::ostream&
operator<<( std::ostream& tream, const IdentObject& object );
}

#endif
