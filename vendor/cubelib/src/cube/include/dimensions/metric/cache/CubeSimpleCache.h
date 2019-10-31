/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2018                                                **
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
 * \file
 * \brief Provides an interface for simple caching mechanisms in metrics, using three maps
 */

#ifndef __SIMPLE_CACHE_H
#define __SIMPLE_CACHE_H


#include <map>
#include <stdint.h>
#include <limits>

#include "CubeCache.h"
#include "CubeCnode.h"
#include "CubeValue.h"
#include "CubeSysres.h"

namespace cube
{
/**
 * Class "SimpleCache" is a class, which stores all values without any evaluation of probability
 * Drawback: memory footprint is too big. But this simple realization allows to test another functionalities
 */
template<class T>
class SimpleCache :
    public Cache
{
private:
    typedef std::map<const simple_cache_key_t, Value*>        cache_map;
    typedef typename std::map<const simple_cache_key_t, char*>row_cache_map;
    typedef typename std::map<const simple_cache_key_t, T>    t_cache_map;

    cache_map     stn_container;
    cache_map     sum_container;
    t_cache_map   t_stn_container;
    t_cache_map   t_sum_container;
    row_cache_map row_container;

    T prepared_value;

protected:

    cnode_id_t  number_cnodes;
    sysres_id_t number_loc;
    size_t      loc_size;

    CalculationFlavour myf;

    simple_cache_key_t threshold;



    simple_cache_key_t
    get_key( const Cnode*,
             const CalculationFlavour,
             const Sysres*            sysres = 0,
             const CalculationFlavour sf = CUBE_CALCULATE_INCLUSIVE  ) const;


    void
    empty();


public:

    SimpleCache( cnode_id_t         _n_cnode,
                 sysres_id_t        _n_loc,
                 size_t             _loc_size,
                 CalculationFlavour metric_flavor = CUBE_CALCULATE_EXCLUSIVE
                 )
        : number_cnodes( _n_cnode ), number_loc( _n_loc ), loc_size( _loc_size ),
        myf( metric_flavor ), threshold( 0.7 * number_cnodes )
    {
    }

    virtual
    ~SimpleCache()
    {
        empty();
    };

    virtual Value*
    getCachedValue( const Cnode*             cnode,
                    const CalculationFlavour cf,
                    const Sysres*            sysres = 0,
                    const CalculationFlavour sf = CUBE_CALCULATE_INCLUSIVE ) const;                                                                                    // /< Returns Value or NULL, if not present

    virtual void
    setCachedValue( Value*,
                    const Cnode*             cnode,
                    const CalculationFlavour cf,
                    const Sysres*            sysres = 0,
                    const CalculationFlavour sf = CUBE_CALCULATE_INCLUSIVE );


    T
    getTCachedValue( const Cnode*             cnode,
                     const CalculationFlavour cf,
                     const Sysres*            sysres = 0,
                     const CalculationFlavour sf = CUBE_CALCULATE_INCLUSIVE,
                     const bool               use_prepared_value = true
                     ) const;                                                                                // /< Returns Value or NULL, if not present

    bool
    isTCachedValue( const Cnode*             cnode,
                    const CalculationFlavour cf,
                    const Sysres*            sysres = 0,
                    const CalculationFlavour sf = CUBE_CALCULATE_INCLUSIVE );


    void
    setTCachedValue( T                        value,
                     const Cnode*             cnode,
                     const CalculationFlavour cf,
                     const Sysres*            sysres = 0,
                     const CalculationFlavour sf = CUBE_CALCULATE_INCLUSIVE );

    char*
    getCachedRow( const Cnode*             cnode,
                  const CalculationFlavour cf ) const;                                                                                     // /< Returns Value or NULL, if not present

    void
    setCachedRow( char*                    value,
                  const Cnode*             cnode,
                  const CalculationFlavour cf );

    // /< Stores or not (if not needed) a Value.

    virtual void
    invalidateCachedValue( const Cnode*             cnode,
                           const CalculationFlavour cf,
                           const Sysres*            sysres = 0,
                           const CalculationFlavour sf = CUBE_CALCULATE_INCLUSIVE );


    virtual void
    invalidate( void );
};



template<class T>
bool
SimpleCache<T>::isTCachedValue( const Cnode*             cnode,
                                const CalculationFlavour cf,
                                const Sysres*            sysres,
                                const CalculationFlavour sf )
{
    simple_cache_key_t key = get_key( cnode, cf, sysres, sf );
    if ( key < 0 ) // do not cache ...
    {
        return false;
    }
    if ( sysres )
    {
        typename t_cache_map::const_iterator iter = t_stn_container.find( key );
        if ( iter != t_stn_container.end() )
        {
            prepared_value =  iter->second;
            return true;
        }
    }
    else
    {
        typename t_cache_map::const_iterator iter = t_sum_container.find( key );
        if ( iter != t_sum_container.end() )
        {
            prepared_value =  iter->second;
            return true;
        }
    }
    return false;
}

template<class T>
T
SimpleCache<T>::getTCachedValue( const Cnode*             cnode,
                                 const CalculationFlavour cf,
                                 const Sysres*            sysres,
                                 const CalculationFlavour sf,
                                 const bool               use_prepared_value ) const
{
    if ( use_prepared_value )
    {
        return prepared_value;
    }

    simple_cache_key_t key = get_key( cnode, cf, sysres, sf );
    if ( key < 0 ) // do not cache ...
    {
        return std::numeric_limits<T>::max();
    }
    if ( sysres )
    {
        typename t_cache_map::const_iterator iter = t_stn_container.find( key );
        if ( iter != t_stn_container.end() )
        {
            return iter->second;
        }
    }
    else
    {
        typename t_cache_map::const_iterator iter = t_sum_container.find( key );
        if ( iter != t_sum_container.end() )
        {
            return iter->second;
        }
    }
    return std::numeric_limits<T>::max();
}


template<class T>
void
SimpleCache<T>::setTCachedValue( T                        value,
                                 const Cnode*             cnode,
                                 const CalculationFlavour cf,
                                 const Sysres*            sysres,
                                 const CalculationFlavour sf )
{
    const simple_cache_key_t key = get_key( cnode, cf, sysres, sf );
    if ( key < 0 ) // do not cache ...
    {
        return;
    }
    // efficient "add if not yet in map" (S. Meyers, "Efficient STL", Item 24)
    if ( sysres )
    {
        typename t_cache_map::const_iterator iter = t_stn_container.lower_bound( key );
        if ( iter == t_stn_container.end() || t_stn_container.key_comp() ( key, iter->first ) )
        {
            t_stn_container.insert( typename t_cache_map::value_type( key, value ) );
        }
    }
    else
    {
        typename t_cache_map::const_iterator iter = t_sum_container.lower_bound( key );
        if ( iter == t_sum_container.end() || t_sum_container.key_comp() ( key, iter->first ) )
        {
            t_sum_container.insert( typename t_cache_map::value_type( key, value ) );
        }
    }
}

template<class T>
void
SimpleCache<T>::empty()
{
    // use Free call from Value to remove items "from memory" -> place them back to pool
    for ( cache_map::iterator iter = stn_container.begin(); iter != stn_container.end(); ++iter )
    {
        iter->second->Free();
    }
    for ( cache_map::iterator iter = sum_container.begin(); iter != sum_container.end(); ++iter )
    {
        iter->second->Free();
    }
    for ( row_cache_map::iterator iter = row_container.begin(); iter != row_container.end(); ++iter )
    {
        delete[] iter->second;
    }
    sum_container.clear();
    stn_container.clear();
    t_sum_container.clear();
    t_stn_container.clear();
    row_container.clear();
}

template<class T>
Value*
SimpleCache<T>::getCachedValue( const Cnode*             cnode,
                                const CalculationFlavour cf,
                                const Sysres*            sysres,
                                const CalculationFlavour sf ) const
{
    simple_cache_key_t key = get_key( cnode, cf, sysres, sf );
    if ( key < 0 ) // do not cache ...
    {
        return 0;
    }

    Value* _value = 0;
    if ( sysres )
    {
        cache_map::const_iterator iter = stn_container.find( key );
        if ( iter != stn_container.end() )
        {
            _value = iter->second;
        }
    }
    else
    {
        cache_map::const_iterator iter = sum_container.find( key );
        if ( iter != sum_container.end() )
        {
            _value = iter->second;
        }
    }
    return _value ? _value->copy() : 0;     // pretend we do not
}

template<class T>
void
SimpleCache<T>::setCachedValue( Value*                   value,
                                const Cnode*             cnode,
                                const CalculationFlavour cf,
                                const Sysres*            sysres,
                                const CalculationFlavour sf )
{
    simple_cache_key_t key = get_key( cnode, cf, sysres, sf );
    if ( key < 0 ) // do not cache ...
    {
        return;
    }

    // efficient "add if not yet in map" (S. Meyers, "Efficient STL", Item 24)
    if ( sysres )
    {
        cache_map::iterator iter = stn_container.lower_bound( key );
        if ( iter == stn_container.end() || stn_container.key_comp() ( key, iter->first ) )
        {
            stn_container.insert( cache_map::value_type( key, value->copy() ) );
        }
    }
    else
    {
        cache_map::iterator iter = sum_container.lower_bound( key );
        if ( iter == sum_container.end() || sum_container.key_comp() ( key, iter->first ) )
        {
            sum_container.insert(  cache_map::value_type( key, value->copy() ) );
        }
    }
}


template<class T>
simple_cache_key_t
SimpleCache<T>::get_key( const Cnode*             cnode,
                         const CalculationFlavour cf,
                         const Sysres*            sysres,
                         const CalculationFlavour sf ) const
{
    if ( cf == myf )
    {
        return ( simple_cache_key_t )( -1 );
    }
    if ( !sysres )
    {
        return 2 * cnode->get_id() + cf;
    }
    if ( !sysres->isSystemTreeNode() )
    {
        return ( simple_cache_key_t )( -1 );
    }

    simple_cache_key_t Nc;
    if ( myf == CUBE_CALCULATE_EXCLUSIVE )
    {
        Nc = cnode->total_num_children();
    }
    else // myf == CUBE_CALCULATE_INCLUSIVE
    {
        Nc = cnode->num_children();
    }
    if ( Nc <= threshold )
    {
        return ( simple_cache_key_t )( -1 );
    }

    return 2 * number_loc * ( 2 * cnode->get_id() + cf ) +  2 * sysres->get_id() + sf;
}


template<class T>
void
SimpleCache<T>::invalidateCachedValue( const Cnode*             cnode,
                                       const CalculationFlavour cf,
                                       const Sysres*            sysres,
                                       const CalculationFlavour sf )
{
    simple_cache_key_t key = get_key( cnode, cf, sysres, sf );

    cache_map::iterator iter = stn_container.find( key );
    if ( iter != stn_container.end() )
    {
        iter->second->Free();
    }
    iter = sum_container.find( key );
    if ( iter != sum_container.end() )
    {
        iter->second->Free();
    }
    row_cache_map::iterator r_iter = row_container.find( key );
    if ( r_iter != row_container.end() )
    {
        delete[] r_iter->second;
    }
    sum_container.erase( key );
    stn_container.erase( key );
    t_sum_container.erase( key );
    t_stn_container.erase( key );
    row_container.erase( key );
}


template<class T>
char*
SimpleCache<T>::getCachedRow( const Cnode*             cnode,
                              const CalculationFlavour cf ) const
{
    simple_cache_key_t key = get_key( cnode, cf );
    if ( key < 0 ) // do not cache ...
    {
        return 0;
    }

    char*                         _value = NULL;
    row_cache_map::const_iterator iter   = row_container.find( key );
    if ( iter != row_container.end() )
    {
        _value = new char[ number_loc * loc_size ];
        memcpy( _value, iter->second, number_loc * loc_size  );
    }
    return _value;
}



template<class T>
void
SimpleCache<T>::setCachedRow( char*                    value,
                              const Cnode*             cnode,
                              const CalculationFlavour cf )
{
    simple_cache_key_t key = get_key( cnode, cf );
    if ( key < 0 ) // do not cache ...
    {
        return;
    }

    // efficient "add if not yet in map" (S. Meyers, "Efficient STL", Item 24)
    row_cache_map::iterator iter = row_container.lower_bound( key );
    if ( iter == row_container.end() || row_container.key_comp() ( key, iter->first ) )
    {
        char* _tmp =  new char[ number_loc * loc_size ];
        memcpy( _tmp, value, number_loc * loc_size  );
        row_container.insert( row_cache_map::value_type( key, _tmp ) );
    }
}


template<class T>
void
SimpleCache<T>::invalidate( void )
{
    empty();
}
}

#endif
