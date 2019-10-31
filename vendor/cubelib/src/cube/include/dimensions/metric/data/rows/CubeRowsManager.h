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
 * \file CubeRowsManager.h
 * \brief  Provides a consistent state of map<int, char*> rows[]. It performs loading/unloading, caching, swapping and so on.
 */

#ifndef CUBE_ROWS_MANAGER_H
#define CUBE_ROWS_MANAGER_H

#include "CubeTypes.h"

namespace cube
{
class RowsManager
{
private:

    // flag to not to drop any rows (for cube3 compatibility)
    bool no_drop;


    // /Data container, storing the data rows ,
    rows_t* rows;

    // / a pointer got from RowWiseMatrix, signalizing that some row is "absent" row and shouldn't be deleted
    row_t no_row_pointer;

    // / Strategy to drop/load rows
    BasicStrategy* strategy;

    // / Pointer on the row interface
    Row* row;

    // / Rows Supplier: acts like memory manager, it delivers a row either from memory or from swap file.
    RowsSupplier* row_supplier;



    RowsSupplier*
        selectRowsSupplier( fileplace_t DataPlace,
                            fileplace_t IndexPlace, uint64_t, uint64_t );

    RowsSupplier*
        selectRowsSupplier( uint64_t, uint64_t );

public:

    RowsManager( fileplace_t DataPlace,
                 fileplace_t IndexPlace,
                 rows_t*,
                 Row*,
                 BasicStrategy*,
                 row_t       no_row_pointer = NULL
                 );                                                                                                                       // name of file
    virtual
    ~RowsManager();


    void
    setStrategy( BasicStrategy* _str );

    void
    provideRow( cnode_id_t&,
                bool for_writing = false );

    void
    dropAllRows();

    void
    dropRow( cnode_id_t& );

    void
    finalize();                         // /< initiates writing on disk
};
}

#endif
