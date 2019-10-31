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



#ifndef __CUBE_PDT_CANONIZER_H
#define __CUBE_PDT_CANONIZER_H

#include "GenericCanonizer.h"

namespace cube
{
class PDTCanonizer : public GenericCanonizer
{
public:
    PDTCanonizer()
        : GenericCanonizer()
    {
    }
    virtual std::string
    transform( std::string const& name ) const;
};
};


std::string
cube::PDTCanonizer::transform( std::string const& name ) const
{
    std::string            transformed = name.substr( 0, name.find_first_of( "(" ) );
    std::string::size_type pos         = transformed.find_last_of( " " );
    if ( pos != std::string::npos )
    {
        transformed = transformed.substr( pos + 1 );
    }
    return GenericCanonizer::transform( transformed );
}



#endif
