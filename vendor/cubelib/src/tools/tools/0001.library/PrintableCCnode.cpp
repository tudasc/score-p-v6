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



#include "config.h"
#include "PrintableCCnode.h"

#include <iostream>
#include <iomanip>
#include <sstream>

#include "CCnode.h"
#include "CnodeMetric.h"

#include "CubeRegion.h"
#include "CubeCnode.h"

using namespace cube;
using namespace std;

PrintableCCnode::PrintableCCnode( Region*            callee,
                                  const std::string& mod,
                                  int                line,
                                  Cnode*             parent,
                                  uint32_t           id,
                                  int                cache_size )
    : CCnode( callee, mod, line, parent, id, cache_size )
{
}

void
PrintableCCnode::print(
    vector<CnodeMetric*> const& metrics,
    ostream&                    stream )
{
    std::vector<int> number_of_cubes = print_headers( metrics, stream );
    stream << "Call tree" << endl;
    print_helper( metrics, stream, number_of_cubes );
}

void
PrintableCCnode::print_callpath(
    vector<CnodeMetric*> const& metrics,
    ostream&                    stream )
{
    vector<int> number_of_cubes = print_headers( metrics, stream );
    stream << "Call path" << endl;
    print_values( metrics, stream, number_of_cubes );
    stream << "           ";
    pretty_print_region( get_callee(), stream );
    PrintableCCnode* _parent = this;
    while ( ( _parent = _parent->get_parent() ) != NULL )
    {
        _parent->print_values( metrics, stream, number_of_cubes );
        stream << " called by ";
        pretty_print_region( _parent->get_callee(), stream );
    }
}

string
PrintableCCnode::to_string(
    vector<CnodeMetric*> const& metrics )
{
    stringstream ss;
    print( metrics, ss );
    return ss.str();
}

string
PrintableCCnode::to_string_callpath(
    vector<CnodeMetric*> const& metrics )
{
    stringstream ss;
    print_callpath( metrics, ss );
    return ss.str();
}

PrintableCCnode*
PrintableCCnode::get_parent()
{
    return static_cast<PrintableCCnode*>( CCnode::get_parent() );
}

PrintableCCnode*
PrintableCCnode::get_child( unsigned int id )
{
    return static_cast<PrintableCCnode*>( CCnode::get_child( id ) );
}

vector<int>
PrintableCCnode::print_headers(
    vector<CnodeMetric*>const& metrics,
    ostream&                   stream )
{
    vector<CnodeMetric*>::const_iterator it;
    int                                  i = 0;
    vector<int>                          number_of_stored_values;
    if ( metrics.empty() == false )
    {
        stream << "| ";
    }

    for ( it = metrics.begin(); it != metrics.end(); ++it, ++i )
    {
        int number_of_stored_values_metric = get_cache_size(); // get_all(*it).size();
        number_of_stored_values.push_back( number_of_stored_values_metric );
        for ( int j = 0; j < number_of_stored_values_metric; ++j )
        {
            stream << setw( column_width )
                   << ( *it )->to_string( column_width - 2 ) << " | ";
        }
    }
    return number_of_stored_values;
}

void
PrintableCCnode::print_helper(
    vector<CnodeMetric*>const& metrics,
    ostream& stream, vector<int> const& number_of_values )
{
    print_values( metrics, stream, number_of_values );
    stream << treeindent() << get_callee()->get_name() << endl;
    for ( unsigned int i = 0; i < num_children(); ++i )
    {
        get_child( i )->print_helper( metrics, stream, number_of_values );
    }
}

void
PrintableCCnode::print_values(
    vector<CnodeMetric*>const& metrics,
    ostream& stream, vector<int> const& number_of_values )
{
    int number_of_metrics = metrics.size();

    if ( metrics.empty() == false )
    {
        stream << "| ";
    }

    for ( int i = 0; i < number_of_metrics; ++i )
    {
        CnodeMetric*   metric          = metrics[ i ];
        vector<double> values          = metric->compute( static_cast< PrintableCCnode*>(this) );
        int            number_of_cubes = number_of_values[ i ];

        for ( int j = 0; j < number_of_cubes; ++j )
        {
            try {
                double value = values.at( j );
                stream << setw( column_width ) <<
                metric->to_string( value, column_width ) << " | ";
            }
            catch ( const exception& e )
            {
                stream << setw( column_width ) << "NVA" << " | ";
            }
        }
    }
}

void
PrintableCCnode::print_values(
    vector<CnodeMetric*>const& metrics,
    ostream& stream, vector<int> const& number_of_values,
    vector<double> const& values )
{
    if ( metrics.empty() == false )
    {
        stream << "| ";
    }

    int number_of_metrics = metrics.size();
    for ( int i = 0; i < number_of_metrics; ++i )
    {
        CnodeMetric* metric          = metrics[ i ];
        int          number_of_cubes = number_of_values[ i ];
        for ( int j = 0; j < number_of_cubes; ++j )
        {
            stream << setw( column_width ) <<
            metric->to_string( values[ i * number_of_cubes + j ], column_width ) << " | ";
        }
    }
}

string
PrintableCCnode::treeindent()
{
    return treeindent( get_level() );
}

string
PrintableCCnode::treeindent( int level )
{
    string s;
    while ( level-- > 0 )
    {
        s += " | ";
    }
    s += " * ";
    return s;
}

inline void
PrintableCCnode::pretty_print_region(
    const Region* region, ostream& stream )
{
    stream << region->get_name()
           << " (File: " << region->get_mod() << ", Line: "
           << region->get_begn_ln() << ")" << endl;
}
