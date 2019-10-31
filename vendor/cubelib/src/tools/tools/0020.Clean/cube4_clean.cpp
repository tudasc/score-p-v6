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
 * \file cube4_clean.cpp
 * \brief Creates a clean copy (removes unused regions) of input cube and saves it in "clean.cube|.gz" file.
 *
 */
/******************************************

   Performance Algebra Operation: CLEAN

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
 * - Check calling arguments
 * - Read the .cube input file
 * - Calls cube_clean(...) to create a "cleaned" copy of the cube.
 * - Saves a new cube in the file "clean.cube|.gz"
 * - end.
 */
int
main( int argc, char* argv[] )
{
    int             ch;
    bool            subset   = false;
    bool            collapse = false;
    vector <string> inputs;
    const char*     output = "clean";

    const string USAGE = "Usage: " + string( argv[ 0 ] ) + " [-o output] [-c|-C] [-h] <cube experiment>\n"
                         "  -o     Name of the output file (default: " + output + ")\n"
                         "  -c     Reduce system dimension, if experiments are incompatible. \n"
                         "  -C     Collapse system dimension! Overrides option -c.\n"
                         "  -h     Help; Output a brief help message.\n"
    ;

    while ( ( ch = getopt( argc, argv, "cCo:h?" ) ) != -1 )
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

    if ( argc - optind != 1 )
    {
        cerr << USAGE << "\nError: Wrong arguments.\n";
        exit( EXIT_FAILURE );
    }

    for ( int i = optind; i < argc; i++ )
    {
        inputs.push_back( argv[ i ] );
    }

    Cube* inCube = new Cube();
    Cube* clean  = new Cube();
    cout << "++++++++++++ Clean operation begins ++++++++++++++++++++++++++" << endl;

    cout << "Reading " << inputs[ 0 ] << " ... " << endl;
    try {
        inCube->openCubeReport( inputs[ 0 ].c_str() );
        cout << "done." << endl;
        cube4_clean( clean, inCube, subset, collapse );
        cout << "++++++++++++ Clean operation ends successfully ++++++++++++++++" << endl;
        cout << "Writing " << output << flush;
        clean->writeCubeReport( output );
    }
    catch ( RuntimeError& e )
    {
        std::cerr << e.what() << std::endl;
        delete clean;
        delete inCube;
        exit( EXIT_FAILURE );
    }
    delete clean;
    delete inCube;
    cout << " done." << endl;
    exit( EXIT_SUCCESS );
}
