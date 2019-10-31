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



/**
 * \file CubePostDerivedMetric.h
 * \brief Defines a metric, which calculates its value using user defined expression in CubePL"
 */
#ifndef CUBE_POSTDERIVED_METRIC_H
#define CUBE_POSTDERIVED_METRIC_H



#include "CubeMetricBuildInType.h"

#include "CubeValues.h"
#include "CubeGeneralEvaluation.h"

/*
 *----------------------------------------------------------------------------
 *
 * class Metric
 *
 *******************************----------------------------------------------------------------------------
 */

namespace cube
{
class Connection;
class CubeProxy;

/**
 * Metric has a treelike structure and is a kind of Vertex.
 */

class PostDerivedMetric : public BuildInTypeMetric<double>
{
public:

    PostDerivedMetric( const std::string& disp_name,
                       const std::string& uniq_name,
                       const std::string& dtype,
                       const std::string& uom,
                       const std::string& val,
                       const std::string& url,
                       const std::string& descr,
                       FileFinder*        ffinder,
                       Metric*            parent,
                       uint32_t           id               = 0,
                       const std::string  _expression      = "",
                       const std::string& _expression_init = "",
                       const std::string& _aggr_expression = "",
                       const bool         threadwise = true,
                       VizTypeOfMetric    is_ghost = CUBE_METRIC_NORMAL
                       )
        : BuildInTypeMetric<double>( disp_name, uniq_name, dtype, uom, val, url, descr, ffinder, parent, id, _expression, _expression_init, "", "", _aggr_expression, threadwise,  is_ghost )
    {
        adv_sev_mat = NULL;
        initialized = false; // with creation initialisation is done
        cache_selection( ncid, ntid, cube::CUBE_METRIC_EXCLUSIVE );
    }

    /// @brief
    ///     Create a metric object via Cube connection
    /// @param connection
    ///     Active Cube connection.
    /// @param cubeProxy
    ///     Cube proxy for internal cross-referencing.
    ///
    static Serializable*
    create( Connection&      connection,
            const CubeProxy& cubeProxy );

    virtual
    ~PostDerivedMetric();

    /// @copydoc Serialization::get_serialization_key
    ///
    virtual std::string
    get_serialization_key() const;

    /// @copydoc Serialization::get_serialization_key
    ///
    static std::string
    get_static_serialization_key();

    virtual row_of_objects_t*
    create_calltree_id_maps( IDdeliverer*,
                             Cnode*,
                             row_of_objects_t* row )
    {
        return row;
    };

    virtual TypeOfMetric
    get_type_of_metric() const
    {
        return CUBE_METRIC_POSTDERIVED;
    };
    virtual std::string
    get_metric_kind() const
    {
        return "POSTDERIVED";
    };

    virtual
    bool
    isBuildIn()
    {
        return true;
    };

    virtual
    bool
    isDerived()
    {
        return true;
    };


    virtual
    void
    initialize( void );



    virtual IndexFormat
    get_index_format()
    {
        return CUBE_INDEX_FORMAT_SPARSE;
    };


    // ----------------- post derived metric should implement these calls directly


    virtual double
    get_sev_native(
        const list_of_cnodes&       cnodes,
        const list_of_sysresources& sysres
        );

    // -----------------row wise ----------------------------------------
    virtual double*
    get_sevs_native(
        const list_of_cnodes& cnodes
        );

    //  --massive calculation of a system tree
    virtual
    void
    get_system_tree_sevs_native( const list_of_cnodes&  cnodes,
                                 std::vector< double >& inclusive_values,
                                 std::vector< double >& exclusive_values
                                 );

    virtual
    inline
    double
    aggr_operator( double a,
                   double b ) const;


    // /< Empty hook
protected:
    /// @brief
    ///     Constructs a Metric object via a Cube connection.
    /// @param connection
    ///     Active Cube connection.
    /// @param cubeProxy
    ///     Cube proxy for internal cross-referencing.
    ///
    /// @note
    ///     This constructor is called by the factory method.
    ///
    PostDerivedMetric( Connection&      connection,
                       const CubeProxy& cubeProxy );




    virtual double
    get_sev_native(
        const cube::Cnode*,
        const CalculationFlavour,
        const cube::Sysres*,
        const CalculationFlavour
        )
    {
        assert( false ); // we never should be here
        return 0;
    };


    virtual double*
    get_sevs_native(
        const cube::Cnode*,
        const CalculationFlavour
        )
    {
        assert( false ); // we never should be here
        return NULL;
    };

    virtual
    void
    get_system_tree_sevs_native(
        const cube::Cnode*,
        const CalculationFlavour,
        std::vector< double >&,
        std::vector< double >&
        )
    {
        assert( false ); // we never should be here
        return;
    };
};
}
#endif
