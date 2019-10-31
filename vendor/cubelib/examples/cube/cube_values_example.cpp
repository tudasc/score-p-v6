/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2017                                                **
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
 * \file cube_example.cpp
 * \brief An example how to create and save a cube.
 */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Cube.h"
#include "CubeMetric.h"
#include "CubeCnode.h"
#include "CubeValues.h"


using namespace std;
using namespace cube;

int
main( int argc, char* argv[] )
{
    Metric* met0, * met1, * met2, * met3,
          * met4, * met5, * met6, * met7,
          * met8, * met9, * met10, * met11,
          * met12, * met13, * met14, * met15,
          * met16,  * met17;

    Region*  regn0, * regn1, * regn2;
    Cnode*   cnode0, * cnode1, * cnode2;
    Machine* mach;
    Node*    node;
    Process* proc0, * proc1;
    Thread*  thrd0, * thrd1,
          * thrd2, * thrd3;
    try
    {
        Cube cube;



        // Build metric tree
        met0 = cube.def_met( "INT8", "INT8", "INT8", "sec", "",
                             "@mirror@patterns-2.1.html#execution",
                             "root node", NULL, CUBE_METRIC_INCLUSIVE ); // using mirror
        // Build metric tree
        met1 = cube.def_met( "UINT8", "UINT8", "UINT8", "sec", "",
                             "@mirror@patterns-2.1.html#execution",
                             "root node", NULL, CUBE_METRIC_INCLUSIVE ); // using mirror
        // Build metric tree
        met2 = cube.def_met( "INT16", "INT16", "INT16", "sec", "",
                             "@mirror@patterns-2.1.html#execution",
                             "root node", NULL, CUBE_METRIC_INCLUSIVE ); // using mirror
        // Build metric tree
        met3 = cube.def_met( "UINT16", "UINT16", "UINT16", "sec", "",
                             "@mirror@patterns-2.1.html#execution",
                             "root node", NULL, CUBE_METRIC_INCLUSIVE ); // using mirror
        // Build metric tree
        met4 = cube.def_met( "INT32", "INT32", "INT32", "sec", "",
                             "@mirror@patterns-2.1.html#execution",
                             "root node", NULL, CUBE_METRIC_INCLUSIVE ); // using mirror
        // Build metric tree
        met5 = cube.def_met( "UINT32", "UINT32", "UINT32", "sec", "",
                             "@mirror@patterns-2.1.html#execution",
                             "root node", NULL, CUBE_METRIC_INCLUSIVE ); // using mirror
        // Build metric tree
        met6 = cube.def_met( "INT64", "INT64", "INT64", "sec", "",
                             "@mirror@patterns-2.1.html#execution",
                             "root node", NULL, CUBE_METRIC_INCLUSIVE ); // using mirror
        // Build metric tree
        met7 = cube.def_met( "UINT64", "UINT64", "UINT64", "sec", "",
                             "@mirror@patterns-2.1.html#execution",
                             "root node", NULL, CUBE_METRIC_INCLUSIVE ); // using mirror
        // Build metric tree
        met8 = cube.def_met( "DOUBLE", "DOUBLE", "DOUBLE", "sec", "",
                             "@mirror@patterns-2.1.html#execution",
                             "root node", NULL, CUBE_METRIC_INCLUSIVE ); // using mirror
        // Build metric tree
        met9 = cube.def_met( "MINDOUBLE", "MINDOUBLE", "MINDOUBLE", "sec", "",
                             "@mirror@patterns-2.1.html#execution",
                             "root node", NULL, CUBE_METRIC_EXCLUSIVE ); // using mirror
        // Build metric tree
        met10 = cube.def_met( "MAXDOUBLE", "MAXDOUBLE", "MAXDOUBLE", "sec", "",
                              "@mirror@patterns-2.1.html#execution",
                              "root node", NULL, CUBE_METRIC_EXCLUSIVE ); // using mirror
        // Build metric tree
        met11 = cube.def_met( "RATE", "RATE", "RATE", "sec", "",
                              "@mirror@patterns-2.1.html#execution",
                              "root node", NULL, CUBE_METRIC_INCLUSIVE ); // using mirror
        // Build metric tree
        met12 = cube.def_met( "TAU_ATOMIC", "TAU_ATOMIC", "TAU_ATOMIC", "sec", "",
                              "@mirror@patterns-2.1.html#execution",
                              "root node", NULL, CUBE_METRIC_EXCLUSIVE ); // using mirror

        met13 = cube.def_met( "HISTOGRAM5", "HISTOGRAM5", "HISTOGRAM(5)", "sec", "",
                              "@mirror@patterns-2.1.html#execution",
                              "root node", NULL, CUBE_METRIC_EXCLUSIVE ); // using mirror
        // Build metric tree
        met14 = cube.def_met( "NDOUBLES10", "NDOUBLES10", "NDOUBLES(10)", "sec", "",
                              "@mirror@patterns-2.1.html#execution",
                              "root node", NULL, CUBE_METRIC_INCLUSIVE ); // using mirror
        // Build metric tree
        met15 = cube.def_met( "SCALE_FUNC3", "SCALE_FUNC3", "SCALE_FUNC", "sec", "",
                              "@mirror@patterns-2.1.html#execution",
                              "root node", NULL, CUBE_METRIC_EXCLUSIVE ); // using mirror


        // Build metric tree
        met16 = cube.def_met( "COMPLEX", "COMPLEX", "COMPLEX", "sec", "",
                              "@mirror@patterns-2.1.html#execution",
                              "root node", NULL, CUBE_METRIC_INCLUSIVE ); // using mirror

        // Build metric tree
        met17 = cube.def_met( "TAU_ATOMIC2", "TAU_ATOMIC2", "TAU_ATOMIC", "sec", "",
                              "@mirror@patterns-2.1.html#execution",
                              "root node", NULL, CUBE_METRIC_EXCLUSIVE ); // using mirror






        // Build call tree
        string mod = "/ICL/CUBE/example.c";
        regn0 = cube.def_region( "main", "main", "mpi", "barrier", 21, 100, "", "1st level", mod );
        regn1 = cube.def_region( "foo", "foo", "mpi", "barrier", 1, 10, "", "2nd level", mod );
        regn2 = cube.def_region( "bar", "bar", "mpi", "barrier", 11, 20, "", "2nd level", mod );


        cnode0 = cube.def_cnode( regn0, mod, 21, NULL );
        cnode1 = cube.def_cnode( regn1, mod, 60, cnode0 );
        cnode2 = cube.def_cnode( regn2, mod, 80, cnode0 );

        // Build location tree
        mach  = cube.def_mach( "MSC", "" );
        node  = cube.def_node( "Athena", mach );
        proc0 = cube.def_proc( "Process 0", 0, node );
        proc1 = cube.def_proc( "Process 1", 1, node );
        thrd0 = cube.def_thrd( "Thread 0", 0, proc0 );
        thrd1 = cube.def_thrd( "Thread 1", 1, proc1 );
        thrd2 = cube.def_thrd( "Thread 2", 2, proc0 );
        thrd3 = cube.def_thrd( "Thread 3", 3, proc1 );

        cube.initialize();

        // Severity mapping

        CharValue* tmp_int8 = new CharValue();

        *tmp_int8 = 1;
        cube.set_sev( met0, cnode0, thrd0, tmp_int8 );
        cube.set_sev( met1, cnode0, thrd0, tmp_int8 );
        *tmp_int8 = 2;
        cube.set_sev( met0, cnode0, thrd1, tmp_int8 );
        cube.set_sev( met1, cnode0, thrd1, tmp_int8 );
        *tmp_int8 = 3;
        cube.set_sev( met0, cnode0, thrd2, tmp_int8 );
        cube.set_sev( met1, cnode0, thrd2, tmp_int8 );
        *tmp_int8 = 4;
        cube.set_sev( met0, cnode0, thrd3, tmp_int8 );
        cube.set_sev( met1, cnode0, thrd3, tmp_int8 );
        *tmp_int8 = 5;
        cube.set_sev( met0, cnode1, thrd0, tmp_int8 );
        cube.set_sev( met1, cnode1, thrd0, tmp_int8 );
        *tmp_int8 = 6;
        cube.set_sev( met0, cnode1, thrd1, tmp_int8 );
        cube.set_sev( met1, cnode1, thrd1, tmp_int8 );
        *tmp_int8 = 7;
        cube.set_sev( met0, cnode1, thrd2, tmp_int8 );
        cube.set_sev( met1, cnode1, thrd2, tmp_int8 );
        *tmp_int8 = 8;
        cube.set_sev( met0, cnode1, thrd3, tmp_int8 );
        cube.set_sev( met1, cnode1, thrd3, tmp_int8 );
        *tmp_int8 = 9;
        cube.set_sev( met0, cnode2, thrd0, tmp_int8 );
        cube.set_sev( met1, cnode2, thrd0, tmp_int8 );
        *tmp_int8 = 10;
        cube.set_sev( met0, cnode2, thrd1, tmp_int8 );
        cube.set_sev( met1, cnode2, thrd1, tmp_int8 );
        *tmp_int8 = 11;
        cube.set_sev( met0, cnode2, thrd2, tmp_int8 );
        cube.set_sev( met1, cnode2, thrd2, tmp_int8 );
        *tmp_int8 = 12;
        cube.set_sev( met0, cnode2, thrd3, tmp_int8 );
        cube.set_sev( met1, cnode2, thrd3, tmp_int8 );

        tmp_int8->Free();


        SignedShortValue* tmp_int16 = new SignedShortValue;

        *tmp_int16 = 1;
        cube.set_sev( met2, cnode0, thrd0, tmp_int16 );
        *tmp_int16 = 2;
        cube.set_sev( met2, cnode0, thrd1, tmp_int16 );
        *tmp_int16 = 3;
        cube.set_sev( met2, cnode0, thrd2, tmp_int16 );
        *tmp_int16 = 4;
        cube.set_sev( met2, cnode0, thrd3, tmp_int16 );
        *tmp_int16 = 5;
        cube.set_sev( met2, cnode1, thrd0, tmp_int16 );
        *tmp_int16 = 6;
        cube.set_sev( met2, cnode1, thrd1, tmp_int16 );
        *tmp_int16 = 7;
        cube.set_sev( met2, cnode1, thrd2, tmp_int16 );
        *tmp_int16 = 8;
        cube.set_sev( met2, cnode1, thrd3, tmp_int16 );
        *tmp_int16 = 9;
        cube.set_sev( met2, cnode2, thrd0, tmp_int16 );
        *tmp_int16 = 10;
        cube.set_sev( met2, cnode2, thrd1, tmp_int16 );
        *tmp_int16 = 11;
        cube.set_sev( met2, cnode2, thrd2, tmp_int16 );
        *tmp_int16 = 12;
        cube.set_sev( met2, cnode2, thrd3, tmp_int16 );

        delete tmp_int16;



        UnsignedShortValue* _uint16 = new UnsignedShortValue;

        *_uint16 = 1;
        cube.set_sev( met3, cnode0, thrd0, _uint16 );
        *_uint16 = 2;
        cube.set_sev( met3, cnode0, thrd1, _uint16 );
        *_uint16 = 3;
        cube.set_sev( met3, cnode0, thrd2, _uint16 );
        *_uint16 = 4;
        cube.set_sev( met3, cnode0, thrd3, _uint16 );
        *_uint16 = 5;
        cube.set_sev( met3, cnode1, thrd0, _uint16 );
        *_uint16 = 6;
        cube.set_sev( met3, cnode1, thrd1, _uint16 );
        *_uint16 = 7;
        cube.set_sev( met3, cnode1, thrd2, _uint16 );
        *_uint16 = 8;
        cube.set_sev( met3, cnode1, thrd3, _uint16 );
        *_uint16 = 9;
        cube.set_sev( met3, cnode2, thrd0, _uint16 );
        *_uint16 = 10;
        cube.set_sev( met3, cnode2, thrd1, _uint16 );
        *_uint16 = 11;
        cube.set_sev( met3, cnode2, thrd2, _uint16 );
        *_uint16 = 12;
        cube.set_sev( met3, cnode2, thrd3, _uint16 );

        delete _uint16;


        SignedValue* tmp_int32 = new SignedValue;

        *tmp_int32 = 1;
        cube.set_sev( met4, cnode0, thrd0, tmp_int32 );
        *tmp_int32 = 2;
        cube.set_sev( met4, cnode0, thrd1, tmp_int32 );
        *tmp_int32 = 3;
        cube.set_sev( met4, cnode0, thrd2, tmp_int32 );
        *tmp_int32 = 4;
        cube.set_sev( met4, cnode0, thrd3, tmp_int32 );
        *tmp_int32 = 5;
        cube.set_sev( met4, cnode1, thrd0, tmp_int32 );
        *tmp_int32 = 6;
        cube.set_sev( met4, cnode1, thrd1, tmp_int32 );
        *tmp_int32 = 7;
        cube.set_sev( met4, cnode1, thrd2, tmp_int32 );
        *tmp_int32 = 8;
        cube.set_sev( met4, cnode1, thrd3, tmp_int32 );
        *tmp_int32 = 9;
        cube.set_sev( met4, cnode2, thrd0, tmp_int32 );
        *tmp_int32 = 10;
        cube.set_sev( met4, cnode2, thrd1, tmp_int32 );
        *tmp_int32 = 11;
        cube.set_sev( met4, cnode2, thrd2, tmp_int32 );
        *tmp_int32 = 12;
        cube.set_sev( met4, cnode2, thrd3, tmp_int32 );

        delete tmp_int32;



        UnsignedValue* _uint32 = new UnsignedValue;

        *_uint32 = 1;
        cube.set_sev( met5, cnode0, thrd0, _uint32 );
        *_uint32 = 2;
        cube.set_sev( met5, cnode0, thrd1, _uint32 );
        *_uint32 = 3;
        cube.set_sev( met5, cnode0, thrd2, _uint32 );
        *_uint32 = 4;
        cube.set_sev( met5, cnode0, thrd3, _uint32 );
        *_uint32 = 5;
        cube.set_sev( met5, cnode1, thrd0, _uint32 );
        *_uint32 = 6;
        cube.set_sev( met5, cnode1, thrd1, _uint32 );
        *_uint32 = 7;
        cube.set_sev( met5, cnode1, thrd2, _uint32 );
        *_uint32 = 8;
        cube.set_sev( met5, cnode1, thrd3, _uint32 );
        *_uint32 = 9;
        cube.set_sev( met5, cnode2, thrd0, _uint32 );
        *_uint32 = 10;
        cube.set_sev( met5, cnode2, thrd1, _uint32 );
        *_uint32 = 11;
        cube.set_sev( met5, cnode2, thrd2, _uint32 );
        *_uint32 = 12;
        cube.set_sev( met5, cnode2, thrd3, _uint32 );

        delete _uint32;



        SignedLongValue* tmp_int64 = new SignedLongValue;

        *tmp_int64 = 1;
        cube.set_sev( met6, cnode0, thrd0, tmp_int64 );
        *tmp_int64 = 2;
        cube.set_sev( met6, cnode0, thrd1, tmp_int64 );
        *tmp_int64 = 3;
        cube.set_sev( met6, cnode0, thrd2, tmp_int64 );
        *tmp_int64 = 4;
        cube.set_sev( met6, cnode0, thrd3, tmp_int64 );
        *tmp_int64 = 5;
        cube.set_sev( met6, cnode1, thrd0, tmp_int64 );
        *tmp_int64 = 6;
        cube.set_sev( met6, cnode1, thrd1, tmp_int64 );
        *tmp_int64 = 7;
        cube.set_sev( met6, cnode1, thrd2, tmp_int64 );
        *tmp_int64 = 8;
        cube.set_sev( met6, cnode1, thrd3, tmp_int64 );
        *tmp_int64 = 9;
        cube.set_sev( met6, cnode2, thrd0, tmp_int64 );
        *tmp_int64 = 10;
        cube.set_sev( met6, cnode2, thrd1, tmp_int64 );
        *tmp_int64 = 11;
        cube.set_sev( met6, cnode2, thrd2, tmp_int64 );
        *tmp_int64 = 12;
        cube.set_sev( met6, cnode2, thrd3, tmp_int64 );

        delete tmp_int64;



        UnsignedLongValue* _uint64 = new UnsignedLongValue;

        *_uint64 = 1;
        cube.set_sev( met7, cnode0, thrd0, _uint64 );
        *_uint64 = 2;
        cube.set_sev( met7, cnode0, thrd1, _uint64 );
        *_uint64 = 3;
        cube.set_sev( met7, cnode0, thrd2, _uint64 );
        *_uint64 = 4;
        cube.set_sev( met7, cnode0, thrd3, _uint64 );
        *_uint64 = 5;
        cube.set_sev( met7, cnode1, thrd0, _uint64 );
        *_uint64 = 6;
        cube.set_sev( met7, cnode1, thrd1, _uint64 );
        *_uint64 = 7;
        cube.set_sev( met7, cnode1, thrd2, _uint64 );
        *_uint64 = 8;
        cube.set_sev( met7, cnode1, thrd3, _uint64 );
        *_uint64 = 9;
        cube.set_sev( met7, cnode2, thrd0, _uint64 );
        *_uint64 = 10;
        cube.set_sev( met7, cnode2, thrd1, _uint64 );
        *_uint64 = 11;
        cube.set_sev( met7, cnode2, thrd2, _uint64 );
        *_uint64 = 12;
        cube.set_sev( met7, cnode2, thrd3, _uint64 );

        delete _uint64;

        DoubleValue* _double = new DoubleValue;

        *_double = 1.1;
        cube.set_sev( met8, cnode0, thrd0, _double );
        *_double = 2.2;
        cube.set_sev( met8, cnode0, thrd1, _double );
        *_double = 3.3;
        cube.set_sev( met8, cnode0, thrd2, _double );
        *_double = 4.4;
        cube.set_sev( met8, cnode0, thrd3, _double );
        *_double = 5.5;
        cube.set_sev( met8, cnode1, thrd0, _double );
        *_double = 6.6;
        cube.set_sev( met8, cnode1, thrd1, _double );
        *_double = 7.7;
        cube.set_sev( met8, cnode1, thrd2, _double );
        *_double = 8.8;
        cube.set_sev( met8, cnode1, thrd3, _double );
        *_double = 9.9;
        cube.set_sev( met8, cnode2, thrd0, _double );
        *_double = 10.10;
        cube.set_sev( met8, cnode2, thrd1, _double );
        *_double = 11.11;
        cube.set_sev( met8, cnode2, thrd2, _double );
        *_double = 12.12;
        cube.set_sev( met8, cnode2, thrd3, _double );

        delete _double;


        MinDoubleValue* _mindouble = new MinDoubleValue;
        *_mindouble = 1.1;
        cube.set_sev( met9, cnode0, thrd0, _mindouble );
        *_mindouble = 2.2;
        cube.set_sev( met9, cnode0, thrd1, _mindouble );
        *_mindouble = 3.3;
        cube.set_sev( met9, cnode0, thrd2, _mindouble );
        *_mindouble = 4.4;
        cube.set_sev( met9, cnode0, thrd3, _mindouble );
        *_mindouble = 5.5;
        cube.set_sev( met9, cnode1, thrd0, _mindouble );
        *_mindouble = 6.6;
        cube.set_sev( met9, cnode1, thrd1, _mindouble );
        *_mindouble = 7.7;
        cube.set_sev( met9, cnode1, thrd2, _mindouble );
        *_mindouble = 8.8;
        cube.set_sev( met9, cnode1, thrd3, _mindouble );
        *_mindouble = 9.9;
        cube.set_sev( met9, cnode2, thrd0, _mindouble );
        *_mindouble = 10.10;
        cube.set_sev( met9, cnode2, thrd1, _mindouble );
        *_mindouble = 11.11;
        cube.set_sev( met9, cnode2, thrd2, _mindouble );
        *_mindouble = 12.12;
        cube.set_sev( met9, cnode2, thrd3, _mindouble );

        delete _mindouble;


        MaxDoubleValue* _maxdouble = new MaxDoubleValue;
        *_maxdouble = 1.1;
        cube.set_sev( met10, cnode0, thrd0, _maxdouble );
        *_maxdouble = 2.2;
        cube.set_sev( met10, cnode0, thrd1, _maxdouble );
        *_maxdouble = 3.3;
        cube.set_sev( met10, cnode0, thrd2, _maxdouble );
        *_maxdouble = 4.4;
        cube.set_sev( met10, cnode0, thrd3, _maxdouble );
        *_maxdouble = 5.5;
        cube.set_sev( met10, cnode1, thrd0, _maxdouble );
        *_maxdouble = 6.6;
        cube.set_sev( met10, cnode1, thrd1, _maxdouble );
        *_maxdouble = 7.7;
        cube.set_sev( met10, cnode1, thrd2, _maxdouble );
        *_maxdouble = 8.8;
        cube.set_sev( met10, cnode1, thrd3, _maxdouble );
        *_maxdouble = 9.9;
        cube.set_sev( met10, cnode2, thrd0, _maxdouble );
        *_maxdouble = 10.10;
        cube.set_sev( met10, cnode2, thrd1, _maxdouble );
        *_maxdouble = 11.11;
        cube.set_sev( met10, cnode2, thrd2, _maxdouble );
        *_maxdouble = 12.12;
        cube.set_sev( met10, cnode2, thrd3, _maxdouble );

        delete _maxdouble;


        RateValue* _rate1 = new RateValue( 1, 1 );
        cube.set_sev( met11, cnode0, thrd0, _rate1 );
        delete _rate1;
        RateValue* _rate2 = new RateValue( 1, 2 );
        cube.set_sev( met11, cnode0, thrd1, _rate2 );
        delete _rate2;
        RateValue* _rate3 = new RateValue( 1, 3 );
        cube.set_sev( met11, cnode0, thrd2, _rate3 );
        delete _rate3;
        RateValue* _rate4 = new RateValue( 1, 4 );
        cube.set_sev( met11, cnode0, thrd3, _rate4 );
        delete _rate4;
        RateValue* _rate5 = new RateValue( 1, 5 );
        cube.set_sev( met11, cnode1, thrd0, _rate5 );
        delete _rate5;
        RateValue* _rate6 = new RateValue( 1, 6 );
        cube.set_sev( met11, cnode1, thrd1, _rate6 );
        delete _rate6;
        RateValue* _rate7 = new RateValue( 1, 7 );
        cube.set_sev( met11, cnode1, thrd2, _rate7 );
        delete _rate7;
        RateValue* _rate8 = new RateValue( 1, 8 );
        cube.set_sev( met11, cnode1, thrd3, _rate8 );
        delete _rate8;
        RateValue* _rate9 = new RateValue( 1, 9 );
        cube.set_sev( met11, cnode2, thrd0, _rate9 );
        delete _rate9;
        RateValue* _rate10 = new RateValue( 10., 1.1 );
        cube.set_sev( met11, cnode2, thrd1, _rate10 );
        delete _rate10;
        RateValue* _rate11 = new RateValue( 11., 1.2 );
        cube.set_sev( met11, cnode2, thrd2, _rate11 );
        delete _rate11;
        RateValue* _rate12 = new RateValue( 12., 1.3 );
        cube.set_sev( met11, cnode2, thrd3, _rate12 );
        delete _rate12;



        TauAtomicValue* _tauv1 = new TauAtomicValue( 1, 1, 1, 1, 1 );
        cube.set_sev( met12, cnode0, thrd0, _tauv1 );
        cube.set_sev( met17, cnode0, thrd0, _tauv1 );
        delete _tauv1;
        TauAtomicValue* _tauv2 = new TauAtomicValue( 2, 1, 3, 4, 10 );
        cube.set_sev( met12, cnode0, thrd1, _tauv2 );
        cube.set_sev( met17, cnode0, thrd1, _tauv2 );
        delete _tauv2;
        TauAtomicValue* _tauv3 = new TauAtomicValue( 3, 1, 5, 9, 35 );
        cube.set_sev( met12, cnode0, thrd2, _tauv3 );
        cube.set_sev( met17, cnode0, thrd2, _tauv3 );
        delete _tauv3;
        TauAtomicValue* _tauv4 = new TauAtomicValue( 4, 1, 7, 16, 84 );
        cube.set_sev( met12, cnode0, thrd3, _tauv4 );
        cube.set_sev( met17, cnode0, thrd3, _tauv4 );
        delete _tauv4;
        TauAtomicValue* _tauv5 = new TauAtomicValue( 5, 1, 11, 27, 205 );
        cube.set_sev( met12, cnode0, thrd3, _tauv4 );
        cube.set_sev( met17, cnode0, thrd3, _tauv4 );
        delete _tauv5;
        TauAtomicValue* _tauv6 = new TauAtomicValue( 6, 1, 13, 40, 374 );
        cube.set_sev( met12, cnode1, thrd1, _tauv6 );
        cube.set_sev( met17, cnode1, thrd1, _tauv6 );
        delete _tauv6;
        TauAtomicValue* _tauv7 = new TauAtomicValue( 7, 1, 17, 57, 663 );
        cube.set_sev( met12, cnode1, thrd2, _tauv7 );
        cube.set_sev( met17, cnode1, thrd2, _tauv7 );
        delete _tauv7;
        TauAtomicValue* _tauv8 = new TauAtomicValue( 8, 1, 19, 76, 1024 );
        cube.set_sev( met12, cnode1, thrd3, _tauv8 );
        cube.set_sev( met17, cnode1, thrd3, _tauv8 );
        delete _tauv8;
        TauAtomicValue* _tauv9 = new TauAtomicValue( 9, 1, 23, 99, 1553 );
        cube.set_sev( met12, cnode2, thrd0, _tauv9 );
        cube.set_sev( met17, cnode2, thrd0, _tauv9 );
        delete _tauv9;
        TauAtomicValue* _tauv10 = new TauAtomicValue( 10, 1, 29, 128, 2394 );
        cube.set_sev( met12, cnode2, thrd1, _tauv10 );
        cube.set_sev( met17, cnode2, thrd1, _tauv10 );
        delete _tauv10;
        TauAtomicValue* _tauv11 = new TauAtomicValue( 11, 1, 31, 159, 3355 );
        cube.set_sev( met12, cnode2, thrd2, _tauv11 );
        cube.set_sev( met17, cnode2, thrd2, _tauv11 );
        delete _tauv11;
        TauAtomicValue* _tauv12 = new TauAtomicValue( 12, 1, 37, 196, 4724 );
        cube.set_sev( met12, cnode2, thrd3, _tauv12 );
        cube.set_sev( met17, cnode2, thrd3, _tauv12 );
        delete _tauv12;



        const int N = 5;
        double    tmp[ N ];

        for ( size_t i = 0; i < N; ++i )
        {
            tmp[ i ] = i;
        }

        HistogramValue* _histov1 = new HistogramValue( 1, 3, N, tmp );
        cube.set_sev( met13, cnode0, thrd0, _histov1 );
        _histov1->Free();
        HistogramValue* _histov2 = new HistogramValue( 1, 5, N, tmp );
        cube.set_sev( met13, cnode0, thrd1, _histov2 );
        _histov2->Free();
        HistogramValue* _histov3 = new HistogramValue( 3, 7, N, tmp );
        cube.set_sev( met13, cnode0, thrd2, _histov3 );
        _histov3->Free();
        HistogramValue* _histov4 = new HistogramValue( 5, 11, N, tmp );
        cube.set_sev( met13, cnode0, thrd3, _histov4 );
        _histov4->Free();
        HistogramValue* _histov5 = new HistogramValue( 7, 13, N, tmp );
        cube.set_sev( met13, cnode1, thrd0, _histov5 );
        _histov5->Free();
        HistogramValue* _histov6 = new HistogramValue( 11, 17, N, tmp );
        cube.set_sev( met13, cnode1, thrd1, _histov6 );
        _histov6->Free();
        HistogramValue* _histov7 = new HistogramValue( 13, 19, N, tmp );
        cube.set_sev( met13, cnode1, thrd2, _histov7 );
        _histov7->Free();
        HistogramValue* _histov8 = new HistogramValue( 17, 23, N, tmp );
        cube.set_sev( met13, cnode1, thrd3, _histov8 );
        _histov8->Free();
        HistogramValue* _histov9 = new HistogramValue( 19, 29, N, tmp );
        cube.set_sev( met13, cnode2, thrd0, _histov9 );
        _histov9->Free();
        HistogramValue* _histov10 = new HistogramValue( 23, 31, N, tmp );
        cube.set_sev( met13, cnode2, thrd1, _histov10 );
        _histov10->Free();
        HistogramValue* _histov11 = new HistogramValue( 29, 37, N, tmp );
        cube.set_sev( met13, cnode2, thrd2, _histov11 );
        _histov11->Free();
        HistogramValue* _histov12 = new HistogramValue( 31, 41, N, tmp );
        cube.set_sev( met13, cnode2, thrd3, _histov12 );
        _histov12->Free();


        std::vector<double> terms;
        const size_t        Nscale = 3;
#define FILL_SCALE( x, y ) \
    terms.clear(); \
        \
    for ( size_t i = 0; i < Nscale; ++i ) \
    {   \
        terms.push_back( x + i ); \
        terms.push_back( y + i ); \
        terms.push_back( y + i + 1 ); \
        terms.push_back( y + i + 2 );  \
    }


        FILL_SCALE( 0, 0 );
        ScaleFuncValue* _scalefunc1 = new ScaleFuncValue( terms );
        cube.set_sev( met15, cnode0, thrd0, _scalefunc1 );
        _scalefunc1->Free();
        FILL_SCALE( 1, 1 );
        ScaleFuncValue* _scalefunc2 = new ScaleFuncValue( terms );
        cube.set_sev( met15, cnode0, thrd1, _scalefunc2 );
        _scalefunc2->Free();
        FILL_SCALE( 3, 3 );
        ScaleFuncValue* _scalefunc3 = new ScaleFuncValue( terms );
        cube.set_sev( met15, cnode0, thrd2, _scalefunc3 );
        _scalefunc3->Free();
        FILL_SCALE( 1, 0 );
        ScaleFuncValue* _scalefunc4 = new ScaleFuncValue( terms );
        cube.set_sev( met15, cnode0, thrd3, _scalefunc4 );
        _scalefunc4->Free();
        FILL_SCALE( 0, 1 );
        ScaleFuncValue* _scalefunc5 = new ScaleFuncValue( terms );
        cube.set_sev( met15, cnode1, thrd0, _scalefunc5 );
        _scalefunc5->Free();
        FILL_SCALE( 1, 3 );
        ScaleFuncValue* _scalefunc6 = new ScaleFuncValue( terms );
        cube.set_sev( met15, cnode1, thrd1, _scalefunc6 );
        _scalefunc6->Free();
        FILL_SCALE( 3, 1 );
        ScaleFuncValue* _scalefunc7 = new ScaleFuncValue( terms );
        cube.set_sev( met15, cnode1, thrd2, _scalefunc7 );
        _scalefunc7->Free();
        FILL_SCALE( 3, 0 );
        ScaleFuncValue* _scalefunc8 = new ScaleFuncValue( terms );
        cube.set_sev( met15, cnode1, thrd3, _scalefunc8 );
        _scalefunc8->Free();
        FILL_SCALE( 0, 3 );
        ScaleFuncValue* _scalefunc9 = new ScaleFuncValue( terms );
        cube.set_sev( met15, cnode2, thrd0, _scalefunc9 );
        _scalefunc9->Free();
        FILL_SCALE( 1.5, 1 );
        ScaleFuncValue* _scalefunc10 = new ScaleFuncValue( terms );
        cube.set_sev( met15, cnode2, thrd1, _scalefunc10 );
        _scalefunc10->Free();
        FILL_SCALE( 2.5, 1 );
        ScaleFuncValue* _scalefunc11 = new ScaleFuncValue( terms );
        cube.set_sev( met15, cnode2, thrd2, _scalefunc11 );
        _scalefunc11->Free();
        FILL_SCALE( 3.5, 2 );
        ScaleFuncValue* _scalefunc12 = new ScaleFuncValue( terms );
        cube.set_sev( met15, cnode2, thrd3, _scalefunc12 );
        _scalefunc12->Free();








        ComplexValue* _complex1 = new ComplexValue( 1, 1 );
        cube.set_sev( met16, cnode0, thrd0, _complex1 );
        delete _complex1;
        ComplexValue* _complex2 = new ComplexValue( 1, 2 );
        cube.set_sev( met16, cnode0, thrd1, _complex2 );
        delete _complex2;
        ComplexValue* _complex3 = new ComplexValue( 1, 3 );
        cube.set_sev( met16, cnode0, thrd2, _complex3 );
        delete _complex3;
        ComplexValue* _complex4 = new ComplexValue( 1, 4 );
        cube.set_sev( met16, cnode0, thrd3, _complex4 );
        delete _complex4;
        ComplexValue* _complex5 = new ComplexValue( 1, 5 );
        cube.set_sev( met16, cnode1, thrd0, _complex5 );
        delete _complex5;
        ComplexValue* _complex6 = new ComplexValue( 1, 6 );
        cube.set_sev( met16, cnode1, thrd1, _complex6 );
        delete _complex6;
        ComplexValue* _complex7 = new ComplexValue( 1, 7 );
        cube.set_sev( met16, cnode1, thrd2, _complex7 );
        delete _complex7;
        ComplexValue* _complex8 = new ComplexValue( 1, 8 );
        cube.set_sev( met16, cnode1, thrd3, _complex8 );
        delete _complex8;
        ComplexValue* _complex9 = new ComplexValue( 1, 9 );
        cube.set_sev( met16, cnode2, thrd0, _complex9 );
        delete _complex9;
        ComplexValue* _complex10 = new ComplexValue( 10., 1.1 );
        cube.set_sev( met16, cnode2, thrd1, _complex10 );
        delete _complex10;
        ComplexValue* _complex11 = new ComplexValue( 11., 1.2 );
        cube.set_sev( met16, cnode2, thrd2, _complex11 );
        delete _complex11;
        ComplexValue* _complex12 = new ComplexValue( 12., 1.3 );
        cube.set_sev( met16, cnode2, thrd3, _complex12 );
        delete _complex12;




        const int Ndoubles = 10;
        double    tmp_double[ Ndoubles ];

#define FILL( x, y ) \
    for ( size_t i = 0; i < Ndoubles; ++i ) { \
        x[ i ] = y + i; \
    }


        FILL( tmp_double, 0 );
        NDoublesValue* _ndv1 = new NDoublesValue( Ndoubles, tmp_double );
        cube.set_sev( met14, cnode0, thrd0, _ndv1 );
        _ndv1->Free();
        FILL( tmp_double, 1 );
        NDoublesValue* _ndv2 = new NDoublesValue( Ndoubles, tmp_double );
        cube.set_sev( met14, cnode0, thrd1, _ndv2 );
        _ndv2->Free();
        FILL( tmp_double, 2 );
        NDoublesValue* _ndv3 = new NDoublesValue( Ndoubles, tmp_double );
        cube.set_sev( met14, cnode0, thrd2, _ndv3 );
        _ndv3->Free();
        FILL( tmp_double, 3 );
        NDoublesValue* _ndv4 = new NDoublesValue( Ndoubles, tmp_double );
        cube.set_sev( met14, cnode0, thrd3, _ndv4 );
        _ndv4->Free();
        FILL( tmp_double, 5 );
        NDoublesValue* _ndv5 = new NDoublesValue( Ndoubles, tmp_double );
        cube.set_sev( met14, cnode1, thrd0, _ndv5 );
        _ndv5->Free();
        FILL( tmp_double, 7 );
        NDoublesValue* _ndv6 = new NDoublesValue( Ndoubles, tmp_double );
        cube.set_sev( met14, cnode1, thrd1, _ndv6 );
        _ndv6->Free();
        FILL( tmp_double, 11 );
        NDoublesValue* _ndv7 = new NDoublesValue( Ndoubles, tmp_double );
        cube.set_sev( met14, cnode1, thrd2, _ndv7 );
        _ndv7->Free();
        FILL( tmp_double, 13 );
        NDoublesValue* _ndv8 = new NDoublesValue( Ndoubles, tmp_double );
        cube.set_sev( met14, cnode1, thrd3, _ndv8 );
        _ndv8->Free();
        FILL( tmp_double, 17 );
        NDoublesValue* _ndv9 = new NDoublesValue( Ndoubles, tmp_double );
        cube.set_sev( met14, cnode2, thrd0, _ndv9 );
        _ndv9->Free();
        FILL( tmp_double, 19 );
        NDoublesValue* _ndv10 = new NDoublesValue( Ndoubles, tmp_double );
        cube.set_sev( met14, cnode2, thrd1, _ndv10 );
        _ndv10->Free();
        FILL( tmp_double, 23 );
        NDoublesValue* _ndv11 = new NDoublesValue( Ndoubles, tmp_double );
        cube.set_sev( met14, cnode2, thrd2, _ndv11 );
        _ndv11->Free();
        FILL( tmp_double, 29 );
        NDoublesValue* _ndv12 = new NDoublesValue( Ndoubles, tmp_double );
        cube.set_sev( met14, cnode2, thrd3, _ndv12 );
        _ndv12->Free();




        cube.writeCubeReport( "cube-values_example" );
    }
    catch ( const RuntimeError& error )
    {
        cout << error.what() << endl;
    }
}
