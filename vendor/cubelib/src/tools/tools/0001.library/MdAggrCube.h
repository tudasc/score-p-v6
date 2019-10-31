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



#ifndef MDAGGRCUBE_H_GUARD_
#define MDAGGRCUBE_H_GUARD_

#include <string>

#include "Cube.h"
#include "AggrCube.h"
#include "algebra4.h"

namespace cube
{
class Cube;
class AggrCube;
class CnodeMetric;
class CnodeSubForest;
class PrintableCCnode;
class Region;
class CRegion;

class MdAggrCube : public AggrCube
{
    friend class Cube;
    friend class AggrCube;

public:
    MdAggrCube();
    MdAggrCube( Cube& copy,
                int   cache_size = 1 );
    virtual
    ~MdAggrCube();
    CnodeMetric*
    add_cnode_metric( CnodeMetric* metric );
    CnodeMetric*
    get_cnode_metric( std::string stringified );
    CnodeSubForest*
    get_forest();
    virtual CubeMapping*
    get_cube_mapping( unsigned int id ) const;
    virtual unsigned int
    get_number_of_cubes() const;

private:
/**
 * Actual method to create a region.
 */
    Region*
    def_region( const std::string& name,
                const std::string& mangled_name,
                const std::string& paradigm,
                const std::string& role,
                long               begln,
                long               endln,
                const std::string& url,
                const std::string& descr,
                const std::string& mod,
                uint32_t           id,
                int                cache_size );

/**
 * Actual method to create a cnode.
 */
    Cnode*
    def_cnode( Region*            callee,
               const std::string& mod,
               int                line,
               Cnode*             parent,
               uint32_t           id,
               int                cache_size );

    std::map< std::string, CnodeMetric* > cnode_metrics;
    Cube*                                 original_address;
};
}

#endif
