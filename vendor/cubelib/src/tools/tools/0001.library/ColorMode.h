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


#ifndef COLORMODE_H
#define COLORMODE_H

#include <ostream>
namespace Color
{
enum Code
{
    FG_BLACK   = 30,
    FG_RED     = 31,
    FG_GREEN   = 32,
    FG_YELLOW  = 33,
    FG_BLUE    = 34,
    FG_MAGENTA = 35,
    FG_CYAN    = 36,
    FG_WHITE   = 37,
    FG_DEFAULT = 39,

    BG_BLACK   = 40,
    BG_RED     = 41,
    BG_GREEN   = 42,
    BG_YELLOW  = 43,
    BG_BLUE    = 44,
    BG_MAGENTA = 45,
    BG_CYAN    = 46,
    BG_WHITE   = 47,
    BG_DEFAULT = 49
};
class Modifier
{
    Code code;
public:
    Modifier( Code pCode ) : code( pCode )
    {
    }
    friend std::ostream&
    operator<<( std::ostream& os, const Modifier& mod )
    {
        return os << "\033[" << mod.code << "m";
    }
};
}

#endif // COLORMODE_H
