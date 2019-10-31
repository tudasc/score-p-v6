/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2016                                                **
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
 * \file CubeError.cpp
 * \brief Define the output functions for every kind of error.
 */
#include "config.h"
#include "CubeError.h"

using namespace std;
using namespace cube;

namespace cube
{

Error::Error( std::string message )
    : mMessage( std::string( "Error: " ) + message )
{
}

Error::Error( const std::string& prefix,
              const std::string& message )
    : mMessage( prefix + message )
{
}

Error::~Error() throw()
{
}

std::string
Error::get_msg() const
{
    return std::string( what() );
}

const char*
Error::what() const throw()
{
    return mMessage.c_str();
}

RuntimeError::RuntimeError( std::string message )
    : Error( "Runtime Error: ", message )
{
}

RuntimeError::RuntimeError( const std::string& prefix,
                            const std::string& message )
    : Error( prefix, message )
{
}

FatalError::FatalError( std::string message )
    : Error( "Fatal Error: ", message )
{
}

AnchorSyntaxError::AnchorSyntaxError( std::string message )
    : RuntimeError( "Syntax Error: ", message )
{
}

NotSupportedVersionError::NotSupportedVersionError()
    : RuntimeError( "Unsupported Cube version." )
{
}

NotSupportedVersionError::NotSupportedVersionError( std::string rejected_version )
    : RuntimeError( "Unsupported Cube version: " + rejected_version +  ".")
{
}

MissingValueError::MissingValueError()
    : RuntimeError( "Incomplete value stream." )
{
}

MissingValueError::MissingValueError( std::string message )
    : RuntimeError( message )
{
}

WrongMarkerInFileError::WrongMarkerInFileError()
    : RuntimeError( "Wrong marker in Cube archive." )
{
}

WrongMarkerInFileError::WrongMarkerInFileError( std::string message )
    : RuntimeError( message )
{
}

PlaceOutOfBufferError::PlaceOutOfBufferError( int size,
                                              int index )
        : RuntimeError( constructMessage( size, index ) ),
          mSize( size ),
          mIndex( index )
{
}

std::string
PlaceOutOfBufferError::constructMessage( int size,
                                         int index )
{
    std::stringstream ss;
    ss << "Access at index " << index
       << " is out of bounds of the buffer of size "
       << size << ".";
    return ss.str();
}

UnknownResourceError::UnknownResourceError( std::string message )
    : RuntimeError( message )
{
}

IOError::IOError( std::string message )
    : RuntimeError( "I/O Error: ", message )
{
}

NoFileError::NoFileError( std::string message )
    : IOError( message )
{
}

NoFileInTarError::NoFileInTarError( std::string filename )
    : NoFileError( "File '" + filename + "' not found in Cube archive." )
{
}

NoIndexFileError::NoIndexFileError( std::string filename )
    : NoFileError( "Missing or incomplete index file '" + filename + "." )
{
}

FinalizeFilesError::FinalizeFilesError( std::string message )
    : RuntimeError( message )
{
}

CreateFileError::CreateFileError( std::string message )
    : IOError( message )
{
}

OpenFileError::OpenFileError( std::string filename )
    : IOError( "Cannot open file: " + filename )
{
}

ReadFileError::ReadFileError( std::string message )
    : IOError( "Cannot read file: " + message )
{
}

WriteFileError::WriteFileError( std::string message )
    : IOError( "Cannot write file: " + message )
{
}

NotAllocatedMemoryForRow::NotAllocatedMemoryForRow( std::string message )
    : RuntimeError( "Memory Error: ", message )
{
}

NoLeftSpaceError::NoLeftSpaceError( std::string message )
    : RuntimeError( "Error writing data: " + message )
{
}

ZLibError::ZLibError()
    : RuntimeError( "ZLib compression error." )
{
}

ZLibError::ZLibError( const std::string& message )
    : RuntimeError( "ZLib Error: ", message )
{
}

ZNotEnoughMemoryError::ZNotEnoughMemoryError()
    : ZLibError( "Insufficient memory to uncompress." )
{
}

ZNotEnoughBufferError::ZNotEnoughBufferError()
    : ZLibError( "Insufficient output buffer space to uncompress." )
{
}

ZDataCorruptError::ZDataCorruptError()
    : ZLibError( "Compressed data is corrupt or incomplete." )
{
}

CannotSelectRowSupplierError::CannotSelectRowSupplierError( std::string message )
    : RuntimeError(  "Selection of RowSupplier failed. " + message )
{
}

CubePLError::CubePLError( std::string message )
    : RuntimeError( "CubePL Error: ", message )
{
}

CubePLError::CubePLError( const std::string& prefix,
                          const std::string& message )
        : RuntimeError( prefix, message )
{
}

CubePLCompilationError::CubePLCompilationError( std::string message )
    : CubePLError( "CubePL Compilation Error: ", message )
{
}

CubePLMemoryLayoutError::CubePLMemoryLayoutError( std::string message )
    : CubePLError( "CubePL Memory Mgmt. Error: ", message )
{
}

CubePLUnsupportedVersionError::CubePLUnsupportedVersionError( std::string version_string )
    : CubePLError( "Version '" + version_string +
                   "' of CubePL engine is not supported by this version of Cube. Please try a newer version of Cube." )
{
}

CubeClusteringLayoutError::CubeClusteringLayoutError( std::string message )
    : RuntimeError( "Error handling clustered data. " + message )
{
}

Cube3SystemTreeMismatchError::Cube3SystemTreeMismatchError( std::string message )
    : RuntimeError( "System Tree is incompatible with Cube3 model. " + message )
{
}

NetworkError::NetworkError( const std::string& message )
    : RuntimeError( "Network Error: ", message )
{
}

InvalidSocket::InvalidSocket(const std::string& message)
	: NetworkError( message )
{
}

RecoverableNetworkError::RecoverableNetworkError( const std::string& message )
    : NetworkError( message )
{
}

UnrecoverableNetworkError::UnrecoverableNetworkError( const std::string& message )
    : NetworkError( message )
{
}

ostream&
operator <<( ostream& out, Error& exception )
{
    out << exception.what() << endl;
    return out;
}

ostream&
operator <<( ostream& out, RuntimeError& exception )
{
    out << exception.what() << endl;
    return out;
}

ostream&
operator <<( ostream& out, FatalError& exception )
{
    out << exception.what() << endl;
    return out;
}
}
