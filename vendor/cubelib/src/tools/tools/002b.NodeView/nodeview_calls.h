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



#ifndef __CUBE_NODEVIEW_CALLS_H
#define __CUBE_NODEVIEW_CALLS_H



/**
 * Finds a maximum value in a vector. Returns a pair, value and place in the vector.
 *
 */
template<class T>
pair<T, size_t>
find_max( vector<T> v )
{
    T      t( 0 );
    size_t max_id( 0 );
    for ( size_t i = 0; i < v.size(); i++ )
    {
        if ( v[ i ] > t )
        {
            t      = v[ i ];
            max_id = i;
        }
    }
    return make_pair( t, max_id );
}







/**
 * Finds a minimum value in a vector. Returns a pair, value and place in the vector.
 *
 */
template<class T>
pair<T, size_t>
find_min( vector<T> v )
{
    T      t( v[ 0 ] );
    size_t min_id( 0 );
    for ( size_t i = 1; i < v.size(); i++ )
    {
        if ( v[ i ] < t )
        {
            t      = v[ i ];
            min_id = i;
        }
    }
    return make_pair( t, min_id );
}






/**
 * Calculates a percent value.
 *
 */
template<class S, class T>
double
percent( S total, T costs )
{
    if ( total != 0 )
    {
        return 100.0 * ( double )costs / ( double )total;
    }
    else
    {
        return 0.0;
    }
}


struct map_add
{
    double
    operator()( double i, const std::pair<SystemTreeNode* const, double>& x )
    {
        return i + x.second;
    }
};



/**
 * Calculates a number of threads per node.
 *
 */
double
threads_per_node( const vector<Node*>& nodes )
{
    double tpn( 0.0 );

    for ( size_t j = 0; j < nodes.size(); j++ )
    {
        for ( size_t i = 0; i < nodes[ j ]->num_groups(); i++ )
        {
            tpn += ( ( Vertex* )( nodes[ j ] )->get_location_group( i ) )->num_children();
        }
    }
    return tpn / ( double )nodes.size();
}






/**
 * Prints out the help how to use this tool.
 *
 */
void
usage( const char* filename )
{
    cout << "Usage: " << filename << " [-m metricname] [-h] cubefile1 cubefile2 ... cubefileN\n";
    cout << "  -h     Help; Output this help message\n";
    cout << "  -m     Choose metric (defaults to runtime)\n";
    exit( EXIT_SUCCESS );
}


#endif
