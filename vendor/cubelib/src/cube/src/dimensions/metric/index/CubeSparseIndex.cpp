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


/**
 * \file CubeSparseIndex.cpp
 * \brief Provides methods for SparseIndex
 */

#include "config.h"
#include <iostream>
#include <istream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include "CubeError.h"
#include "CubeSparseIndex.h"

using namespace std;
using namespace cube;



SparseIndex::~SparseIndex()
{
    if ( new_index != NULL )
    {
        delete new_index;
    }
    if ( sorted_new_index != NULL )
    {
        delete sorted_new_index;
    }
    if ( index != NULL )
    {
        delete[] index;
    }
}



SparseIndex::SparseIndex( cnodes_number_t   cnt,
                          threads_number_t  tnt,
                          SingleValueTrafo* trafo ) : Index( cnt, tnt, trafo )
{
    indexsize        = 0;
    new_index        = NULL;
    sorted_new_index = NULL;
    index            = NULL;
    read_only        = false;
};  // per default we CREATE index.


index_t
SparseIndex::getPosition( cnode_id_t cid, thread_id_t tid )
{
// #warning "Error handling has to be done"
    if ( cid >= number_cnodes )
    {
        throw RuntimeError( "position_t SparseIndex::getPosition( cnode_id_t cid, thread_id_t tid ): Try to get a position of CID outside of maximal number of cnodes for current layout." ); // Further real Exception
    }
    if ( tid >= number_threads )
    {
        throw RuntimeError( "position_t SparseIndex::getPosition( cnode_id_t cid, thread_id_t tid ):Try to get a position of TID outside of maximal number of threads for current layout." );
    }
    ;                                                                                                                // Further real Exception
    index_t pos_in_index = findPosition( cid );
    if ( pos_in_index == non_index )
    {
        return non_index;
    }
    return ( index_t )( pos_in_index * number_threads + tid );
}

index_t
SparseIndex::getPosition( tuplet coords )
{
// #warning "Error handling has to be done"
    cnode_id_t  cid = coords.first;
    thread_id_t tid = coords.second;

    if ( cid >= number_cnodes )
    {
        throw RuntimeError( "position_t SparseIndex::getPosition( tuplet coords ): Try to get a position of CID outside of maximal number of cnodes for current layout." ); // Further real Exception
    }
    if ( tid >= number_threads )
    {
        throw RuntimeError( "position_t SparseIndex::getPosition( tuplet coords ): Try to get a position of TID outside of maximal number of threads for current layout." );
    }
    ;                                                                                                                // Further real Exception
    index_t pos_in_index = findPosition( cid );
    if ( pos_in_index == non_index )
    {
        return non_index;
    }
    return ( index_t )( pos_in_index * number_threads + tid );
}

index_t
SparseIndex::setPosition( cnode_id_t cid, thread_id_t tid )
{
// #warning "TO TEST IMPLEMENTATION"
    if ( !read_only )
    {
        if ( new_index == NULL )
        {
            new_index = new vector<pair<index_t, index_t> >();
            new_index->empty();
            indexsize = 0;
        }
        size_t i = 0;
        for ( i = 0; i < new_index->size(); ++i )
        {
            if ( new_index->at( i ).first == ( size_t )cid )
            {
                break;
            }
        }

        if ( i < new_index->size() )
        {
            return ( index_t )( i * number_threads + tid );  // existing position of value
        }
        else
        {
            pair<index_t, index_t> place;
            place.first  = cid;
            place.second = i;
            new_index->push_back( place );
            indexsize++;
            index_t* _index = index;
            index = new index_t[ indexsize ];
            memcpy( index, _index, ( indexsize - 1 ) * sizeof( index_t ) );
            delete[] _index;
            index[ indexsize - 1 ] = cid;
            return i * number_threads + tid;   // new position of value
        }
    }
    return 0;
}

index_t
SparseIndex::setPosition( tuplet coords )
{
    return setPosition( coords.first, coords.second );
}



tuplet
SparseIndex::getPosition( index_t pos )
{
    tuplet coords;

    coords.first  = index[ pos / number_threads ];
    coords.second = pos % number_threads;
    return coords;
}

void
SparseIndex::readData( fstream& in )
{
    read_only = true;
    in.read( ( char* )&indexsize, sizeof( index_size_t ) );

    endianess->trafo( ( char* )( &indexsize ), sizeof( index_size_t ) );

    if ( index != NULL )
    {
        delete[] index;
    }
    index = new index_t[ indexsize ];
    in.read( ( char* )( index ), sizeof( index_t ) * indexsize );
    for ( unsigned i = 0; i < indexsize; ++i )
    {
        endianess->trafo( ( char* )( index + i ), sizeof( index_t ) );
    }
    return;
}

void
SparseIndex::writeData( fstream& out )
{
    if ( !read_only && indexsize != 0 && new_index != NULL )
    {
        sort( new_index->begin(), new_index->end() );
        for ( unsigned i = 0; i < indexsize; ++i )
        {
            index[ i ] = new_index->at( i ).first;
        }
        out.write( ( char* )&indexsize, sizeof( index_size_t ) );
        out.write( ( char* )( index ), sizeof( index_t ) * indexsize );
        out.flush();
    }
    return;
}


void
SparseIndex::writeData( FILE* fout )
{
    if ( !read_only && indexsize != 0 && new_index != NULL )
    {
        sort( new_index->begin(), new_index->end() );
        for ( unsigned i = 0; i < indexsize; ++i )
        {
            index[ i ] = new_index->at( i ).first;
        }
        fwrite( ( char* )&indexsize, 1, sizeof( index_size_t ), fout );
        fwrite( ( char* )( index ), 1, sizeof( index_t ) * indexsize, fout  );
        fflush( fout );
    }
    return;
}





void
SparseIndex::printSelf()
{
    cerr << "Im a Sparse Index" << endl;
}

void
SparseIndex::printIndex()
{
    cout << " --- INDEX START --- " << read_only << " " << true << endl;

//     if ( read_only )
//     {
    if ( index != NULL )
    {
        for ( unsigned i = 0; i < indexsize; ++i )
        {
            cout << "index[" << i << "]=" << index[ i ] << endl;
        }
    }
//     }
//     else
//     {
//         if ( new_index != NULL && sorted_new_index != NULL )
//         {
//             for ( unsigned i = 0; i < new_index->size(); ++i )
//             {
//                 cout << "new_index[" << i << "].first=" << new_index->at( i ).first << " new_index[" << i << "].second = " << new_index->at( i ).second << "                ";
//                 cout << "sorted_new_index[" << i << "].first=" << sorted_new_index->at( i ).first << " sorted_new_index[" << i << "].second = " << sorted_new_index->at( i ).second << endl;
//             }
//         }
//     }
    cout << "---- INDEX END ---- "  << endl;
}



void
SparseIndex::prepareOptimization()
{
// #warning " SPARSE INDEX OPTIMIZATION!!"
    if ( !read_only )
    {
        if ( new_index != NULL )
        {
            start            = 0;
            sorted_new_index = new vector<pair<index_t, index_t> >( new_index->size(), pair<index_t, index_t>( 0, 0 ) );
        }
    }
}



bool
SparseIndex::toOptimize()
{
// #warning " SPARSE INDEX OPTIMIZATION!!"
    if ( read_only )
    {
        return false;
    }
    if ( new_index == NULL || sorted_new_index == NULL )
    {
        return false;
    }
    *sorted_new_index = *new_index;
    sort( sorted_new_index->begin(), sorted_new_index->end() );
    for ( start = 0; start < sorted_new_index->size() && sorted_new_index->at( start ).second == start; ++start )
    {
    }
    to_exchange = start;
    return to_exchange < new_index->size();
    ;
}; // it is already optimal!



rows_pair
SparseIndex::exchange()
{
// #warning " SPARSE INDEX OPTIMIZATION!!"

    rows_pair to_return;
    to_return.second = to_exchange;
    to_return.first  = sorted_new_index->at( to_exchange ).second;

    index_t tmp = new_index->at( to_exchange ).first;
    new_index->at( to_exchange ).first                                = new_index->at( sorted_new_index->at( to_exchange ).second ).first;
    new_index->at( sorted_new_index->at( to_exchange ).second ).first = tmp;
    return to_return;
}





Ranges
SparseIndex::getRowRange( cnode_id_t cid, thread_id_t tid, uint32_t number )
{
    Ranges to_return;
    to_return.empty();
    if ( cid > number_cnodes )
    {
        return to_return;                    // empty ranges;
    }
    if ( tid > number_threads )
    {
        return to_return;                     // empty ranges;
    }
    if ( tid + number > number_threads )
    {
        number = number_threads - tid;
    }

    pair<position_t, position_t> tmp;
    tmp.first  = getPosition( cid, tid );
    tmp.second = tmp.first + number;
    to_return.push_back( tmp );
    return to_return;
}




Rows*
SparseIndex::cutRect( cnode_id_t cid_lu, cnode_id_t cid_rb )
{
    Rows* to_return = new Rows();
    ;
    to_return->empty();
    if ( cid_rb < cid_lu )
    {
        swap( cid_lu, cid_rb );
    }
    if ( cid_lu > number_cnodes )
    {
        return to_return;                       // empty ranges;
    }
    if ( cid_rb > number_cnodes )
    {
        cid_rb = number_cnodes;
    }

    for ( index_t i = 0; i < indexsize; ++i )
    {
        if ( index[ i ] >= ( index_t )cid_lu && index[ i ] <= ( index_t )cid_rb )
        {
            to_return->push_back( index[ i ] );
        }
    }
    return to_return;
}









// ------------- PRIVATE METHODS ---------------




index_t
SparseIndex::findPosition( cnode_id_t cnode )
{
// #warning "Error handling should be done better!"
    index_t _cnode = ( index_t )cnode;

    // sync index and new_index
    if ( index == NULL )
    {
        return non_index;
//         throw RuntimeError( "Index is NULL, expected to be not." );
    }


    if ( read_only )
    {
        if ( indexsize == 0 )
        {
            return non_index;
//             throw MissingValueError( "Index is empty" );
        }
        if ( _cnode < index[ 0 ] )
        {
            return non_index;
//             throw MissingValueError( "Asked cnode_id is smaller than minimal saved cnode_id in the index." );
        }
        if ( _cnode > index[ indexsize - 1 ] )
        {
            return non_index;
//             throw MissingValueError( "Asked cnode_id is bigger than maximal saved cnode_id in the index." );
        }

        index_t lo = 0;

        index_t hi   = indexsize - 1;
        index_t newx = 99999999;

// #warning " ASSUMED SORTED INDEX!!!"
        if ( _cnode == index[ lo ] )
        {
            return lo;
        }
        if ( _cnode == index[ hi ] )
        {
            return hi;
        }


        while ( hi - lo > 1 )
        {
            if ( _cnode == index[ lo ] )
            {
                return lo;
            }
            if ( _cnode == index[ hi ] )
            {
                return hi;
            }

            newx = half( lo, hi );

            if ( index[ newx ] == _cnode )
            {
                break;
            }
            if ( index[ newx ] < _cnode )
            {
                lo = newx;
            }
            if ( index[ newx ] > _cnode )
            {
                hi = newx;
            }
        }
        if ( hi - lo == 1 )
        {
            return non_index;
//             throw MissingValueError( "cnode_id is not in index" );
        }
        return newx;
    }
    else
    {
        if ( _cnode == index[ 0 ] )
        {
            return 0;
        }
        if ( _cnode == index[ indexsize - 1 ] )
        {
            return indexsize - 1;
        }
        index_t newx = 0;
        while ( newx < indexsize && index[ newx ] != _cnode  )
        {
            ++newx;
        }
        if ( newx >= indexsize )
        {
            return non_index;
//             throw MissingValueError( "cnode_id is not in index yet" );                  //?????
        }
        return newx;
    }
}





index_t
SparseIndex::half( index_t lo, index_t hi )
{
    return ( hi + lo ) / 2;
}

