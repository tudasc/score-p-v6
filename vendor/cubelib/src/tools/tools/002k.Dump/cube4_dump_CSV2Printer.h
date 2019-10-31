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



#ifndef CUBE_DUMP_CSV2_PRINTER
#define CUBE_DUMP_CSV2_PRINTER

#include <sstream>
#include "cube4_dump_CSVPrinter.h"


class CSV2Printer : public CSVPrinter
{
protected:
    /**
     * Called in dump*() methods, redirect the data and modifier
     * to the proper output.
     * Used in RPrinter for forwarding the data into an R matrix.
     */
    virtual void
    save_column_name( const std::string& id ) const;
    virtual void
    save_io_formatter( const std::string& formatter ) const;
    virtual void
    save_column_value( const uint32_t value ) const;
    virtual void
    save_column_value( cube::Value* value ) const;
    virtual void
    save_newline() const;

public:
    CSV2Printer( std::ostream& _out,
                 cube::Cube*   _cube ) : CSVPrinter( _out, _cube )
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

    virtual
    void
    dump_flat_profile(  std::vector < cube::Metric* >& _metrics,
                        std::vector < cube::Region* >& regions,
                        std::vector < cube::Thread* >& _threads,
                        cube::CalculationFlavour       _mf,
                        ThreadSelection                selected_threads ) const;
};

#endif
