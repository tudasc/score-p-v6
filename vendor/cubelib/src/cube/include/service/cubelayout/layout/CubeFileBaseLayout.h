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
 * \file CubeFileBaseLayout.h
 * \brief Provides an abstract interface for any possible realization of the CUBE report layout. It provides names for the files in the CUBE report layout.
 */
#ifndef __FILE_BASE_LAYOUT_H
#define __FILE_BASE_LAYOUT_H


#include <inttypes.h>
#include <stdint.h>
#include <map>
#include <string>
#include <vector>
#include <iostream>

// #include "CubeMetric.h"

namespace cube
{
class Metric;

class FileBaseLayout
{
protected:
    std::string reportname;



    virtual std::string
    getPathToAnchor();
    virtual std::string
    getPathToData();
    virtual std::string
    getPathToMetricData( cube::Metric* met );
    virtual std::string
    getPathToMetricIndex( cube::Metric* met );

    virtual std::string
    getAnchorName();
    virtual std::string
    getMetricDataName( cube::Metric* met );
    virtual std::string
    getMetricIndexName( cube::Metric* met );


public:
    FileBaseLayout( const std::string& name ) : reportname( name )
    {
    };
    virtual
    ~FileBaseLayout()
    {
    }

    std::string
    getFullPathToAnchor();
    std::string
    getFullPathToData( const std::string );
    std::string
    getFullPathToMetricData( cube::Metric* );
    std::string
    getFullPathToMetricIndex( cube::Metric* );

    static std::string
    getAnchorExtension()
    {
        return ".cubex";
    }
    static std::string
    getDataExtension()
    {
        return ".data";
    }
    static std::string
    getIndexExtension()
    {
        return ".index";
    }
};
}

#endif
