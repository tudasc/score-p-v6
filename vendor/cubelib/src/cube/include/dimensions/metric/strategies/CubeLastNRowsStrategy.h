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
 * \file CubeLastNRowsStrategy.h
 * \brief In this strategy, the last N accessed rows are kept in memory.
 */
#ifndef CUBE_LAST_N_ROWS_STRATEGY_H
#define CUBE_LAST_N_ROWS_STRATEGY_H 0

#include <list>
#include "CubeBasicStrategy.h"


#define CUBE_N_LAST_ROWS_NUMBER 50
#ifdef CUBE_DEFAULT_LAST_N
#ifdef CUBE_N_LAST_ROWS
#undef  CUBE_N_LAST_ROWS_NUMBER
#define CUBE_N_LAST_ROWS_NUMBER CUBE_N_LAST_ROWS
#endif
#endif


namespace cube
{
class LastNRowsStrategy : public BasicStrategy
{
public:
    /**
     * @param[in] permissionToFreeAll Specifies if the strategy should
     * give permission for freeing all rows when asked
     *
     * @ param[in] lastN Specifies how many rows should be kept in
     * memory at once
     */
    LastNRowsStrategy( bool permissionToFreeAll,
                       int  lastN = CUBE_N_LAST_ROWS_NUMBER );
    /**
     * Virtual destructor
     */
    virtual
    ~LastNRowsStrategy()
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

    virtual
    std::vector<cnode_id_t>
    initialize( rows_t* _rows );

private:
    bool                            m_permissionToFreeAll;
    std::list<cnode_id_t>           m_rowsInMemory;
    std::list<cnode_id_t>::iterator removal_frontier;
    int                             m_lastN;
};
}

#endif
