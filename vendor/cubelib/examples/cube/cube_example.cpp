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
 * \file cube_example.cpp
 * \brief An example how to create and save a cube.
 */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Cube.h"
#include "CubeMetric.h"
#include "CubeCnode.h"
#include "CubeProcess.h"
#include "CubeNode.h"
#include "CubeThread.h"
#include "CubeCartesian.h"

using namespace std;
using namespace cube;

// example code.
/**
 * Main program.
 * - Create an object "cube"
 * - Specify mirrors for onilne help.
 * - Specify information related to the file (optional)
 * - Build metric tree
 * - Build call tree
 * - Build location tree
 * - Building a topology
 *    - create 1st cartesian.
 *    - create 2nd cartesian
 * - Output to a cube file
 * - Converting into cube3 format
 * - Reading it from cube3 generated file.
 * - For a test read the cube again and save it in another file.
 * - end.
 */
int
main( int argc, char* argv[] )
{
    Metric*  met0, * met1, * met2, * met3;
    Region*  regn0, * regn1, * regn2;
    Cnode*   cnode0, * cnode1, * cnode2;
    Machine* mach;
    Node*    node;
    Process* proc0, * proc1;
    Thread*  thrd0, * thrd1;

    try
    {
        Cube cube;
//   Cube cube;

        // Specify mirrors (optional)
        cube.def_mirror( "http://www.fz-juelich.de/jsc/scalasca/" );

        // Specify information related to the file (optional)
        cube.def_attr( "experiment time", "November 1st, 2014" );
        cube.def_attr( "description", "a simple example example how to use c++ cube library" );

        // Build metric tree
        met0 = cube.def_met( "Time", "time", "FLOAT", "sec", "",
                             "@mirror@patterns-2.1.html#execution",
                             "root node", NULL, CUBE_METRIC_INCLUSIVE ); // using mirror
        met1 = cube.def_met( "User time", "usertime", "FLOAT", "sec", "",
                             "http://www.cs.utk.edu/usr.html",
                             "2nd level", met0 ); // without using mirror
        met2 = cube.def_met( "System time", "systemtime", "FLOAT", "sec", "",
                             "http://www.cs.utk.edu/sys.html",
                             "2nd level", met0 ); // without using mirror
        met3 = cube.def_met( "Allocated memory bytes", "mem", "INTEGER", "bytes", "",
                             "http://www.cs.utk.edu/sys.html",
                             "root level metric", NULL ); // without using mirror

        // Build call tree
        string mod = "/ICL/CUBE/example.c";
        regn0 = cube.def_region( "main", "main", "mpi", "barrier", 21, 100, "", "1st level", mod );
        regn1 = cube.def_region( "foo", "foo", "mpi", "barrier", 1, 10, "", "2nd level", mod );
        regn2 = cube.def_region( "bar", "bar", "mpi", "barrier", 11, 20, "", "2nd level", mod );


        cnode0 = cube.def_cnode( regn0, mod, 21, NULL );
        cnode1 = cube.def_cnode( regn1, mod, 60, cnode0 );
        cnode2 = cube.def_cnode( regn2, mod, 80, cnode0 );

        // Build location tree
        mach  = cube.def_mach( "MSC", "" );
        node  = cube.def_node( "Athena", mach );
        proc0 = cube.def_proc( "Process 0", 0, node );
        proc1 = cube.def_proc( "Process 1", 1, node );
        thrd0 = cube.def_thrd( "Thread 0", 0, proc0 );
        thrd1 = cube.def_thrd( "Thread 1", 1, proc1 );

        cube.initialize();
        
        // Severity mapping

        cube.set_sev( met0, cnode0, thrd0, 12. );
        cube.set_sev( met0, cnode0, thrd1, 11. );
        cube.set_sev( met0, cnode1, thrd0, 5. );
        cube.set_sev( met0, cnode1, thrd1, 6. );
        cube.set_sev( met0, cnode2, thrd0, 4.2 );
        cube.set_sev( met0, cnode2, thrd1, 3.5 );

        cube.set_sev( met1, cnode0, thrd0, 4. );
        cube.set_sev( met1, cnode0, thrd1, 4. );
        cube.set_sev( met1, cnode1, thrd0, 3. );
        cube.set_sev( met1, cnode1, thrd1, 3.2 );
        cube.set_sev( met1, cnode2, thrd0, 0.2 );
        cube.set_sev( met1, cnode2, thrd1, 0.5 );

        cube.set_sev( met2, cnode0, thrd0, 2. );
        cube.set_sev( met2, cnode0, thrd1, 2.4 );
        cube.set_sev( met2, cnode1, thrd0, 1.2 );
        cube.set_sev( met2, cnode1, thrd1, 1.2 );
        cube.set_sev( met2, cnode2, thrd0, 0.01 );
        cube.set_sev( met2, cnode2, thrd1, 0.03 );

        cube.set_sev( met3, cnode0, thrd0, 10 );
        cube.set_sev( met3, cnode0, thrd1, 20 );
        cube.set_sev( met3, cnode1, thrd0, 800 );
        cube.set_sev( met3, cnode1, thrd1, 700 );
        cube.set_sev( met3, cnode2, thrd0, 9300 );
        cube.set_sev( met3, cnode2, thrd1, 9500 );


        double value1 = cube.get_sev( met0, cnode0, thrd0 );
        double value2 = cube.get_sev( met0,   cube::CUBE_CALCULATE_INCLUSIVE,
                                      cnode0, cube::CUBE_CALCULATE_INCLUSIVE,
                                      thrd0, cube::CUBE_CALCULATE_INCLUSIVE );
        double value3 = cube.get_sev( met0,   cube::CUBE_CALCULATE_INCLUSIVE,
                                      cnode0, cube::CUBE_CALCULATE_INCLUSIVE,
                                      node, cube::CUBE_CALCULATE_INCLUSIVE );
        double value4 = cube.get_sev( met0,   cube::CUBE_CALCULATE_INCLUSIVE,
                                      cnode0, cube::CUBE_CALCULATE_INCLUSIVE
                                      );
        double value5 = cube.get_sev( met0,   cube::CUBE_CALCULATE_EXCLUSIVE
                                      );


        // building a topology
        // create 1st cartesian.
        int          ndims = 2;
        vector<long> dimv;
        vector<bool> periodv;
        for ( int i = 0; i < ndims; i++ )
        {
            dimv.push_back( 5 );
            if ( i % 2 == 0 )
            {
                periodv.push_back( true );
            }
            else
            {
                periodv.push_back( false );
            }
        }
        Cartesian* cart = cube.def_cart( ndims, dimv, periodv );

        if ( cart != NULL )
        {
            vector<long> p[ 2 ];
            p[ 0 ].push_back( 0 );
            p[ 0 ].push_back( 0 );
            p[ 1 ].push_back( 2 );
            p[ 1 ].push_back( 1 );
            cube.def_coords( cart, thrd0, p[ 0 ] );
            cube.def_coords( cart, thrd1, p[ 1 ] );
        }
        vector<string> dim_names;
        dim_names.push_back( "X" );
        dim_names.push_back( "Y" );
        cart->set_namedims( dim_names );


        // create 2nd cartesian
        ndims = 2;
        vector<long> dimv2;
        vector<bool> periodv2;
        for ( int i = 0; i < ndims; i++ )
        {
            dimv2.push_back( 3 );
            if ( i % 2 == 0 )
            {
                periodv2.push_back( true );
            }
            else
            {
                periodv2.push_back( false );
            }
        }


        Cartesian* cart2 = cube.def_cart( ndims, dimv2, periodv2 );
        cart2->set_name( "Application topology 2" );
        if ( cart2 != NULL )
        {
            vector<long> p2[ 2 ];
            p2[ 0 ].push_back( 0 );
            p2[ 0 ].push_back( 1 );
            p2[ 1 ].push_back( 1 );
            p2[ 1 ].push_back( 0 );
            cube.def_coords( cart2, thrd0, p2[ 0 ] );
            cube.def_coords( cart2, thrd1, p2[ 1 ] );
        }
        cart2->set_dim_name( 0, "Dimension 1" );
        cart2->set_dim_name( 1, "Dimension 2" );



        // Output to a cube file
        ofstream out;
        out.open( "cube3-example.cube" );
        out << cube;
        out.close();

	cube.writeCubeReport( "cube-example" );

	
	
        // Read it (example.cube) in and write it to another file (example2.cube)
        ifstream in( "cube3-example.cube" );
        Cube     cube2;
        in >> cube2;
        ofstream out2;
        out2.open( "cube3-example2.cube" );
        out2 << cube2;
    }
    catch ( const RuntimeError& error )
    {
        cout << error.what() << endl;
    }
}
