#ifndef COMMON_GENERATE_LIBRARY_DEPENDENCIES_LA_OBJECT_HPP
#define COMMON_GENERATE_LIBRARY_DEPENDENCIES_LA_OBJECT_HPP

/*
 * This file is part of the Score-P software (http://www.score-p.org)
 *
 * Copyright (c) 2009-2013,
 * RWTH Aachen University, Germany
 *
 * Copyright (c) 2009-2013,
 * Gesellschaft fuer numerische Simulation mbH Braunschweig, Germany
 *
 * Copyright (c) 2009-2014,
 * Technische Universitaet Dresden, Germany
 *
 * Copyright (c) 2009-2013,
 * University of Oregon, Eugene, USA
 *
 * Copyright (c) 2009-2013, 2017,
 * Forschungszentrum Juelich GmbH, Germany
 *
 * Copyright (c) 2009-2013,
 * German Research School for Simulation Sciences GmbH, Juelich/Aachen, Germany
 *
 * Copyright (c) 2009-2013,
 * Technische Universitaet Muenchen, Germany
 *
 * This software may be modified and distributed under the terms of
 * a BSD-style license.  See the COPYING file in the package base
 * directory for details.
 *
 */


/**
 * @file
 */

#include <string>
#include <deque>

/**
 * Helper struct to represent the content of one .la file. Used in code
 * generated by generate-library-dependencies.sh. To make usage easier
 * everything is public.
 */
struct la_object
{
    /**
     * Empty contructor. Needed to allow copies of STL containers containing this
     * class
     */
    la_object( void )
    {
    }

    /**
     * Copy constructor.
     */
    la_object( const la_object& source )
        :
        m_lib_name( source.m_lib_name ),
        m_build_dir( source.m_build_dir ),
        m_install_dir( source.m_install_dir ),
        m_libs( source.m_libs ),
        m_ldflags( source.m_ldflags ),
        m_rpath( source.m_rpath ),
        m_dependency_las( source.m_dependency_las )
    {
    }


    /**
     * Regular constructor.
     */
    la_object( const std::string&             lib_name,
               const std::string&             build_dir,
               const std::string&             install_dir,
               const std::deque<std::string>& libs,
               const std::deque<std::string>& ldflags,
               const std::deque<std::string>& rpaths,
               const std::deque<std::string>& dependency_las )
        :
        m_lib_name( lib_name ),
        m_build_dir( build_dir ),
        m_install_dir( install_dir ),
        m_libs( libs ),
        m_ldflags( ldflags ),
        m_rpath( rpaths ),
        m_dependency_las( dependency_las )
    {
    }

    /**
     * Destructor.
     */
    virtual
    ~la_object()
    {
    }

    /**
     * Member.
     */
    std::string             m_lib_name;
    std::string             m_build_dir;
    std::string             m_install_dir;
    std::deque<std::string> m_libs;
    std::deque<std::string> m_ldflags;
    std::deque<std::string> m_rpath;
    std::deque<std::string> m_dependency_las;
};

#endif /* COMMON_GENERATE_LIBRARY_DEPENDENCIES_LA_OBJECT_HPP */