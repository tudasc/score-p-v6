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


/**
 * \file CubeAllInMemoryPleloadStrategy.h
 * \brief In this strategy, all data is in memory all the time and loaded while
 * initialization phase
 */
#ifndef CUBE_ALL_IN_MEMORY_PRELOAD_STRATEGY_H
#define CUBE_ALL_IN_MEMORY_PRELOAD_STRATEGY_H 0

#include <map>
#include "CubeAllInMemoryStrategy.h"

namespace cube
{
class AllInMemoryPreloadStrategy : public AllInMemoryStrategy
{
public:
    /**
     * @param[in] permissionToFreeAll Specifies if the strategy should
     * give permission for freeing all rows when asked
     */
    AllInMemoryPreloadStrategy( bool permissionToFreeAll );
    /**
     * Virtual destructor
     */
    virtual
    ~AllInMemoryPreloadStrategy()
    {
    };

    virtual std::vector<cnode_id_t>
    initialize( rows_t* rows );

protected:
    std::vector<cnode_id_t> m_rowsInMemory;
};
}

#endif
