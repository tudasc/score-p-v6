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
 * \file InfoObj.h
 * \brief Provides a general class contains the information about a callpaths.
   Just a wrapper over vector<CallpathType>
 */


#ifndef CUBE_INFOOBJ
#define CUBE_INFOOBJ

#include <vector>
#include <cstdlib>

#include "enums.h"

namespace cube
{
class InfoObj
{
protected:
    std::vector<CallpathType> m_types;

public:
/**
 * Wrapper for an operator []
 */
    CallpathType
    operator[]( size_t i ) const
    {
        return m_types[ i ];
    }

/**
 * Constructor. Creates "n" USR calls.
 */
    InfoObj( size_t n )
        : m_types( n, USR )
    {
    }
};
}

#endif
