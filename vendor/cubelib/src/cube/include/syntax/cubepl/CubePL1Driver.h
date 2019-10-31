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


#ifndef __CUBEPL1_DRIVER_H
#define __CUBEPL1_DRIVER_H 0

#include <vector>
#include <iostream>
#include <float.h>
#include <cmath>



#include "CubePLDriver.h"



namespace cubeplparser
{
class CubePL1Driver : public CubePLDriver
{
public:

    CubePL1Driver( cube::Cube* );

    virtual
    ~CubePL1Driver();

    virtual
    cube::GeneralEvaluation*
    compile( std::         istream*,
             std::ostream* errs );

    virtual
    bool
    test( std::string&,
          std::string& );

    virtual
    std::string
    printStatus();
};
};

#endif
