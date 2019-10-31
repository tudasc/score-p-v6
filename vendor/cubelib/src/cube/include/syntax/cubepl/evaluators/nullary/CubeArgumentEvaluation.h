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


#ifndef __ARGUMENT_EVALUATION_H
#define __ARGUMENT_EVALUATION_H 0

#include "CubeNullaryEvaluation.h"

namespace cube
{
// / Used to specify, if an inclusive or an exclusive value is being calculated
enum NumberOfArgument { FIRST_ARGUMENT = 0, SECOND_ARGUMENT = 1 };

class ArgumentEvaluation : public NullaryEvaluation
{
protected:
    NumberOfArgument number_of_argument;

public:
    ArgumentEvaluation( NumberOfArgument  );

    virtual
    ~ArgumentEvaluation();

    inline
    virtual
    double
    eval() const
    {
        return 0.;
    }


    virtual
    double
    eval( double arg1,
          double arg2 ) const
    {
        if ( number_of_argument == cube::FIRST_ARGUMENT )
        {
            return arg1;
        }
        return arg2;
    }


    virtual
    double
    eval( const Cnode*  _cnode,
          const CalculationFlavour,
          const Sysres* _sys,
          const CalculationFlavour ) const
    {
        if ( number_of_argument == cube::FIRST_ARGUMENT )
        {
            return ( double )( _cnode->get_id() );
        }
        return ( double )( _sys->get_id() );
    }

    inline
    virtual
    double
    eval( const Cnode* _cnode,
          const CalculationFlavour ) const
    {
        if ( number_of_argument == cube::FIRST_ARGUMENT )
        {
            return ( double )( _cnode->get_id() );
        }
        return 0.;
    };

    inline
    virtual
    double*
    eval_row( const Cnode* _cnode,
              const CalculationFlavour ) const
    {
        double* result = services::create_row_of_doubles( row_size );
        for ( size_t i = 0; i < row_size; i++ )
        {
            result[ i ] = ( number_of_argument == cube::FIRST_ARGUMENT ) ? ( double )_cnode->get_id() : ( double )i;
        }
        return result;
    }


    inline
    virtual
    double
    eval( const list_of_cnodes& lc, const list_of_sysresources& ls ) const
    {
        if ( number_of_argument == cube::FIRST_ARGUMENT )
        {
            return ( lc.size() > 0 ) ? ( double )( lc.begin()->first->get_id() ) : 0.;
        }
        return ( ls.size() > 0 ) ? ( double )( ls.begin()->first->get_id() ) : 0.;
    };

    virtual
    double*
    eval_row( const list_of_cnodes& lc, const list_of_sysresources& ) const
    {
        double* result = services::create_row_of_doubles( row_size );
        if ( lc.size() > 0 )
        {
            for ( size_t i = 0; i < row_size; i++ )
            {
                result[ i ] = ( number_of_argument == cube::FIRST_ARGUMENT ) ? ( double )( lc.begin()->first->get_id() ) : ( double )i;
            }
        }
        return result;
    };






    inline
    virtual
    void
    print() const
    {
        if ( number_of_argument == cube::FIRST_ARGUMENT )
        {
            std::cout << "arg1";
        }
        else
        {
            std::cout << "arg2";
        }
    };
};
};

#endif
