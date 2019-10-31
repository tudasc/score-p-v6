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
 * \file cube4_mean.cpp
 * \brief Creates a mean (average) cube of many  .cube4 files.
 *
 */
/******************************************

   Performance Algebra Operation: MEAN

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

using namespace std;
using namespace cube;
using namespace services;
/**
 * Main program.
 * - Check the calling parameters.
 * - For every filename it does
 * - Read the  .cube file. and saves it on alternate way either in 0-th,
   or 1th place in cube[] array.
 * - Calls cube_mean(...) with previous cube (summed) and the current one
   multiplied with a 1/number.
 * - Saves a created mean (average) cube in either "-o output" or "mean.cube|.gz" file.
 * - end.
 */
int
main( int argc, char* argv[] )
{
    int             ch;
    bool            subset   = true;
    bool            collapse = false;
    vector <string> inputs;
    const char*     output = "mean";

    const string USAGE = "Usage: " + string( argv[ 0 ] ) + " [-o output] [-c] [-C] [-h] <cube experiment> ...\n"
                         "  -o     Name of the output file (default: " + output + ")\n"
                         "  -c     Do not collapse system dimension, if experiments are incompatible\n"
                         "  -C     Collapse system dimension!\n"
                         "  -h     Help; Output a brief help message.\n"
    ;

    while ( ( ch = getopt( argc, argv, "o:cCh?" ) ) != -1 )
    {
        switch ( ch )
        {
            case 'o':
                output = optarg;
                break;
            case 'c':
                subset = false;
                break;
            case 'C':
                collapse = true;
                break;
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

    if ( argc - optind < 1 )
    {
        cerr << USAGE << "\nError: Wrong arguments.\n";
        exit( EXIT_FAILURE );
    }

    for ( int i = optind; i < argc; i++ )
    {
        inputs.push_back( argv[ i ] );
    }


    cout << "++++++++++++ Mean operation begins ++++++++++++++++++++++++++" << endl;



    int    num  = inputs.size();
    Cube** cube = new Cube*[ num ];



    for ( int i = 0; i < num; i++ )
    {
        cube[ i ] = new Cube();
    }
    Cube* mean = new Cube();
    try
    {
        for ( int i = 0; i < num; i++ )
        {
            cube[ i ]->openCubeReport( inputs[ i ].c_str() );
        }


        cube4_mean( mean, cube, num, subset, collapse );
    }
    catch ( const RuntimeError& e )
    {
        std::cerr << e.what() << std::endl;
        for ( int i = 0; i < num; i++ )
        {
            delete cube[ i ];
        }
        delete[] cube;
        exit( EXIT_FAILURE );
    }

    cout << "++++++++++++ Mean operation ends successfully ++++++++++++++++" << endl;


    for ( int i = 0; i < num; i++ )
    {
        delete cube[ i ];
    }
    try
    {
        cout << "Writing " << output << flush;
        mean->writeCubeReport( get_cube4_name( output ) );
    }
    catch ( const RuntimeError& e )
    {
        std::cerr << e.what() << std::endl;
        delete mean;
        delete[] cube;
        exit( EXIT_FAILURE );
    }
    delete mean;
    delete[] cube;
    cout << " done. " << endl;
    exit( EXIT_SUCCESS );
}
