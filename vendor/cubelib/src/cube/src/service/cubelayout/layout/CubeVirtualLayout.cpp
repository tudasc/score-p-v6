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
 * \file CubeVirtualLayout.cpp
 * \brief Implements common parts of the interface for embedded layout of CUBE report.
 */

#include "config.h"

#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeMetric.h"
#include "CubeError.h"
#include "CubeVirtualLayout.h"

using namespace cube;
using namespace std;

std::string
VirtualLayout::getPathToAnchor()
{
//     throw NoFileError("");
    return "_placeholder_anchor_";
}
std::string
VirtualLayout::getPathToData()
{
//     throw NoFileError("");
    return "_placeholder_path_";
}

std::string
VirtualLayout::getPathToMetricData( cube::Metric*  )
{
//     throw NoFileError("");
    return "_placeholder_path_metric_data_";
}

std::string
VirtualLayout::getPathToMetricIndex( cube::Metric*  )
{
//     throw NoFileError("");
    return "_placeholder_path_metric_index_";
}

std::string
VirtualLayout::getAnchorName()
{
//     throw NoFileError("");
    return "anchor" + getOwnAnchorExtension();
}

std::string
VirtualLayout::getMetricDataName( cube::Metric*  )
{
//     throw NoFileError("");
    return "_placeholder_path_metric_dataname_";
}

std::string
VirtualLayout::getMetricIndexName( cube::Metric*  )
{
//     throw NoFileError("");
    return "_placeholder_path_metric_indexname_";
}
