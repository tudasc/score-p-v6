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
 * \brief Defines a metric class, which uses build in type as a data type
 *
 */
#ifndef CUBE_INCLUSIVE_BUILDIN_METRIC_H
#define CUBE_INCLUSIVE_BUILDIN_METRIC_H


#include <iosfwd>
#include <map>
#include <cstring>
#include <limits>

#include "CubeIDdeliverer.h"
#include "CubeWideSearchEnumerator.h"

#include "CubeMetricBuildInType.h"
#include "CubeServices.h"

/*
 *----------------------------------------------------------------------------
 *
 * class BuildInTypeMetric
 *
   =======
 */


namespace cube
{
class Connection;
class CubeProxy;

template <class T>
class InclusiveBuildInTypeMetric : public BuildInTypeMetric<T>
{
public:

    InclusiveBuildInTypeMetric( const std::string& disp_name,
                                const std::string& uniq_name,
                                const std::string& dtype,
                                const std::string& uom,
                                const std::string& val,
                                const std::string& url,
                                const std::string& descr,
                                FileFinder*        ffinder,
                                Metric*            parent,
                                uint32_t           id = 0,
                                const std::string& cubepl_expression = "",
                                const std::string& cubepl_init_expression = "",
                                const std::string& cubepl_aggr_plus_expression = "",
                                const std::string& cubepl_aggr_minus_expression = "",
                                const std::string& cubepl_aggr_aggr_expression = "",
                                bool               row_wise = true,
                                VizTypeOfMetric    is_ghost = CUBE_METRIC_NORMAL
                                )
        :
        BuildInTypeMetric< T >( disp_name,
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
    }

    /// @brief
    ///     Factory method to create an intrinsic-type inclusive metric via a Cube connection.
    /// @param connection
    ///     Active Cube connection.
    /// @param cubeProxy
    ///     Cube proxy for internal cross-referencing.
    /// @return
    ///     New metric.
    ///
    static Serializable*
    create( Connection&      connection,
            const CubeProxy& cubeProxy );

    virtual
    ~InclusiveBuildInTypeMetric<T>( )
    {
    }

    /// @copydoc cube::Serializable::get_serialization_key
    ///
    virtual std::string
    get_serialization_key() const;

    /// @copydoc cube::Serializable::get_serialization_key
    ///
    static std::string
    get_static_serialization_key();

    virtual TypeOfMetric
    get_type_of_metric() const
    {
        return CUBE_METRIC_INCLUSIVE;
    }

    virtual IndexFormat
    get_index_format()
    {
        return CUBE_INDEX_FORMAT_DENSE;
    }

    virtual std::string
    get_metric_kind() const
    {
        return "INCLUSIVE";
    };

    virtual row_of_objects_t*
    create_calltree_id_maps( IDdeliverer*,
                             Cnode*,
                             row_of_objects_t*  );                               // /< Creates enumeration of Callpath-Tree according the "deep search" prescription. It is optimal for the calculation of inclusive values in exclusive metric.



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
    InclusiveBuildInTypeMetric( Connection&      connection,
                                const CubeProxy& cubeProxy )
        : BuildInTypeMetric<T>( connection, cubeProxy )
    {
        /// @note The full packing and unpacking is done by the Metric base class;
    }

    // ----------------- calculations of poitlike parameters

    virtual double
    get_sev_native(
        const cube::Cnode*,
        const CalculationFlavour cnf,
        const cube::Sysres* = NULL,
        const CalculationFlavour snf = CUBE_CALCULATE_NONE
        );

    // -----------------row wise ----------------------------------------
    virtual double*
    get_sevs_native(
        const cube::Cnode*,
        const CalculationFlavour cnf
        );

private:
    double
    get_sev_aggregated( const cube::Cnode*       cnode,
                        const CalculationFlavour cnf );

    double
    get_sev_pointlike( const Cnode*             cnode,
                       const CalculationFlavour cnf,
                       const Sysres*            sys,
                       const CalculationFlavour sf );

    char*
    get_sevs_raw(
        const cube::Cnode*,
        const CalculationFlavour cnf
        );
};




template <class T>
row_of_objects_t*
InclusiveBuildInTypeMetric<T>::create_calltree_id_maps( IDdeliverer* ids, Cnode* root, row_of_objects_t* _row  )
{
    WideSearchEnumerator enumerator;
    ids->reset();
    _row = enumerator.get_objects_to_enumerate( root, _row );

    for ( row_of_objects_t::iterator iter = _row->begin(); iter < _row->end(); ++iter )
    {
        if ( this->calltree_local_ids.size() <= ( *iter )->get_id() )
        {
            this->calltree_local_ids.resize( ( *iter )->get_id() + 1  );
        }
        this->calltree_local_ids[ ( *iter )->get_id() ] = ids->get_next_id();
    }

    return _row;
}




// / ------------------------ Sum over all threads for given cnode and all subcnodes

template <class T>
double
InclusiveBuildInTypeMetric<T>::get_sev_native(
    const cube::Cnode*       cnode,
    const CalculationFlavour cnf,
    const cube::Sysres*      sys,
    const CalculationFlavour sf
    )
{
    if ( sys == NULL )
    {
        return get_sev_aggregated( cnode, cnf );
    }
    else
    {
        return get_sev_pointlike( cnode, cnf, sys, sf );
    }
}




template <class T>
double
InclusiveBuildInTypeMetric<T>::get_sev_aggregated( const Cnode* cnode, const CalculationFlavour cnf )
{
    if ( !( this->active ) )
    {
        return 0.;
    }


    T v = static_cast<T>( 0 );
    if ( this->isCacheable() && ( ( this->t_cache )->isTCachedValue( cnode, cnf )  ) )
    {
        return ( this->t_cache )->getTCachedValue( cnode, cnf );
    }

    if ( this->adv_sev_mat == NULL && get_type_of_metric() == CUBE_METRIC_INCLUSIVE )
    {
        return v;
    }

    size_t sysv_size = this->sysv.size();
    for ( size_t i = 0; i < sysv_size; i++ )
    {
        const Location* _loc = this->sysv[ i ];
        T               tmp  = this->get_sev_elementary( cnode, _loc );
        ( v ) = this->aggr_operator( v,  tmp );
    }



    if ( cnf == CUBE_CALCULATE_EXCLUSIVE &&  ( cnode->num_children() > 0 ) )
    {
        std::vector<const Cnode*> _cnodes;  // collection of cnodes for the calculation
        for ( cnode_id_t cid = 0; cid < cnode->num_children(); cid++  )
        {
            const Cnode* __c  = cnode->get_child( cid );
            bool         _add = ( !__c->isHidden() );
            if ( _add )
            {
                _cnodes.push_back( __c );
            }
        }

        for ( std::vector<const Cnode*>::const_iterator _iter = _cnodes.begin(); _iter != _cnodes.end(); ++_iter )
        {
            const Cnode* __c = *_iter;
            T            __v = static_cast<T>( 0 );
            for ( size_t i = 0; i < sysv_size; i++ )
            {
                const Location* _loc = this->sysv[ i ];
                T               tmp  = this->get_sev_elementary( __c, _loc );
                ( __v ) = this->aggr_operator( __v,  tmp );
            }
            ( v ) = this->minus_operator( v,  __v );
        }
    }
    if ( this->isCacheable() )
    {
        this->t_cache->setTCachedValue( v,  cnode, cnf );
    }
    return static_cast<double>( v );
}








template <class T>
double
InclusiveBuildInTypeMetric<T>::get_sev_pointlike( const Cnode* cnode, const CalculationFlavour cnf, const Sysres* sys,  const CalculationFlavour sf )
{
    if ( !( this->active ) )
    {
        return 0.;
    }

    T v = static_cast<T>( 0 );
    if ( ( sys->isSystemTreeNode() || sys->isLocationGroup() ) && ( sf == cube::CUBE_CALCULATE_EXCLUSIVE ) )
    {
        return 0.;
    }
    if ( this->adv_sev_mat == NULL && get_type_of_metric() == CUBE_METRIC_INCLUSIVE )
    {
        return v;
    }

    if (  this->isCacheable() && (  ( this->t_cache )->isTCachedValue( cnode, cnf, sys, sf ) ) )
    {
        return ( this->t_cache )->getTCachedValue( cnode, cnf, sys, sf );
    }



    std::vector<Sysres*> _locations = sys->get_whole_subtree();  // collection of locations of this sysres
    for ( std::vector<Sysres*>::const_iterator _siter = _locations.begin(); _siter != _locations.end(); ++_siter )
    {
        const Location* _loc = ( Location* )( *_siter );
        T               _v   = this->get_sev_elementary( cnode, _loc );
        v = this->aggr_operator( v, _v );
    }

    if ( cnf == CUBE_CALCULATE_EXCLUSIVE &&  ( cnode->num_children() > 0 ) )
    {
        std::vector<const Cnode*> _cnodes;  // collection of cnodes for the calculation
        for ( cnode_id_t cid = 0; cid < cnode->num_children(); cid++  )
        {
            const Cnode* __c  = cnode->get_child( cid );
            bool         _add = ( !__c->isHidden() );
            if ( _add )
            {
                _cnodes.push_back( __c );
            }
        }
        for ( std::vector<const Cnode*>::const_iterator _iter = _cnodes.begin(); _iter != _cnodes.end(); ++_iter )
        {
            const Cnode* __c = *_iter;
            T            _v  = static_cast<T>( 0 );
            for ( std::vector<Sysres*>::const_iterator _siter = _locations.begin(); _siter != _locations.end(); ++_siter )
            {
                const Location* _loc = ( Location* )( *_siter );
                T               __v  = this->get_sev_elementary( __c, _loc );
                _v = this->aggr_operator( _v,  __v );
            }
            v = this->minus_operator( v, _v );
        }
    }
    if ( this->isCacheable() )
    {
        this->t_cache->setTCachedValue( v, cnode, cnf, sys, sf );
    }
    return static_cast<double>( v );
}

template < class T >
inline Serializable*
InclusiveBuildInTypeMetric< T >::create( Connection&      connection,
                                         const CubeProxy& cubeProxy )
{
    return new InclusiveBuildInTypeMetric<T>( connection, cubeProxy );
}

template < class T >
inline std::string
InclusiveBuildInTypeMetric< T >::get_serialization_key() const
{
    return get_static_serialization_key();
}

template < class T >
inline std::string
InclusiveBuildInTypeMetric< T >::get_static_serialization_key()
{
    return "Metric|Inclusive|" + BuildInTypeMetric<T>::get_type_string();
}

template <class T>
char*
InclusiveBuildInTypeMetric<T>::get_sevs_raw( const Cnode* cnode, const CalculationFlavour cnf )
{
    if ( !( this->active ) )
    {
        return NULL;
    }


    if ( this->adv_sev_mat == NULL && get_type_of_metric() == CUBE_METRIC_EXCLUSIVE )
    {
        return NULL;
    }
    if ( this->isCacheable() )
    {
        char* v = ( this->t_cache )->getCachedRow( cnode, cnf );
        if ( v != NULL )
        {
            return v;
        }
    }

    size_t sysv_size  = this->sysv.size();
    char*  to_return  = services::create_raw_row( sysv_size * this->metric_value->getSize() );
    T*     _to_return = ( T* )to_return;

    for ( size_t i = 0; i < sysv_size; i++ )
    {
        Location* _loc = this->sysv[ i ];
        _to_return[ i ] = this->get_sev_elementary( cnode, _loc );
    }


    if ( cnf == CUBE_CALCULATE_EXCLUSIVE &&  ( cnode->num_children() > 0 ) )
    {
        std::vector<const Cnode*> _cnodes;  // collection of cnodes for the calculation
        for ( cnode_id_t cid = 0; cid < cnode->num_children(); cid++  )
        {
            const Cnode* __c  = cnode->get_child( cid );
            bool         _add = ( !__c->isHidden() );
            if ( _add )
            {
                _cnodes.push_back( __c );
            }
        }

        for ( std::vector<const Cnode*>::const_iterator _iter = _cnodes.begin(); _iter != _cnodes.end(); ++_iter )
        {
            const Cnode* __c = *_iter;
            for ( size_t i = 0; i < sysv_size; i++ )
            {
                const Location* _loc = this->sysv[ i ];
                T               tmp  = this->get_sev_elementary( __c, _loc );
                _to_return[ i ] = this->minus_operator( _to_return[ i ], tmp );
            }
        }
    }
    if ( this->isCacheable() )
    {
        ( this->t_cache )->setCachedRow( to_return,  cnode, cnf );
    }
    return to_return;
}


template <class T>
double*
InclusiveBuildInTypeMetric<T>::get_sevs_native( const Cnode*             cnode,
                                                const CalculationFlavour cfv
                                                )
{
    char*   _v        =   this->get_sevs_raw( cnode, cfv );
    T*      __v       = ( T* )_v;
    size_t  sysv_size = this->sysv.size();
    double* to_return = services::create_row_of_doubles( sysv_size );
    if ( _v == NULL )
    {
        return to_return;
    }
    for ( unsigned i = 0; i < sysv_size; ++i )
    {
        to_return[ i ] = ( double )__v[ i ];
    }
    services::delete_raw_row( _v );
    return to_return;
}
}


#endif
