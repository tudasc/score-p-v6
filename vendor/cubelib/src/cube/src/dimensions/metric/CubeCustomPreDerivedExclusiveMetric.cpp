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
 * \file CubeCustomPreDerivedExclusiveMetric.cpp
 * \brief Defines methods to calculate incl/exclusve values if the metric is defined as an expression. Expression gets calculated first, then the value gets aggregated.

 ********************************************/


#include "config.h"
#include <iostream>
#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"
#include "CubeCustomPreDerivedExclusiveMetric.h"
#include "CubeServices.h"

using namespace std;
using namespace cube;


CustomPreDerivedExclusiveMetric::~CustomPreDerivedExclusiveMetric()
{
}

double
CustomPreDerivedExclusiveMetric::plus_operator( double a, double b ) const
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
CustomPreDerivedExclusiveMetric::aggr_operator( double a, double b ) const
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




Serializable*
cube::CustomPreDerivedExclusiveMetric::create( Connection&      connection,
                                               const CubeProxy& cubeProxy )
{
    return new CustomPreDerivedExclusiveMetric( connection, cubeProxy );
}

std::string
cube::CustomPreDerivedExclusiveMetric::get_serialization_key() const
{
    return get_static_serialization_key();
}

std::string
cube::CustomPreDerivedExclusiveMetric::get_static_serialization_key()
{
    return "CustomPreDerivedMetric|Exclusive";
}

cube::CustomPreDerivedExclusiveMetric::CustomPreDerivedExclusiveMetric( Connection&      connection,
                                                                        const CubeProxy& cubeProxy )
    : PreDerivedExclusiveMetric( connection, cubeProxy )
{
    /// @note Full packing and unpacking is done by Metric class.
}
