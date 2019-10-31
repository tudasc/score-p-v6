/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2018                                                **
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


#ifndef __STRING_CONSTANT_EVALUATION_H
#define __STRING_CONSTANT_EVALUATION_H 0

#include "CubeStringEvaluation.h"

namespace cube
{
class StringConstantEvaluation : public StringEvaluation
{
protected:
    std::string constant;

public:
    StringConstantEvaluation( std::string _const );

    virtual
    ~StringConstantEvaluation();

    virtual
    std::string
    strEval() const
    {
        return constant;
    };


    virtual
    void
    print() const
    {
        std::cout << "\"" << constant << "\"";
    };
};
};

#endif
