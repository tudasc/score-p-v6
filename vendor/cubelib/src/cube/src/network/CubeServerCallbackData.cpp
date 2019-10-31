/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2017                                                     **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2014-2015                                                **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  Copyright (c) 2014-2015                                                **
**  RWTH Aachen University, JARA-HPC                                       **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/*-------------------------------------------------------------------------*/
/**
 *  @file
 *  @ingroup Cube_lib.network
 *  @brief   Definition of the class cube::ServerCallbackData
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>
#include "CubeServerCallbackData.h"

#include "CubeIoProxy.h"

namespace cube
{
ServerCallbackData::ServerCallbackData()
    : mCube( 0 )
{
}


ServerCallbackData::~ServerCallbackData()
{
    if ( mCube )
    {
        mCube->closeReport();
    }
}
}    /* namespace cube */
