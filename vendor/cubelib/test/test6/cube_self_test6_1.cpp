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

#include "Cube.h"
#include "CubeMetric.h"
#include "CubeCnode.h"
#include "CubeThread.h"

using namespace std;
using namespace cube;

int
main( int argc, char** argv )
{
    Cube cube;
    cout << " Open cube example6.cubex...";
    cube.openCubeReport( "example6.cubex" );
    cout << "done." << endl;
    cout << "Get dimenstions ...";
    vector<Metric*> metrics = cube.get_metv();
    vector<Cnode*>  cnodes  = cube.get_cnodev();
    vector<Thread*> threads = cube.get_thrdv();
    cout << "done" << endl;
    double v1 = cube.get_saved_sev( metrics[ 0 ], cnodes[ 0 ], threads[ 1000 ] );
    cout << v1 << endl;
    double v2 = cube.get_saved_sev( metrics[ 1 ], cnodes[ 30 ], threads[ 1234 ] );
    cout << v2 << endl;
    double v3 = cube.get_saved_sev( metrics[ 2 ], cnodes[ 100 ], threads[ 4321 ] );
    cout << v3 << endl;
    double v4 = cube.get_saved_sev( metrics[ 0 ], cnodes[ 1000 ], threads[ 12345 ] );
    cout << v4 << endl;
    double v5 = cube.get_saved_sev( metrics[ 1 ], cnodes[ 300 ], threads[ 100 ] );
    cout << v5 << endl;
    return ( v1 == 0. && v2 == 283 && v3 == 993 && v4 == 2839 && v5 == 23 ) ? 0 : -1;
}
