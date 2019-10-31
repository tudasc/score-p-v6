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
 * \file cube_nodeview.cpp
 * \brief Displays information about some specific metric
   (max, min values, and so on) and node related information
   (threads total, threads per node,...).
 *
 */
#include "config.h"

// #ifndef CUBE_COMPRESSED
#include <fstream>
// #else
#include "CubeZfstream.h"
// #endif
#include <iomanip>
#include <string>
#include <set>
#include <map>
#include <numeric>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <limits>



#include "AggrCube.h"
#include "CubeCnode.h"
#include "CubeThread.h"
#include "CubeMetric.h"
#include "CubeRegion.h"
#include "CubeNode.h"
#include "CubeServices.h"
#include "CubeError.h"

using namespace std;
using namespace cube;
using namespace services;


#include "nodeview_calls.h"

/**
 * Main program.
 * - Check the calling parameters.
 * - For every filename it does
 * - Read the  .cube file..
 * - Gets nodes, processes, regions, threads, calltrees of the cube.
 * - Calculate interesting values for metrics (per node, per thread, ...)
 * - Finds a maximum and minimum values.
 * - Prints in table form the collected information.
 * - end.
 */
int
main( int argc, char* argv[] )
{
    if ( argc == 1 )
    {
        usage( argv[ 0 ] );
    }

    bool header( true );

    string cubefile( "undef" );
    string metricname( "undef" );
    int    c;
    opterr = 0;

    int argcount( 1 );
    while ( ( c = getopt( argc, argv, "m:h" ) ) != -1 )
    {
        switch ( c )
        {
            case 'h':
                usage( argv[ 0 ] );
                break;

            case 'm':
                metricname = string( optarg );
                argcount  += 2;
                break;
        }
    }

    while ( argcount < argc )
    {
        cubefile = string( argv[ argcount ] );
        argcount++;

        AggrCube* input = NULL;
        try
        {
            input = new AggrCube();
            input->openCubeReport( cubefile );


            const vector<Node*>& nodes = input->get_nodev();
            //     const vector<Process*>& procs   = input->get_procv(); // unused
            const vector<Thread*>& threads = input->get_thrdv();
            const vector<Cnode*>&  cnodes  = input->get_cnodev();
            const vector<Region*>& regions = input->get_regv();

            Metric* metric;

            if ( metricname == "undef" )
            {
                metricname = string( "time" );
            }
            metric = input->get_met( metricname );

            if ( metric == 0 )
            {
                cerr << "Error: unknown metric\n";
                exit( EXIT_FAILURE );
            }

            /*
               accumulate metric values on a per thread basis
             */
            vector<double> pt_mvalues( threads.size(), 0.0 );
            for ( size_t i = 0; i < threads.size(); ++i )
            {
                for ( size_t j = 0; j < cnodes.size(); j++ )
                {
                    pt_mvalues[ i ] += input->get_sev( metric, cnodes[ j ], threads[ i ] );
                }
            }

            /*
               accumulate metric values on a per node basis
             */
            map<Node*, double> pn_mvalues;
            for ( size_t i = 0; i < threads.size(); ++i )
            {
                //       Process* parent_proc = threads[i]->get_parent();
                //       Node* parent_node = parent_proc->get_parent();

                //       Process* parent_proc = ;
                Node* parent_node = ( Node* )( ( Sysres* )threads[ i ]->get_parent() )->get_parent();


    #ifdef DEBUG
                cout << "Thread " << i << " belongs to node " << nodeId << endl;
    #endif
                pn_mvalues[ parent_node ] += pt_mvalues[ i ];
//                 cout << "___ ! " <<  nodeId << " " << pn_mvalues[ nodeId ]  << " " << pt_mvalues[ i ] << endl;
            }
            ;

            /*
               Calculate total number of threads
             */
            int numthreads( 0 );
            for ( size_t i = 0; i < nodes.size(); ++i )
            {
                for ( size_t j = 0; j < nodes[ i ]->num_groups(); j++ )
                {
                    numthreads += ( ( Sysres* )nodes[ i ]->get_location_group( j ) )->num_children();
                }
            }
            /* done */

            // size_t min_id(0);
            double min_val( std::numeric_limits<double>::max() );
            // size_t max_id(0);
            double max_val( -std::numeric_limits<double>::max() );
            for ( map<Node*, double>::iterator i = pn_mvalues.begin(); i !=  pn_mvalues.end(); ++i )
            {
                if ( ( *i ).second > max_val )
                {
                    max_val = ( *i ).second;
                    // max_id=i;
                }
                if ( ( *i ).second < min_val )
                {
                    min_val = ( *i ).second;
                    // min_id=i;
                }
            }
            double avg = accumulate( pn_mvalues.begin(), pn_mvalues.end(), 0.0, map_add() ) / ( double )nodes.size();
            double stddev( 0.0 );
            for (  map<Node*, double>::iterator i = pn_mvalues.begin(); i !=  pn_mvalues.end(); ++i )
            {
                double tmp = ( *i ).second - avg;
                stddev += tmp * tmp;
            }
            stddev = sqrt( stddev );

            const int w0( 16 );
            const int w1( 8 );
            const int w2( metricname.length() + 6 );

            int prec = 2;
            //   if (metricname=="time") prec=2;
            //   else prec=0;

            if ( header )
            {
                header = false;
                cout << right
                     << setw( w1 ) << "Nodes"
                     << setw( w1 ) << "Total"
                     << setw( w2 ) << "Per node"
                     << setw( w1 ) << "Regions"
                     << setw( w1 ) << "Cnodes"
                     << setw( w2 ) << "Metric"
                     << setw( w0 ) << "Max"
                     << setw( w0 ) << "Min"
                     << setw( w0 ) << "Avg"
                     << setw( w0 ) << "Std_dev"
                     << left << " Cubefile" << endl;
                cout << right
                     << setw( w1 ) << ""
                     << setw( w1 ) << "Threads"
                     << setw( w2 ) << "Threads"
                     << endl;
            }

            cout << right
                 << setw( w1 ) << nodes.size()
                 << setw( w1 ) << numthreads
                 << setprecision( 2 ) << fixed
                 << setw( w2 ) << threads_per_node( nodes )
                 << setw( w1 ) << regions.size()
                 << setw( w1 ) << cnodes.size()
                 << setw( w2 ) << metricname
                 << setprecision( prec ) << fixed
                 << setw( w0 ) << max_val
                 << setprecision( prec ) << fixed
                 << setw( w0 ) << min_val
                 << setprecision( prec ) << fixed
                 << setw( w0 ) << avg
                 << setw( w0 ) << stddev
                 << left
                 << " " + cubefile << endl;

            if ( input != NULL )
            {
                delete input;
            }
        }
        catch ( const RuntimeError& error )
        {
            cerr << error.what() << endl;
        }
    }
}
