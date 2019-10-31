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
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>

#include "cube4_dump_CSV2Printer.h"

using namespace cube;
using namespace std;


void
CSV2Printer::dump_flat_profile( vector<Metric*>& metrics, std::vector<Region*>& regions, vector<Thread*>& threads, CalculationFlavour mf, ThreadSelection aggregate_over_threads )  const
{
    if ( aggregate_over_threads == AGGREGATED_THREADS )
    {
        save_column_name( "Region ID" );
        for ( vector<Metric*>::iterator m_iter = metrics.begin(); m_iter != metrics.end(); ++m_iter )
        {
            save_io_formatter( "," );
            save_column_name( ( *m_iter )->get_uniq_name() );
            save_io_formatter( "," );
            save_column_name( "Subroutines" );
        }
        save_newline();
        for ( std::vector<Region*>::iterator r_iter = regions.begin(); r_iter != regions.end(); ++r_iter )
        {
            save_column_value( ( *r_iter )->get_id() );
            for ( vector<Metric*>::iterator m_iter = metrics.begin(); m_iter != metrics.end(); ++m_iter )
            {
                save_io_formatter( "," );
                Value* _v = NULL;
                _v = cube->get_sev_adv( *m_iter, mf,  *r_iter, cube::CUBE_CALCULATE_EXCLUSIVE );
                Value* _v_sub = NULL;
                ( *r_iter )->set_as_subroutines();   // calculate subroutines of this region
                _v_sub = cube->get_sev_adv( *m_iter, mf,  *r_iter, cube::CUBE_CALCULATE_INCLUSIVE );
                ( *r_iter )->unset_as_subroutines(); // reset its status
                save_column_value( _v );
                save_io_formatter( "," );
                save_column_value( _v_sub );
                _v->Free();
                _v_sub->Free();
            }
            save_newline();
        }
    }
    else
    {
        save_column_name( "Region ID" );
        save_io_formatter( ", " );
        save_column_name( "Thread ID" );
        for ( vector<Metric*>::iterator m_iter = metrics.begin(); m_iter != metrics.end(); ++m_iter )
        {
            save_io_formatter( "," );
            save_column_name( ( *m_iter )->get_uniq_name() );
            save_io_formatter( "," );
            save_column_name( "Subroutines" );
        }
        save_newline();
        int t_index = 0;
        for ( std::vector<Region*>::iterator r_iter = regions.begin(); r_iter != regions.end(); ++r_iter )
        {
            int thread_id = ( *r_iter )->get_id();
            for ( vector<Thread*>::iterator t_iter = threads.begin(); t_iter != threads.end(); ++t_iter, ++t_index )
            {
                save_column_value( thread_id );
                save_io_formatter( "," );
                save_column_value( ( *t_iter )->get_id() );
                for ( vector<Metric*>::iterator m_iter = metrics.begin(); m_iter != metrics.end(); ++m_iter )
                {
                    save_io_formatter( "," );
                    Value* _v = NULL;
                    _v = cube->get_sev_adv( *m_iter, mf,  *r_iter, cube::CUBE_CALCULATE_EXCLUSIVE, *t_iter, cube::CUBE_CALCULATE_EXCLUSIVE );

                    save_column_value( _v );
                    _v->Free();

                    Value* _v_sub = NULL;
                    ( *r_iter )->set_as_subroutines();   // calculate subroutines of this region
                    _v_sub = cube->get_sev_adv( *m_iter, mf,  *r_iter, cube::CUBE_CALCULATE_INCLUSIVE, *t_iter, cube::CUBE_CALCULATE_EXCLUSIVE );
                    ( *r_iter )->unset_as_subroutines(); // reset its status

                    save_io_formatter( "," );
                    save_column_value( _v_sub );
                    _v_sub->Free();
                }
                save_newline();
            }
        }
    }
}





void
CSV2Printer::dump_data( vector<Metric*>& metrics, vector<Cnode*>& cnodes, vector<Thread*>& threads, CalculationFlavour mf, CalculationFlavour cf, bool stored, ThreadSelection aggregate_over_threads )  const
{
    if ( aggregate_over_threads  == AGGREGATED_THREADS )
    {
        save_column_name( "Cnode ID" );
        for ( vector<Metric*>::iterator m_iter = metrics.begin(); m_iter != metrics.end(); ++m_iter )
        {
            save_io_formatter( "," );
            save_column_name( ( *m_iter )->get_uniq_name() );
        }
        save_newline();
        for ( vector<Cnode*>::iterator c_iter = cnodes.begin(); c_iter != cnodes.end(); ++c_iter )
        {
            save_column_value( ( *c_iter )->get_id() );
            for ( vector<Metric*>::iterator m_iter = metrics.begin(); m_iter != metrics.end(); ++m_iter )
            {
                save_io_formatter( "," );
                Value* _v = NULL;
                _v = cube->get_sev_adv( *m_iter, mf, *c_iter, cf );
                save_column_value( _v );
                _v->Free();
            }
            save_newline();
        }
    }
    else
    {
        save_column_name( "Cnode ID" );
        save_io_formatter( ", " );
        save_column_name( "Thread ID" );
        for ( vector<Metric*>::iterator m_iter = metrics.begin(); m_iter != metrics.end(); ++m_iter )
        {
            save_io_formatter( "," );
            save_column_name( ( *m_iter )->get_uniq_name() );
        }
        save_newline();
        int t_index = 0;
        for ( vector<Cnode*>::iterator c_iter = cnodes.begin(); c_iter != cnodes.end(); ++c_iter )
        {
            for ( vector<Thread*>::iterator t_iter = threads.begin(); t_iter != threads.end(); ++t_iter, ++t_index )
            {
                save_column_value( ( *c_iter )->get_id() );
                save_io_formatter( "," );
                save_column_value( ( *t_iter )->get_id() );
                for ( vector<Metric*>::iterator m_iter = metrics.begin(); m_iter != metrics.end(); ++m_iter )
                {
                    save_io_formatter( "," );
                    Value* _v = NULL;
                    if ( stored )
                    {
                        _v = cube->get_saved_sev_adv( *m_iter, *c_iter, *t_iter );
                    }
                    else
                    {
                        _v = cube->get_sev_adv( *m_iter, mf, *c_iter, cf, *t_iter, cube::CUBE_CALCULATE_EXCLUSIVE );
                    }

                    save_column_value( _v );
                    _v->Free();
                }
                save_newline();
            }
        }
    }
}

void
CSV2Printer::save_column_name( const string& name ) const
{
    fout << name;
}

void
CSV2Printer::save_io_formatter( const string& formatter ) const
{
    fout << formatter;
}

void
CSV2Printer::save_column_value( const uint32_t value ) const
{
    stringstream sstr;
    sstr.str( string() );
    sstr.clear();
    sstr << value;
    string str;
    sstr >> str;
    fout << str;
}

void
CSV2Printer::save_column_value( Value* value ) const
{
    if ( value == NULL )
    {
        fout << "0.";
    }
    else
    {
        fout << value->getString();
    }
}

void
CSV2Printer::save_newline() const
{
    fout << endl;
}
