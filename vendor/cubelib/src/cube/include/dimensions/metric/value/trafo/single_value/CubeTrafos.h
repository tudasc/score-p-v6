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
 * \file CubeTrafos.h
 * \brief Collects all headers of all value transformations used in Cube. Currently only two.
 */


#ifndef __TRAFOS_H
#define __TRAFOS_H

// basis class
#include "CubeSingleValueTrafo.h"

// correct endianes transformation
#include "CubeSwapBytesTrafo.h"

// no correction needed endianess transformation
#include "CubeNOPTrafo.h"

#endif
