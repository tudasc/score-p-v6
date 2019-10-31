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
**  Copyright (c) 2003-2008                                                **
**  University of Tennessee, Innovative Computing Laboratory               **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


#ifndef __CUBE_TEST_CALLS_H
#define __CUBE_TEST_CALLS_H

#include <cmath>

typedef enum EquivalenceTest_ToleranceMode
{
    ABSOLUTE,
    RELATIVE
} EquivalenceTest_ToleranceMode;






class CnodesEquivalent : public CMetricCnodeConstraint
{
public:
    CnodesEquivalent( CnodeSubForest* forest,
                      string metric, double threshold = 0.,
                      EquivalenceTest_ToleranceMode mode = ABSOLUTE )
        : CMetricCnodeConstraint( forest, metric ), metric( metric ),
        mode( mode ), threshold( threshold )
    {
    }

    virtual string
    get_name()
    {
        if ( threshold == 0 )
        {
            return "Equality " + metric;
        }
        else
        {
            stringstream ss;
            ss << "Similarity ";
            ss << metric << " ";
            ss << ( mode == ABSOLUTE ? "(absolute, " : "(relative, " );
            ss << threshold << ")";
            return ss.str();
        }
    }
    virtual string
    get_description()
    {
        return "XXX: DESCRIPTION MISSING!!!";
    }

    virtual void
    check()
    {
        if ( get_forest()->get_reference_cube()->get_number_of_cubes() < 2 )
        {
            throw RuntimeError( "CnodesEquivalent requires the MultiMdAggrCube "
                                "to contain exactly two cube files." );
        }
        CMetricCnodeConstraint::check();
    }

protected:
    virtual void
    cnode_handler( Cnode* node )
    {
        unsigned int number_of_cubes = get_forest()
                                       ->get_reference_cube()
                                       ->get_number_of_cubes();
        double node_threshold;

        if ( mode == RELATIVE )
        {
            double sum = 0.;
            for ( unsigned int id = 0; id < number_of_cubes; ++id )
            {
                sum += fabs( get_metric()->compute( node, id ) );
            }
            node_threshold = threshold * ( sum / number_of_cubes );
        }
        else if ( mode == ABSOLUTE )
        {
            node_threshold = threshold;
        }
        else
        {
            return skip( "Unknown comparison mode.", node );
        }

        double min = get_metric()->compute( node, ( unsigned int )0 );
        double max = min;
        for ( unsigned int id = 1; id < number_of_cubes; ++id )
        {
            double val = get_metric()->compute( node, id );
            if ( val < min )
            {
                min = val;
            }
            if ( val > max )
            {
                max = val;
            }
            double diff2min = val - min;
            double diff2max = max - val;
            double absdiff  = diff2min < diff2max ? diff2max : diff2min;
            if ( absdiff > node_threshold )
            {
                stringstream ss;
                ss << "Absolute difference between the file with id "
                   << id << " and a file with a lower id is " << absdiff
                   << " but should be lower than " << node_threshold << ".";
                return fail( ss.str(), node, CNODE_OUTPUT_MODE_BACKTRACE );
            }
        }
        ok();
    }

private:
    string                        metric;
    EquivalenceTest_ToleranceMode mode;
    double                        threshold;
};







AggrCube*
openCubeFile( const char* filename )
{
    AggrCube* input = new AggrCube();
    input->openCubeReport( filename );
    return input;
}



#endif
