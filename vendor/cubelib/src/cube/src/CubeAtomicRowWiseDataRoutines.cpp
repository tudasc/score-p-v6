/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2017                                                **
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
 * \file Cube.cpp
 * \brief Defines methods of the class cube and IO-interface.
 *
 */

// PGI compiler replaces all ofstream.open() calls by open64 and then cannot find a propper one. Result -> compilation error
#if !defined( __PGI ) && !defined( __CRAYXT )  && !defined( __CRAYXE )
#define _FILE_OFFSET_BITS 64
#endif


#include "config.h"
#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeValue.h"
#include "CubeMetric.h"
#include "Cube.h"
// #include "CubeServices.h"

using namespace std;
using namespace cube;

void
Cube::set_sevs_raw( Metric* met,
                    Cnode*  cnode,
                    char*   val )
{
    met->set_sevs_raw( cnode, val );
}



Value**
Cube::get_saved_sevs_adv( Metric* met,
                          Cnode*  cnode )
{
    Value** _row = met->get_saved_sevs_adv( cnode );
    return _row;
}




double*
Cube::get_saved_sevs( Metric* met,
                      Cnode*  cnode )
{
    double* _row = met->get_saved_sevs( cnode );
    return _row;
}



char*
Cube::get_saved_sevs_raw( Metric* met,
                          Cnode*  cnode )
{
    char* _raw_row = met->get_saved_sevs_raw( cnode );
    return _raw_row;
}


// ------------------ SEVERITIES PART END --------------------------------
