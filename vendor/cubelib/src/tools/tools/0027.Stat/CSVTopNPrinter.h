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



#ifndef __CUBE_STAT_CSV_TOPN_PRINTER_H
#define __CUBE_STAT_CSV_TOPN_PRINTER_H


#include <vector>

#include "AggrCube.h"
#include "CubeMetric.h"
#include "CubeCnode.h"

#include "TopNPrinter.h"



/*-------------------------------------------------------------------------*/
/**
 * @class   CSVTopNPrinter
 * @brief   Class for printing topN flat profile data as a comma seperated
 *          value file
 */
/*-------------------------------------------------------------------------*/
class CSVTopNPrinter : public TopNPrinter
{
public:
    // / @name Constructor & destructor
    // / @{
    CSVTopNPrinter( cube::AggrCube*                 cubeObj,
                    std::vector<std::string> const& metNames );
    virtual
    ~CSVTopNPrinter()
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
    cube::AggrCube* cubeObject;
};

/**
 * Creates a new CSVTopNPrinter instance from the given CUBE object and
 * the names of the requested metrics and cnodes.
 *
 * @param cubeObj The CUBE object used to parse the CUBE file to be analyzed.
 * @param metNames A std::vector containing all metric names for which data is
 * to be gathered and printed.
 */
CSVTopNPrinter::CSVTopNPrinter( cube::AggrCube*                 cubeObj,
                                std::vector<std::string> const& metNames )
    : TopNPrinter( cubeObj, metNames ), cubeObject( cubeObj )
{
}

/**
 * Prints the legend for topN flat profile as a line of a comma seperated
 * value file
 */
void
CSVTopNPrinter::PrintLegend() const
{
    std::vector<cube::Metric*> const& _requestedMetricVec = GetRequestedMetrics();
    int                               num_metrics         = _requestedMetricVec.size();
    const int                         inclTimeMetricID    = 2;

    std::cout << "cube::Region,Number of Calls,Exclusive Time,Inclusive Time";
    for ( int m = inclTimeMetricID + 1; m < num_metrics; ++m )
    {
        std::cout << ',' << _requestedMetricVec[ m ]->get_uniq_name();
    }
    std::cout << std::endl;
}

/**
 * Prints the values for the @p n top regions as a topN flat profile
 * as a line of a comma seperated value file
 *
 * @param n Number of regions to print
 */
void
CSVTopNPrinter::Print( int n ) const
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
        std::cout << "\"" << regionsVec[ rr ]->get_name() << "\"";
        for ( int m = 0; m < num_metrics; ++m )
        {
            std::vector<double> const& curr_met_values = values[ m ];
            std::cout << ',';
            if ( _requestedMetricVec[ m ]->get_dtype() == "INTEGER"
                 ||
                 _requestedMetricVec[ m ]->get_dtype() == "UINT64"
                 ||
                 _requestedMetricVec[ m ]->get_dtype() == "INT64"  )
            {
                std::cout << std::fixed << std::noshowpoint << std::setprecision( 0 );
            }
            std::cout << curr_met_values[ rr ];
            std::cout.setf( std::ios_base::fmtflags( 0 ), std::ios_base::floatfield );
            std::cout << std::showpoint << std::setprecision( 6 );
        }
        std::cout << std::endl;
    }
}


#endif
