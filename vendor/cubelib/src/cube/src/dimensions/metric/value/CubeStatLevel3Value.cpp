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
 * \file CubeStatLevel3Value.cpp
 * \brief Defines the methods of the "StatLevel3Value".
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

std::vector<cube::StatLevel3ValueConfig> cube::StatLevel3Value::parameters;

StatLevel3Value::StatLevel3Value() : N( 1 ), Sum( 0. ), Sum2( 0. ), Sum3( 0. )
{
    isSingleValue = false;
}

StatLevel3Value::StatLevel3Value( uint32_t n,
                                  double   sum,
                                  double   sum2,
                                  double   sum3 ) : N( n ), Sum( sum ), Sum2( sum2 ), Sum3( sum3 )
{
    isSingleValue = false;
}



unsigned
StatLevel3Value::getSize() const
{
    return
        N.getSize() +
        Sum.getSize() +
        Sum2.getSize() +
        Sum3.getSize()

    ;
}

/**
 * Single value of StatLevel3Value is impossible. Therefore an exception is thrown.
 */
double
StatLevel3Value::getDouble() const
{
    return 0.;
}

/**
 * Single value of StatLevel3Value is impossible. Therefore an exception is thrown.
 */
uint16_t
StatLevel3Value::getUnsignedShort() const
{
    return ( uint16_t )getDouble();
}

/**
 * Single value of StatLevel3Value is impossible. Therefore an exception is thrown.
 */
int16_t
StatLevel3Value::getSignedShort() const
{
    return ( int16_t )getDouble();
}



/**
 * Single value of StatLevel3Value is impossible. Therefore an exception is thrown.
 */
uint32_t
StatLevel3Value::getUnsignedInt() const
{
    return ( uint32_t )getDouble();
}

/**
 * Single value of StatLevel3Value is impossible. Therefore an exception is thrown.
 */
int32_t
StatLevel3Value::getSignedInt() const
{
    return ( int32_t )getDouble();
}





/**
 * Single value of StatLevel3Value is impossible. Therefore an exception is thrown.
 */
uint64_t
StatLevel3Value::getUnsignedLong() const
{
    return ( uint64_t )getDouble();
}

/**
 * Single value of StatLevel3Value is impossible. Therefore an exception is thrown.
 */
int64_t
StatLevel3Value::getSignedLong() const
{
    return ( int64_t )getDouble();
}





/**
 * Char is meaningless representation of StatLevel3Value. Therefore an exception is thrown.
 */
char
StatLevel3Value::getChar() const
{
    return ' ';
}



/**
 * Creates the string representation of the value.
 */
string
StatLevel3Value::getString() const
{
    double       avg  = calcAvg();
    double       var  = calcVar();
    double       skew = calcSkew();
    stringstream sstr;
    string       str;
    sstr << "(" << avg << "," << var << "," << skew << ")"  << endl;
    sstr >> str;
    return str;
}


// overloaded new operator
void*
StatLevel3Value::operator new( size_t )
{
    return ( void* )stat3_preallocator.Get();
}
// delete operator overloaded
void
StatLevel3Value::operator delete( void* p )
{
    stat3_preallocator.Put( ( StatLevel3Value* )p );
}


/**
 * Creates the copy and sets the value to 0.
 */
Value*
StatLevel3Value::clone() const
{
    return new StatLevel3Value( 1, 0., 0., 0. );
}


/**
 * Creates the copy.
 */
Value*
StatLevel3Value::copy() const
{
// #warning "Missing interface for unsigned long long"
    return new StatLevel3Value( N.getUnsignedInt(), Sum.getDouble(), Sum2.getDouble(), Sum3.getDouble() );
}


/**
 * Sets the value from stream and returns the position in stream right after the value.
 */
const char*
StatLevel3Value::fromStream( const char* cv )
{
    return Sum3.fromStream(
        Sum2.fromStream(
            Sum.fromStream(
                N.fromStream( cv ) ) ) );
}

const double*
StatLevel3Value::fromStreamOfDoubles( const double* cv )
{
    return Sum3.fromStreamOfDoubles(
        Sum2.fromStreamOfDoubles(
            Sum.fromStreamOfDoubles(
                N.fromStreamOfDoubles( cv ) ) ) );
}


/**
 * Saves the value in the stream and returns the position in stream right after the value.
 */
char*
StatLevel3Value::toStream( char* cv ) const
{
    return Sum3.toStream(
        Sum2.toStream(
            Sum.toStream(
                N.toStream( cv ) ) ) );
}

/**
 * Transforms the endianness in the stream according its layout
 */
char*
StatLevel3Value::transformStream( char* cv, SingleValueTrafo* trafo ) const
{
    return Sum3.transformStream(
        Sum2.transformStream(
            Sum.transformStream(
                N.transformStream( cv, trafo ), trafo ), trafo ), trafo );
}


void
StatLevel3Value::operator+=( Value* chval )
{
    if ( chval == NULL )
    {
        return;
    }
    N    += ( ( Value* )( &( ( ( StatLevel3Value* )chval )->N ) ) );
    Sum  += ( ( Value* )( &( ( ( StatLevel3Value* )chval )->Sum ) ) );
    Sum2 += ( ( Value* )( &( ( ( StatLevel3Value* )chval )->Sum2 ) ) );
    Sum3 += ( ( Value* )( &( ( ( StatLevel3Value* )chval )->Sum3 ) ) );
}

void
StatLevel3Value::operator-=( Value* chval )
{
    if ( chval == NULL )
    {
        return;
    }
    N    -= ( ( Value* )( &( ( ( StatLevel3Value* )chval )->N ) ) );
    Sum  -= ( ( Value* )( &( ( ( StatLevel3Value* )chval )->Sum ) ) );
    Sum2 -= ( ( Value* )( &( ( ( StatLevel3Value* )chval )->Sum2 ) ) );
    Sum3 -= ( ( Value* )( &( ( ( StatLevel3Value* )chval )->Sum3 ) ) );
}


void
StatLevel3Value::operator*=( double dval )
{
// multiplication with an scalas destroys the relation between variance and average.
//     N *= dval;  // only average scales
    Sum  *= dval;               // average scales
    Sum2 *= dval * dval;        // variance scales quadratically
    Sum3 *= dval * dval * dval; // skewness scales like cube
}

void
StatLevel3Value::operator/=( double dval )
{
    if ( dval == 0. )
    {
        cerr << "ERROR: DEVISION BY ZERO!" << endl;
    }
    else
    {
        N    /= dval;
        Sum  /= dval;
        Sum2 /= dval;
        Sum3 /= dval;
    }
}


void
StatLevel3Value::operator=( double )
{
    throw RuntimeError( "Impossible to assign a  single double to StatLevel3Value" );
}

void
StatLevel3Value::operator=( Value* )
{
// #warning "Error handling has to be done"
    throw RuntimeError( "Impossible to assign a singlegeneral Value to StatLevel3Value" );
}

// -------------------- PRIVATE METHODS- ------------------------

double
StatLevel3Value::calcAvg() const
{
    uint32_t n  = N.getUnsignedInt();
    double   dn = N.getDouble();
    double   s  = Sum.getDouble();
    return ( n == 0 ) ? s / ( dn + 1e-256 )  : s / dn;
}

double
StatLevel3Value::calcVar() const
{
    uint32_t n  = N.getUnsignedInt();
    double   dn = N.getDouble();
    double   s  = Sum.getDouble();
    double   s2 = Sum2.getDouble();

    return ( n == 1 ) ? 0.             : 1. / ( dn - 1. ) * sqrt( s2 - 1. / dn * s * s );
}


double
StatLevel3Value::calcSkew() const
{
    uint32_t n  = N.getUnsignedInt();
    double   dn = N.getDouble();
    double   s  = Sum.getDouble();
    double   s2 = Sum2.getDouble();
    double   s3 = Sum3.getDouble();

    double Variance = calcVar();
    return ( n == 1 ) ? 0.             : ( 1. / dn *  ( s3 - 3. / dn * s2 * s + 2. / ( dn * dn ) * s * s * s ) ) / ( Variance * Variance * Variance );
}





void
StatLevel3Value::normalizeWithClusterCount( uint64_t _N )
{
    N.normalizeWithClusterCount( _N );
    Sum.normalizeWithClusterCount( _N );
    Sum2.normalizeWithClusterCount( _N );
    Sum3.normalizeWithClusterCount( _N );
}

void
StatLevel3Value::init_new()
{
    StatLevel3ValueConfig a;
    ( cube::StatLevel3Value::parameters ).push_back( a );
    index = ( cube::StatLevel3Value::parameters ).size() - 1;
};

void
StatLevel3Value::clone_new( const Value* v )
{
    index = ( static_cast<const StatLevel3Value*>( v ) )->index;
}

void
cube::StatLevel3Value::fromStream( Connection& connection )
{
    N.fromStream( connection );
    Sum.fromStream( connection );
    Sum2.fromStream( connection );
    Sum3.fromStream( connection );
}

void
cube::StatLevel3Value::toStream( Connection& connection ) const
{
    N.toStream( connection );
    Sum.toStream( connection );
    Sum2.toStream( connection );
    Sum3.toStream( connection );
}
