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



#ifndef CUBE_DUMP_R_PRINTER
#define CUBE_DUMP_R_PRINTER
#include <RInside.h>
// there is a macro called "Free", defined in R headers
// also, some Cube classes have method named "Free"
#undef Free
#include "cube4_dump_CSV2Printer.h"


class RPrinter : public CSV2Printer
{
    // name of output file
    std::string& file;
    /**
     * The interface of overriden functions requires const-qualifier,
     * but the class has to contain R objects which will be modified.
     */
    // internal instance of R
    mutable RInside R;
    // currently processed matrices
    mutable std::vector<Rcpp::NumericMatrix*> matrices;
    // counter of currently processed row and column (for internal method)
    mutable int row_counter;
    mutable int col_counter;
    // number of metrics
    mutable int metric_size;
    // metric counter for internal methods
    mutable int metric_counter;
    // number of columns in each matrix
    mutable int col_size;
    /**
     * Internal function, called when the matrix is filled
     * and can be saved to a file.
     */
    void
    saveMatrix( std::vector<cube::Metric*>& metrices ) const;

    /**
     * Increment internal counters after inserting value into one of R matrices.
     */
    void
    increment_counters() const;

protected:
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
    RPrinter( std::string& _out,
              cube::Cube*  _cube ) : CSV2Printer( std::cout, _cube ), file( _out ), row_counter( 0 ), col_counter( 0 ), metric_size( 0 ), metric_counter( 0 ), col_size( 0 )
    {
    }
    ~RPrinter()
    {
        for ( std::vector<Rcpp::NumericMatrix*>::iterator it = matrices.begin(); it != matrices.end(); ++it )
        {
            delete *it;
        }
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
