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


#ifndef __CUBEPL2_MEMORY_INITIALIZER_H
#define __CUBEPL2_MEMORY_INITIALIZER_H 0

#include <vector>
#include <stack>
#include <iostream>
#include <float.h>
#include <cmath>
#include <map>


#include "CubePLMemoryInitializer.h"
#include "CubePL2MemoryManager.h"

namespace cube
{
class CubePL2MemoryInitializer : public CubePLMemoryInitializer
{
protected:
    CubePL2MemoryManager* cubepl2_memory_manager;

public:
    CubePL2MemoryInitializer( CubePLMemoryManager* _manager ) : CubePLMemoryInitializer( _manager )
    {
        cubepl2_memory_manager = ( CubePL2MemoryManager* )_manager;
    };

    virtual
    ~CubePL2MemoryInitializer()
    {
    }

    virtual
    void
    memory_init();

    virtual
    void
    memory_new( uint32_t _id = ( uint32_t )-1 );

    virtual
    void
    memory_cleanup( uint32_t _id = ( uint32_t )-1 );



    virtual
    void
    memory_setup( const cube::Cube* );

    virtual
    void
    memory_setup( const cube::Metric*,
                  const uint32_t _id = ( uint32_t )-1  );

    virtual
    void
    memory_setup( const cube::Cnode*,
                  const CalculationFlavour cf,
                  const uint32_t           _id = ( uint32_t )-1  );

    virtual
    void
    memory_setup( const cube::Region*,
                  const uint32_t _id = ( uint32_t )-1  );

    virtual
    void
    memory_setup( const cube::Sysres*,
                  const CalculationFlavour sf,
                  const uint32_t           _id = ( uint32_t )-1  );
};
}

#endif
