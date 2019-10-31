/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2016                                                **
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



#ifndef __CUBE_STAT_TOPN_PRINTER_H
#define __CUBE_STAT_TOPN_PRINTER_H


#include <vector>
#include <algorithm>

#include "AggrCube.h"
#include "CubeMetric.h"
#include "CubeCnode.h"

#include "Printer.h"




/*-------------------------------------------------------------------------*/
/**
 * @class   TopNPrinter
 * @brief   Abstract base class for printers that print flat profiles.
 *
 * This is the abstract base class of all Printer classes used for printing
 * of topN flat profiles.
 */
/*-------------------------------------------------------------------------*/
class TopNPrinter : public Printer
{
public:
    // / @name Constructor & destructor
    // / @{
    TopNPrinter( cube::AggrCube*                 cubeObject,
                 std::vector<std::string> const& metNames );
    virtual
    ~TopNPrinter()
    {
    }
    // / @}
    // / @name Print methods used by clients
    // / @{
    virtual void
    PrintLegend() const = 0;
    virtual void
    Print( int n ) const = 0;

    // / @}

protected:
    // / Vector of requested metroc value vectors
    std::vector< std::vector<double> > values;
    // / Index std::vector represending sort order (per exclusive time)
    std::vector<int> indexVec;

private:
    static std::vector<std::string> const dummyEmptyCnodenames;
};




/**
 * Creates a new TopNPrinter instance from the given CUBE object and the names
 * of the requested metrics. Gathers requested metic value vectors and
 * determines sort order.
 *
 * @param cubeObject The CUBE object used to parse the CUBE file to be analyzed.
 * @param metNames A std::vector containing all metric names for which data is to
 * be gathered and printed.
 */
TopNPrinter::TopNPrinter( cube::AggrCube*                 cubeObject,
                          std::vector<std::string> const& metNames )
    : Printer( cubeObject, metNames, dummyEmptyCnodenames )
{
    // Gather values
    const int                         inclTimeMetricID    = 2;
    std::vector<cube::Metric*> const& _requestedMetricVec = GetRequestedMetrics();
    std::vector<cube::Region*> const& regionsVec          = cubeObject->get_regv();
    int                               num_metrics         = _requestedMetricVec.size();
    int                               num_regions         = regionsVec.size();
    values.resize( _requestedMetricVec.size() );

    for ( int m = 0; m < num_metrics; ++m )
    {
        std::vector<double>& curr_met_values = values[ m ];
        curr_met_values.resize( num_regions );
#ifdef _OPENMP
        #pragma omp parallel for
#endif
        for ( int r = 0; r < num_regions; ++r )
        {
            curr_met_values[ r ] = cubeObject->get_vrsev( INCL,
                                                          ( m == inclTimeMetricID ? INCL : EXCL ), INCL,
                                                          _requestedMetricVec[ m ], regionsVec[ r ],
                                                          0 /* = machine */ );
        }
    }

    // Create index std::vector, i.e. sorting order for exclusive time
    const int exclTimeMetricID = 1;
    indexVec.resize( num_regions );
    for ( int r = 0; r < num_regions; ++r )
    {
        indexVec[ r ] = r;
    }
    std::sort( indexVec.begin(), indexVec.end(), cubestat::indirectCmp( values[ exclTimeMetricID ] ) );
}



std::vector<std::string> const TopNPrinter::dummyEmptyCnodenames;



#endif
