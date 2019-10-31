/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2018                                                **
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



#ifndef __CUBE_STAT_CSV_STATISTIC_PRINTER_H
#define __CUBE_STAT_CSV_STATISTIC_PRINTER_H


#include <vector>

#include "AggrCube.h"
#include "CubeMetric.h"
#include "CubeCnode.h"

#include "StatisticPrinter.h"

/*-------------------------------------------------------------------------*/
/**
 * @class   CSVStatisticsPrinter
 * @brief   Class for printing comma seperated value files with statistics
 */
/*-------------------------------------------------------------------------*/
class CSVStatisticsPrinter : public StatisticPrinter
{
public:
    // / @name Constructor & destructor
    // / @{
    CSVStatisticsPrinter( cube::AggrCube*                 cubeObject,
                          std::vector<std::string> const& metNames,
                          std::vector<std::string> const& cnodeNames );
    virtual
    ~CSVStatisticsPrinter()
    {
    }
    // / @}
    // / @name Print methods used by clients
    // / @{
    virtual void
    PrintLegend() const;

    // / @}
private:
    // / Virtual method overwrite of the abstract method used by
    // / StatisticPrinter::GatherAndPrint
    virtual void
    PrintStatistic( cube::Cnode*       currCnode,
                    cube::Metric*      met,
                    P2Statistic const& stat,
                    bool               indented,
                    std::string const& name ) const;
};

/**
 * Creates a new CSVStatisticsPrinter instance from the given CUBE object and
 * the names of the requested metrics and cnodes.
 *
 * @param cubeObject The CUBE object used to parse the CUBE file to be analyzed.
 * @param metNames A std::vector containing all metric names for which data is to be
 * gathered and printed.
 * @param cnodeNames A std::vector containing all region names for which data is to
 * be gathered and printed.
 */
CSVStatisticsPrinter::CSVStatisticsPrinter( cube::AggrCube*                 cubeObject,
                                            std::vector<std::string> const& metNames,
                                            std::vector<std::string> const& cnodeNames )
    : StatisticPrinter( cubeObject, metNames, cnodeNames )
{
}

/**
 * Prints the legend for the statistics as a line of a comma seperated value
 * file
 */
void
CSVStatisticsPrinter::PrintLegend() const
{
    std::cout << "cube::Metric" << ',' << "Routine" << ',' << "Count";
    std::cout << ',' << captions[ 0 ];
    for ( size_t i = 1; i < sizeof( captions ) / sizeof( char const* ); ++i )
    {
        std::cout << ',' << captions[ i ];
    }
    std::cout << std::endl;
}



/**
 * Virtual method overwrite of the abstract method used by
 * StatisticPrinter::GatherAndPrint.  This method prints the given statistic
 * @p stat formatted as a part of a comma seperated value file.
 *
 * @param currCnode Determines the current cnode. This is only used to obtain
 * the CUBE name of the region belonging to the cnode if no @p name is provided.
 * @param met The metric to which the statistic belongs. Only used to obtain
 * the metric name.
 * @param stat The statistic to be printed.
 * @param name The name to be printed. Default is empty. If @p name is empty,
 * the CUBE name of the region is used as a default.
 */
void
CSVStatisticsPrinter::PrintStatistic( cube::Cnode* currCnode, cube::Metric* met,
                                      P2Statistic const& stat, bool, std::string const& name ) const
{
    std::cout << met->get_uniq_name() << ',';
    // If no name is given use the CUBE name as a default
    if ( name.length() == 0 )
    {
        std::cout << currCnode->get_callee()->get_name();
    }
    else
    {
        std::cout << name;
    }

    // values is an array of method pointers, allowing to access the statistic
    // information conveniently
    double( P2Statistic::* values[] )() const = {
        &P2Statistic::sum, &P2Statistic::mean, &P2Statistic::var,
        &P2Statistic::min, &P2Statistic::q25,  &P2Statistic::med,
        &P2Statistic::q75, &P2Statistic::max
    };
    // Array containing the minimal count a statistic object has to have in
    // order to provide a specific value
    // For example P2Statistic::q25 = values[4] requires a minimum count of 5
    // = minCount[4]
    int const minCount[] = { 0, 0, 2, 0, 5, 0, 5, 0 };
    // Array stating which statistic values are integers, if the metric is of
    // type integer (e.g. for hardware counters)
    bool const integerValues[] =
    { true, false, false, true, false, false, false, true };

    // Print the statistic
    std::cout << "," << stat.count();
    for ( size_t i = 0; i < sizeof( values ) / sizeof( double ( P2Statistic::* )() ); ++i )
    {
        if ( stat.count() >= minCount[ i ] )
        {
            if ( integerValues[ i ] && ( met->get_dtype() == "INTEGER"
                                         ||
                                         met->get_dtype() == "UINT64"
                                         ||
                                         met->get_dtype() == "INT64"  )

                 )
            {
                std::cout << std::fixed << std::noshowpoint << std::setprecision( 0 );
            }
            std::cout << "," << ( stat.*values[ i ] )();
            std::cout.setf( std::ios_base::fmtflags( 0 ), std::ios_base::floatfield );
            std::cout << std::showpoint << std::setprecision( 6 );
        }
        else
        {
            std::cout << ",";
        }
    }
    std::cout << std::endl;
}



#endif
