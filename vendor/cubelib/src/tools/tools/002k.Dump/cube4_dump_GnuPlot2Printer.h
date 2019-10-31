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




#ifndef CUBE4_DUMP_GNUPLOT2PRINTER_H
#define CUBE4_DUMP_GNUPLOT2PRINTER_H


#include "cube4_dump_Printer.h"


class GnuPlot2Printer : public Printer
{
public:
    GnuPlot2Printer( std::ostream& _out,
                     cube::Cube*   _cube ) : Printer( _out, _cube )
    {
    }


    virtual
    void
    dump_data( std::vector < cube::Metric* >& _metrics,
               std::vector < cube::Cnode* >&  _cnodes,
               std::vector < cube::Thread* >& _threads,
               cube::CalculationFlavour       _mf,
               cube::CalculationFlavour       _cf,
               bool                           stored,
               ThreadSelection                selected_threads ) const;
};


#endif // CUBE4_DUMP_GNUPLOT2PRINTER_H
