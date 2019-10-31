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
 *
 * \file CubeUnsignedLongValue.cpp
 * \brief  Defines the methods of the "UnsignedLongValue".
 ************************************************/

#include "config.h"

#include <cstring>
#include <sstream>
#include <string>

#include "CubeConnection.h"
#include "CubeValues.h"

using namespace std;
using namespace cube;


UnsignedLongValue::UnsignedLongValue()
{
    isSingleValue = true;
    value.ulValue = 0;
}


UnsignedLongValue::UnsignedLongValue( uint64_t uv )
{
    isSingleValue = true;
    value.ulValue = ( uint64_t )uv;
}

uint16_t
UnsignedLongValue::getUnsignedShort() const
{
    return ( uint16_t )value.ulValue;
}
int16_t
UnsignedLongValue::getSignedShort() const
{
    return ( int16_t )value.ulValue;
}

uint32_t
UnsignedLongValue::getUnsignedInt() const
{
    return ( uint32_t )value.ulValue;
}
int32_t
UnsignedLongValue::getSignedInt() const
{
    return ( int32_t )value.ulValue;
}

uint64_t
UnsignedLongValue::getUnsignedLong() const
{
    return ( uint64_t )value.ulValue;
}
int64_t
UnsignedLongValue::getSignedLong() const
{
    return ( int64_t )value.ulValue;
}



/**
 * As char will be returned just first char of the char representation
 */
char
UnsignedLongValue::getChar() const
{
    return value.aValue[ 0 ];
}

/**
 * Creates the string representation of the value.
 */
string
UnsignedLongValue::getString() const
{
    stringstream sstr;
    string       str;
    sstr << value.ulValue;
    sstr >> str;
    return str;
}


/**
 * Sets the value from stream and returns the position in stream right after the value.
 */
const char*
UnsignedLongValue::fromStream( const char* cv )
{
    memcpy( value.aValue, cv, sizeof( uint64_t ) );
    return cv + sizeof( uint64_t );
}

const double*
UnsignedLongValue::fromStreamOfDoubles( const double* cv )
{
    value.ulValue = ( uint64_t )( *cv );
    return ++cv;
}

/**
 * Saves the value in the stream and returns the position in stream right after the value.
 */
char*
UnsignedLongValue::toStream( char* cv ) const
{
    memcpy( cv, value.aValue, sizeof( uint64_t ) );
    return cv + sizeof( uint64_t );
}



// overloaded new operator
void*
UnsignedLongValue::operator new( size_t )
{
    return ( void* )uint64_preallocator.Get();
}
// delete operator overloaded
void
UnsignedLongValue::operator delete( void* p )
{
    uint64_preallocator.Put( ( UnsignedLongValue* )p );
}

void
UnsignedLongValue::operator=( double d )
{
    value.ulValue = ( uint64_t )d;
}


void
UnsignedLongValue::operator=( Value* v )
{
    value.ulValue = v->getUnsignedLong();
}

void
UnsignedLongValue::normalizeWithClusterCount( uint64_t N )
{
    value.ulValue = ( uint64_t )( ( double )value.ulValue / ( double )N );
}

void
cube::UnsignedLongValue::fromStream( Connection& connection )
{
    connection >> value.ulValue;
}

void
cube::UnsignedLongValue::toStream( Connection& connection ) const
{
    connection << value.ulValue;
}
