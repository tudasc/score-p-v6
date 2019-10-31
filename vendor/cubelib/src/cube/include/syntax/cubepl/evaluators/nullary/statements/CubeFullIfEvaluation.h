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


#ifndef __FULL_IF_EVALUATION_H
#define __FULL_IF_EVALUATION_H 0

#include "CubeNullaryEvaluation.h"

namespace cube
{
class FullIfEvaluation : public NullaryEvaluation
{
protected:
    GeneralEvaluation* condition;
    unsigned           n_true;
    unsigned           n_false;
public:
    FullIfEvaluation( GeneralEvaluation* _condition,
                      unsigned           _n_true,
                      unsigned           _n_false ) : NullaryEvaluation(), condition( _condition ), n_true( _n_true ), n_false( _n_false )
    {
    };

    virtual
    ~FullIfEvaluation();



    inline
    virtual
    void
    setRowSize( size_t size )
    {
        row_size = size;
        condition->setRowSize( size );
        for ( std::vector<GeneralEvaluation*>::iterator iter = arguments.begin(); iter != arguments.end(); ++iter )
        {
            GeneralEvaluation* arg = *iter;
            arg->setRowSize( size );
        }
    }

    inline
    virtual
    void
    set_metric_id( uint32_t _id )
    {
        met_id = _id;
        condition->set_metric_id( _id );
        for ( std::vector<GeneralEvaluation*>::iterator iter = arguments.begin(); iter != arguments.end(); ++iter )
        {
            GeneralEvaluation* arg = *iter;
            arg->set_metric_id( _id );
        }
    }



    inline
    virtual
    void
    set_verbose_execution( bool _v )
    {
        GeneralEvaluation::set_verbose_execution( _v );
        condition->set_verbose_execution( _v );
    }

    virtual
    double
    eval() const;

    virtual
    double
    eval( const Cnode*             cnode,
          const CalculationFlavour cf,
          const Sysres*            sr,
          const CalculationFlavour tf  ) const
    {
        double _tmp = condition->eval( cnode, cf, sr, tf );
        if ( _tmp != 0 )
        {
            for ( unsigned i = 0; i < n_true; ++i )
            {
                arguments[ i ]->eval( cnode, cf, sr, tf );
            }
        }
        else
        {
            for ( unsigned i = n_true; i < n_true + n_false; ++i )
            {
                arguments[ i ]->eval( cnode, cf, sr, tf  );
            }
        }
        return 0.;
    };


    virtual
    double
    eval( const Cnode*             cnode,
          const CalculationFlavour cf ) const
    {
        double _tmp = condition->eval( cnode, cf );
        if ( _tmp != 0 )
        {
            for ( unsigned i = 0; i < n_true; ++i )
            {
                arguments[ i ]->eval( cnode, cf );
            }
        }
        else
        {
            for ( unsigned i = n_true; i < n_true + n_false; ++i )
            {
                arguments[ i ]->eval( cnode, cf );
            }
        }
        return 0.;
    };


    virtual
    double
    eval( double arg1, double arg2 ) const
    {
        double _tmp = condition->eval( arg1, arg2 );
        if ( _tmp != 0 )
        {
            for ( unsigned i = 0; i < n_true; ++i )
            {
                arguments[ i ]->eval( arg1, arg2 );
            }
        }
        else
        {
            for ( unsigned i = n_true; i < n_true + n_false; ++i )
            {
                arguments[ i ]->eval( arg1, arg2 );
            }
        }
        return 0.;
    };

    virtual
    double*
    eval_row( const Cnode*             cnode,
              const CalculationFlavour cf ) const
    {
        double _tmp = condition->eval( cnode, cf );
        if ( _tmp != 0 )
        {
            for ( unsigned i = 0; i < n_true; ++i )
            {
                delete[] arguments[ i ]->eval_row( cnode, cf );
            }
        }
        else
        {
            for ( unsigned i = n_true; i < n_true + n_false; ++i )
            {
                delete[] arguments[ i ]->eval_row( cnode, cf );
            }
        }
        return NULL;
    };


    inline
    virtual
    double
    eval( const list_of_cnodes& lc, const list_of_sysresources& ls ) const
    {
        double _tmp = condition->eval( lc, ls );
        if ( _tmp != 0 )
        {
            for ( unsigned i = 0; i < n_true; ++i )
            {
                arguments[ i ]->eval( lc, ls );
            }
        }
        else
        {
            for ( unsigned i = n_true; i < n_true + n_false; ++i )
            {
                arguments[ i ]->eval( lc, ls );
            }
        }
        return 0.;
    };

    virtual
    double*
    eval_row( const list_of_cnodes& lc, const list_of_sysresources& ls ) const
    {
        double _tmp = condition->eval( lc, ls );
        if ( _tmp != 0 )
        {
            for ( unsigned i = 0; i < n_true; ++i )
            {
                delete[] arguments[ i ]->eval_row( lc, ls );
            }
        }
        else
        {
            for ( unsigned i = n_true; i < n_true + n_false; ++i )
            {
                delete[] arguments[ i ]->eval_row( lc, ls );
            }
        }
        return NULL;
    };




    virtual
    void
    print() const
    {
        std::cout << "if (";
        condition->print();
        std::cout << ") " << std::endl << "{" << std::endl;
        for ( unsigned i = 0; i < n_true; ++i )
        {
            arguments[ i ]->print();
        }
        std::cout << "} " << std::endl << "else "  << std::endl << "{ " << std::endl;
        for ( unsigned i = n_true; i < n_true + n_false; ++i )
        {
            arguments[ i ]->print();
        }
        std::cout << "};" << std::endl;
    };
};
};

#endif
