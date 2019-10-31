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
 * \file CubeTarReader.cpp
 * \brief Implements a methods to access a tar file and get a proper position of a given file in it.
 */

#include "config.h"

#include <string>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <iostream>
#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>

#include "CubeError.h"
#include "CubeServices.h"

#include "CubeTarReader.h"
#include "CubeFileBaseLayout.h"
#include "CubePlatformsCompat.h"


using namespace std;
using namespace cube;


uint64_t
TarReader::calculate_pos_of_next_header( const uint64_t currpos, const size_t size )
{
    const uint64_t headersize = 512;
    const uint64_t blocksize  = 512;

    if ( size == 0 )
    {
        return currpos + headersize;
    }

    return currpos + headersize + ( ( ( ( ( uint64_t )( size ) ) / blocksize ) + 1 ) * blocksize );
}




void
TarReader::readHeaders()
{
    tar_gnu_header header;
    FILE*          tar = NULL;
    __FOPEN( tar,  tar_name.c_str(), "rb" );
    if ( tar == NULL )
    {
        throw RuntimeError( "No file " + tar_name + " found." );
    }

    char* endptr;
    off_t seekpos = 0;
    while ( true )
    {
        fseeko( tar, seekpos, 0 );
        size_t readedsize = fread( ( char* )&header, 1, sizeof( tar_gnu_header ), tar );

        if ( readedsize != sizeof( tar_gnu_header ) )
        {
            break;
        }

        size_t size = strtol( header.size, &endptr, 8 );

        if ( strlen( header.name ) != 0 )
        {
            shifts[ header.name ].first  = seekpos + 512;
            shifts[ header.name ].second = size;
        }
        seekpos = calculate_pos_of_next_header( seekpos, size );
    }

    fclose( tar );
}



void
TarReader::write_gnu_header( FILE* f, const char* name, size_t size )
{
    uid_t uid = getuid();
    gid_t gid = getgid();

    const char* mode         = "0000600";
    const char* pre_checksum = "        ";
    const char* user         = getenv( "USER" );
    if ( user == NULL )
    {
        user = getenv( "LOGNAME" );
    }
    if ( user == NULL )
    {
        user = "nobody";
    }
    char* group = new char[ 32 ]();
    strcpy( group, "users" );
    tar_gnu_header* header = new tar_gnu_header;
    memset( ( char* )header, 0, sizeof( tar_gnu_header ) );
    memcpy( header->name, name,  strlen( name ) );
    memcpy( header->mode, mode,  strlen( mode ) );
    sprintf( header->uid, "%7.7lo", ( unsigned long )uid & 0x0FFF );
    sprintf( header->gid, "%7.7lo", ( unsigned long )gid & 0x0FFF );
    unsigned int mtime = time( NULL );
    sprintf( header->mtime, "%11.11lo", ( unsigned long )mtime );
    memcpy( header->checksum, pre_checksum,  strlen( pre_checksum ) );
    memcpy( header->typeflag, "0",  1 );

    sprintf( header->size, "%11.11lo", ( unsigned long )size );

    const char* _magic = "ustar";
    memcpy( header->magic, _magic, 5 );
    const char* _version = "00";
    memcpy( header->version, _version, 2 );

    memcpy( header->uname, user,  strlen( user ) );
    memcpy( header->gname, group,  strlen( group ) );

    unsigned checksum = 0;
    uint8_t* pos      = ( uint8_t* )header;
    for ( unsigned i = 0; i < ( sizeof( tar_gnu_header ) ); ++i )
    {
        checksum += ( *pos );
        pos++;
    }
    sprintf( header->checksum, "%6.6lo", ( unsigned long )checksum );

    int written = fwrite( ( char* )( header ), 1, sizeof( tar_gnu_header ), f );
    if ( written !=  sizeof( tar_gnu_header ) )
    {
        throw FinalizeFilesError( "Cannot create container (writing tar header error)." );
    }

    delete[] group;
    delete  header;
}


void
TarReader::end_tar( FILE* f )
{
    tar_empty_block* block = new tar_empty_block;
    memset( block->block, 0, sizeof( tar_empty_block ) );
    fwrite( ( char* )block, 1, sizeof( tar_empty_block ), f );
    fwrite( ( char* )block, 1, sizeof( tar_empty_block ), f );
    delete block;
}



void
TarReader::end_file_blocks_in_tar( FILE* f, size_t size )
{
    unsigned int difference = ( ( ( unsigned int )( ( unsigned int )( size / sizeof( tar_gnu_header ) ) + 1 ) * sizeof( tar_gnu_header ) )  - size );
    char*        _tmp       = new char[ difference ];
    memset( _tmp, 0, difference );
    fwrite( _tmp, 1, difference, f );
    delete[] _tmp;
    return;
}



// -------------------- class methods --------------------------


TarReader::TarReader( const std::string _tarname,
                      bool              mode ) : SimpleReader( mode )
{
    tar_name      = _tarname;
    prefix_string = services::create_unique_dir_name();
    if ( !creating_mode )
    {
        prefix_string = "";
        readHeaders();
    }
}

bool
TarReader::isFile( const std::string& name )
{
    std::map<std::string, std::pair<uint64_t, uint64_t> >::iterator iter;
    iter = shifts.find( name );
    return !( iter == shifts.end() );
}


std::string
TarReader::getFile( const std::string& name )
{
    if ( creating_mode )
    {
        shifts[ name ].first  = 0;
        shifts[ name ].second = 0;
        return prefix_string + name;
    }
    std::map<std::string, std::pair<uint64_t, uint64_t> >::iterator iter;
    iter = shifts.find( name );
    if ( iter == shifts.end() )
    {
        throw cube::NoFileInTarError( name );
    }
    return tar_name;
}

uint64_t
TarReader::getShift( const std::string& name )
{
    if ( creating_mode )
    {
        return 0;               // In creastion mode all fileas are created separately, then packed to tar.
    }
    std::map<std::string, std::pair<uint64_t, uint64_t> >::iterator iter;
    iter = shifts.find( name );
    if ( iter == shifts.end() )
    {
        throw cube::NoFileInTarError( name );
    }
    return ( *iter ).second.first;
}

uint64_t
TarReader::getSize( const std::string& name )
{
    if ( creating_mode )
    {
        return 0;               // In creastion mode all fileas are created separately, then packed to tar.
    }
    std::map<std::string, std::pair<uint64_t, uint64_t> >::iterator iter;
    iter = shifts.find( name );
    if ( iter == shifts.end() )
    {
        throw cube::NoFileInTarError( name );
    }
    return ( *iter ).second.second;
}



std::vector<  std::string>
TarReader::getAllFiles()
{
    std::vector<  std::string>                                      to_return;
    std::map<std::string, std::pair<uint64_t, uint64_t> >::iterator iter;
    for ( iter = shifts.begin(); iter != shifts.end(); ++iter )
    {
        to_return.push_back( ( *iter ).first );
    }
    return to_return;
}



void
TarReader::printFileList()
{
    cout << " Found files: " << endl;
    std::map<std::string, std::pair<uint64_t, uint64_t> >::iterator iter;
    for ( iter = shifts.begin(); iter != shifts.end(); ++iter )
    {
        cout << "     " <<  prefix_string  << iter->first << " at position " << iter->second.first << " and size " << iter->second.second  << endl;
    }
    cout << " ---------- end." << endl;
}


bool
TarReader::contains_ending( const std::string& file )
{
    std::map<std::string, std::pair<uint64_t, uint64_t> >::iterator iter;
    for ( iter = shifts.begin(); iter != shifts.end(); ++iter )
    {
        std::string path = ( *iter ).first;
        size_t      pos  = path.rfind( file );
        if ( pos == string::npos )
        {
            continue;
        }
        if ( pos == ( path.length() - file.length() ) )
        {
            return true;
        }
    }
    return false;
}

bool
TarReader::contains( const std::string& file )
{
    std::map<std::string, std::pair<uint64_t, uint64_t> >::iterator iter;
    for ( iter = shifts.begin(); iter != shifts.end(); ++iter )
    {
        std::string path = ( *iter ).first;
        size_t      pos  = path.rfind( file );
        if ( pos == string::npos )
        {
            continue;
        }
        return true;
    }
    return false;
}


std::string
TarReader::get_file_before( const std::string& file )
{
    std::map<std::string, std::pair<uint64_t, uint64_t> >::iterator iter;
    for ( iter = shifts.begin(); iter != shifts.end(); ++iter )
    {
        std::string path = ( *iter ).first;
        size_t      pos  = path.rfind( file );
        if ( pos == string::npos )
        {
            continue;
        }
        return path.substr( 0, pos );
    }
    return "";
}








void
TarReader::createContainer( const std::string& _tar_name )
{
    if ( !creating_mode )
    {
        return;
    }
    const unsigned int buffer_size = 50 * 1024 * 1024;          // buffer for copying
    char*              buffer      = new char[ buffer_size ];
    memset( buffer, 0, buffer_size );

    services::create_path_for_file( _tar_name );
    FILE* f1 = NULL;
    __FOPEN( f1,  ( _tar_name + ".cubex" ).c_str(), "wb" );
    if ( f1 == NULL )
    {
        delete[] buffer;
        throw RuntimeError( "Cannot create file " + _tar_name + ".cubex" );
    }


    std::map<std::string, std::pair<uint64_t, uint64_t> >::iterator iter;
    for ( iter = shifts.begin(); iter != shifts.end(); ++iter )
    {
        string        nextfile = ( *iter ).first;
        __STRUCT_STAT stat_of_file;
        int           status = 0;
        __STAT( status,  ( prefix_string + nextfile ).c_str(), &stat_of_file );
        if ( status == -1 )
        {
            delete[] buffer;
            throw RuntimeError( "TarReader::createContainer: cannot stat file " + ( prefix_string + nextfile ) );
        }
        size_t size = stat_of_file.st_size;
        FILE*  f2   = NULL;
        __FOPEN( f2,  ( prefix_string + nextfile ).c_str(), "rb" );
        if ( f2 != NULL )
        {
            write_gnu_header( f1, nextfile.c_str(), size );
            while ( !feof( f2 ) )
            {
                size_t readsize = fread( buffer, 1, buffer_size, f2 );
                size_t written  = fwrite( buffer, 1, readsize, f1 );
                if ( written != readsize )
                {
                    delete[] buffer;
                    throw FinalizeFilesError( "Cannot create container (copy files error)." );
                }
            }
            end_file_blocks_in_tar( f1, size );
        }
        fclose( f2 );
    }
    end_tar( f1 );
    fclose( f1 );

    delete[] buffer;
}


TarReader::~TarReader()
{
    if ( !creating_mode )
    {
        return;
    }
    if ( prefix_string == "" )
    {
        return;                      // no files were created... only memory... then one cdoesnt need to remove anything
    }
    std::map<std::string, std::pair<uint64_t, uint64_t> >::iterator iter;
    for ( iter = shifts.begin(); iter != shifts.end(); ++iter )
    {
        string nextfile = ( *iter ).first;
        unlink( ( prefix_string + nextfile ).c_str() );
    }
    rmdir( prefix_string.substr( 0, prefix_string.length() - 1 ).c_str() );
}
