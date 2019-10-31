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
 *
 * \file CubeSparseIndex.h
 * \brief  Provides a sparse index with sorted(not during creation) list of entries.
 ************************************************/

#ifndef __SPARSE_INDEX_H
#define __SPARSE_INDEX_H

#include <fstream>
#include <vector>
#include "CubeIndex.h"


namespace cube
{
/**
 * Provides an  index, which builds a std::vector of occupated "cnodes". Every position is then calculated as : a) new cnode_id -> then sizeof(index)* # threads + thread_id. b) existing cnode_id -> position_in_index(cnode_id) * #threads + threads_id.
 * Before destroying the index object, it performs the optimisation of the index. It sorts the index in the ascending manner and tells which rows have to be exchanged to ensure sorted index. Exchange is done by object, containing the Index object. Here it is destructor of "AdvancedMatrix".
 */
class SparseIndex : public Index
{
private:
    // / "Heart of the index". Is used to save Index into file. Internally it works with std::std::vector new_index. See below. If the Index read from file, used to keep the read index data.
    index_t* index;
    // / The size of the index. Saved as the first value in the index file right after IndexHeader
    index_size_t indexsize;
    // / Performs the binary searh over the index to find the position of given cnode_id in index.
    index_t findPosition( cnode_id_t );

    // / Search happens in the target space of the mapping "(cnode, 0) -> position" Therefore the arguments are position_t and the result is position_t. It returns the downrounded center of the range.
    index_t half( index_t, index_t );

    // / New index is used during creation of new index. pair.first == cnode_id, pair::second == position in index. Saved separatel, coz after sorting the connection has to persist.
    std::vector<std::pair<index_t, index_t> >* new_index;
    // / During optimisation the new_index is sorted according to the cnode_id.
    std::vector<std::pair<index_t, index_t> >* sorted_new_index;

    // / internal marker, used during optimisation
    index_t to_exchange;                 // marks the place in index to exchange duringoptimization

    // / internal marker, used during optimisation
    index_t start;                 // marks the place in index to exchange during next step of optimization
public:
    SparseIndex( cnodes_number_t,
                 threads_number_t,
                 SingleValueTrafo* );                                                // per default we CREATE index.
    virtual
    ~SparseIndex();
    // / Calculated position of the Value with coordinates (cnode_id, thread_id) in the Data stream using index.
    virtual index_t getPosition( cnode_id_t, thread_id_t );
    // / Calculated position of the Value with coordinates tuplet in the Data stream using index.
    virtual index_t getPosition( tuplet );
    // / Checks, whether new element is already in index, then calculates position of saved data, or extends the index on one element and adds the new element.
    virtual index_t setPosition( cnode_id_t, thread_id_t );
    // / Checks, whether new element is already in index, then calculates position of saved data, or extends the index on one element and adds the new element.
    virtual index_t setPosition( tuplet );
    // / Returns the coordinates of the element on "position".
    virtual tuplet getPosition( index_t );
    // / Reads the "index" from the file. Assumes, that fstream read pointer is places right after IndexHeader and next element is the size of the index. It reads the size of the index, allocates the memory for "index" and reads inti "index" the saved index.
    virtual void
    readData( std::fstream& );

    // / Writes the index into file, assuming that fstream writing pointer is placed right after IndexHeader and index is optimised. It is ensured in process of destroying of Index. Destructor of AdvancedMatrix optimises the Index, calls destructor of IndexManager. IndexManager calls "header->writeHeader(); index->writeData()" and destroys the Index object.
    virtual void
    writeData( std::fstream& );

    // / Writes the index into file, assuming that fstream writing pointer is placed right after IndexHeader and index is optimised. It is ensured in process of destroying of Index. Destructor of AdvancedMatrix optimises the Index, calls destructor of IndexManager. IndexManager calls "header->writeHeader(); index->writeData()" and destroys the Index object.
    virtual void
    writeData( FILE* );

    // / Prepares optimisation. Allocates memory for sorted version of index.
    virtual void
    prepareOptimization();

    // / Checks, whethere there are still elements in index, which are not sorted yet. If yes, saves position which have to be exchanged  and returns true.
    virtual bool
    toOptimize();

    // / Builds pair of the cnode-rows, which have to be exchanged and returns it. Exchange is done by AdvancedMatrix in destructor.
    virtual rows_pair
    exchange();


    // / Prints "Im a sparse index". Used for debuging.
    virtual void
    printSelf();

    // / Prints contents of used indexes: index[], new_index and sorted_new_index. Used for debugging,
    virtual void
    printIndex();

    virtual Ranges getRowRange( cnode_id_t, thread_id_t, uint32_t );

    // / Runs over the index  and collects all rows, which are in the range "cnode 1" and "cnode 2". Index assumend to be not sorted, because one might call "cutRect" in the middle of creation of new index.
    virtual Rows* cutRect( cnode_id_t, cnode_id_t );
};
}
#endif
