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
 * \file cube4_dump.cpp
 * \brief Extracts data from the cube in various format
 *
 */
/******************************************

   Performance Algebra Operation: MERGE

 *******************************************/
#include "config.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>


#include "Cube.h"
#include "CubeCnode.h"
#include "CubeMachine.h"
#include "CubeMetric.h"
#include "CubeRegion.h"
#include "CubeServices.h"
#include "CubeTypes.h"
#include "algebra4.h"

#include "cube4_dump_Printer.h"
#include "cube4_dump_GnuPlotPrinter.h"
#include "cube4_dump_GnuPlot2Printer.h"
#include "cube4_dump_CSVPrinter.h"
#include "cube4_dump_CSV2Printer.h"
#ifdef CUBE_DUMP_WITH_R
#include "cube4_dump_RPrinter.h"
#endif

#include "cube4_dump_CommandOption.h"

using namespace std;
using namespace cube;
using namespace services;


enum OutputFormat { HUMAN_READABLE_FORMAT = 0, GNUPLOT_FORMAT = 1, CSV_FORMAT = 2, CSV2_FORMAT = 3, GNUPLOT2_FORMAT = 4, R_FORMAT };




/**
 * Main program.
 * - Check the calling parameters.
 * - For every filename it does
 * - Read the  .cube file. and saves it on alternate way either in 0-th,
   or 1th place in cube[] array.
 * - Calls cube_merge(...) with previous cube (merged) and the current one.
 * - Saves a created merged cube in either "-o output" or "merge.cube|.gz" file.
 * - end.
 */
int
main( int argc, char* argv[] )
{
    int             return_code = EXIT_SUCCESS;
    int             ch;
    vector <string> inputs;

    bool            selected_metric = false;
    bool            selected_cnode  = false;
    ThreadSelection selected_thread = THREADS_AS_ROW;

    bool                selected_header       = false;
    bool                selected_data         = false;
    bool                selected_flat_profile = false;
    bool                disable_clustering    = false;
    bool                show_ghost            = false;
    string              data;
    CalculationFlavour  mf     = cube::CUBE_CALCULATE_INCLUSIVE;
    CalculationFlavour  cf     = cube::CUBE_CALCULATE_EXCLUSIVE;
    bool                stored = false;
    std::string         metric;
    std::vector<string> metricv;
    std::vector<string> _metricv;
//     bool                  check_newmet = false;
    bool                  check_all = false;
    string                tempmet;
    unsigned              cnode_id;
    std::vector<unsigned> cnode_idv;
    unsigned              thread_id;
    std::vector<unsigned> thread_idv;
    std::string           cnode_cond_cubepl;
    bool                  cnode_cond = false;
    stringstream          sstr_c, sstr_t;
    bool                  show_coords = false;
    string                output      = "-";
    OutputFormat          format      = HUMAN_READABLE_FORMAT;



    const string USAGE = "Usage: " + string( argv[ 0 ] ) + " [-m <metrics>|<new metrics>|all|<filename>] [-c <cnode ids>|all|leafs|roots|level>X|level=X|level<X|name=/regext/|<filename>] [-x incl|excl] [-z incl|excl|stored] [-t thread_id|aggr]  [-r] ] [-f name]  [-w] [-g]- [-s human|gnuplot|csv|csv2 ] [-h|-?] [-o output] <cube experiment>\n"
                         "\n"
                         "  -m <metrics>|<new metrics>|all|<filename>\n"
                         "                                        Select one or more of metrics (unique names) for data dump. \n"
                         "                                        \n"
                         "                                        By giving a CubePL expression one can define one or more new metrics by giving correspond formula\n"
                         "                                        If the expression prefixed with \"<name>:\", <name> is used as a unique name for the new metric\n"
                         "                                        <filename> - takes a CubePL expression from file <filename> and defines a derived metric with it \n"
                         "                                        all - all metrics will be printed.\n"
                         "                                        Combination of these three is possible.\n"
                         "  -c <cnode ids>|all|leafs|roots|level>X|level=X|level<X|name=/regexp/|<filename>\n"
                         "                                        Select one or more call paths to be printed out . \n"
                         "                                        <cnode ids> -  list or range of call path ids: 0,3,5-10,25\n"
                         "                                        all - all call paths are printed \n"
                         "                                        leafs - only call paths without children are printed \n"
                         "                                        roots - only root cnodes are printed \n"
                         "                                        level<X, level=X or level>X - only cnodes of the level more, equal or less than N are printed \n"
                         "                                        name=/regexp/ - only cnodes of with the name matching to the regular expression 'regexp' \n"
                         "                                        <filename> - takes a CubePL expression from file <filename> and evaluates it for every callpath. \n"
                         "                                                     If the result is non-zero - call path is included into the output.\n"
                         "  -x incl|excl                          Selects, if the data along the metric tree should be calculated as an inclusive or an exclusive value.\n"
                         "                                        (Default value: incl).\n"
                         "  -z incl|excl|stored                   Selects, if the data along the call tree should be calculated as an inclusive or an exclusive value.\n"
                         "                                        (Default value: excl).\n"
                         "  -t <thread id>|aggr                   Show data for one or more selected threads or aggregated over system tree. \n"
                         "  -r                                    Prints aggregated values for every region (flat profile), sorted by id.\n"
                         "  -f <name>                             Selects a stored data with the name <name> to display\n"
                         "  -d                                    Shows the coordinates for every topology as well.\n"
                         "  -y                                    Disables expansion of clusters and shows bare stored meta structure.\n"
                         "  -w                                    Prints out the information about structure of the cube.\n"
                         "  -g                                    Show ghost metrics (only in combination with -w).\n"
                         "  -o <filename>|-                       Uses a device or STDOUT for the output. If omit, STDOUT is used.\n"
                                                #ifdef CUBE_DUMP_WITH_R
                         "  -s human|gnuplot|gnuplot2|csv|csv2|R           Uses either human readable form, GNUPLOT, CSV (two different layouts) format or binary R matrix for data export.\n"
                                                #else
                         "  -s human|gnuplot|gnuplot2|csv|csv2           Uses either human readable form, GNUPLOT, CSV (two different layouts) format for data export.\n"
                                                #endif
                         "  -h|-?                                 Help; Output a brief help message.\n"

    ;

    while ( ( ch = getopt( argc, argv, "s:o:f:z:x:m:c:t:rdwghy?" ) ) != -1 )
    {
        switch ( ch )
        {
            case 'h':
            case '?':
                cerr << USAGE << endl;
                exit( EXIT_SUCCESS );
                break;
            case 's':
                if ( strcmp( optarg, "gnuplot" ) == 0 )
                {
                    format = GNUPLOT_FORMAT;
                }
                else if ( strcmp( optarg, "gnuplot2" ) == 0 )
                {
                    format = GNUPLOT2_FORMAT;
                }
                else if ( strcmp( optarg, "csv" ) == 0 )
                {
                    format = CSV_FORMAT;
                }
                else if ( strcmp( optarg, "csv2" ) == 0 )
                {
                    format = CSV2_FORMAT;
                }
                #ifdef CUBE_DUMP_WITH_R
                else if ( strcmp( optarg, "R" ) == 0 )
                {
                    format = R_FORMAT;
                }
                                #endif
                break;
            case 'o':
                output = optarg;
                break;
            case 'f':
                data          = optarg;
                selected_data = true;
                break;
            case 'm':
                selected_metric = true;
                tempmet         = optarg;
                // parseMetrics( optarg, metricv, new_metricv, check_newmet, check_all );
                break;
            case 'c':
                // sstr_c << optarg;
                if ( strcmp( optarg, "all" ) == 0 )
                {
                    selected_cnode = false;
                }
                else if ( parseCallPaths_Threads( optarg, cnode_idv ) )
                {
                    //  sstr_c >> cnode_id;
                    selected_cnode = true;
                    ;
                }
                else if ( parseCubePlCnodeCondition( optarg, cnode_cond_cubepl ) )
                {
                    selected_cnode = true;
                    cnode_cond     = true;
                }
                else
                {
                    cerr << USAGE << "\nError: Wrong arguments.\n";
                    exit( EXIT_FAILURE );
                }
                break;
            case 't':
                // sstr_t << optarg;
                if ( strcmp( optarg, "aggr" ) == 0 )
                {
                    selected_thread = AGGREGATED_THREADS;
                }
                else
                {
                    // sstr_t >> thread_id;
                    selected_thread = SELECTED_THREADS;
                    parseCallPaths_Threads( optarg, thread_idv );
                }
                break;
            case 'd':
                show_coords = true;
                break;
            case 'w':
                selected_header = true;
                break;
            case 'g':
                show_ghost = true;
                break;
            case 'y':
                disable_clustering = true;
                break;
            case 'r':
                selected_flat_profile = true;
                break;
            case 'x':
                if ( strcmp( optarg, "excl" ) == 0 )
                {
                    mf = cube::CUBE_CALCULATE_EXCLUSIVE;
                }
                else
                if ( strcmp( optarg, "incl" ) == 0 )
                {
                    mf = cube::CUBE_CALCULATE_INCLUSIVE;
                }
                else
                {
                    cerr << USAGE << "\nError: Wrong arguments.\n";
                    exit( EXIT_FAILURE );
                }
                break;
            case 'z':
                if ( strcmp( optarg, "stored" ) == 0 )
                {
                    stored = true;
                }
                else
                if ( strcmp( optarg, "excl" ) == 0 )
                {
                    cf = cube::CUBE_CALCULATE_EXCLUSIVE;
                }
                else
                if ( strcmp( optarg, "incl" ) == 0 )
                {
                    cf = cube::CUBE_CALCULATE_INCLUSIVE;
                }
                else
                {
                    cerr << USAGE << "\nError: Wrong arguments.\n";
                    exit( EXIT_FAILURE );
                }
                break;
            default:
                cerr << USAGE << "\nError: Wrong arguments.\n";
                exit( EXIT_FAILURE );
        }
    }

    if ( argc - optind < 1 )
    {
        cerr << USAGE << "\nError: Wrong arguments.\n";
        exit( EXIT_FAILURE );
    }

    for ( int i = optind; i < argc; i++ )
    {
        inputs.push_back( argv[ i ] );
    }

    fstream    _fout;
    ostream&   fout = cout;
    streambuf* buf  = NULL;
    if ( ( output.compare( "-" ) != 0 ) )
    {
        _fout.open(  output.c_str(),  fstream::in | fstream::out | fstream::trunc );
        if ( !_fout.is_open() )
        {
            cerr << "Cannot open " << output << " to use as an output device. " << endl;
            exit( EXIT_FAILURE );
        }
        buf = fout.rdbuf();
        fout.rdbuf( _fout.rdbuf() );
    }

    int    num  = inputs.size();
    Cube** cube = new Cube*[ num ];

    Printer* printer = NULL;


    // _______________________________________________________________________
    // num is the number of files

    for ( int i = 0; i < num; i++ )
    {
        cube[ i ] = NULL;
        cube[ i ] = new Cube();
        try
        {
            cube[ i ]->openCubeReport( inputs[ i ].c_str(), disable_clustering );

            if ( cnode_cond )
            {
                cnodeSelection( cube[ i ], cnode_cond_cubepl,  cnode_idv );
            }


            if ( selected_metric == true )
            {
                parseMetrics( tempmet, _metricv, cube[ i ] );
                parseNewMetric( _metricv, metricv, check_all, cube[ i ] );
            }

            if ( format == GNUPLOT_FORMAT )
            {
                printer = new GnuPlotPrinter( fout, cube[ i ] );
            }
            else if ( format == GNUPLOT2_FORMAT )
            {
                printer = new GnuPlot2Printer( fout, cube[ i ] );
            }
            else
            if ( format == HUMAN_READABLE_FORMAT )
            {
                printer = new Printer( fout, cube[ i ] );
            }
            else
            if ( format == CSV_FORMAT )
            {
                printer = new CSVPrinter( fout, cube[ i ] );
            }
            else
            if ( format == CSV2_FORMAT )
            {
                printer = new CSV2Printer( fout, cube[ i ] );
            }
                        #ifdef CUBE_DUMP_WITH_R
            else
            if ( format == R_FORMAT )
            {
                // we're not exporting into file
                if ( output.compare( "-" ) == 0 )
                {
                    cerr << "Output to R matrix requires specifying file to output"  << endl;
                    exit( EXIT_FAILURE );
                }
                printer = new RPrinter( output, cube[ i ] );
            }
                        #endif
            std::vector<Metric*>    root_metrics = cube[ i ]->get_root_metv();
            std::vector<Metric*>    metrics      = cube[ i ]->get_metv();
            std::vector<Cnode*>     root_cnodes  = cube[ i ]->get_root_cnodev();
            std::vector<Cnode*>     cnodes       = cube[ i ]->get_cnodev();
            std::vector<Machine*>   machines     = cube[ i ]->get_machv();
            std::vector<Node*>      nodes        = cube[ i ]->get_nodev();
            std::vector<Process*>   processs     = cube[ i ]->get_procv();
            std::vector<Thread*>    threads      = cube[ i ]->get_thrdv();
            std::vector<Cartesian*> cartv        = cube[ i ]->get_cartv();
            std::vector<Region*>    regions      = cube[ i ]->get_regv();
            if ( selected_header )
            {
                printer->print_header(  data, show_ghost, selected_data, show_coords );
            }

            if ( selected_metric )
            {
                std::vector < Metric* > _metrics;
                if ( check_all == true ) // show all metrics
                {
                    _metrics = metrics;
                }
                else
                {
                    for ( size_t mv_iter = 0; mv_iter != metricv.size(); ++mv_iter )
                    {
                        metric = metricv[ mv_iter ];
                        _metrics.push_back( cube[ i ]->get_met( metric ) );
                    }
                }

                std::vector < Cnode* > _cnodes;
                if ( selected_cnode )
                {
                    for ( size_t cv_iter = 0; cv_iter != cnode_idv.size(); ++cv_iter )
                    {
                        cnode_id = cnode_idv[ cv_iter ];
                        for ( vector<Cnode*>::iterator c_iter = cnodes.begin(); c_iter != cnodes.end(); ++c_iter )
                        {
                            if ( ( *c_iter )->get_id() == cnode_id )
                            {
                                _cnodes.push_back( *c_iter );
                            }
                        }
                    }
                }
                else
                {
                    _cnodes = cnodes;
                }
                std::vector < Thread* > _threads;
                if ( selected_thread == SELECTED_THREADS )
                {
                    for ( size_t tv_iter = 0; tv_iter != thread_idv.size(); ++tv_iter )
                    {
                        thread_id = thread_idv[ tv_iter ];
                        for ( vector<Thread*>::iterator t_iter = threads.begin(); t_iter != threads.end(); ++t_iter )
                        {
                            if ( ( *t_iter )->get_id() == thread_id )
                            {
                                _threads.push_back( *t_iter );
                            }
                        }
                    }
                }
                else
                {
                    _threads = threads;
                }

                if ( selected_flat_profile )
                {
                    printer->dump_flat_profile( _metrics, regions, _threads, mf, selected_thread );
                }
                else
                {
                    printer->dump_data( _metrics, _cnodes, _threads, mf, cf, stored, selected_thread );
                }
            }
        }
        catch ( const RuntimeError& error )
        {
            delete cube[ i ];
            cube[ i ] = 0;
            cerr << error.what() << endl;
            return_code = EXIT_FAILURE;
        }
        delete printer;
    }

    for ( int i = 0; i < num; i++ )
    {
        delete cube[ i ];
    }
    delete[] cube;
    if ( _fout.is_open() )
    {
        fout.rdbuf( buf );
        _fout.close();
    }
    return return_code;
}
