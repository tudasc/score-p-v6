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
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/



#ifndef __CUBE_STATISTICS_H
#define __CUBE_STATISTICS_H


#include <vector>
#include <limits>

#include "AggrCube.h"
#include "CubeMetric.h"
#include "CubeCnode.h"
#include "CubeServices.h"
#include "TopNPrinter.h"
#include "StatisticPrinter.h"
#include "PlainPrinter.h"
#include "PrettyTopNPrinter.h"
#include "CSVTopNPrinter.h"
#include "PrettyStatisticPrinter.h"
#include "CSVStatisticPrinter.h"
#include "PrettyPlainPrinter.h"
#include "CSVPlainPrinter.h"

/*-------------------------------------------------------------------------*/
/**
 * @class   CubeStatistics
 * @brief   Main class providing the functionality for cube3_stat
 *
 * The CubeStatistics class provides the main functinality for the
 * cube3_stat tool. It parses the given command line parameters and
 * can than be used to print the statistical information accordingly.
 */
/*-------------------------------------------------------------------------*/

class CubeStatistics
{
public:
    // / @name Constructor & destructor
    // / @{
    CubeStatistics( int   argc,
                    char* argv[] );
    ~CubeStatistics();
    // / @}
    // / @name Printing the selected data
    // / @{
    void
    Print() const;

    // / @}
private:

    CubeStatistics( const CubeStatistics& )
    {
    };                                           //prevent copy


    // /cube::Metric names chosen by the user to be printed
    std::vector<std::string> metricNames;
    // /cube::Cnode names chosen by the user to be printed
    std::vector<std::string> cnodeNames;
    // /Cube object used to read the selected cube file
    cube::AggrCube* cubeObject;
    // /Printer object used for output with statistics
    StatisticPrinter* myStatPrinter;
    // /Printer object used for output without statistics
    PlainPrinter* myPlainPrinter;
    // /Printer object used for topN output
    TopNPrinter* myTopNPrinter;
    // /Flag indicating whether to print statistics
    bool printStatistics;
    // /Number of regions for topN profile
    int top;
    // / @name Internal parsing and printing routines
    // / @{
    static void
    split( std::string const&        str,
           std::vector<std::string>& vec,
           char                      seperator = ',' );
    void
    PrintWithStatistics() const;
    void
    PrintWithoutStatistics() const;
    void
    PrintUsage() const;

    // / @}
};

/**
 * Helper method for command line parsing.
 * This method splits the std::string @p str at all occurences of the given
 * character @p seperator and saves all resulting parts into the passed
 * std::vector @p vec.
 *
 * @param str The std::string to be split
 * @param vec Vector of strings in which the resulting parts are stored
 * @param seperator The character at which str is to be split. Default: ','
 */
void
CubeStatistics::split( std::string const& str, std::vector<std::string>& vec,
                       char seperator )
{
    // offset is the current reading position
    std::string::size_type offset = 0;
    // commaPos is the position of the next found comma
    std::string::size_type commaPos = 0;
    while ( offset != std::string::npos && offset < str.length() )
    {
        commaPos = str.find( seperator, offset );
        if ( commaPos != std::string::npos )
        {
            vec.push_back( str.substr( offset, commaPos - offset ) );
            offset = commaPos + 1;
        }
        else
        {
            vec.push_back( str.substr( offset ) );
            offset = commaPos;
        }
    }
}

/**
 * Creates a new CubeStatistics instance from the given command line options.
 * Available options:
 *
 *    -p: Pretty print. This will switch all the output to nice human readable
 *        tables. If this is not provided the output is just a comma seperated
 *        value file.
 *    -m: Metrics. This option has to be followed by a (comma seperated) list
 *        of (unique) names of metrics. If this option is not provided, "time"
 *        is used as the default. If "time" can't be found, the metric
 *        with metric id of zero (with respect to the cube file) is chosen.
 *
 * Either call tree profile (-r [-%]) or flat profiles (-t) can be
 * generated and printed
 *
 *    -r: Regions for which 1-level call tree profiles are requested.
 *        This option has to be followed by a (comma seperated) list
 *        of region names. If this option is not provided, roots are used as
 *        the default
 *    -%: Print statistics. This is used to print statistical information for
 *        the given metrics. The statistics describe the distribution of the
 *        metrics onto the different threads.
 *
 *    -t: Number of regions for which a topN flat profile is requested.
 *        Values "inf", "unlimited" or "infinite" set it to MAX_INT
 *
 * @param argc Argument count (just pass the argument of main)
 * @param argv Array of command line arguments (just pass the argument of main)
 */
CubeStatistics::CubeStatistics( int   argc,
                                char* argv[] )
    : cubeObject( 0 ), myStatPrinter( 0 ), myPlainPrinter( 0 ), myTopNPrinter( 0 ),
    printStatistics( false ), top( 0 )
{
    // Parse the command line arguments
    int  c      = -1;
    bool pretty = false;
    while ( ( c = getopt( argc, argv, "h?m:pr:t:%" ) ) != -1 )
    {
        switch ( c )
        {
            case 'h':
            case '?':
                PrintUsage();
                break;
            case 'p':
                pretty = true;
                break;
            case '%':
                if ( top )
                {
                    std::cerr << "ERROR: Options -% and -t cannot be used together."
                              << std::endl;
                    exit( EXIT_FAILURE );
                }
                printStatistics = true;
                break;
            case 'm':
                split( optarg, metricNames );
                break;
            case 'r':
                if ( top )
                {
                    std::cerr << "ERROR: Options -r and -t cannot be used together."
                              << std::endl;
                    exit( EXIT_FAILURE );
                }
                split( optarg, cnodeNames );
                break;
            case 't':
                if ( !cnodeNames.empty() )
                {
                    std::cerr << "ERROR: Options -r and -t cannot be used together."
                              << std::endl;
                    exit( EXIT_FAILURE );
                }
                else if ( printStatistics )
                {
                    std::cerr << "ERROR: Options -% and -t cannot be used together."
                              << std::endl;
                    exit( EXIT_FAILURE );
                }
                std::string _optarg( optarg );
                if ( _optarg.compare( "unlimited" ) == 0 ||
                     _optarg.compare( "inf" ) == 0 ||
                     _optarg.compare( "infinite" ) == 0
                     )
                {
                    top = std::numeric_limits<int>::max();
                }
                else
                {
                    top = atoi( optarg );
                }
                break;
        }
    }
    if ( ( argc - optind ) != 1 )
    {
        PrintUsage();
    }
    else if ( ( argc - optind ) == 1 )
    {
        char* filename = argv[ optind ];
        cubeObject = new cube::AggrCube();
        try
        {
            cubeObject->openCubeReport( filename );
        }
        catch ( const cube::RuntimeError& e )
        {
            std::cerr << e.what() << std::endl;
            delete cubeObject;
            exit( EXIT_FAILURE );
        }

        // If topN flat profile requested, get default metrics
        // (visits, excl time, incl time)
    }

    if ( top )
    {
        // Insert metric "time" twice (for incl + excl)
        if ( cube::Metric* m = cubestat::findMetric( cubeObject, "time" ) )
        {
            metricNames.insert( metricNames.begin(), 2, m->get_uniq_name() );
        }
        else if ( cube::Metric* m = cubestat::findMetric( cubeObject, "Time", false ) )
        {
            metricNames.insert( metricNames.begin(), 2, m->get_uniq_name() );
        }
        else
        {
            std::cerr << "ERROR: Cannot find metric 'Time'." << std::endl;
            exit( EXIT_FAILURE );
        }

        // Insert metric "visits"
        if ( cube::Metric* m = cubestat::findMetric( cubeObject, "visits" ) )
        {
            metricNames.insert( metricNames.begin(), m->get_uniq_name() );
        }
        else if ( cube::Metric* m = cubestat::findMetric( cubeObject, "Visits", false ) )
        {
            metricNames.insert( metricNames.begin(), m->get_uniq_name() );
        }
        else
        {
            std::cerr << "ERROR: Cannot find metric 'Visits'." << std::endl;
            exit( EXIT_FAILURE );
        }
    }

    // If no metrics are provided (for non flat profiles) use the default
    // ("time" or the metric with an id of zero)
    if ( metricNames.empty() && top == 0 )
    {
        std::vector<cube::Metric*> const&          metVec         = cubeObject->get_metv();
        std::vector<cube::Metric*>::const_iterator zeroMetricIDIt = metVec.begin();
        bool                                       timeFound      = false;
        for ( std::vector<cube::Metric*>::const_iterator it = metVec.begin();
              it != metVec.end(); ++it )
        {
            if ( ( *it )->get_uniq_name() == "time" )
            {
                timeFound = true;
            }
            if ( ( *it )->get_id() == 0 )
            {
                zeroMetricIDIt = it;
            }
        }
        if ( timeFound )
        {
            metricNames.push_back( "time" );
        }
        else
        {
            metricNames.push_back( ( *zeroMetricIDIt )->get_uniq_name() );
        }
    }

    if ( top )
    {
        // FLAT PROFILE (TOP top)
        // Create the appropiate Printer objects
        if ( pretty )
        {
            myTopNPrinter =
                new PrettyTopNPrinter( cubeObject, metricNames, top );
        }
        else
        {
            myTopNPrinter =
                new CSVTopNPrinter( cubeObject, metricNames );
        }
    }
    else
    {
        // 1-LEVEL CALLTREE PROFILE
        // If no region names are provided use the default ("main" or the
        // region name which belongs to the cnode with an id of zero)
        if ( cnodeNames.empty() )
        {
            std::vector<cube::Cnode*> const&          cnodeVec      = cubeObject->get_cnodev();
            std::vector<cube::Cnode*>::const_iterator zeroCnodeIDIt = cnodeVec.begin();
            bool                                      mainFound     = false;
            for ( std::vector<cube::Cnode*>::const_iterator it = cnodeVec.begin();
                  it != cnodeVec.end(); ++it )
            {
                if ( ( *it )->get_parent() == 0 ) // root
                {
                    zeroCnodeIDIt = it;
                    cnodeNames.push_back( ( *zeroCnodeIDIt )->get_callee()->get_name() );
                }
            }
        }

        // Create the appropiate Printer objects
        if ( pretty )
        {
            if ( printStatistics )
            {
                myStatPrinter = new PrettyStatisticsPrinter( cubeObject,
                                                             metricNames, cnodeNames );
            }
            else
            {
                myPlainPrinter = new PrettyPlainPrinter( cubeObject,
                                                         metricNames, cnodeNames );
            }
        }
        else
        {
            if ( printStatistics )
            {
                myStatPrinter = new CSVStatisticsPrinter( cubeObject,
                                                          metricNames, cnodeNames );
            }
            else
            {
                myPlainPrinter = new CSVPlainPrinter( cubeObject,
                                                      metricNames, cnodeNames );
            }
        }
    }
}

/**
 * Prints the selected data according to the command line arguments used for
 * initialization of the CubeStatistics object.
 */
void
CubeStatistics::Print() const
{
    if ( printStatistics )
    {
        PrintWithStatistics();
    }
    else
    {
        PrintWithoutStatistics();
    }
}

/**
 * Prints the selected data with statistic information describing the
 * distribution of the selected metrics upon the different threads.
 */
void
CubeStatistics::PrintWithStatistics() const
{
    typedef std::vector<cube::Metric*>::const_iterator MetricIT;
    typedef std::vector<cube::Cnode*>::const_iterator  CnodeIT;

    myStatPrinter->PrintLegend();
    std::vector<cube::Metric*> const& requestedMetricVec =
        myStatPrinter->GetRequestedMetrics();
    std::vector<cube::Cnode*> const& requestedCnodeVec =
        myStatPrinter->GetRequestedCnodes();
    for ( MetricIT requestedMetricIT = requestedMetricVec.begin();
          requestedMetricIT != requestedMetricVec.end(); ++requestedMetricIT )
    {
        for ( CnodeIT requestedCnodeIT = requestedCnodeVec.begin();
              requestedCnodeIT != requestedCnodeVec.end(); ++requestedCnodeIT )
        {
            myStatPrinter->GatherAndPrint( *requestedMetricIT, *requestedCnodeIT,
                                           cubeObject );
        }
    }
}

/**
 * Prints the selected data without statistic information,
 * thus only calculating the sum for the selected metrics over all threads.
 */
void
CubeStatistics::PrintWithoutStatistics() const
{
    if ( top )
    {
        myTopNPrinter->PrintLegend();
        myTopNPrinter->Print( top );
    }
    else
    {
        typedef std::vector<cube::Cnode*>::const_iterator CnodeIT;

        myPlainPrinter->PrintLegend();
        std::vector<cube::Cnode*> const& requestedCnodeVec =
            myPlainPrinter->GetRequestedCnodes();
        for ( CnodeIT requestedCnodeIT = requestedCnodeVec.begin();
              requestedCnodeIT != requestedCnodeVec.end(); ++requestedCnodeIT )
        {
            myPlainPrinter->GatherAndPrint( *requestedCnodeIT );
            std::cout << std::endl;
        }
    }
}




CubeStatistics::~CubeStatistics()
{
    delete cubeObject;
    delete myStatPrinter;
    delete myPlainPrinter;
    delete myTopNPrinter;
}





void
CubeStatistics::PrintUsage() const
{
    std::cerr << "Usage: cube_stat [-h] [-p] [-m <metric>[,<metric>...]]" << std::endl;
    std::cerr << "                  [-%] [-r <routine>[,<routine>...]] <cubefile>" << std::endl;
    std::cerr << "                  OR" << std::endl;
    std::cerr << "                  [-t <topN>] <cubefile>" << std::endl;
    std::cerr << "  -h     Display this help message" << std::endl;
    std::cerr << "  -p     Pretty-print statistics (instead of CSV output)" << std::endl;
    std::cerr << "  -%     Provide statistics about process/thread metric values" << std::endl;
    std::cerr << "  -m     List of metrics (default: time)" << std::endl;
    std::cerr << "  -r     List of routines (default: main)" << std::endl;
    std::cerr << "  -t     Number for topN regions flat profile." << std::endl;
    std::cerr << "         Values \"inf\", \"unlimited\" and \"infinite\" are supported" << std::endl;
    std::cerr << "         and lead to display of all regions." << std::endl;
    exit( EXIT_SUCCESS );
}


#endif
