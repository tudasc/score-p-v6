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
 * \file CubeCharValue.h
 * \brief  Provides the "char" (8bit) build-in type as "Value"
 ************************************************/

#ifndef __CHAR_VALUE_H
#define __CHAR_VALUE_H

#include <istream>
#include "CubeValue.h"

#include <iostream>

namespace cube
{
class Connection;
class CharValue;
extern Preallocator<CharValue>char_preallocator;

/**
 * Value works with 1 bytes of char as the whole int value, and as 1 bytes (endianess). Therefore it
 * defined a union to keep the realisation consistent with another types.
 */
typedef union
{
    char cValue;
    char aValue[ sizeof( char ) ];
} c_value_t;

class CharValue :
    public Value
{
protected:
    c_value_t value;                    // / "heart" of the value.



public:
    CharValue();
    CharValue( char );


    virtual
    ~CharValue()
    {
    };
    virtual unsigned
    inline
    getSize() const
    {
        return sizeof( char );
    }
    inline
    virtual double
    getDouble() const
    {
        return ( double )value.cValue;
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
    virtual char*
    transformStream( char* stream, SingleValueTrafo* trafo ) const
    {
        trafo++; // dummy operation to remove most of warnings about not used parameter or similar
        return stream;
    }

    inline
    virtual CharValue*
    clone() const
    {
        return new CharValue();
    }

    inline
    virtual CharValue*
    copy() const
    {
        return new CharValue( value.cValue );
    }


    virtual void
    Free()
    {
        delete ( CharValue* )this;
    }

    void*
    operator new( size_t size );
    void
    operator delete( void* p );

    virtual void
    inline
    operator+=( Value* chval )
    {
        if ( chval == NULL )
        {
            return;
        }
        value.cValue += ( ( CharValue* )chval )->value.cValue;
    }
    inline
    virtual void
    operator-=( Value* chval )
    {
        if ( chval == NULL )
        {
            return;
        }
        value.cValue -= ( ( CharValue* )chval )->value.cValue;
    }

    inline
    virtual void
    operator*=( double dval )
    {
        value.cValue *= dval;
    }                                 // needed by algebra tools


    inline
    virtual void
    operator/=( double dval )
    {
        if ( dval == 0. )
        {
            std::cerr << "ERROR: DEVISION BY ZERO!" << std::endl;
        }
        value.cValue /= dval;
    }

    virtual void
    operator=( double );

    virtual void
    operator=( Value* );

    virtual bool
    isZero() const
    {
        return value.cValue == 0;
    };

    virtual DataType
    myDataType() const
    {
        return CUBE_DATA_TYPE_UINT8;
    };
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
