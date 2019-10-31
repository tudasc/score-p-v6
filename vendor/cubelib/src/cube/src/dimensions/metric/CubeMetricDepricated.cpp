/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2018                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/



/**
 * \file CubeMetricDepricated.cpp
 * \brief Defines a depricated calls methods of a Metric

 ********************************************/

#include "config.h"

#include "CubeMetric.h"

#include <cassert>
#include <iostream>
#include <utility>

#include "CubeCaches.h"
#include "CubeCnode.h"
#include "CubeConnection.h"
#include "CubeCustomPreDerivedExclusiveMetric.h"
#include "CubeCustomPreDerivedInclusiveMetric.h"
#include "CubeError.h"
#include "CubeExclusiveMetric.h"
#include "CubeExclusiveMetricBuildInType.h"
#include "CubeFileFinder.h"
#include "CubeGeneralEvaluation.h"
#include "CubeIDdeliverer.h"
#include "CubeInclusiveMetric.h"
#include "CubeInclusiveMetricBuildInType.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeObjectsEnumerator.h"
#include "CubePLMemoryManager.h"
#include "CubePostDerivedMetric.h"
#include "CubePreDerivedExclusiveMetric.h"
#include "CubePreDerivedInclusiveMetric.h"
#include "CubeProxy.h"
#include "CubeRegion.h"
#include "CubeRowWiseMatrix.h"
#include "CubeServices.h"
#include "CubeSerializablesFactory.h"
#include "CubeStrategies.h"
#include "CubeSysres.h"
#include "CubeSystemTreeNode.h"
#include "CubeTypes.h"

using namespace std;
using namespace cube;
using namespace services;



double*
Metric::get_sevs( const Cnode*             cnode,
                  const CalculationFlavour cnf )
{
    list_of_cnodes lcnodes;
    cnode_pair     pair = std::make_pair( const_cast<Cnode*>( cnode ), cnf );
    lcnodes.push_back( pair );
    Value** _val      = get_sevs( lcnodes );
    double* to_return = services::create_row_of_doubles( ntid );
    for ( unsigned i = 0; i < ntid; ++i )
    {
        to_return[ i ] = _val[ i ]->getDouble();
    }
    services::delete_row_of_values( _val, ntid );
    return to_return;
}


void
Metric::set_sev( const Cnode*    cnode,
                 const Location* loc,
                 double          value )
{
    if ( cnode != NULL && loc != NULL && adv_sev_mat != NULL )
    {
        int64_t process_rank = loc->get_parent()->get_rank();
        adv_sev_mat->setValue( value, calltree_local_ids[ cnode->get_remapping_cnode( process_rank )->get_id() ], loc->get_id() );
    }
    else
    {
        cerr << " Something is wrong in Metric::set_sev(" << cnode << ", " << loc << ", " << value << ")" << endl;
    }
}


// /*
//
//
// Value*
// Metric::get_sev_adv( const list_of_cnodes& cnodes  )
// {
//     Value* to_return = adv_sev_mat->getValue();
//
//     for ( list_of_cnodes::const_iterator c_iter = cnodes.begin(); c_iter != cnodes.end(); ++c_iter )
//     {
//         cube::Cnode*             _cnode = c_iter->first;
//         cube::CalculationFlavour cf     = c_iter->second;
//         Value*                   _v     = get_sev_adv( _cnode, cf );
//         to_return->
//         operator+=( _v );
//
//         delete _v;
//     }
//     return to_return;
// }
//
// Value*
// Metric::get_sev_adv( const list_of_cnodes& cnodes,
//                      Sysres*               sys,
//                      CalculationFlavour    sf )
// {
//     Value* to_return = adv_sev_mat->getValue();
//
//     for ( list_of_cnodes::const_iterator c_iter = cnodes.begin(); c_iter != cnodes.end(); ++c_iter )
//     {
//         cube::Cnode*             _cnode = c_iter->first;
//         cube::CalculationFlavour cf     = c_iter->second;
//         Value*                   _v     = get_sev_adv( _cnode, cf, sys, sf );
//         to_return->
//         operator+=( _v );
//
//         delete _v;
//     }
//     return to_return;
// }
//
// Value**
// Metric::get_sevs_adv( const list_of_cnodes& cnodes
//                       )
// {
//     Value** to_return = NULL;
//
//     for ( list_of_cnodes::const_iterator c_iter = cnodes.begin(); c_iter != cnodes.end(); ++c_iter )
//     {
//         cube::Cnode*             _cnode = c_iter->first;
//         cube::CalculationFlavour cf     = c_iter->second;
//         Value**                  _v     = get_sevs_adv( _cnode, cf );
//         for ( unsigned i = 0; i < ntid; ++i )
//         {
//             if ( to_return == NULL )
//             {
//                 to_return[ i ] = _v[ i ];
//             }
//             else
//             {
//                 to_return[ i ]->
//                 operator+=( _v[ i ] );
//             }
//         }
//         services::delete_row_of_values( _v, ntid );
//     }
//     return to_return;
// }
//
//
//
//
// double
// Metric::get_sev( const list_of_cnodes& cnodes  )
// {
//     Value* _v        = get_sev_adv( cnodes );
//     double to_return = _v->getDouble();
//     _v->Free();
//     return to_return;
// }
//
// double
// Metric::get_sev( const list_of_cnodes& cnodes,
//                  Sysres*               sys,
//                  CalculationFlavour    sf )
// {
//     Value* _v        = get_sev_adv( cnodes, sys, sf );
//     double to_return = _v->getDouble();
//     _v->Free();
//     return to_return;
// }
//
// double*
// Metric::get_sevs( const list_of_cnodes& cnodes
//                   )
// {
//     Value** _v        = get_sevs_adv( cnodes );
//     double* to_return = services::create_row_of_doubles( ntid );
//     for ( uint64_t i = 0; i < ntid; i++ )
//     {
//         to_return[ i ] = _v[ i ]->getDouble();
//     }
//     services::delete_row_of_values( _v, ntid );
//     return to_return;
// }*/



// // /*
// //
// // double
// // Metric::get_sev( Cnode* cnode, Thread* thrd )
// // {
// //     double ret = 0.;
// //     Value* v   = get_sev_adv( cnode, thrd );
// //     if ( v == NULL )
// //     {
// //         return 0.;
// //     }
// //     ret = v->getDouble();
// //     v->Free();
// //     return ret;
// // }
// //
// //
// // Value*
// // Metric::get_sev_adv( Cnode* cnode, Thread* thrd )
// // {
// //     if ( adv_sev_mat != NULL )
// //     {
// //         Value*             v            =  metric_value->clone();
// //         int64_t            process_rank = thrd->get_parent()->get_rank();
// //         const cube::Cnode* _mapped      =  cnode->get_remapping_cnode( process_rank  );
// //         Value*             _v           = ( _mapped == NULL ) ? v->clone() : ( adv_sev_mat->getValue(
// //                                                                                    calltree_local_ids[ _mapped->get_id() ],
// //                                                                                    thrd->get_id() ) );
// //         int64_t _norm = cnode->get_cluster_normalization( process_rank );
// //         if ( ( _norm > 0 ) &&  ( _v != NULL ) )
// //         {
// //             _v->normalizeWithClusterCount( ( uint64_t )_norm );
// //         }
// //         v->Free();
// //         return _v;
// //     }
// //     Value* v =  metric_value->clone();
// //     return v;
// // }
// // */


// // //  --massive calculation of a system tree
// // void
// // Metric::get_system_tree_sevs_adv( const list_of_cnodes&  cnodes,
// //                                   std::vector< Value* >& inclusive_values,
// //                                   std::vector< Value* >& exclusive_values
// //                                   )
// // {
// //     list_of_cnodes::const_iterator c_iter = cnodes.begin();
// //     get_system_tree_sevs_adv( c_iter->first, c_iter->second, inclusive_values, exclusive_values );
// //
// //     for (; c_iter != cnodes.end(); ++c_iter )
// //     {
// //         std::vector< Value* > _inclusive_values;
// //         std::vector< Value* > _exclusive_values;
// //         get_system_tree_sevs_adv( c_iter->first, c_iter->second, _inclusive_values, _exclusive_values );
// //         for ( uint64_t i = 0; i < ntid; i++ )
// //         {
// //             inclusive_values[ i ]->
// //             operator+=( _inclusive_values[ i ] );
// //
// //             exclusive_values[ i ]->
// //             operator+=( _exclusive_values[ i ] );
// //
// //             _inclusive_values[ i ]->Free();
// //             _exclusive_values[ i ]->Free();
// //         }
// //     }
// // }
// //


// /*
// //  --massive calculation of a system tree
// void
// Metric::get_system_tree_sevs( const list_of_cnodes&  cnodes,
//                               std::vector< double >& inclusive_values,
//                               std::vector< double >& exclusive_values
//                               )
// {
//     list_of_cnodes::const_iterator c_iter = cnodes.begin();
//     get_system_tree_sevs( c_iter->first, c_iter->second, inclusive_values, exclusive_values );
//
//     for (; c_iter != cnodes.end(); ++c_iter )
//     {
//         std::vector< double > _inclusive_values;
//         std::vector< double > _exclusive_values;
//         get_system_tree_sevs( c_iter->first, c_iter->second, _inclusive_values, _exclusive_values );
//         for ( uint64_t i = 0; i < ntid; i++ )
//         {
//             inclusive_values[ i ] += ( _inclusive_values[ i ] );
//             exclusive_values[ i ] += ( _exclusive_values[ i ] );
//         }
//     }
// }*/


// /*
//
//
// //  --massive calculation of a system tree . stub
// void
// Metric::get_system_tree_sevs_adv( Cnode*               cnode,
//                                   CalculationFlavour   cnf,
//                                   std::vector<Value*>& inclusive_values,
//                                   std::vector<Value*>& exclusive_values
//                                   )
// {
//     inclusive_values.resize( sysresv.size(), NULL );
//     exclusive_values.resize( sysresv.size(), NULL );
//     Value** _locs = NULL;
//     if ( !isBuildIn() )
//     {
//         _locs = get_sevs_adv( cnode, cnf );
//     }
//     else
//     {
//         double* __tmp_locs =  get_sevs( cnode, cnf );
//         _locs = cube::services::create_row_of_values( ntid );
//         for ( size_t i = 0; i < ntid; ++i )
//         {
//             Value* _tmp_value = metric_value->clone();
//             _tmp_value->
//             operator=( ( __tmp_locs != NULL ) ? __tmp_locs[ i ] : 0. );
//
//             _locs[ i ] = _tmp_value;
//         }
//         cube::services::delete_raw_row( __tmp_locs );
//     }
//     // first copy locations
//     for ( size_t i = 0; i < ntid; ++i )
//     {
//         exclusive_values[ sysv[ i ]->get_sys_id() ] = _locs[ i ];
//         inclusive_values[ sysv[ i ]->get_sys_id() ] = _locs[ i ]->copy();
//     }
//     // set non-location elements to zero
//     for ( size_t i = 0; i < exclusive_values.size(); ++i )
//     {
//         if ( exclusive_values[ i ] == NULL )
//         {
//             exclusive_values[ i ] = metric_value->clone();
//         }
//         if ( inclusive_values[ i ] == NULL )
//         {
//             inclusive_values[ i ] = metric_value->clone();
//         }
//     }
//     if ( !isCustom() && get_type_of_metric() != cube::CUBE_METRIC_POSTDERIVED )
//     {
//         // calculate  location groups
//         for ( size_t i = 0; i < lgv.size(); ++i )
//         {
//             LocationGroup* lg = lgv[ i ];
//             for ( size_t j = 0; j < lg->num_children(); j++ )
//             {
//                 Location* _loc = lg->get_child( j );
//                 inclusive_values[ lg->get_sys_id() ]->operator+=( _locs[ _loc->get_id() ] );
//
//                 //add up to all parents ... need this coz of hybrid character of
//                 // the system tree model
//                 SystemTreeNode* _lg_parent = lg->get_parent();
//                 while ( _lg_parent != NULL )
//                 {
//                     inclusive_values[ _lg_parent->get_sys_id() ]->operator+=( _locs[ _loc->get_id() ] );
//                     _lg_parent = _lg_parent->get_parent();
//                 }
//             }
//         }
//     }
//     else
//     {
//         // calculate  location groups
//         for ( size_t i = 0; i < lgv.size(); ++i )
//         {
//             LocationGroup* lg = lgv[ i ];
//             inclusive_values[ lg->get_sys_id() ]->operator=( this->get_sev( cnode, cnf, lg, cube::CUBE_CALCULATE_INCLUSIVE ) );
//         }
//         for ( size_t i = 0; i < stnv.size(); ++i )
//         {
//             SystemTreeNode* stn = stnv[ i ];
//             inclusive_values[ stn->get_sys_id() ]->operator=( this->get_sev( cnode, cnf, stn, cube::CUBE_CALCULATE_INCLUSIVE ) );
//         }
//     }
//     return;
// }
//
//
// */




// // inclusive value and exclusive value in this metric are same
// //
// Value*
// Metric::get_sev_adv( Cnode* cnode, CalculationFlavour cnf, Sysres* sys, CalculationFlavour sf )
// {
//     Value* v = NULL;
//     v = adv_sev_mat->getValue( calltree_local_ids[ cnode->get_id() ], sys->get_id() );
//     return v;
// }
//
// // // // ---------------------- rowwise calls ---------------------
//
// // --------// inclusive value and exclusive value in this metric are same
// Value**
// Metric::get_sevs_adv( Cnode* cnode, CalculationFlavour cnf )
// {
//     if ( adv_sev_mat == NULL )
//     {
//         return NULL;
//     }
//     char* _v =   adv_sev_mat->getRow( calltree_local_ids[ cnode->get_id() ] );
//     if ( _v == NULL )
//     {
//         return NULL;
//     }
//     Value** to_return = services::create_row_of_values( ntid );
//     char*   start     = _v;
//     for ( unsigned i = 0; i < ntid; ++i )
//     {
//         Value* _val = metric_value->clone();
//         start = _val->fromStream( start );
//
//         int64_t _norm = cnode->get_cluster_normalization( sysv[ i ]->get_parent()->get_rank() );
//         if ( _norm > 0 )
//         {
//             _val->normalizeWithClusterCount( ( uint64_t )_norm );
//         }
//         to_return[ i ] = _val;
//     }
//     return to_return;
// }
//


/*
   double
   Metric::get_sev( Cnode* cnode, CalculationFlavour cnf, Sysres* sys, CalculationFlavour sf )
   {
    double ret = 0.;
    Value* v   = get_sev_adv( cnode, cnf, sys, sf );
    if ( v == NULL )
    {
        return 0.;
    }
    ret = v->getDouble();
    v->Free();
    return ret;
   }

   // inclusive value and exclusive value in this metric are same
   Value*
   Metric::get_sev_adv( Cnode* cnode, CalculationFlavour cnf )
   {
    Value* v =  metric_value->clone();
    for ( unsigned i = 0; i < ntid; ++i )
    {
        const cube::Cnode* _mapped =  cnode->get_remapping_cnode( sysv[ i ]->get_parent()->get_rank()   );
        Value*             _v      =    ( _mapped == NULL ) ? v->clone() : ( adv_sev_mat->getValue( calltree_local_ids[ _mapped->get_id() ], i ) );
        int64_t            _norm   = cnode->get_cluster_normalization( sysv[ i ]->get_parent()->get_rank() );
        if ( _norm > 0 )
        {
            _v->normalizeWithClusterCount( ( uint64_t )_norm );
        }
        v->
        operator+=( _v );

        _v->Free();
    }
    return v;
   }

 */


// double
// Metric::get_sev( Cnode* cnode, CalculationFlavour cnf )
// {
//     double ret = 0.;
//     Value* v   = get_sev_adv( cnode, cnf );
//     if ( v == NULL )
//     {
//         return 0.;
//     }
//     ret = v->getDouble();
//     v->Free();
//     return ret;
// }
//



/*

   double
   Metric::get_adv_sev( Cnode* cnode, Thread* thrd )
   {
    Value* v = get_adv_sev_adv( cnode, thrd );
    if ( v == NULL )
    {
        return 0.;
    }
    double d = v->getDouble();
    v->Free();
    return d;
   }*/

// // /*
// //
// //
// // Value*
// // Metric::get_adv_sev_adv( Cnode* cnode, Thread* thrd )
// // {
// //     if ( adv_sev_mat == NULL )
// //     {
// //         return NULL;
// //     }
// //     int64_t process_rank = thrd->get_parent()->get_rank();
// //     Value*  v            =  adv_sev_mat->getValue( calltree_local_ids[ cnode->get_remapping_cnode( process_rank )->get_id() ], thrd->get_id() );
// //     int64_t _norm        = cnode->get_cluster_normalization( process_rank );
// //     if ( _norm > 0 )
// //     {
// //         v->normalizeWithClusterCount( ( uint64_t )_norm );
// //     }
// //     return v;
// // }
// //
// //
// //
// // double
// // Metric::get_adv_sev( const Cnode*  cnode,
// //                      const Thread* thrd )
// // {
// //     Value* v = get_adv_sev_adv( cnode, thrd );
// //     if ( v == NULL )
// //     {
// //         return 0.;
// //     }
// //     double d = v->getDouble();
// //     v->Free();
// //     return d;
// // }
// //
// //
// // void
// // Metric::set_adv_sev( const Cnode*  cnode,
// //                      const Thread* thrd,
// //                      double        value )
// // {
// //     if ( cnode != NULL && thrd != NULL && adv_sev_mat != NULL )
// //     {
// //         int64_t process_rank = thrd->get_parent()->get_rank();
// //         adv_sev_mat->setValue( value, calltree_local_ids[ cnode->get_remapping_cnode( process_rank )->get_id() ], thrd->get_id() );
// //     }
// //     else
// //     {
// //         cerr << " Something is wrong in Metric::set_adv_set(" << cnode << ", " << thrd << ", " << value << ")" << endl;
// //     }
// // }
// //
// //
// // void
// // Metric::set_adv_sev_adv( const Cnode* cnode,
// //                          const Thread* thrd,
// //                          const Value* value )
// // {
// //     if ( cnode != NULL && thrd != NULL && adv_sev_mat != NULL )
// //     {
// //         int64_t process_rank = thrd->get_parent()->get_rank();
// //         adv_sev_mat->setValue( value, calltree_local_ids[ cnode->get_remapping_cnode( process_rank )->get_id() ], thrd->get_id() );
// //     }
// // }
// //
// //
// //
// //
// //
// // double
// // Metric::get_sev( const Cnode*             cnode,
// //             const CalculationFlavour cfv,
// //             const Sysres*            sys,
// //             const CalculationFlavour sf );
// //
// // // / Calculates inclusive value for given cnode and over all threads. Sums up over all threads. Assumed that all threads have continueos ids. Expands only calltree. Returns double representation of Value if possible.
// // double
// // Metric::get_sev( const Cnode*             cnode,
// //             const CalculationFlavour cfv );
// //
// // // /  Calculates inclusive value for given thread. Expands only calltree.
// // Value*
// // Metric::get_sev_adv( const Cnode*             cnode,
// //                 const CalculationFlavour cfv,
// //                 const Sysres*            sys,
// //                 const CalculationFlavour sf );
// //
// // // / Calculates inclusive value for given cnode and over all threads. Sums up over all threads. Assumed that all threads have continueos ids. Expands only calltree.
// // Value*
// // Metric::get_sev_adv( const Cnode*             cnode,
// //                 const CalculationFlavour cfv );
// //
// // Value**
// // Metric::get_sevs_adv(
// //     const Cnode*,
// //     const CalculationFlavour cfv
// //     );
// //
// // double*
// // Metric::get_sevs(
// //     const Cnode*,
// //     const CalculationFlavour cfv
// //     );
// //
// //
// //
// //
// //
// //
// //
// //
// //
// // // / ------------------------ Sum over all threads for given cnode and all subcnodes
// //
// //
double
Metric::get_sev( const Cnode*             cnode,
                 const CalculationFlavour cnf )
{
    double ret = 0.;
    Value* v   = get_sev_adv( cnode, cnf );
    if ( v == NULL )
    {
        return 0.;
    }
    ret = v->getDouble();
    v->Free();
    return ret;
}

Value*
Metric::get_sev_adv( const Cnode*             cnode,
                     const CalculationFlavour cnf )
{
    list_of_cnodes lcnodes;
    cnode_pair     cpair = std::make_pair( const_cast<Cnode*>( cnode ), cnf );
    lcnodes.push_back( cpair );
    list_of_sysresources lsysres;
    return get_sev( lcnodes, lsysres );
}

// //
// //
// //
double
Metric::get_sev( const Cnode*             cnode,
                 const CalculationFlavour cnf,
                 const Sysres*            sys,
                 const CalculationFlavour sf )
{
    double ret = 0.;
    Value* v   = get_sev_adv( cnode, cnf, sys, sf );
    if ( v == NULL )
    {
        return 0.;
    }
    ret = v->getDouble();
    v->Free();
    return ret;
}

Value*
Metric::get_sev_adv( const Cnode*             cnode,
                     const CalculationFlavour cnf,
                     const Sysres*            sys,
                     const CalculationFlavour sf )
{
    double         ret = 0.;
    list_of_cnodes lcnodes;
    cnode_pair     cpair = std::make_pair( const_cast<Cnode*>( cnode ), cnf );
    lcnodes.push_back( cpair );

    list_of_sysresources lsysres;
    sysres_pair          spair = std::make_pair( const_cast<Sysres*>( sys ), sf );
    lsysres.push_back( spair );

    return get_sev( lcnodes, lsysres );
}


// //
// //
// //
// // // // // ---------------------- rowwise calls ---------------------
// //
// // // --------// inclusive value and exclusive value in this metric are same
Value**
Metric::get_sevs_adv( const Cnode* cnode, const CalculationFlavour cnf )
{
    list_of_cnodes lcnodes;
    cnode_pair     pair;
    pair = std::make_pair( const_cast<Cnode*>( cnode ), cnf );
    lcnodes.push_back( pair );
    return get_sevs( lcnodes );
}
// //
// //
// //
// //
// //
// //
// //
// //
// //
// // //  --massive calculation of a system tree . stub
// // void
// // Metric::get_system_tree_sevs_adv( Cnode*               cnode,
// //                                   CalculationFlavour   cnf,
// //                                   std::vector<Value*>& inclusive_values,
// //                                   std::vector<Value*>& exclusive_values
// //                                   )
// // {
// //     inclusive_values.resize( sysresv.size(), NULL );
// //     exclusive_values.resize( sysresv.size(), NULL );
// //     Value** _locs = NULL;
// //     if ( !isBuildIn() )
// //     {
// //         _locs = get_sevs_adv( cnode, cnf );
// //     }
// //     else
// //     {
// //         double* __tmp_locs =  get_sevs( cnode, cnf );
// //         _locs = cube::services::create_row_of_values( ntid );
// //         for ( size_t i = 0; i < ntid; ++i )
// //         {
// //             Value* _tmp_value = metric_value->clone();
// //             _tmp_value->
// //             operator=( ( __tmp_locs != NULL ) ? __tmp_locs[ i ] : 0. );
// //
// //             _locs[ i ] = _tmp_value;
// //         }
// //         cube::services::delete_raw_row( __tmp_locs );
// //     }
// //     // first copy locations
// //     for ( size_t i = 0; i < ntid; ++i )
// //     {
// //         exclusive_values[ sysv[ i ]->get_sys_id() ] = _locs[ i ];
// //         inclusive_values[ sysv[ i ]->get_sys_id() ] = _locs[ i ]->copy();
// //     }
// //     // set non-location elements to zero
// //     for ( size_t i = 0; i < exclusive_values.size(); ++i )
// //     {
// //         if ( exclusive_values[ i ] == NULL )
// //         {
// //             exclusive_values[ i ] = metric_value->clone();
// //         }
// //         if ( inclusive_values[ i ] == NULL )
// //         {
// //             inclusive_values[ i ] = metric_value->clone();
// //         }
// //     }
// //     if ( !isCustom() && get_type_of_metric() != cube::CUBE_METRIC_POSTDERIVED )
// //     {
// //         // calculate  location groups
// //         for ( size_t i = 0; i < lgv.size(); ++i )
// //         {
// //             LocationGroup* lg = lgv[ i ];
// //             for ( size_t j = 0; j < lg->num_children(); j++ )
// //             {
// //                 Location* _loc = lg->get_child( j );
// //                 inclusive_values[ lg->get_sys_id() ]->operator+=( _locs[ _loc->get_id() ] );
// //
// //                 //add up to all parents ... need this coz of hybrid character of
// //                 // the system tree model
// //                 SystemTreeNode* _lg_parent = lg->get_parent();
// //                 while ( _lg_parent != NULL )
// //                 {
// //                     inclusive_values[ _lg_parent->get_sys_id() ]->operator+=( _locs[ _loc->get_id() ] );
// //                     _lg_parent = _lg_parent->get_parent();
// //                 }
// //             }
// //         }
// //     }
// //     else
// //     {
// //         // calculate  location groups
// //         for ( size_t i = 0; i < lgv.size(); ++i )
// //         {
// //             LocationGroup* lg = lgv[ i ];
// //             inclusive_values[ lg->get_sys_id() ]->operator=( this->get_sev( cnode, cnf, lg, cube::CUBE_CALCULATE_INCLUSIVE ) );
// //         }
// //         for ( size_t i = 0; i < stnv.size(); ++i )
// //         {
// //             SystemTreeNode* stn = stnv[ i ];
// //             inclusive_values[ stn->get_sys_id() ]->operator=( this->get_sev( cnode, cnf, stn, cube::CUBE_CALCULATE_INCLUSIVE ) );
// //         }
// //     }
// //     return;
// // }
// //
// // //  --massive calculation of a system tree. stub
// // void
// // Metric::get_system_tree_sevs( Cnode*               cnode,
// //                               CalculationFlavour   cnf,
// //                               std::vector<double>& inclusive_values,
// //                               std::vector<double>& exclusive_values
// //                               )
// // {
// //     inclusive_values.resize( sysresv.size(), 0. );
// //     exclusive_values.resize( sysresv.size(), 0. );
// //     vector<Value*>_inclusive_values;
// //     vector<Value*>_exclusive_values;
// //     get_system_tree_sevs_adv( cnode, cnf, _inclusive_values, _exclusive_values );
// //
// //     for ( size_t i = 0; i < exclusive_values.size(); ++i )
// //     {
// //         exclusive_values[ i ] = _exclusive_values[ i ]->getDouble();
// //         _exclusive_values[ i ]->Free();
// //     }
// //     for ( size_t i = 0; i < inclusive_values.size(); ++i )
// //     {
// //         inclusive_values[ i ] = _inclusive_values[ i ]->getDouble();
// //         _inclusive_values[ i ]->Free();
// //     }
// //     return;
// // }
// //
// //
// //
// //
// //
// //
// //
// //
// //
// //
// // Value**
// // Metric::get_saved_sevs_adv( Cnode* cnode )
// // {
// //     if ( adv_sev_mat == NULL )
// //     {
// //         return NULL;
// //     }
// //
// //     char* _v =   adv_sev_mat->getRow( calltree_local_ids[ cnode->get_id() ] );
// //     if ( _v == NULL )
// //     {
// //         return NULL;
// //     }
// //     Value** to_return = services::create_row_of_values( ntid );
// //     char*   start     = _v;
// //     for ( unsigned i = 0; i < ntid; ++i )
// //     {
// //         Value* _val = metric_value->clone();
// //         start = _val->fromStream( start );
// //
// //         int64_t _norm = cnode->get_cluster_normalization( sysv[ i ]->get_parent()->get_rank() );
// //         if ( _norm > 0 )
// //         {
// //             _val->normalizeWithClusterCount( ( uint64_t )_norm );
// //         }
// //         to_return[ i ] = _val;
// //     }
// //     return to_return;
// // }
// //
// //
// // char*
// // Metric::get_saved_sevs_raw( Cnode* cnode )
// // {
// //     if ( adv_sev_mat == NULL )
// //     {
// //         return NULL;
// //     }
// //
// //     return adv_sev_mat->getRow( calltree_local_ids[ cnode->get_id() ] );
// // }
// //
// //
// //
// //
// // double*
// // Metric::get_saved_sevs( Cnode* cnode )
// // {
// //     Value** _v        =   get_saved_sevs_adv( cnode );
// //     double* to_return = services::create_row_of_doubles( ntid );
// //     if ( _v == NULL )
// //     {
// //         return to_return;
// //     }
// //     for ( unsigned i = 0; i < ntid; ++i )
// //     {
// //         to_return[ i ] = _v[ i ]->getDouble();
// //     }
// //     services::delete_row_of_values( _v, ntid );
// //     return to_return;
// // }
// //
// //
// //
// //
// // // ------------------ adv part end -------------------
// //
// // double
// // Metric::get_sev( Cnode* cnode, Thread* thrd )
// // {
// //     double ret = 0.;
// //     Value* v   = get_sev_adv( cnode, thrd );
// //     if ( v == NULL )
// //     {
// //         return 0.;
// //     }
// //     ret = v->getDouble();
// //     v->Free();
// //     return ret;
// // }
// //
// //
// // Value*
// // Metric::get_sev_adv( const list_of_cnodes& cnodes  )
// // {
// //     Value* to_return = adv_sev_mat->getValue();
// //
// //     for ( list_of_cnodes::const_iterator c_iter = cnodes.begin(); c_iter != cnodes.end(); ++c_iter )
// //     {
// //         cube::Cnode*             _cnode = c_iter->first;
// //         cube::CalculationFlavour cf     = c_iter->second;
// //         Value*                   _v     = get_sev_adv( _cnode, cf );
// //         to_return->
// //         operator+=( _v );
// //
// //         delete _v;
// //     }
// //     return to_return;
// // }
// //
// // Value*
// // Metric::get_sev_adv( const list_of_cnodes& cnodes,
// //                      Sysres*               sys,
// //                      CalculationFlavour    sf )
// // {
// //     Value* to_return = adv_sev_mat->getValue();
// //
// //     for ( list_of_cnodes::const_iterator c_iter = cnodes.begin(); c_iter != cnodes.end(); ++c_iter )
// //     {
// //         cube::Cnode*             _cnode = c_iter->first;
// //         cube::CalculationFlavour cf     = c_iter->second;
// //         Value*                   _v     = get_sev_adv( _cnode, cf, sys, sf );
// //         to_return->
// //         operator+=( _v );
// //
// //         delete _v;
// //     }
// //     return to_return;
// // }
// //
// // Value**
// // Metric::get_sevs_adv( const list_of_cnodes& cnodes
// //                       )
// // {
// //     Value** to_return = NULL;
// //
// //     for ( list_of_cnodes::const_iterator c_iter = cnodes.begin(); c_iter != cnodes.end(); ++c_iter )
// //     {
// //         cube::Cnode*             _cnode = c_iter->first;
// //         cube::CalculationFlavour cf     = c_iter->second;
// //         Value**                  _v     = get_sevs_adv( _cnode, cf );
// //         for ( unsigned i = 0; i < ntid; ++i )
// //         {
// //             if ( to_return == NULL )
// //             {
// //                 to_return[ i ] = _v[ i ];
// //             }
// //             else
// //             {
// //                 to_return[ i ]->
// //                 operator+=( _v[ i ] );
// //             }
// //         }
// //         services::delete_row_of_values( _v, ntid );
// //     }
// //     return to_return;
// // }
// //
// //
// //
// //
// // double
// // Metric::get_sev( const list_of_cnodes& cnodes  )
// // {
// //     Value* _v        = get_sev_adv( cnodes );
// //     double to_return = _v->getDouble();
// //     _v->Free();
// //     return to_return;
// // }
// //
// // double
// // Metric::get_sev( const list_of_cnodes& cnodes,
// //                  Sysres*               sys,
// //                  CalculationFlavour    sf )
// // {
// //     Value* _v        = get_sev_adv( cnodes, sys, sf );
// //     double to_return = _v->getDouble();
// //     _v->Free();
// //     return to_return;
// // }
// //
// // double*
// // Metric::get_sevs( const list_of_cnodes& cnodes
// //                   )
// // {
// //     Value** _v        = get_sevs_adv( cnodes );
// //     double* to_return = services::create_row_of_doubles( ntid );
// //     for ( uint64_t i = 0; i < ntid; i++ )
// //     {
// //         to_return[ i ] = _v[ i ]->getDouble();
// //     }
// //     services::delete_row_of_values( _v, ntid );
// //     return to_return;
// // }*/
