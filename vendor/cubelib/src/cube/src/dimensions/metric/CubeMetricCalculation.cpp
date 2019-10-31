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
 * \file CubeMetricCalls.cpp
 * \brief Defines a depricated calls methods of a Metric

 ********************************************/

#include "config.h"

#include "CubeMetric.h"

#include <cassert>
#include <iostream>

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


void
Metric::set_sev( const Cnode*    cnode,
                 const Location* loc,
                 const Value*    value )
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

void
Metric::set_sevs_raw( const Cnode* cnode,
                      char*        _val
                      )
{
    if ( adv_sev_mat == NULL )
    {
        return;
    }
    adv_sev_mat->setRow( _val, calltree_local_ids[ cnode->get_id() ] );
}


char*
Metric::get_sevs_raw( const Cnode*             cnode,
                      const CalculationFlavour cnf  )
{
    return reinterpret_cast<char*>( get_sevs( cnode, cnf ) );
}



char*
Metric::get_saved_sevs_raw( const Cnode* cnode )
{
    if ( adv_sev_mat == NULL )
    {
        return NULL;
    }

    return adv_sev_mat->getRow( calltree_local_ids[ cnode->get_id() ] );
}


double*
Metric::get_saved_sevs( const Cnode* cnode )
{
    Value** _v        =   get_saved_sevs_adv( cnode );
    double* to_return = services::create_row_of_doubles( ntid );
    if ( _v == NULL )
    {
        return to_return;
    }
    for ( unsigned i = 0; i < ntid; ++i )
    {
        to_return[ i ] = _v[ i ]->getDouble();
    }
    services::delete_row_of_values( _v, ntid );
    return to_return;
}


Value**
Metric::get_saved_sevs_adv( const Cnode* cnode )
{
    if ( adv_sev_mat == NULL )
    {
        return NULL;
    }

    char* _v =   adv_sev_mat->getRow( calltree_local_ids[ cnode->get_id() ] );
    if ( _v == NULL )
    {
        return NULL;
    }
    Value**     to_return = services::create_row_of_values( ntid );
    const char* start     = _v;
    for ( unsigned i = 0; i < ntid; ++i )
    {
        Value* _val = metric_value->clone();
        start = _val->fromStream( start );

        int64_t _norm = cnode->get_cluster_normalization( sysv[ i ]->get_parent()->get_rank() );
        if ( _norm > 0 )
        {
            _val->normalizeWithClusterCount( ( uint64_t )_norm );
        }
        to_return[ i ] = _val;
    }
    return to_return;
}
