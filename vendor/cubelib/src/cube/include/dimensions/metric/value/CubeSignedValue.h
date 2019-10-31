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
 * \file CubeSignedValue.h
 * \brief   Provides the "signed int" (32bit) build-in type as "Value"
 ************************************************/
#ifndef __SIGNED_VALUE_H
#define __SIGNED_VALUE_H

#include <istream>
#include "CubeValue.h"

#include <iostream>

namespace cube
{
class Connection;
class SignedValue;
extern Preallocator<SignedValue> int32_preallocator;


/**
 * Value works with 4 bytes of the nsigned int as teh whole int value, and as 4 bytes (endianess). Therefore it
 * defined a union.
 */
typedef union
{
    int32_t iValue;
    char    aValue[ sizeof( int32_t ) ];
} i_value_t;

class SignedValue : public Value
{
protected:
    i_value_t value;                     // / "heart" of the value.
public:
    SignedValue();
    SignedValue( int32_t );
    virtual
    ~SignedValue()
    {
    };
    inline
    virtual unsigned
    getSize() const
    {
        return sizeof( int32_t );
    }

    inline
    virtual double
    getDouble() const
    {
        return ( double )value.iValue;
    };
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

    inline
    virtual Value*
    clone() const
    {
        return new SignedValue( 0 );
    }
    inline
    virtual Value*
    copy() const
    {
        return new SignedValue( value.iValue );
    }

    inline
    virtual void
    operator+=( Value* chval )
    {
        if ( chval == NULL )
        {
            return;
        }
        value.iValue += ( ( SignedValue* )chval )->value.iValue;
    }

    inline
    virtual void
    operator-=( Value* chval )
    {
        if ( chval == NULL )
        {
            return;
        }
        value.iValue -= ( ( SignedValue* )chval )->value.iValue;
    }

    inline
    virtual void
    operator*=( double dval )
    {
        value.iValue *= dval;
    }                                 // needed by algebra tools

    inline
    virtual void
    operator/=( double dval )
    {
        if ( dval == 0. )
        {
            std::cerr << "ERROR: DEVISION BY ZERO!" << std::endl;
        }
        value.iValue /= dval;
    }

    void*
    operator new( size_t size );
    void
    operator delete( void* p );

    virtual void
    Free()
    {
        delete ( SignedValue* )this;
    }

    virtual void
    operator=( double );

    virtual void
    operator=( Value* );

    virtual bool
    isZero() const
    {
        return value.iValue == 0;
    };

    virtual DataType
    myDataType() const
    {
        return CUBE_DATA_TYPE_INT32;
    };                                              // not supported yet
    virtual void
        normalizeWithClusterCount( uint64_t );

    virtual
    void
    init_new()
    {
    };

    virtual
    void
    clone_new( const Value* )
    {
    };
};
}
#endif
