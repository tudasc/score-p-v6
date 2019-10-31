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
 * \file CubeWORowsSupplier.cpp
 * \brief  Implements methods of the class WORowsSupplier
 */

#if !defined( __PGI ) && !defined( __CRAYXT )  && !defined( __CRAYXE )
#define _FILE_OFFSET_BITS 64
#endif

#include "config.h"
#include <cstdio>
#include <unistd.h>
#include <cstring>


#include "CubePlatformsCompat.h"
#include "CubeWORowsSupplier.h"
#include "CubeError.h"
#include "CubeIndexManager.h"
#include "CubeDataMarker.h"
#include "CubeServices.h"
#include "CubeIndexes.h"

using namespace std;
using namespace cube;



WORowsSupplier::WORowsSupplier(
    fileplace_t DataPlace,
    fileplace_t IndexPlace,
    uint64_t    rs,
    uint64_t    es
    ) : RowsSupplier( rs ), _dataplace( DataPlace ), _indexplace( IndexPlace )
{
    index         = NULL;
    index_manager = NULL;
    element_size  = es;

    dataMarker = NULL;
    dataMarker = new DataMarker();
    initIndex( rs, es );

    initData();
}



void
WORowsSupplier::initIndex( uint64_t rs, uint64_t )
{
    index_manager = new IndexManager( _indexplace, 0xFFFFFFFFL, rs, CUBE_INDEX_FORMAT_SPARSE );
    index         = index_manager->getIndex();
    endianness    = index_manager->getTrafo();  // in this case it is NOPTrafo
    row_size      = rs * element_size;
}


void
WORowsSupplier::initData()
{
    services::create_path_for_file( _dataplace.first.c_str() );
    __FOPEN( datafile,  _dataplace.first.c_str(), "rb+" );
    if ( datafile == NULL )
    {
        services::create_path_for_file( _dataplace.first.c_str() );
        __FOPEN( datafile, _dataplace.first.c_str(), "wb" );

        if ( datafile == NULL )
        {
            perror( "WORowsSupplier::initData():  Data file opening error: " );
            throw OpenFileError( "WORowsSupplier::initData():  Cannot open data file " + _dataplace.first );
        }
        setvbuf( datafile, NULL, _IOFBF, IO_BUFFERSIZE );
        if ( fseeko( datafile, _dataplace.second.first, SEEK_SET ) )
        {
            perror( "WORowsSupplier::initData(): Seek in data file error:" );
        }
        dataMarker->writeMarker( datafile );
        _dataplace.second.first  += dataMarker->markerSize();
        _dataplace.second.second -= dataMarker->markerSize();
        position                  = ( position_t )( dataMarker->markerSize() );
    }
    else
    {
        fclose( datafile );
        throw OpenFileError( "WORowsSupplier::initData(): Attempt to create new file, which already exists " + _dataplace.first );
    }
}


WORowsSupplier::~WORowsSupplier()
{
    if ( !_finalized )
    {
        fclose( datafile );
    }
    if ( _dummy_creation )
    {
        return;
    }
    delete dataMarker;
    delete index_manager;
}



void
WORowsSupplier::finalize()
{
    fflush( datafile );
    fclose( datafile );
    index_manager->write();
    _finalized = true;
}



row_t
WORowsSupplier::provideRow( cnode_id_t row_id, bool for_writing )
{
    char* _row = NULL;
    if ( for_writing )
    {
        _row = ::new char[ row_size ];                    // allocate memory, coz in any case we need it
        memset( _row, 0, row_size );
    }

    position_t _row_position = index->getPosition( row_id, 0 );
    if ( _row_position == non_index ) // it means, row is not in index.... just ignore, return empty row
    {
        return _row;
    }
    if ( _row == NULL )
    {
        _row = ::new char[ row_size ];                 // allocate memory, coz in any case we need it
    }
    position_t _raw_position = _row_position * element_size + _dataplace.second.first;

    if ( position != _raw_position )
    {
        if ( fseeko( datafile, _raw_position, SEEK_SET ) != 0 )
        {
            perror( "WORowsSupplier: Seek in data file error:" );
        }
    }
    if ( row_size != fread( _row, 1, row_size, datafile ) )
    {
        if ( ferror( datafile ) != 0 )
        {
            perror( "WORowsSupplier: Data file read error: " );
            throw ReadFileError( "WORowsSupplier: Cannot read a data file " + _dataplace.first );
        }
    }
    position = _raw_position + ( position_t )row_size;
    return _row;
}




void
WORowsSupplier::dropRow( row_t _row, cnode_id_t row_id )
{
    position_t _row_position = index->getPosition( row_id, 0 );
    if ( _row_position == non_index )
    {
        _row_position = index->setPosition( row_id, 0 );
    }

    position_t _raw_position = _row_position * element_size + _dataplace.second.first;


    if ( position != _row_position )
    {
        if ( fseeko( datafile, _raw_position, SEEK_SET ) != 0 )
        {
            perror( "WORowsSupplier: Seek in data file error:" );
        }
    }
    if ( row_size != fwrite( _row, 1, row_size, datafile ) )
    {
        if ( ferror( datafile ) != 0 )
        {
            perror( "WORowsSupplier: Data file write error: " );
            throw ReadFileError( "WORowsSupplier: Cannot write to the data file " + _dataplace.first );
        }
    }
    position = _raw_position + ( position_t )row_size;
    delete[] _row; // remove row from memory
}




bool
WORowsSupplier::probe( fileplace_t _dataplace,
                       fileplace_t )
{
    FILE* datafile = NULL;
    __FOPEN( datafile, _dataplace.first.c_str(), "r" );     // if file exists, cannot use this supplier, use instead RORowsSuplier
    if ( datafile == NULL )
    {
        return true;
    }
    fclose( datafile );
    return false;
}
