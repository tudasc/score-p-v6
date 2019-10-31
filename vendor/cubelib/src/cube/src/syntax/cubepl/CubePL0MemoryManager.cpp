/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2019                                                **
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
#include <vector>
#include <iostream>
#include <sstream>
#include <float.h>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <string>

#include "CubePL0MemoryManager.h"
#include "CubePL0MemoryInitializer.h"
using namespace std;
using namespace cube;


CubePL0MemoryManager::CubePL0MemoryManager() : CubePLMemoryManager()
{
    cubepl_memory_initializer = new CubePL0MemoryInitializer( this );
    while ( memory.size() > 1 )
    {
        throw_page();
    }
    reserved_variables.clear();

    reserved_variables[ "cube::#mirrors" ]         = cubepl0::CUBE_NUM_MIRRORS;
    reserved_variables[ "cube::#metrics" ]         = cubepl0::CUBE_NUM_METRICS;
    reserved_variables[ "cube::#root::metrics" ]   = cubepl0::CUBE_NUM_ROOT_METRICS;
    reserved_variables[ "cube::#regions" ]         = cubepl0::CUBE_NUM_REGIONS;
    reserved_variables[ "cube::#callpaths" ]       = cubepl0::CUBE_NUM_CALLPATHS;
    reserved_variables[ "cube::#root::callpaths" ] = cubepl0::CUBE_NUM_ROOT_CALLPATHS;
    reserved_variables[ "cube::#threads" ]         = cubepl0::CUBE_NUM_THREADS;
    reserved_variables[ "cube::filename" ]         = cubepl0::CUBE_FILENAME;

    reserved_variables[ "calculation::metric::uniq::name" ]  = cubepl0::CALCULATION_METRIC_UNIQ_NAME;
    reserved_variables[ "calculation::metric::disp::name" ]  = cubepl0::CALCULATION_METRIC_DISP_NAME;
    reserved_variables[ "calculation::metric::url" ]         = cubepl0::CALCULATION_METRIC_URL;
    reserved_variables[ "calculation::metric::description" ] = cubepl0::CALCULATION_METRIC_DESCRIPTION;
    reserved_variables[ "calculation::metric::dtype" ]       = cubepl0::CALCULATION_METRIC_DTYPE;
    reserved_variables[ "calculation::metric::uom" ]         = cubepl0::CALCULATION_METRIC_UOM;
    reserved_variables[ "calculation::metric::expression" ]  = cubepl0::CALCULATION_METRIC_EXPRESSION;
    reserved_variables[ "calculation::metric::id" ]          = cubepl0::CALCULATION_METRIC_ID;
    reserved_variables[ "calculation::metric::#children" ]   = cubepl0::CALCULATION_METRIC_NUM_CHILDREN;

    reserved_variables[ "calculation::callpath::mod" ]       = cubepl0::CALCULATION_CALLPATH_MOD;
    reserved_variables[ "calculation::callpath::line" ]      = cubepl0::CALCULATION_CALLPATH_LINE;
    reserved_variables[ "calculation::callpath::id" ]        = cubepl0::CALCULATION_CALLPATH_ID;
    reserved_variables[ "calculation::callpath::#children" ] = cubepl0::CALCULATION_CALLPATH_NUM_CHILDREN;

    reserved_variables[ "calculation::region::name" ]        = cubepl0::CALCULATION_REGION_NAME;
    reserved_variables[ "calculation::region::url" ]         = cubepl0::CALCULATION_REGION_URL;
    reserved_variables[ "calculation::region::description" ] = cubepl0::CALCULATION_REGION_DESCRIPTION;
    reserved_variables[ "calculation::region::mod" ]         = cubepl0::CALCULATION_REGION_MOD;
    reserved_variables[ "calculation::region::begin::line" ] = cubepl0::CALCULATION_REGION_BEGIN_LINE;
    reserved_variables[ "calculation::region::end::line" ]   = cubepl0::CALCULATION_REGION_END_LINE;
    reserved_variables[ "calculation::region::id" ]          = cubepl0::CALCULATION_REGION_ID;

    reserved_variables[ "calculation::sysres::name" ] = cubepl0::CALCULATION_SYSRES_NAME;
    reserved_variables[ "calculation::sysres::id" ]   = cubepl0::CALCULATION_SYSRES_ID;
    reserved_variables[ "calculation::sysres::kind" ] = cubepl0::CALCULATION_SYSRES_KIND;
    reserved_variables[ "calculation::sysres::rank" ] = cubepl0::CALCULATION_SYSRES_RANK;


    reserved_variables[ "cube::#threads::void" ]      = cubepl0::CUBE_NUM_VOID_THRDS;
    reserved_variables[ "cube::#threads::nonvoid" ]   = cubepl0::CUBE_NUM_NONVOID_THRDS;
    reserved_variables[ "cube::#processes::void" ]    = cubepl0::CUBE_NUM_VOID_PROCS;
    reserved_variables[ "cube::#processes::nonvoid" ] = cubepl0::CUBE_NUM_NONVOID_PROCS;

    reserved_variables[ "calculation::thread::void" ]  = cubepl0::CALCULATION_THREAD_VOID;
    reserved_variables[ "calculation::process::void" ] = cubepl0::CALCULATION_PROCESS_VOID;
};

CubePL0MemoryManager::~CubePL0MemoryManager()
{
};


MemoryAdress
CubePL0MemoryManager::register_variable( std::string name, KindOfVariable )
{
    std::map<std::string, MemoryAdress>::iterator it;
    it = reserved_variables.find( name );
    if ( it  != reserved_variables.end() )
    {
        return ( *it ).second;
    }
    it = registered_variables.find( name );
    if ( it  != registered_variables.end() )
    {
        return ( *it ).second;
    }
    size_t                                    _addr = memory.top().size();
    vector< vector < CubePL0MemoryDuplet > >& page  = memory.top();
    page.resize( memory.top().size() + 1 );
    registered_variables[ name ] = _addr;
    return _addr;
}

bool
CubePL0MemoryManager::defined( std::string name )
{
    std::map<std::string, MemoryAdress>::iterator it;
    it = reserved_variables.find( name );
    if ( it  != reserved_variables.end() )
    {
        return true;
    }
    it = registered_variables.find( name );
    if ( it  != registered_variables.end() )
    {
        return true;
    }
    return false;
}



void
CubePL0MemoryManager::clear_variable( MemoryAdress adress,
                                      uint32_t met_id, KindOfVariable )
{
    ( void )met_id;
    vector< vector < CubePL0MemoryDuplet > >& page = memory.top();
    page[ adress ].clear();
}

void
CubePL0MemoryManager::put( MemoryAdress adress,  double index, double value,
                           uint32_t met_id, KindOfVariable )
{
    ( void )met_id;
    stringstream sstr;
    string       str;
    sstr <<  setprecision( 14 ) << value;
    sstr >> str;


    vector< vector < CubePL0MemoryDuplet > >& page   = memory.top();
    size_t                                    _index = ( size_t )index;

    if ( page[ adress ].size() <= _index )
    {
        page[ adress ].resize( _index + 1 );
    }
    page[ adress ][ _index ].double_value = value;
    page[ adress ][ _index ].string_value = str;
};


void
CubePL0MemoryManager::put( MemoryAdress adress,  double index, string value,
                           uint32_t met_id, KindOfVariable )
{
    ( void )met_id;
    size_t                                    _index = ( size_t )index;
    vector< vector < CubePL0MemoryDuplet > >& page   = memory.top();
    if ( page[ adress ].size() <= _index )
    {
        page[ adress ].resize( _index + 1 );
    }

    std::istringstream stream( value );
    double             t;
    stream >> t;
    page[ adress ][ _index ].double_value = t;
    page[ adress ][ _index ].string_value = value;
};


void
CubePL0MemoryManager::put( MemoryAdress,
                           double,
                           double*,
                           uint32_t,
                           KindOfVariable
                           )
{
    return;
}



void
CubePL0MemoryManager::push_back( MemoryAdress adress,  double value,
                                 uint32_t met_id, KindOfVariable )
{
    ( void )met_id;
    vector< vector < CubePL0MemoryDuplet > >& page = memory.top();
    stringstream                              sstr;
    string                                    str;
    sstr <<  setprecision( 14 ) << value;
    sstr >> str;

    CubePL0MemoryDuplet _t;
    _t.double_value = value;
    _t.string_value = str;

    page[ adress ].push_back( _t );
}

void
CubePL0MemoryManager::push_back( MemoryAdress adress, string value,
                                 uint32_t met_id, KindOfVariable )
{
    ( void )met_id;
    vector< vector < CubePL0MemoryDuplet > >& page = memory.top();

    std::istringstream stream( value );
    double             t;
    stream >> t;
    CubePL0MemoryDuplet _t;
    _t.double_value = t;
    _t.string_value = value;
    page[ adress ].push_back( _t );
}

double
CubePL0MemoryManager::get( MemoryAdress adress,  double index,
                           uint32_t met_id, KindOfVariable )
{
    ( void )met_id;
    vector< vector < CubePL0MemoryDuplet > >& page = memory.top();

    size_t _index = ( size_t )index;
    if ( page[ adress ].size() <= _index )
    {
        return 0.;
    }
    else
    {
        return page[ adress ][ _index ].double_value;
    }
}

string
CubePL0MemoryManager::get_as_string( MemoryAdress adress,  double index,
                                     uint32_t met_id, KindOfVariable )
{
    ( void )met_id;
    vector< vector < CubePL0MemoryDuplet > >& page   = memory.top();
    size_t                                    _index = ( size_t )index;
    if ( page[ adress ].size() <= _index )
    {
        return "";
    }
    else
    {
        return page[ adress ][ _index ].string_value;
    }
}


size_t
CubePL0MemoryManager::size_of( MemoryAdress adress,
                               uint32_t met_id, KindOfVariable )
{
    ( void )met_id;
    vector< vector < CubePL0MemoryDuplet > >& page = memory.top();
    return page[ adress ].size();
}
