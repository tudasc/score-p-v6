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
 * \file CubeSignedValue.cpp
 * \brief  Defines the methods of the "SignedValue".
 ************************************************/

#include "config.h"

#include <sstream>
#include <cstring>
#include <string>

#include "CubeValues.h"
#include "CubeConnection.h"

using namespace std;
using namespace cube;



SignedValue::SignedValue()
{
    isSingleValue = true;
    value.iValue  = 0;
}


SignedValue::SignedValue( int32_t uv )
{
    isSingleValue = true;

    value.iValue = uv;
}



uint16_t
SignedValue::getUnsignedShort() const
{
    return ( uint16_t )value.iValue;
}
int16_t
SignedValue::getSignedShort() const
{
    return ( int16_t )value.iValue;
}

uint32_t
SignedValue::getUnsignedInt() const
{
    return ( uint32_t )value.iValue;
}
int32_t
SignedValue::getSignedInt() const
{
    return value.iValue;
}


uint64_t
SignedValue::getUnsignedLong() const
{
    return ( uint64_t )value.iValue;
}
int64_t
SignedValue::getSignedLong() const
{
    return ( int64_t )value.iValue;
}



/**
 * As char will be returned just first char of the char representation
 */
char
SignedValue::getChar() const
{
    return ( char )value.iValue;
}

/**
 * Creates the string representation of the value.
 */
string
SignedValue::getString() const
{
    stringstream sstr;
    string       str;
    sstr << value.iValue;
    sstr >> str;
    return str;
}


/**
 * Sets the value from stream and returns the position in stream right after the value.
 */
const char*
SignedValue::fromStream( const char* cv )
{
    memcpy( value.aValue, cv, sizeof( int32_t ) );
    return cv + sizeof( int32_t );
}

const double*
SignedValue::fromStreamOfDoubles( const double* cv )
{
    value.iValue = ( int32_t )( *cv );
    return ++cv;
}

/**
 * Saves the value in the stream and returns the position in stream right after the value.
 */
char*
SignedValue::toStream( char* cv ) const
{
    memcpy( cv, value.aValue, sizeof( int32_t ) );
    return cv + sizeof( int32_t );
}


// overloaded new operator
void*
SignedValue::operator new( size_t )
{
    return ( void* )int32_preallocator.Get();
}
// delete operator overloaded
void
SignedValue::operator delete( void* p )
{
    int32_preallocator.Put( ( SignedValue* )p );
}

void
SignedValue::operator=( double d )
{
// #warning LOST PRECISION
    value.iValue = ( int32_t )d;
}

void
SignedValue::operator=( Value* v )
{
    value.iValue = v->getSignedInt();
}

void
SignedValue::normalizeWithClusterCount( uint64_t N )
{
    value.iValue = ( int32_t )( ( double )value.iValue / ( double )N );
}

void
cube::SignedValue::fromStream( Connection& connection )
{
    connection >> this->value.iValue;
}

void
cube::SignedValue::toStream( Connection& connection ) const
{
    connection << this->value.iValue;
}
