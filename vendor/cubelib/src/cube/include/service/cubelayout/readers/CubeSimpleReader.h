/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2019                                                **
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
 * \file CubeSimpleReader.h
 * \brief It translation of the "laout name" into "name to be opened " and position, to be seeked..
 */
#ifndef __SIMPLE_READER_H
#define __SIMPLE_READER_H

#if !defined( __PGI ) && !defined( __CRAYXT )  && !defined( __CRAYXE )
#define _FILE_OFFSET_BITS 64
#endif

#include <inttypes.h>
#include <stdint.h>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <iomanip>
#include <limits>

namespace cube
{
class SimpleReader
{
protected:
    bool creating_mode;
public:
    SimpleReader() : creating_mode( false )
    {
    };
    SimpleReader( bool mode ) : creating_mode( mode )
    {
    };
    virtual
    ~SimpleReader()
    {
    };


    virtual bool
    isFile( const std::string& )
    {
        return false;
    };

    virtual std::string
    getFile( const std::string& name )
    {
        if ( name.size() == 0 )
        {
        }
        return name;
    };
    virtual uint64_t
    getShift( const std::string& name )
    {
        if ( name.size() == 0 )
        {
        }
        return 0;
    };
    virtual uint64_t
    getSize( const std::string& name )
    {
        if ( name.size() == 0 )
        {
        }
        return 0;
    };

    virtual std::vector<  std::string>
    getAllFiles()
    {
        std::vector<  std::string> _tmp;
        return _tmp;
    };                                                                // this container doesn't provide information about misc data.

    virtual void
    createContainer( const std::string& name );
};
}

#endif
