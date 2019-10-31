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
 * \file CubeFileEmddedLayout.h
 * \brief It provides names for the files in the CUBE report hybrid layout, with all file in a current directory: anchor.cubex, [metric_id].data, [metric_id].index.
 */
#ifndef __FILE_EMBEDDED_LAYOUT_H
#define __FILE_EMBEDDED_LAYOUT_H


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
class FileEmbeddedLayout : public FileBaseLayout
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
    FileEmbeddedLayout( const std::string& name ) : FileBaseLayout( name )
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
