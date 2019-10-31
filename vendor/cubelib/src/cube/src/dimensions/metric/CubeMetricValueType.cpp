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
 * \file CubeMetricValueType.cpp
 * \brief Defines methods to calculate incl/exclusve values if the metric contains only general values

 ********************************************/


#include "config.h"
#include <iostream>
#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"

#include "CubeMetricValueType.h"
#include "CubeServices.h"


using namespace std;
using namespace cube;


Value*
ValueMetric::get_sev_native(
    const list_of_cnodes&       cnodes,
    const list_of_sysresources& sysres
    )
{
    Value* to_return = metric_value->clone();
    if ( sysres.size() == 0 ) // aggregation version
    {
        for ( list_of_cnodes::const_iterator c_iter = cnodes.begin(); c_iter != cnodes.end(); ++c_iter )
        {
            Value* _v = get_sev_native( c_iter->first,
                                        c_iter->second );
            to_return->
            operator+=( _v );

            _v->Free();
        }
    }
    else
    {
        list_of_sysresources _locs = services::expand_sys_resources( sysres );
        for ( list_of_cnodes::const_iterator c_iter = cnodes.begin(); c_iter != cnodes.end(); ++c_iter )
        {
            for ( list_of_sysresources::const_iterator s_iter = _locs.begin(); s_iter != _locs.end(); ++s_iter )
            {
                Value* _v = get_sev_native( c_iter->first,
                                            c_iter->second,
                                            s_iter->first,
                                            s_iter->second );
                to_return->
                operator+=( _v );

                _v->Free();
            }
        }
    }
    return to_return;
}

// -----------------row wise ----------------------------------------

Value**
ValueMetric::get_sevs_native( const cube::Cnode*       cnode,
                              const CalculationFlavour cnf
                              )
{
    Value** to_return = services::create_row_of_values( ntid );
    for ( unsigned i = 0; i < ntid; ++i )
    {
        cube::Sysres* sysres = sysv[ i ];

        Value* _val = get_sev_native( cnode, cnf, sysres, cube::CUBE_CALCULATE_INCLUSIVE );
        to_return[ i ] = _val;
    }
    return to_return;
}






Value**
ValueMetric::get_sevs_native(
    const list_of_cnodes& cnodes
    )
{
    list_of_cnodes::const_iterator c_iter    = cnodes.begin();
    Value**                        to_return = get_sevs_native( c_iter->first, c_iter->second );
    ++c_iter;
    for (; c_iter != cnodes.end(); ++c_iter )
    {
        Value** row = get_sevs_native( c_iter->first, c_iter->second );

        for ( uint64_t i = 0; i < ntid; i++ )
        {
            to_return[ i ]->
            operator+=( row[ i ] );
        }
        services::delete_row_of_values( row, ntid );
    }
    return to_return;
}



//  --massive calculation of a system tree

void
ValueMetric::get_system_tree_sevs(    const list_of_cnodes&  cnodes,
                                      std::vector< double >& inclusive_values,
                                      std::vector< double >& exclusive_values
                                      )
{
    inclusive_values.resize( sysresv.size(), 0. );
    exclusive_values.resize( sysresv.size(), 0. );
    vector<Value*>_inclusive_values;
    vector<Value*>_exclusive_values;
    get_system_tree_sevs_native( cnodes, _inclusive_values, _exclusive_values );

    for ( size_t i = 0; i < exclusive_values.size(); ++i )
    {
        exclusive_values[ i ] = _exclusive_values[ i ]->getDouble();
        _exclusive_values[ i ]->Free();
    }
    for ( size_t i = 0; i < inclusive_values.size(); ++i )
    {
        inclusive_values[ i ] = _inclusive_values[ i ]->getDouble();
        _inclusive_values[ i ]->Free();
    }
    return;
}





void
ValueMetric::get_system_tree_sevs_native(    const list_of_cnodes&  cnodes,
                                             std::vector< Value* >& inclusive_values,
                                             std::vector< Value* >& exclusive_values
                                             )
{
    list_of_cnodes::const_iterator c_iter = cnodes.begin();
    get_system_tree_sevs_native( c_iter->first, c_iter->second, inclusive_values, exclusive_values );
    ++c_iter;
    for (; c_iter != cnodes.end(); ++c_iter )
    {
        std::vector< Value* > _inclusive_values;
        std::vector< Value* > _exclusive_values;
        get_system_tree_sevs_native( c_iter->first, c_iter->second, _inclusive_values, _exclusive_values );
        for ( uint64_t i = 0; i < ntid; i++ )
        {
            inclusive_values[ i ]->
            operator+=( _inclusive_values[ i ] );

            exclusive_values[ i ]->
            operator+=( _exclusive_values[ i ] );

            _inclusive_values[ i ]->Free();
            _exclusive_values[ i ]->Free();
        }
    }
}


//  --massive calculation of a system tree

void
ValueMetric::get_system_tree_sevs_native(
    const cube::Cnode*       cnode,
    const CalculationFlavour cnf,
    std::vector< Value* >&   inclusive_values,
    std::vector< Value* >&   exclusive_values
    )
{
    inclusive_values.resize( sysresv.size(), NULL );
    exclusive_values.resize( sysresv.size(), NULL );
    Value** _locs = get_sevs_native( cnode, cnf );
    // first copy locations
    for ( size_t i = 0; i < ntid; ++i )
    {
        exclusive_values[ sysv[ i ]->get_sys_id() ] = _locs[ i ];
        inclusive_values[ sysv[ i ]->get_sys_id() ] = _locs[ i ]->copy();
    }
    // set non-location elements to zero
    for ( size_t i = 0; i < exclusive_values.size(); ++i )
    {
        if ( exclusive_values[ i ] == NULL )
        {
            exclusive_values[ i ] = metric_value->clone();
        }
        if ( inclusive_values[ i ] == NULL )
        {
            inclusive_values[ i ] = metric_value->clone();
        }
    }
    // calculate  location groups
    for ( size_t i = 0; i < lgv.size(); ++i )
    {
        LocationGroup* lg = lgv[ i ];
        for ( size_t j = 0; j < lg->num_children(); j++ )
        {
            Location* _loc = lg->get_child( j );
            inclusive_values[ lg->get_sys_id() ]->operator+=( _locs[ _loc->get_id() ] );

            //add up to all parents ... need this coz of hybrid character of
            // the system tree model
            SystemTreeNode* _lg_parent = lg->get_parent();
            while ( _lg_parent != NULL )
            {
                inclusive_values[ _lg_parent->get_sys_id() ]->operator+=( _locs[ _loc->get_id() ] );
                _lg_parent = _lg_parent->get_parent();
            }
        }
    }
    return;
}
