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
 * \file CubeIndexMarker.cpp
 * \brief Initialization of a member of IndexMarker
 */

#include "config.h"
#include <utility>
#include <vector>
#include <istream>
#include <inttypes.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "CubeIndexMarker.h"
#include "CubeError.h"
using namespace std;
using namespace cube;


const string IndexMarker::marker = "CUBEX.INDEX";

bool
IndexMarker::checkMarker( fstream& in )
{
    const size_t _size  = marker.size() + 1;
    char*        Marker = ( char* )calloc( 1, _size );
    in.read( Marker, marker.size() );
    if ( marker.compare( Marker )  )
    {
        free( Marker );
        throw WrongMarkerInFileError( "IndexMarker::checkMarker( fstream& in ) :Index file marker at the beginning of header in index file is missing or wrong." );
    }
    free( Marker );
    return true;
}

bool
IndexMarker::checkMarker( FILE* in )
{
    const size_t _size  = marker.size() + 1;
    char*        Marker = ( char* )calloc( 1, _size );
    size_t       readed = fread( Marker, 1,  marker.size(), in );
    if ( readed != marker.size() )
    {
        free( Marker );
        throw ReadFileError( "IndexMarker::checkMarker(  FILE* in ) : Error during  writing of a index file marker. " );
    }
    if ( marker.compare( Marker )  )
    {
        free( Marker );
        throw WrongMarkerInFileError( "IndexMarker::checkMarker( FILE* in ) : Index file marker at the beginning of header in index file is missing or wrong." );
    }
    free( Marker );
    return true;
}


bool
IndexMarker::writeMarker( fstream& in )
{
    in.write( marker.c_str(),  marker.size() );
    return true;
}

bool
IndexMarker::writeMarker( FILE* in )
{
    if ( marker.size() != fwrite( marker.c_str(), 1,  marker.size(), in ) )
    {
        throw WriteFileError( "IndexMarker::writeMarker( FILE* in  ) : Error during  writing of a index file marker. " );
    }
    return true;
}
