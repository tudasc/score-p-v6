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



#include "config.h"
#include "VisitorsMetric.h"

#include <limits>

#include "CubeError.h"
#include "MdAggrCube.h"

using namespace cube;
using namespace std;

VisitorsMetric::VisitorsMetric( string metric_descriptor_string )
    :  metric( NULL )
{
    if ( metric_descriptor_string != "visitors@" )
    {
        throw Error( string( "Can not reconstruct VisitorsMetric from string " )
                     + metric_descriptor_string + "!" );
    }
}

string
VisitorsMetric::to_string( int max_length )
{
    return string( "Visitors" ).substr( 0, max_length );
}

double
VisitorsMetric::compute( Cnode* node, CubeMapping* mapping )
{   // We usually have to read a lot of unaggregated values. Storing them in the
    // cache would just make the cache slower and would not get us any speed up.
    // Thus, we will not use other CnodeMetrics or the Trees cache, just for
    // the reason of speed.
    int visitors = 0;

    Cnode* aggr_node = node;

    if ( mapping != NULL )
    {
        map<Cnode*, Cnode*>::iterator nodit = mapping->cnodem.find( node );

        if ( nodit == mapping->cnodem.end() )
        {
            return numeric_limits<double>::quiet_NaN();
        }

        aggr_node = nodit->second;
    }

    for ( vector<Thread*>::const_iterator thrit = ( cube->get_thrdv() ).begin();
          thrit != ( cube->get_thrdv() ).end(); ++thrit )
    {
        if ( cube->get_sev( metric, aggr_node, *thrit ) > 0 )
        {
            ++visitors;
        }
    }

    return visitors;
}

double
VisitorsMetric::compute( Region*, CubeMapping* )
{
    return 0.;
}

string
VisitorsMetric::stringify()
{
    return "visitors@";
}

void
VisitorsMetric::register_with( MdAggrCube* _cube )
{
    CnodeMetric::register_with( _cube );
    cube   = _cube;
    metric = _cube->get_met( "visits" );
}

string
VisitorsMetric::get_dtype()
{
    return "INTEGER";
}
