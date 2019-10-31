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


#include "config.h"

#include <ios>
#include <istream>
#include "CubeIstream.h"
using namespace cube;

/// Default constructor initializes stream buffer
CubeIstream::CubeIstream(std::istream & _in )
    : std::ifstream(), stream_size (( size_t )-1) 
{
    std::ios::rdbuf(_in.rdbuf());
}


/// Default constructor initializes stream buffer
CubeIstream::CubeIstream( size_t _size )
    : std::ifstream(), stream_size( _size )
{
}

/// Default constructor initializes stream buffer
CubeIstream::CubeIstream( const char*             name,
                          std::ios_base::openmode mode,
                          size_t                  _size )
    : std::ifstream( name, mode ), stream_size( _size )
{
}
