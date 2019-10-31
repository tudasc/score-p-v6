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
#include "AggregatedMetric.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <vector>

#include "CubeError.h"
#include "MdAggrCube.h"
#include "AggrCube.h"
#include "Cube.h"
#include "CubeMetric.h"
#include "CubeProcess.h"
#include "CubeThread.h"

using namespace cube;
using namespace std;

namespace
{
/**
 * STL conform version to get a lowercase of a string.
 */
struct fo_tolower : public std::unary_function<int, int>
{
    int
    operator()( int x ) const
    {
        return std::tolower( x );
    }
};
}   /* unnamed namespace */


AggregatedMetric::AggregatedMetric( string metric_descriptor_string )
    : descriptor_string( metric_descriptor_string ),
    metric( NULL ), inclusion_mode( INCL ), sysres( NULL )
{
}

string
AggregatedMetric::to_string( int max_length )
{
    if ( metric == NULL )
    {
        throw Error( "Cannot build string from uninitialized CnodeMetric." );
    }

    stringstream append;
    if ( inclusion_mode == EXCL || sysres != NULL )
    {
        append << " (";
        if ( inclusion_mode == EXCL )
        {
            append << "E";
        }
        if ( inclusion_mode == EXCL && sysres != NULL )
        {
            append << ",";
        }
        if ( sysres != NULL )
        {
            if ( Thread* t = dynamic_cast<Thread*>( sysres ) )
            {
                append << t->get_parent()->get_rank() << "." << t->get_rank();
            }
            else
            {
                append << dynamic_cast<Process*>( sysres )->get_rank();
            }
        }
        append << ")";
        max_length -= append.str().length();
    }

    string r = metric->get_disp_name().substr( 0, max_length );
    r += append.str();
    return r;
}

double
AggregatedMetric::compute( Cnode* node, CubeMapping* mapping )
{
    Metric* used_metric = metric;
    Cnode*  used_node   = node;
    Sysres* used_res    = sysres;

    if ( mapping != NULL )
    {
        Process*                        p     = NULL;
        map<Metric*, Metric*>::iterator metit = mapping->metm.find( used_metric );
        map<Cnode*, Cnode*>::iterator   nodit = mapping->cnodem.find( used_node );
        map<Thread*, Thread*>::iterator resit;
        if ( sysres == NULL )
        {
            resit = mapping->sysm.begin();
        }
        else if ( ( p = dynamic_cast<Process*>( used_res ) ) )
        {
            resit = mapping->sysm.find( p->get_child( 0 ) );
        }
        else
        {
            resit = mapping->sysm.find( dynamic_cast<Thread*>( sysres ) );
        }

        if (  metit == mapping->metm.end()
              || nodit == mapping->cnodem.end()
              || resit == mapping->sysm.end() )
        {
            return numeric_limits<double>::quiet_NaN();
        }

        used_metric = metit->second;
        used_node   = nodit->second;
        if ( sysres == NULL )
        {
            used_res = NULL;
        }
        else if ( p )
        {
            used_res = resit->second->get_parent();
        }
        else
        {
            used_res = resit->second;
        }
    }

    return cube->get_vcsev( INCL, inclusion_mode, INCL,
                            used_metric, used_node, used_res );
}

double
AggregatedMetric::compute( Region*, CubeMapping* )
{
    return 0.;
}

string
AggregatedMetric::stringify()
{
    if ( metric == NULL )
    {
        throw RuntimeError( "AggregatedMetric was asked to stringify, but "
                            "it was not registered with a cube yet." );
    }

    if ( descriptor_string.empty() == false )
    {
        return descriptor_string;
    }

    stringstream ss;
    ss << "basic@" << metric->get_uniq_name() << ":";
    if ( inclusion_mode == INCL )
    {
        ss << "incl:";
    }
    else
    {
        ss << "excl:";
    }
    if ( sysres == NULL )
    {
        ss << "*.*";
    }
    else
    {
        unsigned int process_id;
        Process*     p = dynamic_cast<Process*>( sysres );
        Thread*      t = NULL;
        if ( p == NULL )
        {
            t = dynamic_cast<Thread*>( sysres );
            if ( t == NULL )
            {
                throw RuntimeError( "Unexpected sysres data type." );
            }
            p = t->get_parent();
        }
        process_id = p->get_id();
        ss << process_id << ".";
        if ( t != NULL )
        {
            unsigned int local_thread_id = 0;
            for ( unsigned int i = 0; i < p->num_children(); ++i )
            {
                if ( t == p->get_child( i ) )
                {
                    local_thread_id = i;
                    break;
                }
            }
            ss << local_thread_id;
        }
        else
        {
            ss << "*";
        }
    }

    descriptor_string = ss.str();

    return descriptor_string;
}

void
AggregatedMetric::register_with( MdAggrCube* _cube )
{
    CnodeMetric::register_with( _cube );

    string metric_uniq_name, mode_str, proc_str, thr_str, helper;
    size_t pos = 0;

    if ( ( pos = descriptor_string.find( '@' ) ) != string::npos )
    {
        string prefix = descriptor_string.substr( 0, pos );
        if ( prefix != "basic" )
        {
            throw RuntimeError( "Unknown prefix " + prefix +
                                "in Constructor of AggregatedMetric." );
        }
        descriptor_string = descriptor_string.substr( pos + 1 );
    }

    pos = ( pos != string::npos ) ? pos : 0;
    do
    {
        pos              = descriptor_string.find( ':', pos );
        metric_uniq_name = descriptor_string.substr( 0, pos );
        if ( pos == string::npos )
        {
            break;
        }
        pos++;
    }
    while ( ( cube->get_met( metric_uniq_name ) == NULL ) );


    helper   = ( pos == string::npos ? "" : descriptor_string.substr( pos ) );
    pos      = helper.find( ':' );
    mode_str = helper.substr( 0, pos );
    helper   = ( pos == string::npos ? "" : helper.substr( pos + 1 ) );
    pos      = helper.find( '.' );
    proc_str = helper.substr( 0, pos );
    thr_str  = ( pos == string::npos ? "" : helper.substr( pos + 1 ) );

    metric = cube->get_met( metric_uniq_name );
    if ( metric == NULL )
    {
        throw Error( "Unknown metric " + metric_uniq_name );
    }

    transform( mode_str.begin(), mode_str.end(), mode_str.begin(), fo_tolower() );

    if ( mode_str == "excl" || mode_str == "exclusive" )
    {
        inclusion_mode = EXCL;
    }
    else if ( mode_str.empty() || mode_str == "incl" || mode_str == "inclusive" )
    {
        mode_str       = "incl";
        inclusion_mode = INCL;
    }
    else
    {
        throw Error( "Unknown mode " + mode_str + "! Use either incl or excl" );
    }

    if ( proc_str.empty() == false && proc_str != "*" )
    {
        vector<Process*>           procv = cube->get_procv();
        int                        rank  = atoi( proc_str.data() );
        vector<Process*>::iterator it;

        for ( it = procv.begin(); it != procv.end() && ( *it )->get_rank() != rank; ++it )
        {
            ;
        }
        if ( it == procv.end() )
        {
            throw Error( "There is no process with rank " + proc_str + "!" );
        }
        sysres = *it;

        if ( thr_str.empty() == false && thr_str != "*" )
        {
            int thr = atoi( thr_str.data() );
            sysres = sysres->get_child( thr );
            // XXX: get_child may raise an exception, if thr is an invalid number. This
            //      exception is not treated in an appropiate way by the CLI, but catching
            //      and rethrowing the exception (as something that IS handled by the CLI
            //      did not work either for some reason. This is a bug.
        }
    }

    descriptor_string = "basic@" + metric_uniq_name + ":"
                        + mode_str + ":"
                        + ( proc_str.empty() ? "*" : proc_str )
                        + "."
                        + ( thr_str.empty() ? "*" : thr_str );
}

string
AggregatedMetric::get_dtype()
{
    return metric->get_dtype();
}
