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
 * \file CubeRowsManager.cpp
 * \brief  Implements methods of a class RowsManager
 */

#include "config.h"
#include "CubeTrafos.h"
#include "CubeRowsManager.h"
#include "CubeRowsSuppliers.h"
#include "CubeRow.h"
#include "CubeValue.h"
#include "CubeStrategies.h"



using namespace cube;



RowsManager::RowsManager( fileplace_t    DataPlace,
                          fileplace_t    IndexPlace,
                          rows_t*        _rows,
                          Row*           _row,
                          BasicStrategy* _strategy,
                          row_t          __no_row_pointer )
{
    no_drop        = false;
    row            = _row;
    rows           = _rows;
    no_row_pointer = __no_row_pointer;
    Value* _value = row->getValue();
    if ( DataPlace.second.first != ( uint64_t )-1 && IndexPlace.second.first != ( uint64_t )-1 && DataPlace.second.second != ( uint64_t )-1 && IndexPlace.second.second != ( uint64_t )-1  )
    {
        row_supplier = selectRowsSupplier( DataPlace, IndexPlace,  row->getRowSize(), _value->getSize() );
    }
    else
    {
        row_supplier = selectRowsSupplier(   row->getRowSize(), _value->getSize() );
    }

    delete _value;
    row->setEndianness( row_supplier->getEndianness() ); // endianess detected in rowSupplier and passed to the row interface.
    setStrategy( _strategy );
}


RowsManager::~RowsManager()
{
    for ( rows_t::iterator iter = rows->begin(); iter != rows->end(); ++iter )
    {
        if ( ( *iter ) != no_row_pointer && ( *iter ) != NULL )
        {
            delete[]  ( *iter );
        }
    }
    rows->clear();

    delete row_supplier;
    row_supplier = NULL;
}


void
RowsManager::setStrategy( BasicStrategy* _str )
{
    strategy = _str;
    std::vector<cnode_id_t>wanted_rows = strategy->initialize( rows );
    for ( std::vector<cnode_id_t>::iterator iter = wanted_rows.begin(); iter < wanted_rows.end(); ++iter )
    {
        row_t _present_row = rows->at( *iter );
        if (  _present_row == NULL )
        {
            row_t _tmp = NULL;
            _tmp = row_supplier->provideRow( *iter );
            if ( _tmp != NULL )
            {
                row->correctEndianness( _tmp );
                ( *rows )[ *iter ] = _tmp;
            }
        }
    }
}



void
RowsManager::finalize()
{
    row_supplier->finalize();
}


void
RowsManager::dropAllRows()
{
    if ( no_drop )
    {
        return;
    }
    for ( size_t _cid = 0; _cid < rows->size(); ++_cid )
    {
        row_t _row = ( *rows )[ _cid ];
        if ( _row == no_row_pointer ||  _row == NULL )
        {
            continue;
        }
        row_supplier->dropRow( _row, _cid );
        ( *rows )[ _cid ] = NULL;
    }
}


void
RowsManager::provideRow( cnode_id_t& id, bool for_writing )
{
    row_t _present_row = ( id < ( cnode_id_t )( rows->size() ) ) ? rows->at( id ) : NULL;
    if (  ( _present_row == NULL ) || ( for_writing == true && _present_row == no_row_pointer ) )
    {
        row_t _tmp = NULL;
        _tmp = row_supplier->provideRow( id, for_writing  );
        if ( _tmp != NULL )
        {
            row->correctEndianness( _tmp );
            ( *rows )[ id ] = _tmp;
        }
    }
}



void
RowsManager::dropRow( cnode_id_t& id )
{
    if ( no_drop )
    {
        return;
    }
    row_t _present_row = rows->at( id );
    if (  _present_row != no_row_pointer )
    {
        row_supplier->dropRow( _present_row, id );
        ( *rows )[ id ] = NULL;
    }
}


// ---------------------------------------------------------------------



RowsSupplier*
RowsManager::selectRowsSupplier( fileplace_t DataPlace,
                                 fileplace_t IndexPlace, uint64_t rowsize, uint64_t es )
{
    if ( RORowsSupplier::probe( DataPlace, IndexPlace ) )
    {
        return new RORowsSupplier( DataPlace, IndexPlace, rowsize, es );
    }
    else
    if ( ROZRowsSupplier::probe( DataPlace, IndexPlace ) )
    {
        return new ROZRowsSupplier( DataPlace, IndexPlace, rowsize, es );
    }
    else
    if ( WOZRowsSupplier::probe( DataPlace, IndexPlace ) )
    {
        return new WOZRowsSupplier( DataPlace, IndexPlace, rowsize, es );
    }
    else
    if ( WORowsSupplier::probe( DataPlace, IndexPlace ) )
    {
        return new WORowsSupplier( DataPlace, IndexPlace, rowsize, es );
    }
    throw CannotSelectRowSupplierError( "Error in selection of a rows supplier. \n"
                                        "This installation of cube doesn't support compressed cube files. \n"
                                        "Please recompile and reinstall CUBE using configure flags:\n"
                                        "      --with-compression=full|ro and --with-frontend-zlib=[path to zlib]" );
//    return NULL;
}

RowsSupplier*
RowsManager::selectRowsSupplier( uint64_t rowsize, uint64_t es )
{
    if ( MemoryRowsSupplier::probe() )
    {
        no_drop = true;
        return new MemoryRowsSupplier( rowsize * es );
    }
    throw CannotSelectRowSupplierError( "Error in selection of a rows supplier. \n" );
//    return NULL;
}
