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
 * \file CubeBasicStrategy.h
 * \brief Abstract base class for memory management strategies for
 * storing matrices.
 */
#ifndef CUBE_BASIC_STRATEGY_H
#define CUBE_BASIC_STRATEGY_H 0

#include "CubeTypes.h"

// KeepAll, LastN(20), PreloadAll
#define CUBE_STRATEGY_SELECTION "CUBE_DATA_LOADING"


namespace cube
{
class BasicStrategy
{
public:

    /**
     * Virtual destructor
     */
    virtual
    ~BasicStrategy()
    {
    };

    /**
     * Tells the strategy that a row is being added. May decide to
     * read all rows now. May cause removal of rows.
     *
     * @param[in] rowId The id of the row to be added.
     *
     * @param[out] readAllRows If true, all rows should be read at this point.
     *
     * @param[out] rowsToRemove Vector of rows to be removed as a
     * result.
     */
    virtual void
    addRow( const cnode_id_t         rowId,
            bool&                    readAllRows,
            std::vector<cnode_id_t>& rowsToRemove ) = 0;

    /**
     * Asks the strategy to remove a row. May cause removal of rows.
     *
     * @param[in] rowId The id of the row to be removed.
     *
     * @param[out] rowsToRemove Vector of rows to be removed as a
     * result.
     */
    virtual void
    removeRows( std::vector<cnode_id_t>& rowsWantedToReove,
                std::vector<cnode_id_t>& rowsToRemove ) = 0;


    virtual void
    removeRow( cnode_id_t               id,
               std::vector<cnode_id_t>& rowsToRemove )
    {
        std::vector<cnode_id_t> _ids;
        _ids.push_back( id );
        removeRows( _ids, rowsToRemove );
    }



    /**
     * Asks to add a list of rows and gets a list of rows, which do have to be removed first.
     * it might lead in naive realisation for dropping and adding of same rows.
     * The good realisation of a LastNRows should avoid removing and adding of same rows.
     *

     */
    virtual void
    needRows( std::vector<cnode_id_t>& rowsToAdd,
              std::vector<cnode_id_t>& rowsToRemoveFirst ) = 0;


    /**
     * @return If the return value is true, the rows can be freed,
     * otherwise not.
     */
    virtual bool
    permissionToFreeAll() = 0;

    /**
     * Tells the strategy that all rows have been freed. This is a way
     * to override the permissionToFreeAll() decision. Use sparingly.
     */
    virtual void
    forcedFreeAll() = 0;



    /**
     * Initializes an internal state of a strategy, using rows_t as a container for rows.
     * Used in strategies, which need information about internal state of the matrix
     *
     */
    virtual std::vector<cnode_id_t>
    initialize( rows_t* rows )
    {
        rows++;
        std::vector<cnode_id_t> _to_return;
        return _to_return;
    };


    static
    CubeStrategy
    selectInitialStrategy();
};
}

#endif
