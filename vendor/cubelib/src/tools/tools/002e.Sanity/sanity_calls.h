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



#ifndef __CUBE_SANITY_CALLS_H
#define __CUBE_SANITY_CALLS_H

#include "algebra4.h"
#include "algebra4-internals.h"

#ifdef CUBE_COMPRESSED
#  include "CubeZfstream.h"
#endif

#include "MdAggrCube.h"
#include "CnodeConstraint.h"
#include "RegionConstraint.h"
#include "PrintableCCnode.h"
#include "CCnode.h"
#include "CRegion.h"
#include "Filter.h"

#include "Cube.h"
#include "CubeCnode.h"
#include "CubeRegion.h"
#include "CubeError.h"
#include "CubeServices.h"

#define CUBE_SANITY_INTERNAL_ERROR -1
#define CUBE_SANITY_OK 0
#define CUBE_SANITY_TESTS_FAILED 1



class NameNotEmptyOrUnknown : public RegionConstraint
{
public:
    NameNotEmptyOrUnknown( CnodeSubForest* forest )
        : RegionConstraint( forest )
    {
    }

    virtual std::string
    get_name()
    {
        return "Name not empty or UNKNOWN";
    }
    virtual std::string
    get_description()
    {
        return
            "Checks whether the name of a region is empty or \"UNKNOWN\".\n";
    }

protected:
    virtual void
    region_handler( cube::Region* region )
    {
        std::string name = region->get_name();
        if ( name.empty() )
        {
            fail( "The region's name is empty.", region );
        }
        else if ( name == "UNKNOWN" )
        {
            fail( "The region's name is UNKNOWN.", region );
        }
        else
        {
            ok();
        }
    }
};

class FilenameNotEmpty : public RegionConstraint
{
public:
    FilenameNotEmpty( CnodeSubForest* forest )
        : RegionConstraint( forest )
    {
    }

    virtual std::string
    get_name()
    {
        return "File name not empty";
    }
    virtual std::string
    get_description()
    {
        return
            "Checks whether the module name (file name for user functions)\n"
            "is empty.";
    }

protected:
    virtual void
    region_handler( cube::Region* region )
    {
        std::string filename = region->get_mod();
        if ( filename.empty() )
        {
            fail( "The region's file name is empty.", region );
        }
        else
        {
            ok();
        }
    }
};

class ProperLineNumbers : public RegionConstraint
{
public:
    ProperLineNumbers( CnodeSubForest* forest )
        : RegionConstraint( forest )
    {
    }

    virtual std::string
    get_name()
    {
        return "Proper line numbers";
    }
    virtual std::string
    get_description()
    {
        return
            "Checks that the line numbers of a region are not -1.";
    }

protected:
    virtual void
    region_handler( cube::Region* region )
    {
        if ( region->get_begn_ln() < 0 && region->get_end_ln() < 0 )
        {
            fail( "Begin and end line numbers are negative.", region );
        }
        else if ( region->get_begn_ln() < 0 )
        {
            fail( "Begin line number is negative.", region );
        }
        else if ( region->get_end_ln() < 0 )
        {
            fail( "End line number is negative.", region );
        }
        else
        {
            ok();
        }
    }
};

class NoAnonymousFunctions : public RegionConstraint
{
public:
    NoAnonymousFunctions( CnodeSubForest* forest )
        : RegionConstraint( forest )
    {
    }

    virtual std::string
    get_name()
    {
        return "No ANONYMOUS functions";
    }
    virtual std::string
    get_description()
    {
        return
            "Checks that the region's name is not ANONYMOUS@something.";
    }

protected:
    virtual void
    region_handler( cube::Region* region )
    {
        if ( region->get_name().find( "ANONYMOUS@" ) == 0 )
        {
            fail( "cube::Region's name is \"ANONYMOUS\".", region );
        }
        else
        {
            ok();
        }
    }
};

class NoTruncatedFunctions : public RegionConstraint
{
public:
    NoTruncatedFunctions( CnodeSubForest* forest )
        : RegionConstraint( forest )
    {
    }

    virtual std::string
    get_name()
    {
        return "No TRUNCATED functions";
    }
    virtual std::string
    get_description()
    {
        return
            "Checks that the region's name does not contain the std::string TRUNCATED.";
    }

protected:
    virtual void
    region_handler( cube::Region* region )
    {
        if ( region->get_name().find( "TRUNCATED" ) != std::string::npos )
        {
            fail( "The region's name contains the std::string \"TRUNCATED\".", region );
        }
        else
        {
            ok();
        }
    }
};

class NoTracingOutsideInitAndFinalize : public CnodeConstraint
{
public:
    NoTracingOutsideInitAndFinalize( CnodeSubForest* forest )
        : CnodeConstraint( forest )
    {
    }

    virtual std::string
    get_name()
    {
        return "No TRACING outside Init and Finalize";
    }
    virtual std::string
    get_description()
    {
        return "";
    }

protected:
    virtual void
    cnode_handler( Cnode* node )
    {
        std::string name = node->get_callee()->get_name();
        if ( name == "TRACING" )
        {
            name = node->get_parent()->get_callee()->get_name();
            if ( name != "MPI_Init" && name != "MPI_Finalize" )
            {
                return fail( "Found TRACING outside MPI_Init and MPI_Finalize.\n"
                             "Parent's name is " + name, node,
                             CNODE_OUTPUT_MODE_BACKTRACE );
            }
        }
        ok();
    }
};

class NoNegativeExclusiveMetrics : public AbstractConstraint
{
public:
    NoNegativeExclusiveMetrics( Cube* cube )
        : m_cube( cube ), m_threshold( 1e-12 )
    {
        set_step_size( 10000 );
    }

    virtual std::string
    get_name()
    {
        return "No negative exclusive metrics";
    }
    virtual std::string
    get_description()
    {
        return "Checks whether the exclusive values are non-negative.";
    }
    virtual void
    check()
    {
        const std::vector<Metric*> metrics = m_cube->get_metv();
        const std::vector<Cnode*>  cnodes  = m_cube->get_cnodev();
        const std::vector<Thread*> threads = m_cube->get_thrdv();
        for ( std::vector<Metric*>::const_iterator metric = metrics.begin();
              metric != metrics.end(); ++metric )
        {
            int i = 0;
            for ( std::vector<Cnode*>::const_iterator cnode = cnodes.begin();
                  cnode != cnodes.end(); ++cnode )
            {
                int j = 0;
                for ( std::vector<Thread*>::const_iterator thread = threads.begin();
                      thread != threads.end(); ++thread )
                {
                    stringstream ss;
                    ss << get_name() << " :: " << ( *metric )->get_uniq_name() << " :: "
                       << ++i << " :: " << ++j;
                    test( ss.str() );
                    // Compute sum of children metrics
                    double sum_of_children = 0.;
                    for ( unsigned int i = 0; i < ( *metric )->num_children(); ++i )
                    {
                        sum_of_children += m_cube->get_sev( ( *metric )->get_child( i ), *cnode, *thread );
                    }

                    // compute exclusive metric
                    double exclusive_sev = m_cube->get_sev( *metric, *cnode, *thread ) - sum_of_children;

                    if ( exclusive_sev < ( -1 * m_threshold ) )
                    {
                        stringstream err;
                        err << "exclusive metric: " << ( *metric )->get_uniq_name() << ", cnode: "
                            << ( *cnode )->get_callee()->get_name() << " (id: "
                            << ( *cnode )->get_id() << ")" << ", thread id: "
                            << ( *thread )->get_id() << " is negative.";
                        fail( err.str() );
                    }
                    else
                    {
                        ok();
                    }
                }
            }
        }
        finish();
    }

private:
    Cube*  m_cube;
    double m_threshold;
};

class NoNegativeInclusiveMetrics : public AbstractConstraint
{
public:
    NoNegativeInclusiveMetrics( Cube* cube )
        : cube( cube ), m_threshold( 1e-12 )
    {
        set_step_size( 10000 );
    }

    virtual std::string
    get_name()
    {
        return "No negative inclusive metrics";
    }
    virtual std::string
    get_description()
    {
        return
            "Checks whether all metrics' values are non-negative.";
    }
    virtual void
    check()
    {
        const std::vector<Metric*> metrics = cube->get_metv();
        const std::vector<Cnode*>  cnodes  = cube->get_cnodev();
        const std::vector<Thread*> threads = cube->get_thrdv();
        for ( std::vector<Metric*>::const_iterator metric = metrics.begin();
              metric != metrics.end(); ++metric )
        {
            int i = 0;
            for ( std::vector<Cnode*>::const_iterator cnode = cnodes.begin();
                  cnode != cnodes.end(); ++cnode )
            {
                int j = 0;
                for ( std::vector<Thread*>::const_iterator thread = threads.begin();
                      thread != threads.end(); ++thread )
                {
                    stringstream ss;
                    ss << get_name() << " :: " << ( *metric )->get_uniq_name() << " :: "
                       << ++i << " :: " << ++j;
                    test( ss.str() );
                    if ( cube->get_sev( *metric, cube::CUBE_CALCULATE_INCLUSIVE, *cnode, cube::CUBE_CALCULATE_INCLUSIVE, *thread, cube::CUBE_CALCULATE_EXCLUSIVE ) < ( -1 * m_threshold ) )
                    {
                        stringstream err;
                        err << "metric: " << ( *metric )->get_uniq_name() << ", cnode: "
                            << ( *cnode )->get_callee()->get_name() << " (id: "
                            << ( *cnode )->get_id() << ")" << ", thread id: "
                            << ( *thread )->get_id() << " is negative.";
                        fail( err.str() );
                    }
                    else
                    {
                        ok();
                    }
                }
            }
        }
        finish();
    }

private:
    Cube*  cube;
    double m_threshold;
};






class ProperlyFiltered : public RegionConstraint
{
public:
    ProperlyFiltered( CnodeSubForest* forest,
                      Filter&         filter )
        : RegionConstraint( forest ), filter( filter )
    {
    }

    virtual std::string
    get_name()
    {
        return "Regions properly filtered.";
    }
    virtual std::string
    get_description()
    {
        return
            "Checks whether the Filter filter does not match any of the regions of\n"
            "the cube.";
    }

protected:
    void
    region_handler( cube::Region* region )
    {
        if ( filter.matches( region->get_name() ) )
        {
            fail( "Filter matches region.", region );
        }
        else
        {
            ok();
        }
    }

private:
    Filter& filter;
};





Cube*
openCubeFile( const char* filename )
{
    Cube* input = new Cube();
    input->openCubeReport( filename );
    return input;
}





#endif
