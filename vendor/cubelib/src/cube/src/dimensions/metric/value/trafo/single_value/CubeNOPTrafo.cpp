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
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/**
 * \file CubeNOPTrafo.cpp
 * \brief Defines a method "trafo" of the nop-transformation
 */


#include "config.h"

#include "CubeNOPTrafo.h"
using namespace cube;



/**
 * Does nothing, just returns. No changes in value are done.
 */
char*
NOPTrafo::trafo( char* stream, unsigned )
{
    return stream;
}
