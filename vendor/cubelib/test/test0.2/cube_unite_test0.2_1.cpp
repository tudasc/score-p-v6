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
#include "CubeValue.h"

using namespace std;
using namespace cube;



int
main( int argc, char** argv )
{
    const double epsilon = 1e-11;
    try
    {
        Cube cube;

        vector<Metric*>metrics;
        vector<Cnode*> cnodes;
        vector<Thread*>threads;

        cout << " Open cube tau_example.cubex...";
        cube.openCubeReport( "tau_example.cubex" );

        metrics = cube.get_metv();
        cnodes  = cube.get_cnodev();
        threads = cube.get_thrdv();
        cout << "done" << endl;
        Value* v1 = cube.get_saved_sev_adv( metrics[ 0 ], cnodes[ 1 ], threads[ 0 ] );
        cout << v1->getString() << endl;
        Value* v2 = cube.get_saved_sev_adv( metrics[ 0 ], cnodes[ 1 ], threads[ 1 ] );
        cout << v2->getString() << endl;
        Value* v3 = cube.get_saved_sev_adv( metrics[ 0 ], cnodes[ 2 ], threads[ 0 ] );
        cout << v3->getString() << endl;
        Value* v4 = cube.get_saved_sev_adv( metrics[ 0 ], cnodes[ 2 ], threads[ 1 ] );
        cout << v4->getString() << endl;
        Value* v5 = cube.get_saved_sev_adv( metrics[ 1 ], cnodes[ 2 ], threads[ 0 ] );
        cout << v5->getString() << endl;
        Value* v6 = cube.get_saved_sev_adv( metrics[ 2 ], cnodes[ 2 ], threads[ 0 ] );
        cout << v6->getString() << endl;

        v1->Free();
        v2->Free();
        v3->Free();
        v4->Free();
        v5->Free();
        v6->Free();



        Value* vv1 = cube.get_sev_adv( metrics[ 1 ], CUBE_CALCULATE_INCLUSIVE );
        cout << vv1->getString() << endl;
        Value* vv2 = cube.get_sev_adv( metrics[ 0 ], CUBE_CALCULATE_INCLUSIVE );
        cout << vv2->getString() << endl;
        Value* vv3 = cube.get_sev_adv( metrics[ 0 ], CUBE_CALCULATE_EXCLUSIVE );
        cout << vv3->getString() << endl;


        vv1->Free();
        vv2->Free();
        vv3->Free();
    }
    catch ( const RuntimeError& error )
    {
        cerr << error.what() << endl;
        return -1;
    }
    return 0;
}
