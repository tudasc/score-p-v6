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

/**
 *
 * \file algebra4.cpp
 * \brief Contains a set of functions allows to operate with a cube and parts of
   it (metrics tree, cnodes tree and so on).
 * Merging, comparison, copying and another operations.
 *
 ************************************************/
/******************************************

   Performance Algebra

 *******************************************/

#include <climits>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iomanip>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>


#include "algebra4-internals.h"
#include "CubeServices.h"


#define CUBELIB_DEBUG_MODULE_NAME CUBELIB_TOOLS
#include <UTILS_Debug.h>


using namespace std;
using namespace cube;

using namespace cube;
using namespace std;

#ifdef HAVE_CUBELIB_DEBUG
#include <sstream>
#endif

namespace cube
{
DataType
metric_data_type_adust( DataType _old_dtype, MetricDataTypeAdjust adjust )
{
    DataType _new_dtype = _old_dtype;
    if ( adjust != NO_ADJUST )
    {
        if ( ( adjust & INT_TO_UINT ) != 0 )
        {
            switch ( _old_dtype )
            {
                case CUBE_DATA_TYPE_INT64:
                    _new_dtype = CUBE_DATA_TYPE_UINT64;
                    break;
                case CUBE_DATA_TYPE_INT32:
                    _new_dtype = CUBE_DATA_TYPE_UINT32;
                    break;
                case CUBE_DATA_TYPE_INT16:
                    _new_dtype = CUBE_DATA_TYPE_UINT16;
                    break;
                case CUBE_DATA_TYPE_INT8:
                    _new_dtype = CUBE_DATA_TYPE_UINT8;
                    break;
                default:
                    break;
            }
        }
        if ( ( adjust & INT_TO_DOUBLE ) != 0 )
        {
            switch ( _old_dtype )
            {
                case CUBE_DATA_TYPE_INT64:
                case CUBE_DATA_TYPE_INT32:
                case CUBE_DATA_TYPE_INT16:
                case CUBE_DATA_TYPE_INT8:
                    _new_dtype = CUBE_DATA_TYPE_DOUBLE;
                    break;
                default:
                    break;
            }
        }
        if ( ( adjust & UINT_TO_INT ) != 0 )
        {
            switch ( _old_dtype )
            {
                case CUBE_DATA_TYPE_UINT64:
                    _new_dtype = CUBE_DATA_TYPE_INT64;
                    break;
                case CUBE_DATA_TYPE_UINT32:
                    _new_dtype = CUBE_DATA_TYPE_INT32;
                    break;
                case CUBE_DATA_TYPE_UINT16:
                    _new_dtype = CUBE_DATA_TYPE_INT16;
                    break;
                case CUBE_DATA_TYPE_UINT8:
                    _new_dtype = CUBE_DATA_TYPE_INT8;
                    break;
                default:
                    break;
            }
        }
        if ( ( adjust & UINT_TO_DOUBLE ) != 0 )
        {
            switch ( _old_dtype )
            {
                case CUBE_DATA_TYPE_UINT64:
                case CUBE_DATA_TYPE_UINT32:
                case CUBE_DATA_TYPE_UINT16:
                case CUBE_DATA_TYPE_UINT8:
                    _new_dtype = CUBE_DATA_TYPE_DOUBLE;
                    break;
                default:
                    break;
            }
        }
        if ( ( adjust & INT_TO_DOUBLE ) != 0 )
        {
            switch ( _old_dtype )
            {
                case CUBE_DATA_TYPE_INT64:
                case CUBE_DATA_TYPE_INT32:
                case CUBE_DATA_TYPE_INT16:
                case CUBE_DATA_TYPE_INT8:
                    _new_dtype = CUBE_DATA_TYPE_DOUBLE;
                    break;
                default:
                    break;
            }
        }
        if ( ( adjust & DOUBLE_TO_INT ) != 0 )
        {
            switch ( _old_dtype )
            {
                case CUBE_DATA_TYPE_DOUBLE:
                    _new_dtype = CUBE_DATA_TYPE_INT64;
                    break;
                default:
                    break;
            }
        }
        if ( ( adjust & DOUBLE_TO_UINT ) != 0 )
        {
            switch ( _old_dtype )
            {
                case CUBE_DATA_TYPE_DOUBLE:
                    _new_dtype = CUBE_DATA_TYPE_UINT64;
                    break;
                default:
                    break;
            }
        }
    }
    return _new_dtype;
}



static
void
copyAttributes( const Vertex* source, Vertex* target )
{
    const std::map<std::string, std::string>& attrs = source->get_attrs();
    map<string, string>::const_iterator       ai;
    for ( ai = attrs.begin(); ai != attrs.end(); ++ai )
    {
        target->def_attr( ai->first, ai->second );
    }
}



/* Merge metric forest  */
/**
 * Merging only metrics from one cube ("input") into another cube ("newCube").
   It returns whether the new cube allready had an identical  tree of metrics.
   But merging happens only in the case the "newCube" hasn't a tree with same root
   element as "input" has.
 ********/
bool
metric_merge( Cube& newCube, const Cube& input, CubeMapping&   cubeMap,  MetricDataTypeAdjust adjust )
{
    bool is_equal = true;
    /* Get roots */
    const vector<Metric*>& newroot = newCube.get_root_metv();
    const vector<Metric*>& inroot  = input.get_root_metv();
    /* Compare root trees */
    for ( size_t i = 0; i < inroot.size(); ++i )
    {
        Metric* rhs = inroot[ i ];
        bool    in  = false;
        for ( size_t j = 0; j < newroot.size(); ++j )
        {
            Metric* lhs = newroot[ j ];
            if ( rhs->get_uniq_name() == lhs->get_uniq_name() )
            {
                in                    = true;
                cubeMap.metm[ rhs ]   = lhs;
                cubeMap.r_metm[ lhs ] = rhs;
                copyAttributes( rhs, lhs );

                /* If tree already exists then compare whole tree */
                if ( !compare_tree( newCube, *lhs, *rhs, cubeMap,  adjust ) )
                {
                    is_equal = false;
                }
            }
        }
        if ( !in )
        {
            DataType _old_dtype = rhs->get_data_type();
            DataType _new_dtype = metric_data_type_adust( _old_dtype, adjust );

            /* If tree does not exist then copy whole tree */
            Metric* _new_metric =
                newCube.def_met( rhs->get_disp_name(),
                                 rhs->get_uniq_name(),
                                 cube::getDataTypeAsString( _new_dtype ),
                                 rhs->get_uom(),
                                 rhs->get_val(),
                                 rhs->get_url(),
                                 rhs->get_descr(),
                                 NULL,
                                 rhs->get_type_of_metric(),
                                 rhs->get_expression(),
                                 rhs->get_init_expression(),
                                 rhs->get_aggr_plus_expression(),
                                 rhs->get_aggr_minus_expression(),
                                 rhs->get_aggr_aggr_expression(),
                                 rhs->isRowWise(),
                                 rhs->get_viz_type()
                                 );
            cubeMap.metm[ rhs ]           = _new_metric;
            cubeMap.r_metm[ _new_metric ] = rhs;
            copyAttributes( rhs, _new_metric );
            copy_tree( newCube, *rhs,  cubeMap, COPY_SAME_FLAVOUR, false, adjust );
            is_equal = false;
        }
    }
    return is_equal;
}

/* Re-map metric forrest */
/**
 * Setting a values of metrics in "newCube" to values of metrics in "input".
   If necessary, the new metric in "newCube" is created.
 ********/
void
metric_remap( Cube& newCube, const Cube& input, CubeMapping&   cubeMap )
{
    const vector<Metric*>& inmetv = input.get_metv();
    for ( size_t i = 0; i < inmetv.size(); ++i )
    {
        Metric* rhs = inmetv[ i ];
        if ( rhs == NULL )
        {
            continue;
        }
        Metric* lhs = newCube.get_met( rhs->get_uniq_name() );

        if ( lhs )
        {
            lhs->set_val( rhs->get_val() );
        }
        else
        {
            lhs =  newCube.def_met( rhs->get_disp_name(), rhs->get_uniq_name(),
                                    rhs->get_dtype(), rhs->get_uom(), rhs->get_val(),
                                    rhs->get_url(), rhs->get_descr(),
                                    rhs->get_parent() ? cubeMap.metm[ rhs->get_parent() ] : NULL,
                                    rhs->get_type_of_metric() );
        }
        cubeMap.metm[ rhs ]   = lhs;
        cubeMap.r_metm[ lhs ] = rhs;
        copyAttributes( rhs, lhs );
    }
}

/* Compare two metric trees */
/**
 * Compares "lhs"-tree with "rhs"-tree using recursive deep search method.
   In the case "newCube" doesn't have a metric tree it will be copied.
 */
bool
compare_tree( Cube& newCube, Metric& lhs,  Metric& rhs,   CubeMapping&   cubeMap,  MetricDataTypeAdjust adjust  )
{
    bool is_equal = true;
    for ( unsigned int i = 0; i < rhs.num_children(); ++i )
    {
        Metric* it = rhs.get_child( i );
        bool    in = false;
        for ( unsigned int j = 0; j < lhs.num_children(); ++j )
        {
            if ( it->get_uniq_name() == lhs.get_child( j )->get_uniq_name() )
            {       /* Tree already exists? */
                cubeMap.metm[ it ]                   = lhs.get_child( j );
                cubeMap.r_metm[ lhs.get_child( j ) ] = it;
                in                                   = true;
                if ( it->num_children() != 0 )
                {       /* Has metric children? */
                    if ( !compare_tree( newCube, *lhs.get_child( j ), *it, cubeMap, adjust ) )
                    {
                        is_equal = false;
                        break;
                    }
                }
            }
        }
        if ( !in )
        {
            DataType _old_dtype = it->get_data_type();
            DataType _new_dtype = metric_data_type_adust( _old_dtype, adjust );
            /* Create metric and copy tree */
            Metric* _new_metric =
                newCube.def_met( it->get_disp_name(), it->get_uniq_name(),
                                 cube::getDataTypeAsString( _new_dtype ), it->get_uom(), it->get_val(), it->get_url(),
                                 it->get_descr(),
                                 newCube.get_met( rhs.get_uniq_name() ),
                                 it->get_type_of_metric(),
                                 it->get_expression(),
                                 it->get_init_expression(),
                                 it->get_aggr_plus_expression(),
                                 it->get_aggr_minus_expression(),
                                 it->get_aggr_aggr_expression(),
                                 it->isRowWise(),
                                 it->get_viz_type()
                                 );
            cubeMap.metm[ it ]            = _new_metric;
            cubeMap.r_metm[ _new_metric ] = it;
            copyAttributes( &rhs, _new_metric );
            copy_tree( newCube, *it, cubeMap, COPY_SAME_FLAVOUR, false, adjust );
            is_equal = false;
        }
    }
    return is_equal;
}

/* Copy metric tree */
/**
 * Copy a  "rhs"-tree into  "newCube" using recursive deep search method.
 */
void
copy_tree( Cube& newCube, Metric& rhs,   CubeMapping&   cubeMap,  CallTreeCopy modifier, bool omit_void,  MetricDataTypeAdjust adjust )
{
    Metric* met = newCube.get_met( rhs.get_uniq_name() );
    for ( unsigned int i = 0; i < rhs.num_children(); ++i )
    {
        Metric* it = rhs.get_child( i );
        if ( omit_void && it->isInactive() )
        {
            continue;
        }
        TypeOfMetric mtype = it->get_type_of_metric();


        mtype = ( modifier == COPY_SAME_FLAVOUR || !( it->isConvertible() ) ) ?
                mtype
                :  (
            ( modifier == COPY_TO_EXCLUSIFY ) ?
            CUBE_METRIC_EXCLUSIVE
            :  CUBE_METRIC_INCLUSIVE
            );

        DataType _old_dtype = it->get_data_type();
        DataType _new_dtype = metric_data_type_adust( _old_dtype, adjust );

        Metric* _new_metric =
            newCube.def_met( it->get_disp_name(),
                             it->get_uniq_name(),
                             cube::getDataTypeAsString( _new_dtype ),
                             it->get_uom(),
                             it->get_val(),
                             it->get_url(),
                             it->get_descr(),
                             met,
                             mtype,
                             it->get_expression(),
                             it->get_init_expression(),
                             it->get_aggr_plus_expression(),
                             it->get_aggr_minus_expression(),
                             it->get_aggr_aggr_expression(),
                             it->isRowWise(),
                             it->get_viz_type() );
        if ( _new_metric == NULL )
        {
            _new_metric = newCube.def_met( it->get_disp_name(), it->get_uniq_name(),
                                           cube::getDataTypeAsString( _new_dtype ), it->get_uom(), it->get_val(),
                                           it->get_url(), it->get_descr(), met, CUBE_METRIC_EXCLUSIVE,
                                           it->get_expression(),
                                           it->get_init_expression(),
                                           it->get_aggr_plus_expression(),
                                           it->get_aggr_minus_expression(),
                                           it->get_aggr_aggr_expression(),
                                           it->isRowWise(),
                                           it->get_viz_type() );
        }
        cubeMap.metm[ it ]            = _new_metric;
        cubeMap.r_metm[ _new_metric ] = it;
        copyAttributes( it, _new_metric );
        if ( met != NULL )
        {
            if ( rhs.num_children() != 0 )
            {
                copy_tree( newCube, *rhs.get_child( i ), cubeMap, modifier, omit_void, adjust );
            }
        }
    }
}

/* Merge cnode forest  */
bool
regions_exists( const Cube& input,  const std::vector<std::string>& _nodes ) // this produces warnings inside
{
    if ( _nodes.size() == 0 )                                                // if empty - don't do anything
    {
        return true;
    }
    bool                       to_return = false;                            // default -> doesnt exist. it appears if whole loops get executed
    const std::vector<Cnode*>& cnodes    = input.get_cnodev();


    for (  std::vector<std::string>::const_iterator _n_iter = _nodes.begin(); _n_iter != _nodes.end(); ++_n_iter )
    {
        bool _local_found = false;
        for ( std::vector<Cnode*>::const_iterator _c_iter = cnodes.begin(); _c_iter != cnodes.end(); ++_c_iter )
        {
            Cnode* _cnode = *_c_iter;
            if ( _cnode->get_callee()->get_name().compare( *_n_iter ) == 0 )
            {
                // found cnode with such
                to_return    = true;
                _local_found = true;
            }
        }
        if ( !_local_found )
        {
            cerr << "WARNING: Region " << *_n_iter << " doesn't exist in the input file." << std::endl;
        }
    }
    return to_return;
}



bool
region_merge( Cube& newCube, const Cube& input, CubeMapping& cubeMap )
{
    bool is_equal = true;
    /* Get roots */
    const vector<Region*>& newregs = newCube.get_regv();
    const vector<Region*>& inregs  = input.get_regv();
    /* Compare root trees */
    for ( size_t i = 0; i < inregs.size(); ++i )
    {
        Region* rhs = inregs[ i ];
        bool    in  = false;
        for ( size_t j = 0; j < newregs.size(); ++j )
        {
            Region* lhs = newregs[ j ];
            if (   *rhs == *lhs )
            {
                in                       = true;
                cubeMap.regionm[ rhs ]   = lhs;
                cubeMap.r_regionm[ lhs ] = rhs;
            }
        }
        if ( !in )
        {
            /* If tree does not exist then copy whole tree */
            Region* _new_region =
                newCube.def_region(
                    rhs->get_name(),
                    rhs->get_mangled_name(),
                    rhs->get_paradigm(),
                    rhs->get_role(),
                    rhs->get_begn_ln(),
                    rhs->get_end_ln(),
                    rhs->get_url(),
                    rhs->get_descr(),
                    rhs->get_mod() );
            cubeMap.regionm[ rhs ]           = _new_region;
            cubeMap.r_regionm[ _new_region ] = rhs;
            is_equal                         = false;
        }
    }
    return is_equal;
}




/**
 * Merging a cnodes tree of "input" cube into the "newCube" cube.
   It returns whether the new cube allready has an identical  tree of cnodes.
   But merging happens only in the case, the "newCube" hasn't a tree with same
   root element as "input" has.
 */
bool
cnode_merge( Cube& newCube, const Cube& input,   CubeMapping&   cubeMap, bool copy_ids  )
{
    bool is_equal = true;
    /* Get roots */
    const vector<Cnode*>& newroot = newCube.get_root_cnodev();
    const vector<Cnode*>& inroot  = input.get_root_cnodev();
    /* Compare root trees */
    for ( size_t i = 0; i < inroot.size(); ++i )
    {
        Cnode* rhs = inroot[ i ];
        bool   in  = false;
        for ( size_t j = 0; j < newroot.size(); ++j )
        {
            Cnode* lhs = newroot[ j ];
            if ( *rhs == *lhs )
            {       /* Cnode found => compare tree */
                cubeMap.cnodem[ rhs ]   = lhs;
                cubeMap.r_cnodem[ lhs ] = rhs;
                in                      = true;
                if ( !compare_tree( newCube, *lhs, *rhs, cubeMap, copy_ids ) )
                {
                    is_equal = false;
                    break;
                }
            }
        }
        if ( !in )
        {       /* Not found => create cnode and copy tree */
            Cnode* newCnode = def_cnode( newCube, *rhs, NULL, copy_ids  );
            cubeMap.cnodem[ rhs ]        = newCnode;
            cubeMap.r_cnodem[ newCnode ] = rhs;
            copy_tree( newCube, *rhs, *newCnode, cubeMap, copy_ids  );
            is_equal = false;
        }
    }
    return is_equal;
}

/* Copy input Cnode-tree (only from newroot if specified) without pruned Cnodes */
/**
 * Copy all (if "newrootname" isn't spezified) or some (having callee with a name
   "newrootname") cnodes from "input" into "newCube". Returns if some elements were copyied.
 */
bool
cnode_reroot( Cube& newCube, const Cube& input, const string& cn_newrootname,
              const vector<string>& cn_prunes, CubeMapping& cubeMap, bool copy_ids )
{
    // if newrootname specified, search entire input cnodev for it
    // otherwise retain vector of existing roots
    const vector<Cnode*>& incnodev = cn_newrootname.empty() ?
                                     input.get_root_cnodev() : input.get_cnodev();
    bool got_root = false;

    /* Get roots */
    for ( size_t i = 0; i < incnodev.size(); ++i )
    {
        Cnode* rhs = incnodev[ i ];
        if ( cn_newrootname.empty() || *rhs->get_callee() == cn_newrootname )
        {
            /* matching Cnode found => copy tree */
            Cnode* newCnode = def_cnode( newCube, *rhs, NULL, copy_ids );
            cubeMap.cnodem[ rhs ]        = newCnode;
            cubeMap.r_cnodem[ newCnode ] = rhs;
            copy_tree( newCube, *rhs, *newCnode, cn_prunes, cubeMap, copy_ids );
            got_root = true;
        }
    }
    return got_root;
}
/**
 * Comparing of two "rhs"-tree with "lhs"-tree. In the case "newCube" doesn't
   have some elements of "lhs" they will be copied in to the "newCube" cube.
 */
bool
compare_tree( Cube& newCube, Cnode& lhs,  Cnode& rhs,   CubeMapping&   cubeMap, bool copy_ids )
{
    bool is_equal = true;
    for ( unsigned int i = 0; i < rhs.num_children(); ++i )
    {
        Cnode* it = rhs.get_child( i );
        bool   in = false;
        for ( unsigned int j = 0; j < lhs.num_children(); ++j )
        {
            if ( *it == *( lhs.get_child( j ) ) )
            {
                cubeMap.cnodem[ it ]                   = lhs.get_child( j );
                cubeMap.r_cnodem[ lhs.get_child( j ) ] = it;
                in                                     = true;
                if ( it->num_children() != 0 )
                {
                    if ( !compare_tree( newCube, *lhs.get_child( j ), *it, cubeMap, copy_ids ) )
                    {
                        is_equal = false;
                        break;
                    }
                }
            }
        }
        if ( !in )
        {
            Cnode* _newCnode = def_cnode( newCube, *it, &lhs, copy_ids );
            cubeMap.cnodem[ it ]          = _newCnode;
            cubeMap.r_cnodem[ _newCnode ] = it;
            copy_tree( newCube, *it, *_newCnode, cubeMap, copy_ids );
            is_equal = false;
        }
    }
    return is_equal;
}

/* Copy Cnode-tree */
/**
 * Recursive copying of a "rhs"-tree into "newCube" without any conditions.
 */
void
copy_tree( Cube& newCube, Cnode& rhs, Cnode& parent,   CubeMapping&   cubeMap, bool copy_ids )
{
    for ( unsigned int i = 0; i < rhs.num_children(); ++i )
    {
        Cnode* newCnode = def_cnode( newCube, *rhs.get_child( i ), &parent, copy_ids );
        cubeMap.cnodem[ rhs.get_child( i ) ] = newCnode;
        cubeMap.r_cnodem[ newCnode ]         = rhs.get_child( i );
        if ( rhs.num_children() != 0 )
        {
            copy_tree( newCube, *rhs.get_child( i ), *newCnode, cubeMap, copy_ids );
        }
    }
}

/* Copy Cnode-tree */
/**
 * Recursive copying of a "rhs"-tree into "parent" cnode of "newCube" with pruning (??????).
 */
void
copy_tree( Cube& newCube, Cnode& rhs, Cnode& parent,
           const vector<string>& prunes, CubeMapping& cubeMap, bool copy_ids  )

{
    const Region* par = parent.get_callee(); // newCnode in newCube for rhs
    const Region* reg = rhs.get_callee();

    for ( unsigned int i = 0; i < rhs.num_children(); ++i )
    {
        bool          prune = ( par->get_name() != reg->get_name() );
        const Region* child = rhs.get_child( i )->get_callee();

        for ( size_t p = 0; p < prunes.size(); p++ )
        {
            if ( child->get_name() == prunes[ p ] )
            {
                prune = true;
            }
        }

        // copy to parent when pruning, otherwise create matching Cnode in newCube
        Cnode* newCnode = prune ? &parent : def_cnode( newCube, *rhs.get_child( i ), &parent, copy_ids );
        cubeMap.cnodem[ rhs.get_child( i ) ] = newCnode;
        cubeMap.r_cnodem[ newCnode ]         = rhs.get_child( i );
        copy_tree( newCube, *rhs.get_child( i ), *newCnode, prunes, cubeMap, copy_ids  );
    }
}
/**
 * Define and return a cnode. Returns directly if the "newCube" has already the
   right "region" or the region will be created.
 */
Cnode*
def_cnode( Cube& newCube, Cnode& rhs, Cnode* parent, bool copy_ids   )
{
    const vector<Region*>& newRegv = newCube.get_regv();
    int                    num     = newRegv.size();

    Region* region = 0;
    for ( int i = 0; i < num; ++i )
    {
        if ( *newRegv[ i ] == *rhs.get_callee() )
        {
            region = newRegv[ i ];
            break;
        }
    }

    if ( region == 0 )
    {
        region = newCube.def_region( rhs.get_callee()->get_name(),
                                     rhs.get_callee()->get_mangled_name(),
                                     rhs.get_callee()->get_paradigm(),
                                     rhs.get_callee()->get_role(),
                                     rhs.get_callee()->get_begn_ln(),
                                     rhs.get_callee()->get_end_ln(), rhs.get_callee()->get_url(),
                                     rhs.get_callee()->get_descr(), rhs.get_callee()->get_mod() );
        copyAttributes( rhs.get_callee(), region );
    }

    Cnode* newcnode = newCube.def_cnode( region, rhs.get_mod(), rhs.get_line(), parent, ( copy_ids ) ? rhs.get_id() : ( uint32_t )-1  );

    std::vector<std::pair<std::string, double> >num_params = rhs.get_num_parameters();
    for ( unsigned i = 0; i < num_params.size(); i++ )
    {
        newcnode->add_num_parameter( num_params[ i ].first, num_params[ i ].second );
    }

    std::vector<std::pair<std::string, std::string> >str_params = rhs.get_str_parameters();
    for ( unsigned i = 0; i < str_params.size(); i++ )
    {
        newcnode->add_str_parameter( str_params[ i ].first, str_params[ i ].second );
    }
    copyAttributes( &rhs, newcnode );
    return newcnode;
}




/* set undefined URLs according to descr field */
void
set_region_urls( Cube& cube )
{
    const vector<Region*>& regv = cube.get_regv();
    for ( size_t r = 0; r < regv.size(); r++ )
    {
        Region* reg = regv[ r ];
        if ( ( reg->get_url() == "" ) && ( reg->get_descr() != "" ) )
        {
            reg->set_url( REGIONS_URL + reg->get_descr() );
        }
    }
}




/* Merge system dimension */
/**
 * Merging of two ("lhs" and "rhs") system resources tree into third one "newCube".
   If "collapse" set on "false" -> only bigger tree will be merged. Returns whether a "lhs" and "rhs" are equal.
 */
bool
sysres_merge( Cube&        newCube,
              const Cube&  rhs,
              CubeMapping& cubeMap,
              bool         reduce,
              bool         collapse,
              bool         strict )
{
    if ( collapse )
    {
        collapsed_merge( newCube, rhs, cubeMap );
        return true;
    }
    if ( reduce )
    {
        reduced_merge( newCube, rhs, cubeMap );
        return true;
    }
    else
    if ( is_subset( rhs, newCube, NULL, strict ) )
    {
        copy_system_tree( newCube, rhs, cubeMap, strict );
        return true;
    }
    else
    if ( is_subset( newCube, rhs, &cubeMap, strict  ) )
    {
        return true; // no merge is needed
    }
    else
    {
        return false; // merge is not possible.
    }
}


void
collapsed_merge( Cube& newCube,
                 const Cube& lhs, CubeMapping& cubeMap )
{
    std::vector<SystemTreeNode*>machines = newCube.get_machv();
    std::vector<SystemTreeNode*>nodes    = newCube.get_nodev();

    Machine* mach = NULL;
    Node*    node = NULL;
    if ( machines.size() == 0 )
    {
        mach = newCube.def_system_tree_node( "Virtual machine", "MACHINE", "machine", NULL );
    }
    else
    {
        mach = machines[ 0 ];
    }

    if ( nodes.size() == 0 )
    {
        node = newCube.def_system_tree_node( "Virtual node", "NODE", "node", mach );
    }
    else
    {
        node = nodes[ 0 ];
    }

    std::vector<LocationGroup*>new_lgs = lhs.get_location_groupv();
    std::vector<LocationGroup*>lgs     = newCube.get_location_groupv();
    for ( std::vector<LocationGroup*>::iterator new_lg_iter = new_lgs.begin(); new_lg_iter != new_lgs.end(); /* new_lg_iter++*/  )
    {
        LocationGroup* new_lg   = *new_lg_iter;
        bool           lg_equal = false;
        for ( std::vector<LocationGroup*>::iterator lg_iter = lgs.begin(); lg_iter != lgs.end(); )
        {
            LocationGroup* lg = *lg_iter;
            if ( ( *( *new_lg_iter ) ) == ( *( *lg_iter ) ) )
            {
                cubeMap.lgm[ new_lg ] = lg;
                cubeMap.r_lgm[ lg ]   = new_lg;
                merge( newCube, lg, new_lg, cubeMap );
                new_lgs.erase( new_lg_iter );
                lgs.erase( lg_iter );
                lg_equal = true;
                break;
            }
            else
            {
                ++lg_iter;
            }
        }
        if ( !lg_equal )
        {
            LocationGroup* _created = newCube.def_location_group( new_lg->get_name(), new_lg->get_rank(), new_lg->get_type(), node );
            cubeMap.lgm[ new_lg ]     = _created;
            cubeMap.r_lgm[ _created ] = new_lg;
            merge( newCube, _created, new_lg, cubeMap );
            new_lgs.erase( new_lg_iter );
            copyAttributes( new_lg, _created );
        }
    }
}

void
merge( Cube& newCube, LocationGroup* target_lg, LocationGroup* to_copy, CubeMapping& cubeMap, CubeMapping* midCubeMap  )
{
    for ( unsigned i = 0; i < to_copy->num_children(); ++i  )
    {
        Location* new_loc = to_copy->get_child( i );
        bool      equal   = false;
        for (  unsigned j = 0; j < target_lg->num_children(); ++j   )
        {
            Location* loc = target_lg->get_child( j );
            if ( *new_loc == *loc )
            {
                if ( midCubeMap != NULL )
                {
                    cubeMap.sysm[ midCubeMap->sysm[ new_loc ] ] = loc;
                    cubeMap.r_sysm[ loc ]                       = midCubeMap->sysm[ new_loc ];
                }
                else
                {
                    cubeMap.sysm[ new_loc ] = loc;
                    cubeMap.r_sysm[ loc ]   = new_loc;
                }
                equal = true;
                break;
            }
        }
        if ( !equal ) // we have to create a location
        {
            Location* _created = newCube.def_location( new_loc->get_name(), new_loc->get_rank(), new_loc->get_type(), target_lg );
            if ( midCubeMap != NULL )
            {
                cubeMap.sysm[ midCubeMap->sysm[ new_loc ] ] = _created;
                cubeMap.r_sysm[ _created ]                  = midCubeMap->sysm[ new_loc ];
            }
            else
            {
                cubeMap.sysm[ new_loc ]    = _created;
                cubeMap.r_sysm[ _created ] = new_loc;
            }
            copyAttributes( new_loc, _created );
        }
    }
}

void
merge( Cube&           newCube,
       SystemTreeNode* target_stn,
       SystemTreeNode* to_copy,
       CubeMapping&    cubeMap,
       CubeMapping*    midCubeMap,
       bool            strict  )
{
    for ( unsigned i = 0; i < to_copy->num_children(); ++i  )
    {
        SystemTreeNode* created_stn = NULL;
        SystemTreeNode* new_stn     = to_copy->get_child( i );
        bool            equal       = false;
        for (  unsigned j = 0; j < target_stn->num_children(); ++j   )
        {
            SystemTreeNode* stn      = target_stn->get_child( j );
            bool            _merging = false;
            if ( strict )
            {
                _merging = ( *new_stn == *stn  );
            }
            else
            {
                _merging =  new_stn->isWeakEqual( stn );
            }

            if ( _merging )
            {
                if ( midCubeMap != NULL )
                {
                    cubeMap.stnm[ midCubeMap->stnm[ new_stn ] ] = stn;
                    cubeMap.r_stnm[ stn ]                       = midCubeMap->stnm[ new_stn ];
                }
                else
                {
                    cubeMap.stnm[ new_stn ] = stn;
                    cubeMap.r_stnm[ stn ]   = new_stn;
                }
                merge( newCube, stn, new_stn, cubeMap, midCubeMap, strict );
                equal = true;
                break;
            }
        }
        if ( !equal )
        {
            created_stn = newCube.def_system_tree_node( new_stn->get_name(), new_stn->get_desc(), new_stn->get_class(), target_stn );
            if ( midCubeMap != NULL )
            {
                cubeMap.stnm[ midCubeMap->stnm[ new_stn ] ] = created_stn;
                cubeMap.r_stnm[ created_stn ]               = midCubeMap->stnm[ new_stn ];
            }
            else
            {
                cubeMap.stnm[ new_stn ]       = created_stn;
                cubeMap.r_stnm[ created_stn ] = new_stn;
            }

            copyAttributes( new_stn, created_stn );
            merge( newCube, created_stn, new_stn, cubeMap, midCubeMap );
        }
    }
    for ( unsigned i = 0; i < to_copy->num_groups(); ++i  )
    {
        LocationGroup* created_lg = NULL;
        LocationGroup* new_lg     = to_copy->get_location_group( i );
        bool           equal      = false;
        for (  unsigned j = 0; j < target_stn->num_groups(); ++j   )
        {
            LocationGroup* lg = target_stn->get_location_group( j );
            if ( *new_lg == *lg )
            {
                if ( midCubeMap != NULL )
                {
                    cubeMap.lgm[ midCubeMap->lgm[ new_lg ] ] = lg;
                    cubeMap.r_lgm[ lg ]                      = midCubeMap->lgm[ new_lg ];
                }
                else
                {
                    cubeMap.lgm[ new_lg ] = lg;
                    cubeMap.r_lgm[ lg ]   = new_lg;
                }
                merge( newCube, lg, new_lg, cubeMap, midCubeMap );
                equal = true;
                break;
            }
        }
        if ( !equal ) // we have to create a location
        {
            created_lg = newCube.def_location_group( new_lg->get_name(), new_lg->get_rank(), new_lg->get_type(), target_stn );
            if ( midCubeMap != NULL )
            {
                cubeMap.lgm[ midCubeMap->lgm[ new_lg ] ] = created_lg;
                cubeMap.r_lgm[ created_lg ]              = midCubeMap->lgm[ new_lg ];
            }
            else
            {
                cubeMap.lgm[ new_lg ]       = created_lg;
                cubeMap.r_lgm[ created_lg ] = new_lg;
            }
            copyAttributes( new_lg, created_lg );
            merge( newCube, created_lg, new_lg, cubeMap, midCubeMap );
        }
    }
}




void
reduced_merge( Cube& newCube,
               const Cube& lhs, CubeMapping& cubeMap  )
{
    CubeMapping                 midCubeMap;
    std::vector<SystemTreeNode*>stns = newCube.get_root_stnv();

    std::vector<SystemTreeNode*>_new_stns = get_reduced_system_tree( lhs, midCubeMap );

    for ( std::vector<SystemTreeNode*>::iterator new_stn_iter = _new_stns.begin(); new_stn_iter != _new_stns.end(); /*new_stn_iter++*/ )
    {
        bool            equal   = false;
        SystemTreeNode* new_stn = *new_stn_iter;
        for ( std::vector<SystemTreeNode*>::iterator stn_iter = stns.begin(); stn_iter != stns.end(); )
        {
            SystemTreeNode* stn = *stn_iter;
            if ( ( *new_stn ) == ( *stn ) )
            {
                merge( newCube, stn, new_stn, cubeMap, &midCubeMap );
                stns.erase( stn_iter );
                delete_system_tree_node( *new_stn_iter );
                _new_stns.erase( new_stn_iter );
                equal = true;
                break;
            }
            else
            {
                ++stn_iter;
            }
        }
        if ( !equal ) // we have to create a location
        {
            SystemTreeNode* created_stn = newCube.def_system_tree_node( new_stn->get_name(), new_stn->get_desc(), new_stn->get_class(), NULL );
            copyAttributes( new_stn, created_stn );
            merge( newCube, created_stn, new_stn, cubeMap, &midCubeMap );
            _new_stns.erase( new_stn_iter );
        }
    }
}



std::vector<SystemTreeNode*>
get_reduced_system_tree( const Cube& cube, CubeMapping& midCubeMap  )
{
    std::vector<SystemTreeNode*>stns = cube.get_root_stnv();

    std::vector<SystemTreeNode*>to_return;
    for ( std::vector<SystemTreeNode*>::iterator stn_iter = stns.begin(); stn_iter != stns.end(); ++stn_iter )
    {
        SystemTreeLogical can_do_it = is_reducable_tree( *stn_iter );
        if ( can_do_it.is_machine & can_do_it.is_node )
        {
            get_reduced_system_tree( *stn_iter, NULL,  to_return, midCubeMap );
        }
    }
    return to_return;
}

SystemTreeLogical
is_reducable_tree( SystemTreeNode* stn )
{
    SystemTreeLogical answer;
    answer.is_machine =  ( stn->get_class().compare( "machine" ) == 0 );
    answer.is_node    =  ( stn->get_class().compare( "node" ) == 0 )
                        ||
                        ( stn->get_class().compare( "nodecard" ) == 0 );
    for (  unsigned j = 0; j < stn->num_children(); ++j   )
    {
        SystemTreeNode*   _child  = stn->get_child( j );
        SystemTreeLogical _answer = is_reducable_tree( _child );

        answer.is_machine = answer.is_machine ||  _answer.is_machine;
        answer.is_node    = answer.is_node || _answer.is_node;
        if ( answer.is_machine & answer.is_node )
        {
            return answer;
        }
    }
    return answer;
}



void
get_reduced_system_tree( SystemTreeNode* to_copy, SystemTreeNode* root, std::vector<SystemTreeNode*>& stns, CubeMapping& midCubeMap )
{
    if ( to_copy->get_class().compare( "machine" ) == 0 ||
         to_copy->get_class().compare( "node" ) == 0 ||
         to_copy->get_class().compare( "nodecard" ) == 0
         )
    {
        root                    = new SystemTreeNode( to_copy->get_name(), to_copy->get_desc(), to_copy->get_class(), root );
        midCubeMap.stnm[ root ] = to_copy;
        if ( to_copy->get_class().compare( "machine" ) == 0 && is_reducable_tree( to_copy ).is_node )
        {
            stns.push_back( root );
        }
    }
    for (  unsigned j = 0; j < to_copy->num_children(); ++j   )
    {
        SystemTreeNode* _child = to_copy->get_child( j );
        get_reduced_system_tree( _child, root, stns, midCubeMap );
    }
    if ( root != NULL
         &&
         ( root->get_class().compare( "node" ) == 0 || root->get_class().compare( "nodecard" ) == 0 ) )
    {
        copy_location_groups( to_copy, root, midCubeMap );
    }
}





void
delete_system_tree_node( SystemTreeNode* root )
{
    for (  unsigned j = 0; j < root->num_children(); ++j   )
    {
        SystemTreeNode* stn = root->get_child( j );
        delete_system_tree_node( stn );
        delete stn;
    }
    for (  unsigned j = 0; j < root->num_groups(); ++j   )
    {
        LocationGroup* lg = root->get_location_group( j );
        delete_locations( lg );
        delete lg;
    }
}

void
copy_location_groups( SystemTreeNode* to_copy, SystemTreeNode* root, CubeMapping& midCubeMap )
{
    for (  unsigned j = 0; j < to_copy->num_groups(); ++j   )
    {
        LocationGroup* lg  = to_copy->get_location_group( j );
        LocationGroup* _lg =  new LocationGroup( lg->get_name(), root, lg->get_rank(), lg->get_type() );
        midCubeMap.lgm[ _lg ] = lg;
        copy_locations( lg, _lg, midCubeMap );
    }
}
void
delete_location_groups( SystemTreeNode* root )
{
    for (  unsigned j = 0; j < root->num_groups(); ++j   )
    {
        LocationGroup* lg = root->get_location_group( j );
        delete_locations( lg );
        delete lg;
    }
}

void
copy_locations( LocationGroup* to_copy, LocationGroup* root, CubeMapping& midCubeMap )
{
    for (  unsigned j = 0; j < to_copy->num_children(); ++j   )
    {
        Location* loc  = to_copy->get_child( j );
        Location* _loc = new Location( loc->get_name(), loc->get_rank(), root, loc->get_type() );
        midCubeMap.sysm[ _loc ] = loc;
    }
}
void
delete_locations( LocationGroup* root )
{
    for (  unsigned j = 0; j < root->num_children(); ++j   )
    {
        Location* loc = root->get_child( j );
        delete loc;
    }
}



void
copy_system_tree( Cube& newCube,
                  const Cube& lhs, CubeMapping& cubeMap,
                  bool strict )
{
    std::vector<SystemTreeNode*>stns     = newCube.get_root_stnv();
    std::vector<SystemTreeNode*>new_stns = lhs.get_root_stnv();
    for ( std::vector<SystemTreeNode*>::iterator new_snt_iter = new_stns.begin(); new_snt_iter != new_stns.end(); /*new_snt_iter++*/ )
    {
        bool            equal   = false;
        SystemTreeNode* new_stn = *new_snt_iter;
        for ( std::vector<SystemTreeNode*>::iterator stn_iter = stns.begin(); stn_iter != stns.end(); )
        {
            SystemTreeNode* stn      = *stn_iter;
            bool            _merging = false;
            if ( strict )
            {
                _merging = ( *new_stn == *stn  );
            }
            else
            {
                _merging =  new_stn->isWeakEqual( stn );
            }

            if ( _merging )
            {
                cubeMap.stnm[ new_stn ] = stn;
                cubeMap.r_stnm[ stn ]   = new_stn;
                merge( newCube, stn, new_stn, cubeMap, NULL, strict );
                stns.erase( stn_iter );
                new_stns.erase( new_snt_iter );
                equal = true;
                break;
            }
            else
            {
                ++stn_iter;
            }
        }
        if ( !equal )
        {
            SystemTreeNode* created_stn = newCube.def_system_tree_node( new_stn->get_name(), new_stn->get_desc(), new_stn->get_class(), NULL );
            copyAttributes( new_stn, created_stn );
            cubeMap.stnm[ new_stn ]       = created_stn;
            cubeMap.r_stnm[ created_stn ] = new_stn;
            merge( newCube, created_stn, new_stn, cubeMap, NULL, strict );
            new_stns.erase( new_snt_iter );
        }
    }
}





/**
 * Merging "big" into "newCube". If the "big" not a subset of machines in "newCube",
   the needed "machines" will be created.
 */
void
merge( Cube& newCube, const vector<Machine*>& big, bool subset, bool collapse )
{
    int num = big.size();
    for ( int i = 0; i < num; ++i )
    {
        Machine*     rhs = big[ i ];
        stringstream num;
        num << i;
        if ( subset && !collapse )
        {
            copy_tree( newCube, *rhs, *newCube.def_mach( rhs->get_name(), "" ), subset, collapse );
        }
        else
        {
            copy_tree( newCube, *rhs, *newCube.def_mach( ( "Machine " + num.str() ), "" ), subset, collapse );
        }
    }
}

/**
 * Recursive copying of "oldMach" tree into "newMach" tree using a deep search algorithm.
 */
void
copy_tree( Cube& newCube, Machine& oldMach, Machine& newMach, bool subset, bool collapse )
{
    int num = oldMach.num_children();
    for ( int i = 0; i < num; ++i )
    {
        stringstream num;
        num << i;
        if ( subset && !collapse )
        {
            copy_tree( newCube, *oldMach.get_child( i ), *newCube.def_node( oldMach.get_child( i )->get_name(), &newMach ) );
        }
        else
        {
            copy_tree( newCube, *oldMach.get_child( i ), *newCube.def_node( ( "Node " + num.str() ), &newMach ) );
        }
    }
}



/**
 * Copyying of "nodes" of a machine.
 */
void
copy_tree( Cube& newCube, Node& oldNode, Node& newNode )
{
    int num = oldNode.num_groups();
    for ( int i = 0; i < num; ++i )
    {
        def_pro( newCube, *oldNode.get_location_group( i ), newNode );
    }
}



/**
 * Creating of a "system" dimension in "newCube" using bigger number of processes
   and threads of "rhs" and "lhs". Number of processes and threads have to have a common divider.
   Otherwise it stops the program.
 */
// void plain_merge (Cube& newCube, Cube& lhs, const Cube& rhs)  // original
void
plain_merge( Cube& newCube, const Cube& rhs )
{
    int num = ( newCube.get_procv().size() > rhs.get_procv().size() )
              ? newCube.get_procv().size() : rhs.get_procv().size();
    int thrd = ( newCube.get_thrdv().size() > rhs.get_thrdv().size() )
               ? newCube.get_thrdv().size() : rhs.get_thrdv().size();

    int thrds_per_pro = thrd / num;
    if ( thrd % num != 0 )
    {
        cerr << "No valid cube experiment!" << endl;
        exit(   EXIT_FAILURE );
    }

    Machine* mach = newCube.def_mach( "Virtual machine", "" );

    Node* node = newCube.def_node( "Virtual node", mach );
    for ( int i = 0; i < num; ++i )
    {
        stringstream num;
        num << i;
        Process* newproc = newCube.def_proc( ( "Process " + num.str() ), i, node );
        for ( int j = 0; j < thrds_per_pro; ++j )
        {
            stringstream mynum;
            mynum << j;
            newCube.def_thrd( ( "Thread " + mynum.str() ), j, newproc );
        }
    }
}



/**
 * Create "process" and threads just like in "lhs" Process.
 */
void
def_pro( Cube& newCube, Process& lhs, Node& rhs )
{
    Process* newproc = newCube.def_proc( lhs.get_name(), lhs.get_rank(), &rhs );
    copyAttributes( &lhs, newproc );
    int num = lhs.num_children();
#if 1
    /* possibly copy a minimal number of threads, even if they are VOID */
    /* when only a single process on node and XT_NODE_CORES is set */
    char* env       = getenv( "XT_NODE_CORES" );
    int   min_thrds = ( env && ( atoi( env ) > 0 ) ) ? atoi( env ) : 1;
    if ( ( lhs.get_parent()->num_children() == 1 ) && ( min_thrds > 1 ) )
    {
        for ( int i = 0; i < num; ++i )
        {
            string thrd_name = lhs.get_child( i )->get_name();
            if ( ( thrd_name != "VOID" ) || ( i < min_thrds ) )
            {
                Thread* t = newCube.def_thrd( thrd_name, i, newproc );
                copyAttributes( lhs.get_child( i ), t );
            }
        }
        if ( ( min_thrds > 1 ) &&
             ( newproc->get_child( newproc->num_children() - 1 )->get_name() == "VOID" ) )
        {
            cout << "Retained minimum of " << min_thrds << " threads for process "
                 << lhs.get_rank() << endl;
        }
    }
    else

#endif
    for ( int i = 0; i < num; ++i )   /* copy non-VOID threads */
    {
        string   thrd_name = lhs.get_child( i )->get_name();
        unsigned thrd_rank = lhs.get_child( i )->get_rank();
        if ( thrd_name != "VOID" )
        {
            Thread* t = newCube.def_thrd( thrd_name, thrd_rank, newproc );
            copyAttributes( lhs.get_child( i ), t );
        }
    }
}



/**
 * Testing is a "lhs" and "rhs" Machines are subsets of eachother (result saved
   in "bigger_left") or are equal.
 */
bool
is_subset( const Cube&  lhs,
           const Cube&  rhs,
           CubeMapping* cubeMap,
           bool         strict  )
{
    vector<SystemTreeNode*>lroot  = lhs.get_root_stnv();
    vector<SystemTreeNode*>inroot = rhs.get_root_stnv();
    bool                   subset = true;
    for ( vector<SystemTreeNode*>::iterator riter = inroot.begin(); riter != inroot.end(); /* riter++ */ )
    {
        subset = false;
        for ( vector<SystemTreeNode*>::iterator liter = lroot.begin(); liter != lroot.end(); /**/ )
        {
            subset = true;
            if ( !is_subset( *liter, *riter, cubeMap, strict ) )
            {
                return false;
            }
            else
            {
                lroot.erase( liter );
                inroot.erase( riter );
            }
        }
    }
    return subset;
}

/**
 * Testing is a "lhs" and "rhs" Machines are subsets of eachother (result saved
   in "bigger_left") or are equal.
 */
bool
is_subset( SystemTreeNode* bigger,
           SystemTreeNode* smaller,
           CubeMapping*    cubeMap,
           bool            strict  )
{
    if ( strict )
    {
        if ( !( *bigger == *smaller ) )
        {
            return false;
        }
    }
    else
    {
        if ( !( bigger->isWeakEqual( smaller ) ) ) // only type compare
        {
            return false;
        }
    }
    if ( cubeMap != NULL )
    {
        cubeMap->stnm[ smaller ]  = bigger;
        cubeMap->r_stnm[ bigger ] = smaller;
    }
    vector<Vertex*>lchildren = bigger->get_children();
    vector<Vertex*>rchildren = smaller->get_children();

    for ( vector<Vertex*>::iterator riter = rchildren.begin(); riter != rchildren.end(); /* change is not needed*/ )
    {
        bool            local_subset = false;
        SystemTreeNode* rhs          = ( SystemTreeNode* )( *riter );
        for ( vector<Vertex*>::iterator liter = lchildren.begin(); liter != lchildren.end(); ++liter )
        {
            SystemTreeNode* lhs =  ( SystemTreeNode* )( *liter );
            if ( is_subset( lhs, rhs, cubeMap, strict ) )
            {
                if ( cubeMap != NULL )
                {
                    cubeMap->stnm[ lhs ]   = rhs;
                    cubeMap->r_stnm[ rhs ] = lhs;
                }
                lchildren.erase( liter );
                rchildren.erase( riter );
                local_subset = true;
                break;
            }
        }
        if ( !local_subset )
        {
            return false;
        }
    }
    vector<LocationGroup*>lgchildren = bigger->get_groups();
    vector<LocationGroup*>rgchildren = smaller->get_groups();
    for ( vector<LocationGroup*>::iterator riter = rgchildren.begin(); riter != rgchildren.end(); /* change is not needed*/ )
    {
        bool           local_subset = false;
        LocationGroup* lhs          = ( *riter );
        for ( vector<LocationGroup*>::iterator liter = lgchildren.begin(); liter != lgchildren.end(); ++liter )
        {
            LocationGroup* rhs = *liter;
            if ( is_subset( lhs, rhs, cubeMap ) )
            {
                if ( cubeMap != NULL )
                {
                    cubeMap->lgm[ rhs ]   = lhs;
                    cubeMap->r_lgm[ lhs ] = rhs;
                }
                lgchildren.erase( liter );
                rgchildren.erase( riter );
                local_subset = true;
                break;
            }
        }
        if ( !local_subset )
        {
            return false;
        }
    }

    return true;
}

/**
 * Testing is a "lhs" and "rhs" Machines are subsets of eachother (result saved
   in "bigger_left") or are equal.
 */
bool
is_subset( LocationGroup* bigger, LocationGroup*  smaller, CubeMapping* cubeMap  )
{
    if ( !( *bigger == *smaller ) )
    {
        return false;
    }
    if ( cubeMap != NULL )
    {
        cubeMap->lgm[ smaller ]  = bigger;
        cubeMap->r_lgm[ bigger ] = smaller;
    }
    vector<Vertex*>lchildren = bigger->get_children();
    vector<Vertex*>rchildren = smaller->get_children();
    for ( vector<Vertex*>::iterator riter = rchildren.begin(); riter != rchildren.end(); /* iterator is changed at the end of the loop*/ )
    {
        bool      local_subset = false;
        Location* lhs          = ( Location* )( *riter );
        for ( vector<Vertex*>::iterator liter = lchildren.begin(); liter != lchildren.end(); ++liter )
        {
            Location* rhs =  ( Location* )( *liter );
            if ( *lhs == *rhs )
            {
                if ( cubeMap != NULL )
                {
                    cubeMap->sysm[ rhs ]   = lhs;
                    cubeMap->r_sysm[ lhs ] = rhs;
                }
                lchildren.erase( liter );
                rchildren.erase( riter );
                local_subset = true;
                break;
            }
        }
        if ( !local_subset )
        {
            return false;
        }
    }
    return true;
}







/**
 * Testing is a "lhs" and "rhs" Machines are subsets of eachother (result saved
   in "bigger_left") or are equal.
 */
bool
is_subset( Cube& lhs, const Cube& rhs, bool& bigger_left, bool& is_equal )
{
    const vector<Machine*>& lroot  = lhs.get_machv();
    const vector<Machine*>& inroot = rhs.get_machv();
    if ( lroot.size() != inroot.size() )
    {
        is_equal = false;
    }

    const vector<Node*>&    lnode  = lhs.get_nodev();
    const vector<Node*>&    innode = rhs.get_nodev();
    const vector<Process*>& lproc  = lhs.get_procv();
    const vector<Process*>& inproc = rhs.get_procv();
    const vector<Thread*>&  lthrd  = lhs.get_thrdv();
    const vector<Thread*>&  inthrd = rhs.get_thrdv();

    if ( lproc.size() < inproc.size() &&  lthrd.size() < inthrd.size() )
    {
        bigger_left = false;
        is_equal    = false;
        return is_subset( innode, lnode, is_equal ) && is_subset( inproc, lproc, is_equal );
    }
    else
    if ( lproc.size() >= inproc.size() &&  lthrd.size() >= inthrd.size() )
    {
        bigger_left = true;

        if ( lproc.size() != inproc.size() &&  lthrd.size() != inthrd.size() )
        {
            is_equal = false;
        }

        if ( ( is_subset( lnode, innode, is_equal ) && is_subset( lproc, inproc, is_equal ) ) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        bigger_left = false;
        is_equal    = false;
        return false;
    }
}




/**
 * Testing is the "big" and the "small" nodes of a machine are subsets of eachother  or are equal.
 */
bool
is_subset( const vector<Node*>& big, const vector<Node*>& small, bool& is_equal )
{
    bool   subset = true;
    size_t num    = small.size();
    for ( size_t i = 0; i < num; ++i )
    {
        int big_num   = big[ i ]->num_groups();
        int small_num = small[ i ]->num_groups();
        if ( big_num < small_num )
        {
            subset   = false;
            is_equal = false;
            return subset;
        }
        else
        if ( big_num > small_num )
        {
            is_equal = false;
        }
    }
    return subset;
}



/**
 * Testing is a "big" and "small" Processes are subsets of eachother  or are equal.
 */
bool
is_subset( const vector<Process*>& big, const vector<Process*>& small, bool& is_equal )
{
    bool   subset = true;
    size_t num    = small.size();
    for ( size_t i = 0; i < num; ++i )
    {
        int big_num   = big[ i ]->num_children();
        int small_num = small[ i ]->num_children();
        if ( big_num < small_num )
        {
            subset   = false;
            is_equal = false;
            return subset;
        }
        else
        if ( big_num > small_num )
        {
            is_equal = false;
        }
    }
    return subset;
}


/**
 * Makes a connection ("mapping") between identical metrics, cnodes and threades
   and saves it in "cubeMap". The connection is allways map[metric1]-> metric2 .
   (-> stands for "points at"). Mapping of threads is tricky.

 */
void
createMapping( Cube& newCube, Cube& comp, CubeMapping& cubeMap, bool )
{
    createMappingMetric( newCube, comp, cubeMap );
    createMappingCnode( newCube, comp, cubeMap );
    createMappingSystem( newCube, comp, cubeMap );
}

/**
 * Creates a mapping in the metric dimension
 */
void
createMappingMetric( Cube& newCube, Cube& comp, CubeMapping& cubeMap )
{
    /* Mapping of the metric dimension */
    const vector<Metric*>& newCubemet  = newCube.get_metv();
    const vector<Metric*>& compmet     = comp.get_metv();
    int                    num_met_new = newCubemet.size();
    for ( int i = 0; i < num_met_new; ++i )
    {
        Metric* it = newCubemet[ i ];
        if ( it == NULL )
        {
            continue;
        }
        int num_met_old = compmet.size();
        for ( int j = 0; j < num_met_old; ++j )
        {
            Metric* cp = compmet[ j ];
            if ( cp == NULL )
            {
                continue;
            }
            if ( *it == *cp )
            {
                cubeMap.metm[ cp ] = it;
                break;
            }
        }
    }

    /* Mapping of the metric dimension */
    const vector<Metric*>& g_newCubemet  = newCube.get_ghost_metv();
    const vector<Metric*>& g_compmet     = comp.get_ghost_metv();
    int                    g_num_met_new = g_newCubemet.size();
    for ( int i = 0; i < g_num_met_new; ++i )
    {
        Metric* it = g_newCubemet[ i ];
        if ( it == NULL )
        {
            continue;
        }
        int num_met_old = g_compmet.size();
        for ( int j = 0; j < num_met_old; ++j )
        {
            Metric* cp = g_compmet[ j ];
            if ( cp == NULL )
            {
                continue;
            }
            if ( *it == *cp )
            {
                cubeMap.metm[ cp ] = it;
                break;
            }
        }
    }
}

/**
 * Creates a mapping in the calltree dimension
 */
void
createMappingCnode( Cube& newCube, Cube& comp, CubeMapping& cubeMap )
{
    /* Mapping of the program dimension */
    const vector<Cnode*>& newCubecnode  = newCube.get_cnodev();
    const vector<Cnode*>& compcnode     = comp.get_cnodev();
    int                   num_cnode_new = newCubecnode.size();
    int                   num_cnode_old = compcnode.size();
    for ( int i = 0; i < num_cnode_new; ++i )
    {
        Cnode* it = newCubecnode[ i ];
        for ( int j = 0; j < num_cnode_old; ++j )
        {
            Cnode* cp = compcnode[ j ];
            if ( *it == *cp )
            {
                cubeMap.cnodem[ cp ] = it;
                break;
            }
        }
    }
}



/**
 * Creates a mapping in the system dimension. Very naive realisation.
 */
void
createMappingSystem( Cube& newCube, Cube& comp, CubeMapping& cubeMap )
{
    /* Mapping of the program dimension */
    vector<Location*>newCube_locs = newCube.get_locationv();
    vector<Location*>comp_locs    = comp.get_locationv();
    for (  vector<Location*>::iterator loc_iter1 = newCube_locs.begin(); loc_iter1 != newCube_locs.end(); )
    {
        Location* it    = *loc_iter1;
        bool      found = false;
        for ( vector<Location*>::iterator loc_iter2 = comp_locs.begin(); loc_iter2 != comp_locs.end(); )
        {
            Location* cp = *loc_iter2;
            if ( *it == *cp )
            {
                cubeMap.sysm[ cp ] = it;
                comp_locs.erase( loc_iter2 );
                found = true;
                break;
            }
            else
            {
                ++loc_iter2;
            }
        }
        if ( found )
        {
            newCube_locs.erase( loc_iter1 );
        }
        else
        {
            ++loc_iter1;
        }
    }
}



/**
 * Creates a mapping in the system dimension
 */
void
createMappingSystem( Cube& newCube, Cube& comp, CubeMapping& cubeMap, bool collapse )
{
    /* Mapping of the system dimension */
    const vector<Machine*>& newCubemach = newCube.get_machv();
    for ( size_t i = 0; i < newCubemach.size(); ++i )
    {
        string oldDesc = newCubemach[ i ]->get_desc();
        newCubemach[ i ]->set_desc( oldDesc );
    }
    const vector<Node*>&    newCubenode   = newCube.get_nodev();
    const vector<Node*>&    compnode      = comp.get_nodev();
    const vector<Process*>& newCubeproc   = newCube.get_procv();
    const vector<Process*>& compproc      = comp.get_procv();
    int                     num_nodes_new = newCubenode.size();
    int                     num_nodes_old =  compnode.size();
    int                     num_procs_new = newCubeproc.size();
    int                     num_procs_old = compproc.size();
    bool                    tmp;
    if ( num_nodes_new >= num_nodes_old
         && is_subset( newCubenode, compnode, tmp )
         && is_subset( newCubeproc, compproc, tmp )
         && !collapse )
    {
//         int num = ( num_nodes_new == num_nodes_old ) ? num_nodes_new : num_nodes_old;
        int num =  num_nodes_old;
        for ( int i = 0; i < num; ++i )
        {
            Node* cp_it        = compnode[ i ];
            Node* newCube_it   = newCubenode[ i ];
            int   num_children = cp_it->num_groups();
            for ( int k = 0; k < num_children; k++ )
            {
                Process* newCubep = newCube_it->get_location_group( k );
                Process* cp       = cp_it->get_location_group( k );
                if ( *newCubep == *cp )
                {
                    int cp_thrds = cp->num_children();
                    for ( int m = 0; m < cp_thrds; m++ )
                    {
                        cubeMap.sysm[ cp->get_child( m ) ] = newCubep->get_child( m );
                    }
                }
            }
        }
    }
    else if ( num_procs_new == num_procs_old )     // map threads process-to-process
    {
        for ( int k = 0; k < num_procs_old; k++ )
        {
            Process* newCubep  = newCubeproc[ k ];
            Process* cp        = compproc[ k ];
            int      num_thrds = min( newCubep->num_children(), cp->num_children() );
            for ( int m = 0; m < num_thrds; m++ )
            {
                cubeMap.sysm[ cp->get_child( m ) ] = newCubep->get_child( m );
            }
        }
    }
    else     // map threads in the order they are globally defined
    {
        const vector<Thread*>  newCubethrd  = newCube.get_thrdv();
        const vector<Thread*>& compthrd     = comp.get_thrdv();
        int                    num_thrd_old = compthrd.size();
        for ( int i = 0; i < num_thrd_old; ++i )
        {
            cubeMap.sysm[ const_cast<Thread*>( compthrd[ i ] ) ] = const_cast<Thread*>( newCubethrd[ i ] );

            ostringstream id_map;
            id_map << "(" << compthrd[ i ]->get_parent()->get_rank()
                   << "," << compthrd[ i ]->get_rank() << ") to "
                   << "(" << newCubethrd[ i ]->get_parent()->get_rank()
                   << "," << newCubethrd[ i ]->get_rank() << ");";
            string oldDesc = newCubethrd[ i ]->get_parent()->get_parent()->get_parent()->get_desc();

            newCubethrd[ i ]->get_parent()->get_parent()
            ->get_parent()->set_desc( oldDesc + "\n" + id_map.str() );
        }
    }
}




/**
 * Copies the severities of "oldCube" in to matrix of severities in "newCube"
   according to the cube mapping "cubeMap" multiplying every value with factor "fac".
 */
void
add_sev( Cube& newCube, Cube& oldCube, CubeMapping& cubeMap, double fac )
{
    map<Metric*, Metric*>::iterator miter;
    map<Cnode*, Cnode*>::iterator   citer;
    map<Thread*, Thread*>::iterator siter;

    for ( miter = cubeMap.metm.begin(); miter != cubeMap.metm.end(); ++miter )
    {
        if ( miter->second->get_type_of_metric() == CUBE_METRIC_POSTDERIVED ||
             miter->second->get_type_of_metric() == CUBE_METRIC_PREDERIVED_INCLUSIVE ||
             miter->second->get_type_of_metric() == CUBE_METRIC_PREDERIVED_EXCLUSIVE
             )
        {
#ifdef HAVE_CUBELIB_DEBUG
            UTILS_DEBUG_PRINTF
            (
                ( CUBELIB_DEBUG_CUBELIB_TOOLS ),
                "\r    Skip metric %s (derived)\n",
                miter->first->get_uniq_name().c_str()
            );
#endif
            continue;
        }
        for ( citer = cubeMap.cnodem.begin(); citer != cubeMap.cnodem.end(); ++citer )
        {
            for ( siter = cubeMap.sysm.begin(); siter != cubeMap.sysm.end(); ++siter )
            {
                Value* val = oldCube.get_sev_adv( miter->first, citer->first, siter->first );
                if ( val != NULL )
                {
                    ( *val ) *= fac;
                    newCube.add_sev( miter->second, citer->second, siter->second, val );
                    val->Free();
                }
            }
        }
    }
}
/**
 * Copies the severities of "oldCube" in to matrix of severities in "newCube"
   according to the cube mapping "cubeMap".
 */
void
set_sev( Cube& newCube, Cube& oldCube, CubeMapping& cubeMap, DataDropCombination drop  )
{
    map<Metric*, Metric*>::iterator miter;
    map<Cnode*, Cnode*>::iterator   citer;
    map<Thread*, Thread*>::iterator siter;
    size_t                          num_metrics = cubeMap.metm.size();
    size_t                          num_cnodes  = cubeMap.cnodem.size();
    size_t                          cnode_step  = ( num_cnodes / 20 );
    cnode_step = ( cnode_step == 0 ) ? 1 : cnode_step;
    size_t i = 0;
    for ( miter = cubeMap.metm.begin(); miter != cubeMap.metm.end(); ++miter, ++i )
    {
        size_t j = 0;
        if ( miter->second->get_type_of_metric() == CUBE_METRIC_POSTDERIVED ||
             miter->second->get_type_of_metric() == CUBE_METRIC_PREDERIVED_INCLUSIVE ||
             miter->second->get_type_of_metric() == CUBE_METRIC_PREDERIVED_EXCLUSIVE
             )
        {
#ifdef HAVE_CUBELIB_DEBUG
            UTILS_DEBUG_PRINTF
            (
                ( CUBELIB_DEBUG_CUBELIB_TOOLS ),
                "\r    Skip %dth metric %s (derived)\n",
                i,
                miter->first->get_uniq_name().c_str()
            );
#endif
            continue;
        }
        for ( citer = cubeMap.cnodem.begin(); citer != cubeMap.cnodem.end(); ++citer, ++j  )
        {
#ifdef HAVE_CUBELIB_DEBUG
            if ( j % cnode_step == 0 )
            {
                UTILS_DEBUG_PRINTF
                (
                    ( CUBELIB_DEBUG_CUBELIB_TOOLS ),
                    "\r     Copy %dth metric %s of %d (%d/%d)",
                    i,
                    miter->first->get_uniq_name().c_str(),
                    num_metrics,
                    num_cnodes
                );
            }
#endif
            for ( siter = cubeMap.sysm.begin(); siter != cubeMap.sysm.end(); ++siter )
            {
                cube::CalculationFlavour calc_flavor = ( miter->second->get_type_of_metric() == CUBE_METRIC_INCLUSIVE )
                                                       ? cube::CUBE_CALCULATE_INCLUSIVE : cube::CUBE_CALCULATE_EXCLUSIVE;
                Value* val = oldCube.get_sev_adv( miter->first, cube::CUBE_CALCULATE_INCLUSIVE, citer->first, calc_flavor,  siter->first, cube::CUBE_CALCULATE_EXCLUSIVE );
                if ( val == NULL )
                {
                    continue;
                }
                newCube.set_sev( miter->second, citer->second, siter->second, val );
                val->Free();
            }
        }


        if ( drop == OLD_CUBE_DROP || drop == BOTH_CUBES_DROP )
        {
            oldCube.dropAllRowsInMetric( miter->first ); // assuming that source metric used only once
        }
        if ( drop == NEW_CUBE_DROP || drop == BOTH_CUBES_DROP )
        {
            newCube.dropAllRowsInMetric( miter->second );
        }
#ifdef HAVE_CUBELIB_DEBUG
        UTILS_DEBUG_PRINTF
        (
            ( CUBELIB_DEBUG_CUBELIB_TOOLS ),
            "\r     Copy %dth metric %s of %d (%d/%d)",
            i,
            miter->first->get_uniq_name().c_str(),
            num_metrics,
            num_cnodes
        );
#endif
    }
}


/**
 * Copies the severities of "oldCube" in to matrix of severities in "newCube"
   according to the cube mapping "cubeMap".
 */
void
set_sevs( Cube& newCube, Cube& oldCube, CubeMapping& cubeMap, DataDropCombination drop )
{
    map<Metric*, Metric*>::iterator miter;
    map<Cnode*, Cnode*>::iterator   citer;
    map<Thread*, Thread*>::iterator siter;
    size_t                          num_metrics = cubeMap.metm.size();
    size_t                          num_cnodes  = cubeMap.cnodem.size();
    size_t                          cnode_step  = ( num_cnodes / 20 );
    cnode_step = ( cnode_step == 0 ) ? 1 : cnode_step;
    size_t i = 0;
    for ( miter = cubeMap.metm.begin(); miter != cubeMap.metm.end(); ++miter, ++i )
    {
        size_t j = 0;
        if ( miter->second->get_type_of_metric() == CUBE_METRIC_POSTDERIVED ||
             miter->second->get_type_of_metric() == CUBE_METRIC_PREDERIVED_INCLUSIVE ||
             miter->second->get_type_of_metric() == CUBE_METRIC_PREDERIVED_EXCLUSIVE
             )
        {
            continue;
        }
        for ( citer = cubeMap.cnodem.begin(); citer != cubeMap.cnodem.end(); ++citer, ++j  )
        {
#ifdef HAVE_CUBELIB_DEBUG
            if ( j % cnode_step == 0 )
            {
                UTILS_DEBUG_PRINTF
                (
                    ( CUBELIB_DEBUG_CUBELIB_TOOLS ),
                    "\r     Copy %dth metric %s of %d (%d/%d)",
                    i,
                    miter->first->get_uniq_name().c_str(),
                    num_metrics,
                    num_cnodes
                );
            }
#endif
            if ( miter->first->isRowWise() )
            {
                cube::CalculationFlavour calc_flavor = ( miter->second->get_type_of_metric() == CUBE_METRIC_INCLUSIVE )
                                                       ? cube::CUBE_CALCULATE_INCLUSIVE : cube::CUBE_CALCULATE_EXCLUSIVE;
                char* val = oldCube.get_sevs_raw( miter->first, cube::CUBE_CALCULATE_INCLUSIVE, citer->first, calc_flavor );
                if ( val == NULL )
                {
                    continue;
                }
                newCube.set_sevs_raw( miter->second, citer->second, val );
            }
            else
            {
                for ( siter = cubeMap.sysm.begin(); siter != cubeMap.sysm.end(); ++siter )
                {
                    cube::CalculationFlavour calc_flavor = ( miter->second->get_type_of_metric() == CUBE_METRIC_INCLUSIVE )
                                                           ? cube::CUBE_CALCULATE_INCLUSIVE : cube::CUBE_CALCULATE_EXCLUSIVE;
                    Value* val = oldCube.get_sev_adv( miter->first, cube::CUBE_CALCULATE_INCLUSIVE, citer->first, calc_flavor,  siter->first, cube::CUBE_CALCULATE_EXCLUSIVE );
                    if ( val == NULL )
                    {
                        continue;
                    }
                    newCube.set_sev( miter->second, citer->second, siter->second, val );
                    val->Free();
                }
            }
        }

        if ( drop == OLD_CUBE_DROP || drop == BOTH_CUBES_DROP )
        {
            oldCube.dropAllRowsInMetric( miter->first ); // assuming that source metric used only once
        }
        if ( drop == NEW_CUBE_DROP || drop == BOTH_CUBES_DROP )
        {
            newCube.dropAllRowsInMetric( miter->second );
        }
#ifdef HAVE_CUBELIB_DEBUG
        UTILS_DEBUG_PRINTF
        (
            ( CUBELIB_DEBUG_CUBELIB_TOOLS ),
            "\r     Copy %dth metric %s of %d (%d/%d)",
            i,
            miter->first->get_uniq_name().c_str(),
            num_metrics,
            num_cnodes
        );
#endif
    }
}




static bool
_almost_equal( double x, double y, int ulp )
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::abs( x - y ) < std::numeric_limits<double>::epsilon() * std::abs( x + y ) * ulp
           // unless the result is subnormal
           || std::abs( x - y ) < std::numeric_limits<double>::min();

//     return (std::abs(x-y) < std::abs(x+y) * 1E-14 *ulp) || (std::abs(x-y) < std::numeric_limits<double>::min());
}


/**
 * Compares  the severities of "oldCube" with severities in "newCube" according
   to the cube mapping "cubeMap" and returns whether all are equal.
 */
bool
check_sev( Cube& newCube, Cube& oldCube, CubeMapping& cubeMap )
{
    bool                            is_equal = true;
    map<Metric*, Metric*>::iterator miter;
    map<Cnode*, Cnode*>::iterator   citer;
    map<Thread*, Thread*>::iterator siter;
    for ( miter = cubeMap.metm.begin(); miter != cubeMap.metm.end(); ++miter )
    {
        cube::CalculationFlavour calc_flavor1 = ( miter->first->get_type_of_metric() == CUBE_METRIC_INCLUSIVE )
                                                ? cube::CUBE_CALCULATE_INCLUSIVE : cube::CUBE_CALCULATE_EXCLUSIVE;
        cube::CalculationFlavour calc_flavor2 = ( miter->second->get_type_of_metric() == CUBE_METRIC_INCLUSIVE )
                                                ? cube::CUBE_CALCULATE_INCLUSIVE : cube::CUBE_CALCULATE_EXCLUSIVE;
        if ( ( calc_flavor1 != calc_flavor2 )  && ( calc_flavor1 == CUBE_CALCULATE_EXCLUSIVE ) )
        {
            calc_flavor1 = CUBE_CALCULATE_INCLUSIVE;
        }
        else if ( ( calc_flavor1 != calc_flavor2 )  && ( calc_flavor2 == CUBE_CALCULATE_EXCLUSIVE ) )
        {
            calc_flavor2 = CUBE_CALCULATE_INCLUSIVE;
        }

        for ( citer = cubeMap.cnodem.begin(); citer != cubeMap.cnodem.end(); ++citer )
        {
            if ( miter->first->isBuildIn() )
            {
                double* first_row  = newCube.get_sevs( miter->first, cube::CUBE_CALCULATE_INCLUSIVE,  citer->first, calc_flavor1 );
                double* second_row = oldCube.get_sevs( miter->second, cube::CUBE_CALCULATE_INCLUSIVE,  citer->second, calc_flavor2 );
                for ( size_t i = 0; i < cubeMap.sysm.size(); i++ )
                {
                    if ( !_almost_equal( first_row[ i ], second_row[ i ], 2 ) )
                    {
                        is_equal = false;
                        cout << miter->first->get_uniq_name() << " vs. " << miter->second->get_uniq_name() << endl;
                        cout << citer->first->get_callee()->get_name() << " vs. " << citer->second->get_callee()->get_name() << endl;
                        cout << first_row[ i ] << " != " << second_row[ i ] << "(" << i << "th element )" << endl;
                        delete[] first_row;
                        delete[] second_row;
                        return false;
                    }
                }
                delete[] first_row;
                delete[] second_row;
            }
            else
            {
                for ( siter = cubeMap.sysm.begin(); siter != cubeMap.sysm.end(); ++siter )
                {
                    double newval = newCube.get_sev( miter->first,  citer->first,  siter->first );
                    double oldval = oldCube.get_sev( miter->second, citer->second, siter->second );
                    if ( !_almost_equal( oldval, newval, 2 ) )
                    {
                        is_equal = false;
                        cout << miter->first->get_uniq_name() << " vs. " << miter->second->get_uniq_name() << endl;
                        cout << citer->first->get_callee()->get_name() << " vs. " << citer->second->get_callee()->get_name() << endl;
                        cout << siter->first->get_name() << " vs. " << siter->second->get_name() << endl;
                        cout << newval << " != " << oldval << endl;
                        return false;
                    }
                }
            }
        }
        oldCube.dropAllRowsInMetric( miter->first );
        newCube.dropAllRowsInMetric( miter->second );
    }
    return is_equal;
}



/**
 * Adds in to "newCube" topology from the "oldCube" according the cube mapping "cubeMap".
 */
void
add_top( Cube&        newCube,
         Cube&        oldCube,
         CubeMapping& cubeMap )
{
    const vector<Cartesian*>& cartv = oldCube.get_cartv();
    int                       num   = cartv.size();

    for ( int i = 0; i < num; ++i )
    {
        Cartesian* newCart = newCube.def_cart( cartv[ i ]->get_ndims(),
                                               cartv[ i ]->get_dimv(),
                                               cartv[ i ]->get_periodv() );

        newCart->set_name( cartv[ i ]->get_name() );
        newCart->set_namedims( cartv[ i ]->get_namedims() );

        const TopologyMap&              coordv = cartv[ i ]->get_cart_sys();
        map<Thread*, Thread*>::iterator th_it;

        for ( th_it = cubeMap.sysm.begin(); th_it != cubeMap.sysm.end(); ++th_it )
        {
            TopologyMap::const_iterator                                   it;
            pair<TopologyMap::const_iterator, TopologyMap::const_iterator>ret;
            ret = coordv.equal_range(  th_it->first  );
            if ( ret.first  != ret.second )
            {
                for ( it = ret.first; it != ret.second; ++it )
                {
                    newCube.def_coords( newCart, cubeMap.sysm[ ( Thread* )( th_it->first ) ], ( *it ).second );
                }
            }
        }
    }
}

/**
 * Merges two lists of topologies
 */
void
merge_top( Cube& newCube, Cube& cube1, Cube& cube2 )
{
    const vector<Cartesian*>& old_top1 = cube1.get_cartv();
    const vector<Cartesian*>& old_top2 = cube2.get_cartv();
    vector<Cartesian*>        new_top;

    for ( unsigned i = 0; i < old_top1.size(); ++i )
    {
        if ( new_top.empty() )
        {
            new_top.push_back( ( old_top1[ i ] )->clone( newCube.get_thrdv() ) );
        }
        else
        {
            bool present = true;
            for ( unsigned j = 0; j < new_top.size(); ++j )
            {
                present = present && (  *( new_top[ j ] ) == *( old_top1[ i ] ) );
            }
            if ( !present )
            {
                new_top.push_back( ( old_top1[ i ] )->clone( newCube.get_thrdv() ) );
            }
        }
    }
    for ( unsigned i = 0; i < old_top2.size(); ++i )
    {
        if ( new_top.empty() )
        {
            new_top.push_back( ( old_top2[ i ] )->clone( newCube.get_thrdv() ) );
        }
        else
        {
            bool present = true;
            for ( unsigned j = 0; j < new_top.size(); ++j )
            {
                present = present && ( *( new_top[ j ] ) == *( old_top2[ i ] ) );
            }
            if ( !present )
            {
                new_top.push_back( ( old_top2[ i ] )->clone( newCube.get_thrdv() ) );
            }
        }
    }
    newCube.add_cart( new_top );
}


/**
 * Set all severities (for every thread) in "newCube" for given Metric "src" and
   Cnode "cnode" into Metric "dest" and same "cnode".
 */
void
copy_sev( Cube& newCube, Metric* src, Metric* dest, Cnode* cnode )
{
    const vector<Thread*>&          threadv = newCube.get_thrdv();
    vector<Thread*>::const_iterator it      = threadv.begin();
    while ( it != threadv.end() )
    {
        Value* v = newCube.get_sev_adv( src, cnode, *it );
        newCube.set_sev( dest, cnode, *it, v );
        v->Free();
        ++it;
    }
}
/**
 * Add all severities (for every thread) in "newCube" for given Metric "src" and
   Cnode "cnode" into Metric "dest" and same "cnode".
 */
void
add_sev( Cube& newCube, Metric* src, Metric* dest, Cnode* cnode )
{
    const vector<Thread*>&          threadv = newCube.get_thrdv();
    vector<Thread*>::const_iterator it      = threadv.begin();
    while ( it != threadv.end() )
    {
        Value* v = newCube.get_sev_adv( src, cnode, *it );
        newCube.add_sev( dest, cnode, *it, v );
        v->Free();
        ++it;
    }
}


/**
 * Applys a filter to a cube file.
 */
void
cube_apply_filter( Cube& newCube, Cube& rhs, Filter& filter,
                   CubeMapping& mapping )
{
    metric_merge( newCube, rhs, mapping );
    sysres_merge( newCube, rhs, mapping, false, false );
    const vector<Cnode*>root_nodes = rhs.get_root_cnodev();
    for ( vector<Cnode*>::const_iterator it = root_nodes.begin();
          it != root_nodes.end(); ++it )
    {
        Cnode* new_root = def_cnode( newCube, **it, NULL );
        mapping.cnodem.insert( pair<Cnode*, Cnode*>( *it, new_root ) );
        add_sev( newCube, rhs, mapping, *it );
        _cube_apply_filter( newCube, rhs, new_root, *it, mapping, filter );
    }
}



void
_cube_apply_filter( Cube& lhs,  Cube& rhs,
                    Cnode* lhs_parent, Cnode* rhs_parent, CubeMapping& mapping,
                    Filter& filter )
{
    for ( unsigned int i = 0; i < rhs_parent->num_children(); ++i )
    {
        bool   found     = false;
        Cnode* rhs_child = rhs_parent->get_child( i );
        Cnode* lhs_child = NULL;

        if ( filter.matches( rhs_child ) )
        {
            continue;
        }

        for ( unsigned int j = 0; j < lhs_parent->num_children(); ++j )
        {
            lhs_child = lhs_parent->get_child( j );
            if ( *( lhs_child->get_callee() ) == *( rhs_child->get_callee() ) )
            {
                found = true;
                break;
            }
        }
        if ( found == false )
        {
            lhs_child = def_cnode( lhs, *rhs_child, lhs_parent );
        }
        mapping.cnodem.insert( pair<Cnode*, Cnode*>( rhs_child, lhs_child ) );
        add_sev( lhs, rhs, mapping, rhs_child );
    }

    // Now go into depth:
    for ( unsigned int i = 0; i < rhs_parent->num_children(); ++i )
    {
        Cnode* rhs_child = rhs_parent->get_child( i );

        if ( filter.matches( rhs_child ) == true )
        {
            mapping.cnodem.insert( pair<Cnode*, Cnode*>( rhs_child, lhs_parent ) );
            add_sev( lhs, rhs, mapping, rhs_child, false );
            _cube_apply_filter( lhs, rhs, lhs_parent, rhs_child,
                                mapping, filter );
        }
        else
        {
            _cube_apply_filter( lhs, rhs, mapping.cnodem[ rhs_child ], rhs_child,
                                mapping, filter );
        }
    }
}

void
add_sev( Cube& newCube, Cube& oldCube, CubeMapping& old2new,
         Cnode* oldCnode, bool with_visits )
{
    map<Metric*, Metric*>::iterator miter;
    map<Cnode*,  Cnode*>::iterator  citer;
    map<Thread*, Thread*>::iterator siter;

    citer = old2new.cnodem.find( oldCnode );
    if ( citer == old2new.cnodem.end() )
    {
        throw RuntimeError( "Could not find the node "
                            + oldCnode->get_callee()->get_name() + " in mapping." );
    }

    for ( miter = old2new.metm.begin(); miter != old2new.metm.end(); ++miter )
    {
        if ( with_visits == false && miter->first->get_uniq_name() == "visits" )
        {
            continue;
        }
        for ( siter = old2new.sysm.begin(); siter != old2new.sysm.end(); ++siter )
        {
            double val = oldCube.get_sev( miter->first, citer->first, siter->first );
            if ( val != 0.0 )
            {
                newCube.add_sev( miter->second, citer->second, siter->second, val );
            }
        }
    }
}


/**
 * Creates a wide search enumeration of the trees, wqhich roots are saved in list_of_vertices
 */
template<class T>
void
createTreeEnumeration( vector<T*>& list_of_vertices )
{
    unsigned int current_index = 0;
    for (; current_index < list_of_vertices.size(); current_index++ )
    {
        T*        _v = list_of_vertices[ current_index ];
        vector<T*>_v_children;
        for ( unsigned i = 0; i < _v->num_children(); ++i )
        {
            _v_children.push_back( _v->get_child( i ) );
        }
        stable_sort( _v_children.begin(), _v_children.end(), id_compare );
        for ( unsigned i = 0; i < _v_children.size(); ++i )
        {
            list_of_vertices.push_back( _v_children[ i ] );
        }
    }
}






template<class T>
bool
compareVertices( vector<T*>& lhs, vector<T*>& rhs )
{
//     bool to_return = true;
    if ( lhs.size() != rhs.size() )
    {
        return false;
    }
    for ( unsigned i = 0; i < lhs.size(); ++i )
    {
        if ( !(  lhs[ i ]->get_id() == rhs[ i ]->get_id() ) )
        {
            return false;
        }
    }
    return true;
}


inline bool
id_compare( IdentObject* v1, IdentObject* v2 )
{
    return v1->get_id() < v2->get_id();
}



template<class T>
bool
compareTrees( vector<T*>& lhs, vector<T*>& rhs )
{
    stable_sort( lhs.begin(), lhs.end(), id_compare );
    stable_sort( rhs.begin(), rhs.end(), id_compare );

    createTreeEnumeration<T>( lhs );
    createTreeEnumeration<T>( rhs );
    return compareVertices<T>( lhs, rhs );
}



/**
 * Compares dimensions of two cubes. Using only O(n) and O(N Log(N)) algorithms
 */
bool
compare_metric_dimensions( Cube& lhsCube, Cube& rhsCube )
{
    vector<Metric*>lhs_m_roots = lhsCube.get_root_metv();
    vector<Metric*>rhs_m_roots = rhsCube.get_root_metv();

    return compareTrees<Metric>( lhs_m_roots, rhs_m_roots );
}

/**
 * Compares dimensions of two cubes. Using only O(n) and O(N Log(N))  algorithms
 */
bool
compare_calltree_dimensions( Cube& lhsCube, Cube& rhsCube )
{
    vector<Cnode*>lhs_c_roots = lhsCube.get_root_cnodev();
    vector<Cnode*>rhs_c_roots = rhsCube.get_root_cnodev();

    return compareTrees<Cnode>( lhs_c_roots, rhs_c_roots );
}
/**
 * Compares dimensions of two cubes. Using only O(n) and O(N Log(N)) algorithms
 */
bool
compare_system_dimensions( Cube& lhsCube, Cube& rhsCube )
{
    vector<Machine*>_lhs_s_roots = lhsCube.get_machv();
    vector<Machine*>_rhs_s_roots = rhsCube.get_machv();

    vector<Sysres*>lhs_s_roots;
    vector<Sysres*>rhs_s_roots;
    for ( vector<Machine*>::iterator it = _lhs_s_roots.begin(); it != _lhs_s_roots.end(); ++it )
    {
        lhs_s_roots.push_back( ( Sysres* )( *it ) );
    }
    for ( vector<Machine*>::iterator it = _rhs_s_roots.begin(); it != _rhs_s_roots.end(); ++it )
    {
        rhs_s_roots.push_back( ( Sysres* )( *it ) );
    }

    return compareTrees<Sysres>( lhs_s_roots, rhs_s_roots );
}



/**
 *  Another implementation of diff operation
 * outCube should habe by the time of call merged dimension structure
 */
void
diff_sevs( Cube& outCube, Cube& minCube, CubeMapping& lhsmap, Cube& subCube, CubeMapping& rhsmap )
{
    const std::vector<Metric*>& _mets   = outCube.get_metv();
    const std::vector<Cnode*>&  _cnodes = outCube.get_cnodev();
    const std::vector<Thread*>& _thrds  =  outCube.get_thrdv();
    for ( std::vector<Metric*>::const_iterator m_iter = _mets.begin(); m_iter != _mets.end(); ++m_iter )
    {
        Metric* metric = *m_iter;
        if ( metric == NULL )
        {
            continue;
        }
        cube::CalculationFlavour calc_flavor = ( metric->get_type_of_metric() == CUBE_METRIC_INCLUSIVE )
                                               ? cube::CUBE_CALCULATE_INCLUSIVE : cube::CUBE_CALCULATE_EXCLUSIVE;

        for ( std::vector<Cnode*>::const_iterator c_iter = _cnodes.begin(); c_iter != _cnodes.end(); ++c_iter )
        {
            Cnode* cnode = *c_iter;
            for ( std::vector<Thread*>::const_iterator t_iter = _thrds.begin(); t_iter != _thrds.end(); ++t_iter )
            {
                Thread* thread = *t_iter;

                Value* min_val = NULL;
                Value* sub_val = NULL;
                if ( lhsmap.r_metm[ metric ] != NULL &&
                     lhsmap.r_cnodem[ cnode ] != NULL &&
                     lhsmap.r_sysm[ thread ] != NULL
                     )
                {
                    min_val = minCube.get_sev_adv( lhsmap.r_metm[ metric ], cube::CUBE_CALCULATE_INCLUSIVE,  lhsmap.r_cnodem[ cnode ], calc_flavor, lhsmap.r_sysm[ thread ], cube::CUBE_CALCULATE_EXCLUSIVE );
                }
                if ( rhsmap.r_metm[ metric ] != NULL &&
                     rhsmap.r_cnodem[ cnode ] != NULL &&
                     rhsmap.r_sysm[ thread ] != NULL
                     )
                {
                    sub_val = subCube.get_sev_adv( rhsmap.r_metm[ metric ], cube::CUBE_CALCULATE_INCLUSIVE, rhsmap.r_cnodem[ cnode ], calc_flavor, rhsmap.r_sysm[ thread ], cube::CUBE_CALCULATE_EXCLUSIVE );
                }
                if ( sub_val != NULL )
                {
                    sub_val->
                    operator*=( -1. );
                }

                Value* val = NULL;
                if ( min_val != NULL )
                {
                    val = min_val;
                    if ( sub_val != NULL )
                    {
                        val->
                        operator+=( sub_val );
                    }
                }
                else
                {
                    if ( sub_val != NULL )
                    {
                        val = sub_val;
                    }
                }
                if ( val != NULL )
                {
                    outCube.set_sev( metric, cnode, thread, val );
                }
                if ( min_val != NULL && min_val != val ) // in code above there are cases, where val and min_val and sub_val can get identical
                {
                    min_val->Free();
                }
                if ( sub_val != NULL && sub_val != val )
                {
                    sub_val->Free();
                }
                if ( val != NULL )
                {
                    val->Free();
                }
            }
        }
    }
}
} /* End of unnamed namespace */
