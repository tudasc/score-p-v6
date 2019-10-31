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
 * \file cube4_is_empty.cpp
 * \brief Checks, if the cube report is completely empty (structureless), zero data or not.
 *
 */
/******************************************

   Performance Algebra Operation: IS EMPTY

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
 * - Read the first .cube input file and the second file.
 * - Calls cube_cmp(...) to compare them.
 * - Prints the result in human readable form.
 * - end.
 */
int
main( int argc, char* argv[] )
{
    int             ch;
    int             return_value = -1;
    vector <string> inputs;

    const string USAGE = "Usage: " + string( argv[ 0 ] ) + " [-h]  <cube experiment 1> \n"
                         "  -h     Help; Output a brief help message.\n"
    ;

    while ( ( ch = getopt( argc, argv, "o:ch?" ) ) != -1 )
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

    if ( argc - optind == 1 )
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
        cerr << USAGE << "Error: Only one file required.\n\n";
        exit( EXIT_FAILURE );
    }



    Cube* cube = NULL;
    try
    {
        cube = new Cube();

        cout << "Reading " << inputs[ 0 ] << " ... " << flush;
        cube->openCubeReport( inputs[ 0 ].c_str() );

        cout << "done." << endl;
        cout << "++++++++++++ Checking operation begins ++++++++++++++++++++++++++" << endl;

        if ( cube::cube4_is_empty( cube ) )
        {
            return_value = EXIT_SUCCESS;
        }
        else
        {
            cout << "Experiments are different." << endl;
            return_value = EXIT_FAILURE;
        }


        cout << "+++++++++++++ Checking operation ends successfully ++++++++++++++++" << endl;
    }
    catch ( const RuntimeError& e )
    {
        std::cerr << e.what() << std::endl;
    }
    delete cube;
    return return_value;
}
