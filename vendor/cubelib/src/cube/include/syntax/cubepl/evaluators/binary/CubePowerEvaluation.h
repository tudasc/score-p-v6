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


#ifndef __POWER_EVALUATION_H
#define __POWER_EVALUATION_H 0

#include "CubeBinaryEvaluation.h"

namespace cube
{
class PowerEvaluation : public BinaryEvaluation
{
public:
    PowerEvaluation();
    PowerEvaluation( GeneralEvaluation*,
                     GeneralEvaluation* );
    virtual
    ~PowerEvaluation();

    inline
    virtual
    double
    eval() const
    {
        double base  = arguments[ 0 ]->eval();
        double power = arguments[ 1 ]->eval();
        return pow( base, power );
    }

    inline
    virtual
    double
    eval( const Cnode*             _cnode,
          const CalculationFlavour _cf,
          const Sysres*            _sf,
          const CalculationFlavour _tf  ) const
    {
        double base = arguments[ 0 ]->eval(       _cnode, _cf,
                                                  _sf, _tf );
        double power = arguments[ 1 ]->eval(      _cnode, _cf,
                                                  _sf, _tf );
        return pow( base, power );
    }


    inline
    virtual
    double
    eval( const Cnode*             _cnode,
          const CalculationFlavour _cf ) const
    {
        double base  = arguments[ 0 ]->eval(       _cnode, _cf );
        double power = arguments[ 1 ]->eval(      _cnode, _cf );
        return pow( base, power );
    }

    inline
    virtual
    double*
    eval_row( const Cnode*             _cnode,
              const CalculationFlavour _cf ) const
    {
        double* result = arguments[ 0 ]->eval_row( _cnode, _cf );
        if ( result == NULL )
        {
            return NULL;
        }
        double* _result = arguments[ 1 ]->eval_row( _cnode, _cf );
        if ( _result == NULL )
        {
            for ( size_t i = 0; i < row_size; i++ )
            {
                result[ i ] =  ( result[ i ] != 0. ) ? 1. : 0.;
            }
        }
        else
        {
            for ( size_t i = 0; i < row_size; i++ )
            {
                result[ i ] =  pow( result[ i ], _result[ i ] );
            }
            delete _result;
        }
        return result;
    }


    inline
    virtual
    double
    eval( const list_of_cnodes& lc, const list_of_sysresources& ls ) const
    {
        double base  = arguments[ 0 ]->eval( lc, ls );
        double power = arguments[ 1 ]->eval(  lc, ls );
        return pow( base, power );
    };

    virtual
    double*
    eval_row( const list_of_cnodes& lc, const list_of_sysresources& ls ) const
    {
        double* result = arguments[ 0 ]->eval_row( lc, ls );
        if ( result == NULL )
        {
            return NULL;
        }
        double* _result = arguments[ 1 ]->eval_row( lc, ls );
        if ( _result == NULL )
        {
            for ( size_t i = 0; i < row_size; i++ )
            {
                result[ i ] =  ( result[ i ] != 0. ) ? 1. : 0.;
            }
        }
        else
        {
            for ( size_t i = 0; i < row_size; i++ )
            {
                result[ i ] =  pow( result[ i ], _result[ i ] );
            }
            delete _result;
        }
        return result;
    }




    inline
    virtual
    void
    print() const
    {
        arguments[ 0 ]->print();
        std::cout << "^";
        arguments[ 1 ]->print();
    };


    inline
    virtual
    double
    eval( double arg1,
          double arg2 ) const
    {
        double base  = arguments[ 0 ]->eval( arg1, arg2 );
        double power = arguments[ 1 ]->eval( arg1, arg2 );
        return pow( base, power );
    }
};
};

#endif
