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
 * \file Cube.cpp
 * \brief Defines methods of the class cube and IO-interface.
 *
 */

// PGI compiler replaces all ofstream.open() calls by open64 and then cannot find a propper one. Result -> compilation error
#if !defined( __PGI ) && !defined( __CRAYXT )  && !defined( __CRAYXE )
#define _FILE_OFFSET_BITS 64
#endif

#include "config.h"

#include  <cstdlib>
#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeValue.h"
#include "CubeMetric.h"
#include "CubeRegion.h"
#include "Cube.h"
#include "CubeServices.h"

using namespace std;
using namespace cube;





// ------------------- ANALYSIS PART --------------------------

Value**
Cube::get_sevs_adv( Metric*            metric,
                    CalculationFlavour mf,
                    Cnode*             cnode,
                    CalculationFlavour cnf )
{
    list_of_cnodes cnodes;
    cnode_pair     cpair;
    cpair.first  = cnode;
    cpair.second = cnf;
    cnodes.push_back( cpair );
    list_of_metrics metrics;
    metric_pair     mpair;
    mpair.first  = metric;
    mpair.second = mf;
    metrics.push_back( mpair );

    return get_sevs_adv( metrics, cnodes );
}

double*
Cube::get_sevs( Metric*            metric,
                CalculationFlavour mf,
                Cnode*             cnode,
                CalculationFlavour cnf )
{
    Value** v     = get_sevs_adv( metric, mf, cnode, cnf );
    double* v_ret = services::transform_values_to_doubles( v, locationv.size() );
    services::delete_row_of_values( v, locationv.size() );
    return v_ret;
}



char*
Cube::get_sevs_raw( Metric*            metric,
                    CalculationFlavour mf,
                    Cnode*             cnode,
                    CalculationFlavour cnf )
{
    Value** v     = get_sevs_adv( metric, mf, cnode, cnf );
    char*   v_ret = services::transform_values_to_raw( v, metric->its_value(), locationv.size() );
    services::delete_row_of_values( v, locationv.size() );
    return v_ret;
}



Value**
Cube::get_sevs_adv( Metric*            metric,
                    CalculationFlavour mf,
                    Region*            region,
                    CalculationFlavour rf )
{
    list_of_regions regions;
    region_pair     rpair;
    rpair.first  = region;
    rpair.second = rf;
    regions.push_back( rpair );
    list_of_cnodes  cnodes = cube::services::expand_regions( this, regions );
    list_of_metrics metrics;
    metric_pair     mpair;
    mpair.first  = metric;
    mpair.second = mf;
    metrics.push_back( mpair );
    return get_sevs_adv( metrics, cnodes );
}






double*
Cube::get_sevs( Metric* metric, CalculationFlavour mf, Region* region, CalculationFlavour rnf )
{
    Value** v     = get_sevs_adv( metric, mf, region, rnf );
    double* v_ret = services::transform_values_to_doubles( v, locationv.size() );
    services::delete_row_of_values( v, locationv.size() );
    return v_ret;
}

char*
Cube::get_sevs_raw( Metric*            metric,
                    CalculationFlavour mf,
                    Region*            region,
                    CalculationFlavour rf )
{
    Value** v     = get_sevs_adv( metric, mf, region, rf );
    char*   v_ret = services::transform_values_to_raw( v, metric->its_value(), locationv.size() );
    services::delete_row_of_values( v, locationv.size() );
    return v_ret;
}




// ------------------- aggregation over root cnodes -----------------------------


Value**
Cube::get_sevs_adv( Metric*            metric,
                    CalculationFlavour mf )
{
    list_of_cnodes            cnodes;
    std::vector<cube::Cnode*> croots = get_root_cnodev();
    for ( std::vector<cube::Cnode*>::const_iterator c_iter = croots.begin(); c_iter != croots.end(); ++c_iter )
    {
        cnode_pair cpair;
        cpair.first  = *c_iter;
        cpair.second = cube::CUBE_CALCULATE_INCLUSIVE;
        cnodes.push_back( cpair );
    }
    list_of_metrics metrics;
    metric_pair     mpair;
    mpair.first  = metric;
    mpair.second = mf;
    metrics.push_back( mpair );
    return get_sevs_adv( metrics, cnodes );
}

double*
Cube::get_sevs( Metric*            metric,
                CalculationFlavour mf )
{
    Value** v     = get_sevs_adv( metric, mf );
    double* v_ret = services::transform_values_to_doubles( v, locationv.size() );
    services::delete_row_of_values( v, locationv.size() );
    return v_ret;
}

char*
Cube::get_sevs_raw( Metric*            metric,
                    CalculationFlavour mf )
{
    Value** v     = get_sevs_adv( metric, mf );
    char*   v_ret = services::transform_values_to_raw( v, metric->its_value(), locationv.size() );
    services::delete_row_of_values( v, locationv.size() );
    return v_ret;
}
