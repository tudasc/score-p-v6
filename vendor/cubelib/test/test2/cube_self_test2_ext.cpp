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
 * \file cubew_example.c
   \brief A small example of using "libcubew4.a".
   One creates a cube file "example.cube", defined structure of metrics, call tree, machine, cartesian topology
   and fills teh severity matrix.
   At the end the file will be written on the disk.
 */
#include "config.h"

#include <cstdio>
#include <stdint.h>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>

#include "Cube.h"




#define CNODES_NUMBER 10
#ifndef NWRITERS
#define NWRITERS 1
#endif


#ifndef CNODES
#define CNODES 180
#endif

#ifndef NTHREADS
#define NTHREADS 1024
#endif

#ifndef COMPRESSION
#define COMPRESSION CUBE_FALSE
#endif

#define NMETRICS 4
#define NTAUMETRICS 7



static int current_random = 0; // uswd to create a stable random loooking sequence of numbers (used for creating of a calltree)
static int MAXDEPTH       = 6;


#define NDIMS 2


using namespace std;
using namespace cube;


void
create_cube_structure( Cube* cube,
                       Metric** metrics,
                       Cnode**  cnodes,
                       unsigned      Nthreads );

void
fill_double_row( double* row,
                           unsigned          size,
                           double            value );
void
fill_double_row_only_masters( double* row, unsigned size,  double value );
void
fill_double_row_only_first_master( double* row, unsigned size, double value );
void
fill_double_row_zero_all( double* row, unsigned size);
void
fill_int64_row( int64_t* row,
                          unsigned         size,
                          int64_t          value );
void
fill_int64_row_only_masters( int64_t* row, unsigned size, int64_t value );
void
fill_int64_row_only_first_master( int64_t* row, unsigned size, int64_t value );
void
fill_int64_row_zero_all( int64_t* row, unsigned size);


void
create_calltree( Cube*       cube,
                 Region** regn,
                 Cnode**  codes,
                 int*          idx,
                 int*          reg_idx,
                 Cnode*   parent,
                 int           level );
int
get_next_random();
void
set_seed_random( int s );
void
calculate_max_depth();
int
calcaulate_sum2( int start,
                 int finish );

/// Start point of this example.
int
main( int argc, char* argv[] )
{
    calculate_max_depth();

    /// actual number of writers might be different. For code it is transparent.
    unsigned ArraySize = CNODES;    /// In this pattern, number of cnodes

    unsigned Nthreads = NTHREADS;   /// In this pattern, number of threads


    /// Pattern has to know, which metrics are there to perform parallel writing.
    /// To destroy is only this aray, not metrics inside. Metrics are destroyed by "cube_free"
    Metric** metrics_vector = ( Metric** )calloc( NMETRICS, sizeof( Metric* ) );

    // Metric** tau_metrics_vector = ( Metric** )calloc( NTAUMETRICS, sizeof( Metric* ) );


    /// Pattern has to know, which cnodes are there to perform parallel writing.
    /// To destroy is only this aray, not cnodes inside. Cnodes are destroyed by "cube_free"
    Cnode** cnodes_vector = ( Cnode** )calloc( ArraySize, sizeof( Cnode* ) );




    //    FILE* fp = fopen(cubefile, "w");
    Cube* cube = new Cube();
    if ( !cube )
    {
        fprintf( stderr, "cube_create failed!\n" );
        exit( 1 );
    }

    create_cube_structure( cube, metrics_vector, cnodes_vector, Nthreads );


//     double     sev_double[ Nthreads ];
//     int64_t  sev_int64[ Nthreads ];


    unsigned mi = 0;
    for ( mi = 0; mi < NMETRICS; mi++ ) /// run over the metrics
    {
//         carray* sequence = cube_get_cnodes_for_metric( cube, metrics_vector[ mi ] );

        unsigned ci = 0;

        if ( mi == 2)//byte_sent
        {
            ci = 0;
            for ( ci = 0; ci < CNODES; ci++ )
            {
		int64_t * sev_int64 = new int64_t[ Nthreads ];
                if (ci ==74 )//MPI_Isend
                {
                    fill_int64_row_only_masters(sev_int64, Nthreads,ci + mi );
                }
                else
                {
                    fill_int64_row_zero_all( sev_int64, Nthreads );
                }
                cube->set_sevs_raw( metrics_vector[ mi ], cnodes_vector[ ci ], (char*)sev_int64 );

            }
        }
        else if ( mi == 3)//byte_recieve
        {
            ci = 0;
            for ( ci = 0; ci < CNODES; ci++ )
            {
		int64_t * sev_int64 = new int64_t[ Nthreads ];
                if (ci ==76 )//MPI_Waitall
                {
                    fill_int64_row_only_masters(sev_int64, Nthreads,ci + mi );
                }
                else
                {
                    fill_int64_row_zero_all( sev_int64, Nthreads );
                }
                cube->set_sevs_raw( metrics_vector[ mi ], cnodes_vector[ ci ], (char*)sev_int64 );

            }
        }
        else if ( mi == 0)//visits
        {
            for ( ci = 0; ci < CNODES; ci++ )
            {
		int64_t * sev_int64 = new int64_t[ Nthreads ];
		if (ci == 178)
		{
		    fill_int64_row_only_first_master(sev_int64, Nthreads,ci + mi);
		}
		else if ((ci >= 0 && ci <= 15 )||
			    (ci == 38)||
			    (ci >= 53 && ci <= 55 )||
			    (ci == 64)||
			    (ci >= 74 && ci <= 79 )||
			    (ci == 84)||
			    (ci == 86)||
			    (ci == 88)||
			    (ci == 98)||
			    (ci == 104)||
			    (ci == 115)||
			    (ci == 125)||
			    (ci == 134)||
			    (ci >= 138 && ci <= 143 )||
			    (ci == 150)||
			    (ci == 155)||
			    (ci == 157)||
			    (ci == 159)||
			    (ci == 168)||
			    (ci == 171)||
			    (ci == 176)||
			    (ci == 177)||
			    (ci == 179) )
		{
		    fill_int64_row_only_masters(sev_int64, Nthreads,ci + mi+1 );
		}
		else
		{
		    fill_int64_row( sev_int64, Nthreads, ci + mi );
		}
		 cube->set_sevs_raw( metrics_vector[ mi ], cnodes_vector[ ci ], (char* )sev_int64 );
            }
        }
        else if ( mi == 1)//time
        {

            for ( ci = 0; ci < CNODES; ci++ )
            {
		double * sev_double = new double[ Nthreads ];
                int id = cnodes_vector[ ci ]->get_id();
                if((id == 17)||
                    (id >= 20 && id <= 21) ||
                    (id == 23)||
                    (id == 25)||
                    (id == 27)||
                    (id == 29)||
                        (id == 30)||
                        (id == 32)||
                        (id >= 35 && id <= 37)||
                        (id == 41)||
                        (id == 43)||
                        (id >=45 && id <= 47)||
                        (id == 49)||
                        (id >= 50 && id<= 52)||
                        (id == 58)||
                        (id == 59)||
                        (id == 62)||
                        (id == 63)||
                        (id == 67)||
                        (id == 68)||
                        (id >= 72 && id<=73)||
                        (id == 81)||
                        (id == 83)||
                        (id == 85)||
                        (id == 87)||
                        (id >= 90 && id <=92)||
                        (id == 94)||
                        (id == 95)||
                        (id == 97)||
                        (id >= 100 && id<= 103)||
                        (id == 108)||
                        (id >=110 && id<= 114)||
                        (id == 119)||
                        (id == 121)||
                        (id == 124)||
                        (id == 129)||
                        (id >= 131 && id <= 133)||
                        (id == 137)||
                        (id >= 147 && id<= 149)||
                        (id == 152)||
                        (id == 154)||
                        (id == 156)||
                        (id == 158)||
                        (id >= 161 && id <= 165)||
                        (id == 167)||
                        (id == 169)||
                        (id == 170)||
                        (id >= 173 && id <= 175) )
                        fill_double_row(sev_double, Nthreads,0.1);
                else if( (id >= 3 && id <= 7)||
                         (id >= 9 && id <= 10) ||
                         (id >= 12 && id <= 14) ||
                         (id == 53)||
                         (id >= 74 && id<=77)||
                         (id == 84)||
                         (id == 86)||
                         (id == 88)||
                         (id == 98)||
                         (id >= 138 && id<= 139)||
                         (id == 140)||
                         (id == 141)||
                         (id == 155)||
                         (id == 157)||
                         (id == 159)||
                         (id == 168)||
                         (id == 176)||
                         (id == 177)||
                         (id == 179) )
                             fill_double_row(sev_double, Nthreads,0.1);
                else if (id == 178)
                    fill_double_row(sev_double, Nthreads,0.1);
                else if ((id == 19)||
                         (id == 22)||
                         (id == 24)||
                         (id == 26)||
                         (id == 31)||
                         (id == 34)||
                         (id == 40)||
                         (id == 42)||
                         (id == 61)||
                         (id == 66)||
                         (id == 71)||
                         (id == 82)||
                         (id == 89)||
                         (id == 93)||
                         (id == 96)||
                         (id == 99)||
                         (id == 107)||
                         (id == 109)||
                         (id == 118)||
                         (id == 120)||
                         (id == 122)||
                         (id == 123)||
                         (id == 128)||
                         (id == 130)||
                         (id == 136)||
                         (id == 146)||
                         (id == 153)||
                         (id == 160)||
                         (id == 166))
                {
                    fill_double_row(sev_double, Nthreads,0.2);
                }
                else if ((id == 8)||
                         (id == 11))
                {
                    fill_double_row(sev_double, Nthreads,0.2);
                }
                else if (id == 2)
                    fill_double_row(sev_double, Nthreads,0.5);
                else if ((id == 28)||
                         (id == 48)||
                         (id == 57))
                {
                    fill_double_row(sev_double, Nthreads,0.3);
                }
                else if ((id == 44)||
                         (id == 172))
                {
                    fill_double_row(sev_double, Nthreads,0.4);
                }
                else if ((id == 18)||
                         (id == 33)||
                         (id == 56)||
                         (id == 65))
                {
                    fill_double_row(sev_double, Nthreads,0.4);
                }
                else if ((id == 60)||
                         (id == 70)||
                         (id == 135)||
                         (id == 145))
                {
                    fill_double_row(sev_double, Nthreads,0.3);
                }
                else if (id == 39)
                    fill_double_row(sev_double, Nthreads,1.40);
                else if (id == 80)
                    fill_double_row(sev_double, Nthreads,2.30);
                else if (id == 106)
                    fill_double_row(sev_double, Nthreads,0.6);
                else if (id == 117)
                    fill_double_row(sev_double, Nthreads,0.7);
                else if (id == 127)
                    fill_double_row(sev_double, Nthreads,0.6);
                else if (id == 151)
                    fill_double_row(sev_double, Nthreads,2.00);
                else if (id == 171)
                    fill_double_row(sev_double, Nthreads,0.5);
                else if (id == 16)
                    fill_double_row(sev_double, Nthreads,2.20);
                else if (id == 38)
                    fill_double_row(sev_double, Nthreads,1.50);
                else if (id == 55)
                    fill_double_row(sev_double, Nthreads,0.90);
                else if (id == 69)
                    fill_double_row(sev_double, Nthreads,0.40);
                else if (id == 79)
                    fill_double_row(sev_double, Nthreads,2.50);
                else if (id == 105)
                    fill_double_row(sev_double, Nthreads,0.90);
                else if (id == 116)
                    fill_double_row(sev_double, Nthreads,1.00);
                else if (id == 126)
                    fill_double_row(sev_double, Nthreads,0.80);
                else if (id == 134)
                    fill_double_row(sev_double, Nthreads,0.40);
                else if (id == 15)
                    fill_double_row(sev_double, Nthreads,35.30);
                else if (id == 64)
                    fill_double_row(sev_double, Nthreads,1.0);
                else if (id == 104)
                    fill_double_row(sev_double, Nthreads,1.10);
                else if (id == 115)
                    fill_double_row(sev_double, Nthreads,1.10);
                else if (id == 125)
                    fill_double_row(sev_double, Nthreads,0.90);
                else if (id == 144)
                    fill_double_row(sev_double, Nthreads,0.60);
                else if (id == 150)
                    fill_double_row(sev_double, Nthreads,2.10);
                else if (id == 54)
                    fill_double_row(sev_double, Nthreads,2.40);
                else if (id == 78)
                    fill_double_row(sev_double, Nthreads,6.10);
                else if (id == 143)
                    fill_double_row(sev_double, Nthreads,0.70);
                else if (id == 142)
                    fill_double_row(sev_double, Nthreads,3.50);
                else if (id == 1)
                    fill_double_row(sev_double, Nthreads,18);
                else if (id == 0)
                    fill_double_row(sev_double, Nthreads,18.10);
                else
                    fill_double_row(sev_double, Nthreads,0);


         cube->set_sevs_raw( metrics_vector[ mi ], cnodes_vector[ ci ], (char*)sev_double );
            }
        }
    }



   

    free( metrics_vector );               /* content shouldn't be freed, it is done internally by cube */
    free( cnodes_vector );                /* content shouldn't be freed, it is done internally by cube */

    
    cube->writeCubeReport("example3");
        
    printf( "Test file complete.\n" );


    delete cube;
    return 0;
}






void
fill_double_row( double* row, unsigned size, double value )
{
    unsigned i = 0;
  //  printf ("value inside routine %f \n",value);
    for ( i = 0; i < size; i++ )
    {

        row[ i ] = value ;
    }
}
void
fill_double_row_only_masters( double* row, unsigned size,  double value )
{
    unsigned i = 0;

    for ( i = 0; i < size; i++ )
    {
        if ( i % 16 == 0)
            row[ i ] = value ;
        else
            row[ i ] = 0.;
    }
}
void
fill_double_row_only_first_master( double* row, unsigned size, double value )
{
    unsigned i = 0;
    row[ 0 ] = value ;
    for ( i = 1; i < size; i++ )
    {
        row[ i ] = 0.;
    }
}
void
fill_double_row_zero_all( double* row, unsigned size)
{
    unsigned i = 0;
    for ( i = 0; i < size; i++ )
    {
        row[ i ] = 0.;
    }
}
void
fill_int64_row( int64_t* row, unsigned size, int64_t value )
{
    unsigned i = 0;
    for ( i = 0; i < size; i++ )
    {
        row[ i ] = value + i;
    }
}
void
fill_int64_row_only_masters( int64_t* row, unsigned size, int64_t value )
{
    unsigned i = 0;
    
    for ( i =0; i < size; i++ )
    {
        if ( i % 16 == 0)
            row[ i ]  = value + i;
        else
            row[ i ]  = 0;
    }
}
void
fill_int64_row_only_first_master( int64_t* row, unsigned size, int64_t value )
{
    unsigned i = 0;
    row[ 0 ]  = value ;
    for ( i =1; i < size; i++ )
    {
        row[ i ]  = 0;
    }
}
void
fill_int64_row_zero_all( int64_t* row, unsigned size )
{
    unsigned i = 0;
    for ( i = 0; i < size; i++ )
    {
        row[ i ]  = 0;
    }
}




int
calcaulate_sum2( int start, int finish )
{
    int sum = 0;
    int i   = start;
    for ( i = start; i <= finish; i++ )
    {
        sum += i * i;
    }
    return sum;
}




void
create_cube_structure( Cube* cube, Metric** metrics, Cnode** cnodes, unsigned Nthreads )
{
    /* generate header */
    cube->def_mirror( "http://icl.cs.utk.edu/software/kojak/" );
    cube->def_mirror( "http://www.fz-juelich.de/jsc/kojak/" );
    cube->def_attr(  "description", "a simple example" );
    cube->def_attr(  "experiment time", "November 1st, 2004" );

    /* define metric tree */

    metrics[ 0 ] = cube->def_met(  "Visits", "visits", "INTEGER", "occ", "",
                                 "http://www.cs.utk.edu/usr.html",
                                 "Number of visits", NULL,  CUBE_METRIC_EXCLUSIVE );

    metrics[ 1 ] = cube->def_met(  "Time", "time", "FLOAT", "sec", "",
                                 "@mirror@patterns-2.1.html#execution",
                                 "Total CPU allocation time", NULL, CUBE_METRIC_INCLUSIVE );

    metrics[ 2 ] = cube->def_met(  "P2P bytes sent", "bytes_sent", "INTEGER", "bytes", "",
                                 "http://www.cs.utk.edu/sys.html",
                                 "Number of bytes sent in point-to-point operations", NULL,  CUBE_METRIC_EXCLUSIVE );

    metrics[ 3 ] = cube->def_met( "P2P bytes received", "bytes_rcvd", "INTEGER", "bytes", "",
                                 "http://www.cs.utk.edu/sys.html",
                                 "Number of bytes received in point-to-point operations", NULL,  CUBE_METRIC_EXCLUSIVE );



    /* define call tree */

    //      Region *regn0, *regn1, *regn2;

    Region** regn = ( Region** )calloc( 180, sizeof( Region* ) );


    string _names[ 180 ] = {
        "main",
        "MAIN__",
        "mpi_setup_",
        "MPI_Init_thread",
        "MPI_Comm_size",
        "MPI_Comm_rank",
        "MPI_Comm_split",
        "MPI_Bcast",
        "env_setup_",
        "MPI_Bcast",
        "zone_setup_",
        "map_zones_",
        "get_comm_index_",
        "zone_starts_",
        "set_constants_",
        "initialize_",
        "!$omp parallel @initialize.f:28",
        "!$omp do @initialize.f:31",
        "!$omp do @initialize.f:50",
        "exact_solution_",
        "TRACE BUFFER FLUSH",
        "TRACE BUFFER FLUSH",
        "!$omp do @initialize.f:100",
        "exact_solution_",
        "!$omp do @initialize.f:119",
        "exact_solution_",
        "!$omp do @initialize.f:137",
        "exact_solution_",
        "!$omp do @initialize.f:156",
        "exact_solution_",
        "!$omp implicit barrier @initialize.f:167",
        "!$omp do @initialize.f:174",
        "exact_solution_",
        "!$omp do @initialize.f:192",
        "exact_solution_",
        "TRACE BUFFER FLUSH",
        "TRACE BUFFER FLUSH",
        "!$omp implicit barrier @initialize.f:204",
        "exact_rhs_",
        "!$omp parallel @exact_rhs.f:21",
        "!$omp do @exact_rhs.f:31",
        "!$omp implicit barrier @exact_rhs.f:41",
        "!$omp do @exact_rhs.f:46",
        "exact_solution_",
        "!$omp do @exact_rhs.f:147",
        "exact_solution_",
        "!$omp implicit barrier @exact_rhs.f:242",
        "TRACE BUFFER FLUSH",
        "!$omp do @exact_rhs.f:247",
        "exact_solution_",
        "!$omp implicit barrier @exact_rhs.f:341",
        "!$omp do @exact_rhs.f:346",
        "!$omp implicit barrier @exact_rhs.f:357",
        "timer_clear_",
        "exch_qbc_",
        "copy_x_face_",
        "!$omp parallel @exch_qbc.f:255",
        "!$omp do @exch_qbc.f:255",
        "!$omp implicit barrier @exch_qbc.f:264",
        "TRACE BUFFER FLUSH",
        "!$omp parallel @exch_qbc.f:244",
        "!$omp do @exch_qbc.f:244",
        "!$omp implicit barrier @exch_qbc.f:253",
        "TRACE BUFFER FLUSH",
        "copy_y_face_",
        "!$omp parallel @exch_qbc.f:215",
        "!$omp do @exch_qbc.f:215",
        "!$omp implicit barrier @exch_qbc.f:224",
        "TRACE BUFFER FLUSH",
        "!$omp parallel @exch_qbc.f:204",
        "!$omp do @exch_qbc.f:204",
        "!$omp implicit barrier @exch_qbc.f:213",
        "TRACE BUFFER FLUSH",
        "TRACE BUFFER FLUSH",
        "MPI_Isend",
        "MPI_Irecv",
        "MPI_Waitall",
        "TRACE BUFFER FLUSH",
        "adi_",
        "compute_rhs_",
        "!$omp parallel @rhs.f:28",
        "!$omp do @rhs.f:37",
        "!$omp do @rhs.f:62",
        "!$omp implicit barrier @rhs.f:72",
        "!$omp master @rhs.f:74",
        "!$omp do @rhs.f:80",
        "!$omp master @rhs.f:183",
        "!$omp do @rhs.f:191",
        "!$omp master @rhs.f:293",
        "!$omp do @rhs.f:301",
        "!$omp implicit barrier @rhs.f:353",
        "!$omp do @rhs.f:359",
        "!$omp do @rhs.f:372",
        "!$omp do @rhs.f:384",
        "TRACE BUFFER FLUSH",
        "!$omp do @rhs.f:400",
        "!$omp do @rhs.f:413",
        "!$omp implicit barrier @rhs.f:423",
        "!$omp master @rhs.f:424",
        "!$omp do @rhs.f:428",
        "TRACE BUFFER FLUSH",
        "!$omp implicit barrier @rhs.f:439",
        "TRACE BUFFER FLUSH",
        "TRACE BUFFER FLUSH",
        "x_solve_",
        "!$omp parallel @x_solve.f:46",
        "!$omp do @x_solve.f:54",
        "lhsinit_",
        "TRACE BUFFER FLUSH",   
        "binvrhs_",
        "TRACE BUFFER FLUSH",
        "TRACE BUFFER FLUSH",
        "!$omp implicit barrier @x_solve.f:407",
        "TRACE BUFFER FLUSH",
        "TRACE BUFFER FLUSH",
        "y_solve_",
        "!$omp parallel @y_solve.f:43",
        "!$omp do @y_solve.f:52",
        "lhsinit_",
        "TRACE BUFFER FLUSH",
        "binvrhs_",
        "TRACE BUFFER FLUSH",
        "TRACE BUFFER FLUSH",
        "!$omp implicit barrier @y_solve.f:406",
        "TRACE BUFFER FLUSH",
        "z_solve_",
        "!$omp parallel @z_solve.f:43",
        "!$omp do @z_solve.f:52",
        "lhsinit_",
        "TRACE BUFFER FLUSH",
        "binvrhs_",
        "TRACE BUFFER FLUSH",
        "TRACE BUFFER FLUSH",
        "!$omp implicit barrier @z_solve.f:428",
        "add_",
        "!$omp parallel @add.f:22",
        "!$omp do @add.f:22",
        "!$omp implicit barrier @add.f:33",
        "MPI_Barrier",
        "timer_start_",
        "timer_stop_",
        "timer_read_",
        "verify_",
        "error_norm_",
        "!$omp parallel @error.f:27",
        "!$omp do @error.f:33",
        "exact_solution_",
        "TRACE BUFFER FLUSH",
        "!$omp atomic @error.f:51",
        "!$omp implicit barrier @error.f:54",
        "compute_rhs_",
        "!$omp parallel @rhs.f:28",
        "!$omp do @rhs.f:37",
        "!$omp do @rhs.f:62",
        "!$omp implicit barrier @rhs.f:72",
        "!$omp master @rhs.f:74",
        "!$omp do @rhs.f:80",
        "!$omp master @rhs.f:183",
        "!$omp do @rhs.f:191",
        "!$omp master @rhs.f:293",
        "!$omp do @rhs.f:301",
        "!$omp implicit barrier @rhs.f:353",
        "!$omp do @rhs.f:359",
        "!$omp do @rhs.f:372",
        "!$omp do @rhs.f:384",
        "!$omp do @rhs.f:400",
        "!$omp do @rhs.f:413",
        "!$omp implicit barrier @rhs.f:423",
        "!$omp master @rhs.f:424",
        "!$omp do @rhs.f:428",
        "!$omp implicit barrier @rhs.f:439",
        "rhs_norm_",
        "!$omp parallel @error.f:86",
        "!$omp do @error.f:91",
        "!$omp atomic @error.f:104",
        "!$omp implicit barrier @error.f:107",
        "MPI_Reduce",
        "MPI_Reduce",
        "print_results_",
        "MPI_Finalize"    };

    vector<string> names (_names, _names + 180); 
	
    string mod ("/home/geimer/Examples/NPB3.3-MZ-MPI/BT-MZ/mpi_setup.prep.opari.F");
    string paradigm ("compiler");
    string role ("function");
    long beg,end;
    for ( unsigned i = 0; i < 180; i++ )
    {

        if ((i >= 0 && i<= 2) ||
                (i == 8) ||
                (i >= 10 && i<= 15) ||
                (i == 19) ||
                (i == 21) ||
                (i == 23) ||
                (i == 25) ||
                (i == 27) ||
                (i == 30) ||
                (i == 32) ||
                (i == 34) ||
                (i == 39) ||
                (i == 41) ||
                (i == 44) ||
                (i >= 48 && i<= 50) ||
                (i == 57) ||
                (i == 67) ||
                (i == 68) ||
                (i == 89) ||
                (i == 92) ||
                (i == 93) ||
                (i == 96) ||
                (i == 99) ||
                (i == 100) ||
                (i == 102) ||
                (i == 105) ||
                (i == 106) ||
                (i == 109) ||
                (i >= 114 && i<= 118) ||
                (i == 121) ||
                (i == 124) ||
                (i == 145) ||
                (i == 152) )
        {
            mod = "/home/geimer/Examples/NPB3.3-MZ-MPI/BT-MZ/mpi_setup.prep.opari.F";
            paradigm="compiler";
            end = -1;
            beg = -1;
            role="function";
        }
        else if ((i >= 154 && i<= 179) ||
                 (i == 94) ||
                 (i == 107)  )
        {
            mod = "";
            paradigm="measurement_system";
            end = -1;
            beg = -1;
            role="artificial";
        }
        else if ((i >= 3 && i<= 6) ||
                 (i == 153)  )
        {
            mod = "MPI";
            paradigm="mpi";
            end = -1;
            beg = -1;
            role="function";
        }
        else if ((i == 7) ||
                 (i == 9)  )
        {
            mod = "MPI";
            paradigm="mpi";
            end = -1;
            beg = -1;
            role="one2all";
        }
        else if ((i == 113)  )
        {
            mod = "MPI";
            paradigm="mpi";
            end = -1;
            beg = -1;
            role="barrier";
        }
        else if ((i >= 64 && i <= 66)   )
        {
            mod = "MPI";
            paradigm="mpi";
            end = -1;
            beg = -1;
            role="point2point";
        }
        else if ((i == 150) ||
                 (i == 151)  )
        {
            mod = "MPI";
            paradigm="mpi";
            end = -1;
            beg = -1;
            role="all2one";
        }
        else if ( (i == 16) ||
                  (i == 35) ||
                  (i == 51) ||
                  (i == 54) ||
                  (i == 58) ||
                  (i == 61) ||
                  (i == 69) ||
                  (i == 90) ||
                  (i == 97) ||
                  (i == 103) ||
                  (i == 110) ||
                  (i == 119) ||
                  (i == 125) ||
                  (i == 146) )
        {
            mod = "/home/geimer/Examples/NPB3.3-MZ-MPI/BT-MZ/mpi_setup.prep.opari.F";
            paradigm="openmp";
            end = -1;
            beg = -1;
            role="parallel";
        }
        else if ( (i == 28) ||
                  (i == 33) ||
                  (i == 37) ||
                  (i == 42) ||
                  (i == 45) ||
                  (i == 47) ||
                  (i == 53) ||
                  (i == 56) ||
                  (i == 60) ||
                  (i == 63) ||
                  (i == 72) ||
                  (i == 79) ||
                  (i == 85) ||
                  (i == 88) ||
                  (i == 95) ||
                  (i == 101) ||
                  (i == 108) ||
                  (i == 112) ||
                  (i == 123) ||
                  (i == 128) ||
                  (i == 135) ||
                  (i == 141) ||
                  (i == 144) ||
                  (i == 149))
        {
            mod = "/home/geimer/Examples/NPB3.3-MZ-MPI/BT-MZ/mpi_setup.prep.opari.F";
            paradigm="openmp";
            end = -1;
            beg = -1;
            role="implicit barrier";
        }
        else if ( (i == 73) ||
                  (i == 75) ||
                  (i == 77) ||
                  (i == 86) ||
                  (i == 129) ||
                  (i == 131) ||
                  (i == 133) ||
                  (i == 142) )
        {
            mod = "/home/geimer/Examples/NPB3.3-MZ-MPI/BT-MZ/mpi_setup.prep.opari.F";
            paradigm="openmp";
            end = -1;
            beg = -1;
            role="master";
        }
        else if ( (i == 122) ||
                  (i == 148) )
        {
            mod = "/home/geimer/Examples/NPB3.3-MZ-MPI/BT-MZ/mpi_setup.prep.opari.F";
            paradigm="openmp";
            end = -1;
            beg = -1;
            role="atomic";
        }
        else
        {
            mod = "/home/geimer/Examples/NPB3.3-MZ-MPI/BT-MZ/mpi_setup.prep.opari.F";
            paradigm="openmp";
            end = -1;
            beg = -1;
            role="loop";
        }

        regn[ i ] = cube->def_region( names[ i ], names[ i ], paradigm, role,  beg, end, "", "", mod );
    }

    //     create calltree
    srand( 0 );
    int idx        = 0;
    int region_idx = 0;
    //   create_calltree( cube, regn, cnodes, &idx, &region_idx,  NULL, 0 );
    cnodes[0] = cube->def_cnode( regn[0], NULL);
    cnodes[1] = cube->def_cnode( regn[1], cnodes[0]);
    cnodes[2] = cube->def_cnode( regn[2], cnodes[1]);
    for (int i=3 ; i < 7; i++)
        cnodes[i] = cube->def_cnode( regn[i], cnodes[2]);
    for (int i=7 ; i < 9; i++)
        cnodes[i] = cube->def_cnode( regn[i], cnodes[1]);
    cnodes[9] = cube->def_cnode( regn[9], cnodes[8]);

    for (int i=10 ; i < 12; i++)
        cnodes[i] = cube->def_cnode( regn[i], cnodes[1]);
    cnodes[12] = cube->def_cnode( regn[12], cnodes[11]);
    for (int i=13 ; i < 16; i++)
        cnodes[i] = cube->def_cnode( regn[i], cnodes[1]);
    cnodes[16] = cube->def_cnode( regn[16], cnodes[15]);
    for (int i=17 ; i < 19; i++)
        cnodes[i] = cube->def_cnode( regn[i], cnodes[16]);
    cnodes[19] = cube->def_cnode( regn[19], cnodes[18]);

    cnodes[20] = cube->def_cnode( regn[20], cnodes[19]);
    cnodes[21] = cube->def_cnode( regn[21], cnodes[18]);
    cnodes[22] = cube->def_cnode( regn[22], cnodes[16]);
    cnodes[23] = cube->def_cnode( regn[23], cnodes[22]);
    cnodes[24] = cube->def_cnode( regn[24], cnodes[16]);
    cnodes[25] = cube->def_cnode( regn[25], cnodes[24]);
    cnodes[26] = cube->def_cnode( regn[26], cnodes[16]);
    cnodes[27] = cube->def_cnode( regn[27], cnodes[26]);
    cnodes[28] = cube->def_cnode( regn[28], cnodes[16]);
    for (int i=29 ; i < 31; i++)
        cnodes[i] = cube->def_cnode( regn[i], cnodes[28]);

    cnodes[31] = cube->def_cnode( regn[31], cnodes[16]);
    cnodes[32] = cube->def_cnode( regn[32], cnodes[31]);
    cnodes[33] = cube->def_cnode( regn[33], cnodes[16]);
    cnodes[34] = cube->def_cnode( regn[34], cnodes[33]);
    cnodes[35] = cube->def_cnode( regn[35], cnodes[34]);
    cnodes[36] = cube->def_cnode( regn[36], cnodes[33]);
    cnodes[37] = cube->def_cnode( regn[37], cnodes[16]);
    cnodes[38] = cube->def_cnode( regn[38], cnodes[1]);
    cnodes[39] = cube->def_cnode( regn[39], cnodes[38]);

    cnodes[40] = cube->def_cnode( regn[40], cnodes[39]);
    cnodes[41] = cube->def_cnode( regn[41], cnodes[40]);
    cnodes[42] = cube->def_cnode( regn[42], cnodes[39]);
    cnodes[43] = cube->def_cnode( regn[43], cnodes[42]);
    cnodes[44] = cube->def_cnode( regn[44], cnodes[39]);
    cnodes[45] = cube->def_cnode( regn[45], cnodes[44]);
    cnodes[46] = cube->def_cnode( regn[46], cnodes[44]);
    cnodes[47] = cube->def_cnode( regn[47], cnodes[44]);
    cnodes[48] = cube->def_cnode( regn[48], cnodes[39]);
    cnodes[49] = cube->def_cnode( regn[49], cnodes[48]);

    cnodes[50] = cube->def_cnode( regn[50], cnodes[48]);
    cnodes[51] = cube->def_cnode( regn[51], cnodes[39]);
    cnodes[52] = cube->def_cnode( regn[52], cnodes[39]);
    cnodes[53] = cube->def_cnode( regn[53], cnodes[1]);
    cnodes[54] = cube->def_cnode( regn[54], cnodes[1]);
    cnodes[55] = cube->def_cnode( regn[55], cnodes[54]);
    cnodes[56] = cube->def_cnode( regn[56], cnodes[55]);
    cnodes[57] = cube->def_cnode( regn[57], cnodes[56]);
    cnodes[58] = cube->def_cnode( regn[58], cnodes[57]);
    cnodes[59] = cube->def_cnode( regn[59], cnodes[57]);

    cnodes[60] = cube->def_cnode( regn[60], cnodes[55]);
    cnodes[61] = cube->def_cnode( regn[61], cnodes[60]);
    cnodes[62] = cube->def_cnode( regn[62], cnodes[61]);
    cnodes[63] = cube->def_cnode( regn[63], cnodes[55]);
    cnodes[64] = cube->def_cnode( regn[64], cnodes[54]);
    cnodes[65] = cube->def_cnode( regn[65], cnodes[64]);
    cnodes[66] = cube->def_cnode( regn[66], cnodes[65]);
    cnodes[67] = cube->def_cnode( regn[67], cnodes[66]);
    cnodes[68] = cube->def_cnode( regn[68], cnodes[65]);
    cnodes[69] = cube->def_cnode( regn[69], cnodes[64]);

    cnodes[70] = cube->def_cnode( regn[70], cnodes[69]);
    cnodes[71] = cube->def_cnode( regn[71], cnodes[70]);
    cnodes[72] = cube->def_cnode( regn[72], cnodes[71]);
    cnodes[73] = cube->def_cnode( regn[73], cnodes[64]);
    cnodes[74] = cube->def_cnode( regn[74], cnodes[54]);
    cnodes[75] = cube->def_cnode( regn[75], cnodes[54]);
    cnodes[76] = cube->def_cnode( regn[76], cnodes[54]);
    cnodes[77] = cube->def_cnode( regn[77], cnodes[54]);
    cnodes[78] = cube->def_cnode( regn[78], cnodes[1]);
    cnodes[79] = cube->def_cnode( regn[79], cnodes[78]);

    cnodes[80] = cube->def_cnode( regn[80], cnodes[79]);
    cnodes[81] = cube->def_cnode( regn[81], cnodes[80]);
    cnodes[82] = cube->def_cnode( regn[82], cnodes[80]);
    cnodes[83] = cube->def_cnode( regn[83], cnodes[82]);
    cnodes[84] = cube->def_cnode( regn[84], cnodes[80]);
    cnodes[85] = cube->def_cnode( regn[85], cnodes[80]);
    cnodes[86] = cube->def_cnode( regn[86], cnodes[80]);
    cnodes[87] = cube->def_cnode( regn[87], cnodes[80]);
    cnodes[88] = cube->def_cnode( regn[88], cnodes[80]);
    cnodes[89] = cube->def_cnode( regn[89], cnodes[80]);

    cnodes[90] = cube->def_cnode( regn[90], cnodes[89]);
    cnodes[91] = cube->def_cnode( regn[91], cnodes[80]);
    cnodes[92] = cube->def_cnode( regn[92], cnodes[80]);
    cnodes[93] = cube->def_cnode( regn[93], cnodes[80]);
    cnodes[94] = cube->def_cnode( regn[94], cnodes[93]);
    cnodes[95] = cube->def_cnode( regn[95], cnodes[80]);
    cnodes[96] = cube->def_cnode( regn[96], cnodes[80]);
    cnodes[97] = cube->def_cnode( regn[97], cnodes[96]);
    cnodes[98] = cube->def_cnode( regn[98], cnodes[80]);
    cnodes[99] = cube->def_cnode( regn[99], cnodes[80]);

    cnodes[100] = cube->def_cnode( regn[100], cnodes[99]);
    cnodes[101] = cube->def_cnode( regn[101], cnodes[80]);
    cnodes[102] = cube->def_cnode( regn[102], cnodes[80]);
    cnodes[103] = cube->def_cnode( regn[103], cnodes[79]);
    cnodes[104] = cube->def_cnode( regn[104], cnodes[78]);
    cnodes[105] = cube->def_cnode( regn[105], cnodes[104]);
    cnodes[106] = cube->def_cnode( regn[106], cnodes[105]);
    cnodes[107] = cube->def_cnode( regn[107], cnodes[106]);
    cnodes[108] = cube->def_cnode( regn[108], cnodes[107]);
    cnodes[109] = cube->def_cnode( regn[109], cnodes[106]);

    cnodes[110] = cube->def_cnode( regn[110], cnodes[109]);
    cnodes[111] = cube->def_cnode( regn[111], cnodes[106]);
    cnodes[112] = cube->def_cnode( regn[112], cnodes[105]);
    cnodes[113] = cube->def_cnode( regn[113], cnodes[105]);
    cnodes[114] = cube->def_cnode( regn[114], cnodes[104]);
    cnodes[115] = cube->def_cnode( regn[115], cnodes[78]);
    cnodes[116] = cube->def_cnode( regn[116], cnodes[115]);
    cnodes[117] = cube->def_cnode( regn[117], cnodes[116]);
    cnodes[118] = cube->def_cnode( regn[118], cnodes[117]);
    cnodes[119] = cube->def_cnode( regn[119], cnodes[118]);

    cnodes[120] = cube->def_cnode( regn[120], cnodes[117]);
    cnodes[121] = cube->def_cnode( regn[121], cnodes[120]);
    cnodes[122] = cube->def_cnode( regn[122], cnodes[117]);
    cnodes[123] = cube->def_cnode( regn[123], cnodes[116]);
    cnodes[124] = cube->def_cnode( regn[124], cnodes[123]);
    cnodes[125] = cube->def_cnode( regn[125], cnodes[78]);
    cnodes[126] = cube->def_cnode( regn[126], cnodes[125]);
    cnodes[127] = cube->def_cnode( regn[127], cnodes[126]);
    cnodes[128] = cube->def_cnode( regn[128], cnodes[127]);
    cnodes[129] = cube->def_cnode( regn[129], cnodes[128]);

    cnodes[130] = cube->def_cnode( regn[130], cnodes[127]);
    cnodes[131] = cube->def_cnode( regn[131], cnodes[130]);
    cnodes[132] = cube->def_cnode( regn[132], cnodes[127]);
    cnodes[133] = cube->def_cnode( regn[133], cnodes[126]);
    cnodes[134] = cube->def_cnode( regn[134], cnodes[78]);
    cnodes[135] = cube->def_cnode( regn[135], cnodes[134]);
    cnodes[136] = cube->def_cnode( regn[136], cnodes[135]);
    cnodes[137] = cube->def_cnode( regn[137], cnodes[136]);
    cnodes[138] = cube->def_cnode( regn[138], cnodes[1]);
    cnodes[139] = cube->def_cnode( regn[139], cnodes[1]);

    cnodes[140] = cube->def_cnode( regn[140], cnodes[1]);
    cnodes[141] = cube->def_cnode( regn[141], cnodes[1]);
    cnodes[142] = cube->def_cnode( regn[142], cnodes[1]);
    cnodes[143] = cube->def_cnode( regn[143], cnodes[142]);
    cnodes[144] = cube->def_cnode( regn[144], cnodes[143]);
    cnodes[145] = cube->def_cnode( regn[145], cnodes[144]);
    cnodes[146] = cube->def_cnode( regn[146], cnodes[145]);
    cnodes[147] = cube->def_cnode( regn[147], cnodes[146]);
    cnodes[148] = cube->def_cnode( regn[148], cnodes[144]);
    cnodes[149] = cube->def_cnode( regn[149], cnodes[144]);

    cnodes[150] = cube->def_cnode( regn[150], cnodes[142]);
    cnodes[151] = cube->def_cnode( regn[151], cnodes[150]);
    cnodes[152] = cube->def_cnode( regn[152], cnodes[151]);
    cnodes[153] = cube->def_cnode( regn[153], cnodes[151]);
    cnodes[154] = cube->def_cnode( regn[154], cnodes[153]);
    cnodes[155] = cube->def_cnode( regn[155], cnodes[151]);
    cnodes[156] = cube->def_cnode( regn[156], cnodes[151]);
    cnodes[157] = cube->def_cnode( regn[157], cnodes[151]);
    cnodes[158] = cube->def_cnode( regn[158], cnodes[151]);
    cnodes[159] = cube->def_cnode( regn[159], cnodes[151]);

    cnodes[160] = cube->def_cnode( regn[160], cnodes[151]);
    cnodes[161] = cube->def_cnode( regn[161], cnodes[160]);
    cnodes[162] = cube->def_cnode( regn[162], cnodes[151]);
    cnodes[163] = cube->def_cnode( regn[163], cnodes[151]);
    cnodes[164] = cube->def_cnode( regn[164], cnodes[151]);
    cnodes[165] = cube->def_cnode( regn[165], cnodes[151]);
    cnodes[166] = cube->def_cnode( regn[166], cnodes[151]);
    cnodes[167] = cube->def_cnode( regn[167], cnodes[166]);
    cnodes[168] = cube->def_cnode( regn[168], cnodes[151]);
    cnodes[169] = cube->def_cnode( regn[169], cnodes[151]);

    cnodes[170] = cube->def_cnode( regn[170], cnodes[151]);
    cnodes[171] = cube->def_cnode( regn[171], cnodes[142]);
    cnodes[172] = cube->def_cnode( regn[172], cnodes[171]);
    cnodes[173] = cube->def_cnode( regn[173], cnodes[172]);
    cnodes[174] = cube->def_cnode( regn[174], cnodes[172]);
    cnodes[175] = cube->def_cnode( regn[175], cnodes[172]);
    cnodes[176] = cube->def_cnode( regn[176], cnodes[142]);
    cnodes[177] = cube->def_cnode( regn[177], cnodes[1]);
    cnodes[178] = cube->def_cnode( regn[178], cnodes[1]);
    cnodes[179] = cube->def_cnode( regn[179], cnodes[1]);





    /* define location tree */
    Machine* mach  = cube->def_mach( "MSC", "" );
    Node*    node  = cube->def_node( "Athena", mach );
    char str[80];
    int proc_num = Nthreads / 16 ;
    for ( unsigned j = 0 ; j < proc_num ; j++)
    {
        sprintf(str, "Proc  %i", j);
        Process* proc0 = cube->def_proc( str, j, node );
        for ( unsigned i = 0; i < 16; i++ )
        {
            sprintf(str, "Thread  %i", i);
            Thread* thrd0 = cube->def_thrd( str, i, proc0 );
            thrd0 = NULL;
        }
        proc0 = NULL;
    }

    free( regn );







    cube->set_statistic_name( "mystat" );

    cube->set_metrics_title( "Metric tree (QMCD App <ver.34>)" );
    cube->set_calltree_title( "Calltree (serial run, #2345)" );
    cube->set_systemtree_title( "System  ( Linux cluster < 43 & 23 >)" );

    cube->initialize();
}








int
get_next_random()
{
    current_random = ( current_random + 5 ) % 13;
    return current_random;
}

void
set_seed_random( int s )
{
    current_random = s;
}



void
create_calltree( Cube* cube, Region** regn, Cnode** cnodes, int* idx, int* region_idx,  Cnode* parent, int level )
{
    if ( ( *idx ) >= CNODES )
    {
        return;
    }
    if ( level >= MAXDEPTH )
    {
        return;
    }
    int _num_children = get_next_random();
    for ( unsigned i = 0; i < _num_children; i++ )
    {
        unsigned rand_reg = *region_idx;
        *region_idx = ( ( *region_idx + 1 ) % 180 );      // cyclic selection of regions
        Cnode* cnode = cube->def_cnode(  regn[ rand_reg ], parent );
        cnodes[ *idx ] = cnode;
        ( *idx )++;
        create_calltree( cube, regn, cnodes, idx, region_idx, cnode, level + 1 );
        if ( ( *idx ) >= CNODES )
        {
            return;                            // for the case, inside of those function was reached the end of array
        }
    }
}





void
calculate_max_depth()
{
    MAXDEPTH = ( int )( log( (double)CNODES ) / log( 13. ) ) + 2;
}
