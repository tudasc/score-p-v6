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
 * \file CubeStatLevel4Value.cpp
 * \brief Defines the methods of the "StatLevel4Value".
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

std::vector<cube::StatLevel4ValueConfig> cube::StatLevel4Value::parameters;

StatLevel4Value::StatLevel4Value() : N( 1 ), Sum( 0. ), Sum2( 0. ), Sum3( 0. ), Sum4( 0. )
{
    isSingleValue = false;
}

StatLevel4Value::StatLevel4Value( uint32_t n,
                                  double   sum,
                                  double   sum2,
                                  double   sum3,
                                  double   sum4 ) : N( n ), Sum( sum ), Sum2( sum2 ), Sum3( sum3 ), Sum4( sum4 )
{
    isSingleValue = false;
}


unsigned
StatLevel4Value::getSize() const
{
    return
        N.getSize() +
        Sum.getSize() +
        Sum2.getSize() +
        Sum3.getSize() +
        Sum4.getSize();
}

/**
 * Single value of StatLevel4Value is impossible. Therefore an exception is thrown.
 */
double
StatLevel4Value::getDouble() const
{
    return 0.;
}

/**
 * Single value of StatLevel4Value is impossible. Therefore an exception is thrown.
 */
uint16_t
StatLevel4Value::getUnsignedShort() const
{
    return ( uint16_t )getDouble();
}

/**
 * Single value of StatLevel4Value is impossible. Therefore an exception is thrown.
 */
int16_t
StatLevel4Value::getSignedShort() const
{
    return ( int16_t )getDouble();
}


/**
 * Single value of StatLevel4Value is impossible. Therefore an exception is thrown.
 */
uint32_t
StatLevel4Value::getUnsignedInt() const
{
    return ( uint32_t )getDouble();
}

/**
 * Single value of StatLevel4Value is impossible. Therefore an exception is thrown.
 */
int32_t
StatLevel4Value::getSignedInt() const
{
    return ( int32_t )getDouble();
}



/**
 * Single value of StatLevel4Value is impossible. Therefore an exception is thrown.
 */
uint64_t
StatLevel4Value::getUnsignedLong() const
{
    return ( uint64_t )getDouble();
}

/**
 * Single value of StatLevel4Value is impossible. Therefore an exception is thrown.
 */
int64_t
StatLevel4Value::getSignedLong() const
{
    return ( int64_t )getDouble();
}



/**
 * Char is meaningless representation of StatLevel4Value. Therefore an exception is thrown.
 */
char
StatLevel4Value::getChar() const
{
    return ' ';
}



/**
 * Creates the string representation of the value.
 */
string
StatLevel4Value::getString() const
{
    double       avg  = calcAvg();
    double       var  = calcVar();
    double       skew = calcSkew();
    double       kur  = calcKur();
    stringstream sstr;
    string       str;
    sstr << "(" << avg << "," << var << "," << skew << "," << kur << ")"  << endl;
    sstr >> str;
    return str;
}




/**
 * Creates the copy and sets the value to 0.
 */
Value*
StatLevel4Value::clone() const
{
    return new StatLevel4Value( 1, 0., 0., 0., 0. );
}


/**
 * Creates the copy.
 */
Value*
StatLevel4Value::copy() const
{
// #warning "Missing interface for unsigned long long"
    return new StatLevel4Value( N.getUnsignedInt(), Sum.getDouble(), Sum2.getDouble(), Sum3.getDouble(), Sum4.getDouble() );
}


/**
 * Sets the value from stream and returns the position in stream right after the value.
 */
const char*
StatLevel4Value::fromStream( const char* cv )
{
    return Sum4.fromStream(
        Sum3.fromStream(
            Sum2.fromStream(
                Sum.fromStream(
                    N.fromStream( cv ) ) ) ) );
}

const double*
StatLevel4Value::fromStreamOfDoubles( const double* cv )
{
    return Sum4.fromStreamOfDoubles(
        Sum3.fromStreamOfDoubles(
            Sum2.fromStreamOfDoubles(
                Sum.fromStreamOfDoubles(
                    N.fromStreamOfDoubles( cv ) ) ) ) );
}



/**
 * Saves the value in the stream and returns the position in stream right after the value.
 */
char*
StatLevel4Value::toStream( char* cv ) const
{
    return Sum4.toStream(
        Sum3.toStream(
            Sum2.toStream(
                Sum.toStream(
                    N.toStream( cv ) ) ) ) );
}

/**
 * Transforms the endianness in the stream according its layout
 */
char*
StatLevel4Value::transformStream( char* cv, SingleValueTrafo* trafo ) const
{
    return Sum4.transformStream(
        Sum3.transformStream(
            Sum2.transformStream(
                Sum.transformStream(
                    N.transformStream( cv, trafo ), trafo ), trafo ), trafo ), trafo );
}



void
StatLevel4Value::operator+=( Value* chval )
{
    if ( chval == NULL )
    {
        return;
    }
    N    += ( ( Value* )( &( ( ( StatLevel4Value* )chval )->N ) ) );
    Sum  += ( ( Value* )( &( ( ( StatLevel4Value* )chval )->Sum ) ) );
    Sum2 += ( ( Value* )( &( ( ( StatLevel4Value* )chval )->Sum2 ) ) );
    Sum3 += ( ( Value* )( &( ( ( StatLevel4Value* )chval )->Sum3 ) ) );
    Sum4 += ( ( Value* )( &( ( ( StatLevel4Value* )chval )->Sum4 ) ) );
}

void
StatLevel4Value::operator-=( Value* chval )
{
    if ( chval == NULL )
    {
        return;
    }
    N    -= ( ( Value* )( &( ( ( StatLevel4Value* )chval )->N ) ) );
    Sum  -= ( ( Value* )( &( ( ( StatLevel4Value* )chval )->Sum ) ) );
    Sum2 -= ( ( Value* )( &( ( ( StatLevel4Value* )chval )->Sum2 ) ) );
    Sum3 -= ( ( Value* )( &( ( ( StatLevel4Value* )chval )->Sum3 ) ) );
    Sum4 -= ( ( Value* )( &( ( ( StatLevel4Value* )chval )->Sum4 ) ) );
}


void
StatLevel4Value::operator*=( double dval )
{
    Sum  *= dval;
    Sum2 *= dval * dval;
    Sum3 *= dval * dval * dval;
    Sum4 *= dval * dval * dval * dval;
}

void
StatLevel4Value::operator/=( double dval )
{
    if ( dval == 0. )
    {
        cerr << "ERROR: DEVISION BY ZERO!" << endl;
    }
    else
    {
        Sum  /= dval;
        Sum2 /= dval;
        Sum3 /= dval;
        Sum4 /= dval;
    }
}


void
StatLevel4Value::operator=( double )
{
    throw  RuntimeError( "Impossible to assign a  single double to StatLevel4Value" );
}


// overloaded new operator
void*
StatLevel4Value::operator new( size_t )
{
    return ( void* )stat4_preallocator.Get();
}
// delete operator overloaded
void
StatLevel4Value::operator delete( void* p )
{
    stat4_preallocator.Put( ( StatLevel4Value* )p );
}


void
StatLevel4Value::operator=( Value* )
{
// #warning "Error handling has to be done"
    throw RuntimeError( "Impossible to assign a single general Value to StatLevel4Value" );
}

// -------------------- PRIVATE METHODS- ------------------------

double
StatLevel4Value::calcAvg() const
{
    uint32_t n  = N.getUnsignedInt();
    double   dn = N.getDouble();
    double   s  = Sum.getDouble();

    return ( n == 0 ) ? s / ( dn + 1e-256 )  : s / dn;
}

double
StatLevel4Value::calcVar() const
{
    uint32_t n  = N.getUnsignedInt();
    double   dn = N.getDouble();
    double   s  = Sum.getDouble();
    double   s2 = Sum2.getDouble();
    return ( n == 1 ) ? 0.             : 1. / ( dn - 1. ) * sqrt( s2 - 1. / dn * s * s );
}



double
StatLevel4Value::calcSkew() const
{
    uint32_t n  = N.getUnsignedInt();
    double   dn = N.getDouble();
    double   s  = Sum.getDouble();
    double   s2 = Sum2.getDouble();
    double   s3 = Sum3.getDouble();
    double   s4 = Sum4.getDouble();

    double Variance = calcVar();

    return ( n == 1 ) ? 0.             : ( 1. / dn *  ( s3 - 3. / dn * s2 * s + 2. / ( dn * dn ) * s * s * s ) ) / ( Variance * Variance * Variance );
}




double
StatLevel4Value::calcKur() const
{
    uint32_t n  = N.getUnsignedInt();
    double   dn = N.getDouble();
    double   s  = Sum.getDouble();
    double   s2 = Sum2.getDouble();
    double   s3 = Sum3.getDouble();
    double   s4 = Sum4.getDouble();

    double Variance = calcVar();
    return ( n == 1 ) ? 0.             : ( 1. / dn * ( s4 - 4. / dn * s3 * s + 6. / ( dn * dn ) * s2 * s * s - 3. / ( dn * dn * dn ) * s * s * s * s ) ) / ( Variance * Variance * Variance * Variance ) - 3.;
}









void
StatLevel4Value::normalizeWithClusterCount( uint64_t _N )
{
    N.normalizeWithClusterCount( _N );
    Sum.normalizeWithClusterCount( _N );
    Sum2.normalizeWithClusterCount( _N );
    Sum3.normalizeWithClusterCount( _N );
    Sum4.normalizeWithClusterCount( _N );
}

void
StatLevel4Value::init_new()
{
    StatLevel4ValueConfig a;
    ( cube::StatLevel4Value::parameters ).push_back( a );
    index = ( cube::StatLevel4Value::parameters ).size() - 1;
};

void
StatLevel4Value::clone_new( const Value* v )
{
    index = ( static_cast<const StatLevel4Value*>( v ) )->index;
}

void
cube::StatLevel4Value::fromStream( Connection& connection )
{
    N.fromStream( connection );
    Sum.fromStream( connection );
    Sum2.fromStream( connection );
    Sum3.fromStream( connection );
    Sum4.fromStream( connection );
}

void
cube::StatLevel4Value::toStream( Connection& connection ) const
{
    N.toStream( connection );
    Sum.toStream( connection );
    Sum2.toStream( connection );
    Sum3.toStream( connection );
    Sum4.toStream( connection );
}
