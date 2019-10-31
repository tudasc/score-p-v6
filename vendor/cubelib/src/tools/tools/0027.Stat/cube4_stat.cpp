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




#include "config.h"

#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <vector>

#include <unistd.h>
#include <stdlib.h>

#include <algorithm>

#include "AggrCube.h"
#include "CubeThread.h"
#include "CubeMetric.h"
#include "CubeRegion.h"
#include "CubeCnode.h"
#include "CubeServices.h"

#include "P2Statistic.h"


#include "CubeStatistics.h"
#include "stat_calls.h"


/*-------------------------------------------------------------------------*/
/**
 * @file    cube4_stat.cpp
 * @brief   Provides the tool cube3_stat which extracts statistical information
 *          from CUBE files
 *
 */
/*-------------------------------------------------------------------------*/

using namespace std;
using namespace cube;
using namespace services;
int
main( int argc, char* argv[] )
{
    CubeStatistics myCubeStat( argc, argv );
    myCubeStat.Print();
    exit( EXIT_SUCCESS );
}
