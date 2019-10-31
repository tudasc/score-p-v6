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
#include "CubeError.h"
#include "CubeServices.h"
#include "Cube.h"


using namespace std;
using namespace cube;





// --- basic call... all other calls are mapped here ...

Value*
Cube::get_sev_adv( const list_of_metrics&      metrics,
                   const list_of_cnodes&       cnodes,
                   const list_of_sysresources& sysresources )
{
    if ( metrics.size() == 0 )
    {
        throw RuntimeError( "Error in calculation call  get_sev_adv(const list_of_metrics, const list_of_cnodes ,const list_of_sysresources): No metrics are specified. Empty list." );
    }
    if ( cnodes.size() == 0 )
    {
        return NULL;
    }
    Value* value = NULL;

    std::pair<list_of_metrics, list_of_metrics> reduced_metrics = cube::services::expand_metrics( metrics );

    value = reduced_metrics.first[ 0 ].first->get_sev( cnodes, sysresources );

    for ( unsigned i = 1; i < reduced_metrics.first.size(); i++ )
    {
        Value* _value = reduced_metrics.first[ i ].first->get_sev( cnodes, sysresources );
        value->
        operator+=( _value );

        _value->Free();
    }
    for ( unsigned i = 0; i < reduced_metrics.second.size(); i++ )
    {
        Value* _value = reduced_metrics.second[ i ].first->get_sev( cnodes, sysresources );
        value->
        operator-=( _value );

        _value->Free();
    }
    return value;
}

double
Cube::get_sev( const list_of_metrics&      metrics,
               const list_of_cnodes&       cnodes,
               const list_of_sysresources& sys_res )
{
    if ( metrics.size() == 0 )
    {
        return 0;
    }
    if ( cnodes.size() == 0 )
    {
        return 0;
    }
    if ( sys_res.size() == 0 )
    {
        return 0;
    }

    Value* v = get_sev_adv( metrics, cnodes, sys_res );
    if ( v == NULL )
    {
        return 0.;
    }
    double d = v->getDouble();
    v->Free();
    return d;
}








// --------------- calls with lists--------------------------------------------------------------------------------


Value*
Cube::get_sev_adv( const list_of_metrics& metrics, Cnode* cnode, CalculationFlavour cf )
{
    if ( metrics.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_metrics& metrics, Cnode* cnode, CalculationFlavour cf ): No metrics are specified. Empty list." );
    }
    if ( cnode == NULL )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_metrics& metrics, Cnode* cnode, CalculationFlavour cf ): No cnode is specified for the calculation." );
    }


    std::pair<list_of_metrics, list_of_metrics> reduced_metrics = cube::services::expand_metrics( metrics );
    list_of_cnodes                              cnodes;
    cnode_pair                                  pair;
    pair.first  = cnode;
    pair.second = cf;
    cnodes.push_back( pair );
    list_of_sysresources sysres; // empty

    return get_sev_adv( metrics, cnodes, sysres );
}



double
Cube::get_sev( const list_of_metrics& metrics, Cnode* cnode, CalculationFlavour cf )                                                                                              // sum over roots of calltree
{
    if ( metrics.size() == 0 )
    {
        return 0;
    }
    if ( cnode == NULL )
    {
        return 0;
    }
    Value* v = get_sev_adv( metrics, cnode,  cf );
    if ( v == NULL )
    {
        return 0.;
    }
    double d = v->getDouble();
    v->Free();
    return d;
}






Value*
Cube::get_sev_adv( const list_of_metrics& metrics, Region* region, CalculationFlavour rf )
{
    if ( metrics.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_metrics& metrics, Region* region, CalculationFlavour rf ): No metrics are specified. Empty list." );
    }
    if ( region == NULL )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_metrics& metrics, Region* region, CalculationFlavour rf ): No cnode is specified for the calculation." );
    }

    Value*          value = NULL;
    list_of_regions regions;
    region_pair     pair;
    pair.first  = region;
    pair.second = rf;
    regions.push_back( pair );
    list_of_cnodes       cnodes = cube::services::expand_regions( this, regions );
    list_of_sysresources sysres; // empty
    return get_sev_adv( metrics, cnodes, sysres );
}


double
Cube::get_sev( const list_of_metrics& metrics, Region* region, CalculationFlavour rf )                                                                                              // sum over roots of calltree
{
    if ( metrics.size() == 0 )
    {
        return 0;
    }
    if ( region == NULL )
    {
        return 0;
    }

    Value* v = get_sev_adv( metrics, region,  rf );
    if ( v == NULL )
    {
        return 0.;
    }
    double d = v->getDouble();
    v->Free();
    return d;
}





Value*
Cube::get_sev_adv( const list_of_metrics& metrics, Sysres* sysres, CalculationFlavour sf )
{
    if ( metrics.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_metrics& metrics, Sysres* sysres, CalculationFlavour sf ): No metrics are specified. Empty list." );
    }
    if ( sysres == NULL )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_metrics& metrics, Sysres* sysres, CalculationFlavour sf ): No system resource (machine, node, process or thread) is specified for the calculation." );
    }

    list_of_cnodes            cnodes;
    std::vector<cube::Cnode*> croots = get_root_cnodev();
    for ( std::vector<cube::Cnode*>::const_iterator c_iter = croots.begin(); c_iter != croots.end(); ++c_iter )
    {
        cnode_pair pair;
        pair.first  = *c_iter;
        pair.second = cube::CUBE_CALCULATE_INCLUSIVE;
        cnodes.push_back( pair );
    }

    list_of_sysresources sysresources;
    sysres_pair          pair;
    pair.first  = sysres;
    pair.second = sf;
    sysresources.push_back( pair );


    return get_sev_adv( metrics, cnodes, sysresources );
}



double
Cube::get_sev( const list_of_metrics& metrics, Sysres* sysres, CalculationFlavour sf )                                                                                              // sum over roots of calltree
{
    if ( metrics.size() == 0 )
    {
        return 0.;
    }
    if ( sysres == NULL )
    {
        return 0.;
    }
    Value* v = get_sev_adv( metrics, sysres,  sf );
    if ( v == NULL )
    {
        return 0.;
    }
    double d = v->getDouble();
    v->Free();
    return d;
}





Value*
Cube::get_sev_adv( const list_of_cnodes& cnodes, Metric* metric, CalculationFlavour mf )
{
    if ( cnodes.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_cnodes& cnodes, Metric* metric, CalculationFlavour mf ): No cnodes are specified. Empty list." );
    }
    if ( metric == NULL )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_cnodes& cnodes, Metric* metric, CalculationFlavour mf ):No metric is specified for the calculation" );
    }
    list_of_metrics metrics;
    metric_pair     pair;
    pair.first  = metric;
    pair.second = mf;
    metrics.push_back( pair );
    list_of_sysresources sysresources;
    return get_sev_adv( metrics, cnodes, sysresources );
}




double
Cube::get_sev( const list_of_cnodes& cnodes, Metric* metric, CalculationFlavour mf )                                                                                              // sum over roots of calltree
{
    if ( cnodes.size() == 0 )
    {
        return 0.;
    }
    if ( metric == NULL )
    {
        return 0;
    }
    Value* v = get_sev_adv( cnodes, metric,  mf );
    if ( v == NULL )
    {
        return 0.;
    }
    double d = v->getDouble();
    v->Free();
    return d;
}








double
Cube::get_sev( const list_of_cnodes&,
               Sysres*,
               CalculationFlavour )              // sum over roots of calltree
{
    return 0;                                    // any combination of that call return 0, coz metric is not specified
}






Value*
Cube::get_sev_adv( const list_of_regions& regions, Metric* metric, CalculationFlavour mf )
{
    if ( regions.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_regions& regions, Metric* metric, CalculationFlavour mf ): No regions are specified. Empty list." );
    }
    if ( metric == NULL )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_regions& regions, Metric* metric, CalculationFlavour mf ):No metric is specified for calculation" );
    }
    list_of_sysresources sysresources;
    list_of_cnodes       cnodes = cube::services::expand_regions( this, regions );
    list_of_metrics      metrics;
    metric_pair          pair;
    pair.first  = metric;
    pair.second = mf;
    metrics.push_back( pair );
    return get_sev_adv( metrics, cnodes, sysresources );
}

double
Cube::get_sev( const list_of_regions& regions, Metric* metric, CalculationFlavour mf )                                                                                              // sum over roots of calltree
{
    if ( regions.size() == 0 )
    {
        return 0.;
    }
    if ( metric == NULL )
    {
        return 0;
    }
    Value* v = get_sev_adv( regions, metric,  mf );
    if ( v == NULL )
    {
//         cerr << "get_sev_adv(regions, metric,  mf) returned NULL" << endl;
        return 0.;
    }
    double d = v->getDouble();
    v->Free();
    return d;
}








double
Cube::get_sev( const list_of_regions&,
               Sysres*,
               CalculationFlavour )
{
    return 0;                                                                                                                                                                 // any combination of that call return 0, coz metric is not specified
}





Value*
Cube::get_sev_adv( const list_of_sysresources& sysresources, Metric* metric, CalculationFlavour mf )
{
    if ( sysresources.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_sysresources& sysresources, Metric* metric, CalculationFlavour mf ): No system resources (machines, nodes, processes or lists) are specified. Empty list." );
    }
    if ( metric == NULL )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_sysresources& sysresources, Metric* metric, CalculationFlavour mf ):No metric is specified for the calculation" );
    }
    list_of_cnodes            cnodes;
    std::vector<cube::Cnode*> croots = get_root_cnodev();
    for ( std::vector<cube::Cnode*>::const_iterator c_iter = croots.begin(); c_iter != croots.end(); ++c_iter )
    {
        cnode_pair pair;
        pair.first  = *c_iter;
        pair.second = cube::CUBE_CALCULATE_INCLUSIVE;
        cnodes.push_back( pair );
    }
    list_of_metrics metrics;
    metric_pair     pair;
    pair.first  = metric;
    pair.second = mf;
    metrics.push_back( pair );
    return get_sev_adv( metrics, cnodes, sysresources );
}

double
Cube::get_sev( const list_of_sysresources& sysres, Metric* metric, CalculationFlavour mf )                                                                                              // sum over roots of calltree
{
    if ( sysres.size() == 0 )
    {
        return 0.;
    }
    if ( metric == NULL )
    {
        return 0;
    }
    Value* v = get_sev_adv( sysres, metric, mf );
    if ( v == NULL )
    {
        return 0.;
    }
    double d = v->getDouble();
    v->Free();
    return d;
}



double
Cube::get_sev( const list_of_sysresources&,
               Cnode*,
               CalculationFlavour )
{
    return 0.;                                                                                                                                                                  // any combination of that call return 0, coz metric is not specified
}


double
Cube::get_sev( const list_of_sysresources&,
               Region*,
               CalculationFlavour )
{
    return 0.;                                                                                                                                                                    // any combination of that call return 0, coz metric is not specified
}


// ------------------------- right panel ---------------------------------

Value*
Cube::get_sev_adv( const list_of_metrics& metrics, const list_of_cnodes& cnodes, Sysres* sys, CalculationFlavour sf )
{
    if ( metrics.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_metrics& metrics, const list_of_cnodes& cnodes, Sysres* sys, CalculationFlavour sf ): No metrics are specified. Empty list." );
    }
    if ( cnodes.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_metrics& metrics, const list_of_cnodes& cnodes, Sysres* sys, CalculationFlavour sf ): No cnodes are specified. Empty list." );
    }
    if ( sys == NULL )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_metrics& metrics, const list_of_cnodes& cnodes, Sysres* sys, CalculationFlavour sf ):No system resource (machine, node, process or thread) is specified for the calculation" );
    }
    list_of_sysresources sysresources;
    sysres_pair          pair;
    pair.first  = sys;
    pair.second = sf;
    sysresources.push_back( pair );
    return get_sev_adv( metrics, cnodes, sysresources );
}


double
Cube::get_sev( const list_of_metrics& metrics, const list_of_cnodes& cnodes, Sysres* sys, CalculationFlavour sf )                                                                                               // sum over roots of calltree
{
    if ( metrics.size() == 0 )
    {
        return 0;
    }
    if ( cnodes.size() == 0 )
    {
        return 0;
    }
    if ( sys == NULL )
    {
        return 0;
    }

    Value* v = get_sev_adv( metrics, cnodes, sys, sf );
    if ( v == NULL )
    {
//         cerr << "get_sev_adv(metrics, cnodes, sys, sf) returned NULL" << endl;
        return 0.;
    }
    double d = v->getDouble();
    v->Free();
    return d;
}




Value*
Cube::get_sev_adv( const list_of_metrics& metrics, const list_of_regions& regions, Sysres* sys, CalculationFlavour sf )
{
    if ( metrics.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_metrics& metrics, const list_of_regions& regions, Sysres* sys, CalculationFlavour sf ): No metrics are specified. Empty list." );
    }
    if ( regions.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_metrics& metrics, const list_of_regions& regions, Sysres* sys, CalculationFlavour sf ): No regions are specified. Empty list." );
    }
    if ( sys == NULL )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_metrics& metrics, const list_of_regions& regions, Sysres* sys, CalculationFlavour sf ):No system resource (machine, node, process or thread) is specified for the calculation" );
    }

    list_of_cnodes       cnodes = cube::services::expand_regions( this, regions );
    list_of_sysresources sysresources;
    sysres_pair          pair;
    pair.first  = sys;
    pair.second = sf;
    sysresources.push_back( pair );
    return get_sev_adv( metrics, cnodes, sysresources );
}

double
Cube::get_sev( const list_of_metrics& metrics, const list_of_regions& regions, Sysres* sys, CalculationFlavour sf )                                                                                               // sum over roots of calltree
{
    if ( metrics.size() == 0 )
    {
        return 0;
    }
    if ( regions.size() == 0 )
    {
        return 0;
    }
    if ( sys == NULL )
    {
        return 0;
    }

    Value* v = get_sev_adv( metrics, regions, sys, sf );
    if ( v == NULL )
    {
//         cerr << "get_sev_adv(metrics, regions, sys, sf) returned NULL" << endl;
        return 0.;
    }
    double d = v->getDouble();
    v->Free();
    return d;
}




Value*
Cube::get_sev_adv( const list_of_metrics& metrics, const list_of_sysresources& sysresources, Cnode* cnode, CalculationFlavour cf )
{
    if ( metrics.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_metrics& metrics, const list_of_sysresources& sysresources, Cnode* cnode, CalculationFlavour cf ): No metrics are specified. Empty list." );
    }
    if ( sysresources.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_metrics& metrics, const list_of_sysresources& sysresources, Cnode* cnode, CalculationFlavour cf ): No system resources (machines, nodes, processes  and threads) are specified. Empty list." );
    }
    if ( cnode == NULL )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_metrics& metrics, const list_of_sysresources& sysresources, Cnode* cnode, CalculationFlavour cf ):No cnode  is specified for the calculation" );
    }
    list_of_cnodes cnodes;
    cnode_pair     pair;
    pair.first  = cnode;
    pair.second = cf;
    cnodes.push_back( pair );

    return get_sev_adv( metrics, cnodes, sysresources );
}

double
Cube::get_sev( const list_of_metrics& metrics, const list_of_sysresources& sys_res, Cnode* cnode, CalculationFlavour cf )                                                                                               // sum over roots of calltree
{
    if ( metrics.size() == 0 )
    {
        return 0;
    }
    if ( sys_res.size() == 0 )
    {
        return 0;
    }
    if ( cnode == NULL )
    {
        return 0;
    }

    Value* v = get_sev_adv( metrics, sys_res, cnode, cf );
    if ( v == NULL )
    {
        return 0.;
    }
    double d = v->getDouble();
    v->Free();
    return d;
}






Value*
Cube::get_sev_adv( const list_of_metrics& metrics, const list_of_sysresources& sysresources, Region* region, CalculationFlavour rf )
{
    if ( metrics.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_metrics& metrics, const list_of_sysresources& sysresources, Region* region, CalculationFlavour rf ): No metrics are specified. Empty list." );
    }
    if ( region == NULL )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_metrics& metrics, const list_of_sysresources& sysresources, Region* region, CalculationFlavour rf ):No region is specified for the calculation" );
    }

    list_of_regions regions;
    region_pair     pair;
    pair.first  = region;
    pair.second = rf;
    regions.push_back( pair );
    list_of_cnodes cnodes = cube::services::expand_regions( this, regions );
    return get_sev_adv( metrics, cnodes, sysresources );
}

double
Cube::get_sev( const list_of_metrics& metrics, const list_of_sysresources& sys_res, Region* region, CalculationFlavour rf )                                                                                               // sum over roots of calltree
{
    if ( metrics.size() == 0 )
    {
        return 0;
    }
    if ( region == NULL )
    {
        return 0;
    }

    Value* v = get_sev_adv( metrics, sys_res, region, rf );
    if ( v == NULL )
    {
        return 0.;
    }
    double d = v->getDouble();
    v->Free();
    return d;
}






Value*
Cube::get_sev_adv( const list_of_cnodes& cnodes, const list_of_sysresources& sysresources, Metric* metric, CalculationFlavour mf )
{
    if ( cnodes.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_cnodes& cnodes, const list_of_sysresources& sysresources, Metric* metric, CalculationFlavour mf ): No cnodes are specified. Empty list." );
    }
    if ( sysresources.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_cnodes& cnodes, const list_of_sysresources& sysresources, Metric* metric, CalculationFlavour mf ): No system resources (machines, nodes, processes  and threads) are specified. Empty list." );
    }
    if ( metric == NULL )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_cnodes& cnodes, const list_of_sysresources& sysresources, Metric* metric, CalculationFlavour mf ):No metric is specified for the calculation." );
    }
    list_of_metrics metrics;
    metric_pair     pair;
    pair.first  = metric;
    pair.second = mf;
    metrics.push_back( pair );
    return get_sev_adv( metrics, cnodes, sysresources );
}

double
Cube::get_sev( const list_of_cnodes& cnodes, const list_of_sysresources& sys_res, Metric* metric, CalculationFlavour mf )                                                                                               // sum over roots of calltree
{
    if ( cnodes.size() == 0 )
    {
        return 0;
    }
    if ( sys_res.size() == 0 )
    {
        return 0;
    }
    if ( metric == NULL )
    {
        return 0;
    }

    Value* v = get_sev_adv( cnodes, sys_res, metric, mf );
    if ( v == NULL )
    {
        return 0.;
    }
    double d = v->getDouble();
    v->Free();
    return d;
}









Value*
Cube::get_sev_adv( const list_of_regions& regions, const list_of_sysresources& sysresources, Metric* metric, CalculationFlavour mf )
{
    if ( regions.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_regions& regions, const list_of_sysresources& sysresources, Metric* metric, CalculationFlavour mf ): No regions are specified. Empty list." );
    }
    if ( sysresources.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_regions& regions, const list_of_sysresources& sysresources, Metric* metric, CalculationFlavour mf ): No system resources (machines, nodes, processes  and threads) are specified. Empty list." );
    }
    if ( metric == NULL )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_regions& regions, const list_of_sysresources& sysresources, Metric* metric, CalculationFlavour mf ):No metric is specified for the calculation" );
    }
    list_of_metrics metrics;
    metric_pair     pair;
    pair.first  = metric;
    pair.second = mf;
    metrics.push_back( pair );
    list_of_cnodes cnodes = cube::services::expand_regions( this, regions );
    return get_sev_adv( metrics, cnodes, sysresources );
}

double
Cube::get_sev( const list_of_regions& regions, const list_of_sysresources& sys_res, Metric* metric, CalculationFlavour mf )                                                                                               // sum over roots of calltree
{
    if ( regions.size() == 0 )
    {
        return 0;
    }
    if ( sys_res.size() == 0 )
    {
        return 0;
    }
    if ( metric == NULL )
    {
        return 0;
    }

    Value* v = get_sev_adv( regions, sys_res, metric, mf );
    if ( v == NULL )
    {
        return 0.;
    }
    double d = v->getDouble();
    v->Free();
    return d;
}




Value*
Cube::get_sev_adv( const list_of_metrics& metrics,
                   const list_of_cnodes&  cnodes )
{
    if ( metrics.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_metrics& metrics, const list_of_cnodes&  cnodes ): No metrics are specified. Empty list." );
    }
    if ( cnodes.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_metrics& metrics, const list_of_cnodes&  cnodes ): No cnodes are specified. Empty list." );
    }

    list_of_sysresources sysresources;
    return get_sev_adv( metrics, cnodes, sysresources );
}
double
Cube::get_sev( const list_of_metrics& metrics,
               const list_of_cnodes&  cnodes )
{
    if ( metrics.size() == 0 )
    {
        return 0;
    }
    if ( cnodes.size() == 0 )
    {
        return 0;
    }

    Value* v = get_sev_adv( metrics, cnodes );
    if ( v == NULL )
    {
        return 0.;
    }
    double d = v->getDouble();
    v->Free();
    return d;
}



Value*
Cube::get_sev_adv( const list_of_metrics&      metrics,
                   const list_of_sysresources& sysresources )
{
    if ( metrics.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_metrics&      metrics, const list_of_sysresources& sysresources ): No metrics are specified. Empty list." );
    }
    if ( sysresources.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_metrics&      metrics, const list_of_sysresources& sysresources ): No system resources are specified. Empty list." );
    }


    list_of_cnodes            cnodes;
    std::vector<cube::Cnode*> croots = get_root_cnodev();
    for ( std::vector<cube::Cnode*>::const_iterator c_iter = croots.begin(); c_iter != croots.end(); ++c_iter )
    {
        cnode_pair pair;
        pair.first  = *c_iter;
        pair.second = cube::CUBE_CALCULATE_INCLUSIVE;
        cnodes.push_back( pair );
    }
    return get_sev_adv( metrics, cnodes, sysresources );
}



double
Cube::get_sev( const list_of_metrics&      metrics,
               const list_of_sysresources& sys_res )
{
    if ( metrics.size() == 0 )
    {
        return 0;
    }
    if ( sys_res.size() == 0 )
    {
        return 0;
    }

    Value* v = get_sev_adv( metrics, sys_res );
    if ( v == NULL )
    {
        return 0.;
    }
    double d = v->getDouble();
    v->Free();
    return d;
}




Value*
Cube::get_sev_adv( const list_of_cnodes&       cnodes,
                   const list_of_sysresources& sys_res )
{
    if ( cnodes.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_cnodes&       cnodes,const list_of_sysresources& sys_res ): No cnodes are specified. Empty list." );
    }
    if ( sys_res.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_cnodes&       cnodes,const list_of_sysresources& sys_res ): No system resources are specified. Empty list." );
    }
    return NULL;
}
double
Cube::get_sev( const list_of_cnodes&       cnodes,
               const list_of_sysresources& sys_res )
{
    if ( cnodes.size() == 0 )
    {
        return 0;
    }
    if ( sys_res.size() == 0 )
    {
        return 0;
    }

    Value* v = get_sev_adv( cnodes, sys_res );
    if ( v == NULL )
    {
        return 0.;
    }
    double d = v->getDouble();
    v->Free();
    return d;
}














Value*
Cube::get_sev_adv( const list_of_metrics& metrics )
{
    if ( metrics.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_metrics& metrics ): No metrics are specified. Empty list." );
    }
    list_of_cnodes            cnodes;
    std::vector<cube::Cnode*> croots = get_root_cnodev();
    for ( std::vector<cube::Cnode*>::const_iterator c_iter = croots.begin(); c_iter != croots.end(); ++c_iter )
    {
        cnode_pair pair;
        pair.first  = *c_iter;
        pair.second = cube::CUBE_CALCULATE_INCLUSIVE;
        cnodes.push_back( pair );
    }

    list_of_sysresources sysresources;
    return get_sev_adv( metrics, cnodes, sysresources );
}


double
Cube::get_sev( const list_of_metrics& metrics )
{
    if ( metrics.size() == 0 )
    {
        return 0;
    }


    Value* v = get_sev_adv( metrics );
    if ( v == NULL )
    {
        return 0.;
    }
    double d = v->getDouble();
    v->Free();
    return d;
}



Value*
Cube::get_sev_adv( const list_of_cnodes& cnodes )
{
    if ( cnodes.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_cnodes& cnodes ): No cnodes are spezified. Empty list." );
    }
    // here one has t ocheck if all root metrics do have same  uom and one can sum them up, but with warning... result might be meaningless
    return NULL;
}



double
Cube::get_sev( const list_of_cnodes& cnodes )
{
    if ( cnodes.size() == 0 )
    {
        return 0;
    }


    Value* v = get_sev_adv( cnodes );
    if ( v == NULL )
    {
//         cerr << "get_sev_adv(regions, sys_res, metric, mf) returned NULL" << endl;
        return 0.;
    }
    double d = v->getDouble();
    v->Free();
    return d;
}




Value*
Cube::get_sev_adv( const list_of_sysresources& sys_res )
{
    if ( sys_res.size() == 0 )
    {
        throw RuntimeError( "Cube::get_sev_adv( const list_of_sysresources& sys_res ): No sysres are spezified. Empty list." );
    }
    // here one has t ocheck if all root metrics do have same  uom and one can sum them up, but with warning... result might be meaningless
    return NULL;
}



double
Cube::get_sev( const list_of_sysresources& sys_res )
{
    if ( sys_res.size() == 0 )
    {
        return 0;
    }


    Value* v = get_sev_adv( sys_res );
    if ( v == NULL )
    {
//         cerr << "get_sev_adv(regions, sys_res, metric, mf) returned NULL" << endl;
        return 0.;
    }
    double d = v->getDouble();
    v->Free();
    return d;
}





// call with the list as an argument
void
Cube::get_system_tree_sevs_adv(  list_of_metrics&     metrics,
                                 list_of_regions&     regions,
                                 std::vector<Value*>& inclusive_values,
                                 std::vector<Value*>& exclusive_values
                                 )
{
    if ( metrics.size() == 0 )
    {
        throw RuntimeError( "Cube::get_system_tree_sevs_adv(  list_of_metrics&     metrics,list_of_regions&     regions,std::vector<Value*>& inclusive_values,std::vector<Value*>& exclusive_values): No metrics are spezified. Empty list." );
    }
    if ( regions.size() == 0 )
    {
        throw RuntimeError( "Cube::get_system_tree_sevs_adv(  list_of_metrics&     metrics,list_of_regions&     regions,std::vector<Value*>& inclusive_values,std::vector<Value*>& exclusive_values: No cnodes are spezified. Empty list." );
    }
    list_of_cnodes lcnodes = cube::services::expand_regions( this, regions );
    get_system_tree_sevs_adv( metrics, lcnodes, inclusive_values, exclusive_values );
}



// call with the list as an argument
void
Cube::get_system_tree_sevs_adv(  list_of_metrics&     metrics,
                                 list_of_cnodes&      cnodes,
                                 std::vector<Value*>& inclusive_values,
                                 std::vector<Value*>& exclusive_values
                                 )
{
    if ( metrics.size() == 0 )
    {
        throw RuntimeError( "Cube::get_system_tree_sevs_adv(  list_of_metrics&     metrics, list_of_cnodes&      cnodes, std::vector<Value*>& inclusive_values, std::vector<Value*>& exclusive_values): No metrics are spezified. Empty list." );
    }
    if ( cnodes.size() == 0 )
    {
        return;
    }
    std::vector<Value*>                         _tmp_inclusive_values;
    std::vector<Value*>                         _tmp_exclusive_values;
    std::pair<list_of_metrics, list_of_metrics> reduced_metrics = cube::services::expand_metrics( metrics );
    reduced_metrics.first[ 0 ].first->get_system_tree_sevs( cnodes, inclusive_values, exclusive_values );
    for ( unsigned i = 1; i < reduced_metrics.first.size(); i++ )
    {
        _tmp_inclusive_values.clear();
        _tmp_exclusive_values.clear();

        reduced_metrics.first[ i ].first->get_system_tree_sevs( cnodes, _tmp_inclusive_values, _tmp_exclusive_values );
        for ( size_t j = 0; j < _tmp_inclusive_values.size(); j++ )
        {
            inclusive_values[ j ]->
            operator+=( _tmp_inclusive_values[ j ] );

            _tmp_inclusive_values[ j ]->Free();
            exclusive_values[ j ]->
            operator+=( _tmp_exclusive_values[ j ] );

            _tmp_exclusive_values[ j ]->Free();
        }
    }
    for ( unsigned i = 0; i < reduced_metrics.second.size(); i++ )
    {
        _tmp_inclusive_values.clear();
        _tmp_exclusive_values.clear();
        reduced_metrics.second[ i ].first->get_system_tree_sevs( cnodes, _tmp_inclusive_values, _tmp_exclusive_values );
        for ( size_t j = 0; j < _tmp_inclusive_values.size(); j++ )
        {
            inclusive_values[ j ]->
            operator-=( _tmp_inclusive_values[ j ] );

            _tmp_inclusive_values[ j ]->Free();
            exclusive_values[ j ]->
            operator-=( _tmp_exclusive_values[ j ] );

            _tmp_exclusive_values[ j ]->Free();
        }
    }
}

// VErsion for the case, system tree pane is in the middle.
void
Cube::get_system_tree_sevs_adv( list_of_metrics&     metrics,
                                std::vector<Value*>& inclusive_values,
                                std::vector<Value*>& exclusive_values
                                )
{
    if ( metrics.size() == 0 )
    {
        throw RuntimeError( "Cube::get_system_tree_sevs_adv( list_of_metrics&     metrics, std::vector<Value*>& inclusive_values, std::vector<Value*>& exclusive_values ): No metrics are spezified. Empty list." );
    }
    std::pair<list_of_metrics, list_of_metrics> reduced_metrics = cube::services::expand_metrics( metrics );
    list_of_cnodes                              lcnodes;
    std::vector<cube::Cnode*>                   croots = get_root_cnodev();
    for ( std::vector<cube::Cnode*>::const_iterator c_iter = croots.begin(); c_iter != croots.end(); ++c_iter )
    {
        cnode_pair pair;
        pair.first  = *c_iter;
        pair.second = cube::CUBE_CALCULATE_INCLUSIVE;
        lcnodes.push_back( pair );
    }
    get_system_tree_sevs_adv( metrics, lcnodes, inclusive_values, exclusive_values );
}




// call with the list as an argument
void
Cube::get_system_tree_sevs(  list_of_metrics&     metrics,
                             list_of_regions&     regions,
                             std::vector<double>& inclusive_values,
                             std::vector<double>& exclusive_values
                             )
{
    if ( metrics.size() == 0 )
    {
        throw RuntimeError( "Cube::get_system_tree_sevs(  list_of_metrics&     metrics, list_of_regions&     regions, std::vector<double>& inclusive_values, std::vector<double>& exclusive_values ): No metrics are spezified. Empty list." );
    }
    if ( regions.size() == 0 )
    {
        return;
    }
    list_of_cnodes lcnodes = cube::services::expand_regions( this, regions );
    get_system_tree_sevs( metrics, lcnodes, inclusive_values, exclusive_values );
}

// call with the list as an argument
void
Cube::get_system_tree_sevs(  list_of_metrics&     metrics,
                             list_of_cnodes&      cnodes,
                             std::vector<double>& inclusive_values,
                             std::vector<double>& exclusive_values
                             )
{
    if ( metrics.size() == 0 )
    {
        throw RuntimeError( "Cube::get_system_tree_sevs(  list_of_metrics&     metrics, list_of_cnodes&      cnodes, std::vector<double>& inclusive_values, std::vector<double>& exclusive_values ): No metrics are spezified. Empty list." );
    }
    if ( cnodes.size() == 0 )
    {
        return;
    }

    std::vector<double>                         _tmp_inclusive_values;
    std::vector<double>                         _tmp_exclusive_values;
    std::pair<list_of_metrics, list_of_metrics> reduced_metrics = cube::services::expand_metrics( metrics );
    reduced_metrics.first[ 0 ].first->get_system_tree_sevs( cnodes, inclusive_values, exclusive_values );
    for ( unsigned i = 1; i < reduced_metrics.first.size(); i++ )
    {
        _tmp_inclusive_values.clear();
        _tmp_exclusive_values.clear();
        reduced_metrics.first[ i ].first->get_system_tree_sevs( cnodes, _tmp_inclusive_values, _tmp_exclusive_values );
        for ( size_t j = 0; j < _tmp_inclusive_values.size(); j++ )
        {
            inclusive_values[ j ] += ( _tmp_inclusive_values[ j ] );
            exclusive_values[ j ] += ( _tmp_exclusive_values[ j ] );
        }
    }
    for ( unsigned i = 0; i < reduced_metrics.second.size(); i++ )
    {
        _tmp_inclusive_values.clear();
        _tmp_exclusive_values.clear();
        reduced_metrics.second[ i ].first->get_system_tree_sevs( cnodes, _tmp_inclusive_values, _tmp_exclusive_values );
        for ( size_t j = 0; j < _tmp_inclusive_values.size(); j++ )
        {
            inclusive_values[ j ] -= ( _tmp_inclusive_values[ j ] );
            exclusive_values[ j ] -= ( _tmp_exclusive_values[ j ] );
        }
    }
}

// VErsion for the case, system tree pane is in the middle.
void
Cube::get_system_tree_sevs( list_of_metrics&     metrics,
                            std::vector<double>& inclusive_values,
                            std::vector<double>& exclusive_values
                            )
{
    if ( metrics.size() == 0 )
    {
        throw RuntimeError( "Cube::get_system_tree_sevs( list_of_metrics&     metrics, std::vector<double>& inclusive_values, std::vector<double>& exclusive_values ): No metrics are spezified. Empty list." );
    }
    list_of_cnodes           lcnodes;
    std::vector<cube::Cnode*>croots = get_root_cnodev();
    for ( std::vector<cube::Cnode*>::const_iterator c_iter = croots.begin(); c_iter != croots.end(); ++c_iter )
    {
        cnode_pair pair;
        pair.first  = *c_iter;
        pair.second = cube::CUBE_CALCULATE_INCLUSIVE;
        lcnodes.push_back( pair );
    }
    get_system_tree_sevs( metrics, lcnodes, inclusive_values, exclusive_values );
}
