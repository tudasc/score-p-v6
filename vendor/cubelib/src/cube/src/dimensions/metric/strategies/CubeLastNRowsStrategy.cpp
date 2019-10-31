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


/**
 * \file CubeLastNRowsStrategy.cpp
 * \brief In this strategy, the last N accessed rows are kept in memory.
 */

#include "config.h"
#include <iostream>
#include <cstdlib>
#include "CubeLastNRowsStrategy.h"

#define CUBE_LAST_N_ROWS_NUMBER "CUBE_NUMBER_ROWS"

using namespace cube;

LastNRowsStrategy::LastNRowsStrategy( bool permissionToFreeAll,
                                      int  lastN )
    : m_permissionToFreeAll( permissionToFreeAll )
{
    char* _n = getenv( CUBE_LAST_N_ROWS_NUMBER );
    if ( _n == NULL )
    {
        m_lastN = lastN;
    }
    else
    {
        m_lastN = atoi( _n );
    }
    m_rowsInMemory.clear();
    removal_frontier = m_rowsInMemory.begin();
}



std::vector<cnode_id_t>
LastNRowsStrategy::initialize( rows_t* _rows )
{
    m_rowsInMemory.clear();
    std::vector<cnode_id_t> to_return;
    removal_frontier = m_rowsInMemory.begin();
    for ( cnode_id_t _cid = 0; _cid < ( cnode_id_t )( _rows->size() ); ++_cid )
    {
        m_rowsInMemory.push_back( _cid );
        to_return.push_back( _cid );
    }
    removal_frontier = m_rowsInMemory.begin();
    return to_return;
}



void
LastNRowsStrategy::addRow( const cnode_id_t rowId, bool&, std::vector<cnode_id_t>& rowsToRemove )
{
    // Put the new rowId to the end of the list
    m_rowsInMemory.push_back( rowId );
    // Mark superfluous rows for removal
    rowsToRemove.clear();
    while ( m_rowsInMemory.size() > ( size_t )m_lastN )
    {
        rowsToRemove.push_back( m_rowsInMemory.front() );
        m_rowsInMemory.pop_front();
    }
}




void
LastNRowsStrategy::removeRows( std::vector<cnode_id_t>&, std::vector<cnode_id_t>& rowsToRemove )
{
    // Ignore removal request.
    rowsToRemove.clear();
}


bool
LastNRowsStrategy::permissionToFreeAll()
{
    if ( m_permissionToFreeAll )
    {
        m_rowsInMemory.clear();
    }

    return m_permissionToFreeAll;
}




void
LastNRowsStrategy::forcedFreeAll()
{
    m_rowsInMemory.clear();
}



void
LastNRowsStrategy::needRows( std::vector<cnode_id_t>& rowsToAdd, std::vector<cnode_id_t>& rowsToRemoveFirst )
{
    for (; m_rowsInMemory.begin() != removal_frontier; )
    {
        rowsToRemoveFirst.push_back( m_rowsInMemory.front() );
        m_rowsInMemory.pop_front();
    }
    for ( std::vector<cnode_id_t>::iterator iter = rowsToAdd.begin(); iter < rowsToAdd.end(); ++iter )
    {
        m_rowsInMemory.push_back( *iter );
    }
    for ( int i = 0; i < ( int )( m_rowsInMemory.size() )  - ( int )m_lastN; ++i )
    {
        removal_frontier++;
    }
}
