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



#include "config.h"
#include "CRegion.h"

#include "CubeRegion.h"

using namespace cube;
using namespace std;

CRegion::CRegion( const string& name,
                  const string& mangled_name,
                  const string& paradigm,
                  const string& role,
                  int           begln,
                  int           endln,
                  const string& url,
                  const string& descr,
                  const string& mod,
                  uint32_t      id,
                  int           cache_size )
    : Region( name, mangled_name, paradigm, role, begln, endln, url, descr, mod, id ), Cacheable( cache_size )
{
}
