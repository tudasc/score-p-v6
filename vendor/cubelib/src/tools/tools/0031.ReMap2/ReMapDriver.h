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
 * \file ReMapDriver.h
 * \brief Provides a class, which should allow to oad the data from the remap hierarhy description file
 */

#ifndef REMAP_PARSER_DRIVER_H
#define REMAP_PARSER_DRIVER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Cube.h"

// forward declaration
class ReMapParseContext;


/** The remapparser namespace is used to encapsulate the parser classes
 * remapparser::Cube4Parser
 * remapparser::Cube4Scanner,
 *  and remapparser::Driver */

namespace remapparser
{
//  class Cube3Scanner;
//  class Cube3Parser;
class ReMapScanner;
class ReMapParser;

/** The Driver class brings together all components. It creates an instance of
 * the Parser and Scanner classes and connects them. Then the input stream is
 * fed into the scanner object and the parser gets it's token
 * sequence. Furthermore the driver object is available in the grammar rules as
 * a parameter. Therefore the driver class contains a reference to the
 * structure into which the parsed data is saved. */

class ReMapDriver
{
private:
    char* currentlocale;
    ReMapDriver( const ReMapDriver& )
    {
    };

public:
    /// construct a new parser driver context
    ReMapDriver();
    ~ReMapDriver();

    /// stream name (file or input stream) used for error messages.
    std::ostringstream errorStream;
    std::string        streamname;

    /** Invoke the scanner and parser for a stream.
     * @param in	input stream
     * @param sname	stream name for error messages
     * @return		true if successfully parsed
     */
    void
    parse_stream( std::istream& in,
                  cube::Cube&   cubeObj );


/*     ABSOLETE
    void parse_stream_dynamic(std::istream& in, cube::Cube& cubeObj, std::string fileName);
    void parse_matrix(std::istream& in, cube::Cube& cubeObj, int index);
    void parse_matrix_pos(std::istream& in);*/

    // To demonstrate pure handling of parse errors, instead of
    // simply dumping them on the standard error output, we will pass
    // them to the driver using the following two member functions.

    /** Error handling with associated line number. This can be modified to
     * output the error e.g. to a dialog box. */
    void
    error( const class location&  l,
               const std::string& m );

    /**
       This call is used only to  place an error message in to errorstream without
       throwing an exception. Used to build full error message in Cube3Parse.yy
     */
    void
    error_just_message( const std::string& m );

    /** General error handling. This can be modified to output the error
     * e.g. to a dialog box. */
    void
    error( const std::string& m );

    /** Info output*/
    void
    info( const std::string& m );

    /** Pointer to the current lexer instance, this is used to connect the
     * parser to the scanner. It is used in the yylex macro. */
/*    Cube3Scanner* cube3Lexer;
    Cube3Parser*  cube3Parser;*/
    ReMapScanner* remapLexer;
    ReMapParser*  remapParser;

    /** Reference to the context filled during parsing of the
     * expressions. */
    ReMapParseContext* parseContext;

    std::vector<long int> metricPos;
    std::vector<double>   metricSum;
};
} // namespace remapparser

#endif // CUBEPARSER_DRIVER_H
