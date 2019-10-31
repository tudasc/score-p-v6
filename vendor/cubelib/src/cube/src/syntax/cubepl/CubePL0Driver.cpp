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

#include <vector>
#include <iostream>
#include <sstream>
#include <float.h>
#include <cmath>
#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"

#include "CubePL0Driver.h"
#include "CubePL0Parser.h"
#include "CubePL0Scanner.h"
#include "CubePL0ParseContext.h"
#include "CubePL0MemoryManager.h"




using namespace std;
using namespace cube;
using namespace cubeplparser;

// cube::CubePL0MemoryManager cubepl_memory_manager;



CubePL0Driver::CubePL0Driver( Cube* _cube ) : CubePLDriver( _cube )
{
};

CubePL0Driver::~CubePL0Driver()
{
};

GeneralEvaluation*
CubePL0Driver::compile( istream* strin, ostream* errs )
{
//  stringstream strin(cubepl_program);

    CubePL0ParseContext* parseContext = new CubePL0ParseContext( cube );

    cubeplparser::CubePL0Scanner* lexer  = new cubeplparser::CubePL0Scanner( strin, errs, parseContext );
    cubeplparser::CubePL0Parser*  parser = new cubeplparser::CubePL0Parser( *parseContext, *lexer );
    parser->parse();
    GeneralEvaluation* formula = parseContext->result;

    delete lexer;
    delete parser;
    delete parseContext;

    return formula;
};

bool
CubePL0Driver::test( std::string& cubepl_program, std::string& error_message )
{
    stringstream strin( cubepl_program );
    stringstream ssout;

    CubePL0ParseContext*          parseContext = new CubePL0ParseContext( NULL, true );
    cubeplparser::CubePL0Scanner* lexer        = new cubeplparser::CubePL0Scanner( &strin, &ssout, parseContext );
    cubeplparser::CubePL0Parser*  parser       = new cubeplparser::CubePL0Parser( *parseContext, *lexer );
    parser->parse();

    string error_output;
    ssout >> error_output;
    bool _ok = parseContext->syntax_ok;

    if ( error_output.length() != 0 )
    {
        _ok                         = false;
        parseContext->error_message = "CubePL0Scanner cannot recognize token: " + error_output;
    }

    if ( !_ok  )
    {
        error_message = parseContext->error_message;
    }

    delete parseContext->result;
    delete lexer;
    delete parser;
    delete parseContext;

    return _ok;
}

std::string
CubePL0Driver::printStatus()
{
    return "OK";
};


