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


/*-------------------------------------------------------------------------*/
/**
 *  @file
 *  @ingroup CUBE_lib.base
 *  @brief   Declaration of the class Cube.
 **/
/*-------------------------------------------------------------------------*/


#ifndef __CUBE_H
#define __CUBE_H

#include <inttypes.h>
#include <stdint.h>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <iosfwd>

#ifndef CUBE_AS_SVN_EXTERNAL
#  include  "cubelib-version.h"
#endif
#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeSystemTreeNode.h"
#include "CubeLocationGroup.h"
#include "CubeLocation.h"
#include "CubeMetric.h"
#include "CubeRegion.h"
#include "CubeCnode.h"
#include "CubeCartesian.h"
#include "CubeValues.h"
#include "CubeError.h"
#include "CubeOperationProgress.h"
#include "CubeIstream.h"


//#include "CubeStrategies.h"

namespace cubeparser
{
// Forward declarations
class Cube4Parser;
}

namespace cubeplparser
{
// Forward declarations
class CubePLDriver;
}

#define CUBELIB_LIBRARY_VERSION_KEY "CUBE Library version"

/// CubePL version label
#define CUBEPL_VERSION_KEY "CubePL Version"
/// CubePL version, written by this version of C-writer library
#define CUBEPL_VERSION "1.1"
#define CUBEPL_VERSION_KEY "CubePL Version"
#define CUBELIB_VERSION_KEY "Cube Version"
#define CUBELIB_ANCHOR_VERSION_KEY "Cube anchor.xml syntax version"
#define CUBELIB_XML_VERSION_KEY "Cube syntax version"
#define CUBELIB_ANCHOR_VERSION "4.5"

/**
 * \namespace cube
 */
namespace cube
{
// Forward declarations
/*-------------------------------------------------------------------------*/
/**
 *  @class   cube::Cube
 *  @ingroup CUBE_lib.base
 *  @brief   Cube base class for access to performance data.
 *
 *  The performance data is arranged in three dimensions (1) metric,
 *  (2) call tree, and (3) system. Each dimension has its own hierarchical
 *  (tree-like) structure.
 **/
/*-------------------------------------------------------------------------*/


class Cube
{
public:
    /// @name Construction and destruction
    /// @{

    /**
     * Default constructor for Cube objects
     * @param enforce_saving Flag on how to handle zero values in the performance data.
     */
    Cube( CubeEnforceSaving enforce_saving = CUBE_IGNORE_ZERO );

    /**
     * Copy constructor for Cube objects
     * @param cube Source Cube objects
     * @param copy_flag Flag on type of copy
     * @param enforce_savingFlag on how to handle zero values in the performance data.
     */
    Cube( Cube&             cube,
          CubeCopyFlag      copy_flag      = CUBE_ONLY_STRUCTURE,
          CubeEnforceSaving enforce_saving = CUBE_IGNORE_ZERO
          );

    /**
     * Virtual destructor to allow derived classes.
     */
    virtual
    ~Cube();

    /// @}
    /// @name Report handling
    /// @{

    void
    openCubeReport( std::string cubename,
                    bool        disable_clustering = false
                    );             // enable clustering by default.
    void
    writeCubeReport( std::string cubename,
                     bool        write_ghost_metrics = false );
    void
    closeCubeReport();
    void
    writeMetricsData( std::string cubename );

    /// @}

    /**************************************************************
     * CUBE write API
     *************************************************************/

    // The order of children in any hierarchical structure is defined by
    // the order of child creation. For example, the first performance metric
    // created as child of a given metric is the first child.

    // / set attributes
    void
    def_attr( const std::string& key,
              const std::string& value );

    // / set mirror URLs
    void
    def_mirror( const std::string& url );

    // build metric dimension

    // url is a URL or a file path, or a std::string of "@mirror@...".
    // descr is simply a short std::string.

/**
 * Defines a metric and its parent in the dimension "metrix" of the cube.
 *
 * url is a URL or a file path, or a std::string of "@mirror@...", descr is simply a short std::string.
 */
    Metric*
    def_met( const std::string& disp_name,
             const std::string& uniq_name,
             const std::string& dtype,
             const std::string& uom,
             const std::string& val,
             const std::string& url,
             const std::string& descr,
             Metric*            parent,
             TypeOfMetric       type_of_metric = CUBE_METRIC_EXCLUSIVE,
             const std::string& expression = "",
             const std::string& init_expression = "",
             const std::string& aggr_plus_expression = "",
             const std::string& aggr_minus_expression = "",
             const std::string& aggr_aggr_expression = "",
             const bool         threadwise = true,
             VizTypeOfMetric    is_ghost = CUBE_METRIC_NORMAL
             );

    // build program dimension
/**
 * Define a region in a program.
 */
    Region*
    def_region( const std::string& name,
                const std::string& mangled_name,
                const std::string& paradigm,
                const std::string& role,
                long               begln,
                long               endln,
                const std::string& url,
                const std::string& descr,
                const std::string& mod );

    // if source-code info available
/**
 * Define a call node with a known source code.
 */
    Cnode*
    def_cnode( Region*            callee,
               const std::string& mod,
               int                line,
               Cnode*             parent,
               uint32_t           id = ( uint32_t )-1 // -! signalizes, that automatical id assignent should be performed
               );

    // if source-code info not available
/**
 * Define a call node without a known source code.
 */
    Cnode*
    def_cnode( Region* callee,
               Cnode*  parent );

    // build system dimension
/**
 * Define machine, on which the measurement was done.
 */
    Machine*
    def_mach( const std::string& name,
              const std::string& desc );

/**
 * Define node of the machine.
 */
    Node*
    def_node( const std::string& name,
              Machine*           mach );

/**
 * Define process of a programm.
 */
    Process*
    def_proc( const std::string& name,
              int                rank,
              Node*              node );

/**
 * Define thread.
 */
    Thread*
    def_thrd( const std::string& name,
              int                rank,
              Process*           proc );


/**
 * Define system tree node, on which the measurement was done.
 */
    SystemTreeNode*
    def_system_tree_node( const std::string& name,
                          const std::string& desc,
                          const std::string& stn_class,
                          SystemTreeNode*    parent = NULL
                          );

/**
 * Define location group for the measured values.
 */
    LocationGroup*
    def_location_group( const std::string& name,
                        int                rank,
                        LocationGroupType  type,
                        SystemTreeNode*    parent
                        );

/**
 * Define the location, which carreis the measured value.
 */
    Location*
    def_location( const std::string& name,
                  int                rank,
                  LocationType       type,
                  LocationGroup*     parent
                  );

    // define topology
/**
 * Set to every thread coordinates in the topology.
 */
    Cartesian*
    def_cart( long                     ndims,
              const std::vector<long>& dimv,
              const std::vector<bool>& periodv );
    void
    def_coords( Cartesian*               cart,
                const Sysres*            sys,
                const std::vector<long>& coordv );



/**
 * Set a std::vector of topologies
 */
    void
    add_cart( std::vector<Cartesian*>& cart )
    {
        cartv = cart;
    };



    /**************************************************************
     * CUBE read API
     *************************************************************/

    //  std::vector of entities
    inline
    const std::vector<Metric*>&
    get_metv()      const
    {
        return metv;
    };
    // /<  Get a std::vector of metrics.
    inline
    const std::vector<Metric*>&
    get_ghost_metv()      const
    {
        return ghost_metv;
    };                                                                                          // /<  Get a std::vector of metrics.


    Metric*
    get_met( const std::string& ) const;                                                        // /< Returns a metric with given unique name or NULL.

    Metric*
        get_met( uint32_t, bool filed_id = false ) const;                                                              // /< Returns a metric with given id or NULL.


    inline
    const std::vector<Region*>&
    get_regv()      const
    {
        return regv;
    };                                                                                          // /<  Get a std::vector of regions.
    inline
    const std::vector<Cnode*>&
    get_cnodev()    const
    {
        return cnodev;
    };                                                                                  // /<  Get a std::vector of call nodes.
    inline
    const std::vector<Sysres*>&
    get_sysv()      const
    {
        return sysv;
    };                                                                                          // /<  Get a std::vector of system resources.

    inline
    const std::vector<SystemTreeNode*>&
    get_stnv()     const
    {
        return stnv;
    };

    inline
    const std::vector<SystemTreeNode*>&
    get_root_stnv()     const
    {
        return root_stnv;
    };

    inline
    const std::vector<SystemTreeNode*>&
    get_non_root_stnv()     const
    {
        return non_root_stnv;
    };

    inline
    const std::vector<LocationGroup*>&
    get_location_groupv()     const
    {
        return location_groupv;
    };

    inline
    const std::vector<Location*>&
    get_locationv()     const
    {
        return locationv;
    };



    inline
    const std::vector<Machine*>&
    get_machv()     const
    {
        return machv;
    };                                                                                          // /<  Get a std::vector of machines.

    inline
    const std::vector<Node*>&
    get_nodev()     const
    {
        return nodev;
    };                                                                                          // /<  Get a std::vector of nodes.

    inline
    const std::vector<Process*>&
    get_procv()     const
    {
        return location_groupv;
    };                                                                                          // /<  Get a std::vector of processes.

    inline
    const std::vector<Thread*>&
    get_thrdv()     const
    {
        return locationv;
    };                                                                                          // /<  Get a std::vector of threads.

    inline
    const std::vector<Cartesian*>&
    get_cartv()     const
    {
        return cartv;
    };                                                                                          // /<  Get a std::vector of cartesian topologies.

    const Cartesian*
    get_cart( int i )  const;

    // / get the roots of metric and program dimension

    inline
    const std::vector<Metric*>&
    get_root_metv()   const
    {
        return root_metv;
    };
    // / get the roots of program dimension

    inline
    const std::vector<Cnode*>&
    get_root_cnodev() const
    {
        return root_cnodev;
    };

    // / Returns full list of full callpath

    inline
    const std::vector<Cnode*>&
    get_fullcnodev() const
    {
        return fullcnodev;
    };


    // / Returns cubaname

    inline
    const std::string&
    get_cubename() const
    {
        return cubename;
    }


// ----------- GETIING DIFFERENT VALUES ------------

/**
 * Set a severity "value" for triplet (metric, cnode, thread). It sets just a value in the
 * metric "met" without taking into account, its this value inclusive or exclusive.
 */
    void
    set_sev( Metric* met,
             Cnode*  cnode,
             Thread* thrd,
             double  value );

/**
 * Add a value "inc" to severiti for triplet (metric, cnode, thread). It adds a value to the  saved value in the
 * metric "met" without taking into account, its this value inclusive or exclusive.
 */
    void
    add_sev( Metric* met,
             Cnode*  cnode,
             Thread* thrd,
             double  incr );

    // flat-tree only



// -------------------- WONT WORK!!!! -----
// ----------ALL REGIOS HAVE TO BE DECLATRED BEFORE set_sev is called----------------
/**
 * Set a severity "value" for triplet (metric, region, thread). All cnodes with the "region" as callee gets the value.
 */
    void
    set_sev( Metric* met,
             Region* region,
             Thread* thrd,
             double  value );

/**
 * Add a value "inc" to severiti for triplet (metric, region, thread). All cnodes with the "region" as callee add the value.
 */
    void
    add_sev( Metric* met,
             Region* region,
             Thread* thrd,
             double  incr );

// --------------------------------------------------------------------------





// ------------------- adv part


/**
 * Set a severity "value" for triplet (metric, cnode, thread). General call. All another calls uses this call to operate with values.
 */
    void
    set_sev( Metric* met,
             Cnode*  cnode,
             Thread* thrd,
             Value*  value );


/**
 * Add a value "inc" to severiti for triplet (metric, cnode, thread)
 */
    void
    add_sev( Metric* met,
             Cnode*  cnode,
             Thread* thrd,
             Value*  val );

    // flat-tree only



// -------------------- WONT WORK!!!! -----
// ----------ALL REGIOS HAVE TO BE DECLATRED BEFORE set_sev is called----------------
/**
 * Set a severity "value" for triplet (metric, region, thread). All cnodes with the "region" as callee gets the value.
 */
    void
    set_sev( Metric* met,
             Region* region,
             Thread* thrd,
             Value*  val );

/**
 * Add a value "inc" to severiti for triplet (metric, region, thread). All cnodes with the "region" as callee add the value.
 */
    void
    add_sev( Metric* met,
             Region* region,
             Thread* thrd,
             Value*  incr );

// ---------------------------------------------------------------------------



/**
 * Returns a severity "value" for triplet (metric, cnode, thread) (metric, excl cnode, thread). In the case,
 * if metric is inclusive, an exclusive value along calltree gets calculated
 */
    double
    get_sev( Metric*         met,
             const Cnode*    cnode,
             const Location* thrd );

    // / get severity, advanced
    Value*
    get_sev_adv( Metric*         met,
                 const Cnode*    cnode,
                 const Location* thrd );


// ---------------------- ANALYSIS PART -----------------------------
/**
 * Returns direct saved severity "value" for triplet (metric, cnode, thread), without taking into account inclusivity or exclusivity
 */
    double
    get_saved_sev( Metric*         met,
                   const Cnode*    cnode,
                   const Location* thrd );

    // / get severity, advanced
    Value*
    get_saved_sev_adv( Metric*         met,
                       const Cnode*    cnode,
                       const Location* thrd );







//        ---- for the begining it is not needed ---------------------
    //
    // / Calculates an exclusive or an inclusive  value for given Metric, Cnode and Thread.
    // / Expansion along the metric dimension assumes their inclusive nature.
    // / Expansion in calltree dimension is done by corresponding metric.
    Value*
    get_sev_adv( Metric*            metric,
                 CalculationFlavour mf,
                 Region*            region,
                 CalculationFlavour rf,
                 Sysres*            sys,
                 CalculationFlavour sf );


    //
    // / Calculates an exclusive or an inclusive  value for given Metric, Cnode and Thread.
    // / Expansion along the metric dimension assumes their inclusive nature.
    // / Expansion in calltree dimension is done by corresponding metric.
    Value*
    get_sev_adv( Metric*            metric,
                 CalculationFlavour mf,
                 Cnode*             cnode,
                 CalculationFlavour cnf,
                 Sysres*            sys,
                 CalculationFlavour sf );

    // / Calculates an exclusive or an inclusive  Value for given Metric, Cnode..
    // /Expansion along the metric dimension assumes their inclusive nature.
    // /Expansion in calltree dimension is done by corresponding metric.
    // / Along the system dimension (over all threads) the value is summed up.
    Value*
    get_sev_adv( Metric*            metric,
                 CalculationFlavour mf,
                 Cnode*             cnode,
                 CalculationFlavour cnf );

    // / Calculates an exclusive or an inclusive  Value for given Metric, Cnode..
    // /Expansion along the metric dimension assumes their inclusive nature.
    // /Expansion in calltree dimension is done by corresponding metric.
    // / Along the system dimension (over all threads) the value is summed up.
    Value*
    get_sev_adv( Metric*            metric,
                 CalculationFlavour mf,
                 Region*            region,
                 CalculationFlavour rf );

    // / Calculates an exclusive or an inclusive  Value for given Metric, Cnode..
    // /Expansion along the metric dimension assumes their inclusive nature.
    // /Expansion in calltree dimension is done by corresponding metric.
    // / Along the system dimension (over all threads) the value is summed up.
    Value*
    get_sev_adv( Metric*            metric,
                 CalculationFlavour mf,
                 Sysres*            sys,
                 CalculationFlavour sf );

    // / Calculates an exclusive or an inclusive  Value for given Metric and over whole calltree.
    // /Expansion along the metric dimension assumes their inclusive nature.
    // / Along the system dimension (over all threads) and calltree dimensions ( over all roots of hte calltree) the value is summed up.
    Value*
    get_sev_adv( Metric*            metric,
                 CalculationFlavour mf );


    // an actual call, which performs the calculation (delegates it to the metric)
    void
    get_system_tree_sevs_adv( Metric*                metric,
                              CalculationFlavour     mf,
                              Cnode*                 cnode,
                              CalculationFlavour     cnf,
                              std::vector< Value* >& inclusive_values,
                              std::vector< Value* >& exclusive_values
                              );

    // an actual call, which performs the calculation (delegates it to the metric)
    void
    get_system_tree_sevs_adv( Metric*                metric,
                              CalculationFlavour     mf,
                              Region*                region,
                              CalculationFlavour     rnf,
                              std::vector< Value* >& inclusive_values,
                              std::vector< Value* >& exclusive_values
                              );

    // VErsion for the case, system tree pane is in the middle.
    void
    get_system_tree_sevs_adv( Metric*                metric,
                              CalculationFlavour     mf,
                              std::vector< Value* >& inclusive_values,
                              std::vector< Value* >& exclusive_values
                              );





// Version of the methods above with another return value.

    // / Calculates an exclusive or an inclusive  Value for given Metric, Cnode and Thread.
    // / Returns the "double" representation of the internal "Value" if possible.
    // / Uses the corresponding call "get_excl_sev_adv(...)"
    double
    get_sev( Metric*            metric,
             CalculationFlavour mf,
             Region*            region,
             CalculationFlavour rf,
             Sysres*            sys,
             CalculationFlavour sf );

    // / Calculates an exclusive or an inclusive  Value for given Metric, Cnode and Thread.
    // / Returns the "double" representation of the internal "Value" if possible.
    // / Uses the corresponding call "get_excl_sev_adv(...)"
    double
    get_sev( Metric*            metric,
             CalculationFlavour mf,
             Cnode*             cnode,
             CalculationFlavour cnf,
             Sysres*            sys,
             CalculationFlavour sf );

    // / Calculates an exclusive or an inclusive  Value for given Metric, Cnode and  and whole Machine (over all threads).
    // / Returns the "double" representation of the internal "Value" if possible.
    // / Uses the corresponding call "get_excl_sev_adv(...)"
    double
    get_sev( Metric*            metric,
             CalculationFlavour mf,
             Cnode*             cnode,
             CalculationFlavour cnf );

    // / Calculates an exclusive or an inclusive  Value for given Metric, Cnode and  and whole Machine (over all threads).
    // / Returns the "double" representation of the internal "Value" if possible.
    // / Uses the corresponding call "get_excl_sev_adv(...)"
    double
    get_sev( Metric*            metric,
             CalculationFlavour mf,
             Region*            region,
             CalculationFlavour rf );

    // / Calculates an exclusive or an inclusive  Value for given Metric, Cnode..
    // /Expansion along the metric dimension assumes their inclusive nature.
    // /Expansion in calltree dimension is done by corresponding metric.
    // / Along the system dimension (over all threads) the value is summed up.
    double
    get_sev( Metric*            metric,
             CalculationFlavour mf,
             Sysres*            sys,
             CalculationFlavour sf );

    // / Calculates an exclusive or an inclusive Value for given Metric, whole calltree and whole machine.
    // / Returns the "double" representation of the internal "Value" if possible.
    // / Uses the corresponding call "get_excl_sev_adv(...)"
    double
    get_sev( Metric*            metric,
             CalculationFlavour mf );


    // to complete call list
    double
    get_sev( Cnode*             cnode,
             CalculationFlavour cf );
    double
    get_sev( Region*            region,
             CalculationFlavour rf );
    double
    get_sev( Sysres*            sys,
             CalculationFlavour sf );


    // an actual call, which performs the calculation (delegates it to the metric)
    void
    get_system_tree_sevs( Metric*                metric,
                          CalculationFlavour     mf,
                          Cnode*                 cnode,
                          CalculationFlavour     cnf,
                          std::vector< double >& inclusive_values,
                          std::vector< double >& exclusive_values
                          );

    // an actual call, which performs the calculation (delegates it to the metric)
    void
    get_system_tree_sevs( Metric*                metric,
                          CalculationFlavour     mf,
                          Region*                region,
                          CalculationFlavour     rnf,
                          std::vector< double >& inclusive_values,
                          std::vector< double >& exclusive_values
                          );

    // VErsion for the case, system tree pane is in the middle.
    void
    get_system_tree_sevs( Metric*                metric,
                          CalculationFlavour     mf,
                          std::vector< double >& inclusive_values,
                          std::vector< double >& exclusive_values
                          );



// ------------ row wise (always over system dimension) simple versions ----------------
    Value**
    get_saved_sevs_adv( Metric* met,
                        Cnode*  cnode );

    double*
    get_saved_sevs( Metric* met,
                    Cnode*  cnode );

    char*
    get_saved_sevs_raw( Metric* met,
                        Cnode*  cnode );

// ------------ row wise (always over system dimension) versions with aggregation ----------------
// ----------------- basic one -------------------

    /**
     * Saves row of values "as it is... without any conversion... used for fast copy"
     */
    void
    set_sevs_raw( Metric* met,
                  Cnode*  cnode,
                  char*   val );


    Value**
    get_sevs_adv( Metric*            metric,
                  CalculationFlavour mf,
                  Cnode*             cnode,
                  CalculationFlavour cnf );

    double*
    get_sevs( Metric*            metric,
              CalculationFlavour mf,
              Cnode*             cnode,
              CalculationFlavour cnf );

    char*
    get_sevs_raw( Metric*            metric,
                  CalculationFlavour mf,
                  Cnode*             cnode,
                  CalculationFlavour cnf );

// ---------------- for flat tree --------------------------

    Value**
    get_sevs_adv( Metric*            metric,
                  CalculationFlavour mf,
                  Region*            region,
                  CalculationFlavour cnf );

    double*
    get_sevs( Metric*            metric,
              CalculationFlavour mf,
              Region*            region,
              CalculationFlavour cnf );

    char*
    get_sevs_raw( Metric*            metric,
                  CalculationFlavour mf,
                  Region*            region,
                  CalculationFlavour cnf );

// ----------------agregated over cnode roots -

    Value**
    get_sevs_adv( Metric*            metric,
                  CalculationFlavour mf );

    double*
    get_sevs( Metric*            metric,
              CalculationFlavour mf );

    char*
    get_sevs_raw( Metric*            metric,
                  CalculationFlavour mf );


// ------------- list rowwise aggregation calls

    Value**
    get_sevs_adv( const list_of_metrics& metrics,
                  const list_of_cnodes&  cnodes );

    double*
    get_sevs( list_of_metrics& metrics,
              list_of_cnodes&  cnodes );

    Value**
    get_sevs_adv( list_of_metrics& metrics );

    double*
    get_sevs( list_of_metrics& metrics );

// ----------- analysis part with aggregation  (used by GUI. )  ---------------------



    Value*
    get_sev_adv( const list_of_metrics& metrics,
                 Cnode*                 cnode,
                 CalculationFlavour     cf );
    double
    get_sev( const list_of_metrics& metrics,
             Cnode*                 cnode,
             CalculationFlavour     cf );





    Value*
    get_sev_adv( const list_of_metrics& metrics,
                 Region*                region,
                 CalculationFlavour     rf );
    double
    get_sev( const list_of_metrics& metrics,
             Region*                region,
             CalculationFlavour     rf );

    Value*
    get_sev_adv( const list_of_metrics& metrics,
                 Sysres*                sysres,
                 CalculationFlavour     sf );
    double
    get_sev( const list_of_metrics& metrics,
             Sysres*                sysres,
             CalculationFlavour     sf );


    Value*
    get_sev_adv( const list_of_cnodes& cnodes,
                 Metric*               metric,
                 CalculationFlavour    mf );
    double
    get_sev( const list_of_cnodes& cnodes,
             Metric*               metric,
             CalculationFlavour    mf );


    double
    get_sev( const list_of_cnodes& cnodes,
             Sysres*               sysres,
             CalculationFlavour    sf );


    Value*
    get_sev_adv( const list_of_regions& regions,
                 Metric*                metric,
                 CalculationFlavour     mf );
    double
    get_sev( const list_of_regions& regions,
             Metric*                metric,
             CalculationFlavour     mf );


    double
    get_sev( const list_of_regions& regions,
             Sysres*                sysres,
             CalculationFlavour     sf );


    Value*
    get_sev_adv( const list_of_sysresources& sysres,
                 Metric*                     metric,
                 CalculationFlavour          mf );
    double
    get_sev( const list_of_sysresources& sysres,
             Metric*                     metric,
             CalculationFlavour          mf );

    double
    get_sev( const list_of_sysresources& sysres,
             Cnode*                      cnode,
             CalculationFlavour          cf );
    double
    get_sev( const list_of_sysresources& sysres,
             Region*                     region,
             CalculationFlavour          rf );

    // call with the list as an argument
    void
    get_system_tree_sevs_adv(  list_of_metrics&       metrics,
                               list_of_regions&       regions,
                               std::vector< Value* >& inclusive_values,
                               std::vector< Value* >& exclusive_values
                               );

    // call with the list as an argument
    void
    get_system_tree_sevs_adv(  list_of_metrics&       metrics,
                               list_of_cnodes&        cnodes,
                               std::vector< Value* >& inclusive_values,
                               std::vector< Value* >& exclusive_values
                               );

    // VErsion for the case, system tree pane is in the middle.
    void
    get_system_tree_sevs_adv( list_of_metrics&        metrics,
                              std::vector< Value*  >& inclusive_values,
                              std::vector< Value* >&  exclusive_values
                              );

    // call with the list as an argument
    void
    get_system_tree_sevs(  list_of_metrics&       metrics,
                           list_of_regions&       regions,
                           std::vector< double >& inclusive_values,
                           std::vector< double >& exclusive_values
                           );

    // call with the list as an argument
    void
    get_system_tree_sevs(  list_of_metrics&       metrics,
                           list_of_cnodes&        cnodes,
                           std::vector< double >& inclusive_values,
                           std::vector< double >& exclusive_values
                           );

    // VErsion for the case, system tree pane is in the middle.
    void
    get_system_tree_sevs( list_of_metrics&       metrics,
                          std::vector< double >& inclusive_values,
                          std::vector< double >& exclusive_values
                          );



    // ------------------------- right panel ---------------------------------

    Value*
    get_sev_adv( const list_of_metrics& metrics,
                 const list_of_cnodes&  cnodes,
                 Sysres*                sys,
                 CalculationFlavour     sf );
    double
    get_sev( const list_of_metrics& metrics,
             const list_of_cnodes&  cnodes,
             Sysres*                sys,
             CalculationFlavour     sf );

    Value*
    get_sev_adv( const list_of_metrics& metrics,
                 const list_of_regions& regions,
                 Sysres*                sys,
                 CalculationFlavour     sf );
    double
    get_sev( const list_of_metrics& metrics,
             const list_of_regions& regions,
             Sysres*                sys,
             CalculationFlavour     sf );

    Value*
    get_sev_adv( const list_of_metrics&      metrics,
                 const list_of_sysresources& sys_res,
                 Cnode*                      cnode,
                 CalculationFlavour          cf );
    double
    get_sev( const list_of_metrics&      metrics,
             const list_of_sysresources& sys_res,
             Cnode*                      cnode,
             CalculationFlavour          cf );


    Value*
    get_sev_adv( const list_of_metrics&      metrics,
                 const list_of_sysresources& sys_res,
                 Region*                     region,
                 CalculationFlavour          rf );
    double
    get_sev( const list_of_metrics&      metrics,
             const list_of_sysresources& sys_res,
             Region*                     region,
             CalculationFlavour          rf );



    Value*
    get_sev_adv( const list_of_cnodes&       cnodes,
                 const list_of_sysresources& sys_res,
                 Metric*                     metric,
                 CalculationFlavour          mf );
    double
    get_sev( const list_of_cnodes&       cnodes,
             const list_of_sysresources& sys_res,
             Metric*                     metric,
             CalculationFlavour          mf );


    Value*
    get_sev_adv( const list_of_regions&      regions,
                 const list_of_sysresources& sys_res,
                 Metric*                     metric,
                 CalculationFlavour          mf );
    double
    get_sev( const list_of_regions&      regions,
             const list_of_sysresources& sys_res,
             Metric*                     metric,
             CalculationFlavour          mf );

// ----  additional calls, which might replace all others

    Value*
    get_sev_adv( const list_of_metrics&      metrics,
                 const list_of_cnodes&       cnodes,
                 const list_of_sysresources& sys_res );
    double
    get_sev( const list_of_metrics&      metrics,
             const list_of_cnodes&       cnodes,
             const list_of_sysresources& sys_res );


    Value*
    get_sev_adv( const list_of_metrics& metrics,
                 const list_of_cnodes&  cnodes );
    double
    get_sev( const list_of_metrics& metrics,
             const list_of_cnodes&  cnodes );

    Value*
    get_sev_adv( const list_of_metrics&      metrics,
                 const list_of_sysresources& sys_res );
    double
    get_sev( const list_of_metrics&      metrics,
             const list_of_sysresources& sys_res );

    Value*
    get_sev_adv( const list_of_cnodes&       cnodes,
                 const list_of_sysresources& sys_res );
    double
    get_sev( const list_of_cnodes&       cnodes,
             const list_of_sysresources& sys_res );




    Value*
    get_sev_adv( const list_of_metrics& metrics );
    double
    get_sev( const list_of_metrics& metrics );


    Value*
    get_sev_adv( const list_of_cnodes& cnodes );
    double
    get_sev( const list_of_cnodes& cnodes );


    Value*
    get_sev_adv( const list_of_sysresources& sys_res );
    double
    get_sev( const list_of_sysresources& sys_res );

    // -------------------- end of analysis part  ------------------------


// ---------------- optimisation of writting ------------------

    /** @brief return optimal ID sequence for a specific metric.
     * Gives the user of Cube an opportunity to write every metric in for it
     * optimal way. If the user does it, metric doesn't have to make
     * optimisation of the underlying AdvancedMatrix for faster reading.
     * Returns the sequence of the callnodes. By writing in this order one
     * avoids the optimisation delay and gets from the beginning the optimal
     * data file.
     */
    std::vector<Cnode* >
    get_optimal_sequence( Metric* metric );

// _---------------------- end of ADVANCED PART ------------------------



    // / setting the cubewide stratedy
    void
    setGlobalMemoryStrategy( CubeStrategy strategy );

    // / setting the metric own stratedy
    void
    setMetricMemoryStrategy( Metric*      met,
                             CubeStrategy strategy );


    // / droping row  if strategy will allow it (manual for example)
    void
    dropRowInMetric( Metric* met,
                     Cnode*  row );

    // / drop specific row in all metrics
    void
    dropRowInAllMetrics( Cnode* row );

    // / drop specific row in all metrics
    void
    dropAllRowsInMetric( Metric* met );

    // / drop specific row in all metrics
    void
    dropAllRowsInAllMetrics();

    // / get attribute
    std::string
    get_attr( const std::string& key ) const;

    // / get attributes

    inline
    const std::map<std::string, std::string>&
    get_attrs() const
    {
        return attrs;
    }

    // / get mirrors
    const std::vector<std::string>&
    get_mirrors() const;

    // / get mirrors

    inline
    std::vector<std::string>&
    get_mirror()
    {
        return mirror_urlv;
    }

    // / returns the number of threads
    int
    max_num_thrd() const;

    // / get a root of metrics
    Metric*
    get_root_met( Metric* met );

    // / search for cnodes
    Cnode*
    get_cnode( Cnode& cn ) const;

    // / search for sysres (machines, nodes)
    Machine*
    get_mach( Machine& mach ) const;

    // / get a machine node
    Node*
    get_node( Node& node ) const;

// ------ additinal writing ----------------
    /**
     * @brief Writes a meta part in the cube3 file or a metafile of cube4.
     * @param[in,out] out Reference to the header file output stream.
     * @param[in] cube3_export Flag to indicate Cube 3 format.
     * @param[in] write_ghost_metrics Flag to indicate whether ghost metrics should be written to the header.
     */
    void
    writeXML_header( std::ostream& out,
                     bool          cube3_export,
                     bool          write_ghost_metrics = false
                     );

    /**
     * @brief Writes a data part in cube3 format.
     * @param[in,out] out Reference to the header file output stream.
     *
     * @note  Used to transform cube4 into cube3 format.
     */
    void
    writeXML_data( std::ostream& out );

    /**
     * @brief Finishes the meta-data file by writing "</cube>"
     * @param[in,out] out Reference to the header file output stream
     */
    void
    writeXML_closing( std::ostream& out );

// ------------------------------------------


//     void
//     restore_calltree()							///< Restores a calltree form backop copy.
//     {
//      cnodev = fullcnodev;
//      root_cnodev = root_cnodev_backup;
//
//     }
//
    void
    reroot_cnode( Cnode* );                                               // /< Sets this cnode as a root element.

    void
    prune_cnode( Cnode* );                                                // /< Cuts this cnode and sets the parent as a leaf. If this cnode is a root, it removes it from call tree. Backup copy is not touched.

    void
    set_cnode_as_leaf( Cnode* );



    inline
    void
    set_statistic_name( const std::string& _stat )
    {
        def_attr( "statisticfile", _stat );
    };                                           // /< Sets the name of the statistic file in cube.
    std::string
    get_statistic_name();                        // /< Returns the name of the statistic file in cube.



    inline
    void
    enable_flat_tree( const bool status )
    {
        def_attr( "withflattree", ( status ) ? "yes" : "no" );
    };                                                                                                      // /< Saves attribute "withflattree" to "yes", if it should be enabled

    bool
    is_flat_tree_enabled();                         // /< Returns true -> if flattree is enabled.



    inline
    void
    set_metrics_title( const std::string& _metrics )
    {
        metrics_title = _metrics;
    };                                                                                              // /< Sets the name of the metrics dimension in cube.

    inline
    std::string
    get_metrics_title()
    {
        return metrics_title;
    };                                                                   // /< Returns the name of the metrics dimension in cube.


    inline
    void
    set_calltree_title( const std::string& _calltree )
    {
        calltree_title = _calltree;
    };                                                                                                  // /< Sets the name of the program dimension in cube.

    inline
    std::string
    get_calltree_title()
    {
        return calltree_title;
    };                                                                     // /< Returns the name of the program dimension in cube.


    inline
    void
    set_systemtree_title( const std::string& _systemtree )
    {
        systemtree_title = _systemtree;
    };                                                                      // /< Sets the name of the system dimension in cube.

    inline
    std::string
    get_systemtree_title()
    {
        return systemtree_title;
    };                                                                         // /< Returns the name of the system dimension in cube.


    uint32_t
    get_number_void_threads() const;                                           // /< Calculates number of void threads. Used in setup_cubepl1_memory()
    uint32_t
    get_number_void_processes() const;                                         // /< Calculates number of void processes. Used in setup_cubepl1_memory()
    void
    setup_cubepl_memory();                                                     // /< Stores in the memory manager for CubePL1 evaluations a set of values, related to the calculation context: number of metrics, number of regions, etc.





    inline
    void
    set_post_initialization( bool _v )
    {
        postcompilation_of_derived_metrics = _v;
        postcreation_of_containers         = _v;
    };                                                                             // /< sets the postinitialization of metrics. Open this interface for different parsers.


    void
    compile_derived_metric_expressions();                       // /< After reading in the cube and creationg the structure, one runs over all metrics and compiles their expressions.


    std::vector<std::string>
    get_misc_data();                                                    // /< Returns a list of file names, stored in the cube. Including cube-format related files.

    std::vector<char>
    get_misc_data( std::string& dataname );                            // /< Returns a std::vector with the content of the file "dataname" if present, otherwise empty;
    void
    write_misc_data( std::string& dataname,
                     const char*  buffer,
                     size_t       len );                                                             // /< stores anydata inside of cube. C-like call
    void
    write_misc_data( std::string& dataname,
                     std::vector<char>& );                                                   // /< stores anydata inside of cube.

    inline
    bool
    is_clustering_on()                                                                  // /< Returns, if one expands clusters
    {
        return !disable_clustering;
    };


    inline
    void
    enable_clustering( bool status )
    {
        disable_clustering = !status;
    }

    inline
    void
    set_clusters_count( std::map<uint64_t, std::map<uint64_t, uint64_t > > counter )                            // /< Sets cluster counters in cube. It is set syntax parser if clustering is enabled. Otherwise it stays empty.
    {
        cluster_counter = counter;
    }

    inline
    std::map<uint64_t,  std::map<uint64_t, uint64_t > >&
    get_clusters_counter()                                                                              // /< Sets cluster counters in cube. It is set syntax parser if clustering is enabled. Otherwise it stays empty.
    {
        return cluster_counter;
    }


    inline
    void
    set_original_root_cnodev( std::vector<cube::Cnode*>& vec )
    {
        original_root_cnodev = vec;
    }


    inline
    CubePLMemoryManager*
    get_cubepl_memory_manager()
    {
        return cubepl_memory_manager;
    }


    inline
    cubeplparser::CubePLDriver*
    get_cubepl_driver()
    {
        return cubepl_driver;
    }


    // here one can store all working copies of cnodes, which should be removed if Cube object is deleted and which are not direct part
    // of calltree dimension. (clustering remapping cnodes)

    inline
    void
    store_ghost_cnode( const Cnode* _cnode )
    {
        remapping_cnodev[ _cnode ] = 1;
    }

    void
    select_cubepl_engine( std::string version );   // replaces internally used cubepl engine  by proper version, if needed

    bool
    test_cubepl_expression( std::string&,
                            std::string& );   // testes CubePL expression with currently selected CubePL engine...



    inline
    void
    initialize()
    {
        if ( is_initialized() )
        {
            return;
        }
        create_metrics_data_containers();
        initialized = true;
        set_post_initialization( false );
    }

    inline
    bool
    is_initialized()
    {
        return initialized;
    }


    inline
    OperationProgress*
    get_operation_progress()
    {
        return operation_progress;
    }



protected:

    // metric dimension
    std::vector<Metric*> metv;                     // /<  Vector of metrics. Plain storage. Tree hierarchy is saved inside of metric.
    // program dimension
    std::vector<Region*> regv;                     // /<  Vector of region. Plain storage. Tree hierarchy is saved inside of region.
    std::vector<Cnode*>  cnodev;                   // /<  Vector of call threes after operation prune.
    std::vector<Cnode*>  fullcnodev;               // /<  Full std::vector of call threes. Plain storage. Tree hierarchy is saved inside of cnode.
    // system dimension
    std::vector<Sysres*> sysv;                     // /<  Vector of system resources.
//     std::vector<Machine*>        machv;            ///<  Vector of machines.
//     std::vector<Node*>           nodev;            ///<  Vector of nodes.
//     std::vector<Process*>        procv;            ///<  Vector of processes.
//     std::vector<Thread*>         thrdv;            ///< Vector of threads
    std::vector<SystemTreeNode*> stnv;             // /<  Vector of SystemTreeNodes.
    std::vector<SystemTreeNode*> root_stnv;        // /<  Vector of root systen tree nodes.
    std::vector<SystemTreeNode*> non_root_stnv;    // /<  Vector of not  root systen tree nodes. (nodes in old model)
    std::vector<SystemTreeNode*> machv;            // /<  Vector of systen tree nodes , wich are "machines"
    std::vector<SystemTreeNode*> nodev;            // /<  Vector of systen tree nodes, which are  "nodes"

    std::vector<LocationGroup*> location_groupv;   // /<  Vector of location groups.
    std::vector<Location*>      locationv;         // /<  Vector of locations.



    std::vector<Cartesian*>            cartv;       // /< Vector of topologie, used in cube.
    std::map<std::string, std::string> attrs;       // /< attributes <key, value>
    std::vector<std::string>           mirror_urlv; // /< mirror urls


    // severity.
//     std::map<Metric*, Matrix*> sev_matm; // ABSOLETE
//     Matrix* get_sev_matrix(Metric* metric);  // ABSOLETE

    // / roots of metric dimension
    std::vector<Metric*> root_metv;
    // / roots of call tree (actual, also after reroot operations)
    std::vector<Cnode*> root_cnodev;

    // std::vector storing original calltree, if clastering id on.
    std::vector<Cnode*> original_root_cnodev;

    // std::vector storing ghost cnodes, which are used in clustering algorith but not deleted.
    // just bookeeping to delete them and to avoid memory leak
    // Map is used to avoid multiple storing
    std::map<const Cnode*, uint8_t> remapping_cnodev;

//     /// roots of call tree stored in cube
//     std::vector<Cnode*>  root_cnodev_backup;



    uint32_t cur_cnode_id;
    uint32_t cur_metric_id;
    uint32_t cur_region_id;
//     uint32_t cur_machine_id;
//     uint32_t cur_node_id;
//     uint32_t cur_process_id;
//     uint32_t cur_thread_id;
    uint32_t cur_stn_id;
    uint32_t cur_location_group_id;
    uint32_t cur_location_id;


// ------------------------ Additional part (for AdvancedMatrix) -----------------
    cube::CubePLMemoryManager*  cubepl_memory_manager;
    cubeplparser::CubePLDriver* cubepl_driver;
    CubePLVerbosityLevel        cubepl_verbose;
    std::string                 cubepl_metric_verbose_execution;
    // ghost metrics
    std::vector<Metric*> ghost_metv;                            // /<  Vector of ghost metrics. They are invisible in  Cube and get returned onyl if uniqname is known via get_met

    std::string cubename;                                       // /< Saves the name of the cube. Files get then name [cubename].cubex , [cubename].cubex.data/...

    FileFinder* filefinder;                                     // /< Compoment, which delivers name of the files, according to he different layouts.

    std::string metrics_title;                                  // /< Title of metrics dimension
    std::string calltree_title;                                 // /< Title of program dimension
    std::string systemtree_title;                               // /< Title of system dimension


    OperationProgress* operation_progress;                  ///< used by parser and cube to mark progress of a long term operation


// /    std::string     filemode;                                   ///< ???????? NOT USED
//     bool              first_call;                               ///< Indicates, that there are no data containers in metrics yet. Ifter creating container no changes in dimensions are allowed.
//     bool              writing_mode;                             ///< Indicates, whether Cube already writed some values. If yes, no changes in dimensions are allowes. Probably redundand with "first_call".
    bool mode_read_only;                                              // /< Indicates, that no severities cann be added. Makes "set_sev" having no effect.

    bool postcompilation_of_derived_metrics;                          // /< Signalizes, that we are in "operator << " and def_met should omit compilation of expression of derived metric.
    bool postcreation_of_containers;                                  // /< Signalizes, that we are in "operator << " and def_met should omit initialization  of container....
    bool initialized;                                                 // marks if containers have been created


    bool                                                disable_clustering;                 // /<  Parser disables cllustering reconstruction.
    std::map<uint64_t,   std::map<uint64_t, uint64_t> > cluster_counter;                    // /< Stores count of clusters.



//     bool              only_memory;                              ///< Indicates, that Cube doesn't create any files regular cube4 in the filesystem. Needed to work with old cube2/cube3 files. To storage their values it uses temporary files.
    CubeEnforceSaving enforce_saving;                           // /< Makes cube ignore zeroes or enforce saving.

    void
    create_metrics_data_containers();                           // /< is called in the end of anchor.xml <system> element to initializeall metrics
    void
    create_metrics_data_containers( Metric* met );              // /<  Initializes metrics container

    std::string
    create_prefix( std::string );                               // /< Creates a prefix "[cubename].binary_data/" for the AdvancedMatrix data files.
    void
    assign_ids( Metric* met );                                  // /< Sets the proper ids for given metric in every dimension.
    void
    assign_id_metrics();                                        // /< Sets the proper ids in the metric dimension. Currently empty , coz no special prescription than order of creation is needed.
    void
    create_calltree_ids( Metric* met );                         // /< Sets the proper ids in the calltree dimension for every metric separately.
    void
    create_system_ids();                                        // /< Sets the proper ids in the system dimension. Currently empty, coz no spetial  prescription than order of creation is needed.


    bool
    system_tree_cube3_compatibility_check();                    // /< Checks whether the current system tree can be represented in cube3 model. Used in streaming >> operator.


// --------------------------------------------------------------------------


/**
 * Actual method to create a metric.
 */
    Metric*
    def_met( const std::string& disp_name,
             const std::string& uniq_name,
             const std::string& dtype,
             const std::string& uom,
             const std::string& val,
             const std::string& url,
             const std::string& descr,
             Metric*            parent,
             uint32_t           id,
             TypeOfMetric       type_of_metric = CUBE_METRIC_EXCLUSIVE,
             const std::string& expression = "",
             const std::string& init_expression = "",
             const std::string& aggr_plus_expression = "",
             const std::string& aggr_minus_expression = "",
             const std::string& aggr_aggr_expression = "",
             const bool         threadwise = true,
             VizTypeOfMetric    is_ghost = CUBE_METRIC_NORMAL );

/**
 * Actual method to create a region.
 */
    Region*
    def_region( const std::string& name,
                const std::string& mangled_name,
                const std::string& paradigm,
                const std::string& role,
                long               begln,
                long               endln,
                const std::string& url,
                const std::string& descr,
                const std::string& mod,
                uint32_t           id );


/**
 * Actual method to create a machine.
 */
    Machine*
    def_mach( const std::string& name,
              const std::string& desc,
              uint32_t           id );

/**
 * Actual method to create a node.
 */
    Node*
    def_node( const std::string& name,
              Machine*           mach,
              uint32_t           id );

/**
 * Actual method to create a process.
 */
    Process*
    def_proc( const std::string& name,
              int                rank,
              Node*              node,
              uint32_t           id );

/**
 * Actual method to create a thread.
 */
    Thread*
    def_thrd( const std::string& name,
              int                rank,
              Process*           proc,
              uint32_t           id );

/**
 * Actual method to create system tree node
 */
    SystemTreeNode*
    def_system_tree_node( const std::string& name,
                          const std::string& desc,
                          const std::string& stn_class,
                          SystemTreeNode*    parent,
                          uint32_t           id
                          );

/**
 * Actual method to create location group
 */
    LocationGroup*
    def_location_group( const std::string& name,
                        int                rank,
                        LocationGroupType  type,
                        SystemTreeNode*    parent,
                        uint32_t           id
                        );

/**
 * Actual method to create a location
 */
    Location*
    def_location( const std::string& name,
                  int                rank,
                  LocationType       type,
                  LocationGroup*     parent,
                  uint32_t           id
                  );


// ------------------ Calls needed by construcor Cube(Cube&)-------------------------------------------------------

/**
 * Creates a copy of metric _met. To set parent, it uses the mapping met_map. All parents should be already present in the mapping table.
 */
    Metric*
    def_met( Metric* _met,
             std::map<Metric*, Metric*>& met_map );



/**
 * Creates a copy of region _region.
 */
    Region*
    def_region( Region* _region );


/**
 * Creates a copy of cnode _cnode. To set parent, it uses the mapping cnode_map. All parents should be already present in the mapping table. To set a region, it uses mapping region_map
 */
    Cnode*
    def_cnode( Cnode* _cnode,
               std::map<Cnode*, Cnode*>& cnode_map,
               std::map<Region*, Region*>& region_map,
               bool copy_id = false
               );


    /**
     * Creates a copy of machines _machine.
     */
    Machine*
    def_mach( Machine* _machine );

    /**
     * Creates a copy of node _node. To set a parent, it uses mapping mach_map
     */
    Node*
    def_node( Node* _node,
              std::map< Machine*, Machine*>& mach_map );

    /**
     * Creates a copy of process _process. To set a parent, it uses mapping node_map
     */
    Process*
    def_proc( Process* _process,
              std::map< Node*, Node*>& node_map );

    /**
     * Creates a copy of node _node. To set a parent, it uses mapping mach_map
     */
    Thread*
    def_thrd( Thread* _thread,
              std::map< Process*, Process*>& process_map );

    /**
     * Creates a copy of system tree nodes _machine.
     */
    SystemTreeNode*
    def_system_tree_node( SystemTreeNode* _stn,
                          std::map< SystemTreeNode*, SystemTreeNode*>& stn_map  );

    /**
     * Creates a copy of location group _locationGroup. To set a parent, it uses mapping stn_map
     */
    LocationGroup*
    def_location_group( LocationGroup* _locationGroup,
                        std::map< SystemTreeNode*, SystemTreeNode*>& stn_map );

    /**
     * Creates a copy of node _node. To set a parent, it uses mapping locationGroup_map
     */
    Location*
    def_location( Location* _locationGroup,
                  std::map< LocationGroup*, LocationGroup*>& locationGroup_map );


    /**
     * \brief Flag special cubes so they can be distinguished on loading.
     *
     * If a metric of one of the special kinds is passed, mark the parent cube object.
     * Currently only used for ScaleFuncValue to enable (future) display of widgets.
     * FIXME: met should be const, but called function (see implementation) does not guarantee const-ness.
     * \param met   New metric that is used to decide whether to mark the cube.
     */
    void
    check_special_cube( Metric* met );

    // initialiazes collection of the subtree to perform faster calculation of an inclusive value
    void
    collect_whole_subtree_for_callpaths();

// initialiazes collection of the subtree to perform faster calculation of an inclusive value
    void
    collect_whole_subtree_for_systemtree();

    /**
     * Creates a copy of topology _node. To set a parent, it uses mapping mach_map
     */
//     Cartesian*   def_cart(Cartesian * _topo, std::map< Thread*, Thread*> & thread_map);



//    friend class MdAggrCube; ///< Extension of Student M.Meyer (or whoever).. class MdAggrCube is a part of tools. should be them moved into library...
    friend class Parser;                  // /< Parser (not defined anywhere)
    friend class cubeparser::Cube4Parser; // /< Parser of saved .cube v4.0
//    friend class cubeparser::Cube3Parser; ///< Parser of saved .cube v3.0


    // write to a file
/**
 * Write a cube3 file.
 */
    void
    write( const std::string& filename );
};

// I/O operators
// / Read a cube meta part. If it reads the cube3, it sets "only_memory", "writing_mode" flag during the reading of the "<severity>...</severity>" part of the cube2/cube3 file.
cube::CubeIstream&
operator>>( cube::CubeIstream& in,
            Cube&              cb );

std::istream&
operator>>( std::istream& in,
            Cube&         cb );


// / Writes a cube3 version of the cube.
std::ostream&
operator<<( std::ostream& out,
            Cube&         cb );
}

#endif
