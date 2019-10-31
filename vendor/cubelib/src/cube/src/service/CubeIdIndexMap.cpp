/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016-2019                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/*-------------------------------------------------------------------------*/
/**
 *  @file    CubeIdIndexMap.cpp
 *  @ingroup CUBE_lib.service
 *  @brief   Definition of the class IdIndexMap.
 **/
/*-------------------------------------------------------------------------*/

#include "config.h"

#include "CubeIdIndexMap.h"

using namespace std;
using namespace cube;

// --- Iterator class --------------------------------------------------------

cube::IdIndexMap::iterator::iterator()
{
}


cube::IdIndexMap::iterator::iterator( container_t::const_iterator iterator )
    : mIterator( iterator )
{
}


uint32_t
cube::IdIndexMap::iterator::getId() const
{
    return mIterator->first;
}


size_t
cube::IdIndexMap::iterator::getIndex() const
{
    return mIterator->second;
}


cube::IdIndexMap::iterator&
cube::IdIndexMap::iterator::operator++()
{
    ++mIterator;

    return *this;
}


cube::IdIndexMap::iterator
cube::IdIndexMap::iterator::operator++( int )
{
    IdIndexMap::iterator result( *this );
    ++mIterator;

    return result;
}


cube::IdIndexMap::iterator&
cube::IdIndexMap::iterator::operator--()
{
    --mIterator;

    return *this;
}


cube::IdIndexMap::iterator
cube::IdIndexMap::iterator::operator--( int )
{
    IdIndexMap::iterator result( *this );
    --mIterator;

    return result;
}


bool
cube::IdIndexMap::iterator::operator!=( const iterator& rhs ) const
{
    return !( *this == rhs );
}


bool
cube::IdIndexMap::iterator::operator==( const iterator& rhs ) const
{
    return mIterator == rhs.mIterator;
}


// --- Capacity --------------------------------------------------------------

bool
cube::IdIndexMap::empty() const
{
    return size() == 0;
}


size_t
cube::IdIndexMap::size() const
{
    return mMappings.size();
}


// --- Modifiers -----------------------------------------------------------

void
cube::IdIndexMap::insert( uint32_t id,
                          size_t   index )
{
    mMappings[ id ] = index;
}


void
cube::IdIndexMap::clear()
{
    mMappings.clear();
}


// --- Lookup ----------------------------------------------------------------

size_t
cube::IdIndexMap::getIndex( uint32_t id ) const
{
    return mMappings.at( id );
}


cube::IdIndexMap::iterator
cube::IdIndexMap::begin() const
{
    return IdIndexMap::iterator( mMappings.begin() );
}


cube::IdIndexMap::iterator
cube::IdIndexMap::end() const
{
    return IdIndexMap::iterator( mMappings.end() );
}
