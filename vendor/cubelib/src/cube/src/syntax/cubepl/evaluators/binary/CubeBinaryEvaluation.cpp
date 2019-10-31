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
#include "CubeBinaryEvaluation.h"
using namespace cube;
using namespace std;



BinaryEvaluation::BinaryEvaluation() : GeneralEvaluation()
{
};

BinaryEvaluation::BinaryEvaluation( GeneralEvaluation* _arg1,
                                    GeneralEvaluation* _arg2 ) : GeneralEvaluation()
{
    arguments.push_back( _arg1 );
    arguments.push_back( _arg2 );
};


BinaryEvaluation::~BinaryEvaluation()
{
}

size_t
BinaryEvaluation::getNumOfArguments() const
{
    return 2;
}
