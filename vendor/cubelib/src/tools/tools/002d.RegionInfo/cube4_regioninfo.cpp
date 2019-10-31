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
 * \file cube_regioninfo.cpp
 * \brief Collect a data about every region in a cube and prints it out.
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
#include <vector>

#include "Blacklist.h"
#include "AggrCube.h"
#include "CubeCnode.h"
#include "CubeThread.h"
#include "CubeMetric.h"
#include "CubeRegion.h"
#include "CubeServices.h"
#include "CubeError.h"

#include "CnodeInfo.h"
#include "RegionInfo.h"

#include "helper.h"

using namespace std;
using namespace cube;
using namespace services;

#include "regioninfo_calls.h"

/**
 * Main program.
 * - Check calling arguments
 * - Read the .cube input file.
 * - Create blacklist for the cube and regions in the cube.
 * - Run over metrics (comma separated values in command parameter.) and for every metric do.
 * - Calculate a values for every region for given metric.
 * - Create a trace cost.
 * - Prints the result in human readable form.
 * - end.
 */
int
main( int argc, char* argv[] )
{
    string cubefile;
    string blacklistname;
    string metriclist;

//     bool use_rl(false); // unused
    bool do_regions( false );
    bool do_blacklist( false );
    bool do_metriclist( false );
    bool do_maxtbc( false );
    bool do_totaltbc( false );

    int c;

    if ( argc == 1 )
    {
        usage( argv[ 0 ] );
    }

    opterr = 0;
    int mna( 1 );

    while ( ( c = getopt( argc, argv, "m:hrl:" ) ) != -1 )
    {
        switch ( c )
        {
            case 'h':
                usage( argv[ 0 ] );
                break;
            case 'r':
                do_regions = true;
                mna++;
                break;
            case 'l':
                blacklistname = string( optarg );
                do_blacklist  = true;
                mna          += 2;
                break;
            case 'm':
                metriclist    = string( optarg );
                do_metriclist = true;
                mna          += 2;
                break;
        }
    }



    if ( mna == ( argc ) )
    {
        usage( argv[ 0 ] );
    }
    else if ( mna == ( argc - 1 ) )
    {
        cubefile = string( argv[ argc - 1 ] );
    }
    AggrCube* input = NULL;
    try
    {
        input = new AggrCube();
        input->openCubeReport( cubefile );
        cout << " done." << endl;

        const vector<Region*>& regions = input->get_regv();

        const size_t rcnt = regions.size();
        //     const size_t tcnt = threads.size(); // unsused
        CRegionInfo reginfo = input;

        CBlacklist* blacklist = 0;
        if ( do_blacklist )
        {
            blacklist = new CBlacklist( input, blacklistname, &reginfo );
        }
        /*
           BEGIN: pre-calculate total runtime and total number of visits
         */

        vector<metric_data<double> > metricdata;
        if ( do_metriclist )
        {
            size_t oldpos = 0;
            while ( true )
            {
                const size_t f = metriclist.find_first_of( ',', oldpos );
                string       metricname;
                if ( f == string::npos )
                {
                    metricname = metriclist.substr( oldpos );
                }
                else
                {
                    metricname = metriclist.substr( oldpos, f - oldpos );
                }

                oldpos = f + 1;

                if ( metricname == "max_tbc" )
                {
                    do_maxtbc = true;
                    if ( f == string::npos )
                    {
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }

                if ( metricname == "total_tbc" )
                {
                    do_totaltbc = true;
                    if ( f == string::npos )
                    {
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
                metricdata.push_back( metric_data<double>() );
                metricdata[ metricdata.size() - 1 ].name = metricname;
                if ( f == string::npos )
                {
                    break;
                }
            }
        }
        else
        {
            metricdata.push_back( metric_data<double>() );
            metricdata[ 0 ].name = string( "time" );
            do_maxtbc            = true;
        }

        for ( size_t i = 0; i < metricdata.size(); i++ )
        {
            metricdata[ i ].metric = input->get_met( metricdata[ i ].name );

            if ( metricdata[ i ].metric != 0 )
            {
                input->get_reg_tree( metricdata[ i ].excl, metricdata[ i ].incl, metricdata[ i ].diff, INCL, INCL, metricdata[ i ].metric, 0 );
            }
            else
            {
                cout << "unknown metric: " << metricdata[ i ].name << "\n";
                exit( EXIT_FAILURE );
            }
            acc_with_type<double>( metricdata[ i ], reginfo, blacklist );
        }

        /*
           DONE: pre-calculate total runtime and total number of visits
         */

        tracefile_costs tbcosts( calculate_tracefile_costs( input, reginfo, blacklist ) );
        /*
           BEGIN: Print results
         */

        size_t w0 = 14;

        if ( do_regions )
        {
            /* calculate layout information */
            for ( size_t i = 0; i < rcnt; i++ )
            {
                size_t l = regions[ i ]->get_name().length();
                if ( l > w0 )
                {
                    w0 = l;
                }
            }
        }

        w0 += 2;
        const int w1 = 14;
        const int w2 = 8;

        cout << right
             << setw( 3 )  << "bl"
             << setw( 6 )  << "type";
        if ( do_maxtbc )
        {
            cout << setw( w1 ) << "max_tbc";
        }
        if ( do_totaltbc )
        {
            cout << setw( w1 ) << "total_tbc";
        }

        for ( size_t i = 0; i < metricdata.size(); i++ )
        {
            size_t n  = string::npos;
            int    sz = metricdata[ i ].name.length();
            if ( sz > w1 )
            {
                n = w2 - 3;
            }

            cout << setw( w1 ) << metricdata[ i ].name.substr( 0, n )
                 << setw( w2 )  << "%";
        }

        cout << left
             << " "
             << "region"
             << endl;

        if ( do_regions )
        {
            for ( size_t i = 0; i < rcnt; i++ )
            {
                if ( reginfo[ i ] == NUL )
                {
                    continue;
                }

                if ( do_blacklist )
                {
                    if ( ( *blacklist )( ( Region* )regions[ i ] ) )
                    {
                        cout << " * ";
                    }
                    else
                    {
                        cout << "   ";
                    }
                }
                else
                {
                    cout << "   ";
                }

                cout << right
                     << setw( 6 ) << Callpathtype2String( reginfo[ i ] );
                if ( do_maxtbc )
                {
                    cout << setw( w1 ) << tbcosts.max_costs_by_region[ i ];
                }
                if ( do_totaltbc )
                {
                    cout << setw( w1 ) << tbcosts.acc_costs_by_region[ i ];
                }

                for ( size_t j = 0; j < metricdata.size(); j++ )
                {
                    int prec = 0;
                    if ( metricdata[ j ].isfloat() )
                    {
                        prec = 2;
                    }
                    cout << setprecision( prec ) << fixed
                         << setw( w1 ) << metricdata[ j ].excl[ regions[ i ] ]
                         << setprecision( 2 ) << fixed
                         << setw( w2 ) << percent( metricdata[ j ].total, metricdata[ j ].excl[ regions[ i ] ] );
                }

                cout << left
                     << " "
                     << regions[ i ]->get_name() << endl;
            }
            cout << endl;
        }

        cout << right
             << "   " << "   ANY";

        if ( do_maxtbc )
        {
            cout << setw( w1 ) << tbcosts.max_all;
        }
        if ( do_totaltbc )
        {
            cout << setw( w1 ) << tbcosts.acc_all;
        }
        for ( size_t i = 0; i < metricdata.size(); i++ )
        {
            int prec = 0;
            if ( metricdata[ i ].isfloat() )
            {
                prec = 2;
            }
            cout << setw( w1 ) << setprecision( prec ) << fixed << metricdata[ i ].total
                 << setw( w2 ) << setprecision( 2 ) << fixed << percent( metricdata[ i ].total, metricdata[ i ].total );
        }
        cout << left  << " (summary) ALL"
             << endl;

        cout << right
             << "   " << "   MPI";
        if ( do_maxtbc )
        {
            cout << setw( w1 ) << tbcosts.max_mpi;
        }
        if ( do_totaltbc )
        {
            cout << setw( w1 ) << tbcosts.acc_mpi;
        }
        for ( size_t i = 0; i < metricdata.size(); i++ )
        {
            int prec = 0;
            if ( metricdata[ i ].isfloat() )
            {
                prec = 2;
            }
            cout << setw( w1 ) << setprecision( prec ) << fixed << metricdata[ i ].mpi
                 << setw( w2 ) << setprecision( 2 ) << fixed << percent( metricdata[ i ].total, metricdata[ i ].mpi );
        }
        cout << left  << " (summary) MPI"
             << endl;

        cout << right
             << "   " << "   USR";

        if ( do_maxtbc )
        {
            cout << setw( w1 ) << tbcosts.max_usr;
        }
        if ( do_totaltbc )
        {
            cout << setw( w1 ) << tbcosts.acc_usr;
        }

        for ( size_t i = 0; i < metricdata.size(); i++ )
        {
            int prec = 0;
            if ( metricdata[ i ].isfloat() )
            {
                prec = 2;
            }

            cout << setw( w1 ) << setprecision( prec ) << fixed << metricdata[ i ].usr
                 << setw( w2 ) << setprecision( 2 ) << fixed << percent( metricdata[ i ].total, metricdata[ i ].usr );
        }

        cout << left  << " (summary) USR"
             << endl;

        cout << right
             << "   " << "   COM";
        if ( do_maxtbc )
        {
            cout << setw( w1 ) << tbcosts.max_com;
        }
        if ( do_totaltbc )
        {
            cout << setw( w1 ) << tbcosts.acc_com;
        }

        for ( size_t i = 0; i < metricdata.size(); i++ )
        {
            int prec = 0;
            if ( metricdata[ i ].isfloat() )
            {
                prec = 2;
            }

            cout << setw( w1 ) << setprecision( prec ) << fixed << metricdata[ i ].com
                 << setw( w2 ) << setprecision( 2 ) << fixed << percent( metricdata[ i ].total, metricdata[ i ].com );
        }
        cout << left  << " (summary) COM"
             << endl;

        if ( do_blacklist )
        {
            cout << right
                 << "   " << "    BL";
            if ( do_maxtbc )
            {
                cout << setw( w1 ) << tbcosts.max_bl;
            }
            if ( do_totaltbc )
            {
                cout << setw( w1 ) << tbcosts.acc_bl;
            }

            for ( size_t i = 0; i < metricdata.size(); i++ )
            {
                int prec = 0;
                if ( metricdata[ i ].isfloat() )
                {
                    prec = 2;
                }

                cout << setw( w1 ) << setprecision( prec ) << fixed << metricdata[ i ].bl
                     << setw( w2 ) << setprecision( 2 ) << fixed << percent( metricdata[ i ].total, metricdata[ i ].bl );
            }

            cout << left  << " (summary) BL"
                 << endl;
            cout << right
                 << "   " << "   ANY";

            if ( do_maxtbc )
            {
                cout << setw( w1 ) << tbcosts.max_wbl;
            }
            if ( do_totaltbc )
            {
                cout << setw( w1 ) << tbcosts.acc_all - tbcosts.acc_bl;
            }

            for ( size_t i = 0; i < metricdata.size(); i++ )
            {
                int prec = 0;
                if ( metricdata[ i ].isfloat() )
                {
                    prec = 2;
                }

                cout << setw( w1 ) << setprecision( prec ) << fixed << metricdata[ i ].total - metricdata[ i ].bl
                     << setw( w2 ) << setprecision( 2 ) << fixed << percent( metricdata[ i ].total, ( metricdata[ i ].total - metricdata[ i ].bl ) );
            }

            cout << left  << " (summary) ALL-BL"
                 << endl;


            cout << right
                 << "   " << "   MPI";
            if ( do_maxtbc )
            {
                cout << setw( w1 ) << tbcosts.max_mpi_bl;
            }
            if ( do_totaltbc )
            {
                cout << setw( w1 ) << tbcosts.acc_mpi_bl;
            }

            for ( size_t i = 0; i < metricdata.size(); i++ )
            {
                int prec = 0;
                if ( metricdata[ i ].isfloat() )
                {
                    prec = 2;
                }

                cout << setw( w1 ) << setprecision( prec ) << fixed << metricdata[ i ].mpi_bl
                     << setw( w2 ) << setprecision( 2 ) << fixed << percent( metricdata[ i ].total, metricdata[ i ].mpi_bl );
            }
            cout << left  << " (summary) MPI-BL"
                 << endl;

            cout << right
                 << "   " << "   USR";
            if ( do_maxtbc )
            {
                cout << setw( w1 ) << tbcosts.max_usr_bl;
            }
            if ( do_totaltbc )
            {
                cout << setw( w1 ) << tbcosts.acc_usr_bl;
            }

            for ( size_t i = 0; i < metricdata.size(); i++ )
            {
                int prec = 0;
                if ( metricdata[ i ].isfloat() )
                {
                    prec = 2;
                }

                cout << setw( w1 ) << setprecision( prec ) << fixed << metricdata[ i ].usr_bl
                     << setw( w2 ) << setprecision( 2 ) << fixed << percent( metricdata[ i ].total, metricdata[ i ].usr_bl );
            }

            cout << left  << " (summary) USR-BL"
                 << endl;

            cout << right
                 << "   " << "   COM";

            if ( do_maxtbc )
            {
                cout << setw( w1 ) << tbcosts.max_com_bl;
            }
            if ( do_totaltbc )
            {
                cout << setw( w1 ) << tbcosts.acc_com_bl;
            }

            for ( size_t i = 0; i < metricdata.size(); i++ )
            {
                int prec = 0;
                if ( metricdata[ i ].isfloat() )
                {
                    prec = 2;
                }

                cout << setw( w1 ) << setprecision( prec ) << fixed << metricdata[ i ].com_bl
                     << setw( w2 ) << setprecision( 2 ) << fixed << percent( metricdata[ i ].total, metricdata[ i ].com_bl );
            }
            cout << left  << " (summary) COM-BL"
                 << endl;
        }

/* END: Print results */
    }
    catch ( const RuntimeError& error )
    {
        cerr << error.what() << endl;
        if ( input != NULL )
        {
            delete input;
        }
        exit( EXIT_FAILURE );
    }
    if ( input != NULL )
    {
        delete input;
    }
    exit( EXIT_SUCCESS );
}
