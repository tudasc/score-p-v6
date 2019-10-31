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



#ifndef AGGREGATED_METRIC_H_GUARD_
#define AGGREGATED_METRIC_H_GUARD_

#include "algebra4.h"
#include "AggrCube.h"
#include "CnodeMetric.h"

namespace cube
{
class Cnode;
class Metric;
class Region;
class Sysres;
/**
 * \class AggregatedMetric
 * \brief Implements cube::info::CnodeMetric
 */
class AggregatedMetric : public CnodeMetric
{
public:
    using CnodeMetric::to_string;

    AggregatedMetric( std::string metric_descriptor_string );
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

    void
    make_inclusive()
    {
        descriptor_string.clear();
        inclusion_mode = INCL;
    }
    void
    make_exclusive()
    {
        descriptor_string.clear();
        inclusion_mode = EXCL;
    }
    inclmode
    get_inclusion_mode()
    {
        return inclusion_mode;
    }

protected:
    virtual std::string
    get_dtype();

private:
    std::string descriptor_string;
    Metric*     metric;
    inclmode    inclusion_mode;
    Sysres*     sysres;
};
}

#endif
