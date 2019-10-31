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



#ifndef CNODESUBFOREST_H_GUARD_
#define CNODESUBFOREST_H_GUARD_

#include <vector>
#include "CnodeSubTree.h"
#include "Traversal.h"

namespace cube
{
class MdAggrCube;
class Traversal;
class CnodeSubTree;
class PrintableCCnode;

class CnodeSubForest
{
    class GenerateNodeList : public Traversal
    {
public:
        GenerateNodeList( std::vector<CnodeSubTree*>& nodes )
            : nodes( nodes )
        {
        }
        Traversal_Type
        get_type() const
        {
            return TRAVERSE_POSTORDER;
        }
        bool
        is_constant() const
        {
            return true;
        }

protected:
        void
        node_handler( CnodeSubTree* node );

private:
        std::vector<CnodeSubTree*>& nodes;
    };

public:
    CnodeSubForest( CnodeSubForest const& copy );
    CnodeSubForest( MdAggrCube* cube );
    CnodeSubForest( std::vector<CnodeSubTree*> trees,
                    MdAggrCube*                cube );
    CnodeSubForest( std::       vector<PrintableCCnode*> const&,
                    MdAggrCube* cube );
    ~CnodeSubForest();
    MdAggrCube*
    get_reference_cube()
    {
        return cube;
    }
    CnodeSubTree*
    get_root( unsigned int id = 0 )
    {
        return roots.at( id );
    }
    void
    traverse( Traversal* trav );

private:
    MdAggrCube*                cube;
    std::vector<CnodeSubTree*> roots;
    std::vector<CnodeSubTree*> nodes;
};
}

#endif
