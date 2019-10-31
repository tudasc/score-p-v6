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
 * \file CubeNOPTrafo.h
 * \brief Defines a nop-transformation, which DO NOT changes the value.
 */

#ifndef __NOP_TRAFO_H
#define __NOP_TRAFO_H

#include "CubeSingleValueTrafo.h"

namespace cube
{
/**
 * In the case of the same endianess, one doesn't have to change the byte sequence.
 * One applyes the nop-transformation, which is just "return".
 */
class NOPTrafo : public SingleValueTrafo
{
public:
    virtual
    ~NOPTrafo()
    {
    };
    virtual char*
    trafo( char*    stream,
           unsigned n );
};
}
#endif
