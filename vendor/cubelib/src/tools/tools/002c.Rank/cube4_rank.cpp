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
 * \file cube_rank.cpp
 * \brief Calculates a probability for every region of the program to be run by
   ranking it based on some metric ("visits" default).
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
#include <stdexcept>
#include <vector>
#include <set>
#include <cmath>
#include <valarray>

#include "Cube.h"
#include "CubeCnode.h"
#include "CubeThread.h"
#include "CubeMetric.h"
#include "CubeRegion.h"
#include "CubeServices.h"
#include "CubeError.h"

#include "helper.h"

using namespace std;
using namespace cube;
using namespace services;


#include "rank_calls.h"

/**
 * Main program.
 * - Check the calling parameters.
 * - Read the  .cube file..
 * - Read absolut values of ranks. Create absolut ranking.
 * - Transform absolut ranking into gradient ranking.
 * - Print the probability for every region.
 * - end.
 */
int
main( int argc, char* argv[] )
{
//     size_t fcnt = 0;  // unused
    int c;
    opterr = 0;
    string cubefile;
    string metricname = string( "visits" );
    //    bool propose = false;

    while ( ( c = getopt( argc, argv, "m:p" ) ) != -1 )
    {
        switch ( c )
        {
            case 'm':
                metricname = string( optarg );
                break;
            case 'p':
//	    propose=true;
                break;
        }
    }

    cubefile = string( argv[ argc - 1 ] );

    cerr << "Reading " << cubefile << "...";
    Cube* input = NULL;
    try
    {
        input = new Cube();
        input->openCubeReport( cubefile.c_str() );

        cerr << " done." << endl;

        Ranking ranking = find_ranking( input, metricname );

        ranking = gradient_ranking( ranking );

        const double one = cgfnd( 0.0, 1.0, -10.0, 10.0 );

        std::cout << "Following value should be close to one: " << one << std::endl;

        //     const vector<Region*>&  regions = input->get_regv(); // unused
        const vector<Cnode*>& cnodes = input->get_cnodev();

        for ( size_t i = 0; i < ranking.size(); i++ )
        {
            const int w0 = 12;
            const int w1 = 6;

            //  const size_t threadId = ranking[i].second.second; // unused
            const size_t  cnodeId = ranking[ i ].second.first;
            const double  prob    = ranking[ i ].first;
            const Region* callee  = cnodes[ cnodeId ]->get_callee();

            cout << right
                 << setw( w1 ) << cnodes[ cnodeId ]->get_id()
                 << fixed << setprecision( 4 )
                 << setw( w0 ) << prob << " "
                 << callee->get_name()
                 << endl;
        }
    }
    catch ( const RuntimeError& error )
    {
        cerr << error.what() << endl;
    }

    if ( input != NULL )
    {
        delete input;
    }
}
