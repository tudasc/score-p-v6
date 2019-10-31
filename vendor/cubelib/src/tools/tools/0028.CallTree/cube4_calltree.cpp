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
 * \file cube_calltree.cpp
 * \brief Prints out in a tree format a call path with values for given
   (-m metricname) metric.
 *
 * It implements a non recursive algorithm to print out the tree structure.
   Cnodes are saved in a vector ccnt.  Internaly they save a parent-child relation
   between eachother. It is a reason for "non recursive" algorithm.
 */
#include "config.h"

// #ifndef CUBE_COMPRESSED
#include <fstream>
// #else
#include "CubeZfstream.h"
// #endif

#include <iomanip>
#include <string>
#include <algorithm>
#include <numeric>
#include <list>
#include <map>
#include <iostream>

#include "Cube.h"
#include "CubeCnode.h"
#include "CubeThread.h"
#include "CubeMetric.h"
#include "CubeRegion.h"
#include "helper.h"
#include "CubeServices.h"

#include "CnodeInfo.h"

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <limits>

#include "calltree_calls.h"

using namespace std;
using namespace cube;
using namespace services;


/**
 * Main program.
 * - Check calling arguments
 * - Read the .cube file
 * - If necessary -> collect data from metrics.
 * - Get a cnodes and print them out (with or wthout metrics value) with
   indentation according to the level of cnode in tree hierarchy.
 * - end.
 */
int
main( int argc, char* argv[] )
{
//   size_t fcnt(0); // unused
    bool   annotate( false );
    int    c;
    int    tab( 16 );
    double treashold = -std::numeric_limits<double>::max();
    opterr = 0;
    string             metric_name( "undef" );
    vector <string>    inputs;
    bool               do_metric( false );
    bool               do_treashold( false );
    bool               display_percent( false );
    bool               display_callpath( false );
    CalculationFlavour cf                 = cube::CUBE_CALCULATE_EXCLUSIVE;
    vector<double>*    pvec               = NULL; // initialized only if do_metric="true" and used also in this case.
    double             total_metric_value = std::numeric_limits<double>::max();

    while ( ( c = getopt( argc, argv, "ichapm:f:t:" ) ) != -1 )
    {
        switch ( c )
        {
            case 'a':
                annotate = true;
                break;
            case 'c':
                display_callpath = true;
                break;
            case 'm':
                metric_name = string( optarg );
                do_metric   = true;
                break;
            case 't':
                treashold = strtod( optarg, NULL );
                if ( treashold >= 100 )
                {
                    std::cerr << "ERROR: Value of a treashold should be a percent value in range of from 0 to 100" << std::endl;
                    usage( argv[ 0 ], EXIT_FAILURE );
                }
                treashold   /= 100.;
                do_treashold = true;
                break;
            case 'i':
                cf = CUBE_CALCULATE_INCLUSIVE;
                break;
            case 'h':
                usage( argv[ 0 ], EXIT_SUCCESS );
                break;
            case 'p':
                display_percent = true;
                tab             = 32;
                break;
            case 'f':
                inputs.push_back( string( optarg ) );
                break;
            default:
                break;
        }
    }

    if ( do_treashold &&  !do_metric )
    {
        cerr << "Error: Treashold value should be specified for some metric. See \"-m\".\n\n";
        usage( argv[ 0 ], EXIT_FAILURE );
    }

    if ( ( argc - optind > 0 ) || inputs.size() != 0 /* no file was given */ )
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
        cerr << "Error: Input file is  required.\n\n";
        usage( argv[ 0 ], EXIT_FAILURE );
    }

    Cube* input = NULL;



    for ( unsigned fi = 0; fi < inputs.size(); fi++ )
    {
        try
        {
            // Read input files
            cerr << "Reading " << inputs[ fi ] << "...";
            input = new Cube();
            input->openCubeReport( inputs[ fi ].c_str() );

            cerr << " done." << endl;



            // --- fill out a vector in deep first order
            const vector<Cnode*>& roots_cnodes = input->get_root_cnodev();
            vector<Cnode*>        cnodes;
            for ( vector<Cnode*>::const_iterator iter = roots_cnodes.begin(); iter != roots_cnodes.end(); ++iter )
            {
                Cnode* _cnode = *iter;
                get_deep_first_enimeration( _cnode, cnodes );
            }

            size_t            ccnt = cnodes.size();
            std::vector<bool> cnode_include( ccnt, ( ( do_metric ) ? false : true ) );

            vector<string> callpaths( ccnt, "undefined" );
            vector<string> cnode_names( ccnt, "undefined" );

            CCnodeInfo cninfo( input );

            if ( do_metric )
            {
                if ( metric_name.compare( "undef" ) == 0 )
                {
                    std::cerr << "ERROR: No metric name is given." << std::endl;
                    usage( argv[ 0 ], EXIT_FAILURE );
                    continue;
                }

                Metric* metric = input->get_met( metric_name );
                if ( metric == NULL )
                {
                    std::cerr << "ERROR: Metric " << metric_name << " doesn't exist in the input file." << std::endl;
                    continue;
                }
                pvec               = new vector<double>( ccnt, 0 );
                total_metric_value = input->get_sev( metric, cube::CUBE_CALCULATE_INCLUSIVE );
                for ( size_t ci = 0; ci < ccnt; ++ci )
                {
                    Cnode* c = cnodes[ ci ];

                    if ( c->isHidden() )
                    {
                        cnode_include[ ci ] = false;
                        continue;
                    }

                    double _tmp = input->get_sev( metric, cube::CUBE_CALCULATE_INCLUSIVE, c, cube::CUBE_CALCULATE_INCLUSIVE );


                    ( *pvec )[ ci ] =  input->get_sev( metric, cube::CUBE_CALCULATE_INCLUSIVE, c, cf );



                    if ( ( _tmp / total_metric_value ) >= treashold )
                    {
                        cnode_include[ ci ] = true;
                        // include all parents
                        int    cci = ci;
                        Cnode* _p  = c->get_parent();
                        while ( cci >= 0 && _p != NULL )
                        {
                            cci--;
                            if ( cnodes[ cci ] == _p )
                            {
                                cnode_include[ cci ] = true;
                                _p                   = cnodes[ cci ]->get_parent();
                            }
                        }
                    }
                    else
                    {
                        c->hide();
                        cnode_include[ ci ] = false;
                        int    cci = ci;
                        Cnode* _p  = c->get_parent();
                        while ( cci >= 0 && _p != NULL )
                        {
                            cci--;
                            if ( cnodes[ cci ] == _p )
                            {
                                if ( cnodes[ cci ]->isVisible() )
                                {
                                    ( *pvec )[ cci ] = input->get_sev( metric, cube::CUBE_CALCULATE_INCLUSIVE, _p, cf );
                                    //                                  break;
                                }
                                cnode_include[ cci ] = true;
                                _p                   = cnodes[ cci ]->get_parent();
                            }
                        }
                    }
                }
            } // if do_metric




            /*
                build string-formatted --calltree--

                example:

             + task_init
             |   + mpi_init
             |   |   + tracing
             |   + bcast_int
             |   |   + mpi_bcast
             |   + barrier_sync
             |   |   + mpi_barrier
             + read_input
             |   + bcast_int
             |   |   + mpi_bcast

                results in cnode_names[] and callpaths[]
             */

            cnode_names[ 0 ] = cnodes[ 0 ]->get_callee()->get_name();
            callpaths[ 0 ]   = "/" + cnode_names[ 0 ];
            int nl( -1 ); /* height of the current stack  */
            for ( size_t ci = 1; ci < ccnt; ++ci )
            {
                if ( !cnode_include[ ci ] )
                {
                    continue;
                }
                Cnode*        c      = cnodes[ ci ];
                Cnode*        parent = c->get_parent();
                const Region* r      = c->get_callee();
                string        name   = r->get_name();
                cnode_names[ ci ] = "  + " + name;
                nl++;
                if ( cnodes[ ci - 1 ] != parent )
                {
                    if ( parent != NULL )
                    {
                        nl = get_level( *c ) - 1;
                    }
                    else  // found another root element
                    {
                        nl                = -1;
                        cnode_names[ ci ] = name;
                    }
                }
                if ( nl >= 0 )
                {
                    for ( size_t sf = 0; sf < ( size_t )nl; sf++ )
                    {
                        cnode_names[ ci ] = "  | " + cnode_names[ ci ];
                    }
                }
                callpaths[ ci ] = get_callpath_for_cnode( *c );
            }

            int maxstrlen( 0 );
            for ( size_t i = 0; i < ccnt; i++ )
            {
                if ( !cnode_include[ i ] )
                {
                    continue;
                }
                int l = cnode_names[ i ].length();
                if ( l > maxstrlen )
                {
                    maxstrlen = l;
                }
            }

            for ( size_t i = 0; i < ccnt; i++ )
            {
                if ( !cnode_include[ i ] )
                {
                    continue;
                }
                cout << left;
                if ( do_metric )
                {
                    double value  = 0.;
                    double pvalue = 100;
                    string unit   = "";
                    value = ( *pvec )[ i ];
                    stringstream sstr;
                    sstr <<  value;
                    if ( display_percent )
                    {
                        pvalue = ( *pvec )[ i ] / total_metric_value * 100.;
                        unit   = "%";
                        sstr << " (" << setprecision( ( pvalue < 10 ) ? 4 : 5 ) <<  pvalue << unit << ")";
                        if ( cnodes[ i ]->isHidden() )
                        {
                            sstr << "(x)";
                        }
                    }
                    cout <<  setw( tab ) << sstr.str();
                }

                cout << setw( maxstrlen + 4 )
                     << cnode_names[ i ];
                if ( display_callpath )
                {
                    if ( annotate )
                    {
                        cout << Callpathtype2String( cninfo[ i ] )
                             << ":";
                    }

                    cout << callpaths[ i ];
                }
                cout << endl;
            }
        }
        catch ( const RuntimeError& error )
        {
            cerr << error.what() << endl;
            delete input;
            delete pvec;
            exit( EXIT_FAILURE );
        }
    }
    delete input;
    delete pvec;
    exit( EXIT_SUCCESS );
}
