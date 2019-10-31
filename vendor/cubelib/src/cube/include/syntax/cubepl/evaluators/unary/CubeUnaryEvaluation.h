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


#ifndef __UNARY_EVALUATION_H
#define __UNARY_EVALUATION_H 0

#include "CubeGeneralEvaluation.h"

namespace cube
{
class UnaryEvaluation : public GeneralEvaluation
{
protected:

    virtual size_t
    getNumOfArguments() const;

public:
    UnaryEvaluation();
    UnaryEvaluation( GeneralEvaluation* );

    virtual
    ~UnaryEvaluation();
};
};

#endif
