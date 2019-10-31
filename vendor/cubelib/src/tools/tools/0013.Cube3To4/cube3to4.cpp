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
 * \file cube3to4.cpp
 * \brief Transforms teh cube3 file onto cube4
 *
 */

#include "config.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include <unistd.h>

#include "Cube.h"
#include "CubeZfstream.h"
#include "CubeIstream.h"
#include "CubeServices.h"
#include "CubeError.h"

using namespace std;
using namespace cube;
using namespace services;
/**
 * Main program.
 * -
 * -
 */
int
main( int argc, char* argv[] )
{
    int             ch;
    vector <string> inputs;
    const char*     output = "__NO_NAME__";
    const string    USAGE  = "Usage: " + string( argv[ 0 ] ) + "[-o output] [-h]  <cube1> <cube2> ..\n"
                             "  -o     Name of the output file. Extension .cubex is appended. (default: [name].cubex)\n"
                             "  -h     Help; Output a brief help message.\n"
    ;

    while ( ( ch = getopt( argc, argv, "o:h?" ) ) != -1 )
    {
        switch ( ch )
        {
            case 'o':
                output = optarg;
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

    if ( argc - optind > 0 )
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
        cerr << USAGE << "Error: At least one file is  required.\n\n";
        exit( EXIT_FAILURE );
    }

    for ( unsigned i = 0; i < inputs.size(); i++ )
    {
        cout << "Reading " << inputs[ i ] << " ... " << flush;
#if defined( FRONTEND_CUBE_COMPRESSED ) || defined( FRONTEND_CUBE_COMPRESSED_READONLY )
        gzifstream in1( inputs[ i ].c_str(), ios_base::in | ios_base::binary );
#else
        CubeIstream in1( inputs[ i ].c_str(), ios_base::in | ios_base::binary );
#endif

        if ( !in1 )
        {
            cerr << "Error: open " << inputs[ i ] << endl;
            exit( EXIT_FAILURE );
        }
        Cube* cube = NULL;
        try
        {
            cube = new Cube();

            string name;
            if ( strcmp( output, "__NO_NAME__" ) == 0 )
            {
                name = get_cube3_name( inputs[ i ] );
            }
            else
            {
                name += output;
                if ( i > 0 )
                {
                    stringstream str;
                    string       _tmp;
                    str << i;
                    name += ".";
                    str >> _tmp;
                    name += _tmp;
                }
            }

            in1 >> *cube;
            cout <<  endl;
            cout << " Start to export " << inputs[ i ] << " into " <<  name  << ".cubex" <<  endl;

            cube->writeCubeReport( name.c_str() );


            cout << " done." << endl;
        }
        catch ( const RuntimeError& error )
        {
            cerr << error.what() << endl;
            exit( EXIT_FAILURE );
        }
        delete cube;
    }
    exit( EXIT_SUCCESS );
}
