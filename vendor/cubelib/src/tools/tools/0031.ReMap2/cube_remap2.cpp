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
 * \file cube_remap2.cpp
 * \brief Remaps a
   cube and saves it in new "remap.cube|.gz" file.
 */
/******************************************

   Performance Algebra Operation: REMAP

 *******************************************/
#include "config.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>

#include "Cube.h"
#include "AggrCube.h"
#include "CubeCnode.h"
#include "CubeMachine.h"
#include "CubeMetric.h"
#include "CubeRegion.h"
#include "CubeServices.h"
#include "algebra4.h"

#include "remap2_calls.h"

using namespace std;
using namespace cube;
using namespace remapper;
using namespace services;
/**
 * Main program.
 * - Check calling arguments
 * - Read the  .cube input file.
 * - Calls cube_remap(...) to create a clone of input cube and calculate exclusive
   and inclusive values.
 * - Saves the result in "-o outputfile" or "remap.cube|.gz" file.
 * - end.
 */
int
main( int argc, char* argv[] )
{
    int         ch;
    const char* output               = "remap";
    const char* spec                 = "__NO_SPEC__";
    bool        copy_structure       = false;
    bool        convert              = false;
    bool        add_scalasca_metrics = false;

    const string USAGE = "Usage: " + string( argv[ 0 ] ) + " -r <remap specification file> [-o output] [-d] [-s] [-h] <cube experiment>\n"
                         "  -r     Name of the remapping specification file. By omitting this option the specification file from the \n"
                         "        cube experiment is taken if present. \n"
                         "  -c     Create output file with the same structure as an input file. It overrides option \"-r\"\n"
                         "  -o     Name of the output file (default: " + output + ")\n"
                         "  -d     Convert all prederived metrics into usual metrics, calculate and store their values as a data. \n"
                         "  -s     Add hardcoded Scalasca metrics \"Idle threads\" and \"Limited parallelizm\"\n"
                         "  -h     Help; Output a brief help message.\n"
    ;

    while ( ( ch = getopt( argc, argv, "csdr:o:h?" ) ) != -1 )
    {
        switch ( ch )
        {
            case 's':
                add_scalasca_metrics = true;
                break;
            case 'd':
                convert = true;
                break;
            case 'c':
                copy_structure = true;
                break;
            case 'r':
                spec = optarg;
                break;
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

    if ( argc - optind != 1 )
    {
        cerr << USAGE << "\nError: Wrong arguments.\n";
        exit( EXIT_FAILURE );
    }

    string filename = argv[ optind ];
    string epikname = filename.substr( 0, filename.rfind( '/' ) );
    if ( epikname.substr( epikname.rfind( '/' ) + 1, 5 ) != "epik_" )
    {
        epikname.clear();
    }

    Cube* inCube = new Cube();
    // Create new CUBE object
    AggrCube* outCube = NULL;
    if ( copy_structure && !convert )
    {
        outCube = new AggrCube( *inCube );
    }
    else
    {
        outCube = new AggrCube();
    }

    cout << "++++++++++++ Remapping operation begins ++++++++++++++++++++++++++" << endl;
    try
    {
        cout << "Reading " << filename << " ... " << flush;
        inCube->openCubeReport( filename.c_str() );
        cout << " done." << endl;
        cube_remap( outCube, inCube, spec, epikname, convert, add_scalasca_metrics, false, copy_structure );

        cout << "++++++++++++ Remapping operation ends successfully ++++++++++++++++" << endl;

        cout << "Writing " << output << " ... " << flush;
        outCube->writeCubeReport( get_cube4_name( output ), true );
        cout << "done." << endl;
    }
    catch ( const RuntimeError& e )
    {
        std::cerr << e.what() << std::endl;
        delete outCube;
        exit( EXIT_FAILURE );
    }
    delete outCube;
    exit( EXIT_SUCCESS );
}
