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
 * \file CubeComplexValue.cpp
 * \brief   Defines the methods of the "ComplexValue".
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

std::vector<cube::ComplexValueConfig> cube::ComplexValue::parameters;

ComplexValue::ComplexValue() : r_value( 0. ), i_value( 0. )
{
    isSingleValue = false;
}



ComplexValue::ComplexValue( double r_dv,
                            double i_dv ) : r_value( r_dv ), i_value( i_dv )
{
    isSingleValue = false;
}



uint16_t
ComplexValue::getUnsignedShort() const
{
    return ( uint16_t )getDouble();
}


int16_t
ComplexValue::getSignedShort() const
{
    return ( int16_t )getDouble();
}

uint32_t
ComplexValue::getUnsignedInt() const
{
    return ( uint32_t )getDouble();
}


int32_t
ComplexValue::getSignedInt() const
{
    return ( int32_t )getDouble();
}


uint64_t
ComplexValue::getUnsignedLong() const
{
    return ( uint64_t )getDouble();
}


int64_t
ComplexValue::getSignedLong() const
{
    return ( int64_t )getDouble();
}




char
ComplexValue::getChar() const
{
    return ' ';
}

string
ComplexValue::getString() const
{
    string tmp = "(" + r_value.getString() + ")";
    tmp += " +i(";
    tmp += i_value.getString();
    tmp += ")";
    return tmp;
}


const char*
ComplexValue::fromStream( const char* cv )
{
    return i_value.fromStream( r_value.fromStream( cv ) );
}


const double*
ComplexValue::fromStreamOfDoubles( const double* cv )
{
    return ( double* )( i_value.fromStream( r_value.fromStream( ( char* )cv ) ) );
}

char*
ComplexValue::toStream( char* cv ) const
{
    return i_value.toStream( r_value.toStream( cv ) );
}

char*
ComplexValue::transformStream( char* stream, SingleValueTrafo* trafo ) const
{
    return i_value.transformStream( r_value.transformStream( stream, trafo ), trafo );
}


// overloaded new operator
void*
ComplexValue::operator new( size_t )
{
    return ( void* )complex_preallocator.Get();
}
// delete operator overloaded
void
ComplexValue::operator delete( void* p )
{
    complex_preallocator.Put( ( ComplexValue* )p );
}



void
ComplexValue::operator=( double )
{
    throw RuntimeError( "Impossible to assign a single double value  to ComplexValue" );
}

void
ComplexValue::operator=( Value* )
{
    throw RuntimeError( "Impossible to assign a single general Value to ComplexValue" );
}



void
ComplexValue::normalizeWithClusterCount( uint64_t N )
{
    r_value.normalizeWithClusterCount( N );
    i_value.normalizeWithClusterCount( N );
}

void
ComplexValue::init_new()
{
    ComplexValueConfig a;
    ( cube::ComplexValue::parameters ).push_back( a );
    index = ( cube::ComplexValue::parameters ).size() - 1;
};

void
ComplexValue::clone_new( const Value* v )
{
    index = ( static_cast<const ComplexValue*>( v ) )->index;
}

void
cube::ComplexValue::fromStream( Connection& connection )
{
    r_value.fromStream( connection );
    i_value.fromStream( connection );
}

void
cube::ComplexValue::toStream( Connection& connection ) const
{
    r_value.toStream( connection );
    i_value.toStream( connection );
}
