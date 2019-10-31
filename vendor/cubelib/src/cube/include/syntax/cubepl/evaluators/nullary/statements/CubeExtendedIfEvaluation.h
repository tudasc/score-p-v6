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


#ifndef __EXTENDED_IF_EVALUATION_H
#define __EXTENDED_IF_EVALUATION_H 0

#include <vector>
#include <stack>

#include "CubeNullaryEvaluation.h"

namespace cube
{
class ExtendedIfEvaluation : public NullaryEvaluation
{
protected:
    std::vector<std::vector<GeneralEvaluation*> > statement_blocks;
    std::vector<GeneralEvaluation*>               statement_conditions;
public:

    ExtendedIfEvaluation( std::stack<GeneralEvaluation*>              _statement_conditions,
                          std::stack<std::stack<GeneralEvaluation*> > _statement_blocks );

    virtual
    ~ExtendedIfEvaluation();


    inline
    virtual
    void
    set_verbose_execution( bool _v )
    {
        GeneralEvaluation::set_verbose_execution( _v );
        for ( std::vector<GeneralEvaluation*>::iterator iter = statement_conditions.begin(); iter != statement_conditions.end(); ++iter )
        {
            GeneralEvaluation* arg = *iter;
            arg->set_verbose_execution( _v );
        }
        for ( std::vector<std::vector<GeneralEvaluation*> >::iterator blocks_iter = statement_blocks.begin(); blocks_iter != statement_blocks.end(); ++blocks_iter )
        {
            std::vector<GeneralEvaluation*>& _arg = *blocks_iter;
            for ( std::vector<GeneralEvaluation*>::iterator iter = _arg.begin(); iter != _arg.end(); ++iter )
            {
                GeneralEvaluation* arg = *iter;
                arg->set_verbose_execution( _v );
            }
        }
    }


    inline
    virtual
    void
    setRowSize( size_t size );

    inline
    virtual
    void
    set_metric_id( uint32_t _id );


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
        std::vector<std::vector<GeneralEvaluation*> >::const_iterator blocks_iter = statement_blocks.begin();
        for ( std::vector<GeneralEvaluation*>::const_iterator iter = statement_conditions.begin(); iter != statement_conditions.end(); ++iter )
        {
            GeneralEvaluation* arg = *iter;
            if ( arg->eval( cnode, cf, sr, tf ) != 0. )
            {
                const std::vector<GeneralEvaluation*>& _arg = *blocks_iter;
                for ( std::vector<GeneralEvaluation*>::const_iterator _iter = _arg.begin(); _iter != _arg.end(); ++_iter )
                {
                    GeneralEvaluation* __arg = *_iter;
                    __arg->eval( cnode, cf, sr, tf );
                }
                return 0.;
            }
            ++blocks_iter;
        }

        // at this moment the else is executed
        if ( blocks_iter != statement_blocks.end() )
        {
            const std::vector<GeneralEvaluation*>& _arg = *blocks_iter;
            for ( std::vector<GeneralEvaluation*>::const_iterator _iter = _arg.begin(); _iter != _arg.end(); ++_iter )
            {
                GeneralEvaluation* __arg = *_iter;
                __arg->eval( cnode, cf, sr, tf );
            }
        }
        return 0.;
    };


    virtual
    double
    eval( const Cnode*             cnode,
          const CalculationFlavour cf ) const
    {
        std::vector<std::vector<GeneralEvaluation*> >::const_iterator blocks_iter = statement_blocks.begin();
        for ( std::vector<GeneralEvaluation*>::const_iterator iter = statement_conditions.begin(); iter != statement_conditions.end(); ++iter )
        {
            GeneralEvaluation* arg = *iter;
            if ( arg->eval( cnode, cf ) != 0. )
            {
                const std::vector<GeneralEvaluation*>& _arg = *blocks_iter;
                for ( std::vector<GeneralEvaluation*>::const_iterator _iter = _arg.begin(); _iter != _arg.end(); ++_iter )
                {
                    GeneralEvaluation* __arg = *_iter;
                    __arg->eval( cnode, cf );
                }
                return 0.;
            }
            ++blocks_iter;
        }
        // at this moment the else is executed
        if ( blocks_iter != statement_blocks.end() )
        {
            const std::vector<GeneralEvaluation*>& _arg = *blocks_iter;
            for ( std::vector<GeneralEvaluation*>::const_iterator _iter = _arg.begin(); _iter != _arg.end(); ++_iter )
            {
                GeneralEvaluation* __arg = *_iter;
                __arg->eval( cnode, cf );
            }
        }

        return 0.;
    };


    virtual
    double
    eval( double arg1, double arg2 ) const
    {
        std::vector<std::vector<GeneralEvaluation*> >::const_iterator blocks_iter = statement_blocks.begin();
        for ( std::vector<GeneralEvaluation*>::const_iterator iter = statement_conditions.begin(); iter != statement_conditions.end(); ++iter )
        {
            GeneralEvaluation* arg = *iter;
            if ( arg->eval(  arg1, arg2 ) != 0. )
            {
                const std::vector<GeneralEvaluation*>& _arg = *blocks_iter;
                for ( std::vector<GeneralEvaluation*>::const_iterator _iter = _arg.begin(); _iter != _arg.end(); ++_iter )
                {
                    GeneralEvaluation* __arg = *_iter;
                    __arg->eval(  arg1, arg2 );
                }
                return 0.;
            }
            ++blocks_iter;
        }
        // at this moment the else is executed
        if ( blocks_iter != statement_blocks.end() )
        {
            const std::vector<GeneralEvaluation*>& _arg = *blocks_iter;
            for ( std::vector<GeneralEvaluation*>::const_iterator _iter = _arg.begin(); _iter != _arg.end(); ++_iter )
            {
                GeneralEvaluation* __arg = *_iter;
                __arg->eval(  arg1, arg2 );
            }
        }

        return 0.;
    };

    virtual
    double*
    eval_row( Cnode*             cnode,
              CalculationFlavour cf ) const
    {
        std::vector<std::vector<GeneralEvaluation*> >::const_iterator blocks_iter = statement_blocks.begin();
        for ( std::vector<GeneralEvaluation*>::const_iterator iter = statement_conditions.begin(); iter != statement_conditions.end(); ++iter )
        {
            GeneralEvaluation* arg = *iter;
            if ( arg->eval(  cnode, cf ) != 0. )
            {
                const std::vector<GeneralEvaluation*>& _arg = *blocks_iter;
                for ( std::vector<GeneralEvaluation*>::const_iterator _iter = _arg.begin(); _iter != _arg.end(); ++_iter )
                {
                    GeneralEvaluation* __arg = *_iter;
                    delete[] ( __arg->eval_row(  cnode, cf ) );
                }
                return NULL;
            }
            ++blocks_iter;
        }
        // at this moment the else is executed
        if ( blocks_iter != statement_blocks.end() )
        {
            const std::vector<GeneralEvaluation*>& _arg = *blocks_iter;
            for ( std::vector<GeneralEvaluation*>::const_iterator _iter = _arg.begin(); _iter != _arg.end(); ++_iter )
            {
                GeneralEvaluation* __arg = *_iter;
                delete[] ( __arg->eval_row(  cnode, cf ) );
            }
        }
        return NULL;
    };



    inline
    virtual
    double
    eval( const list_of_cnodes& lc, const list_of_sysresources& ls ) const
    {
        std::vector<std::vector<GeneralEvaluation*> >::const_iterator blocks_iter = statement_blocks.begin();
        for ( std::vector<GeneralEvaluation*>::const_iterator iter = statement_conditions.begin(); iter != statement_conditions.end(); ++iter )
        {
            GeneralEvaluation* arg = *iter;
            if ( arg->eval(  lc, ls ) != 0. )
            {
                const std::vector<GeneralEvaluation*>& _arg = *blocks_iter;
                for ( std::vector<GeneralEvaluation*>::const_iterator _iter = _arg.begin(); _iter != _arg.end(); ++_iter )
                {
                    GeneralEvaluation* __arg = *_iter;
                    __arg->eval( lc, ls );
                }
                return 0.;
            }
            ++blocks_iter;
        }
        // at this moment the else is executed
        if ( blocks_iter != statement_blocks.end() )
        {
            const std::vector<GeneralEvaluation*>& _arg = *blocks_iter;
            for ( std::vector<GeneralEvaluation*>::const_iterator _iter = _arg.begin(); _iter != _arg.end(); ++_iter )
            {
                GeneralEvaluation* __arg = *_iter;
                __arg->eval( lc, ls );
            }
        }

        return 0.;
    };

    virtual
    double*
    eval_row( const list_of_cnodes& lc, const list_of_sysresources& ls ) const
    {
        std::vector<std::vector<GeneralEvaluation*> >::const_iterator blocks_iter = statement_blocks.begin();
        for ( std::vector<GeneralEvaluation*>::const_iterator iter = statement_conditions.begin(); iter != statement_conditions.end(); ++iter )
        {
            GeneralEvaluation* arg = *iter;
            if ( arg->eval( lc, ls ) != 0. )
            {
                const std::vector<GeneralEvaluation*>& _arg = *blocks_iter;
                for ( std::vector<GeneralEvaluation*>::const_iterator _iter = _arg.begin(); _iter != _arg.end(); ++_iter )
                {
                    GeneralEvaluation* __arg = *_iter;
                    delete[] ( __arg->eval_row( lc, ls ) );
                }
                return NULL;
            }
            ++blocks_iter;
        }
        // at this moment the else is executed
        if ( blocks_iter != statement_blocks.end() )
        {
            const std::vector<GeneralEvaluation*>& _arg = *blocks_iter;
            for ( std::vector<GeneralEvaluation*>::const_iterator _iter = _arg.begin(); _iter != _arg.end(); ++_iter )
            {
                GeneralEvaluation* __arg = *_iter;
                delete[] ( __arg->eval_row( lc, ls ) );
            }
        }
        return NULL;
    };




    virtual
    void
    print() const;
};
};

#endif
