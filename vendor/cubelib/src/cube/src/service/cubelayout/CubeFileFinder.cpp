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
 * \file CubeFileFinder.cpp
 * \brief Implements a methods of FileFinder class.
 */


#include "config.h"
#include <string>
#include <cstdlib>
#include <iostream>
#include <string.h>

#include "CubeTypes.h"
#include "CubeError.h"
#include "CubeFileFinder.h"
#include "CubeLayouts.h"
#include "CubeSimpleReader.h"


using namespace std;
using namespace cube;





fileplace_t
FileFinder::getAnchor()
{
    fileplace_t to_return;
    to_return.second.first  = ( uint64_t )-1;
    to_return.second.second = ( uint64_t )-1;

    std::string anchorname = layout->getFullPathToAnchor();

    if ( !creating_mode &&  !( reader->isFile( anchorname ) ) )
    {
        return to_return;
    }

    to_return.first = reader->getFile( anchorname );

    if ( !creating_mode )
    {
        to_return.second.first  = reader->getShift( anchorname );
        to_return.second.second = reader->getSize( anchorname );
    }
    else
    {
        to_return.second.first  = 0;
        to_return.second.second = 0;
    }
    return to_return;
}


fileplace_t
FileFinder::getMetricData( Metric* met )
{
    fileplace_t to_return;
    to_return.second.first  = ( uint64_t )-1;
    to_return.second.second = ( uint64_t )-1;
    std::string metric_data_name = layout->getFullPathToMetricData( met );

    if ( !creating_mode &&  !( reader->isFile( metric_data_name ) ) )
    {
        return to_return;
    }

    to_return.first = reader->getFile( metric_data_name );
    if ( !creating_mode )
    {
        to_return.second.first  = reader->getShift( metric_data_name );
        to_return.second.second = reader->getSize( metric_data_name );
    }
    else
    {
        to_return.second.first  = 0;
        to_return.second.second = 0;
    }



    return to_return;
}



fileplace_t
FileFinder::getMetricIndex( Metric* met )
{
    fileplace_t to_return;
    to_return.second.first  = ( uint64_t )-1;
    to_return.second.second = ( uint64_t )-1;
    std::string metric_index_name = layout->getFullPathToMetricIndex( met );

    if ( !creating_mode &&  !( reader->isFile( metric_index_name ) ) )
    {
        return to_return;
    }

    to_return.first = reader->getFile( metric_index_name );
    if ( !creating_mode )
    {
        to_return.second.first  = reader->getShift( metric_index_name );
        to_return.second.second = reader->getSize( metric_index_name );
    }
    else
    {
        to_return.second.first  = 0;
        to_return.second.second = 0;
    }
    return to_return;
}



fileplace_t
FileFinder::getMiscData( std::string filename )
{
    fileplace_t to_return;
    to_return.second.first  = ( uint64_t )-1;
    to_return.second.second = ( uint64_t )-1;
    std::string misc_data_name = layout->getFullPathToData( filename );

    if ( !creating_mode && !( reader->isFile( misc_data_name ) ) )
    {
        return to_return;
    }

    to_return.first = reader->getFile( misc_data_name );
    if ( !creating_mode )
    {
        to_return.second.first  = reader->getShift( misc_data_name );
        to_return.second.second = reader->getSize( misc_data_name );
    }
    else
    {
        to_return.second.first  = 0;
        to_return.second.second = 0;
    }
    return to_return;
}




FileFinder::~FileFinder()
{
    delete reader;
    delete layout;
}



void
FileFinder::finalizeFiles( std::string name )
{
    reader->createContainer( name );
}



std::vector< std::string>
FileFinder::getAllData()
{
    return reader->getAllFiles();
}


