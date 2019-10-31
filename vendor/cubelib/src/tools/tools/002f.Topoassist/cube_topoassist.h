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





#include "CubeCartesian.h"
#include "Cube.h"
#include "CubeProcess.h"
#include "CubeThread.h"


void
write_cube( cube::Cube* inCube );
void
create_topology( cube::Cube* inCube );
void
rename_topology( cube::Cube* inCube );
void
rename_dimensions( cube::Cube* inCube );
void
show_topologies( std::vector<cube::Cartesian*> topologies );
