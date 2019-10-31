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
 * \file CubeSingleValueTrafo.h
 * \brief Represents a general transformation of a single value.
 */

#ifndef __SINGLE_VALUE_TRAFO_H
#define __SINGLE_VALUE_TRAFO_H

namespace cube
{
/**
 * Abstract class, which defines an interface of all single valued transformations. It is a
 * base for the endianess transformation.
 */
class SingleValueTrafo
{
public:
    virtual
    ~SingleValueTrafo()
    {
    };
    virtual char*
    trafo( char*,
           unsigned ) = 0;
};
}
#endif
