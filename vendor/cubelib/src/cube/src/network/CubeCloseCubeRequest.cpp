/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016                                                     **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2014                                                     **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  Copyright (c) 2014                                                     **
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
 *  @brief   Definition of the class cube::CloseCubeRequest.
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeCloseCubeRequest.h"

#include <cassert>
#include <string>

#include "CubeClientConnection.h"
#include "CubeConnection.h"
#include "CubeError.h"
#include "CubeIoProxy.h"
#include "CubeServerCallbackData.h"
#include "CubeServerConnection.h"
#include "cube_network_types.h"

using namespace std;
using namespace cube;

NetworkRequestPtr
CloseCubeRequest::create()
{
    return NetworkRequest::Ptr(new CloseCubeRequest());
}


string
CloseCubeRequest::getName() const
{
    return "CloseCube";
}


NetworkRequest::id_t
CloseCubeRequest::getId() const
{
    return CLOSE_CUBE_REQUEST;
}


void
CloseCubeRequest::sendRequestPayload(ClientConnection&   connection,
                                     ClientCallbackData* data) const
{
}


void
CloseCubeRequest::receiveRequestPayload(ServerConnection&   connection,
                                        ServerCallbackData* data)
{
}


void
CloseCubeRequest::processRequest(ServerCallbackData* data)
{
    assert(data);

    try
    {
        data->getCube()->closeReport();

        cerr << "Closed Cube report: "
             << data->getCube()->getAttribute("cubename")
             << endl;
    }
    catch (const std::exception& e)
    {
        throw RecoverableNetworkError("Unable to close file.");
    }
}


void
CloseCubeRequest::sendResponsePayload(ServerConnection&   connection,
                                      ServerCallbackData* data) const
{
    int8_t error_code = 0;
    connection << error_code;
}


void
CloseCubeRequest::receiveResponsePayload(ClientConnection&   connection,
                                         ClientCallbackData* data)
{
    int8_t error_code = connection.get< uint8_t >();
    if (error_code == 0)
    {
        cerr << "Cube report closed remotely." << endl;
    }
    else
    {
        cerr << "Problems closing Cube report remotely." << endl;
    }
}


CloseCubeRequest::CloseCubeRequest()
{
}


CloseCubeRequest::~CloseCubeRequest()
{
}
