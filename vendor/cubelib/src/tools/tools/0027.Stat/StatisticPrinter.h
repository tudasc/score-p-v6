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



#ifndef __CUBE_STAT_STATISTIC_PRINTER_H
#define __CUBE_STAT_STATISTIC_PRINTER_H


#include <vector>

#include "AggrCube.h"
#include "CubeMetric.h"
#include "CubeCnode.h"

#include "Printer.h"



/*-------------------------------------------------------------------------*/
/**
 * @class   StatisticPrinter
 * @brief   Abstract base class for printers that print statistical information
 *          gathered about all threads.
 *
 * This is the abstract base class of all Printer classes used for output with
 * statistical information. It already implements the GatherAndPrint method
 * which is used by client classes. The subclasses only have to implement the
 * PrintLegend and PrintStatistic methods.
 */
/*-------------------------------------------------------------------------*/
class StatisticPrinter : public Printer
{
public:
    // / @name Constructor & destructor
    // / @{
    StatisticPrinter( cube::AggrCube*                 cubeObject,
                      std::vector<std::string> const& metNames,
                      std::vector<std::string> const& cnodeNames );
    virtual
    ~StatisticPrinter()
    {
    }
    // / @}
    // / @name Print methods used by clients
    // / @{
    virtual void
    GatherAndPrint( cube::Metric*   met,
                    cube::Cnode*    cnode,
                    cube::AggrCube* cubeObject ) const;
    virtual void
    PrintLegend() const = 0;

    // / @}
    // / The captions used for printing the legend
    static char const* const captions[];
private:
    // / PrintStatistic method to be overwritten by subclasses to modify
    // / the way the statistics are printed
    virtual void
    PrintStatistic( cube::Cnode*       currCnode,
                    cube::Metric*      met,
                    P2Statistic const& stat,
                    bool               indented = false,
                    std::string const& name = "" ) const = 0;
};






char const* const StatisticPrinter::captions[] = { "Sum",     "Mean",        "Variance",
                                                   "Minimum", "Quartile 25", "Median",         "Quartile 75", "Maximum" };

/**
 * Creates a new StatisticPrinter instance from the given CUBE object and the
 * names of the requested metrics and cnodes.
 *
 * @param cubeObject The CUBE object used to parse the CUBE file to be analyzed.
 * @param metNames A std::vector containing all metric names for which data is to be
 * gathered and printed.
 * @param cnodeNames A std::vector containing all region names for which data is to
 * be gathered and printed.
 */
StatisticPrinter::StatisticPrinter( cube::AggrCube*                 cubeObject,
                                    std::vector<std::string> const& metNames,
                                    std::vector<std::string> const& cnodeNames )
    : Printer( cubeObject, metNames, cnodeNames )
{
}




/**
 * Method for gathering and printing statistical information for the
 * distribution of metrics upon all threads. This method creates and prints a
 * statistic about the distribution of the given metric met on all threads
 * for the given cube::Cnode cnode and all cnodes called by cnode
 *
 * @param met The metric for which the distribution among all threads is
 * calculated
 * @param cnode The statistics is gathered for this cnode and all it's child
 * cnodes
 * @param cubeObject The CUBE object used to extract the severity information
 */
void
StatisticPrinter::GatherAndPrint( cube::Metric* met, cube::Cnode* cnode,
                                  cube::AggrCube* cubeObject ) const
{
    typedef cube::Thread SysResType;
    std::vector<SysResType*> const& processVec = cubeObject->get_thrdv();
    if ( cnode->num_children() == 0 )
    {
        // Gather and print the statistic for the given cnode inclusively
        // (as there are no children, inclusive value is equal with its exlcusive value)
        {
            P2Statistic stat;
            for ( std::vector<SysResType*>::const_iterator it = processVec.begin();
                  it != processVec.end(); ++it )
            {
                stat.add( cubeObject->get_vcsev( INCL, INCL, EXCL,  met, cnode, *it ) );
            }
            PrintStatistic( cnode, met, stat, false,
                            "LEAF(" + cnode->get_callee()->get_name() + ")" );
        }
    }
    else
    {
        // Gather and print the statistic for the given cnode inclusively
        // (that is with the severity caused by all its children)

        {
            P2Statistic stat;
            for ( std::vector<SysResType*>::const_iterator it = processVec.begin();
                  it != processVec.end(); ++it )
            {
                stat.add( cubeObject->get_vcsev( INCL, INCL, EXCL,  met, cnode, *it ) );
            }
            PrintStatistic( cnode, met, stat, false,
                            "INCL(" + cnode->get_callee()->get_name() + ")" );
        }
        // Gather and print the statistic for the given cnode exclusively
        // (that is without the severity caused by its children)
        {
            P2Statistic stat;
            for ( std::vector<SysResType*>::const_iterator it = processVec.begin();
                  it != processVec.end(); ++it )
            {
                stat.add( cubeObject->get_vcsev( INCL, EXCL, EXCL,  met, cnode, *it ) );
            }
            PrintStatistic( cnode, met, stat, true,
                            "EXCL(" + cnode->get_callee()->get_name() + ")" );
        }
        // Gather and print the statistics for all childs of the given cnode
        for ( unsigned int i = 0; i < cnode->num_children(); ++i )
        {
            P2Statistic  stat;
            cube::Cnode* currCnode = cnode->get_child( i );
            for ( std::vector<SysResType*>::const_iterator it = processVec.begin();
                  it != processVec.end(); ++it )
            {
                stat.add( cubeObject->get_vcsev( INCL, INCL, EXCL,  met, currCnode,
                                                 *it ) );
            }
            if ( currCnode->num_children() != 0 )
            {
                PrintStatistic( currCnode, met, stat, true,
                                "INCL(" + currCnode->get_callee()->get_name() + ")" );
            }
            else
            {
                PrintStatistic( currCnode, met, stat, true,
                                "LEAF(" + currCnode->get_callee()->get_name() + ")" );
            }
        }
        std::cout << std::endl;
    }
}





#endif
