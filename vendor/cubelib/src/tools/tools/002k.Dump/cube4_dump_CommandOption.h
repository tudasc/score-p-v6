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



#ifndef CUBE4_DUMP_COMMANDOPTION_H
#define CUBE4_DUMP_COMMANDOPTION_H


#include "Cube.h"
#include "CubePL1Driver.h"


enum ThreadSelection { SELECTED_THREADS = 0, AGGREGATED_THREADS = 1, THREADS_AS_ROW = 2 };



void
parseMetrics( std::string               _optarg,
              std::vector<std::string>& metric,
              cube::Cube*               _cube );
bool
parseCallPaths_Threads( std::string            _optarg,
                        std::vector<unsigned>& cnodeId );

void
parseNewMetric( std::vector<std::string>& newmetric,
                std::vector<std::string>& metric,
                bool&                     check_all,
                cube::Cube*               _cube );

bool
parseCubePlCnodeCondition( std::string  _optarg,
                           std::string& cubepl );


std::string
fakeNumberCheck( std::string& input );

void
cnodeSelection( cube::Cube*            cube,
                std::string&           cnode_cond_cubepl,
                std::vector<unsigned>& cnode_idv );



template <class T>
bool
from_string( T&                 t,
             const std::string& s,
             std::              ios_base& ( *f )( std::ios_base & ) )
{
    std::istringstream iss( s );
    return !( iss >> f >> t ).fail();
}


#endif // CUBE4_DUMP_COMMANDOPTION_H
