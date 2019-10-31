/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2017                                                **
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



#ifndef __CUBE_CANONIZER_H
#define __CUBE_CANONIZER_H

// #ifndef CUBE_COMPRESSED
#include <fstream>
// #else
#include "CubeZfstream.h"
// #endif
#include "Cube.h"
#include "CubeRegion.h"
#include "CubeError.h"
#include "CubeServices.h"

namespace cube
{
class Canonizer
{
public:
    Canonizer()
        : _max_length( 0 ), _case_sensitive( true ),
        _remove_line_numbers( false ), _remove_file_names( false )
    {
    }
    virtual
    ~Canonizer();
    void
    max_length( int l )
    {
        _max_length = l;
    }
    void
    case_sensitive( bool b )
    {
        _case_sensitive = b;
    }
    void
    remove_line_numbers( bool b )
    {
        _remove_line_numbers = b;
    }
    void
    remove_file_names( bool b )
    {
        _remove_file_names = b;
    }
    void
    run( const char*   in_name,
         const char*   out_name = NULL,
         std::ostream* name_list = NULL );
    virtual std::string
    transform( std::string const& name ) const = 0;

private:
    int  _max_length;
    bool _case_sensitive;
    bool _remove_line_numbers;
    bool _remove_file_names;
};








Canonizer::~Canonizer()
{
}

void
Canonizer::run( const char* in_name, const char* out_name, std::ostream* name_list )
{
    if ( out_name == NULL )
    {
        out_name = in_name;
    }

    cube::Cube* input = new Cube();
    input->openCubeReport( in_name );



    std::vector<Region*> regions = input->get_regv();
    for ( std::vector<Region*>::const_iterator region = regions.begin();
          region != regions.end(); ++region )
    {
        std::string name        = ( *region )->get_name();
        std::string transformed = transform( name );
        transformed = _max_length <= 0 ? transformed : transformed.substr( 0, _max_length );
        if ( _case_sensitive == false )
        {
            std::transform( transformed.begin(), transformed.end(),
                            transformed.begin(), ::tolower );
        }
        if ( name_list != NULL && transformed != name )
        {
            *name_list << transformed << std::endl << name << std::endl;
        }
        ( *region )->set_name( transformed );

        if ( _remove_line_numbers )
        {
            ( *region )->set_begn_ln( 0 );
            ( *region )->set_end_ln( 0 );
        }
        if ( _remove_file_names )
        {
            ( *region )->set_mod( "" );
        }
    }

    Cube* out = new Cube( *input, cube::CUBE_DEEP_COPY );
    out->writeCubeReport( services::get_cube4_name( out_name ) );
    delete out;
    delete input;
}
};


#endif
