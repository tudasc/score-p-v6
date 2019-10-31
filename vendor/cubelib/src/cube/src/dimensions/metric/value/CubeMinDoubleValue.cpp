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
 * \file CubeMinDoubleValue.cpp
 * \brief   Defines the methods of the "MinDoubleValue".
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
MinDoubleValue::getString() const
{
    stringstream sstr;
    string       str;
    if ( value.dValue != DBL_MAX )
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
MinDoubleValue::operator new( size_t )
{
    return ( void* )min_double_preallocator.Get();
}
// delete operator overloaded
void
MinDoubleValue::operator delete( void* p )
{
    min_double_preallocator.Put( ( MinDoubleValue* )p );
}

void
MinDoubleValue::normalizeWithClusterCount( uint64_t )
{
}
