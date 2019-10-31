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
 * \file CubeSwapBytesTrafo.cpp
 * \brief Defines a method "trafo" of the swap transformation.
 */


#include "config.h"
#include <iostream>
#include <stdint.h>
#include "CubeServices.h"
#include "CubeSwapBytesTrafo.h"

using namespace cube;


char*
SwapBytesTrafo::trafo( char*    stream,
                       unsigned n )
{
    uint16_t& source16 = *( ( uint16_t* )stream );
    uint32_t& source32 = *( ( uint32_t* )stream );
    uint64_t& source64 = *( ( uint64_t* )stream );
    switch ( n )
    {
        case 1:
            break;
        case  2:
            source16 = services::cube_swap16( source16 );
            break;
        case  4:
            source32 = services::cube_swap32( source32 );
            break;
        case  8:
            source64 = services::cube_swap64( source64 );
            break;
        default:
            for ( unsigned i = 0; i < n / 2; ++i )
            {
                char tmp;
                tmp                 = stream[ i ];
                stream[ i ]         = stream[ n - i - 1 ];
                stream[ n - i - 1 ] = tmp;
            }
            ;
            break;
    }
    return stream + n;
}
