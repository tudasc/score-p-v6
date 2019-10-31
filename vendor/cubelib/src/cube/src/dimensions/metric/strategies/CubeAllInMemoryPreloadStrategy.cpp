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
 * \file CubeAllInMemoryPreloadStrategy.cpp
 * \brief In this strategy, all data is in memory all the time and loaded
 * while initializeing phase
 */

#include "config.h"
#include <iostream>

#include "CubeAllInMemoryPreloadStrategy.h"

using namespace cube;

AllInMemoryPreloadStrategy::AllInMemoryPreloadStrategy( bool permissionToFreeAll )
    : AllInMemoryStrategy( permissionToFreeAll )
{
}


std::vector<cnode_id_t>
AllInMemoryPreloadStrategy::initialize( rows_t* _rows )
{
    m_rowsInMemory.clear();
    for ( cnode_id_t _cid = 0; _cid < (cnode_id_t)(_rows->size()); ++_cid )
    {
        m_rowsInMemory.push_back( _cid );
    }
    return m_rowsInMemory;
}
