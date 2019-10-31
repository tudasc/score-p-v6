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


#ifndef __CUBE_CALLTREE_CALLS_H
#define __CUBE_CALLTREE_CALLS_H


#include "CubeCnode.h"
#include <vector>


/**
 * Prints the format of "usage" of this tool.
 */
void
usage( const char* argv, int error_code )
{
    std::cout << "usage: " << argv << " -a -m metricname -t threashold -c -i -u -h [-f] filename \n";
    std::cout << std::endl;
    std::cout << "        -m metricname -- print out values for the metric <metricname>;" << std::endl;
    std::cout << "        -a            -- annotate call path;" << std::endl;
    std::cout << "        -t treashold  -- print out only call path with a value, which is larger than <treashold>% of the total metric value. 0<=treashold<=100;" << std::endl;
    std::cout << "        -i            -- calculate inclusive values instead of exclusive." << std::endl;
    std::cout << "        -f            -- open <filename>;" << std::endl;
    std::cout << "        -p            -- diplay percent value;" << std::endl;
    std::cout << "        -c            -- diplay callpath for every region;" << std::endl;
    std::cout << "        -h            -- display this help." << std::endl;
    exit( error_code );
}

/**
 * Recursiv counting of the level in a tree hierarchy of given cnode.
 */
int
get_level( const cube::Cnode& c )
{
    cube::Cnode* ptr = c.get_parent();
    int          level( 0 );
    while ( true )
    {
        if ( ptr == NULL )
        {
            break;
        }
        else
        {
            level++;
            ptr = ptr->get_parent();
        }
    }
    return level;
}


void
get_deep_first_enimeration( cube::Cnode* cnode,  std::vector<cube::Cnode*>& deep_first_cnodes )
{
    deep_first_cnodes.push_back( cnode );
    if ( cnode->num_children() == 0 )
    {
        return;
    }
    for ( size_t i = 0; i < cnode->num_children(); ++i )
    {
        cube::Cnode* _cnode = cnode->get_child( i );
        get_deep_first_enimeration( _cnode, deep_first_cnodes );
    }
}

#endif
