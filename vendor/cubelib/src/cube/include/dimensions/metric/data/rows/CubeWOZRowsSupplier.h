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
 * \file CubeWOZRowsSupplier.h
 * \brief  Provides a row supplier, which writes rows on disk. It stores them in to sap file, call finalize() packs them into compressed cube4 format.
 */

#ifndef CUBE_WO_Z_ROWS_SUPPLIER_H
#define CUBE_WO_Z_ROWS_SUPPLIER_H


#include "CubeTypes.h"
#include "CubeSwapRowsSupplier.h"
#include "CubeZDataMarker.h"


namespace cube
{
/**
 * This class delivers rows, stored in the couple of files "XXX.index" ans "XXX.data", it supports both, dense and sparse indexes. Read-only ability. (used for reading existing cube) Data is compressed.
 */

class WOZRowsSupplier : public SwapRowsSupplier
{
private:

    void
    __temp_print_row( row_t _row ); // / used for debug proposes.


    void
    __temp_print_sub_index(); // / used for debug

    void
    finalizeData();                  // / processed the compression of the data

protected:

    DataMarker* dataMarker;                    // /< Holds an object, which checks the integrity of the data. Currently only magic number.

    fileplace_t   _dataplace;                  // /< Stores the position of the data in some file and its size
    fileplace_t   _indexplace;                 // /< Stores position of the index and its size
    IndexManager* index_manager;               // /< Provides index  and data
    Index*        index;                       // /< Created index (get removed by index manager)
    uint64_t      element_size;                // /< Stores a size of an element of the row in bytes
    FILE*         datafile;


    SubIndexElement* sub_index;                                 // /< Holds a index of the compressed data.
    uint64_t         subindex_size;                             // /< Holds a size of the subindex. With another words, number of saved rows.
    std::string      zfile;                                     // /< Holds a filename, where the




public:

    WOZRowsSupplier();


    WOZRowsSupplier(  fileplace_t DataPlace,
                      fileplace_t IndexPlace,
                      uint64_t    nt,
                      uint64_t    es,
                      DataMarker* _dm = new ZDataMarker() );

    virtual
    ~WOZRowsSupplier();



    virtual void
    initIndex( uint64_t, uint64_t );              // /< Reads index file

    virtual void
    initData();                                 // /< Creates  data. file

    virtual void
    dropRow( row_t      row,
             cnode_id_t row_id );


    virtual void
    finalize();


    static bool
    probe( fileplace_t DataPlace,
           fileplace_t IndexPlace );
};
}

#endif
