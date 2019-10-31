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


#ifndef TOPOASSIST_QUESTION_H
#define TOPOASSIST_QUESTION_H



std::string
intToStr( int number );


unsigned int
strToUInt( std::string* s ) ;

bool
isNumber( std::string* s );



bool
isComment( std::string* s );


void
question( std::string q, std::string* a );


void
question( int i, std::string q, std::string* a );



void
question( int i, std::string q, size_t* a );

void
question( std::string q, unsigned int* a );

void
question( std::string q, bool* a );


void
question( int i, std::string q, bool* a );

#endif

