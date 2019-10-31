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


#ifndef __METRIC_GET_EVALUATION_H
#define __METRIC_GET_EVALUATION_H 0

#include "CubeStringEvaluation.h"
#include "CubeMetric.h"

namespace cube
{
class MetricGetEvaluation : public StringEvaluation
{
protected:
    cube::Metric* metric;
public:
    MetricGetEvaluation();
    MetricGetEvaluation( cube::Metric* _met,
                         GeneralEvaluation* );

    virtual
    ~MetricGetEvaluation();

    virtual
    std::string
    strEval() const;


    virtual
    void
    print() const
    {
        std::cout << " cube::metric::get::" << metric->get_uniq_name() << "(";
        arguments[ 0 ]->print();
        std::cout << ")";
    };
};
};
#endif
