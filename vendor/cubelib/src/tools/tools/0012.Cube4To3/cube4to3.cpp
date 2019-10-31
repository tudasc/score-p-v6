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
 * \file cube4to3.cpp
 * \brief Transforms the cube4 file in to the  cube3
 *
 */

#include "config.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <unistd.h>

#include "Cube.h"
#include "CubeZfstream.h"
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
    int ch;
//     bool            subset   = true;
//     bool            collapse = false;
    vector <string> inputs;
    const char*     output = "__NO_NAME__";
    const string    USAGE  = "Usage: " + string( argv[ 0 ] ) + " [-o output] [-h] <cube1> <cube2> ..\n"
                             "  -o     Name of the output file (default: [name].cube)\n"
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
        Cube* cube = NULL;
        try
        {
            cube = new Cube();
            cout << "Reading " << inputs[ i ] << " ... " << flush;
            cube->openCubeReport( inputs[ i ].c_str() );
            cout << " done." << endl;

            ofstream out;
            string   ext( ".cube" );
            string   name;
            if ( strcmp( output, "__NO_NAME__" ) == 0 )
            {
                name = get_cube4_name( inputs[ i ] ) + ext;
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

            cout << " Start to export " << inputs[ i ] << " into " <<  name << endl;
            out.open( name.c_str() );


            out << *cube;
            delete cube;
            cout << "done." << endl;
        }
        catch ( const cube::Cube3SystemTreeMismatchError& e )
        {
            delete cube;
            exit( EXIT_FAILURE );
        }
    }
    exit( EXIT_SUCCESS );
}
