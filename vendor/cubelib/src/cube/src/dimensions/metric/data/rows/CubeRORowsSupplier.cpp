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
 * \file CubeRORowsSupplier.cpp
 * \brief  Implements methods of the class RORowsSupplier
 */

#include "config.h"
#if !defined( __PGI ) && !defined( __CRAYXT )  && !defined( __CRAYXE )
#define _FILE_OFFSET_BITS 64
#endif


#include <cstdio>
#include <unistd.h>
#include <cstring>


#include "CubePlatformsCompat.h"
#include "CubeRORowsSupplier.h"
#include "CubeError.h"
#include "CubeIndexManager.h"
#include "CubeIndexes.h"


using namespace std;
using namespace cube;



RORowsSupplier::RORowsSupplier(
    fileplace_t DataPlace,
    fileplace_t IndexPlace,
    uint64_t    rs,
    uint64_t    es,
    DataMarker* _dm
    ) : RowsSupplier( rs ), dataMarker( _dm ), _dataplace( DataPlace ), _indexplace( IndexPlace )
{
    element_size = es;
    initIndex( rs, es );
    initData();
    element_size = es;
}



void
RORowsSupplier::initIndex( uint64_t rs, uint64_t es )
{
    index_manager = new IndexManager( _indexplace, 0xFFFFFFFFL, rs );
    index         = index_manager->getIndex();
    endianness    = index_manager->getTrafo();
    row_size      = rs * es;
}



void
RORowsSupplier::initData()
{
    __FOPEN( datafile, _dataplace.first.c_str(), "rb" );
    if ( datafile == NULL )
    {
        perror( "RORowsSupplier::initData(): Data file opening error: " );
        throw OpenFileError( "RORowsSupplier::initData(): Cannot open data file " + _dataplace.first );
    }
    setvbuf( datafile, NULL, _IOFBF, IO_BUFFERSIZE );
    if ( fseeko( datafile, _dataplace.second.first, SEEK_SET ) )
    {
        perror( "RORowsSupplier::initData(): Seek in data file error:" );
    }
    dataMarker->checkMarker( datafile );
    _dataplace.second.first  += dataMarker->markerSize();
    _dataplace.second.second -= dataMarker->markerSize();
    position                  = 0;
    position                 += dataMarker->markerSize();
}








RORowsSupplier::~RORowsSupplier()
{
    if ( _dummy_creation )
    {
        return;
    }
    ::delete dataMarker;
    ::delete index_manager;
    fclose( datafile );
}


row_t
RORowsSupplier::provideRow( cnode_id_t row_id, bool for_writing )
{
    char* _row = NULL;
    if ( for_writing )
    {
        _row = ::new char[ row_size ];                    // allocate memory, coz in any case we need it
        memset( _row, 0, row_size );
    }
    position_t _row_position = index->getPosition( row_id, 0 );
    if ( _row_position == non_index )     // it means, row is not in index.... just ignore, return empty row
    {
        return _row;
    }
    position_t _raw_position = _row_position * element_size + _dataplace.second.first;
    if ( _raw_position + row_size > ( _dataplace.second.second + _dataplace.second.first ) )
    {
        return _row;                   // return empty string if out of file
    }
    if ( _row == NULL )
    {
        _row = ::new char[ row_size ];                     // allocate memory, coz in any case we need it
        memset( _row, 0, row_size );
    }
    if ( position != _raw_position )
    {
        if ( fseeko( datafile, _raw_position, SEEK_SET ) != 0 )
        {
            perror( "RORowsSupplier::Seek in data file error:" );
        }
    }
    if ( row_size != fread( _row, 1, row_size, datafile ) )
    {
        if ( ferror( datafile ) != 0 )
        {
            perror( "RORowsSupplier::Data file read error: " );
            throw ReadFileError( "RORowsSupplier:: Cannot read a data file " + _dataplace.first );
        }
    }
    position = _raw_position + row_size;

    return _row;
}




void
RORowsSupplier::dropRow( row_t _row, cnode_id_t )
{
    ::delete[] _row; // remove row from memory, no saving in file ??? read only
}


bool
RORowsSupplier::probe( fileplace_t _dataplace,
                       fileplace_t )
{
    DataMarker* _dm      = new DataMarker();
    FILE*       datafile = NULL;
    __FOPEN( datafile,  _dataplace.first.c_str(), "rb" );
    if ( datafile == NULL )
    {
        ::delete _dm;
        return false;
    }
    if ( fseeko( datafile, _dataplace.second.first, SEEK_SET ) )
    {
        ::delete _dm;
        perror( "RORowsSupplier::probe: Seek in data file error:" );
        return false;
    }
    try
    {
        _dm->checkMarker( datafile );
    }
    catch ( const WrongMarkerInFileError& err )
    {
        fclose( datafile );
        ::delete _dm;
        return false;
    }
    fclose( datafile );
    ::delete _dm;
    return true;
}
