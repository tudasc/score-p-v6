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


#ifndef __CONSTANT_EVALUATION_H
#define __CONSTANT_EVALUATION_H 0

#include "CubeNullaryEvaluation.h"
#include "CubeServices.h"
using namespace std;

namespace cube
{
class ConstantEvaluation : public NullaryEvaluation
{
protected:
    double constant;

public:
    ConstantEvaluation( double _const );
    ConstantEvaluation( std::string _const );

    virtual
    ~ConstantEvaluation();

    inline
    virtual
    double
    eval() const
    {
        return constant;
    };

    virtual
    double
    eval( const Cnode*,
          const CalculationFlavour,
          const Sysres*,
          const CalculationFlavour   ) const
    {
        return constant;
    };


    virtual
    double
    eval( const Cnode*, const CalculationFlavour ) const
    {
        return constant;
    };

    virtual
    double*
    eval_row( const Cnode*,
              const CalculationFlavour ) const
    {
        double* result = services::create_row_of_doubles( row_size );
        for ( size_t i = 0; i < row_size; i++ )
        {
            result[ i ] = constant;
        }
        return result;
    }


    inline
    virtual
    double
    eval( const list_of_cnodes& lc, const list_of_sysresources& ls ) const
    {
        ( void )lc;
        ( void )ls;
        return constant;
    };

    virtual
    double*
    eval_row( const list_of_cnodes& lc, const list_of_sysresources& ls ) const
    {
        ( void )lc;
        ( void )ls;
        double* result = services::create_row_of_doubles( row_size );
        for ( size_t i = 0; i < row_size; i++ )
        {
            result[ i ] = constant;
        }
        return result;
    };





    virtual
    void
    print() const
    {
        std::cout << constant;
    };

    virtual
    double
    eval( double,
          double ) const
    {
        return constant;
    };
};
};

#endif
