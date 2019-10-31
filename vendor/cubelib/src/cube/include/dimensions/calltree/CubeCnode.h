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
**  Copyright (c) 2015                                                     **
**  RWTH Aachen University, JARA-HPC                                       **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/**
 * \file CubeCnode.h
 * \brief Provides a class with an element of call tree.
 */
#ifndef CUBE_CNODE_H
#define CUBE_CNODE_H

#include <iosfwd>
#include <string>
#include <utility>
#include <vector>

#include "CubeSerializableVertex.h"
#include "CubeTypes.h"

/*
 *
 * class Cnode
 *
 */

namespace cube
{
class Connection;
class CubeProxy;
class Region;

/**
 * An element of the call tree. As child of general element of a tree (Vertex).
 */
class Cnode : public SerializableVertex
{
public:
    /// @name Construction & destruction
    /// @{

    Cnode( Region*            callee,
           const std::string& mod,
           int                line,
           Cnode*             parent,
           uint32_t           id = 0 );

    ~Cnode();                                   // /< Desctructor... destroys remapping_cnode and children recursively.

    /// @brief
    ///     Factory method to create a new Cnode via the serialization framework.
    /// @param connection
    ///     Active Cube connection.
    /// @param cubeProxy
    ///     Cube proxy for internal cross-referencing of objects.
    /// @return
    ///     Pointer to new cnode.
    ///
    static Serializable*
    create( Connection&      connection,
            const CubeProxy& cubeProxy );

    /// @}
    /// @name Serialization
    /// @{

    /// @copydoc SerializableVertex::pack
    ///
    virtual void
    pack( Connection& connection ) const;

    /// @copydoc Serializable::get_serialization_key
    ///
    virtual std::string
    get_serialization_key() const;

    /// @copydoc Serializable::get_serialization_key
    ///
    static std::string
    get_static_serialization_key();

    /// @}

    inline
    int
    get_line() const
    {
        return line;
    }                                     // /< Returns a start line of a region.

    inline
    std::string
    get_mod() const
    {
        return mod;
    }                                           // /< Returns a modus of a call node.

    inline
    Region*
    get_callee() const
    {
        return callee;
    }                                            // /< Returns a region, from where entered here.
    Region*
    get_caller() const;


    inline
    Cnode*
    get_parent() const
    {
        return static_cast<Cnode*>( Vertex::get_parent() ); // /< Get a call three from where enetered.
    }

    inline
    Cnode*
    get_child( unsigned int i ) const
    {
        return static_cast<Cnode*>( Vertex::get_child( i ) ); // /< Get a further calls of from this call.
    }

    void
    add_num_parameter( std::string key,
                       double      param );                                    // /< Adds an additional numeric parameter to the parameter list.
    void
    add_str_parameter( std::string key,
                       std::string param );                                         // /< Adds an additional string parameter to the parameter list.


    inline
    std::vector < std::pair < std::string, double> >
    get_num_parameters()
    {
        return num_parameters;
    }
    // /< Returns a list of numerical parameters, with which a callee was called/marked.
    inline
    std::vector < std::pair  <std::string, std::string> >
    get_str_parameters()
    {
        return str_parameters;
    }                                                     // /< Returns a list of string parameters, with which a callee was called/marked.

    inline
    const std::vector < std::pair < std::string, double> >&
    numeric_parameters() const
    {
        return num_parameters;
    }
    // /< Returns a list of numerical parameters, with which a callee was called/marked.
    inline
    const std::vector < std::pair  <std::string, std::string> >&
    string_parameters() const
    {
        return str_parameters;
    }                                                     // /< Returns a list of string parameters, with which a callee was called/

    inline
    bool
    isHidden() const
    {                                                    // /< Returns the status "hidden" or not of the node
        return is_hidden;
    }


    inline
    bool
    isVisible() const
    {                                                    // /< Returns the status "not hidden"
        return !isHidden();
    }

    const Cnode*
    get_remapping_cnode( int64_t process_rank = -1 ) const;                                // /< Returns either remapped cnode for given "process id"  or "common remapped cnode" or this.

    void
    set_remapping_cnode( const Cnode* );                              // /< Sets common remapped cnode for this cnode and cluster normalization factor

    void
        set_remapping_cnode( int64_t, const Cnode*, int64_t );       // /< Sets remapped cnode for this cnode depending on process id  and cluster normalization factor.

    int64_t
        get_cluster_normalization( int64_t ) const;


    inline
    bool
    is_clustered() const
    {
        return !no_remapping;
    }

    const std::vector<cube::Cnode*>&
    get_whole_subtree() const
    {
        return whole_subtree;
    }





    void
    hide( bool recursive = true );                                              // /< Hides cnode

    void
    set_as_leaf();                                      // /< Hides all leaves.

    void
    writeXML( std::ostream& out,
              bool          cube3export = false ) const;               // /< Writes a xml-representation of the call node.

    bool
    weakEqual( Cnode* _c );                                             // /< compared just a body of cnode, not the hierarhy...

    void
    whole_tree_is_collected()
    {
        collected_whole_tree = true;
    };

    bool
    is_whole_tree_collected()
    {
        return collected_whole_tree;
    }

    void
    fill_whole_tree_vector();

protected:



    std::vector<cube::Cnode*>&
    get_sub_tree_vector();

private:

    /// @brief
    ///     Constructs a Cnode object via a Cube connection.
    /// @param connection
    ///     Active Cube connection.
    /// @param existingCnodes
    ///     Vector of Cnodes to identify parent Cnodes.
    /// @param existingRegions
    ///     Vector of Regions for cross-referencing.
    ///
    /// @note
    ///     This constructor is called by the factory method.
    ///
    Cnode ( Connection&                  connection,
            const std::vector< Cnode* >  existingCnodes,
            const std::vector< Region* > existingRegions );

    Region*                                           callee; ///< Region in a source code, where the call node was entered from.
    std::string                                       mod;    ///< Modus.
    int                                               line;   ///< Start line in a region.
    std::vector<std::pair<std::string, std::string> > str_parameters;
    std::vector<std::pair<std::string, double> >      num_parameters;
    const Cnode*                                      common_remapping_cnode;
    bool                                              no_remapping;  // /< set to "true"ifnoclustering is engaged.
    std::map<int64_t, const Cnode*>                   remapping_cnodes;
    bool                                              is_hidden;     // /< Signalizes, that this cnode is hidden and contributes to excl value of the parent.
    std::map<int64_t, int64_t>                        cluster_normalization;
    std::vector<Cnode*>                               whole_subtree; // used to calculate inclusive value by exclusive metric
    bool                                              collected_whole_tree;
};

bool
operator==( const Cnode& a,
            const Cnode& b );
}





#endif
