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
 * \file CubeIDdeliverer.h
 * \brief Delivers incrementaly a sequence of id's.
 */
#ifndef CUBE_ID_DELIVERER_H
#define CUBE_ID_DELIVERER_H

/*
   *----------------------------------------------------------------------------
 *
 * class Metric
 *
 ***************----------------------------------------------------------------------------
 */

namespace cube
{
/**
 * IDdeliverer is used by IDassgner to assign id for the treelike objects.
 * Enumerator delivers a row of IdentObject's.
 */
class IDdeliverer
{
private:
    uint32_t current_id;
public:
    IDdeliverer()
    {
        reset();
    }
    virtual
    ~IDdeliverer()
    {
    };
    virtual uint32_t
    get_next_id()
    {
        return current_id++;
    };

    virtual void
    reset()
    {
        current_id = 0;
    };
};
}
#endif
