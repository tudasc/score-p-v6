/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2019                                                **
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
 * \brief Defines a metric class, which uses build in type as a data type
 *
 */
#ifndef CUBE_BUILDIN_METRIC_H
#define CUBE_BUILDIN_METRIC_H


#include <iosfwd>
#include <map>
#include <type_traits>

// #include "CubeVertex.h"
#include "CubeTypes.h"
#include "CubeSystemTreeNode.h"
#include "CubeLocationGroup.h"
#include "CubeLocation.h"
#include "CubeSimpleCache.h"
#include "CubeMetric.h"
#include "CubeRowWiseMatrix.h"
#include "CubeServices.h"
#include <limits>
#include <cstdlib>
#include <cmath>
namespace cube
{
static
bool
almost_equal( double x, double y, int ulp )
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::abs( x - y ) <= std::numeric_limits<double>::epsilon() * std::abs( x + y ) * ulp
           // unless the result is subnormal
           || std::abs( x - y ) < std::numeric_limits<double>::min();
};


class Connection;
class CubeProxy;

template <class T>
class BuildInTypeMetric : public Metric
{
protected:
    SimpleCache<T>* t_cache;

public:

    BuildInTypeMetric( const std::string& disp_name,
                       const std::string& uniq_name,
                       const std::string& dtype,
                       const std::string& uom,
                       const std::string& val,
                       const std::string& url,
                       const std::string& descr,
                       FileFinder*        ffinder,
                       Metric*            parent,
                       uint32_t           id                           = 0,
                       const std::string& cubepl_expression            = "",
                       const std::string& cubepl_init_expression       = "",
                       const std::string& cubepl_aggr_plus_expression  = "",
                       const std::string& cubepl_aggr_minus_expression = "",
                       const std::string& cubepl_aggr_aggr_expression  = "",
                       bool               row_wise                     = true,
                       VizTypeOfMetric    is_ghost                     = CUBE_METRIC_NORMAL
                       )
        :
        Metric( disp_name,
                uniq_name,
                dtype,
                uom,
                val,
                url,
                descr,
                ffinder,
                parent,
                id,
                cubepl_expression,
                cubepl_init_expression,
                cubepl_aggr_plus_expression,
                cubepl_aggr_minus_expression,
                cubepl_aggr_aggr_expression,
                row_wise,
                is_ghost
                )
    {
        t_cache = NULL;
    }

    virtual
    ~BuildInTypeMetric()
    {
        delete t_cache;
    };

    virtual
    bool
    isBuildIn()
    {
        return true;
    };

    virtual
    void
    invalidateCachedValue( Cnode*             cnode,
                           CalculationFlavour cf,
                           Sysres*            sysres = 0,
                           CalculationFlavour sf     = CUBE_CALCULATE_INCLUSIVE );

    virtual
    void
    invalidateCache( void );



    virtual
    void
    cache_selection( uint32_t     n_cid,
                     uint32_t     n_tid,
                     TypeOfMetric type );

    virtual
    void
    dropAllRows();


    // ----------- get incl/ecl severities ----------------------
    virtual Value*
    get_sev(
        const list_of_cnodes&       cnodes,
        const list_of_sysresources& sysres
        );

    // -----------------row wise ----------------------------------------
    virtual Value**
    get_sevs(
        const list_of_cnodes& cnodes
        );

    // --- massive calculation of a system tree ---------------------
    virtual
    void
    get_system_tree_sevs( const list_of_cnodes&  cnodes,
                          std::vector< Value* >& inclusive_values,
                          std::vector< Value* >& exclusive_values
                          );
    virtual
    inline
    void
    get_system_tree_sevs( const list_of_cnodes&  cnodes,
                          std::vector< double >& inclusive_values,
                          std::vector< double >& exclusive_values
                          );





protected:

    /// @brief
    ///     Constructs a Metric object via a Cube connection.
    /// @param connection
    ///     Active Cube connection.
    /// @param cubeProxy
    ///     Cube proxy for internal cross-referencing.
    ///
    /// @note
    ///     This constructor is called by the factory method.
    ///
    BuildInTypeMetric( Connection&      connection,
                       const CubeProxy& cubeProxy )
        : Metric( connection, cubeProxy )
    {
        t_cache = NULL;
    }

    static std::string
    get_type_string();


    // calculations used  in public implementations

    // --------- operators ( in future -> replaced by)

    virtual
    inline
    T
    plus_operator( T a, T b ) const
    {
        return a + b;
    }

    virtual
    inline
    T
    minus_operator( T a, T b ) const
    {
        if ( std::is_floating_point<T>::value )
        {
            if ( cube::almost_equal( a, b, 2 ) )
            {
                return static_cast<T>( 0. );
            }
        }
        return a - b;
    }

    virtual
    inline
    T
    aggr_operator( T a, T b ) const
    {
        return a + b;
    }

    // ----------------- calculations of poitlike parameters

    // returns an element corresponsing to cnode and location in not clustered case
    virtual
    inline
    T
    get_sev_elementary( const Cnode*    cnode,
                        const Location* loc )
    {
        if ( !cnode->is_clustered() )
        {
            return ( this->adv_sev_mat )->template getBuildInValue<T>(
                this->calltree_local_ids[ cnode->get_remapping_cnode()->get_id() ],
                loc->get_id() );
        }
        else
        {
            Process*           _proc        = loc->get_parent();
            int64_t            process_rank = _proc->get_rank();
            const cube::Cnode* _mapped      =  cnode->get_remapping_cnode( process_rank  );
            T                  tmp          = ( _mapped == NULL ) ? static_cast<T>( 0 ) : ( ( this->adv_sev_mat )->template getBuildInValue<T>( this->calltree_local_ids[ _mapped->get_id() ], loc->get_id() ) );
            int64_t            _norm        = cnode->get_cluster_normalization( process_rank );
            if ( _norm > 0 )
            {
                tmp /= ( ( uint64_t )_norm );
            }
            return tmp;
        }
    }




    virtual double
    get_sev_native(
        const list_of_cnodes&       cnodes,
        const list_of_sysresources& sysres
        );

    virtual double
    get_sev_native(
        const cube::Cnode*,
        const CalculationFlavour cnf,
        const cube::Sysres*         = NULL,
        const CalculationFlavour sf = CUBE_CALCULATE_NONE
        ) = 0;




    // -----------------row wise ----------------------------------------
    virtual double*
    get_sevs_native(
        const list_of_cnodes& cnodes
        );

    virtual double*
    get_sevs_native(
        const cube::Cnode*,
        const CalculationFlavour cnf
        ) = 0;

    //  --massive calculation of a system tree
    virtual
    void
    get_system_tree_sevs_native( const list_of_cnodes&  cnodes,
                                 std::vector< double >& inclusive_values,
                                 std::vector< double >& exclusive_values
                                 );

    virtual
    void
    get_system_tree_sevs_native(
        const cube::Cnode*,
        const CalculationFlavour cnf,
        std::vector< double >&   inclusive_values,
        std::vector< double >&   exclusive_values
        );
};

/// @todo The 'inline' definition is needed to make it work
///     with clang 5.1. Maybe test this with other compilers.
///
template < class T >
inline std::string
BuildInTypeMetric< T >::get_type_string()
{
    return "unknown";
}

/// @brief Syntactic sugar for the definition of template specializations.
///
#define CUBE_GET_TYPE_STRING_SPECIALIZATION_FOR( type ) \
    template < > \
    inline std::string BuildInTypeMetric< type >::get_type_string() { return #type; }

CUBE_GET_TYPE_STRING_SPECIALIZATION_FOR( double )
CUBE_GET_TYPE_STRING_SPECIALIZATION_FOR( int8_t )
CUBE_GET_TYPE_STRING_SPECIALIZATION_FOR( uint8_t )
CUBE_GET_TYPE_STRING_SPECIALIZATION_FOR( int16_t )
CUBE_GET_TYPE_STRING_SPECIALIZATION_FOR( uint16_t )
CUBE_GET_TYPE_STRING_SPECIALIZATION_FOR( int32_t )
CUBE_GET_TYPE_STRING_SPECIALIZATION_FOR( uint32_t )
CUBE_GET_TYPE_STRING_SPECIALIZATION_FOR( int64_t )
CUBE_GET_TYPE_STRING_SPECIALIZATION_FOR( uint64_t )

#undef CUBE_GET_TYPE_STRING_SPECIALIZATION_FOR

template <class T>
void
BuildInTypeMetric<T>::dropAllRows()
{
    Metric::dropAllRows();
    if ( t_cache )
    {
        t_cache->invalidate();
    }
}



template <class T>
double
BuildInTypeMetric<T>::get_sev_native(
    const list_of_cnodes&       cnodes,
    const list_of_sysresources& sysres
    )
{
    T to_return = 0;
    if ( sysres.size() == 0 ) // aggregation version
    {
        for ( list_of_cnodes::const_iterator c_iter = cnodes.begin(); c_iter != cnodes.end(); ++c_iter )
        {
            to_return = aggr_operator( to_return, get_sev_native( c_iter->first,
                                                                  c_iter->second
                                                                  ) );
        }
    }
    else
    {
        T                    over_sys = 0;
        list_of_sysresources _locs    = services::expand_sys_resources( sysres );
        for ( list_of_cnodes::const_iterator c_iter = cnodes.begin(); c_iter != cnodes.end(); ++c_iter )
        {
            over_sys = 0;
            for ( list_of_sysresources::const_iterator s_iter = _locs.begin(); s_iter != _locs.end(); ++s_iter )
            {
                over_sys = aggr_operator( over_sys, get_sev_native( c_iter->first,
                                                                    c_iter->second,
                                                                    s_iter->first,
                                                                    s_iter->second ) );
            }
            to_return = plus_operator( to_return, over_sys );
        }
    }
    return static_cast<double>( to_return );
}


template <class T>
Value*
BuildInTypeMetric<T>::get_sev(
    const list_of_cnodes&       cnodes,
    const list_of_sysresources& sysres
    )
{
    Value* v = metric_value->clone();
    ( *v ) = get_sev_native( cnodes, sysres );
    return v;
}

// -----------------row wise ----------------------------------------

template <class T>
double*
BuildInTypeMetric<T>::get_sevs_native(
    const list_of_cnodes& cnodes
    )
{
    list_of_cnodes::const_iterator c_iter    = cnodes.begin();
    double*                        to_return = get_sevs_native( c_iter->first, c_iter->second );
    ++c_iter;
    for (; c_iter != cnodes.end(); ++c_iter )
    {
        double* _to_return = get_sevs_native( c_iter->first, c_iter->second );

        for ( uint64_t i = 0; i < ntid; i++ )
        {
            to_return[ i ] = plus_operator( to_return[ i ], _to_return[ i ] );
        }
        services::delete_raw_row( _to_return );
    }
    return to_return;
}

template <class T>
Value**
BuildInTypeMetric<T>::get_sevs(
    const list_of_cnodes& cnodes
    )
{
//
    Value** to_return = services::create_row_of_values( ntid );
    double* row       = get_sevs_native( cnodes );
    for ( unsigned i = 0; i < ntid; ++i )
    {
        Value* _val = metric_value->clone();
        if ( row != NULL )
        {
            _val->
            operator=( row[ i ] );
        }

        to_return[ i ] = _val;
    }
    services::delete_raw_row( row );
    return to_return;
}


//  --massive calculation of a system tree

template <class T>
void
BuildInTypeMetric<T>::get_system_tree_sevs(    const list_of_cnodes&  cnodes,
                                               std::vector< Value* >& inclusive_values,
                                               std::vector< Value* >& exclusive_values
                                               )
{
    std::vector< double > _inclusive_values;
    std::vector< double > _exclusive_values;
    get_system_tree_sevs_native( cnodes, _inclusive_values, _exclusive_values );
    std::vector< double >::const_iterator i_iter = _inclusive_values.begin();
    std::vector< double >::const_iterator e_iter = _exclusive_values.begin();

    for (; i_iter != _inclusive_values.end(); ++i_iter, ++e_iter )
    {
        Value* _val = metric_value->clone();
        _val->
        operator=( * i_iter );

        inclusive_values.push_back( _val );
        _val = metric_value->clone();
        _val->
        operator=( * e_iter );

        exclusive_values.push_back( _val );
    }
}

template <class T>
inline
void
BuildInTypeMetric<T>::get_system_tree_sevs(    const list_of_cnodes&  cnodes,
                                               std::vector< double >& inclusive_values,
                                               std::vector< double >& exclusive_values
                                               )
{
    get_system_tree_sevs_native( cnodes, inclusive_values, exclusive_values );
}


//  --massive calculation of a system tree
template <class T>
void
BuildInTypeMetric<T>::get_system_tree_sevs_native( const list_of_cnodes&  cnodes,
                                                   std::vector< double >& inclusive_values,
                                                   std::vector< double >& exclusive_values
                                                   )
{
    list_of_cnodes::const_iterator c_iter = cnodes.begin();
    get_system_tree_sevs_native( c_iter->first, c_iter->second, inclusive_values, exclusive_values );
    ++c_iter;
    for (; c_iter != cnodes.end(); ++c_iter )
    {
        std::vector< double > _inclusive_values;
        std::vector< double > _exclusive_values;
        get_system_tree_sevs_native( c_iter->first, c_iter->second, _inclusive_values, _exclusive_values );
        for ( uint64_t i = 0; i < inclusive_values.size(); i++ )
        {
            inclusive_values[ i ] = this->plus_operator( inclusive_values[ i ], ( _inclusive_values[ i ] ) );
            exclusive_values[ i ] = this->plus_operator( exclusive_values[ i ], ( _exclusive_values[ i ] ) );
        }
    }
}



template <class T>
void
BuildInTypeMetric<T>::get_system_tree_sevs_native(
    const cube::Cnode*       cnode,
    const CalculationFlavour cnf,
    std::vector< double >&   inclusive_values,
    std::vector< double >&   exclusive_values
    )
{
    inclusive_values.resize( sysresv.size(), 0. );
    exclusive_values.resize( sysresv.size(), 0. );
    double* _locs = get_sevs_native( cnode, cnf );
    // set non-location elements to zero
    for ( size_t i = 0; i < exclusive_values.size(); ++i )
    {
        exclusive_values[ i ] = 0.;
        inclusive_values[ i ] = 0.;
    }
    // first copy locations
    for ( size_t i = 0; i < ntid; ++i )
    {
        exclusive_values[ sysv[ i ]->get_sys_id() ] = _locs[ i ];
        inclusive_values[ sysv[ i ]->get_sys_id() ] = _locs[ i ];
    }
    // calculate  location groups
    for ( size_t i = 0; i < lgv.size(); ++i )
    {
        LocationGroup* lg = lgv[ i ];
        for ( size_t j = 0; j < lg->num_children(); j++ )
        {
            Location* _loc = lg->get_child( j );
            inclusive_values[ lg->get_sys_id() ] = this->aggr_operator( inclusive_values[ lg->get_sys_id() ],  _locs[ _loc->get_id() ] );

            //add up to all parents ... need this coz of hybrid character of
            // the system tree model
            SystemTreeNode* _lg_parent = lg->get_parent();
            while ( _lg_parent != NULL )
            {
                inclusive_values[ _lg_parent->get_sys_id() ] = this->aggr_operator( inclusive_values[ _lg_parent->get_sys_id() ],  _locs[ _loc->get_id() ] );
                _lg_parent                                   = _lg_parent->get_parent();
            }
        }
    }
    return;
}







template <class T>
void
BuildInTypeMetric<T>::cache_selection( uint32_t n_cid, uint32_t n_tid, TypeOfMetric type )
{
    t_cache =  new SimpleCache<T>( n_cid, n_tid, sizeof( T ), ( type == CUBE_METRIC_INCLUSIVE ) ? CUBE_CALCULATE_INCLUSIVE : CUBE_CALCULATE_EXCLUSIVE );
}


template <class T>
void
BuildInTypeMetric<T>::invalidateCachedValue( Cnode* cnode, CalculationFlavour cf, Sysres* sysres, CalculationFlavour sf )
{
    t_cache->invalidateCachedValue( cnode, cf, sysres, sf );
}

template <class T>
void
BuildInTypeMetric<T>::invalidateCache( void )
{
    t_cache->invalidate();
}
}


#endif
