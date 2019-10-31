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

#include "cube4_dump_GnuPlot2Printer.h"

using namespace cube;
using namespace std;



void
GnuPlot2Printer::dump_data( vector<Metric*>& metrics, vector<Cnode*>& cnodes, vector<Thread*>& threads, CalculationFlavour mf, CalculationFlavour cf, bool stored, ThreadSelection aggregate_over_threads )  const
{
    fout << endl << endl << "# ===================== CONFIGURE GNUPLOT =================== " << endl;

    fout << "set logscal x ; set logscal y ; set grid ; set xrange [16:1000000] ; set terminal png size \"600,400\"" << endl << endl;

    fout << " set style line 1 lt 1 lc rgb '#0072bd' lw 2 ps 2 # blue" << endl;
    fout << "set style line 2 lt 1 lc rgb '#d95319' lw 2 ps 2 # orange" << endl;
    fout << " set style line 3 lt 1 lc rgb '#a2142f' lw 2 ps 2 # red" << endl;
    fout << " set style line 4 lt 1 lc rgb '#7e2f8e' lw 2 ps 2 # purple" << endl;
    fout << " set style line 5 lt 1 lc rgb '#77ac30' lw 2 ps 2 # green" << endl;

    fout << " set key  tmargin" << endl;

    fout << endl << endl << "# ===================== DATA =================== " << endl;


    string       comma   = "";
    int          counter = 0;
    string       outputName;
    stringstream outputCounter;

    string       colorName;
    stringstream colorCounter;

    string       result1Name;
    stringstream result1Counter;
    string       result2Name;
    stringstream result2Counter;

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

            string _caption = "\"" + ( ( ( *c_iter )->get_callee() )->get_name() + _str ) + "\"";

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
                    if ( counter % 5 == 0 )
                    {
                        outputCounter.str( "" );
                        outputCounter << counter / 5;
                        outputName = outputCounter.str();

                        result1Counter.str( "" );
                        result1Counter << counter;
                        result1Name = result1Counter.str();

                        result2Counter.str( "" );
                        result2Counter << counter + 4;
                        result2Name = result2Counter.str();


                        fout << endl << endl << ";set output \"" << outputName << ".png\" ; plot for [IDX=" << result1Name << ":" << result2Name << "] \"result.dat\" i IDX ls (IDX%5)+1 ";
                        comma = "";
                    }

                    _value = _v->getString();


                    colorCounter.str( "" );
                    colorCounter << ( counter % 5 ) + 1;
                    colorName = colorCounter.str();
                    comma     = " , ";
                    fout << comma << _value << " t " << _caption << " ls " << colorName;



                    counter++;
                }
                _v->Free();
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
                        if ( counter % 5 == 0 )
                        {
                            outputCounter.str( "" );
                            outputCounter << counter / 5;
                            outputName = outputCounter.str();

                            result1Counter.str( "" );
                            result1Counter << counter;
                            result1Name = result1Counter.str();

                            result2Counter.str( "" );
                            result2Counter << counter + 4;
                            result2Name = result2Counter.str();


                            fout << endl << endl << ";set output \"" << outputName << ".png\" ; plot for [IDX=" << result1Name << ":" << result2Name << "] \"result.dat\" i IDX ls (IDX%5)+1  ";
                            comma = "";
                        }

                        _value = _v->getString();
                        colorCounter.str( "" );
                        colorCounter << ( counter % 5 ) + 1;
                        colorName = colorCounter.str();
                        comma     = " , ";
                        fout << comma << _value << " t " << _caption << " ls " << colorName;


                        counter++;
                    }
                    _v->Free();
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
                        if ( counter % 5 == 0 )
                        {
                            outputCounter.str( "" );
                            outputCounter << counter / 5;
                            outputName = outputCounter.str();

                            result1Counter.str( "" );
                            result1Counter << counter;
                            result1Name = result1Counter.str();

                            result2Counter.str( "" );
                            result2Counter << counter + 4;
                            result2Name = result2Counter.str();


                            fout << endl << endl << ";set output \"" << outputName << ".png\" ; plot for [IDX=" << result1Name << ":" << result2Name << "] \"result.dat\" i IDX ls (IDX%5)+1 ";
                            comma = "";
                        }
                        _value = _v[ t_index ]->getString();
                        colorCounter.str( "" );
                        colorCounter << ( counter % 5 ) + 1;
                        colorName = colorCounter.str();
                        comma     = " , ";
                        fout << comma << _value << " t " << _caption << " ls " << colorName;


                        counter++;
                    }
                }
                services::delete_row_of_values( _v, threads.size() );
            }
        }
    }
}
