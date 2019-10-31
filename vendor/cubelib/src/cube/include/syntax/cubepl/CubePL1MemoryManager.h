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


#ifndef __CUBEPL1_MEMORY_MANAGER_H
#define __CUBEPL1_MEMORY_MANAGER_H 0

#include <vector>
#include <stack>
#include <iostream>
#include <float.h>
#include <cmath>
#include <map>
#include "CubePLMemoryManager.h"

namespace cubepl1
{
enum CubePL1ReservedVariables
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
    CUBE_REGION_URL                   = 51,
    CUBE_REGION_DESCRIPTION           = 52,
    CUBE_REGION_MOD                   = 53,
    CUBE_REGION_BEGIN_LINE            = 54,
    CUBE_REGION_END_LINE              = 55,

    CUBE_STN_NAME                     = 60,
    CUBE_STN_DESCRIPTION              = 61,
    CUBE_STN_CLASS                    = 62,
    CUBE_STN_NUM_CHILDREN             = 63,
    CUBE_STN_ENUMERATION              = 64,
    CUBE_STN_NUM_LOCATION_GROUPS      = 65,
    CUBE_STN_LOCATION_GROUPS          = 66,
    CUBE_STN_PARENT_ID                = 67,

    CUBE_LOCATION_GROUP_NAME          = 70,
    CUBE_LOCATION_GROUP_PARENT_ID     = 71,
    CUBE_LOCATION_GROUP_RANK          = 72,
    CUBE_LOCATION_GROUP_TYPE          = 73,
    CUBE_LOCATION_GROUP_VOID          = 74,
    CUBE_LOCATION_GROUP_NUM_LOCATIONS = 75,
    CUBE_LOCATION_GROUP_LOCATIONS     = 76,

    CUBE_LOCATION_NAME                = 80,
    CUBE_LOCATION_TYPE                = 81,
    CUBE_LOCATION_PARENT_ID           = 82,
    CUBE_LOCATION_RANK                = 83,
    CUBE_LOCATION_VOID                = 84,


    CUBE_NUM_VOID_LOCS                = 90,
    CUBE_NUM_NONVOID_LOCS             = 91,
    CUBE_NUM_VOID_LGS                 = 92,
    CUBE_NUM_NONVOID_LGS              = 93
};

enum CubePL1RegisteredVariables
{
    CALCULATION_METRIC_ID   = 0,
    CALCULATION_CALLPATH_ID = 1,
    CALCULATION_REGION_ID   = 2,
    CALCULATION_SYSRES_ID   = 3,
    CALCULATION_SYSRES_KIND = 4
};
};


namespace cube
{
typedef MemoryAdress                CubePL1MemoryAdress;
typedef CubePLStateOfCubePLVariable CubePL1StateOfCubePLVariable;
typedef KindOfVariable              CubePL1KindOfVariable;




class CubePL1MemoryDuplet
{
public:
    std::string                  string_value;
    double                       double_value;
    double*                      row_value;
    CubePL1StateOfCubePLVariable state;

    CubePL1MemoryDuplet()
    {
        string_value = "";
        double_value = 0.;
        row_value    = NULL;
        state        = CUBEPL_VALUE_DOUBLE;
    };
};






class CubePL1MemoryManager : public CubePLMemoryManager
{
private:

    CubePL1MemoryDuplet init_value;

    std::vector< std::vector<CubePL1MemoryDuplet> > memory;              // normal memory. Every new expression calculation allocates new "page" and moves stack pointer
    std::stack< size_t >                            memory_stack;

    std::vector< std::vector<CubePL1MemoryDuplet> > global_memory;       // variables here are exisiting from metric call to metric call... they are global // kept for future use....
    std::vector< std::vector<CubePL1MemoryDuplet> > reserved_memory;     // here are reserved variables stored. No paging. They supposed to be  "readonly"

    std::map<std::string, CubePL1MemoryAdress > reserved_variables;
    std::map<std::string, CubePL1MemoryAdress > registered_variables;
    std::map<std::string, CubePL1MemoryAdress > registered_global_variables;

    size_t page_size;                                                           // stores   size of the page (number of variables, which do exist over whole cube)
    size_t max_reserved_memory_size;                                            // stores   size of the page (number of variables, which do exist over whole cube)


    void
    clear_memory();                     // destroys every "row" stored in memory



public:
    CubePL1MemoryManager();

    virtual
    ~CubePL1MemoryManager();
    virtual
    void
    init();
    virtual
    void
    new_page( uint32_t id = 0 );
    virtual
    void
    throw_page( uint32_t id = 0 );

    virtual
    CubePL1MemoryAdress
    register_variable( std::string           name,
                       CubePL1KindOfVariable var = CUBEPL_VARIABLE );

    virtual
    void
        clear_variable( CubePL1MemoryAdress,
                        uint32_t id = 0,
                        CubePL1KindOfVariable var = CUBEPL_VARIABLE );

    virtual
    void
        put( CubePL1MemoryAdress,
             double,
             double,
             uint32_t id = 0,
             CubePL1KindOfVariable var = CUBEPL_VARIABLE
             );
    virtual
    void
        put( CubePL1MemoryAdress,
             double,
             std::string,
             uint32_t id = 0,
             CubePL1KindOfVariable var = CUBEPL_VARIABLE );

    virtual
    void
        put( MemoryAdress,
             double,
             double*,
             uint32_t id = 0,
             KindOfVariable var = CUBEPL_VARIABLE
             );

    virtual
    void
        push_back( CubePL1MemoryAdress,
                   double,
                   uint32_t id = 0,
                   CubePL1KindOfVariable var = CUBEPL_VARIABLE );
    virtual
    void
        push_back( CubePL1MemoryAdress,
                   std::string,
                   uint32_t id = 0,
                   CubePL1KindOfVariable var = CUBEPL_VARIABLE );

    virtual
    double
        get( CubePL1MemoryAdress,
             double,
             uint32_t id = 0,
             CubePL1KindOfVariable var = CUBEPL_VARIABLE  );

    virtual
    double*
        get_row( MemoryAdress,
                 double,
                 uint32_t id = 0,
                 KindOfVariable var = CUBEPL_VARIABLE  );



    virtual
    std::string
        get_as_string( CubePL1MemoryAdress,
                       double,
                       uint32_t id = 0,
                       CubePL1KindOfVariable var = CUBEPL_VARIABLE  );
    virtual
    size_t
        size_of( CubePL1MemoryAdress,
                 uint32_t id = 0, CubePL1KindOfVariable = CUBEPL_VARIABLE );
    virtual
    bool
    defined( std::string  );

    virtual
    CubePL1KindOfVariable
    kind_of_variable( std::string name );


    virtual
    CubePL1StateOfCubePLVariable
        type( MemoryAdress, double,
              uint32_t id, KindOfVariable );
};
}

#endif
