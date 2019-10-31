/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016                                                     **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/*-------------------------------------------------------------------------*/
/**
 *  @file    cube_selftest_CubeProxy
 *  @ingroup CUBE_lib.tests
 *  @brief   Integration test suite for CubeProxy interface
 **/
/*-------------------------------------------------------------------------*/

#include <cstdlib>
#include <iostream>
#include <string>

#include <gtest/gtest.h>

#include "CubeCnode.h"
#include "CubeError.h"
#include "CubeIdIndexMap.h"
#include "CubeMetric.h"
#include "CubeProxy.h"
#include "CubeServices.h"
#include "CubeSysres.h"
#include "CubeTypes.h"
#include "CubeUrl.h"

using namespace cube;
using namespace std;
using namespace::testing;

namespace cube
{
namespace testing
{
extern string url;
}
}

class TestProxy
    : public Test
{
    protected:
        virtual void
        SetUp()
        {
            if (getenv("CUBE_TEST_URL"))
            {
                url = Url(services::remove_dotted_path(getenv("CUBE_TEST_URL")));
            }
            else
            {
                url = services::remove_dotted_path(cube::testing::url);
            }

            try {
                proxy = CubeProxy::create(url.toString());
                proxy->openReport();
            }
            catch (const std::exception& e)
            {
                cerr << "Caught exception while opening report on URL: "
                     << url.toString() << endl;
            }

            inclusiveTimeMetric.push_back(make_pair(proxy->getMetric("time"),
                                                    CUBE_CALCULATE_INCLUSIVE));

            exclusiveTimeMetric.push_back(make_pair(proxy->getMetric("time"),
                                                    CUBE_CALCULATE_EXCLUSIVE));

            for (vector< Cnode* >::const_iterator it =
                     proxy->getRootCnodes().begin();
                 it != proxy->getRootCnodes().end(); ++it)
            {
                inclusiveRootCnodes.push_back(make_pair(*it,
                                                        CUBE_CALCULATE_INCLUSIVE));
            }
            for (vector< SystemTreeNode* >::const_iterator it =
                     proxy->getRootSystemTreeNodes().begin();
                 it != proxy->getRootSystemTreeNodes().end(); ++it)
            {
                inclusiveRootSysresources.push_back(make_pair(*it,
                                                              CUBE_CALCULATE_INCLUSIVE));
            }
            depthZero = 0;
            depthOne  = 1;
        }

        virtual void
        TearDown()
        {
            if (proxy->isInitialized())
            {
                proxy->closeReport();
            }
            if (proxy)
            {
                delete proxy;
            }
        }

        CubeProxy*           proxy;
        Url                  url;
        list_of_metrics      inclusiveTimeMetric;
        list_of_metrics      exclusiveTimeMetric;
        list_of_cnodes       inclusiveRootCnodes;
        list_of_sysresources inclusiveRootSysresources;
        value_container      inclusiveValues;
        value_container      exclusiveValues;
        IdIndexMap           idIndexMap;
        size_t               depthZero;
        size_t               depthOne;
};


TEST(Proxy, throwsExceptionIfFileNotFound)
{
    CubeProxy* proxy = CubeProxy::create("");

    ASSERT_THROW(proxy->openReport(), exception);
}

TEST_F(TestProxy, isInitializedAfterOpen)
{
    ASSERT_EQ(true, proxy->isInitialized());
}

TEST_F(TestProxy, isUninitializedAfterClosing)
{
    proxy->closeReport();

    ASSERT_EQ(false, proxy->isInitialized());
}

TEST_F(TestProxy, reportsCorrectCubename)
{
    ASSERT_EQ(url.getPath(), proxy->getAttribute("cubename"));
}

TEST_F(TestProxy, reportsCorrectMetricTitle)
{
    // The tested string is specific to the tested Cube file
    ASSERT_EQ("Generated Metrics Title",
              proxy->getAttribute("metrictree title"));
}

TEST_F(TestProxy, reportsCorrectCalltreeTitle)
{
    // The tested string is specific to the tested Cube file
    ASSERT_EQ("Generated Calltree Title",
              proxy->getAttribute("calltree title"));
}

TEST_F(TestProxy, reportsCorrectSystemTreeTitle)
{
    // The tested string is specific to the tested Cube file
    ASSERT_EQ("Generated Systemtree Title",
              proxy->getAttribute("systemtree title"));
}

TEST_F(TestProxy, returnsMetricByUniqName)
{
    ASSERT_NE(static_cast< Metric* >(0), proxy->getMetric("visits"));
}

TEST_F(TestProxy, returnsMetricsVectorOfCorrectSize)
{
    const vector< Metric* >& metrics = proxy->getMetrics();

    ASSERT_EQ(2, metrics.size());
}

TEST_F(TestProxy, returnsRootMetricsVectorOfCorrectSize)
{
    const vector< Metric* >& root_metrics = proxy->getRootMetrics();

    ASSERT_EQ(2, root_metrics.size());
}

TEST_F(TestProxy, returnsGhostMetricsVectorOfCorrectSize)
{
    // TODO provide Ghost metrics in Cube archive
    const vector< Metric* > ghost_metrics = proxy->getGhostMetrics();

    ASSERT_EQ(0, ghost_metrics.size());
}

TEST_F(TestProxy, returnsCnodeVector)
{
    const vector< Cnode* > cnodes = proxy->getCnodes();

    ASSERT_EQ(236, cnodes.size());
}

TEST_F(TestProxy, returnsRootCnodeVectorOfCorrectSize)
{
    const vector< Cnode* > root_cnodes = proxy->getRootCnodes();

    ASSERT_EQ(8, root_cnodes.size());
}

TEST_F(TestProxy, returnsRegionVectorOfCorrectSize)
{
    const vector< Region* > regions = proxy->getRegions();

    ASSERT_EQ(236, regions.size());
}

TEST_F(TestProxy, returnsLocationVectorOfCorrectSize)
{
    const vector< Location* > locations = proxy->getLocations();

    ASSERT_EQ(1, locations.size());
}

TEST_F(TestProxy, returnsLocationGroupVectorOfCorrectSize)
{
    const vector< LocationGroup* > location_groups =
        proxy->getLocationGroups();

    ASSERT_EQ(1, location_groups.size());
}

TEST_F(TestProxy, returnsSystemTreeNodeVectorOfCorrectSize)
{
    const vector< SystemTreeNode* > system_tree_nodes =
        proxy->getSystemTreeNodes();

    ASSERT_EQ(1, system_tree_nodes.size());
}

TEST_F(TestProxy, returnsSystemResourceVectorOfCorrectSize)
{
    const vector< Sysres* > system_resources =
        proxy->getSystemResources();

    ASSERT_EQ(3, system_resources.size());
}

TEST_F(TestProxy, returnsEmptyStringForUnknownAttributes)
{
    string unknownKey("unknownKey");
    string emptyString("");

    ASSERT_EQ(emptyString, proxy->getAttribute(unknownKey));
}

TEST_F(TestProxy, returnsAttributeForKnownKey)
{
    string cubeNameKey("cubename");
    string cubeNameValue(url.getPath());

    ASSERT_EQ(cubeNameValue, proxy->getAttribute(cubeNameKey));
}

TEST_F(TestProxy, allowsDefinitionOfAttributes)
{
    string newKey("newKey");
    string newValue("newValue");
    proxy->defineAttribute(newKey, newValue);

    ASSERT_EQ(newValue, proxy->getAttribute(newKey));
}

TEST_F(TestProxy, allowsDefinitionOfMirrors)
{
    string newMirror("http://server/path/to/documentation");
    proxy->defineMirror(newMirror);
    const vector< string >& mirrors = proxy->getMirrors();

    ASSERT_NE(mirrors.end(),
              find(mirrors.begin(), mirrors.end(), newMirror));
}


TEST_F(TestProxy, retrievesLeftOrderMetricTreeValues)
{
    proxy->getMetricTreeValues(inclusiveRootCnodes,
                               inclusiveRootSysresources,
                               inclusiveValues,
                               exclusiveValues);

    // TODO adapt expected value once Cube file is remapped
    ASSERT_DOUBLE_EQ(228, inclusiveValues[0]->getDouble());
    ASSERT_DOUBLE_EQ(228, exclusiveValues[0]->getDouble());
}

TEST_F(TestProxy, retrievesMiddleOrderMetricTreeValuesForCnode)
{
    list_of_cnodes exclusiveCnodeMain;
    exclusiveCnodeMain.push_back(make_pair(proxy->getCnodes()[228],
                                           CUBE_CALCULATE_EXCLUSIVE));

    proxy->getMetricTreeValues(exclusiveCnodeMain,
                               inclusiveRootSysresources,
                               inclusiveValues,
                               exclusiveValues);

    // TODO adapt expected value once Cube file is remapped
    ASSERT_DOUBLE_EQ(1, inclusiveValues[0]->getDouble());
    ASSERT_DOUBLE_EQ(1, exclusiveValues[0]->getDouble());
}

TEST_F(TestProxy, retrievesRightOrderMetricTreeValues)
{
    list_of_cnodes exclusiveCnodeMain;
    exclusiveCnodeMain.push_back(make_pair(proxy->getCnodes()[228],
                                           CUBE_CALCULATE_EXCLUSIVE));
    list_of_sysresources inclusiveSysresZero;
    inclusiveSysresZero.push_back(make_pair(static_cast< Sysres* >(proxy->
                                                                       getSystemResources()
                                                                   [0]),
                                            CUBE_CALCULATE_INCLUSIVE));

    proxy->getMetricTreeValues(exclusiveCnodeMain,
                               inclusiveSysresZero,
                               inclusiveValues,
                               exclusiveValues);

    // TODO adapt expected value once Cube file is remapped
    ASSERT_DOUBLE_EQ(1, inclusiveValues[0]->getDouble());
    ASSERT_DOUBLE_EQ(1, exclusiveValues[0]->getDouble());
}


TEST_F(TestProxy, retrievesParentOnlyMetricSubtreeValues)
{
    proxy->getMetricSubtreeValues(inclusiveRootCnodes,
                                  inclusiveRootSysresources,
                                  *(proxy->getMetrics()[0]),
                                  depthZero,
                                  idIndexMap,
                                  &inclusiveValues,
                                  &exclusiveValues);

    ASSERT_EQ(1, idIndexMap.size());
}

TEST_F(TestProxy, retrievesParentAndChildrenMetricSubtreeValues)
{
    proxy->getMetricSubtreeValues(inclusiveRootCnodes,
                                  inclusiveRootSysresources,
                                  *(proxy->getMetrics()[0]),
                                  depthOne,
                                  idIndexMap,
                                  &inclusiveValues,
                                  &exclusiveValues);

    // TODO adapt expected value once Cube file is remapped
    ASSERT_EQ(1, idIndexMap.size());
}

TEST_F(TestProxy, retrievesLeftOrderMetricSubtreeValues)
{
    proxy->getMetricSubtreeValues(inclusiveRootCnodes,
                                  inclusiveRootSysresources,
                                  *(proxy->getMetrics()[0]),
                                  CUBE_PROXY_FULL_SUBTREE,
                                  idIndexMap,
                                  &inclusiveValues,
                                  &exclusiveValues);

    // TODO adapt expected value once Cube file is remapped
    ASSERT_DOUBLE_EQ(228, inclusiveValues[0]->getDouble());
    ASSERT_DOUBLE_EQ(228, exclusiveValues[0]->getDouble());
}

TEST_F(TestProxy, retrievesMiddleOrderMetricSubtreeValuesForCnode)
{
    list_of_cnodes exclusiveCnodeMain;
    exclusiveCnodeMain.push_back(make_pair(proxy->getCnodes()[228],
                                           CUBE_CALCULATE_EXCLUSIVE));

    proxy->getMetricSubtreeValues(exclusiveCnodeMain,
                                  inclusiveRootSysresources,
                                  *(proxy->getMetrics()[0]),
                                  CUBE_PROXY_FULL_SUBTREE,
                                  idIndexMap,
                                  &inclusiveValues,
                                  &exclusiveValues);

    // TODO adapt expected value once Cube file is remapped
    ASSERT_DOUBLE_EQ(1, inclusiveValues[0]->getDouble());
    ASSERT_DOUBLE_EQ(1, exclusiveValues[0]->getDouble());
}

TEST_F(TestProxy, retrievesRightOrderMetricSubtreeValues)
{
    list_of_cnodes exclusiveCnodeMain;
    exclusiveCnodeMain.push_back(make_pair(proxy->getCnodes()[228],
                                           CUBE_CALCULATE_EXCLUSIVE));
    list_of_sysresources inclusiveSysresZero;
    inclusiveSysresZero.push_back(make_pair(static_cast< Sysres* >(proxy->
                                                                       getSystemResources()
                                                                   [0]),
                                            CUBE_CALCULATE_INCLUSIVE));

    proxy->getMetricSubtreeValues(exclusiveCnodeMain,
                                  inclusiveSysresZero,
                                  *(proxy->getMetrics()[0]),
                                  CUBE_PROXY_FULL_SUBTREE,
                                  idIndexMap,
                                  &inclusiveValues,
                                  &exclusiveValues);

    // TODO adapt expected value once Cube file is remapped
    ASSERT_DOUBLE_EQ(1, inclusiveValues[0]->getDouble());
    ASSERT_DOUBLE_EQ(1, exclusiveValues[0]->getDouble());
}

TEST_F(TestProxy, retrievesMiddleOrderMetricSubtreeValuesForRegion)
{
    list_of_regions exclusiveRegionMain;
    exclusiveRegionMain.push_back(make_pair(proxy->getRegions()[228],
                                            CUBE_CALCULATE_EXCLUSIVE));

    proxy->getMetricSubtreeValues(exclusiveRegionMain,
                                  inclusiveRootSysresources,
                                  *(proxy->getMetrics()[0]),
                                  CUBE_PROXY_FULL_SUBTREE,
                                  idIndexMap,
                                  &inclusiveValues,
                                  &exclusiveValues);

    // TODO adapt expected value once Cube file is remapped
    ASSERT_DOUBLE_EQ(1, inclusiveValues[0]->getDouble());
    ASSERT_DOUBLE_EQ(1, exclusiveValues[0]->getDouble());
}

TEST_F(TestProxy, retrieveInclusiveOnlyMetricSubtree)
{
    proxy->getMetricSubtreeValues(inclusiveRootCnodes,
                                  inclusiveRootSysresources,
                                  *(proxy->getMetrics()[0]),
                                  CUBE_PROXY_FULL_SUBTREE,
                                  idIndexMap,
                                  &inclusiveValues,
                                  CUBE_PROXY_VALUES_IGNORE);

    // TODO adapt expected value once Cube file is remapped
    ASSERT_DOUBLE_EQ(228, inclusiveValues[0]->getDouble());
}

TEST_F(TestProxy, retrieveExclusiveOnlyMetricSubtree)
{
    proxy->getMetricSubtreeValues(inclusiveRootCnodes,
                                  inclusiveRootSysresources,
                                  *(proxy->getMetrics()[0]),
                                  CUBE_PROXY_FULL_SUBTREE,
                                  idIndexMap,
                                  CUBE_PROXY_VALUES_IGNORE,
                                  &exclusiveValues);

    // TODO adapt expected value once Cube file is remapped
    ASSERT_DOUBLE_EQ(228, exclusiveValues[0]->getDouble());
}

TEST_F(TestProxy, retrievesParentOnlySubCallTreeValues)
{
    proxy->getCallpathSubtreeValues(inclusiveTimeMetric,
                                    inclusiveRootSysresources,
                                    *(proxy->getCnodes()[0]),
                                    depthZero,
                                    idIndexMap,
                                    &inclusiveValues,
                                    &exclusiveValues);

    ASSERT_EQ(1, idIndexMap.size());
}

TEST_F(TestProxy, retrievesParentAndChildrenSubCallTreeValues)
{
    proxy->getCallpathSubtreeValues(inclusiveTimeMetric,
                                    inclusiveRootSysresources,
                                    *(proxy->getCnodes()[0]),
                                    depthOne,
                                    idIndexMap,
                                    &inclusiveValues,
                                    &exclusiveValues);

    // TODO adapt expected value once Cube file is remapped
    // currently it is the MPI call tree with 204 children.
    ASSERT_EQ(205, idIndexMap.size());
}

TEST_F(TestProxy, retrievesMiddleOrderSubCallTreeValuesForCnode)
{
    list_of_cnodes exclusiveCnodeMain;
    exclusiveCnodeMain.push_back(make_pair(proxy->getCnodes()[228],
                                           CUBE_CALCULATE_EXCLUSIVE));

    proxy->getCallpathSubtreeValues(inclusiveTimeMetric,
                                    inclusiveRootSysresources,
                                    *(proxy->getCnodes()[0]),
                                    CUBE_PROXY_FULL_SUBTREE,
                                    idIndexMap,
                                    &inclusiveValues,
                                    &exclusiveValues);

    // TODO adapt expected value once Cube file is remapped
    ASSERT_DOUBLE_EQ(204, inclusiveValues[0]->getDouble());
    ASSERT_DOUBLE_EQ(0, exclusiveValues[0]->getDouble());
}

TEST_F(TestProxy, retrievesRightOrderSubCallTreeValues)
{
    list_of_cnodes exclusiveCnodeMain;
    exclusiveCnodeMain.push_back(make_pair(proxy->getCnodes()[228],
                                           CUBE_CALCULATE_EXCLUSIVE));
    list_of_sysresources inclusiveSysresZero;
    inclusiveSysresZero.push_back(make_pair(static_cast< Sysres* >(proxy->
                                                                       getSystemResources()
                                                                   [0]),
                                            CUBE_CALCULATE_INCLUSIVE));

    proxy->getCallpathSubtreeValues(exclusiveTimeMetric,
                                    inclusiveSysresZero,
                                    *(proxy->getCnodes()[0]),
                                    CUBE_PROXY_FULL_SUBTREE,
                                    idIndexMap,
                                    &inclusiveValues,
                                    &exclusiveValues);

    // TODO adapt expected value once Cube file is remapped
    ASSERT_DOUBLE_EQ(204, inclusiveValues[0]->getDouble());
    ASSERT_DOUBLE_EQ(0, exclusiveValues[0]->getDouble());
}

TEST_F(TestProxy, retrieveInclusiveOnlySubCallTree)
{
    proxy->getCallpathSubtreeValues(inclusiveTimeMetric,
                                    inclusiveRootSysresources,
                                    *(proxy->getCnodes()[0]),
                                    CUBE_PROXY_FULL_SUBTREE,
                                    idIndexMap,
                                    &inclusiveValues,
                                    CUBE_PROXY_VALUES_IGNORE);

    // TODO adapt expected value once Cube file is remapped
    ASSERT_DOUBLE_EQ(204, inclusiveValues[0]->getDouble());
    for (size_t i = 1; i < idIndexMap.size(); ++i)
    {
        ASSERT_DOUBLE_EQ(1, inclusiveValues[i]->getDouble());
    }
}

TEST_F(TestProxy, retrieveExclusiveOnlySubCallTree)
{
    proxy->getCallpathSubtreeValues(inclusiveTimeMetric,
                                    inclusiveRootSysresources,
                                    *(proxy->getCnodes()[0]),
                                    CUBE_PROXY_FULL_SUBTREE,
                                    idIndexMap,
                                    CUBE_PROXY_VALUES_IGNORE,
                                    &exclusiveValues);

    // TODO adapt expected value once Cube file is remapped
    ASSERT_DOUBLE_EQ(0, exclusiveValues[0]->getDouble());
    for (size_t i = 1; i < idIndexMap.size(); ++i)
    {
        ASSERT_DOUBLE_EQ(1, exclusiveValues[i]->getDouble());
    }
}
