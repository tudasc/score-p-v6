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
 * \file CubeFileBaseLayout.cpp
 * \brief Implements common parts of the interface, providing file layout for CUBE report.
 */

#include "config.h"

#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeMetric.h"
#include "CubeFileBaseLayout.h"

using namespace cube;
using namespace std;



std::string
FileBaseLayout::getFullPathToAnchor()
{
    return getPathToAnchor() +  getAnchorName();
}

std::string
FileBaseLayout::getFullPathToData( std::string dataname )
{
    return getPathToData() + dataname;
}


std::string
FileBaseLayout::getFullPathToMetricData( cube::Metric* met )
{
    return getPathToMetricData( met ) +  getMetricDataName( met );
}

std::string
FileBaseLayout::getFullPathToMetricIndex( cube::Metric* met )
{
    return getPathToMetricIndex( met ) +  getMetricIndexName( met );
}



std::string
FileBaseLayout::getPathToAnchor()
{
    return "";
};

std::string
FileBaseLayout::getPathToData()
{
    return "";
};


std::string
FileBaseLayout::getPathToMetricData( cube::Metric* )
{
    return "";
};

std::string
FileBaseLayout::getPathToMetricIndex( cube::Metric* )
{
    return "";
};

std::string
FileBaseLayout::getAnchorName()
{
    return "anchor" + getAnchorExtension();
};

std::string
FileBaseLayout::getMetricDataName( cube::Metric* met )
{
    return "Metric" + met->get_uniq_name() + getDataExtension();
};

std::string
FileBaseLayout::getMetricIndexName( cube::Metric* met )
{
    return "Metric" + met->get_uniq_name() + getIndexExtension();
};
