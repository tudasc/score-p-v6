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
 * \file CubeExclusiveMetric.h
 * \brief Defines a metric, whick collects exclusive values.By calling "get_excl_sev..." it returns the saved value, by calling "get_incl_sev..." it calculates it via "excl_sev  + Sum (exc_sev of all children)"
 */
#ifndef CUBE_EXCLUSIVE_METRIC_H
#define CUBE_EXCLUSIVE_METRIC_H


#include <iosfwd>
#include <map>

// #include "Matrix.h"
#include "CubeVertex.h"
#include "CubeCnode.h"
#include "CubeThread.h"
#include "CubeMetricValueType.h"
#include "CubeAdvMatrix.h"
#include "CubeRowWiseMatrix.h"
// #include "CubeMemoryMatrix.h"
#include "CubeIDdeliverer.h"
#include "CubeDeepSearchEnumerator.h"


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

class ExclusiveMetric : public ValueMetric
{
public:

    ExclusiveMetric( const std::string& disp_name,
                     const std::string& uniq_name,
                     const std::string& dtype,
                     const std::string& uom,
                     const std::string& val,
                     const std::string& url,
                     const std::string& descr,
                     FileFinder*        ffinder,
                     Metric*            parent,
                     uint32_t           id = 0,
                     VizTypeOfMetric    is_ghost = CUBE_METRIC_NORMAL )
        : ValueMetric( disp_name, uniq_name, dtype, uom, val, url, descr, ffinder, parent, id, "", "", "", "", "", true, is_ghost )
    {
    }

    /// @brief
    ///     Factory method to create an intrinsic-type inclusive metric via a Cube connection.
    /// @param connection
    ///     Active Cube connection.
    /// @param cubeProxy
    ///     Cube proxy for internal cross-referencing.
    /// @return
    ///     New metric.
    ///
    static Serializable*
    create( Connection&      connection,
            const CubeProxy& cubeProxy );

    virtual
    ~ExclusiveMetric();

    /// @copydoc cube::Serializable::get_serialization_key
    ///
    virtual std::string
    get_serialization_key() const;

    /// @copydoc cube::Serializable::get_serialization_key
    ///
    static std::string
    get_static_serialization_key();

    virtual row_of_objects_t*
    create_calltree_id_maps( IDdeliverer*,
                             Cnode*,
                             row_of_objects_t*  );                               // /< Creates enumeration of Callpath-Tree according the "deep search" prescription. It is optimal for the calculation of inclusive values in exclusive metric.

    virtual TypeOfMetric
    get_type_of_metric() const
    {
        return CUBE_METRIC_EXCLUSIVE;
    };
    virtual std::string
    get_metric_kind() const
    {
        return "EXCLUSIVE";
    };

    virtual IndexFormat
    get_index_format()
    {
        return CUBE_INDEX_FORMAT_SPARSE;
    };



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
    ExclusiveMetric( Connection&      connection,
                     const CubeProxy& cubeProxy );

    virtual Value*
    get_sev_native(
        const cube::Cnode*,
        const CalculationFlavour cnf,
        const cube::Sysres* = NULL,
        const CalculationFlavour sf = CUBE_CALCULATE_NONE
        );

private:

    Value*
    get_sev_aggregated( const cube::Cnode*       cnode,
                        const CalculationFlavour cnf );

    Value*
    get_sev_pointlike( const Cnode*             cnode,
                       const CalculationFlavour cnf,
                       const Sysres*            sys,
                       const CalculationFlavour sf );
};
}
#endif
