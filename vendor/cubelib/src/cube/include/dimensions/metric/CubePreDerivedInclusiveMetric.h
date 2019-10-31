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
 * \file CubePreDerivedInclusiveMetric.h
 * \brief Defines a metric, which calculates its value using user defined expression in CubePL"
 */
#ifndef CUBE_DERIVED_INCLUSIVE_METRIC_H
#define CUBE_DERIVED_INCLUSIVE_METRIC_H

#include "CubeMetric.h"
#include "CubeValues.h"
#include "CubeGeneralEvaluation.h"
#include "CubeInclusiveMetricBuildInType.h"
/*
 *----------------------------------------------------------------------------
 *
 * class Metric
 *
 *******************************----------------------------------------------------------------------------
 */

namespace cube
{
/*  class Cnode;
   class Thread;*/

/**
 * Metric has a treelike structure and is a kind of Vertex.
 */

class PreDerivedInclusiveMetric : public InclusiveBuildInTypeMetric<double>
{
public:

    PreDerivedInclusiveMetric( const std::string& disp_name,
                               const std::string& uniq_name,
                               const std::string& dtype,
                               const std::string& uom,
                               const std::string& val,
                               const std::string& url,
                               const std::string& descr,
                               FileFinder*        ffinder,
                               Metric*            parent,
                               uint32_t           id                     = 0,
                               const std::string& _expression            = "",
                               const std::string& _expression_init       = "",
                               const std::string& _expression_aggr_plus  = "",
                               const std::string& _expression_aggr_minus = "",
                               const std::string& _expression_aggr_aggr  = "",
                               const bool         threadwise             = true,
                               VizTypeOfMetric    is_ghost               = CUBE_METRIC_NORMAL
                               )
        : InclusiveBuildInTypeMetric<double>( disp_name, uniq_name, dtype, uom, val, url, descr, ffinder, parent, id, _expression, _expression_init, _expression_aggr_plus, _expression_aggr_minus, _expression_aggr_aggr, threadwise,  is_ghost )
    {
        adv_sev_mat = NULL;
        initialized = false; // with creation initialisation is done
        cache_selection( ncid, ntid, CUBE_METRIC_EXCLUSIVE );
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
    ~PreDerivedInclusiveMetric();

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
    };                                                                                                             // /< Creates apropriate enumeration of the calltree. Exclusive metric need deep search, Inclusive -> wide search enumeration.

    virtual TypeOfMetric
    get_type_of_metric() const
    {
        return CUBE_METRIC_PREDERIVED_INCLUSIVE;
    };
    virtual std::string
    get_metric_kind() const
    {
        return "PREDERIVED_INCLUSIVE";
    };


    virtual
    void
    initialize( void );



    virtual IndexFormat
    get_index_format()
    {
        return CUBE_INDEX_FORMAT_SPARSE;
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

protected:
    // /< Empty hook
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
    PreDerivedInclusiveMetric( Connection&      connection,
                               const CubeProxy& cubeProxy );

    // ----------------- calculations of poitlike parameters

    // returns an element corresponsing to cnode and location in not clustered case
    virtual
    inline
    double
    get_sev_elementary( const Cnode*    cnode,
                        const Location* loc )
    {
        pre_calculation_preparation( cnode, CUBE_CALCULATE_INCLUSIVE, loc, CUBE_CALCULATE_EXCLUSIVE );
        double to_return;
        if ( !cnode->is_clustered() )
        {
            to_return =  evaluation->eval( cnode, CUBE_CALCULATE_INCLUSIVE, loc, CUBE_CALCULATE_EXCLUSIVE );
        }
        else
        {
            Process*           _proc        = loc->get_parent();
            int64_t            process_rank = _proc->get_rank();
            const cube::Cnode* _mapped      =  cnode->get_remapping_cnode( process_rank  );
            to_return = ( _mapped == NULL ) ? static_cast<double>( 0. ) :
                        (
                evaluation->eval( _mapped, CUBE_CALCULATE_INCLUSIVE, loc, CUBE_CALCULATE_EXCLUSIVE ) );

            int64_t _norm = cnode->get_cluster_normalization( process_rank );
            if ( _norm > 0 )
            {
                to_return /= ( ( uint64_t )_norm );
            }
        }
        post_calculation_cleanup();
        return to_return;
    }
};
}
#endif
