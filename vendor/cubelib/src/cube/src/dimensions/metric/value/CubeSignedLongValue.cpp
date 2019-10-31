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
 * \file CubeSignedLongValue.cpp
 * \brief   Defines the methods of the "SignedLongValue".
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


SignedLongValue::SignedLongValue()
{
    isSingleValue = true;

    value.ilValue = 0;
}

SignedLongValue::SignedLongValue( int64_t uv )
{
    isSingleValue = true;

    value.ilValue = ( int64_t )uv;
}

uint16_t
SignedLongValue::getUnsignedShort() const
{
    return ( uint16_t )value.ilValue;
}

int16_t
SignedLongValue::getSignedShort() const
{
    return ( int16_t )value.ilValue;
}

uint32_t
SignedLongValue::getUnsignedInt() const
{
    return ( uint32_t )value.ilValue;
}

int32_t
SignedLongValue::getSignedInt() const
{
    return ( int32_t )value.ilValue;
}

uint64_t
SignedLongValue::getUnsignedLong() const
{
    return ( uint64_t )value.ilValue;
}

int64_t
SignedLongValue::getSignedLong() const
{
    return value.ilValue;
}



/**
 * As char will be returned just first char of the char representation
 */
char
SignedLongValue::getChar() const
{
    return ( char )value.ilValue;
}

/**
 * Creates the string representation of the value.
 */
string
SignedLongValue::getString() const
{
    stringstream sstr;
    string       str;
    sstr << value.ilValue;
    sstr >> str;
    return str;
}



/**
 * Sets the value from stream and returns the position in stream right after the value.
 */
const char*
SignedLongValue::fromStream( const char* cv )
{
    memcpy( value.aValue, cv, sizeof( int64_t ) );
    return cv + sizeof( int64_t );
}

const double*
SignedLongValue::fromStreamOfDoubles( const double* cv )
{
    value.ilValue = ( int64_t )( *cv );
    return ++cv;
}

/**
 * Saves the value in the stream and returns the position in stream right after the value.
 */
char*
SignedLongValue::toStream( char* cv ) const
{
    memcpy( cv, value.aValue, sizeof( int64_t ) );
    return cv + sizeof( int64_t );
}


// overloaded new operator
void*
SignedLongValue::operator new( size_t )
{
    return ( void* )int64_preallocator.Get();
}
// delete operator overloaded
void
SignedLongValue::operator delete( void* p )
{
    int64_preallocator.Put( ( SignedLongValue* )p );
}

void
SignedLongValue::operator=( double d )
{
    value.ilValue = ( int64_t )d;
}

void
SignedLongValue::operator=( Value* v )
{
    value.ilValue = v->getSignedLong();
}


void
SignedLongValue::normalizeWithClusterCount( uint64_t N )
{
    value.ilValue = ( int64_t )( ( double )value.ilValue / ( double )N );
}

void
cube::SignedLongValue::fromStream( Connection& connection )
{
    connection >> this->value.ilValue;
}

void
cube::SignedLongValue::toStream( Connection& connection ) const
{
    connection << this->value.ilValue;
}
