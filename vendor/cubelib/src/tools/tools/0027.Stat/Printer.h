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



#ifndef __CUBE_STAT_PRINTER_H
#define __CUBE_STAT_PRINTER_H


#include <vector>

#include "Cube.h"
#include "AggrCube.h"
#include "CubeMetric.h"
#include "CubeCnode.h"

#include "stat_calls.h"

/*-------------------------------------------------------------------------*/
/**
 * @class   Printer
 * @brief   Abstract base class of all Printer classes.
 *          Used to extract the CUBE cube::Metric and cube::Cnode objects based on the
 *          names entered by the user.
 *
 * This is the common base class of all Printer classes. It's purpose is to
 * provide access to the CUBE cube::Metric and cube::Cnode objects based on given names.
 * It also prints warnings if there are no Metrics or Cnodes for a given name.
 */
/*-------------------------------------------------------------------------*/
class Printer
{
public:
    // / @name Constructor & destructor
    // / @{
    Printer( cube::AggrCube*                 cubeObject,
             std::vector<std::string> const& metNames,
             std::vector<std::string> const& cnodeNames );
    virtual
    ~Printer()
    {
    }
    // / @}
    // / @name Getters for cube objects
    // / @{
    std::vector<cube::Metric*> const&
    GetRequestedMetrics() const
    {
        return requestedMetricVec;
    }
    std::vector<cube::Cnode*>  const&
    GetRequestedCnodes() const
    {
        return requestedCnodeVec;
    }
    // / @}
private:
    std::vector<cube::Metric*> requestedMetricVec;
    std::vector<cube::Cnode*>  requestedCnodeVec;
};




/**
 * Creates a new Printer instance from the given CUBE object and the names of
 * the requested metrics and cnodes.
 *
 * @param cubeObject The CUBE object used to parse the CUBE file to be analyzed.
 * @param metNames A std::vector containing all metric names for which data is to be
 * gathered and printed.
 * @param cnodeNames A std::vector containing all region names for which data is to
 * be gathered and printed.
 */
Printer::Printer( cube::AggrCube*                 cubeObject,
                  std::vector<std::string> const& metNames,
                  std::vector<std::string> const& cnodeNames )
{
    for ( std::vector<std::string>::const_iterator metNameIT = metNames.begin();
          metNameIT != metNames.end(); ++metNameIT )
    {
        if ( cube::Metric * m = cubestat::findMetric( cubeObject, *metNameIT ) )
        {
            requestedMetricVec.push_back( m );
        }
        else
        {
            std::cerr << "WARNING: cube::Metric " << *metNameIT << " doesn't exist"
                      << std::endl;
        }
    }

    std::vector<cube::Cnode*> const& cnodeVec = cubeObject->get_cnodev();
    for ( std::vector<std::string>::const_iterator cnodeNameIT = cnodeNames.begin();
          cnodeNameIT != cnodeNames.end(); ++cnodeNameIT )
    {
        bool cnodeFound = false;
        for ( std::vector<cube::Cnode*>::const_iterator cnodeIT = cnodeVec.begin();
              cnodeIT != cnodeVec.end(); ++cnodeIT )
        {
            if ( *cnodeNameIT == ( *cnodeIT )->get_callee()->get_name() )
            {
                requestedCnodeVec.push_back( *cnodeIT );
                cnodeFound = true;
            }
        }
        if ( !cnodeFound )
        {
            std::cerr << "WARNING: cube::Cnode with name " << *cnodeNameIT
                      << " doesn't exist" << std::endl;
        }
    }
}


#endif
