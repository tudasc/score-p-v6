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
 * \file AggrCube.h
 * \brief Provides a cube, which can "aggregate" the date over some dimension.
 */

#ifndef CUBE_AGGRCUBE_H
#define CUBE_AGGRCUBE_H

#include <vector>

#include "CubeTypes.h"
#include "Cube.h"


enum inclmode { INCL,   // /< inlclusive severity
                EXCL,   // /< exclusive severity
                DIFF }; // /< inlcusive minus exclusive severity (only for regions)

enum aggrmode { SUM, MAX };

namespace cube
{
class AggrCube : public Cube
{
public:

    AggrCube()
        : Cube(),
          ct_aggr_mode( SUM )
    {
    };

    AggrCube( Cube&        _cube,
              CubeCopyFlag copy_flag = CUBE_ONLY_STRUCTURE )
        : Cube( _cube, copy_flag ),
          ct_aggr_mode( SUM )
    {
    };


    // ------------- call-tree view ---------------------

    // / metric tree
    void
    get_met_tree( std::vector<double>& excl_sevv,
                  std::vector<double>& incl_sevv,
                  inclmode             cnode_mode,
                  inclmode             sys_mode,
                  Cnode*               cnode,
                  Sysres*              sys );

    // / call tree
    void
    get_cnode_tree( std::vector<double>& excl_sevv,
                    std::vector<double>& incl_sevv,
                    inclmode             met_mode,
                    inclmode             sys_mode,
                    Metric*              met,
                    Sysres*              sys );

    // / system tree
    void
    get_sys_tree( std::vector<double>& excl_sevv,
                  std::vector<double>& incl_sevv,
                  inclmode             met_mode,
                  inclmode             cnode_mode,
                  Metric*              met,
                  Cnode*               cnode );


    // ------------- flat-profile view ------------------

    // / metric tree
    void
    get_met_tree( std::vector<double>& excl_sevv,
                  std::vector<double>& incl_sevv,
                  inclmode             reg_mode,
                  inclmode             sys_mode,
                  Region*              reg,
                  Sysres*              sys );

    // / metric tree (additianl interface)
    void
    get_met_tree( std::map<Metric*, double>& excl_sevv,
                  std::map<Metric*, double>& incl_sevv,
                  inclmode reg_mode,
                  inclmode sys_mode,
                  Cnode* cnode,
                  Sysres* sys );

    // / region tree
    void
    get_reg_tree( std::vector<double>& excl_sevv,
                  std::vector<double>& incl_sevv,
                  std::vector<double>& diff_sevv,
                  inclmode             met_mode,
                  inclmode             sys_mode,
                  Metric*              met,
                  Sysres*              sys );

    // / region tree (additianl interface)
    void
    get_reg_tree( std::map<Region*, double>& excl_sevv,
                  std::map<Region*, double>& incl_sevv,
                  std::map<Region*, double>& diff_sevv,
                  inclmode met_mode,
                  inclmode sys_mode,
                  Metric* met,
                  Sysres* sys );


    // / system tree
    void
    get_sys_tree( std::vector<double>& excl_sevv,
                  std::vector<double>& incl_sevv,
                  inclmode             met_mode,
                  inclmode             reg_mode,
                  Metric*              met,
                  Region*              reg );


    // ------------- single severity values ------------------

    // / single call-path severity
    double
    get_vcsev( inclmode met_mode,
               inclmode cnode_mode,
               inclmode sys_mode,
               Metric*  met,
               Cnode*   cnode,
               Sysres*  sys );

    // / single region severity
    double
    get_vrsev( inclmode met_mode,
               inclmode reg_mode,
               inclmode sys_mode,
               Metric*  met,
               Region*  reg,
               Sysres*  sys );

    // / metric root severity
    double
    get_rmet_sev( Metric* met );


private:

    // / extended severity
    double
    get_esev( Metric* met,
              Cnode*  cnode,
              Sysres* sys );

    // / call-tree aggregation mode
    aggrmode ct_aggr_mode;

    // / metric root severity cache
    std::map<Metric*, double> rmet_sevm;
};
}

#endif
