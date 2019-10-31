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
 *
 * \file CubeMaxDoubleValue.cpp
 * \brief   Defines the methods of the "MaxDoubleValue".
 ************************************************/

#include "config.h"

#include <cstring>
#include <iomanip>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "CubeValues.h"

using namespace std;
using namespace cube;



string
MaxDoubleValue::getString() const
{
    stringstream sstr;
    string       str;
    if ( value.dValue != -DBL_MAX )
    {
        sstr <<  setprecision( 12 ) << value.dValue;
    }
    else
    {
        sstr <<  "-";
    }

    sstr >> str;
    return str;
}

// overloaded new operator
void*
MaxDoubleValue::operator new( size_t )
{
    return ( void* )max_double_preallocator.Get();
}
// delete operator overloaded
void
MaxDoubleValue::operator delete( void* p )
{
    max_double_preallocator.Put( ( MaxDoubleValue* )p );
}



void
MaxDoubleValue::normalizeWithClusterCount( uint64_t )
{
}
