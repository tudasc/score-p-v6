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
 * \file CubeEnumerators.h
 * \brief Collects a headers from all enumerators at one place.
 */
#ifndef CUBE_ENUMERATORS_H
#define CUBE_ENUMERATORS_H


// basis enumerator. maps 1 -> 1, 2-> 2
#include "CubeObjectsEnumerator.h"

// enumerator according the "deep search" search prescription for exclusive metric
#include "CubeDeepSearchEnumerator.h"

// enumerator according the "wide search" search prescription for inclusive metric
#include "CubeWideSearchEnumerator.h"

#endif
