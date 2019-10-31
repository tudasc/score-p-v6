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


#ifndef __DIRECT_METRIC_EVALUATION_H
#define __DIRECT_METRIC_EVALUATION_H 0

#include "CubeNullaryEvaluation.h"
#include "CubeCalcFlavorModificators.h"
#include "CubeMetric.h"
#include "CubeTypes.h"
#include "Cube.h"



namespace cube
{
enum  MetricReferenceType { CONTEXT_METRIC = 0, FIXED_METRIC_NO_AGGR, FIXED_METRIC_AGGR_SYS, FIXED_METRIC_FULL_AGGR, METRIC_CALL_FULL, METRIC_CALL_CALLPATH };


class DirectMetricEvaluation : public NullaryEvaluation
{
private:
    MetricReferenceType    reference_type;
    Cube*                  cube;
    Metric*                metric;
    CalcFlavorModificator* calltree_cf;
    CalcFlavorModificator* systree_sf;
    std::string            metric_uniq_name;

    GeneralEvaluation* callpath_id;
    GeneralEvaluation* sysres_id;

public:
    DirectMetricEvaluation( MetricReferenceType    _reference_type,
                            Cube*                  _cube,
                            Metric*                _met,
                            CalcFlavorModificator* cf = new CalcFlavorModificatorSame(),
                            CalcFlavorModificator* sf = new CalcFlavorModificatorSame() );
    DirectMetricEvaluation( MetricReferenceType    _reference_type,
                            Cube*                  _cube,
                            Metric*                _met,
                            GeneralEvaluation*     _cnode_id,
                            CalcFlavorModificator* cf );

    DirectMetricEvaluation( MetricReferenceType    _reference_type,
                            Cube*                  _cube,
                            Metric*                _met,
                            GeneralEvaluation*     _cnode_id,
                            CalcFlavorModificator* cf,
                            GeneralEvaluation*     _sysres_id,
                            CalcFlavorModificator* sf );

    virtual
    ~DirectMetricEvaluation();

    virtual
    double
    eval( const Cnode*,
          const CalculationFlavour,
          const Sysres*,
          const CalculationFlavour   ) const;

    virtual
    double
    eval( const Cnode*,
          const CalculationFlavour ) const;

    virtual
    double
    eval() const;

    virtual
    double*
    eval_row( const Cnode*       _cnode,
              CalculationFlavour _cf ) const;


    virtual
    double
    eval( const list_of_cnodes&       lc,
          const list_of_sysresources& ls ) const;

    virtual
    double*
    eval_row( const list_of_cnodes&       lc,
              const list_of_sysresources& ls ) const;


    inline
    virtual
    void
    setRowSize( size_t size )
    {
        GeneralEvaluation::setRowSize( size );
        if ( callpath_id != NULL )
        {
            callpath_id->setRowSize( size );
        }
        if ( sysres_id  != NULL )
        {
            sysres_id->setRowSize( size );
        }
    }


    inline
    virtual
    void
    set_metric_id( uint32_t _id )
    {
        GeneralEvaluation::set_metric_id( _id );
        if ( callpath_id != NULL )
        {
            callpath_id->set_metric_id( _id );
        }
        if ( sysres_id  != NULL )
        {
            sysres_id->set_metric_id( _id );
        }
    }


    inline
    virtual
    void
    set_verbose_execution( bool _v )
    {
        GeneralEvaluation::set_verbose_execution( _v );
        if ( callpath_id != NULL )
        {
            callpath_id->set_verbose_execution( _v );
        }
        if ( sysres_id  != NULL )
        {
            sysres_id->set_verbose_execution( _v );
        }
        if ( calltree_cf  != NULL )
        {
            calltree_cf->set_verbose_execution( _v );
        }
        if ( systree_sf  != NULL )
        {
            systree_sf->set_verbose_execution( _v );
        }
    }

    virtual
    void
    print() const
    {
        std::cout << "metric::";
        switch ( reference_type )
        {
            case METRIC_CALL_FULL:
            case METRIC_CALL_CALLPATH:
                std::cout << "call::";
                break;
            case FIXED_METRIC_AGGR_SYS:
            case FIXED_METRIC_FULL_AGGR:
            case FIXED_METRIC_NO_AGGR:
                std::cout << "fixed::";
                break;
            case CONTEXT_METRIC:
            default:
                std::cout << "context::";
                break;
        }
        std::cout << metric_uniq_name << "(";
        if ( reference_type == METRIC_CALL_CALLPATH || reference_type == METRIC_CALL_FULL )
        {
            callpath_id->print();
            std::cout << ",";
        }
        calltree_cf->print();
        if ( reference_type == METRIC_CALL_FULL )
        {
            std::cout << ", ";
            sysres_id->print();
            std::cout << ",";
        }
        if ( reference_type != METRIC_CALL_CALLPATH )
        {
            systree_sf->print();
        }
        std::cout <<  ")";
    };

    virtual
    double
    eval( double, double ) const
    {
        return 0.;
    };
};
};
#endif
