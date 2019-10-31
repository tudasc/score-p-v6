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
 * \file CubeDataMarker.h
 * \brief Provides a static merthod to check the marker of the data  at the beginning of file. ( Further extension might allow checl of crc sum, or another correctness checks)
 */


#ifndef __DATA_MARKER_H
#define __DATA_MARKER_H

#include <string>
#include <fstream>




namespace cube
{
/**
 *
 */
class DataMarker
{
protected:
    std::string marker;
public:

    DataMarker() : marker( "CUBEX.DATA" )
    {
    };
    virtual
    ~DataMarker()
    {
    };

    virtual bool
    checkMarker( std::fstream& in );
    virtual bool
    checkMarker( FILE* in );

    virtual bool
    writeMarker( std::fstream& in );
    virtual bool
    writeMarker( FILE* in );


    size_t
    markerSize()
    {
        return marker.size();
    }
};
}
#endif
