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



#include "config.h"
#include "CMetricCnodeConstraint.h"

#include <string>
#include <sstream>

#include "CnodeMetric.h"
#include "CnodeConstraint.h"
#include "CnodeSubForest.h"
#include "MdAggrCube.h"
#include "PrintableCCnode.h"

#include "CubeCnode.h"
#include "CubeRegion.h"
#include "CubeError.h"

using namespace cube;
using namespace std;

CMetricCnodeConstraint::CMetricCnodeConstraint( CnodeSubForest* _forest,
                                                string          metric_str )
    : CnodeConstraint( _forest )
{
    metric = _forest->get_reference_cube()->get_cnode_metric( metric_str );
    if ( metric == NULL )
    {
        throw RuntimeError( "Could not find or create metric " + metric_str
                            + "!" );
    }
}

CnodeMetric*
CMetricCnodeConstraint::get_metric()
{
    return metric;
}

string
CMetricCnodeConstraint::build_header( Cnode*                     node,
                                      Constraint_CnodeOutputMode output_mode )
{
    stringstream ss;
    if ( ( output_mode & CNODE_OUTPUT_MODE_BASIC )
         == CNODE_OUTPUT_MODE_BASIC )
    {
        ss << "In call node with id " << node->get_id() << " (Name: "
           << node->get_callee()->get_name() << ")" << endl
           << "   " << "for cnode metric " << get_metric()->to_string()
           << " (" << metric->stringify() << ")" << endl;
    }
    if ( ( output_mode & CNODE_OUTPUT_MODE_BACKTRACE )
         == CNODE_OUTPUT_MODE_BACKTRACE )
    {
        PrintableCCnode* pccnode = dynamic_cast<PrintableCCnode*>( node );
        if ( pccnode != NULL )
        {
            pccnode->print_callpath( vector<CnodeMetric*>( 1, metric ), ss );
        }
        else
        {
            ss << "  Warning: Could not print out backtrace!" << endl;
        }
    }
    if ( ( output_mode & CNODE_OUTPUT_MODE_TREE_REROOTED )
         == CNODE_OUTPUT_MODE_TREE_REROOTED )
    {
        PrintableCCnode* pccnode = dynamic_cast<PrintableCCnode*>( node );
        if ( pccnode != NULL )
        {
            pccnode->print( vector<CnodeMetric*>( 1, metric ), ss );
        }
        else
        {
            ss << "  Warning: Could not print out re-rooted tree output!" << endl;
        }
    }
    return ss.str();
}
