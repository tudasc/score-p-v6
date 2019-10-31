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


#ifndef __ENV_EVALUATION_H
#define __ENV_EVALUATION_H 0

#include "CubeStringEvaluation.h"
#include "CubeMetric.h"

namespace cube
{
class EnvEvaluation : public StringEvaluation
{
protected:
    GeneralEvaluation* variable;
public:
    EnvEvaluation();
    EnvEvaluation( GeneralEvaluation* );

    virtual
    ~EnvEvaluation();

    virtual
    std::string
    strEval() const;

    inline
    virtual
    void
    set_verbose_execution( bool _v )
    {
        GeneralEvaluation::set_verbose_execution( _v );
        variable->set_verbose_execution( _v );
    }

    virtual
    void
    print() const
    {
        std::cout << "env(";
        variable->print();
        std::cout << ")";
    };
};
};
#endif
