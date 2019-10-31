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


#ifndef __CUBEPL2_MEMORY_MANAGER_H
#define __CUBEPL2_MEMORY_MANAGER_H 0

#include <vector>
#include <stack>
#include <iostream>
#include <float.h>
#include <cmath>
#include <map>
#include "CubePL1MemoryManager.h"

namespace cubepl2
{
enum CubePL2ReservedVariables
{
    CUBE_NUM_MIRRORS                  = 0,
    CUBE_NUM_METRICS                  = 1,
    CUBE_NUM_ROOT_METRICS             = 2,
    CUBE_NUM_REGIONS                  = 3,
    CUBE_NUM_CALLPATHS                = 4,
    CUBE_NUM_ROOT_CALLPATHS           = 5,
    CUBE_NUM_LOCATIONS                = 6,
    CUBE_NUM_LOCATION_GROUPS          = 7,
    CUBE_NUM_STNS                     = 8,
    CUBE_NUM_ROOT_STNS                = 9,
    CUBE_FILENAME                     = 10,

    CUBE_METRIC_UNIQ_NAME             = 21,
    CUBE_METRIC_DISP_NAME             = 22,
    CUBE_METRIC_URL                   = 23,
    CUBE_METRIC_DESCRIPTION           = 24,
    CUBE_METRIC_DTYPE                 = 25,
    CUBE_METRIC_UOM                   = 26,
    CUBE_METRIC_EXPRESSION            = 27,
    CUBE_METRIC_INIT_EXPRESSION       = 28,
    CUBE_METRIC_NUM_CHILDREN          = 29,
    CUBE_METRIC_PARENT_ID             = 30,
    CUBE_METRIC_CHILDREN              = 31,
    CUBE_METRIC_ENUMERATION           = 32,

    CUBE_CALLPATH_MOD                 = 40,
    CUBE_CALLPATH_LINE                = 41,
    CUBE_CALLPATH_NUM_CHILDREN        = 42,
    CUBE_CALLPATH_CHILDREN            = 43,
    CUBE_CALLPATH_CALLEE_ID           = 44,
    CUBE_CALLPATH_PARENT_ID           = 45,
    CUBE_CALLPATH_ENUMERATION         = 46,


    CUBE_REGION_NAME                  = 50,
    CUBE_REGION_MANGLED_NAME          = 51,
    CUBE_REGION_PARADIGM              = 52,
    CUBE_REGION_ROLE                  = 53,
    CUBE_REGION_URL                   = 54,
    CUBE_REGION_DESCRIPTION           = 55,
    CUBE_REGION_MOD                   = 56,
    CUBE_REGION_BEGIN_LINE            = 57,
    CUBE_REGION_END_LINE              = 58,

    CUBE_STN_NAME                     = 60,
    CUBE_STN_DESCRIPTION              = 61,
    CUBE_STN_CLASS                    = 62,
    CUBE_STN_NUM_CHILDREN             = 63,
    CUBE_STN_ENUMERATION              = 64,
    CUBE_STN_NUM_LOCATION_GROUPS      = 65,
    CUBE_STN_LOCATION_GROUPS          = 66,
    CUBE_STN_PARENT_ID                = 67,
    CUBE_STN_PARENT_SYS_ID            = 68,

    CUBE_LOCATION_GROUP_NAME          = 70,
    CUBE_LOCATION_GROUP_PARENT_ID     = 71,
    CUBE_LOCATION_GROUP_PARENT_SYS_ID = 72,
    CUBE_LOCATION_GROUP_RANK          = 73,
    CUBE_LOCATION_GROUP_TYPE          = 74,
    CUBE_LOCATION_GROUP_VOID          = 75,
    CUBE_LOCATION_GROUP_NUM_LOCATIONS = 76,
    CUBE_LOCATION_GROUP_LOCATIONS     = 77,

    CUBE_LOCATION_NAME                = 80,
    CUBE_LOCATION_TYPE                = 81,
    CUBE_LOCATION_PARENT_ID           = 82,
    CUBE_LOCATION_PARENT_SYS_ID       = 83,
    CUBE_LOCATION_RANK                = 84,
    CUBE_LOCATION_VOID                = 85,


    CUBE_NUM_VOID_LOCS                = 90,
    CUBE_NUM_NONVOID_LOCS             = 91,
    CUBE_NUM_VOID_LGS                 = 92,
    CUBE_NUM_NONVOID_LGS              = 93
};

enum CubePL2RegisteredVariables
{
    CALCULATION_METRIC_ID      = 0,
    CALCULATION_CALLPATH_ID    = 1,
    CALCULATION_CALLPATH_STATE = 2,
    CALCULATION_CALLPATH_NUM   = 3,
    CALCULATION_REGION_ID      = 4,
    CALCULATION_REGION_NUM     = 5,
    CALCULATION_SYSRES_ID      = 6,
    CALCULATION_SYSRES_STATE   = 7,
    CALCULATION_SYSRES_SYS_ID  = 8,
    CALCULATION_SYSRES_KIND    = 9,
    CALCULATION_SYSRES_NUM     = 10
};
};


namespace cube
{
typedef MemoryAdress                 CubePL2MemoryAdress;
typedef CubePL1StateOfCubePLVariable CubePL2StateOfCubePLVariable;
typedef KindOfVariable               CubePL2KindOfVariable;




class CubePL2MemoryDuplet
{
public:
    std::string                  string_value;
    double                       double_value;
    double*                      row_value;
    CubePL2StateOfCubePLVariable state;

    CubePL2MemoryDuplet()
    {
        string_value = "";
        double_value = 0.;
        row_value    = NULL;
        state        = CUBEPL_VALUE_DOUBLE;
    };
};


class CubePL2LocalMemoryManager;



class CubePL2MemoryManager : public CubePLMemoryManager
{
private:
    CubePL2MemoryDuplet init_value;

    std::vector< CubePL2LocalMemoryManager* > local_memory;

    std::vector< std::vector<CubePL2MemoryDuplet> > global_memory;       // variables here are exisiting from metric call to metric call... they are global // kept for future use....
    std::vector< std::vector<CubePL2MemoryDuplet> > reserved_memory;     // here are reserved variables stored. No paging. They supposed to be  "readonly"

    std::map<std::string, CubePL2MemoryAdress > reserved_variables;
    std::map<std::string, CubePL2MemoryAdress > registered_variables;
    std::map<std::string, CubePL2MemoryAdress > registered_global_variables;

    size_t page_size;                                                           // stores   size of the page (number of variables, which do exist over whole cube)
    size_t max_reserved_memory_size;                                            // stores   size of the page (number of variables, which do exist over whole cube)


    void
    clear_memory();                     // destroys every "row" stored in memory

public:
    CubePL2MemoryManager();

    virtual
    ~CubePL2MemoryManager();
    virtual
    void
    init();

    void
    set_row_size( size_t _size );


    virtual
    void
    set_local_memory_for_metric( uint32_t id );


    virtual
    void
    new_page();
    virtual
    void
    throw_page();

    virtual
    void
        new_page( uint32_t );

    virtual
    void
        throw_page( uint32_t );

    virtual
    CubePL2MemoryAdress
    register_variable( std::string           name,
                       CubePL2KindOfVariable var = CUBEPL_VARIABLE );

    virtual
    void
        clear_variable( CubePL2MemoryAdress,
                        uint32_t,
                        CubePL2KindOfVariable var = CUBEPL_VARIABLE );

    virtual
    void
        put( CubePL2MemoryAdress,
             double,
             double,
             uint32_t,
             CubePL2KindOfVariable var = CUBEPL_VARIABLE
             );
    virtual
    void
        put( CubePL2MemoryAdress,
             double,
             std::string,
             uint32_t,
             CubePL2KindOfVariable var = CUBEPL_VARIABLE );

    virtual
    void
        put( MemoryAdress,
             double,
             double*,
             uint32_t,
             KindOfVariable var = CUBEPL_VARIABLE
             );


    virtual
    void
        push_back( CubePL2MemoryAdress,
                   double,
                   uint32_t,
                   CubePL2KindOfVariable var = CUBEPL_VARIABLE );
    virtual
    void
        push_back( CubePL2MemoryAdress,
                   std::string,
                   uint32_t,
                   CubePL2KindOfVariable var = CUBEPL_VARIABLE );

    virtual
    double
        get( CubePL2MemoryAdress,
             double,
             uint32_t,
             CubePL2KindOfVariable var = CUBEPL_VARIABLE  );

    virtual
    double*
        get_row( MemoryAdress,
                 double,
                 uint32_t,
                 KindOfVariable var = CUBEPL_VARIABLE  );

    virtual
    std::string
        get_as_string( CubePL2MemoryAdress,
                       double,
                       uint32_t,
                       CubePL2KindOfVariable var = CUBEPL_VARIABLE  );
    virtual
    size_t
        size_of( CubePL2MemoryAdress,
                 uint32_t,
                 CubePL2KindOfVariable = CUBEPL_VARIABLE );
    virtual
    bool
    defined( std::string  );

    virtual
    CubePL2KindOfVariable
    kind_of_variable( std::string name );

    virtual
    CubePL2StateOfCubePLVariable
        type( MemoryAdress, double,
              uint32_t,  KindOfVariable );
};
}

#endif
