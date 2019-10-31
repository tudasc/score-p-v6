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
 * \file CubeRow.h
 * \brief  Represents a row of values. It stores an object Value, endianess transformation and  and a memory, which is going to be stored in file. It applies endianess transformation, if needed.
 */

#ifndef CUBE_ROW_H
#define CUBE_ROW_H

#include "CubeTypes.h"
#include "CubeError.h"

namespace cube
{
class Row
{
private:
    // / Pointer on the example of a value, carried by trhe tor
    Value* value;

    // / Number of elements, stored in row.
    uint64_t n;

    // / Transformation of endianness
    SingleValueTrafo* endianness;

public:
    Row( size_t _n,
         Value* _v );                                                                                                                                               // name of file
    ~Row();


    Value*
    getValue();



    void
    correctEndianness( row_t row ); // / applied an endianess transformation on the row.

    void
    setEndianness( SingleValueTrafo* _trafo ); // / to set the endianess

    size_t
    getRawRowSize();                            // / returns a full size of a row in bytes

    size_t
    getRowSize();                                   // / returns a size of a row in elements.

    void
        setData( row_t,
                 const Value*,
                 thread_id_t tid );   // / sets a value (general)

    void
        setData( row_t,
                 double,
                 thread_id_t tid ); // / sets a value (double)

    void
        setData( row_t,
                 uint64_t,
                 thread_id_t tid ); // / sets a value (uin64_t)

    Value*
        getData( row_t, thread_id_t ); // / returns a value (creates a clone copy, should be deleted by an acceptor af a value)


    void
        printRow( row_t, std::ostream & );                       // / Prints a content of any row

    void
        printRawRow( row_t, std::ostream & );                       // / Prints a content of any row charwise

    template <class T>
    T
        getBuildInData( row_t, thread_id_t );
};



template <class T>
T
Row::getBuildInData( row_t row,   thread_id_t tid )
{
    T v = static_cast<T>( 0 );
    if ( row == NULL )
    {
        throw NotAllocatedMemoryForRow( "Row::getData(...) tries to create a value on the not available memory. Please allocate memory first." );
    }
    if ( ( uint64_t )tid >= n )
    {
        return v;
    }
    T* __row = ( T* )row;

    return __row[ tid ];
}
}

#endif
