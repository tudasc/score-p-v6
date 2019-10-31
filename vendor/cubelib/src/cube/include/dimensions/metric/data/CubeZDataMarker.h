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
 * \file CubeZDataMarker.h
 * \brief Provides a method to check the marker of the compressed data  at the beginning of file. ( Further extension might allow checl of crc sum, or another correctness checks)
 */


#ifndef __Z_DATA_MARKER_H
#define __Z_DATA_MARKER_H

#include "CubeDataMarker.h"



namespace cube
{
/**
 * Defines an interface for all kinds of Indecies, used in Cube.
 */
class ZDataMarker : public DataMarker
{
public:

    ZDataMarker() : DataMarker()
    {
        marker = "ZCUBEX.DATA";
    };

    virtual
    ~ZDataMarker()
    {
    };
};
}
#endif
