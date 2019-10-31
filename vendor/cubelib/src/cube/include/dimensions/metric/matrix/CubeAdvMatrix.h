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
 * \file CubeAdvMatrix.h
 * \brief Provides a for given Metric a matrix ov values (Cnode, Thread) -> Value
 */

#ifndef __ADV_MATRIX_H
#define __ADV_MATRIX_H

#include <iostream>

#include "CubeTypes.h"


namespace cube
{
/**
 * Class "advMatrix" is an abstract class, which defines a interface for "Metric" to access the data
 */
class advMatrix
{
protected:
    // / cnode dimension of the matrix are known on this level. Neither type of the values, nor real layout.
    cnode_id_t ncid;
    // / thread dimension of the matrix are known on this level. Neither type of the values, nor real layout.
    thread_id_t ntid;
public:
    virtual
    ~advMatrix()
    {
    };
    cnode_id_t
    get_ncid()
    {
        return ncid;
    };
    thread_id_t
    get_ntid()
    {
        return ntid;
    };

    virtual void
    writeData() = 0;                                 // /< Writes Data to disk

    // / Returns a  pointer on value, saved on position (cnode_id, thread_id)
    virtual Value* getValue( cnode_id_t, thread_id_t ) = 0;

    // / Returns a  pointer on empty value
    virtual Value*
    getValue() = 0;


    // / Sets a value on position (cnode_id, thread_id) using a pointer on Value.
    virtual void setValue( const Value*, cnode_id_t, thread_id_t ) = 0;

    // / Sets a value on position (cnode_id, thread_id) using double value. Internally the "double" is transformed into "Value".
    virtual void setValue( double, cnode_id_t, thread_id_t ) = 0;
    // / Sets a value on position (cnode_id, thread_id) using unsigned value. Internally the "uint64_t" is transformed into "Value".
    virtual void setValue( uint64_t, cnode_id_t, thread_id_t ) = 0;


    // / Returns a whole row -> row, as a char*
    virtual char* getRow( cnode_id_t ) = 0;
    // / Stores a whole row -> row, as a char*
    virtual void setRow( char*, cnode_id_t ) = 0;

//     /// For the calculation of the incl/excl values needed method.  Sum N values in the column, starting from  (cnode, thread)
//     virtual Value* sumColumn( cnode_id_t, thread_id_t, uint64_t ) = 0;

    // / Writes tha XML Representation of the matrix. (cube3 format)
    virtual void
    writeXML( std::ostream& out ) = 0;

    // / just a prototype for setting the strategy, realisation in RowWiseMatrix
    virtual void
    setStrategy( CubeStrategy strategy ) = 0;

    virtual void
    setStrategy( BasicStrategy* _str ) = 0;


    // / just a prototype to control the memory footprint
    virtual void
    dropRow( cnode_id_t id ) = 0;
};
}

#endif
