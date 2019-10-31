/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2018                                                     **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2015                                                     **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  Copyright (c) 2015                                                     **
**  RWTH Aachen University, JARA-HPC                                       **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/*-------------------------------------------------------------------------*/
/**
 *  @file
 *  @ingroup CUBE_lib.base
 *  @brief   Definition of the class CubeProxy.
 **/
/*-------------------------------------------------------------------------*/

#include "config.h"
#include "CubeProxy.h"

#include <cassert>
#include <iostream>
#include <limits>

#include "CubeIoProxy.h"
#include "CubeNetworkProxy.h"
#include "CubeUrl.h"

#ifdef USE_CUBE_TOOLS_LIB
#include "../../tools/common_inc/algebra4.h"
#include "../../tools/tools/0040.Tau2Cube/tau2cube_calls.h"
#endif

using namespace std;
using namespace cube;

namespace cube
{
const list_of_metrics      CubeProxy::ALL_METRICS;
const list_of_cnodes       CubeProxy::ALL_CNODES;
const list_of_regions      CubeProxy::ALL_REGIONS;
const list_of_sysresources CubeProxy::ALL_SYSTEMNODES;

CubeProxy::CubeProxy()
    : mUrl( "" ),
    mInitialized( false )
{
}


CubeProxy::~CubeProxy()
{
}

CubeProxy*
CubeProxy::create( std::string url_string )
{
    CubeProxy* obj = NULL;
    Url        url = Url( url_string );
    if ( url.getProtocol() == "cube" )
    {
        // open remote Cube via Client/Server
        obj = new CubeNetworkProxy( url.toString() );
        obj->defineAttribute( "cubename", obj->mUrl.toString() );
    }
    else
    {
        // open local Cube
        obj = new CubeIoProxy();
        obj->defineAttribute( "cubename", obj->mUrl.getPath() );
    }

    obj->mUrl = url;
    obj->setInitialized( true );

    return obj;
}

CubeProxy*
CubeProxy::create( Algorithm algo, std::vector<std::string> fileNames, std::vector<string> options )
{
    if ( fileNames.size() == 0 )
    {
        throw cube::Error( "empty list of files in CubeProxy::create" );
    }
    else if ( algo == ALGORITHM_DIFF && fileNames.size() != 2 )
    {
        throw cube::Error( "diff requires two filenames as argument" );
    }

    string protocol = Url( fileNames[ 0 ] ).getProtocol();
    for ( size_t i = 0; i < fileNames.size(); i++ )
    {
        Url url = Url( fileNames[ i ] );
        if ( url.getProtocol() != protocol )
        {
            throw cube::Error( "all files have to be either local or be placed on the same server" );
        }
    }

    CubeProxy* obj = NULL;
    if ( protocol == "file" )
    {
        cube::Cube** cubeList = NULL;
        if ( algo != ALGORITHM_TAU )
        {
            cubeList = new Cube*[ fileNames.size() ];
            for ( size_t i = 0; i < fileNames.size(); i++ )
            {
                cubeList[ i ] = new Cube();
                cubeList[ i ]->openCubeReport( fileNames[ i ] );
            }
        }
        bool        collapse = false, reduce = false;
        cube::Cube* result   = new Cube();
        switch ( algo ) // handle options of the algorithms
        {
            case ALGORITHM_DIFF:
            case ALGORITHM_MERGE:
            case ALGORITHM_MEAN:
                for ( size_t i = 0; i < options.size(); i++ )
                {
                    reduce   = ( options[ i ] == "reduce" ) ? true : reduce;
                    collapse = ( options[ i ] == "collapse" ) ? true : collapse;
                }
        }
        switch ( algo )
        {
#ifdef USE_CUBE_TOOLS_LIB
            case ALGORITHM_DIFF:
                cube4_diff( result, cubeList[ 0 ], cubeList[ 1 ], reduce, collapse );
                break;
            case ALGORITHM_MERGE:
                cube4_merge( result, cubeList, fileNames.size(), reduce, collapse );
                break;
            case ALGORITHM_MEAN:
                cube4_mean( result, cubeList, fileNames.size(), reduce, collapse );
                break;
            case ALGORITHM_TAU:
                create_from_tau( result, fileNames[ 0 ].c_str() );
                break;
#endif
            default:
                throw cube::Error( "Unknown algorithm in CubeProxy::create" );
        }
        if ( algo != ALGORITHM_TAU )
        {
            for ( size_t i = 0; i < fileNames.size(); i++ )
            {
                delete cubeList[ i ];
            }
            delete[] cubeList;
        }

        obj = new CubeIoProxy( result );
        obj->setInitialized( true );
    }
    else if ( protocol == "cube" )
    {
        throw cube::Error( "not yet implemented" );
    }

    return obj;
}

bool
CubeProxy::isInitialized() const
{
    return mInitialized;
}


void
CubeProxy::setInitialized( bool initialized )
{
    mInitialized = initialized;
}


const Url&
CubeProxy::getUrl() const
{
    return mUrl;
}


void
CubeProxy::setUrlPath( const std::string& path )
{
    mUrl.setPath( path );
}
}    /* namespace cube */
