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
 * \file CubeCharValue.cpp
 * \brief
 ************************************************/

#include "config.h"

#include <cstring>
#include <sstream>
#include <string>

#include "CubeConnection.h"
#include "CubeValues.h"

using namespace std;
using namespace cube;



CharValue::CharValue()
{
    isSingleValue = true;
    value.cValue  = 0;
}

CharValue::CharValue( char cv )
{
    isSingleValue = true;
    value.cValue  = cv;
}

uint16_t
CharValue::getUnsignedShort() const
{
    return ( uint16_t )value.cValue;
}
int16_t
CharValue::getSignedShort() const
{
    return ( int16_t )value.cValue;
}


uint32_t
CharValue::getUnsignedInt() const
{
    return ( uint32_t )value.cValue;
}
int32_t
CharValue::getSignedInt() const
{
    return ( int32_t )value.cValue;
}


uint64_t
CharValue::getUnsignedLong() const
{
    return ( uint64_t )value.cValue;
}
int64_t
CharValue::getSignedLong() const
{
    return ( int64_t )value.cValue;
}


char
CharValue::getChar() const
{
    return value.cValue;
}

string
CharValue::getString() const
{
    stringstream sstr;
    string       str;
    sstr << value.cValue;
    sstr >> str;
    return str;
}

const char*
CharValue::fromStream( const char* cv )
{
    memcpy( value.aValue, cv, sizeof( char ) );
    return cv + sizeof( char );
}


const double*
CharValue::fromStreamOfDoubles( const double* cv )
{
    value.cValue = ( char )( *cv );
    return cv + sizeof( double );
}



char*
CharValue::toStream( char* cv ) const
{
    memcpy( cv, value.aValue, sizeof( char ) );
    return cv + sizeof( char );
}

// overloaded new operator
void*
CharValue::operator new( size_t )
{
    return ( void* )char_preallocator.Get();
}
// delete operator overloaded
void
CharValue::operator delete( void* p )
{
    char_preallocator.Put( ( CharValue* )p );
}

void
CharValue::operator=( double d )
{
// #warning LOST PRECISION!
    value.cValue = ( char )d;
}

void
CharValue::operator=( Value* v )
{
    value.cValue = v->getChar();
}

void
CharValue::normalizeWithClusterCount( uint64_t N )
{
    value.cValue = ( char )( ( double )value.cValue / ( double )N );
}

void
cube::CharValue::fromStream( Connection& connection )
{
    connection >> value.cValue;
}

void
cube::CharValue::toStream( Connection& connection ) const
{
    connection << value.cValue;
}
