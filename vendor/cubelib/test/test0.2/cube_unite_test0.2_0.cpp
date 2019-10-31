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
 * \file cube_test.cpp
 * \brief An example how to create and save a cube.
 */
#include "config.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Cube.h"


using namespace std;
using namespace cube;

/** Debug: only used for Metric, Cnode */
template<class T>
void
traverse_print( T root )
{
    cout << root->get_id() << endl;
    for ( int i = 0; i < root->num_children(); i++ )
    {
        traverse_print<T>( ( T )root->get_child( i ) );
    }
}

// example code.
/**
 * Main program.
 * - Create an object "cube"
 * - Specify mirrors for onilne help.
 * - Specify information related to the file (optional)
 * - Build metric tree
 * - Build call tree
 * - Build location tree
 * - Severity mapping
 * - Building a topology
 *    - create 1st cartesian.
 *    - create 2nd cartesian
 * - Output to a cube file
 *
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

    std::string cubename = "tau_example";
    try
    {
        Cube cube;
//   Cube cube;

        // Specify mirrors (optional)
        cube.def_mirror( "http://icl.cs.utk.edu/software/kojak/" );
        cube.def_mirror( "http://www.fz-juelich.de/jsc/kojak/" );

        // Specify information related to the file (optional)
        cube.def_attr( "experiment time", "November 1st, 2004" );
        cube.def_attr( "description", "a simple example of saving tau atomic values" );

        // Build metric tree
        met0 = cube.def_met( "Time", "Uniq_name1", "TAU_ATOMIC", "", "",
                             "@mirror@patterns-2.1.html#execution",
                             "root node", NULL ); // using mirror
        met1 = cube.def_met( "User time", "Uniq_name2", "TAU_ATOMIC", "", "",
                             "http://www.cs.utk.edu/usr.html",
                             "2nd level", met0 ); // without using mirror
        met2 = cube.def_met( "System time", "Uniq_name3", "TAU_ATOMIC", "", "",
                             "http://www.cs.utk.edu/sys.html",
                             "2nd level", met0 ); // without using mirror
        met3 = cube.def_met( "System scaling", "Uniq_name4", "SCALE_FUNC", "", "",
                             "http://www.cs.utk.edu/sys.html",
                             "2nd level", NULL ); // without using mirror
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


        // Severity mapping
        TauAtomicValue* tau1 = new TauAtomicValue( 1, 1.234, 1.234, 1.234, 1.522756 );
        TauAtomicValue* tau2 = new TauAtomicValue( 1,  2, 2., 2., 4. );
        TauAtomicValue* tau3 = new TauAtomicValue( 1,  -0.5, -0.5, -0.5, 0.25 );
        TauAtomicValue* tau4 = new TauAtomicValue( 1,  10., 10., 10., 100. );
        TauAtomicValue* tau5 = new TauAtomicValue( 1,  4, 4., 4., 16. );
//     cube->set_sev(met0, cnodes_arr[ci], thrd_arr[ti], &tau);

        cube.set_sev( met0, cnode1, thrd0, tau1 );
        cube.set_sev( met0, cnode1, thrd1, tau2 );

        cube.set_sev( met0, cnode2, thrd0, tau3 );
        cube.set_sev( met0, cnode2, thrd1, tau4 );

        cube.set_sev( met1, cnode2, thrd0, tau5 );

        tau1->Free();
        tau2->Free();
        tau3->Free();
        tau4->Free();
        tau5->Free();


        // Severity mapping
        const size_t  sfv_length = 28;  // 7 terms
        vector<double>_a;
        _a.reserve( sfv_length );
        // vector guarantees contiguous storage, memset is safe
        memset( &_a[ 0 ], 0, sizeof( double ) * sfv_length );
        _a[ 0 ] = 2;
        _a[ 1 ] = 3;
        _a[ 4 ] = 4.2;
        ScaleFuncValue* sv1 = new ScaleFuncValue( _a );
//     cube->set_sev(met0, cnodes_arr[ci], thrd_arr[ti], &tau);

        cube.set_sev( met3, cnode1, thrd0, sv1 );
        cube.set_sev( met3, cnode1, thrd1, sv1 );
        sv1->Free();

        memset( &_a[ 0 ], 0, sizeof( double ) * sfv_length );
        _a[ 4 ] = 22;
        _a[ 3 ] = 34;
        _a[ 7 ] = 1.2;

        ScaleFuncValue* sv2 = new ScaleFuncValue( _a );
        ScaleFuncValue* sv3 = new ScaleFuncValue( _a );
        cube.set_sev( met3, cnode2, thrd0, sv2 );
        cube.set_sev( met3, cnode2, thrd1, sv3 );
        sv2->Free();
        sv3->Free();

        // building a topology
        // create 1st cartesian.
        int         ndims = 2;
        vector<long>dimv;
        vector<bool>periodv;
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
            vector<long>p[ 2 ];
            p[ 0 ].push_back( 0 );
            p[ 0 ].push_back( 0 );
            p[ 1 ].push_back( 2 );
            p[ 1 ].push_back( 2 );
            cube.def_coords( cart, thrd1, p[ 0 ] );
        } // create 2nd cartesian
        ndims = 2;
        vector<long>dimv2;
        vector<bool>periodv2;
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
        cart2->set_name( "MY SUPER TOPOL<<d>&&$%&<y;\"\"OGYW 2" );
        if ( cart2 != NULL )
        {
            vector<long>p2[ 2 ];
            p2[ 0 ].push_back( 0 );
            p2[ 0 ].push_back( 1 );
            p2[ 1 ].push_back( 1 );
            p2[ 1 ].push_back( 0 );
            cube.def_coords( cart2, thrd0, p2[ 0 ] );
            cube.def_coords( cart2, thrd1, p2[ 1 ] );
        }


        cube.set_statistic_name( "statisticstat" );
        cube.set_metrics_title( "sfdgsaf%$&WDFGYVART&" );
        cube.set_calltree_title( "calltreesfdgsaf%$&WDFGYVART&" );
        cube.set_systemtree_title( "systemsfdgsaf%$&WDFGYVART&" );

//         cube.enable_flat_tree( true );
        cube.writeCubeReport( cubename );
    }
    catch ( const RuntimeError& error )
    {
        cerr << error.what() << endl;
        return -1;
    }
    return 0;
}
