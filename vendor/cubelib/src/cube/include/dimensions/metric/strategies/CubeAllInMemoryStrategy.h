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
 * \file CubeAllInMemoryStrategy.h
 * \brief In this strategy, all data is in memory all the time.
 */
#ifndef CUBE_ALL_IN_MEMORY_STRATEGY_H
#define CUBE_ALL_IN_MEMORY_STRATEGY_H 0

#include <map>
#include "CubeBasicStrategy.h"

namespace cube
{
class AllInMemoryStrategy : public BasicStrategy
{
public:
    /**
     * @param[in] permissionToFreeAll Specifies if the strategy should
     * give permission for freeing all rows when asked
     */
    AllInMemoryStrategy( bool permissionToFreeAll );
    /**
     * Virtual destructor
     */
    virtual
    ~AllInMemoryStrategy()
    {
    };
    virtual void
    addRow( const cnode_id_t         rowId,
            bool&                    readAllRows,
            std::vector<cnode_id_t>& rowsToRemove );
    virtual void
    removeRows( std::vector<cnode_id_t>& rowsWantToRemove,
                std::vector<cnode_id_t>& rowsToRemove );
    virtual bool
    permissionToFreeAll();
    virtual void
    forcedFreeAll();
    virtual void
    needRows( std::vector<cnode_id_t>& rowsToAdd,
              std::vector<cnode_id_t>& rowsToRemoveFirst );



protected:
//      std::map<cnode_id_t, bool> rows_in_memory;
    bool m_permissionToFreeAll;
    bool m_allRowsInMemory;
};
}

#endif
