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
 * \file CubeScaleFuncValue.cpp
 * \brief   Defines the methods of the "ScaleFuncValue" and the "Term" object.
 ************************************************/

#include "config.h"
#include <sstream>
#include <cstring>
#include <string>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <cassert>
#include "CubeValues.h"
#include "CubeScaleFuncValue.h"
#include "CubeConnection.h"

using namespace std;
using namespace cube;

std::vector<cube::ScaleFuncValueConfig>cube::ScaleFuncValue::parameters;

/***************************
        Term
***************************/

/**
 * Return a string representation of the term of the form
 * 3*x^(2)*log(x)^(3)
 */
string
ScaleFuncValue::Term::getString() const
{
    stringstream ss;
    ss.precision( 2 );
    ss << a;
    if ( b != 0 )
    {
        if ( b == ( int32_t )c )
        {
            ss << "*x";
        }
        else
        {
            ss << "*x**(" << showpoint << ( float )b << "/" << showpoint << ( float )c << ")";
        }
    }
    if ( d != 0 )
    {
        if ( d == 1 )
        {
            ss << "*log(x)";
        }
        else
        {
            ss << "*log(x)**(" << showpoint << ( float )d << ")";
        }
    }
    return ss.str();
}

/**
 * Use b, c and d to construct an identifier of the term structure
 */
string
ScaleFuncValue::Term::getUID() const
{
    stringstream ss;
    ss << "b" << b << "c" << c << "d" << d;
    return ss.str();
}

double
ScaleFuncValue::Term::calculateValue( double x ) const
{
    if ( c == 0 )
    {
        throw RuntimeError( "ScaleFuncValue::Term: c == 0 while evaluating " + getUID() );
    }
    double value = a * pow( x, ( ( double )b ) / c ) * pow( log2( x ), d );
    // cout << "term = " << this->getString() << endl;
    // cout << "term(" << x << ") = " << value << endl;
    return value;
}

double
ScaleFuncValue::getParameter( int termIndex, int parameterIndex )
{
    assert( 0 <= parameterIndex and parameterIndex <= 3 );

    switch ( parameterIndex )
    {
        case 0:
            return getTerm( termIndex ).a;
        case 1:
            return getTerm( termIndex ).b;
        case 2:
            return getTerm( termIndex ).c;
        case 3:
            return getTerm( termIndex ).d;
    }
    return -1;      // should not reach this point. Just to remove a warning.
}

void
ScaleFuncValue::setParameter( int termIndex, int parameterIndex, double value )
{
    assert( 0 <= parameterIndex and parameterIndex <= 3 );

    switch ( parameterIndex )
    {
        case 0:
            term( termIndex ).a = value;
            break;
        case 1:
            term( termIndex ).b = value;
            break;
        case 2:
            term( termIndex ).c = value;
            break;
        case 3:
            term( termIndex ).d = value;
            break;
    }
}


/* Comparison operators: Compare only asymptotic behavior of Terms lhs and rhs,
 * i.e. ignore coefficient "a"
 * FIXME: const_cast is ugly, but required since the Value classes do not define getDouble() and the like
 * as const (even though they probably should)!
 */
namespace cube
{
/**
 * Terms compare equally if the coefficients b, c and d match exactly.
 */
bool
operator==( const ScaleFuncValue::Term& lhs_,
            const ScaleFuncValue::Term& rhs_ )
{
    ScaleFuncValue::Term& lhs = const_cast<ScaleFuncValue::Term&>( lhs_ );
    ScaleFuncValue::Term& rhs = const_cast<ScaleFuncValue::Term&>( rhs_ );

    return lhs == rhs;
}

bool
operator==( ScaleFuncValue::Term& lhs,
            ScaleFuncValue::Term& rhs )
{
    bool beq = lhs.b == rhs.b,
         ceq = lhs.c == rhs.c,
         deq = lhs.d == rhs.d;
    if ( beq && ceq && deq )
    {
        return true;
    }

    else
    {
        return false;
    }
}

/**
 * Rank according to the exponents:
 * 1. If exponent of x is smaller, term is smaller; else, it is bigger.
 * 2. If exponent of x is the same, compare exponent of log
 */
bool
operator<( const ScaleFuncValue::Term& lhs_,
           const ScaleFuncValue::Term& rhs_ )
{
    ScaleFuncValue::Term& lhs  = const_cast<ScaleFuncValue::Term&>( lhs_ );
    ScaleFuncValue::Term& rhs  = const_cast<ScaleFuncValue::Term&>( rhs_ );
    double                blhs = lhs.b;
    double                clhs = lhs.c;
    double                brhs = rhs.b;
    double                crhs = rhs.c;

    double dx1 = blhs / clhs;
    double dx2 = brhs / crhs;

    if ( lhs.a == 0 and rhs.a > 0 )
    {
        return true;
    }

    if ( lhs.a > 0 and rhs.a == 0 )
    {
        return false;
    }

    // there should not be floating point comparison issues since b, c are stored as
    // integer numbers
    if ( dx1 < dx2 )
    {
        return true;
    }
    else if ( dx1 > dx2 )
    {
        return false;
    }
    else      // same exponent in x, compare log
    {
        if ( lhs.d < rhs.d )
        {
            return true;
        }

        else if ( lhs.d > rhs.d )
        {
            return false;
        }
        else    // some log, so compare a
        {
            return lhs.a < rhs.a;
        }
    }
}
} // namespace cube
/***************************
        ScaleFuncValue
***************************/

/* Static initializations */
int ScaleFuncValue::max_log_exp = 0;

/**
 * Default constructor, does nothing besides reserving space
 */
ScaleFuncValue::ScaleFuncValue()
{
    initialize();
}

/**
 * Take a vector of double numbers and construct a Term out of every 4
 * values. The size must be divisible by 4.
 * Terms are sorted after being added.
 */
ScaleFuncValue::ScaleFuncValue(
    const std::vector<double>& vals )
{
    size_t n = vals.size();
    if ( n % Term::length != 0 )
    {
        throw RuntimeError( "ScaleFuncValue: wrong number of values passed" );
    }
    if ( n > ScaleFuncValue::prealloc_terms * Term::length )
    {
        throw RuntimeError( "ScaleFuncValue (double constructor): argument to constructor exceeds maximum number of terms" );
    }
    initialize();
    for ( size_t i = 0; i < n / Term::length; ++i )
    {
        Term t;
        t.a = ( double )( vals[ Term::length * i + 0 ] );
        // b, c and d will be implicitly cast to integer type by operator=
        t.b = ( int32_t )( vals[ Term::length * i + 1 ] );
        t.c = ( uint32_t )( vals[ Term::length * i + 2 ] );
        if ( t.c == 0 )
        {
            throw new RuntimeError( "ScaleFuncValue: creating with c == 0 not allowed." );
        }
        t.d = ( int32_t )( vals[ Term::length * i + 3 ] );
        addTerm( t, false ); // sort after adding all terms
    }
    sortTerms();
}

/**
 * Take a vector of already initialized Term objects and add them. Also sorts afterwards.
 */
ScaleFuncValue::ScaleFuncValue(
    const std::vector<ScaleFuncValue::Term>& terms,
    const measurements_t&                    _measurements )
{
    if ( terms.size() > ScaleFuncValue::prealloc_terms )
    {
        throw RuntimeError( "ScaleFuncValue (term constructor): argument to constructor exceeds maximum number of terms." );
    }
    initialize();
    for ( size_t i = 0; i < terms.size(); i++ )
    {
        addTerm( terms[ i ] );
    }
    sortTerms();
    // cerr << "#measurements (constructor) = " << measurements.size();
    this->measurements = _measurements;
}

/**
 * Generic initialization for all constructed objects.
 */
void
ScaleFuncValue::initialize()
{
    // std::cerr.setf( std::ios_base::unitbuf );
    isSingleValue = false;
    my_terms.clear();
    measurements.clear();
    // cerr << "Measurements cleared in initialize()" << endl;
    // cerr << "After initialize() of " << this << endl;
}

/**
 * Return the specified term
 * \param index     index to return, error thrown if out of range
 * \return          a reference to the desired term
 */
const ScaleFuncValue::Term&
ScaleFuncValue::getTerm( size_t _index ) const
{
    if ( _index >= getNumTerms() )
    {
        throw RuntimeError( "ScaleFuncValue: term index out of bounds" );
    }
    return my_terms.at( _index );
}

/**
 * Return the specified term
 * \param index     index to return, error thrown if out of range
 * \return          a reference to the desired term
 */
ScaleFuncValue::Term&
ScaleFuncValue::term( size_t _index )
{
    if ( _index >= getNumTerms() )
    {
        throw RuntimeError( "ScaleFuncValue: term index out of bounds" );
    }
    return my_terms.at( _index );
}


/**
 * Sort the list of terms
 *
 * After sorting is done, update the highest log exponent.
 */
void
ScaleFuncValue::sortTerms()
{
    if ( my_terms.size() == 0 )
    {
        return;
    }

    // sort terms descending
    sort( my_terms.begin(), my_terms.end() );
    reverse( my_terms.begin(), my_terms.end() );

    const Term& maxTerm = getDominantTerm();

    // FIXME: thread safety
    if ( maxTerm.d > max_log_exp )
    {
        max_log_exp = maxTerm.d;
    }
}
/**
 * Insert a new term, optionally sort afterwards
 *
 * If sorting is performed, also update the highest log exponent for getDouble()
 * \param t         copy of t is stored
 * \param doSort    if false, no sorting will be performed
 */
void
ScaleFuncValue::addTerm( const Term& t, bool doSort )
{
    if ( t.a == 0 )
    {
        return;
    }

    int termIndex = -1;     // does term already exists?
    for ( size_t i = 0; i < my_terms.size(); i++ )
    {
        if ( my_terms.at( i ) == t )
        {
            termIndex = i;
            break;
        }
    }

    if ( termIndex == -1 )
    {
        my_terms.push_back( t );
    }
    else
    {
        my_terms[ termIndex ] += t;
    }

    if ( doSort )
    {
        sortTerms();
    }

    if ( my_terms.size() > ScaleFuncValue::prealloc_terms )
    {
        throw RuntimeError( "ScaleFuncValue::addTerm() exceeds maximum number of terms." );
    }
}

const ScaleFuncValue::Term&
ScaleFuncValue::getDominantTerm() const
{
    return my_terms.front();
}

/**
 * Return a string representation for display in the Cube GUI.
 * \return  a string containing the most dominant terms
 */
string
ScaleFuncValue::getString() const
{
    stringstream ss;

    if ( true )
    {
        for ( size_t i = 0; i < getNumMeasurements(); i++ )
        {
            ss << "(" << measurements.at( i ).numProcesses << "," << measurements.at( i ).mean << ")";
        }
    }

    if ( getConfig().asymptotic )
    {
        // cout << "getString (asymptotic) for coreCount = " << getConfig().coreCount << endl;
        const size_t max_print_terms = 3;
        return ss.str() + getString( min( max_print_terms, getNumTerms() ), false );
    }
    else
    {
        // cout << "getString (concrete) for coreCount = " << getConfig().coreCount << endl;
        stringstream tmp;
        tmp << calculateValue( getConfig().coreCount );
        return ss.str() + tmp.str();
    }
}

/**
 * Return a string representation of the object with variable content, useful for debug output
 * \param num_print_terms   number of terms to return, "-1" means all terms
 * \param most_dominant     where to start/how to sort: if true, start with asymptotically dominant terms
 * \return                  a single string representing the object
 */
string
ScaleFuncValue::getString( int num_print_terms, bool most_dominant = true ) const
{
    if ( getNumTerms() == 0 )
    {
        /* getString() is called for empty SFV objects sometimes, which leads to getTerm raising
         * an exception. The call is spurious and the objects are in fact supposed to
         * be empty.
         */
        return "0";
    }
    if ( num_print_terms == -1 )
    {
        num_print_terms = getNumTerms();
    }
    string tmp = "";
    // num_print_terms is defacto >0 at this place
    for ( size_t i = 0; i < ( size_t )num_print_terms; ++i )
    {
        size_t _index = most_dominant ? getNumTerms() - i - 1 : i;
        tmp += ( getTerm( _index ) ).getString();
        if ( i < ( size_t )num_print_terms - 1 )
        {
            tmp += " + ";
        }
    }
    return tmp;
}

/**
 * \brief Return an object of the same type, but with no data.
 */
ScaleFuncValue*
ScaleFuncValue::clone() const
{
    ScaleFuncValue* to_return = new ScaleFuncValue();
    to_return->clone_new( this );
    return to_return;
}

/**
 * Calculate total size in bytes needed to store SFV object.
 * FIXME: Includes "padded" storage since it is not trivial to set the size
 * of a datatype depending on the metric specification
 * \return size in bytes nedded to store the object
 */
unsigned int
ScaleFuncValue::getSize() const
{
    unsigned int   s  = 0;
    UnsignedValue* us = new UnsignedValue();
    Term           t;
    s += sizeof( t.a ) + sizeof( t.b ) + sizeof( t.c ) + sizeof( t.d ); // single term
    s *= prealloc_terms;
    s += 2 * us->getSize();                                             // store number of terms and measurements
    s += 10 * ( sizeof( measurement_t ) );
    delete us;
    return s;
}

/**
 * Create a copy of the object with the same data.
 * FIXME: as in other classes, copy constructor should be provided
 */
ScaleFuncValue*
ScaleFuncValue::copy() const
{
    ScaleFuncValue* ret = new ScaleFuncValue( my_terms, measurements );
    ret->clone_new( this );
    return ret;
}

/* STREAM FUNCTIONS */
/**
 * \brief Load stored object
 *
 * From a provided bytestream, reconstruct the object by reading first the
 * actual number of stored terms and ignoring the padding that follows.
 * Start here if debugging the storage logic.
 * \param   cv  start adress of the input bytestream
 * \return      original stream "cv" incremented by object size
 */
const char*
ScaleFuncValue::fromStream( const char* cv )
{
    my_terms.clear();
    measurements.clear();
    const char*    stream          = cv;
    UnsignedValue* numMeasurements = new UnsignedValue();
    UnsignedValue* usv             = new UnsignedValue();
    DoubleValue*   dv              = new DoubleValue();
    SignedValue*   sv1             = new SignedValue();
    SignedValue*   sv2             = new SignedValue();
    // extract actual number of terms stored
    stream = usv->fromStream( stream );
    // extract number of measurements
    stream = numMeasurements->fromStream( stream );

    UnsignedValue* numProcesses = new UnsignedValue();
    DoubleValue*   mean         = new DoubleValue();
    DoubleValue*   width        = new DoubleValue();

    // cout << "##measurements = " <<  numMeasurements->getUnsignedInt() << endl;

    size_t my_num_terms = usv->getUnsignedInt();
    for ( size_t i = 0; i < my_num_terms; ++i )
    {
        Term t;
        stream = sv2->fromStream(
            usv->fromStream(
                sv1->fromStream(
                    dv->fromStream( stream )
                    )
                )
            );
        t.a = dv->getDouble();
        t.b = sv1->getSignedInt();
        t.c = usv->getUnsignedInt();
        t.d = sv2->getSignedInt();


        addTerm( t, false );
    }

    for ( size_t i = 0; i < numMeasurements->getUnsignedInt(); i++ )
    {
        measurement_t measurement;

        stream = numProcesses->fromStream( stream );
        stream = mean->fromStream( stream );
        stream = width->fromStream( stream );

        measurement.mean         = mean->getDouble();
        measurement.numProcesses = numProcesses->getUnsignedInt();
        measurement.width        = width->getDouble();

        measurements.push_back( measurement );
    }

    delete usv;
    delete dv;
    delete sv1;
    delete sv2;
    delete numMeasurements;
    delete numProcesses;
    delete mean;
    delete width;
    // sort term list
    sortTerms();
    // pad offset for file i/o functions
    return cv + getSize();
}


/**
 * \brief Load stored object
 *
 * From a provided bytestream, reconstruct the object by reading first the
 * actual number of stored terms and ignoring the padding that follows.
 * Start here if debugging the storage logic.
 * \param   cv  start adress of the input bytestream
 * \return      original stream "cv" incremented by object size
 */
const double*
ScaleFuncValue::fromStreamOfDoubles( const double* cv )
{
    my_terms.clear();
    measurements.clear();
    const double*  stream          = cv;
    UnsignedValue* usv             = new UnsignedValue();
    UnsignedValue* numMeasurements = new UnsignedValue();
    DoubleValue*   dv              = new DoubleValue();
    SignedValue*   sv1             = new SignedValue();
    SignedValue*   sv2             = new SignedValue();
    // extract actual number of terms stored
    stream = usv->fromStreamOfDoubles( stream );
    stream = numMeasurements->fromStreamOfDoubles( stream );

    size_t my_num_terms = usv->getUnsignedInt();
    for ( size_t i = 0; i < my_num_terms; ++i )
    {
        Term t;
        stream = sv2->fromStreamOfDoubles(
            usv->fromStreamOfDoubles(
                sv1->fromStreamOfDoubles(
                    dv->fromStreamOfDoubles( stream )
                    )
                )
            );
        t.a = dv->getDouble();
        t.b = sv1->getSignedInt();
        t.c = usv->getUnsignedInt();
        t.d = sv2->getSignedInt();


        addTerm( t, false );
    }

    UnsignedValue* numProcesses = new UnsignedValue();
    DoubleValue*   mean         = new DoubleValue();
    DoubleValue*   width        = new DoubleValue();

    for ( size_t i = 0; i < numMeasurements->getUnsignedInt(); i++ )
    {
        measurement_t measurement;

        stream = numProcesses->fromStreamOfDoubles( stream );
        stream = mean->fromStreamOfDoubles( stream );
        stream = width->fromStreamOfDoubles( stream );

        measurement.mean         = mean->getDouble();
        measurement.numProcesses = numProcesses->getUnsignedInt();
        measurement.width        = width->getDouble();

        measurements.push_back( measurement );
    }

    delete usv;
    delete dv;
    delete sv1;
    delete sv2;
    delete numMeasurements;
    delete numProcesses;
    delete mean;
    delete width;
    // sort term list
    sortTerms();
    // pad offset for file i/o functions
    return cv + getSize();
}


/**
 * \brief Write object to stream
 *
 * See fromStream() as this function is its "inverse".
 * \param   cv  start adress of output stream
 * \return      original stream "cv" incremented by object size
 */
char*
ScaleFuncValue::toStream( char* cv ) const
{
    char* stream = cv;
    // store actual number of terms first
    UnsignedValue* us = new UnsignedValue( getNumTerms() );
    // store number of measured data second
    UnsignedValue* numMeasurements = new UnsignedValue( getNumMeasurements() );

    UnsignedValue* numProcesses = new UnsignedValue();
    DoubleValue*   mean         = new DoubleValue();
    DoubleValue*   width        = new DoubleValue();

    UnsignedValue* usv = new UnsignedValue();
    DoubleValue*   dv  = new DoubleValue();
    SignedValue*   sv1 = new SignedValue();
    SignedValue*   sv2 = new SignedValue();
    stream = us->toStream( stream );
    stream = numMeasurements->toStream( stream );

    // only store terms that have actually been set
    for ( size_t i = 0; i < getNumTerms(); ++i )
    {
        const Term& t = getTerm( i );
        dv->
        operator=( t.a );

        sv1->
        operator=( t.b );

        usv->
        operator=( t.c );

        sv2->
        operator=( t.d );

        stream = sv2->toStream(
            usv->toStream(
                sv1->toStream(
                    dv->toStream( stream )
                    )
                )
            );
    }

    for ( size_t i = 0; i < getNumMeasurements(); i++ )
    {
        measurement_t measurement = measurements.at( i );

        numProcesses->
        operator=( measurement.numProcesses );

        mean->
        operator=( measurement.mean );

        width->
        operator=( measurement.width );

        stream = numProcesses->toStream( stream );
        stream = mean->toStream( stream );
        stream = width->toStream( stream );
    }

    delete us;
    delete usv;
    delete dv;
    delete sv1;
    delete sv2;
    delete numMeasurements;
    delete numProcesses;
    delete mean;
    delete width;
    // pad offset for file i/o functions
    return cv + getSize();
}

char*
ScaleFuncValue::transformStream( char* cv, SingleValueTrafo* trafo ) const
{
    char*          stream          = cv;
    UnsignedValue* us              = new UnsignedValue( getNumTerms() );
    UnsignedValue* numMeasurements = new UnsignedValue( getNumMeasurements() );
    UnsignedValue* usv             = new UnsignedValue();
    DoubleValue*   dv              = new DoubleValue();
    SignedValue*   sv1             = new SignedValue();
    SignedValue*   sv2             = new SignedValue();
    stream = us->transformStream( stream, trafo );
    if ( stream == cv )
    {
        delete us;
        delete usv;
        delete dv;
        delete sv1;
        delete sv2;
        delete numMeasurements;
        return stream;
    }

    stream = numMeasurements->transformStream( stream, trafo );

    for ( size_t i = 0; i < getNumTerms(); ++i )
    {
        stream = sv2->transformStream(
            usv->transformStream(
                sv1->transformStream(
                    dv->transformStream( stream, trafo ), trafo
                    ), trafo
                ), trafo
            );
    }

    UnsignedValue* numProcesses = new UnsignedValue();
    DoubleValue*   mean         = new DoubleValue();
    DoubleValue*   width        = new DoubleValue();

    for ( size_t i = 0; i < getNumMeasurements(); i++ )
    {
        stream = numProcesses->transformStream( stream, trafo );
        stream = mean->transformStream( stream, trafo );
        stream = width->transformStream( stream, trafo );
    }

    delete us;
    delete usv;
    delete dv;
    delete sv1;
    delete sv2;
    delete numMeasurements;
    return cv + getSize();
}

void
ScaleFuncValue::normalizeWithClusterCount( uint64_t count )
{
    for ( size_t i = 0; i < getNumTerms(); ++i )
    {
        // only value that can be normalized
        term( i ).a = getTerm( i ).a / count;
    }
}

void
ScaleFuncValue::calculateValues( const vector<double>& xValues, vector<double>& yValues ) const
{
    for ( vector<double>::const_iterator it = xValues.begin(); it != xValues.end(); ++it )
    {
        double yValue = 0;
        for ( size_t numTerms = 0; numTerms < getNumTerms(); ++numTerms )
        {
            yValue += getTerm( numTerms ).calculateValue( *it );
        }
        yValues.push_back( yValue );
    }
}

double
ScaleFuncValue::calculateValue( double xValue ) const
{
    vector<double>_xValues, yValues;
    _xValues.push_back( xValue );
    calculateValues( _xValues, yValues );
    return yValues.front();
}

void
ScaleFuncValue::calculateErrors( const vector<double>&, vector<double>& ) const
{
//	for (double x : xValues)
//	{
//		errors.push_back(1); // TODO some testdata
//	}
}


/**************************************
        ALGEBRA
**************************************/

/**
 * Copy assignment
 */
/*
   ScaleFuncValue&
   ScaleFuncValue::operator=( ScaleFuncValue* comp )
   {
    my_terms = comp->my_terms;
    return *this;
   }
 */


/**
 * Add or subtract another SFV instance term-by-term.
 * Algorithm: The list of terms is sorted on construction. Start at the beginning,
 * \param sfv   the other operand
 * \param op    either +1 or -1, choose between addition and subtraction
 */
void
ScaleFuncValue::op_plus_or_minus( const ScaleFuncValue* sfv, int op )
{
    // ScaleFuncValue *tmp = const_cast<ScaleFuncValue*>(sfv);
    // cout << "+/-: " << getString() << "  " << op << "  " << tmp->getString() << endl << flush;

    ScaleFuncValue* s = const_cast<ScaleFuncValue*>( sfv );
    for ( size_t i = 0; i < s->getNumTerms(); i++ )
    {
        ScaleFuncValue::Term term = s->term( i );
        term.a *= op;
        addTerm( term );
    }

    return;
}

void
ScaleFuncValue::operator+=( Value* v )
{
    ScaleFuncValue* sfv = dynamic_cast<ScaleFuncValue*>( v );
    if ( sfv )
    {
        op_plus_or_minus( sfv, +1 );
    }
    else
    {
        throw RuntimeError( "ScaleFuncValue: invalid pointer for operator+" );
    }
}
void
ScaleFuncValue::operator-=( Value* v )
{
    ScaleFuncValue* sfv = dynamic_cast<ScaleFuncValue*>( v );
    if ( sfv )
    {
        op_plus_or_minus( sfv, -1 );
    }
    else
    {
        throw RuntimeError( "ScaleFuncValue: invalid pointer for operator-" );
    }
}
void
ScaleFuncValue::operator*=( double d )
{
    for ( size_t i = 0; i < getNumTerms(); ++i )
    {
        term( i ).a *= d;
    }
}
void
ScaleFuncValue::operator/=( double d )
{
    if ( d == 0 )
    {
        throw RuntimeError( "ScaleFuncValue: division by zero" );
    }
    for ( size_t i = 0; i < getNumTerms(); ++i )
    {
        term( i ).a /= d;
    }
}
bool
ScaleFuncValue::isZero() const
{
    return getNumTerms() == 0;
}
// overloaded new operator
void*
ScaleFuncValue::operator new( size_t )
{
    return ( void* )scale_func_preallocator.Get();
}
// delete operator overloaded
void
ScaleFuncValue::operator delete( void* p )
{
    scale_func_preallocator.Put( ( ScaleFuncValue* )p );
}

/**
 * Return a double representing the scaling behavior of the SFV object.
 * There are two different modes:
 * 1) Asymptotic and 2) for a fixed number of processes p
 */
double
ScaleFuncValue::getDouble() const
{
    assert( getConfig().asymptotic );
    if ( getConfig().asymptotic )
    {
        return getAsymptoticDouble();
    }
    else
    {
        // cout << "concrete value for coreCount = " << getConfig().coreCount << endl;
        return calculateValue( getConfig().coreCount );
    }
}

double
ScaleFuncValue::getAsymptoticDouble() const
{
    // cout << "asymptotic value" << endl;
    if ( isZero() )
    {
        return 0.;
    }

    // cout << "# of term: " << getNumTerms() << endl;
    const Term& maxTerm = getDominantTerm();

    double primary   = ( double )( maxTerm.b ) / ( double )( maxTerm.c );
    int    secundary = maxTerm.d;
    double tertiary  = maxTerm.a;

    return primary * 1000 + secundary + tertiary / 1000;
}

uint16_t
ScaleFuncValue::getUnsignedShort() const
{
    return ( uint16_t )getDouble();
}
int16_t
ScaleFuncValue::getSignedShort() const
{
    return ( int16_t )getDouble();
}
uint32_t
ScaleFuncValue::getUnsignedInt() const
{
    return ( uint32_t )getDouble();
}
int32_t
ScaleFuncValue::getSignedInt() const
{
    return ( int32_t )getDouble();
}

uint64_t
ScaleFuncValue::getUnsignedLong() const
{
    return ( uint64_t )getDouble();
}
int64_t
ScaleFuncValue::getSignedLong() const
{
    return ( uint64_t )getDouble();
}
char
ScaleFuncValue::getChar() const
{
    return ' ';
}

void
ScaleFuncValue::init_new()
{
    ScaleFuncValueConfig a;
    ( cube::ScaleFuncValue::parameters ).push_back( a );
    index = ( cube::ScaleFuncValue::parameters ).size() - 1;
}

void
ScaleFuncValue::clone_new( const Value* v )
{
    index = ( static_cast<const ScaleFuncValue*>( v ) )->index;
}

ScaleFuncValueConfig&
ScaleFuncValue::getConfig() const
{
    return ScaleFuncValue::parameters[ index ];
}

ScaleFuncValue::ScaleFuncValue ( const ScaleFuncValue& scaleFuncValue )
{
    index = scaleFuncValue.index;
    initialize();
    for ( vector<Term>::const_iterator it = scaleFuncValue.my_terms.begin(); it != scaleFuncValue.my_terms.end(); ++it )
    {
        addTerm( *it );
    }

    this->setMeasurements( scaleFuncValue.measurements );
}

void
ScaleFuncValue::setMeasurements( const measurements_t& measurements )
{
    this->measurements = measurements;
}

const measurements_t&
ScaleFuncValue::getMeasurements() const
{
    return measurements;
}

void
cube::ScaleFuncValue::Term::fromStream( Connection& connection )
{
    connection >> a;
    connection >> b;
    connection >> c;
    connection >> d;
}

void
cube::ScaleFuncValue::Term::toStream( Connection& connection ) const
{
    connection << a;
    connection << b;
    connection << c;
    connection << d;
}

void
cube::ScaleFuncValue::fromStream( Connection& connection )
{
    my_terms.clear();
    measurements.clear();
    UnsignedValue* numMeasurements = new UnsignedValue();
    UnsignedValue* usv             = new UnsignedValue();
    DoubleValue*   dv              = new DoubleValue();
    SignedValue*   sv1             = new SignedValue();
    SignedValue*   sv2             = new SignedValue();

    // extract actual number of terms stored
    usv->fromStream( connection );
    // extract number of measurements
    numMeasurements->fromStream( connection );

    UnsignedValue* numProcesses = new UnsignedValue();
    DoubleValue*   mean         = new DoubleValue();
    DoubleValue*   width        = new DoubleValue();

    // cout << "##measurements = " <<  numMeasurements->getUnsignedInt() << endl;

    size_t my_num_terms = usv->getUnsignedInt();
    for ( size_t i = 0; i < my_num_terms; ++i )
    {
        Term t;
        sv2->fromStream( connection );
        usv->fromStream( connection );
        sv1->fromStream( connection );
        dv->fromStream( connection );

        t.a = dv->getDouble();
        t.b = sv1->getSignedInt();
        t.c = usv->getUnsignedInt();
        t.d = sv2->getSignedInt();


        addTerm( t, false );
    }

    for ( size_t i = 0; i < numMeasurements->getUnsignedInt(); i++ )
    {
        measurement_t measurement;

        numProcesses->fromStream( connection );
        mean->fromStream( connection );
        width->fromStream( connection );

        measurement.mean         = mean->getDouble();
        measurement.numProcesses = numProcesses->getUnsignedInt();
        measurement.width        = width->getDouble();

        measurements.push_back( measurement );
    }

    delete usv;
    delete dv;
    delete sv1;
    delete sv2;
    delete numMeasurements;
    delete numProcesses;
    delete mean;
    delete width;
    // sort term list
    sortTerms();

    UnsignedValue indexValue;
    indexValue.fromStream( connection );
    index = indexValue.getUnsignedInt();
}

void
cube::ScaleFuncValue::toStream( Connection& connection ) const
{
    // store actual number of terms first
    UnsignedValue* us = new UnsignedValue( getNumTerms() );
    // store number of measured data second
    UnsignedValue* numMeasurements = new UnsignedValue( getNumMeasurements() );

    UnsignedValue* numProcesses = new UnsignedValue();
    DoubleValue*   mean         = new DoubleValue();
    DoubleValue*   width        = new DoubleValue();

    UnsignedValue* usv = new UnsignedValue();
    DoubleValue*   dv  = new DoubleValue();
    SignedValue*   sv1 = new SignedValue();
    SignedValue*   sv2 = new SignedValue();
    us->toStream( connection );
    numMeasurements->toStream( connection );

    // only store terms that have actually been set
    for ( size_t i = 0; i < getNumTerms(); ++i )
    {
        if ( i >= getNumTerms() )
        {
            throw RuntimeError( "ScaleFuncValue: term index out of bounds" );
        }
        Term t = my_terms.at( i );

        dv->
        operator=( t.a );

        sv1->
        operator=( t.b );

        usv->
        operator=( t.c );

        sv2->
        operator=( t.d );

        sv2->toStream( connection );
        usv->toStream( connection );
        sv1->toStream( connection );
        dv->toStream( connection );
    }

    for ( size_t i = 0; i < getNumMeasurements(); i++ )
    {
        measurement_t measurement = measurements.at( i );

        numProcesses->
        operator=( measurement.numProcesses );

        mean->
        operator=( measurement.mean );

        width->
        operator=( measurement.width );

        numProcesses->toStream( connection );
        mean->toStream( connection );
        width->toStream( connection );
    }

    delete us;
    delete usv;
    delete dv;
    delete sv1;
    delete sv2;
    delete numMeasurements;
    delete numProcesses;
    delete mean;
    delete width;

    UnsignedValue indexValue( index );
    indexValue.toStream( connection );
}
