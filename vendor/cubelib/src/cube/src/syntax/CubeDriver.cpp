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
 * \file CubeDriver.cpp
 * \brief Implementation of all components of Driver to scan and parse a .cube file and to create CUBE.
 */


#include "config.h"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <locale.h>

#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"

#include "CubeDriver.h"
#include "Cube4Parser.h"
#include "Cube4Scanner.h"
#include "CubeError.h"
#include "CubeMetric.h"
#include "CubeCnode.h"
#include "CubeThread.h"


/**
 * Defines all components of Driver to scan and parse a .cube file and to create CUBE.
 */
namespace cubeparser
{
Driver::Driver() : errorStream( std::ostringstream::out )
{
    parseContext = new ParseContext();
//   cube3Lexer = NULL;
    cube4Lexer = NULL;
//   cube3Parser = NULL;
    cube4Parser = NULL;
    metricPos.clear();
    metricSum.clear();
/*
    currentlocale = setlocale( LC_ALL, NULL );*/
    setlocale( LC_ALL, "C" );
}

Driver::~Driver()
{
//     setlocale( LC_ALL, currentlocale );
    delete parseContext;
}

enum ParseState { INIT, SEVERITY, SEVERITY_MATRIX, SEVERITY_END, MATRIX, MATRIX_ROW, MATRIX_END, ROW, ROW_END };

#define SIZE 1024


void
Driver::parse_stream( cube::CubeIstream& in, cube::Cube& cubeObj )
{
    bool clustering = true; // CHANGE ME.... this should be a parameter of Driver comming from Cube
    cube4Lexer  = new Cube4Scanner( &in, &errorStream, parseContext, &cubeObj );
    cube4Parser = new Cube4Parser( *this, *parseContext, *cube4Lexer, cubeObj, clustering );
    try
    {
        cubeObj.set_post_initialization( true );
        cube4Parser->parse();
        cubeObj.set_post_initialization( false );
        delete cube4Lexer;
        delete cube4Parser;
    }
    catch ( const cube::RuntimeError& e )
    {
        delete cube4Lexer;
        delete cube4Parser;
        throw e;
    }
}




void
Driver::info( const std::string& m )
{
    errorStream << m;
    std::cerr << errorStream.str();
    errorStream.str( "" );
}


void
Driver::error_just_message( const std::string& m )
{
    errorStream << std::endl <<  m << std::endl;
}


void
Driver::error( const class location&  l,
                   const std::string& m )
{
    errorStream << l << ": " << m << std::endl;
    throw cube::RuntimeError( errorStream.str() );
}

void
Driver::error( const std::string& m )
{
    errorStream << m << std::endl;
    throw cube::RuntimeError( errorStream.str() );
}
} // namespace cubeparser
