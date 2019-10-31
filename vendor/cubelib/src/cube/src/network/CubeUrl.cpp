/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2017                                                     **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2014-2015                                                **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  Copyright (c) 2014-2015                                                **
**  RWTH Aachen University, JARA-HPC                                       **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/*-------------------------------------------------------------------------*/
/**
 *  @file
 *  @ingroup CUBE_lib.network
 *  @brief   Definition of the class cube::Url.
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeUrl.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <iterator>

#include "CubeError.h"

using namespace std;

namespace cube
{
Url::Url()
    : mPort( mDefaultPort ),
    mPath( mDefaultPath )
{
}


Url::Url( const string& url_string )
    : mPort( mDefaultPort ),
    mPath( mDefaultPath )
{
    parse( url_string );
}


void
Url::parse( const string& url_string )
{
    // --- Detect protocol

    const string           protocol_delimiter( "://" );
    string::const_iterator token_it = search( url_string.begin(),
                                              url_string.end(),
                                              protocol_delimiter.begin(),
                                              protocol_delimiter.end() );

    if ( token_it == url_string.end() )
    {
        // no protocol section found; set default
        mProtocol = mDefaultProtocol;
        token_it  = url_string.begin();
    }
    else
    {
        // protocol section found; copy lower-case string into mProtocol
        mProtocol.reserve( distance( url_string.begin(), token_it ) );
        transform( url_string.begin(), token_it,
                   back_inserter( mProtocol ),
                   ptr_fun< int, int >( tolower ) );
        advance( token_it, protocol_delimiter.length() );
    }


    // --- Detect server name (i.e. address), port and path

    string::const_iterator it = token_it;
    const string           port_and_path_delimiter( ":/" );

    if ( mProtocol != "file" )
    {
        // check if explicit port or path is given on rest of url_string
        it = find_first_of( token_it, url_string.end(),
                            port_and_path_delimiter.begin(),
                            port_and_path_delimiter.end() );

        // either way, the next part of the URL would be the address
        if ( distance( token_it, it ) == 0 )
        {
            // no host given
            throw cube::UnrecoverableNetworkError( "No host given." );
        }
        else
        {
            // explicit address given; copy it into into mHost
            mHost.reserve( distance( token_it, it ) );
            transform( token_it, it,
                       back_inserter( mHost ),
                       ptr_fun< int, int >( tolower ) );
        }

        // port is given?
        if ( *it == ':' )
        {
            // explicit port it given
            advance( it, 1 );
            string::const_iterator port_end = find_first_of( it,
                                                             url_string.end(),
                                                             port_and_path_delimiter.begin(),
                                                             port_and_path_delimiter.end() );

            stringstream s( url_string.substr( distance( url_string.begin(), it ),
                                               distance( it, port_end ) ) );
            s >> mPort;

            advance( it, distance( it, port_end ) );
        }

        if ( it != url_string.end() )
        {
            advance( it, 1 );
        }
    }

    string::const_iterator::difference_type len = distance( it, url_string.end() );
    if ( len != 0 )
    {
        // explicit path is given; copy path as is
        mPath = url_string.substr( distance( url_string.begin(), it ),
                                   distance( it, url_string.end() ) );
    }
}


const string
Url::toString() const
{
    if ( getProtocol() == "file" )
    {
        return getProtocol() + "://" + getPath();
    }
    else
    {
        stringstream portStr;
        if ( !( getPort() == this->getDefaultPort() ) )
        {
            portStr << ":" << getPort();
        }

        return getProtocol() + "://" + getHost() + portStr.str() + "/"
               + getPath();
    }
}


const string       Url::mDefaultProtocol = "file";
const string       Url::mDefaultHost     = "";
const unsigned int Url::mDefaultPort     = 3300;
const string       Url::mDefaultPath     = "";
}    /* namespace cube */
