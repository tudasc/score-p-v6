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
 * \file CubeIndexHeader.h
 * \brief Provides a format of the header at the beginning of the Index-File. It provides general information about the layout (#cnodes, #threads), endianess, saved value and so on.
 */

#ifndef __INDEX_HEADER_H
#define __INDEX_HEADER_H

#include <fstream>
#include "CubeTypes.h"



namespace cube
{
/**
 * Provides methods to get the general information about data lyout, endianess and transformation.
 *
 */
class IndexHeader
{
private:
    // / Heart of  the class, Physical representation of the header.
    Header header;
    // / Saves the transformation, which is needed to deal with endianess.
    SingleValueTrafo* trafo;

    // / Index , used to acces he data. Can be Sparse or Dense
    Index* index;
    // / Field, holding the value of the data
    char data_type;
    // / Field, holding the sizes of underlying data
    threads_number_t threads_count;
    cnodes_number_t  cnodes_count;

    // / applies the trafo to adjust endianess
    void
    applyTrafo();

    // / checks the header.format and creates a corresponding Index
    void
    selectIndex();


public:
    // / Constructor  used if one reads existing header.
    IndexHeader( cnodes_number_t,
                 threads_number_t );
    // / Constructor  used if one will save header.
    IndexHeader( cnodes_number_t,
                 threads_number_t,
                 IndexFormat format );
    virtual
    ~IndexHeader();

    // / Reads the first sizeof(Header) bytes into Header from fstream
    virtual void
    readHeader( std::fstream& );

    // / Reads the first sizeof(Header) bytes into Header from "file"
    virtual void readHeader( fileplace_t );
    // / Writes into the first sizeof(Header) bytes of the fstream the  Header
    virtual void
    writeHeader( std::fstream& );

    // / Writes into the first sizeof(Header) bytes of the fstream the  Header
    virtual void
    writeHeader( FILE* );


    // / Writes into the first sizeof(Header) bytes of the file the  Header
    virtual void writeHeader( fileplace_t );

    // / Prints the saved information into STDOUT. Used for Debugging
    virtual void
    printSelf();

    inline
    uint32_t
    getEndianness()
    {
        return header.named.endianness;
    };

    inline
    uint16_t
    getVersion()
    {
        return header.named.version;
    };

    inline
    char
    getIndexFormat()
    {
        return header.named.format;
    };

    inline
    SingleValueTrafo*
    getTrafo()
    {
        return trafo;
    };

    inline
    Index*
    getIndex()
    {
        return index;
    };
};
}

#endif
