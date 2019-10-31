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
 * \file CubeComplexValue.h
 * \brief  Provides the experimental complex value, consisting of two "Value"'s. Needed for future to support atomic events.
 ************************************************/
#ifndef __COMPLEX_VALUE_H
#define __COMPLEX_VALUE_H

#include <istream>
#include <cmath>
#include "CubeDoubleValue.h"

#include <iostream>

namespace cube
{
class Connection;
class ComplexValue;
extern Preallocator<ComplexValue>complex_preallocator;
typedef   struct
{
    int pivot;
}  __attribute__ ( ( __packed__ ) ) ComplexValueConfig;


class ComplexValue :
    public Value
{
private:
    static
    std::vector<ComplexValueConfig>parameters;
    size_t                         index;

protected:
    DoubleValue r_value;                      // / "heart 1" of the value.
    DoubleValue i_value;                      // / "heart 2" of the value.



public:
    ComplexValue();

    ComplexValue( double,
                  double );


    virtual
    ~ComplexValue()
    {
    };

    inline
    virtual unsigned
    getSize() const
    {
        return r_value.getSize() + i_value.getSize();
    }
    virtual double
    getDouble() const
    {
        double r = r_value.getDouble();
        double i = i_value.getDouble();

        return sqrt( r * r + i * i );
    }
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

    virtual DoubleValue
    getRealValue() const
    {
        return r_value;
    };
    virtual DoubleValue
    getImaginaryValue() const
    {
        return i_value;
    };

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

    inline
    virtual ComplexValue*
    clone() const
    {
        return new ComplexValue( 0., 0. );
    }
    inline
    virtual ComplexValue*
    copy() const
    {
        return new ComplexValue( r_value.getDouble(),
                                 i_value.getDouble()
                                 );
    }

    void*
    operator new( size_t size );
    void
    operator delete( void* p );


    inline
    virtual void
    operator+=( Value* chval )
    {
        if ( chval == NULL )
        {
            return;
        }
        r_value += ( ( Value* )( &( ( ( ComplexValue* )chval )->r_value ) ) );
        i_value += ( ( Value* )( &( ( ( ComplexValue* )chval )->i_value ) ) );
    }

    inline
    virtual void
    operator-=( Value* chval )
    {
        if ( chval == NULL )
        {
            return;
        }
        r_value -= ( ( Value* )( &( ( ( ComplexValue* )chval )->r_value ) ) );
        i_value -= ( ( Value* )( &( ( ( ComplexValue* )chval )->i_value ) ) );
    }

    inline
    virtual void
    operator*=( double dval )
    {
        r_value *= dval;
        i_value *= dval;
    }                                 // needed by algebra tools

    inline
    virtual void
    operator/=( double dval )
    {
        if ( dval == 0. )
        {
            std::cerr << "ERROR: DEVISION BY ZERO!" << std::endl;
        }
        r_value /= dval;
        i_value /= dval;
    }



    inline
    virtual void
    Free()
    {
        delete ( ComplexValue* )this;
    }

    virtual void
    operator=( double );

    virtual void
    operator=( Value* );

    virtual bool
    isZero() const
    {
        return r_value.isZero() && i_value.isZero();
    };

    virtual DataType
    myDataType() const
    {
        return CUBE_DATA_TYPE_COMPLEX;
    };
    virtual void
        normalizeWithClusterCount( uint64_t );



    virtual
    void
    init_new();

    virtual
    void
    clone_new( const Value* );
};
}
#endif
