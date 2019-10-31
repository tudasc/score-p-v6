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


#ifndef CUBE_ALGORITHM_H
#define CUBE_ALGORITHM_H

#include <iterator>
#include <typeinfo>

namespace cube
{
/** \brief Transform the values in a container in the range [from, to).
 * @param[in] from Iterator pointing to first element to be transformed.
 * @param[in] to Iterator pointing to the delimiting element (first not to be transformed).
 * @param[out] result Iterator pointing to the first element of the result container.
 * @param[in] op Transformation operation.
 * @return Iterator pointing to the first element in the output sequence after the last transformed element.
 */
template <class InputIterator,
          class OutputIterator,
          class UnaryOperator
          >
OutputIterator
transform( InputIterator  from,
           InputIterator  to,
           OutputIterator result,
           UnaryOperator  op );

/** \brief Transform the values from two containers in the range of [from_first, to_first).
 * @param[in] from_first Iterator pointing to the first element in the first vector to be transformed.
 * @param[in] to_first Iterator pointing to the delimiting element in the first vector (first not to be transformed).
 * @param[in] from_second Iterator pointing to the first element in the second vector to be transformed.
 * @param[out] result Iterator pointing to the first element of the result container.
 * @param[in] op Transformation operation.
 * @return Iterator pointing to the first element in the output container after the last transformed element.
 */
template <class InputIterator,
          class OutputIterator,
          class BinaryOperator
          >
OutputIterator
transform( InputIterator  from_first,
           InputIterator  to_first,
           InputIterator  from_second,
           OutputIterator result,
           BinaryOperator op );


/** \brief Set the values of the elements of the specified range [from,to) to the value provided.
 * @param[in,out] from Iterator pointing to the first element to be set.
 * @param[in] to Iterator pointing to the delimiting element in the range (first not to be set).
 * @param[in] value Value to be assigned to each element in the range.
 */
template <class InputIterator,
          typename T>
void
fill( InputIterator from,
      InputIterator to,
      const T&      value )
{
    if ( typeid( typename std::iterator_traits<InputIterator>::iterator_category ) == typeid( std::random_access_iterator_tag ) )
    {
        typename std::iterator_traits<InputIterator>::value_type * data = &( *from );
        size_t num_elements = std::distance( from, to );

#pragma omp parallel for
        for ( size_t i = 0; i < num_elements; ++i )
        {
            data[ i ] = value;
        }
    }
    else
    {
#pragma omp parallel
        {
            for (; from != to; ++from )
            {
#pragma omp task
                {
                    *from = value;
                }
            }
        }
    }
}

/** \brief Accumulate values in the range [from, to) according to an aggregation operation.
 * @param from Iterator pointing to the first element of the input range.
 * @param to Iterator pointing to the delimiting element of the input range (first not to be accumulated).
 * @return Aggregated value according to the specified operation.
 */
template <template <typename> class BinaryOperator,
          class InputIterator>
typename std::iterator_traits<InputIterator>::value_type
accumulate( InputIterator from,
            InputIterator to )
{
    BinaryOperator<typename std::iterator_traits<InputIterator>::value_type> op;
    typename std::iterator_traits<InputIterator>::value_type                 result( op.neutralElement() );
    typename std::iterator_traits<InputIterator>::value_type                 local_result( result );

    if ( typeid( typename std::iterator_traits<InputIterator>::iterator_category ) == typeid( std::random_access_iterator_tag ) )
    {
        const typename std::iterator_traits<InputIterator>::value_type * const data = &( *from );
        size_t num_elements = std::distance( from, to );

#pragma omp parallel shared(result) firstprivate(local_result)
        {
#pragma omp for nowait
            for ( size_t i = 0; i < num_elements; ++i )
            {
                local_result = op.apply( local_result, data[ i ] );
            }

#pragma omp critical
            {
                result = op.apply( result, local_result );
            }
        }
    }
    else
    {
#pragma omp parallel
        {
            for (; from != to; ++from )
            {
#pragma omp task firstprivate( local_result )
                {
                    local_result = op.apply( local_result, *from );
                }
            }
#pragma omp critical
            {
                result = op.apply( result, local_result );
            }
        }
    }

    return result;
}
} // namespace cube


#endif /* CUBE_ALGORITHM_H */
