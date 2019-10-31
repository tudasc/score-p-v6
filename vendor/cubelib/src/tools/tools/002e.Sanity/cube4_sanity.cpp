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
 * \file cube_sanity.cpp
 * \brief Runs some sanity checks on a .cube file and reports eventual errors.
 *
 */
#include "config.h"

// #ifdef CUBE_COMPRESSED
#include "CubeZfstream.h"
// #endif
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <unistd.h>
#if 0
#  include <getopt.h>
#endif

#include "MdAggrCube.h"
#include "CnodeConstraint.h"
#include "RegionConstraint.h"
#include "PrintableCCnode.h"
#include "CCnode.h"
#include "CRegion.h"
#include "Filter.h"

#include "Cube.h"
#include "CubeCnode.h"
#include "CubeRegion.h"
#include "CubeError.h"
#include "CubeServices.h"

#define CUBE_SANITY_INTERNAL_ERROR -1
#define CUBE_SANITY_OK 0
#define CUBE_SANITY_TESTS_FAILED 1

using namespace std;
using namespace cube;



#include "sanity_calls.h"











int
main( int argc, char* argv[] )
{
    int             ch   = 0;
    MdAggrCube*     cube = NULL;
    map<char, bool> settings;
    settings[ 'n' ] = false;
    settings[ 'l' ] = false;
    Filter               filter;
    string               output_filename;
    Constraint_Verbosity verbosity_level = FAILVERB_SILENT;
    ofstream             out;

    // list of tests
    RegionConstraint*           non_empty                            = NULL;
    NoAnonymousFunctions*       no_anonymous_functions               = NULL;
    NoTruncatedFunctions*       no_truncated_functions               = NULL;
    RegionConstraint*           filename_not_empty                   = NULL;
    RegionConstraint*           proper_line_numbers                  = NULL;
    CnodeConstraint*            no_tracing_outside_init_and_finalize = NULL;
    NoNegativeInclusiveMetrics* no_negative_inclusive_metrics        = NULL;
    NoNegativeExclusiveMetrics* no_negative_exclusive_metrics        = NULL;
#if 0
    int          option_index = 0;
    const string USAGE        = "Usage: " + string( argv[ 0 ] ) + " [ flags ] <cube experiment>\n"
                                "where flags basically turns certains tests on or off:\n"
                                "  -h, --help                    Help; Output a brief help message.\n"
                                "  -n, --no-negative-values      Disables the (time consuming) ckeck for negative\n"
                                "                                metric values.\n"
                                "  -l, --no-line-numbers         Disables checks for line numbers.\n"
                                "  -f, --filter <file.filt>      Checks whether a node's name is matched by a\n"
                                "                                pattern in file.filt.\n"
                                "  -o, --output <output_file>    Path of the output file. If no output file is\n"
                                "                                given, detailed output will be suppressed. A\n"
                                "                                summary will always be printed out to stdout.\n";

    static struct option long_options[] = {
        { "help",               no_argument,                   0,                   'h'                   },
        { "no-negative-values", no_argument,                   0,                   'n'                   },
        { "no-line-numbers",    no_argument,                   0,                   'l'                   },
        { "filter",             required_argument,             0,                   'f'                   },
        { "output",             required_argument,             0,                   'o'                   }
    };
#else
    const string USAGE = "Usage: " + string( argv[ 0 ] ) + " [ flags ] <cube experiment>\n"
                         "where flags basically turns certains tests on or off:\n"
                         "  -h                   Help; Output a brief help message.\n"
                         "  -n                   Disables the (time consuming) check for negative\n"
                         "                          inclusive metric values.\n"
                         "  -x                   Disables the (time consuming) check for negative\n"
                         "                          exclusive metric values.\n"
                         "  -l                   Disables checks for line numbers.\n"
                         "  -f <file.filt>       Checks whether a node's name is matched by a\n"
                         "                          pattern in file.filt.\n"
                         "  -o <output_file>     Path of the output file. If no output file is\n"
                         "                          given, detailed output will be suppressed. A\n"
                         "                          summary will always be printed out to stdout.\n"
                         "  -v <0|1|2|3>         Verbosity level of output\n";
#endif
    const char* short_options = "o:f:nxv:lh?";

#if 0
    while ( ( ch = getopt_long( argc, argv, short_options, long_options, &option_index ) ) != -1 )
#else
    while ( ( ch = getopt( argc, argv, short_options ) ) != -1 )
#endif
    {
        switch ( ch )
        {
            case 'n':
                settings[ 'n' ] = true;
                break;
            case 'x':
                settings[ 'x' ] = true;
                break;
            case 'l':
                settings[ 'l' ] = true;
                break;
            case 'f':
                filter.add_file( string( optarg ) );
                break;
            case 'o':
                output_filename = string( optarg );
                break;
            case 'h':
                cout << USAGE;
                return 0;
            case 'v':
                verbosity_level = static_cast<Constraint_Verbosity>( strtol( optarg, NULL, 0 ) );
                break;
            default:
                cout << USAGE
                     << "Error: Unknown option -" << ch << endl;
                return 1;
        }
    }

    try
    {
        if ( argc - optind != 1 )
        {
            cout << USAGE << endl;
            return CUBE_SANITY_INTERNAL_ERROR;
        }

        /* XXX: BAD HACK! The >> operator is not overloaded for MdAggrCube and
         *                Cube is not virtual.
         */
        Cube* _cube = openCubeFile( argv[ optind ] );
        cube = new MdAggrCube( *_cube );
        delete _cube;

        CnodeSubForest* all = cube->get_forest();

        non_empty = new NameNotEmptyOrUnknown( all );

        if ( filter.empty() == false )
        {
            ( new ProperlyFiltered( all, filter ) )->set_parent( non_empty );
        }

        no_anonymous_functions = new NoAnonymousFunctions( all );
        no_anonymous_functions->set_parent( non_empty );

        no_truncated_functions = new NoTruncatedFunctions( all );
        no_truncated_functions->set_parent( non_empty );

        filename_not_empty = new FilenameNotEmpty( all );
        filename_not_empty->set_parent( non_empty );

        if ( settings[ 'l' ] == false )
        {
            proper_line_numbers = new ProperLineNumbers( all );
            proper_line_numbers->set_parent( filename_not_empty );
        }

        no_tracing_outside_init_and_finalize
            = new NoTracingOutsideInitAndFinalize( all );
        no_tracing_outside_init_and_finalize->set_parent( non_empty );

        if ( settings[ 'n' ] == false )
        {
            no_negative_inclusive_metrics = new NoNegativeInclusiveMetrics( cube );
            no_negative_inclusive_metrics->set_verbosity( verbosity_level );
        }

        if ( settings[ 'x' ] == false )
        {
            no_negative_exclusive_metrics = new NoNegativeExclusiveMetrics( cube );
            no_negative_exclusive_metrics->set_verbosity( verbosity_level );
        }

        if ( output_filename.empty() == false )
        {
            out.open( output_filename.c_str(), ios::out );
            non_empty->set_details_stream( out, true );

            if ( no_negative_inclusive_metrics != NULL )
            {
                no_negative_inclusive_metrics->set_details_stream( out, true );
            }
            if ( no_negative_exclusive_metrics != NULL )
            {
                no_negative_exclusive_metrics->set_details_stream( out, true );
            }
        }

        non_empty->set_verbosity( verbosity_level, true );
        non_empty->check();
        if ( no_negative_inclusive_metrics != NULL )
        {
            no_negative_inclusive_metrics->check();
        }
        if ( no_negative_exclusive_metrics != NULL )
        {
            no_negative_exclusive_metrics->check();
        }




        if ( output_filename.empty() == false )
        {
            out.close();
        }

        delete no_truncated_functions;
        delete no_anonymous_functions;
        delete non_empty;
        delete no_negative_exclusive_metrics;
        delete no_negative_inclusive_metrics;
        delete filename_not_empty;
        delete proper_line_numbers;
        delete no_tracing_outside_init_and_finalize;
        delete cube;
    }
    catch ( const Error& error )   // Does this pointer have to be deleted? Memory allocated not in stack, but in heap...
    {
        cerr << error.what() << endl;
        delete no_truncated_functions;
        delete no_anonymous_functions;
        delete non_empty;
        delete no_negative_exclusive_metrics;
        delete no_negative_inclusive_metrics;
        delete filename_not_empty;
        delete proper_line_numbers;
        delete no_tracing_outside_init_and_finalize;
        delete cube;
        return CUBE_SANITY_INTERNAL_ERROR;
    }
}
