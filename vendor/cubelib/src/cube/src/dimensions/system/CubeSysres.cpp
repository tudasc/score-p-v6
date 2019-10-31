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


/*-------------------------------------------------------------------------*/
/**
 *  @file    Sysres.cpp
 *  @ingroup CUBE_lib.base
 *  @brief   Definition of the class cube::Sysres
 **/
/*-------------------------------------------------------------------------*/

#include "config.h"

#include "CubeSysres.h"

#include <iostream>

#include "CubeConnection.h"
#include "CubeError.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeProxy.h"
#include "CubeSystemTreeNode.h"

using namespace cube;
using namespace std;

//--- Construction & destruction -----------------------------------------

cube::Sysres::Sysres( Connection& connection,
                      const CubeProxy& )
    : SerializableVertex( connection )
{
    kind                 = sysres_kind( connection.get<uint32_t>() );
    name                 = connection.get<string>();
    sys_id               = connection.get<uint32_t>();
    collected_whole_tree = false;
}

//--- Serialization ------------------------------------------------------

void
cube::Sysres::pack( cube::Connection& connection ) const
{
    SerializableVertex::pack( connection );

    connection << uint32_t( kind );
    connection << name;
    connection << sys_id;
}
