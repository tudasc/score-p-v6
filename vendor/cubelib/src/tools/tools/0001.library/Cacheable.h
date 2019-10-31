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



#ifndef CACHEABLE_H_GUARD_
#define CACHEABLE_H_GUARD_

/**
 * @file    Cacheable.h
 * @brief   Contains a base class for items that want to store CnodeMetric
 *          values in a cache.
 */

#include <map>

#include "algebra4.h"

namespace cube
{
class CnodeMetric;

/**
 * @class   Cacheable
 * @brief   Base class for items that need to store certain CnodeMetric values.
 *
 * This class is extended by CCnode and CRegion through multiple inheritance to
 * enable these classes to cache metric values. At construction time, you need
 * to know how many values you would like to store per CnodeMetric. For the
 * testing library, this basically corresponds to the number of cube files you
 * process.
 */

class Cacheable
{
public:
    /**
     * @fn Cacheable(int cache_size)
     *
     * Creates a new Cacheable instance with a certain cache size. The cache
     * size is the number of values that can be stored per CnodeMetric. In the
     * context of the testing library, this usually corresponds to the number
     * of cube files that are processed.
     *
     * @param cache_size Capacity of the cache for each CnodeMetric.
     */
    Cacheable( int cache_size = 1 );

    /**
     * @fn void store(CnodeMetric* metric, double value,
     *                CubeMapping* mapping)
     *
     * Stores the value for the CnodeMetric metric in the cache
     * referred to by either the CubeMapping mapping or the integer cube_id.
     *
     * @param metric A pointer to the CnodeMetric that contains all
     *    the details about how the value got computed.
     * @param value The double value.
     * @param mapping The mapping which describes to which cache we refer to.
     */
    void
    store( CnodeMetric* metric,
           double       value,
           CubeMapping* mapping = NULL );

    /**
     * @fn bool has(CnodeMetric* metric, CubeMapping* mapping,
     *              double* value) const
     *
     * Returns whether a value for a certain CnodeMetric is stored within
     * a certain cache. Optionally returns that value.
     *
     * @param metric A pointer to the CnodeMetric that is looked up
     *    in cache.
     * @param mapping A pointer to the mapping, the cache is identified by.
     * @param value A pointer to a double. The value that is obtained from
     *    the cache is written to that location. If the cache does not contain
     *    an appropiate value, the location, value refers to, is unchanged.
     */
    bool
    has( CnodeMetric* metric,
         CubeMapping* mapping = NULL,
         double*      value = NULL );

    /**
     * @fn double get(CnodeMetric* metric,
     *      CubeMapping* mapping) const
     *
     * Returns the cached value for a certain CnodeMetric and a certain
     * cache. Throws an exception in case no such value has been cached.
     *
     * @param metric A pointer to the CnodeMetric that is looked up in
     *    cache.
     * @param mapping A pointer to the mapping, the specific cache is
     *    identified by.
     */
    double
    get( CnodeMetric* metric,
         CubeMapping* mapping = NULL );

protected:
    unsigned int
    get_cache_size();

    /**
     * @fn std::vector<double> const& get_all(
     *            const CnodeMetric* metric) const
     *
     * Returns a vector containing the values of all caches for a specific
     * CnodeMetric.
     *
     * @param metric Pointer to the CnodeMetric.
     */
    std::vector<double> const&
    get_all(
        CnodeMetric* metric );

private:
    /**
     * @fn void store(CnodeMetric* metric, double value,
     *                int cube_id)
     *
     * Stores the value for the CnodeMetric metric in the cache
     * referred to by either the CubeMapping mapping or the integer cube_id.
     *
     * @param metric A pointer to the CnodeMetric that contains all
     *    the details about how the value got computed.
     * @param value The double value.
     * @param cube_id Id of the cache.
     */
    void
    store( CnodeMetric* metric,
           double       value,
           int          cube_id = 0 );


    /**
     * @fn bool has(CnodeMetric* metric, int cube_id,
     *              double* value) const
     *
     * Returns whether a value for a certain CnodeMetric is stored within
     * a certain cache. Optionally returns that value.
     *
     * @param metric A pointer to the CnodeMetric that is looked up
     *    in cache.
     * @param cube_id The id of the cache.
     * @param value A pointer to a double. The value that is obtained from
     *    the cache is written to that location. If the cache does not contain
     *    an appropiate value, the location, value refers to, is unchanged.
     */
    bool
    has( CnodeMetric* metric,
         int          cube_id = 0,
         double*      value = NULL );

    /**
     * @fn double get(CnodeMetric* metric, int cube_id) const
     *
     * Returns the cached value for a certain CnodeMetric and a certain
     * cache. Throws an exception in case no such value has been cached.
     *
     * @param metric A pointer to the CnodeMetric that is looked up in
     *    cache.
     * @param cube_id The id of the cache.
     */
    double
    get( CnodeMetric* metric,
         int          cube_id = 0 );

    /**
     * @fn int get_mapping_id(CubeMapping* mapping) const
     *
     * Returns the id that corresponds to a certain mapping. In case, the
     * the mapping has not been added to any CCnode yet, this functions returns
     * -1.
     *
     * @param mapping Pointer to a CubeMapping.
     */
    int
    get_mapping_id( CubeMapping* mapping );

    /**
     * @fn int add_mapping(CubeMapping* mapping)
     *
     * Adds a mapping, assigns an id to it and returns that id.
     *
     * @param mapping Pointer to the CubeMapping.
     */
    int
    add_mapping( CubeMapping* mapping );

    int                                                cache_size;
    std::map<const CnodeMetric*, std::vector<double> > cache;
    static std::map<CubeMapping*, int>                 mappings;
    static int                                         number_of_mappings;
};
}

#endif
