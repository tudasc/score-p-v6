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
 * \file CubeDoubleValue.cpp
 * \brief   Defines the methods of the "DoubleValue".
 ************************************************/

#include "config.h"

#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "CubeConnection.h"
#include "CubeValues.h"

using namespace std;
using namespace cube;

DoubleValue::DoubleValue()
{
    isSingleValue = true;

    value.dValue = 0.;
}





DoubleValue::DoubleValue( double dv )
{
    isSingleValue = true;

    value.dValue = dv;
}



uint16_t
DoubleValue::getUnsignedShort() const
{
    return ( uint16_t )value.dValue;
}
int16_t
DoubleValue::getSignedShort() const
{
    return ( int16_t )value.dValue;
}

uint32_t
DoubleValue::getUnsignedInt() const
{
    return ( uint32_t )value.dValue;
}
int32_t
DoubleValue::getSignedInt() const
{
    return ( int32_t )value.dValue;
}
uint64_t
DoubleValue::getUnsignedLong() const
{
    return ( uint64_t )value.dValue;
}
int64_t
DoubleValue::getSignedLong() const
{
    return ( int64_t )value.dValue;
}
/**
 * As char will be returned just first char of the char representation
 */
char
DoubleValue::getChar() const
{
    return value.aValue[ 0 ];
}

/**
 * Creates the string representation of the value.
 */
string
DoubleValue::getString() const
{
    stringstream sstr;
    string       str;
    sstr << value.dValue;
    sstr >> str;
    return str;
}



/**
 * Sets the value from stream and returns the position in stream right after the value.
 */
const char*
DoubleValue::fromStream( const char* cv )
{
    memcpy( value.aValue, cv, sizeof( double ) );
    return cv + sizeof( double );
}

const double*
DoubleValue::fromStreamOfDoubles( const double* cv )
{
    return ( const double* )fromStream( ( const char* )cv );
}

/**
 * Saves the value in the stream and returns the position in stream right after the value.
 */
char*
DoubleValue::toStream( char* cv ) const
{
    memcpy( cv, value.aValue, sizeof( double ) );
    return cv + sizeof( double );
}

// overloaded new operator
void*
DoubleValue::operator new( size_t )
{
    return ( void* )double_preallocator.Get();
}
// delete operator overloaded
void
DoubleValue::operator delete( void* p )
{
    double_preallocator.Put( ( DoubleValue* )p );
}

void
DoubleValue::operator=( double d )
{
    value.dValue = d;
}


void
DoubleValue::normalizeWithClusterCount( uint64_t N )
{
    value.dValue = value.dValue / ( double )N;
}



void
DoubleValue::operator=( Value* v )
{
    value.dValue = v->getDouble();
}

void
cube::DoubleValue::fromStream( Connection& connection )
{
    connection >> this->value.dValue;
}

void
cube::DoubleValue::toStream( Connection& connection ) const
{
    connection << this->value.dValue;
}
