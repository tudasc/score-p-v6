/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2017                                                **
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
 *
 * \file remap_calls.h
 * \brief Contains a cube_remap spezific calls
 *
 ************************************************/


#ifndef __REMAP_CALLS_H
#define __REMAP_CALLS_H

#include <cstdio>

#include "algebra4.h"
#include "algebra4-internals.h"
#include "Predicates.h"
#include "ReMapDriver.h"

// #define VERSION "remap-dev"
#define PATTERNS_URL "@mirror@scalasca_patterns-" VERSION ".html#"


using namespace cube;
namespace remapper
{
/**
 * An attempt to use xtprocadmin mapfile to remap Cray XT nodenames
 * and generate topologies (based on cabinets and mesh)
 */
void
node_remap( Cube&       newCube,
            std::string dirname );



/**
 * Creates a new cube with manually specified list of metrics. Calculates
   exclusive and inclusive values for metrics and fills severities.
 *
 * only for DOUBLE METRIC
 *
 */
void
cube_remap( AggrCube*           outCube,
            Cube*               inCube,
            const std::string&  specname,
            const std::string&  dirname,
            bool                convert,
            bool                add_scalasca_threads,
            bool                skip_omp,
            bool                copy_cube_structure,
            DataDropCombination drop = BOTH_CUBES_DROP );


/**
 * Creates a new cube with manually specified list of metrics. Calculates
   exclusive and inclusive values for metrics and fills severities.
 *
 * only for DOUBLE METRIC
 *
 */
void
cube_remap( AggrCube*           outCube,
            Cube*               inCube,
            std::istream&       specin,
            const std::string&  dirname,
            bool                convert,
            bool                add_scalasca_threads,
            bool                skip_omp,
            bool                copy_cube_structure,
            DataDropCombination drop = BOTH_CUBES_DROP );
} /* namespace cube */


#endif          // REMAP_CALLS
