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
 * \file CubeRateValue.cpp
 * \brief   Defines the methods of the "RateValue".
 ************************************************/

#include "config.h"

#include <sstream>
#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>

#include "CubeValues.h"
#include "CubeConnection.h"

using namespace std;
using namespace cube;

std::vector<cube::RateValueConfig> cube::RateValue::parameters;

RateValue::RateValue() : main_value( 0. ), duratio_value( 0. )
{
    isSingleValue = true;
}


RateValue::RateValue( double main_dv,
                      double duratio_dv ) : main_value( main_dv ), duratio_value( duratio_dv )
{
    isSingleValue = true;
}


uint16_t
RateValue::getUnsignedShort() const
{
    return ( uint16_t )getDouble();
}
int16_t
RateValue::getSignedShort() const
{
    return ( int16_t )getDouble();
}

uint32_t
RateValue::getUnsignedInt() const
{
    return ( uint32_t )getDouble();
}
int32_t
RateValue::getSignedInt() const
{
    return ( int32_t )getDouble();
}

uint64_t
RateValue::getUnsignedLong() const
{
    return ( uint64_t )getDouble();
}
int64_t
RateValue::getSignedLong() const
{
    return ( int64_t )getDouble();
}

char
RateValue::getChar() const
{
    return ' ';
}

string
RateValue::getString() const
{
    stringstream sstr;
    string       str;
    sstr <<  setprecision( 12 ) << getDouble();
    sstr >> str;


    string tmp = str + "[(" + main_value.getString() + ")";
    tmp += "/(";
    tmp += duratio_value.getString();
    tmp += ")]";
    return tmp;
}


const char*
RateValue::fromStream( const char* cv )
{
    return duratio_value.fromStream( main_value.fromStream( cv ) );
}

const double*
RateValue::fromStreamOfDoubles( const double* cv )
{
    return ( const double* )( duratio_value.fromStream( main_value.fromStream( ( const char* )cv ) ) );
}


char*
RateValue::toStream( char* cv ) const
{
    return duratio_value.toStream( main_value.toStream( cv ) );
}

char*
RateValue::transformStream( char* stream, SingleValueTrafo* trafo ) const
{
    return duratio_value.transformStream( main_value.transformStream( stream, trafo ), trafo );
}

// overloaded new operator
void*
RateValue::operator new( size_t )
{
    return ( void* )rate_preallocator.Get();
}
// delete operator overloaded
void
RateValue::operator delete( void* p )
{
    rate_preallocator.Put( ( RateValue* )p );
}



void
RateValue::operator=( double )
{
    throw RuntimeError( "Impossible to assign a single double value to RateValue" );
}


void
RateValue::operator=( Value* )
{
    throw RuntimeError( "Impossible to assign a single general value to RateValue" );
}



void
RateValue::normalizeWithClusterCount( uint64_t N )
{
    main_value.normalizeWithClusterCount( N );
    duratio_value.normalizeWithClusterCount( N );
}

void
RateValue::init_new()
{
    RateValueConfig a;
    ( cube::RateValue::parameters ).push_back( a );
    ;
    index = ( cube::RateValue::parameters ).size() - 1;
};

void
RateValue::clone_new( const Value* v )
{
    index = ( static_cast<const RateValue*>( v ) )->index;
}

void
cube::RateValue::fromStream( Connection& connection )
{
    this->main_value.fromStream( connection );
    this->duratio_value.fromStream( connection );
}

void
cube::RateValue::toStream( Connection& connection ) const
{
    this->main_value.toStream( connection );
    this->duratio_value.toStream( connection );
}
