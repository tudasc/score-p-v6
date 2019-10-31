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
 * \file CubeRowWiseMatrix.cpp
 * \brief Definces methods of the RowWiseMatrix class.
 */



#include "config.h"
#include <string>
#include <cstring>
#include <iostream>

#include "CubeTrafos.h"
#include "CubeValues.h"
#include "CubeIndexes.h"
#include "CubeIndexManager.h"
#include "CubeRowWiseMatrix.h"
#include "CubeStrategies.h"

using namespace std;
using namespace cube;

RowWiseMatrix::RowWiseMatrix(
    fileplace_t DataPlace,
    fileplace_t IndexPlace,
    cnode_id_t  ct,
    thread_id_t nt,
    Value*      value )
{
    rows.resize( ct, NULL );
    _no_row_pointer = new char[ 1 ];
    strategy        = NULL;
    rows_manager    = NULL;
    setStrategy( BasicStrategy::selectInitialStrategy() );
    row_interface = new Row( nt, value );   // create Row with standart interfaces, which do get replaces later on in initialization of RowsSupplier
    rows_manager  = new RowsManager( DataPlace, IndexPlace, &rows, row_interface,  strategy, _no_row_pointer );
}


RowWiseMatrix::RowWiseMatrix(
    fileplace_t    DataPlace,
    fileplace_t    IndexPlace,
    cnode_id_t     ct,
    thread_id_t    nt,
    Value*         value,
    BasicStrategy* _strategy )
{
    RowWiseMatrix( DataPlace, IndexPlace, ct, nt, value );
    if ( _strategy != NULL )
    {
        setStrategy( _strategy );
    }
}


RowWiseMatrix::~RowWiseMatrix()
{
    delete row_interface;
    delete rows_manager;
    delete strategy;
    delete[] _no_row_pointer;
}


void
RowWiseMatrix::writeData()
{
    if ( rows_manager  != NULL )
    {
        rows_manager->dropAllRows();
    }
    rows_manager->finalize();
}


void
RowWiseMatrix::setStrategy( CubeStrategy _strategy )
{
    switch ( _strategy )
    {
        case CUBE_MANUAL_STRATEGY:
            setStrategy( new ManualStrategy( true ) );
            break;
        case CUBE_ALL_IN_MEMORY_STRATEGY:
            setStrategy( new AllInMemoryStrategy( true ) );
            break;
        case CUBE_ALL_IN_MEMORY_PRELOAD_STRATEGY:
            setStrategy( new AllInMemoryPreloadStrategy( true ) );
            break;
        case CUBE_LAST_N_ROWS_STRATEGY:
            setStrategy( new LastNRowsStrategy( true ) );
            break;
        default: // default is all in memory, recursiv call this call
            setStrategy( CUBE_ALL_IN_MEMORY_STRATEGY );
            break;
    }
}


void
RowWiseMatrix::setStrategy( BasicStrategy* _str )
{
    delete strategy;
    strategy = _str;
    if ( rows_manager != NULL )
    {
        rows_manager->setStrategy( _str );
    }
};

void
RowWiseMatrix::dropRow( cnode_id_t cid )
{
    rows_manager->dropRow( cid );
}

void
RowWiseMatrix::dropAllRows()
{
    if ( rows_manager )
    {
        rows_manager->dropAllRows();
    }
}


Value*
RowWiseMatrix::getValue()
{
    return row_interface->getValue();
};

Value*
RowWiseMatrix::getValue( cnode_id_t cid, thread_id_t tid )
{
    Value* _to_return    = NULL;
    row_t  _present_row1 = rows[ cid ];
    if ( _present_row1 == NULL )
    {
        rows_manager->provideRow( cid );
        row_t _present_row2 = rows[ cid ];
        if ( _present_row2 == NULL )
        {
            rows[ cid ] = _no_row_pointer;
            _to_return  =   row_interface->getValue();
        }
        else
        {
            _to_return =  row_interface->getData( _present_row2, tid );
        }
    }
    else
    {
        if ( _present_row1 == _no_row_pointer  )
        {
            _to_return = row_interface->getValue();
        }
        else
        {
            _to_return =  row_interface->getData( _present_row1, tid );
        }
    }
    return _to_return;
}

void
RowWiseMatrix::setValue( const Value* v, cnode_id_t cid, thread_id_t tid )
{
    row_t _tmp = rows[ cid ];
    if ( _tmp == NULL || _tmp == _no_row_pointer )
    {
        rows_manager->provideRow( cid, true );
    }
    row_interface->setData( rows[ cid ], v, tid );
    return;
}


void
RowWiseMatrix::setValue( double val, cnode_id_t cid, thread_id_t tid )
{
    row_t _tmp = rows[ cid ];
    if ( _tmp == NULL || _tmp == _no_row_pointer )
    {
        rows_manager->provideRow( cid, true );
    }
    row_interface->setData( rows[ cid ], val, tid );
}

void
RowWiseMatrix::setValue( uint64_t val, cnode_id_t cid, thread_id_t tid )
{
    row_t _tmp = rows[ cid ];
    if ( _tmp == NULL || _tmp == _no_row_pointer )
    {
        rows_manager->provideRow( cid, true );
    }
    row_interface->setData( rows[ cid ], val, tid );
}



char*
RowWiseMatrix::getRow( cnode_id_t cid )
{
    row_t _present_row1 = rows[ cid ];
    if ( _present_row1 == NULL )
    {
        rows_manager->provideRow( cid );
        row_t _present_row2 = rows[ cid ];
        if ( _present_row2 == NULL )
        {
            rows[ cid ] = _no_row_pointer;
            return NULL;
        }
        else
        {
            return _present_row2;
        }
    }
    else
    {
        if ( _present_row1 == _no_row_pointer  )
        {
            return NULL;
        }
        else
        {
            return _present_row1;
        }
    }
};


void
RowWiseMatrix::setRow( char* _row, cnode_id_t cid )
{
    row_t _tmp = rows[ cid ];
    if ( _tmp == NULL || _tmp == _no_row_pointer )
    {
        rows_manager->provideRow( cid, true );
        _tmp = rows[ cid ];
    }
    if (  _tmp != _no_row_pointer )
    {
        delete[] _tmp;
    }
    rows[ cid ] = _row;
};



void
RowWiseMatrix::writeXML( std::ostream& )
{
// writen on Cube level
}
