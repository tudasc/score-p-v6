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
 * \file
 * \brief Provides an interface for caching mechanisms in metrics
 */

#ifndef __CACHE_H
#define __CACHE_H


#include "CubeTypes.h"


namespace cube
{
/**
 * Class "Cache" is an abstract class, which defines an interface for "Metric" to access the cached data
 */
class Cache
{
public:
    virtual
    ~Cache()
    {
    };

    virtual Value*
    getCachedValue( const Cnode*,
                    const CalculationFlavour,
                    const Sysres*            sysres = 0,
                    const CalculationFlavour sf = CUBE_CALCULATE_INCLUSIVE ) const = 0;                              // /< Returns Value or NULL, if not present

    virtual void
    setCachedValue( Value*,
                    const Cnode*,
                    const CalculationFlavour,
                    const Sysres*            sysres = 0,
                    const CalculationFlavour sf = CUBE_CALCULATE_INCLUSIVE ) = 0;                 // /< Stores or not (if not needed) a Value.

    virtual void
    invalidateCachedValue( const Cnode*,
                           const CalculationFlavour,
                           const Sysres*            sysres = 0,
                           const CalculationFlavour sf = CUBE_CALCULATE_INCLUSIVE ) = 0;

    virtual void
    invalidate( void ) = 0;
};
}

#endif
