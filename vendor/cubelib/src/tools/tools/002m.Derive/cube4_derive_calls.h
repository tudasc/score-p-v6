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



#ifndef CUBE_DERIVE_CALLS
#define CUBE_DERIVE_CALLS

#include <vector>
#include "CubePL1Driver.h"
using namespace std;

namespace cube
{
/// specifies kind of rate is getting calculated
enum derivedMetric { PREDERIVED_METRIC_EXCLUSIVE = 0, PREDERIVED_METRIC_INCLUSIVE = 1, METRIC_EXCLUSIVE = 2, METRIC_INCLUSIVE = 3, POSTDERIVED_METRIC = 4 };
enum InclExclType { INCLUSIVE = 0, EXCLUSIVE = 1 };
enum PrePostType { SIMPLE = 0, PREDERIVED = 1, POSTDERIVED = 2 };

Metric*
find_metric( Cube& cube, std::string name )
{
    vector<Metric*> metv = cube.get_metv();
    for ( vector<Metric*>::iterator m_iter = metv.begin(); m_iter < metv.end(); ++m_iter )
    {
        if ( ( *m_iter )->get_disp_name().compare( name ) == 0 )
        {
            return *m_iter;
        }
    }
    return NULL;
}



void
add_derived_metric( Cube& outCube, Cube& cube, std::string _parent_metric, std::string _target_metric, derivedMetric _kind_of_metric,  std::string& _expression )
{
    Metric* parent_metric     = find_metric( cube, _parent_metric );     // metrics should exist in both cubes
    Metric* new_parent_metric = find_metric( outCube, _parent_metric );

    std::string _to_test = std::string( "<cubepl>" ) + _expression + std::string( "</cubepl>" );
    std::string error_in_expression;
    if ( !cube.get_cubepl_driver()->test( _to_test, error_in_expression ) )
    {
        throw RuntimeError( "Syntax Error in CubePL expression: " +  error_in_expression );
    }


    TypeOfMetric       _new_metric_type    = cube::CUBE_METRIC_EXCLUSIVE;
    TypeOfMetric       _source_metric_type = cube::CUBE_METRIC_PREDERIVED_EXCLUSIVE;
    CalculationFlavour cf                  = cube::CUBE_CALCULATE_EXCLUSIVE;
    switch ( _kind_of_metric )
    {
        case METRIC_EXCLUSIVE:
            _new_metric_type    = cube::CUBE_METRIC_EXCLUSIVE;
            cf                  = cube::CUBE_CALCULATE_EXCLUSIVE;
            _source_metric_type = cube::CUBE_METRIC_PREDERIVED_EXCLUSIVE;
            break;
        case METRIC_INCLUSIVE:
            _new_metric_type    = cube::CUBE_METRIC_INCLUSIVE;
            cf                  = cube::CUBE_CALCULATE_INCLUSIVE;
            _source_metric_type = cube::CUBE_METRIC_PREDERIVED_INCLUSIVE;
            break;
        case PREDERIVED_METRIC_EXCLUSIVE:
            _new_metric_type = cube::CUBE_METRIC_PREDERIVED_EXCLUSIVE;
            break;
        case PREDERIVED_METRIC_INCLUSIVE:
            _new_metric_type = cube::CUBE_METRIC_PREDERIVED_INCLUSIVE;
            break;
        case POSTDERIVED_METRIC:
            _new_metric_type = cube::CUBE_METRIC_POSTDERIVED;
            break;
    }

    Metric* target_metric = outCube.def_met(
        _target_metric,
        _target_metric,
        "DOUBLE",
        "",
        "",
        "https://url.de",
        "Created metric using tool cube_derive with a CubePL expression \"" + _expression + "\"",
        new_parent_metric,
        _new_metric_type,
        _expression );
    if ( _new_metric_type == cube::CUBE_METRIC_EXCLUSIVE ||
         _new_metric_type == cube::CUBE_METRIC_INCLUSIVE
         )
    {
        Metric* created_metric = cube.def_met(  _target_metric, _target_metric, std::string( "DOUBLE" ), "", "", "https://url.de",
                                                "Created metric using tool cube_derive with a CubePL expression \"" + _expression + "\"", parent_metric, _source_metric_type, _expression );     // we use this metric to calculate values

        CubeMapping cubeMap;


        cnode_merge( outCube, cube, cubeMap );
        sysres_merge( outCube, cube, cubeMap, false, false );



        CalculationFlavour sf = cube::CUBE_CALCULATE_EXCLUSIVE;




//         createMapping( outCube, cube, cubeMap, false );
        map<Cnode*, Cnode*>::iterator   citer;
        map<Thread*, Thread*>::iterator siter;
        for ( citer = cubeMap.cnodem.begin(); citer != cubeMap.cnodem.end(); ++citer )
        {
            for ( siter = cubeMap.sysm.begin(); siter != cubeMap.sysm.end(); ++siter )
            {
                double val1 = cube.get_sev( created_metric, cube::CUBE_CALCULATE_INCLUSIVE, citer->first, cf, siter->first, sf );
                outCube.set_sev( target_metric, citer->second, siter->second, val1 );
            }
        }
    }
}
}
#endif
