/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2017                                                     **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/*-------------------------------------------------------------------------*/
/**
 *  @file    CubeIdIndexMap_Test.cpp
 *  @ingroup CUBE_lib.service.test
 *  @brief   Unit tests for cube::IdIndexMap
 **/
/*-------------------------------------------------------------------------*/

#include "config.h"

#include "CubeIdIndexMap.h"

#include <string>

#include <gtest/gtest.h>

#include "CubeError.h"

using namespace cube;
using namespace std;
using namespace testing;

class AnIdIndexMap : public Test
{
public:
    AnIdIndexMap()
        : arbitraryId( 123 ),
        arbitraryIndex( 456 )
    {
    }

    IdIndexMap index_map;
    uint32_t   arbitraryId;
    size_t     arbitraryIndex;
};

TEST_F( AnIdIndexMap, isEmptyWhenCreated )
{
    ASSERT_EQ( true, index_map.empty() );
}

TEST_F( AnIdIndexMap, hasZeroSizeWhenCreated )
{
    ASSERT_EQ( 0, index_map.size() );
}

TEST_F( AnIdIndexMap, isNotEmptyAfterInsert )
{
    index_map.insert( 0, 0 );

    ASSERT_EQ( false, index_map.empty() );
}
#ifndef __PGIC__
TEST_F( AnIdIndexMap, throwsExceptionForUnknownMapping )
{
    ASSERT_THROW( index_map.getIndex( 0 ), std::exception );
}
#endif
TEST_F( AnIdIndexMap, returnsKnownMapping )
{
    index_map.insert( arbitraryId, arbitraryIndex );

    ASSERT_EQ( arbitraryIndex, index_map.getIndex( arbitraryId ) );
}

TEST_F( AnIdIndexMap, isEmptyWhenCleared )
{
    index_map.insert( arbitraryId, arbitraryIndex );
    index_map.clear();

    ASSERT_EQ( true, index_map.empty() );
}

TEST_F( AnIdIndexMap, returnsEndOnBeginIfEmpty )
{
    IdIndexMap::iterator it = index_map.begin();

    ASSERT_EQ( index_map.end(), it );
}

TEST_F( AnIdIndexMap, returnsFirstElementOnBegin )
{
    index_map.insert( arbitraryId, arbitraryIndex );

    IdIndexMap::iterator it = index_map.begin();

    ASSERT_EQ( arbitraryId, it.getId() );
    ASSERT_EQ( arbitraryIndex, it.getIndex() );
}

TEST_F( AnIdIndexMap, returnsEndIfPastLastElement )
{
    index_map.insert( arbitraryId, arbitraryIndex );

    IdIndexMap::iterator it = index_map.begin();
    ++it;

    ASSERT_EQ( index_map.end(), it );
}


