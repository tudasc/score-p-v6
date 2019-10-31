/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2015-2016                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2009-2014                                                **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  Copyright (c) 2014                                                     **
**  RWTH Aachen University, JARA-HPC                                       **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


#ifndef CUBE_AGGREGATOR_H
#define CUBE_AGGREGATOR_H

#include <vector>

#include "CubeOperator.h"
/**
 * \file CubeAggregator.h
 *
 * \brief Defines aggregation classes for operators working on vector iterators.
 */

namespace cube
{
/** \class Aggregator
 *  \brief Parallel aggregation class for vectors using OpenMP.
 */
template <
    typename T,
    template <typename> class Operator
    >
struct Aggregator
{
    typedef typename std::vector<T>::const_iterator Iterator; ///< Iterator type

    /** \brief Apply operator to all elements of [from : end)
     *
     * @param from Iterator defining the start element.
     * @param to Iterator defining the end element (which is not aggregated).
     * @return Result of the aggregation process.
     */
    inline static T
    apply( Iterator from,
           Iterator to )
    {
        T              result( Operator<T>::neutralElement() );
        T              local_result( result );
        const T* const data         = &( *from );
        size_t         num_elements = std::distance( from, to );

#pragma omp parallel shared(result) firstprivate(local_result)
        {
#pragma omp for nowait
            for ( int i = 0; i < num_elements; ++i )
            {
                local_result = Operator<T>::apply( local_result, data[ i ] );
            }

#pragma omp critical
            {
                result = Operator<T>::apply( result, local_result );
            }
        }
        return result;
    }
};
} // namespace cube

#endif // CUBE_AGGREGATOR_H
