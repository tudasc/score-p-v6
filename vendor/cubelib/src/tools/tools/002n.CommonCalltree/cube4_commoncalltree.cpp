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
 * \file cube4_commoncalltree.cpp
 * \brief Takes set of cubes and produces same set of cubes with reduced calltrees
 *
 */
/******************************************

   Performance Algebra Operation: MINIMAL COMMON CALLTREE

 *******************************************/
#include "config.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>

#include "Cube.h"
#include "CubeCnode.h"
#include "CubeMachine.h"
#include "CubeMetric.h"
#include "CubeRegion.h"
#include "CubeServices.h"
#include "algebra4.h"

#include "commoncalltree_calls.h"

using namespace std;
using namespace cube;
using namespace services;


int
main( int argc, char* argv[] )
{
    int             ch;
    vector <string> inputs;
    const char*     output = "_commoncalltree";

    const string USAGE = "Usage: " + string( argv[ 0 ] ) + " [-h] <cube experiment> ...\n"
                         "  -h     Help; Output a brief help message.\n"
    ;


    while ( ( ch = getopt( argc, argv, "h?" ) ) != -1 )
    {
        switch ( ch )
        {
            case 'h':
            case '?':
                cerr << USAGE << endl;
                exit( EXIT_SUCCESS );
                break;
            default:
                cerr << USAGE << "\nError: Wrong arguments.\n";
                exit( EXIT_FAILURE );
        }
    }

    if ( argc - optind < 2 )
    {
        cerr << USAGE << "\nError: Wrong arguments.\n";
        exit( EXIT_FAILURE );
    }

    for ( int i = optind; i < argc; i++ )
    {
        inputs.push_back( argv[ i ] );
    }



    cout << "++++++++++++ Minimal common calltree operation begins ++++++++++++++++++++++++++" << endl;
    int    num     = inputs.size();
    Cube** cube    = new Cube*[ num ];
    Cube** outcube = new Cube*[ num ];


    try
    {
        for ( int i = 0; i < num; i++ )
        {
            cout << "Reading " << inputs[ i ] << " ... " << flush;
            cube[ i ] = new Cube();
            cube[ i ]->openCubeReport( inputs[ i ].c_str() );
            cout << "done." << endl;
            outcube[ i ] = new Cube();
        }

        cube_common_calltree( cube, outcube, num );

        cout << "++++++++++++ Minimal common calltree operation ends successfully ++++++++++++++++" << endl;
        for ( int i = 0; i < num; i++ )
        {
            cout << "Writing " << ( get_cube4_name( cube[ i ]->get_cubename() ) + output ) << flush;
            outcube[ i ]->writeCubeReport( get_cube4_name( cube[ i ]->get_cubename() ) + output );
            cout << "done." << endl;
        }
    }
    catch ( const RuntimeError& error )
    {
        cerr << error.what() << endl;
        for ( int i = 0; i < num; i++ )
        {
            delete cube[ i ];
            delete outcube[ i ];
        }
        delete[] cube;
        delete[] outcube;
        exit( EXIT_FAILURE );
    }
    for ( int i = 0; i < num; i++ )
    {
        delete cube[ i ];
        delete outcube[ i ];
    }
    delete[] cube;
    delete[] outcube;
    cout << " done." << endl;
    exit( EXIT_SUCCESS );
}
