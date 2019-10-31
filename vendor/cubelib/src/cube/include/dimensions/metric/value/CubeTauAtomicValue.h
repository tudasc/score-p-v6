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
 * \file CubeTauAtomicValue.h
 * \brief Provide a value for atomic metric of Tau.
 *
 * It saves an int N, MinDouble, MaxDouble and two doubles (\f$ \sum_i^N {x_i} \f$ and \f$ \sum_i^N x_i^2 \f$) for calculation of mean and variance. Values have to be exclusive.
 *
 *
 */

#ifndef __TAU_ATOMIC_VALUE_H
#define __TAU_ATOMIC_VALUE_H

#include <istream>

#include <cstring>
#include <string>
#include <iostream>
#include "CubeValues.h"
#include "CubeTrafos.h"

enum TauAtomicValuePivot { TAU_AVG = 0, TAU_DEV = 1, TAU_N = 2, TAU_MIN = 3, TAU_MAX = 4, TAU_SUM = 5, TAU_SUM2 = 6 };


namespace cube
{
typedef   struct
{
    TauAtomicValuePivot pivot;
}  __attribute__ ( ( __packed__ ) ) TauAtomicValueConfig;



class Connection;
class TauAtomicValue;
extern Preallocator<TauAtomicValue> tau_preallocator;


/**
 *  The TAU value for atomic metrics. NOT TESTED
 */
class TauAtomicValue : public Value
{
private:

    static
    std::vector<TauAtomicValueConfig> parameters;
    size_t                            index;

    double
    calcAvg() const;

    double
    calcVar() const;

    double
    calcDeviation() const;

protected:
    UnsignedValue  N;
    MinDoubleValue MinValue;
    MaxDoubleValue MaxValue;
    DoubleValue    Sum;
    DoubleValue    Sum2;



public:
    TauAtomicValue();
    TauAtomicValue( uint32_t,
                    double,
                    double,
                    double,
                    double );
//     TauAtomicValue( char* );

    virtual
    ~TauAtomicValue()
    {
    };                                                                 // /< Vitual destructor allows, that every inherited class destroy itself properly.
    inline
    virtual unsigned
    getSize() const
    {
        return
            N.getSize() +
            MinValue.getSize() +
            MaxValue.getSize() +
            Sum.getSize() +
            Sum2.getSize();
    }
    virtual double
    getDouble() const;                                     // /< Returns the double representation of itself, if possible.
    virtual uint16_t
    getUnsignedShort() const;                              // /< Returns the unsigned 16bit representation of itself, if possible.
    virtual int16_t
    getSignedShort() const;                                // /< Returns the signed 16bit representation of itself, if possible.
    virtual uint32_t
    getUnsignedInt() const;                                // /< Returns the unsigned 32bit representation of itself, if possible.
    virtual int32_t
    getSignedInt() const;                                  // /< Returns the signed 32bit representation of itself, if possible.
    virtual uint64_t
    getUnsignedLong() const;                               // /< Returns the unsigned 64bit representation of itself, if possible.
    virtual int64_t
    getSignedLong() const;                                 // /< Returns the signed 64bit representation of itself, if possible.
    virtual char
    getChar() const;                                       // /< Returns the single byte representation of itself, if possible.
    virtual std::string
    getString() const;                                     // /< Returns the textual representation of itself, if possible. Used to save itself in Cube3 format.

    virtual UnsignedValue
    getN() const
    {
        return N;
    };
    virtual MinDoubleValue
    getMinValue() const
    {
        return MinValue;
    };
    virtual MaxDoubleValue
    getMaxValue() const
    {
        return MaxValue;
    };
    virtual DoubleValue
    getSum() const
    {
        return Sum;
    };
    virtual DoubleValue
    getSum2() const
    {
        return Sum2;
    };



    virtual const char*
    fromStream( const char* );                                                        // /< Constructs itself from the stream. The first stream byte used as starting point.
    virtual const double*
    fromStreamOfDoubles( const double* stream );
    virtual char*
    toStream( char* ) const;                                                          // /< Write to the stream the stream-representation of itself. The first stream byte used as starting point.

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
                     SingleValueTrafo* ) const;                                           // /< Applyes the transformation on the stream according to its layout. Used to deal with different endianess. Needed for comples types with non trivial layout.

    inline
    virtual Value*
    clone() const
    {
        TauAtomicValue* _v = new TauAtomicValue();
        _v->clone_new( this );
        return _v;
    }
    inline
    virtual Value*
    copy() const
    {
        TauAtomicValue* _v = new TauAtomicValue( N.getUnsignedInt(), MinValue.getDouble(), MaxValue.getDouble(), Sum.getDouble(), Sum2.getDouble() );
        _v->clone_new( this );
        return _v;
    }                                                                   // /< Makes a copy of itself and keeps the value.


    inline
    virtual void
    operator+=( Value* chval )
    {
        if ( chval == NULL )
        {
            return;
        }
        N        += ( ( Value* )( &( ( ( TauAtomicValue* )chval )->N ) ) );
        MinValue += ( ( Value* )( &( ( ( TauAtomicValue* )chval )->MinValue ) ) );
        MaxValue += ( ( Value* )( &( ( ( TauAtomicValue* )chval )->MaxValue ) ) );
        Sum      += ( ( Value* )( &( ( ( TauAtomicValue* )chval )->Sum ) ) );
        Sum2     += ( ( Value* )( &( ( ( TauAtomicValue* )chval )->Sum2 ) ) );
    }

    inline
    virtual void
    operator-=( Value* chval )
    {
        if ( chval == NULL )
        {
            return;
        }
        N        -= ( ( Value* )( &( ( ( TauAtomicValue* )chval )->N ) ) );
        MinValue -= ( ( Value* )( &( ( ( TauAtomicValue* )chval )->MinValue ) ) );
        MaxValue -= ( ( Value* )( &( ( ( TauAtomicValue* )chval )->MaxValue ) ) );
        Sum      -= ( ( Value* )( &( ( ( TauAtomicValue* )chval )->Sum ) ) );
        Sum2     -= ( ( Value* )( &( ( ( TauAtomicValue* )chval )->Sum2 ) ) );
    }

    inline
    virtual void
    operator*=( double dval )
    {
        N        *= dval;
        MinValue *= dval;
        MaxValue *= dval;
        Sum      *= dval;
        Sum2     *= dval;
    }                                 // needed by algebra tools

    inline
    virtual void
    operator/=( double dval )
    {
        if ( dval == 0. )
        {
            std::cerr << "ERROR: DEVISION BY ZERO!" << std::endl;
        }
        N        /= dval;
        MinValue /= dval;
        MaxValue /= dval;
        Sum      /= dval;
        Sum2     /= dval;
    }

    void*
    operator new( size_t size );
    void
    operator delete( void* p );

    virtual void
    Free()
    {
        delete ( TauAtomicValue* )this;
    }

    virtual void
    operator=( double );                                     // /< Allows to assign its value from the build in double.

    virtual void
    operator=( Value* );                                     // /< Allows to assign its value from another object of same type. [WARNING, real type is not checked]


    virtual bool
    isZero() const
    {
        return Sum.isZero() && Sum2.isZero() && MinValue.isZero() && MaxValue.isZero() && N.isZero();
    };

    virtual bool
    asInclusiveMetric() const
    {
        return false;
    }

    virtual DataType
    myDataType() const
    {
        return CUBE_DATA_TYPE_TAU_ATOMIC;
    };                                                   // not supported yet
    virtual void
        normalizeWithClusterCount( uint64_t );

    virtual
    void
    init_new();

    virtual
    void
    clone_new( const Value* );

    TauAtomicValueConfig&
    getConfig();
};
}



#endif
