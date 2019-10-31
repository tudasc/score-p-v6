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



#include "config.h"

#include "CubeLambdaCalculEvaluation.h"
using namespace cube;
using namespace std;


LambdaCalculEvaluation::LambdaCalculEvaluation() : UnaryEvaluation()
{
};


LambdaCalculEvaluation::~LambdaCalculEvaluation()
{
}

double
LambdaCalculEvaluation::eval() const
{
    for ( unsigned i = 0; i < getNumOfParameters() - 1; ++i )
    {
        arguments[ i ]->eval();
    }
    return arguments[ getNumOfParameters() - 1 ]->eval();
}


double
LambdaCalculEvaluation::eval( const cube::Cnode*       _cnode,
                              const CalculationFlavour _cf,
                              const cube::Sysres*      _sf,
                              const CalculationFlavour _tf   ) const
{
    for ( unsigned i = 0; i < getNumOfParameters() - 1; ++i )
    {
        arguments[ i ]->eval( _cnode, _cf, _sf, _tf );
    }
    return arguments[ getNumOfParameters() - 1 ]->eval( _cnode, _cf, _sf, _tf );
}


double
LambdaCalculEvaluation::eval( const cube::Cnode*       _cnode,
                              const CalculationFlavour _cf ) const
{
    for ( unsigned i = 0; i < getNumOfParameters() - 1; ++i )
    {
        arguments[ i ]->eval( _cnode, _cf );
    }
    return arguments[ getNumOfParameters() - 1 ]->eval( _cnode, _cf );
}

double
LambdaCalculEvaluation::eval( double arg1, double arg2 ) const
{
    for ( unsigned i = 0; i < getNumOfParameters() - 1; ++i )
    {
        arguments[ i ]->eval(  arg1, arg2 );
    }
    return arguments[ getNumOfParameters() - 1 ]->eval( arg1, arg2 );
}




double*
LambdaCalculEvaluation::eval_row( const Cnode*             _cnode,
                                  const CalculationFlavour _cf ) const
{
    for ( unsigned i = 0; i < getNumOfParameters() - 1; ++i )
    {
        delete[] ( arguments[ i ]->eval_row( _cnode, _cf ) );
    }
    return arguments[ getNumOfParameters() - 1 ]->eval_row( _cnode, _cf );
}


double
LambdaCalculEvaluation::eval(   const list_of_cnodes&       lc,
                                const list_of_sysresources& ls ) const
{
    for ( unsigned i = 0; i < getNumOfParameters() - 1; ++i )
    {
        arguments[ i ]->eval(  lc, ls );
    }
    return arguments[ getNumOfParameters() - 1 ]->eval( lc, ls );
}




double*
LambdaCalculEvaluation::eval_row(   const list_of_cnodes&       lc,
                                    const list_of_sysresources& ls ) const
{
    for ( unsigned i = 0; i < getNumOfParameters() - 1; ++i )
    {
        delete[] ( arguments[ i ]->eval_row( lc, ls ) );
    }
    return arguments[ getNumOfParameters() - 1 ]->eval_row( lc, ls );
}
