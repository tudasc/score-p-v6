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
 * \file cube_info.cpp
 * \brief Contains the cube4_info tool which is a tool to print out information
 *        about a single or multiple cube files and some metric values.
 *
 * Please take a look at the USAGE string for a description of the available
 * options. You may also want to use cube4_info -h from the command line.
 */

#include "config.h"
// #ifndef CUBE_COMPRESSED
#include <fstream>
// #else
#include "CubeZfstream.h"
// #endif
#include <iomanip>
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#if 0
#  include <getopt.h>
#endif

#include "AggrCube.h"
#include "Cube.h"
#include "CubeError.h"
#include "CubeServices.h"
#include "CubeNode.h"
#include "CubeProcess.h"
#include "helper.h"

#include "MdAggrCube.h"
#include "MultiMdAggrCube.h"
#include "AbridgeTraversal.h"
#include "ComputeTraversal.h"
#include "DiffPrintTraversal.h"
#include "AggregatedMetric.h"
#include "VisitorsMetric.h"
#include "CnodeSubForest.h"


using namespace std;
using namespace cube;
using namespace services;


#include "info_calls.h"


int
main( int argc, char* argv[] )
{
    int    ch = 0;
    string node_name;
    string show_cnode;

#if 0
    int          option_index = 0;
    const string USAGE        = "Usage: " + string( argv[ 0 ] ) + " [ flags ] <cube experiments>\n"
                                "where flags is any combination of the following options:\n"
                                "  -h, --help                  Help; Output a brief help message.\n"
                                "  -t, --time                  Shows the metric \"time\" (inclusive, aggregated\n"
                                "                                over all threads.)\n"
                                "  -v, --visits                Shows the metric \"visits\" (exclusive, aggregated\n"
                                "                                over all threads.)\n"
                                "  -w, --visitors              Shows the number of visitors for each Cnode, i.e.\n"
                                "                                the number of threads that have a visits counter\n"
                                "                                of 1 or higher.\n"
                                "  -m met, --metric met        Shows the metric described by the string met.\n"
                                "  -l, --list                  Lists all available metrics.\n"
                                "  -b, --basics                Shows some basic information about the cube file.\n"
                                "  -a, --absolute met,thrh     Checks whether a node's value for a certain metric\n"
                                "                                is below a given threshold with respect to the\n"
                                "                                node's absolute value. Affected nodes are\n"
                                "                                aggregated to a single node and output of their\n"
                                "                                children is suppressed.\n"
                                "  -r, --relative met,thrh     Like --absolute, but based on a percentage of the\n"
                                "                                root's value.\n"
                                "  -x, --cum-sum met,thrh      Like --absolute, but based on selecting most\n"
                                "                                relevant children of a node at each level.\n"
                                "\n"
                                "met must have the following form:\n"
                                "   unique_metric_name:[incl|excl]:process_number.thread_number\n"
                                "It is allowed to omit anything except for the metric's unique name, so\n"
                                "\"time\" would compute the inclusive time aggregated over all threads or\n"
                                "\"time:excl:2\" would compute the exclusive time aggregated over all threads\n"
                                "that belong to the process with the id 2.\n";

    static struct option long_options[] = {
        { "time",      no_argument,          0,          't'          },
        { "visits",    no_argument,          0,          'v'          },
        { "visitors",  no_argument,          0,          'w'          },
        { "basics",    no_argument,          0,          'b'          },
        { "list",      no_argument,          0,          'l'          },
        { "metric",    required_argument,    0,          'm'          },
        { "inclusive", required_argument,    0,          'i'          },
        { "exclusive", required_argument,    0,          'e'          },
        { "relative",  required_argument,    0,          'r'          },
        { "absolute",  required_argument,    0,          'a'          },
        { "cum-sum",   required_argument,    0,          'x'          },
        { "help",      no_argument,          0,          'h'          },
    };
#else
    const string USAGE = "Usage: " + string( argv[ 0 ] ) + " [ flags ] <cube experiments>\n"
                         "where flags is any combination of the following options:\n"
                         "  -h              Help; Output a brief help message.\n"
                         "  -t              Shows the metric \"time\" (inclusive, aggregated\n"
                         "                     over all threads.)\n"
                         "  -v              Shows the metric \"visits\" (exclusive, aggregated\n"
                         "                     over all threads.)\n"
                         "  -w              Shows the number of visitors for each Cnode, i.e.\n"
                         "                     the number of threads that have a visits counter\n"
                         "                     of 1 or higher.\n"
                         "  -m met          Shows the metric described by the string met.\n"
                         "  -l              Lists all available metrics.\n"
                         "  -b              Shows some basic information about the cube file.\n"
                         "  -a met,thrh     Checks whether a node's value for a certain metric\n"
                         "                     is below a given threshold with respect to the\n"
                         "                     node's absolute value. Affected nodes are\n"
                         "                     aggregated to a single node and output of their\n"
                         "                     children is suppressed.\n"
                         "  -r met,thrh     Like --absolute, but based on a percentage of the\n"
                         "                     root's value.\n"
                         "  -x met,thrh     Like --absolute, but based on selecting most\n"
                         "                     relevant children of a node at each level.\n"
                         "\n"
                         "met must have the following form:\n"
                         "   unique_metric_name:[incl|excl]:process_number.thread_number\n"
                         "It is allowed to omit anything except for the metric's unique name, so\n"
                         "\"time\" would compute the inclusive time aggregated over all threads or\n"
                         "\"time:excl:2\" would compute the exclusive time aggregated over all threads\n"
                         "that belong to the process with the id 2.\n";
#endif

    const char* short_options = "m:a:r:x:bhltvw?";

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
            case 'h': // --help
            case '?':
                cout << USAGE;
                return 0;
        }
    }

    MdAggrCube* cinfo;

    try {
        vector<string>            metrics;            // /< a list of the metrics that is print out.
        vector<AbridgeTraversal*> abridge_traversals; // /< a list of
        // / AbridgeTraversal instances that is applied before printing out.

        // / Creates either a MultiMdAggrCube instance or a MdAggrCube instance
        // / depending on the number of input cubes.
        if ( argc - optind >= 2 )
        {
            vector<AggrCube*> cubes;
            for ( int i = 0; i < argc - optind; ++i )
            {
                cubes.push_back( openCubeFile( argv[ optind + i ] ) );
            }
            cinfo = new MultiMdAggrCube( cubes );
        }
        else if ( argc - optind == 1 )
        {
            AggrCube* in = openCubeFile( argv[ optind++ ] ); /* XXX: Bad Hack!!! */
            cinfo = new MdAggrCube( *in );
            delete in;
        }
        else
        {
            cerr << "Please provide at least one cube file." << endl;
            return 1;
        }

        optind = 1;

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
                case 'b': // --basics
                {
                    const vector<Node*>&    nodes = cinfo->get_nodev();
                    const vector<Process*>& procs = cinfo->get_procv();

                    cout << "Number of nodes    : " << nodes.size() << endl
                         << "Processes per node : " << nodes[ 0 ]->num_children() << endl
                         << "Number of processes: " << procs.size() << endl
                         << "Wallclock time     : " << get_atotalt( cinfo, "time" ) << endl;
                    return 0;
                }
                case 'h': // --help
                case '?':
                    break;
                case 'l': // --list, prints out a number of available metrics.
                {
                    const vector<Metric*> metrics = cinfo->get_metv();
                    for ( vector<Metric*>::const_iterator metric = metrics.begin();
                          metric != metrics.end(); ++metric )
                    {
                        cout << ( *metric )->get_uniq_name() << endl;
                    }
                    delete cinfo;
                    return 0;
                }
                case 'm': // --metric, add metric to list of output metrics.
                    metrics.push_back(
                        cinfo->add_cnode_metric(
                            new AggregatedMetric( string( optarg ) ) )->stringify() );
                    break;
                case 't': // --time, add time metric to list of output metrics.
                    metrics.push_back(
                        cinfo->add_cnode_metric(
                            new AggregatedMetric( "time" ) )->stringify() );
                    break;
                case 'v': // --visits, add visits metric to list of output metrics.
                    metrics.push_back(
                        cinfo->add_cnode_metric(
                            new AggregatedMetric( "visits:excl" ) )->stringify() );
                    break;
                case 'w': // --visitors, add visitors metric to list of output metrics.
                    metrics.push_back(
                        cinfo->add_cnode_metric(
                            new VisitorsMetric( "visitors@" ) )->stringify() );
                    break;
                case 'a': // --absolute, create abridge based on absolute value.
                case 'r': // --relative, create abridge based on relative value.
                case 'x': // --cum-sum
                {
                    string arg = string( optarg );
                    size_t pos = arg.find( "," );
                    if ( pos == string::npos )
                    {
                        throw Error( "Could not parse " + arg + "!" );
                    }
                    string metric     = arg.substr( 0, pos );
                    double val        = atof( arg.substr( pos + 1 ).c_str() );
                    string metric_str = ( cinfo->add_cnode_metric(
                                              new AggregatedMetric( metric ) ) )->stringify();
                    if ( ch == 'a' )
                    {
                        abridge_traversals.push_back( new AbridgeTraversal( metric_str, val,
                                                                            THRTYPE_ABSOLUTE ) );
                    }
                    else if ( ch == 'r' )
                    {
                        abridge_traversals.push_back( new AbridgeTraversal( metric_str, val,
                                                                            THRTYPE_ROOT_RELATIVE ) );
                    }
                    else
                    {
                        abridge_traversals.push_back( new AbridgeTraversal( metric_str, val,
                                                                            THRTYPE_CUMSUM ) );
                    }
                }
                break;
                default:
                    cerr << USAGE << endl << "Error: Wrong arguments." << endl;
                    return 1;
            }
        }

        CnodeSubForest* all = cinfo->get_forest();
        for ( vector<AbridgeTraversal*>::iterator trav = abridge_traversals.begin();
              trav != abridge_traversals.end(); ++trav )
        {
            ( *trav )->run( all );
        }


        DiffPrintTraversal( metrics ).run( all );


        for ( vector<AbridgeTraversal*>::iterator trav = abridge_traversals.begin();
              trav != abridge_traversals.end(); ++trav )
        {
            delete ( *trav );
        }
        delete all;
        delete cinfo;
    }
    catch ( const Error& error ) // Does this pointer have to be deleted? Memory allocated not in stack, but in heap...
    {
        cerr << error.what() << endl;
        return -1;
    }
}
