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



#ifndef COMPUTETRAVERSAL_H_GUARD_
#define COMPUTETRAVERSAL_H_GUARD_

#include <string>
#include <vector>

#include "MdTraversal.h"
#include "algebra4.h"

namespace cube
{
class CnodeSubTree;

class ComputeTraversal : public MdTraversal
{
public:
    ComputeTraversal( std::vector<std::string> metrics );
    virtual Traversal_Type
    get_type() const
    {
        return TRAVERSE_UNORDERED;
    }
    virtual bool
    is_constant() const
    {
        return true;
    }
    virtual bool
    get_auto_register_metric_mode() const
    {
        return true;
    }

protected:
    virtual void
    initialize( CnodeSubForest* forest );
    virtual void
    node_handler( CnodeSubTree* node );

private:
    const std::vector<CubeMapping*>* mappings;
};
}

#endif
