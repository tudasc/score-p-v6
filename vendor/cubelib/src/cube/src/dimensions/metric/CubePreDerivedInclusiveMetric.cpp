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
 * \file CubePreDerivedInclusiveMetric.cpp
 * \brief Defines methods to calculate incl/exclusve values if the metric is defined as an expression. Expression gets calculated first, then the value gets aggregated.

 ********************************************/


#include "config.h"
#include "config.h"
#include <iostream>
#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"
#include "CubePreDerivedInclusiveMetric.h"
#include "CubeServices.h"


using namespace std;
using namespace cube;


PreDerivedInclusiveMetric::~PreDerivedInclusiveMetric()
{
}


void
PreDerivedInclusiveMetric::initialize( void )
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
cube::PreDerivedInclusiveMetric::create( Connection&      connection,
                                         const CubeProxy& cubeProxy )
{
    return new PreDerivedInclusiveMetric( connection, cubeProxy );
}

cube::PreDerivedInclusiveMetric::PreDerivedInclusiveMetric( Connection&      connection,
                                                            const CubeProxy& cubeProxy )
    : InclusiveBuildInTypeMetric<double>( connection, cubeProxy )
{
    /// @note Full packing and unpacking is done by Metric class.
}

std::string
cube::PreDerivedInclusiveMetric::get_serialization_key() const
{
    return get_static_serialization_key();
}

std::string
cube::PreDerivedInclusiveMetric::get_static_serialization_key()
{
    return "PreDerivedMetric|Inclusive";
}
