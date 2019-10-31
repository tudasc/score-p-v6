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



#ifndef CMETRICCNODECONSTRAINT_H_GUARD_
#define CMETRICCNODECONSTRAINT_H_GUARD_

/**
 * @file    CMetricCnodeConstraint.h
 * @brief   Contains CMetricCnodeConstraint, a class that slightly extends
 *          CnodeConstraint.
 */

#include <string>

#include "CnodeConstraint.h"

namespace cube
{
class CnodeMetric;
class CnodeSubForest;

/**
 * @class   CMetricCnodeConstraint
 * @brief   Extends CnodeConstraint providing more suitable output routines.
 *
 * This class slightly extends CnodeConstraint in two ways. First, it contains
 * some code to automatically look-up a CnodeMetric instance provided you pass
 * in the serialized version of that string. Second, it provides slightly more
 * suitable output routines that also include the concerned metric.
 */
class CMetricCnodeConstraint : public CnodeConstraint
{
public:
    CMetricCnodeConstraint( CnodeSubForest* forest,
                            std::string     metric_str );

    CnodeMetric*
    get_metric();

protected:
    virtual std::string
    build_header( Cnode*                     node,
                  Constraint_CnodeOutputMode mode );

private:
    CnodeMetric* metric;
};
}

#endif
