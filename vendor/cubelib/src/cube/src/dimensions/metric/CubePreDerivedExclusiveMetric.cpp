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
 * \file CubePreDerivedExclusiveMetric.cpp
 * \brief Defines methods to calculate incl/exclusve values if the metric is defined as an expression. Expression gets calculated first, then the value gets aggregated.

 ********************************************/


#include "config.h"
#include <iostream>
#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"
#include "CubePreDerivedExclusiveMetric.h"
#include "CubeServices.h"

using namespace std;
using namespace cube;


PreDerivedExclusiveMetric::~PreDerivedExclusiveMetric()
{
}


void
PreDerivedExclusiveMetric::initialize( void )
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



Serializable*
cube::PreDerivedExclusiveMetric::create( Connection&      connection,
                                         const CubeProxy& cubeProxy )
{
    return new PreDerivedExclusiveMetric( connection, cubeProxy );
}

cube::PreDerivedExclusiveMetric::PreDerivedExclusiveMetric( Connection&      connection,
                                                            const CubeProxy& cubeProxy )
    : ExclusiveBuildInTypeMetric<double>( connection, cubeProxy )
{
    /// @note Full packing and unpacking is done by Metric class.
}

std::string
cube::PreDerivedExclusiveMetric::get_serialization_key() const
{
    return get_static_serialization_key();
}

std::string
cube::PreDerivedExclusiveMetric::get_static_serialization_key()
{
    return "PreDerivedMetric|Exclusive";
}
