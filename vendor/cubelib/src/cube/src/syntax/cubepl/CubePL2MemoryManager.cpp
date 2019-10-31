/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2018                                                **
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
#include <algorithm>

#include "CubePL2MemoryManager.h"
#include "CubePL2MemoryInitializer.h"
#include "CubePL2LocalMemoryManager.h"
#include "CubeError.h"


using namespace std;
using namespace cube;


CubePL2MemoryManager::CubePL2MemoryManager() : CubePLMemoryManager()
{
    cubepl_memory_initializer = new CubePL2MemoryInitializer( this );

    max_reserved_memory_size = 100;
    init();
    reserved_variables[ "cube::#mirrors" ]         = cubepl2::CUBE_NUM_MIRRORS;
    reserved_variables[ "cube::#metrics" ]         = cubepl2::CUBE_NUM_METRICS;
    reserved_variables[ "cube::#root::metrics" ]   = cubepl2::CUBE_NUM_ROOT_METRICS;
    reserved_variables[ "cube::#regions" ]         = cubepl2::CUBE_NUM_REGIONS;
    reserved_variables[ "cube::#callpaths" ]       = cubepl2::CUBE_NUM_CALLPATHS;
    reserved_variables[ "cube::#root::callpaths" ] = cubepl2::CUBE_NUM_ROOT_CALLPATHS;
    reserved_variables[ "cube::#locations" ]       = cubepl2::CUBE_NUM_LOCATIONS;
    reserved_variables[ "cube::#locationgroups" ]  = cubepl2::CUBE_NUM_LOCATION_GROUPS;
    reserved_variables[ "cube::#stns" ]            = cubepl2::CUBE_NUM_STNS;
    reserved_variables[ "cube::#rootstns" ]        = cubepl2::CUBE_NUM_ROOT_STNS;
    reserved_variables[ "cube::filename" ]         = cubepl2::CUBE_FILENAME;

    reserved_variables[ "cube::metric::uniq::name" ]     = cubepl2::CUBE_METRIC_UNIQ_NAME;
    reserved_variables[ "cube::metric::disp::name" ]     = cubepl2::CUBE_METRIC_DISP_NAME;
    reserved_variables[ "cube::metric::url" ]            = cubepl2::CUBE_METRIC_URL;
    reserved_variables[ "cube::metric::description" ]    = cubepl2::CUBE_METRIC_DESCRIPTION;
    reserved_variables[ "cube::metric::dtype" ]          = cubepl2::CUBE_METRIC_DTYPE;
    reserved_variables[ "cube::metric::uom" ]            = cubepl2::CUBE_METRIC_UOM;
    reserved_variables[ "cube::metric::expression" ]     = cubepl2::CUBE_METRIC_EXPRESSION;
    reserved_variables[ "cube::metric::initexpression" ] = cubepl2::CUBE_METRIC_INIT_EXPRESSION;
    reserved_variables[ "cube::metric::#children" ]      = cubepl2::CUBE_METRIC_NUM_CHILDREN;
    reserved_variables[ "cube::metric::parent::id" ]     = cubepl2::CUBE_METRIC_PARENT_ID;
    reserved_variables[ "cube::metric::children" ]       = cubepl2::CUBE_METRIC_CHILDREN;
    reserved_variables[ "cube::metric::enumeration" ]    = cubepl2::CUBE_METRIC_ENUMERATION;

    reserved_variables[ "cube::callpath::mod" ]         = cubepl2::CUBE_CALLPATH_MOD;
    reserved_variables[ "cube::callpath::line" ]        = cubepl2::CUBE_CALLPATH_LINE;
    reserved_variables[ "cube::callpath::#children" ]   = cubepl2::CUBE_CALLPATH_NUM_CHILDREN;
    reserved_variables[ "cube::callpath::children" ]    = cubepl2::CUBE_CALLPATH_CHILDREN;
    reserved_variables[ "cube::callpath::calleeid" ]    = cubepl2::CUBE_CALLPATH_CALLEE_ID;
    reserved_variables[ "cube::callpath::parent::id" ]  = cubepl2::CUBE_CALLPATH_PARENT_ID;
    reserved_variables[ "cube::callpath::enumeration" ] = cubepl2::CUBE_CALLPATH_ENUMERATION;


    reserved_variables[ "cube::region::name" ]          = cubepl2::CUBE_REGION_NAME;
    reserved_variables[ "cube::region::mangled::name" ] = cubepl2::CUBE_REGION_MANGLED_NAME;
    reserved_variables[ "cube::region::paradigm" ]      = cubepl2::CUBE_REGION_PARADIGM;
    reserved_variables[ "cube::region::role" ]          = cubepl2::CUBE_REGION_ROLE;
    reserved_variables[ "cube::region::url" ]           = cubepl2::CUBE_REGION_URL;
    reserved_variables[ "cube::region::description" ]   = cubepl2::CUBE_REGION_DESCRIPTION;
    reserved_variables[ "cube::region::mod" ]           = cubepl2::CUBE_REGION_MOD;
    reserved_variables[ "cube::region::begin::line" ]   = cubepl2::CUBE_REGION_BEGIN_LINE;
    reserved_variables[ "cube::region::end::line" ]     = cubepl2::CUBE_REGION_END_LINE;

    reserved_variables[ "cube::stn::name" ]            = cubepl2::CUBE_STN_NAME;
    reserved_variables[ "cube::stn::description" ]     = cubepl2::CUBE_STN_DESCRIPTION;
    reserved_variables[ "cube::stn::class" ]           = cubepl2::CUBE_STN_CLASS;
    reserved_variables[ "cube::stn::#children" ]       = cubepl2::CUBE_STN_NUM_CHILDREN;
    reserved_variables[ "cube::stn::children" ]        = cubepl2::CUBE_STN_ENUMERATION;
    reserved_variables[ "cube::stn::#locationgroups" ] = cubepl2::CUBE_STN_NUM_LOCATION_GROUPS;
    reserved_variables[ "cube::stn::locationgroups" ]  = cubepl2::CUBE_STN_LOCATION_GROUPS;
    reserved_variables[ "cube::stn::parent::id" ]      = cubepl2::CUBE_STN_PARENT_ID;
    reserved_variables[ "cube::stn::parent::sysid" ]   = cubepl2::CUBE_STN_PARENT_SYS_ID;

    reserved_variables[ "cube::locationgroup::name" ]          = cubepl2::CUBE_LOCATION_GROUP_NAME;
    reserved_variables[ "cube::locationgroup::parent::id" ]    = cubepl2::CUBE_LOCATION_GROUP_PARENT_ID;
    reserved_variables[ "cube::locationgroup::parent::sysid" ] = cubepl2::CUBE_LOCATION_GROUP_PARENT_SYS_ID;
    reserved_variables[ "cube::locationgroup::rank" ]          = cubepl2::CUBE_LOCATION_GROUP_RANK;
    reserved_variables[ "cube::locationgroup::type" ]          = cubepl2::CUBE_LOCATION_GROUP_TYPE;
    reserved_variables[ "cube::locationgroup::void" ]          = cubepl2::CUBE_LOCATION_GROUP_VOID;
    reserved_variables[ "cube::locationgroup::#locations" ]    = cubepl2::CUBE_LOCATION_GROUP_NUM_LOCATIONS;
    reserved_variables[ "cube::locationgroup::locations" ]     = cubepl2::CUBE_LOCATION_GROUP_LOCATIONS;

    reserved_variables[ "cube::location::name" ]          = cubepl2::CUBE_LOCATION_NAME;
    reserved_variables[ "cube::location::type" ]          = cubepl2::CUBE_LOCATION_TYPE;
    reserved_variables[ "cube::location::parent::id" ]    = cubepl2::CUBE_LOCATION_PARENT_ID;
    reserved_variables[ "cube::location::parent::sysid" ] = cubepl2::CUBE_LOCATION_PARENT_SYS_ID;
    reserved_variables[ "cube::location::rank" ]          = cubepl2::CUBE_LOCATION_RANK;
    reserved_variables[ "cube::location::void" ]          = cubepl2::CUBE_LOCATION_VOID;


    reserved_variables[ "cube::#locations::void" ]         = cubepl2::CUBE_NUM_VOID_LOCS;
    reserved_variables[ "cube::#locations::nonvoid" ]      = cubepl2::CUBE_NUM_NONVOID_LOCS;
    reserved_variables[ "cube::#locationgroups::void" ]    = cubepl2::CUBE_NUM_VOID_LGS;
    reserved_variables[ "cube::#locationgroups::nonvoid" ] = cubepl2::CUBE_NUM_NONVOID_LGS;
};

CubePL2MemoryManager::~CubePL2MemoryManager()
{
    clear_memory();
    for ( std::vector<CubePL2LocalMemoryManager*> ::iterator it = local_memory.begin(); it != local_memory.end(); ++it )
    {
        delete ( *it );
    }
};


MemoryAdress
CubePL2MemoryManager::register_variable( std::string    name,
                                         KindOfVariable var )
{
    size_t                                        _addr = 0;
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

    it = registered_global_variables.find( name );
    if ( it  != registered_global_variables.end() )
    {
        return ( *it ).second;
    }

    switch ( var )
    {
        case  CUBEPL_RESERVED_VARIABLE:
        {
            _addr = reserved_memory.size();
            reserved_memory.resize( _addr + 1 );
            reserved_variables[ name ] = _addr;
            break;
        }
        case  CUBEPL_VARIABLE:
        {
            _addr                        = page_size;
            registered_variables[ name ] = _addr;
            page_size++;
            for ( std::vector<CubePL2LocalMemoryManager*> ::iterator it = local_memory.begin(); it != local_memory.end(); ++it )
            {
                if ( ( *it ) != NULL )
                {
                    ( *it )->set_page_size( page_size );
                }
            }
            break;
        }
        case  CUBEPL_GLOBAL_VARIABLE:
        {
            _addr = global_memory.size();
            global_memory.resize( _addr + 1 );
            registered_global_variables[ name ] = _addr;
            break;
        }
        default:
            throw CubePLError( "Unknown type of CubePL variable." );
    }
    return _addr;
}


KindOfVariable
CubePL2MemoryManager::kind_of_variable( std::string name )
{
    std::map<std::string, MemoryAdress>::iterator it;
    it = reserved_variables.find( name );
    if ( it  != reserved_variables.end() )
    {
        return CUBEPL_RESERVED_VARIABLE;
    }
    it = registered_global_variables.find( name );
    if ( it  != registered_global_variables.end() )
    {
        return CUBEPL_GLOBAL_VARIABLE;
    }
    it = registered_variables.find( name );
    if ( it  != registered_variables.end() )
    {
        return CUBEPL_VARIABLE;
    }
    throw CubePLError( "Variable " + name + " is not registered yet" );
}


void
CubePL2MemoryManager::clear_memory()
{
    for ( std::vector<CubePL2LocalMemoryManager*> ::iterator it = local_memory.begin(); it != local_memory.end(); ++it )
    {
        if ( ( *it ) != NULL )
        {
            ( *it )->clear_memory();
        }
    }

    for ( std::vector< std::vector<CubePL2MemoryDuplet> >::iterator it = reserved_memory.begin(); it != reserved_memory.end(); ++it )
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
    for ( std::vector< std::vector<CubePL2MemoryDuplet> >::iterator it = global_memory.begin(); it != global_memory.end(); ++it )
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
    global_memory.clear();
    reserved_memory.clear();
    reserved_memory.resize( max_reserved_memory_size );
}


void
CubePL2MemoryManager::init()
{
    clear_memory();
    registered_variables.clear();
    registered_variables[ "calculation::metric::id" ]          = cubepl2::CALCULATION_METRIC_ID;
    registered_variables[ "calculation::callpath::id" ]        = cubepl2::CALCULATION_CALLPATH_ID;
    registered_variables[ "calculation::callpath::state" ]     = cubepl2::CALCULATION_CALLPATH_STATE;
    registered_variables[ "calculation::callpath::#elements" ] = cubepl2::CALCULATION_CALLPATH_NUM;
    registered_variables[ "calculation::region::id" ]          = cubepl2::CALCULATION_REGION_ID;
    registered_variables[ "calculation::region::#elements" ]   = cubepl2::CALCULATION_REGION_NUM;
    registered_variables[ "calculation::sysres::id" ]          = cubepl2::CALCULATION_SYSRES_ID;
    registered_variables[ "calculation::sysres::sysid" ]       = cubepl2::CALCULATION_SYSRES_SYS_ID;
    registered_variables[ "calculation::sysres::state" ]       = cubepl2::CALCULATION_SYSRES_STATE;
    registered_variables[ "calculation::sysres::kind" ]        = cubepl2::CALCULATION_SYSRES_KIND;
    registered_variables[ "calculation::sysres::#elements" ]   = cubepl2::CALCULATION_SYSRES_NUM;

    page_size = 11;
    for ( std::vector<CubePL2LocalMemoryManager*> ::iterator it = local_memory.begin(); it != local_memory.end(); ++it )
    {
        if ( ( *it ) != NULL )
        {
            ( *it )->set_page_size( page_size );
        }
    }
};

void
CubePL2MemoryManager::set_local_memory_for_metric( uint32_t met_id )
{
    if ( local_memory.size() <= met_id )
    {
        local_memory.resize( met_id + 1, NULL );
    }
    delete local_memory[ met_id ];
    local_memory[ met_id ] = new CubePL2LocalMemoryManager();
    local_memory[ met_id ]->set_page_size( page_size );
    local_memory[ met_id ]->set_row_size( row_size );
};


void
CubePL2MemoryManager::set_row_size( size_t _size )
{
    CubePLMemoryManager::set_row_size( _size );
    for ( std::vector<CubePL2LocalMemoryManager*> ::iterator it = local_memory.begin(); it != local_memory.end(); ++it )
    {
        if ( ( *it ) != NULL )
        {
            ( *it )->set_row_size( _size );
        }
    }
}




void
CubePL2MemoryManager::new_page()
{
    for ( std::vector<CubePL2LocalMemoryManager*> ::iterator it = local_memory.begin(); it != local_memory.end(); ++it )
    {
        if ( ( *it ) != NULL )
        {
            ( *it )->new_page();
        }
    }
};

void
CubePL2MemoryManager::throw_page()
{
    for ( std::vector<CubePL2LocalMemoryManager*> ::iterator it = local_memory.begin(); it != local_memory.end(); ++it )
    {
        if ( ( *it ) != NULL )
        {
            ( *it )->throw_page();
        }
    }
}




void
CubePL2MemoryManager::new_page( uint32_t met_id )
{
    local_memory[ met_id ]->new_page();
};

void
CubePL2MemoryManager::throw_page( uint32_t met_id )
{
    local_memory[ met_id ]->throw_page();
}



bool
CubePL2MemoryManager::defined( std::string name )
{
    std::map<std::string, MemoryAdress>::iterator it;
    it = reserved_variables.find( name );
    if ( it  != reserved_variables.end() )
    {
        return true;
    }
    it = registered_global_variables.find( name );
    if ( it  != registered_global_variables.end() )
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
CubePL2MemoryManager::clear_variable( MemoryAdress   adress,
                                      uint32_t       met_id,
                                      KindOfVariable var  )
{
    switch ( var )
    {
        case CUBEPL_VARIABLE:
        {
            local_memory[ met_id ]->clear_variable( adress );
            break;
        }

        case CUBEPL_RESERVED_VARIABLE:
        {
            for ( std::vector<CubePL2MemoryDuplet>::iterator it1 = reserved_memory[ adress ].begin(); it1 != reserved_memory[ adress ].end(); ++it1 )
            {
                delete[] ( *it1 ).row_value;
                ( *it1 ).row_value = NULL;
            }
            reserved_memory[ adress ].clear();
            break;
        }
        case  CUBEPL_GLOBAL_VARIABLE:
        {
            global_memory[ adress ].clear();
            for ( std::vector<CubePL2MemoryDuplet>::iterator it1 = global_memory[ adress ].begin(); it1 != global_memory[ adress ].end(); ++it1 )
            {
                delete[] ( *it1 ).row_value;
                ( *it1 ).row_value = NULL;
            }
            break;
        }
        default:
            throw CubePLError( "Unknown type of CubePL variable." );
    }
    ;
}

void
CubePL2MemoryManager::put( MemoryAdress   adress,
                           double         index,
                           double         value,
                           uint32_t       met_id,
                           KindOfVariable var   )
{
    size_t _index = ( size_t )index;
    switch ( var )
    {
        case CUBEPL_VARIABLE:
        {
            local_memory[ met_id ]->put( adress, index, value );
            break;
        }
        case CUBEPL_RESERVED_VARIABLE:
        {
            if (  reserved_memory.size() <= adress )
            {
                reserved_memory.resize( adress + 20 );
            }
            if (  reserved_memory[ adress ].size() <= _index )
            {
                reserved_memory[  adress ].resize( _index + 20 );
            }
            reserved_memory[ adress ][ _index ].double_value = value;
            delete[] reserved_memory[ adress ][ _index ].row_value;
            reserved_memory[ adress ][ _index ].row_value = NULL;
            reserved_memory[ adress ][ _index ].state     = CUBEPL_VALUE_DOUBLE;
            break;
        }
        case  CUBEPL_GLOBAL_VARIABLE:
        {
            if (  global_memory.size() <= adress )
            {
                global_memory.resize( adress + 20 );
            }
            if (  global_memory[ adress ].size() <= _index )
            {
                global_memory[  adress ].resize( _index + 20 );
            }
            global_memory[ adress ][ _index ].double_value = value;
            delete[] global_memory[ adress ][ _index ].row_value;
            global_memory[ adress ][ _index ].row_value = NULL;
            global_memory[ adress ][ _index ].state     = CUBEPL_VALUE_DOUBLE;
            break;
        }
        default:
            throw CubePLError( "Unknown type of CubePL variable." );
    }
    ;
};


void
CubePL2MemoryManager::put( MemoryAdress   adress,
                           double         index,
                           string         value,
                           uint32_t       met_id,
                           KindOfVariable var  )
{
    size_t _index = ( size_t )index;
    switch ( var )
    {
        case CUBEPL_VARIABLE:
        {
            local_memory[ met_id ]->put( adress, index, value );
            break;
        }
        case CUBEPL_RESERVED_VARIABLE:
        {
            if (  reserved_memory.size() <= adress )
            {
                reserved_memory.resize( adress + 20 );
            }
            if (  reserved_memory[  adress ].size() <= _index )
            {
                reserved_memory[  adress ].resize( _index + 20 );
            }
            reserved_memory[  adress ][ _index ].state        = CUBEPL_VALUE_STRING;
            reserved_memory[  adress ][ _index ].string_value = value;
            break;
        }
        case  CUBEPL_GLOBAL_VARIABLE:
        {
            if (  global_memory.size() <= adress )
            {
                global_memory.resize( adress + 20 );
            }
            if (  global_memory[  adress ].size() <= _index )
            {
                global_memory[  adress ].resize( _index + 20 );
            }
            global_memory[  adress ][ _index ].state        = CUBEPL_VALUE_STRING;
            global_memory[  adress ][ _index ].string_value = value;
            break;
        }
        default:
            throw CubePLError( "Unknown type of CubePL variable." );
    }
    ;
};

void
CubePL2MemoryManager::put( MemoryAdress   adress,
                           double         index,
                           double*        value,
                           uint32_t       met_id,
                           KindOfVariable var
                           )
{
    size_t _index = ( size_t )index;
    switch ( var )
    {
        case CUBEPL_VARIABLE:
        {
            local_memory[ met_id ]->put( adress, index, value );
            break;
        }
        case CUBEPL_RESERVED_VARIABLE:
        {
            if (  reserved_memory.size() <= adress )
            {
                reserved_memory.resize( adress + 20 );
            }
            if (  reserved_memory[  adress ].size() <= _index )
            {
                reserved_memory[  adress ].resize( _index + 20 );
            }
            reserved_memory[  adress ][ _index ].state = CUBEPL_VALUE_ROW;
            delete[] reserved_memory[  adress ][ _index ].row_value;
            reserved_memory[  adress ][ _index ].row_value = value;
            break;
        }
        case  CUBEPL_GLOBAL_VARIABLE:
        {
            if (  global_memory.size() <= adress )
            {
                global_memory.resize( adress + 20 );
            }
            if (  global_memory[  adress ].size() <= _index )
            {
                global_memory[  adress ].resize( _index + 20 );
            }
            global_memory[  adress ][ _index ].state = CUBEPL_VALUE_ROW;
            delete[] global_memory[  adress ][ _index ].row_value;
            global_memory[  adress ][ _index ].row_value = value;
            break;
        }
        default:
            throw CubePLError( "Unknown type of CubePL variable." );
    }
    ;
}




void
CubePL2MemoryManager::push_back( MemoryAdress   adress,
                                 double         value,
                                 uint32_t       met_id,
                                 KindOfVariable var )
{
    switch ( var )
    {
        case CUBEPL_VARIABLE:
        {
            local_memory[ met_id ]->push_back( adress, value );
            break;
        }
        case CUBEPL_RESERVED_VARIABLE:
        {
            if (  reserved_memory.size() <= adress )
            {
                reserved_memory.resize( adress + 20 );
            }

            CubePL2MemoryDuplet _t;
            _t.double_value = value;
            _t.state        = CUBEPL_VALUE_DOUBLE;

            reserved_memory[ adress ].push_back( _t );
            break;
        }
        case  CUBEPL_GLOBAL_VARIABLE:
        {
            if (  global_memory.size() <= adress )
            {
                global_memory.resize( adress + 20 );
            }
            CubePL2MemoryDuplet _t;
            _t.double_value = value;
            _t.state        = CUBEPL_VALUE_DOUBLE;

            global_memory[ adress ].push_back( _t );
            break;
        }
        default:
            throw CubePLError( "Unknown type of CubePL variable." );
    }
    ;
}

void
CubePL2MemoryManager::push_back( MemoryAdress   adress,
                                 string         value,
                                 uint32_t       met_id,
                                 KindOfVariable var )
{
    switch ( var )
    {
        case CUBEPL_VARIABLE:
        {
            local_memory[ met_id ]->push_back( adress,  value );
            break;
        }
        case CUBEPL_RESERVED_VARIABLE:
        {
            if (  reserved_memory.size() <= adress )
            {
                reserved_memory.resize( adress + 20 );
            }

            CubePL2MemoryDuplet _t;
            _t.string_value = value;
            _t.state        = CUBEPL_VALUE_STRING;
            reserved_memory[ adress ].push_back( _t );
            break;
        }
        case  CUBEPL_GLOBAL_VARIABLE:
        {
            if (  global_memory.size() <= adress )
            {
                global_memory.resize( adress + 20 );
            }

            CubePL2MemoryDuplet _t;
            _t.string_value = value;
            _t.state        = CUBEPL_VALUE_STRING;
            global_memory[ adress ].push_back( _t );
            break;
        }
        default:
            throw CubePLError( "Unknown type of CubePL variable." );
    }
}

double
CubePL2MemoryManager::get( MemoryAdress   adress,
                           double         index,
                           uint32_t       met_id,
                           KindOfVariable var   )
{
    size_t _index = ( size_t )index;
    switch ( var )
    {
        case CUBEPL_VARIABLE:
        {
            return local_memory[ met_id ]->get( adress, index );
        }
        case CUBEPL_RESERVED_VARIABLE:
        {
            if ( ( reserved_memory.size() <= adress ) || ( reserved_memory[ adress ].size() <= _index ) )
            {
                return 0.;
            }
            else
            {
                CubePL2MemoryDuplet& _t =  reserved_memory[ adress ][ _index ];
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
        case  CUBEPL_GLOBAL_VARIABLE:
        {
            if ( ( global_memory.size() <= adress ) || ( global_memory[ adress ].size() <= _index ) )
            {
                return 0.;
            }
            else
            {
                CubePL2MemoryDuplet& _t =  global_memory[ adress ][ _index ];
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
        default:
            throw CubePLError( "Unknown type of CubePL variable." );
    }
}

string
CubePL2MemoryManager::get_as_string( MemoryAdress   adress,
                                     double         index,
                                     uint32_t       met_id,
                                     KindOfVariable var  )
{
    size_t _index = ( size_t )index;

    switch ( var )
    {
        case CUBEPL_VARIABLE:
        {
            return local_memory[ met_id ]->get_as_string( adress, index );
        }
        case CUBEPL_RESERVED_VARIABLE:
        {
            if ( ( reserved_memory.size() <= adress ) || ( reserved_memory[ adress ].size() <= _index ) )
            {
                return "";
            }
            else
            {
                CubePL2MemoryDuplet& _t =  reserved_memory[ adress ][ _index ];
                if ( _t.state == CUBEPL_VALUE_DOUBLE )   // convert to string if possible
                {
                    stringstream sstr;
                    sstr <<  setprecision( 14 ) <<  _t.double_value;
                    sstr >> _t.string_value;
                    _t.state = CUBEPL_VALUE_EQUAL;
                }
                return _t.string_value;
            }
        }
        case  CUBEPL_GLOBAL_VARIABLE:
        {
            if ( ( global_memory.size() <= adress ) || ( global_memory[ adress ].size() <= _index ) )
            {
                return "";
            }
            else
            {
                CubePL2MemoryDuplet& _t =  global_memory[ adress ][ _index ];
                if ( _t.state == CUBEPL_VALUE_DOUBLE )   // convert to string if possible
                {
                    stringstream sstr;
                    sstr <<  setprecision( 14 ) <<  _t.double_value;
                    sstr >> _t.string_value;
                    _t.state = CUBEPL_VALUE_EQUAL;
                }
                return _t.string_value;
            }
        }
        default:
            throw CubePLError( "Unknown type of CubePL variable." );
    }
}

double*
CubePL2MemoryManager::get_row( MemoryAdress   adress,
                               double         index,
                               uint32_t       met_id,
                               KindOfVariable var )
{
    size_t _index = ( size_t )index;
    switch ( var )
    {
        case CUBEPL_VARIABLE:
        {
            return local_memory[ met_id ]->get_row( adress, index );
        }
        case CUBEPL_RESERVED_VARIABLE:
        {
            if ( ( reserved_memory.size() <= adress ) || ( reserved_memory[ adress ].size() <= _index ) )
            {
                return NULL;
            }
            else
            {
                CubePL2MemoryDuplet& _t =  reserved_memory[ adress ][ _index ];
                if ( _t.state != CUBEPL_VALUE_ROW && _t.row_value == NULL ) // convert to double if possible
                {
                    double  value = _t.double_value;
                    double* _row  = new double[ row_size ];
                    for ( size_t i = 0; i < row_size; i++ )
                    {
                        _row[ i ] = value;
                    }
                    _t.row_value = _row;
                    _t.state     = CUBEPL_VALUE_ROW;
                }
                return _t.row_value;
            }
        }
        case  CUBEPL_GLOBAL_VARIABLE:
        {
            if ( ( global_memory.size() <= adress ) || ( global_memory[ adress ].size() <= _index ) )
            {
                return NULL;
            }
            else
            {
                CubePL2MemoryDuplet& _t =  global_memory[ adress ][ _index ];
                if ( _t.state != CUBEPL_VALUE_ROW && _t.row_value == NULL ) // convert to double if possible
                {
                    double  value = _t.double_value;
                    double* _row  = new double[ row_size ];
                    for ( size_t i = 0; i < row_size; i++ )
                    {
                        _row[ i ] = value;
                    }
                    _t.row_value = _row;
                    _t.state     = CUBEPL_VALUE_ROW;
                }
                return _t.row_value;
            }
        }
        default:
            throw CubePLError( "Unknown type of CubePL variable." );
    }
}





size_t
CubePL2MemoryManager::size_of( MemoryAdress   adress,
                               uint32_t       met_id,
                               KindOfVariable var )
{
    if ( var == CUBEPL_VARIABLE )
    {
        return local_memory[ met_id ]->size_of( adress );
    }
    if ( var == CUBEPL_RESERVED_VARIABLE )
    {
        return reserved_memory[ adress ].size();
    }
    if ( var == CUBEPL_GLOBAL_VARIABLE )
    {
        return global_memory[ adress ].size();
    }
    throw CubePLError( "Unknown type of CubePL variable." );
}

CubePL2StateOfCubePLVariable
CubePL2MemoryManager::type( MemoryAdress   adress,
                            double         index,
                            uint32_t       met_id,
                            KindOfVariable var )
{
    size_t _index = ( size_t )index;

    switch ( var )
    {
        case CUBEPL_VARIABLE:
        {
            return local_memory[ met_id ]->type( adress, index );
        }
        case CUBEPL_RESERVED_VARIABLE:
        {
            if ( reserved_memory[ adress ].size() <= _index )
            {
                return CUBEPL_VALUE_DOUBLE;
            }
            else
            {
                CubePL2MemoryDuplet& _t =  reserved_memory[ adress ][ _index ];
                return _t.state;
            }
        }
        case  CUBEPL_GLOBAL_VARIABLE:
        {
            if ( global_memory[ adress ].size() <= _index )
            {
                return CUBEPL_VALUE_DOUBLE;
            }
            else
            {
                CubePL2MemoryDuplet& _t =  global_memory[ adress ][ _index ];
                return _t.state;
            }
        }
        default:
            throw CubePLError( "Unknown type of CubePL variable." );
    }
}
