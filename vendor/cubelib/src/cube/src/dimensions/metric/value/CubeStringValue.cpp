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
 * \file CubeStringValue.cpp
 * \brief  Defines the methods of the "StringValue".
 ************************************************/

#include "config.h"

#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

#include "CubeConnection.h"
#include "CubeServices.h"
#include "CubeValues.h"


using namespace std;
using namespace cube;

std::vector<cube::StringValueConfig> cube::StringValue::parameters;

StringValue::StringValue()
{
    isSingleValue = false;

    size = 0;
    value.empty();
}

StringValue::StringValue( uint16_t s )
{
    isSingleValue = false;

    size = ( size_t )s;
    value.resize( size, ' ' );
}


StringValue::StringValue( int16_t s )
{
    if ( s < 0 )
    {
        throw RuntimeError( "[StringValue(int16_t s)] Size of string cannot be negative." );
    }
    isSingleValue = false;

    size = s;
    value.resize( size, ' ' );
}


StringValue::StringValue( uint32_t s )
{
    isSingleValue = false;

    size = ( size_t )s;
    value.resize( size, ' ' );
}


StringValue::StringValue( int32_t s )
{
    if ( s < 0 )
    {
        throw RuntimeError( "[StringValue(int32_t s)] Size of string cannot be negative." );
    }
    isSingleValue = false;

    size = s;
    value.resize( size, ' ' );
}
StringValue::StringValue( uint64_t s )
{
    isSingleValue = false;

    size = ( size_t )s;
    value.resize( size, ' ' );
}


StringValue::StringValue( int64_t s )
{
    if ( s < 0 )
    {
        throw RuntimeError( "[StringValue(int64_t s)] Size of string cannot be negative." );
    }
    isSingleValue = false;

    size = s;
    value.resize( size, ' ' );
}



StringValue::StringValue( double dv )
{
    isSingleValue = false;

    stringstream sstr;
    sstr << dv;
    sstr >> value;
    size = value.size();
}

StringValue::StringValue( char cv )
{
    isSingleValue = false;

//     cout << "char CONSTRUCTOR" << endl;
    stringstream sstr;
    sstr << cv;
    sstr >> value;
    size = value.size();
}
StringValue::StringValue( size_t n,
                          char*  cv )
{
    isSingleValue = false;
    char* tmp = new char[ n + 1 ]();
    memcpy( tmp, cv, n );
    value = *tmp;
    delete[] tmp;
    size = value.size();
}

StringValue::StringValue( string sv )
{
    isSingleValue = false;

    value = sv;
    size  = value.size();
}

unsigned
StringValue::getSize() const
{
    return size;
}


double
StringValue::getDouble() const
{
    return 0.;
}

uint16_t
StringValue::getUnsignedShort() const
{
    return ( uint16_t )getDouble();
}

int16_t
StringValue::getSignedShort() const
{
    return ( int16_t )getDouble();
}

uint32_t
StringValue::getUnsignedInt() const
{
    return ( uint32_t )getDouble();
}



int32_t
StringValue::getSignedInt() const
{
    return ( int32_t )getDouble();
}

uint64_t
StringValue::getUnsignedLong() const
{
    return ( uint64_t )getDouble();
}

int64_t
StringValue::getSignedLong() const
{
    return ( int64_t )getDouble();
}
char
StringValue::getChar() const
{
    return ' ';
}

string
StringValue::getString() const
{
    return value;
}

/**
 * Creates the copy and sets the value to ' '.
 */
StringValue*
StringValue::clone() const
{
    string v( ' ', value.size() );
    return new StringValue( v );
}

/**
 * Creates the copy.
 */
StringValue*
StringValue::copy() const
{
    return new StringValue( value );
}


/**
 * Sets the value from stream and returns the position in stream right after the value.
 */
const char*
StringValue::fromStream( const char* cv )
{
    char* tmp = new char[ size + 1 ]();
    memcpy( tmp, cv, size );
    value = *tmp;
    delete[] tmp;
    return cv + size;
}

const double*
StringValue::fromStreamOfDoubles( const double* cv )
{
    value = services::numeric2string( *cv );
    return cv + sizeof( double );
}

/**
 * Saves the value in the stream and returns the position in stream right after the value.
 */
char*
StringValue::toStream( char* cv ) const
{
    memcpy( cv, value.c_str(),  size );
    return cv + size;
}

// overloaded new operator
void*
StringValue::operator new( size_t )
{
    return ( void* )string_preallocator.Get();
}

// delete operator overloaded
void
StringValue::operator delete( void* p )
{
    string_preallocator.Put( ( StringValue* )p );
}

void
StringValue::operator+=( Value* )
{
// #warning " Operation + is for string undefined and has no action"
    return;
}

void
StringValue::operator-=( Value* )
{
// #warning " Operation + is for string undefined  and has no action"
    return;
}

void
StringValue::operator*=( double  )
{
// #warning " Operation + is for string undefined and has no action"
    return;
}

void
StringValue::operator/=( double )
{
// #warning " Operation + is for string undefined and has no action"
    return;
}

void
StringValue::operator=( double d )
{
    stringstream sstr;
    sstr << d;
    sstr >> value;
    value.reserve( size );
}

void
StringValue::operator=( Value* v )
{
    value = v->getString();
    value.reserve( size );
}


void
StringValue::normalizeWithClusterCount( uint64_t )
{
}

void
StringValue::init_new()
{
    StringValueConfig a;
    ( cube::StringValue::parameters ).push_back( a );
    index = ( cube::StringValue::parameters ).size() - 1;
};

void
StringValue::clone_new( const Value* v )
{
    index = ( static_cast<const StringValue*>( v ) )->index;
}

void
cube::StringValue::fromStream( Connection& connection )
{
    connection >> value;
    size = value.size();
}

void
cube::StringValue::toStream( Connection& connection ) const
{
    connection << value;
}
