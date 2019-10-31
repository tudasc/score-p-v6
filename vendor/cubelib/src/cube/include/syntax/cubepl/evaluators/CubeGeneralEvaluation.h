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


#ifndef __GENERAL_EVALUATION_H
#define __GENERAL_EVALUATION_H 0

#include <string>
#include <vector>
#include <iostream>
#include <float.h>
#include <cmath>
#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeMetric.h"
#include "CubeThread.h"
#include "CubeSysres.h"
#include "CubeProcess.h"
#include "CubeNode.h"
#include "CubeMachine.h"
#include "CubeTypes.h"
#include "CubePL1MemoryManager.h"


namespace cube
{
class GeneralEvaluation
{
protected:
    uint32_t                         met_id;
    size_t                           row_size;
    std::vector<GeneralEvaluation* > arguments;

    bool is_string;
    bool verbose_execution;
protected:


    size_t
    getNumOfParameters() const;

    virtual size_t
    getNumOfArguments() const;

public:
    GeneralEvaluation();

    virtual
    ~GeneralEvaluation();


    inline
    virtual
    bool
    isString() const
    {
        return is_string;
    };

    inline
    virtual
    void
    setRowSize( size_t size )
    {
        row_size = size;
        for ( std::vector<GeneralEvaluation*>::iterator iter = arguments.begin(); iter != arguments.end(); ++iter )
        {
            GeneralEvaluation* arg = *iter;
            arg->setRowSize( size );
        }
    };


    inline
    virtual
    void
    set_metric_id( uint32_t _id )
    {
        met_id = _id;
        for ( std::vector<GeneralEvaluation*>::iterator iter = arguments.begin(); iter != arguments.end(); ++iter )
        {
            GeneralEvaluation* arg = *iter;
            arg->set_metric_id( _id );
        }
    }

    inline
    uint32_t
    get_metric_id() const
    {
        return met_id;
    }


    void
    addArgument( GeneralEvaluation* _arg );

    inline
    virtual
    double
    eval( const Cnode*             _cnode,
          const CalculationFlavour _cf,
          const Sysres*            _sys,
          const CalculationFlavour _sf  ) const
    {
        ( void )_cnode;
        ( void )_cf;
        ( void )_sys;
        ( void )_sf;
        return eval();
    };


    inline
    virtual
    double
    eval( const Cnode*             _cnode,
          const CalculationFlavour _cf ) const
    {
        ( void )_cnode;
        ( void )_cf;
        return eval();
    };


    inline
    virtual
    double*
    eval_row( const Cnode*             _cnode,
              const CalculationFlavour _cf ) const
    {
        ( void )_cnode;
        ( void )_cf;
        return NULL;
    };

    virtual
    double
    eval( double arg1, double arg2 ) const
    {
        return 0. * ( arg1 + arg2 );
    };

    virtual
    double
    eval( const list_of_cnodes& lc, const list_of_sysresources& ls ) const
    {
        ( void )lc;
        ( void )ls;
        return 0.;
    };

    virtual
    double*
    eval_row( const list_of_cnodes& lc, const list_of_sysresources& ls ) const
    {
        ( void )lc;
        ( void )ls;
        return NULL;
    };


    inline
    virtual
    void
    set_verbose_execution( bool _v )
    {
        verbose_execution = _v;
        for ( std::vector<GeneralEvaluation*>::iterator iter = arguments.begin(); iter != arguments.end(); ++iter )
        {
            GeneralEvaluation* arg = *iter;
            arg->set_verbose_execution( _v );
        }
    }


    virtual
    double
    eval() const
    {
        return 0;
    }

    virtual
    void
    print() const
    {
    };
};
}

#endif
