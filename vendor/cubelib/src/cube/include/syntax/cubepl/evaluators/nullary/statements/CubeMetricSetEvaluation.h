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


#ifndef __METRIC_SET_EVALUATION_H
#define __METRIC_SET_EVALUATION_H 0

#include "CubeNullaryEvaluation.h"
#include "CubeStringConstantEvaluation.h"
using namespace std;

namespace cube
{
class MetricSetEvaluation : public NullaryEvaluation
{
protected:
    cube::Metric*      metric;
    GeneralEvaluation* property;
    GeneralEvaluation* value;



public:
    MetricSetEvaluation( cube::Metric*      _met,
                         GeneralEvaluation* _property,
                         GeneralEvaluation* _value ) : NullaryEvaluation(), metric( _met ), property( _property ), value( _value )
    {
    };

    virtual
    ~MetricSetEvaluation();



    inline
    virtual
    void
    setRowSize( size_t size )
    {
        row_size = size;
        property->setRowSize( size );
        value->setRowSize( size );
    }


    inline
    virtual
    void
    set_metric_id( uint32_t _id )
    {
        met_id = _id;
        property->set_metric_id( _id );
        value->set_metric_id( _id );
    }



    inline
    virtual
    void
    set_verbose_execution( bool _v )
    {
        GeneralEvaluation::set_verbose_execution( _v );
        property->set_verbose_execution( _v );
        value->set_verbose_execution( _v );
    }

    inline
    virtual
    double
    eval() const
    {
        if ( metric == NULL )
        {
            return 0.;
        }
        StringConstantEvaluation* prop = dynamic_cast<StringConstantEvaluation*>( property );
        StringConstantEvaluation* val  = dynamic_cast<StringConstantEvaluation*>( value );

        string _prop  = ( prop  != NULL ) ? prop->strEval() : "";
        string _value = ( val != NULL ) ? val->strEval() : "";

        if ( _prop == "value" )
        {
            metric->set_val( _value );
            return 0.;
        }
        cerr << "Supported only \"value\". Property \"" << _prop << "\" is ignored" << endl;
        return 0.;
    }


    inline
    virtual
    double
    eval( const Cnode*,
          const CalculationFlavour,
          const Sysres*,
          const CalculationFlavour )  const
    {
        eval();
        return 0.;
    };

    inline
    virtual
    double
    eval( const Cnode*,
          const CalculationFlavour ) const
    {
        eval();
        return 0.;
    };


    inline
    virtual
    double
    eval( double,
          double ) const
    {
        eval();
        return 0.;
    };

    inline
    virtual
    double*
    eval_row( const Cnode*,
              const CalculationFlavour ) const
    {
        eval();
        return NULL;
    };




    inline
    virtual
    double
    eval( const list_of_cnodes&,
          const list_of_sysresources& ) const
    {
        eval();
        return 0.;
    };

    virtual
    double*
    eval_row( const list_of_cnodes&,
              const list_of_sysresources& ) const
    {
        eval();
        return NULL;
    };




    inline
    virtual
    void
    print() const
    {
        if ( metric == NULL ) // no metric -> no print
        {
            return;
        }
        std::cout << "cube::metric::set::" << metric->get_uniq_name() << "(";
        property->print();
        std::cout << ",";
        value->print();
        std::cout << ");";
    };
};
};

#endif
