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
 * \file CubeFileFinder.h
 * \brief It connects a selected CUBE report layout and a container (if some ) and provides a single standard file name translation.
 */
#ifndef __FILE_FINDER_H
#define __FILE_FINDER_H


#include <string>
#include <vector>

#include "CubeTypes.h"


namespace cube
{



class FileFinder
{
protected:
    SimpleReader*   reader;                     ///< TarReader is inherited from SimpelReader. Therefore here SimpleReader
    FileBaseLayout* layout;                     ///< All layouts are inherited from BaseLayout
    bool            creating_mode;              ///< Marks, if the action in destructor is needed (for example to create Tar);

public:
    FileFinder( SimpleReader*   sr,
                FileBaseLayout* fbl,
                bool            mode = false ) : reader( sr ), layout( fbl ), creating_mode( mode )
    {
    };
    ~FileFinder();

    void
    finalizeFiles( std::string );                       ///< In the case of tar, creates a tar archive.
    fileplace_t
    getAnchor();                                        ///< Returns a file and place, where the start of the anchor file is expected
    fileplace_t
    getMetricData( cube::Metric* );                     ///< Returns a file and place, where the data of given metric is expected
    fileplace_t
    getMetricIndex( cube::Metric* );                    ///< Returns a file and place, where the index file for the data  of given metric is expected
    fileplace_t
    getMiscData( std::string );                         ///< Returns a file and place, where the mesc data is or should be stored

    std::vector<std::string>
    getAllData();                                 ///< Returns a list of files, stored inside of cube report. In the case of hybrid or other than "tar" container -> returns empty list
    void
    setFinalName( std::string );                  ///< Sets the final name for the cube report.
};
}

#endif
