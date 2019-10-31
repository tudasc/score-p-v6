/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2017                                                **
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
 * \file CubePreallocator.h
 * \brief Provide a general preallocator of any Cube4 value.
 *
 *
 */

#ifndef __PREALLOCATOR_H
#define __PREALLOCATOR_H

// #define __DEBUG


#include <iostream>
#include <stdint.h>
#include <vector>
#include <iomanip>

namespace cube
{
template <typename T>
class Preallocator
{
protected:
    uint32_t        current_index;
    std::vector<T*> pool;
#ifdef __DEBUG
    uint32_t max_index;
    uint32_t num_up;
    uint32_t num_down;
#endif
public:
    bool truecreation;
    Preallocator<T>( );
    ~Preallocator<T>( );
    T*
    Get();
    void
    Put( T* );
};


template <typename T>
inline
Preallocator<T>::Preallocator()
{
    truecreation = true;
    size_t _size = 7;
    pool.resize( _size );
    for ( uint64_t i = 0; i < _size; i++ )
    {
        pool[ i ] = ::new T();
#ifdef __DEBUG
        std::cout << " Preallocate  element " << i << " : " << std::hex << ( uint64_t )( pool[ i ] ) << std::dec   << std::endl;
#endif
    }
    current_index = 0;
#ifdef __DEBUG
    max_index = 0;
    num_down  = 0;
    num_up    = 0;
#endif
    truecreation = false;
}



template <typename T>
inline
Preallocator<T>::~Preallocator()
{
    truecreation = true;
#ifdef __DEBUG
    std::cout << " Statistics: " << pool.size() << " " << max_index << " " << num_up << " " << num_down << std::endl;
#endif
    for ( int64_t i = pool.size() - 1; i >= 0; i-- )
    {
#ifdef __DEBUG
        std::cout << " Delete element " << i << " : " << std::hex << ( uint64_t )( pool[ i ] ) << " " << static_cast<T*>( pool[ i ] ) << " " << sizeof( *( static_cast<T*>( pool[ i ] ) ) ) << std::dec   << std::endl;
#endif
        ::delete static_cast<T*>( pool[ i ] );
    }
    truecreation = false;
}



// overloaded new operator
template <typename T>
inline
T*
Preallocator<T>::Get()
{
    if ( current_index >= pool.size() )
    {
        truecreation = true;
        pool.resize( 2 * pool.size() );
        for ( uint64_t i = current_index; i < pool.size(); ++i )
        {
            pool[ i ] = ( ::new T() );
        }
        truecreation = false;
    }
    T* _v = pool[ current_index ];

#ifdef __DEBUG
    num_up++;
    max_index = std::max( current_index, max_index );
    std::cout << "Get element " << std::hex << ( uint64_t )_v << std::dec << " from " << current_index << " " << num_up << " " << max_index << std::endl;
#endif

    pool[ current_index ] = NULL;
    current_index++;
    return _v;
}

// overloaded delete operator
template <typename T>
inline
void
Preallocator<T>::Put( T* element )
{
    if ( current_index == 0 )
    {
#ifdef  __DEBUG
        std::cout << " About to throw an exception bad_alloc coz one returns more than expected" << current_index << std::endl;
#endif
        throw std::bad_alloc();
    }
    current_index--;
#ifdef  __DEBUG
    std::cout << "Place element " << std::hex << ( uint64_t )element << std::dec << " back to " << current_index << std::endl;
#endif
    pool[ current_index ] = element;
#ifdef  __DEBUG
    num_down++;
#endif
}
}



#endif
