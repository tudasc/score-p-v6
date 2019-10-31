/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016-2019                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2015                                                     **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  Copyright (c) 2015                                                     **
**  RWTH Aachen University, JARA-HPC                                       **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/*-------------------------------------------------------------------------*/
/**
 *  @file
 *  @ingroup CUBE_lib.network
 *  @brief   Definition of the class cube::SaveCubeReport.
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeSaveCubeRequest.h"

#include "CubeClientConnection.h"
#include "CubeIoProxy.h"
#include "CubeServerCallbackData.h"
#include "CubeServerConnection.h"

using namespace std;
using namespace cube;

SaveCubeRequest::~SaveCubeRequest()
{
}


NetworkRequestPtr
SaveCubeRequest::create( const string& filename )
{
    return NetworkRequest::Ptr( new SaveCubeRequest( filename ) );
}


string
SaveCubeRequest::getName() const
{
    return "SaveCube";
}


NetworkRequest::id_t
SaveCubeRequest::getId() const
{
    return SAVE_CUBE_REQUEST;
}


void
SaveCubeRequest::sendRequestPayload( ClientConnection& connection,
                                     ClientCallbackData* ) const
{
    connection << mFilename;
}


void
SaveCubeRequest::receiveRequestPayload( ServerConnection& connection,
                                        ServerCallbackData* )
{
    connection >> mFilename;
}


void
SaveCubeRequest::processRequest( ServerCallbackData* data )
{
    try
    {
        data->getCube()->saveCopy( mFilename );
    }
    catch ( const std::exception& e )
    {
        throw RecoverableNetworkError( e.what() );
    }
}


void
SaveCubeRequest::sendResponsePayload( ServerConnection&,
                                      ServerCallbackData* ) const
{
}


void
SaveCubeRequest::receiveResponsePayload( ClientConnection&,
                                         ClientCallbackData* )
{
}


SaveCubeRequest::SaveCubeRequest( const string& filename )
    : mFilename( filename )
{
}


NetworkRequestPtr
cube::SaveCubeRequest::create()
{
    return NetworkRequest::Ptr( new SaveCubeRequest() );
}


cube::SaveCubeRequest::SaveCubeRequest()
{
}
