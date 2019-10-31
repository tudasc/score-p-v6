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



#ifndef CCNODE_H_GUARD_
#define CCNODE_H_GUARD_

/**
 * @file    CCnode.h
 * @brief   Contains a class which can cache computed, aggregated values.
 */

#include "CubeCnode.h"
#include "Cacheable.h"

namespace cube
{
/**
 * @class   CCnode
 * @brief   This class extends the Cnode class by providing methods to cache
 *          computed, aggregated values.
 *
 * This class extends the Cnode class by providing methods to cache computed,
 * aggregated values. A cacheable item is called a MetricDescriptor. The
 * CCnode class is also able to maintain multiple caches for different cubes.
 * There are two ways of accessing the separate caches, either by an additional
 * integer id or by providing a pointer to a certain CubeMapping
 * (see algebra.h). The class internally maps the mappings to integer ids.
 * For the basic methods store, has, get, there are two flavors, one taking an
 * integer to specify the cache and one taking a CubeMapping.
 */
class CCnode : public Cnode, public Cacheable
{
public:
    /**
     * @fn CCnode(Region* callee, const string& mod, int line,
     *            Cnode* parent, uint32_t id, int cache_size)
     *
     * Creates a new CCnode, all arguments except for the cache_size correspond
     * to the according parameters for the construction of Cnode. cache_size
     * is directly passed to the constructor of Cacheable.
     */
    CCnode( Region*            callee,
            const std::string& mod,
            int                line,
            Cnode*             parent,
            uint32_t           id,
            int                cache_size );

    /**
     * @fn unsigned int size() const
     *
     * Returns the number of nodes that descend from this node.
     */
    unsigned int
    size() const;
};
}

#endif
