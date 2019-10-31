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


/*-------------------------------------------------------------------------*/
/**
 *  @file
 *  @ingroup CUBE_lib.dimensions
 *  @brief   Declaration of the class cube::SerializableVertex.
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_SERIALIZEABLEVERTEX_H
#define CUBE_SERIALIZEABLEVERTEX_H

#include <cstdlib>

#include "CubeVertex.h"
#include "CubeSerializable.h"

namespace cube
{
// Forward declarations
class Connection;

/*-------------------------------------------------------------------------*/
/**
 *  @class   cube::SerializableVertex
 *  @ingroup CUBE_lib.dimensions
 *  @brief   Base class for serializable vertices.
 **/
/*-------------------------------------------------------------------------*/

class SerializableVertex : public Vertex, public Serializable
{
public:
    /// @name Construction & destruction
    /// @{

    /// @brief
    ///     Standard constructor passed down to Vertex
    /// @param id
    ///     Id of this vertex
    ///
    SerializableVertex( uint32_t id = 0 );

    /// @brief
    ///     Standard constructor passed down to Vertex with known parent
    /// @param parent
    ///     Pointer to parent vertex
    /// @param id
    ///     Id of this vertex
    ///
    SerializableVertex( Vertex*  parent,
                         uint32_t id );

    /// @brief
    ///     Connection-based constructor to be used in initialization lists
    /// @param connection
    ///     Active Cube connection object.
    ///
    SerializableVertex( Connection& connection );

    /// @brief
    ///     Virtual destructor to allow destruction-by-base-pointer
    ///
    virtual
    ~SerializableVertex();

    /// @}
protected:

    /// @name Serialization
    /// @{

    /// @brief
    ///     Pack all information needed to reconstruct a SerializableVertex
    /// @param connection
    ///     Active Cube connection.
    ///
    /// @note
    ///     The parent-child relationship should be set by the derived-class'
    ///     factory method.
    ///
    virtual void
    pack( Connection& connection ) const;

    /// @}
};

} /* namespace cube */

#endif /* ! CUBE_SERIALIZEABLEVERTEX_H */
