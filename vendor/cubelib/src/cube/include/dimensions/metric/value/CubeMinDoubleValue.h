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
 * \file CubeMinDoubleValue.h
 * \brief  Provides the "double" (64bit) build-in type as "Value" with the operation "+" as "min". Operator"-" is "Min".
 ************************************************/
#ifndef __MIN_DOUBLE_VALUE_H
#define __MIN_DOUBLE_VALUE_H

#include <istream>
#include "CubeDoubleValue.h"

#include <iostream>
#include <float.h>

#ifndef DBL_MAX
#define DBL_MAX 1.7976931348623158e+308
#endif


namespace cube
{
class MinDoubleValue;
extern Preallocator<MinDoubleValue> min_double_preallocator;

class MinDoubleValue : public DoubleValue
{
public:
    MinDoubleValue() : DoubleValue( DBL_MAX )
    {
    };

    MinDoubleValue( double d ) : DoubleValue( d )
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
        value.dValue = std::min( value.dValue, ( ( MinDoubleValue* )chval )->value.dValue );
    }
    inline
    virtual void
    operator-=( Value* chval )
    {
        if ( chval == NULL )
        {
            return;
        }
        value.dValue = std::max( value.dValue, ( ( MinDoubleValue* )chval )->value.dValue );
    }
    virtual std::string
    getString() const;


    inline
    virtual MinDoubleValue*
    clone() const
    {
        return new MinDoubleValue();
    }

    inline
    virtual MinDoubleValue*
    copy() const
    {
        return new MinDoubleValue( value.dValue );
    };

    void*
    operator new( size_t size );
    void
    operator delete( void* p );


    virtual void
    Free()
    {
        delete ( MinDoubleValue* )this;
    }
    using DoubleValue::operator=;

    virtual bool
    isZero() const
    {
        return value.dValue == DBL_MAX;
    };

    virtual bool
    asInclusiveMetric() const
    {
        return false;
    }

    virtual DataType
    myDataType() const
    {
        return CUBE_DATA_TYPE_MIN_DOUBLE;
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
