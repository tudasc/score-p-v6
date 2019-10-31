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


#ifndef __MULT_EVALUATION_H
#define __MULT_EVALUATION_H 0

#include "CubeBinaryEvaluation.h"

namespace cube
{
class MultEvaluation : public BinaryEvaluation
{
public:
    MultEvaluation();
    MultEvaluation( GeneralEvaluation*,
                    GeneralEvaluation* );
    virtual
    ~MultEvaluation();

    inline
    virtual
    double
    eval() const
    {
        double _first = ( arguments[ 1 ]->eval() );
        if ( _first == 0. )
        {
            return 0.;
        }
        double _second = ( arguments[ 0 ]->eval() );
        double _value  =  _first * _second;
        if ( fabs( _value ) == std::numeric_limits<double>::infinity() )
        {
            if ( _value < 0 )
            {
                return -DBL_MAX;
            }
            else
            {
                return DBL_MAX;
            }
        }
        else
        {
            return _value;
        }
    }


    inline
    virtual
    double
    eval( const Cnode*             _cnode,
          const CalculationFlavour _cf,
          const Sysres*            _sf,
          const CalculationFlavour _tf  ) const
    {
        double _first = ( arguments[ 1 ]->eval( _cnode, _cf,
                                                _sf, _tf ) );
        if ( _first == 0. )
        {
            return 0.;
        }
        double _second = ( arguments[ 0 ]->eval( _cnode, _cf, _sf, _tf ) );

        double _value =  _first * _second;
        if ( fabs( _value ) == std::numeric_limits<double>::infinity() )
        {
            if ( _value < 0 )
            {
                return -DBL_MAX;
            }
            else
            {
                return DBL_MAX;
            }
        }
        else
        {
            return _value;
        }
    }

    inline
    virtual
    double
    eval( const Cnode*             _cnode,
          const CalculationFlavour _cf ) const
    {
        double _first = ( arguments[ 1 ]->eval( _cnode, _cf ) );
        if ( _first == 0. )
        {
            return 0.;
        }
        double _second = ( arguments[ 0 ]->eval( _cnode, _cf ) );

        double _value =  _first * _second;
        if ( fabs( _value ) == std::numeric_limits<double>::infinity() )
        {
            if ( _value < 0 )
            {
                return -DBL_MAX;
            }
            else
            {
                return DBL_MAX;
            }
        }
        else
        {
            return _value;
        }
    }

    inline
    virtual
    double*
    eval_row( const Cnode*             _cnode,
              const CalculationFlavour _cf ) const
    {
        // cube pl expression A*B is compiled into B->arg0, A->arg2. therefore we evaluate first arg2 (A)
        double* arg2 = arguments[ 1 ]->eval_row( _cnode, _cf );
        if ( arg2 == NULL  )
        {
            delete[] arg2;
            return NULL;
        }
        double* result = arg2;
        bool    zero   = true;
        for ( size_t i = 0; i < row_size; i++ )
        {
            zero &= ( arg2[ i ] == 0. );
            if ( !zero )
            {
                break;
            }
        }
        if ( zero )
        {
            delete[] arg2;
            return NULL;
        }
        // then arg1 (B)
        double* arg1 = arguments[ 0 ]->eval_row( _cnode, _cf );
        if ( arg1 != NULL )
        {
            for ( size_t i = 0; i < row_size; i++ )
            {
                result[ i ] *= ( arg1[ i ] );
                if ( fabs( result[ i ]  ) == std::numeric_limits<double>::infinity() )
                {
                    if ( result[ i ]  < 0 )
                    {
                        result[ i ] = -DBL_MAX;
                    }
                    else
                    {
                        result[ i ] = DBL_MAX;
                    }
                }
            }
            delete[] arg1;
        }
        return result;
    }


    inline
    virtual
    double
    eval( const list_of_cnodes& lc, const list_of_sysresources& ls ) const
    {
        double _first = ( arguments[ 1 ]->eval( lc, ls ) );
        if ( _first == 0. )
        {
            return 0.;
        }
        double _second = ( arguments[ 0 ]->eval( lc, ls ) );

        double _value =  _first * _second;
        if ( fabs( _value ) == std::numeric_limits<double>::infinity() )
        {
            if ( _value < 0 )
            {
                return -DBL_MAX;
            }
            else
            {
                return DBL_MAX;
            }
        }
        else
        {
            return _value;
        }
    };

    virtual
    double*
    eval_row( const list_of_cnodes& lc, const list_of_sysresources& ls ) const
    {
        // cube pl expression A*B is compiled into B->arg0, A->arg2. therefore we evaluate first arg2 (A)
        double* arg2 = arguments[ 1 ]->eval_row( lc, ls );
        if ( arg2 == NULL  )
        {
            delete[] arg2;
            return NULL;
        }
        double* result = arg2;
        bool    zero   = true;
        for ( size_t i = 0; i < row_size; i++ )
        {
            zero &= ( arg2[ i ] == 0. );
            if ( !zero )
            {
                break;
            }
        }
        if ( zero )
        {
            delete[] arg2;
            return NULL;
        }
        // then arg1 (B)
        double* arg1 = arguments[ 0 ]->eval_row( lc, ls );
        if ( arg1 != NULL )
        {
            for ( size_t i = 0; i < row_size; i++ )
            {
                result[ i ] *= ( arg1[ i ] );
                if ( fabs( result[ i ]  ) == std::numeric_limits<double>::infinity() )
                {
                    if ( result[ i ]  < 0 )
                    {
                        result[ i ] = -DBL_MAX;
                    }
                    else
                    {
                        result[ i ] = DBL_MAX;
                    }
                }
            }
            delete[] arg1;
        }
        return result;
    };







    inline
    virtual
    void
    print() const
    {
        std::cout << "(";
        arguments[ 0 ]->print();
        std::cout << "*";
        arguments[ 1 ]->print();
        std::cout << ")";
    };

    inline
    virtual
    double
    eval( double arg1,
          double arg2 ) const
    {
        double _first = ( arguments[ 1 ]->eval( arg1, arg2  ) );
        if ( _first == 0. )
        {
            return 0.;
        }
        double _second = ( arguments[ 0 ]->eval( arg1, arg2  ) );

        double _value =  _first * _second;
        if ( fabs( _value ) == std::numeric_limits<double>::infinity() )
        {
            if ( _value < 0 )
            {
                return -DBL_MAX;
            }
            else
            {
                return DBL_MAX;
            }
        }
        else
        {
            return _value;
        }
    }
};
};

#endif
