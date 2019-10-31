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



#ifndef __CUBE_STAT_PRETTY_STATISTIC_PRINTER_H
#define __CUBE_STAT_PRETTY_STATISTIC_PRINTER_H


#include <vector>

#include "AggrCube.h"
#include "CubeMetric.h"
#include "CubeCnode.h"

#include "StatisticPrinter.h"




/*-------------------------------------------------------------------------*/
/**
 * @class   PrettyStatisticsPrinter
 * @brief   Class for printing pretty human readable tables with statistics
 */
/*-------------------------------------------------------------------------*/
class PrettyStatisticsPrinter : public StatisticPrinter
{
public:
    // / @name Constructor & destructor
    // / @{
    PrettyStatisticsPrinter( cube::AggrCube*                 cubeObj,
                             std::vector<std::string> const& metNames,
                             std::vector<std::string> const& cnodeNames );
    virtual
    ~PrettyStatisticsPrinter()
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

    // / Defines the widthes used for the columns of the statistics
    // / (e.g. the Sum, Min, Max,... columns) - compile time constant
    static int const widthes[];
    // /Widthes used for the cnode and metric name columns
    int maxCnodeNameLength;
    int maxMetricNameLength;
};

int const PrettyStatisticsPrinter::widthes[] = { 15, 13, 14, 13, 15, 13, 15, 13 };

/**
 * Creates a new PrettyStatisticsPrinter instance from the given CUBE object
 * and the names of the requested metrics and cnodes.
 *
 * @param cubeObj The CUBE object used to parse the CUBE file to be analyzed.
 * @param metNames A std::vector containing all metric names for which data is to
 * be gathered and printed.
 * @param cnodeNames A std::vector containing all region names for which data is to
 * be gathered and printed.
 */
PrettyStatisticsPrinter::PrettyStatisticsPrinter( cube::AggrCube*                 cubeObj,
                                                  std::vector<std::string> const& metNames,
                                                  std::vector<std::string> const& cnodeNames )
    : StatisticPrinter( cubeObj, metNames, cnodeNames ),
    maxCnodeNameLength( strlen( "Routine" ) ),
    maxMetricNameLength( 0 )
{
    // Calculate the width of the cnode name column
    std::vector<cube::Cnode*> const& _requestedCnodeVec = GetRequestedCnodes();
    for ( std::vector<cube::Cnode*>::const_iterator it = _requestedCnodeVec.begin();
          it != _requestedCnodeVec.end(); ++it )
    {
        maxCnodeNameLength = std::max<size_t>( maxCnodeNameLength,
                                               ( *it )->get_callee()->get_name().length() );
        for ( unsigned int i = 0; i < ( *it )->num_children(); ++i )
        {
            maxCnodeNameLength = std::max<size_t>( maxCnodeNameLength,
                                                   ( *it )->get_child( i )->get_callee()->get_name().length() + 2 );
        }
    }
    ++maxCnodeNameLength;

    // Calculate the width of the metric name column
    maxMetricNameLength = metNames[ 0 ].length();
    for ( std::vector<std::string>::const_iterator it = metNames.begin();
          it != metNames.end(); ++it )
    {
        maxMetricNameLength = std::max<size_t>( maxMetricNameLength, it->length() );
    }
    ++maxMetricNameLength;
}

/**
 * Prints the legend for the statistics using the widthes compile time constant
 * and the calculated widthes for the name columns
 */
void
PrettyStatisticsPrinter::PrintLegend() const
{
    std::cout << std::setw( maxMetricNameLength ) << std::left << "cube::Metric"
              << std::setw( maxCnodeNameLength + 2 ) << std::left << "Routine"
              << std::setw( 7 ) << std::right << "Count";
    for ( size_t i = 0; i < sizeof( captions ) / sizeof( char const* ); ++i )
    {
        std::cout << std::setw( widthes[ i ] ) << std::right << captions[ i ];
    }
    std::cout << std::endl;
}

/**
 * Virtual method overwrite of the abstract method used by
 * StatisticPrinter::GatherAndPrint. This method prints the given statistic
 * @p stat formatted in a nice way.
 *
 * @param currCnode Determines the current cnode. This is only used to obtain
 * the CUBE name of the region belonging to the cnode if no @p name is provided.
 * @param met The metric to which the statistic belongs. Only used to obtain
 * the metric name.
 * @param stat The statistic to be printed.
 * @param indented Determines whether the statistic is to be indented. This is
 * used for regions being called by another region, making it obvious that
 * it is a child of the first unindented region printed above.
 * @param name The name to be printed. Default is empty. If @p name is empty,
 * the CUBE name of the region is used as a default.
 */
void
PrettyStatisticsPrinter::PrintStatistic( cube::Cnode* currCnode, cube::Metric* met,
                                         P2Statistic const& stat, bool indented, std::string const& name ) const
{
    std::cout << std::setw( maxMetricNameLength ) << std::left << met->get_uniq_name();

    // Indented items have 2 spaces in front
    if ( indented )
    {
        std::cout << "  ";
        std::cout << std::setw( maxCnodeNameLength ) << std::left;
    }
    // Therefore unindented items have to be printed in a column which is
    // 2 characters larger
    else
    {
        std::cout << std::setw( maxCnodeNameLength + 2 ) << std::left;
    }

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
    std::cout << std::setw( 7 ) << std::right << stat.count();
    for ( size_t i = 0; i < sizeof( values ) / sizeof( double ( P2Statistic::* )() ); ++i )
    {
        std::cout << std::setw( widthes[ i ] ) << std::right << std::fixed;
        if ( stat.count() >= minCount[ i ] )
        {
            if ( integerValues[ i ] && ( met->get_dtype() == "INTEGER"
                                         ||
                                         met->get_dtype() == "UINT64"
                                         ||
                                         met->get_dtype() == "INT64" )
                 )
            {
                std::cout << std::noshowpoint << std::setprecision( 0 );
            }
            std::cout << ( stat.*values[ i ] )();
            std::cout << std::showpoint << std::setprecision( 6 );
        }
        else
        {
            std::cout << "";
        }
    }
    std::cout << std::endl;
}





#endif
