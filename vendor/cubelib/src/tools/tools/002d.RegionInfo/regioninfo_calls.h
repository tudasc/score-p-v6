/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2017                                                **
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



#ifndef __CUBE_REGIONINFO_CALLS_H
#define __CUBE_REGIONINFO_CALLS_H


// string lowercase(const string& str);
/**
 * A collection of all costs (??) for a region.
 */
struct tracefile_costs
{
    vector<unsigned long long> acc_costs_by_region;
    vector<unsigned long long> max_costs_by_region;

    unsigned long long         acc_all;
    unsigned long long         acc_bl;
    unsigned long long         acc_com;
    unsigned long long         acc_mpi;
    unsigned long long         acc_usr;

    unsigned long long         acc_com_bl;
    unsigned long long         acc_mpi_bl;
    unsigned long long         acc_usr_bl;

    vector<unsigned long long> pt_all;
    vector<unsigned long long> pt_bl;
    vector<unsigned long long> pt_wbl;
    vector<unsigned long long> pt_com;
    vector<unsigned long long> pt_mpi;
    vector<unsigned long long> pt_usr;
    vector<unsigned long long> pt_com_bl;
    vector<unsigned long long> pt_mpi_bl;
    vector<unsigned long long> pt_usr_bl;

    unsigned long long         max_all;
    unsigned long long         max_bl;
    unsigned long long         max_wbl;
    unsigned long long         max_com;
    unsigned long long         max_mpi;
    unsigned long long         max_usr;
    unsigned long long         max_com_bl;
    unsigned long long         max_mpi_bl;
    unsigned long long         max_usr_bl;

    tracefile_costs( size_t rcnt,
                     size_t tcnt )
        : acc_costs_by_region( rcnt, 0 ),
        max_costs_by_region( rcnt, 0 ),
        pt_all( tcnt, 0 ),
        pt_bl( tcnt, 0 ),
        pt_wbl( tcnt, 0 ),
        pt_com( tcnt, 0 ),
        pt_mpi( tcnt, 0 ),
        pt_usr( tcnt, 0 ),
        pt_com_bl( tcnt, 0 ),
        pt_mpi_bl( tcnt, 0 ),
        pt_usr_bl( tcnt, 0 )

    {
        acc_all    = 0;
        acc_bl     = 0;
        acc_com    = 0;
        acc_mpi    = 0;
        acc_usr    = 0;
        acc_com_bl = 0;
        acc_mpi_bl = 0;
        acc_usr_bl = 0;
        max_all    = 0;
        max_bl     = 0;
        max_wbl    = 0;
        max_com    = 0;
        max_mpi    = 0;
        max_usr    = 0;
        max_com_bl = 0;
        max_mpi_bl = 0;
        max_usr_bl = 0;
    }
/**
 * A method of a collection, allows to get the maximum values for all kinds of regions.
 */
    void
    calculate_maxima()
    {
        max_all    = find_max( pt_all ).first;
        max_bl     = find_max( pt_bl ).first;
        max_wbl    = find_max( pt_wbl ).first;
        max_com    = find_max( pt_com ).first;
        max_mpi    = find_max( pt_mpi ).first;
        max_usr    = find_max( pt_usr ).first;
        max_com_bl = find_max( pt_com_bl ).first;
        max_mpi_bl = find_max( pt_mpi_bl ).first;
        max_usr_bl = find_max( pt_usr_bl ).first;
    }
};


/// @cond PROTOTYPES
tracefile_costs
calculate_tracefile_costs( AggrCube*,
                           const CRegionInfo&,
                           CBlacklist* );

/// @endcond
/**
 * A collection about all data for a given metric.
 */
template<typename T>
struct metric_data
{
    Metric*              metric; ///< metric.
    std::string          name;   ///< Name of the metric.
    AggrCube*            acube;  ///< CUBE with the information.
    T                    bl;     ///< Black listed code.
    T                    com;    ///< Communication.
    T                    com_bl; ///< Blacklisted communcation.
    T                    mpi;    ///< MPI code
    T                    mpi_bl; ///< Blacklisted MPI
    T                    total;  ///< Total.
    T                    usr;    ///< User defined code.
    T                    usr_bl; ///< Blacklisted user define code.
    map<Region*, double> excl;   ///< Excusiv value.
    map<Region*, double> incl;   ///< Incusive value.
    map<Region*, double> diff;   ///< Difference of inclusive and excusive value

    metric_data()
    {
        bl     = T( 0 );
        com    = T( 0 );
        com_bl = T( 0 );
        mpi    = T( 0 );
        mpi_bl = T( 0 );
        total  = T( 0 );
        usr    = T( 0 );
        usr_bl = T( 0 );
        metric = 0;
        acube  = 0;
    };

/**
 * Returns a type of the metric value.
 */
    bool
    isfloat()
    {
        if ( metric != 0 )
        {
            return metric->get_dtype() == "FLOAT";
        }
        else
        {
            return false;
        }
    }
};
/**
 *  Calculates a percent.
 */
template<class S, class T>
double
percent( S total, T costs )
{
    if ( total != 0 )
    {
        return 100.0 * ( double )costs / ( double )total;
    }
    else
    {
        return 0.0;
    }
}
/**
 * Prints a usage of this tool.
 */
void
usage( const char* filename )
{
    cout << "Usage: " << filename << " [-l filename] [-m filename] [-h] [-s] cubefile\n";
    cout << "  -h     Help; Output this help message\n";
    cout << "  -r     be verbose, print info about any region\n";
    cout << "  -l     Specify a list of regions for the blacklist\n";
    cout << "  -m     Specify a list of metrics, the list has to be comma-seperated, no spaces allowed\n";
    exit( EXIT_SUCCESS );
};
/**
 * Accumulate usr, mpi, com and total values in md.
 */
template<class T>
void
acc_with_type( metric_data<T>& md, CRegionInfo& reginfo, CBlacklist* blacklist )
{
    /*
       accumulate usr, mpi, com and total values in md
     */
    typename std::map<Region*, double>::const_iterator it;
    for ( it = md.excl.begin(); it != md.excl.end(); it++ )
    {
        T             nv( ( T )it->second );
        const Region* region( it->first );

        md.total += nv;
        switch ( reginfo[ region->get_id() ] )
        {
            case MPI:
                md.mpi += nv;
                break;

            case COM:
                md.com += nv;
                break;

            case USR:
                md.usr += nv;
                break;
            default: // another regions are not observed at all and will be ignored
                break;
        }

        if ( blacklist != 0 )
        {
            if ( ( *blacklist )( region->get_id() ) )
            {
                md.bl += nv;
            }
            else
            {
                switch ( reginfo[ region->get_id() ] )
                {
                    case MPI:
                        md.mpi_bl += nv;
                        break;

                    case COM:
                        md.com_bl += nv;
                        break;

                    case USR:
                        md.usr_bl += nv;
                        break;
                    default: // another regions are not observed at all and will be ignored
                        break;
                }
            }
        }
    }
}



/**
 * Calculate a cost ( given as a severity value mulpilied wih a factor ) for
   every region for every thread. Calculate a cost for every kind of regions
   (usr, mpi, omp, and so on) over all threads. And get a maximum value at the end.
 */
tracefile_costs
calculate_tracefile_costs( AggrCube* input, const CRegionInfo& reginfo, CBlacklist* blacklist )
{
    const vector<Region*>& regions = input->get_regv();
//     const vector<Cnode*>&   cnodes  = input->get_cnodev(); // unsused
    const vector<Thread*>& threads = input->get_thrdv();

    const size_t rcnt = regions.size();
    const size_t tcnt = threads.size();

    tracefile_costs tbcosts = tracefile_costs( rcnt, tcnt );

    Metric* visits = input->get_met( "visits" );

    /* accumulated costs on a per thread basis */
    for ( size_t i = 0; i < rcnt; i++ )
    {
        const Region*              region = regions[ i ];
        const unsigned long long   d      = TypeFactor( region->get_name() );
        const vector<Cnode*>&      cnodev = region->get_cnodev();
        const size_t               ccnt   = cnodev.size();
        vector<unsigned long long> buffer = vector<unsigned long long>( tcnt, 0 );

        for ( size_t j = 0; j < ccnt; j++ )
        {
            Cnode*                 cnode   = cnodev[ j ];
            const vector<Thread*>& threads = input->get_thrdv();
            const size_t           tcnt    = threads.size();
            for ( size_t ThreadId = 0; ThreadId < tcnt; ThreadId++ )
            {
                Thread* thread = threads[ ThreadId ];


                const unsigned long long newval = static_cast<unsigned long long>( input->get_sev( visits, cnode, thread ) );
                const unsigned long long costs  = newval * d;
                buffer[ ThreadId ]               += costs;
                tbcosts.pt_all[ ThreadId ]       += costs;
                tbcosts.acc_costs_by_region[ i ] += costs;
                if ( blacklist != 0 )
                {
                    if ( ( *blacklist )( ( Region* )region ) )
                    {
                        tbcosts.pt_bl[ ThreadId ] += costs;
                    }
                    else
                    {
                        switch ( reginfo[ i ] )
                        {
                            case MPI:
                                tbcosts.pt_mpi_bl[ ThreadId ] += costs;
                                break;

                            case USR:
                                tbcosts.pt_usr_bl[ ThreadId ] += costs;
                                break;

                            case COM:
                                tbcosts.pt_com_bl[ ThreadId ] += costs;
                                break;
                            default: // another regions are not observed at all and will be ignored
                                break;
                        }
                        tbcosts.pt_wbl[ ThreadId ] += costs;
                    }
                }

                switch ( reginfo[ i ] )
                {
                    case MPI:
                        tbcosts.pt_mpi[ ThreadId ] += costs;
                        break;

                    case USR:
                        tbcosts.pt_usr[ ThreadId ] += costs;
                        break;

                    case COM:
                        tbcosts.pt_com[ ThreadId ] += costs;
                        break;
                    default: // another regions are not observed at all and will be ignored
                        break;
                }
            }
        }

        unsigned long long max_costs = find_max( buffer ).first;
        if ( tbcosts.max_costs_by_region[ i ] < max_costs )
        {
            tbcosts.max_costs_by_region[ i ] = max_costs;
        }
    }

    /*
       BEGIN: calculate total costs split by category (mpi, com, usr, blacklist) using get_met_tree(...)
     */

    for ( size_t regionId = 0; regionId < regions.size(); regionId++ )
    {
        Region*               region = regions[ regionId ];
        const vector<Cnode*>& cnodev( region->get_cnodev() );
        unsigned long long    d = TypeFactor( region->get_name() );
        for ( size_t cnodeId = 0; cnodeId < cnodev.size(); cnodeId++ )
        {
            map<Metric*, double> excl_metrics;
            map<Metric*, double> incl_metrics;
            Cnode*               cnode = cnodev[ cnodeId ];
            input->get_met_tree( excl_metrics, incl_metrics, EXCL, INCL, cnode, 0 );
            Metric* metric = input->get_met( "visits" );

            unsigned long long visits( ( unsigned long long )excl_metrics[ metric ] );
            unsigned long long nc = d * visits;

            tbcosts.acc_all += nc;

            if ( blacklist != 0 )
            {
                if ( ( *blacklist )( ( Region* )region ) )
                {
                    tbcosts.acc_bl += nc;
                }
                else
                {
                    switch ( reginfo[ regionId ] )
                    {
                        case MPI:
                            tbcosts.acc_mpi_bl += nc;
                            break;
                        case USR:
                            tbcosts.acc_usr_bl += nc;
                            break;
                        case COM:
                            tbcosts.acc_com_bl += nc;
                            break;
                        default: // another regions are not observed at all and will be ignored
                            break;
                    }
                }
            }

            switch ( reginfo[ regionId ] )
            {
                case MPI:
                    tbcosts.acc_mpi += nc;
                    break;
                case USR:
                    tbcosts.acc_usr += nc;
                    break;
                case COM:
                    tbcosts.acc_com += nc;
                    break;
                default: // another regions are not observed at all and will be ignored
                    break;
            }
        }
    }

    /*
       DONE: calculate total costs split by category (mpi, com, usr, blacklist) using get_met_tree(...)
     */

    /*
       BEGIN: accumulute per thread data items
     */

    tbcosts.calculate_maxima();

    /*
       END: accumulute per thread data items
     */

    return tbcosts;
}




#endif
