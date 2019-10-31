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


#ifndef __CUBEPL_MEMORY_INITIALIZER_H
#define __CUBEPL_MEMORY_INITIALIZER_H 0

#include <vector>
#include <stack>
#include <iostream>
#include <float.h>
#include <cmath>
#include <map>

#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubePLMemoryManager.h"

namespace cube
{
class CubePLMemoryInitializer
{
protected:
    CubePLMemoryManager* cubepl_memory_manager;

public:

    CubePLMemoryInitializer( CubePLMemoryManager* _manager ) : cubepl_memory_manager( _manager )
    {
    }

    virtual
    ~CubePLMemoryInitializer()
    {
    };


    virtual
    void
        memory_new( uint32_t ) = 0;

    virtual
    void
    memory_init() = 0;

    virtual
    void
        memory_cleanup( uint32_t ) = 0;

    virtual
    void
    memory_setup( const cube::Cube* ) = 0;

    virtual
    void
        memory_setup( const cube::Metric*, uint32_t  ) = 0;

    virtual
    void
        memory_setup( const cube::Cnode*,
                      const CalculationFlavour,
                      uint32_t ) = 0;
    virtual
    void
        memory_setup( const cube::Region*,
                      uint32_t  ) = 0;
    virtual
    void
        memory_setup( const cube::Sysres*,
                      const CalculationFlavour,
                      uint32_t  ) = 0;
};
}

#endif
