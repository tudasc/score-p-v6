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
 * \file CubeStatLevel1Value.cpp
 * \brief Defines the methods of the "StatLevel1Value".
 ************************************************/

#include "config.h"

#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

#include "CubeConnection.h"
#include "CubeError.h"
#include "CubeValues.h"

using namespace std;
using namespace cube;

std::vector<cube::StatLevel1ValueConfig> cube::StatLevel1Value::parameters;


StatLevel1Value::StatLevel1Value() : N( 1 ), Sum( 0. )
{
    isSingleValue = false;
}

StatLevel1Value::StatLevel1Value( uint32_t n,
                                  double   sum ) : N( n ), Sum( sum )
{
    isSingleValue = false;
}



unsigned
StatLevel1Value::getSize() const
{
    return
        N.getSize() +
        Sum.getSize();
}

/**
 * Single value of StatLevel1Value is possible. It is the average value,.
 */
double
StatLevel1Value::getDouble() const
{
    return Sum.getDouble() / N.getDouble();
}

/**
 * Single value of StatLevel1Value is possible. It is the average value, but casted to unsigned. Might be wrong, if average value is negative..
 */
uint16_t
StatLevel1Value::getUnsignedShort() const
{
    return ( uint16_t )getDouble();
}

/**
 * Single value of StatLevel1Value is possible. It is the average value, but casted to unsigned.
 */
int16_t
StatLevel1Value::getSignedShort() const
{
    return ( int16_t )getDouble();
}

/**
 * Single value of StatLevel1Value is possible. It is the average value, but casted to unsigned. Might be wrong, if average value is negative..
 */
uint32_t
StatLevel1Value::getUnsignedInt() const
{
    return ( uint32_t )getDouble();
}

/**
 * Single value of StatLevel1Value is possible. It is the average value, but casted to unsigned.
 */
int32_t
StatLevel1Value::getSignedInt() const
{
    return ( int32_t )getDouble();
}


/**
 * Single value of StatLevel1Value is possible. It is the average value, but casted to unsigned. Might be wrong, if average value is negative..
 */
uint64_t
StatLevel1Value::getUnsignedLong() const
{
    return ( uint64_t )getDouble();
}

/**
 * Single value of StatLevel1Value is possible. It is the average value, but casted to unsigned.
 */
int64_t
StatLevel1Value::getSignedLong() const
{
    return ( int64_t )getDouble();
}

/**
 * Char is meaningless representation of StatLevel1Value. Therefore an exception is thrown.
 */
char
StatLevel1Value::getChar() const
{
    return ' ';
}



/**
 * Creates the string representation of the value.
 */
string
StatLevel1Value::getString() const
{
    const double avg = calcAvg();
    stringstream sstr;
    string       str;
    sstr << avg  << endl;
    sstr >> str;
    return str;
}

// overloaded new operator
void*
StatLevel1Value::operator new( size_t )
{
    return ( void* )stat1_preallocator.Get();
}
// delete operator overloaded
void
StatLevel1Value::operator delete( void* p )
{
    stat1_preallocator.Put( ( StatLevel1Value* )p );
}


/**
 * Creates the copy and sets the value to 0.
 */
Value*
StatLevel1Value::clone() const
{
    return new StatLevel1Value( 1, 0. );
}


/**
 * Creates the copy.
 */
Value*
StatLevel1Value::copy() const
{
// #warning "Missing interface for unsigned long long"
    return new StatLevel1Value( N.getUnsignedInt(), Sum.getDouble() );
}


/**
 * Sets the value from stream and returns the position in stream right after the value.
 */
const char*
StatLevel1Value::fromStream( const char* cv )
{
    return Sum.fromStream( N.fromStream( cv ) );
}

/**
 * Sets the value from stream and returns the position in stream right after the value.
 */
const double*
StatLevel1Value::fromStreamOfDoubles( const double* cv )
{
    return Sum.fromStreamOfDoubles( N.fromStreamOfDoubles( cv ) );
}

/**
 * Saves the value in the stream and returns the position in stream right after the value.
 */
char*
StatLevel1Value::toStream( char* cv ) const
{
    return Sum.toStream( N.toStream( cv ) );
}

/**
 * Transforms the endianness in the stream according its layout
 */
char*
StatLevel1Value::transformStream( char* cv, SingleValueTrafo* trafo ) const
{
    return Sum.transformStream( N.transformStream( cv, trafo ), trafo );
}




void
StatLevel1Value::operator+=( Value* chval )
{
    if ( chval == NULL )
    {
        return;
    }
    N   += ( ( Value* )( &( ( ( StatLevel1Value* )chval )->N ) ) );
    Sum += ( ( Value* )( &( ( ( StatLevel1Value* )chval )->Sum ) ) );
}

void
StatLevel1Value::operator-=( Value* chval )
{
    if ( chval == NULL )
    {
        return;
    }
    N   -= ( ( Value* )( &( ( ( StatLevel1Value* )chval )->N ) ) );
    Sum -= ( ( Value* )( &( ( ( StatLevel1Value* )chval )->Sum ) ) );
}


void
StatLevel1Value::operator*=( double dval )
{
//     N *= dval; // Average gets multiplied, not the both values.
    Sum *= dval;
}

void
StatLevel1Value::operator/=( double dval )
{
    if ( dval == 0. )
    {
        cerr << "ERROR: DEVISION BY ZERO!" << endl;
    }
    else
    {
        Sum /= dval;     //Avarege gets devided, not both (then no action )
    }
}


void
StatLevel1Value::operator=( double )
{
    throw RuntimeError( "Impossible to assign a  single double to StatLevel1Value" );
}

void
StatLevel1Value::operator=( Value* )
{
// #warning "Error handling has to be done"
    throw RuntimeError( "Impossible to assign a singlegeneral Value to StatLevel1Value" );
}

// -------------------- PRIVATE METHODS- ------------------------

double
StatLevel1Value::calcAvg() const
{
    uint32_t n  = N.getUnsignedInt();
    double   dn = N.getDouble();
    double   s  = Sum.getDouble();

    return ( n == 0 ) ? s / ( dn + 1e-256 )  : s / dn;
}


void
StatLevel1Value::normalizeWithClusterCount( uint64_t _N )
{
    N.normalizeWithClusterCount( _N );
    Sum.normalizeWithClusterCount( _N );
}

void
StatLevel1Value::init_new()
{
    StatLevel1ValueConfig a;
    ( cube::StatLevel1Value::parameters ).push_back( a );
    index = ( cube::StatLevel1Value::parameters ).size() - 1;
};

void
StatLevel1Value::clone_new( const Value* v )
{
    index = ( static_cast<const StatLevel1Value*>( v ) )->index;
}

void
cube::StatLevel1Value::fromStream( Connection& connection )
{
    N.fromStream( connection );
    Sum.fromStream( connection );
}

void
cube::StatLevel1Value::toStream( Connection& connection ) const
{
    N.toStream( connection );
    Sum.toStream( connection );
}
