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
 * \file CubeSwapRowsSupplier.h
 * \brief  Provides a row supplier, allocating in the file for swapping ability.
 */

#ifndef CUBE_SWAP_ROWS_SUPPLIER_H
#define CUBE_SWAP_ROWS_SUPPLIER_H

#include "CubeTypes.h"
#include <map>
#include <string>
#include "CubeRowsSupplier.h"


namespace cube
{
/**
 * This class provides a swapping functionality for target file "XXX.data". It creates a file "XXX.data.swapfile" in same directory and uses it for intermediate storing of the data.
 */

class SwapRowsSupplier : public RowsSupplier
{
protected:
    std::string                      swapfile;                  // /< Stores a name of the swap file. It uses same directory, like the target file. just adds ".swapfile"
    std::map<cnode_id_t, position_t> positions;                 // /< Stores a mapping cnode_id -> into position (in rows as a unit) in the swap file
    position_t                       next_new_row_position;     // /< Marks a position of the last saved row
    FILE*                            swpfd;                     // /< File descriptof of the opened swap file
    position_t                       position;                  // /< Marks an actual position of writing in swap file. If one has to write sequentially, it doesn't perform fseek (with underlying flush)

public:

    SwapRowsSupplier() : RowsSupplier()
    {
    };                                       // / used only to invoke lated "probe"... does not creat fully initialized instance

    SwapRowsSupplier( std::string file,
                      uint64_t    rs );

    virtual
    ~SwapRowsSupplier();


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
