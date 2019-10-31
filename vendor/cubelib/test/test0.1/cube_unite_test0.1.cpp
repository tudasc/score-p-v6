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
    Metric*  met0, * met1, * met2;
    Region*  regn0, * regn1, * regn2;
    Cnode*   cnode0, * cnode1, * cnode2;
    Machine* mach;
    Node*    node;
    Process* proc0, * proc1;
    Thread*  thrd0, * thrd1;

    std::string cubename = "example.cubex";
    try
    {
        Cube cube;
//   Cube cube;

        // Build metric tree
        met0 = cube.def_met( "Time", "Uniq_name1", "INTEGER", "sec", "",
                             "@mirror@patterns-2.1.html#execution",
                             "root node", NULL ); // using mirror
        met1 = cube.def_met( "User time", "Uniq_name2", "INTEGER", "sec", "",
                             "http://www.cs.utk.edu/usr.html",
                             "2nd level", met0 ); // without using mirror
        met2 = cube.def_met( "System time", "Uniq_name3", "INTEGER", "sec", "",
                             "http://www.cs.utk.edu/sys.html",
                             "2nd level", met0 ); // without using mirror

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
    }
    catch ( const RuntimeError& error )
    {
        cerr << error.what() << endl;
        return -1;
    }
    return 0;
}
