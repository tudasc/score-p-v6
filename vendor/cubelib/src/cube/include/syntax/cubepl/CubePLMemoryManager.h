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


#ifndef __CUBEPL_MEMORY_MANAGER_H
#define __CUBEPL_MEMORY_MANAGER_H 0

#include <vector>
#include <stack>
#include <iostream>
#include <float.h>
#include <cmath>
#include <map>

#include "CubePLMemoryInitializer.h"


namespace cube
{
class CubePLMemoryInitializer;

typedef unsigned MemoryAdress;
enum  CubePLStateOfCubePLVariable { CUBEPL_VALUE_EQUAL, CUBEPL_VALUE_DOUBLE, CUBEPL_VALUE_STRING, CUBEPL_VALUE_ROW };
enum  KindOfVariable { CUBEPL_GLOBAL_VARIABLE, CUBEPL_VARIABLE, CUBEPL_RESERVED_VARIABLE };




class CubePLMemoryManager
{
protected:
    CubePLMemoryInitializer* cubepl_memory_initializer;
    size_t                   row_size;


public:

    virtual
    ~CubePLMemoryManager();


    virtual
    CubePLMemoryInitializer*
    get_memory_initializer()
    {
        return cubepl_memory_initializer;
    };


    inline
    void
    set_row_size( size_t _size )
    {
        row_size = _size;
    };


    virtual
    inline
    void
    set_local_memory_for_metric( uint32_t id )
    {
        ( void )id;
    }

    virtual
    void
    init() = 0;

    virtual
    void
    new_page(
        uint32_t id = 0 ) = 0;

    virtual
    void
    throw_page(
        uint32_t id = 0 ) = 0;

    virtual
    MemoryAdress
    register_variable( std::string    name,
                       KindOfVariable var = CUBEPL_VARIABLE ) = 0;

    virtual
    void
        clear_variable( MemoryAdress,
                        uint32_t id = 0,
                        KindOfVariable var = CUBEPL_VARIABLE ) = 0;

    virtual
    void
        put( MemoryAdress,
             double,
             double,
             uint32_t id = 0,
             KindOfVariable var = CUBEPL_VARIABLE
             ) = 0;

    virtual
    void
        put( MemoryAdress,
             double,
             double*,
             uint32_t id = 0,
             KindOfVariable var = CUBEPL_VARIABLE
             ) = 0;



    virtual
    void
        put( MemoryAdress,
             double,
             std::string,
             uint32_t id = 0,
             KindOfVariable var = CUBEPL_VARIABLE ) = 0;

    virtual
    void
        push_back( MemoryAdress,
                   double,
                   uint32_t id = 0,
                   KindOfVariable var = CUBEPL_VARIABLE ) = 0;

    virtual
    void
        push_back( MemoryAdress,
                   std::string,
                   uint32_t id = 0,
                   KindOfVariable var = CUBEPL_VARIABLE ) = 0;

    virtual
    double
        get( MemoryAdress,
             double,
             uint32_t id = 0,
             KindOfVariable var = CUBEPL_VARIABLE  ) = 0;
    virtual
    double*
        get_row( MemoryAdress,
                 double,
                 uint32_t id = 0,
                 KindOfVariable var = CUBEPL_VARIABLE  ) = 0;

    virtual
    double
    get_as_number( MemoryAdress   adress,
                   double         index,
                   uint32_t       id = 0,
                   KindOfVariable var = CUBEPL_VARIABLE  )
    {
	( void ) id;
        return get( adress, index, var );
    };
    virtual
    std::string
        get_as_string( MemoryAdress,
                       double,
                       uint32_t id = 0,
                       KindOfVariable var = CUBEPL_VARIABLE  ) = 0;

    virtual
    size_t
        size_of( MemoryAdress,
                 uint32_t id = 0, KindOfVariable = CUBEPL_VARIABLE ) = 0;

    virtual
    bool
    defined( std::string  ) = 0;


    virtual
    KindOfVariable
    kind_of_variable( std::string name ) = 0;


    virtual
    CubePLStateOfCubePLVariable
    type( MemoryAdress, double,
          uint32_t, KindOfVariable )
    {
        return CUBEPL_VALUE_DOUBLE;
    };
};
}

#endif
