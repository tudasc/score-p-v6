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


#ifndef __CUBEPL0_MEMORY_MANAGER_H
#define __CUBEPL0_MEMORY_MANAGER_H 0

#include <vector>
#include <stack>
#include <iostream>
#include <float.h>
#include <cmath>
#include <map>
#include "CubePLMemoryManager.h"

namespace cubepl0
{
enum CubePL0ReservedVariables
{
    CUBE_NUM_MIRRORS                  = 0,
    CUBE_NUM_METRICS                  = 1,
    CUBE_NUM_ROOT_METRICS             = 2,
    CUBE_NUM_REGIONS                  = 3,
    CUBE_NUM_CALLPATHS                = 4,
    CUBE_NUM_ROOT_CALLPATHS           = 5,
    CUBE_NUM_THREADS                  = 6,
    CUBE_FILENAME                     = 7,

    CALCULATION_METRIC_UNIQ_NAME      = 8,
    CALCULATION_METRIC_DISP_NAME      = 9,
    CALCULATION_METRIC_URL            = 10,
    CALCULATION_METRIC_DESCRIPTION    = 11,
    CALCULATION_METRIC_DTYPE          = 12,
    CALCULATION_METRIC_UOM            = 13,
    CALCULATION_METRIC_EXPRESSION     = 14,
    CALCULATION_METRIC_ID             = 15,
    CALCULATION_METRIC_NUM_CHILDREN   = 16,

    CALCULATION_CALLPATH_MOD          = 17,
    CALCULATION_CALLPATH_LINE         = 18,
    CALCULATION_CALLPATH_ID           = 19,
    CALCULATION_CALLPATH_NUM_CHILDREN = 20,

    CALCULATION_REGION_NAME           = 21,
    CALCULATION_REGION_URL            = 22,
    CALCULATION_REGION_DESCRIPTION    = 23,
    CALCULATION_REGION_MOD            = 24,
    CALCULATION_REGION_BEGIN_LINE     = 25,
    CALCULATION_REGION_END_LINE       = 26,
    CALCULATION_REGION_ID             = 27,

    CALCULATION_SYSRES_NAME           = 28,
    CALCULATION_SYSRES_ID             = 29,


    CUBE_NUM_VOID_PROCS               = 30,
    CUBE_NUM_VOID_THRDS               = 31,
    CUBE_NUM_NONVOID_PROCS            = 32,
    CUBE_NUM_NONVOID_THRDS            = 33,

    CALCULATION_SYSRES_KIND           = 34,
    CALCULATION_SYSRES_RANK           = 35,

    CALCULATION_PROCESS_VOID          = 36,
    CALCULATION_THREAD_VOID           = 37
};
};

namespace cube
{
typedef MemoryAdress CubePL0MemoryAdress;




class CubePL0MemoryDuplet
{
public:
    std::string string_value;
    double      double_value;


    CubePL0MemoryDuplet()
    {
        string_value = "";
        double_value = 0.;
    };
};






class CubePL0MemoryManager : public CubePLMemoryManager
{
private:
    std::stack< std::vector< std::vector<CubePL0MemoryDuplet> > > memory;
    std::map<std::string, CubePL0MemoryAdress >                   reserved_variables;
    std::map<std::string, CubePL0MemoryAdress >                   registered_variables;

public:
    CubePL0MemoryManager();
    virtual
    ~CubePL0MemoryManager();
    virtual
    void
    init()
    {
        std::vector < std::vector < CubePL0MemoryDuplet> > _init_page;
        memory.push( _init_page );
        memory.top().resize( reserved_variables.size() );
        registered_variables.clear();
    };
    virtual
    void
    new_page( uint32_t id = 0 )
    {
        ( void )id;
        std::vector< std::vector<CubePL0MemoryDuplet> > page = memory.top();
//      page.resize( reserved_variables.size() + registered_variables.size() );
        memory.push( page );
    };

    void
    throw_page( uint32_t id = 0 )
    {
        ( void )id;
        if ( memory.size() >= 1 )
        {
            memory.pop();
        }
    }
    virtual
    bool
    defined( std::string  );

    virtual
    CubePL0MemoryAdress
    register_variable( std::string    name,
                       KindOfVariable var = CUBEPL_VARIABLE );



    virtual
    void
        clear_variable( CubePL0MemoryAdress,
                        uint32_t id        = 0,
                        KindOfVariable var = CUBEPL_VARIABLE );

    void
        put( CubePL0MemoryAdress,
             double,
             double,
             uint32_t id        = 0,
             KindOfVariable var = CUBEPL_VARIABLE );
    virtual
    void
        put( CubePL0MemoryAdress,
             double,
             std::string,
             uint32_t id        = 0,
             KindOfVariable var = CUBEPL_VARIABLE );

    virtual
    void
        put( MemoryAdress,
             double,
             double*,
             uint32_t id        = 0,
             KindOfVariable var = CUBEPL_VARIABLE
             );



    virtual
    void
        push_back( CubePL0MemoryAdress,
                   double,
                   uint32_t id        = 0,
                   KindOfVariable var = CUBEPL_VARIABLE );
    virtual
    void
        push_back( CubePL0MemoryAdress,
                   std::string,
                   uint32_t id        = 0,
                   KindOfVariable var = CUBEPL_VARIABLE );


    virtual
    double
        get( CubePL0MemoryAdress, double,
             uint32_t id        = 0,
             KindOfVariable var = CUBEPL_VARIABLE );


    virtual
    double*
    get_row( MemoryAdress,
             double,
             uint32_t,
             KindOfVariable )
    {
        return NULL;
    };

    virtual
    double
    get_as_number( CubePL0MemoryAdress adress, double index,
                   uint32_t id        = 0,
                   KindOfVariable var = CUBEPL_VARIABLE )
    {
        ( void )id;
        return get( adress, index, var );
    };


    virtual
    std::string
        get_as_string( CubePL0MemoryAdress, double,
                       uint32_t id        = 0,
                       KindOfVariable var = CUBEPL_VARIABLE  );

    virtual
    size_t
        size_of( CubePL0MemoryAdress,
                 uint32_t id = 0, KindOfVariable = CUBEPL_VARIABLE );



    virtual
    KindOfVariable
    kind_of_variable( std::string )
    {
        return CUBEPL_VARIABLE;
    };
};
}

#endif
