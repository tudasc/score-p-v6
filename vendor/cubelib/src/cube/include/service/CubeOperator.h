/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2014-2016                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2014                                                     **
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


#ifndef CUBE_OPERATOR_H
#define CUBE_OPERATOR_H

#include <limits>
#include <inttypes.h>

/**
 * @file CubeOperator.h
 *
 * @brief Defines aggregator operator class templates.
 *
 * The class templates defined in this header can be used in aggregation
 * functions when exclusifying and inclusifying dimensions.
 */

namespace cube
{
/// \name Helper classes
/// \{

/**
 * \brief Alexandrescu's integer-to-type mapping template
 */
template < int v >
struct Int2Type
{
    enum
    {
        value = v
    };
};

/// \}
/// \name Type traits
/// \{

enum ByteSwapAlgorithm
{
    BYTE_SWAP_GENERIC, BYTE_SWAP_INTEGRAL
};

/// Traits class to select the generic byte swap algorithm for any data type not specifically specialized.
template < typename T >
struct ByteSwapAlgorithmSelector
{
    enum
    {
        Algorithm = BYTE_SWAP_GENERIC
    };
};

#if 0
/// Traits specialization to use specific integral value swap algorithm for uint16_t values.
template < >
struct ByteSwapAlgorithmSelector< uint16_t >
{
    enum
    {
        Algorithm = BYTE_SWAP_INTEGRAL
    };
};

/// Traits specialization to use specific integral value swap algorithm for uint32_t values.
template < >
struct ByteSwapAlgorithmSelector< uint32_t >
{
    enum
    {
        Algorithm = BYTE_SWAP_INTEGRAL
    };
};

/// Traits specialization to use specific integral value swap algorithm for uint64_t values.
template < >
struct ByteSwapAlgorithmSelector< uint64_t >
{
    enum
    {
        Algorithm = BYTE_SWAP_INTEGRAL
    };
};
#endif

/// \}
/// \name Unary Operators
/// \{

/** \class ByteSwapOperator
 *  \brief Operator to swap the byte order of any integral type.
 */
template < class T >
class ByteSwapOperator
{
public:
    /** \brief Apply byte swap to data according to its datatype.
     * @param[in,out] data Data to be swapped.
     */
    inline static void
    apply( T& data )
    {
        data = swap(
            data,
            Int2Type< ByteSwapAlgorithmSelector< T >::Algorithm >() );
    }

    /** @ \brief Function operator to enable use in std::transform
     * @param[in] data Input data to be byte swapped.
     * @return Byte-swapped value of data
     */
    T
    operator()( const T& data )
    {
        return swap(
            data,
            Int2Type< ByteSwapAlgorithmSelector< T >::Algorithm >() );
    }

    /** \brief Inverse operation of the byte swap is the operation itself.
     * @param[in] data Data to be swapped.
     */
    inline static void
    inverse( T& data )
    {
        apply( data );
    }

private:
    /** \brief Generic byte swap algorithm
     *
     * @param[in] data Data to be swapped.
     * @param[in] algorithm Type trait to identify algorithm.
     */
    inline static T
    swap( const T& data, Int2Type< BYTE_SWAP_GENERIC > )
    {
        union
        {
            T             data;
            unsigned char byte[ sizeof( T ) ];
        } data_orig, data_swapped;
        data_orig.data = data;

        for ( size_t i = 0; i < sizeof( T ); ++i )
        {
            data_swapped.byte[ i ] = data_orig.byte[ sizeof( T ) - 1 - i ];
        }
        return data_swapped.data;
    }

    /** \brief Specialized byte swap algorithms for integral types
     *
     * @param[in] data Data to be swapped.
     * @param[in] algorithm Type trait to identify algorithm.
     */
    inline static T
    swap( const T& data, Int2Type< BYTE_SWAP_INTEGRAL > )
    {
        unsigned char byte[ sizeof( T ) ];
        for ( int i = 0; i < sizeof( T ); ++i )
        {
            byte[ i ] = ( data >> i * 8 ) & 255;
        }
        T data_swapped = 0;
        for ( int i = 0; i < sizeof( T ); ++i )
        {
            data_swapped += ( byte[ i ] << ( sizeof( T ) - 1 - i ) * 8 );
        }
        return data_swapped;
    }
};

/// \}
/// \name Binary Operators
/// \{

/** @class SumOperator
 *  @brief Computes the sum of two values.
 */
template < class T >
struct SumOperator
{
    /// @brief Type of values used with this operator
    typedef T value_type;
#if 0
    /// @brief Inverse operator
    typedef DiffOperator<T> inverse_op;
#endif
    /** \brief Returns zero (the neutral element to addition/subtraction).
     * @return Zero.
     */
    inline static T
    neutralElement()
    {
        return 0;
    }

    /** Adds to values.
     * @param[in] lhs Left-hand side of the operation.
     * @param[in] rhs Right-hand side of the operation.
     * @return Sum of the values.
     */
    inline static T
    apply( const T& lhs, const T& rhs )
    {
        return lhs + rhs;
    }

    /** \brief Subtracts one value from the other
     * @param[in] lhs Left-hand side of the operation.
     * @param[in] rhs Right-hand side of the operation.
     * @return The difference between \a lhs and \a rhs.
     */
    inline static T
    inverse( const T& lhs, const T& rhs )
    {
        return lhs - rhs;
    }
};

/** @class DiffOperator
 * @brief Computes the difference between the first and the second argument.
 */
template < typename T>
struct DiffOperator
{
    /// @brief Type of values used with this operator
    typedef T value_type;
#if 0
    /// @brief Inverse operator
    typedef SumOperator<T> inverse_op;
#endif
    /** \brief Returns zero (the neutral element to addition/subtraction).
     * @return Zero.
     */
    inline static T
    neutralElement()
    {
        return 0;
    }

    /** \brief Subtracts one value from the other
     * @param[in] lhs Left-hand side of the operation.
     * @param[in] rhs Right-hand side of the operation.
     * @return The difference between \a lhs and \a rhs.
     */
    inline static T
    apply( const T& lhs, const T& rhs )
    {
        return lhs - rhs;
    }

    /** \brief Functor interface for operator
     * @param[in] lhs Left-hand side of the operation.
     * @param[in] rhs Right-hand side of the operation.
     * @return The difference between @p lhs and @p rhs.
     */
    inline T
    operator()( const T& lhs, const T& rhs )
    {
        return lhs - rhs;
    }
};

/** @class MaxOperator
 *  @brief Computes the maximum of two values.
 */
template < class T >
struct MaxOperator
{
    /// @brief Type of values used with this operator
    typedef T value_type;


    /** \brief Returns the minimum value possible for a given type.
     * The neutral element is used to initialize local aggregation values.
     * @return Minimum value for a given datatype.
     */
    inline static T
    neutralElement()
    {
        return std::numeric_limits< T >::min();
    }

    /** \brief Determine the larger of two values.
     * @param[in] lhs Left-hand value of the operator.
     * @param[in] rhs Right-hand value of the operator.
     * @return Larger value of the two \a lhs and \a rhs.
     */
    inline static T
    apply( const T& lhs, const T& rhs )
    {
        return lhs > rhs ? lhs : rhs;
    }

    /// @note The maximum operator does not define an inverse function.
};

/** @class MinOperator
 *  @brief Computes the minimum of two values
 */
template < class T >
struct MinOperator
{
    /** \brief Returns the maximum value possible for a given type.
     *  The neutral element is used to initialize local aggregation values.
     *  @return Maximum value for a given datatype.
     */
    static T
    neutralElement()
    {
        return std::numeric_limits< T >::max();
    }

    /** \brief Determine the smaller of two values.
     *  @param[in] lhs Left-hand side of the operation.
     *  @param[in] rhs Right-hand side of the operation.
     *  @return Smaller value of the two \a lhs and \a rhs.
     */
    inline static T
    apply( const T& lhs, const T& rhs )
    {
        return lhs < rhs ? lhs : rhs;
    }

    /// @note The minimum operator does not define an inverse function.
};

/// \}
} // namespace cube

#endif // CUBE_OPERATOR_H
