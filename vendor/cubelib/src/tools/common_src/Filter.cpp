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


#include "config.h"

#include "Filter.h"

#include <fstream>
#include <set>
#include <string>

#ifndef __MINGW32__
#include <fnmatch.h>
#endif
#ifdef __MINGW32__
#include "CubePlatformsCompat.h"
#endif


#include "CubeRegion.h"

using namespace cube;
using namespace std;

void
Filter::add_file( string file_url )
{
    ifstream ifs( file_url.c_str(), ios_base::in );
    string   line;
    while ( 1 )
    {
        ifs >> line;
        if ( ifs.eof() )
        {
            break;
        }
        filter_set.insert( line );
    }
}

bool
Filter::matches( Cnode* node ) const
{
    return matches( node->get_callee()->get_name() );
}

bool
Filter::matches( const string& node_name ) const
{
    ( void )node_name;   // suppress warning on win32, where there is no fnmatch
    // TODO: For efficiency, we may detect whether a line is really a pattern or just
    //   a string. Using this detection, we may apply a filter to a single node in
    //     O(log(number of non-wildcard-filters) + (number of wildcard-filters))
    //   instead of
    //     O(number of filters).
    for ( set<string>::const_iterator it = filter_set.begin();
          it != filter_set.end(); ++it )
    {
        if ( fnmatch( it->c_str(), node_name.c_str(), 0 ) != FNM_NOMATCH )
        {
            return true;
        }
    }
    return false;
}
