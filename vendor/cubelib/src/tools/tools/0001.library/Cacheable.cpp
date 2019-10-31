/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2016                                                **
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
#include "Cacheable.h"

#include <limits>

#include "CnodeMetric.h"
#include "CubeError.h"

using namespace cube;
using namespace std;

map<CubeMapping*, int> Cacheable::mappings           = map<CubeMapping*, int>();
int Cacheable::                   number_of_mappings = 0;

Cacheable::Cacheable( int cache_size )
    : cache_size( cache_size )
{
}

void
Cacheable::store( CnodeMetric* metric,
                  double value, CubeMapping* mapping )
{
    int cube_id = get_mapping_id( mapping );
    if ( cube_id < 0 ) // mapping not in mapping2cube-map
    {
        cube_id = add_mapping( mapping );
    }
    store( metric, value, cube_id );
}

bool
Cacheable::has( CnodeMetric* metric, CubeMapping* mapping, double* value )
{
    int cube_id = get_mapping_id( mapping );
    if ( cube_id < 0 ) // mapping not in mapping2cube-map
    {
        return false;
    }
    return has( metric, cube_id, value );
}

double
Cacheable::get( CnodeMetric* metric, CubeMapping* mapping )
{
    int cube_id = get_mapping_id( mapping );
    if ( cube_id < 0 ) // mapping not in mapping2cube-map
    {
        throw Error( "Could not find stored value for specific mapping and metric "
                     + metric->to_string() );
    }
    return get( metric, cube_id );
}

void
Cacheable::store( CnodeMetric* metric,
                  double value, int cube_id )
{
    map<const CnodeMetric*, vector<double> >::iterator it
        = cache.find( metric );
    if ( it == cache.end() )
    {
        vector<double> vec( cache_size, numeric_limits<double>::quiet_NaN() );
        vec[ cube_id ] = value;
        cache.insert( pair<const CnodeMetric*, vector<double> >( metric, vec ) );
    }
    else
    {
        it->second.at( cube_id ) = value;
    }
}

bool
Cacheable::has( CnodeMetric* metric, int cube_id, double* value )
{
    map<const CnodeMetric*, vector<double> >::const_iterator it
        = cache.find( metric );
    // The following condition ensures that
    //   1.) The metric metric is in the cache.
    //   2.) The cube_id'th value is not NaN.
    if ( it != cache.end() )
    {
        double tmp = it->second.at( cube_id );
        if ( tmp != tmp )
        {
            return false;
        }
        else
        {
            if ( value != NULL )
            {
                *value = tmp;
            }
            return true;
        }
    }
    else
    {
        return false;
    }
}

double
Cacheable::get( CnodeMetric* metric, int cube_id )
{
    vector<double> const& values = get_all( metric );
    return values.at( cube_id );
}

vector<double> const&
Cacheable::get_all( CnodeMetric* metric )
{
    map<const CnodeMetric*, vector<double> >::const_iterator it
        = cache.find( metric );
    if ( it != cache.end() )
    {
        return it->second;
    }
    else
    {
        throw Error( "Could not find metric descriptor "
                     + metric->to_string() );
    }
}

int
Cacheable::get_mapping_id( CubeMapping* mapping )
{
    map<CubeMapping*, int>::const_iterator it = mappings.find( mapping );
    if ( it == mappings.end() )
    {
        return -1;
    }
    else
    {
        return it->second;
    }
}

int
Cacheable::add_mapping( CubeMapping* mapping )
{
    mappings.insert( pair<CubeMapping*, int>( mapping, number_of_mappings ) );
    return number_of_mappings++;
}

unsigned int
Cacheable::get_cache_size()
{
    return cache_size;
}
