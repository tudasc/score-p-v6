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


#ifndef __LOWER_CASE_EVALUATION_H
#define __LOWER_CASE_EVALUATION_H 0

#include "CubeStringEvaluation.h"

namespace cube
{
class LowerCaseEvaluation : public StringEvaluation
{
public:
    LowerCaseEvaluation();
    LowerCaseEvaluation( GeneralEvaluation* );

    virtual
    ~LowerCaseEvaluation();

    virtual
    std::string
    strEval() const;


    virtual
    void
    print() const
    {
        std::cout << " lowercase(";
        arguments[ 0 ]->print();
        std::cout << ")";
    };
};
};
#endif
