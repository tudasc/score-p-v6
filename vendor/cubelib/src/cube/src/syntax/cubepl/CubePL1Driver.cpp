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

#include "CubePL1Driver.h"
#include "CubePL1Parser.h"
#include "CubePL1Scanner.h"
#include "CubePL1ParseContext.h"
#include "CubePL1MemoryManager.h"




using namespace std;
using namespace cube;
using namespace cubeplparser;




CubePL1Driver::CubePL1Driver( Cube* _cube ) : CubePLDriver( _cube )
{
};

CubePL1Driver::~CubePL1Driver()
{
};

GeneralEvaluation*
CubePL1Driver::compile( istream* strin, ostream* errs )
{
//  stringstream strin(cubepl_program);

    CubePL1ParseContext* parseContext = new CubePL1ParseContext( cube );

    cubeplparser::CubePL1Scanner* lexer  = new cubeplparser::CubePL1Scanner( strin, errs, parseContext );
    cubeplparser::CubePL1Parser*  parser = new cubeplparser::CubePL1Parser( *parseContext, *lexer );
    parser->parse();
    GeneralEvaluation* formula = parseContext->result;

    delete lexer;
    delete parser;
    delete parseContext;

    return formula;
};

bool
CubePL1Driver::test( std::string& cubepl_program, std::string& error_message )
{
    stringstream strin( cubepl_program );
    stringstream ssout;

    CubePL1ParseContext*          parseContext = new CubePL1ParseContext( NULL, true );
    cubeplparser::CubePL1Scanner* lexer        = new cubeplparser::CubePL1Scanner( &strin, &ssout, parseContext );
    cubeplparser::CubePL1Parser*  parser       = new cubeplparser::CubePL1Parser( *parseContext, *lexer );
    parser->parse();

    string error_output;
    ssout >> error_output;
    bool _ok = parseContext->syntax_ok;

    if ( error_output.length() != 0 )
    {
        _ok                         = false;
        parseContext->error_message = "CubePL1Scanner cannot recognize token: " + error_output;
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
CubePL1Driver::printStatus()
{
    return "OK";
};


