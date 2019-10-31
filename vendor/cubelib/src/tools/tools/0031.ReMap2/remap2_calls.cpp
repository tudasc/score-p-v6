/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2019                                                **
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


#include "config.h"
#include <cstdio>

#include "remap2_calls.h"


using namespace cube;
using namespace remapper;


/**
 * An attempt to use xtprocadmin mapfile to remap Cray XT nodenames
 * and generate topologies (based on cabinets and mesh)
 */
void
remapper::node_remap( Cube& newCube, std::string dirname )
{
    // verify first node has (unmapped) name in expected format "node<NID>"
    const std::vector<Node*>&          nodev = newCube.get_nodev();
    std::vector<Node*>::const_iterator nit   = nodev.begin();
    if ( nit == nodev.end() ) // no nodes - perhaps flexible system tree - no node remap is needed
    {
        return;
    }

    std::string node_name = ( *nit )->get_name();
    if ( node_name.substr( 0, 4 ) != "node" )
    {
        // std::cerr << "First node has unexpected name " << node_name << std::endl;
        return;
    }

    std::string   mapname = "./xtnids";
    std::ifstream in( mapname.c_str() );
    if ( !in )   // no map found in current directory
    {
        if ( dirname.empty() )
        {
            return;
        }
        mapname.erase( 0, 1 );
        mapname.insert( 0, dirname );
        in.clear();
        in.open( mapname.c_str() );
        if ( !in )
        {
            return;     // no map found in given (epik) directory
        }
        // XXXX should also check installdir
    }
    std::cout << "Remapping " << nodev.size() << " nodes using " << mapname << std::endl;

    const std::string header1 = "   NID    (HEX)    NODENAME     TYPE ARCH        OS CORES";
    const std::string header2 = "   NID    (HEX)    NODENAME     TYPE ARCH        OS CPUS";
    char              linebuf[ 1024 ];

    in.getline( linebuf, 1024 );
    if ( ( strncmp( linebuf, header1.c_str(), header1.length() ) != 0 ) &&
         ( strncmp( linebuf, header2.c_str(), header2.length() ) != 0 ) )
    {
        std::cerr << "Error: Map header mismatch:" << std::endl << linebuf << std::endl;
        return;
    }

    unsigned           CagesPerCbnt = 3; // typical cabinet configuration, but may need to be adjusted
    unsigned           SlotsPerCage = 8; // "
    unsigned           NodesPerSlot = 4; // "
    unsigned           CoresPerNode = 0;
    unsigned           minCABX      = 1000;
    unsigned           maxCABX      = 0, maxCABY = 0;
    std::vector<char*> xtnidnames( 1024, ( char* )NULL );
    char               nodetype[ 16 ], nodearch[ 16 ], nodeos[ 16 ];

    // parse each map entry for nid & nodename to store in std::vector of xtnidnames
    // additionally parse each nodename to determine cabinet ranges

    while ( !in.eof() )
    {
        in.getline( linebuf, 1024 );
        if ( in.gcount() == 0 )
        {
            continue;
        }

        unsigned nid, hex, cores;
        char*    nodename = ( char* )calloc( 16, 1 );
        if ( 7 != sscanf( linebuf, "%u %x %16s %s %s %s %u", &nid, &hex,
                          nodename, nodetype, nodearch, nodeos, &cores ) )
        {
            // down compute nodes ('X' in xtstat) have incomplete data
            if ( 4 == sscanf( linebuf, "%u %x %16s %s", &nid, &hex,
                              nodename, nodetype ) )
            {
                std::cerr << "Info: skipping down compute node " << nodename << std::endl;
            }
            else
            {
                std::cerr << "Error: Invalid map entry:" << std::endl << linebuf << std::endl;
            }
        }
        else if ( nid != hex )
        {
            std::cerr << "Error: Inconsistent nid " << nid << "<>" << hex << std::endl;
        }
        else
        {
            // std::cout << "Parsed: nid=" << nid << " name=" << (nodename ? nodename : "(nil)")
            //     << " cores=" << cores << std::endl;
            while ( nid >= xtnidnames.size() )
            {
                xtnidnames.resize( xtnidnames.size() + 1024, ( char* )NULL );
            }
            xtnidnames[ nid ] = nodename;
            if ( cores > CoresPerNode )
            {
                CoresPerNode = cores;
            }
            unsigned CABX, CABY, CAGE, SLOT, NODE;
            if ( nodename[ 0 ] == 'r' ) // x2 compute node?
            {                           // std::cerr << "Ignoring unexpected nodename " << nodename << " for nid " << nid << std::endl;
            }
            else
            if ( 5 != sscanf( nodename, "c%u-%uc%us%un%u", &CABX, &CABY, &CAGE, &SLOT, &NODE ) )
            {
                std::cerr << "Error: Unparsable nodename " << nodename << " for nid " << nid << std::endl;
            }
            else
            {
                if ( CABY > maxCABY )
                {
                    maxCABY = CABY;
                }
                if ( CABX > maxCABX )
                {
                    maxCABX = CABX;
                }
                if ( CABX < minCABX )
                {
                    minCABX = CABX;
                }
                if ( CAGE >= CagesPerCbnt )
                {
                    CagesPerCbnt = CAGE + 1;
                }
                if ( SLOT >= SlotsPerCage )
                {
                    SlotsPerCage = SLOT + 1;
                }
                if ( NODE >= NodesPerSlot )
                {
                    NodesPerSlot = NODE + 1;
                }
            }
        }
    }

    // Define new topologies
    std::vector<bool>        periodv( 3 ), altperiodv( 6 );
    std::vector<long>        dimv( 3 ), altdimv( 6 ), coordv( 3 ), altcoordv( 6 );
    std::vector<std::string> altnamev( 6 );

    char* env = getenv( "XT_NODE_CORES" );
    if ( env )
    {
        int cores = atoi( env );
        if ( cores > 0 )
        {
            CoresPerNode = cores;
            std::cout << "Using XT_NODE_CORES=" << CoresPerNode << std::endl;
        }
        else
        {
            std::cerr << "Ignoring invalid XT_NODE_CORES=" << env << std::endl;
        }
    }
    std::cout << "Using " << CoresPerNode << " cores per XT node" << std::endl;
    // plain topology with separate dimensions
    altperiodv[ 0 ] = false;
    altnamev[ 0 ]   = "CabX";
    altdimv[ 0 ]    = maxCABX + 1;
    altperiodv[ 1 ] = false;
    altnamev[ 1 ]   = "CabY";
    altdimv[ 1 ]    = maxCABY + 1;
    altperiodv[ 2 ] = false;
    altnamev[ 2 ]   = "Cage";
    altdimv[ 2 ]    = CagesPerCbnt;
    altperiodv[ 3 ] = false;
    altnamev[ 3 ]   = "Slot";
    altdimv[ 3 ]    = SlotsPerCage;
    altperiodv[ 4 ] = false;
    altnamev[ 4 ]   = "Node";
    altdimv[ 4 ]    = NodesPerSlot;
    altperiodv[ 5 ] = false;
    altnamev[ 5 ]   = "Core";
    altdimv[ 5 ]    = CoresPerNode;
    Cartesian* xtTopoCart = newCube.def_cart( 6, altdimv, altperiodv );
    xtTopoCart->set_name( "XT Topology" );
    xtTopoCart->set_namedims( altnamev );
    // cabinet topology

    periodv[ 0 ] = false;
    dimv[ 0 ]    = ( ( maxCABY + 1 ) * SlotsPerCage ) * CoresPerNode;
    periodv[ 1 ] = false;
    dimv[ 1 ]    = CagesPerCbnt * NodesPerSlot;
    periodv[ 2 ] = false;
    dimv[ 2 ]    = maxCABX + 1;              // (max) number of cabinets
    Cartesian* xtCabsCart = newCube.def_cart( 3, dimv, periodv );
    xtCabsCart->set_name( "XT NodeStat" );

    std::cout << "Generating " << dimv[ 0 ] << "*" << dimv[ 1 ] << "*" << dimv[ 2 ]
              << " topology for " << maxCABX + 1 << "*" << maxCABY + 1
              << " Cray XT cabinets (" << CagesPerCbnt << " cages, "
              << SlotsPerCage << " slots, " << NodesPerSlot << " nodes)" << std::endl;
    // Remap nodes
    while ( nit != nodev.end() )
    {
        std::string node_name = ( *nit )->get_name();
        unsigned    nid       = atoi( node_name.substr( 4 ).c_str() );
        if ( node_name.substr( 0, 4 ) != "node" )
        {
            std::cerr << "Leaving node with unexpected name " << node_name << std::endl;
        }
        else if ( ( nid >= xtnidnames.size() ) || !xtnidnames[ nid ] )
        {
            std::cerr << "Skipping " << node_name << " without nid mapping" << std::endl;
        }
        else
        {
            unsigned CABX, CABY, CAGE, SLOT, NODE;
            sscanf( xtnidnames[ nid ], "c%u-%uc%us%un%u", &CABX, &CABY, &CAGE, &SLOT, &NODE );
            ( *nit )->set_name( xtnidnames[ nid ] );

            unsigned cabsX = CABY * SlotsPerCage + SLOT;
            unsigned cabsY = CAGE * NodesPerSlot + NODE;
            unsigned cabsZ = CABX;


            unsigned processesOnNode = ( *nit )->num_groups();
            for ( unsigned p = 0; p < processesOnNode; p++ )
            {
                Process* proc    = ( *nit )->get_location_group( p );
                unsigned threads = proc->num_children();
                for ( unsigned t = 0; t < threads; t++ )
                {
                    unsigned core = ( t * processesOnNode ) + p;
                    if ( core >= CoresPerNode )
                    {
                        std::cout << core << ">=" << CoresPerNode
                                  << ": Skipping coordinate mapping for over-subscribed compute node!" << std::endl;
                        continue;
                    }
                    Thread* thrd = proc->get_child( t );
                    coordv[ 0 ] = cabsX * CoresPerNode + core;
                    coordv[ 1 ] = cabsY;
                    coordv[ 2 ] = cabsZ;
                    // NB: coord checks only valid for single topology
                    if ( coordv[ 0 ] >= dimv[ 0 ] )
                    {
                        std::cerr << xtnidnames[ nid ] << ": " << coordv[ 0 ] << ">=" << dimv[ 0 ]
                                  << ": Skipping x-coordinate out of range!" << std::endl;
                        continue;
                    }
                    if ( coordv[ 1 ] >= dimv[ 1 ] )
                    {
                        std::cerr << xtnidnames[ nid ] << ": " << coordv[ 1 ] << ">=" << dimv[ 1 ]
                                  << ": Skipping y-coordinate out of range!" << std::endl;
                        continue;
                    }
                    if ( coordv[ 2 ] >= dimv[ 2 ] )
                    {
                        std::cerr << xtnidnames[ nid ] << ": " << coordv[ 2 ] << ">=" << dimv[ 2 ]
                                  << ": Skipping z-coordinate out of range!" << std::endl;
                        continue;
                    }
                    xtCabsCart->def_coords( thrd, coordv );
                    // plain topology
                    altcoordv[ 0 ] = CABX;
                    altcoordv[ 1 ] = CABY;
                    altcoordv[ 2 ] = CAGE;
                    altcoordv[ 3 ] = SLOT;
                    altcoordv[ 4 ] = NODE;
                    altcoordv[ 5 ] = core;
                    xtTopoCart->def_coords( thrd, altcoordv );
                }
            }
#if DEBUG
            std::cout << node_name << " : " << xtnidnames[ nid ]
                      << " : " << CABX << "/" << CABY << "/" << CAGE << "/" << SLOT << "/" << NODE
                      << " (" << cabsX << "," << cabsY << "," << cabsZ << ")"
                      << std::endl;
#endif
        }
        ++nit;
    }
}









/**
 * Creates a new cube with manually specified list of metrics. Calculates
   exclusive and inclusive values for metrics and fills severities.
 *
 * only for DOUBLE METRIC
 *
 */
void
remapper::cube_remap( AggrCube*           outCube,
                      Cube*               inCube,
                      const std::string&  specname,
                      const std::string&  dirname,
                      bool                convert,
                      bool                add_scalasca_threads,
                      bool                skip_omp,
                      bool                copy_cube_structure,
                      DataDropCombination drop )
{
    std::istream* specin;

    if ( specname.compare( "__NO_SPEC__" ) == 0 )
    {
        std::string       speccontent;
        std::string       name    = "remapping.spec";
        std::vector<char> content = inCube->get_misc_data( name );
        if ( content.size() == 0 )
        {
            throw RuntimeError( "No remapping specification found inside of the cube." );
        }
        else
        {
            std::cout << "Found remapping specification file inside of cube. Use it." << std::endl;
        }


        for ( std::vector<char>::iterator _iter = content.begin(); _iter != content.end(); ++_iter )
        {
            speccontent += *_iter;
        }


        std::stringstream* _specin = new std::stringstream( speccontent );
        specin = _specin;
    }
    else
    {
        std::ifstream* _specin = new std::ifstream();
        _specin->open( specname.c_str(), std::ios::in );
        if ( _specin->fail() )
        {
            delete _specin;
            throw RuntimeError( "No remapping specification file (" + specname + ") found." );
        }
        specin = _specin;
    }


    cube_remap( outCube, inCube, *specin, dirname, convert, add_scalasca_threads, skip_omp, copy_cube_structure, drop );
    delete specin;
}


/**
 * Creates a new cube with manually specified list of metrics. Calculates
   exclusive and inclusive values for metrics and fills severities.
 *
 * only for DOUBLE METRIC
 *
 */
void
remapper::cube_remap( AggrCube*           outCube,
                      Cube*               inCube,
                      std::istream&       specin,
                      const std::string&  dirname,
                      bool                convert,
                      bool                add_scalasca_threads,
                      bool,
                      bool                copy_cube_structure,
                      DataDropCombination drop )
{
    AggrCube*                 tmpCube = NULL;
    remapparser::ReMapDriver* driver  = NULL;
    try
    {
        std::cout << "Create cube according the remapping specification..." << std::endl;
        AggrCube* working_cube;

        if ( copy_cube_structure )
        {
            tmpCube = new AggrCube( *inCube );
        }
        else
        {
            tmpCube = new AggrCube();
        }

        if ( !convert )
        {
            working_cube = outCube; // we do not convert derived metrics into data
        }
        else
        {
            working_cube = tmpCube; // we convert derived metrics into data. Working via temporary cube.
        }

        if ( !copy_cube_structure )
        {
            working_cube->set_post_initialization( true );
            driver = new remapparser::ReMapDriver();
            driver->parse_stream( specin, *working_cube );


            delete driver;
        }
        // Define mirror & attributes
        working_cube->def_attr( "CUBE_CT_AGGR", "SUM" );
        // Copy severities & topology
        CubeMapping inMap;
        // Re-map or merge hierarchies

        const std::vector<std::string>&          __mirrors = inCube->get_mirrors();
        std::vector<std::string>::const_iterator iter1;
        for ( iter1 = __mirrors.begin(); iter1 != __mirrors.end(); ++iter1 )
        {
            const std::vector<std::string>&          __already_mirrors = working_cube->get_mirrors();
            std::vector<std::string>::const_iterator iter2             = __already_mirrors.begin();
            for (; iter2 != __already_mirrors.end(); ++iter2 )
            {
                if ( ( *iter2 ).compare( *iter1 ) == 0 )
                {
                    continue;
                }
            }
            if ( iter2  == __already_mirrors.end() || iter2  == __already_mirrors.begin() )
            {
                working_cube->def_mirror( *iter1 );
            }
        }

        metric_remap( *working_cube, *inCube, inMap );          // false -> do not convert derived metrics, but create first a copy.
        cnode_merge( *working_cube, *inCube, inMap, true );     // true -> we copy ids. and do not create new
        set_region_urls( *working_cube );
        sysres_merge( *working_cube, *inCube, inMap, false, false );

        node_remap( *working_cube, dirname );    // update nodes and topologies


        add_top( *working_cube, *inCube, inMap );
        working_cube->initialize();
        set_sevs( *working_cube, *inCube, inMap, OLD_CUBE_DROP );

        working_cube->setup_cubepl_memory();
        working_cube->compile_derived_metric_expressions();
        working_cube->set_post_initialization( false );

        // at this point we dont need inCube anymore -> destroy it and release memory.
        delete inCube;

        if ( add_scalasca_threads ) // here one calculates scalsca metrics "idle threads" and "limited parallelizm" and adds their value to metric "time"
        {
            std::cout << " Add scalasca specific metrics ..." << std::endl;
            Metric*                    omp_time     = working_cube->get_met( "omp_time" );
            const bool                 includes_omp = ( omp_time != NULL && !( omp_time->isInactive() ) );
            const std::vector<Cnode*>& cnodev       = working_cube->get_cnodev();
            if ( includes_omp )
            {
                std::cout << " Add metrics \"idle threads\" and \"limited parallelism\"..." << std::flush;
                Metric* time   = working_cube->get_met( "time" );
                Metric* limpar = working_cube->get_met( "omp_limited_parallelism" );
                Metric* idleth = working_cube->get_met( "omp_idle_threads" );

                const std::vector<LocationGroup*>& procv     = working_cube->get_location_groupv();
                size_t                             num_procs = procv.size();


                // scan call-tree for OpenMP parallel regions
                bool                in_parallel = false;
                size_t              preg_level  = UINT_MAX;
                size_t              num_thrds   = working_cube->get_locationv().size();
                std::vector<double> tvalues( num_thrds );
                Cnode*              preg = NULL;

                std::vector<Cnode*>::const_iterator it = cnodev.begin();
                while ( it != cnodev.end() )
                {
                    const Region* region = ( *it )->get_callee();
                    const size_t  level  = ( *it )->indent().length() / 2;
                    if ( level <= preg_level )
                    {
                        if ( is_omp( region ) )
                        {
                            preg_level = level;
                        }
                        else
                        {
                            preg_level = UINT_MAX;
                        }
                        if ( preg )
                        {
                            // const Region* region = preg->get_callee();
                            // printf("%s inclusive times:\n", region->get_name().c_str());
                            for ( size_t t = 0; t < num_thrds; ++t )
                            {
                                Location* thread = working_cube->get_locationv()[ t ];
                                Location* master = thread->get_parent()->get_child( 0 );
                                double    mvalue = tvalues[ master->get_id() ];
                                double    idled  = mvalue - tvalues[ t ];
                                if ( idled < 1e-10 )
                                {
                                    continue;      // ignore values below measurement threshold
                                }
                                working_cube->set_sev( limpar, preg, thread, idled );
                                working_cube->add_sev( idleth, preg, thread, idled );
                                working_cube->add_sev( time, preg, thread, idled );
                            }
                            preg = NULL; // no longer in parallel region
                        }
                    }
                    in_parallel = ( preg_level != UINT_MAX );
                    // printf("%d-%s:%d %s%s\n", level, region->get_descr().c_str(), in_parallel,
                    //         (*it)->indent().c_str(), region->get_name().c_str());

                    if ( in_parallel ) // accumulate inclusive execution time in parallel region
                    {
                        if ( !preg )
                        {
                            preg = *it; // stash current parallel region
                            // const Region* region = preg->get_callee();
                            // printf("%s stashed at level %d\n", region->get_name().c_str(), preg_level);
                            for ( size_t t = 0; t < num_thrds; ++t )
                            {
                                tvalues[ t ] = 0.0;
                            }
                        }
                        for ( size_t t = 0; t < num_thrds; ++t )
                        {
                            Location* thread = working_cube->get_locationv()[ t ];
                            double    value  = working_cube->get_sev( time, *it, thread );
                            tvalues[ thread->get_id() ] += value;
                        }
                    }
                    else  // master's serial time is idle time for workers
                    {
                        for ( size_t p = 0; p < num_procs; ++p )
                        {
                            LocationGroup* proc       = procv[ p ];
                            const size_t   proc_thrds = proc->num_children();
                            Location*      master     = proc->get_child( 0 );
                            double         value      = working_cube->get_sev( time, *it, master );
                            // printf("    %s %.6f\n", master->get_name().c_str(), value);

                            for ( size_t t = 1; t < proc_thrds; ++t )
                            {
                                Location* worker = proc->get_child( t );
                                working_cube->set_sev( idleth, *it, worker, value );
                                working_cube->add_sev( time, *it, worker, value );
                                // printf("    %s -> %.6f\n", worker->get_name().c_str(), value);
                            }
                        }
                    }

                    ++it;
                }

                if ( preg ) // still have last parallel region stashed
                {           // const Region* region = preg->get_callee();
                    // printf("%s inclusive times:\n", region->get_name().c_str());
                    for ( size_t t = 0; t < num_thrds; ++t )
                    {
                        Thread* thread = working_cube->get_thrdv()[ t ];
                        Thread* master = thread->get_parent()->get_child( 0 );
                        double  mvalue = tvalues[ master->get_id() ];
                        double  idled  = mvalue - tvalues[ t ];
                        if ( idled < 1e-10 )
                        {
                            continue;      // ignore values below measurement threshold
                        }
                        working_cube->set_sev( limpar, preg, thread, idled );
                        working_cube->add_sev( idleth, preg, thread, idled );
                        working_cube->add_sev( time, preg, thread, idled );
                    }
                }
            }
            std::cout << "done." << std::endl; // idle threads and limited parallelism output


// imbalance heuristics
//             First get some metrics:
            std::cout << " Add metrics \"load imbalance\"..." << std::endl;
            Metric* exec = working_cube->get_met( "comp" );
            if ( exec == NULL )
            {
                exec = working_cube->get_met( "execution" );
            }
            Metric* visits = working_cube->get_met( "visits" );
            Metric* imbal  = working_cube->get_met( "imbalance" );
            Metric* above  = working_cube->get_met( "imbalance_above" );
            Metric* single = working_cube->get_met( "imbalance_above_single" );
            Metric* below  = working_cube->get_met( "imbalance_below" );
            Metric* bypass = working_cube->get_met( "imbalance_below_bypass" );
            Metric* bysing = working_cube->get_met( "imbalance_below_singularity" );


            // Calculate load imbalance heuristic
            std::vector<double> average;
            std::vector<double> dummy;
            size_t              num_cnodes  = working_cube->get_cnodev().size();
            size_t              num_threads = working_cube->get_thrdv().size();
            size_t              num_procs   = working_cube->get_procv().size();

            std::cout << "      Determine numbers of void processes and threads to ignore..." << std::flush;
            size_t void_procs = 0, void_thrds = 0;
            for ( size_t p = 0; p < working_cube->get_procv().size(); p++ )
            {
                Process* proc = working_cube->get_procv()[ p ];
                if ( proc->get_name().find( "VOID" ) != std::string::npos )
                {
                    void_procs++;
                    void_thrds += proc->num_children();
                }
            }
            std::cout << "done." << std::endl;

            if ( num_threads == 1 )
            {
                if ( imbal != NULL )
                {
                    imbal->set_val( "VOID" );
                }
            }

            std::cout << "      Calculate average exclusive execution time..." << std::flush;
            working_cube->get_cnode_tree( average, dummy, EXCL, INCL, exec, NULL );
            std::cout << "done." << std::endl;
            for ( size_t cid = 0; cid < num_cnodes; ++cid )
            {
                Cnode* cnode = cnodev[ cid ];

                /* Inside parallel region? */
                bool is_parallel = false;
                if ( includes_omp )
                {
                    while ( cnode && !is_parallel )
                    {
                        is_parallel = is_omp_parallel( cnode->get_callee()->get_name() );
                        cnode       = cnode->get_parent();
                    }
                }

                if ( is_parallel )
                {
                    average[ cid ] = average[ cid ] / ( num_threads - void_thrds );
                }
                else
                {
                    average[ cid ] = average[ cid ] / ( num_procs - void_procs );
                }
            }

            std::cout << "      Calculate difference to average value..." << std::flush;
            for ( size_t tid = 0; tid < num_threads; ++tid )
            {
                Thread* thread = working_cube->get_thrdv()[ tid ];

                /* Skip threads on void processes */
                if ( thread->get_parent()->get_name().find( "VOID" ) != std::string::npos )
                {
                    continue;
                }

                /* Skip worker threads for pure MPI */
                if ( ( !includes_omp ) && thread->get_rank() != 0 )
                {
                    continue;
                }

                for ( size_t cid = 0; cid < num_cnodes; ++cid )
                {
                    Cnode* cnode = cnodev[ cid ];

                    /* Inside parallel region? */
                    bool   is_parallel = false;
                    Cnode* tmp_cnode   = cnode;
                    while ( tmp_cnode && !is_parallel )
                    {
                        is_parallel = is_omp_parallel( tmp_cnode->get_callee()->get_name() );
                        tmp_cnode   = tmp_cnode->get_parent();
                    }

                    /* Ignore worker threads when outside parallel region */
                    if ( !is_parallel && thread->get_rank() != 0 )
                    {
                        continue;
                    }

                    double sev  = working_cube->get_vcsev( EXCL, EXCL, EXCL, exec, cnode, ( Sysres* )thread );
                    double diff = sev - average[ cid ];

                    if ( diff > 0 )
                    {
                        working_cube->set_sev( imbal, cnode, thread, diff );
                        working_cube->set_sev( above, cnode, thread, diff );
                    }
                    else if ( diff < 0 )
                    {
                        working_cube->set_sev( imbal, cnode, thread, -diff );
                        working_cube->set_sev( below, cnode, thread, -diff );
                    }
                }
            }

            std::cout << "done." << std::endl << " Add metrics \"imbalance due to singularities and imperfect parallelization\"..." << std::flush;

            // resolve computational imbalance due to singularities and imperfect parallelization
            for ( size_t cid = 0; cid < num_cnodes; ++cid )
            {
                unsigned visitors = 0;
                Cnode*   cnode    = cnodev[ cid ];
                double   imbsev   = average[ cid ];

                if ( imbsev == 0.0 )
                {
                    continue;
                }

                if ( includes_omp )
                {
                    /* Inside parallel region? */
                    bool   is_parallel = false;
                    Cnode* tmp_cnode   = cnode;
                    while ( tmp_cnode && !is_parallel )
                    {
                        is_parallel = is_omp_parallel( tmp_cnode->get_callee()->get_name() );
                        tmp_cnode   = tmp_cnode->get_parent();
                    }

                    /* Ignore OpenMP threads when outside parallel region */
                    if ( !is_parallel )
                    {
                        continue;
                    }
                }

                for ( size_t tid = 0; tid < num_threads; ++tid )
                {
                    Thread* thread = working_cube->get_thrdv()[ tid ];
                    if ( thread->get_parent()->get_name().find( "VOID" ) != std::string::npos )
                    {
                        continue;
                    }
                    int nvisits = ( int )working_cube->get_sev( visits, cnode, thread );
                    if ( nvisits )
                    {
                        visitors++;
                    }
                }

                if ( visitors == ( num_threads - void_thrds ) )
                {
                    continue;
                }

                for ( size_t tid = 0; tid < num_threads; ++tid )
                {
                    Thread* thread = working_cube->get_thrdv()[ tid ];
                    if ( thread->get_parent()->get_name().find( "VOID" ) != std::string::npos )
                    {
                        continue;
                    }
                    int nvisits = ( int )working_cube->get_sev( visits, cnode, thread );
                    if ( nvisits == 0 )
                    {
                        working_cube->set_sev( bypass, cnode, thread, imbsev );
                    }
                    if ( visitors == 1 ) // executed by a single participant
                    {
                        if ( nvisits == 0 )
                        {
                            working_cube->set_sev( bysing, cnode, thread, imbsev );
                        }
                        else
                        {
                            working_cube->set_sev( single, cnode, thread, imbsev * ( num_threads - void_thrds - 1 ) );
                        }
                    }
                }
            }
            std::cout << "done." << std::endl;
        }   // if (add_scalasca_threads)


        if ( convert ) // here we have to recalculate values and fill the output cube
        {
            const std::vector<std::string>&          __mirrors = working_cube->get_mirrors();
            std::vector<std::string>::const_iterator iter1;
            for ( iter1 = __mirrors.begin(); iter1 != __mirrors.end(); ++iter1 )
            {
                const std::vector<std::string>           __already_mirrors = outCube->get_mirrors();
                std::vector<std::string>::const_iterator iter2             = __already_mirrors.begin();
                for (; iter2 != __already_mirrors.end(); ++iter2 )
                {
                    if ( ( *iter2 ).compare( *iter1 ) == 0 )
                    {
                        continue;
                    }
                }
                if ( iter2  == __already_mirrors.end() || iter2  == __already_mirrors.begin() )
                {
                    outCube->def_mirror( *iter1 );
                }
            }



            outCube->set_post_initialization( true );
            std::cout << "Copy values of derived metric into target cube... " << std::endl;
            // here we copy final hierarchy without derived metrics  (using old copy_tree call)
            CubeMapping          inMap2;
            std::vector<Metric*> all_metrics = working_cube->get_ghost_metv();
            for ( std::vector<Metric*>::const_iterator miter = working_cube->get_root_metv().begin(); miter != working_cube->get_root_metv().end(); ++miter )
            {
                all_metrics.push_back( *miter );
            }


            for ( std::vector<Metric*>::const_iterator miter = all_metrics.begin(); miter != all_metrics.end(); ++miter )
            {
                if ( ( *miter )->isInactive() )
                {
                    continue;
                }
                Metric* _met = NULL;
                if ( !( ( *miter )->isConvertible() ) )    // not convertible
                {
                    _met = outCube->def_met( ( *miter )->get_disp_name(), ( *miter )->get_uniq_name(),
                                             ( *miter )->get_dtype(), ( *miter )->get_uom(), ( *miter )->get_val(),
                                             ( *miter )->get_url(), ( *miter )->get_descr(), NULL, ( *miter )->get_type_of_metric(),
                                             ( *miter )->get_expression(),
                                             ( *miter )->get_init_expression(),
                                             ( *miter )->get_aggr_plus_expression(),
                                             ( *miter )->get_aggr_minus_expression(),
                                             ( *miter )->get_aggr_aggr_expression(),
                                             ( *miter )->isRowWise(),
                                             ( *miter )->isGhost() ? CUBE_METRIC_GHOST : CUBE_METRIC_NORMAL
                                             );
                    _met->setConvertible( ( *miter )->isConvertible() );
                }
                else
                {
                    _met = outCube->def_met( ( *miter )->get_disp_name(), ( *miter )->get_uniq_name(),
                                             ( *miter )->get_dtype(), ( *miter )->get_uom(), ( *miter )->get_val(),
                                             ( *miter )->get_url(), ( *miter )->get_descr(), NULL, CUBE_METRIC_INCLUSIVE,
                                             ( *miter )->get_expression(),
                                             ( *miter )->get_init_expression(),
                                             ( *miter )->get_aggr_plus_expression(),
                                             ( *miter )->get_aggr_minus_expression(),
                                             ( *miter )->get_aggr_aggr_expression(),
                                             ( *miter )->isRowWise(),
                                             ( *miter )->isGhost() ? CUBE_METRIC_GHOST : CUBE_METRIC_NORMAL );
                }
                if ( _met == NULL ) // it is convertible. but not inclusive
                {
                    _met = outCube->def_met( ( *miter )->get_disp_name(), ( *miter )->get_uniq_name(),
                                             ( *miter )->get_dtype(), ( *miter )->get_uom(), ( *miter )->get_val(),
                                             ( *miter )->get_url(), ( *miter )->get_descr(), NULL, CUBE_METRIC_EXCLUSIVE,
                                             ( *miter )->get_expression(),
                                             ( *miter )->get_init_expression(),
                                             ( *miter )->get_aggr_plus_expression(),
                                             ( *miter )->get_aggr_minus_expression(),
                                             ( *miter )->get_aggr_aggr_expression(),
                                             ( *miter )->isRowWise(),
                                             ( *miter )->isGhost() ? CUBE_METRIC_GHOST : CUBE_METRIC_NORMAL );
                }
                inMap2.metm[ ( *miter ) ] = _met;
                inMap2.r_metm[ _met ]     = ( *miter );
                copy_tree( *outCube, *( *miter ), inMap2, COPY_TO_INCLUSIFY, true );
            }

            cnode_merge( *outCube, *working_cube, inMap2, true );       // true -> we copy ids...
            set_region_urls( *outCube );
            sysres_merge( *outCube, *working_cube, inMap2, false, false );

            node_remap( *outCube, dirname );    // update nodes and topologies


            add_top( *outCube, *working_cube, inMap2 );

            outCube->initialize();
            outCube->setup_cubepl_memory();
            outCube->compile_derived_metric_expressions();
            outCube->set_post_initialization( false );
            set_sevs( *outCube, *working_cube, inMap2, drop );
            delete tmpCube; // we do not use tmpCube in this case
        }                   // if ( convert )
    }
    catch ( RuntimeError e )
    {
        std::cerr << e;
        delete tmpCube; // we do not use tmpCube in this case
        throw;
    }

    return;
}
