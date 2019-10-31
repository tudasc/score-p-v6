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



/**
 * \file CubeReMapDriver.cpp
 * \brief Implementation of all components of ReMapDriver to scan and parse a .cube file and to create CUBE.
 */

#include "config.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <locale.h>

#include "ReMapDriver.h"
/*#include "Cube3Parser.h"
 #include "Cube3Scanner.h"*/
#include "ReMapParser.hh"
#include "ReMapScanner.h"
#include "CubeError.h"
#include "CubeMetric.h"
#include "CubeCnode.h"
#include "CubeThread.h"


/**
 * Defines all components of ReMapDriver to scan and parse a .cube file and to create CUBE.
 */
namespace remapparser
{
ReMapDriver::ReMapDriver() : errorStream( std::ostringstream::out )
{
    parseContext = new ReMapParseContext();
//   cube3Lexer = NULL;
    remapLexer = NULL;
//   cube3Parser = NULL;
    remapParser = NULL;
    metricPos.clear();
    metricSum.clear();

    currentlocale = setlocale( LC_ALL, NULL );
    setlocale( LC_ALL, "C" );
}

ReMapDriver::~ReMapDriver()
{
    setlocale( LC_ALL, currentlocale );
    delete parseContext;
}

enum ParseState { INIT, SEVERITY, SEVERITY_MATRIX, SEVERITY_END, MATRIX, MATRIX_ROW, MATRIX_END, ROW, ROW_END };

#define SIZE 1024


void
ReMapDriver::parse_stream( std::istream& in, cube::Cube& cubeObj )
{
    remapLexer  = new ReMapScanner( &in, &errorStream, parseContext );
    remapParser = new ReMapParser( *this, *parseContext, *remapLexer, cubeObj );
    try
    {
        cubeObj.set_post_initialization( true );
        remapParser->parse();
        delete remapLexer;
        delete remapParser;
    }
    catch ( const cube::RuntimeError& e )
    {
        delete remapLexer;
        delete remapParser;
        throw e;
    }
}









void
ReMapDriver::info( const std::string& m )
{
    errorStream << m;
    std::cerr << errorStream.str();
    errorStream.str( "" );
}


void
ReMapDriver::error_just_message( const std::string& m )
{
    errorStream << std::endl <<  m << std::endl;
}


void
ReMapDriver::error( const class location& l,
                    const std::string&    m )
{
    errorStream << l << ": " << m << std::endl;
    throw cube::RuntimeError( errorStream.str() );
}

void
ReMapDriver::error( const std::string& m )
{
    errorStream << m << std::endl;
    throw cube::RuntimeError( errorStream.str() );
}
} // namespace remapparser
