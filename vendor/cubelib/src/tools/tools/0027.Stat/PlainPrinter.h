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



#ifndef __CUBE_STAT_PLAIN_PRINTER_H
#define __CUBE_STAT_PLAIN_PRINTER_H


#include <vector>

#include "AggrCube.h"
#include "CubeMetric.h"
#include "CubeCnode.h"

#include "Printer.h"



/*-------------------------------------------------------------------------*/
/**
 * @class   PlainPrinter
 * @brief   Abstract base class for printers that print severity data, but do
 * not print statistical information gathered about all threads.
 *
 * This is the abstract base class of all Printer classes used for output
 * without statistical information.
 */
/*-------------------------------------------------------------------------*/
class PlainPrinter : public Printer
{
public:
    // / @name Constructor & destructor
    // / @{
    PlainPrinter( cube::AggrCube*                 cubeObject,
                  std::vector<std::string> const& metNames,
                  std::vector<std::string> const& cnodeNames );
    virtual
    ~PlainPrinter()
    {
    }
    // / @}
    // / @name Print methods used by clients
    // / @{
    virtual void
    PrintLegend() const = 0;
    virtual void
    GatherAndPrint( cube::Cnode* cnode ) const = 0;

    // / @}
};




/**
 * Creates a new PlainPrinter instance from the given CUBE object and the names
 * of the requested metrics and cnodes.
 *
 * @param cubeObject The CUBE object used to parse the CUBE file to be analyzed.
 * @param metNames A std::vector containing all metric names for which data is to be
 * gathered and printed.
 * @param cnodeNames A std::vector containing all region names for which data is to
 * be gathered and printed.
 */
PlainPrinter::PlainPrinter( cube::AggrCube*                 cubeObject,
                            std::vector<std::string> const& metNames,
                            std::vector<std::string> const& cnodeNames )
    : Printer( cubeObject, metNames, cnodeNames )
{
}



#endif
