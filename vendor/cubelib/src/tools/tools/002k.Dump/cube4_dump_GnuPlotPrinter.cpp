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
#include <sstream>
#include <fstream>
#include <unistd.h>

#include "cube4_dump_GnuPlotPrinter.h"

using namespace cube;
using namespace std;


void
GnuPlotPrinter::dump_flat_profile( vector<Metric*>& metrics, std::vector<Region*>& regions, vector<Thread*>& threads, CalculationFlavour mf, ThreadSelection aggregate_over_threads  )  const
{
    fout << endl << endl << "# ===================== FLAT PROFILE  =================== " << endl;

    for ( vector<Metric*>::iterator m_iter = metrics.begin(); m_iter != metrics.end(); ++m_iter )
    {
        fout << "# Print out the data of the metric " << ( ( *m_iter )->get_uniq_name() ) << endl << endl;

        for ( std::vector<Region*>::iterator r_iter = regions.begin(); r_iter != regions.end(); ++r_iter )
        {
            stringstream sstr;
            string       _str;
            sstr << "(id=" << ( *r_iter )->get_id() << ")";
            sstr >> _str;
            stringstream sstr1;
            string       _str_id;
            sstr1 << ( *r_iter )->get_id();
            sstr1 >> _str_id;

            string _caption = "#" + ( ( *r_iter )->get_name() + _str ) + "   Subroutines ";
            fout << endl << _caption << endl;
            if ( aggregate_over_threads == AGGREGATED_THREADS )
            {
                Value* _v = NULL;
                _v = cube->get_sev_adv( *m_iter, mf,  *r_iter, cube::CUBE_CALCULATE_EXCLUSIVE );
                Value* _v_sub = NULL;
                ( *r_iter )->set_as_subroutines();   // calculate subroutines of this region
                _v_sub = cube->get_sev_adv( *m_iter, mf,  *r_iter, cube::CUBE_CALCULATE_INCLUSIVE );
                ( *r_iter )->unset_as_subroutines(); // reset its status
                string _value1;
                string _value2;

                if ( _v == NULL )
                {
                    _value1 = "0.";
                }
                else
                {
                    _value1 = _v->getString();
                }
                if ( _v_sub == NULL )
                {
                    _value2 = "0.";
                }
                else
                {
                    _value2 = _v_sub->getString();
                }

                _v->Free();
                _v_sub->Free();

                fout << _str_id << '\t' << _value1 <<  '\t'  << _value2 << endl;
            }
            else if ( aggregate_over_threads == SELECTED_THREADS )
            {
                int t_index = 0;
                for ( vector<Thread*>::iterator t_iter = threads.begin(); t_iter != threads.end(); ++t_iter, ++t_index )
                {
                    Value* _v = NULL;
                    _v = cube->get_sev_adv( *m_iter, mf,  *r_iter, cube::CUBE_CALCULATE_EXCLUSIVE, *t_iter, cube::CUBE_CALCULATE_EXCLUSIVE );

                    string _value1;
                    if ( _v == NULL )
                    {
                        _value1 = "0.";
                    }
                    else
                    {
                        _value1 = _v->getString();
                    }
                    _v->Free();
                    fout << _str_id << '\t' << ( *t_iter )->get_id() << '\t' << _value1;
                    Value* _v_sub = NULL;
                    ( *r_iter )->set_as_subroutines();   // calculate subroutines of this region
                    _v_sub = cube->get_sev_adv( *m_iter, mf,  *r_iter, cube::CUBE_CALCULATE_INCLUSIVE, *t_iter, cube::CUBE_CALCULATE_EXCLUSIVE );
                    ( *r_iter )->unset_as_subroutines(); // reset its status

                    string _value2;
                    if ( _v_sub == NULL )
                    {
                        _value2 = "0.";
                    }
                    else
                    {
                        _value2 = _v_sub->getString();
                    }
                    _v_sub->Free();
                    fout << '\t' << _value2 << endl;
                }
            }
            else
            {
                int     t_index = 0;
                Value** _v      = NULL;
                _v = cube->get_sevs_adv( *m_iter, mf, *r_iter, cube::CUBE_CALCULATE_EXCLUSIVE );
                Value** _v_sub = NULL;
                ( *r_iter )->set_as_subroutines();   // calculate subroutines of this region
                _v_sub = cube->get_sevs_adv( *m_iter, mf,  *r_iter, cube::CUBE_CALCULATE_INCLUSIVE );
                ( *r_iter )->unset_as_subroutines(); // reset its status

                for ( vector<Thread*>::iterator t_iter = threads.begin(); t_iter != threads.end(); ++t_iter, ++t_index )
                {
                    string _value1;
                    if ( _v == NULL || _v[ t_index ] == NULL )
                    {
                        _value1 = "0.";
                    }
                    else
                    {
                        _value1 = _v[ t_index ]->getString();
                    }

                    fout << _str_id << '\t' << ( *t_iter )->get_id() << '\t' << _value1;
                    string _value2;
                    if ( _v_sub == NULL || _v_sub[ t_index ] == NULL )
                    {
                        _value2 = "0.";
                    }
                    else
                    {
                        _value2 = _v_sub[ t_index ]->getString();
                    }
                    fout << '\t' << _value2 << endl;
                }
                services::delete_row_of_values( _v, threads.size() );
                services::delete_row_of_values( _v_sub, threads.size() );
            }
        }
        fout << endl;
    }
}





void
GnuPlotPrinter::dump_data( vector<Metric*>& metrics, vector<Cnode*>& cnodes, vector<Thread*>& threads, CalculationFlavour mf, CalculationFlavour cf, bool stored, ThreadSelection aggregate_over_threads )  const
{
    fout << endl << endl << "# ===================== DATA =================== " << endl;



    for ( vector<Metric*>::iterator m_iter = metrics.begin(); m_iter != metrics.end(); ++m_iter )
    {
        fout << "# Print out the data of the metric " << ( ( *m_iter )->get_uniq_name() ) << endl << endl;


        for ( vector<Cnode*>::iterator c_iter = cnodes.begin(); c_iter != cnodes.end(); ++c_iter )
        {
            stringstream sstr;
            string       _str;
            sstr << "(id=" << ( *c_iter )->get_id() << ")";
            sstr >> _str;
            stringstream sstr1;
            string       _str_id;
            sstr1 << ( *c_iter )->get_id();
            sstr1 >> _str_id;

            string _caption = "#" + ( ( ( *c_iter )->get_callee() )->get_name() + _str );
            fout << endl << _caption << endl;

            if ( aggregate_over_threads == AGGREGATED_THREADS )
            {
                Value* _v = NULL;
                _v = cube->get_sev_adv( *m_iter, mf, *c_iter, cf );
                string _value;
                if ( _v == NULL )
                {
                    _value = "0.";
                }
                else
                {
                    _value = _v->getString();
                }
                _v->Free();
                fout << _str_id << '\t' << _value << endl;
            }
            else if ( aggregate_over_threads == SELECTED_THREADS )
            {
                int t_index = 0;
                for ( vector<Thread*>::iterator t_iter = threads.begin(); t_iter != threads.end(); ++t_iter, ++t_index )
                {
                    Value* _v = NULL;
                    if ( stored )
                    {
                        _v = cube->get_saved_sev_adv( *m_iter, *c_iter, *t_iter );
                    }
                    else
                    {
                        _v = cube->get_sev_adv( *m_iter, mf, *c_iter, cf, *t_iter, cube::CUBE_CALCULATE_EXCLUSIVE );
                    }

                    string _value;
                    if ( _v == NULL )
                    {
                        _value = "0.";
                    }
                    else
                    {
                        _value = _v->getString();
                    }
                    _v->Free();
                    fout << _str_id << '\t' << ( *t_iter )->get_id() << '\t' << _value << endl;
                }
            }
            else
            {
                Value** _v = NULL;
                if ( stored )
                {
                    _v = cube->get_saved_sevs_adv( *m_iter, *c_iter );
                }
                else
                {
                    _v = cube->get_sevs_adv( *m_iter, mf, *c_iter, cf );
                }
                int t_index = 0;
                for ( vector<Thread*>::iterator t_iter = threads.begin(); t_iter != threads.end(); ++t_iter, ++t_index )
                {
                    string _value;
                    if ( _v == NULL || _v[ t_index ] == NULL )
                    {
                        _value = "0.";
                    }
                    else
                    {
                        _value = _v[ t_index ]->getString();
                    }
                    fout << _str_id << '\t' << ( *t_iter )->get_id() << '\t' << _value << endl;
                }
                services::delete_row_of_values( _v, threads.size() );
            }
        }
        fout << endl;
    }
}
