/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2016                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2009-2014                                                **
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
 *  @brief   Declaration of the class ServerCallbackData
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_SERVERCALLBACKDATA_H
#define CUBE_SERVERCALLBACKDATA_H

namespace cube
{
// Forward declarations
class CubeIoProxy;

/*-------------------------------------------------------------------------*/
/**
 *  @class   cube::ServerCallbackData
 *  @ingroup CUBE_lib.network
 *  @brief   Server-side callback data used for client-server communication.
 *
 *  ServerCallbackData is used to store sever-side information between
 *  two network request calls. This can be between send and receiving
 *  a request or response, respectively; or between distinct network
 *  requests.
 **/
/*-------------------------------------------------------------------------*/

class ServerCallbackData
{
    public:
        ServerCallbackData();
        virtual
        ~ServerCallbackData();

        /// @brief Get pointer to Cube object.
        ///
        /// @return
        ///     Pointer to Cube object
        ///
        CubeIoProxy*
        getCube() const
        {
            return mCube;
        }

        /// @brief Store pointer to Cube object.
        ///
        /// @param cube
        ///     Pointer to Cube object.
        ///
        void
        setCube(CubeIoProxy* cube)
        {
            mCube = cube;
        }

    private:
        CubeIoProxy* mCube;
};
}    /* namespace cube */

#endif    /* !CUBE_SERVERCALLBACKDATA_H */
