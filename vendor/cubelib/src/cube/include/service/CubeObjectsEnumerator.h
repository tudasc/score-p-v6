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


#ifndef CUBE_OBJECTS_ENUMERATOR_H
#define CUBE_OBJECTS_ENUMERATOR_H

/**
 * \file CubeObjectsEnumerator.h
 * \brief Enumerates objects in the tree. Delivers a row of objects in the order, they might (not necessarily) get an id.
 */

#include "CubeTypes.h"


namespace cube
{
/** @class ObjectsEnumerator
 *  @brief Enumerate elements of a tree structure.
 *
 * ID assigned is used by cube(metric) to assign id for the tree-like objects.
 * Enumerator delivers a row of IdentObject's, started with \param root.
 */
class ObjectsEnumerator
{
public:

    virtual
    ~ObjectsEnumerator()
    {
    }

    virtual row_of_objects_t*
    get_objects_to_enumerate( cube::Vertex*     root,
                              row_of_objects_t* row = 0 );

protected:

//     std::map<unsigned, signed int> calltree_strides;           ///< (ABSOLETE ... ) Optimisation trick. Saves the range of the children, which one takes to calculate Inc/excl Value for every element in the tree as a map ID -> stride.

    virtual row_of_objects_t*
    traverse( row_of_objects_t* row,
              cube::Vertex*     root ); ///< Every type of enumerator defines its way to run over the objects and to assign its id. Might be recursive call.
};
}

#endif
