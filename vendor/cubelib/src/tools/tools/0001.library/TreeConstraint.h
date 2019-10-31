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



#ifndef TREECONSTRAINT_H_GUARD_
#define TREECONSTRAINT_H_GUARD_

#include <set>

#include "AbstractConstraint.h"

namespace cube
{
class Cnode;
class CnodeSubForest;
class CnodeSubTree;
class Region;

class TreeConstraint : public AbstractConstraint
{
public:
    TreeConstraint( CnodeSubForest* forest = NULL );
    virtual
    ~TreeConstraint();

    void
    set_forest( CnodeSubForest* new_forest );

    virtual void
    check();

    bool
    is_skipable( CnodeSubTree* node ) const;

protected:
    bool
    is_skipable( Cnode* node ) const;
    bool
    is_skipable( Region* region ) const;
    void
    add_to_skipped( Cnode* node );
    void
    add_to_failed( Cnode* node );
    void
    add_to_skipped( Region* region );
    void
    add_to_failed( Region* region );

    std::set<Cnode*>
    get_skipable_cnodes() const;

    std::set<Region*>
    get_skipable_regions() const;
    CnodeSubForest*
    get_forest() const;

private:
    CnodeSubForest*   forest;
    std::set<Cnode*>  skipped_cnodes;
    std::set<Cnode*>  failed_cnodes;
    std::set<Region*> skipped_regions;
    std::set<Region*> failed_regions;
};
};

#endif
