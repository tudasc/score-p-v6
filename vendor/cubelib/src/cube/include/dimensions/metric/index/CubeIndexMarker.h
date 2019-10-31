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
 * \file CubeIndexMarker.h
 * \brief Provides a static merthod to check the marker of the index at the beginning of file. ( Further extension might allow checl of crc sum, or another correctness checks)
 */


#ifndef __INDEX_MARKER_H
#define __INDEX_MARKER_H

#include <string>
#include <fstream>



namespace cube
{
/**
 * Defines an interface for all kinds of Indecies, used in Cube.
 */
class IndexMarker
{
private:
    static const std::string marker;
public:

    static bool
    checkMarker( std::fstream& in );
    static bool
    checkMarker( FILE* in );
    static bool
    writeMarker( std::fstream& in );
    static bool
    writeMarker( FILE* in );

    static size_t
    markerSize()
    {
        return marker.size();
    }
};
}
#endif
