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
 *  @ingroup CUBE_lib.base
 *  @brief   Definitions of cube::IdentObject
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include <ostream>
#include <typeinfo>

#include "CubeIdentObject.h"

#include "CubeServerConnection.h"
#include "CubeClientConnection.h"

using namespace std;

namespace cube
{
ostream&
IdentObject::output( ostream& stream ) const
{
    return stream << "  m_id : " << m_id << "\n"
                  << "  m_filed_id : " << m_filed_id << "\n";
}

std::ostream&
operator <<( std::ostream&      stream,
             const IdentObject& object )
{
    stream << typeid( object ).name() << " {\n";
    object.output( stream );
    stream << "}\n";
    return stream;
}
}
