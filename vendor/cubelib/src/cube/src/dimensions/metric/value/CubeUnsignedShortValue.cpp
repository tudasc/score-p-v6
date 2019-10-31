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
 * \file CubeUnsignedShortValue.cpp
 * \brief  Defines the methods of the "UnsignedShortValue".
 ************************************************/

#include "config.h"

#include <cstring>
#include <sstream>
#include <string>

#include "CubeConnection.h"
#include "CubeValues.h"

using namespace std;
using namespace cube;



UnsignedShortValue::UnsignedShortValue()
{
    isSingleValue = true;
    value.usValue = 0;
}
UnsignedShortValue::UnsignedShortValue( uint16_t uv )
{
    isSingleValue = true;
    value.usValue = ( uint16_t )uv;
}


uint16_t
UnsignedShortValue::getUnsignedShort() const
{
    return ( uint16_t )value.usValue;
}

int16_t
UnsignedShortValue::getSignedShort() const
{
    return ( int16_t )value.usValue;
}


uint32_t
UnsignedShortValue::getUnsignedInt() const
{
    return ( uint32_t )value.usValue;
}

int32_t
UnsignedShortValue::getSignedInt() const
{
    return ( int32_t )value.usValue;
}



uint64_t
UnsignedShortValue::getUnsignedLong() const
{
    return ( uint64_t )value.usValue;
}

int64_t
UnsignedShortValue::getSignedLong() const
{
    return ( int64_t )value.usValue;
}


/**
 * As char will be returned just first char of the char representation
 */
char
UnsignedShortValue::getChar() const
{
    return value.aValue[ 0 ];
}

/**
 * Creates the string representation of the value.
 */
string
UnsignedShortValue::getString() const
{
    stringstream sstr;
    string       str;
    sstr << value.usValue;
    sstr >> str;
    return str;
}


/**
 * Sets the value from stream and returns the position in stream right after the value.
 */
const char*
UnsignedShortValue::fromStream( const char* cv )
{
    memcpy( value.aValue, cv, sizeof( uint16_t ) );
    return cv + sizeof( uint16_t );
}

const double*
UnsignedShortValue::fromStreamOfDoubles( const double* cv )
{
    value.usValue = ( uint16_t )( *cv );
    return ++cv;
}



/**
 * Saves the value in the stream and returns the position in stream right after the value.
 */
char*
UnsignedShortValue::toStream( char* cv ) const
{
    memcpy( cv, value.aValue, sizeof( uint16_t ) );
    return cv + sizeof( uint16_t );
}



// overloaded new operator
void*
UnsignedShortValue::operator new( size_t )
{
    return ( void* )uint16_preallocator.Get();
}
void
UnsignedShortValue::operator delete( void* p )
{
    uint16_preallocator.Put( ( UnsignedShortValue* )p );
}

void
UnsignedShortValue::operator=( double d )
{
// #warning LOST PRECISION
    value.usValue = ( uint16_t )d;
}

void
UnsignedShortValue::operator=( Value* v )
{
    value.usValue = v->getUnsignedShort();
}



void
UnsignedShortValue::normalizeWithClusterCount( uint64_t N )
{
    value.usValue = ( uint16_t )( ( double )value.usValue / ( double )N );
}

void
cube::UnsignedShortValue::fromStream( Connection& connection )
{
    connection >> value.usValue;
}

void
cube::UnsignedShortValue::toStream( Connection& connection ) const
{
    connection << value.usValue;
}
