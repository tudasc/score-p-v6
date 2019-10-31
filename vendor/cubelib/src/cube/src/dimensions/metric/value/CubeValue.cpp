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
 * \file CubeValue.cpp
 * \brief Defines the common methods for all kind of values: transformation of the byte stream according to the lyout of the Value.
 */


#include "config.h"

#include <cstring>
#include <iostream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

#include "CubeError.h"
#include "CubePreallocator.h"
#include "CubeTrafos.h"
#include "CubeValues.h"


using namespace std;
using namespace cube;


// / Here we declare a series of global static preallocators for CubeXXXValues
Preallocator<DoubleValue>       cube:: double_preallocator;
Preallocator<MaxDoubleValue>    cube:: max_double_preallocator;
Preallocator<MinDoubleValue>    cube:: min_double_preallocator;
Preallocator<CharValue>         cube:: char_preallocator;
Preallocator<SignedShortValue>  cube:: int16_preallocator;
Preallocator<SignedValue>       cube:: int32_preallocator;
Preallocator<SignedLongValue>   cube:: int64_preallocator;
Preallocator<UnsignedShortValue>cube:: uint16_preallocator;
Preallocator<UnsignedValue>     cube:: uint32_preallocator;
Preallocator<UnsignedLongValue> cube:: uint64_preallocator;
Preallocator<ComplexValue>      cube:: complex_preallocator;
Preallocator<RateValue>         cube:: rate_preallocator;
Preallocator<TauAtomicValue>    cube:: tau_preallocator;
Preallocator<NDoublesValue>     cube:: ndoubles_preallocator;
Preallocator<HistogramValue>    cube:: histogram_preallocator;
Preallocator<StatLevel1Value>   cube:: stat1_preallocator;
Preallocator<StatLevel2Value>   cube:: stat2_preallocator;
Preallocator<StatLevel3Value>   cube:: stat3_preallocator;
Preallocator<StatLevel4Value>   cube:: stat4_preallocator;
Preallocator<ScaleFuncValue>    cube:: scale_func_preallocator;
Preallocator<StringValue>       cube:: string_preallocator;





/**
 * Applies the transformation 'trafo' on the [size] bytes of the 'stream'. Returns the position in the stream, moved on its 'size'.
 *
 */
char*
Value::transformStream( char* stream, SingleValueTrafo* trafo ) const
{
    return trafo->trafo( stream, getSize() );
};



/**
   Allows to get an object "Value" according to the CUBE enum type.
 */
Value*
cube::selectValueOnDataType( DataType type )
{
    switch ( type )
    {
        case CUBE_DATA_TYPE_NONE:
            throw RuntimeError( "NONE Value is not supported" );
        case CUBE_DATA_TYPE_DOUBLE:
            return new DoubleValue();
        case CUBE_DATA_TYPE_INT8:
            return new CharValue();
        case CUBE_DATA_TYPE_UINT8:
            return new CharValue();
        case CUBE_DATA_TYPE_INT16:
            return new SignedShortValue();
        case CUBE_DATA_TYPE_UINT16:
            return new UnsignedShortValue();
        case CUBE_DATA_TYPE_INT32:
            return new SignedValue();
        case CUBE_DATA_TYPE_UINT32:
            return new UnsignedValue();
        case CUBE_DATA_TYPE_INT64:
            return new SignedLongValue();
        case CUBE_DATA_TYPE_UINT64:
            return new UnsignedLongValue();
        case CUBE_DATA_TYPE_COMPLEX:
            return new ComplexValue();
        case CUBE_DATA_TYPE_TAU_ATOMIC:
            return new TauAtomicValue();
        case CUBE_DATA_TYPE_RATE:
            return new RateValue();
        case CUBE_DATA_TYPE_MAX_DOUBLE:
            return new MaxDoubleValue();
        case CUBE_DATA_TYPE_MIN_DOUBLE:
            return new MinDoubleValue();
        case CUBE_DATA_TYPE_SCALE_FUNC:
            return new ScaleFuncValue();
        case CUBE_DATA_TYPE_HISTOGRAM:
            return new HistogramValue();
        case CUBE_DATA_TYPE_NDOUBLES:
            return new NDoublesValue();
        default:
            throw RuntimeError( "Not supported type for a metric is selected" );
    }
}


/**
   Allows to get an object "Value" according to the CUBE enum type.
 */
std::string
cube::getDataTypeAsString( DataType type )
{
    switch ( type )
    {
        case CUBE_DATA_TYPE_NONE:
            throw RuntimeError( "NONE Value is not supported" );
        case CUBE_DATA_TYPE_DOUBLE:
            return "DOUBLE";
        case CUBE_DATA_TYPE_INT8:
            return "INT8";
        case CUBE_DATA_TYPE_UINT8:
            return "UINT8";
        case CUBE_DATA_TYPE_INT16:
            return "INT16";
        case CUBE_DATA_TYPE_UINT16:
            return "UINT16";
        case CUBE_DATA_TYPE_INT32:
            return "INT32";
        case CUBE_DATA_TYPE_UINT32:
            return "UINT32";
        case CUBE_DATA_TYPE_INT64:
            return "INT64";
        case CUBE_DATA_TYPE_UINT64:
            return "UINT64";
        case CUBE_DATA_TYPE_COMPLEX:
            return "COMPLEX";
        case CUBE_DATA_TYPE_TAU_ATOMIC:
            return "TAU_ATOMIC";
        case CUBE_DATA_TYPE_RATE:
            return "RATE";
        case CUBE_DATA_TYPE_MAX_DOUBLE:
            return "MAXDOUBLE";
        case CUBE_DATA_TYPE_MIN_DOUBLE:
            return "MINDOUBLE";
        case CUBE_DATA_TYPE_SCALE_FUNC:
            return "SCALE_FUNC";
        case CUBE_DATA_TYPE_HISTOGRAM:
            return "HISTOGRAM";
        case CUBE_DATA_TYPE_NDOUBLES:
            return "NDOUBLES";
        default:
            throw RuntimeError( "Not supported type for a metric is selected" );
    }
}



/**
 * Function to decide whether a type can receive arguments
 */
bool
cube::typeTakesArguments( DataType type )
{
    // TODO: implement as abstract interface and change to dynamic_cast and error checks
    switch ( type )
    {
        case CUBE_DATA_TYPE_HISTOGRAM:
        case CUBE_DATA_TYPE_NDOUBLES:
            return true;
        case CUBE_DATA_TYPE_SCALE_FUNC:
        // return true;
        default:
            return false;
    }
}




/**
   Allows to build a corresponding to the buil in type a general object "Value".
 */
Value*
cube::selectValueOnType( double d )
{
    return new DoubleValue( d );
};

/**
   Allows to build a corresponding to the buil in type a general object "Value".
 */
Value*
cube::selectValueOnType( char ch )
{
    return new CharValue( ch );
};

/**
   Allows to build a corresponding to the buil in type a general object "Value".
 */
Value*
cube::selectValueOnType( string str )
{
    return new StringValue( ( uint64_t )str.size() );
}

/**
   Allows to build a corresponding to the buil in type a general object "Value".
 */
Value*
cube::selectValueOnType( uint16_t us )
{
    return new UnsignedShortValue( us );
}

/**
   Allows to build a corresponding to the buil in type a general object "Value".
 */
Value*
cube::selectValueOnType( uint32_t ui )
{
    return new UnsignedValue( ui );
}

/**
   Allows to build a corresponding to the buil in type a general object "Value".
 */
Value*
cube::selectValueOnType( uint64_t ul )
{
    return new UnsignedLongValue( ul );
}

/**
   Allows to build a corresponding to the buil in type a general object "Value".
 */
Value*
cube::selectValueOnType( int16_t ss )
{
    return new SignedShortValue( ss );
}

/**
   Allows to build a corresponding to the buil in type a general object "Value".
 */
Value*
cube::selectValueOnType( int32_t si )
{
    return new SignedValue( si );
}

/**
   Allows to build a corresponding to the buil in type a general object "Value".
 */
Value*
cube::selectValueOnType( int64_t sl )
{
    return new SignedLongValue( ( unsigned int )sl );
}

/**
   Allows to build a corresponding to the buil in type a general object "Value".
 */
Value*
cube::selectValueOnType( Value* v )
{
    return v->clone();
}

void
cube::deleteAndResize( std::vector<Value*>& valueVector, size_t size )
{
    for ( vector<Value*>::iterator it = valueVector.begin(); it != valueVector.end(); ++it )
    {
        ( *it )->Free();
        *it = NULL;
    }
    valueVector.resize( size, NULL );
}
