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
 * \file Cube.cpp
 * \brief Defines methods of the class cube and IO-interface.
 *
 */

// PGI compiler replaces all ofstream.open() calls by open64 and then cannot find a propper one. Result -> compilation error
#if !defined( __PGI ) && !defined( __CRAYXT )  && !defined( __CRAYXE )
#define _FILE_OFFSET_BITS 64
#endif


#include "config.h"
#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeValue.h"
#include "CubeMetric.h"
#include "CubeRegion.h"
#include "Cube.h"
#include "CubeServices.h"

using namespace std;
using namespace cube;






// --------------- calls with lists--------------------------------------------------------------------------------




Value**
Cube::get_sevs_adv( const list_of_metrics& metrics,
                    const list_of_cnodes&  cnodes )
{
    if ( metrics.size() == 0 )
    {
        throw RuntimeError( "Error in calculation call  get_sevs_adv(list_of_metrics, list_of_cnodes): No metrics are spezified. Empty list." );
    }
    if ( cnodes.size() == 0 )
    {
        return NULL;
    }
    Value** value = NULL;

    std::pair<list_of_metrics, list_of_metrics> reduced_metrics = cube::services::expand_metrics( metrics );

    value = reduced_metrics.first[ 0 ].first->get_sevs( cnodes );

    for ( unsigned i = 1; i < reduced_metrics.first.size(); i++ )
    {
        Value** _value = reduced_metrics.first[ i ].first->get_sevs( cnodes );
        for ( size_t i = 0; i < locationv.size(); ++i )
        {
            Value* __v = _value[ i ];
            if ( __v != NULL )
            {
                value[ i ]->
                operator+=( __v );
            }
        }
        services::delete_row_of_values( _value, locationv.size() );
    }
    for ( unsigned i = 0; i < reduced_metrics.second.size(); i++ )
    {
        Value** _value = reduced_metrics.second[ i ].first->get_sevs( cnodes );
        for ( size_t i = 0; i < locationv.size(); ++i )
        {
            Value* __v = _value[ i ];
            if ( __v != NULL )
            {
                value[ i ]->
                operator-=( __v );
            }
        }
        services::delete_row_of_values( _value, locationv.size() );
    }
    return value;
}


double*
Cube::get_sevs( list_of_metrics& metrics,
                list_of_cnodes&  cnodes )
{
    Value** v     = get_sevs_adv( metrics, cnodes );
    double* v_ret = services::transform_values_to_doubles( v, locationv.size() );
    services::delete_row_of_values( v, locationv.size() );       // == delete[] _v;
    return v_ret;
}

Value**
Cube::get_sevs_adv( list_of_metrics& metrics )
{
    list_of_cnodes            cnodes;
    std::vector<cube::Cnode*> croots = get_root_cnodev();
    for ( std::vector<cube::Cnode*>::const_iterator c_iter = croots.begin(); c_iter != croots.end(); ++c_iter )
    {
        cnode_pair pair;
        pair.first  = *c_iter;
        pair.second = cube::CUBE_CALCULATE_INCLUSIVE;
        cnodes.push_back( pair );
    }
    return get_sevs_adv( metrics, cnodes );
}

double*
Cube::get_sevs( list_of_metrics& metrics )
{
    Value** v     = get_sevs_adv( metrics );
    double* v_ret = services::transform_values_to_doubles( v, locationv.size() );
    services::delete_row_of_values( v, locationv.size() );    // == delete[] _v;
    return v_ret;
}
