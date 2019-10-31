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



#ifndef VISITORSMETRIC_H_GUARD_
#define VISITORSMETRIC_H_GUARD_

#include <string>

#include "CnodeMetric.h"

#include "algebra4.h"

namespace cube
{
/**
 * \class VisitorsMetric
 * \brief Implements cube::info::CnodeMetric and provides a new metric that
 *   shows how many threads called a certain function (or call node, in general).
 */
class VisitorsMetric : public CnodeMetric
{
public:
    using CnodeMetric::to_string;

    VisitorsMetric( std::string metric_descriptor_string );
    virtual std::string
    to_string( int max_length = max_column_length );
    virtual double
    compute( Cnode*       node,
             CubeMapping* mapping = NULL );
    virtual double
    compute( Region*      region,
             CubeMapping* mapping = NULL );
    virtual std::string
    stringify();
    virtual void
    register_with( MdAggrCube* cube );

protected:
    virtual std::string
    get_dtype();

private:
    Metric* metric;
};
}

#endif
