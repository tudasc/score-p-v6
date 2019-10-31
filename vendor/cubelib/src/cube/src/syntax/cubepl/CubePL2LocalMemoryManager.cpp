/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016-2018                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/



#include "config.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <float.h>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <string>
#include <algorithm>

#include "CubePL2LocalMemoryManager.h"
#include "CubeError.h"


using namespace std;
using namespace cube;


CubePL2LocalMemoryManager::CubePL2LocalMemoryManager()
{
    init();
};

CubePL2LocalMemoryManager::~CubePL2LocalMemoryManager()
{
//     cout << " Statistic on CubePL:" << endl;
//     cout << " Max size of used memory : " << memory.size() << endl;
//     cout << " Max size of used global memory : " << global_memory.size() << endl;
    clear_memory();
};



void
CubePL2LocalMemoryManager::clear_memory()
{
    for ( std::vector< std::vector<CubePL2MemoryDuplet> >::iterator it = memory.begin(); it != memory.end(); ++it )
    {
        std::vector<CubePL2MemoryDuplet> _vec = *it;
        for ( std::vector<CubePL2MemoryDuplet>::iterator it1 = _vec.begin(); it1 != _vec.end(); ++it1 )
        {
            if ( ( *it1 ).row_value != NULL )
            {
                delete[] ( *it1 ).row_value;
                ( *it1 ).row_value = NULL;
            }
        }
        _vec.clear();
    }

    memory.clear();
    while ( memory_stack.size() > 0 )
    {
        memory_stack.pop();
    }
    memory_stack.push( 0 );
}


void
CubePL2LocalMemoryManager::init()
{
    clear_memory();
//     registered_variables.clear();
//     registered_variables[ "calculation::metric::id" ]   = cubepl2::CALCULATION_METRIC_ID;
//     registered_variables[ "calculation::callpath::id" ] = cubepl2::CALCULATION_CALLPATH_ID;
//     registered_variables[ "calculation::region::id" ]   = cubepl2::CALCULATION_REGION_ID;
//     registered_variables[ "calculation::sysres::id" ]   = cubepl2::CALCULATION_SYSRES_ID;
//     registered_variables[ "calculation::sysres::kind" ] = cubepl2::CALCULATION_SYSRES_KIND;
//     page_size                                           = 5;
};


void
CubePL2LocalMemoryManager::set_page_size( uint32_t _page_size )
{
    page_size = _page_size;
    memory.resize( memory_stack.top() + page_size );
};


void
CubePL2LocalMemoryManager::new_page()
{
    if ( page_size == 0 )
    {
        return;
    }
    if ( memory_stack.top() > memory.size() )
    {
        throw CubePLMemoryLayoutError( "Memory stack point out of memory range" );
    }
    if ( memory.size() - memory_stack.top() < 2 * page_size )
    {
        memory.resize( 10 * page_size + memory_stack.top() ); // Extend the memory for double page. Complete current and allocate new one
    }
    memory_stack.push( memory_stack.top() + page_size );      // move page pointer to another page;
};

void
CubePL2LocalMemoryManager::throw_page()
{
    for ( size_t adress = 0; adress < page_size; ++adress )
    {
        memory[ memory_stack.top() +  adress ].clear();
    }
    if ( memory_stack.size() > 1 )
    {
        memory_stack.pop();
    }
}




void
CubePL2LocalMemoryManager::clear_variable( MemoryAdress adress )
{
    for ( std::vector<CubePL2MemoryDuplet>::iterator it1 = memory[ memory_stack.top() +  adress ].begin(); it1 != memory[ memory_stack.top() +  adress ].end(); ++it1 )
    {
        delete[] ( *it1 ).row_value;
        ( *it1 ).row_value = NULL;
    }
    memory[ memory_stack.top() +  adress ].clear();
}

void
CubePL2LocalMemoryManager::put( MemoryAdress adress,
                                double       index,
                                double       value )
{
    size_t _index = ( size_t )index;
    if ( memory_stack.top() +  adress <= memory.size() )
    {
        if (  memory[ memory_stack.top() +  adress ].size() <= _index )
        {
            memory[ memory_stack.top() +  adress ].resize( _index + 20 );
        }
    }
    memory[ memory_stack.top() +  adress ][ _index ].double_value = value;
    delete[] memory[ memory_stack.top() +  adress ][ _index ].row_value;
    memory[ memory_stack.top() +  adress ][ _index ].row_value = NULL;
    memory[ memory_stack.top() +  adress ][ _index ].state     = CUBEPL_VALUE_DOUBLE;
};


void
CubePL2LocalMemoryManager::put( MemoryAdress adress,
                                double       index,
                                string       value )
{
    size_t _index = ( size_t )index;
    if (  memory[ memory_stack.top() +  adress ].size() <= _index )
    {
        memory[ memory_stack.top() +  adress ].resize( _index + 20 );
    }
    memory[ memory_stack.top() +  adress ][ _index ].state        = CUBEPL_VALUE_STRING;
    memory[ memory_stack.top() +  adress ][ _index ].string_value = value;
};

void
CubePL2LocalMemoryManager::put( MemoryAdress adress,
                                double       index,
                                double*      value
                                )
{
    size_t       _index = ( size_t )index;
    MemoryAdress _top   = memory_stack.top();

    if (  memory[ _top +  adress ].size() <= _index )
    {
        memory[ _top +  adress ].resize( _index + 20 );
    }
    memory[ _top +  adress ][ _index ].state = CUBEPL_VALUE_ROW;
    delete[] memory[ _top +  adress ][ _index ].row_value;
    memory[ _top +  adress ][ _index ].row_value = value;
}




void
CubePL2LocalMemoryManager::push_back( MemoryAdress adress,
                                      double       value )
{
    CubePL2MemoryDuplet _t;
    _t.double_value = value;
    _t.state        = CUBEPL_VALUE_DOUBLE;

    memory[ memory_stack.top() +  adress ].push_back( _t );
}

void
CubePL2LocalMemoryManager::push_back( MemoryAdress adress,
                                      string       value )
{
    CubePL2MemoryDuplet _t;
    _t.string_value = value;
    _t.state        = CUBEPL_VALUE_STRING;
    memory[ memory_stack.top() +  adress ].push_back( _t );
}

double
CubePL2LocalMemoryManager::get( MemoryAdress adress,
                                double       index )
{
    size_t _index = ( size_t )index;
    if ( memory[ memory_stack.top() +  adress ].size() <= _index )
    {
        return 0.;
    }
    else
    {
        CubePL2MemoryDuplet& _t =  memory[ memory_stack.top() +  adress ][ _index ];
        if ( _t.state == CUBEPL_VALUE_STRING ) // convert to double if possible
        {
            std::istringstream stream( _t.string_value );
            double             t;
            stream >> t;
            _t.double_value = t;
            _t.state        = CUBEPL_VALUE_EQUAL;
        }
        return _t.double_value;
    }
}

string
CubePL2LocalMemoryManager::get_as_string( MemoryAdress adress,
                                          double       index )
{
    size_t _index = ( size_t )index;
    if ( memory[ memory_stack.top() +  adress ].size() <= _index )
    {
        return "";
    }
    else
    {
        CubePL2MemoryDuplet& _t =  memory[ memory_stack.top() +  adress ][ _index ];
        if ( _t.state == CUBEPL_VALUE_DOUBLE ) // convert to string if possible
        {
            stringstream sstr;
            sstr <<  setprecision( 14 ) <<  _t.double_value;
            sstr >> _t.string_value;
            _t.state = CUBEPL_VALUE_EQUAL;
        }
        return _t.string_value;
    }
}

double*
CubePL2LocalMemoryManager::get_row( MemoryAdress adress,
                                    double       index )
{
    size_t _index = ( size_t )index;
    if ( memory[ memory_stack.top() +  adress ].size() <= _index )
    {
        return NULL;
    }
    else
    {
        CubePL2MemoryDuplet& _t =  memory[ memory_stack.top() +  adress ][ _index ];
        if ( _t.state != CUBEPL_VALUE_ROW && _t.row_value == NULL ) // convert to double if possible
        {
            double  value = get( adress, index );
            double* _row  = new double[ row_size ];
            std::fill_n( _row, row_size, value );
            _t.row_value = _row;
            _t.state     = CUBEPL_VALUE_ROW;
        }
        return _t.row_value;
    }
}





size_t
CubePL2LocalMemoryManager::size_of( MemoryAdress adress )
{
    return memory[ memory_stack.top() +  adress ].size();
}

CubePL2StateOfCubePLVariable
CubePL2LocalMemoryManager::type( MemoryAdress adress,
                                 double       index )
{
    size_t _index = ( size_t )index;
    if ( memory[ memory_stack.top() +  adress ].size() <= _index )
    {
        return CUBEPL_VALUE_DOUBLE;
    }
    else
    {
        CubePL2MemoryDuplet& _t =  memory[ memory_stack.top() +  adress ][ _index ];
        return _t.state;
    }
}
