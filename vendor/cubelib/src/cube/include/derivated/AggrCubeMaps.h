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


/**
 * \file AggrCubeMaps.h
 * \brief Provides a Map for from "dimension value" -> "aggregate severity value"
 */

#ifndef CUBE_AGGRCUBEMAPS_H
#define CUBE_AGGRCUBEMAPS_H


#include <map>

#include "AggrCube.h"


/*
   *----------------------------------------------------------------------------
 *
 * class AggrCubeMaps
 *
 **************----------------------------------------------------------------------------
 */

namespace cube
{
class AggrCubeMaps : public AggrCube
{
public:

    AggrCubeMaps() : AggrCube()
    {
    };
    AggrCubeMaps( Cube&        _cube,
                  CubeCopyFlag copy_flag = CUBE_ONLY_STRUCTURE ) : AggrCube( _cube, copy_flag )
    {
    };


    /// Import vector interface
    using AggrCube::get_met_tree;
    using AggrCube::get_cnode_tree;
    using AggrCube::get_reg_tree;
    using AggrCube::get_sys_tree;


    //------------- call-tree view ---------------------

    /// metric tree
    void
    get_met_tree( std::map<Metric*, double>& excl_sevm,
                  std::map<Metric*, double>& incl_sevm,
                  inclmode cnode_mode,
                  inclmode sys_mode,
                  Cnode* cnode,
                  Sysres* sys );

    /// call tree
    void
    get_cnode_tree( std::map<Cnode*, double>& excl_sevm,
                    std::map<Cnode*, double>& incl_sevm,
                    inclmode met_mode,
                    inclmode sys_mode,
                    Metric* met,
                    Sysres* sys,
                    Cnode* cur_cnode = NULL );      // last argument only used internally

    /// system tree
    void
    get_sys_tree( std::map<Sysres*, double>& excl_sevm,
                  std::map<Sysres*, double>& incl_sevm,
                  inclmode met_mode,
                  inclmode cnode_mode,
                  Metric* met,
                  Cnode* cnode,
                  Sysres* cur_sys = NULL );       // last argument only used internally


    //------------- flat-profile view ------------------

    /// metric tree
    void
    get_met_tree( std::map<Metric*, double>& excl_sevm,
                  std::map<Metric*, double>& incl_sevm,
                  inclmode reg_mode,
                  inclmode sys_mode,
                  Region* reg,
                  Sysres* sys );

    /// region tree
    void
    get_reg_tree( std::map<Region*, double>& excl_sevm,
                  std::map<Region*, double>& incl_sevm,
                  std::map<Region*, double>& diff_sevm,
                  inclmode met_mode,
                  inclmode sys_mode,
                  Metric* met,
                  Sysres* sys );

    /// system tree
    void
    get_sys_tree( std::map<Sysres*, double>& excl_sevm,
                  std::map<Sysres*, double>& incl_sevm,
                  inclmode met_mode,
                  inclmode reg_mode,
                  Metric* met,
                  Region* reg,
                  Sysres* cur_sys = NULL );       // last argument only used internally
};
}


#endif   /* CUBE_AGGRCUBEMAPS_H */
