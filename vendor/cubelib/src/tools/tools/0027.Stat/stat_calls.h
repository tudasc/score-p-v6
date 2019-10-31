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



#ifndef __CUBE_STAT_INTERNALS_H
#define __CUBE_STAT_INTERNALS_H


#include <string>
#include <vector>

#include "AggrCube.h"
#include "CubeMetric.h"



using stats::P2Statistic;

namespace cubestat
{
cube::Metric*
findMetric( cube::AggrCube* cubeObject, const std::string& metname,
            bool exact = true )
{
    std::vector<cube::Metric*> const& metVec = cubeObject->get_metv();
    for ( std::vector<cube::Metric*>::const_iterator it = metVec.begin();
          it != metVec.end(); ++it )
    {
        const std::string& uname = ( *it )->get_uniq_name();
        size_t             pos;
        if ( exact )
        {
            if ( uname == metname )
            {
                return *it;
            }
        }
        // uname ends with metname?
        else if ( ( pos = uname.rfind( metname ) ) != std::string::npos )
        {
            if ( ( uname.length() - metname.length() ) == pos )
            {
                return *it;
            }
        }
    }
    return 0;
}



/*-------------------------------------------------------------------------*/
/**
 * @class   indirectCmp
 * @brief   Greater functor for index sorting
 *
 * Functor calculating "Greater" used for generating index std::vector.
 * Constructor argument "vals" is reference to base std::vector which values
 * determine the sort order.
 */
/*-------------------------------------------------------------------------*/
class indirectCmp
{
public:
    indirectCmp( std::vector<double>& vals ) : myVals( vals )
    {
    }
    bool
    operator()( int l, int r ) const
    {
        return myVals[ l ] > myVals[ r ];
    }
private:
    std::vector<double>& myVals;
};
}




#endif
