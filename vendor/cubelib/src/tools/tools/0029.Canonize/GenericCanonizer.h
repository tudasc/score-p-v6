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



#ifndef __CUBE_GENERIC_CANONIZER_H
#define __CUBE_GENERIC_CANONIZER_H

#include "Canonizer.h"

namespace cube
{
class GenericCanonizer : public Canonizer
{
public:
    GenericCanonizer()
        : Canonizer()
    {
    }
    virtual std::string
    transform( std::string const& name ) const;
};
};



std::string
cube::GenericCanonizer::transform( std::string const& name ) const
{
    const char* valid_char =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string transformed = name.substr( name.find_first_of( valid_char ),
                                           name.find_last_of( valid_char ) + 1 );
    return transformed;
}



#endif
