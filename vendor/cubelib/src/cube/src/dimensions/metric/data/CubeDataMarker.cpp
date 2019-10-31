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
 * \file CubeDataMarker.cpp
 * \brief Initialization of a member
 */


#include "config.h"
#include <utility>
#include <vector>
#include <istream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <inttypes.h>

#include "CubeDataMarker.h"
#include "CubeError.h"
using namespace std;
using namespace cube;



bool
DataMarker::checkMarker( fstream& in )
{
    const size_t _size  = marker.size() + 1;
    char*        Marker = ( char* )calloc( 1, _size );
    in.read( Marker, marker.size() );
    if ( marker.compare( Marker ) )
    {
        free( Marker );
        throw WrongMarkerInFileError( "DataMarker::checkMarker( fstream& in ) : Data file marker at the beginning of the data  file is missing or wrong." );
    }
    free( Marker );
    return true;
}

bool
DataMarker::checkMarker( FILE* in )
{
    const size_t _size  = marker.size() + 1;
    char*        Marker = ( char* )calloc( 1, _size );

    size_t readed = fread( Marker, 1,  marker.size(), in );
    if ( readed != marker.size() )
    {
		perror ("The following error occurred");
        free( Marker );
        throw ReadFileError( "DataMarker::checkMarker(  FILE* in ) : Error during  reading of a data file marker. " );
    }
    if ( marker.compare( Marker ) )
    {
        free( Marker );
        throw WrongMarkerInFileError( "DataMarker::checkMarker( FILE* in ) : Data file marker at the beginning of the data  file is missing or wrong." );
    }
    free( Marker );
    return true;
}


bool
DataMarker::writeMarker( fstream& in )
{
    in.write( marker.c_str(),  marker.size() );
    return true;
}

bool
DataMarker::writeMarker( FILE* in )
{
    size_t written = fwrite( marker.c_str(), 1,  marker.size(), in );
    if ( marker.size() != written )
    {
		perror ("The following error occurred");
        throw WriteFileError( "DataMarker::writeMarker( FILE* in  ) : Error during  writing of a data file marker. " );
    }
    return true;
}

