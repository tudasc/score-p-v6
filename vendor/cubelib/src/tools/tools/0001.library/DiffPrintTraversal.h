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


#ifndef DIFFPRINTTRAVERSAL_H_GUARD_
#define DIFFPRINTTRAVERSAL_H_GUARD_

/**
 * @file    DiffPrintTraversal.h
 * @brief   Contains a traversal class that compares a CnodeSubForest to the
 *          underlying Cnode trees and shows missing nodes in the
 *          CnodeSubForest as "aggregated nodes".
 */

#include <vector>
#include <string>
#include <iostream>
#include <ostream>

#include "MdTraversal.h"

namespace cube
{
class CnodeSubForest;
class CnodeSubTree;
class MdAggrCube;

/**
 * @class   DiffPrintTraversal
 *
 * This class implements a Traversal that may be used to print out
 * instances of CnodeSubForest. In contrast to PrintTraversal, this Traversal
 * looks for differences between the reference tree and the CnodeSubForest and
 * shows differences. As the reference tree is a superset of the CnodeSubForest
 * in a certain way, this class simply aggregates all requested metrics for
 * the missing Cnodes and shows them on a separate line.
 *
 * Aggregation only works for BasicMetricDescriptor instances, for other
 * instances a N/A message is displayed.
 */
class DiffPrintTraversal : public MdTraversal
{
public:
    /**
     * @fn DiffPrintTraversal
     *
     * @param metrics This is a list of stringified metrics, for example
     *        "basic@time:excl:*.*" or "visitors@".
     * @param stream A reference to an std::ostream instance. This is the
     *        stream, the function will print to during traversing the tree.
     */
    DiffPrintTraversal( std::vector<std::string> metrics,
                        std::ostream&            stream = std::cout );
    virtual Traversal_Type
    get_type() const
    {
        return TRAVERSE_PREORDER;
    }
    virtual MdTraversal_ErrorHandling
    get_error_handling_strategy() const
    {
        return WARNING;
    }

protected:
    virtual void
    initialize( CnodeSubForest* forest );
    virtual void
    node_handler( CnodeSubTree* node );

private:
    MdAggrCube*      cube;
    std::vector<int> number_of_metrics_cubes;
    std::ostream&    stream;
};
}

#endif
