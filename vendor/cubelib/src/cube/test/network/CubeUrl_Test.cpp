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
 *  @file    CubeUrl_Test.cpp
 *  @ingroup CUBE_lib.network.tests
 *  @brief   Unit tests for cube::Url
 **/
/*-------------------------------------------------------------------------*/


#include <config.h>

#include "CubeUrl.h"

#include <string>

#include <gtest/gtest.h>

#include "CubeError.h"


using namespace testing;
using namespace cube;

// Common test fixture
class UrlParser
    : public Test
{
    public:
        Url url;
};


TEST_F(UrlParser, defaultProtocolIsFile)
{
    ASSERT_EQ(url.getDefaultProtocol(), "file");
}

TEST_F(UrlParser, setsDefaultProtocolIfNoneSpecified)
{
    ASSERT_NO_THROW(url.parse("/"));
    ASSERT_EQ(url.getProtocol(), url.getDefaultProtocol());
}
TEST_F(UrlParser, hasDefaultPort3300)
{
    ASSERT_EQ(url.getDefaultPort(), 3300);
}

TEST_F(UrlParser, setsDefaultPortIfNoneSpecified)
{
    ASSERT_NO_THROW(url.parse("/"));
    ASSERT_EQ(url.getPort(), url.getDefaultPort());
}

TEST_F(UrlParser, treatsWordAsPathIfProtocolNotPresent)
{
    std::string singleTokenPath("path");

    ASSERT_NO_THROW(url.parse(singleTokenPath));
    ASSERT_EQ(url.getPath(), singleTokenPath);
}

TEST_F(UrlParser, treatsRelativePathAsPathIfProtocolNotPresent)
{
    std::string relativePath("relative/path/to/file");

    ASSERT_NO_THROW(url.parse(relativePath));
    ASSERT_EQ(url.getPath(), relativePath);
}

TEST_F(UrlParser, treatsAbsolutePathAsPathIfProtocolNotPresent)
{
    std::string absolutePath("/absolute/path/to/file");

    ASSERT_NO_THROW(url.parse(absolutePath));
    ASSERT_EQ(url.getPath(), absolutePath);
}

TEST_F(UrlParser, separatesProtocolAndPathIfFileProtocolPresent)
{
    std::string path("/path/to/file");

    ASSERT_NO_THROW(url.parse("file://" + path));
    EXPECT_EQ(url.getProtocol(), "file");
    EXPECT_EQ(url.getPath(), path);
}

TEST_F(UrlParser, setsHostToFirstTokenAfterProtocolWithoutPort)
{
    ASSERT_NO_THROW(url.parse("cube://host.domain/"));
    ASSERT_EQ(url.getHost(), "host.domain");
}

TEST_F(UrlParser, setsPathToRemainingTokensAfterHostWithoutPort)
{
    ASSERT_NO_THROW(url.parse("cube://host/relative/path"));
    ASSERT_EQ(url.getPath(), "relative/path");
}

TEST_F(UrlParser, setsHostToFirstTokenAfterProtocolWithPort)
{
    ASSERT_NO_THROW(url.parse("cube://remote:3300/"));
    ASSERT_EQ(url.getHost(), "remote");
}

TEST_F(UrlParser, stetsHostAndPortIfSpecifiedExlicitly)
{
    ASSERT_NO_THROW(url.parse("cube://remote:1234"));
    EXPECT_EQ(url.getHost(), "remote");
    ASSERT_EQ(url.getPort(), 1234);
}

TEST_F(UrlParser, setsPortAndPathIfSpecifiedExplicitly)
{
    ASSERT_NO_THROW(url.parse("cube://remote:4321/path"));
    EXPECT_EQ(url.getPort(), 4321);
    ASSERT_EQ(url.getPath(), "path");
}

TEST_F(UrlParser, recognizesAbsolutePathInPresenseOfHost)
{
    std::string absolutePath("/absolute/path");
    ASSERT_NO_THROW(url.parse("cube://remote/" + absolutePath));
    ASSERT_EQ(url.getPath(), absolutePath);
}

TEST(UrlPrinter, insertsFileProtocolIfNoneSpecified)
{
    Url url("relative/path/to/file");
    ASSERT_EQ(url.toString(), "file://relative/path/to/file");
}
