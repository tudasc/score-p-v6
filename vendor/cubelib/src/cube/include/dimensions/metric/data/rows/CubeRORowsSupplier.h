/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2017                                                **
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
 * \file CubeRORowsSupplier.h
 * \brief  Provides a read-only row supplier, which does read current cube data layout.
 */

#ifndef CUBE_RO_ROWS_SUPPLIER_H
#define CUBE_RO_ROWS_SUPPLIER_H

#include "CubeTypes.h"
#include "CubeDataMarker.h"
#include "CubeRowsSupplier.h"


namespace cube
{
/**
 * This class delivers rows, stored in the couple of files "XXX.index" ans "XXX.data", it supports both, dense and sparse indexes. Read-only ability. (used for reading existing cube)
 */

class RORowsSupplier : public RowsSupplier
{
protected:

    DataMarker* dataMarker;                    // /< Holds an object, which checks the integrity of the data. Currently only magic number.

    fileplace_t   _dataplace;                  // /< Stores the position of the data in some file and its size
    fileplace_t   _indexplace;                 // /< Stores position of the index and its size
    IndexManager* index_manager;               // /< Provides index  and data
    Index*        index;                       // /< Created index (get removed by index manager)
//     Value*        value;                       ///< Holds an exemplar of value to be able to have an access to the data.
    FILE*      datafile;
    position_t position;                       // /< Marks an actual position of writing in swap file. If one has to write sequentially, it doesn't perform fseek (with underlying flush)
    uint64_t   element_size;                   // /< Stores size of a single elemnt of a row  in bytes


// ----- methods ----------


    virtual void
    initIndex( uint64_t, uint64_t );              // /< Reads index file

    virtual void
    initData();                                 // /< Reads data.



public:

    RORowsSupplier( DataMarker* _dm = new DataMarker() ) : RowsSupplier(), dataMarker( _dm )
    {
    };                                                                                          // / used only to invoke  "probe"... does not creat fully initialized instance


    RORowsSupplier(  fileplace_t DataPlace,
                     fileplace_t IndexPlace,
                     uint64_t    nt,
                     uint64_t    es,
                     DataMarker* _dm = new DataMarker() );

    virtual
    ~RORowsSupplier();


    virtual row_t
    provideRow( cnode_id_t row_id,
                bool       for_writing = false );

    virtual void
    dropRow( row_t      row,
             cnode_id_t row_id );


    static bool
    probe( fileplace_t DataPlace,
           fileplace_t IndexPlace );
};
}

#endif
