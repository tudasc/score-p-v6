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
 * Opens a big created cube report and reqds some values.
 */
#include "config.h"

#include <iostream>
#include <cmath>
#include <iomanip>

#include "Cube.h"
#include "CubeMetric.h"
#include "CubeCnode.h"
#include "CubeThread.h"

using namespace std;
using namespace cube;



int
main( int argc, char** argv )
{
    const double epsilon = 1e-11;
    Cube         cube;

    vector<Metric*> metrics;
    vector<Cnode*>  cnodes;
    vector<Thread*> threads;
    cout << " Open cube example3_incl.cubex...";
    cube.openCubeReport( "example3_incl.cubex" );

    bool all_inclusive = true;
    metrics = cube.get_metv();
    for ( vector<Metric*>::iterator miter = metrics.begin(); miter != metrics.end(); miter++ )
    {
        all_inclusive &= ( ( *miter )->get_metric_kind() == "INCLUSIVE" );
    }


    cnodes  = cube.get_cnodev();
    threads = cube.get_thrdv();
    cout << "done" << endl;
    double v1 = cube.get_sev( metrics[ 0 ], CUBE_CALCULATE_INCLUSIVE, cnodes[ 0 ], CUBE_CALCULATE_INCLUSIVE );
    cout << v1 << endl;
    double v2 = cube.get_sev( metrics[ 0 ], CUBE_CALCULATE_INCLUSIVE, cnodes[ 0 ], CUBE_CALCULATE_INCLUSIVE, threads[ 0 ], CUBE_CALCULATE_INCLUSIVE );
    cout << v2 << endl;
    double v3 = cube.get_sev( metrics[ 0 ], CUBE_CALCULATE_EXCLUSIVE );
    cout << v3 << endl;
    double v4 = cube.get_sev( metrics[ 0 ], CUBE_CALCULATE_EXCLUSIVE, cnodes[ 1 ], CUBE_CALCULATE_EXCLUSIVE, threads[ 1 ], CUBE_CALCULATE_EXCLUSIVE );
    cout << v4 << endl;

    cout << v1 << endl;
    cout << v2 << endl;
    cout << v3 << endl;
    cout << v4 << endl;
    cout << ( ( all_inclusive ) ? "all metrics inclusive" : "some metrics exclusive" ) << endl;
    return 0;
}
