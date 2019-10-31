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



#ifndef CREGION_H_GUARD_
#define CREGION_H_GUARD_

#include "CubeRegion.h"
#include "Cacheable.h"

namespace cube
{
class MetricDescriptor;

class CRegion : public Region, public Cacheable
{
public:
    CRegion( const std::string& name,
             const std::string& mangled_name,
             const std::string& paradigm,
             const std::string& role,
             int                begln,
             int                endln,
             const std::string& url,
             const std::string& descr,
             const std::string& mod,
             uint32_t           id,
             int                cache_size );
};
}

#endif
