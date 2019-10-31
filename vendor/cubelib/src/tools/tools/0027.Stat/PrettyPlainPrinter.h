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



#ifndef __CUBE_STAT_PRETTY_PLAIN_PRINTER_H
#define __CUBE_STAT_PRETTY_PLAIN_PRINTER_H


#include <vector>

#include "AggrCube.h"
#include "CubeMetric.h"
#include "CubeCnode.h"

#include "PlainPrinter.h"



/*-------------------------------------------------------------------------*/
/**
 * @class   PrettyPlainPrinter
 * @brief   Class for printing pretty human readable tables
 */
/*-------------------------------------------------------------------------*/
class PrettyPlainPrinter : public PlainPrinter
{
public:
    // / @name Constructor & destructor
    // / @{
    PrettyPlainPrinter( cube::AggrCube*                 cubeObj,
                        std::vector<std::string> const& metNames,
                        std::vector<std::string> const& cnodeNames );
    virtual
    ~PrettyPlainPrinter()
    {
    }
    // / @}
    // / @name Print methods used by clients
    // / @{
    virtual void
    PrintLegend() const;
    virtual void
    GatherAndPrint( cube::Cnode* cnode ) const;

    // / @}
private:
    cube::AggrCube*  cubeObject;
    size_t           maxCnodeNameLength;
    std::vector<int> columnWidthes;

    // / Private helper method for gathering and printing the data
    // / (without names)
    void
    PrintValues( cube::Cnode* cnode,
                 inclmode     cnodeMode = INCL ) const;
};

/**
 * Creates a new PrettyPlainPrinter instance from the given CUBE object and the
 * names of the requested metrics and cnodes.
 *
 * @param cubeObj The CUBE object used to parse the CUBE file to be analyzed.
 * @param metNames A std::vector containing all metric names for which data is to be
 * gathered and printed.
 * @param cnodeNames A std::vector containing all region names for which data is to
 * be gathered and printed.
 */
PrettyPlainPrinter::PrettyPlainPrinter( cube::AggrCube*                 cubeObj,
                                        std::vector<std::string> const& metNames,
                                        std::vector<std::string> const& cnodeNames )
    : PlainPrinter( cubeObj, metNames, cnodeNames ), cubeObject( cubeObj ),
    maxCnodeNameLength( strlen( "routine" ) )
{
    // Calculate the width of the cnode name column
    std::vector<cube::Cnode*> const& _requestedCnodeVec = GetRequestedCnodes();
    for ( std::vector<cube::Cnode*>::const_iterator it = _requestedCnodeVec.begin();
          it != _requestedCnodeVec.end(); ++it )
    {
        maxCnodeNameLength = std::max( maxCnodeNameLength,
                                       ( *it )->get_callee()->get_name().length() + strlen( "INCL()" ) );
        for ( unsigned int i = 0; i < ( *it )->num_children(); ++i )
        {
            maxCnodeNameLength = std::max( maxCnodeNameLength,
                                           ( *it )->get_child( i )->get_callee()->get_name().length() + 2 );
        }
    }
    ++maxCnodeNameLength;

    // Calculate column widthes for the different metric columns
    for ( std::vector<std::string>::const_iterator it = metNames.begin();
          it != metNames.end(); ++it )
    {
        columnWidthes.push_back( std::max<size_t>( it->length() + 1, 13 ) );
    }
}



/**
 * Prints the legend for the data using the column widthes and the width for
 * the cnode name column calculated in the constructor
 */
void
PrettyPlainPrinter::PrintLegend() const
{
    std::cout << std::setw( maxCnodeNameLength ) << std::left << "Routine";
    std::vector<cube::Metric*> const& _requestedMetricVec = GetRequestedMetrics();
    for ( size_t i = 0; i < _requestedMetricVec.size(); ++i )
    {
        std::cout << std::setw( columnWidthes[ i ] ) << std::right
                  << _requestedMetricVec[ i ]->get_uniq_name();
    }
    std::cout << std::endl;
    std::cout << std::fixed << std::showpoint << std::setprecision( 6 );
}



/**
 * Method for gathering and printing data about the severity of certain metrics
 * with respect to given cnodes and their children. This method gathers and
 * prints data about the requested metrics for the given cube::Cnode cnode and all
 * cnodes called by cnode
 *
 * @param cnode The data is gathered for this cnode and all it's child cnodes.
 */
void
PrettyPlainPrinter::GatherAndPrint( cube::Cnode* cnode ) const
{
    // First print data for the given cnode inclusively
    // and exclusively its children
    inclmode modes[] = { INCL, EXCL };
    for ( size_t i = 0; i < sizeof( modes ) / sizeof( inclmode ); ++i )
    {
        std::cout << std::setw( maxCnodeNameLength ) << std::left;
        if ( modes[ i ] == INCL )
        {
            std::cout << ( "INCL(" + cnode->get_callee()->get_name() + ")" );
        }
        else
        {
            std::cout << ( "  EXCL(" + cnode->get_callee()->get_name() + ")" );
        }
        PrintValues( cnode, modes[ i ] );
    }

    // Print data for all children of the given cnode
    for ( unsigned int i = 0; i < cnode->num_children(); ++i )
    {
        std::cout << std::setw( maxCnodeNameLength ) << std::left
                  << ( "  " + cnode->get_child( i )->get_callee()->get_name() );
        PrintValues( cnode->get_child( i ), INCL );
    }
}




/**
 * Private helper method for gathering and printing the data (without names)
 * for a given cnode
 *
 * @param cnode The data is gathered for this cnode.
 * @param cnodeMode Determines the inclusion mode. If it is INCL, the
 * severities of the child cnodes are added. If it is EXCL, they are not.
 */
void
PrettyPlainPrinter::PrintValues( cube::Cnode* cnode, inclmode cnodeMode ) const
{
    std::vector<cube::Metric*> const& _requestedMetricVec = GetRequestedMetrics();
    std::vector<cube::Thread*> const& threadVec           = cubeObject->get_thrdv();
    for ( size_t i = 0; i < _requestedMetricVec.size(); ++i )
    {
        double severity = 0.0;
        for ( std::vector<cube::Thread*>::const_iterator threadIT = threadVec.begin();
              threadIT != threadVec.end(); ++threadIT )
        {
            severity += cubeObject->get_vcsev( INCL, cnodeMode, EXCL,
                                               _requestedMetricVec[ i ], cnode, *threadIT );
        }
        std::cout << std::setw( columnWidthes[ i ] ) << std::right;
        if ( _requestedMetricVec[ i ]->get_dtype() == "INTEGER"
             ||
             _requestedMetricVec[ i ]->get_dtype() == "UINT64"
             ||
             _requestedMetricVec[ i ]->get_dtype() == "INT64"
             )
        {
            std::cout << std::noshowpoint << std::setprecision( 0 ) << severity;
        }
        else
        {
            std::cout << std::fixed << severity;
        }
        std::cout << std::showpoint << std::setprecision( 6 );
    }
    std::cout << std::endl;
}




#endif
