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



#ifndef METRICDESCRIPTOR_H_GUARD_
#define METRICDESCRIPTOR_H_GUARD_

#include <string>

#include "CubeIdentObject.h"

#include "algebra4.h"

namespace cube
{
class MdAggrCube;
class CCnode;
class CRegion;

/**
 * \class CnodeMetric
 * \brief An abstract base class for all kinds of metric descriptors.
 *
 * A metric descriptor encapsulates all information that is required to compute
 * a certain value that depends only on the cube instance and a given
 * cube::info::Tree node and it contains the implementation of the compute method.
 */
class CnodeMetric : public IdentObject
{
public:
    CnodeMetric();

    double
    compute( CCnode*      node,
             CubeMapping* mapping,
             bool         cache = true );
    double
    compute( CCnode*      node,
             unsigned int mapping_id,
             bool         cache = true );

    std::vector<double>
    compute( CCnode* node,
             bool    cache = true );
    double
    compute( Cnode*       node,
             unsigned int mapping_id );
    virtual double
    compute( Cnode*       node,
             CubeMapping* mapping ) = 0;

    double
    compute( CRegion*     region,
             CubeMapping* mapping,
             bool         cache = true );
    double
    compute( CRegion*     region,
             unsigned int mapping_id,
             bool         cache = true );

    std::vector<double>
    compute( CRegion* region,
             bool     cache = true );
    double
    compute( Region*      region,
             unsigned int mapping_id );
    virtual double
    compute( Region*      region,
             CubeMapping* mapping ) = 0;

    virtual std::string
    to_string(
        int max_length = max_column_length ) = 0;
    virtual std::string
    to_string( double value,
               int    max_length = max_column_length );

    virtual std::string
    stringify() = 0;
    virtual void
    register_with( MdAggrCube* cube );

protected:
    MdAggrCube* cube;
    virtual std::string
    get_dtype() = 0;

    static const int max_column_length = 15;
};
}

#endif
