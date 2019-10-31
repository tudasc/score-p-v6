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
 *  @file    CubeError_Test.cpp
 *  @ingroup CUBE_lib.service.test
 *  @brief   Unit tests for
 **/
/*-------------------------------------------------------------------------*/


#include "config.h"

#include <string>

#include <gtest/gtest.h>

#include "CubeError.h"

using namespace cube;
using namespace std;
using namespace testing;

namespace {
    string arbitraryText("arbitrary text.");
    string cubePlCompilationPrefix("CubePL Compilation Error: ");
    string cubePlMemoryPrefix("CubePL Memory Mgmt. Error: ");
    string cubePlPrefix("CubePL Error: ");
    string errorPrefix("Error: ");
    string fatalErrorPrefix("Fatal Error: ");
    string filename("file.name");
    string ioErrorPrefix("I/O Error: ");
    string memoryErrorPrefix("Memory Error: ");
    string networkErrorPrefix("Network Error: ");
    string runtimeErrorPrefix("Runtime Error: ");
    string syntaxPrefix("Syntax Error: ");
    string zlibPrefix("ZLib Error: ");
}

TEST(CubeError, hasCorrectPrefix) {
    Error error("");

    ASSERT_EQ( ::errorPrefix, string(error.what()).substr(0, ::errorPrefix.length()));
}

TEST(CubeRuntimeError, hasCorrectPrefix) {
    RuntimeError error("");

    ASSERT_EQ( ::runtimeErrorPrefix, string(error.what()).substr(0, ::runtimeErrorPrefix.length()));
}

TEST(CubeFatalError, hasCorrectPrefix) {
    FatalError error("");

    ASSERT_EQ( ::fatalErrorPrefix, string(error.what()).substr(0, ::fatalErrorPrefix.length()));
}

TEST(CubeAnchorSyntaxError, hasCorrectPrefix) {
    AnchorSyntaxError error("");

    ASSERT_EQ( ::syntaxPrefix, string(error.what()).substr(0, ::syntaxPrefix.length()));
}

TEST(CubeNotSupportedVersionError, hasRuntimePrefix) {
    NotSupportedVersionError error("");

    ASSERT_EQ( ::runtimeErrorPrefix, string(error.what()).substr(0, ::runtimeErrorPrefix.length()));
}

TEST(CubeNotSupportedVersionError, showsCorrectStaticWhat) {
    string message("Unsupported Cube version.");
    NotSupportedVersionError error;

    ASSERT_EQ( ::runtimeErrorPrefix + message, error.what());
}

TEST(CubeNotSupportedVersionError, showsCorrectDynamicWhat) {
    string message("Unsupported Cube version: 1.2.3.");
    NotSupportedVersionError error("1.2.3");

    ASSERT_EQ( ::runtimeErrorPrefix + message, error.what());
}

TEST(CubeMissingValueError, showsCorrectStaticWhat) {
    string message("Incomplete value stream.");
    MissingValueError error;

    ASSERT_EQ( ::runtimeErrorPrefix + message, error.what());
}

TEST(CubeMissingValueError, showsCorrectDynamicWhat) {
    MissingValueError error(::arbitraryText);

    ASSERT_EQ( ::runtimeErrorPrefix + ::arbitraryText, error.what());
}

TEST(CubeWrongMarkerInFileError, showsCorrectStaticWhat) {
    string message("Wrong marker in Cube archive.");
    WrongMarkerInFileError error;

    ASSERT_EQ( ::runtimeErrorPrefix + message, error.what());
}

TEST(CubeWrongMarkerInFileError, showsCorrectDynamicWhat) {
    WrongMarkerInFileError error(::arbitraryText);

    ASSERT_EQ( ::runtimeErrorPrefix + ::arbitraryText, error.what());
}

TEST(CubePlaceOutOfBufferError, showsCorrectDynamicWhat) {
    string message("Access at index 2 is out of bounds of the buffer of size 1.");
    int size = 1, index = 2;
    PlaceOutOfBufferError error(size,index);

    ASSERT_EQ( ::runtimeErrorPrefix + message, error.what());
}

TEST(CubeUnknownResourceError, showsCorrectDynamicWhat) {
    UnknownResourceError error(::arbitraryText);

    ASSERT_EQ( ::runtimeErrorPrefix + ::arbitraryText, error.what());
}

TEST(CubeIOError, hasCorrectPrefix) {
    IOError error("");

    ASSERT_EQ( ::ioErrorPrefix, string(error.what()).substr(0, ::ioErrorPrefix.length()));
}

TEST(CubeIOError, showsCorrectDynamicWhat) {
    IOError error(::arbitraryText);

    ASSERT_EQ( ::ioErrorPrefix + ::arbitraryText, error.what());
}

TEST(CubeNoFileError, showsCorrectDynamicWhat) {
    NoFileError error(::arbitraryText);

    ASSERT_EQ( ::ioErrorPrefix + ::arbitraryText, error.what());
}

TEST(CubeNoFileInTarError, showsCorrectDynamicWhat) {
    string message(::ioErrorPrefix + "File '" + ::filename + "' not found in Cube archive.");
    NoFileInTarError error(filename);

    ASSERT_EQ( message, error.what());
}

TEST(CubeFinalizeFilesError, showsCorrectDynamicWhat) {
    FinalizeFilesError error(arbitraryText);

    ASSERT_EQ( ::runtimeErrorPrefix + ::arbitraryText, error.what());
}

TEST(CubeCreateFileError, showsCorrectDynamicWhat) {
    CreateFileError error(::arbitraryText);

    ASSERT_EQ( ::ioErrorPrefix + ::arbitraryText, error.what());
}

TEST(CubeOpenFileError, showsCorrectDynamicWhat) {
    string message(::ioErrorPrefix + "Cannot open file: " + ::filename);
    OpenFileError error(::filename);

    ASSERT_EQ( message, error.what());
}

TEST(CubeReadFileError, showsCorrectDynamicWhat) {
    string message(::ioErrorPrefix + "Cannot read file: " + ::arbitraryText);
    ReadFileError error(::arbitraryText);

    ASSERT_EQ( message, error.what());
}

TEST(CubeWriteFileError, showsCorrectDynamicWhat) {
    string message(::ioErrorPrefix + "Cannot write file: " + ::filename);
    WriteFileError error(filename);

    ASSERT_EQ( message, error.what());
}

TEST(CubeNotMemoryAllocatedForRow, showsCorrectDynamicWhat) {
    NotAllocatedMemoryForRow error(::arbitraryText);

    ASSERT_EQ( ::memoryErrorPrefix + ::arbitraryText, error.what());
}

TEST(CubeNoLeftSpaceError, showsCorrectDynamicWhat) {
    string message(::runtimeErrorPrefix + "Error writing data: " + ::arbitraryText);
    NoLeftSpaceError error(::arbitraryText);

    ASSERT_EQ( message, error.what());
}

TEST(CubeZLibError, hasCorrectPrefix) {
    ZLibError error(::arbitraryText);

    ASSERT_EQ( ::zlibPrefix + ::arbitraryText, error.what());
}

TEST(CubeZLibError, showsCorrectDynamicWhat) {
    ZLibError error(arbitraryText);

    ASSERT_EQ( ::zlibPrefix + ::arbitraryText, error.what());
}

TEST(CubeZNotEnoughMemoryError, hasCorrectStaticWhat) {
    string message("Insufficient memory to uncompress.");
    ZNotEnoughMemoryError error;

    ASSERT_EQ( ::zlibPrefix + message, error.what());
}

TEST(CubeZNotEnoughBufferError, hasCorrectStaticWhat) {
    string message("Insufficient output buffer space to uncompress.");
    ZNotEnoughBufferError error;

    ASSERT_EQ( ::zlibPrefix + message, error.what());
}

TEST(CubeZDataCorruptError, hasCorrectStaticWhat) {
    string message("Compressed data is corrupt or incomplete.");
    ZDataCorruptError error;

    ASSERT_EQ( ::zlibPrefix + message, error.what());
}

TEST(CubeCannotSelectRowSupplierError, showsCorrectDynamicWhat) {
    string message(::runtimeErrorPrefix + "Selection of RowSupplier failed. " + ::arbitraryText);
    CannotSelectRowSupplierError error(::arbitraryText);

    ASSERT_EQ( message, error.what());
}

TEST(CubePLError, hasCorrectPrefix) {
    CubePLError error("");

    ASSERT_EQ( ::cubePlPrefix, string(error.what()).substr(0, ::cubePlPrefix.length()));
}

TEST(CubePLError, showsCorrectDynamicWhat) {
    CubePLError error(::arbitraryText);

    ASSERT_EQ( ::cubePlPrefix + ::arbitraryText, error.what());
}

TEST(CubePLCompilationError, hasCorrectPrefix) {
    CubePLCompilationError error("");

    ASSERT_EQ( ::cubePlCompilationPrefix, string(error.what()).substr(0, ::cubePlCompilationPrefix.length()));
}

TEST(CubePLCompilationError, showsCorrectDynamicWhat) {
    CubePLCompilationError error(::arbitraryText);

    ASSERT_EQ( ::cubePlCompilationPrefix + ::arbitraryText, error.what());
}

TEST(CubePLMemoryLayoutError, hasCorrectPrefix) {
    CubePLMemoryLayoutError error("");

    ASSERT_EQ( ::cubePlMemoryPrefix, string(error.what()).substr(0, ::cubePlMemoryPrefix.length()));
}

TEST(CubePLMemoryLayoutError, showsCorrectDynamicWhat) {
    CubePLMemoryLayoutError error(::arbitraryText);

    ASSERT_EQ( ::cubePlMemoryPrefix + ::arbitraryText, error.what());
}

TEST(CubeNetworkError, hasCorrectPrefix) {
    NetworkError error("");

    ASSERT_EQ( ::networkErrorPrefix, string(error.what()).substr(0, ::networkErrorPrefix.length()));
}

TEST(CubeNetworkError, showsCorrectDynamicWhat) {
    NetworkError error(::arbitraryText);

    ASSERT_EQ( ::networkErrorPrefix + ::arbitraryText, error.what());
}

TEST(CubeNetworkErrorRecoverable, hasCorrectPrefix) {
    RecoverableNetworkError error("");

    ASSERT_EQ( ::networkErrorPrefix, string(error.what()).substr(0, ::networkErrorPrefix.length()));
}

TEST(CubeNetworkErrorRecoverable, showsCorrectDynamicWhat) {
    RecoverableNetworkError error(::arbitraryText);

    ASSERT_EQ( ::networkErrorPrefix + ::arbitraryText, error.what());
}

TEST(CubeNetworkErrorUnrecoverable, hasCorrectPrefix) {
    UnrecoverableNetworkError error("");

    ASSERT_EQ( ::networkErrorPrefix, string(error.what()).substr(0, ::networkErrorPrefix.length()));
}

TEST(CubeNetworkErrorUnrecoverable, showsCorrectDynamicWhat) {
    UnrecoverableNetworkError error(::arbitraryText);

    ASSERT_EQ( ::networkErrorPrefix + ::arbitraryText, error.what());
}

