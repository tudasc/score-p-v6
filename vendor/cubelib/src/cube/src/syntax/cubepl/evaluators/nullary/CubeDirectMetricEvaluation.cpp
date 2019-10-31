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



#include "config.h"
#include "CubeDirectMetricEvaluation.h"

#include "CubeServices.h"

using namespace cube;

DirectMetricEvaluation::DirectMetricEvaluation( MetricReferenceType    _reference_type,
                                                Cube*                  _cube,
                                                Metric*                _met,
                                                CalcFlavorModificator* cf,
                                                CalcFlavorModificator* sf ) : NullaryEvaluation(), reference_type( _reference_type ), cube( _cube ), metric( _met ), calltree_cf( cf ), systree_sf( sf ), callpath_id( NULL ), sysres_id( NULL )
{
    metric_uniq_name = metric->get_uniq_name();
};

DirectMetricEvaluation::DirectMetricEvaluation( MetricReferenceType    _reference_type,
                                                Cube*                  _cube,
                                                Metric*                _met,
                                                GeneralEvaluation*     _call_path_id,
                                                CalcFlavorModificator* cf ) : NullaryEvaluation(), reference_type( _reference_type ), cube( _cube ), metric( _met ), calltree_cf( cf ), systree_sf( NULL ), callpath_id( _call_path_id ), sysres_id( NULL )
{
    metric_uniq_name = metric->get_uniq_name();
};

DirectMetricEvaluation::DirectMetricEvaluation( MetricReferenceType    _reference_type,
                                                Cube*                  _cube,
                                                Metric*                _met,
                                                GeneralEvaluation*     _call_path_id,
                                                CalcFlavorModificator* cf,
                                                GeneralEvaluation*     _sysres_id,
                                                CalcFlavorModificator* sf ) : NullaryEvaluation(), reference_type( _reference_type ), cube( _cube ), metric( _met ), calltree_cf( cf ), systree_sf( sf ), callpath_id( _call_path_id ), sysres_id( _sysres_id )
{
    metric_uniq_name = metric->get_uniq_name();
};



DirectMetricEvaluation::~DirectMetricEvaluation()
{
    delete calltree_cf;
    delete systree_sf;
    delete callpath_id;
    delete sysres_id;
}



double
DirectMetricEvaluation::eval( const cube::Cnode*       _cnode,
                              const CalculationFlavour _cf,
                              const cube::Sysres*      _sf,
                              const CalculationFlavour _tf   ) const
{
    double _value         = 0.;
    size_t _call_path_id  = ( size_t )-1;
    size_t _ref_sysres_id = ( size_t )-1;

    switch ( reference_type )
    {
        case METRIC_CALL_CALLPATH:
        {
            _call_path_id = ( size_t )callpath_id->eval( _cnode, _cf, _sf, _tf );
            const cube::Cnode* _call_cnode = ( cube->get_cnodev().size() >  _call_path_id ) ? cube->get_cnodev()[ _call_path_id ] : NULL;

            if ( _call_cnode != NULL )
            {
                _value = metric->get_sev( _call_cnode, calltree_cf->flavour( _cf ) );
            }
            else
            {
                std::cerr << "DirectMetricEvaluation::eval: Index " << _call_path_id << " is out of call path id range. Return 0";
            }
        }
        break;
        case METRIC_CALL_FULL:
        {
            _call_path_id = ( size_t )callpath_id->eval( _cnode, _cf, _sf, _tf );
            const cube::Cnode* _call_cnode = ( cube->get_cnodev().size() >  _call_path_id ) ? cube->get_cnodev()[ _call_path_id ] : NULL;
            _ref_sysres_id = ( size_t )sysres_id->eval( _cnode, _cf, _sf, _tf );
            const cube::Sysres* _call_sysres = ( cube->get_sysv().size() >  _ref_sysres_id ) ? cube->get_sysv()[ _ref_sysres_id ] : NULL;
            if ( _call_sysres != NULL && _call_cnode != NULL )
            {
                _value = metric->get_sev( _call_cnode, calltree_cf->flavour( _cf ), _call_sysres, systree_sf->flavour( _tf ) );
            }
            else
            {
                std::cerr << "DirectMetricEvaluation::eval: Ineces " << _call_path_id << " or " << _ref_sysres_id << " are out of id range. Return 0";
            }
        }
        break;
        case FIXED_METRIC_FULL_AGGR:
            _value = cube->get_sev( metric, cube::CUBE_CALCULATE_INCLUSIVE );
            break;
        case FIXED_METRIC_AGGR_SYS:
            _value = metric->get_sev( _cnode, calltree_cf->flavour( _cf ) );
            break;
        case FIXED_METRIC_NO_AGGR:
            _value = metric->get_sev( _cnode, calltree_cf->flavour( _cf ),
                                      _sf, systree_sf->flavour( _tf ) );
            break;
        case CONTEXT_METRIC:
        default:
            _value = metric->get_sev( _cnode, calltree_cf->flavour( _cf ),
                                      _sf, systree_sf->flavour( _tf ) );
            break;
    }

    return _value;
}


double
DirectMetricEvaluation::eval( const cube::Cnode*       _cnode,
                              const CalculationFlavour _cf ) const
{
    double        _value         = 0.;
    cube::Cnode*  _call_cnode    = NULL;
    cube::Sysres* _call_sysres   = NULL;
    size_t        _call_path_id  = ( size_t )-1;
    size_t        _ref_sysres_id = ( size_t )-1;
    switch ( reference_type )
    {
        case METRIC_CALL_CALLPATH:
            _call_path_id = ( size_t )callpath_id->eval( _cnode, _cf );
            _call_cnode   = ( cube->get_cnodev().size() >  _call_path_id ) ? cube->get_cnodev()[ _call_path_id ] : NULL;

            if ( _call_cnode != NULL )
            {
                _value = metric->get_sev( _call_cnode, calltree_cf->flavour( _cf ) );
            }
            else
            {
                std::cerr << "DirectMetricEvaluation::eval: Index " << _call_path_id << " is out of call path id range. Return 0";
            }

            break;
        case METRIC_CALL_FULL:
            _call_path_id  = ( size_t )callpath_id->eval( _cnode, _cf );
            _call_cnode    = ( cube->get_cnodev().size() >  _call_path_id ) ? cube->get_cnodev()[ _call_path_id ] : NULL;
            _ref_sysres_id = ( size_t )sysres_id->eval( _cnode, _cf );
            _call_sysres   = ( cube->get_sysv().size() >  _ref_sysres_id ) ? cube->get_sysv()[ _ref_sysres_id ] : NULL;

            if ( _call_sysres != NULL && _call_cnode != NULL )
            {
                _value = metric->get_sev( _call_cnode, calltree_cf->flavour( _cf ), _call_sysres, systree_sf->flavour() );
            }
            else
            {
                std::cerr << "DirectMetricEvaluation::eval: Indices " << _call_path_id << " or " << _ref_sysres_id << " are out of id range. Return 0";
            }
            break;
        case FIXED_METRIC_FULL_AGGR:
            _value = cube->get_sev( metric, cube::CUBE_CALCULATE_INCLUSIVE );
            break;
        case FIXED_METRIC_AGGR_SYS:
            _value = metric->get_sev( _cnode, calltree_cf->flavour( _cf ) );
            break;
        case FIXED_METRIC_NO_AGGR:
            _value = 0.;
            break;
        case CONTEXT_METRIC:
        default:
            _value = metric->get_sev( _cnode, calltree_cf->flavour( _cf ) );
            break;
    }
    return _value;
}



double
DirectMetricEvaluation::eval() const
{
    double        _value         = 0.;
    cube::Cnode*  _call_cnode    = NULL;
    cube::Sysres* _call_sysres   = NULL;
    size_t        _call_path_id  = ( size_t )-1;
    size_t        _ref_sysres_id = ( size_t )-1;
    switch ( reference_type )
    {
        case METRIC_CALL_CALLPATH:
            _call_path_id = ( size_t )callpath_id->eval();
            _call_cnode   = ( cube->get_cnodev().size() >  _call_path_id ) ? cube->get_cnodev()[ _call_path_id ] : NULL;
            if ( _call_cnode != NULL )
            {
                _value = metric->get_sev( _call_cnode, calltree_cf->flavour() );
            }
            else
            {
                std::cerr << "DirectMetricEvaluation::eval: Index " << _call_path_id << " is out of call path id range. Return 0";
            }

            break;
        case METRIC_CALL_FULL:
            _call_path_id  = ( size_t )callpath_id->eval();
            _call_cnode    = ( cube->get_cnodev().size() >  _call_path_id ) ? cube->get_cnodev()[ _call_path_id ] : NULL;
            _ref_sysres_id = ( size_t )sysres_id->eval();
            _call_sysres   = ( cube->get_sysv().size() >  _ref_sysres_id ) ? cube->get_sysv()[ _ref_sysres_id ] : NULL;

            if ( _call_sysres != NULL && _call_cnode != NULL )
            {
                _value = metric->get_sev( _call_cnode, calltree_cf->flavour(), _call_sysres, systree_sf->flavour() );
            }
            else
            {
                std::cerr << "DirectMetricEvaluation::eval: Indices " << _call_path_id << " or " << _ref_sysres_id << " are out of id range. Return 0";
            }
            break;
        case FIXED_METRIC_FULL_AGGR:
            _value = cube->get_sev( metric, cube::CUBE_CALCULATE_INCLUSIVE );
            break;
        case FIXED_METRIC_AGGR_SYS:
        case FIXED_METRIC_NO_AGGR:
            _value = 0.;
            break;
        case CONTEXT_METRIC:
        default:
            std::cerr << "Wrong context of metric::  Return 0";
            break;
    }
    return _value;
}

double*
DirectMetricEvaluation::eval_row( const Cnode*             _cnode,
                                  const CalculationFlavour _cf ) const
{
    double*        result        = NULL;
    double         _value        = 0;
    cube::Cnode*   _call_cnode   = NULL;
    size_t         _call_path_id = ( size_t )-1;
    list_of_cnodes lcnodes;
    switch ( reference_type )
    {
        case METRIC_CALL_CALLPATH:
            _call_path_id = ( size_t )callpath_id->eval( _cnode, _cf );
            _call_cnode   = ( cube->get_cnodev().size() >  _call_path_id ) ? cube->get_cnodev()[ _call_path_id ] : NULL;

            if ( _call_cnode != NULL )
            {
                _value = metric->get_sev( _call_cnode, calltree_cf->flavour( _cf ) );
                result = services::create_row_of_doubles( row_size );
                for ( size_t i = 0; i < row_size; ++i )
                {
                    result[ i ] = _value;
                }
            }
            else
            {
                std::cerr << "DirectMetricEvaluation::eval: Index " << _call_path_id << " is out of call path id range. Return 0";
            }

            break;
        case METRIC_CALL_FULL:
            std::cerr << "DirectMetricEvaluation::eval_row: RowWise call is not defined.";
            break;
        case FIXED_METRIC_FULL_AGGR:
            _value = cube->get_sev( metric, cube::CUBE_CALCULATE_INCLUSIVE );
            result = services::create_row_of_doubles( row_size );
            for ( size_t i = 0; i < row_size; ++i )
            {
                result[ i ] = _value;
            }
            break;
        case FIXED_METRIC_AGGR_SYS:
            _value = metric->get_sev( _cnode, calltree_cf->flavour( _cf ) );
            result = services::create_row_of_doubles( row_size );
            for ( size_t i = 0; i < row_size; ++i )
            {
                result[ i ] = _value;
            }
            break;
        case FIXED_METRIC_NO_AGGR:
        case CONTEXT_METRIC:
        default:
        {
            cnode_pair cpair = std::make_pair( const_cast<Cnode*>( _cnode ), calltree_cf->flavour( _cf ) );
            lcnodes.push_back( cpair );
            cube::Value** _v = metric->get_sevs( lcnodes );
            result = services::transform_values_to_doubles( _v, row_size );
            services::delete_row_of_values( _v, row_size );
        }
        break;
    }
    return result;
}





double
DirectMetricEvaluation::eval( const list_of_cnodes& lc, const list_of_sysresources& ls  ) const
{
    double               value          = 0.;
    cube::Value*         _value         = NULL;
    cube::Cnode*         _call_cnode    = NULL;
    cube::Sysres*        _call_sysres   = NULL;
    size_t               _call_path_id  = ( size_t )-1;
    size_t               _ref_sysres_id = ( size_t )-1;
    list_of_cnodes       llc            = lc;
    list_of_sysresources lls            = ls;
    for ( list_of_cnodes::iterator citer = llc.begin(); citer != llc.end(); ++citer )
    {
        cnode_pair& pair = *citer;
        pair.second = calltree_cf->flavour( pair.second );
    }
    for ( list_of_sysresources::iterator siter = lls.begin(); siter != lls.end(); ++siter )
    {
        sysres_pair& pair = *siter;
        pair.second = systree_sf->flavour( pair.second );
    }
    switch ( reference_type )
    {
        case METRIC_CALL_CALLPATH:
            _call_path_id = ( size_t )callpath_id->eval( llc, lls );
            _call_cnode   = ( cube->get_cnodev().size() >  _call_path_id ) ? cube->get_cnodev()[ _call_path_id ] : NULL;

            if ( _call_cnode != NULL )
            {
                _value =  metric->get_sev( llc, lls );
            }
            else
            {
                std::cerr << "DirectMetricEvaluation::eval: Index " << _call_path_id << " is out of call path id range. Return 0";
            }

            break;
        case METRIC_CALL_FULL:
            _call_path_id  = ( size_t )callpath_id->eval( llc, lls );
            _call_cnode    = ( cube->get_cnodev().size() >  _call_path_id ) ? cube->get_cnodev()[ _call_path_id ] : NULL;
            _ref_sysres_id = ( size_t )sysres_id->eval( llc, lls );
            _call_sysres   = ( cube->get_sysv().size() >  _ref_sysres_id ) ? cube->get_sysv()[ _ref_sysres_id ] : NULL;

            if ( _call_sysres != NULL && _call_cnode != NULL )
            {
                _value = metric->get_sev( llc, lls );
            }
            else
            {
                std::cerr << "DirectMetricEvaluation::eval: Indices " << _call_path_id << " or " << _ref_sysres_id << " are out of id range. Return 0";
            }
            break;
        case FIXED_METRIC_FULL_AGGR:
        {
            list_of_sysresources empty_ls;
            _value = metric->get_sev( llc, empty_ls );
        }
        break;
        case FIXED_METRIC_AGGR_SYS:
            _value = metric->get_sev( llc, lls );
            break;
        case FIXED_METRIC_NO_AGGR:
        case CONTEXT_METRIC:
        default:
            _value = metric->get_sev( llc, lls );
            break;
    }
    value = ( _value != NULL ) ? _value->getDouble() : 0.;
    if ( _value != NULL )
    {
        _value->Free();
    }
    return value;
}



double*
DirectMetricEvaluation::eval_row( const list_of_cnodes& lc, const list_of_sysresources& ls  ) const
{
    double*              result        = NULL;
    cube::Value*         _value        = NULL;
    cube::Cnode*         _call_cnode   = NULL;
    size_t               _call_path_id = ( size_t )-1;
    list_of_cnodes       llc           = lc;
    list_of_sysresources lls           = ls;
    for ( list_of_cnodes::iterator citer = llc.begin(); citer != llc.end(); ++citer )
    {
        cnode_pair& pair = *citer;
        pair.second = calltree_cf->flavour( pair.second );
    }
    for ( list_of_sysresources::iterator siter = lls.begin(); siter != lls.end(); ++siter )
    {
        sysres_pair& pair = *siter;
        pair.second = systree_sf->flavour( pair.second );
    }
    switch ( reference_type )
    {
        case METRIC_CALL_CALLPATH:
            _call_path_id = ( size_t )callpath_id->eval( llc, lls );
            _call_cnode   = ( cube->get_cnodev().size() >  _call_path_id ) ? cube->get_cnodev()[ _call_path_id ] : NULL;

            if ( _call_cnode != NULL )
            {
                _value =  metric->get_sev( llc, lls );
                result = services::create_row_of_doubles( row_size );
                double _d = ( _value != NULL ) ? _value->getDouble() : 0.;
                for ( size_t i = 0; i < row_size; ++i )
                {
                    result[ i ] = _d;
                }
            }
            else
            {
                std::cerr << "DirectMetricEvaluation::eval: Index " << _call_path_id << " is out of call path id range. Return 0";
            }
            _value->Free();
            break;
        case METRIC_CALL_FULL:
            std::cerr << "DirectMetricEvaluation::eval_row: RowWise call is not defined.";
            break;
        case FIXED_METRIC_FULL_AGGR:
        {
            list_of_sysresources empty_ls;
            _value = metric->get_sev( llc, empty_ls );
            double _d = ( _value != NULL ) ? _value->getDouble() : 0.;
            result = services::create_row_of_doubles( row_size );
            for ( size_t i = 0; i < row_size; ++i )
            {
                result[ i ] = _d;
            }
            _value->Free();
        }
        break;
        case FIXED_METRIC_AGGR_SYS:
        {
            _value = metric->get_sev( llc, lls );
            result = services::create_row_of_doubles( row_size );
            double _d = ( _value != NULL ) ? _value->getDouble() : 0.;
            for ( size_t i = 0; i < row_size; ++i )
            {
                result[ i ] = _d;
            }
            _value->Free();
        }
        break;
        case FIXED_METRIC_NO_AGGR:
        case CONTEXT_METRIC:
        default:
        {
            cube::Value** _v = metric->get_sevs( llc );
            result = services::transform_values_to_doubles( _v, row_size );
            services::delete_row_of_values( _v, row_size );
        }
        break;
    }
    return result;
}
