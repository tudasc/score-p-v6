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
 * \file CubeLayoutDetector.cpp
 * \brief Provides a method to select a proper Lyout and Container to use in Cube
 */

#include "config.h"

#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLayoutDetector.h"
#include "CubeError.h"
#include "CubeFileFinder.h"
#include "CubeLayouts.h"
#include "CubeSimpleReader.h"
#include "CubeTarReader.h"
#include "CubeServices.h"


using namespace std;
using namespace cube;




FileFinder*
LayoutDetector::getFileFinder( const std::string& cubename )
{
    static std::string extensions[ 1 ];
    bool               istar = false;

    std::string tarname = ( services::get_cube4_name( cubename ) + ".cubex" );

    FILE* tar = fopen( tarname.c_str(), "r" );
    if ( tar != NULL )
    {
        tar_gnu_header header;
        size_t         readedsize = fread( ( char* )&header, 1, sizeof( tar_gnu_header ), tar );
        if ( readedsize == sizeof( tar_gnu_header ) )
        {   // readed 512 bytes .... good signn
            if (
                ( strcmp( header.magic, "ustar" ) == 0 ) ||
                ( strcmp( header.magic, "ustar  " ) == 0 ) ||
                ( strcmp( header.magic, "ustar 00" ) == 0 )
                )
            {   // it is a tar archive
                istar = true;
                fclose( tar );
            }
        }
    }
    // then according the header and marker "ustar"
    if ( istar )
    {
        TarReader* tr = new TarReader( tarname );
        if ( tr->contains_ending( "anchor.xml" ) )
        {
            return new FileFinder( tr, new FileEmbeddedLayout( cubename ) );   // special case, if hte archive named "anchor" but has a hybrid layout.
        }
        throw NoFileInTarError( "anchor.xml" );
    }
    throw RuntimeError( "All tests failed. Cannot determine what layout to use to create CUBE object. No file " + cubename );
}


FileFinder*
LayoutDetector::getDefaultFileFinderForWriting()
{
    bool        creating_mode = true;
    std::string name          = services::create_unique_dir_name();
    return new FileFinder( new TarReader( name, creating_mode ), new FileEmbeddedLayout( services::get_cube4_name( name ) ), creating_mode );
}


FileFinder*
LayoutDetector::getTmpFileFinder()
{
    bool        creating_mode = true;
    std::string name          = services::create_unique_dir_name();
    return new FileFinder( new TarReader( name, creating_mode ), new FileEmbeddedLayout( services::get_cube4_name( name ) ), creating_mode );
}

FileFinder*
LayoutDetector::getVirtualFileFinder()
{
    bool        creating_mode = false;
    std::string name          = "";
    return new FileFinder( new SimpleReader(), new VirtualLayout(), creating_mode );
}
