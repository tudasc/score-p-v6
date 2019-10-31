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


/*-------------------------------------------------------------------------*/
/**
 * @file
 * @ingroup CUBE_lib.base
 * @brief   General type definitions.
 */
/*-------------------------------------------------------------------------*/


#ifndef CUBE_TYPES_H
#define CUBE_TYPES_H

#include <vector>
#include <limits>
#include <utility>
#include <stdint.h>
#include <string>
#include <utility>

namespace cube
{
/// Aggregation state of values
enum CalculationFlavour
{
    CUBE_CALCULATE_INCLUSIVE = 0,   ///< Value includes children
    CUBE_CALCULATE_EXCLUSIVE = 1,   ///< Value excludes children
    CUBE_CALCULATE_SAME      = 2,   ///< Value depends on type
    CUBE_CALCULATE_NONE      = 3,   ///< Used to identify "empty" call as a default value
};

// / Used to specify, if an inclusive or an exclusive value is being calculated
enum CubePLVerbosityLevel
{
    CUBEPL_VERBOSITY_MUTE      = 0,
    CUBEPL_VERBOSITY_PARSING   = 1,
    CUBEPL_VERBOSITY_EXECUTION = 2,
    CUBEPL_VERBOSITY_FULL      = 3
};

/// Type of copy during Cube construction.
enum CubeCopyFlag
{
    CUBE_DEEP_COPY,         ///< Copy full content
    CUBE_ONLY_STRUCTURE     ///< Copy only the structure (definitions)
};

/// Type of memory handling for zero values
enum CubeEnforceSaving
{
    CUBE_IGNORE_ZERO   = 0, ///< Do not allocate memory for zero values
    CUBE_ENFORCE_ZERO  = 1, ///< Allocate memory for zero values
    CUBE_ENFORCE_UNDEF = 2  ///< FIXME What does this do???
};

// Forward declarations
class Cnode;
class Region;
class Metric;
class Cartesian;
class Vertex;
class IdentObject;
class Location;
class LocationGroup;
class SystemTreeNode;
class Sysres;
class Value;
class Cube;
class GeneralEvaluation;
class CubePLMemoryManager;
class CubePLMemoryInitializer;
class Matrix;
class RowWiseMatrix;
class BasicStrategy;
class FileFinder;
class LayoutDetector;
class RuntimeError;
class IDdeliverer;
class Row;
class Index;
class RowsManager;
class IndexManager;
class SimpleReader;
class TarReader;
class FileBaseLayout;
class RowsSupplier;
class SingleValueTrafo;
class DataMarker;
class ZDataMarker;
class IndexHeader;



typedef Location                                Thread;
typedef std::pair<Thread*, CalculationFlavour>  thread_pair;            // /< Used for various calculations
typedef std::vector<thread_pair>                list_of_threads;        // /< Used to collect a list of threads

typedef LocationGroup                           Process;
typedef std::pair<Process*, CalculationFlavour> process_pair;       // /< Used for calculations of varios types.
typedef std::vector<process_pair>               list_of_processes;  // /< Used to collect a list of processes

typedef SystemTreeNode                          Node;
typedef std::pair<Node*, CalculationFlavour>    node_pair;     // /< Used for calculation of various values.
typedef std::vector<node_pair>                  list_of_nodes; // /< Used to collect a list of nodes

typedef SystemTreeNode                          Machine;
typedef std::pair<Machine*, CalculationFlavour> machine_pair;           // /< Used for calculations of various values.
typedef std::vector<machine_pair>               list_of_machines;       // /< Used to collect a list of machines


typedef std::pair<Location*, CalculationFlavour>       loc_pair;                // /< Used for various calculations
typedef std::vector<loc_pair>                          list_of_location;        // /< Used to collect a list of threads

typedef std::pair<LocationGroup*, CalculationFlavour>  loc_group_pair;          // /< Used for various calculations
typedef std::vector<loc_group_pair>                    list_of_location_groups; // /< Used to collect a list of threads

typedef std::pair<SystemTreeNode*, CalculationFlavour> stn_pair;                // /< Used for various calculations
typedef std::vector<stn_pair>                          list_of_stns;            // /< Used to collect a list of threads


typedef std::pair<Sysres*, CalculationFlavour> sysres_pair;                // /< Used for various calculations
typedef std::vector<sysres_pair>               list_of_sysresources;       // /< Used to collect a list of threads


typedef std::pair<Metric*, CalculationFlavour> metric_pair;             // /< Used for calculations of various values.
typedef std::vector<metric_pair>               list_of_metrics;         // /< Used to collect a list of metrics


typedef std::pair<Region*, CalculationFlavour> region_pair;     // /< Used in the calculations of values in the flattree.
typedef std::vector<region_pair>               list_of_regions; // /< Used to collect a list of regions

typedef std::pair<Cnode*, CalculationFlavour>  cnode_pair;      // /< Used in the calculations of various values.
typedef std::vector<cnode_pair>                list_of_cnodes;  // /< Used to collect a list of cnodes


typedef enum LocationGroupType { CUBE_LOCATION_GROUP_TYPE_PROCESS = 0,
                                 CUBE_LOCATION_GROUP_TYPE_METRICS = 1 } LocationGroupType;


typedef enum LocationType { CUBE_LOCATION_TYPE_CPU_THREAD = 0,
                            CUBE_LOCATION_TYPE_GPU        = 1,
                            CUBE_LOCATION_TYPE_METRIC     = 2 } LocationType;

// / Used to specify, if an inclusive or an exclusive value is being calculated
typedef enum sysres_kind { CUBE_UNKNOWN = 0, CUBE_MACHINE = 1, CUBE_NODE = 2, CUBE_PROCESS = 3, CUBE_THREAD = 4, CUBE_SYSTEM_TREE_NODE = 5, CUBE_LOCATION_GROUP = 6, CUBE_LOCATION = 7 } sysres_kind;



typedef enum TypeOfMetric { CUBE_METRIC_EXCLUSIVE,
                            CUBE_METRIC_INCLUSIVE,
                            CUBE_METRIC_SIMPLE,
                            CUBE_METRIC_POSTDERIVED,
                            CUBE_METRIC_PREDERIVED_INCLUSIVE,
                            CUBE_METRIC_PREDERIVED_EXCLUSIVE } TypeOfMetric;

typedef enum VizTypeOfMetric { CUBE_METRIC_NORMAL,
                               CUBE_METRIC_GHOST } VizTypeOfMetric;


typedef enum CubeStrategy { CUBE_MANUAL_STRATEGY                = 0,
                            CUBE_ALL_IN_MEMORY_STRATEGY         = 1,
                            CUBE_LAST_N_ROWS_STRATEGY           = 2,
                            CUBE_ALL_IN_MEMORY_PRELOAD_STRATEGY = 3 } CubeStrategy;


typedef enum  DataType
{
    CUBE_DATA_TYPE_NONE,
    CUBE_DATA_TYPE_DOUBLE,
    CUBE_DATA_TYPE_INT8,
    CUBE_DATA_TYPE_UINT8,
    CUBE_DATA_TYPE_INT16,
    CUBE_DATA_TYPE_UINT16,
    CUBE_DATA_TYPE_INT32,
    CUBE_DATA_TYPE_UINT32,
    CUBE_DATA_TYPE_INT64,
    CUBE_DATA_TYPE_UINT64,
    CUBE_DATA_TYPE_COMPLEX,
    CUBE_DATA_TYPE_TAU_ATOMIC,
    CUBE_DATA_TYPE_RATE,
    CUBE_DATA_TYPE_MIN_DOUBLE,
    CUBE_DATA_TYPE_MAX_DOUBLE,
    CUBE_DATA_TYPE_SCALE_FUNC,
    CUBE_DATA_TYPE_HISTOGRAM,
    CUBE_DATA_TYPE_NDOUBLES
} DataType;


// / Defines the enumeration of all supported indexes.
// / Note : CUBE_INDEX_FORMAT_BITVECTOR is ABSOLTE and wont be suppported.
typedef enum  IndexFormat { CUBE_INDEX_FORMAT_NONE, CUBE_INDEX_FORMAT_SPARSE, CUBE_INDEX_FORMAT_BITVECTOR_NOT_SUPPORTED, CUBE_INDEX_FORMAT_DENSE } IndexFormat;

// cache types
typedef int64_t simple_cache_key_t;
typedef int64_t sysres_id_t;
typedef int64_t cnode_id_t;


// / position in data stream is 64bit to support big files.
typedef  uint64_t position_t;

// / value iof invalid position, which is used to indicate missing row in the cube file.
static const position_t non_position = std::numeric_limits<position_t>::max();

// / position in data stream is 64bit to support big files.
typedef  uint32_t index_size_t;
// / position in data stream is 64bit to support big files.
typedef  uint32_t index_t;
// / value of index, indication missing row
static const index_t non_index = std::numeric_limits<index_t>::max();
// / the range of the coordinates in the mapping are as big as position in the file
typedef  int64_t cnode_id_t;
// / the range of the coordinates in the mapping are as big as position in the file
typedef  int64_t thread_id_t;

typedef  int64_t cnodes_number_t;
typedef  int64_t threads_number_t;

// / mapping (cnode_id, thread_id) <-> position is bijectiv and tuplet collects two-valued argument of the right side.
typedef  std::pair<cnode_id_t, thread_id_t> tuplet;

// / for optimisation of the index (sorting) one deals with the pairs of rows. A single step of the optimisation prescription is the exchange of two rows.
typedef  std::pair<cnode_id_t, cnode_id_t> rows_pair;

// / one of the underlying steps during calculation of incl/excl value is calculation of the ranges in id-space. Ranges collects the result of such calculation and allows to collect in one variable all needed parts in Data stream.
typedef  std::vector< std::pair< position_t, position_t > > Ranges;

// / Collection of Rows, which participate in single calculation.
typedef  std::vector< cnode_id_t  > Rows;


// / a type of memory, storing raw row data
typedef char* row_t;

// / type of a memory collection
typedef std::vector<row_t> rows_t;

// type for cnode enumeration
typedef std::vector<cube::Vertex*> row_of_objects_t;

// typedef std::pair<std::string, unsigned long long> fileplace_t;
typedef std::pair<std::string, std::pair<uint64_t, uint64_t> > fileplace_t; // name, (start, size)


/// @brief Container for Value* used in bulk calls
typedef std::vector< Value* > value_container;

/**
 *  Index of the compressed Data is a vector of #cnodes elements, every of them describes a compressed row over #threads for given #cnode.
 *  First element is the start position of not compressed buffer. (Usually #cnode * #threads). It grows from element to element.
 *  Second element indicates, when the compressed buffer starts.
 *  Third element saves the size of the compressed buffer.
 *
 *  Element is defined as union of packed structure and byte stream. Byte stream is used to save it into file.
 */
typedef union
{
    struct __attribute__ ( ( __packed__ ) )
    {
        uint64_t start_uncompressed;
        uint64_t start_compressed;
        uint64_t size_compressed;
    } named;
    char as_array[ 1 ];
} SubIndexElement;



/**
 *  For internal data processing, one uses "start_uncompressed" as a key and stores information in the map.
 *
 *  First element is the number of row in the index.
 *  Second element indicates, when the compressed buffer starts.
 *  Third element saves the size of the compressed buffer.
 *
 *  Element is defined as union of packed structure and byte stream. Byte stream is used to save it into file.
 */
typedef union
{
    struct __attribute__ ( ( __packed__ ) )
    {
        uint64_t row_number;
        uint64_t start_compressed;
        uint64_t size_compressed;
    } named;
    char as_array[ 1 ];
} SubIndexInternalElement;


/**
 * Header lyout is represented as packed structure.
 * One need an access to different fields of the header and as char stream for io operations. - therefore one defines it like a n union.
 */
typedef union
{
    struct
    {
        // / If this Value "1" -> no endianess transformation is needed. If "16777216" or "0x1000000" - then one has to apply "SwapBytes" Trafo. Only two endianesses are supported : Little endian and Big Endian. Middle Endian is not supported directly, but it is trivial to support by adding additional "SingleValueTrafo"
        uint32_t endianness;
        // / Current version of the header and index layout. Current == "0"
        uint16_t version;

        // / Byte, indicationg a format of the used index.  Possible index types are defined in "Indexes.h"
        uint8_t format;
    }  __attribute__ ( ( __packed__ ) ) named;
    // / To save header in the file one uses representation of the header as a array of bytes.
    char as_array[ 1 ];
} Header;
}
#endif
