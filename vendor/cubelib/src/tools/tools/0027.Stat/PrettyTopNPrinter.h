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



#ifndef __CUBE_STAT_PRETTY_TOPN_PRINTER_H
#define __CUBE_STAT_PRETTY_TOPN_PRINTER_H


#include <vector>

#include "AggrCube.h"
#include "CubeMetric.h"
#include "CubeCnode.h"

#include "TopNPrinter.h"



/*-------------------------------------------------------------------------*/
/**
 * @class   PrettyTopNPrinter
 * @brief   Class for printing topN flat profile data as a comma seperated
 *          value file
 */
/*-------------------------------------------------------------------------*/
class PrettyTopNPrinter : public TopNPrinter
{
public:
    // / @name Constructor & destructor
    // / @{
    PrettyTopNPrinter( cube::AggrCube*                 cubeObj,
                       std::vector<std::string> const& metNames,
                       int                             n );
    virtual
    ~PrettyTopNPrinter()
    {
    }
    // / @}
    // / @name Print methods used by clients
    // / @{
    virtual void
    PrintLegend() const;
    virtual void
    Print( int n ) const;

    // / @}
private:
    cube::AggrCube*  cubeObject;
    size_t           maxRegionNameLength;
    std::vector<int> columnWidthes;
};




/**
 * Creates a new PrettyTopNPrinter instance from the given CUBE object and
 * the names of the requested metrics and cnodes.
 *
 * @param cubeObj The CUBE object used to parse the CUBE file to be analyzed.
 * @param metNames A std::vector containing all metric names for which data is
 * to be gathered and printed.
 * @param n Maximum number of top @p n functions to print
 */
PrettyTopNPrinter::PrettyTopNPrinter( cube::AggrCube*                 cubeObj,
                                      std::vector<std::string> const& metNames,
                                      int                             n )
    : TopNPrinter( cubeObj, metNames ), cubeObject( cubeObj ),
    maxRegionNameLength( strlen( "cube::Region" ) )
{
    // Calculate the width of the region name column
    std::vector<cube::Region*> const& regionsVec     = cubeObject->get_regv();
    int                               num_regions    = regionsVec.size();
    const int                         visitsMetricID = 0;

    for ( int r = 0; r < num_regions && r < n; ++r )
    {
        int rr = indexVec[ r ];
        if ( values[ visitsMetricID ][ rr ] == 0 )
        {
            // abort loop when functions got never called
            break;
        }
        maxRegionNameLength = std::max( maxRegionNameLength,
                                        regionsVec[ rr ]->get_name().length() );
    }
    ++maxRegionNameLength;

    // Calculate column widthes for the different metric columns
    for ( std::vector<std::string>::const_iterator it = metNames.begin();
          it != metNames.end(); ++it )
    {
        columnWidthes.push_back( std::max<size_t>( it->length() + 1, 14 ) );
    }
}



/**
 * Prints the legend for topN flat profile as a line of a comma seperated
 * value file
 */
void
PrettyTopNPrinter::PrintLegend() const
{
    std::vector<cube::Metric*> const& _requestedMetricVec = GetRequestedMetrics();
    int                               num_metrics         = _requestedMetricVec.size();
    const int                         inclTimeMetricID    = 2;

    std::cout << std::setw( maxRegionNameLength ) << std::left << "cube::Region";
    std::cout << std::setw( 14 ) << std::right << "NumberOfCalls";
    std::cout << std::setw( 14 ) << std::right << "ExclusiveTime";
    std::cout << std::setw( 14 ) << std::right << "InclusiveTime";

    for ( int m = inclTimeMetricID + 1; m < num_metrics; ++m )
    {
        std::cout << std::setw( columnWidthes[ m ] ) << std::right
                  << _requestedMetricVec[ m ]->get_uniq_name();
    }
    std::cout << std::endl;
    std::cout << std::fixed << std::showpoint << std::setprecision( 6 );
}




/**
 * Prints the values for the @p n top regions as a topN flat profile
 * as a line of a comma seperated value file
 *
 * @param n Number of regions to print
 */
void
PrettyTopNPrinter::Print( int n ) const
{
    std::vector<cube::Metric*> const& _requestedMetricVec = GetRequestedMetrics();
    std::vector<cube::Region*> const& regionsVec          = cubeObject->get_regv();
    int                               num_metrics         = values.size();
    int                               num_regions         = regionsVec.size();
    const int                         visitsMetricID      = 0;

    for ( int r = 0; r < num_regions && r < n; ++r )
    {
        int rr = indexVec[ r ];
        if ( values[ visitsMetricID ][ rr ] == 0 )
        {
            // abort loop when functions got never called
            break;
        }
        std::cout << std::setw( maxRegionNameLength ) << std::left << regionsVec[ rr ]->get_name();
        for ( int m = 0; m < num_metrics; ++m )
        {
            std::vector<double> const& curr_met_values = values[ m ];
            std::cout << std::setw( columnWidthes[ m ] ) << std::right;
            if ( _requestedMetricVec[ m ]->get_dtype() == "INTEGER"
                 ||
                 _requestedMetricVec[ m ]->get_dtype() == "UINT64"
                 ||
                 _requestedMetricVec[ m ]->get_dtype() == "INT64"  )
            {
                std::cout << std::noshowpoint << std::setprecision( 0 );
            }
            else
            {
                std::cout << std::fixed;
            }
            std::cout << curr_met_values[ rr ];
            std::cout << std::showpoint << std::setprecision( 6 );
        }
        std::cout << std::endl;
    }
}


#endif
