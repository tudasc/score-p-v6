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



#ifndef CNODECONSTRAINT_H_GUARD_
#define CNODECONSTRAINT_H_GUARD_

/**
 * @file    CnodeConstraint.h
 * @brief   Contains a class for most Cnode-based tests.
 */

#include <set>
#include <string>
#include <utility>

#include "Traversal.h"
#include "TreeConstraint.h"

namespace cube
{
class CnodeConstraint;
class CnodeSubForest;

/**
 * @enum    Constraint_CnodeOutputMode
 * @brief   Encodes output modes for reporting erronous Cnodes
 *
 * You can combine any of the enum's values using bit-wise OR. At the moment,
 * there are three output modes supported:
 *  - CNODE_OUTPUT_MODE_BASIC, basic information about the Cnode
 *  - CNODE_OUTPUT_MODE_BACKTRACE, back-trace of the Cnode
 *  - CNODE_OUTPUT_MODE_TREE_REROOTED, prints out a tree, where the current
 *    Cnode is the root of the tree
 * The current behaviour is that CNODE_OUTPUT_MODE_BASIC is always enabled.
 */
typedef enum Constraint_CnodeOutputMode
{
    CNODE_OUTPUT_MODE_BASIC         = 0,
    CNODE_OUTPUT_MODE_BACKTRACE     = 1,
    CNODE_OUTPUT_MODE_TREE_REROOTED = 2
} Constraint_CnodeOutputMode;

/**
 * @class   CnodeConstraint
 * @brief   Abstract class, meant for simple, Cnode based tests.
 *
 * This class assists in creating Cnode based tests. It provides a way to
 * iterate over all Cnodes of a CnodeSubForest (internally using a Traversal
 * based class). You may choose to run tests only on Cnodes that either passed
 * certain tests that were run earlier or that failed certain tests, for
 * example to expore reasons for certain errors automatically. Error
 * investigating tests are explained at CnodeConstraint::CnodeConstraint,
 * Skipping mechanisms are documented at CnodeConstraint::get_skipable_cnodes.
 *
 * This class also communicates with RegionConstraint-based classes to skip
 * certain Cnode instances in case a RegionConstraint failed on the Cnode's
 * callee region before. Behviour is documented at
 * CnodeConstraint::get_skipable_regions.
 *
 * It also provides helpful methods to produce better Cnode-related error
 * messages, although this is basically just some wrapper-code around the
 * methods of the AbstractConstraint class and the PrintableCCnode class or
 * its super classes. See CnodeConstraint::fail and CnodeConstraint::skip
 * for more details.
 *
 * If you want to implement this abstract class, you have to provide at least
 * three methods:
 *  - virtual void node_handler(CnodeSubTree* tree) (for CnodeConstraint)
 *  - virtual string get_name() (for AbstractConstraint)
 *  - virtual string get_description() (for AbstractConstraint)
 *
 * If you want to run tests based on certain Metric or CnodeMetric instances,
 * you may want to take a look into MetricCnodeConstraint or
 * CMetricCnodeConstraint, which will also handle the look-up of the metric
 * for you and provide another method to retrieve that Metric or CnodeMetric.
 */
class CnodeConstraint : public TreeConstraint
{
    class CnodeConstraintTraversal : public Traversal
    {
public:
        CnodeConstraintTraversal(
            CnodeConstraint* constraint,
            bool             auto_initialize_tests );
        virtual Traversal_Type
        get_type() const;
        virtual bool
        is_constant() const;

protected:
        virtual void
        node_handler( CnodeSubTree* tree );

private:
        bool             auto_initialize_tests;
        CnodeConstraint* constraint;
    };

public:
    CnodeConstraint( CnodeSubForest* forest,
                     bool            auto_initialize_tests = true );
    virtual
    ~CnodeConstraint();

    virtual void
    check();

protected:
    using TreeConstraint::skip;
    using TreeConstraint::fail;

    virtual void
    cnode_handler( Cnode* cnode ) = 0;

    virtual void
    skip( std::string                reason,
          Cnode*                     node,
          Constraint_CnodeOutputMode mode = CNODE_OUTPUT_MODE_BASIC );
    virtual void
    fail( std::string                reason,
          Cnode*                     node,
          Constraint_CnodeOutputMode mode = CNODE_OUTPUT_MODE_BASIC );
    virtual std::string
    build_header( Cnode*                     node,
                  Constraint_CnodeOutputMode mode );

private:
    CnodeConstraintTraversal traversal;
};
}

#endif
