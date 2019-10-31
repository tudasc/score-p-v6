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
 * \file CubeServices.h
 * \brief Provides a set of global service operations for cube library.
 */
#ifndef CUBE_SERVICES_H
#define CUBE_SERVICES_H 0

#include <string>
#include <functional>
#include <clocale>
#include <cctype>
#include <algorithm>
#include <inttypes.h>
#include <sys/stat.h>
#include <vector>
#include <map>

#include "CubeTypes.h"

namespace cube
{
namespace services
{
std::string
cube_errno();  // returns string verbalizing system errono

std::string
escapeToXML( std::string );           // /< Makes all XML reserved symbols XML-conform notation using  [actronym];
std::string
escapeFromXML( std::string );         // /< Makes all XML-conform notation into plaint text withou restriction by.

bool
is_metric_present( const std::string&,
                   const std::string& );                      // checks, if in the first list of metric unique names current is given or "all"


std::string
get_cube_name( std::string );          // / Removes the extansipn .cube from cube3 name.
std::string
get_cube3_name( std::string );         // / Removes the extansipn .cube from cube3 name.
std::string
get_cube3_gzipped_name( std::string ); // / Removes the extansion .cube.gz from gzipped cube3 name.
std::string
get_cube4_name( std::string );         // / Removes the extansipn .cubex from cube4 name.

// std::string
// get_cube4_hyb_dir_name( std::string ); // / Removes the extansipn .cubex from cube4 name.
bool
is_cube3_name( std::string );          // / checks, if it is the name of cube3 file
bool
is_cube3_gzipped_name( std::string );  // / checks, if it is the name of gzipped cube3 file
bool
is_cube4_name( std::string );          // / checks, whether it is a cube4 file
bool
is_cube4_tared( std::string );         // / checkt, whether it is a tared cube4 file. (only cube4 can be tared)

// bool
// is_cube4_hyb_dir( std::string );       // / checkt, whether it is a data dir in hybrid layout. (checks extension .cubex.data)
bool
is_cube4_embedded_anchor( std::string );


// --------- Service for file system operations -------------

bool
is_path( std::string );              // /< Checks, if it is a path or just a filename (contans "/" sign)
std::string
dirname( std::string );              // /< systemlie "dirname"
std::string
filename( std::string );             // /< systemlie "dirname"

std::string
remove_dotted_path( std::string );   // /< Replace /./ by "/" and /XXXX/../ by /
void
create_path_for_file( std::string ); // /< throws an exception if fails. Otherwise creates the path independend of its depth.

int
    _mkdir( const char*, mode_t );   // /< provides an interface to mkdir call, which is different under windows and linuix


std::string
remove_last_slashes( std::string );            // /< Removes a last slash in the path

std::string
create_random_string(  uint64_t seed,
                       unsigned length = 32 );                 // /< Creates a random string with given length (32 symbols defualt)

uint64_t
hr_time();                                // /< Returns current time in nanoseconds. Used to initialize random generator.

std::string
get_tmp_files_location();               // /< Returns a path to the directory where cube places temporary files. As separate call to include check and and fall back into current directory if needed

/* returns a unique for the tmp directory, which surely does not exist (to avoid clash in parallel test suites ).
   Performs file system stat check for existance of the generated name */
std::string
create_unique_dir_name( void );


/**
 * STL conform version to get a lowercase of a string.
 */
struct fo_tolower : public std::unary_function<int, int>
{
    int
    operator()( int x ) const
    {
        return std::tolower( x );
    }
};
/**
 * STL conform version to get a uppercase of a string.
 */
struct fo_toupper : public std::unary_function<int, int>
{
    int
    operator()( int x ) const
    {
        return std::toupper( x );
    }
};


std::string
lowercase( const std::string& str );           // /< Returns a lowercase version of str.
std::string
uppercase( const std::string& str );           // /< Returns a uppercase version of str.



uint64_t
parse_clustering_key( std::string& );            // /< Parses key attribute and returnd "iteration" id.

std::vector<uint64_t>
parse_clustering_value( std::string& );          // /< Parses value attribute and returnd "clusters" id.

uint32_t
string2int( const std::string& );                 // /< General transformation string -> int

std::string
numeric2string( int );                          // /< General transformation int -> string

std::string
numeric2string( double );                    // /< General transformation int -> string

std::string
    numeric2string( uint64_t );                // /< General transformation int -> string

std::string
    numeric2string( int64_t );                // /< General transformation int -> string


bool
get_children( std::vector<cube::Cnode*>& roots,
              uint64_t                   cluster_id,
              std::vector<cube::Cnode*>& children
              );          // /< finds in all cnodes and returns children of cnode with id "cluster_id"
bool
get_children( cube::                     Cnode*,
              uint64_t                   cluster_id,
              std::vector<cube::Cnode*>& children
              );          // /< finds recursively and returns children of cnode with id "cluster_id"





void
copy_tree( const cube:: Cnode*,
           cube::Cnode*& clusters_root,
           uint64_t cluster_id = ( uint64_t )-1,
           cube::Cnode* parent = NULL,
           cube::Cube* cube = NULL,
           std::map<uint64_t, uint64_t>* normalisation_factor = NULL,
           std::vector<uint64_t>* cluster_position = NULL
           );             // /< Creates a copy of a call tree. Used to merge clusters trees. (-2 -> no copy, -1 -> only one copy, otherwise -> Process id)

void
merge_tree( const cube:: Cnode*,
            const cube:: Cnode*,
            cube::Cube* cube = NULL,
            std::map<uint64_t, uint64_t>* normalisation_factor = NULL,
            std::vector<uint64_t>* cluster_position = NULL );                                             // /< Merges children of second cnode into the first cnode


void
merge_trees( const std::vector<cube::Cnode*>&,
             cube::Cnode* common_parent = NULL,
             cube::Cube* cube = NULL,
             std::map<uint64_t, uint64_t>* normalisation_factor = NULL,
             std::vector<uint64_t>* cluster_position = NULL
             );                                                // /< List of trees is merged onto single one.


void
gather_children( std:: vector<cube::Cnode*>&,
                 cube::Cnode* );                                                // /< Extends std::vector with the children of cnode



std::vector<uint64_t>
sort_and_collapse_clusters( std::vector<uint64_t>& );

std::map<uint64_t, std::vector<uint64_t> >
get_cluster_positions( std::vector<uint64_t>& );




/** Swap the bytes in an 2-byte word. */
inline
uint16_t
cube_swap16( uint16_t v16 )
{
    return ( ( v16 >> 8 ) & 0xFFu ) | ( ( v16 & 0xFFu ) << 8 );
}

/** Swap the bytes in an 4-byte word. */
inline
uint32_t
cube_swap32( uint32_t v32 )
{
    return cube_swap16( ( v32 >> 16 ) & 0xFFFFu ) |
           ( ( uint32_t )cube_swap16( v32 & 0xFFFFu ) << 16 );
}

/** Swap the bytes in an 8-byte word. */
inline
uint64_t
cube_swap64( uint64_t v64 )
{
    return cube_swap32( ( v64 >> 32 ) & 0xFFFFFFFFu ) |
           ( ( uint64_t )cube_swap32( v64 & 0xFFFFFFFFu ) << 32 );
}





// ----service calls to operata on rows of Values, chars or doubles
cube::Value**
    create_row_of_values( size_t );  // === new Value*[locationv.size()];
double*
    create_row_of_doubles( size_t ); // === new double[locationv.size()](0.); ;
char*
    create_raw_row( size_t );        // === new char[locationv.size()](0.); ;


template <class T>
T*
create_t_row( size_t size )        // === new char[locationv.size()](0.); ;
{
    return new T[ size ]();
}

void
    delete_row_of_values( cube::Value * *_v, size_t );
void
delete_raw_row( char* v );     // == delete[] _v;
void
delete_raw_row( double* v );   // == delete[] _v;




double*
    transform_values_to_doubles( const cube::Value * const* const v, size_t );

char*
    transform_values_to_raw( const cube::Value * const* const row, const cube::Value * const v, size_t );

cube::Value**
    transform_raw_to_values( const char* const, const cube::Value * const, size_t );

cube::Value**
    transform_doubles_to_values( const double* const, const cube::Value * const, size_t );



template <class T>
char*
transform_doubles_to_t( const double* row, size_t size )
{
    T* _row = services::create_t_row<T>( size );
    if ( row != NULL )
    {
        for ( size_t i = 0; i < size; i++ )
        {
            _row[ i ] = static_cast<T>( row[ i ] );
        }
    }
    return ( char* )_row;
}



double*
    transform_raw_to_doubles( const char*, cube::Value*, size_t );

inline
char*
transform_doubles_to_raw( const double* row )
{
    return ( char* )row;
}


list_of_sysresources
expand_sys_resources( const list_of_sysresources& );

list_of_cnodes
expand_regions( const cube::Cube*,
                const list_of_regions& );

std::pair<list_of_metrics, list_of_metrics>
expand_metrics( const list_of_metrics& ); // from general list of metrics creates two lists, one where all metrics are dded, other, which has to be substracted





void
print_raw_row( char*  _row,
               size_t _size  );

void
print_row_of_doubles( double* _row,
                      size_t  _size  );
} // namespace services
} // namespace cube
#endif
