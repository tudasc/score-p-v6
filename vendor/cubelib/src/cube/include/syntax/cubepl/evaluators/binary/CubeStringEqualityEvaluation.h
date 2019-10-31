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


#ifndef __STRING_EQUALITY_EVALUATION_H
#define __STRING_EQUALITY_EVALUATION_H 0


#define COMPARE_STRING( A, B ) A->strEval().compare( B->strEval() ) == 0


#include "CubeStringEvaluation.h"
#include "CubeBinaryEvaluation.h"

namespace cube
{
class StringEqualityEvaluation : public BinaryEvaluation
{
public:
    StringEqualityEvaluation();
    StringEqualityEvaluation( GeneralEvaluation*,
                              GeneralEvaluation* );
    virtual
    ~StringEqualityEvaluation();

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


        return ( COMPARE_STRING( _val1, _val2 ) ) ? 1. : 0.;
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
    eval( const list_of_cnodes&,
          const list_of_sysresources& ) const
    {
        return eval();
    };



    inline
    virtual
    void
    print() const
    {
        arguments[ 0 ]->print();
        std::cout << " eq ";
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
