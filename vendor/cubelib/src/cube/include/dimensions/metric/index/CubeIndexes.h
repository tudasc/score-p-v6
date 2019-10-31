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


/**
 * \file CubeIndexes.h
 * \brief Collects all headers of all indexes in one file for easy including.
 */

#ifndef __INDEXES_H
#define __INDEXES_H


// / defines a marker at the beginning of the file
#define CUBE_INDEXFILE_MARKER "CUBEX.INDEX"
#define CUBE_INDEXFILE_MARKER_SIZE 11




// basis abstract index
#include "CubeIndex.h"

// fast index for dense data
#include "CubeDenseIndex.h"

// index for sparse data
#include "CubeSparseIndex.h"


#endif
