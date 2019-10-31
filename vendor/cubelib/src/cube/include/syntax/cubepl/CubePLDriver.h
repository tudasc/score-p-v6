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


#ifndef __CUBEPL_DRIVER_H
#define __CUBEPL_DRIVER_H 0

#include <vector>
#include <iostream>
#include <float.h>
#include <cmath>



#include "Cube.h"
#include "CubeEvaluators.h"




namespace cubeplparser
{
class CubePLDriver
{
protected:
    std::vector<std::string > errors;
    cube::Cube*               cube;
protected:
public:

    CubePLDriver( cube::Cube* _cube ) : cube( _cube )
    {
    };
    virtual
    ~CubePLDriver()
    {
    };

    virtual
    cube::GeneralEvaluation*
    compile( std::         istream*,
             std::ostream* errs ) =  0;

    virtual
    bool
    test( std::string&,
          std::string& ) = 0;

    virtual
    std::string
    printStatus() = 0;
};
};

#endif
