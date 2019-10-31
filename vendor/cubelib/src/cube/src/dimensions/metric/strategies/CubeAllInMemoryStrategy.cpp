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
 * \file CubeAllInMemoryStrategy.cpp
 * \brief In this strategy, all data is in memory all the time.
 */
#include "config.h"
#include <iostream>
#include "CubeAllInMemoryStrategy.h"
using namespace cube;

AllInMemoryStrategy::AllInMemoryStrategy( bool permissionToFreeAll )
    : m_permissionToFreeAll( permissionToFreeAll ), m_allRowsInMemory( false )
{
}

void
AllInMemoryStrategy::addRow( const cnode_id_t, bool& readAllRows, std::vector<cnode_id_t>& rowsToRemove )
{
    rowsToRemove.clear();
    if ( !m_allRowsInMemory )
    {
        m_allRowsInMemory = true;
        readAllRows       = true;
    }
    else
    {
        readAllRows = false;
    }
}

void
AllInMemoryStrategy::removeRows( std::vector<cnode_id_t>&, std::vector<cnode_id_t>& rowsToRemove )
{
    rowsToRemove.clear();
}

bool
AllInMemoryStrategy::permissionToFreeAll()
{
    if ( m_permissionToFreeAll )
    {
        m_allRowsInMemory = false;
    }

    return m_permissionToFreeAll;
}

void
AllInMemoryStrategy::forcedFreeAll()
{
    m_allRowsInMemory = false;
}


void
AllInMemoryStrategy::needRows( std::vector<cnode_id_t>&, std::vector<cnode_id_t>& rowsToRemoveFirst )
{
    rowsToRemoveFirst.clear();
}
