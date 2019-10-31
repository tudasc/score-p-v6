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
 * \file CubeValues.h
 * \brief Collects all headers of all supported Values of the Cube in one place. Allows to include just one file.
 */


#ifndef __VALUES_H
#define __VALUES_H



/**
 * Defines an enum type, supported by Cube.
 */
#include "CubeTypes.h"

// basis class
#include "CubeValue.h"

// a single byte (8 bit)
#include "CubeCharValue.h"

// double precision value
#include "CubeDoubleValue.h"
#include "CubeMaxDoubleValue.h"
#include "CubeMinDoubleValue.h"

// normal values (32 bits)
#include "CubeUnsignedValue.h"
#include "CubeSignedValue.h"

// short value (16 bits)
#include "CubeUnsignedShortValue.h"
#include "CubeSignedShortValue.h"

// long long values (64 bits)
#include "CubeUnsignedLongValue.h"
#include "CubeSignedLongValue.h"

// experimental values
#include "CubeComplexValue.h"
#include "CubeRateValue.h"
#include "CubeTauAtomicValue.h"
#include "CubeStringValue.h"
// values for future
#include "CubeHistogramValue.h"
#include "CubeNDoublesValue.h"
#include "CubeStatLevel1Value.h"
#include "CubeStatLevel2Value.h"
#include "CubeStatLevel3Value.h"
#include "CubeStatLevel4Value.h"

#include "CubeScaleFuncValue.h"
#endif
