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



#ifndef REGIONCONSTRAINT_H_GUARD_
#define REGIONCONSTRAINT_H_GUARD_

#include <set>
#include <string>
#include <utility>

#include "Traversal.h"
#include "TreeConstraint.h"

namespace cube
{
class MdAggrCube;
class Region;

class RegionConstraint : public TreeConstraint
{
    class RegionConstraintTraversal : public Traversal
    {
public:
        RegionConstraintTraversal(
            RegionConstraint* constraint,
            bool              auto_initialize_tests );
        virtual Traversal_Type
        get_type() const;
        virtual bool
        is_constant() const;

protected:
        virtual void
        node_handler( CnodeSubTree* tree );

private:
        RegionConstraint* constraint;
        bool              auto_initialize_tests;
        std::set<Region*> visited_regions;
    };

public:
    RegionConstraint( CnodeSubForest* forest,
                      bool            auto_initialize_test = true );
    virtual
    ~RegionConstraint();

    virtual void
    check();

protected:
    using TreeConstraint::skip;
    using TreeConstraint::fail;

    virtual void
    region_handler( Region* region ) = 0;

    virtual void
    skip( std::string reason,
          Region*     region );
    virtual void
    fail( std::string reason,
          Region*     region );
    virtual std::string
    build_header( Region* region );

private:
    RegionConstraintTraversal traversal;
};
}

#endif
