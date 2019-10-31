/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016                                                     **
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
 *  @ingroup CUBE_lib.network
 *  @brief   Definition of the class cube::SerializablesFactory.
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeSerializablesFactory.h"

#include <inttypes.h>

#include "CubeConnection.h"

// These includes are needed for registering the factory methods.
#include "CubeCartesian.h"
#include "CubeCnode.h"
#include "CubeCustomPreDerivedExclusiveMetric.h"
#include "CubeCustomPreDerivedInclusiveMetric.h"
#include "CubeExclusiveMetric.h"
#include "CubeExclusiveMetricBuildInType.h"
#include "CubeInclusiveMetric.h"
#include "CubeInclusiveMetricBuildInType.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubePostDerivedMetric.h"
#include "CubePreDerivedExclusiveMetric.h"
#include "CubePreDerivedInclusiveMetric.h"
#include "CubeRegion.h"
#include "CubeSystemTreeNode.h"

using namespace std;

namespace cube
{
namespace detail
{
template< class T >
void
registerClassFactory(SerializablesFactory& factory)
{
    factory.registerCallback(T::get_static_serialization_key(), T::create);
}
}    // namespace detail

Serializable*
SerializablesFactory::create(Connection&      connection,
                             const CubeProxy& cubeProxy) const
{
    string                      serialization_key = connection.get< string >();
    container_t::const_iterator func              = mRegistry.find(
        serialization_key);
    if (func == mRegistry.end())
    {
        throw NetworkError("Use of unregistered key: " + serialization_key);
    }

    return (func->second(connection, cubeProxy));
}


bool
SerializablesFactory::registerCallback(const string& key,
                                       callback_t    callback)
{
    cerr << "Registered factory method for key: " << key << endl;

    return mRegistry.insert(make_pair(key, callback)).second;
}


SerializablesFactory::SerializablesFactory()
{
    detail::registerClassFactory< Cartesian >(*this);
    detail::registerClassFactory< Region >(*this);
    detail::registerClassFactory< Cnode >(*this);
    detail::registerClassFactory< SystemTreeNode >(*this);
    detail::registerClassFactory< LocationGroup >(*this);
    detail::registerClassFactory< Location >(*this);
    detail::registerClassFactory< CustomPreDerivedExclusiveMetric >(*this);
    detail::registerClassFactory< CustomPreDerivedInclusiveMetric >(*this);
    detail::registerClassFactory< ExclusiveMetric >(*this);
    detail::registerClassFactory< ExclusiveBuildInTypeMetric< double > >(*this);
    detail::registerClassFactory< ExclusiveBuildInTypeMetric< int8_t > >(*this);
    detail::registerClassFactory< ExclusiveBuildInTypeMetric< uint8_t > >(*this);
    detail::registerClassFactory< ExclusiveBuildInTypeMetric< int16_t > >(*this);
    detail::registerClassFactory< ExclusiveBuildInTypeMetric< uint16_t > >(*this);
    detail::registerClassFactory< ExclusiveBuildInTypeMetric< int32_t > >(*this);
    detail::registerClassFactory< ExclusiveBuildInTypeMetric< uint32_t > >(*this);
    detail::registerClassFactory< ExclusiveBuildInTypeMetric< int64_t > >(*this);
    detail::registerClassFactory< ExclusiveBuildInTypeMetric< uint64_t > >(*this);
    detail::registerClassFactory< InclusiveMetric >(*this);
    detail::registerClassFactory< InclusiveBuildInTypeMetric< double > >(*this);
    detail::registerClassFactory< InclusiveBuildInTypeMetric< int8_t > >(*this);
    detail::registerClassFactory< InclusiveBuildInTypeMetric< uint8_t > >(*this);
    detail::registerClassFactory< InclusiveBuildInTypeMetric< int16_t > >(*this);
    detail::registerClassFactory< InclusiveBuildInTypeMetric< uint16_t > >(*this);
    detail::registerClassFactory< InclusiveBuildInTypeMetric< int32_t > >(*this);
    detail::registerClassFactory< InclusiveBuildInTypeMetric< uint32_t > >(*this);
    detail::registerClassFactory< InclusiveBuildInTypeMetric< int64_t > >(*this);
    detail::registerClassFactory< InclusiveBuildInTypeMetric< uint64_t > >(*this);
    detail::registerClassFactory< PostDerivedMetric >(*this);
    detail::registerClassFactory< PreDerivedExclusiveMetric >(*this);
    detail::registerClassFactory< PreDerivedInclusiveMetric >(*this);
}


bool
SerializablesFactory::unregisterCallback(const string& key)
{
    return (mRegistry.erase(key) == 1);
}
}    /* namespace cube */
