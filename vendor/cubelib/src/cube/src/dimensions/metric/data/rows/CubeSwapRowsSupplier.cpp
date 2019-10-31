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
 * \file CubeSwapRowsSupplier.cpp
 * \brief  Implements methods of the class SwapRowsSupplier
 */

#if !defined( __PGI ) && !defined( __CRAYXT )  && !defined( __CRAYXE )
#define _FILE_OFFSET_BITS 64
#endif

#include "config.h"

#include "CubeSwapRowsSupplier.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>

#include "CubeError.h"
#include "CubePlatformsCompat.h"
#include "CubeServices.h"

using namespace std;
using namespace cube;



SwapRowsSupplier::SwapRowsSupplier( std::string file,
                                    uint64_t    rs ) : RowsSupplier( rs )
{
    swapfile = file + ".swapfile";
    services::create_path_for_file( swapfile );
    __FOPEN( swpfd, swapfile.c_str(), "wb+" );
    if ( swpfd == NULL )
    {
        perror( "Swap file creation error: " );
        throw CreateFileError( "Cannot open a swap file " + swapfile );
    }
    next_new_row_position = 0;
    position              = 0;
    positions.clear();
}




SwapRowsSupplier::~SwapRowsSupplier()
{
    if ( _dummy_creation )
    {
        return;
    }
    fclose( swpfd );
    swpfd = NULL;
    if ( remove( swapfile.c_str() ) != 0 )
    {
        cerr << " Cannot delete swap file " << swapfile << " ";
        perror( "Swap file deleting error: " );
    }
}


row_t
SwapRowsSupplier::provideRow( cnode_id_t row_id, bool for_writing )
{
    char* _row = NULL;
    if ( positions.find( row_id ) != positions.end() ) // seems, that such row is stored in swap file. We seek there if needed and read
    {
        _row = new char[ row_size ];                   // allocate memory, coz in any case we need it
        memset( _row, 0, row_size );

        position_t _row_position = positions[ row_id ];
        if ( position != _row_position )
        {
            if ( fseeko( swpfd, _row_position * row_size, SEEK_SET ) != 0 )
            {
                perror( "Seek in swap file error:" );
            }
        }
        if ( row_size != fread( _row, 1, row_size, swpfd ) )
        {
            if ( ferror( swpfd ) != 0 )
            {
                perror( "Swap file read error: " );
                throw ReadFileError( "Cannot read a swap file " + swapfile );
            }
        }
        position = _row_position + row_size;
    }
    if ( for_writing && _row == NULL )
    {
        _row = new char[ row_size ];                // allocate memory, coz in any case we need it
        memset( _row, 0, row_size );
    }
    return _row;
}




void
SwapRowsSupplier::dropRow( row_t row, cnode_id_t row_id )
{
    if ( positions.find( row_id ) == positions.end() ) // seems, that such row is stored in swap file. We seek there if needed and read
    {
        positions[ row_id ] = next_new_row_position;
        next_new_row_position++;
    }

    position_t _row_position = positions[ row_id ];
    if ( position != _row_position )
    {
        if ( fseeko( swpfd, _row_position * row_size, SEEK_SET ) != 0 )
        {
            perror( "Seek in swap file error:" );
        }
    }
    if ( row_size != fwrite( row, 1, row_size, swpfd ) )
    {
        if ( ferror( swpfd ) != 0 )
        {
            perror( "Swap file write error: " );
            throw WriteFileError( "Cannot write a swap file " + swapfile );
        }
    }
    position = _row_position + row_size; // adjust seek position.
    delete[] row;                        // remove row from memory
}




bool
SwapRowsSupplier::probe( fileplace_t _dataplace,
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
