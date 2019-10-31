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


#include "config.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>

#include "Cube.h"
#include "CubeMetric.h"
#include "CubeScaleFuncValue.h"

using namespace std;
using namespace cube;

vector<double>
getVector( double a, double b, double c, double d )
{
    vector<double> vec;
    vec.push_back( a );
    vec.push_back( b );
    vec.push_back( c );
    vec.push_back( d );
    return vec;
}

void
doAssertions()
{
    ScaleFuncValue* sfv1 = new ScaleFuncValue( getVector( 1, 1, 1, 1 ) );
    ScaleFuncValue* sfv2 = new ScaleFuncValue( getVector( 3, 1, 1, 1 ) );
    ScaleFuncValue* sfv3 = new ScaleFuncValue( getVector( 1, 1, 1, 1 ) );

    ScaleFuncValue::Term t1, t2, t3, t4;
    t1.a = 1;
    t1.b = 1;
    t1.c = 1;
    t1.d = 1;
    t2.a = 3;
    t2.b = 1;
    t2.c = 1;
    t2.d = 1;
    t4.a = 2;
    t4.b = 2;
    t4.c = 3;
    t4.d = 1;

    t3 = t1 + t2;
    assert( t3.a == 4 );
    assert( t3.b == 1 );
    assert( t3.c == 1 );
    assert( t3.d == 1 );

    sfv1->
    operator +=( sfv2 );

    assert( sfv1->getNumTerms() == 1 );

    sfv3->addTerm( t1 );
    assert( sfv3->getNumTerms() == 1 );
    assert( sfv3->getString() == "2*x*log(x)" );
    sfv3->addTerm( t4 );
    assert( sfv3->getNumTerms() == 2 );
    assert( sfv3->getString() == "2*x*log(x) + 2*x**(2.0/3.0)*log(x)" );

    sfv1->
    operator+=( sfv3 );

    assert( sfv1->getNumTerms() == 2 );

    assert( sfv1->getDominantTerm().getString() == "6*x*log(x)" );
    assert( sfv3->getDominantTerm().getString() == "2*x*log(x)" );

    // assert(sfv1->getString() == "4*p*log(p)");

    sfv1->Free();
    sfv2->Free();
    sfv3->Free();
}

int
main( int argc, char* argv[] )
{
    Metric*  ghostMetric, * normalMetric, * metVisits, * metTime, * metSent, * metRecv;
    Region*  regn0, * regMain, * regInit, * regFinit, * regOp, * regSubOp1, * regSubOp2;
    Cnode*   cnode0, * cMain, * cInit, * cFinit, * cOp, * cSubOp1, * cSubOp2;
    Machine* mach;
    Node*    node;
    Process* p;
    Thread*  t;
    try
    {
        Cube c;

        metVisits = c.def_met( "Visits", "visits", "SCALE_FUNC", "occ", "",
                               "no URL available", "no description available", NULL, CUBE_METRIC_EXCLUSIVE );

        metTime = c.def_met( "Execution time", "time", "SCALE_FUNC", "ms", "", "",
                             "no description", NULL, CUBE_METRIC_EXCLUSIVE, " ", " ",
                             " ", " ", " ", true, CUBE_METRIC_NORMAL );

        metSent = c.def_met( "Bytes sent", "sent", "SCALE_FUNC", "byte", "", "",
                             "no description", NULL, CUBE_METRIC_EXCLUSIVE, " ", " ",
                             " ", " ", " ", true, CUBE_METRIC_NORMAL );

        metRecv = c.def_met( "Bytes received", "recv", "SCALE_FUNC", "byte", "", "",
                             "no description", NULL, CUBE_METRIC_EXCLUSIVE, " ", " ",
                             " ", " ", " ", true, CUBE_METRIC_NORMAL );

        string module = "test.c";

        regMain   = c.def_region( "main", "main", "USER", "calculation", 1, 2, "", "n/a", module );
        regInit   = c.def_region( "MPI_Init", "MPI_Init", "USER", "calculation", 1, 2, "", "n/a", module );
        regFinit  = c.def_region( "MPI_Finalize", "MPI_Finalize", "USER", "calculation", 1, 2, "", "n/a", module );
        regOp     = c.def_region( "calculate", "calculate", "USER", "calculation", 1, 2, "", "n/a", module );
        regSubOp1 = c.def_region( "matMult", "matMult", "USER", "calculation", 1, 2, "", "n/a", module );
        regSubOp2 = c.def_region( "MPI_Reduce", "MPI_Reduce", "USER", "calculation", 1, 2, "", "n/a", module );

        mach = c.def_mach( "Machine", "" );
        node = c.def_node( "Node", mach );
        p    = c.def_proc( "Process", 0, node );
        t    = c.def_thrd( "Thread", 0, p );

        cMain   = c.def_cnode( regMain, module, 1, NULL );
        cInit   = c.def_cnode( regInit, module, 1, cMain );
        cOp     = c.def_cnode( regOp, module, 1, cMain );
        cSubOp1 = c.def_cnode( regSubOp1, module, 1, cOp );
        cSubOp2 = c.def_cnode( regSubOp2, module, 1, cOp );
        cFinit  = c.def_cnode( regFinit, module, 1, cMain );

        c.initialize();


        c.set_sev( metVisits, cMain, t, new ScaleFuncValue( getVector( 1, 0, 1, 0 ) ) );
        c.set_sev( metTime, cMain, t, new ScaleFuncValue( getVector( 3, 1, 2, 2 ) ) );
        c.set_sev( metSent, cMain, t, new ScaleFuncValue( getVector( 0, 0, 1, 0 ) ) );
        c.set_sev( metRecv, cMain, t, new ScaleFuncValue( getVector( 0, 0, 1, 0 ) ) );

        c.set_sev( metVisits, cInit, t, new ScaleFuncValue( getVector( 1, 0, 1, 0 ) ) );
        c.set_sev( metTime, cInit, t, new ScaleFuncValue( getVector( 4, 0, 1, 1 ) ) );
        c.set_sev( metSent, cInit, t, new ScaleFuncValue( getVector( 0, 0, 1, 0 ) ) );
        c.set_sev( metRecv, cInit, t, new ScaleFuncValue( getVector( 0, 0, 1, 0 ) ) );

        c.set_sev( metVisits, cFinit, t, new ScaleFuncValue( getVector( 1, 0, 1, 0 ) ) );
        c.set_sev( metTime, cFinit, t, new ScaleFuncValue( getVector( 4.2, 0, 1, 1 ) ) );
        c.set_sev( metSent, cFinit, t, new ScaleFuncValue( getVector( 0, 0, 1, 0 ) ) );
        c.set_sev( metRecv, cFinit, t, new ScaleFuncValue( getVector( 0, 0, 1, 0 ) ) );

        c.set_sev( metVisits, cOp, t, new ScaleFuncValue( getVector( 3, 0, 1, 0 ) ) );
        c.set_sev( metTime, cOp, t, new ScaleFuncValue( getVector( 0.4, 1, 3, 3 ) ) );
        c.set_sev( metSent, cOp, t, new ScaleFuncValue( getVector( 1, 1, 1, 3 ) ) );
        c.set_sev( metRecv, cOp, t, new ScaleFuncValue( getVector( 0, 0, 1, 0 ) ) );

        c.set_sev( metVisits, cSubOp1, t, new ScaleFuncValue( getVector( 1, 0, 1, 0 ) ) );
        c.set_sev( metTime, cSubOp1, t, new ScaleFuncValue( getVector( 0.2, 5, 3, 0 ) ) );
        c.set_sev( metSent, cSubOp1, t, new ScaleFuncValue( getVector( 0, 0, 1, 0 ) ) );
        c.set_sev( metRecv, cSubOp1, t, new ScaleFuncValue( getVector( 0, 0, 1, 0 ) ) );

        c.set_sev( metVisits, cSubOp2, t, new ScaleFuncValue( getVector( 1, 0, 1, 0 ) ) );
        c.set_sev( metTime, cSubOp2, t, new ScaleFuncValue( getVector( 12, 0, 1, 1 ) ) );
        c.set_sev( metSent, cSubOp2, t, new ScaleFuncValue( getVector( 3, 2, 1, 2 ) ) );
        c.set_sev( metRecv, cSubOp2, t, new ScaleFuncValue( getVector( 3, 2, 1, 2 ) ) );

        c.writeCubeReport( "scale_test" );
    }
    catch ( const RuntimeError& e )
    {
        cerr << e.what() << endl;
        return 1;
    }

    doAssertions();

    cout << "done" << endl;
    return 0;
}
