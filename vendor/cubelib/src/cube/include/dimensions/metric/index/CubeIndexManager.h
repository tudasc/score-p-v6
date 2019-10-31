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
 * \file IndexManager.h
 * \brief Provides a interface for AdvancedMatrix to get access to right Index.
 */

#ifndef __INDEX_MANAGER_H
#define __INDEX_MANAGER_H

#include "CubeTypes.h"

namespace cube
{
/**
 *   It hides the information about right layout of the .index file from the AdwvancedMatrix. Its task is to deliver to the AdvancedMatric correct endianess transformation (it is needed for Data object),
 *   Index (to have an access to the  elements in Data.) and the exemplar of Value.
 *
 */
class IndexManager
{
private:
    // / Points on header, which contains information about endianess, data dype, index format
    IndexHeader* header;
    // / Saves here a pointer on endianess transformation. To have faster access.
    SingleValueTrafo* trafo;
//     /// Saves here an exemplar of used Value.
//     Value*            value;
    // / Saves here an index object.
    Index* index;
    // / Saves the file, which contains as well as header as index data.
    fileplace_t indexfilename;

    // / Layout of the data.
    cnodes_number_t n_cnodes;
    cnodes_number_t n_threads;

    // / It "readonly" modus (existing index) or not.
    bool read_only;


protected:

//             void              readHeader(istream&);


public:
    // / during creation it reads given file. If file exists, it creats Header and let read info in header. Then it lets index to read needed data. This separation is needed, if the layout of index file changes.
    IndexManager( fileplace_t,
                  cnodes_number_t,
                  threads_number_t
                  );
    // / creates new Header with given information. Marks "not readonly " state.
    IndexManager( fileplace_t,
                  cnodes_number_t,
                  threads_number_t,
                  IndexFormat );

    // / If "readonly" -> do nothing. If not readonly, it creates index file, saves Header and subsequentelly Index data
    ~IndexManager();
    void
    write();
    Index*
    getIndex();                                    //  returns a index object from the file

    SingleValueTrafo*
    getTrafo();

    threads_number_t
    getNumberOfThreads();

    cnodes_number_t
    getNumberOfCNodes();
};
}
#endif
