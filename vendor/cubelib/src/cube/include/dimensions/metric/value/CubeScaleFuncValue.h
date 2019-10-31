/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2018                                                **
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
 * \file CubeScaleFuncValue.h
 * \brief  Provides the "scaling function value" as a symbolic function of the form a "* x^(b/c) * log(x)^(d)"
 ************************************************/
#ifndef __SCALE_FUNC_VALUE_H
#define __SCALE_FUNC_VALUE_H

#include <istream>
#include "CubeValue.h"

#include <iostream>
#include <map>
#include <vector>

namespace cube
{
class Connection;
class ScaleFuncValue;
extern Preallocator<ScaleFuncValue>scale_func_preallocator;

typedef struct sfvConfig
{
    sfvConfig()
    {
        asymptotic = true;
        coreCount  = 1;
    }
    int  dValue;
    int  coreCount;
    bool asymptotic;
}  __attribute__ ( ( __packed__ ) ) ScaleFuncValueConfig;

typedef struct measurement_t
{
    int    numProcesses;
    double mean;
    double width;


    measurement_t()
    {
        numProcesses = 0;
        mean         = 0.;
        width        = 0.;
    }

    measurement_t( const measurement_t& in )
    {
        numProcesses = in.numProcesses;
        mean         = in.mean;
        width        = in.width;
    }

    measurement_t&
    operator=( const measurement_t& in )
    {
        numProcesses = in.numProcesses;
        mean         = in.mean;
        width        = in.width;
        return *this;
    }
} measurement_t;

typedef std::vector<measurement_t>measurements_t;


/**
 * \brief Data type to represent the scaling behavior of call paths.
 *
 * ScaleFuncValue represents a collection of tuples, where each tuple is a single
 * term of the scaling behavior of a particular call path.
 * A single term has the form
 *
 *  a * x^(b/c) * log(x)^(d)
 *
 * and is represented by the tuple (a, b, c, d).
 *
 */
class ScaleFuncValue :
    public Value
{
public:
    /**
     * \brief Term datatype
     *
     * POD datatype that encapsulates the tuple (a, b, c, d), defines a convenience
     * getString - function and provides overloaded operators for algebra operations.
     */
    const static size_t prealloc_terms = 30; // /< Fixed maximum number of terms which can be stored
    struct Term
    {
        const static size_t length = 4; // /< # of values stored per term
        double              a;
        int32_t             b;
        uint32_t            c;
        int32_t             d;
        std::string
                            getString() const; // /< String representation (human-readable)
        std::string
                            getUID() const;    // /< String representation (UID)

        Term()
        {
            a = 0.;
            b = 0;
            c = 0;
            d = 0;
        }

        Term( const Term& in )
        {
            a = in.a;
            b = in.b;
            c = in.c;
            d = in.d;
        }

        Term&
        operator=( const Term& in )
        {
            a = in.a;
            b = in.b;
            c = in.c;
            d = in.d;
            return *this;
        }

        /**
         * Assign value from a Cube connection.
         * @param connection Cube connection stream.
         */
        virtual void
        fromStream( Connection& connection );

        /**
         * Send value through a Cube connection.
         * @param connection Cube connection stream.
         */
        virtual void
        toStream( Connection& connection ) const;

        double
        calculateValue( double x ) const;

        /**
         * Only add the leading coefficient for terms where b,c,d match
         * FIXME: operator+= of DoubleValue is wonky
         */
        Term&
        operator+=( const Term& rhs_ )
        {
            Term& rhs = const_cast<Term&>( rhs_ );
            return *this += ( rhs );
        }

        Term&
        operator+=( Term& rhs )
        {
            if ( b  == rhs.b
                 && c == rhs.c
                 && d   == rhs.d )
            {
                a += rhs.a;
                return *this;
            }
            else
            {
                throw RuntimeError( "Term, operator+=: term type does not match" );
            }
        }

        /**
         * Only add the leading coefficient for terms where b,c,d match
         * FIXME: operator+= of DoubleValue is wonky
         */
        Term&
        operator-=( const Term& rhs_ )
        {
            Term& rhs = const_cast<Term&>( rhs_ );
            if ( b  == rhs.b
                 && c == rhs.c
                 && d   == rhs.d )
            {
                a -= rhs.a;
                return *this;
            }
            else
            {
                throw RuntimeError( "Term, operator-=: term type does not match" );
            }
        }
    };

    // own methods and variables
    ScaleFuncValue();                                     // /< Create empty, reserve space
    ScaleFuncValue( const ScaleFuncValue& scaleFuncValue );
    ScaleFuncValue( const std::vector<double>& );         // /< Use a double aray
    ScaleFuncValue( const std::           vector<Term>&,
                    const measurements_t& measurements ); // /< Use existing Term objects

    virtual
    ~ScaleFuncValue()
    {
#ifdef __DEBUG
        std::cout << "Clear scaling func value  " << my_terms.size() << " and " << measurements.size() << " in " << std::hex << ( uint64_t ) this << std::dec << std::endl;
#endif
        my_terms.clear();
        measurements.clear();
#ifdef __DEBUG
        std::cout << "Cleared scaling func value  " << my_terms.size() << " and " << measurements.size() << " in " << std::hex << ( uint64_t ) this << std::dec << std::endl;
#endif
    };

    void
    addTerm( const Term& t,
             bool        doSort = true ); // /< Add term, specify whether to sort afterwards

    const Term&
    getTerm( size_t index ) const;

    Term&
    term( size_t index );

    double
    getParameter( int termIndex,
                  int parameterIndex );

    void
    setParameter( int    termIndex,
                  int    parameterIndex,
                  double value );

    void
    setMeasurements( const measurements_t& measurements );

    const measurements_t&
    getMeasurements() const;

    const Term&
    getDominantTerm() const;

    size_t
    getNumTerms()  const  // /< Number of terms
    {
        return my_terms.size();
    }

    size_t
    getNumMeasurements()  const  // /< Number of measurements
    {
        return measurements.size();
    }

    std::string
    getString( int,
               bool ) const;    // /< Specify number of terms to print

    // Required functions from superclass
    virtual double
    getDouble() const;
    virtual uint16_t
    getUnsignedShort() const;
    virtual int16_t
    getSignedShort() const;
    virtual uint32_t
    getUnsignedInt() const;
    virtual int32_t
    getSignedInt() const;
    virtual uint64_t
    getUnsignedLong() const;
    virtual int64_t
    getSignedLong() const;
    virtual char
    getChar() const;
    virtual std::string
    getString() const;


    // Implement custom algebra (required from superclass)

    virtual void
    operator+=( Value* );
    virtual void
    operator-=( Value* );

    virtual void
    operator*=( double );
    virtual void
    operator/=( double );
    virtual bool
    isZero() const; // / i.e. if for all terms, a = 0

    virtual void
    operator=( Value* )
    {
        throw RuntimeError( "ScaleFuncValue: not implemented" );
    }
    virtual void
    operator=( double )
    {
        throw RuntimeError( "ScaleFuncValue: not implemented" );
    }

    // Custom stream functions to pack all terms
    virtual const char*
    fromStream( const char* );
    virtual const double*
    fromStreamOfDoubles( const double* stream );

    virtual char*
    toStream( char* ) const;

    /**
     * Assign value from a Cube connection.
     * @param connection Cube connection stream.
     */
    virtual void
    fromStream( Connection& connection );

    /**
     * Send value through a Cube connection.
     * @param connection Cube connection stream.
     */
    virtual void
    toStream( Connection& connection ) const;

    virtual char*
    transformStream( char*,
                     SingleValueTrafo* ) const;
    virtual unsigned int
    getSize() const;


    virtual ScaleFuncValue*
    clone() const;
    virtual ScaleFuncValue*
    copy() const;

    void*
    operator new( size_t size );
    void
    operator delete( void* p );


    virtual void
    Free()
    {
        scale_func_preallocator.Put( this );
    }


    virtual DataType
    myDataType() const
    {
        return CUBE_DATA_TYPE_SCALE_FUNC;
    };
    virtual void
        normalizeWithClusterCount( uint64_t );

    void
    calculateValues( const std::vector<double>&,
                     std::      vector<double>& ) const;

    double
    calculateValue( double xValue ) const;

    void
    calculateErrors( const std::vector<double>&,
                     std::      vector<double>& ) const;

    ScaleFuncValueConfig&
    getConfig() const;

private:
    static
    std::vector<ScaleFuncValueConfig>parameters;
    size_t                           index;

    std::vector<Term>my_terms;              // /< Term storage, only data object.

    static int max_log_exp;                 // /< workaround for getDouble(); contains max for coefficient 'd' across all objects

    measurements_t measurements;

    void
    initialize();

    void
    op_plus_or_minus( const ScaleFuncValue* sfv,
                      int                   op );        // /< Perform addition or subtraction.



    void
    sortTerms(); // /< Sort internal term list

    virtual
    void
    init_new();

    virtual
    void
    clone_new( const Value* );

    double
    getAsymptoticDouble() const;
};

// Operators for Term algebra operations
bool
operator<( const ScaleFuncValue::Term& lhs_,
           const ScaleFuncValue::Term& rhs_ );
bool
operator==( const ScaleFuncValue::Term& lhs_,
            const ScaleFuncValue::Term& rhs_ );

bool
operator==( ScaleFuncValue::Term& lhs,
            ScaleFuncValue::Term& rhs );

inline bool
operator!=( const ScaleFuncValue::Term& lhs,
            const ScaleFuncValue::Term& rhs )
{
    return !operator==( lhs, rhs );
}
inline bool
operator>( const ScaleFuncValue::Term& lhs,
           const ScaleFuncValue::Term& rhs )
{
    return operator<( rhs, lhs );
}
inline bool
operator<=( const ScaleFuncValue::Term& lhs,
            const ScaleFuncValue::Term& rhs )
{
    return !operator>( lhs, rhs );
}
inline bool
operator>=( const ScaleFuncValue::Term& lhs,
            const ScaleFuncValue::Term& rhs )
{
    return !operator<( lhs, rhs );
}
inline ScaleFuncValue::Term
operator+( ScaleFuncValue::Term lhs, const ScaleFuncValue::Term& rhs )
{
    lhs += rhs;
    return lhs;
}

// Operators for ScaleFunc algebra operations (asymptotic consideration)
inline bool
operator<( ScaleFuncValue& a, ScaleFuncValue& b )
{
    return a.getDominantTerm() < b.getDominantTerm();
}

inline bool
operator>( ScaleFuncValue& a, ScaleFuncValue& b )
{
    return b.getDominantTerm() < a.getDominantTerm();
}

inline bool
operator>=( ScaleFuncValue& a, ScaleFuncValue& b )
{
    return !( b.getDominantTerm() > a.getDominantTerm() );
}

inline bool
operator<=( ScaleFuncValue& a, ScaleFuncValue& b )
{
    return !( b.getDominantTerm() < a.getDominantTerm() );
}

inline bool
operator==( ScaleFuncValue& a, ScaleFuncValue& b )
{
    return a.getDominantTerm() == b.getDominantTerm();
}

inline bool
operator!=( ScaleFuncValue& a, ScaleFuncValue& b )
{
    return !( a.getDominantTerm() == b.getDominantTerm() );
}
} // namespace cube

#endif
