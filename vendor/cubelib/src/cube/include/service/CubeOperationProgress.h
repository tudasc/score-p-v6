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
 * \file CubeOperationProgress.h
 * \brief Provides a hierarchy of errors compatible with C++ thwrow/catch mechanism
 */
#ifndef CUBE_OPERATION_PROGRESS_H
#define CUBE_OPERATION_PROGRESS_H

/*
 *----------------------------------------------------------------------------
 *
 * class Error
 *
 *******************************----------------------------------------------------------------------------
 */
#include <deque>
#include <utility>
#include <iostream>

namespace cube
{
typedef double                            progress_t;
typedef std::pair<progress_t, progress_t> progress_step_t;



class ProgressStatus
{
public:

    std::string message;
    double      status;
};



/**
 * General progress calculation class
 */
class OperationProgress
{
public:


    OperationProgress()
    {
        init();
    }


    inline
    void
    init()
    {
        steps.clear();
        status.message = "";
        status.status  = 0.;
    }

    inline
    void
    start_step( progress_t s, progress_t f )
    {
        start_step( std::make_pair( s, f ) );
    }

    inline
    void
    start_step( progress_step_t step )
    {
        progress_step_t new_step =  step;
        if ( steps.size() > 0 )
        {
            progress_step_t last_step        = steps.back();
            progress_t      last_step_length = last_step.second - last_step.first;
            new_step.first  = step.first * last_step_length + last_step.first;
            new_step.second = step.second * last_step_length + last_step.first;
        }
        steps.push_back( new_step );
    }

    inline
    void
    finish_step( std::string message )
    {
        if ( steps.size() > 0 )
        {
            steps.pop_back();
        }
        progress_step( 1., message );
    }

    inline
    void
    progress_step( progress_t step )
    {
        progress_step_t last_step        = std::make_pair( 0., 1. );
        progress_t      last_step_length = last_step.second - last_step.first;
        if ( steps.size() > 0 )
        {
            last_step        = steps.back();
            last_step_length = last_step.second - last_step.first;
        }
        status.status = step * last_step_length + last_step.first;
    }

    inline
    void
    progress_step( std::string message )
    {
        status.message = message;
    }

    inline
    void
    progress_step( progress_t step, std::string message )
    {
        progress_step( step );
        progress_step( message );
    }


    inline
    ProgressStatus*
    get_progress_status()
    {
        return &status;
    }


protected:

    ProgressStatus              status;
    std::deque<progress_step_t> steps;
};



std::ostream&
operator<<( std::ostream&      out,
            OperationProgress& progress );                                                  // /< Prints out a message about an error.
}

#endif
