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
 * \file CubeTarReader.h
 * \brief It translation of the "laout name" into "tar file name" and position of the file inside of the tar.
 */
#ifndef __TAR_READER_H
#define __TAR_READER_H

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

#include "CubeSimpleReader.h"

namespace cube
{
#define TAR_BLOCKSIZE 512

typedef struct __attribute__ ( ( __packed__ ) ) tar_gnu_header
{
    char name[ 100 ];
    char mode[ 8 ];
    char uid[ 8 ];
    char gid[ 8 ];
    char size[ 12 ];
    char mtime[ 12 ];
    char checksum[ 8 ];
    char typeflag[ 1 ];
    char linkname[ 100 ];
    char magic[ 6 ];
    char version[ 2 ];
    char uname[ 32 ];
    char gname[ 32 ];
    char devmajor[ 8 ];
    char devminor[ 8 ];
    char atime[ 12 ];
    char ctime[ 12 ];
    char offset[ 12 ];
    char longnames[ 4 ];
    char unused[ 1 ];
    struct
    {
        char offset[ 12 ];
        char numbytes[ 12 ];
    } sparse[ 4 ];
    char isextended[ 1 ];
    char realsize[ 12 ];
    char pad[ 17 ];
} tar_gnu_header;


typedef struct tar_empty_block
{
    char block[ TAR_BLOCKSIZE ];
} tar_empty_block;



class TarReader : public SimpleReader
{
private:
    uint64_t
    calculate_pos_of_next_header( const uint64_t,
                                  const size_t );                                  ///< Help function, calcultes position of the next header to perform a seek operation during headers reading.

    void
    write_gnu_header( FILE*       f,
                      const char* name,
                      size_t      size );                      ///< writes a header into opened file f for file "name" and its size. Another fiels it calculates.
    void
    end_tar( FILE* f );                                        ///< Writes two empty TAR BLOCKS

    void
    end_file_blocks_in_tar( FILE*  f,
                            size_t size );                                       ///< Writes missing zeros to 512-block alignment.


    std::string prefix_string;                              ///< every tar container


protected:
    std::map<std::string, std::pair<uint64_t, uint64_t> > shifts;   ///< Saves positions of the files inside of the tar archive.
    std::string                                           tar_name; ///< Saves just the name of the archive.


    void
    readHeaders();                                      ///< Reads all headers inside of the archive and builds a map "name -> position"

public:
//                     TarReader( const std::string );
    TarReader( const std::string,
               bool mode = false );
    virtual
    ~TarReader();


    virtual bool
    isFile( const std::string& name );                       ///< Returns true if file is present

    virtual std::string
    getFile( const std::string& name );                       ///< Returns the name of the file (this case, of the archive), if the file is presented
    virtual uint64_t
    getShift( const std::string& name );                      ///< Returns the position of the file inside of the tar archive.
    virtual uint64_t
    getSize( const std::string& name );                       ///< Returns the size of the file inside of the tar archive.

    virtual void
    createContainer( const std::string& name );                ///< Creates a container (tar archive), according to the file list, collected during running. Collection was done in call getFile().

    virtual std::vector<  std::string>
    getAllFiles();                                              ///< Returns a list of all files stored inside of hte cube report.


    void
    printFileList();                                                     ///< Lists on COUT the list of the saved files and their positions inside of the tar archive.
    bool
    contains_ending( const std::string& );                               ///< Checks, if the file with given name (last part of name) exists inside of the tar archive
    bool
    contains( const std::string& );                                      ///< Checks, if the file with given content exists inside of the tar archive
    std::string
    get_file_before( const std::string& );                               ///< Returns the full name of the file
};
};

#endif
