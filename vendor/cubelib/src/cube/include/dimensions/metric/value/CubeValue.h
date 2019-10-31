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
 * \file CubeValue.h
 * \brief Provide a general Cube4 value.
 *
 *
 */

#ifndef __VALUE_H
#define __VALUE_H

#include <cstring>
#include <inttypes.h>
#include <iostream>
#include <istream>
#include <string>
#include <unistd.h>

#include "CubePreallocator.h"
#include "CubeTrafos.h"



namespace cube
{
// Forward declarations
class Connection;

/**
 *  Represents a general Value, which has to provde  a simple arithmetic for needed operations and service methods.
 */
class Value
{
protected:
// bad idea about returning and assignmend of a single value in many value object..
// but dont delete, if it is not bad after all
//        unsigned nvalues;                                                           ///< Counts the number of values. For simple Values it is not used and is always "undefind" or "1"
//        unsigned assignment_index;                                                      ///< Saves the number of the internal values for the folowing assignation operation.
//        unsigned return_index;                                                      ///< Saves the index of the internal values for the folowing getXXX operation.
    bool valid;                                                                     // /< Signalize, that the value is valid and was really set/read from the file.
    bool isSingleValue;                                                             // /< Saves, if the value is only single number or not. Gets initialized in constructor of the specific value.




public:


    virtual
    ~Value()
    {
    };                                                                              // /< Vitual destructor allows, that every inherited class destroy itself properly.
    virtual unsigned
    getSize() const = 0;                                                            // /< Value has to define size of it in bytes. Used to apply transformations and saving/loading in the file.
    virtual double
    getDouble() const = 0;                                                          // /< Returns the double representation of itself, if possible.
    virtual uint64_t
    getUnsignedLong() const = 0;                                                    // /< Returns the unsigned 64bit representation of itself, if possible.
    virtual int64_t
    getSignedLong() const = 0;                                                      // /< Returns the signed 64bit representation of itself, if possible.
    virtual uint32_t
    getUnsignedInt() const = 0;                                                     // /< Returns the unsigned 32bit representation of itself, if possible.
    virtual int32_t
    getSignedInt() const = 0;                                                       // /< Returns the signed 32bit representation of itself, if possible.
    virtual uint16_t
    getUnsignedShort() const = 0;                                                   // /< Returns the unsigned 16bit representation of itself, if possible.
    virtual int16_t
    getSignedShort() const = 0;                                                     // /< Returns the signed 16bit representation of itself, if possible.
    virtual char
    getChar() const = 0;                                                            // /< Returns the single byte representation of itself, if possible.
    virtual std::string
    getString() const = 0;                                                          // /< Returns the textual representation of itself, if possible. Used to save itself in Cube3 format.

    virtual const char*
    fromStream( const char* ) = 0;                                                  // /< Constructs itself from the stream. The first stream byte used as starting point.
    virtual char*
    toStream( char* ) const = 0;                                                    // /< Write to the stream the stream-representation of itself. The first stream byte used as starting point.

    /**
     * Assign value from a Cube connection.
     * @param connection Cube connection stream.
     */
    virtual void
    fromStream( Connection& connection ) = 0;

    /**
     * Send value through a Cube connection.
     * @param connection Cube connection stream.
     */
    virtual void
    toStream( Connection& connection ) const = 0;

    virtual const double*
    fromStreamOfDoubles( const double* stream ) = 0;                                      // /< Special case, if memory areay is filled with "double" walues


    virtual char*
    transformStream( char*,
                     SingleValueTrafo* ) const;                                           // /< Applyes the transformation on the stream according to its layout. Used to deal with different endianess. Needed for comples types with non trivial layout.


    virtual void
    Free() = 0;

    void*
    operator new( size_t size ) throw( )
    {
        ( void )size;
        return NULL;
    };

    void
    operator delete( void* p )
    {
        ( void )p;
    };


    virtual void
    operator+=( Value* ) = 0;                                                 // /< Defines + operation (for calculation of the excl/incl values).
    virtual void
    operator-=( Value* ) = 0;                                                 // /< Defines - operation (for calculation of the excl values).
    virtual Value*
    clone() const = 0;                                                        // /< Makes a copy of itself and sets the value of the copy to 0.
    virtual Value*
    copy() const = 0;                                                         // /< Makes a copy of itself and keeps the value.


    virtual void
    operator=( double ) = 0;                                              // /< Allows to assign its value from the build in double.


    virtual void
    operator=( Value* ) = 0;                                              // /< Allows to assign its value from another object of same type. [WARNING, real type is not checked]

    virtual void
    operator*=( double ) = 0;                                                       // /< Defines * operation (for calculation of the excl/incl values). Needed by algebra tools.
    virtual void
    operator/=( double ) = 0;                                                       // /< Defines / operation (for calculation of the excl/incl values). Needed by algebra tools.

    virtual bool
    singleValue() const
    {
        return isSingleValue;
    }
    // /< Standard response, that the value is a single number.
    virtual bool
    asExclusiveMetric() const
    {
        return true;
    }
    // /< Standard response, that metric having this data type can be stored in exclusive flavor.
    virtual bool
    asInclusiveMetric() const
    {
        return true;
    }
    // /< Standard response, that metric having this data type can be stored in inclusive flavor. (min, max, taumetric - no)



    virtual bool
    // /< Respones if the value is a zero element of monoid or group . In simple case it is arithmetic zero.
    isZero() const = 0;

    virtual DataType
    myDataType()  const = 0;                                                   // /< Reports its type as an enum value.


    virtual void
        normalizeWithClusterCount( uint64_t ) = 0;                      // /< Normalizes (devides, if needed) itself in the case of clustering

    virtual void
    processArguments( std::vector<std::string>)
    {
    };

    // void          resetValue() {/* assignment_index= 0;  return_index =0; */}                   ///< Resets the assignation sequence. The next operator "=" acts on the first of the values. The next of getDouble() returns the first value.
    virtual
    void
    init_new() = 0;

    virtual
    void
    clone_new( const Value* ) = 0;
};




/**
 * Allows to create an object of the general type "Value" from the build-in type. C++ polimorphism allows this functionality.
 */
std::string
getDataTypeAsString( DataType type );

Value*
    selectValueOnDataType( DataType );
Value*
selectValueOnType( double );
Value*
selectValueOnType( char );

Value*
selectValueOnType( std::string );

Value* selectValueOnType( uint16_t );
Value* selectValueOnType( uint32_t );
Value* selectValueOnType( uint64_t );
Value* selectValueOnType( int16_t );
Value* selectValueOnType( int32_t );
Value* selectValueOnType( int64_t );
Value*
selectValueOnType( Value* );

void
deleteAndResize( std::vector<Value*>& valueVector,
                 size_t               size );

/**
 * Check whether a given DataType takes arguments (number of terms, ...)
 */
bool typeTakesArguments( DataType );
}



#endif
