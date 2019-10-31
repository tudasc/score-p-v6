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
 * \file CubeROZRowsSupplier.cpp
 * \brief  Implements methods of the class ROZRowsSupplier
 */
#if !defined( __PGI ) && !defined( __CRAYXT )  && !defined( __CRAYXE )
#define _FILE_OFFSET_BITS 64
#endif


#include "config.h"

#if defined( FRONTEND_CUBE_COMPRESSED ) ||  defined ( FRONTEND_CUBE_COMPRESSED_READONLY )
#include "zlib.h"
#endif

#include <cstdio>
#include <cstring>
#include <iostream>

#include "CubePlatformsCompat.h"
#include "CubeROZRowsSupplier.h"
#include "CubeError.h"
#include "CubeDataMarker.h"
#include "CubeZDataMarker.h"
#include "CubeTrafos.h"
#include "CubeIndexes.h"

using namespace std;
using namespace cube;



ROZRowsSupplier::ROZRowsSupplier(
    fileplace_t DataPlace,
    fileplace_t IndexPlace,
    uint64_t    rs,
    uint64_t    es,
    DataMarker* _dm ) : RORowsSupplier( DataPlace, IndexPlace, rs, es, _dm )
{
    sub_index = new map<uint64_t, SubIndexInternalElement> ();
    initSubIndex();
}



void
ROZRowsSupplier::initSubIndex()
{
    size_t readed = fread( ( char* )&subindex_size, 1, sizeof( subindex_size ), datafile );    // read length of the index;
    if ( readed != sizeof( subindex_size ) )
    {
        if ( ferror( datafile ) != 0 )
        {
            cerr << "Error in the ROZRowsSupplier::initSubIndex():fread((char *)&_n_rows  1, sizeof(_n_rows), datafile) : "  << endl;
        }
    }
    endianness->trafo( ( char* )&subindex_size, sizeof( subindex_size ) );

    // allocate memory for subindex (tmp flat copy)
    SubIndexElement* _sub_index = new SubIndexElement[ subindex_size ];

    // read the subindex from the file
    readed = fread( ( char* )_sub_index, 1, subindex_size * sizeof( SubIndexElement ), datafile );
    if ( readed != subindex_size * sizeof( SubIndexElement ) )
    {
        if ( ferror( datafile ) != 0 )
        {
            cerr <<  "Error in the ROZRowsSupplier::initSubIndex():fread((char *)sub_index, 1, _n_rows*sizeof(SubIndexElement), datafile) : "  << endl;
        }
    }

    for ( unsigned i = 0; i < subindex_size; ++i )
    {
        endianness->trafo( ( char* )&( _sub_index[ i ].named.start_uncompressed ), sizeof( uint64_t ) );
        endianness->trafo( ( char* )&( _sub_index[ i ].named.start_compressed ),   sizeof( uint64_t ) );
        endianness->trafo( ( char* )&( _sub_index[ i ].named.size_compressed ),    sizeof( uint64_t ) );

        SubIndexInternalElement _element;
        _element.named.row_number       = i;
        _element.named.start_compressed = _sub_index[ i ].named.start_compressed;
        _element.named.size_compressed  = _sub_index[ i ].named.size_compressed;

        ( *sub_index )[ _sub_index[ i ].named.start_uncompressed ] = _element;
    }
    delete[] _sub_index; // remove tmp copy

    // _dataplace.second.first is already shifted on marker size
    _dataplace.second.first  += ( sizeof( subindex_size ) + ( subindex_size * sizeof( SubIndexElement ) ) );
    _dataplace.second.second -= ( sizeof( subindex_size ) + ( subindex_size * sizeof( SubIndexElement ) ) );
    position                 += (  sizeof( subindex_size ) + ( subindex_size * sizeof( SubIndexElement ) ) );
}



ROZRowsSupplier::~ROZRowsSupplier()
{
    if ( _dummy_creation )
    {
        return;
    }
    delete sub_index;
    // dataMarker shouldn't be removed. It gets removed in parent destructor.
}


row_t
ROZRowsSupplier::provideRow( cnode_id_t row_id, bool for_writing  )
{
#if defined( FRONTEND_CUBE_COMPRESSED ) || defined( FRONTEND_CUBE_COMPRESSED_READONLY ) // to prevent compilation error.... failed test previosly should prevent, that this call get executed at all.
    char* _row = NULL;
    if ( for_writing )
    {
        _row = ::new char[ row_size ];                    // allocate memory, coz in any case we need it
        memset( _row, 0, row_size );
    }

    // get a position in NON COMPRESSED CASE
    position_t _row_position = index->getPosition( row_id, 0 );
    if ( _row_position == non_index )     // it means, row is not in index.... just ignore, return empty row
    {
        return _row;
    }
    // get raw position in not compressed case (not shifted)
    position_t _raw_position_not_shifted = _row_position * element_size;
    // translate non comprased row postion into compressed row
    map<uint64_t, SubIndexInternalElement>::iterator found_row;
    found_row = sub_index->find( _raw_position_not_shifted );
    if ( found_row != sub_index->end() )     // if we have such row (found in index)
    {
        SubIndexInternalElement _found_element = ( *found_row ).second;

        // seek in the file to the beginning of the row
        position_t _raw_position = _found_element.named.start_compressed + _dataplace.second.first;
        if ( _raw_position + _found_element.named.size_compressed > ( _dataplace.second.second + _dataplace.second.first ) )
        {
            return _row;                 // return empty string if out of file
        }
        if ( _row == NULL )
        {
            _row = ::new char[ row_size ];                 // allocate memory, coz in any case we need it
        }
        if ( position != _raw_position )
        {
            if ( fseeko( datafile, _raw_position, SEEK_SET ) != 0 )
            {
                perror( "Seek in compressed data file error:" );
            }
        }

        // read compressed data
        Bytef* localbuffer = new Bytef[ _found_element.named.size_compressed ];
        if ( _found_element.named.size_compressed != fread( localbuffer, 1, _found_element.named.size_compressed, datafile ) )
        {
            if ( ferror( datafile ) != 0 )
            {
                perror( "Compressed data file read error: " );
                delete _row;
                throw ReadFileError( "Cannot read a compressed data file " + _dataplace.first );
            }
        }
        // uncompress
        Bytef* ptr_dest  = ( Bytef* )( _row );                           // type cast of destination for zlib
        uLongf dest_size = row_size;

        Bytef* ptr_src  = ( Bytef* )( localbuffer );                           // type case of source for zlib
        uLongf src_size = _found_element.named.size_compressed;
        int    z_result =               uncompress(
            ptr_dest,
            &dest_size,
            ptr_src,
            src_size
            );
        if ( z_result != Z_OK )     // compression error occured
        {
            if ( z_result == Z_MEM_ERROR )
            {
                throw ZNotEnoughMemoryError();
            }
            if ( z_result == Z_BUF_ERROR )
            {
                throw ZNotEnoughBufferError();
            }
            if ( z_result == Z_DATA_ERROR )
            {
                throw ZDataCorruptError();
            }
        }


        delete[] localbuffer;
        position = _raw_position + _found_element.named.size_compressed;
    }
    // at this point _row is either loaded or was empty.
    return _row;
#else
    return NULL;
#endif
}




void
ROZRowsSupplier::dropRow( row_t _row, cnode_id_t )
{
    ::delete[] _row; // remove row from memory, no saving in file ? read only (because of compression)
}




bool
ROZRowsSupplier::probe( fileplace_t _dataplace,
                        fileplace_t )
{
    DataMarker* _dm      = new ZDataMarker();
    FILE*       datafile = NULL;
    __FOPEN( datafile,  _dataplace.first.c_str(), "r" );
    if ( datafile == NULL )
    {
        delete _dm;
        return false;
    }
    if ( fseeko( datafile, _dataplace.second.first, SEEK_SET ) )
    {
        delete _dm;
        perror( "ROZRowsSupplier::probe: Seek in data file error:" );
        return false;
    }
    try
    {
        _dm->checkMarker( datafile );
    }
    catch ( const WrongMarkerInFileError& err )
    {
        fclose( datafile );
        delete _dm;
        return false;
    }
    fclose( datafile );
    delete _dm;
#if defined( FRONTEND_CUBE_COMPRESSED ) || defined( FRONTEND_CUBE_COMPRESSED_READONLY )
    return true;
#else
    cerr << "This installation of cube doesn't support compressed cube files. " << endl << endl <<
        "Please recompile and reinstall CUBE using configure flag --with-compression=full|ro and --with-frontend-zlib=[path to zlib]." << endl;
    return false; // in this case we cannot read compressed cubes
#endif
}


void
ROZRowsSupplier::__temp_print_row( row_t _row )
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
        cout << hex << *( ( uint8_t* )( pos ) ) << dec << " ";
    }
    cout << endl << " ================================================ " << endl;
}


void
ROZRowsSupplier::__temp_print_sub_index()
{
    cout << " --------------- SUBINDEX -------------------- " << endl;
    cout << "Size:  " << sub_index->size() << endl;
    cout << " start uncomp \t\t row number \t\t start compr \t\t size compressed " << endl;
    for ( map<uint64_t, SubIndexInternalElement>::iterator iter = sub_index->begin(); iter != sub_index->end(); ++iter )
    {
        cout <<         ( *iter ).second.named.row_number  << "\t\t" <<
        ( *iter ).first << " \t\t" <<
        ( *iter ).second.named.start_compressed  << "\t\t" <<
        ( *iter ).second.named.size_compressed << endl;
    }
    cout << " -----------END SUBINDEX -------------------------" << endl;
}
