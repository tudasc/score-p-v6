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
 * \file CubeManualStrategy.cpp
 * \brief In this strategy, rows are loaded and unloaded one-by-one,
 * completely under the user's control.
 */
#include "config.h"
#include "CubeManualStrategy.h"

using namespace cube;

ManualStrategy::ManualStrategy( bool permissionToFreeAll )
    : m_permissionToFreeAll( permissionToFreeAll )
{
}

void
ManualStrategy::addRow( const cnode_id_t, bool& readAllRows, std::vector<cnode_id_t>& rowsToRemove )
{
    readAllRows = false;
    rowsToRemove.clear();
}

void
ManualStrategy::removeRows( std::vector<cnode_id_t>& rowsWantToRemove, std::vector<cnode_id_t>& rowsToRemove )
{
    rowsToRemove.clear();
    rowsToRemove = rowsWantToRemove;
}

bool
ManualStrategy::permissionToFreeAll()
{
    return m_permissionToFreeAll;
}

void
ManualStrategy::forcedFreeAll()
{
}

void
ManualStrategy::needRows( std::vector<cnode_id_t>&, std::vector<cnode_id_t>& rowsToRemoveFirst )
{
    rowsToRemoveFirst.clear();
}
