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



/**
 * \file
 * \brief Defines a metric class, which uses build in type as a data type
 *
 */
#ifndef CUBE_VALUE_METRIC_H
#define CUBE_VALUE_METRIC_H


#include <iosfwd>
#include <map>

// #include "CubeVertex.h"
#include "CubeTypes.h"
// #include "CubeCnode.h"
#include "CubeSystemTreeNode.h"
#include "CubeLocationGroup.h"
#include "CubeLocation.h"
#include "CubeSimpleCache.h"
#include "CubeMetric.h"
#include "CubeRowWiseMatrix.h"
#include "CubeServices.h"

namespace cube
{
class Connection;
class CubeProxy;

class ValueMetric : public Metric // metrics, where data type is defined via general object Value*
{
public:

    ValueMetric( const std::string& disp_name,
                 const std::string& uniq_name,
                 const std::string& dtype,
                 const std::string& uom,
                 const std::string& val,
                 const std::string& url,
                 const std::string& descr,
                 FileFinder*        ffinder,
                 Metric*            parent,
                 uint32_t           id = 0,
                 const std::string& cubepl_expression = "",
                 const std::string& cubepl_init_expression = "",
                 const std::string& cubepl_aggr_plus_expression = "",
                 const std::string& cubepl_aggr_minus_expression = "",
                 const std::string& cubepl_aggr_aggr_expression = "",
                 bool               row_wise = true,
                 VizTypeOfMetric    is_ghost = CUBE_METRIC_NORMAL
                 )
        :
        Metric( disp_name,
                uniq_name,
                dtype,
                uom,
                val,
                url,
                descr,
                ffinder,
                parent,
                id,
                cubepl_expression,
                cubepl_init_expression,
                cubepl_aggr_plus_expression,
                cubepl_aggr_minus_expression,
                cubepl_aggr_aggr_expression,
                row_wise,
                is_ghost
                )
    {
    }

    virtual
    ~ValueMetric()
    {
    };


    // ----------- get incl/ecl severities ----------------------
    virtual
    inline
    Value*
    get_sev(
        const list_of_cnodes&       cnodes,
        const list_of_sysresources& sysres
        )
    {
        return get_sev_native( cnodes, sysres );
    }

    // -----------------row wise ----------------------------------------
    virtual
    inline
    Value**
    get_sevs(
        const list_of_cnodes& cnodes
        )
    {
        return get_sevs_native( cnodes );
    }

    // --- massive calculation of a system tree ---------------------
    virtual
    inline
    void
    get_system_tree_sevs( const list_of_cnodes&  cnodes,
                          std::vector< Value* >& inclusive_values,
                          std::vector< Value* >& exclusive_values
                          )
    {
        get_system_tree_sevs_native( cnodes, inclusive_values, exclusive_values );
    }



    virtual
    void
    get_system_tree_sevs( const list_of_cnodes&  cnodes,
                          std::vector< double >& inclusive_values,
                          std::vector< double >& exclusive_values
                          );



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
    ValueMetric( Connection&      connection,
                 const CubeProxy& cubeProxy )
        : Metric( connection, cubeProxy )
    {
    }

    // ----------------- calculations of poitlike parameters

    // returns an element corresponsing to cnode and location in not clustered case
    virtual
    inline
    Value*
    get_sev_elementary( const Cnode*    cnode,
                        const Location* loc )
    {
        if ( !cnode->is_clustered() )
        {
            return adv_sev_mat->getValue( calltree_local_ids[ cnode->get_remapping_cnode()->get_id() ], loc->get_id() );
        }
        else
        {
            LocationGroup*     _lg     = loc->get_parent();
            int64_t            lg_rank = _lg->get_rank();
            const cube::Cnode* _mapped =  cnode->get_remapping_cnode( lg_rank  );
            Value*             _v      = ( _mapped == NULL ) ? metric_value->clone() : ( adv_sev_mat->getValue( calltree_local_ids[ _mapped->get_id() ], loc->get_id() ) );
            int64_t            _norm   = cnode->get_cluster_normalization( lg_rank );
            if ( _norm > 0 )
            {
                _v->normalizeWithClusterCount( ( uint64_t )_norm );
            }
            return _v;
        }
    }




    virtual Value*
    get_sev_native(
        const list_of_cnodes&       cnodes,
        const list_of_sysresources& sysres
        );

    virtual Value*
    get_sev_native(
        const cube::Cnode*,
        const CalculationFlavour cnf,
        const cube::Sysres* = NULL,
        const CalculationFlavour sf = CUBE_CALCULATE_NONE
        ) = 0;




    // -----------------row wise ----------------------------------------
    virtual Value**
    get_sevs_native(
        const list_of_cnodes& cnodes
        );

    virtual Value**
    get_sevs_native(
        const cube::Cnode*,
        const CalculationFlavour cnf
        );

    //  --massive calculation of a system tree
    void
    get_system_tree_sevs_native( const list_of_cnodes&  cnodes,
                                 std::vector< Value* >& inclusive_values,
                                 std::vector< Value* >& exclusive_values
                                 );

    virtual
    void
    get_system_tree_sevs_native(
        const cube::Cnode*,
        const CalculationFlavour cnf,
        std::vector< Value* >&   inclusive_values,
        std::vector< Value* >&   exclusive_values
        );
};
};
#endif
