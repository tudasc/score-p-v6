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



#ifndef ABRIDGETRAVERSAL_H_GUARD_
#define ABRIDGETRAVERSAL_H_GUARD_

/**
 * @file    AbridgeTraversal.h
 * @brief   Contains a class that allows you to remove certain nodes
 *          from a CnodeSubForest depending on some metric's values.
 */

#include <string>

#include "MdTraversal.h"

namespace cube
{
/**
 * @enum    Abridge_ThresholdType
 * @brief   The way a certain threshold is interpreted, either as an absolute
 *          value or as a percentage value of the tree's root.
 */
typedef enum Abridge_ThresholdType
{
    THRTYPE_ABSOLUTE,
    THRTYPE_ROOT_RELATIVE,
    THRTYPE_CUMSUM
} Abridge_ThresholdType;

class CnodeSubForest;
class CnodeSubTree;
/**
 * @class   AbridgeTraversal
 * @brief   Very basic class to modify a CnodeSubForest based on some simple
 *          criterias for the metrics involved.
 */
class AbridgeTraversal : public MdTraversal
{
public:
    /**
     * @fn AbridgeTraversal(std::string metric, double threshold,
     *                      Abridge_ThresholdType type)
     *
     * Constructs a new AbridgeTraversal that may be applied on a certain
     * CnodeSubForest using the run method.
     *
     * This traversal removes certain nodes within the tree based on a metric,
     * a threshold and a threshold type. For each tree, a tree-threshold is
     * computed out of the threshold, the threshold type and the tree root's
     * value for the specific metric. Then every node within the tree is
     * checked and removed in case the node's value for the specific metric
     * is below the computed threshold.
     *
     * For the threshold type THRTYPE_ABSOLUTE, the tree-threshold is just
     * the same as the passed in threshold value.
     *
     * For the threshold type THRTYPE_ROOT_RELATIVE, the tree-threshold is
     * the original threshold multiplied by the root's value for the metric.
     * Obviously, for inclusive metrics only a threshold value between 0 and
     * 1 makes sense.
     *
     * @param metric A metric descriptor string, i.e. a stringified version
     *               of a specific metric. See MdTraversal.
     * @param threshold The threshold value.
     * @param type The threshold type.
     */
    AbridgeTraversal( std::string           metric,
                      double                threshold,
                      Abridge_ThresholdType type = THRTYPE_ROOT_RELATIVE );
    virtual Traversal_Type
    get_type() const
    {
        return TRAVERSE_PREORDER;
    }

protected:
    virtual void
    initialize( CnodeSubForest* forest );
    virtual void
    initialize_tree( CnodeSubTree* node );
    virtual void
    node_handler( CnodeSubTree* node );

private:
    unsigned int          number_of_cubes;
    double                tree_threshold;
    double                threshold;
    Abridge_ThresholdType type;
};
}

#endif
