/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2019                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2009-2015                                                **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  Copyright (c) 2003-2008                                                **
**  University of Tennessee, Innovative Computing Laboratory               **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/**
 * \file cube_test.cpp
 * \brief
 *
 */

#include "config.h"

// #ifdef CUBE_COMPRESSED
#include "CubeZfstream.h"
// #endif
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <ostream>
#include <sstream>
#include <unistd.h>
#include <cmath>
#include <cstdlib>
#if 0
#  include <getopt.h>
#endif

#include "AbridgeTraversal.h"

#include "MultiMdAggrCube.h"

#include "Cube.h"
#include "CubeCnode.h"
#include "CubeError.h"
#include "CubeServices.h"

#include "CMetricCnodeConstraint.h"
#include "CnodeConstraint.h"
#include "AbstractConstraint.h"
#include "CnodeSubForest.h"
#include "CnodeMetric.h"

#include "CCnode.h"

using namespace std;
using namespace cube;
using namespace services;


#include "test_calls.h"

void
finalize( vector<AggrCube*>&,
          MultiMdAggrCube*& );                        // forward declaration of a function with cube destruction (used on several places)


int
main( int argc, char* argv[] )
{
    int ch = 0;

#if 0
    int          option_index = 0;
    const string USAGE        = "Usage: " + string( argv[ 0 ] ) + " [ flags ] <cube1> <cube2>\n"
                                "where flags is any combination of the following options:\n"
                                "  -h, --help                        Help; Output a brief help message.\n"
                                "  -c, --create-tree tree1[,tree2]   \n"
                                "  -e, --equals metric[,tree]        \n"
                                "  -s, --similar metric,tol[,tree]   \n"
                                "  -a, --abs-cut metric,thrh[,tree]  \n"
                                "  -r, --rel-cut metric,thrh[,tree]  \n"
                                "  -x, --csum-cut metric,thrh[,tree] \n";

    static struct option long_options[] = {
        { "help",        no_argument,            0,            'h'            },
        { "output",      required_argument,      0,            'o'            },
        { "create-tree", required_argument,      0,            'c'            },
        { "equals",      required_argument,      0,            'e'            },
        { "similar",     required_argument,      0,            's'            },
        { "abs-cut",     required_argument,      0,            'a'            },
        { "rel-cut",     required_argument,      0,            'r'            },
        { "csum-cut",    required_argument,      0,            'x'            },
    };
#else
    const string LONGHELP = ""
                            "Compares two or more experiments according to some specified criteria. Prints out a summary of the \n"
                            "outcome of the tests and optionally also prints out more detailed information to a file.\n"
                            "\n"
                            "The key idea behind the cube_test tool is to create new call trees out of the default call tree \"ALL\" \n"
                            "that contains the whole call tree, to remove certain nodes from that tree and to apply checks on these \n"
                            "sub-trees. \n"
                            "\n"
                            "We provide two examples below. \n"
                            "\n"
                            "The first example simply checks whether the visits metric matches exactly and \n"
                            "if the time metric matches approximately. For a detailed explanation of the comparison \n"
                            "behaviour, see below. \n"
                            "The file \"details.log\", we specified using the -o option, contains more details about the two cases where the \n"
                            "\"time\" metric did not match sufficiently closely. We can find more details in the file details.log \n"
                            "\n"
                            "       user@host% ./cube_test -e visits -s time,REL,0.33 -o details.log summary.1.cube.gz summary.2.cube.gz \n"
                            "       Equality basic@visits:incl:*.* ... 20 / 20 OK \n"
                            "       Similarity basic@time:incl:*.* (relative, 0.33) ... 18 / 20 OK \n"
                            "\n"
                            "Let us examine the errors detailed in the details.log file. \n"
                            "       user@host% cat details.log \n"
                            "       ...\n"
                            "       In call node with id 1 (Name: Init) \n"
                            "       for cnode metric Time (basic@time:incl:*.*) \n"
                            "       | Time    | Time    | Call path \n"
                            "       | 0.5193  | 0.7538  | Init (File: main.c, Line: -1) \n"
                            "       | 63.2041 | 63.5443 | called by main (File: main.c, Line: -1) \n"
                            "       Absolute difference between the file with id 1 and a file with \n"
                            "       a lower id is 0.234487 but should be lower than 0.210071. \n"
                            "       ... \n"
                            "\n"
                            "The second example creates the tree \"time_rel\" as a copy of the ALL tree and removes all nodes from \n"
                            "that tree where the time metric is below 1 second (aggregated over all processes). Then it runs the \n"
                            "same test as above. \n"
                            "\n"
                            "       user@host% ./cube_test -c time_rel -a time,1,time_rel -s time,REL,0.33 summary.1.cube.gz summary.2.cube.gz \n"
                            "       Similarity basic@time:incl:*.* (relative, 0.33) ... 4 / 4 OK \n"
                            "\n"
                            "\n"
                            "The string \"metric\" can have the following form:    metric uniq_metric_name[:[[INCL | EXCL]:[Process[.Thread]]]];"
                            "\n"
                            "\"uniq_metric_name\" is the name of the metric as reported by the list option.\n"
                            "INCL means that you want to print out the inclusive value and EXCL represents the exclusive value. \n"
                            "Finally \"Process\" is the process you want to aggregate this value over. \"*\" means that the value is aggregated over all processes.\n"
                            "If Process is a non-* value then Thread may be the Process-local rank of the thread that the value is printed out for.\n"
                            "\n"
                            "\n"
    ;
    const string USAGE = "Usage: " + string( argv[ 0 ] ) + " [ flags ] <cube1> <cube2>\n"
                         "where flags is any combination of the following options:\n"
                         "  -?                        Help; Output a brief help message.\n"
                         "  -h                        Help; Output a long help message.\n"
                         "  -o                        Set the output file. If omitted, STDOUT is used. \n"
                         "  -c tree1[,tree2]          Create a new copy of the tree \"tree2\" that is called \"tree1\".\n"
                         "                            If \"tree2\" is omitted, \"tree1\" will be a copy of the \"ALL\" \n"

                         "  -e metric[,tree]          Checks whether the metric described by the string \"metric\" is equal for all provided CUBE files and for all nodes of the tree \"tree\". \n"
                         "                            If tree is omitted, all nodes are checked.\n"
                         "  -s metric,type,tol[,tree] Checks whether the metric described by the string \"metric\" is sufficiently similar for all CUBE files, according to the qualifiers type and \"tol\".\n"
                         "                            \"tol\" specifies the tolerance which is given as a real number. The meaning of the tolerance value depends on the \"type\".\n"
                         "                            \"type\" is either ABS or REL. If \"type\" is ABS than the nodes are similar if the difference between all values for that metric is below \"tol\".\n"
                         "                            If \"type\" is REL than the nodes are similar if the difference between all values for that metric is below:\n"
                         "\n"
                         "                                        Sum_{i=1}^n tol*[value of metric for cnode of i-th file]/n ,\n"
                         "\n"
                         "                             where n is the number of CUBE files.\n"
                         "                             If \"tree\" is omitted, all nodes are checked. \n"
                         "  -a metric,thrh[,tree]     Removes all nodes from the tree \"tree\" whose values are below \"thrh\" for the metric \"metric\". \n"
                         "                            If tree is omitted, nodes are removed from the default tree ALL.\n"
                         "  -r metric,thrh[,tree]     Removes all nodes from the tree \"tree\" whose values are below \"thrh\" percent of the sum of all roots values. \n"
                         "                            \"thrh\" is supposed to be a value between 0 and 1. \n"
                         "                            If \"tree\" is omitted, nodes are removed from the default tree ALL.\n"
                         "  -x metric,thrh[,tree]     For each node of the tree tree we consider all children N of that node. \n"
                         "                            Let vi be the value for the given metric and the node i in N. Then we select a maximal subset M (smaller than N) with the property \n"
                         "\n"
                         "                                        Sum_{i over M} vi  <=  thrh x Sum_{i in M} vi \n"
                         "\n"
                         "                            and remove all nodes from M. \n"
                         "                            If tree is omitted, nodes are removed from the default tree ALL.\n"
                         "  -v [0,1,2,3]              Verbosity level: 0 - silent, 1 - report only summary, 2 - report only errors, 3 - report status of all tests\n"
                         "\n"
                         "\n"
                         "WARNING: The order of the options matters.\n";

#endif

    const char* short_options = "v:o:c:e:s:a:r:x:h?";

    MultiMdAggrCube*  cinfo = NULL;
    vector<AggrCube*> cubes;


    try {
        Constraint_Verbosity verbosity      = FAILVERB_SILENT;
        ostream*             details_stream = &( std::cout );

#if 0
        while ( ( ch = getopt_long( argc, argv, short_options,
                                    long_options, &option_index ) ) != -1 )
        {
#else
        while ( ( ch = getopt( argc, argv, short_options ) ) != -1 )
        {
#endif
            switch ( ch )
            {
                case 'h':
                    cerr << endl << LONGHELP << endl;
                /* FALLTHRU */
                case '?':
                    cerr << USAGE << endl;
                    return 0;
                case 'v':
                    if ( strcmp( optarg, "0" ) == 0 )
                    {
                        cout << " Set verbosity level to 0 (silent)." << endl;
                        verbosity = FAILVERB_SILENT;
                    }
                    else
                    if ( strcmp( optarg, "1" ) == 0 )
                    {
                        cout << " Set verbosity level to 1 (summary)." << endl;
                        verbosity = FAILVERB_SUMMARY;
                    }
                    else
                    if ( strcmp( optarg, "2" ) == 0 )
                    {
                        cout << " Set verbosity level to 2 (errors report)." << endl;
                        verbosity = FAILVERB_ERRORS;
                    }
                    else
                    if ( strcmp( optarg, "3" ) == 0 )
                    {
                        cout << " Set verbosity level to 3 (all tests report)." << endl;
                        verbosity = FAILVERB_TESTS;
                    }
                    else
                    {
                        cerr << " Verbosity level is unknown. Set to 1 (summary)." << endl;
                        verbosity = FAILVERB_SUMMARY;
                    }
                    break;
                case 'o':
                    if ( verbosity == FAILVERB_SILENT )
                    {
                        verbosity = FAILVERB_ERRORS;
                    }

//             throw Error("Please provide at most one output file!");

                    ofstream* helper = new ofstream();
                    helper->open( optarg, ios::out );
                    details_stream = helper;
                    break;
            }
        }
        ;

        if ( argc - optind < 2 )
        {
            cerr << "Please provide exactly two cube files." << endl;
            return 1;
        }




        for ( int i = 0; i < argc - optind; ++i )
        {
            cubes.push_back( openCubeFile( argv[ optind + i ] ) );
        }
        cinfo = new MultiMdAggrCube( cubes );


        optind = 1;

        map<string, CnodeSubForest*> forests;
        forests[ "all" ] = cinfo->get_forest();


#if 0
        while ( ( ch = getopt_long( argc, argv, short_options,
                                    long_options, &option_index ) ) != -1 )
        {
#else
        while ( ( ch = getopt( argc, argv, short_options ) ) != -1 )
        {
#endif
            switch ( ch )
            {
                case 'h':
                case '?':
                    break;
                case 'c':
                {
                    string::size_type pos;
                    string            arg = string( optarg );
                    string            t1  = "", t2 = "";
                    pos = arg.find( "," );
                    t1  = arg.substr( 0, pos );
                    if ( pos != string::npos )
                    {
                        t2 = arg.substr( pos + 1 );
                    }
                    else
                    {
                        t2 = "all";
                    }

                    map<string, CnodeSubForest*>::iterator it = forests.find( t1 );
                    if ( it != forests.end() )
                    {
                        throw Error( "The forest " + t1 + " exists already!" );
                    }
                    it = forests.find( t2 );
                    if ( it == forests.end() )
                    {
                        throw Error( "The forest " + t2 + " does not exist, but you "
                                     "asked me to create a copy from it!" );
                    }
                    forests.insert( pair<string, CnodeSubForest*>(
                                        t1, new CnodeSubForest( *( it->second ) ) ) );
                }
                break;
                case 'e':
                {
                    string::size_type pos;
                    string            metric, tree = "all", arg = string( optarg );
                    pos    = arg.find( "," );
                    metric = arg.substr( 0, pos );
                    if ( pos != string::npos )
                    {
                        tree = arg.substr( pos + 1 );
                    }
                    CnodeMetric* m = cinfo->get_cnode_metric( metric );

                    if ( forests.find( tree ) == forests.end() )
                    {
                        throw Error( "Could not find tree " + tree + "!" );
                    }
                    if ( m == NULL )
                    {
                        throw Error( "Could not parse " + metric + "?" );
                    }

                    CnodesEquivalent constraint =
                        CnodesEquivalent( forests[ tree ], m->stringify() );
                    constraint.set_details_stream( *details_stream );
                    constraint.set_verbosity( verbosity );
                    constraint.check();
                }
                break;
                case 's':
                {
                    string::size_type             pos1, pos2, pos3;
                    string                        metric, mode_str, tree = "all", arg = string( optarg );
                    EquivalenceTest_ToleranceMode mode;
                    double                        tolerance = 0.;

                    pos1 = arg.find( "," );
                    if ( pos1 == string::npos )
                    {
                        throw Error( "Could not find comma in argument " + arg );
                    }
                    pos2 = arg.find( ",", pos1 + 1 );
                    if ( pos2 == string::npos )
                    {
                        throw Error( "Could not find second comma in argument " + arg );
                    }
                    pos3     = arg.find( ",", pos2 + 1 );
                    metric   = arg.substr( 0, pos1 );
                    mode_str = arg.substr( pos1 + 1, pos2 - pos1 - 1 );
                    if ( pos3 == string::npos )
                    {
                        tolerance = atof( arg.substr( pos2 + 1 ).c_str() );
                    }
                    else
                    {
                        tolerance = atof( arg.substr( pos2 + 1, pos3 - pos2 - 1 ).c_str() );
                        tree      = arg.substr( pos3 + 1 );
                    }

                    CnodeMetric* m = cinfo->get_cnode_metric( metric );

                    if ( mode_str == "REL" || mode_str == "RELATIVE" )
                    {
                        mode = RELATIVE;
                    }
                    else if ( mode_str == "ABS" || mode_str == "ABSOLUTE" )
                    {
                        mode = ABSOLUTE;
                    }
                    else
                    {
                        throw Error( "Unknown mode " + mode_str + "!" );
                    }
                    if ( forests.find( tree ) == forests.end() )
                    {
                        throw Error( "Could not find tree " + tree + "!" );
                    }
                    if ( m == NULL )
                    {
                        throw Error( "Could not parse " + metric + "?" );
                    }

                    CnodesEquivalent constraint =
                        CnodesEquivalent( forests[ tree ], m->stringify(),
                                          tolerance, mode );
                    constraint.set_details_stream( *details_stream );
                    constraint.set_verbosity( verbosity );
                    constraint.check();
                }
                break;
                case 'r':
                case 'a':
                case 'x':
                {
                    string::size_type pos1, pos2;
                    string            metric, tree = "all", arg = string( optarg );
                    double            threshold;

                    pos1 = arg.find( "," );
                    if ( pos1 == string::npos )
                    {
                        throw Error( "Could not find comma in argument " + arg );
                    }
                    pos2   = arg.find( ",", pos1 + 1 );
                    metric = arg.substr( 0, pos1 );
                    if ( pos2 == string::npos )
                    {
                        threshold = atof( arg.substr( pos1 + 1 ).c_str() );
                    }
                    else
                    {
                        threshold = atof( arg.substr( pos1 + 1, pos2 - pos1 - 1 ).c_str() );
                        tree      = arg.substr( pos2 + 1 );
                    }

                    CnodeMetric* m = cinfo->get_cnode_metric( metric );

                    if ( forests.find( tree ) == forests.end() )
                    {
                        throw Error( "Could not find tree " + tree + "!" );
                    }
                    if ( m == NULL )
                    {
                        throw Error( "Could not parse " + metric + "?" );
                    }

                    if ( ch == 'r' )
                    {
                        AbridgeTraversal( m->stringify(), threshold,
                                          THRTYPE_ROOT_RELATIVE ).run( forests[ tree ] );
                    }
                    else if ( ch == 'a' )
                    {
                        AbridgeTraversal( m->stringify(), threshold,
                                          THRTYPE_ABSOLUTE ).run( forests[ tree ] );
                    }
                    else
                    {
                        AbridgeTraversal( m->stringify(), threshold,
                                          THRTYPE_CUMSUM ).run( forests[ tree ] );
                    }
                }
                break;
                case 'o':
                case 'v':
                    break;
                default:
                    cerr << USAGE << endl << "Error: Wrong arguments." << endl;
                    finalize( cubes, cinfo );
                    return 1;
            }
        }
        finalize( cubes, cinfo );

        if ( details_stream != &( std::cout ) )
        {
            dynamic_cast<ofstream*>( details_stream )->close();
            delete details_stream;
        }
    }
    catch ( const Error& error )
    {
        finalize( cubes, cinfo );
        cerr << error.what() << endl;
        return 1;
    }
}



void
finalize( vector<AggrCube*>& cubes, MultiMdAggrCube*& cinfo )
{
    for ( vector<AggrCube*>::iterator it = cubes.begin(); it != cubes.end(); ++it )
    {
        delete *it;
    }

    delete cinfo;
}
