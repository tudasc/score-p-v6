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
 * \file CubeLayoutDetector.h
 * \brief Detects, according to the given name of the CUE repor, which layout does it have and deivers corresponding FileFinder, with proper layour and container
 */
#ifndef __LAYOUT_DETECTOR_H
#define __LAYOUT_DETECTOR_H


#include <inttypes.h>
#include <stdint.h>
#include <map>
#include <string>
#include <vector>
#include <iostream>

#include "CubeFileFinder.h"

namespace cube
{
class LayoutDetector
{
public:

    static FileFinder*
    getFileFinder( const std::string& cubename );
    static FileFinder*
    getDefaultFileFinderForWriting();
    static FileFinder*
    getTmpFileFinder();
    static FileFinder*
    getVirtualFileFinder();
     
};
}

#endif
