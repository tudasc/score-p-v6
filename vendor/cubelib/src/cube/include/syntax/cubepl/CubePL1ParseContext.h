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


#ifndef CUBEPL1PARSECONTEXT_H
#define CUBEPL1PARSECONTEXT_H

#include <sstream>
#include <vector>
#include <string>
#include <stack>

#include "Cube.h"
// #include "CubeEvaluators.h"
#include "CubeGeneralEvaluation.h"
#include "CubeCalcFlavorModificators.h"
#include "location.hh"
namespace cubeplparser
{
class CubePL1ParseContext
{
public:
    cube::Cube*                           cube;
    std::stack<cube::GeneralEvaluation* > _stack;
    std::string                           value;
    std::string                           name_of_metric;
    std::stack<cube::GeneralEvaluation* > function_call;

    std::stack<cube::CalcFlavorModificator*> calcFlavorModificators;

    std::stack<cube::GeneralEvaluation* > _statements;
    std::stack<int>                       _number_of_statements;

    std::stack<std::string> string_constants;
    std::stack<std::string> strings_stack;
    std::ostringstream      str;

    std::string init_expression;




    unsigned number_elseif;


    bool syntax_ok;
    bool test_modus;
    bool callparse;


    std::string error_message;
    location    error_place;


    cube::GeneralEvaluation* result;
    CubePL1ParseContext( cube::Cube* _cube,
                         bool        _test_modus = false )
    {
        error_message   = "";
        result          = NULL;
        value           = "";
        cube            = _cube;
        test_modus      = _test_modus;
        syntax_ok       = true;
        init_expression = "";
        number_elseif   = 0;
        callparse       = false;
    }

    ~CubePL1ParseContext()
    {
//      delete result;
    }
};
};
#endif // PARSECONTEXT_H
