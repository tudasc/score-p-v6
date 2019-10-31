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



#include "config.h"
#include "MultiMdAggrCube.h"

#include "AggrCube.h"
#include "CubeError.h"
#include "PrintableCCnode.h"

using namespace cube;
using namespace std;

AggrCube* MultiMdAggrCube::last_created = NULL;

MultiMdAggrCube::MultiMdAggrCube( vector<AggrCube*> _cubes )
    : MdAggrCube( *( merge_AggrCubes( _cubes ) ), _cubes.size() ),
      cubes( _cubes )
{
    number_of_cubes = cubes.size();
    for ( int i = 0; i < number_of_cubes; ++i )
    {
        CubeMapping* merge2cube = new CubeMapping();
        createMapping( *( cubes[ i ] ), *this, *merge2cube, false );
        mappings.push_back( merge2cube );
    }
    delete last_created;
}

MultiMdAggrCube::~MultiMdAggrCube()
{
//   for (vector<AggrCube*>::iterator it = cubes.begin(); it != cubes.end(); ++it)
//     delete *it;
    for ( vector<CubeMapping*>::iterator it = mappings.begin();
          it != mappings.end(); ++it )
    {
        delete *it;
    }
}

vector<CubeMapping*> const&
MultiMdAggrCube::get_mappings()
{
    return mappings;
}

AggrCube*
MultiMdAggrCube::merge_AggrCubes( std::vector<AggrCube*> the_cubes )
{
    int number_of_cubes = the_cubes.size();
    if ( number_of_cubes < 2 )
    {
        throw RuntimeError(
                  "Please use MultiCubeInfo only for two or more cubes." );
    }

    Cube**   cubes = new Cube *[ number_of_cubes ];
    unsigned i     = 0;
    for ( vector<AggrCube*>::iterator c_it = the_cubes.begin(); c_it != the_cubes.end(); ++c_it, i++ )
    {
        cubes[ i ] = *c_it;
    }
    Cube* merged = new Cube();

    cube4_merge( merged, cubes, number_of_cubes, false, false );

    MdAggrCube* retcube = new MdAggrCube( *merged );
    last_created = retcube;
    delete merged;
    delete[] cubes;
    return retcube;
}
