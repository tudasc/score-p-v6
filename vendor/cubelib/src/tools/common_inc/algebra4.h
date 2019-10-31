/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2018                                                **
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
 * \file algebra4.h
 * \brief Provides a set of global operations on "cube4" like "difference",
   "mean" and so on.
 */
#ifndef CUBE_ALGEBRA4_H
#define CUBE_ALGEBRA4_H


 #include "Cube.h"


#include "algebra4-internals.h"


namespace cube
{
/* Type definition */




void
cube_apply_filter( Cube&        newCube,
                   Cube&        rhs,
                   Filter&      filter,
                   CubeMapping& mapping );


void
cube4_inclusify( Cube* outCube,
                 Cube* inCube,
                 bool  subset,
                 bool  collapse );
void
cube4_exclusify( Cube* outCube,
                 Cube* inCube,
                 bool  subset,
                 bool  collapse );

void
cube4_diff( Cube* outCube,
            Cube* minCube,
            Cube* subCube,
            bool  subset,
            bool  collapse );
void
cube4_mean( Cube*          outCube,
            Cube**         cubes,
            const unsigned num,
            bool           subset,
            bool           collapse );
void
cube4_clean( Cube* outCube,
             Cube* lhsCube,
             bool  subset,
             bool  collapse );
bool
cube4_cmp( Cube* lhsCube,
           Cube* rhsCube );
bool
cube4_cmp_old( Cube* lhsCube,
               Cube* rhsCube );
void
cube4_merge( Cube*          outCube,
             Cube**         cubes,
             const unsigned num,
             bool           subset,
             bool           collapse,
             bool           strict = true );
void
cube4_cut( Cube*                           outCube,
           Cube*                           rhsCube,
           bool                            subset,
           bool                            collapse,
           const std::string&              cn_root,
           const std::vector<std::string>& cn_prunes );

bool
cube4_is_empty( Cube* outCube );
}   /* namespace cube */


#endif   /* !CUBE_ALGEBRA_H */
