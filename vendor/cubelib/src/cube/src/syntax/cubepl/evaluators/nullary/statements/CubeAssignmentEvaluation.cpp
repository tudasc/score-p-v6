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


#include "config.h"
#define CUBELIB_DEBUG_MODULE_NAME CUBEPL_VARIABLES
#include <UTILS_Debug.h>


#include "CubeAssignmentEvaluation.h"
#include "CubeStringEvaluation.h"

using namespace cube;
using namespace std;

#ifdef HAVE_CUBELIB_DEBUG
#include <sstream>
#endif

AssignmentEvaluation::~AssignmentEvaluation()
{
    delete value;
    delete index;
}

double
AssignmentEvaluation::eval() const
{
    double _index = index->eval();

    if ( !value->isString() )
    {
        double _value = value->eval();
#ifdef HAVE_CUBELIB_DEBUG
        if ( verbose_execution )
        {
            UTILS_DEBUG_PRINTF
            (
                ( CUBELIB_DEBUG_CUBEPL_VARIABLES | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                "name=%s,adress=%d,index=%g,metric=%d,type=%s,new value=%g",
                variable_name.c_str(),
                variable,
                _index,
                met_id,
                ( ( kind == CUBEPL_GLOBAL_VARIABLE ) ?
                  "global" :
                  ( ( kind == CUBEPL_VARIABLE ) ?
                    "local" :
                    ( ( kind == CUBEPL_RESERVED_VARIABLE ) ? "reserved" : "unknown" )
                  )
                ),
                _value
            );
        }
#endif
        memory->put( variable, _index, _value, met_id, kind );
    }
    else
    {
        string _value =  ( dynamic_cast<StringEvaluation*>( value ) )->strEval();
#ifdef HAVE_CUBELIB_DEBUG
        if ( verbose_execution )
        {
            UTILS_DEBUG_PRINTF
            (
                ( CUBELIB_DEBUG_CUBEPL_VARIABLES | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                "name=%s,adress=%d,index=%g,metric=%d,type=%s,new value=%s",
                variable_name.c_str(),
                variable,
                _index,
                met_id,
                ( ( kind == CUBEPL_GLOBAL_VARIABLE ) ?
                  "global" :
                  ( ( kind == CUBEPL_VARIABLE ) ?
                    "local" :
                    ( ( kind == CUBEPL_RESERVED_VARIABLE ) ? "reserved" : "unknown" )
                  )
                ),
                _value.c_str()
            );
        }
#endif
        memory->put( variable, _index, _value, met_id, kind );
    }
    return 0.;
}



double
AssignmentEvaluation::eval( const Cnode*             cnode,
                            const CalculationFlavour cf,
                            const Sysres*            sr,
                            const CalculationFlavour tf  ) const
{
    double _index = index->eval( cnode, cf, sr, tf  );

    if (  !value->isString() )
    {
        double _value = value->eval( cnode, cf, sr, tf );
        #ifdef HAVE_CUBELIB_DEBUG
        if ( verbose_execution )
        {
            UTILS_DEBUG_PRINTF
            (
                ( CUBELIB_DEBUG_CUBEPL_VARIABLES | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                "name=%s,adress=%d,index=%g,metric=%d,type=%s,new value=%g",
                variable_name.c_str(),
                variable,
                _index,
                met_id,
                ( ( kind == CUBEPL_GLOBAL_VARIABLE ) ?
                  "global" :
                  ( ( kind == CUBEPL_VARIABLE ) ?
                    "local" :
                    ( ( kind == CUBEPL_RESERVED_VARIABLE ) ? "reserved" : "unknown" )
                  )
                ),
                _value
            );
        }
#endif
        memory->put( variable, _index, _value, met_id, kind  );
    }
    else
    {
        string _value =  ( dynamic_cast<StringEvaluation*>( value ) )->strEval();
#ifdef HAVE_CUBELIB_DEBUG
        if ( verbose_execution )
        {
            UTILS_DEBUG_PRINTF
            (
                ( CUBELIB_DEBUG_CUBEPL_VARIABLES | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                "name=%s,adress=%d,index=%g,metric=%d,type=%s,new value=%s",
                variable_name.c_str(),
                variable,
                _index,
                met_id,
                ( ( kind == CUBEPL_GLOBAL_VARIABLE ) ?
                  "global" :
                  ( ( kind == CUBEPL_VARIABLE ) ?
                    "local" :
                    ( ( kind == CUBEPL_RESERVED_VARIABLE ) ? "reserved" : "unknown" )
                  )
                ),
                _value.c_str()
            );
        }
#endif
        memory->put( variable, _index, _value, met_id, kind  );
    }
    return 0.;
};



double
AssignmentEvaluation::eval( const Cnode*             cnode,
                            const CalculationFlavour cf ) const
{
    double _index = index->eval( cnode, cf  );

    if (  !value->isString() )
    {
        double _value = value->eval( cnode, cf );
        #ifdef HAVE_CUBELIB_DEBUG
        if ( verbose_execution )
        {
            UTILS_DEBUG_PRINTF
            (
                ( CUBELIB_DEBUG_CUBEPL_VARIABLES | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                "name=%s,adress=%d,index=%g,metric=%d,type=%s,new value=%g",
                variable_name.c_str(),
                variable,
                _index,
                met_id,
                ( ( kind == CUBEPL_GLOBAL_VARIABLE ) ?
                  "global" :
                  ( ( kind == CUBEPL_VARIABLE ) ?
                    "local" :
                    ( ( kind == CUBEPL_RESERVED_VARIABLE ) ? "reserved" : "unknown" )
                  )
                ),
                _value
            );
        }
#endif
        memory->put( variable, _index, _value, met_id, kind  );
    }
    else
    {
        string _value =  ( dynamic_cast<StringEvaluation*>( value ) )->strEval();
#ifdef HAVE_CUBELIB_DEBUG
        if ( verbose_execution )
        {
            UTILS_DEBUG_PRINTF
            (
                ( CUBELIB_DEBUG_CUBEPL_VARIABLES | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                "name=%s,adress=%d,index=%g,metric=%d,type=%s,new value=%s",
                variable_name.c_str(),
                variable,
                _index,
                met_id,
                ( ( kind == CUBEPL_GLOBAL_VARIABLE ) ?
                  "global" :
                  ( ( kind == CUBEPL_VARIABLE ) ?
                    "local" :
                    ( ( kind == CUBEPL_RESERVED_VARIABLE ) ? "reserved" : "unknown" )
                  )
                ),
                _value.c_str()
            );
        }
#endif
        memory->put( variable, _index, _value, met_id, kind  );
    }
    return 0.;
};


double
AssignmentEvaluation::eval( double arg1, double arg2 ) const
{
    double _index = index->eval( arg1, arg2  );
    if (  !value->isString() )
    {
        double _value = value->eval( arg1, arg2 );
#ifdef HAVE_CUBELIB_DEBUG
        if ( verbose_execution )
        {
            UTILS_DEBUG_PRINTF
            (
                ( CUBELIB_DEBUG_CUBEPL_VARIABLES | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                "name=%s,adress=%d,index=%g,metric=%d,type=%s,new value=%g",
                variable_name.c_str(),
                variable,
                _index,
                met_id,
                ( ( kind == CUBEPL_GLOBAL_VARIABLE ) ?
                  "global" :
                  ( ( kind == CUBEPL_VARIABLE ) ?
                    "local" :
                    ( ( kind == CUBEPL_RESERVED_VARIABLE ) ? "reserved" : "unknown" )
                  )
                ),
                _value
            );
        }
#endif
        memory->put( variable, _index, _value, met_id, kind  );
    }
    else
    {
        string _value =  ( dynamic_cast<StringEvaluation*>( value ) )->strEval();
#ifdef HAVE_CUBELIB_DEBUG
        if ( verbose_execution )
        {
            UTILS_DEBUG_PRINTF
            (
                ( CUBELIB_DEBUG_CUBEPL_VARIABLES | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                "name=%s,adress=%d,index=%g,metric=%d,type=%s,new value=%s",
                variable_name.c_str(),
                variable,
                _index,
                met_id,
                ( ( kind == CUBEPL_GLOBAL_VARIABLE ) ?
                  "global" :
                  ( ( kind == CUBEPL_VARIABLE ) ?
                    "local" :
                    ( ( kind == CUBEPL_RESERVED_VARIABLE ) ? "reserved" : "unknown" )
                  )
                ),
                _value.c_str()
            );
        }
#endif
        memory->put( variable, _index, _value, met_id, kind  );
    }
    return 0.;
};



double*
AssignmentEvaluation::eval_row( const Cnode*             cnode,
                                const CalculationFlavour cf ) const
{
    double _index = index->eval( cnode, cf );
    if (  !value->isString() )
    {
        double* _tmp = value->eval_row( cnode, cf );
#ifdef HAVE_CUBELIB_DEBUG
        if ( verbose_execution )
        {
            stringstream str;
            for ( size_t i = 0; i < row_size; ++i )
            {
                str << _tmp[ i ];
                if ( i != row_size - 1 )
                {
                    str << ",";
                }
            }
            std::string _str;
            str >> _str;
            UTILS_DEBUG_PRINTF
            (
                ( CUBELIB_DEBUG_CUBEPL_VARIABLES | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                "name=%s,adress=%d,index=%g,metric=%d,type=%s,value=%s",
                variable_name.c_str(),
                variable,
                _index,
                met_id,
                ( ( kind == CUBEPL_GLOBAL_VARIABLE ) ?
                  "global" :
                  ( ( kind == CUBEPL_VARIABLE ) ?
                    "local" :
                    ( ( kind == CUBEPL_RESERVED_VARIABLE ) ? "reserved" : "unknown" )
                  )
                ),
                _str.c_str()
            );
        }
#endif

        memory->put( variable, _index, _tmp, met_id, kind  );
    }
    return NULL;
}




double
AssignmentEvaluation::eval( const list_of_cnodes& lc, const list_of_sysresources& ls ) const
{
    double _index = index->eval( lc, ls  );
    if (  !value->isString() )
    {
        double _value = value->eval( lc, ls );
#ifdef HAVE_CUBELIB_DEBUG
        if ( verbose_execution )
        {
            UTILS_DEBUG_PRINTF
            (
                ( CUBELIB_DEBUG_CUBEPL_VARIABLES | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                "name=%s,adress=%d,index=%g,metric=%d,type=%s,new value=%g",
                variable_name.c_str(),
                variable,
                _index,
                met_id,
                ( ( kind == CUBEPL_GLOBAL_VARIABLE ) ?
                  "global" :
                  ( ( kind == CUBEPL_VARIABLE ) ?
                    "local" :
                    ( ( kind == CUBEPL_RESERVED_VARIABLE ) ? "reserved" : "unknown" )
                  )
                ),
                _value
            );
        }
#endif
        memory->put( variable, _index, _value, met_id, kind  );
    }
    else
    {
        string _value =  ( dynamic_cast<StringEvaluation*>( value ) )->strEval();
#ifdef HAVE_CUBELIB_DEBUG
        if ( verbose_execution )
        {
            UTILS_DEBUG_PRINTF
            (
                ( CUBELIB_DEBUG_CUBEPL_VARIABLES | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                "name=%s,adress=%d,index=%g,metric=%d,type=%s,new value=%s",
                variable_name.c_str(),
                variable,
                _index,
                met_id,
                ( ( kind == CUBEPL_GLOBAL_VARIABLE ) ?
                  "global" :
                  ( ( kind == CUBEPL_VARIABLE ) ?
                    "local" :
                    ( ( kind == CUBEPL_RESERVED_VARIABLE ) ? "reserved" : "unknown" )
                  )
                ),
                _value.c_str()
            );
        }
#endif
        memory->put( variable, _index, _value, met_id, kind  );
    }
    return 0.;
};



double*
AssignmentEvaluation::eval_row( const list_of_cnodes& lc, const list_of_sysresources& ls ) const
{
    double _index = index->eval(  lc, ls  );
    if (  !value->isString() )
    {
        double* _tmp = value->eval_row(  lc, ls  );
#ifdef HAVE_CUBELIB_DEBUG
        if ( verbose_execution )
        {
            stringstream str;
            for ( size_t i = 0; i < row_size; ++i )
            {
                str << _tmp[ i ];
                if ( i != row_size - 1 )
                {
                    str << ",";
                }
            }
            std::string _str;
            str >> _str;
            UTILS_DEBUG_PRINTF
            (
                ( CUBELIB_DEBUG_CUBEPL_VARIABLES | CUBELIB_DEBUG_CUBEPL_EXECUTION ),
                "name=%s,adress=%d,index=%g,metric=%d,type=%s,value=%s",
                variable_name.c_str(),
                variable,
                _index,
                met_id,
                ( ( kind == CUBEPL_GLOBAL_VARIABLE ) ?
                  "global" :
                  ( ( kind == CUBEPL_VARIABLE ) ?
                    "local" :
                    ( ( kind == CUBEPL_RESERVED_VARIABLE ) ? "reserved" : "unknown" )
                  )
                ),
                _str.c_str()
            );
        }
#endif

        memory->put( variable, _index, _tmp, met_id, kind  );
    }
    return NULL;
}
