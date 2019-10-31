/*
 * This file is part of the Score-P software (http://www.score-p.org)
 *
 * Copyright (c) 2009-2012,
 * RWTH Aachen University, Germany
 *
 * Copyright (c) 2009-2012,
 * Gesellschaft fuer numerische Simulation mbH Braunschweig, Germany
 *
 * Copyright (c) 2009-2014,
 * Technische Universitaet Dresden, Germany
 *
 * Copyright (c) 2009-2012,
 * University of Oregon, Eugene, USA
 *
 * Copyright (c) 2009-2012,
 * Forschungszentrum Juelich GmbH, Germany
 *
 * Copyright (c) 2009-2012,
 * German Research School for Simulation Sciences GmbH, Juelich/Aachen, Germany
 *
 * Copyright (c) 2009-2012,
 * Technische Universitaet Muenchen, Germany
 *
 * This software may be modified and distributed under the terms of
 * a BSD-style license.  See the COPYING file in the package base
 * directory for details.
 *
 */


/**
 *  @file
 *
 *  @brief      This tool measures the time to generate a valid OTF2 archive and
 *              read it back in.
 *
 *  @b Usage:
 *  @code
 *    otf2_speed_test [--debug]
 *  @endcode
 *  @param --debug              Enable debug modus (optional).
 *                              Please note: This will bias the time results.
 *
 *  @return                     Returns EXIT_SUCCESS if successful, EXIT_FAILURE
 *                              if an error occures.
 */

#include <config.h>

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>

#include <otf2/otf2.h>
#include <mpi.h>

/** @brief Defines the number of event sets that are written. An event set
 *  consists of enter - mpi_send - leave, enter - mpi_recv - leave i.e. the
 *  actual number of events is 6 times bigger. */
#define NUM_EVENT_SETS 500000


/* ___ Global variables. ____________________________________________________ */



/** @internal
 *  @brief Defines if debug is turned on (1) or off (0). */
static bool otf2_DEBUG;



/* ___ Prototypes for static functions. _____________________________________ */



static inline void
otf2_speed_test_get_parameters
(
    int    argc,
    char** argv
);

static inline void
check_pointer
(
    void* pointer,
    char* description,
    ...
);

static inline void
check_status
(
    OTF2_ErrorCode status,
    char*          description,
    ...
);

static OTF2_FlushType
pre_flush
(
    void*         userData,
    OTF2_FileType fileType,
    uint64_t      locationId,
    void*         callerData,
    bool          final
);

static OTF2_TimeStamp
post_flush
(
    void*         userData,
    OTF2_FileType fileType,
    uint64_t      locationId
);

static OTF2_FlushCallbacks flush_callbacks =
{
    .otf2_pre_flush  = pre_flush,
    .otf2_post_flush = post_flush
};

static inline uint64_t
get_time
(
    void
);

static inline double
gtod
(
    void
);

static inline double
smin
(
    double* data,
    int     num_items
);

static inline double
smax
(
    double* data,
    int     num_items
);

static inline double
savg
(
    double* data,
    int     num_items
);


/* ___ Prototypes for all callbacks. ________________________________________ */



static inline OTF2_CallbackCode
GlobDefLocation_Register( void*                 userData,
                          OTF2_LocationRef      locationIdentifier,
                          OTF2_StringRef        stringID,
                          OTF2_LocationType     locationType,
                          uint64_t              numberOfEvents,
                          OTF2_LocationGroupRef locationGroup );

/* ___ main _________________________________________________________________ */



/** @internal
 *  @brief Run otf2_speed_test.
 *
 *  'otf2_speed_test' measures the time to generate a valid OTF2 archive and
 *  read it back in.
 *
 *  Usage:
 *    otf2_speed_test [--debug]
 *
 *  Input parameters:
 *    --debug               Enable debug modus (optional).
 *                          Please note: This will bias the time results.
 *
 *  @param argc             Programs argument counter.
 *  @param argv             Programs argument values.
 *
 *  @return                 Returns EXIT_SUCCESS if successful, EXIT_FAILURE
 *                          if an error occures.
 */
int
main
(
    int    argc,
    char** argv
)
{
    otf2_speed_test_get_parameters( argc, argv );

    /* MPI Initialization. */
    MPI_Init( &argc, &argv );

    int num_ranks = 0;
    int rank      = 0;

    MPI_Comm_size( MPI_COMM_WORLD, &num_ranks );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );


    if ( rank == 0 )
    {
        if ( otf2_DEBUG )
        {
            printf( "\n=== OTF2_SPEED_TEST [DEBUG MODE] ===\n\n" );
            printf( "Please note: Debug mode will bias the time results.\n\n" );
        }
        else
        {
            printf( "\n=== OTF2_SPEED_TEST ===\n\n" );
        }
    }





/* ___ Generate archive. ____________________________________________________ */



    /* Time information. */
    double w_init, w_evts, w_defs, w_final, w_total;

    w_init = gtod();
    /* Create new archive handle. */
    OTF2_Archive* archive = OTF2_Archive_Open( "otf2_speed_test_trace",
                                               "TestTrace",
                                               OTF2_FILEMODE_WRITE,
                                               1024 * 1024,
                                               1024 * 1024,
                                               OTF2_SUBSTRATE_POSIX,
                                               OTF2_COMPRESSION_NONE );

    check_pointer( archive, "Create archive" );


    /* Set description, and creator. */
    OTF2_ErrorCode status = OTF2_ERROR_INVALID;
    if ( rank == 0 )
    {
        status = OTF2_Archive_SetDescription( archive, "Generic OTF2 archive to measure library speed." );
        check_status( status, "Set description." );
        status = OTF2_Archive_SetCreator( archive, "otf2_speed_test" );
        check_status( status, "Set creator." );
    }


    /* Generate location IDs. Just to have non-consecutive location IDs. */
    uint64_t location_id = rank * rank;


    /* Create local event writer. */
    OTF2_EvtWriter* evt_writer = NULL;
    OTF2_DefWriter* def_writer = NULL;

    evt_writer = OTF2_Archive_GetEvtWriter( archive, location_id );
    check_pointer( evt_writer, "Get event writer." );

    def_writer = OTF2_Archive_GetDefWriter( archive, location_id );
    check_pointer( def_writer, "Get definition writer" );

    w_init = gtod() - w_init;

    /* Write enter, mpi_send, leave. */
    uint32_t region = rank * 1000;
    uint32_t string = rank * 1000;

    w_evts = gtod();
    uint64_t i;
    for ( i = 0; i < NUM_EVENT_SETS; ++i )
    {
        /* Write enter, mpi_send, leave. */
        status += OTF2_EvtWriter_Enter( evt_writer, NULL, get_time(), region );
        status += OTF2_EvtWriter_MpiSend( evt_writer, NULL, get_time(), location_id, 1, rank, 1024 );
        status += OTF2_EvtWriter_Leave( evt_writer, NULL, get_time(), region );

        /* Write enter, mpi_recv, leave. */
        status += OTF2_EvtWriter_Enter( evt_writer, NULL, get_time(), region + 1 );
        status += OTF2_EvtWriter_MpiRecv( evt_writer, NULL, get_time(), location_id, 1, rank, 1024 );
        status += OTF2_EvtWriter_Leave( evt_writer, NULL, get_time(), region + 1 );
    }
    w_evts = gtod() - w_evts;
    check_status( status, "Write event sets" );

    /* Write according definitions. */
    w_defs  = gtod();
    status += OTF2_DefWriter_WriteString( def_writer, string, "MPI_Send" );
    string++;
    status += OTF2_DefWriter_WriteString( def_writer, string, "Send an MPI message" );
    string++;
    status += OTF2_DefWriter_WriteRegion( def_writer, region, string - 1, string - 1, string, OTF2_REGION_ROLE_UNKNOWN, OTF2_PARADIGM_UNKNOWN, OTF2_REGION_FLAG_NONE, 0, 0, 0 );
    region++;

    status += OTF2_DefWriter_WriteString( def_writer, string, "MPI_Recv" );
    string++;
    status += OTF2_DefWriter_WriteString( def_writer, string, "Receive an MPI message" );
    string++;
    status += OTF2_DefWriter_WriteRegion( def_writer, region, string - 1, string - 1, string, OTF2_REGION_ROLE_UNKNOWN, OTF2_PARADIGM_UNKNOWN, OTF2_REGION_FLAG_NONE, 0, 0, 0 );
    region++;
    w_defs = gtod() - w_defs;
    check_status( status, "Write definitions" );

    w_final = gtod();
    if ( rank == 0 )
    {
        /* Write location definitions. */
        OTF2_GlobalDefWriter* global_def_writer = NULL;
        global_def_writer = OTF2_Archive_GetGlobalDefWriter( archive );
        check_pointer( global_def_writer, "Get global definition writer" );

        status = OTF2_GlobalDefWriter_WriteString( global_def_writer, 0, "Rank" );
        check_status( status, "Write string definition." );

        uint64_t i;
        for ( i = 0; i < num_ranks; ++i )
        {
            status = OTF2_GlobalDefWriter_WriteLocation( global_def_writer,
                                                         i * i,
                                                         0,
                                                         OTF2_LOCATION_TYPE_CPU_THREAD,
                                                         0,
                                                         i /* location group */ );
            check_status( status, "Write location definition." );
            string++;
        }

        status = OTF2_Archive_CloseGlobalDefWriter( archive, global_def_writer );
        check_status( status, "Closing global definition writer." );
    }


    /* Finalize. */
    status = OTF2_Archive_Close( archive );
    check_status( status, "Close archive." );
    w_final = gtod() - w_final;
    w_total = w_init + w_evts + w_defs + w_final;

    /* This is just to add a message to the debug output. */
    check_status( OTF2_SUCCESS, "Writing finished successfully.\n" );

    double w_inits[ num_ranks ];
    double w_evtss[ num_ranks ];
    double w_defss[ num_ranks ];
    double w_finals[ num_ranks ];
    double w_totals[ num_ranks ];

    MPI_Gather( &w_init, 1, MPI_DOUBLE, w_inits, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD );
    MPI_Gather( &w_evts, 1, MPI_DOUBLE, w_evtss, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD );
    MPI_Gather( &w_defs, 1, MPI_DOUBLE, w_defss, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD );
    MPI_Gather( &w_final, 1, MPI_DOUBLE, w_finals, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD );
    MPI_Gather( &w_total, 1, MPI_DOUBLE, w_totals, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD );


/* ___ Read archive back in. ________________________________________________ */


    /* Reading is done with one single process. */
    if ( rank == 0 )
    {
        double r_init = gtod();
        /* Get a reader handle. */
        OTF2_Reader* reader = OTF2_Reader_Open( "otf2_speed_test_trace/TestTrace.otf2" );
        check_pointer( reader, "Create new reader handle." );
        status = OTF2_Reader_SetSerialCollectiveCallbacks( reader );
        check_status( status, "Set serial mode." );


        /* Define definition callbacks. */
        OTF2_GlobalDefReaderCallbacks* register_defs = OTF2_GlobalDefReaderCallbacks_New();
        check_pointer( register_defs, "Create reader callbacks." );
        OTF2_GlobalDefReaderCallbacks_SetLocationCallback( register_defs, GlobDefLocation_Register );


        /* Get number of locations from the anchor file. */
        uint64_t num_locations = 0;
        status = OTF2_Reader_GetNumberOfLocations( reader, &num_locations );
        check_status( status, "Get number of locations. Number of locations: %llu",
                      ( long long unsigned )num_locations );


        /* Read global definitions. If a location definition is found, a new local
         * event reader is opened in the callback. */
        uint64_t              definitions_read  = 0;
        OTF2_GlobalDefReader* global_def_reader = OTF2_Reader_GetGlobalDefReader( reader );
        check_pointer( global_def_reader, "Create global definition reader handle." );
        status = OTF2_Reader_RegisterGlobalDefCallbacks( reader, global_def_reader,
                                                         register_defs,
                                                         reader );
        check_status( status, "Register global definition callbacks." );
        r_init = gtod() - r_init;

        OTF2_GlobalDefReaderCallbacks_Delete( register_defs );

        double r_defs = gtod();
        status = OTF2_Reader_ReadGlobalDefinitions( reader, global_def_reader,
                                                    OTF2_UNDEFINED_UINT64,
                                                    &definitions_read );
        r_defs = gtod() - r_defs;
        check_status( status, "Read global definitions. Number of definitions: %llu",
                      ( long long unsigned )definitions_read );

        OTF2_Reader_CloseGlobalDefReader( reader,
                                          global_def_reader );

        /* Get global event reader. */
        OTF2_GlobalEvtReader* global_evt_reader = OTF2_Reader_GetGlobalEvtReader( reader );
        check_pointer( global_evt_reader, "Create global event reader." );


        /* Read until an error occures. */
        uint64_t events_read = 0;

        double r_evts = gtod();
        status = OTF2_Reader_ReadGlobalEvents( reader, global_evt_reader, OTF2_UNDEFINED_UINT64, &events_read );
        r_evts = gtod() - r_evts;
        check_status( status, "Read %llu events.", ( long long unsigned )events_read );

        double r_final = gtod();
        status = OTF2_Reader_Close( reader );
        check_status( status, "Close reader." );
        r_final = gtod() - r_final;
        double r_total = r_init + r_defs + r_evts + r_final;

        /* This is just to add a message to the debug output. */
        check_status( OTF2_SUCCESS, "Delete reader handle." );
        check_status( OTF2_SUCCESS, "Programm finished successfully." );

        printf( "\n" );

        time_t timer = time( NULL );

        char hostname[ 1024 ] = "";
        /* directly use the OTF2 own GetHostname, because we are build by the
           Score-P package, but already got the utils lib via libotf2 */
        extern int
        OTF2_UTILS_IO_GetHostname( char*  name,
                                   size_t namelen );

        OTF2_UTILS_IO_GetHostname( hostname, 1023 );

        printf( "Measurement on %s using %d cores from %s", hostname, num_ranks, ctime( &timer ) );
        printf( "Time used in seconds (min, max, avg)\n" );
        printf( "Time to initalize writers: %12.8f %12.8f %12.8f\n", smin( w_inits, num_ranks ), smax( w_inits, num_ranks ), savg( w_inits, num_ranks ) );
        printf( "Time to write events:      %12.8f %12.8f %12.8f\n", smin( w_evtss, num_ranks ), smax( w_evtss, num_ranks ), savg( w_evtss, num_ranks ) );
        printf( "Time to write definitions: %12.8f %12.8f %12.8f\n", smin( w_defss, num_ranks ), smax( w_defss, num_ranks ), savg( w_defss, num_ranks ) );
        printf( "Time to finalize writers:  %12.8f %12.8f %12.8f\n", smin( w_finals, num_ranks ), smax( w_finals, num_ranks ), savg( w_finals, num_ranks ) );
        printf( "Time total writing:        %12.8f %12.8f %12.8f\n", smin( w_totals, num_ranks ), smax( w_totals, num_ranks ), savg( w_totals, num_ranks ) );
        printf( "Time to initalize readers: %12.8f\n", r_init );
        printf( "Time to read events:       %12.8f\n", r_evts );
        printf( "Time to read definitions:  %12.8f\n", r_defs );
        printf( "Time to finalize readers:  %12.8f\n", r_final );
        printf( "Time total reading:        %12.8f\n", r_total );
        printf( "\n" );

        FILE* fp = fopen( "otf2_speed_test.log", "a" );
        fprintf( fp, "Measurement on %s using %d cores from %s", hostname, num_ranks, ctime( &timer ) );
        fprintf( fp, "Time used in seconds (min, max, avg)\n" );
        fprintf( fp, "Time to initalize writers: %12.8f %12.8f %12.8f\n", smin( w_inits, num_ranks ), smax( w_inits, num_ranks ), savg( w_inits, num_ranks ) );
        fprintf( fp, "Time to write events:      %12.8f %12.8f %12.8f\n", smin( w_evtss, num_ranks ), smax( w_evtss, num_ranks ), savg( w_evtss, num_ranks ) );
        fprintf( fp, "Time to write definitions: %12.8f %12.8f %12.8f\n", smin( w_defss, num_ranks ), smax( w_defss, num_ranks ), savg( w_defss, num_ranks ) );
        fprintf( fp, "Time to finalize writers:  %12.8f %12.8f %12.8f\n", smin( w_finals, num_ranks ), smax( w_finals, num_ranks ), savg( w_finals, num_ranks ) );
        fprintf( fp, "Time total writing:        %12.8f %12.8f %12.8f\n", smin( w_totals, num_ranks ), smax( w_totals, num_ranks ), savg( w_totals, num_ranks ) );
        fprintf( fp, "Time to initalize readers: %12.8f\n", r_init );
        fprintf( fp, "Time to read events:       %12.8f\n", r_evts );
        fprintf( fp, "Time to read definitions:  %12.8f\n", r_defs );
        fprintf( fp, "Time to finalize readers:  %12.8f\n", r_final );
        fprintf( fp, "Time total reading:        %12.8f\n", r_total );
        fprintf( fp, "\n" );
        fclose( fp );
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}



/* ___ Implementation of static functions ___________________________________ */



/** @internal
 *  @brief Get command line parameters.
 *
 *  Parses command line parameters and checks for their existence.
 *  Prints help for parameters '-h' or '--help'.
 *
 *  @param argc             Programs argument counter.
 *  @param argv             Programs argument values.
 */
static inline void
otf2_speed_test_get_parameters
(
    int    argc,
    char** argv
)
{
    /* Check if there is at least one command line parameter. */
    if ( argc < 2 )
    {
        return;
    }

    /* Check for passed '--help' or '-h' and print help. */
    if ( !strncmp( argv[ 1 ], "--help", 6 ) || !strncmp( argv[ 1 ], "-h", 2 ) )
    {
        printf( "\n" );
        printf( "'otf2_speed_test' measures the time to generate a valid OTF2 archive and read it back in.\n" );
        printf( "\n" );
        printf( "Usage:\n" );
        printf( "  otf2_speed_test [--debug]" );
        printf( "\n" );
        printf( "Input parameters:\n" );
        printf( "  --debug            To run otf2_speed_test in debug mode.\n" );
        printf( "                     Please note: This will bias the time results.\n" );
        printf( "\n" );
        printf( "Report bugs to <%s>\n", PACKAGE_BUGREPORT );
        printf( "\n" );
        exit( EXIT_SUCCESS );
    }

    /* Check for debug mode. */
    if ( !strncmp( argv[ 1 ], "--debug", 7 ) )
    {
        otf2_DEBUG = true;
    }

    return;
}


/** @internal
 *  @brief Check if pointer is NULL.
 *
 *  Checks if a pointer is NULL. If so it prints an error with the passed
 *  description and exits the program.
 *  If in debug mode, it prints a debug message with the passed description.
 *  It is possible to passed a variable argument list like e.g. in printf.
 *
 *  @param pointer          Pointer to be checked.
 *  @param description      Description for error/debug message.
 *  @param ...              Variable argument list like e.g. in printf.
 */
static inline void
check_pointer
(
    void* pointer,
    char* description,
    ...
)
{
    va_list va;
    va_start( va, description );

    if ( pointer == NULL )
    {
        printf( "==ERROR== " );
        vfprintf( stdout, description, va );
        printf( "\n" );
        exit( EXIT_FAILURE );
    }

    if ( otf2_DEBUG )
    {
        printf( "==DEBUG== " );
        vfprintf( stdout, description, va );
        printf( "\n" );
    }

    va_end( va );
}


/** @internal
 *  @brief Check if status is not OTF2_SUCCESS.
 *
 *  Checks if status is not OTF2_SUCCESS. If so it prints an error with the
 *  passed description and exits the program.
 *  If in debug mode, it prints a debug message with the passed description.
 *  It is possible to passed a variable argument list like e.g. in printf.
 *
 *  @param status           Status to be checked.
 *  @param description      Description for error/debug message.
 *  @param ...              Variable argument list like e.g. in printf.
 */
static inline void
check_status
(
    OTF2_ErrorCode status,
    char*          description,
    ...
)
{
    va_list va;
    va_start( va, description );

    if ( status != OTF2_SUCCESS )
    {
        printf( "==ERROR== " );
        vfprintf( stdout, description, va );
        printf( "\n" );
        exit( EXIT_FAILURE );
    }

    if ( otf2_DEBUG )
    {
        printf( "==DEBUG== " );
        vfprintf( stdout, description, va );
        printf( "\n" );
    }

    va_end( va );
}


/** @brief Pre flush callback.
 *
 *  @param evtWriter        Ignored.
 *  @param evtReader        Ignored.
 *
 *  @return                 Returns always OTF2_NO_FLUSH.
 */
static OTF2_FlushType
pre_flush
(
    void*         userData,
    OTF2_FileType fileType,
    uint64_t      locationId,
    void*         callerData,
    bool          final
)
{
    return OTF2_FLUSH;
}


static OTF2_TimeStamp
post_flush
(
    void*         userData,
    OTF2_FileType fileType,
    uint64_t      locationId
)
{
    return get_time();
}


static inline uint64_t
get_time
(
    void
)
{
    static uint64_t sequence;
    return sequence++;
}

static inline double
gtod
(
    void
)
{
    struct timeval act_time;
    gettimeofday( &act_time, NULL );
    return ( double )act_time.tv_sec + ( double )act_time.tv_usec / 1000000.0;
}

static inline double
smin
(
    double* data,
    int     num_items
)
{
    if ( num_items <= 0 )
    {
        return 0;
    }

    double min = data[ 0 ];
    int    i;
    for ( i = 1; i < num_items; ++i )
    {
        if ( data[ i ] < min )
        {
            min = data[ i ];
        }
    }

    return min;
}

static inline double
smax
(
    double* data,
    int     num_items
)
{
    if ( num_items <= 0 )
    {
        return 0;
    }

    double max = data[ 0 ];
    int    i;
    for ( i = 1; i < num_items; ++i )
    {
        if ( data[ i ] > max )
        {
            max = data[ i ];
        }
    }

    return max;
}

static inline double
savg
(
    double* data,
    int     num_items
)
{
    if ( num_items <= 0 )
    {
        return 0;
    }

    double avg = data[ 0 ];
    int    i;
    for ( i = 1; i < num_items; ++i )
    {
        avg += data[ i ];
    }
    avg = avg / num_items;

    return avg;
}



/* ___ Implementation of callbacks __________________________________________ */



static inline OTF2_CallbackCode
GlobDefLocation_Register( void*                 userData,
                          OTF2_LocationRef      locationIdentifier,
                          OTF2_StringRef        stringID,
                          OTF2_LocationType     locationType,
                          uint64_t              numberOfEvents,
                          OTF2_LocationGroupRef locationGroup )
{
    /* Dummies to suppress compiler warnings for unused parameters. */
    ( void )stringID;
    ( void )locationType;
    ( void )numberOfEvents;
    ( void )locationGroup;

    /* Open a new event reader for each found location ID. */
    OTF2_Reader*    reader     = ( OTF2_Reader* )userData;
    OTF2_EvtReader* evt_reader = OTF2_Reader_GetEvtReader( reader,
                                                           locationIdentifier );
    check_pointer( evt_reader, "Create local event reader for location %llu.",
                   ( long long unsigned )locationIdentifier );

    /* Also open a definition reader and read all definitions. */
    OTF2_DefReader* def_reader = OTF2_Reader_GetDefReader( reader,
                                                           locationIdentifier );
    check_pointer( def_reader, "Create local definition reader for location %llu.",
                   ( long long unsigned )locationIdentifier );

    uint64_t       definitions_read = 0;
    OTF2_ErrorCode status           = OTF2_SUCCESS;
    do
    {
        uint64_t def_reads = 0;
        status            = OTF2_Reader_ReadAllLocalDefinitions( reader, def_reader, &def_reads );
        definitions_read += def_reads;

        /* continue reading, if we have an duplicate mapping table */
        if ( OTF2_ERROR_DUPLICATE_MAPPING_TABLE != status )
        {
            break;
        }
    }
    while ( true );
    check_status( status, "Read %llu definitions for location %llu",
                  ( long long unsigned )definitions_read,
                  ( long long unsigned )locationIdentifier );

    return OTF2_CALLBACK_SUCCESS;
}
