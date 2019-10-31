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


#ifndef __WHILE_EVALUATION_H
#define __WHILE_EVALUATION_H 0

#include "CubeNullaryEvaluation.h"

namespace cube
{
class WhileEvaluation : public NullaryEvaluation
{
protected:
    GeneralEvaluation* condition;
public:
    WhileEvaluation( GeneralEvaluation* _condition ) : NullaryEvaluation(), condition( _condition )
    {
    };

    virtual
    ~WhileEvaluation();

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




    virtual
    double
    eval() const
    {
        unsigned counter = 0;
        while ( condition->eval() != 0 )
        {
            for ( unsigned i = 0; i < getNumOfParameters(); ++i )
            {
                arguments[ i ]->eval();
            }
            counter++;
            if ( counter >= 1000000000 )
            {
                break;
            }
        }
        return 0.;
    }





    inline
    virtual
    void
    set_verbose_execution( bool _v )
    {
        GeneralEvaluation::set_verbose_execution( _v );
        condition->set_verbose_execution( _v );
    }

    inline
    virtual
    double
    eval( const Cnode*             cnode,
          const CalculationFlavour cf,
          const Sysres*            sr,
          const CalculationFlavour tf  ) const
    {
        unsigned counter = 0;
        while ( condition->eval( cnode, cf, sr, tf ) != 0. )
        {
            for ( unsigned i = 0; i < getNumOfParameters(); ++i )
            {
                arguments[ i ]->eval( cnode, cf, sr, tf );
            }
            counter++;
            if ( counter >= 1000000000 )
            {
                break;
            }
        }
        return 0.;
    };

    inline
    virtual
    double
    eval( const Cnode*             cnode,
          const CalculationFlavour cf ) const
    {
        unsigned counter = 0;
        while ( condition->eval( cnode, cf ) )
        {
            for ( unsigned i = 0; i < getNumOfParameters(); ++i )
            {
                arguments[ i ]->eval( cnode, cf );
            }
            counter++;
            if ( counter >= 1000000000 )
            {
                break;
            }
        }
        return 0.;
    };

    inline
    virtual
    double*
    eval_row( const Cnode*             cnode,
              const CalculationFlavour cf ) const
    {
        unsigned counter = 0;
        while ( condition->eval( cnode, cf ) )
        {
            for ( unsigned i = 0; i < getNumOfParameters(); ++i )
            {
                delete[] arguments[ i ]->eval_row( cnode, cf );
            }
            counter++;
            if ( counter >= 1000000000 )
            {
                break;
            }
        }
        return NULL;
    }


    inline
    virtual
    double
    eval( double arg1, double arg2 ) const
    {
        unsigned counter = 0;
        while ( condition->eval( arg1, arg2 ) )
        {
            for ( unsigned i = 0; i < getNumOfParameters(); ++i )
            {
                arguments[ i ]->eval( arg1, arg2 );
            }
            counter++;
            if ( counter >= 1000000000 )
            {
                break;
            }
        }
        return 0.;
    };




    inline
    virtual
    double
    eval( const list_of_cnodes& lc, const list_of_sysresources& ls ) const
    {
        unsigned counter = 0;
        while ( condition->eval( lc, ls ) )
        {
            for ( unsigned i = 0; i < getNumOfParameters(); ++i )
            {
                arguments[ i ]->eval( lc, ls );
            }
            counter++;
            if ( counter >= 1000000000 )
            {
                break;
            }
        }
        return 0.;
    };

    virtual
    double*
    eval_row( const list_of_cnodes& lc, const list_of_sysresources& ls ) const
    {
        unsigned counter = 0;
        while ( condition->eval( lc, ls ) )
        {
            for ( unsigned i = 0; i < getNumOfParameters(); ++i )
            {
                delete[] arguments[ i ]->eval_row( lc, ls );
            }
            counter++;
            if ( counter >= 1000000000 )
            {
                break;
            }
        }
        return NULL;
    };






    inline
    virtual
    void
    print() const
    {
        std::cout << "while (";
        condition->print();
        std::cout << ") " << std::endl <<  "{" << std::endl;
        for ( unsigned i = 0; i < getNumOfParameters(); ++i )
        {
            arguments[ i ]->print();
        }
        std::cout << "};"  << std::endl;
    };
};
};

#endif
