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


#ifndef __MINUS_EVALUATION_H
#define __MINUS_EVALUATION_H 0

#include "CubeBinaryEvaluation.h"

namespace cube
{
static bool
almost_equal( double x, double y, int ulp )
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::abs( x - y ) < std::numeric_limits<double>::epsilon() * std::abs( x + y ) * ulp
           // unless the result is subnormal
           || std::abs( x - y ) < std::numeric_limits<double>::min();

//     return (std::abs(x-y) < std::abs(x+y) * 1E-14 *ulp) || (std::abs(x-y) < std::numeric_limits<double>::min());
}


static
inline
double
stable_minus( double a, double b )
{
    if ( almost_equal( a, b, 2 ) )
    {
        return 0;
    }
    return a - b;
}


class MinusEvaluation : public BinaryEvaluation
{
public:
    MinusEvaluation();
    MinusEvaluation( GeneralEvaluation*,
                     GeneralEvaluation* );
    virtual
    ~MinusEvaluation();

    inline
    virtual
    double
    eval() const
    {
        return stable_minus( ( arguments[ 0 ]->eval() ), ( arguments[ 1 ]->eval() ) );
    }

    inline
    virtual
    double
    eval( const Cnode*             _cnode,
          const CalculationFlavour _cf,
          const Sysres*            _sf,
          const CalculationFlavour _tf  ) const
    {
        return stable_minus(
            ( arguments[ 0 ]->eval( _cnode, _cf,
                                    _sf, _tf ) ), ( arguments[ 1 ]->eval( _cnode, _cf,
                                                                          _sf, _tf ) ) );
    }


    inline
    virtual
    double
    eval( const Cnode*             _cnode,
          const CalculationFlavour _cf ) const
    {
        return stable_minus( ( arguments[ 0 ]->eval( _cnode, _cf ) ), ( arguments[ 1 ]->eval( _cnode, _cf ) ) );
    }


    inline
    virtual
    double*
    eval_row( const Cnode*             _cnode,
              const CalculationFlavour _cf ) const
    {
        double* result  = arguments[ 0 ]->eval_row( _cnode, _cf );
        double* _result = arguments[ 1 ]->eval_row( _cnode, _cf );
        if ( result == NULL && _result == NULL )
        {
            return NULL;
        }
        else
        if ( _result == NULL )
        {
            return result;
        }
        else
        if ( result == NULL )
        {
            for ( size_t i = 0; i < row_size; i++ )
            {
                _result[ i ] = _result[ i ];
            }
            return _result;
        }
        else
        {
            for ( size_t i = 0; i < row_size; i++ )
            {
                result[ i ] = stable_minus( result[ i ],  _result[ i ] );
            }
            delete[] _result;
            return result;
        }
    }


    inline
    virtual
    double
    eval( const list_of_cnodes& lc, const list_of_sysresources& ls ) const
    {
        return stable_minus( ( arguments[ 0 ]->eval( lc, ls ) ), ( arguments[ 1 ]->eval( lc, ls ) ) );
    };

    virtual
    double*
    eval_row( const list_of_cnodes& lc, const list_of_sysresources& ls ) const
    {
        double* result  = arguments[ 0 ]->eval_row( lc, ls );
        double* _result = arguments[ 1 ]->eval_row( lc, ls );
        if ( result == NULL && _result == NULL )
        {
            return NULL;
        }
        else
        if ( _result == NULL )
        {
            return result;
        }
        else
        if ( result == NULL )
        {
            for ( size_t i = 0; i < row_size; i++ )
            {
                _result[ i ] = -_result[ i ];
            }
            return _result;
        }
        else
        {
            for ( size_t i = 0; i < row_size; i++ )
            {
                result[ i ] = stable_minus( result[ i ],  _result[ i ] );
            }
            delete[] _result;
            return result;
        }
    };




    inline
    virtual
    void
    print() const
    {
        arguments[ 0 ]->print();
        std::cout << "-";
        arguments[ 1 ]->print();
    };

    inline
    virtual
    double
    eval( double arg1,
          double arg2 ) const
    {
        return stable_minus( ( arguments[ 0 ]->eval( arg1, arg2 ) ), ( arguments[ 1 ]->eval( arg1, arg2 ) ) );
    }
};
};

#endif
