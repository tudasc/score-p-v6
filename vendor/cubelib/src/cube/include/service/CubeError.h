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
 * \file CubeError.h
 * \brief Provides a hierarchy of errors compatible with C++ throw/catch mechanism
 */
#ifndef CUBE_ERROR_H
#define CUBE_ERROR_H

/*
 *----------------------------------------------------------------------------
 *
 * class Error
 *
 *----------------------------------------------------------------------------
 */

#include <exception>
#include <sstream>
#include <string>

/**
 * @file CubeError.h
 * @brief Declaration and definition of Cube internal exceptions.
 */

namespace cube
{

/**
 * @class Error
 * @brief Indicates a generic (not otherwise specified) error in Cube
 */
class Error : public std::exception
{
public:
    /**
     * Construct with standard prefix and explanatory message.
     * @param message explanatory message
     *
     * @todo Refactor to use const-reference parameter
     */
    Error( std::string message );

    virtual
    ~Error() throw();

    /**
     * @deprecated
     * Returns the explanatory string.
     * @return the explanatory string
     */
    virtual
    std::string
    get_msg() const;

    /**
     * Returns the explanatory message.
     * @return explanatory message
     */
    virtual
    const char*
    what() const throw();

protected:
    /**
     * Construct with special prefix and explanatory message.
     * @param prefix Prefix to the explanatory message
     * @param message explanatory message
     */
    Error( const std::string& prefix,
           const std::string& message );

private:
    /// Explanatory message
    std::string mMessage;
};

/**
 * @class RuntimeError
 * @brief Indicates a runtime error in Cube.
 */
class RuntimeError :  public Error
{
public:
    /**
     * Construct with standard prefix and explanatory message.
     * @param message explanatory message
     *
     * @todo Refactor to use const-reference parameter
     */
    RuntimeError( std::string message );

protected:
    /**
     * Construct with special prefix and explanatory message.
     * @param prefix Prefix to the explanatory message
     * @param message explanatory message
     */
    RuntimeError( const std::string& prefix,
                  const std::string& message );
};

/**
 * @class FatalError
 * @brief Indicates a fatal error in Cube.
 */
class FatalError : public Error
{
public:
    /**
     * Construct with standard prefix and explanatory message.
     * @param message explanatory message
     *
     * @todo Refactor to use const-reference parameter
     */
    FatalError( std::string message );
};

/**
 * @class AnchorSyntaxError
 * @brief Indicates a syntax error in the Cube anchor file.
 */
class AnchorSyntaxError :  public RuntimeError
{
public:
    /**
     * Construct with standard prefix and explanatory message.
     * @param message explanatory message
     *
     * @todo Refactor to use const-reference parameter
     */
    AnchorSyntaxError( std::string message );
};


/**
 * @class NotSupportedVersionError
 * @brief Indicates an incompatible Cube file version.
 */
class NotSupportedVersionError : public RuntimeError
{
public:
    /**
     * Construct with standard prefix and standard explanatory message.
     */
    NotSupportedVersionError();

    /**
     * Construct with standard prefix and explanatory message.
     * @param rejected_version Rejected version string
     *
     * @todo Refactor to use const-reference parameter
     */
    NotSupportedVersionError( std::string rejected_version );
};


/**
 * @class MissingValueError
 * @brief Indicates an incomplete value stream.
 *
 * @todo Deprecate class as it is no longer used?
 */
class MissingValueError : public RuntimeError
{
public:

    /**
     * Construct with standard explanatory message
     */
    MissingValueError();

    /**
     * Construct with standard prefix and explanatory message.
     * @param message explanatory message
     *
     * @todo Refactor to use const-reference parameter
     */
    MissingValueError( std::string message );
};


/**
 * @class WrongMarkerInFileError
 * @brief Indicates an erroneous marker in the Cube archive.
 */
class WrongMarkerInFileError : public RuntimeError
{
public:

    /**
     * Construct with standard explanatory message
     */
    WrongMarkerInFileError();

    /**
     * Construct with standard prefix and explanatory message.
     * @param message explanatory message
     *
     * @todo Refactor to use const-reference parameter
     */
    WrongMarkerInFileError( std::string message );
};


/**
 * @class PlaceOutOfBufferError
 * @brief Indicates an out-of-bounds error accessing Cube buffer
 *
 * @todo Deprecate in favor of a new "IndexOutOfBoundsError"?
 */
class PlaceOutOfBufferError : public RuntimeError
{
public:
    /**
     * Construct with size and index values.
     * @param size  Size of the buffer to write to
     * @param index The out-of-bounds index
     */
    PlaceOutOfBufferError( int size,
                           int index );

private:
    std::string
    constructMessage( int size,
                      int index );

    /// @deprecated size value
    int mSize;

    /// @deprecated index value
    int mIndex;
};



/**
 * @class UnknownResourceError
 * @brief Indicates access to an unknown resource
 */
class UnknownResourceError : public RuntimeError
{
public:
    /**
     * Construct with explanatory message.
     * @param message explanatory message
     *
     * @todo Refactor to use const-reference parameter
     */
    UnknownResourceError( std::string message );
};


/**
 * @class IOError
 * @brief Indicates a generic I/O-related error.
 */
class IOError : public RuntimeError
{
public:
    /**
     * Construct with explanatory message.
     * @param _message explanatory message
     *
     * @todo Refactor to use const-reference parameter
     */
    IOError( std::string message );
};


/**
 * @class NoFileError
 * @brief Indicates a missing file.
 */
class NoFileError : public IOError
{
public:
    /**
     * Construct with explanatory message.
     * @param message explanatory message
     *
     * @todo Refactor to use const-reference parameter
     */
    NoFileError( std::string message );
};


/**
 * @class NoFileInTarError
 * @brief Indicates a file is not part of the Cube archive
 */
class NoFileInTarError : public NoFileError
{
public:
    /**
     * Construct with name of missing file.
     * @param filename Name of the file not found
     *
     * @todo Refactor to use const-reference parameter
     */
    NoFileInTarError( std::string filename );
};


/**
 * @class NoIndexFileError
 * @brief Indicates a missing or incomplete index file in the Cube archive.
 */
class NoIndexFileError : public NoFileError
{
public:
    /**
     * Construct with name of missing file.
     * @param filename Name of the file not found
     *
     * @todo Refactor to use const-reference parameter
     */
    NoIndexFileError( std::string filename );
};


/**
 * @class FinalizeFilesError
 * @brief Indicates an error during finalization of the Cube archive.
 *
 * @todo Refactor to IOError?
 */
class FinalizeFilesError : public RuntimeError
{
public:
    /**
     * Construct with explanatory message.
     * @param message explanatory message
     *
     * @todo Refactor to use const-reference parameter
     */
    FinalizeFilesError( std::string message );
};


/**
 * @class CreateFileError
 * @brief Indicates an error creating a Cube archive.
 */
class CreateFileError : public IOError
{
public:
    /**
     * Construct with explanatory message.
     * @param message explanatory message
     *
     * @todo Refactor to use const-reference parameter
     */
    CreateFileError( std::string message );
};


/**
 * @class OpenFileError
 * @brief Indicates an error opening an existing Cube archive.
 */
class OpenFileError : public IOError
{
public:
    /**
     * Construct with explanatory message
     * @param filename Name of the file that failed to open
     *
     * @todo Refactor to use const-reference parameter
     */
    OpenFileError( std::string filename );
};


/**
 * @class ReadFileError
 * @brief Indicates an error reading from a Cube archive.
 */
class ReadFileError : public IOError
{
public:
    /**
     * Construct with explanatory message
     * @param message explanatory message
     *
     * @todo Refactor to use const-reference parameter
     */
    ReadFileError( std::string message );
};


/**
 * @class WriteFileError
 * @brief Indicates an error writing to a Cube archive.
 */
class WriteFileError : public IOError
{
public:
    /**
     * Construct with explanatory message
     * @param message explanatory message
     *
     * @todo Refactor to use const-reference parameter
     */
    WriteFileError( std::string message );
};


/**
 * @class NotAllocatedMemoryForRow
 * @brief Indicates that memory could not be allocated for row of values.
 */

class NotAllocatedMemoryForRow : public RuntimeError
{
public:
    /**
     * Construct with explanatory message
     * @param message explanatory message
     *
     * @todo Refactor to use const-reference parameter
     */
    NotAllocatedMemoryForRow( std::string message );
};


/**
 * @class NoLeftSpaceError
 * @brief Indicates that there is no space left writing to the Cube archive.
 *
 * @todo Refactor to IOError?
 * @todo Deprecate?
 */
class NoLeftSpaceError : public RuntimeError
{
public:
    /**
     * Construct with explanatory message
     * @param message explanatory message
     *
     * @todo Refactor to use const-reference parameter
     */
    NoLeftSpaceError( std::string message );
};


/**
 * @class ZLibError
 * @brief Indicates a generic error in the use of Zlib.
 */
class ZLibError : public RuntimeError
{
public:
    /**
     * Construct with standard error message
     */
    ZLibError();

    /**
     * Construct with explanatory message.
     * @param message explanatory message
     */
    ZLibError( const std::string& message );
};


/**
 * @class ZNotEnoughMemoryError
 * @brief Indicates insufficient memory during the use of Zlib.
 *
 * @todo Deprecate class as it is not used?
 */
class ZNotEnoughMemoryError : public ZLibError
{
public:
    ZNotEnoughMemoryError();
};


/**
 * @class ZNotEnoughBufferError
 * @brief Indicates insufficient buffer space during uncompress with Zlib.
 *
 * @todo Deprecate class as it is not used?
 */
class ZNotEnoughBufferError : public ZLibError
{
public:
    ZNotEnoughBufferError();
};


/**
 * @class ZDataCorruptError
 * @brief Indicates corrupt data in zlib-compressed stream.
 *
 * @todo Deprecate class as it is not used?
 */
class ZDataCorruptError : public ZLibError
{
public:
    ZDataCorruptError();
};


/**
 * @class CannotSelectRowSupplierError
 * @brief Indicates that now matching RowSupplier could be found.
 */
class CannotSelectRowSupplierError : public RuntimeError
{
public:
    /**
     * Raise an error with explanatory message
     * @param message explanatory message
     *
     * @todo Refactor to use const-reference parameter
     */
    CannotSelectRowSupplierError( std::string message );
};


// compilation errors -------------------

/**
 * @class CubePLError
 * @brief Indicates a general error during CubePL processing.
 */
class CubePLError : public RuntimeError
{
public:
    /**
     * Raise an error with explanatory message
     * @param message explanatory message
     *
     * @todo Refactor to use const-reference parameter
     */
    CubePLError( std::string message );

protected:
    /**
     * Construct a generic Cube error with special prefix and explanatory message.
     * @param prefix Prefix to the explanatory message
     * @param message explanatory message
     */
    CubePLError( const std::string& prefix,
                 const std::string& message );
};


/**
 * @class CubePLCompilationError
 * @brief Indicates compilation error during CubePL processing.
 */
class CubePLCompilationError : public CubePLError
{
public:
    /**
     * Raise an error with explanatory message
     * @param message explanatory message
     *
     * @todo Refactor to use const-reference parameter
     */
    CubePLCompilationError( std::string message );
};


/**
 * @class CubePLMemoryLayourError
 * @brief Indicates memory layout problems
 */
class CubePLMemoryLayoutError : public CubePLError
{
public:
    /**
     * Raise an error with explanatory message
     * @param message explanatory message
     *
     * @todo Refactor to use const-reference parameter
     */
    CubePLMemoryLayoutError( std::string message );
};


/**
 * @class CubePLUnsupportedVersionError
 * @brief Indicates the requested CubePL version to be unsupported.
 */
class CubePLUnsupportedVersionError : public CubePLError
{
public:
    /**
     * Raise an error with explanatory message
     * @param version_string CubePL version string
     *
     * @todo Refactor to use const-reference parameter
     */
    CubePLUnsupportedVersionError( std::string version_string );
};


/**
 * @class CubeClusteringLayoutError
 * @brief Indicates an error handling clustered data.
 */
class CubeClusteringLayoutError : public RuntimeError
{
public:
    /**
     * Raise an error with explanatory message
     * @param message explanatory message
     *
     * @todo Refactor to use const-reference parameter
     */
    CubeClusteringLayoutError( std::string message );
};


/**
 * @class Cube3SystemTreeMismatchError
 * @brief Indicates a general incompatibility of the current system tree to the Cube3 format.
 */
class Cube3SystemTreeMismatchError : public RuntimeError
{
public:
    /**
     * Raise an error with explanatory message
     * @param message explanatory message
     *
     * @todo Refactor to use const-reference parameter
     */
    Cube3SystemTreeMismatchError( std::string message );
};


/// @name Network Exceptions
/// @{

/**
 * @class NetworkError
 * @brief Indicates an error with the client/server communication.
 */
class NetworkError : public RuntimeError
{
public:
    /**
     * Raise an error with explanatory message
     * @param message explanatory message
     */
    NetworkError( const std::string& message );
};

/**
 * @class NetworkError
 * @brief Indicates a recoverable error with the client/server communication.
 *
 * This error is raised when the server cannot complete a request, but the
 * communication between client and server is still considered to be consistent,
 * e.g., a remote file could not be opened. The communication usually does not
 * need to be reset after this kind of error.
 */
class RecoverableNetworkError : public NetworkError
{
public:
    /**
     * Raise an error with explanatory message
     * @param message explanatory message
     */
    RecoverableNetworkError( const std::string& message );
};

/**
 * @class NetworkError
 * @brief Indicates an unrecoverable error with the client/server communication.
 *
 * This error is raised when inconsistencies between client and server arise,
 * e.g., references of non-existing IDs. The communication should be reset
 * after this kind of error is raised.
 */
class UnrecoverableNetworkError : public NetworkError
{
public:
    /**
     * Raise an error with explanatory message
     * @param message explanatory message
     */
    UnrecoverableNetworkError( const std::string& message );
};

/**
 * @class InvalidSocket
 * @ingroup CUBE_lib.exceptions
 * @brief Indicates an invalid Socket, such as a null-initialized SocketPtr.
 */
class InvalidSocket : public NetworkError
{
public:
    /// @brief Raise an error with explanatory message
    /// @param message
    ///     explanatory message
    ///
    InvalidSocket( const std::string& message );
};

/// @}


/**
 * Convenience function to send exception string to an output stream (e.g., cout, cerr, ...)
 * @param out Output stream
 * @param exception Cube exception.
 * @return reference to new output stream.
 *
 * @todo Refactor to take const-reference of exception
 * @todo Deprecate, as it proliferates non-standard use of exceptions in output streams?
 */
std::ostream&
operator<<( std::ostream& out,
            Error&        exception );

/**
 * Convenience function to send exception string to an output stream (e.g., cout, cerr, ...)
 * @param out Output stream
 * @param exception Cube exception.
 * @return reference to new output stream.
 *
 * @todo Refactor to take const-reference of exception
 * @todo Deprecate, as use-case is covered by more general operator?
 */
std::ostream&
operator<<( std::ostream& out,
            RuntimeError& exception );

/**
 * Convenience function to send exception string to an output stream (e.g., cout, cerr, ...)
 * @param out Output stream
 * @param exception Cube exception.
 * @return reference to new output stream.
 *
 * @todo Refactor to take const-reference of exception
 * @todo Deprecate, as use-case is covered by more general operator?
 */
std::ostream&
operator<<( std::ostream& out,
            FatalError&   exception );
}

#endif
