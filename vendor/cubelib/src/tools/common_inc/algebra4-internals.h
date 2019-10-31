/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2019                                                **
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



#ifndef __CUBE_ALGEBRA4_INTERNALS_H
#define __CUBE_ALGEBRA4_INTERNALS_H
/**
 *
 * \file algebra4-internals.h
 * \brief Contains a set of functions , which are used by algebra4 internally, but shouldn't be used by external tools
 *
 ************************************************/
/******************************************

   Performance Algebra

 *******************************************/

#include <climits>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include "AggrCube.h"
#include "CubeCnode.h"
#include "CubeCartesian.h"
#include "CubeMachine.h"
#include "CubeMetric.h"
#include "CubeNode.h"
#include "CubeProcess.h"
#include "CubeRegion.h"
#include "CubeThread.h"
#include "CubeError.h"

#include "Filter.h"


// #define VERSION "dev"
#define REGIONS_URL "@mirror@scalasca_regions-" VERSION ".html#"

enum DataDropCombination { NONE_CUBES_DROP = 0, BOTH_CUBES_DROP = 1, OLD_CUBE_DROP = 2, NEW_CUBE_DROP = 3 };

enum MetricDataTypeAdjust { NO_ADJUST = 0x0, INT_TO_UINT = 0x01, UINT_TO_INT = 0x2, INT_TO_DOUBLE = 0x04, DOUBLE_TO_INT = 0x08, UINT_TO_DOUBLE = 0x10, DOUBLE_TO_UINT = 0x20 };

enum CallTreeCopy { COPY_SAME_FLAVOUR = 0, COPY_TO_EXCLUSIFY = 1, COPY_TO_INCLUSIFY = 2 };

namespace cube
{
/**
 * A general structure of the mapping of one Cube on another.
 */
typedef struct
{
    std::map<Metric*, Metric*>                 metm;
    std::map<Cnode*,  Cnode*>                  cnodem;
    std::map<Region*,  Region*>                regionm;
    std::map<Location*, Location*>             sysm;
    std::map<LocationGroup*, LocationGroup*>   lgm;
    std::map<SystemTreeNode*, SystemTreeNode*> stnm;

    std::map<Metric*, Metric*>                 r_metm;
    std::map<Cnode*,  Cnode*>                  r_cnodem;
    std::map<Region*,  Region*>                r_regionm;
    std::map<Location*, Location*>             r_sysm;
    std::map<LocationGroup*, LocationGroup*>   r_lgm;
    std::map<SystemTreeNode*, SystemTreeNode*> r_stnm;
} CubeMapping;


/*
 *  three valued logic, designed specialy for system tree analysis
 */
typedef struct
{
    bool is_machine;
    bool is_node;
} SystemTreeLogical;


/* Prototypes */
/* Metric dimension */
// / @cond PROTOTYPES

DataType
    metric_data_type_adust( DataType, MetricDataTypeAdjust );


bool
metric_merge( Cube&                newCube,
              const Cube&          input,
              CubeMapping&         cubeMap,
              MetricDataTypeAdjust adjust = NO_ADJUST
              );
void
metric_remap( Cube&        newCube,
              const Cube&  input,
              CubeMapping& cubeMap
              );
void
copy_tree( Cube&                newCube,
           Metric&              rhs,
           CubeMapping&         cubeMap,
           CallTreeCopy         modifier = COPY_SAME_FLAVOUR,
           bool                 omit_void = false,
           MetricDataTypeAdjust adjust = NO_ADJUST
           );
bool
compare_tree( Cube&                newCube,
              Metric&              lhs,
              Metric&              rhs,
              CubeMapping&         cubeMap,
              MetricDataTypeAdjust adjust = NO_ADJUST );

/* Program dimension */
bool
regions_exists( const Cube&                     input,
                const std::vector<std::string>& _nodes );                     // this produces warnings inside

bool
region_merge( Cube&        newCube,
              const Cube&  input,
              CubeMapping& cubeMap );

bool
cnode_merge( Cube&        newCube,
             const Cube&  input,
             CubeMapping& cubeMap,
             bool         copy_ids = false );
bool
cnode_reroot( Cube&                           newCube,
              const Cube&                     input,
              const std::string&              cn_newrootname,
              const std::vector<std::string>& cn_prunes,
              CubeMapping&                    cubeMap,
              bool                            copy_ids = false
              );
void
copy_tree( Cube&                           newCube,
           Cnode&                          rhs,
           Cnode&                          parent,
           const std::vector<std::string>& cn_prunes,
           CubeMapping&                    cubeMap,
           bool                            copy_ids = false );
void
copy_tree( Cube&        newCube,
           Cnode&       rhs,
           Cnode&       parent,
           CubeMapping& cubeMap,
           bool         copy_ids = false );
bool
compare_tree( Cube&        newCube,
              Cnode&       lhs,
              Cnode&       rhs,
              CubeMapping& cubeMap,
              bool         copy_ids = false );
Cnode*
def_cnode( Cube&  newCube,
           Cnode& rhs,
           Cnode* parent,
           bool   copy_ids = false );


// --------------- flexible system tree merge routines - start
bool
sysres_merge( Cube&        newCube,
              const Cube&  rhs,
              CubeMapping& cubeMap,
              bool         reduce,
              bool         collapse,
              bool         strict = true );
bool
is_subset( const Cube&  lhs,
           const Cube&  rhs,
           CubeMapping* cubeMap = NULL,
           bool         strict = true  );

bool
is_subset( SystemTreeNode* lhs,
           SystemTreeNode* rhs,
           CubeMapping*    cubeMap = NULL,
           bool            strict = true );

bool
is_subset( LocationGroup* lhs,
           LocationGroup* rhs,
           CubeMapping*   cubeMap = NULL );

void
collapsed_merge( Cube&        newCube,
                 const Cube&  lhs,
                 CubeMapping& cubeMap );

void
reduced_merge( Cube&        newCube,
               const Cube&  lhs,
               CubeMapping& cubeMap );

void
copy_system_tree( Cube&        cube,
                  const Cube&  lhs,
                  CubeMapping& cubeMap,
                  bool         strict = true );


void
merge( Cube&           newCube,
       SystemTreeNode* new_stn,
       SystemTreeNode* to_copy,
       CubeMapping&    cubeMap,
       CubeMapping*    midCubeMap = NULL,
       bool            strict = true
       );

void
merge( Cube&          newCube,
       LocationGroup* new_lg,
       LocationGroup* to_copy,
       CubeMapping&   cubeMap,
       CubeMapping*   midCubeMap = NULL  );


std::vector<SystemTreeNode*>
get_reduced_system_tree( const Cube&  cube,
                         CubeMapping& cubeMap );


SystemTreeLogical
is_reducable_tree( SystemTreeNode* to_copy );

void
get_reduced_system_tree( SystemTreeNode*               to_copy,
                         SystemTreeNode*               root,
                         std::vector<SystemTreeNode*>& stns,
                         CubeMapping&                  cubeMap );

void
delete_system_tree_node( SystemTreeNode* root );

void
copy_location_groups( SystemTreeNode* to_copy,
                      SystemTreeNode* root,
                      CubeMapping&    cubeMap );
void
delete_location_groups( SystemTreeNode* root );

void
copy_locations( LocationGroup* to_copy,
                LocationGroup* root,
                CubeMapping&   cubeMap );
void
delete_locations( LocationGroup* root );

// --------------- flexible system tree merge routines  - end


bool
is_subset( Cube&       lhs,
           const Cube& rhs,
           bool&       bigger_left,
           bool&       is_equal );


bool
is_subset( const std::vector<Node*>& mnodes,
           const std::vector<Node*>& snodes,
           bool&                     is_equal );
bool
is_subset( const std::vector<Process*>& big,
           const std::vector<Process*>& small,
           bool&                        is_equal );
void
merge( Cube&                        newCube,
       const std::vector<Machine*>& big,
       bool                         subset,
       bool                         collapse );

//   void plain_merge (Cube& newCube, Cube& lhs, const Cube& rhs);// original
void
plain_merge( Cube&       newCube,
             const Cube& rhs );
void
copy_tree( Cube&    newCube,
           Machine& oldMach,
           Machine& newMach,
           bool     subset,
           bool     collapse );
void
copy_tree( Cube& newCube,
           Node& oldNode,
           Node& newNode );
void
def_pro( Cube&    newCube,
         Process& lhs,
         Node&    rhs );

/* Mapping */
void
createMapping( Cube&        newCube,
               Cube&        oldCube,
               CubeMapping& cubeMap,
               bool         collapse );                                                   // old

void
createMappingMetric( Cube&        newCube,
                     Cube&        comp,
                     CubeMapping& cubeMap );
void
createMappingCnode( Cube&        newCube,
                    Cube&        comp,
                    CubeMapping& cubeMapping );
void
createMappingSystem( Cube&        newCube,
                     Cube&        comp,
                     CubeMapping& cubeMap,
                     bool         collapse );
void
createMappingSystem( Cube&        newCube,
                     Cube&        comp,
                     CubeMapping& cubeMap );


/* Topologies */
void
add_top( Cube&        newCube,
         Cube&        oldCube,
         CubeMapping& cubeMap );
void
merge_top( Cube& newCube,
           Cube& cube1,
           Cube& cube2 );


/* Data set operations */
void
add_sev( Cube&        newCube,
         Cube&        oldCube,
         CubeMapping& cubeMapw,
         double       fac );
void
set_sev( Cube&               newCube,
         Cube&               oldCube,
         CubeMapping&        cubeMap,
         DataDropCombination drop = NONE_CUBES_DROP );
void
set_sevs( Cube&               newCube,
          Cube&               oldCube,
          CubeMapping&        cubeMap,
          DataDropCombination drop = NONE_CUBES_DROP );


bool
check_sev( Cube&        newCube,
           Cube&        oldCube,
           CubeMapping& cubeMap );
void
copy_sev( Cube&   newCube,
          Metric* src,
          Metric* dest,
          Cnode*  cnode );
void
add_sev( Cube&   newCube,
         Metric* src,
         Metric* dest,
         Cnode*  cnode );

void
add_sev( Cube&        newCube,
         Cube&        oldCube,
         CubeMapping& old2new,
         Cnode*       oldCnode,
         bool         with_visits = true );

void
diff_sevs( Cube&        outCube,
           Cube&        minCube,
           CubeMapping& lhsmap,
           Cube&        subCube,
           CubeMapping& rhsmap );


/* Another realisations of compare */
bool
compare_metric_dimensions( Cube&,
                           Cube& );
bool
compare_calltree_dimensions( Cube&,
                             Cube& );
bool
compare_system_dimensions( Cube&,
                           Cube& );

template <class T>
bool
compareTrees( std::vector<T*>&,
              std::vector<T*>& );

template <class T>
void
createTreeEnumeration( std::vector<T*>& );

template <class T>
bool
compareVertices( std::vector<T*>&,
                 std::vector<T*>& );

bool
id_compare( IdentObject*,
            IdentObject* );

/* Filtering operations */
void
_cube_apply_filter( Cube&        lhs,
                    Cube&        rhs,
                    Cnode*       lhs_parent,
                    Cnode*       rhs_parent,
                    CubeMapping& mapping,
                    Filter&      filter );


void
set_region_urls( Cube& cube );
}


#endif
