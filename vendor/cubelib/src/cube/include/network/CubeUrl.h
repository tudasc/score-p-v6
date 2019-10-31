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
 *  @brief   Declaration of the class Url.
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_URL_H
#define CUBE_URL_H

#include <sstream>
#include <string>

namespace cube
{
/*-------------------------------------------------------------------------*/
/**
 *  @class   Url
 *  @ingroup CUBE_lib.network
 *  @brief   Simple class to tokenize a given URL for use in Cube.
 **/
/*-------------------------------------------------------------------------*/

class Url
{
    public:
        /// @brief Default constructor.
        ///
        Url();

        /// @brief Constructor with direct initialization.
        ///
        /// The given @p url_string is parsed for different string tokens.
        /// If a certain token is not present it is initialized with the
        /// default value.
        ///
        /// @param url_string
        ///    Given URL to be parsed.
        ///
        Url(const std::string& url_string);


        /// @brief Parse a given input URL and set internal members accordingly.
        ///
        /// @param url_string
        ///     Given URL to be parsed.
        ///
        void
        parse(const std::string& url_string);

        /// @brief Get the protocol part of the URL.
        ///
        /// @return
        ///     Protocol part of the URL.
        ///
        const std::string&
        getProtocol() const
        {
            return mProtocol;
        }

        /// @brief Return default protocol for URLs.
        ///
        /// @return
        ///     Protocol string
        ///
        static const std::string&
        getDefaultProtocol()
        {
            return mDefaultProtocol;
        }

        /// @brief Get the host part of the URL.
        ///
        /// @return
        ///     Host name or address.
        ///
        const std::string&
        getHost() const
        {
            return mHost;
        }

        /// @brief Return default host for URLs.
        ///
        /// @return
        ///     Default host name or address
        ///
        static const std::string&
        getDefaultHost()
        {
            return mDefaultHost;
        }

        /// @brief Get the port part of the URL.
        ///
        /// @return Network port.
        ///
        unsigned int
        getPort() const
        {
            return mPort;
        }

        /// @brief Return default port for URLs
        ///
        /// @return
        ///     Port number
        ///
        static unsigned int
        getDefaultPort()
        {
            return mDefaultPort;
        }

        /// @brief Get path part of the URL.
        ///
        /// @return
        ///     Resource path.
        ///
        const std::string&
        getPath() const
        {
            return mPath;
        }

        /// @brief Set the path part of the URL.
        ///
        /// @param path
        ///     Path to set for the URL.
        ///
        void
        setPath(const std::string& path)
        {
            mPath = path;
        }

        /// @brief Get the well-formed URL of the current state
        ///
        /// @return URL
        ///
        const std::string
        toString() const;


    private:
        /// Network protocol
        std::string mProtocol;

        /// Network host
        std::string mHost;

        /// Network port
        unsigned int mPort;

        /// Resource path
        std::string mPath;

        /// Default protocol
        static const std::string mDefaultProtocol;

        /// Default address
        static const std::string mDefaultHost;

        /// Default port
        static const unsigned int mDefaultPort;

        /// Default path
        static const std::string mDefaultPath;
};
}    /* namespace cube */

#endif    /* CUBE_URL_H */
