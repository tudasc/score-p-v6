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



#ifndef CNODESUBTREE_H_GUARD_
#define CNODESUBTREE_H_GUARD_

#include <vector>

namespace cube
{
class PrintableCCnode;
class Traversal;

class CnodeSubTree
{
public:
    CnodeSubTree( PrintableCCnode* pccnode );
    CnodeSubTree( CnodeSubTree const& copy );
    ~CnodeSubTree();
    unsigned int
    num_children() const;
    CnodeSubTree*
    get_child( unsigned int id ) const;
    PrintableCCnode*
    get_reference_node() const;
    void
    add_child( CnodeSubTree* child );
    void
    remove_child( CnodeSubTree* child );
    void
    remove_child( unsigned int id );
    void
    cut();
    void
    traverse( Traversal* t );

protected:
    void
    preorder_traverse( Traversal* t );
    void
    postorder_traverse( Traversal* t );
    void
    bf_traverse( Traversal* t );
    void
    reloc_remove_child( unsigned int id );

private:
    bool                       mark_of_death;
    CnodeSubTree*              parent;
    std::vector<CnodeSubTree*> childv;
    PrintableCCnode*           reference_node;
};
}

#endif
