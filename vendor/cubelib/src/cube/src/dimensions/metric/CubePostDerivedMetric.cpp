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
 * \file CubePostDerivedMetric.cpp
 * \brief Defines methods to calculate incl/exclusve values if the metric is defined as an expression

 ********************************************/


#include "config.h"
#include <iostream>
#include <cassert>
#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"
#include "CubePostDerivedMetric.h"
#include "CubeServices.h"

using namespace std;
using namespace cube;


PostDerivedMetric::~PostDerivedMetric()
{
}


void
PostDerivedMetric::initialize( void )
{
    if ( evaluation != NULL )
    {
        evaluation->setRowSize( ntid );
    }
    if ( init_evaluation != NULL )
    {
        init_evaluation->setRowSize( ntid );
        init_evaluation->eval();
        delete init_evaluation;
        init_evaluation = NULL;
    }
}


double
PostDerivedMetric::aggr_operator( double a, double b ) const
{
    if ( aggr_aggr_evaluation != NULL )
    {
        return aggr_aggr_evaluation->eval( a, b );
    }
    else
    {
        return a + b;
    }
}



double
PostDerivedMetric::get_sev_native(
    const list_of_cnodes&       cnodes,
    const list_of_sysresources& sysres
    )
{
    double to_return = 0;
    if ( !active ) //  if value == VOID
    {
        return to_return;
    }
    if ( aggr_aggr_evaluation == NULL  )
    {
        pre_calculation_preparation( cnodes, sysres );
        if ( evaluation != NULL )
        {
            to_return = evaluation->eval( cnodes, sysres );
        }
        post_calculation_cleanup();
    }
    else  // we specified aggr operator
    {
        list_of_sysresources _sysres;
        if ( sysres.size() == 0 )
        {
            for ( size_t i = 0; i < sysv.size(); ++i )
            {
                sysres_pair pair;
                pair.first  = sysv[ i ];
                pair.second = cube::CUBE_CALCULATE_INCLUSIVE;
                _sysres.push_back( pair );
            }
        }
        else
        {
            _sysres = sysres;
        }
        for ( list_of_sysresources::const_iterator siter = _sysres.begin(); siter != _sysres.end(); ++siter )
        {
            list_of_sysresources __sysres;
            __sysres.push_back( *siter );
            pre_calculation_preparation( cnodes, __sysres );
            double _to_return = 0.;
            if ( evaluation != NULL )
            {
                _to_return = evaluation->eval( cnodes, __sysres );
            }
            to_return = aggr_aggr_evaluation->eval( to_return, _to_return );
            post_calculation_cleanup();
        }
    }
    return to_return;
}

// -----------------row wise ----------------------------------------
double*
PostDerivedMetric::get_sevs_native(
    const list_of_cnodes& cnodes
    )
{
    double* to_return = NULL;
    if ( !active ) //  if value == VOID
    {
        return to_return;
    }
    pre_calculation_preparation( cnodes );
    list_of_sysresources sysres;

    if ( evaluation != NULL )
    {
        to_return = evaluation->eval_row( cnodes, sysres );
    }
    post_calculation_cleanup();
    return to_return;
}

//  --massive calculation of a system tree
void
PostDerivedMetric::get_system_tree_sevs_native( const list_of_cnodes&  cnodes,
                                                std::vector< double >& inclusive_values,
                                                std::vector< double >& exclusive_values
                                                )
{
    double* to_return = NULL;
    if ( !active ) //  if value == VOID
    {
        return;
    }
    pre_calculation_preparation( cnodes );


    inclusive_values.resize( sysresv.size(), 0. );
    exclusive_values.resize( sysresv.size(), 0. );

    list_of_sysresources sysres;

    if ( evaluation != NULL )
    {
        to_return = evaluation->eval_row( cnodes, sysres );

        pre_calculation_preparation( cnodes );
        for ( size_t i = 0; i < ntid; ++i )
        {
            exclusive_values[ sysv[ i ]->get_sys_id() ] = to_return[ i ];
            inclusive_values[ sysv[ i ]->get_sys_id() ] = to_return[ i ];
        }
        post_calculation_cleanup();
        for ( size_t i = 0; i < lgv.size(); ++i )
        {
            LocationGroup* lg = lgv[ i ];
            if ( aggr_aggr_evaluation == NULL )
            {
                sysres.clear();
                sysres_pair pair;
                pair.first  = lg;
                pair.second = cube::CUBE_CALCULATE_INCLUSIVE;
                sysres.push_back( pair );
                pre_calculation_preparation( cnodes, sysres );
                double to_return_incl = evaluation->eval( cnodes, sysres  );
                post_calculation_cleanup();
                sysres.clear();
                pair.first  = lg;
                pair.second = cube::CUBE_CALCULATE_EXCLUSIVE;
                sysres.push_back( pair );
                pre_calculation_preparation( cnodes, sysres );
                double to_return_excl = evaluation->eval( cnodes, sysres  );
                post_calculation_cleanup();
                exclusive_values[ lg->get_sys_id() ] = to_return_excl;
                inclusive_values[ lg->get_sys_id() ] = to_return_incl;
            }
            else
            {
                for ( size_t s = 0; s <= lgv[ i ]->num_children(); ++s )
                {
                    cube::Location* _loc = lgv[ i ]->get_child( s );
                    exclusive_values[ lg->get_sys_id() ] = aggr_operator( exclusive_values[ lg->get_sys_id() ], exclusive_values[ _loc->get_sys_id() ] );
                    inclusive_values[ lg->get_sys_id() ] = aggr_operator( inclusive_values[ lg->get_sys_id() ], inclusive_values[ _loc->get_sys_id() ] );
                }
            }
        }
        for ( size_t i = 0; i < stnv.size(); ++i )
        {
            SystemTreeNode* stn = stnv[ i ];
            if ( aggr_aggr_evaluation == NULL )
            {
                sysres.clear();
                sysres_pair pair;
                pair.first  = stn;
                pair.second = cube::CUBE_CALCULATE_INCLUSIVE;
                sysres.push_back( pair );
                pre_calculation_preparation( cnodes, sysres );
                double to_return_incl = evaluation->eval( cnodes, sysres  );
                post_calculation_cleanup();
                pair.first  = stn;
                pair.second = cube::CUBE_CALCULATE_EXCLUSIVE;
                sysres.clear();
                sysres.push_back( pair );
                pre_calculation_preparation( cnodes, sysres );
                double to_return_excl = evaluation->eval( cnodes, sysres  );
                post_calculation_cleanup();
                exclusive_values[ stn->get_sys_id() ] = to_return_excl;
                inclusive_values[ stn->get_sys_id() ] = to_return_incl;
            }
            else
            {
                std::vector<Sysres*>& locs = stn->get_all_locations();
                for ( std::vector<Sysres*>::iterator siter = locs.begin(); siter != locs.end(); ++siter )
                {
                    cube::Location* _loc = static_cast<cube::Location*>( *siter );
                    exclusive_values[ stn->get_sys_id() ] = aggr_operator( exclusive_values[ stn->get_sys_id() ], exclusive_values[ _loc->get_sys_id() ] );
                    inclusive_values[ stn->get_sys_id() ] = aggr_operator( inclusive_values[ stn->get_sys_id() ], inclusive_values[ _loc->get_sys_id() ] );
                }
            }
        }
    }
    return;
}






Serializable*
cube::PostDerivedMetric::create( Connection&      connection,
                                 const CubeProxy& cubeProxy )
{
    return new PostDerivedMetric( connection, cubeProxy );
}

std::string
cube::PostDerivedMetric::get_serialization_key() const
{
    return get_static_serialization_key();
}

std::string
cube::PostDerivedMetric::get_static_serialization_key()
{
    return "PostDerivedMetric";
}

cube::PostDerivedMetric::PostDerivedMetric( Connection&      connection,
                                            const CubeProxy& cubeProxy )
    : BuildInTypeMetric<double>( connection, cubeProxy )
{
}
