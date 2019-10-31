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
 * \file CubeMemoryRowsSupplier.h
 * \brief  Provides a row supplier, allocating only in memory.
 */

#ifndef CUBE_MEMORY_ROWS_SUPPLIER_H
#define CUBE_MEMORY_ROWS_SUPPLIER_H


#include "CubeTypes.h"

namespace cube
{
class MemoryRowsSupplier : public RowsSupplier
{
public:

    MemoryRowsSupplier() : RowsSupplier()
    {
        endianness = new NOPTrafo();
    };                                        // / used only to invoke late "probe"... does not creat fully initialized instance

    MemoryRowsSupplier( uint64_t rs ) : RowsSupplier( rs )
    {
        endianness = new NOPTrafo();
    };

    ~MemoryRowsSupplier()
    {
        delete endianness;
    }


    virtual row_t
    provideRow( cnode_id_t row_id, bool for_writing = false )
    {
        ( void )for_writing;
        ( void )row_id;
        return new char[ row_size ]();
        ;
    };

    virtual void
    dropRow( row_t row, cnode_id_t row_id )
    {
        ( void )row_id;
        delete[] row;
    };

    static
    bool
    probe()
    {
        return true;
    }
};
}

#endif
