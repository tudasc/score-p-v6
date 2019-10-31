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



#include "config.h"
#include <iomanip>
#include <sstream>
#include "CubeSizeOfVariableEvaluation.h"

using namespace cube;
using namespace std;

SizeOfVariableEvaluation::~SizeOfVariableEvaluation()
{
}


double
SizeOfVariableEvaluation::eval() const
{
    return ( double )( memory->size_of( variable, kind ) );
}



string
SizeOfVariableEvaluation::strEval() const
{
    size_t       _size = memory->size_of( variable, kind );
    stringstream sstr;
    string       str;
    sstr <<  setprecision( 14 ) << _size;
    sstr >> str;
    return str;
}
