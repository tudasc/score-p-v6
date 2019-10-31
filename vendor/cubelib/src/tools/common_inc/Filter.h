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



#ifndef _FILTER_H_GUARD_
#define _FILTER_H_GUARD_

#include <string>
#include <set>

#include "CubeCnode.h"

namespace cube
{
class Filter
{
public:
    void
    add_file( std::string file_url );
    bool
    matches( Cnode* node ) const;
    bool
    matches( const std::string& uniq_node_name ) const;

    inline bool
    empty()
    {
        return filter_set.empty();
    }

private:
    std::set<std::string> filter_set;
};
}

#endif
