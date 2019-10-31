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
 * \file cube_test.cpp
 * \brief An example how to create and save a cube.
 */
#include "config.h"

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

#define NTHREADS 100000
#define NCNODES 1000

using namespace std;
using namespace cube;

/** Debug: only used for Metric, Cnode */
template <class T>
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
    Region*     regn0, * regn1, * regn2;
    Machine*    mach;
    Node*       node;
    Cube        cube;
    std::string cubename = "example6";
    try
    {
        //   Cube cube;

        // Specify mirrors (optional)
        cube.def_mirror( "http://icl.cs.utk.edu/software/kojak/" );
        cube.def_mirror( "http://www.fz-juelich.de/jsc/kojak/" );

        // Specify information related to the file (optional)
        cube.def_attr( "experiment time", "November 1st, 2004" );
        cube.def_attr( "description", "a simple example" );

        // Build metric tree
        Metric* met[ 3 ];
        met[ 0 ] = cube.def_met( "Time", "Uniq_name1", "INTEGER", "sec", "",
                                 "@mirror@patterns-2.1.html#execution",
                                 "root node", NULL, CUBE_METRIC_INCLUSIVE ); // using mirror
        met[ 1 ] = cube.def_met( "User time", "Uniq_name2", "INTEGER", "sec", "",
                                 "http://www.cs.utk.edu/usr.html",
                                 "2nd level", met[ 0 ], CUBE_METRIC_INCLUSIVE ); // without using mirror
        met[ 2 ] = cube.def_met( "System time", "Uniq_name3", "INTEGER", "sec", "",
                                 "http://www.cs.utk.edu/sys.html",
                                 "2nd level", met[ 0 ], CUBE_METRIC_INCLUSIVE ); // without using mirror

        // Build call tree
        string mod = "/ICL/CUBE/example.c";
        regn0 = cube.def_region( "main", "main", "mpi", "barrier", 21, 100, "", "1st level", mod );
        regn1 = cube.def_region( "foo", "foo", "mpi", "barrier", 1, 10, "", "2nd level", mod );


        Cnode*   cnode0 = cube.def_cnode( regn0, mod, 21, NULL );
        Cnode*   cnodes[ NCNODES ];
        unsigned c_i = 0;
        for ( c_i = 0; c_i < NCNODES; c_i++ )
        {
            cnodes[ c_i ] = cube.def_cnode( regn1, mod, 60, cnode0 );
        }

        // Build location tree
        mach = cube.def_mach( "MSC", "" );
        node = cube.def_node( "Athena", mach );
        Process* proc0 = cube.def_proc( "Process 0", 0, node );
        Thread*  thrd[ NTHREADS ];
        unsigned t_i = 0;
        for ( t_i = 0; t_i < NTHREADS; t_i++ )
        {
            thrd[ t_i ] = cube.def_thrd( "Thread 1", 1, proc0 );
        }




        // Severity mapping

        double sev[ NTHREADS ];
        for ( t_i = 0; t_i < NTHREADS; t_i++ )
        {
            sev[ t_i ] = ( double )( t_i ) * 0.23;
        }
        cout << endl;
        unsigned m_i = 0;
        for ( m_i = 0; m_i < 3; m_i++ )
        {
            for ( c_i = 0; c_i < NCNODES; c_i++ )      // cnodes could be optimised... one has to fill in the "optimal sequence "
            {
                for ( t_i = 0; t_i < NTHREADS; t_i++ ) // thread wise filling is the fastest
                {
                    cube.set_sev( met[ m_i ], cnodes[ c_i ], thrd[ t_i ], sev[ t_i ] );
                }
            }
        }




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
            p[ 1 ].push_back( 2 );
            cube.def_coords( cart, thrd[ 1 ], p[ 0 ] );
        } // create 2nd cartesian
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
        cart2->set_name( "MY SUPER TOPOL<<d>&&$%&<y;\"\"OGYW 2" );
        if ( cart2 != NULL )
        {
            vector<long> p2[ 2 ];
            p2[ 0 ].push_back( 0 );
            p2[ 0 ].push_back( 1 );
            p2[ 1 ].push_back( 1 );
            p2[ 1 ].push_back( 0 );
            cube.def_coords( cart2, thrd[ 0 ], p2[ 0 ] );
            cube.def_coords( cart2, thrd[ 1 ], p2[ 1 ] );
        }


        cube.set_statistic_name( "statisticstat" );
        cube.set_metrics_title( "sfdgsaf%$&WDFGYVART&" );
        cube.set_calltree_title( "calltreesfdgsaf%$&WDFGYVART&" );
        cube.set_systemtree_title( "systemsfdgsaf%$&WDFGYVART&" );

        cube.enable_flat_tree( false );










        cube.writeCubeReport( cubename );
        cout << " Cube written." << endl;
    }
    catch ( const RuntimeError& error )
    {
        cerr << error.what();
        return -1;
    }
    return 0;
}
