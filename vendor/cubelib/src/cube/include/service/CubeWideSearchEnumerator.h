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
 * \file CubeWideSearchEnumerator.h
 * \brief Enumerates objects in the tree. Delivers a row of objects in the order, they might(not neccesarry) get an id.
 */
#ifndef CUBE_WIDE_SEARCH_ENUMERATOR_H
#define CUBE_WIDE_SEARCH_ENUMERATOR_H

#include "CubeObjectsEnumerator.h"


namespace cube
{
/** @class WideSearchEnumerator
 *  @brief Enumerate elements of a tree structure in a breadth-first manner.
 *
 *  WideSearchEnumerator delivers a row of IdentObject's, started with \param root according the "wide search" prescription; Used in InclusiveMetric.
 */
class WideSearchEnumerator : public ObjectsEnumerator
{
protected:
    virtual row_of_objects_t*
    traverse( row_of_objects_t* row,
              cube::Vertex*     root ); ///< Runs over the tree like "wide search" and assigns IDs
};
}
#endif
