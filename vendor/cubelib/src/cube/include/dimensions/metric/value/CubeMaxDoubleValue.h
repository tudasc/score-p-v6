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
 * \file CubeMaxDoubleValue.h
 * \brief  Provides the "double" (64bit) build-in type as "Value" with the operation "+" as "max". Operator"-" is "min".
 ************************************************/
#ifndef __MAX_DOUBLE_VALUE_H
#define __MAX_DOUBLE_VALUE_H

#include <istream>
#include "CubeDoubleValue.h"

#include <iostream>
#include <float.h>

#ifndef DBL_MAX
#define DBL_MAX 1.7976931348623158e+308
#endif

namespace cube
{
class MaxDoubleValue;
extern Preallocator<MaxDoubleValue> max_double_preallocator;


class MaxDoubleValue : public DoubleValue
{
public:
    MaxDoubleValue() : DoubleValue( -DBL_MAX )
    {
    };


    MaxDoubleValue( double d ) : DoubleValue( d )
    {
    };



    inline
    virtual void
    operator+=( Value* chval )
    {
        if ( chval == NULL )
        {
            return;
        }
        value.dValue = std::max( value.dValue, ( ( MaxDoubleValue* )chval )->value.dValue );
    }
    inline
    virtual void
    operator-=( Value* chval )
    {
        if ( chval == NULL )
        {
            return;
        }
        value.dValue = std::min( value.dValue, ( ( MaxDoubleValue* )chval )->value.dValue );
    }

    virtual std::string
    getString() const;


    using DoubleValue::operator=;
    virtual MaxDoubleValue*
    clone() const
    {
        return new MaxDoubleValue();
    }
    virtual MaxDoubleValue*
    copy() const
    {
        return new MaxDoubleValue( value.dValue );
    };

    void*
    operator new( size_t size );
    void
    operator delete( void* p );

    virtual void
    Free()
    {
        delete ( MaxDoubleValue* )this;
    }



    virtual bool
    isZero() const
    {
        return value.dValue == -DBL_MAX;
    };

    virtual bool
    asInclusiveMetric() const
    {
        return false;
    }

    virtual DataType
    myDataType() const
    {
        return CUBE_DATA_TYPE_MAX_DOUBLE;
    };                                             // not supported yet
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
