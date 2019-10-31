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
 * \file CubeSwapBytesTrafo.h
 * \brief Defines a transformation, which reversec the sequence of the bytes.
 */

#ifndef __SWAP_BYTES_TRAFO_H
#define __SWAP_BYTES_TRAFO_H


#include "CubeSingleValueTrafo.h"

namespace cube
{
/**
 * In the case of the different endianess, one has to change the byte sequence.
 * One applyes the transformation, which swaps the postitions of the bytes.
 */
class SwapBytesTrafo : public SingleValueTrafo
{
public:
    virtual
    ~SwapBytesTrafo()
    {
    };

    virtual char*
    trafo( char*    stream,
           unsigned n );
};
}
#endif
