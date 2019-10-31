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



#ifndef MULTIMDAGGRCUBE_H_GUARD_
#define MULTIMDAGGRCUBE_H_GUARD_

#include <vector>

#include "algebra4.h"
#include "MdAggrCube.h"

namespace cube
{
class AggrCube;

class MultiMdAggrCube : public MdAggrCube
{
public:
    MultiMdAggrCube( std::vector<AggrCube*> cubes );
    ~MultiMdAggrCube();
    std::vector<CubeMapping*> const&
    get_mappings();

    virtual unsigned int
    get_number_of_cubes() const
    {
        return number_of_cubes;
    }
    virtual CubeMapping*
    get_cube_mapping( unsigned int id ) const
    {
        return mappings.at( id );
    }

private:
    static AggrCube*
    merge_AggrCubes( std::vector<AggrCube*> the_cubes );

    static AggrCube*          last_created;
    int                       number_of_cubes;
    std::vector<AggrCube*>    cubes;
    std::vector<CubeMapping*> mappings;
};
}

#endif
