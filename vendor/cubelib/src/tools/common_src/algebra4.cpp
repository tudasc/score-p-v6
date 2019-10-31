/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2018                                                **
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
 *
 * \file algebra4.cpp
 * \brief Contains a set of functions allows to operate with a cube and parts of
   it (metrics tree, cnodes tree and so on).
 * Merging, comparison, copying and another operations.
 *
 ************************************************/
/******************************************

   Performance Algebra

 *******************************************/

#include "config.h"
#include <climits>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cfloat>
#include <errno.h>

#include "algebra4.h"
#include "algebra4-internals.h"


using namespace std;
using namespace cube;



/**
 * Merging of two cubes and returns the result as a new cube.
 *
 * It is done step-by-step by creating of an empty cube, merging dimensions and
   addtion in to the new cube old values for severities. If machines are equal
   the topology is copied too.
 */
void
cube::cube4_merge( Cube*          outCube,
                   Cube**         cubes,
                   const unsigned num,
                   bool           reduce,
                   bool           collapse,
                   bool           strict )
{
    CubeMapping* cmap = new CubeMapping[ num ];
    for ( unsigned i = 0; i < num; ++i )
    {
        cout << "INFO::Start operation \"MERGE\" with " << i << "-th cube..." << endl;

        cout << "INFO::Merging metric dimension...";
        metric_merge( *outCube, *( cubes[ i ] ), cmap[ i ] );
        cout << " done." << endl;

        cout << "INFO::Merging program dimension...";
        cnode_merge( *outCube, *( cubes[ i ] ), cmap[ i ] );
        cout << " done." << endl;

        cout << "INFO::Merging system dimension...";
        if ( !sysres_merge( *outCube, *( cubes[ i ] ), cmap[ i ], reduce, collapse, strict ) )
        {
            throw RuntimeError( " System tree seems to be incompatible to be unified in one common system tree. \n"
                                " You may want to collapse or reduce the system trees." );
        }
        cout << " done." << endl;


        cout << "INFO::Merging topologies...";
        merge_top( *outCube, *( cubes[ i ] ), *( cubes[ i ] ) );
        cout << " done." << endl;
    }
    outCube->initialize();
    cout << "INFO::Merge operation...";
    for ( unsigned i = 0; i < num; ++i )
    {
        set_sevs( *outCube, *( cubes[ i ] ), cmap[ i ] );
    }
    cout << " done." << endl;
    delete[] cmap;
}







/**
 * Creates a "cleaned" CUBE object containing only references items.
 */
void
cube::cube4_clean( Cube* outCube, Cube* lhsCube, bool reduce, bool collapse )
{
    CubeMapping lhsmap;
    cout << "INFO::Merging metric dimension...";
    metric_merge( *outCube, *lhsCube, lhsmap );
    cout << " done." << endl;

    cout << "INFO::Merging program dimension...";
    cnode_merge( *outCube, *lhsCube, lhsmap );
    cout << " done." << endl;

    cout << "INFO::Merging system dimension...";
    if ( !( sysres_merge( *outCube, *lhsCube, lhsmap, reduce, collapse ) ) )
    {
        cerr << endl << endl << " System tree seems to be incompatible fied in one common system tree. \n"
            " You may try options -c or -C. See help for further details. " << endl;
        exit( EXIT_FAILURE );
    }
    cout << " done." << endl;
    cout << "INFO::Adding topologies...";
    add_top( *outCube, *lhsCube, lhsmap );
    cout << " done." << endl;
    outCube->initialize();
    cout << "INFO::Copy data...";
    set_sevs( *outCube, *lhsCube, lhsmap );
    cout << " done." << endl;
    return;
}



/**
 * Compares "lhsCube" and "rhsCube".
 *
 * First the metric dimension. If not equal -> return "not equal", "false".
 * Then cnodes dimension, then the machine and at least the vales for severities.
 */
bool
cube::cube4_cmp( Cube* lhsCube, Cube* rhsCube )
{
    CubeMapping lhsmap, rhsmap;

    cout << " Compare metric dimensions...";
    if ( !compare_metric_dimensions( *lhsCube, *rhsCube ) )
    {
        cout << "not equal." << endl;
        return false;
    }
    cout << "equal." << endl;
    cout << " Compare calltree dimensions.";
    if ( !compare_calltree_dimensions( *lhsCube, *rhsCube ) )
    {
        cout << "not equal." << endl;
        return false;
    }
    cout << "equal." << endl;
    cout << " Compare system dimensions...";
    if (  !compare_system_dimensions( *lhsCube, *rhsCube ) )
    {
        cout << "not equal." << endl;
        return false;
    }
    else // lhsCube are equal ...
    {
        cout << "equal." << endl;
    }

    createMapping( *lhsCube, *rhsCube, lhsmap,  false );
    cout << " Compare data...";
    if ( !check_sev( *rhsCube, *lhsCube, lhsmap ) )
    {
        cout << "not equal." << endl;
        return false;
    }
    cout << "equal." << endl;
    return true;
}




/**
 * Creates a cut (???) of two cubes.
 */
void
cube::cube4_cut( Cube* outCube,  Cube* rhsCube, bool reduce, bool collapse,
                 const string& cn_root, const vector<string>& cn_prunes )
{
    if ( cn_root != "" )
    {
        vector<std::string>_cn_roots;
        _cn_roots.push_back( cn_root );

        if ( !regions_exists( *rhsCube, _cn_roots ) )
        {
            cerr << "ERROR: Region " << cn_root << " doesn't exist in the input file.";
            exit( EXIT_FAILURE );
        }
    }
    regions_exists( *rhsCube, cn_prunes ); // this produces warnings inside



    CubeMapping lhsmap, rhsmap;


    // Define mirror & attributes
    outCube->def_mirror( "http://www.fz-juelich.de/jsc/datapool/scalasca/" );
    outCube->def_attr( "CUBE_CT_AGGR", "SUM" );

    cout << "INFO::Merging metric dimension...";
    metric_merge( *outCube, *rhsCube, rhsmap );
    cout << " done." << endl;

    cout << "INFO::Merging program dimension...";
    if ( cnode_reroot( *outCube, *rhsCube, cn_root, cn_prunes, rhsmap ) == false )
    {
        return;
    }
    cout << " done." << endl;

    cout << "INFO::Merging system dimension...";
    if ( !sysres_merge( *outCube, *rhsCube, rhsmap, reduce, collapse ) )
    {
        cerr << endl << endl << " System tree seems to be incompatible fied in one common system tree. \n"
            " You may try options -c or -C. See help for further details. " << endl;
        exit( EXIT_FAILURE );
    }
    cout << " done." << endl;

    cout << "INFO::Adding topologies...";
    add_top( *outCube, *rhsCube, rhsmap );
    cout << " done." << endl;
    outCube->initialize();
    cout << "INFO::Copy data...";
    add_sev( *outCube, *rhsCube, rhsmap, 1. ); // aggregate metrics from pruned nodes
    cout << " done." << endl;
    return;
}






/**
 * Create a difference of two cube and returns the result as a new cube.
 *
 * It is done  step-by-step by creating of an empty cube, merging dimensions and addtion in to the new cube old values for severities multiplied with a +/- 1.
 */
void
cube::cube4_diff( Cube* outCube, Cube* minCube, Cube* subCube, bool reduce, bool collapse )
{
    CubeMapping lhsmap, rhsmap;

    cout << "INFO::Merging metric dimension...";
    metric_merge( *outCube, *minCube, lhsmap, UINT_TO_INT );
    metric_merge( *outCube, *subCube, rhsmap, UINT_TO_INT );
    cout << " done." << endl;

    cout << "INFO::Merging program dimension...";
    cnode_merge( *outCube, *minCube, lhsmap );
    cnode_merge( *outCube, *subCube, rhsmap );
    cout << " done." << endl;

    cout << "INFO::Merging system dimension...";
    if ( ( !sysres_merge( *outCube, *minCube, lhsmap, reduce, collapse ) )
         ||
         ( !sysres_merge( *outCube, *subCube, rhsmap, reduce, collapse ) )
         )
    {
        throw RuntimeError( " System tree seems to be incompatible to be unified in one common system tree. \n"
                            " You may want to collapse or reduce the system trees." );
    }
    cout << " done." << endl;
    cout << "INFO::Mapping severities...";
    cout << " done." << endl;

    cout << "INFO::Merging topologies...";
    merge_top( *outCube, *minCube, *subCube );
    cout << " done." << endl;
    outCube->initialize();

    cout << "INFO::Diff operation..." << flush;

    diff_sevs( *outCube, *minCube, lhsmap, *subCube, rhsmap );
    cout << " done." << endl;

    return;
}





void
cube::cube4_mean( Cube* outCube, Cube** cubes, const unsigned num,  bool reduce, bool collapse )
{
    CubeMapping* cmap = new CubeMapping[ num ];
    for ( unsigned i = 0; i < num; ++i )
    {
        cout << "INFO::Start operation \"MEAN\" with " << i << "-th cube..." << endl;
        cout << "INFO::Merging metric dimension...";
        metric_merge( *outCube, *( cubes[ i ] ), cmap[ i ] );
        cout << " done." << endl;
        cout << "INFO::Merging program dimension...";
        cnode_merge( *outCube, *( cubes[ i ] ), cmap[ i ] );
        cout << " done." << endl;
        cout << "INFO::Merging system dimension...";
        if ( !sysres_merge( *outCube, *( cubes[ i ] ), cmap[ i ], reduce, collapse ) )
        {
            throw RuntimeError( " System tree seems to be incompatible to be unified in one common system tree. \n"
                                " You may want to collapse or reduce the system trees." );
        }
        cout << " done." << endl;
        cout << "INFO::Adding topologies...";
        add_top( *outCube, *( cubes[ i ] ), cmap[ i ] );
        cout << " done." << endl;
    }
    outCube->initialize();
    cout << "INFO::Mean operation...";
    for ( unsigned i = 0; i < num; ++i )
    {
        add_sev( *outCube, *( cubes[ i ] ), cmap[ i ], ( 1. / ( double )num ) );
    }
    cout << " done." << endl;
    delete[] cmap;
    return;
}








void
cube::cube4_inclusify( Cube* outCube, Cube* inCube, bool reduce, bool collapse )
{
    CubeMapping cubeMap, directCubeMap;

    vector<Metric*>      inMetrics = inCube->get_metv();
    map<Metric*, Metric*>treemap;
    for ( vector<Metric*>::iterator miter = inMetrics.begin(); miter != inMetrics.end(); ++miter )
    {
        Metric* _metric = outCube->def_met( ( *miter )->get_disp_name(), ( *miter )->get_uniq_name(),
                                            ( *miter )->get_dtype(), ( *miter )->get_uom(), ( *miter )->get_val(), ( *miter )->get_url(),
                                            ( *miter )->get_descr(), treemap[ ( *miter )->get_parent() ], CUBE_METRIC_INCLUSIVE );
        treemap[ *miter ]         = _metric;
        cubeMap.metm[ *miter ]    = _metric;
        cubeMap.r_metm[ _metric ] =  *miter;
    }


    cnode_merge( *outCube, *inCube, cubeMap );
    if ( !sysres_merge( *outCube, *inCube, cubeMap, reduce, collapse ) )
    {
        cerr << endl << endl << " System tree seems to be incompatible to be unified in one common system tree. \n"
            " You may try options -c or -C. See help for further details. " << endl;
        exit( EXIT_FAILURE );
    }
    add_top( *outCube, *inCube, cubeMap );

    outCube->initialize();


    map<Metric*, Metric*>::iterator miter;
    map<Thread*, Thread*>::iterator siter;

    for ( miter = cubeMap.r_metm.begin(); miter != cubeMap.r_metm.end(); ++miter )
    {
        vector<Cnode*>opt_cnodes = outCube->get_optimal_sequence( miter->second );

        for ( vector<Cnode*>::reverse_iterator c_iter = opt_cnodes.rbegin(); c_iter != opt_cnodes.rend(); ++c_iter )
        {
            for ( siter = cubeMap.r_sysm.begin(); siter != cubeMap.r_sysm.end(); ++siter )
            {
                Value* v = inCube->get_sev_adv
                           (
                    ( miter->second ), CUBE_CALCULATE_INCLUSIVE,
                    cubeMap.r_cnodem[ *c_iter ], CUBE_CALCULATE_INCLUSIVE,
                    ( Sysres* )( siter->second ), CUBE_CALCULATE_INCLUSIVE
                           );
                outCube->set_sev( miter->first, *c_iter, siter->first, v );
                v->Free();
            }
        }
    }
}





void
cube::cube4_exclusify( Cube* outCube, Cube* inCube, bool reduce, bool collapse )
{
    CubeMapping cubeMap, directCubeMap;

    vector<Metric*>      inMetrics = inCube->get_metv();
    map<Metric*, Metric*>treemap;
    for ( vector<Metric*>::iterator miter = inMetrics.begin(); miter < inMetrics.end(); ++miter )
    {
        Metric* _metric = outCube->def_met( ( *miter )->get_disp_name(), ( *miter )->get_uniq_name(),
                                            ( *miter )->get_dtype(), ( *miter )->get_uom(), ( *miter )->get_val(), ( *miter )->get_url(),
                                            ( *miter )->get_descr(),  treemap[ ( *miter )->get_parent() ], CUBE_METRIC_EXCLUSIVE );
        treemap[ *miter ]         = _metric;
        cubeMap.metm[ *miter ]    = _metric;
        cubeMap.r_metm[ _metric ] =  *miter;
    }


    cnode_merge( *outCube, *inCube, cubeMap );
    if ( !sysres_merge( *outCube, *inCube, cubeMap, reduce, collapse ) )
    {
        cerr << endl << endl << " System tree seems to be incompatible to be unified in one common system tree. \n"
            " You may try options -c or -C. See help for further details. " << endl;
        exit( EXIT_FAILURE );
    }

    add_top( *outCube, *inCube, cubeMap );

    outCube->initialize();

    map<Metric*, Metric*>::iterator miter;
    map<Thread*, Thread*>::iterator siter;

    for ( miter = cubeMap.r_metm.begin(); miter != cubeMap.r_metm.end(); ++miter )
    {
        vector<Cnode*>opt_cnodes = outCube->get_optimal_sequence( miter->second );

        for ( vector<Cnode*>::iterator c_iter = opt_cnodes.begin(); c_iter < opt_cnodes.end(); ++c_iter )
        {
            for ( siter = cubeMap.r_sysm.begin(); siter != cubeMap.r_sysm.end(); ++siter )
            {
                Value* v = inCube->get_sev_adv
                           (
                    ( miter->second ), CUBE_CALCULATE_INCLUSIVE,
                    cubeMap.r_cnodem[ *c_iter ], CUBE_CALCULATE_EXCLUSIVE,
                    ( Sysres* )( siter->second ), CUBE_CALCULATE_EXCLUSIVE
                           );
                outCube->set_sev( miter->first, *c_iter, siter->first, v );
                v->Free();
            }
        }
    }
}






bool
cube::cube4_is_empty( Cube* outCube )
{
    double                      treashold = DBL_MIN;
    const std::vector<Metric*>& _mets     = outCube->get_metv();
    const std::vector<Cnode*>&  _cnodes   = outCube->get_cnodev();
    const std::vector<Thread*>& _thrds    =  outCube->get_thrdv();

    for ( std::vector<Metric*>::const_iterator m_iter = _mets.begin(); m_iter != _mets.end(); ++m_iter )
    {
        Metric* metric = *m_iter;
        for ( std::vector<Cnode*>::const_iterator c_iter = _cnodes.begin(); c_iter != _cnodes.end(); ++c_iter )
        {
            Cnode* cnode = *c_iter;
            for ( std::vector<Thread*>::const_iterator t_iter = _thrds.begin(); t_iter != _thrds.end(); ++t_iter )
            {
                Thread* thread = *t_iter;
                double  v      = outCube->get_sev( metric, cnode, thread );
                if ( fabs( v ) >= treashold )
                {
                    cout << "Triplet (" << metric->get_disp_name() << " x " << cnode->get_callee()->get_name() << " x " << thread->get_name() << ") has value abouve treashold (" << treashold << "): " << v << endl;
                    return false;
                }
            }
        }
    }

    return true;
}
