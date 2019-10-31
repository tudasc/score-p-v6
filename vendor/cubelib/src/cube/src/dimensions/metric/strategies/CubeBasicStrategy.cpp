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
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/**
 * \file CubeBasicStrategy.cpp
 * \brief Provides an implemetation of basic paging strategy
 */

#include "config.h"
#include <string>
#include <cstdlib>

#include "CubeBasicStrategy.h"
#include "CubeServices.h"
#include "config.h"

using namespace cube;
using namespace std;

CubeStrategy
BasicStrategy::selectInitialStrategy()
{
    CubeStrategy _strategy =  cube::CUBE_ALL_IN_MEMORY_STRATEGY;
#ifdef CUBE_DEFAULT_ALL_IN_MEMORY_PRELOAD
    _strategy =  cube::CUBE_ALL_IN_MEMORY_PRELOAD_STRATEGY;
#endif
#ifdef CUBE_DEFAULT_MANUAL
    _strategy =  cube::CUBE_MANUAL_STRATEGY;
#endif
#ifdef CUBE_DEFAULT_LAST_N
    _strategy =  cube::CUBE_LAST_N_ROWS_STRATEGY;
#endif
#ifdef CUBE_DEFAULT_ALL_IN_MEMORY
    _strategy =  cube::CUBE_ALL_IN_MEMORY_STRATEGY;
#endif

    char* value = getenv( CUBE_STRATEGY_SELECTION );

    if ( value != NULL )
    {
        string to_return( value );
        if ( services::lowercase( to_return ).compare( "keepall" ) == 0 )
        {
            _strategy =  cube::CUBE_ALL_IN_MEMORY_STRATEGY;
        }
        else if ( services::lowercase( to_return ).compare( "preload" ) == 0 )
        {
            _strategy =  cube::CUBE_ALL_IN_MEMORY_PRELOAD_STRATEGY;
        }
        else if ( services::lowercase( to_return ).compare( "manual" ) == 0 )
        {
            _strategy =  cube::CUBE_MANUAL_STRATEGY;
        }
        else   // lastN
        {
            _strategy =  cube::CUBE_LAST_N_ROWS_STRATEGY;
        }
    }
    return _strategy;
};
