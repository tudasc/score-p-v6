/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016                                                     **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/**
 * \file CubeIstream.h
 * \brief Provides a ifstream with size informatin.
 */

#ifndef CUBE_ISTREAM_H
#define CUBE_ISTREAM_H



#include <fstream>

/*****************************************************************************/

/**
 * \namespace cube
 */
namespace cube
{
// / sets a flavour of the alculation of a single dimension.

/**
 *  @brief  Ifstream with the information about stream size
 *
 */
class CubeIstream : public std::ifstream
{
public:
    //  Default constructor
    CubeIstream(std::istream & );
  
    //  Default constructor
    CubeIstream( size_t _size = ( size_t )-1 );
    
    //  Default constructor
    CubeIstream( const char*             name,
                std::ios_base::openmode mode = std::ios_base::in,
                size_t                  _size = ( size_t )-1 );



    /**
     *  @brief  Returns size of the stream
     *  @return  Size of the stream
     */
    inline
    size_t
    size() const
    {
        return stream_size;
    }

protected:
    /**
     *  Stream size
     */
    size_t stream_size;
};

}; // namespace 
#endif // ZFSTREAM_H
