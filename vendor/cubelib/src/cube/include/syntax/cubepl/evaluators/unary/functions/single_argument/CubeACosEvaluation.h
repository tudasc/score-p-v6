/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2018                                                **
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


#ifndef __ACOS_EVALUATION_H
#define __ACOS_EVALUATION_H 0

#include "CubeUnaryEvaluation.h"

namespace cube
{
class ACosEvaluation : public UnaryEvaluation
{
public:
    ACosEvaluation();
    ACosEvaluation( GeneralEvaluation* _arg ) : UnaryEvaluation( _arg )
    {
    };
    virtual
    ~ACosEvaluation();

    virtual
    double
    eval() const;


    virtual
    double
    eval( const Cnode*,
          const CalculationFlavour,
          const Sysres*,
          const CalculationFlavour   ) const;


    virtual
    double
    eval( const Cnode*,
          const CalculationFlavour ) const;

    virtual
    double*
    eval_row( const Cnode*             _cnode,
              const CalculationFlavour _cf ) const;

    virtual
    double
    eval( const list_of_cnodes&       lc,
          const list_of_sysresources& ls ) const;

    virtual
    double*
    eval_row( const list_of_cnodes&       lc,
              const list_of_sysresources& ls ) const;



    virtual
    void
    print() const
    {
        std::cout << "acos( ";
        arguments[ 0 ]->print();
        std::cout << ")";
    };

    virtual
    double
    eval( double arg1,
          double arg2 ) const;
};
};

#endif
