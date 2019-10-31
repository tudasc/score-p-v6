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
 * \file CubeRowWiseMatrix.h
 * \brief  Provides a variante of the Matix, which holds values rowwise in memory and uses different strategies for caching. Matrix doesn't care about caching, and loading, but assumes, that rows[] is contains at any  time needed rows for calculations. RowsManager d
   assures the consistent state of rows[], performig load-unload, swaping , droping, row allocations.
 */

#ifndef __ROWWISE_MATRIX_H
#define __ROWWISE_MATRIX_H
#include <string>


#include "CubeAdvMatrix.h"
#include "CubeTypes.h"

#include "CubeRow.h"
#include "CubeRowsManager.h"

namespace cube
{
/**
 * Keeps all values in the couple "index-data". Index provides transformation (cnode_id, thread_id)-> position in "data" in terms of  "Value"
 * Data delivers or saves. the "Value" on "position".
 * IndexManager reads the header of the index file and decides, which kind(dense, sparse) of index is really used and which kind of data is used(continues, paged, compressed and so on).
 */
class RowWiseMatrix : public advMatrix
{
private:
    // / Object, which provides tha transformation (cnode_id, thread_id) -> position in the "Data"
    Index* index;
    // / Reads the header of .index file, creates corresponding Index object, Value object, Trafo object (die deal with endianess) and delivers the sizes of matricies (#cnodes x #trreads).
//     static const uint64_t MemorySize =      1024lu * 1024lu * 1024lu * 1lu;
    std::string indexfile;
    std::string datafile;

    // / Data container, storing the data rows
    rows_t rows;

    // / an artificial pointer, which is used to signalize that some row is missing in the cube file and "default" value should be used
    char* _no_row_pointer;

    // / An object, acting like an interface for any access to the memory rows[i].
    Row* row_interface;

    // / Pointer to the caching strategy (used, if no external strategies set)
    BasicStrategy* strategy;

    // / Pointer to the row supplier : it provides a consistent state of rows[] according some.It get a poiner on "rows", but doesn not delete it.
    RowsManager* rows_manager;

public:
    RowWiseMatrix( fileplace_t,
                   fileplace_t,
                   cnode_id_t,
                   thread_id_t,
                   Value*,
                   BasicStrategy* );          // name of file

    RowWiseMatrix( fileplace_t,
                   fileplace_t,
                   cnode_id_t,
                   thread_id_t,
                   Value* );                                                        // name of file
    RowWiseMatrix( fileplace_t,
                   fileplace_t,
                   cnode_id_t,
                   thread_id_t,
                   Value*,
                   IndexFormat );                                                                  // name of file

    virtual
    ~RowWiseMatrix();


    void
    setStrategy( CubeStrategy strategy );

    void
    setStrategy( BasicStrategy* _str );


    void
    dropRow( cnode_id_t id );

    void
    dropAllRows();


    virtual void
    writeData();

    virtual Value* getValue( cnode_id_t, thread_id_t );
    virtual void   setValue( const Value*, cnode_id_t, thread_id_t );
    virtual void   setValue( double, cnode_id_t, thread_id_t );
    virtual void   setValue( uint64_t, cnode_id_t, thread_id_t );

    virtual Value*
    getValue();

    // / Returns a whole row -> row, as a char*
    virtual char* getRow( cnode_id_t );
    // / Stores a whole row -> row, as a char*
    virtual void setRow( char*, cnode_id_t );


    virtual void
    writeXML( std::ostream& out );

    template <class T>
    T
        getBuildInValue( cnode_id_t, thread_id_t );
};



template <class T>
T
RowWiseMatrix::getBuildInValue( cnode_id_t cid, thread_id_t tid )
{
    T     _to_return;
    row_t _present_row1 = rows[ cid ];
    if ( _present_row1 == NULL )
    {
        rows_manager->provideRow( cid );
        row_t _present_row2 = rows[ cid ];
        if ( _present_row2 == NULL )
        {
            rows[ cid ] = _no_row_pointer;
            _to_return  =   static_cast<T>( 0 );
        }
        else
        {
            _to_return =  row_interface->template getBuildInData<T>( _present_row2, tid );
        }
    }
    else
    {
        if ( _present_row1 == _no_row_pointer  )
        {
            _to_return = static_cast<T>( 0 );
        }
        else
        {
            _to_return =  row_interface->template getBuildInData<T>( _present_row1, tid );
        }
    }
    return _to_return;
}
}

#endif
