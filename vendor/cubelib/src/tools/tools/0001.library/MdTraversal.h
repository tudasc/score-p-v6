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



#ifndef MDTRAVERSAL_H_GUARD_
#define MDTRAVERSAL_H_GUARD_

/**
 * @file    MdTraversal.h
 * @brief   Contains a class that extends the traversal class and provides
 *          comfortable translation of metric string representations to actual
 *          MetricDesriptor instances.
 */

#include <vector>
#include <string>

#include "Traversal.h"

namespace cube
{
class CnodeSubForest;
class CnodeMetric;

/**
 * @enum    MdTraversal_ErrorHandling
 *
 * Usually describes, how MdTraversal instances handle errors when looking
 * up the CnodeMetric instances.
 */
typedef enum MdTraversal_ErrorHandling
{                         // The interpretation used by MdTraversal:
    FATAL,                ///  Throw an exception.
    WARNING,              ///  Output to stderr
    SILENT                ///  Just collect errors, i.e. implement handling yourself.
} MdTraversal_ErrorHandling;

/**
 * @class   MdTraversal
 * @brief   Class extends Traversal and provides easy translation from
 *          stringified metric descriptors to actual MetricDesriptor instances.
 */
class MdTraversal : public Traversal
{
public:
    /**
     * @fn MdTraversal()
     *
     * Constructs an empty MdTraversal instance.
     */
    MdTraversal();

    /**
     * @fn MdTraversal(std::vector<std::string> metrics)
     *
     * Construts and initializes a MdTraversal instance. The list of strings is
     * stored for later usage in initialize and finalize.
     *
     * @param metrics A list of stringified metric descriptors.
     */
    MdTraversal( std::vector<std::string> metrics );

    /**
     * @fn MdTraversal_ErrorHandling get_error_handling_strategy() const
     *
     * Returns the error handling strategy. You can overload this method to
     * change the behaviour when metric strings are looked up. There are three
     * options:
     *
     * - cube::FATAL: Throws an exception when a metric is missing.
     * - cube::WARNING: Stores errors and prints out an error message with all
     *                missing metrics when traversing the forest has finished.
     * - cube::SILENT: Just store errors, but do not produce any output. You
     *                should implement some error handling strategy yourself.
     *
     * The default implementation returns FATAL.
     */
    virtual MdTraversal_ErrorHandling
    get_error_handling_strategy() const;

protected:
    /**
     * @fn virtual void initialize(CnodeSubForest* forst)
     *
     * This function is called when the MdTraversal gets applied to a
     * CnodeSubForest (c.f. Traversal) and translates the stringifed version
     * of a CnodeMetric into the instance that belongs to the same cube,
     * the forest belongs to.
     *
     * @param forest The forest, the traversal is applied on.
     */
    virtual void
    initialize( CnodeSubForest* forest );

    /**
     * @fn virtual void finalize(CnodeSubForest* forest)
     *
     * This function gets called as soon as the traversal on a certain
     * CnodeSubForest has finished (c.f. Traversal) and cleans up some things.
     * In case, the ErrorHandling is set to WARNING, it will also output
     * some warnings during this phase.
     *
     * @param forest The forest, the traversal was applied on.
     */
    virtual void
    finalize( CnodeSubForest* forest );

    std::string
    get_metric( unsigned int id = 0 ) const;

    std::vector<CnodeMetric*> cnode_metrics;
    std::vector<std::string>  errors;

private:
    std::vector<std::string> metrics;
};
}

#endif
