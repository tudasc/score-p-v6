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
 * \file CubeSimpleReader.cpp
 * \brief It translation of the "laout name" into "name to be opened " and position, to be seeked..
 */

#include "config.h"
#include "CubeSimpleReader.h"
#include "CubeError.h"

using namespace std;
using namespace cube;
void
SimpleReader::createContainer( const std::string& )
{
    throw RuntimeError( "ERROR: API is not Hybrid layout cpompatible" );
}
