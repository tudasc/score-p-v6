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
 * \file CubeCustomPreDerivedInclusiveMetric.cpp
 * \brief Defines methods to calculate incl/exclusve values if the metric is defined as an expression. Expression gets calculated first, then the value gets aggregated.

 ********************************************/


#include "config.h"
#include <iostream>
#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"
#include "CubeCustomPreDerivedInclusiveMetric.h"
#include "CubeServices.h"


using namespace std;
using namespace cube;



static
bool
almost_equal( double x, double y, int ulp )
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::abs( x - y ) <= std::numeric_limits<double>::epsilon() * std::abs( x + y ) * ulp
           // unless the result is subnormal
           || std::abs( x - y ) < std::numeric_limits<double>::min();
}

CustomPreDerivedInclusiveMetric::~CustomPreDerivedInclusiveMetric()
{
}

double
CustomPreDerivedInclusiveMetric::plus_operator( double a, double b ) const
{
    if ( aggr_plus_evaluation != NULL )
    {
        return aggr_plus_evaluation->eval( a, b );
    }
    else
    {
        return a + b;
    }
}
double
CustomPreDerivedInclusiveMetric::minus_operator( double a, double b ) const
{
    if ( aggr_minus_evaluation != NULL )
    {
        return aggr_minus_evaluation->eval( a, b );
    }
    else
    {
        if ( almost_equal( a, b, 2 ) )
        {
            return 0.;
        }
        return a - b;
    }
}
double
CustomPreDerivedInclusiveMetric::aggr_operator( double a, double b ) const
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


cube::Serializable*
cube::CustomPreDerivedInclusiveMetric::create( Connection&      connection,
                                               const CubeProxy& cubeProxy )
{
    return new CustomPreDerivedInclusiveMetric( connection, cubeProxy );
}

std::string
cube::CustomPreDerivedInclusiveMetric::get_serialization_key() const
{
    return get_static_serialization_key();
}

std::string
cube::CustomPreDerivedInclusiveMetric::get_static_serialization_key()
{
    return "CustomPreDerivedMetric|Inclusive";
}

cube::CustomPreDerivedInclusiveMetric::CustomPreDerivedInclusiveMetric( Connection&      connection,
                                                                        const CubeProxy& cubeProxy )
    : PreDerivedInclusiveMetric( connection, cubeProxy )
{
    /// @note Full packing and unpacking is done by Metric class.
}
