/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016-2018                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2015                                                     **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  Copyright (c) 2015                                                     **
**  RWTH Aachen University, JARA-HPC                                       **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/*-------------------------------------------------------------------------*/
/**
 *  @file
 *  @ingroup CUBE_lib.base
 *  @brief   Declaration of the class cube::CubeIoProxy
 **/
/*-------------------------------------------------------------------------*/


#ifndef CUBE_IOPROXY_H
#define CUBE_IOPROXY_H

#include <string>
#include <vector>

#include "CubeProxy.h"


namespace cube
{
class Cnode;
class Cube;
class IdIndexMap;
class Metric;
class Sysres;
class SystemTreeNode;
class Value;

/*-------------------------------------------------------------------------*/
/**
 *  @class   cube::CubeIoProxy
 *  @ingroup CUBE_lib.base
 *  @brief   Implementation of the CubeProxy interface using local I/O calls.
 **/
/*-------------------------------------------------------------------------*/
class CubeIoProxy
    : public CubeProxy
{
public:
    /// @brief Default constructor
    ///
    CubeIoProxy();

    /// @brief constructor to be used for internally created cube object
    CubeIoProxy( Cube* cube );

    /// @brief Virtual destructor
    ///
    virtual
    ~CubeIoProxy();

    /// @brief Open a report based on filename.
    ///
    /// Open Cube report specified via filename according to the base
    /// URL specified during creation.
    ///
    /// @param filename
    ///     Path and filename
    ///
    virtual void
    openReport( const std::string& filename );

    /// @brief Open the report specified in initial URL.
    ///
    /// Opens the Cube report specified in the initial URL used to create
    /// the CubeProxy object.
    ///
    virtual void
    openReport();

    /// @brief Close report currently open.
    ///
    virtual void
    closeReport();



    inline
    virtual
    const std::string
    get_statistic_name()
    {
        return mCube->get_statistic_name();
    }

    // / drop specific row in all metrics
    virtual
    void
    dropAllRowsInMetric( cube::Metric* met )
    {
        mCube->dropAllRowsInMetric( met );
    };


    /// @brief Save data to a new Cube report.
    ///
    /// @param filename
    ///     Filename of the new Cube report.
    ///
    virtual void
    saveCopy( const std::string& filename );

    /// @}
    /// @name Metrics
    /// @{

    /// @brief Define a new metric.
    ///
    /// @param disp_name
    ///     Name as displayed in the UI
    /// @param uniq_name
    ///     Unique internal name as used in derived metrics
    /// @param dtype
    ///     Name of datatype
    /// @param uom
    ///     Unit of measure
    /// @param val
    ///     TODO
    /// @param url
    ///     URL of online description
    /// @param descr
    ///     Description of the metric as displayed in the UI
    /// @param parent
    ///     Pointer to parent metric (NULL for root metrics)
    /// @param type_of_metric
    ///     Method to compute metric
    /// @param expression
    ///     CubePL expression to compute metric
    /// @param init_expression
    ///     CubePL expression used to initialize metric
    /// @param aggr_plus_expression
    ///     CubePL expression to compute plus aggregation
    /// @param aggr_minus_expression
    ///     CubePL expression to compute minus aggregation
    /// @param aggr_aggr_expression
    ///     CubePL expression to compute aggregation over system tree
    /// @param row_wise
    ///     Row-wise storage of data
    /// @param visibility
    ///     Visibility in UI
    ///
    /// @return Pointer to metric object.
    ///
    virtual Metric*
    defineMetric( const std::string& disp_name,
                  const std::string& uniq_name,
                  const std::string& dtype,
                  const std::string& unit_of_measure,
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
                  const bool         row_wise = true,
                  VizTypeOfMetric    visibility = CUBE_METRIC_NORMAL );

    /// @brief Retrieve a defined metric by its unique name
    ///
    /// @param uniq_name
    ///     Unique string name of metric
    /// @return
    ///     Pointer to metric object, NULL if metric not found.
    ///
    virtual Metric*
    getMetric( const std::string& uniq_name ) const;

    /// @brief Get a vector of all metrics
    ///
    /// @return
    ///     Vector of metrics.
    ///
    virtual const std::vector< Metric* >&
    getMetrics() const;

    /// @brief Get a vector of all root metrics
    ///
    /// @return
    ///     Vector of root metrics.
    ///
    virtual const std::vector< Metric* >&
    getRootMetrics() const;

    /// @brief Get a vector of all non-visible (ghost) metrics
    ///
    /// @return
    ///     Vector of non-visible metrics.
    ///
    virtual const std::vector< Metric* >&
    getGhostMetrics() const;

    /// @brief Get the data for all trees in the metric dimension.
    ///
    /// This call returns all data to fully expand all trees in the metric
    /// dimension.
    ///
    /// @param[in] cnode_selections
    ///     The selected cnodes.
    /// @param[in] sysres_selections
    ///     The selected system resources.
    /// @param[out] inclusive_values
    ///     Reference to a container to be used for the data returned as
    ///     inclusive values. The container will be cleared before new data
    ///     is added.
    /// @param[out] exclusive_values
    ///     Reference to a container to be used for the data returned as
    ///     exclusive values. The container will be cleared before new data
    ///     is added.
    ///
    virtual void
    getMetricTreeValues( const list_of_cnodes&       cnode_selections,
                         const list_of_sysresources& sysres_selections,
                         value_container&            inclusive_values,
                         value_container&            exclusive_values );

    /// @brief Get the data for all trees in the metric dimension.
    ///
    /// This call returns all data to fully expand all trees in the metric
    /// dimension.
    ///
    /// @param[in] region_selections
    ///     The selected region.
    /// @param[in] sysres_selections
    ///     The selected system resources.
    /// @param[out] inclusive_values
    ///     Reference to a container to be used for the data returned as
    ///     inclusive values. The container will be cleared before new data
    ///     is added.
    /// @param[out] exclusive_values
    ///     Reference to a container to be used for the data returned as
    ///     exclusive values. The container will be cleared before new data
    ///     is added.
    ///
    virtual void
    getMetricTreeValues( const list_of_regions&      region_selections,
                         const list_of_sysresources& sysres_selections,
                         value_container&            inclusive_values,
                         value_container&            exclusive_values );

    /// @brief Query inclusive and exclusive values of a Metric subtree.
    ///
    /// @param cnode_selections
    ///     The selected cnodes
    /// @param sysres_selections
    ///     The selected system resources
    /// @param root_metric
    ///     Root of the subtree
    /// @param depth
    ///     Depth of the subtree
    /// @param metric_id_indices
    ///     Associative container with id to index mappingY
    /// @param inclusive_values
    ///     List of inclusive values
    /// @param exclusive_values
    ///     List of exclusive values
    ///
    virtual void
    getMetricSubtreeValues( const list_of_cnodes&       cnode_selections,
                            const list_of_sysresources& sysres_selections,
                            Metric&                     root_metric,
                            size_t                      depth,
                            IdIndexMap&                 metric_id_indices,
                            value_container*            inclusive_values,
                            value_container*            exclusive_values );


    /// @brief Query inclusive and exclusive values of a Metric subtree.
    ///
    /// @param region_selections
    ///     The selected region
    /// @param sysres_selections
    ///     The selected system resources
    /// @param root_metric
    ///     Root of the subtree
    /// @param depth
    ///     Depth of the subtree
    /// @param metric_id_indices
    ///     Associative container with id to index mappingY
    /// @param inclusive_values
    ///     List of inclusive values
    /// @param exclusive_values
    ///     List of exclusive values
    ///
    virtual void
    getMetricSubtreeValues( const list_of_regions&      regions_selections,
                            const list_of_sysresources& sysres_selections,
                            Metric&                     root_metric,
                            size_t                      depth,
                            IdIndexMap&                 metric_id_indices,
                            value_container*            inclusive_values,
                            value_container*            exclusive_values );

    /// @}
    /// @name Call dimension
    /// @{

    /// @brief Get a vector of all call-tree nodes
    ///
    /// @return
    ///     Vector of cnodes
    ///
    virtual const std::vector< Cnode* >&
    getCnodes() const;

    /// @brief Get a vector of all root cnodes.
    ///
    /// @return
    ///     Vector of root cnodes.
    ///
    virtual const std::vector< Cnode* >&
    getRootCnodes() const;

    /// @brief Get the data for the call dimension.
    ///
    /// This call returns all inclusive and exclusive values for the full
    ///     call-tree.
    ///
    /// @param[in] metric_selections
    ///     The selected metrics.
    /// @param[in] sysres_selections
    ///     The selected system resources.
    /// @param[out] inclusive_values
    ///     Reference to a container to be used for the data returned as
    ///     inclusive values. The container will be cleared before new data
    ///     is added.
    /// @param[out] exclusive_values
    ///     Reference to a container to be used for the data returned as
    ///     exclusive values. The container will be cleared before new data
    ///     is added.
    ///
    virtual void
    getCallpathTreeValues( const list_of_metrics&      metric_selections,
                           const list_of_sysresources& sysres_selections,
                           value_container&            inclusive_values,
                           value_container&            exclusive_values );

    /// @brief Get the data for a subtree the the call dimension.
    ///
    /// Depending on the input parameters, this call returns the
    /// inclusive and exclusive values for a subtree specified by the
    /// %root_cnode and %depth. If either %inclusive_values or
    /// %exclusive_values is set to %CUBE_PROXY_VALUES_IGNORE, the
    /// corresponding values are not computed.
    ///
    /// @param[in] metric_selections
    ///     List of selected metrics.
    /// @param[in] sysres_selections
    ///     List of system resources.
    /// @param[in] root_cnode
    ///     Root node of the requested subtree.
    /// @param[in] depth
    ///     Depth of the requested subtree. If value of
    ///     CUBE_PROXY_FULL_SUBTREE is provided, the full subtree up to
    ///     and including the leaf nodes is computed.
    /// @param[out] cnode_id_indices
    ///     Translation table to identify the index in the container for
    ///     a specific cnode_id.
    /// @param[in,out] inclusive_values
    ///     Pointer to a %value_container filled with inclusive values.
    /// @param[in,out] exclusive_values
    ///     Pointer to a %value_container filled with exclusive values.
    ///
    ///
    virtual void
    getCallpathSubtreeValues( const list_of_metrics&      metric_selections,
                              const list_of_sysresources& sysres_selections,
                              Cnode&                      root_cnode,
                              size_t                      depth,
                              IdIndexMap&                 cnode_id_indices,
                              value_container*            inclusive_values,
                              value_container*            exclusive_values );

    /// @brief Set given Cnode as new root Cnode.
    ///
    /// @param cnode
    ///     New root Cnode.
    ///
    virtual void
    rerootCnode( Cnode& cnode );

    /// @brief Remove given Cnode from call tree
    ///
    /// @param cnode
    ///     Cnode to remove.
    ///
    virtual void
    pruneCnode( Cnode& cnode );

    /// @brief Remove all children of a given Cnode
    ///
    /// @param cnode
    ///     Cnode to remove children from.
    ///
    virtual void
    setCnodeAsLeaf( Cnode& cnode );

    /// @brief Get a vector of regions.
    ///
    /// @return
    ///     Vector of regions.
    ///
    virtual const std::vector< cube::Region* >&
    getRegions() const;

    /// @brief Get the data for all regions of the call-path dimension
    ///
    /// @param[in] metric_selections
    ///     The selected metrics.
    /// @param[in] sysres_selections
    ///     The selected system resources.
    /// @param[out] inclusive_values
    ///     Reference to a container to be used for the data returned as
    ///     inclusive values. The container will be cleared before new data
    ///     is added.
    /// @param[out] exclusive_values
    ///     Reference to a container to be used for the data returned as
    ///     exclusive values. The container will be cleared before new data
    ///     is added.
    /// @param[out] difference_values
    ///     Reference to a container to be used for the data returned as
    ///     difference of inclusive and exclusive values. The container
    ///     will be cleared before new data is added.
    ///
    virtual void
    getFlatTreeValues( const list_of_metrics&      metric_selections,
                       const list_of_sysresources& sysres_selections,
                       value_container&            inclusive_values,
                       value_container&            exclusive_values,
                       value_container&            difference_values );

    /// @}
    /// @name System dimension
    /// @{

    /// @brief Get the data for a tree metric.
    ///
    /// This call enables the GUI to query metrics individually, so the GUI
    /// can enable access to an available root metric while other metrics of
    /// the tree are still being aggregated.
    ///
    /// @param[in] metric_selections
    ///     The selected metrics.
    /// @param[in] cnode_selections
    ///     The selected cnodes.
    /// @param[out] inclusive_values
    ///     Reference to a container to be used for the data returned as
    ///     inclusive values. The container will be cleared before new data
    ///     is added.
    /// @param[out] exclusive_values
    ///     Reference to a container to be used for the data returned as
    ///     exclusive values. The container will be cleared before new data
    ///     is added.
    ///
    virtual void
    getSystemTreeValues( const list_of_metrics& metric_selections,
                         const list_of_cnodes&  cnode_selections,
                         value_container&       inclusive_values,
                         value_container&       exclusive_values );

    /// @brief Get the data for a tree metric.
    ///
    /// This call enables the GUI to query metrics individually, so the GUI
    /// can enable Access to an available root metric while other metrics of
    /// the tree are still being aggregated.
    ///
    /// @param[in] metric_selections
    ///     The selected metrics.
    /// @param[in] region_selections
    ///     The selected region.
    /// @param[out] inclusive_values
    ///     Reference to a container to be used for the data returned as
    ///     inclusive values. The container will be cleared before new data
    ///     is added.
    /// @param[out] exclusive_values
    ///     Reference to a container to be used for the data returned as
    ///     exclusive values. The container will be cleared before new data
    ///     is added.
    ///
    virtual void
    getSystemTreeValues( const list_of_metrics& metric_selections,
                         const list_of_regions& region_selections,
                         value_container&       inclusive_values,
                         value_container&       exclusive_values );

    /// @brief Get a vector of locations.
    ///
    /// @return
    ///     Vector of locations.
    ///
    virtual const std::vector< Location* >&
    getLocations() const;

    /// @brief Get a vector of all location groups.
    ///
    /// @return
    ///     Vector of location groups
    ///
    virtual const std::vector< LocationGroup* >&
    getLocationGroups() const;

    /// @brief Get a vector of all system-tree nodes
    ///
    /// @return
    ///     Vector of system-tree nodes
    ///
    virtual const std::vector< SystemTreeNode* >&
    getSystemTreeNodes() const;

    /// @brief Get a vector of only the system-tree root nodes
    ///
    /// @return
    ///     Vector of system-tree root nodes
    ///
    virtual const std::vector< SystemTreeNode* >&
    getRootSystemTreeNodes() const;

    /// @brief Get a vector of system resources
    ///
    /// @return
    ///     Vector of system resources
    ///
    virtual const std::vector< Sysres* >&
    getSystemResources() const;

    /// @brief Get the specific Cartesian topology.
    ///
    /// @param cartesianId
    ///     Unique ID of Cartesian topology.
    /// @return
    ///     Reference to topology object.
    ///
    virtual const Cartesian&
    getCartesian( size_t cartesianId ) const;

    /// @brief Get the number of Cartesian topologies defined.
    ///
    /// @return
    ///     Number of Cartesian topologies defined
    ///
    virtual size_t
    getNumCartesians() const;

    /// @brief Get a vector of Cartesian topologies.
    ///
    /// @return
    ///     Topology vector.
    ///
    virtual const std::vector< Cartesian* >&
    getCartesians() const;

    /// @}
    /// @name Online Documentation
    /// @{

    /// @brief Define a new mirror for the Metrics used in the Cube report.
    ///
    /// @param url
    ///     URL of the metric documentation.
    ///
    virtual void
    defineMirror( const std::string& url );

    /// @brief Get a list of URLs as mirrors for documentation
    ///
    /// @return
    ///     List of URLs of documentation mirrors
    ///
    const std::vector< std::string >&
    getMirrors();

    /// @}
    /// @name CubePL
    /// @{

    /// @brief Query validity of CubePL driver
    ///
    /// @return
    ///     true, if CubePL driver is set. false, otherwise.
    ///
    virtual bool
    hasCubePlDriver() const;

    /// @brief Get a active CubePL driver.
    ///
    /// @return
    ///     The CubePL driver
    ///
    virtual cubeplparser::CubePLDriver&
    getCubePlDriver();

    /// @brief Query validity of CubePL memory manager.
    ///
    /// @return
    ///     true, if CubePL memory manager is set, false, otherwise.
    ///
    virtual bool
    hasCubePlMemoryManager() const;

    /// @brief Get the current CubePL memory manager.
    ///
    /// @return
    ///     CubePL memory manager
    ///
    virtual CubePLMemoryManager&
    getCubePlMemoryManager();

    /// @}
    /// @name Attributes
    /// @{

    /// @brief Define a string attribute.
    ///
    /// @param key
    ///     Unique attribute key
    /// @param value
    ///     Attribute value
    ///
    /// @note If an attribute of the same name is already defined,
    ///     it will be overwritten.
    ///
    virtual void
    defineAttribute( const std::string& key,
                     const std::string& value );

    /// @brief Retrieve the value for a given attribute
    ///
    /// @param key
    ///     Unique attribute key
    /// @return
    ///     Attribute value, empty string for unknown keys.
    ///
    virtual std::string
    getAttribute( const std::string& key ) const;

    /// @brief Get a map of all attributes.
    ///
    /// @return
    ///     Reference to attribute map.
    ///
    virtual const std::map< std::string, std::string >&
    getAttributes() const;

    /// @}
    /// @name Memory settings
    /// @{

    /// @brief Set global memory strategy for the underlying Cube file
    ///
    /// @param strategy
    ///     Memory strategy
    ///
    virtual void
    setMemoryStrategy( CubeStrategy strategy );

    /// @}
    /// @name Miscellaneous
    /// @{

    /// @brief Get the operation status of the current operation running.
    ///
    /// @return
    ///     Progress status structure
    ///
    virtual const ProgressStatus&
    getOperationProgressStatus() const;

    virtual bool
    isCubePlExpressionValid( std::string& _to_test,
                             std::string& error_message );

private:
    /// @}

    /// @brief Internal pointer to Cube object
    ///
    /// @note declared mutable as Cube interface is not entirely const-correct.
    ///
    mutable Cube* mCube;
};
}      /* namespace cube */

#endif /* ! CUBE_IOPROXY_H */
