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
 * \file CnodeInfo.h
 * \brief Extends a InfoObj class to be able to carry information about call tree.
 */


#ifndef CUBE_CNODEINFO
#define CUBE_CNODEINFO

#include <vector>

#include "InfoObj.h"

namespace cube
{
class Cube;
class InfoObj;
class Cnode;

using std::vector;

/**
 * Extension of InfoObj.
 */
class CCnodeInfo : public InfoObj
{
private:
    const vector<Cnode*>& m_cnodes; ///< A set of call nodes.
    const Cube*           m_cube;   ///< CUBE, where the information is saved.
public:
    CCnodeInfo( const Cube* );      ///< A constructor.
    const vector<Cnode*>&
    get_cnodev();                   ///< Just gives a corresponding "cnode" for this CNodeInfo object.

private:
    void
    classify_cnode( Cnode* );
    void
    propagate_com( Cnode* );
};
}

#endif
