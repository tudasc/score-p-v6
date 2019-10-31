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
 * \file CubeRowsSupplier.h
 * \brief  Provides an abstract interface for all rows suppliers.
 */

#ifndef CUBE_ROWS_SUPPLIER_H
#define CUBE_ROWS_SUPPLIER_H

#ifndef IO_BUFFERSIZE
#define IO_BUFFERSIZE 1048576
#endif

#include "CubeTypes.h"


namespace cube
{
class RowsSupplier
{
protected:
    uint64_t row_size;
    SingleValueTrafo*
        endianness;                             // /<  Holds the endianess correction.

    bool _dummy_creation;
    bool _finalized;
public:

    RowsSupplier()
    {
        _dummy_creation = true;
        _finalized      = false;
    };                                           // / used only to invoke late "probe"... does not creat fully initialized instance

    RowsSupplier( uint64_t rs ) : row_size( rs )
    {
        _dummy_creation = false;
        _finalized      = false;
    };

    virtual
    ~RowsSupplier()
    {
    };

    virtual row_t
        provideRow( cnode_id_t, bool for_writing = false ) = 0;

    virtual void
        dropRow( row_t, cnode_id_t ) = 0;

    virtual SingleValueTrafo*
    getEndianness()
    {
        return endianness;
    };


    virtual void
    finalize()
    {
    };              // /< gets invoked in destructor, to performe final format transformation if needed. Standard realizasion - nop operation. Inj WOZ case -> compressing data.


    // / Gets invoked by RowsManager to test, if that or another wors suplier can provide rows. Used in the decision if existing cube or new one, compressed or not.
    static
    bool
    probe( fileplace_t DataPlace,
           fileplace_t IndexPlace )
    {
        DataPlace  = DataPlace;  // just to avoind warning of unused (here) argument
        IndexPlace = IndexPlace; // just to avoind warning of unused (here) argument
        return true;
    }
};
}

#endif
