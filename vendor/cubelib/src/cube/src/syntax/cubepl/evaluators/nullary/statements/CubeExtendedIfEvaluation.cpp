/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2016                                                **
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



#include "config.h"


#include "CubeExtendedIfEvaluation.h"

using namespace cube;
using namespace std;

ExtendedIfEvaluation::ExtendedIfEvaluation(   stack<GeneralEvaluation*>         _statement_conditions,
                                              stack<stack<GeneralEvaluation*> > _statement_blocks
                                              ) : NullaryEvaluation()
{
    while ( !_statement_conditions.empty() )
    {
        GeneralEvaluation* _cond = _statement_conditions.top();
        _statement_conditions.pop();

        stack<GeneralEvaluation*> _stats = _statement_blocks.top();
        _statement_blocks.pop();
        vector<GeneralEvaluation*> _new_stats;

        statement_conditions.push_back( _cond );
        while ( !_stats.empty() )
        {
            GeneralEvaluation* _statement = _stats.top();
            _stats.pop();
            _new_stats.push_back( _statement );
        }
        statement_blocks.push_back( _new_stats );
    }

    // this ist else block
    if ( !_statement_blocks.empty() )
    {
        stack<GeneralEvaluation*> _stats = _statement_blocks.top();
        _statement_blocks.pop();
        vector<GeneralEvaluation*> _new_stats;
        while ( !_stats.empty() )
        {
            GeneralEvaluation* _statement = _stats.top();
            _stats.pop();
            _new_stats.push_back( _statement );
        }
        statement_blocks.push_back( _new_stats );
    }
};



ExtendedIfEvaluation::~ExtendedIfEvaluation()
{
    for ( std::vector<GeneralEvaluation*>::iterator iter = statement_conditions.begin(); iter != statement_conditions.end(); ++iter )
    {
        delete *iter;
    }
    for ( std::vector<vector<GeneralEvaluation*> >::iterator iter = statement_blocks.begin(); iter != statement_blocks.end(); ++iter )
    {
        vector<GeneralEvaluation*>& arg = *iter;
        for ( std::vector<GeneralEvaluation*>::iterator _iter = arg.begin(); _iter != arg.end(); ++_iter )
        {
            GeneralEvaluation* _arg = *_iter;
            delete _arg;
        }
        arg.clear();
    }
    statement_conditions.clear();
    statement_blocks.clear();
}



void
ExtendedIfEvaluation::setRowSize( size_t size )
{
    row_size = size;
    for ( std::vector<GeneralEvaluation*>::const_iterator iter = statement_conditions.begin(); iter != statement_conditions.end(); ++iter )
    {
        GeneralEvaluation* arg = *iter;
        arg->setRowSize( size );
    }
    for ( std::vector<vector<GeneralEvaluation*> >::const_iterator iter = statement_blocks.begin(); iter != statement_blocks.end(); ++iter )
    {
        const vector<GeneralEvaluation*>& arg = *iter;
        for ( std::vector<GeneralEvaluation*>::const_iterator _iter = arg.begin(); _iter != arg.end(); ++_iter )
        {
            GeneralEvaluation* _arg = *_iter;
            _arg->setRowSize( size );
        }
    }
}




void
ExtendedIfEvaluation::set_metric_id( uint32_t _id )
{
    met_id = _id;
    for ( std::vector<GeneralEvaluation*>::const_iterator iter = statement_conditions.begin(); iter != statement_conditions.end(); ++iter )
    {
        GeneralEvaluation* arg = *iter;
        arg->set_metric_id( _id );
    }
    for ( std::vector<vector<GeneralEvaluation*> >::const_iterator iter = statement_blocks.begin(); iter != statement_blocks.end(); ++iter )
    {
        const vector<GeneralEvaluation*>& arg = *iter;
        for ( std::vector<GeneralEvaluation*>::const_iterator _iter = arg.begin(); _iter != arg.end(); ++_iter )
        {
            GeneralEvaluation* _arg = *_iter;
            _arg->set_metric_id( _id );
        }
    }
}


double
ExtendedIfEvaluation::eval() const
{
    std::vector<vector<GeneralEvaluation*> >::const_iterator blocks_iter = statement_blocks.begin();
    for ( std::vector<GeneralEvaluation*>::const_iterator iter = statement_conditions.begin(); iter != statement_conditions.end(); ++iter )
    {
        GeneralEvaluation* arg = *iter;
        if ( arg->eval() != 0. )
        {
            const vector<GeneralEvaluation*>& _arg = *blocks_iter;
            for ( std::vector<GeneralEvaluation*>::const_iterator _iter = _arg.begin(); _iter != _arg.end(); ++_iter )
            {
                GeneralEvaluation* __arg = *_iter;
                __arg->eval();
            }
            return 0.;
        }
        ++blocks_iter;
    }
    // at this moment the else is executed
    if ( blocks_iter != statement_blocks.end() )
    {
        const vector<GeneralEvaluation*>& _arg = *blocks_iter;
        for ( std::vector<GeneralEvaluation*>::const_iterator _iter = _arg.begin(); _iter != _arg.end(); ++_iter )
        {
            GeneralEvaluation* __arg = *_iter;
            __arg->eval();
        }
    }
    return 0.;
}


void
ExtendedIfEvaluation::print() const
{
    std::vector<vector<GeneralEvaluation*> >::const_iterator blocks_iter = statement_blocks.begin();

    std::cout << "if (";
    for ( std::vector<GeneralEvaluation*>::const_iterator iter = statement_conditions.begin(); iter != statement_conditions.end(); ++iter )
    {
        if ( iter != statement_conditions.begin() )
        {
            std::cout << "elseif (";
        }
        GeneralEvaluation* cond = *iter;
        cond->print();
        std::cout << ") " << std::endl << "{" << std::endl;

        const vector<GeneralEvaluation*>& _arg = *blocks_iter;
        for ( std::vector<GeneralEvaluation*>::const_iterator _iter = _arg.begin(); _iter != _arg.end(); ++_iter )
        {
            GeneralEvaluation* __arg = *_iter;
            __arg->print();
        }
        ++blocks_iter;
        std::cout << "} " << std::endl;
    }
    // at this moment the else is executed
    if ( blocks_iter != statement_blocks.end() )
    {
        std::cout << "else {";
        const vector<GeneralEvaluation*>& _arg = *blocks_iter;
        for ( std::vector<GeneralEvaluation*>::const_iterator _iter = _arg.begin(); _iter != _arg.end(); ++_iter )
        {
            GeneralEvaluation* __arg = *_iter;
            __arg->print();
        }
        std::cout << "} " << std::endl;
    }
};
