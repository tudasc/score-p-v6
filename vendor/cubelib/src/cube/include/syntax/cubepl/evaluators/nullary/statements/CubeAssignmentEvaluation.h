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


#ifndef __ASSIGNMENT_EVALUATION_H
#define __ASSIGNMENT_EVALUATION_H 0

#include "CubeNullaryEvaluation.h"
#include "CubePLMemoryManager.h"

namespace cube
{
class AssignmentEvaluation : public NullaryEvaluation
{
protected:

    CubePLMemoryManager* memory;
    std::string          variable_name;
    MemoryAdress         variable;
    KindOfVariable       kind;
    GeneralEvaluation*   value;
    GeneralEvaluation*   index;


public:
    AssignmentEvaluation( std::string          _v,
                          GeneralEvaluation*   _index,
                          GeneralEvaluation*   _val,
                          CubePLMemoryManager* _manager
                          ) : NullaryEvaluation(), memory( _manager ), variable_name( _v ), variable( memory->register_variable( _v ) ), value( _val ), index( _index )
    {
        kind = memory->kind_of_variable( variable_name );
    };

    virtual
    ~AssignmentEvaluation();

    inline
    virtual
    void
    setRowSize( size_t size )
    {
        value->setRowSize( size );
        index->setRowSize( size );
        GeneralEvaluation::setRowSize( size );
    }


    inline
    virtual
    void
    set_metric_id( uint32_t _id )
    {
        value->set_metric_id( _id );
        index->set_metric_id( _id );
        GeneralEvaluation::set_metric_id( _id );
    }




    inline
    virtual
    void
    set_verbose_execution( bool _v )
    {
        GeneralEvaluation::set_verbose_execution( _v );
        value->set_verbose_execution( _v );
        index->set_verbose_execution( _v );
    }


    virtual
    double
    eval() const;
    virtual
    double
    eval( const Cnode*             cnode,
          const CalculationFlavour cf,
          const Sysres*            sr,
          const CalculationFlavour tf  ) const;

    virtual
    double
    eval( const Cnode*             cnode,
          const CalculationFlavour cf ) const;

    virtual
    double*
    eval_row( const Cnode*             _cnode,
              const CalculationFlavour _cf ) const;

    virtual
    double
    eval( double arg1,
          double arg2 ) const;

    virtual
    double
    eval(  const list_of_cnodes&       lc,
           const list_of_sysresources& ls  ) const;

    virtual
    double*
    eval_row(  const list_of_cnodes&       lc,
               const list_of_sysresources& ls ) const;




    inline
    virtual
    void
    print() const
    {
        std::cout << "${" << variable_name << "}[";
        index->print();
        std::cout << "] = ";
        value->print();
        std::cout << ";" << std::endl;
    };
};
};

#endif
