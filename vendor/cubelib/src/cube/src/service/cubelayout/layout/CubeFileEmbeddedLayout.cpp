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
 * \file CubeFileEmbeddedLayout.cpp
 * \brief Implements common parts of the interface for embedded layout of CUBE report.
 */

#include "config.h"
#include <sstream>

#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeMetric.h"
#include "CubeFileEmbeddedLayout.h"

using namespace cube;
using namespace std;

std::string
FileEmbeddedLayout::getPathToAnchor()
{
    return "";
}
std::string
FileEmbeddedLayout::getPathToData()
{
    return "";
}

std::string
FileEmbeddedLayout::getPathToMetricData( cube::Metric* )
{
    return "";
}

std::string
FileEmbeddedLayout::getPathToMetricIndex( cube::Metric* )
{
    return "";
}

std::string
FileEmbeddedLayout::getAnchorName()
{
    return "anchor" + getOwnAnchorExtension();
}

std::string
FileEmbeddedLayout::getMetricDataName( cube::Metric* met )
{
    std::ostringstream stream;
    if ( met->isGhost() )
    {
        stream << "ghost_";
    }
    stream << met->get_filed_id();

    return stream.str() + getDataExtension();
}

std::string
FileEmbeddedLayout::getMetricIndexName( cube::Metric* met )
{
    std::ostringstream stream;
    if ( met->isGhost() )
    {
        stream << "ghost_";
    }
    stream << met->get_filed_id();

    return stream.str() + getIndexExtension();
}
