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


#ifndef __STRING_SEMI_EQUALITY_EVALUATION_H
#define __STRING_SEMI_EQUALITY_EVALUATION_H 0


#define SEMI_COMPARE_STRING( A, B ) services::lowercase( A->strEval() ).compare(  services::lowercase( B->strEval() ) ) == 0

#include "CubeBinaryEvaluation.h"
#include "CubeServices.h"
#include "CubeStringEvaluation.h"

namespace cube
{
class StringSemiEqualityEvaluation : public BinaryEvaluation
{
public:
    StringSemiEqualityEvaluation();
    StringSemiEqualityEvaluation( GeneralEvaluation*,
                                  GeneralEvaluation* );
    virtual
    ~StringSemiEqualityEvaluation();

    inline
    virtual
    double
    eval() const
    {
        StringEvaluation* _val1 = dynamic_cast<StringEvaluation*>( arguments[ 1 ] );
        StringEvaluation* _val2 = dynamic_cast<StringEvaluation*>( arguments[ 0 ] );

        if ( _val1 == NULL )
        {
            return 0.;
        }
        if ( _val2 == NULL )
        {
            return 0.;
        }


        return ( SEMI_COMPARE_STRING( _val1, _val2 ) ) ? 1. : 0.;
    }

    inline
    virtual
    double
    eval( const Cnode*,
          const CalculationFlavour,
          const Sysres*,
          const CalculationFlavour ) const
    {
        return eval();
    }
    inline
    virtual
    double
    eval( const Cnode*,
          const CalculationFlavour ) const
    {
        return eval();
    }

    inline
    virtual
    double
    eval( const list_of_cnodes&, const list_of_sysresources& ) const
    {
        return eval();
    };



    inline
    virtual
    void
    print() const
    {
        arguments[ 0 ]->print();
        std::cout << " seq ";
        arguments[ 1 ]->print();
    };

    inline
    virtual
    double
    eval( double,
          double ) const
    {
        return eval();
    }
};
};

#endif
