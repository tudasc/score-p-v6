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



#ifndef CUBE_DUMP_PRINTER
#define CUBE_DUMP_PRINTER

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>

#include "Cube.h"
#include "CubeCnode.h"
#include "CubeMachine.h"
#include "CubeMetric.h"
#include "CubeRegion.h"
#include "CubeServices.h"
#include "CubeTypes.h"
#include "algebra4.h"


#include "cube4_dump_CommandOption.h"


typedef std::vector<uint64_t> bitstring_t;





class Printer
{
protected:
    std::ostream& fout;
    cube::Cube*   cube;


    bool
    is_bit_set( bitstring_t& bits,
                unsigned     bitnum );

    void
    set_bit( bitstring_t& bits,
             unsigned     bitnum );

    void
    dump_cube_attributes( const std::map<std::string, std::string>& attrs ) const;

    void
    dump_cube_mirrors( const std::vector<std::string>& mirrors ) const;

    void
    dump_metric_dimension( const std::vector<cube::Metric*>& metrics );

    void
    dump_calltree_dimension( const std::vector<cube::Region*>& regn,
                             const std::vector<cube::Cnode*>&  metrics );

    void
    dump_system_dimension( const std::vector<cube::Machine*>& metrics );

    void
    dump_topologies( const std::vector<cube::Cartesian*>& topologies,
                     bool                                 show_coordinates ) const;
    void
    dump_topology( cube::Cartesian* topology,
                   bool             show_coordinates ) const;

    void
    dump_misc_data( std::string data,
                    bool        selected_data ) const;


    void
    dump_metric( cube::Metric* metric,
                 int           level,
                 bitstring_t   childrenmarkers );

    void
    dump_region( cube::Region* region );

    void
    dump_cnode( cube::Cnode* cnode,
                int          level,
                bitstring_t  childrenmarkers );

    void
    dump_location( cube::Location* loc,
                   int             level,
                   bitstring_t     childrenmarkers );

    void
    dump_location_group( cube::LocationGroup* lg,
                         int                  level,
                         bitstring_t          childrenmarkers );

//     void
//     dump_node( cube::Node*       node,
//                int         level,
//                bitstring_t childrenmarkers );

    void
    dump_stn( cube::SystemTreeNode* stn,
              int                   level,
              bitstring_t           childrenmarkers );

public:
    Printer( std::ostream& _out,
             cube::Cube*   _cube ) : fout( _out ), cube( _cube )
    {
    }
    virtual
    ~Printer()
    {
    };

    void
    print_header( const std::string& data,
                  const bool         show_ghost,
                  const bool         selected_data,
                  const bool         show_coords );


    void
    prepare(    std::vector < cube::Metric* >& _metrics,
                std::vector < cube::Cnode* >&  _cnodes,
                std::vector < cube::Thread* >& _threads ) const;


    virtual
    void
    dump_data( std::vector < cube::Metric* >& _metrics,
               std::vector < cube::Cnode* >&  _cnodes,
               std::vector < cube::Thread* >& _threads,
               cube::CalculationFlavour       _mf,
               cube::CalculationFlavour       _cf,
               bool                           stored,
               ThreadSelection                selected_threads ) const;

    virtual
    void
    dump_flat_profile(  std::vector < cube::Metric* >& _metrics,
                        std::vector < cube::Region* >& regions,
                        std::vector < cube::Thread* >& _threads,
                        cube::CalculationFlavour       _mf,
                        ThreadSelection                selected_threads ) const;
};

#endif
