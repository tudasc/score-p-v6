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


/**
 * \file Cube.cpp
 * \brief Defines methods of the class cube and IO-interface.
 *
 */

// PGI compiler replaces all ofstream.open() calls by open64 and then cannot find a propper one. Result -> compilation error
#if !defined( __PGI ) && !defined( __CRAYXT )  && !defined( __CRAYXE )
#define _FILE_OFFSET_BITS 64
#endif


#include "config.h"
#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeValue.h"
#include "CubeMetric.h"
#include "CubeRegion.h"
#include "CubeServices.h"
#include "Cube.h"


using namespace std;
using namespace cube;





// ------------------- ANALYSIS PART --------------------------


Value*
Cube::get_sev_adv( Metric* metric, CalculationFlavour mf, Cnode* cnode, CalculationFlavour cnf, Sysres* sys, CalculationFlavour sf )
{
    Value* v = metric->get_sev_adv( cnode, cnf, sys, sf );
    if ( v == NULL )
    {
        return v;
    }
    if ( mf == cube::CUBE_CALCULATE_EXCLUSIVE )
    {
        for ( unsigned i = 0; i < metric->num_children(); i++ )                                                                                                // recursiv call for  children of the metric
        {
            Metric* _met = metric->get_child( i );
            Value*  _v   = _met->get_sev_adv( cnode, cnf, sys, sf );
            if ( _v == NULL )
            {
                continue;
            }
            v->
            operator-=( _v );

            _v->Free();
        }
    }
    return v;
}



double
Cube::get_sev( Metric* metric, CalculationFlavour mf, Cnode* cnode, CalculationFlavour cnf, Sysres* sysres, CalculationFlavour sf )
{
    Value* v = get_sev_adv( metric, mf, cnode, cnf, sysres, sf );
    double d = v->getDouble();
    v->Free();
    return d;
}





Value*
Cube::get_sev_adv( Metric* metric, CalculationFlavour mf, Region* region, CalculationFlavour rf, Sysres* sys, CalculationFlavour sf )
{
    if ( metric->isBuildIn() )
    {
        double _ret = get_sev( metric, mf, region, rf,  sys, sf );
        Value* _v   = metric->get_metric_value();
        ( *_v ) = _ret;
        return _v;
    }
    else
    {
        CalculationFlavour _rf = rf;

        Value* value = NULL;
        // collectiong cnodes, which have to be calculated for region
        std::vector<Cnode*>v;
        std::vector<Cnode*>cnodes = get_cnodev();
        if ( region->is_subroutines() )                                                                                        // subrouties have to be calculated
        {
            for ( std::vector<Cnode*>::iterator citer = cnodes.begin(); citer != cnodes.end(); ++citer )
            {
                // if the call item's callee is the selected region
                // then take all its subroutines
                if ( ( *citer )->get_callee() == region )
                {
                    for ( unsigned j = 0; j < ( *citer )->num_children(); j++ )
                    {
                        if (  ( ( *citer )->get_child( j ) )->get_callee() != region )
                        {
                            v.push_back( ( *citer )->get_child( j ) );
                        }
                    }
                }
            }
            for ( unsigned i = 0; i < v.size(); i++ )
            {
                for ( unsigned j = 0; j < v[ i ]->num_children(); j++ )
                {
                    if ( ( v[ i ]->get_child( j ) )->get_callee() != region )
                    {
                        v.push_back( v[ i ]->get_child( j ) );
                    }
                }
            }
            _rf = cube::CUBE_CALCULATE_EXCLUSIVE;                                                          // force the exclusve calculation it the case of subroutines calculation.
        }
        else                                                                                               // region
        {
            for ( std::vector<Cnode*>::iterator citer = cnodes.begin(); citer != cnodes.end(); ++citer )
            {
                if ( ( *citer )->get_callee() == region )
                {
                    v.push_back( *citer );
                }
            }
        }

        for ( std::vector<Cnode*>::iterator viter = v.begin(); viter != v.end(); ++viter )
        {
            Value* _v = get_sev_adv( metric, cube::CUBE_CALCULATE_INCLUSIVE, ( *viter ), _rf, sys, sf );
            if ( value == NULL )
            {
                value = _v;
            }
            else
            {
                if ( _v != NULL )
                {
                    value->
                    operator+=( _v );

                    _v->Free();
                }
            }
        }


        if ( mf == cube::CUBE_CALCULATE_EXCLUSIVE )
        {
            for ( unsigned i = 0; i < metric->num_children(); i++ )                                                                                        // recursiv call for  children of the metric
            {
                Metric* _met = metric->get_child( i );
                Value*  _v   = get_sev_adv( _met, cube::CUBE_CALCULATE_INCLUSIVE, region, rf, sys, sf );
                if ( _v == NULL )
                {
                    continue;
                }
                if ( value == NULL )
                {
                    value = _v->clone();
                }
                value->
                operator-=( _v );

                _v->Free();
            }
        }
        return value;
    }
}







double
Cube::get_sev( Metric* metric, CalculationFlavour mf, Region* region, CalculationFlavour rnf, Sysres* sysres, CalculationFlavour sf )
{
    if ( !metric->isBuildIn() )
    {
        Value* v = get_sev_adv( metric, mf, region, rnf, sysres, sf );
        if ( v == NULL )
        {
            return 0.;
        }
        double d = v->getDouble();
        v->Free();
        return d;
    }
    else
    {
        CalculationFlavour _rf = rnf;

        double value = 0.;
        // collectiong cnodes, which have to be calculated for region
        std::vector<Cnode*>v;
        std::vector<Cnode*>cnodes = get_cnodev();
        if ( region->is_subroutines() )                                                                                        // subrouties have to be calculated
        {
            for ( std::vector<Cnode*>::iterator citer = cnodes.begin(); citer != cnodes.end(); ++citer )
            {
                // if the call item's callee is the selected region
                // then take all its subroutines
                if ( ( *citer )->get_callee() == region )
                {
                    for ( unsigned j = 0; j < ( *citer )->num_children(); j++ )
                    {
                        if (  ( ( *citer )->get_child( j ) )->get_callee() != region )
                        {
                            v.push_back( ( *citer )->get_child( j ) );
                        }
                    }
                }
            }
            for ( unsigned i = 0; i < v.size(); i++ )
            {
                for ( unsigned j = 0; j < v[ i ]->num_children(); j++ )
                {
                    if ( ( v[ i ]->get_child( j ) )->get_callee() != region )
                    {
                        v.push_back( v[ i ]->get_child( j ) );
                    }
                }
            }
            _rf = cube::CUBE_CALCULATE_EXCLUSIVE;                                                          // force the exclusve calculation it the case of subroutines calculation.
        }
        else                                                                                               // region
        {
            for ( std::vector<Cnode*>::iterator citer = cnodes.begin(); citer != cnodes.end(); ++citer )
            {
                if ( ( *citer )->get_callee() == region )
                {
                    v.push_back( *citer );
                }
            }
        }

        for ( std::vector<Cnode*>::iterator viter = v.begin(); viter != v.end(); ++viter )
        {
            double _v = get_sev( metric, cube::CUBE_CALCULATE_INCLUSIVE, ( *viter ), _rf, sysres, sf );
            value += _v;
        }


        if ( mf == cube::CUBE_CALCULATE_EXCLUSIVE )
        {
            for ( unsigned i = 0; i < metric->num_children(); i++ )                                                                                        // recursiv call for  children of the metric
            {
                Metric* _met = metric->get_child( i );
                double  _v   = get_sev( _met, cube::CUBE_CALCULATE_INCLUSIVE, region, rnf, sysres, sf );
                value -= _v;
            }
        }
        return value;
    }
}










Value*
Cube::get_sev_adv( Metric* metric, CalculationFlavour mf, Cnode* cnode, CalculationFlavour cnf )
{
    if ( metric->isBuildIn() )
    {
        double _ret = get_sev( metric, mf, cnode, cnf );
        Value* _v   = metric->get_metric_value();
        ( *_v ) = _ret;
        return _v;
    }
    else
    {
        Value* v = metric->get_sev_adv( cnode, cnf );

        if ( v == NULL )
        {
            return v;
        }

        if ( mf == cube::CUBE_CALCULATE_EXCLUSIVE )
        {
            for ( unsigned i = 0; i < metric->num_children(); i++ )                                                                                            // recursiv call for  children of the metric
            {
                Metric* _met = metric->get_child( i );
                Value*  _v   = get_sev_adv( _met, cube::CUBE_CALCULATE_INCLUSIVE, cnode, cnf );
                if ( _v == NULL )
                {
                    continue;
                }
                v->
                operator-=( _v );

                _v->Free();
            }
        }
        return v;
    }
}




double
Cube::get_sev( Metric* metric, CalculationFlavour mf, Cnode* cnode, CalculationFlavour cnf )
{
    if ( !metric->isBuildIn() )
    {
        Value* v = get_sev_adv( metric, mf, cnode, cnf );
        if ( v == NULL )
        {
//         cerr << "get_sev_adv(metric, mf, cnode, cnf) returned NULL" << endl;
            return 0.;
        }
        double d = v->getDouble();
        v->Free();
        return d;
    }
    else
    {
        double v = metric->get_sev( cnode, cnf );
        if ( mf == cube::CUBE_CALCULATE_EXCLUSIVE )
        {
            for ( unsigned i = 0; i < metric->num_children(); i++ )                                                                                            // recursiv call for  children of the metric
            {
                Metric* _met = metric->get_child( i );
                double  _v   = get_sev( _met, cube::CUBE_CALCULATE_INCLUSIVE, cnode, cnf );
                v -= _v;
            }
        }
        return v;
    }
}









Value*
Cube::get_sev_adv( Metric* metric, CalculationFlavour mf, Sysres* sys, CalculationFlavour sf )
{
    if ( metric->isBuildIn() )
    {
        double _ret = get_sev( metric, mf, sys, sf );
        Value* _v   = metric->get_metric_value();
        _v->
        operator=( _ret );

        return _v;
    }
    else
    {
        // over cnode roots
        const std::vector<Cnode*>& roots = get_root_cnodev();
        Value*                     v     = NULL;
        for ( std::vector<Cnode*>::const_iterator citer = roots.begin(); citer != roots.end(); ++citer )
        {
            Cnode* cnode_root = ( *citer );

            Value* inc_metric_v = metric->get_sev_adv( cnode_root, cube::CUBE_CALCULATE_INCLUSIVE, sys, sf );
            if ( inc_metric_v == NULL )
            {
                return inc_metric_v;
            }
            if ( v == NULL )
            {
                v = inc_metric_v;
            }
            else
            {
                v->
                operator+=( inc_metric_v );

                inc_metric_v->Free();
            }
        }
        if ( mf == cube::CUBE_CALCULATE_EXCLUSIVE )
        {
            for ( unsigned i = 0; i < metric->num_children(); i++ )                                                                                        // recursiv call for  children of the metric
            {
                Metric* _met = metric->get_child( i );
                Value*  _v   = get_sev_adv( _met, cube::CUBE_CALCULATE_INCLUSIVE, sys, sf );
                if ( _v == NULL )
                {
                    continue;
                }
                v->
                operator-=( _v );

                _v->Free();
            }
        }
        return v;
    }
}






double
Cube::get_sev( Metric* metric, CalculationFlavour mf, Sysres* sys, CalculationFlavour sf )
{
    if ( !metric->isBuildIn() )
    {
        Value* v = get_sev_adv( metric, mf, sys, sf );
        if ( v == NULL )
        {
            return 0.;
        }
        double d = v->getDouble();
        v->Free();
        return d;
    }
    else
    {
        // over cnode roots
        const std::vector<Cnode*>& roots = get_root_cnodev();
        double                     v     = 0.;
        for ( std::vector<Cnode*>::const_iterator citer = roots.begin(); citer != roots.end(); ++citer )
        {
            Cnode* cnode_root = ( *citer );

            double inc_metric_v = metric->get_sev( cnode_root, cube::CUBE_CALCULATE_INCLUSIVE, sys, sf );
            v += inc_metric_v;
        }
        if ( mf == cube::CUBE_CALCULATE_EXCLUSIVE )
        {
            for ( unsigned i = 0; i < metric->num_children(); i++ )                                                                                        // recursiv call for  children of the metric
            {
                Metric* _met = metric->get_child( i );
                double  _v   = get_sev( _met, cube::CUBE_CALCULATE_INCLUSIVE, sys, sf );
                v -= _v;
            }
        }
        return v;
    }
}














Value*
Cube::get_sev_adv( Metric* metric, CalculationFlavour mf, Region* region, CalculationFlavour rf )
{
    if ( metric->isBuildIn() )
    {
        double _ret = get_sev( metric, mf, region, rf );
        Value* _v   = metric->get_metric_value();
        _v->
        operator=( _ret );

        return _v;
    }
    else
    {
        CalculationFlavour _rf = rf;

        Value* value = NULL;
        // collectiong cnodes, which have to be calculated for region
        std::vector<Cnode*>v;
        std::vector<Cnode*>cnodes = get_cnodev();

        if ( region->is_subroutines() )                                                                                        // subrouties have to be calculated
        {
            for ( std::vector<Cnode*>::iterator citer = cnodes.begin(); citer != cnodes.end(); ++citer )
            {
                // if the call item's callee is the selected region
                // then take all its subroutines
                if ( ( *citer )->get_callee() == region )
                {
                    for ( unsigned j = 0; j < ( *citer )->num_children(); j++ )
                    {
                        if (  ( ( *citer )->get_child( j ) )->get_callee() != region )
                        {
                            v.push_back( ( *citer )->get_child( j ) );
                        }
                    }
                }
            }
            for ( unsigned i = 0; i < v.size(); i++ )
            {
                for ( unsigned j = 0; j < v[ i ]->num_children(); j++ )
                {
                    if ( ( v[ i ]->get_child( j ) )->get_callee() != region )
                    {
                        v.push_back( v[ i ]->get_child( j ) );
                    }
                }
            }
            _rf = cube::CUBE_CALCULATE_EXCLUSIVE;                                                          // force the exclusve calculation it the case of subroutines calculation.
        }
        else                                                                                               // region->is_subroutines()
        {
            for ( std::vector<Cnode*>::iterator citer = cnodes.begin(); citer != cnodes.end(); ++citer )
            {
                if ( ( *citer )->get_callee() == region )
                {
                    v.push_back( *citer );
                }
            }
        }

        for ( std::vector<Cnode*>::iterator viter = v.begin(); viter != v.end(); ++viter )
        {
            Value* _v = get_sev_adv( metric, cube::CUBE_CALCULATE_INCLUSIVE, ( *viter ), _rf );
            if ( value == NULL )
            {
                value = _v;
            }
            else
            {
                if ( _v != NULL )
                {
                    value->
                    operator+=( _v );

                    _v->Free();
                }
            }
        }


        if ( mf == cube::CUBE_CALCULATE_EXCLUSIVE )
        {
            for ( unsigned i = 0; i < metric->num_children(); i++ )                                                                                        // recursiv call for  children of the metric
            {
                Metric* _met = metric->get_child( i );
                Value*  _v   = get_sev_adv( _met, cube::CUBE_CALCULATE_INCLUSIVE, region, rf );
                if ( _v == NULL )
                {
                    continue;
                }
                value->
                operator-=( _v );

                _v->Free();
            }
        }
        return value;
    }
}







double
Cube::get_sev( Metric* metric, CalculationFlavour mf, Region* region, CalculationFlavour rf )
{
    if ( !metric->isBuildIn() )
    {
        Value* v = get_sev_adv( metric, mf, region, rf );
        if ( v == NULL )
        {
            return 0.;
        }
        double d = v->getDouble();
        v->Free();
        return d;
    }
    else
    {
        CalculationFlavour _rf = rf;

        double value = 0.;
        // collectiong cnodes, which have to be calculated for region
        std::vector<Cnode*>v;
        std::vector<Cnode*>cnodes = get_cnodev();

        if ( region->is_subroutines() )                                                                                        // subrouties have to be calculated
        {
            for ( std::vector<Cnode*>::iterator citer = cnodes.begin(); citer != cnodes.end(); ++citer )
            {
                // if the call item's callee is the selected region
                // then take all its subroutines
                if ( ( *citer )->get_callee() == region )
                {
                    for ( unsigned j = 0; j < ( *citer )->num_children(); j++ )
                    {
                        if (  ( ( *citer )->get_child( j ) )->get_callee() != region )
                        {
                            v.push_back( ( *citer )->get_child( j ) );
                        }
                    }
                }
            }
            for ( unsigned i = 0; i < v.size(); i++ )
            {
                for ( unsigned j = 0; j < v[ i ]->num_children(); j++ )
                {
                    if ( ( v[ i ]->get_child( j ) )->get_callee() != region )
                    {
                        v.push_back( v[ i ]->get_child( j ) );
                    }
                }
            }
            _rf = cube::CUBE_CALCULATE_EXCLUSIVE;                                                          // force the exclusve calculation it the case of subroutines calculation.
        }
        else                                                                                               // region->is_subroutines()
        {
            for ( std::vector<Cnode*>::iterator citer = cnodes.begin(); citer != cnodes.end(); ++citer )
            {
                if ( ( *citer )->get_callee() == region )
                {
                    v.push_back( *citer );
                }
            }
        }

        for ( std::vector<Cnode*>::iterator viter = v.begin(); viter != v.end(); ++viter )
        {
            double _v = get_sev( metric, cube::CUBE_CALCULATE_INCLUSIVE, ( *viter ), _rf );
            value += _v;
        }


        if ( mf == cube::CUBE_CALCULATE_EXCLUSIVE )
        {
            for ( unsigned i = 0; i < metric->num_children(); i++ )                                                                                        // recursiv call for  children of the metric
            {
                Metric* _met = metric->get_child( i );
                double  _v   = get_sev( _met, cube::CUBE_CALCULATE_INCLUSIVE, region, rf );
                value -= _v;
            }
        }
        return value;
    }
}

Value*
Cube::get_sev_adv( Metric* metric, CalculationFlavour mf )                                                                                             // sum over roots of calltree
{
    if ( metric->isBuildIn() )
    {
        double _ret = get_sev( metric, mf );
        Value* _v   = metric->get_metric_value();
        _v->
        operator=( _ret );

        return _v;
    }
    else
    {
        const vector<Cnode*>& croots = get_root_cnodev();
        Value*                v      = NULL;

        for ( unsigned i = 0; i < croots.size(); i++ )
        {
            Value* _v = get_sev_adv( metric, cube::CUBE_CALCULATE_INCLUSIVE, croots[ i ], cube::CUBE_CALCULATE_INCLUSIVE );
            if ( _v == NULL )
            {
                continue;
            }
            if ( v == NULL )
            {
                v = _v;
            }
            else
            {
                v->
                operator+=( _v );

                _v->Free();
            }
        }
        if ( mf == cube::CUBE_CALCULATE_INCLUSIVE )
        {
            return v;
        }

        if ( mf == cube::CUBE_CALCULATE_EXCLUSIVE )
        {
            Value* _v = NULL;
            for ( unsigned j = 0; j < metric->num_children(); j++ )                                                                                        // recursiv call for  children of the metric
            {
                Metric* _met = metric->get_child( j );
                Value*  __v  = get_sev_adv( _met, cube::CUBE_CALCULATE_INCLUSIVE );

                if ( __v == NULL )
                {
                    continue;
                }
                if ( _v == NULL )
                {
                    _v = __v;
                }
                else
                {
                    _v->
                    operator+=( __v );

                    __v->Free();
                }
            }

            if ( _v != NULL )
            {
                if ( v == NULL )
                {
                    v = _v;
                }
                else
                {
                    v->
                    operator-=( _v );

                    _v->Free();
                }
            }
            return v;
        }
        return v;
    }
}





double
Cube::get_sev( Metric* metric, CalculationFlavour mf )                                                                                             // sum over roots of calltree
{
    if ( !metric->isBuildIn() )
    {
        Value* v = get_sev_adv( metric, mf );
        double d = v->getDouble();
        v->Free();
        return d;
    }
    else
    {
        const vector<Cnode*>& croots = get_root_cnodev();
        double                ret    = 0.;

        for ( unsigned i = 0; i < croots.size(); i++ )
        {
            double _v = get_sev( metric, cube::CUBE_CALCULATE_INCLUSIVE, croots[ i ], cube::CUBE_CALCULATE_INCLUSIVE );
            ret += _v;
        }
        if ( mf == cube::CUBE_CALCULATE_EXCLUSIVE )
        {
            double _v = 0.;
            for ( unsigned j = 0; j < metric->num_children(); j++ )                                                                                        // recursiv call for  children of the metric
            {
                Metric* _met = metric->get_child( j );
                double  __v  = get_sev( _met, cube::CUBE_CALCULATE_INCLUSIVE );
                _v += __v;
            }

            ret -= _v;
        }
        return ret;
    }
}




// an actual call, which performs the calculation (delegates it to the metric)
void
Cube::get_system_tree_sevs_adv( Metric*              metric,
                                CalculationFlavour   mf,
                                Cnode*               cnode,
                                CalculationFlavour   cnf,
                                std::vector<Value*>& inclusive_values,
                                std::vector<Value*>& exclusive_values
                                )
{
    list_of_cnodes lcnodes;
    cnode_pair     pair;
    pair.first  = cnode;
    pair.second = cnf;
    lcnodes.push_back( pair );

    std::vector<Value*>_tmp_inclusive_values;
    std::vector<Value*>_tmp_exclusive_values;

    metric->get_system_tree_sevs(  lcnodes, inclusive_values, exclusive_values );

    if ( mf == cube::CUBE_CALCULATE_EXCLUSIVE )
    {
        for ( unsigned c = 0; c < metric->num_children(); c++ )                                                                                        // recursiv call for  children of the metric
        {
            Metric* _met = metric->get_child( c );
            _met->get_system_tree_sevs( lcnodes, _tmp_inclusive_values, _tmp_exclusive_values );

            for ( size_t j = 0; j < _tmp_inclusive_values.size(); j++ )
            {
                inclusive_values[ j ]->
                operator-=( _tmp_inclusive_values[ j ] );

                exclusive_values[ j ]->
                operator-=( _tmp_exclusive_values[ j ] );

                _tmp_inclusive_values[ j ]->Free();
                _tmp_exclusive_values[ j ]->Free();
            }
            _tmp_inclusive_values.clear();
            _tmp_exclusive_values.clear();
        }
    }
    return;
}



// an actual call, which performs the calculation (delegates it to the metric)
void
Cube::get_system_tree_sevs_adv( Metric*              metric,
                                CalculationFlavour   mf,
                                Region*              region,
                                CalculationFlavour   rnf,
                                std::vector<Value*>& inclusive_values,
                                std::vector<Value*>& exclusive_values
                                )
{
    std::vector<Value*>_tmp_inclusive_values;
    std::vector<Value*>_tmp_exclusive_values;
    list_of_regions    regions;
    region_pair        pair;
    pair.first  = region;
    pair.second = rnf;
    regions.push_back( pair );
    list_of_cnodes lcnodes = cube::services::expand_regions( this, regions );

    metric->get_system_tree_sevs( lcnodes, _tmp_inclusive_values, _tmp_exclusive_values );

    if ( mf == cube::CUBE_CALCULATE_EXCLUSIVE )
    {
        for ( unsigned c = 0; c < metric->num_children(); c++ )                                                                                        // recursiv call for  children of the metric
        {
            Metric* _met = metric->get_child( c );
            metric->get_system_tree_sevs( lcnodes, _tmp_inclusive_values, _tmp_exclusive_values );

            for ( size_t j = 0; j < _tmp_inclusive_values.size(); j++ )
            {
                inclusive_values[ j ]->
                operator-=( _tmp_inclusive_values[ j ] );

                exclusive_values[ j ]->
                operator-=( _tmp_exclusive_values[ j ] );

                _tmp_inclusive_values[ j ]->Free();
                _tmp_exclusive_values[ j ]->Free();
            }
            _tmp_inclusive_values.clear();
            _tmp_exclusive_values.clear();
        }
    }
    return;
}




// VErsion for the case, system tree pane is in the middle.
void
Cube::get_system_tree_sevs_adv( Metric*              metric,
                                CalculationFlavour   mf,
                                std::vector<Value*>& inclusive_values,
                                std::vector<Value*>& exclusive_values
                                )
{
    list_of_cnodes                   lcnodes;
    const std::vector<cube::Cnode*>& croots = get_root_cnodev();
    for ( std::vector<cube::Cnode*>::const_iterator c_iter = croots.begin(); c_iter != croots.end(); ++c_iter )
    {
        cnode_pair pair;
        pair.first  = *c_iter;
        pair.second = cube::CUBE_CALCULATE_INCLUSIVE;
        lcnodes.push_back( pair );
    }

    metric->get_system_tree_sevs( lcnodes, inclusive_values, exclusive_values );

    if ( mf == cube::CUBE_CALCULATE_EXCLUSIVE )
    {
        std::vector<Value*>_tmp_inclusive_values;
        std::vector<Value*>_tmp_exclusive_values;
        for ( unsigned c = 0; c < metric->num_children(); c++ )                                                                                        // recursiv call for  children of the metric
        {
            Metric* _met = metric->get_child( c );
            for ( unsigned i = 0; i < croots.size(); i++ )
            {
                _met->get_system_tree_sevs( lcnodes, _tmp_inclusive_values, _tmp_exclusive_values );

                for ( size_t j = 0; j < _tmp_inclusive_values.size(); j++ )
                {
                    inclusive_values[ j ]->
                    operator-=( _tmp_inclusive_values[ j ] );

                    exclusive_values[ j ]->
                    operator-=( _tmp_exclusive_values[ j ] );

                    _tmp_inclusive_values[ j ]->Free();
                    _tmp_exclusive_values[ j ]->Free();
                }
                _tmp_inclusive_values.clear();
                _tmp_exclusive_values.clear();
            }
        }
    }
    return;
}






// an actual call, which performs the calculation (delegates it to the metric)
void
Cube::get_system_tree_sevs( Metric*              metric,
                            CalculationFlavour   mf,
                            Cnode*               cnode,
                            CalculationFlavour   cnf,
                            std::vector<double>& inclusive_values,
                            std::vector<double>& exclusive_values
                            )
{
    std::vector<double>_tmp_inclusive_values;
    std::vector<double>_tmp_exclusive_values;
    list_of_cnodes     lcnodes;
    cnode_pair         pair;
    pair.first  = cnode;
    pair.second = cnf;
    lcnodes.push_back( pair );

    metric->get_system_tree_sevs(  lcnodes, inclusive_values, exclusive_values );
    if ( mf == cube::CUBE_CALCULATE_EXCLUSIVE )
    {
        for ( unsigned c = 0; c < metric->num_children(); c++ )            // recursiv call for  children of the metric
        {
            Metric* _met = metric->get_child( c );
            _met->get_system_tree_sevs( lcnodes, _tmp_inclusive_values, _tmp_exclusive_values );

            for ( size_t j = 0; j < _tmp_inclusive_values.size(); j++ )
            {
                inclusive_values[ j ] -= _tmp_inclusive_values[ j ];
                exclusive_values[ j ] -= _tmp_exclusive_values[ j ];
            }
            _tmp_inclusive_values.clear();
            _tmp_exclusive_values.clear();
        }
    }
    return;
}


// an actual call, which performs the calculation (delegates it to the metric)
void
Cube::get_system_tree_sevs( Metric*              metric,
                            CalculationFlavour   mf,
                            Region*              region,
                            CalculationFlavour   rnf,
                            std::vector<double>& inclusive_values,
                            std::vector<double>& exclusive_values
                            )
{
    std::vector<double>_tmp_inclusive_values;
    std::vector<double>_tmp_exclusive_values;
    list_of_regions    regions;
    region_pair        pair;
    pair.first  = region;
    pair.second = rnf;
    regions.push_back( pair );
    list_of_cnodes lcnodes = cube::services::expand_regions( this, regions );
    metric->get_system_tree_sevs( lcnodes, inclusive_values, exclusive_values );
    if ( mf == cube::CUBE_CALCULATE_EXCLUSIVE )
    {
        for ( unsigned c = 0; c < metric->num_children(); c++ )            // recursiv call for  children of the metric
        {
            Metric* _met = metric->get_child( c );
            _met->get_system_tree_sevs( lcnodes, _tmp_inclusive_values, _tmp_exclusive_values );

            for ( size_t j = 0; j < _tmp_inclusive_values.size(); j++ )
            {
                inclusive_values[ j ] -= _tmp_inclusive_values[ j ];
                exclusive_values[ j ] -= _tmp_exclusive_values[ j ];
            }
            _tmp_inclusive_values.clear();
            _tmp_exclusive_values.clear();
        }
    }
    return;
}



// VErsion for the case, system tree pane is in the middle.
void
Cube::get_system_tree_sevs( Metric*              metric,
                            CalculationFlavour   mf,
                            std::vector<double>& inclusive_values,
                            std::vector<double>& exclusive_values
                            )
{
    list_of_cnodes                   lcnodes;
    const std::vector<cube::Cnode*>& croots = get_root_cnodev();
    for ( std::vector<cube::Cnode*>::const_iterator c_iter = croots.begin(); c_iter != croots.end(); ++c_iter )
    {
        cnode_pair pair;
        pair.first  = *c_iter;
        pair.second = cube::CUBE_CALCULATE_INCLUSIVE;
        lcnodes.push_back( pair );
    }
    metric->get_system_tree_sevs( lcnodes, inclusive_values, exclusive_values );
    if ( mf == cube::CUBE_CALCULATE_EXCLUSIVE )
    {
        std::vector<double>_tmp_inclusive_values;
        std::vector<double>_tmp_exclusive_values;
        for ( unsigned c = 0; c < metric->num_children(); c++ )                                                                                        // recursiv call for  children of the metric
        {
            Metric* _met = metric->get_child( c );
            for ( unsigned i = 0; i < croots.size(); i++ )
            {
                _met->get_system_tree_sevs( lcnodes, _tmp_inclusive_values, _tmp_exclusive_values );

                for ( size_t j = 0; j < _tmp_inclusive_values.size(); j++ )
                {
                    inclusive_values[ j ] -= _tmp_inclusive_values[ j ];
                    exclusive_values[ j ] -= _tmp_exclusive_values[ j ];
                }
                _tmp_inclusive_values.clear();
                _tmp_exclusive_values.clear();
            }
        }
    }
    return;
}


double
Cube::get_sev( Cnode*,
               CalculationFlavour )
{
    return 0.;                                                                                            // coz this call is done by call tree, being in almost left panel
}

double
Cube::get_sev( Region*,
               CalculationFlavour )
{
    return 0.;                                                                                            // coz this call is done by flattree, being in almost left panel
}

double
Cube::get_sev( Sysres*,
               CalculationFlavour )
{
    return 0.;                                                                                            // coz this call is done by system tree, being in almost left panel
}
