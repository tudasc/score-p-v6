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

#include <cstdlib>
#include "CubeEnvEvaluation.h"
#include "CubeServices.h"




using namespace cube;
using namespace std;

EnvEvaluation::EnvEvaluation() : StringEvaluation()
{
};

EnvEvaluation::EnvEvaluation(   GeneralEvaluation* _val ) : StringEvaluation()
{
    variable = _val;
};

EnvEvaluation::~EnvEvaluation()
{
    delete variable;
};

string
EnvEvaluation::strEval() const
{
    StringEvaluation* _val = dynamic_cast<StringEvaluation*>( variable );

    std::string _str = _val->strEval();

    char* value = getenv( _str.c_str() );

    if ( value != NULL )
    {
        string to_return( value );
        return to_return;
    }
    return "";
}
