/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2017                                                **
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


#include "config.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include "cube4_dump_RPrinter.h"

using namespace std;
using namespace cube;

void
RPrinter::dump_flat_profile( std::vector<cube::Metric*>& metrics, std::vector<cube::Region*>& regions, std::vector<cube::Thread*>& threads, cube::CalculationFlavour mf, ThreadSelection aggregate_over_threads )  const
{
    if ( aggregate_over_threads  == AGGREGATED_THREADS )
    {
        col_size = 1;
    }
    else
    {
        col_size = threads.size();
    }
    metric_size = metrics.size() * 2;
    // for each metric create matrix [regions, 1] -> accumulated values for threads
    for ( std::vector<cube::Metric*>::iterator m_iter = metrics.begin(); m_iter != metrics.end(); ++m_iter )
    {
        matrices.push_back( new Rcpp::NumericMatrix( regions.size() * col_size, 1 ) );
        // subroutines
        matrices.push_back( new Rcpp::NumericMatrix( regions.size() * col_size, 1 ) );
    }
    col_size = 1;
    // now do the actual processing
    CSV2Printer::dump_flat_profile( metrics, regions, threads, mf, aggregate_over_threads );
    saveMatrix( metrics );
}

void
RPrinter::dump_data( std::vector<cube::Metric*>& metrics, std::vector<cube::Cnode*>& cnodes, std::vector<cube::Thread*>& threads, cube::CalculationFlavour mf, cube::CalculationFlavour cf, bool stored, ThreadSelection aggregate_over_threads ) const
{
    if ( aggregate_over_threads  == AGGREGATED_THREADS )
    {
        col_size = 1;
    }
    else
    {
        col_size = threads.size();
    }
    metric_size = metrics.size();
    // for each metric create matrix [cnodes, 1] -> accumulated values for threads
    for ( std::vector<cube::Metric*>::iterator m_iter = metrics.begin(); m_iter != metrics.end(); ++m_iter )
    {
        matrices.push_back( new Rcpp::NumericMatrix( cnodes.size() * col_size, 1 ) );
    }
    col_size = 1;
    // now do the actual processing
    CSV2Printer::dump_data( metrics, cnodes, threads, mf, cf, stored, aggregate_over_threads );
    saveMatrix( metrics );
}

void
RPrinter::saveMatrix( std::vector<cube::Metric*>& metrices ) const
{
    // set column names - it seems that C++ API doesn't support this
    /*std::string cmd = "colnames(" + file + ") <- colnames(" + file + ",do.NULL=FALSE)";
       R.parseEval(cmd);
       cmd = "colnames(" + file + ") <- c(";
       for(std::vector<std::string>::iterator it = column_names.begin();it != column_names.end();++it) {
            cmd += "\"" + *it + "\",";
       }
       cmd[cmd.length()-1] = ')';
       R.parseEval(cmd);*/

    // write R object
    std::vector<cube::Metric*>::iterator m_it = metrices.begin();
    std::string                          cmd  = "save(";
    std::string                          name;
    for ( std::vector<Rcpp::NumericMatrix*>::iterator it = matrices.begin(); it != matrices.end(); ++it )
    {
        name      = ( *m_it )->get_uniq_name();
        R[ name ] = **it;
        cmd      += name + ",";
        // include subroutine
        if ( metrices.size() != matrices.size() )
        {
            ++it;
            name     += "_Subroutines";
            R[ name ] = **it;
            cmd      += name + ",";
        }
        ++m_it;
    }
    cmd += "file='" + file + "')";
    R.parseEval( cmd );
    for ( std::vector<Rcpp::NumericMatrix*>::iterator it = matrices.begin(); it != matrices.end(); ++it )
    {
        delete *it;
    }
    matrices.clear();
}

void
RPrinter::save_column_name( const std::string& name ) const
{
    // don't use this
}

void
RPrinter::save_io_formatter( const std::string& formatter ) const
{
    // don't use this
}

void
RPrinter::save_column_value( const uint32_t value ) const
{
    // (*matrices[metric_counter])(row_counter,col_counter) = value;
    // increment_counters();
}

void
RPrinter::save_column_value( cube::Value* value ) const
{
    ( *matrices[ metric_counter ] )( row_counter * col_size + col_counter, 0 ) = value ? value->getDouble() : 0.0;
    increment_counters();
}

void
RPrinter::save_newline() const
{
    // don't use this
}

void
RPrinter::increment_counters() const
{
    ++metric_counter;
    // next thread
    if ( metric_counter == metric_size )
    {
        ++col_counter;
        metric_counter = 0;
    }
    // last thread in the row
    if ( col_counter == col_size )
    {
        col_counter = 0;
        row_counter++;
    }
}
