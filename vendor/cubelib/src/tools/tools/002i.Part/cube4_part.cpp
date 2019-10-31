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
 * \file cube_part.cpp
 * \brief Parts the system-tree of nodes/processes/threads of a cube.
 *
 */
/******************************************

   Performance Algebra Operation: PART (System-tree)

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

#include <string.h>

#include "Cube.h"
#include "CubeCnode.h"
#include "Filter.h"
#include "CubeMachine.h"
#include "CubeNode.h"
#include "CubeProcess.h"
#include "CubeThread.h"
#include "CubeMetric.h"
#include "CubeRegion.h"
#include "algebra4.h"
#include "CubeServices.h"
#include "CubeError.h"

using namespace std;
using namespace cube;
using namespace services;

/**
 * Main program.
 * - Check calling arguments
 * - Read the .cube input file.
 * - Calls cube_part(...) to part the systemtree.
 * - Saves the result in "-o outputfile" or "part.cube|.gz" file.
 * - end.
 */
int
main( int argc, char* argv[] )
{
    int             ch;
    bool            invert = true;
    string          ranks;
    vector <string> inputs;
    const char*     output = "part";

    const string USAGE =
        "Partition some of system tree (processes) and void the remainder\n"
        "Usage: " + string( argv[ 0 ] ) +
        " [-h] [-I] [-R ranks] [-o output] <cubefile>\n"
        "  -I     Invert sense of partition\n"
        "  -R     List of process ranks for partition (e.g., \"0-3,7,13-\")\n"
        "  -o     Name of the output file (default: " + output + ")\n"
        "  -h     Help; Show this brief help message and exit.\n"
    ;

    while ( ( ch = getopt( argc, argv, "IR:o:h" ) ) != -1 )
    {
        switch ( ch )
        {
            case 'I':
                invert = false;
                break;
            case 'R':
                ranks = optarg;
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

    for ( int i = optind; i < argc; i++ )
    {
        inputs.push_back( argv[ i ] );
    }

    if ( ranks == "" )
    {
        cerr << "Must specify partition criteria" << endl;
        exit( EXIT_FAILURE );
    }

    Cube* theCube = NULL;
    Cube* inCube  = NULL;

    try
    {
        cout << "Open the cube " << inputs[ 0 ] << "...";
        inCube = new Cube();
        inCube->openCubeReport( inputs[ 0 ].c_str() );
        cout << "done." << endl;
        cout << "Copy the  cube object...";
        theCube = new Cube( *inCube, CUBE_DEEP_COPY, CUBE_ENFORCE_ZERO );
        cout << "done." << endl;

        cout << "++++++++++++ Part operation begins ++++++++++++++++++++++++++" << endl;

        const vector<Process*>& procv = theCube->get_procv();
        vector<bool>            partproc( procv.size() );
        for ( size_t p = 0; p < procv.size(); p++ )
        {
            partproc[ p ] = true;
        }
        char* token = strtok( strdup( ranks.c_str() ), "," );
        while ( token )
        {
            char*  sep   = strchr( token, '-' );
            size_t start = atoi( token ), end = start;
            if ( sep == token )
            {
                start = 0;
            }
            if ( sep != NULL )
            {
                sep++;
                end = atoi( sep );
                if ( end == 0 )
                {
                    end = procv.size() - 1;
                }
            }
            if ( end < start )
            {
                cerr << "Invalid rank range: " << token << endl;
            }
            else
            {
                for ( size_t p = start; p <= end; p++ )
                {
                    partproc[ p ] = false;
                }
            }
            token = strtok( NULL, "," );
        }

        size_t void_procs = 0;
        for ( size_t p = 0; p < procv.size(); p++ )
        {
            Process* proc = procv[ p ];
            if ( partproc[ p ] == invert )
            {
                proc->set_name( proc->get_name() + " <VOID>" );
            }
            void_procs += ( partproc[ p ] == invert );
        }

        if ( void_procs == procv.size() )
        {
            cerr << "Error: partition contains none of the " << procv.size() << " processes." << endl;
            delete inCube;
            delete theCube;
            exit( EXIT_FAILURE );
        }
        else if ( void_procs == 0 )
        {
            cerr << "Error: partition contains all of the " << procv.size() << " processes." << endl;
            delete inCube;
            delete theCube;
            exit( EXIT_FAILURE );
        }
        cout << "Voiding " << void_procs << " of " << procv.size() << " processes." << endl;

        const vector<Thread*>&          thrdv = theCube->get_thrdv();
        vector<bool>                    partthrd( thrdv.size() );
        vector<Thread*>::const_iterator tit = thrdv.begin();
        for ( tit = thrdv.begin(); tit != thrdv.end(); ++tit )
        {
            int tid          = ( *tit )->get_id();
            int process_rank = ( *tit )->get_parent()->get_rank();
            partthrd[ tid ] = ( partproc[ process_rank ] != invert );
        }

        const vector<Metric*>&          metv   = theCube->get_metv();
        const vector<Cnode*>&           cnodev = theCube->get_cnodev();
        vector<Metric*>::const_iterator mit;
        for ( mit = metv.begin(); mit != metv.end(); ++mit )
        {
            if ( ( *mit )->get_val() == "VOID" )
            {
                continue;                          // no values to modify
            }
            if ( ( *mit )->get_uniq_name() == "visits" )
            {
                continue;                                   // retain visit counts
            }
            if ( ( *mit )->get_uniq_name() == "imbalance" ) // non-VOID!
            {
                cerr << "Warning: Voiding metrics for " << ( *mit )->get_disp_name() << "!" << endl;
                ( *mit )->set_val( "VOID" );
            }
            vector<Cnode*>::const_iterator cit;
            for ( cit = cnodev.begin(); cit != cnodev.end(); ++cit )
            {
                for ( tit = thrdv.begin(); tit != thrdv.end(); ++tit )
                {
                    int tid = ( *tit )->get_id();
                    if ( partthrd[ tid ] )
                    {
                        continue;
                    }
                    theCube->set_sev( *mit, *cit, *tit, 0.0 );
                }
            }
        }

        cout << "++++++++++++ Part operation ends successfully ++++++++++++++++" << endl;

        cout << "Writing " << output << " ... " << flush;
        theCube->writeCubeReport( output );
        cout << "done." << endl;
    }
    catch ( const RuntimeError& error )
    {
        cerr << error.what() << endl;
        delete inCube;
        delete theCube;
        exit( EXIT_FAILURE );
    }

    delete inCube;
    delete theCube;
    exit( EXIT_SUCCESS );
}
