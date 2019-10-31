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
 * \file CubeROZRowsSupplier.h
 * \brief  Provides a read-only row supplier, which does read current cube data layout.
 */

#ifndef CUBE_RO_Z_ROWS_SUPPLIER_H
#define CUBE_RO_Z_ROWS_SUPPLIER_H
#include <map>

#include "CubeTypes.h"
#include "CubeZDataMarker.h"
#include "CubeRORowsSupplier.h"


namespace cube
{
/**
 * This class delivers rows, stored in the couple of files "XXX.index" ans "XXX.data", it supports both, dense and sparse indexes. Read-only ability. (used for reading existing cube) Data is compressed.
 */

class ROZRowsSupplier : public RORowsSupplier
{
protected:
    std::map<uint64_t, SubIndexInternalElement>* sub_index;     // /< Holds a index of the compressed data.
    uint64_t                                     subindex_size; // /< Holds a size of the subindex. With another words, number of saved rows.
    void
    initSubIndex();

    void
    __temp_print_row( row_t _row ); // / used for debug proposes.


    void
    __temp_print_sub_index(); // / used for debug

public:

    ROZRowsSupplier( DataMarker* _dm = new ZDataMarker() ) : RORowsSupplier( _dm )
    {
    };                                                                                // / used only to invoke  "probe"... does not creat fully initialized instance

    ROZRowsSupplier(  fileplace_t DataPlace,
                      fileplace_t IndexPlace,
                      uint64_t    nt,
                      uint64_t    es,
                      DataMarker* _dm = new ZDataMarker() );

    virtual
    ~ROZRowsSupplier();


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
