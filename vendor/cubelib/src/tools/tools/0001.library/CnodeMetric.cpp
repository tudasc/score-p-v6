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
#include "CnodeMetric.h"

#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <vector>

#include "MdAggrCube.h"
#include "CCnode.h"
#include "CRegion.h"

#include "Cube.h"
#include "CubeMetric.h"
#include "CubeProcess.h"
#include "CubeThread.h"
#include "CubeError.h"


using namespace cube;
using namespace std;

CnodeMetric::CnodeMetric() : IdentObject(), cube(NULL)
{
}

double
CnodeMetric::compute( CCnode* node,
                      CubeMapping* mapping, bool cache )
{
    double val;
    if ( cache && node->has( this, mapping, &val ) )
    {
        return val;
    }
    else
    {
        val = compute( ( Cnode* )node, mapping );
        if ( cache )
        {
            node->store( this, val, mapping );
        }
        return val;
    }
}

double
CnodeMetric::compute( CCnode* node,
                      unsigned int mapping_id, bool cache )
{
    return compute( node, cube->get_cube_mapping( mapping_id ), cache );
}

vector<double>
CnodeMetric::compute( CCnode* node, bool cache )
{
    unsigned int   number_of_cubes = cube->get_number_of_cubes();
    vector<double> ret             = vector<double>( number_of_cubes );
    for ( unsigned int i = 0; i < number_of_cubes; ++i )
    {
        ret[ i ] = compute( node, i, cache );
    }
    return ret;
}

double
CnodeMetric::compute( Cnode* node, unsigned int mapping_id )
{
    return compute( node, cube->get_cube_mapping( mapping_id ) );
}

double
CnodeMetric::compute( CRegion* region,
                      CubeMapping* mapping, bool cache )
{
    double val;
    if ( cache && region->has( this, mapping, &val ) )
    {
        return val;
    }
    else
    {
        val = compute( ( Region* )region, mapping );
        if ( cache )
        {
            region->store( this, val, mapping );
        }
        return val;
    }
}

double
CnodeMetric::compute( CRegion* region,
                      unsigned int mapping_id, bool cache )
{
    return compute( region, cube->get_cube_mapping( mapping_id ), cache );
}

vector<double>
CnodeMetric::compute( CRegion* region, bool cache )
{
    unsigned int   number_of_cubes = cube->get_number_of_cubes();
    vector<double> ret             = vector<double>( number_of_cubes );
    for ( unsigned int i = 0; i < number_of_cubes; ++i )
    {
        ret[ i ] = compute( region, i, cache );
    }
    return ret;
}

double
CnodeMetric::compute( Region* region, unsigned int mapping_id )
{
    return compute( region, cube->get_cube_mapping( mapping_id ) );
}

string
CnodeMetric::to_string( double value, int max_length )
{
    stringstream stream;
    int          length = max_length;
    if ( value != value ) // is NaN?
    {
        stream << setw( length ) << "N/A";
    }
    else if ( get_dtype() == "FLOAT" )
    {
        int precision = 4;
        if ( value > 1000 )
        {
            precision -= static_cast<int>( log10( value / 1000 ) );
        }
        if ( precision < 0 )
        {
            precision = 0;
        }
        stream << setw( length ) << fixed << setprecision( precision )
               << value;
    }
    else // Data type is integer.
    {
        stream << setw( length ) << ( unsigned long int )value;
    }
    return stream.str();
}

void
CnodeMetric::register_with( MdAggrCube* _cube )
{
    cube = _cube;
}
