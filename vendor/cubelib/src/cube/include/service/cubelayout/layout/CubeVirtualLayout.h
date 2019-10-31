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
 * \file CubeVirtualLayout.h
 * \brief It provides npo names, just hrows an exception
 */
#ifndef __VIRTUAL_LAYOUT_H
#define __VIRTUAL_LAYOUT_H


#include <inttypes.h>
#include <stdint.h>
#include <map>
#include <string>
#include <vector>
#include <iostream>

#include "CubeMetric.h"

#include "CubeFileBaseLayout.h"

namespace cube
{
class VirtualLayout : public FileBaseLayout
{
protected:

    virtual std::string
    getPathToAnchor();
    virtual std::string
    getPathToData();
    virtual std::string
    getPathToMetricData( cube::Metric* );
    virtual std::string
    getPathToMetricIndex( cube::Metric* );

    virtual std::string
    getAnchorName();
    virtual std::string
    getMetricDataName( cube::Metric* );
    virtual std::string
    getMetricIndexName( cube::Metric* );


public:
    VirtualLayout(  ) : FileBaseLayout( "" )
    {
    };
    static std::string
    getOwnAnchorExtension()
    {
        return ".xml";
    }
};
};

#endif
