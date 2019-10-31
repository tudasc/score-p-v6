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
 * \file CubeWOZRowsSupplier.cpp
 * \brief  Implements methods of the class SwapRowsSupplier
 */

#if !defined( __PGI ) && !defined( __CRAYXT )  && !defined( __CRAYXE )
#define _FILE_OFFSET_BITS 64
#endif

#include "config.h"
#ifdef FRONTEND_CUBE_COMPRESSED
#include "zlib.h"
#endif

#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <unistd.h>

#include "CubePlatformsCompat.h"
#include "CubeWOZRowsSupplier.h"
#include "CubeError.h"
#include "CubeServices.h"
#include "CubeTrafos.h"
#include "CubeIndexManager.h"
#include "CubeIndexes.h"


using namespace std;
using namespace cube;


WOZRowsSupplier::WOZRowsSupplier() : SwapRowsSupplier()
{
    endianness = new NOPTrafo();
};

WOZRowsSupplier::WOZRowsSupplier(  fileplace_t DataPlace,
                                   fileplace_t IndexPlace,
                                   uint64_t    rs,
                                   uint64_t    es,
                                   DataMarker* _dm
                                   ) : SwapRowsSupplier( DataPlace.first, rs ), dataMarker( _dm ), _dataplace( DataPlace ), _indexplace( IndexPlace ) // rs is wrong, has to be corrected here (SwapRowsSupplier expects rs in bytes, here it is in value size units)
{
    initIndex( rs, es );
    element_size = es;
    datafile     = NULL;
}




void
WOZRowsSupplier::initIndex( uint64_t rs, uint64_t es )
{
    index_manager = new IndexManager( _indexplace, 0xFFFFFFFFL, rs, CUBE_INDEX_FORMAT_SPARSE  );
    index         = index_manager->getIndex();
    endianness    = index_manager->getTrafo();

//     value    = index_manager->getValue();
    row_size = rs * es;
}

void
WOZRowsSupplier::initData()
{
    services::create_path_for_file( _dataplace.first.c_str() );
    __FOPEN( datafile, _dataplace.first.c_str(), "rb+" );
    if ( datafile == NULL )
    {
        services::create_path_for_file( _dataplace.first.c_str() );
        __FOPEN( datafile, _dataplace.first.c_str(), "wb" );
        if ( datafile == NULL )
        {
            perror( ( string( "WOZRowsSupplier::initData(): Data file opening error: " ) +  _dataplace.first ).c_str()  );
            throw OpenFileError( "WOZRowsSupplier::initData(): Cannot open data file " + _dataplace.first );
        }
    }
    setvbuf( datafile, NULL, _IOFBF, IO_BUFFERSIZE );
    if ( fseeko( datafile, _dataplace.second.first, SEEK_SET ) )
    {
        perror( "WOZRowsSupplier::initData(): Seek in data file error:" );
    }
    dataMarker->writeMarker( datafile );
    _dataplace.second.first  += dataMarker->markerSize();
    _dataplace.second.second -= dataMarker->markerSize();
}


WOZRowsSupplier::~WOZRowsSupplier()
{
    if ( _dummy_creation )
    {
        return;
    }

    delete dataMarker;
    delete index_manager;
};


void
WOZRowsSupplier::finalize()
{
    finalizeData();
    index_manager->write();
    _finalized = true;
}

void
WOZRowsSupplier::finalizeData()
{
#ifdef FRONTEND_CUBE_COMPRESSED // to prevent compilation error.... failed test previosly should prevent, that this call get executed at all.


    initData();


    char* _row = ::new char[ row_size ];

    subindex_size = positions.size();
    sub_index     = new SubIndexElement[ subindex_size ];

    position_t shift = _dataplace.second.first +
                       sizeof( uint64_t ) +
                       subindex_size * sizeof( SubIndexElement );
    if ( fseeko( datafile,  shift, SEEK_SET ) != 0 )
    {
        perror( "Seek in data file error:" );
    }

    std::map<cnode_id_t, position_t>::iterator it;
    // we run over all rows in swap file. their position is synchron with the sparse index.
    uint64_t i        = 0;
    uint64_t compsize = 0;



    //
    // ROWWISE READING AND WRITING
    // KIND OF CACHING IN BIGGER BUFFER MIGHT HELP TO USE BANDWIDTH
    //
    for ( it = positions.begin(); it != positions.end(); ++it, ++i )
    {
        position_t _raw_position = ( *it ).second * row_size;
        // seek to the row
        if ( fseeko( swpfd, _raw_position, SEEK_SET ) != 0 )
        {
            perror( "Seek in swap file error:" );
        }
        // read the row to the memory
        if ( row_size != fread( _row, 1, row_size, swpfd ) )
        {
            if ( ferror( swpfd ) != 0 )
            {
                perror( "Swap file read error: " );
                throw ReadFileError( "Cannot read a swap file " + swapfile );
            }
        }
        // compress the row.
        // ------- extimate size
        uLongf compressed_row_size = compressBound( row_size );
        Bytef* _z_row              = new Bytef[ compressed_row_size ];



        compress( _z_row,   &compressed_row_size, ( Bytef* )( _row ), row_size );

        sub_index[ i ].named.start_uncompressed = i * row_size;
        sub_index[ i ].named.start_compressed   = compsize;
        sub_index[ i ].named.size_compressed    = compressed_row_size;
        compsize                               += compressed_row_size; // update the place where the data starts


        if ( compressed_row_size != fwrite( ( char* )_z_row, 1, compressed_row_size, datafile ) )
        {
            perror( "Compressed data file write  error: " );
            throw WriteFileError( "Cannot write  compressed file " + _dataplace.first );
        }
        delete[] _z_row;
    }
    if ( fseeko( datafile, _dataplace.second.first, SEEK_SET ) != 0 )
    {
        perror( "Seek to the header of compressed  data file error:" );
    }
    if ( sizeof( subindex_size ) != fwrite( ( char* )&subindex_size, 1, sizeof( subindex_size ), datafile ) )
    {
        perror( "Size of the subindex write  error: " );
        throw WriteFileError( "Cannot write  the size if the subindex into " + _dataplace.first );
    }
    if ( subindex_size * sizeof( SubIndexElement ) != fwrite( ( char* )sub_index, 1, subindex_size * sizeof( SubIndexElement ), datafile ) )
    {
        perror( "Subindex write  error: " );
        throw WriteFileError( "Cannot write the subindex into " + _dataplace.first );
    }


//     __temp_print_sub_index();

    delete[] sub_index;
    delete[] _row;
    fclose( datafile );
    _finalized = true;
#endif
}

void
WOZRowsSupplier::dropRow( row_t      row,
                          cnode_id_t row_id )
{
    position_t _row_position = index->getPosition( row_id, 0 );
    if ( _row_position == non_index )
    {
        _row_position = index->setPosition( row_id, 0 );
    }

    SwapRowsSupplier::dropRow( row, row_id );
}


bool
WOZRowsSupplier::probe( fileplace_t _dataplace,
                        fileplace_t )
{
    ( void )_dataplace;
#ifdef FRONTEND_CUBE_COMPRESSED
    FILE* datafile = NULL;
    __FOPEN( datafile, _dataplace.first.c_str(), "r" );     // if file exists, cannot use this supplier, use instead RORowsSuplier
    if ( datafile == NULL )
    {
        return true;
    }
    fclose( datafile );
#endif
    return false;
}


void
WOZRowsSupplier::__temp_print_row( row_t _row )
{
    if ( _row == NULL )
    {
        cout << "0xNULL" << endl;
        return;
    }
    char* pos    = _row;
    char* endpos = _row  + row_size;

    cout << " ================================================ " << endl;
    while ( pos < endpos  )
    {
        cout << hex << *( ( uint8_t* )pos ) << dec << " ";
        ++pos;
    }
    cout << endl << " ================================================ " << endl;
}


void
WOZRowsSupplier::__temp_print_sub_index()
{
    cout << " --------------- SUBINDEX -------------------- " << endl;
    cout << "Size:  " << subindex_size << endl;
    cout << " start uncomp \t\t start compr \t\t size compressed " << endl;
    for ( uint64_t i = 0; i < subindex_size; ++i )
    {
        cout <<
            sub_index[ i ].named.start_uncompressed  << "\t\t" <<
            sub_index[ i ].named.start_compressed  << "\t\t" <<
            sub_index[ i ].named.size_compressed << endl;
    }
    cout << " -----------END SUBINDEX -------------------------" << endl;
}
