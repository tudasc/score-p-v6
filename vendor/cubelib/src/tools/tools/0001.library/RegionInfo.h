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
 * \file RegionInfo.h
 * \brief Extends a general class InfoObj to get ability to carry a cube.
 */

#ifndef CUBE_REGIONINFO
#define CUBE_REGIONINFO

#include "enums.h"
#include "InfoObj.h"

namespace cube

{
class Cube;

class CRegionInfo : public InfoObj
{
private:
    const Cube* m_cube;

public:
    CRegionInfo( const Cube* );
};
}
#endif
