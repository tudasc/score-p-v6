/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016                                                     **
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
 *  @ingroup CUBE_lib.network
 *  @brief   Declaration of ClientCallbackData
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_CLIENTCALLBACKDATA_H
#define CUBE_CLIENTCALLBACKDATA_H

namespace cube
{
class CubeNetworkProxy;

/*-------------------------------------------------------------------------*/
/**
 *  @class   cube::ClientCallbackData
 *  @ingroup CUBE_lib.network
 *  @brief   Client-side callback data used for client-server communication.
 *
 *  ClientCallbackData is used to store client-side information between
 *  two network request calls. This can be between send and receiving
 *  a request or response, respectively; or between distinct network
 *  requests.
 **/
/*-------------------------------------------------------------------------*/

class ClientCallbackData
{
    public:
        /// @brief Default constructor.
        ///
        ClientCallbackData();

        /// @brief Virtual destructor.
        virtual
        ~ClientCallbackData();

        /// @brief Get pointer to Cube object.
        ///
        /// @return
        ///     Pointer to Cube object
        ///
        inline CubeNetworkProxy*
        getCube() const
        {
            return mCube;
        }

        /// @brief Store pointer to Cube object.
        ///
        /// @param cube
        ///     Point to Cube object
        ///
        inline void
        setCube(CubeNetworkProxy* cube)
        {
            mCube = cube;
        }

    private:
        /// Client has an explicit network proxy object
        CubeNetworkProxy* mCube;
};
}    /* namespace cube */

#endif    /* !CUBE_CLIENTCALLBACKDATA_H */
