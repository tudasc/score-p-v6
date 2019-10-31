/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2016                                                **
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
 * \file CubeIndexManager.cpp
 * \brief Provides methods for the IndexManager
 */


#include "config.h"
#include <istream>
#include <iostream>
#include <cstring>
#include <cstdio>

#include "CubePlatformsCompat.h"
#include "CubeIndexManager.h"
#include "CubeTrafos.h"
#include "CubeError.h"
#include "CubeIndexes.h"
#include "CubeIndexHeader.h"


using namespace std;
using namespace cube;


IndexManager::IndexManager( fileplace_t      filename,
                            cnodes_number_t  nc,
                            threads_number_t nt )
{
    read_only     = true;
    indexfilename = filename;
    header        = NULL;
    if ( indexfilename.first == ".index" )
    {
        return;
    }
    header = new IndexHeader(  nc, nt );
    fstream in;
    in.open( indexfilename.first.c_str(), ios::in | ios::binary );
    if ( in.is_open() )
    {
        try
        {
            in.seekg( indexfilename.second.first );
            header->readHeader( in );
        }
        catch ( const WrongMarkerInFileError& e )
        {
            throw RuntimeError( " Error in index file  " + filename.first + ": " + e.what() );
        }
        trafo = header->getTrafo();

        index = header->getIndex();
        index->readData( in );
        in.close();
        n_threads = nt;
        n_cnodes  = nc;
    }
    else
    {
        throw  NoIndexFileError( "No index file " + filename.first );
    }
}

IndexManager::IndexManager( fileplace_t      filename,
                            cnodes_number_t  nc,
                            threads_number_t nt,
                            IndexFormat      format )
{
    read_only     = false;
    indexfilename = filename;
    header        = NULL;
    if ( indexfilename.first == ".index" )
    {
        read_only = true;
    }

    FILE* indexfile = NULL;
	__FOPEN(indexfile, indexfilename.first.c_str(), "rb+" );
    if ( indexfile != NULL ) //  if it exists, it is probably readonly
    {
        fclose( indexfile );
        ::IndexManager( filename, nc, nt );
        return;
    }
    trafo     = NULL;
    header    = new IndexHeader( nc, nt, format );
    trafo     = header->getTrafo();
    index     = header->getIndex();
    n_threads = nt;
    n_cnodes  = nc;
}


IndexManager::~IndexManager()
{
    if ( header != NULL )
    {
        delete header;
    }
}


void
IndexManager::write()
{
    if ( !read_only )
    {
        FILE* fout = NULL;
		__FOPEN(fout, indexfilename.first.c_str(), "wb" );

        if ( fout != NULL )
        {
            fseek( fout, indexfilename.second.first, SEEK_SET );
            header->writeHeader( fout );
            index->writeData( fout );
            fclose( fout );
        }
    }
}



Index*
IndexManager::getIndex()
{
    return index;
}


SingleValueTrafo*
IndexManager::getTrafo()
{
    return trafo;
};



threads_number_t
IndexManager::getNumberOfThreads()
{
    return n_threads;
};

cnodes_number_t
IndexManager::getNumberOfCNodes()
{
    return n_cnodes;
};


