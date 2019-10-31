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
 * \file CubeNDoublesValue.h
 * \brief  Provides the experimental complex value, consisting of N "DoubleValue"'s. Needed for future to support atomic events.
 ************************************************/
#ifndef __NDOUBLES_VALUE_H
#define __NDOUBLES_VALUE_H

#include <istream>
#include <stdlib.h>
#include "CubeError.h"
#include "CubeValues.h"

#include <iostream>
#include <iomanip>

namespace cube
{
class Connection;
class NDoublesValue;
extern Preallocator<NDoublesValue>ndoubles_preallocator;

typedef   struct
{
    int pivot;
}  __attribute__ ( ( __packed__ ) ) NDoublesValueConfig;



class NDoublesValue :
    public Value
{
private:
    static
    std::vector<NDoublesValueConfig>parameters;
    size_t                          index;

public:
    uint64_t N;                       // / Number of values.
    double*  values;                  // / "heart" of the value.


public:
    NDoublesValue();
    NDoublesValue( uint64_t );
//                                 NDoublesValue(double);
    NDoublesValue( uint64_t,
                   double* );

    virtual
    ~NDoublesValue()
    {
#ifdef __DEBUG
        std::cout << "Delete array in ndoubles  " << N << " in " << std::hex << ( uint64_t ) this << " " << ( uint64_t )values << std::dec << std::endl;
#endif
        ::delete[] this->values;
        this->values = 0;
#ifdef __DEBUG
        std::cout << "Deleted  array in ndoubles " << N << " in " << std::hex << ( uint64_t ) this << " " << ( uint64_t )values << std::dec << std::endl;
#endif
        N = 0;
    }


    void
    processArguments( std::vector<std::string>args );  // / parse arguments from metric
    void
    setNumTerms( size_t num );                         // / set number of terms stored according to metric

    /**
     * Resize the value array.
     * @param num Number of elements in the new array.
     * @note Container can only grow in size. Shrinking results in a runtime error.
     */
    void
    resize( size_t num );

    inline
    virtual unsigned
    getSize() const
    {
        return ( N == 0 ) ? 0 : N* ( sizeof( double ) );
    }

    inline
    virtual double
    getDouble() const
    {
        double sum = 0;
        for ( unsigned i = 0; i < N; i++ )
        {
            sum += values[ i ];
        }
        return sum;
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
    virtual double
    getValue( unsigned idx ) const;

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
    virtual NDoublesValue*
    clone() const
    {
        NDoublesValue* _return =  new NDoublesValue( N );
        _return->clone_new( this );
        return _return;
    }

    virtual NDoublesValue*
    copy() const;

    const double*
    get_values( void )
    {
        return values;
    }

    uint64_t
    get_number_of_values( void )
    {
        return N;
    }

    virtual void
    operator+=( Value* );
    virtual void
    operator-=( Value* );
    virtual void
    operator*=( double );                            // needed by algebra tools
    virtual void
    operator/=( double );                            // needed by algebra tools

    void*
    operator new( size_t size );
    void
    operator delete( void* p );


    virtual void
    Free()
    {
        delete[] values;
        values = NULL;
        ndoubles_preallocator.Put( this );
    }

    virtual void
    operator=( double );

    virtual void
    operator=( Value* );


    virtual bool
    isZero() const;                        // faked check. Should be fixed if NDoubles get to use in cube.

    virtual DataType
    myDataType() const
    {
        return CUBE_DATA_TYPE_NDOUBLES;
    };                                             // not supported yet
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
