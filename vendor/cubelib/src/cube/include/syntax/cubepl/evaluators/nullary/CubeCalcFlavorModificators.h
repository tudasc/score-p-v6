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


#ifndef __CALC_FLAVOR_MODIFICATORS_H
#define __CALC_FLAVOR_MODIFICATORS_H 0


#include <float.h>
#include <cmath>

#include "CubeTypes.h"
namespace cube
{
class CalcFlavorModificator
{
protected:
    bool verbose_execution;
public:

    CalcFlavorModificator()
    {
        verbose_execution = false;
    };

    virtual
    ~CalcFlavorModificator()
    {
    };

    virtual
    CalculationFlavour
    flavour( CalculationFlavour cf = CUBE_CALCULATE_SAME ) const
    {
        return cf;
    };

    virtual void
    print() const = 0;

    virtual
    double
    eval( double, double ) const
    {
        return 0.;
    };

    inline
    virtual
    void
    set_verbose_execution( bool _v )
    {
        verbose_execution = _v;
    }
};


class CalcFlavorModificatorSame : public CalcFlavorModificator
{
    virtual void
    print() const
    {
        std::cout << "*";
    };
};

class CalcFlavorModificatorIncl : public CalcFlavorModificator
{
public:
    virtual
    ~CalcFlavorModificatorIncl()
    {
    };
    CalculationFlavour
    flavour( CalculationFlavour cf = CUBE_CALCULATE_INCLUSIVE ) const
    {
        cf = CUBE_CALCULATE_INCLUSIVE;
        return cf;
    };
    virtual void
    print() const
    {
        std::cout << "i";
    };
};


class CalcFlavorModificatorExcl : public CalcFlavorModificator
{
public:
    virtual
    ~CalcFlavorModificatorExcl()
    {
    };
    CalculationFlavour
    flavour( CalculationFlavour cf = CUBE_CALCULATE_EXCLUSIVE ) const
    {
        cf = CUBE_CALCULATE_EXCLUSIVE;
        return cf;
    };
    virtual void
    print() const
    {
        std::cout << "e";
    };
};
};

#endif
