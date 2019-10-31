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

#include "CubeMetricGetEvaluation.h"
#include "CubeServices.h"
using namespace cube;
using namespace std;

MetricGetEvaluation::MetricGetEvaluation() : StringEvaluation()
{
};

MetricGetEvaluation::MetricGetEvaluation( cube::Metric*      _met,
                                          GeneralEvaluation* _val ) : StringEvaluation()
{
    metric = _met;
    arguments.push_back( _val );
};

MetricGetEvaluation::~MetricGetEvaluation()
{
};

string
MetricGetEvaluation::strEval() const
{
    StringEvaluation* _val = dynamic_cast<StringEvaluation*>( arguments[ 0 ] );

    std::string _str = _val->strEval();
    if ( _str == "unique name" )
    {
        return metric->get_uniq_name();
    }
    if ( _str == "display name" )
    {
        return metric->get_disp_name();
    }
    if ( _str == "uom" )
    {
        return metric->get_uom();
    }
    if ( _str == "dtype" )
    {
        return metric->get_dtype();
    }
    if ( _str == "url" )
    {
        return metric->get_url();
    }
    if ( _str == "description" )
    {
        return metric->get_descr();
    }
    if ( _str == "value" )
    {
        return metric->get_val();
    }
    return "";
}
