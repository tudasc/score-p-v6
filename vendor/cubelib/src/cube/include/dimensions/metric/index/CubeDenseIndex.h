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
 * \file CubeDenseIndex.h
 * \brief Provides a dense index.
 ************************************************/

#ifndef __DENSE_INDEX_H
#define __DENSE_INDEX_H

#include <fstream>

#include "CubeIndex.h"


namespace cube
{
/**
 * Provides an  index, which calculates position of (cnode_id, thread_id) as (#threads * cnode_id + thread_id). Useful for dense packed metric. In the case of the few data might lead to waste of the filesystem space. Example: saving of single value (1000,10) by #threads == 128 leads to file size 1000.08Kb even by single saved value.
 */
class DenseIndex : public Index
{
public:
    DenseIndex( cnodes_number_t   cnt,
                threads_number_t  tnt,
                SingleValueTrafo* trafo ) : Index( cnt, tnt, trafo )
    {
    };
    virtual
    ~DenseIndex()
    {
    };
    // / Returns (#threads * cnode_id + thread_id)
    virtual index_t getPosition( cnode_id_t, thread_id_t );
    // / Returns (#threads * tuplet.first( == cnode_id) + tuplet.second ( ==thread_id) )
    virtual index_t getPosition( tuplet );
    // / Returns (#threads * cnode_id + thread_id)
    virtual index_t setPosition( cnode_id_t, thread_id_t );
    // / Returns (#threads * tuplet.first( == cnode_id) + tuplet.second ( ==thread_id) )
    virtual index_t setPosition( tuplet );
    // / Returns tiplet.first = position / #threads; tuplet.second = position % #threads.
    virtual tuplet getPosition( index_t );
    // / NOP Operation, coz only layout data (#cnodes, #threads) saved in IndexHeader is used.
    virtual void
    readData( std::fstream& );

    // / NOP Operation, coz only layout data (#cnodes, #threads) will be saved in IndexHeader.
    virtual void
    writeData( std::fstream& );

    // / NOP Operation, coz only layout data (#cnodes, #threads) will be saved in IndexHeader.
    virtual void
    writeData( FILE* );

    // / Prints "Im a Dense index"
    virtual void
    printSelf();

    // / NOP prints
    virtual void
    printIndex();

    // / Nop operation. No optimisation is needed.
    virtual void
    prepareOptimization();

    // / Returns always "false", coz no optimisation is needed.
    virtual bool
    toOptimize();

    // / Returns always pair (0,0) like 0the row will be replaced with 0th row. It doesnt any effect and ensures, that by wrong calling of this method no changes in data stream happens.
    virtual rows_pair
    exchange();

    virtual Ranges getRowRange( cnode_id_t, thread_id_t, uint32_t );
    virtual Rows*  cutRect( cnode_id_t, cnode_id_t );
};
}
#endif
