/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2019                                                **
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
#include "MdTraversal.h"

#include "CnodeSubForest.h"
#include "MdAggrCube.h"
#include "CnodeMetric.h"

#include "CubeError.h"

using namespace cube;
using namespace std;

MdTraversal::MdTraversal()
    : Traversal()
{
}

MdTraversal::MdTraversal( vector<string> metrics )
    : Traversal(), metrics( metrics )
{
}

void
MdTraversal::initialize( CnodeSubForest* forest )
{
    MdAggrCube*               cube           = forest->get_reference_cube();
    MdTraversal_ErrorHandling error_handling = get_error_handling_strategy();

    for ( vector<string>::iterator it = metrics.begin(); it != metrics.end(); ++it )
    {
        CnodeMetric* md = cube->get_cnode_metric( *it );
        if ( md == NULL )
        {
            if ( error_handling == FATAL )
            {
                throw Error( "Could not find metric named " + *it );
            }
            else
            {
                errors.push_back( *it );
            }
            continue;
        }
        cnode_metrics.push_back( md );
    }
}

void
MdTraversal::finalize( CnodeSubForest* )
{
    MdTraversal_ErrorHandling error_handling = get_error_handling_strategy();
    if ( error_handling == WARNING )
    {
        if ( errors.empty() == false )
        {
            cerr << "Warning: The following cnode metrics were not registered "
                 << "with the MdAggrCube object. They could not be processed:"
                 << endl;
            for ( vector<string>::iterator it = errors.begin(); it != errors.end(); ++it )
            {
                cerr << *it << endl;
            }
        }
    }
}

MdTraversal_ErrorHandling
MdTraversal::get_error_handling_strategy()
const
{
    return FATAL;
}

string
MdTraversal::get_metric( unsigned int id )
const
{
    return metrics.at( id );
}
