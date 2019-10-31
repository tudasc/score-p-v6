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
 * \file CubeRow.cpp
 * \brief  Implements methods of class Row
 */

#include "config.h"
#include "CubeRow.h"
#include "CubeValue.h"
#include "CubeTrafos.h"

using namespace cube;
using namespace std;


template
double
Row::getBuildInData<double>( row_t, thread_id_t );


template
uint64_t
Row::getBuildInData<uint64_t>( row_t, thread_id_t );


template
int64_t
Row::getBuildInData<int64_t>( row_t, thread_id_t );



Row::Row( size_t _n,
          Value* _v )
    : value( _v ), n( _n )
{
    endianness = NULL;
};

Row::~Row()
{
}

Value*
Row::getValue()
{
    return value->clone();
};                            // / Returns a pointer on used value. Used to get a clone copy of the value for processing



void
Row::correctEndianness( row_t _row )
{
    row_t ptr_value = _row;

    while ( ptr_value < _row + getRawRowSize() )
    {
        row_t _tmp = value->transformStream( ptr_value, endianness );
        if ( _tmp == ptr_value )
        {
            break;
        }
        ptr_value = _tmp;
    }
}


void
Row::setEndianness( SingleValueTrafo* _trafo )
{
    delete endianness;
    endianness = _trafo;
}


size_t
Row::getRawRowSize()
{
    return n * ( value->getSize() );
}                                                // / returns a full size of a row in bytes

size_t
Row::
getRowSize()
{
    return n;
}                                                    // / returns a size of a row in elements.


void
Row::setData( row_t row,   const Value* v, thread_id_t tid )
{
    if ( ( uint64_t )tid >= n )
    {
        return;
    }
    // by that time internal pointer should be set on the memoery
    if ( row == NULL )
    {
        throw NotAllocatedMemoryForRow( "Row::setData(...) tries to set the value on not available memory. Please allocate memory first." );
    }
    v->toStream( row + tid * ( v->getSize() ) );
}


void
Row::setData( row_t row,   double v, thread_id_t tid )
{
    if ( ( uint64_t )tid >= n )
    {
        return;
    }
    // by that time internal pointer should be set on the memoery
    if ( row == NULL )
    {
        throw NotAllocatedMemoryForRow( "Row::setData(...) tries to set the value on not available memory. Please allocate memory first." );
    }

    value->
    operator=( v );

    value->toStream( row + tid * value->getSize() );
}



void
Row::setData( row_t row,   uint64_t v, thread_id_t tid )
{
    if ( ( uint64_t )tid >= n )
    {
        return;
    }
    // by that time internal pointer should be set on the memoery
    if ( row == NULL )
    {
        throw NotAllocatedMemoryForRow( "Row::setData(...) tries to set the value on not available memory. Please allocate memory first." );
    }

    value->
    operator=( v );

    value->toStream( row + tid * value->getSize() );
}


Value*
Row::getData( row_t row,   thread_id_t tid )
{
    Value* v = value->clone();
    if ( row == NULL )
    {
        throw NotAllocatedMemoryForRow( "Row::getData(...) tries to create a value on the not available memory. Please allocate memory first." );
    }
    if ( ( uint64_t )tid >= n )
    {
        return v;
    }
    v->fromStream( row + tid * value->getSize() );
    return v;
}



void
Row::printRow( row_t _row, std::ostream& _cout )
{
    if ( _row == NULL )
    {
        _cout << "0xNULL" << endl;
        return;
    }
    Value*      _v     = value->clone();
    const char* pos    = ( const char* )_row;
    char*       endpos = _row  + ( n ) * ( _v->getSize() );
    // sum up the values in the memory
    _cout << " ================================================ " << endl;
    while ( pos < endpos  )
    {
        pos = _v->fromStream( pos );
        _cout << _v->getString() << " ";
    }
    _cout << endl << " ================================================ " << endl;
    _v->Free();
}

void
Row::printRawRow( row_t _row, std::ostream& _cout )
{
    if ( _row == NULL )
    {
        _cout << "0xNULL" << endl;
        return;
    }
    Value* _v     = value->clone();
    char*  pos    = _row;
    char*  endpos = _row  + ( n ) * ( _v->getSize() );
    // sum up the values in the memory
    _cout << " =====================charwise =========================== " << endl;
    cout << hex;
    while ( pos < endpos  )
    {
        _cout << ( unsigned short )( *( ( uint8_t* )( pos ) ) ) << " ";
        pos++;
    }
    cout << dec;
    _cout << endl << " ================================================ " << endl;
    _v->Free();
}
