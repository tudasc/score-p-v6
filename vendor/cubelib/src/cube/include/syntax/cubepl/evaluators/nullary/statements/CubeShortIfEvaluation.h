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


#ifndef __SHORT_IF_EVALUATION_H
#define __SHORT_IF_EVALUATION_H 0


#include "CubeNullaryEvaluation.h"
#include "CubeServices.h"


namespace cube
{
class ShortIfEvaluation : public NullaryEvaluation
{
protected:
    GeneralEvaluation* condition;
public:
    ShortIfEvaluation( GeneralEvaluation* _condition ) : NullaryEvaluation(), condition( _condition )
    {
    };

    virtual
    ~ShortIfEvaluation();


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
    eval() const
    {
        double _tmp = condition->eval();
        if ( _tmp != 0 )
        {
            for ( unsigned i = 0; i < getNumOfParameters(); ++i )
            {
                arguments[ i ]->eval();
            }
        }
        return 0.;
    }




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
            for ( unsigned i = 0; i < getNumOfParameters(); ++i )
            {
                arguments[ i ]->eval( cnode, cf, sr, tf );
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
            for ( unsigned i = 0; i < getNumOfParameters(); ++i )
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
            for ( unsigned i = 0; i < getNumOfParameters(); ++i )
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
            for ( unsigned i = 0; i < getNumOfParameters(); ++i )
            {
                services::delete_raw_row( ( arguments[ i ]->eval_row( cnode, cf ) ) );
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
            for ( unsigned i = 0; i < getNumOfParameters(); ++i )
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
            for ( unsigned i = 0; i < getNumOfParameters(); ++i )
            {
                services::delete_raw_row( ( arguments[ i ]->eval_row( lc, ls ) ) );
            }
        }
        return NULL;
    };





    inline
    virtual
    void
    print() const
    {
        std::cout << "if (";
        condition->print();
        std::cout << ") " << std::endl << "{" << std::endl;
        for ( unsigned i = 0; i < getNumOfParameters(); ++i )
        {
            arguments[ i ]->print();
        }
        std::cout << "}; "  << std::endl;
    };
};
};

#endif
