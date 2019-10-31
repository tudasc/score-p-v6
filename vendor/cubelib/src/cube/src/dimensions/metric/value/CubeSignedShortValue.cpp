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
 * \file CubeSignedShortValue.cpp
 * \brief   Defines the methods of the "SignedShortValue".
 ************************************************/

#include "config.h"

#include <cstring>
#include <sstream>
#include <string>

#include "CubeConnection.h"
#include "CubeValues.h"

using namespace std;
using namespace cube;


SignedShortValue::SignedShortValue()
{
    isSingleValue = true;

    value.isValue = 0;
}



SignedShortValue::SignedShortValue( int16_t uv )
{
    isSingleValue = true;

    value.isValue = uv;
}



uint16_t
SignedShortValue::getUnsignedShort() const
{
    return ( uint16_t )value.isValue;
}
int16_t
SignedShortValue::getSignedShort() const
{
    return value.isValue;
}


uint32_t
SignedShortValue::getUnsignedInt() const
{
    return ( uint32_t )value.isValue;
}
int32_t
SignedShortValue::getSignedInt() const
{
    return ( int32_t )value.isValue;
}


uint64_t
SignedShortValue::getUnsignedLong() const
{
    return ( uint64_t )value.isValue;
}
int64_t
SignedShortValue::getSignedLong() const
{
    return ( int64_t )value.isValue;
}

/**
 * As char will be returned just first char of the char representation
 */
char
SignedShortValue::getChar() const
{
    return ( char )value.isValue;
}


/**
 * Creates the string representation of the value.
 */
string
SignedShortValue::getString() const
{
    stringstream sstr;
    string       str;
    sstr << value.isValue;
    sstr >> str;
    return str;
}



/**
 * Sets the value from stream and returns the position in stream right after the value.
 */
const char*
SignedShortValue::fromStream( const char* cv )
{
    memcpy( value.aValue, cv, sizeof( int16_t ) );
    return cv + sizeof( int16_t );
}

const double*
SignedShortValue::fromStreamOfDoubles( const double* cv )
{
    value.isValue = ( int16_t )( *cv );
    return ++cv;
}

/**
 * Saves the value in the stream and returns the position in stream right after the value.
 */
char*
SignedShortValue::toStream( char* cv ) const
{
    memcpy( cv, value.aValue,  sizeof( int16_t ) );
    return cv + sizeof( int16_t );
}



// overloaded new operator
void*
SignedShortValue::operator new( size_t )
{
    return ( void* )int16_preallocator.Get();
}
// delete operator overloaded
void
SignedShortValue::operator delete( void* p )
{
    int16_preallocator.Put( ( SignedShortValue* )p );
}

void
SignedShortValue::operator=( double d )
{
// #warning LOST PRECISION
    value.isValue = ( int16_t )d;
}


void
SignedShortValue::operator=( Value* v )
{
    value.isValue = v->getSignedShort();
}

void
SignedShortValue::normalizeWithClusterCount( uint64_t N )
{
    value.isValue = ( int16_t )( ( double )value.isValue / ( double )N );
}

void
cube::SignedShortValue::fromStream( Connection& connection )
{
    connection >> value.isValue;
}

void
cube::SignedShortValue::toStream( Connection& connection ) const
{
    connection << value.isValue;
}
