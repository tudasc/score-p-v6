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
#include <cmath>
#include <climits>
#include <float.h>

#include "CubeLnEvaluation.h"
using namespace cube;
using namespace std;


LnEvaluation::LnEvaluation() : UnaryEvaluation()
{
};


LnEvaluation::~LnEvaluation()
{
}

double
LnEvaluation::eval() const
{
    double result = arguments[ 0 ]->eval();
    if ( result > 0 )
    {
        return log( result );
    }
    if ( result == 0. )
    {
        return -DBL_MAX;
    }
    cerr << " Cannot calculate ln(" << result << "). Return zero" << endl;
    return 0.;
}



double
LnEvaluation::eval( const cube::Cnode*       _cnode,
                    const CalculationFlavour _cf,
                    const cube::Sysres*      _sf,
                    const CalculationFlavour _tf   ) const
{
    double _value = arguments[ 0 ]->eval(     _cnode, _cf,
                                              _sf, _tf
                                              );
    if ( _value > 0 )
    {
        return log( _value );
    }
    if ( _value == 0. )
    {
        return -DBL_MAX;
    }
    cerr << " Cannot calculate ln(" << _value << "). Return zero" << endl;
    return 0.;
}



double
LnEvaluation::eval( const cube::Cnode*       _cnode,
                    const CalculationFlavour _cf ) const
{
    double _value = arguments[ 0 ]->eval(     _cnode, _cf
                                              );
    if ( _value > 0 )
    {
        return log( _value );
    }
    if ( _value == 0. )
    {
        return -DBL_MAX;
    }
    cerr << " Cannot calculate ln(" << _value << "). Return zero" << endl;
    return 0.;
}

double
LnEvaluation::eval( double arg1, double arg2 ) const
{
    double _value = arguments[ 0 ]->eval( arg1, arg2  );
    if ( _value > 0 )
    {
        return log( _value );
    }
    if ( _value == 0. )
    {
        return -DBL_MAX;
    }
    cerr << " Cannot calculate ln(" << _value << "). Return zero" << endl;
    return 0.;
}



double*
LnEvaluation::eval_row( const Cnode*             _cnode,
                        const CalculationFlavour _cf ) const
{
    double* result =  arguments[ 0 ]->eval_row( _cnode, _cf );
    if ( result == NULL )
    {
        result = new double[ row_size ]();
    }
    for ( size_t i = 0; i < row_size; i++ )
    {
        if ( result[ i ] > 0 )
        {
            result[ i ] = log( result[ i ] );
        }
        else
        if ( result[ i ] == 0 )
        {
            result[ i ] = -DBL_MAX;
        }
        else
        {
            cerr << " Cannot calculate ln(" << result[ i ] << "). Return zero" << endl;
            result[ i ] = 0.;
        }
    }
    return result;
}


double
LnEvaluation::eval(  const list_of_cnodes&       lc,
                     const list_of_sysresources& ls ) const
{
    double _value = arguments[ 0 ]->eval( lc, ls  );
    if ( _value > 0 )
    {
        return log( _value );
    }
    if ( _value == 0. )
    {
        return -DBL_MAX;
    }
    cerr << " Cannot calculate ln(" << _value << "). Return zero" << endl;
    return 0.;
}



double*
LnEvaluation::eval_row(  const list_of_cnodes&       lc,
                         const list_of_sysresources& ls ) const
{
    double* result =  arguments[ 0 ]->eval_row( lc, ls );
    if ( result == NULL )
    {
        result = new double[ row_size ]();
    }
    for ( size_t i = 0; i < row_size; i++ )
    {
        if ( result[ i ] > 0 )
        {
            result[ i ] = log( result[ i ] );
        }
        else
        if ( result[ i ] == 0 )
        {
            result[ i ] = -DBL_MAX;
        }
        else
        {
            cerr << " Cannot calculate ln(" << result[ i ] << "). Return zero" << endl;
            result[ i ] = 0.;
        }
    }
    return result;
}
