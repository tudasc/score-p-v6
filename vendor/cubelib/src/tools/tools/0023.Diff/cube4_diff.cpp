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
 * \file cube4_diff.cpp
 * \brief Creates a difference of two .cube4 files.
 *
 */
/******************************************

   Performance Algebra Operation: DIFFERENCE

 *******************************************/

#include "config.h"
#include <cstdlib>
#include <iostream>
#include <string>
// #ifndef CUBE_COMPRESSED
#include <fstream>
// #else
#include "CubeZfstream.h"
// #endif
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
 * - Check calling arguments
 * - Read the  .cube input files.
 * - Calls cube_diff(...) to create a difference of them .
 * - Saves the result in "-o outputfile" or "diff.cube|.gz" file.
 * - end.
 */
int
main( int argc, char* argv[] )
{
    int             ch;
    bool            subset   = false;
    bool            collapse = false;
    vector <string> inputs;
    const char*     output = "diff";

    const string USAGE = "Usage: " + string( argv[ 0 ] ) + " [-o output] [-c|-C] [-h] <minuend> <subtrahend>\n"
                         "  -o     Name of the output file (default: " + output + ")\n"
                         "  -c     Reduce system dimension, if experiments are incompatible. \n"
                         "  -C     Collapse system dimension! Overrides option -c.\n"
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
                subset = true;
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

    if ( argc - optind == 2 )
    {
        string cur;
        for ( int i = optind; i < argc; i++ )
        {
            cur = argv[ i ];
            inputs.push_back( cur );
        }
    }
    else
    {
        cerr << USAGE << "Error: Two files required.\n\n";
        exit( EXIT_FAILURE );
    }

    Cube* min  = new Cube();
    Cube* sub  = new Cube();
    Cube* diff = new Cube();
    try
    {
        cout << "Reading " << inputs[ 0 ] << " ... " << flush;
        min->openCubeReport( inputs[ 0 ].c_str() );
        cout << "done." << endl;

        cout << "Reading " << inputs[ 1 ] << " ... " << flush;
        sub->openCubeReport( inputs[ 1 ].c_str() );
        cout << "done." << endl;


        // Write it
        cout << "++++++++++++ Diff operation begins ++++++++++++++++++++++++++" << endl;

        cube4_diff( diff, min, sub,  subset, collapse );
        cout << "++++++++++++ Diff operation ends successfully ++++++++++++++++" << endl;

        cout << "Writing " << output << flush;
        diff->writeCubeReport( get_cube4_name( output ) );
    }
    catch (  const RuntimeError& e )
    {
        std::cerr << e.what() << std::endl;
        delete min;
        delete sub;
        delete diff;
        exit( EXIT_FAILURE );
    }
    delete min;
    delete sub;
    delete diff;
    cout << " done." << endl;
    exit( EXIT_SUCCESS );
}
