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
 *  @file    CubeSerializeableVertex.cpp
 *  @ingroup CUBE_lib.dimensions
 *  @brief   Definition of the class cube:SerializableVertex.
 **/
/*-------------------------------------------------------------------------*/

#include <config.h>
#include <map>

#include "CubeConnection.h"
#include "CubeProxy.h"
#include "CubeSerializableVertex.h"

using namespace std;

namespace cube
{

//--- Construction & destruction ---------------------------------------------

SerializableVertex::SerializableVertex( uint32_t id )
    : Vertex( id )
{
}

SerializableVertex::SerializableVertex( Vertex* parent, uint32_t id )
    : Vertex( parent, id )
{
}

SerializableVertex::SerializableVertex( Connection& connection )
{
    /// @note As IdentObject itself is not serializable, and its constructor
    ///     inputs are identical with those of Vertex, the SerializableVertex
    ///     packs member data for both IdentObject and Vertex.

    set_id( connection.get<uint32_t>() );
    set_filed_id( connection.get<uint32_t>() );

    uint64_t numAttributes = connection.get<uint64_t>();
    for ( uint64_t i = 0; i < numAttributes; ++i )
    {
        def_attr( connection.get<string>(),
                  connection.get<string>() );
    }
}

SerializableVertex::~SerializableVertex()
{
}

//--- Serialization ----------------------------------------------------------

void
SerializableVertex::pack( Connection& connection ) const
{
    /// @note As IdentObject itself is not serializeable, and its constructor
    ///     inputs are identical with those of Vertex, the SerializableVertex
    ///     packs member data for both IdentObject and Vertex.

    connection << uint32_t( get_id() );
    connection << uint32_t( get_filed_id() );

    connection << uint64_t( get_attrs().size() );
    for ( map< string, string >::const_iterator it = get_attrs().begin();
          it != get_attrs().end(); ++it )
    {
        connection << it->first;
        connection << it->second;
    }
}

} /* namespace cube */
