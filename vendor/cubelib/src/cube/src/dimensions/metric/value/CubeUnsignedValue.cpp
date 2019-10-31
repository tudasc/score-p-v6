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
 * \file CubeUnsignedValue.cpp
 * \brief Defines the methods of the "UnsignedValue".
 ************************************************/

#include "config.h"

#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

#include "CubeConnection.h"
#include "CubeValues.h"

using namespace std;
using namespace cube;


UnsignedValue::UnsignedValue()
{
    isSingleValue = true;
    value.uValue  = 0;
}

UnsignedValue::UnsignedValue( uint32_t uv )
{
    isSingleValue = true;
    value.uValue  = ( uint32_t )uv;
}

uint16_t
UnsignedValue::getUnsignedShort() const
{
    return ( uint16_t )value.uValue;
}
int16_t
UnsignedValue::getSignedShort() const
{
    return ( int16_t )value.uValue;
}

uint32_t
UnsignedValue::getUnsignedInt() const
{
    return ( uint32_t )value.uValue;
}
int32_t
UnsignedValue::getSignedInt() const
{
    return ( int32_t )value.uValue;
}


uint64_t
UnsignedValue::getUnsignedLong() const
{
    return ( uint64_t )value.uValue;
}
int64_t
UnsignedValue::getSignedLong() const
{
    return ( int64_t )value.uValue;
}


/**
 * As char will be returned just first char of the char representation
 */
char
UnsignedValue::getChar() const
{
    return ( char )value.uValue;
}


/**
 * Creates the string representation of the value.
 */
string
UnsignedValue::getString() const
{
    stringstream sstr;
    string       str;
    sstr << value.uValue;
    sstr >> str;
    return str;
}


// overloaded new operator
void*
UnsignedValue::operator new( size_t )
{
    return ( void* )uint32_preallocator.Get();
}
// delete operator overloaded
void
UnsignedValue::operator delete( void* p )
{
    uint32_preallocator.Put( ( UnsignedValue* )p );
}


/**
 * Sets the value from stream and returns the position in stream right after the value.
 */
const char*
UnsignedValue::fromStream( const char* cv )
{
    memcpy( value.aValue, cv, sizeof( uint32_t ) );
    return cv + sizeof( uint32_t );
}

const double*
UnsignedValue::fromStreamOfDoubles( const double* cv )
{
    value.uValue = ( uint32_t )( *cv );
    return ++cv;
}



/**
 * Saves the value in the stream and returns the position in stream right after the value.
 */
char*
UnsignedValue::toStream( char* cv ) const
{
    memcpy( cv, value.aValue,  sizeof( uint32_t ) );
    return cv + sizeof( uint32_t );
}


void
UnsignedValue::operator=( double d )
{
// #warning LOST PRECISION
    value.uValue = ( uint32_t )d;
}


void
UnsignedValue::operator=( Value* v )
{
    value.uValue = v->getUnsignedInt();
}




void
UnsignedValue::normalizeWithClusterCount( uint64_t N )
{
    value.uValue = ( uint32_t )( ( double )value.uValue / ( double )N );
}

void
cube::UnsignedValue::fromStream( Connection& connection )
{
    connection >> value.uValue;
}

void
cube::UnsignedValue::toStream( Connection& connection ) const
{
    connection << value.uValue;
}
