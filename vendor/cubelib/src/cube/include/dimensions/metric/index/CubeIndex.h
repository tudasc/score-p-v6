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
 * \file CubeIndex.h
 * \brief Provides a basis class for mapping (cnode_id, thread_id) -> position in Data stream.
 */


#ifndef __INDEX_H
#define __INDEX_H
#include <inttypes.h>

#include "CubeTypes.h"
#include "CubeTrafos.h"



namespace cube
{
/**
 * Defines an interface for all kinds of Indecies, used in Cube.
 */
class Index
{
protected:
    // / Saves a layout of the data
    cnodes_number_t  number_cnodes;
    threads_number_t number_threads;

    // / Saves the transformation for endianess. If the index saved on machine with different endianess, all numbers have to be transformed.
    SingleValueTrafo* endianess;

    // / If the Readonly modus, no changes in index will happen after "setPosition()" call
    bool read_only;
public:
    // / Constructs the index with given layout, and endianess
    Index( cnodes_number_t   cnt,
           threads_number_t  tnt,
           SingleValueTrafo* trafo ) : number_cnodes( cnt ), number_threads( tnt ), endianess( trafo )
    {
    };
    virtual
    ~Index()
    {
    };

    // / returns result of the mapping (cnode_id, thread_id) -> position
    virtual index_t getPosition( cnode_id_t, thread_id_t ) = 0;

    // / adds the new value in the data stream on position (cnode_id, thread_id) -> position. In the case of sparse index, the internal index has to be modified.
    virtual index_t setPosition( cnode_id_t, thread_id_t ) = 0;

    // / returns result of the mapping (cnode_id, thread_id) -> position with another arguments.
    virtual index_t getPosition( tuplet ) = 0;

    // / adds the new value in the data stream on position (cnode_id, thread_id) -> position. In the case of sparse index, the internal index has to be modified.
    virtual index_t setPosition( tuplet ) = 0;

    // / returns result of the mapping position -> (cnode_id, thread_id) position.
    virtual tuplet getPosition( index_t ) = 0;

    // / NOT LUCKY NAME. SHOULD BE PROBABLY "readIndexData()". Reads the data from the index file to provide the mapping (cnode_id, thread_id) -> position. For dense index is trivial. Really reading happens only by sarse index.
    virtual void
    readData( std::fstream& ) = 0;

    // / NOT LUCKY NAME. SHOULD BE PROBABLY "writeIndexData()". Reads the data from the index file to provide the mapping (cnode_id, thread_id) -> position. For dense index is trivial. Really reading happens only by sarse index.
    virtual void
    writeData( std::fstream& ) = 0;

    // / NOT LUCKY NAME. SHOULD BE PROBABLY "writeIndexData()". Reads the data from the index file to provide the mapping (cnode_id, thread_id) -> position. For dense index is trivial. Really reading happens only by sarse index.
    virtual void
    writeData( FILE* ) = 0;

    // / Prints the name of the index. Used for debugging.
    virtual void
    printSelf() = 0;

    // / Prints the content of the index data. Used for Debugging.
    virtual void
    printIndex() = 0;


    // / Last operation before destruction is the optimisation of the index. Dense intex -> nop. Sparse index -> index has to be sorted  to allow logarithmical search later.
    // / During this operation index provides a list of the row pair, which have to be exchanged to get optimisd index.
    // / Optimisation is needed to provide ability to save data in cube in arbitrary order. If the data saved from the beginning in optimal order, optimisation wont't lead to any further changes.
    virtual void
    prepareOptimization() = 0;

    // / Signalize, that optimisation is needed. If "true", optimisation will be prepared by calling "prepareOptimization()" and subsequential loop over row pairs, which habve to be "exchanged".
    virtual bool
    toOptimize() = 0;

    // / Performs the exchange of the rows in teh index data of the index. Dense index -> nop operation.
    virtual rows_pair
    exchange() = 0;


    // / Provides the ranges in the data stream, wihch correspondes to the (cnode_id, thread_id) - (cnode_id, thread_id+ N). Used in the calculation of excl/incl values.
    virtual Ranges getRowRange( cnode_id_t, thread_id_t, uint32_t ) = 0;

    // / Returns the collcection of rows, which are involved in the calculation.
    virtual Rows* cutRect( cnode_id_t, cnode_id_t ) = 0;
};
}
#endif
