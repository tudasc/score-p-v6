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


#include "config.h"

#include <algorithm>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctype.h>
#include <unistd.h>
#if 0
#  include <getopt.h>
#endif




#include "Canonizer.h"
#include "GenericCanonizer.h"
#include "PDTCanonizer.h"

using namespace cube;
using namespace std;


int
main( int argc, char** argv )
{
    int         ch = 0;
    const char* in_name;
    const char* out_name;
#if 0
    int          options_index = 0;
    const string USAGE         = "Usage: " + string( argv[ 0 ] ) + " [ flags ] <input> <output>\n"
                                 "where flags is any combination of the following:\n"
                                 "   -h, --help\n"
                                 "   -p, --pdt\n"
                                 "   -m, --max-length\n"
                                 "   -c, --lower-case\n"
                                 "   -f, --remove-file-names\n"
                                 "   -l, --remove-line-numbers\n";

    static struct option long_options[] = {
        { "help",                no_argument,                 0,                 'h'                 },
        { "pdt",                 no_argument,                 0,                 'p'                 },
        { "max-length",          required_argument,           0,                 'm'                 },
        { "lower-case",          no_argument,                 0,                 'c'                 },
        { "remove-file-names",   no_argument,                 0,                 'f'                 },
        { "remove-line-numbers", no_argument,                 0,                 'l'                 }
    };
#else
    const string USAGE = "Usage: " + string( argv[ 0 ] ) + " [ flags ] <input> <output>\n"
                         "where flags is any combination of the following:\n"
                         "   -h         Print this help\n"
                         "   -p         Use PDT format\n"
                         "   -m <num>   Maximum length\n"
                         "   -c         Lower case\n"
                         "   -f         Remove file names\n"
                         "   -l         Remove line numbers\n";
#endif

    const char* short_options = "m:flhpc?";

    int  max_length        = 0;
    bool case_sensitive    = true;
    bool remove_file_names = false, remove_lines = false;
    bool pdt               = false;

#if 0
    while ( ( ch = getopt_long( argc, argv, short_options, long_options, &options_index ) )
            != -1 )
#else
    while ( ( ch = getopt( argc, argv, short_options ) ) != -1 )
#endif
    {
        switch ( ch )
        {
            case 'c':
                case_sensitive = false;
                break;
            case 'm':
                max_length = atoi( optarg );
                break;
            case 'f':
                remove_file_names = true;
                break;
            case 'l':
                remove_lines = true;
                break;
            case 'p':
                pdt = true;
                break;
            case 'h':
            case '?':
                cout << USAGE << endl;
                return 0;
            default:
                cerr << "Unrecognized option: " << ch << endl;
                return 1;
        }
    }

    if ( argc - optind != 2 )
    {
        cerr << "Please provide an input and an output cube file!" << endl;
        cerr << USAGE << endl;
        return 2;
    }
    else
    {
        in_name  = argv[ optind++ ];
        out_name = argv[ optind++ ];
    }

    Canonizer* canonizer;
    if ( pdt )
    {
        canonizer = new PDTCanonizer();
    }
    else
    {
        canonizer = new GenericCanonizer();
    }

    canonizer->max_length( max_length );
    canonizer->case_sensitive( case_sensitive );
    canonizer->remove_file_names( remove_file_names );
    canonizer->remove_line_numbers( remove_lines );
    try
    {
        canonizer->run( in_name, out_name );
    }
    catch ( const RuntimeError& error )
    {
        cerr << error.what() << endl;
        return -1;
    }

    delete canonizer;
    return 0;
}
