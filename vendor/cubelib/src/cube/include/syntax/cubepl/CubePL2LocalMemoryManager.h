/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016                                                     **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


#ifndef __CUBEPL2_LOCAL_MEMORY_MANAGER_H
#define __CUBEPL2_LOCAL_MEMORY_MANAGER_H 0

#include <vector>
#include <stack>
#include <iostream>
#include <float.h>
#include <cmath>
#include <map>
#include "CubePL2MemoryManager.h"

namespace cube
{
class CubePL2LocalMemoryManager
{
private:

    size_t              row_size;
    CubePL2MemoryDuplet init_value;

    std::vector< std::vector<CubePL2MemoryDuplet> > memory;              // normal memory. Every new expression calculation allocates new "page" and moves stack pointer
    std::stack< size_t >                            memory_stack;

    size_t page_size;                                                           // stores   size of the page (number of variables, which do exist over whole cube)


public:
    CubePL2LocalMemoryManager();

    virtual
    ~CubePL2LocalMemoryManager();

    inline
    void
    set_row_size( size_t _size )
    {
        row_size = _size;
    };

    void
    clear_memory();                     // destroys every "row" stored in memory


    virtual
    void
    init();
    virtual
    void
    new_page();
    virtual
    void
    throw_page();

    void
        set_page_size( uint32_t );

    virtual
    void
        clear_variable( CubePL2MemoryAdress );

    virtual
    void put( CubePL2MemoryAdress,
              double,
              double
              );
    virtual
    void put( CubePL2MemoryAdress,
              double,
              std::string );

    virtual
    void put( MemoryAdress,
              double,
              double*
              );


    virtual
    void push_back( CubePL2MemoryAdress,
                    double );
    virtual
    void push_back( CubePL2MemoryAdress,
                    std::string );

    virtual
    double get( CubePL2MemoryAdress,
                double );

    virtual
    double* get_row( MemoryAdress,
                     double );

    virtual
    std::string get_as_string( CubePL2MemoryAdress,
                               double );
    virtual
    size_t size_of( CubePL2MemoryAdress  );

    virtual
    CubePL2StateOfCubePLVariable
        type( MemoryAdress, double );
};
}

#endif
