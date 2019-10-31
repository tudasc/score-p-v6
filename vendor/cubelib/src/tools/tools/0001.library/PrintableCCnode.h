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



#ifndef PRINTABLECCNODE_H_GUARD_
#define PRINTABLECCNODE_H_GUARD_

/**
 * @file    PrintableCCnode.h
 * @brief   Contains a class that extends the CCnode class by providing
 *          further methods for output.
 */

#include <vector>
#include <iostream>

#include "CCnode.h"

namespace cube
{
class CnodeMetric;
class Region;

/**
 * @class   PrintableCCnode
 * @brief   Extends CCnode and provides further methods for output.
 *
 * The provided methods can print out several compute aggregated values
 * and basically support two modes. The first is a backtrace like output
 * and the second is a tree like output that visualizes which function
 * was called by which one.
 */
class PrintableCCnode : public CCnode
{
public:
    const static int column_width = 15;

    PrintableCCnode( Region*            callee,
                     const std::string& mod,
                     int                line,
                     Cnode*             parent,
                     uint32_t           id,
                     int                cache_size );

    /**
     * @fn void print(std::vector<CnodeMetric*> const& metrics,
     *                std::ostream& stream) const
     *
     * Prints out the call-tree structure next to a table containing all
     * stored values for the metrics.
     *
     * @param metrics A list of CnodeMetrics that is displayed.
     * @param stream The stream, this method writes its' output to. Defaults to
     *        cout.
     */
    void
    print( std::vector<CnodeMetric*>const& metrics,
           std::ostream&                   stream = std::cout );

    /**
     * @fn void print_callpath(std::vector<CnodeMetric*> const& metrics,
     *                        std::ostream& stream) const
     *
     * Prints out a backtrace from a specific node to its' root node. Also
     * prints out a table containing all stored values for the metrics.
     *
     * @param metrics A list of CnodeMetrics that is displayed.
     * @param stream The stream, this method writes its' output to. Defaults to
     *        cout.
     */
    void
    print_callpath(
        std::vector<CnodeMetric*>const& metrics,
        std::ostream&                   stream = std::cout );

    /**
     * @fn std::string to_string(
     *          std::vector<CnodeMetric*> const& metrics) const
     *
     * Behaves exactly like the print method, but returns a string containing
     * the output.
     *
     * @param metrics A list of CnodeMetrics that is displayed.
     */
    std::string
    to_string(
        std::vector<CnodeMetric*>const& metrics
            = std::                     vector<CnodeMetric*>() );

    /**
     * @fn std::string to_string_callpath(
     *          std::vector<CnodeMetric*> const& metrics) const
     *
     * Behaves exactly like the print_callpath method, but returns a string
     * containing the output.
     *
     * @param metrics A list of CnodeMetrics that is displayed.
     */
    std::string
    to_string_callpath(
        std::vector<CnodeMetric*>const& metrics
            = std::                     vector<CnodeMetric*>() );

    /**
     * @fn PrintableCCnode* get_parent() const
     *
     * Returns the node's parent. In case, this node is the root of the call
     * tree, NULL is returned.
     */
    PrintableCCnode*
    get_parent();

    /**
     * @fn PrintableCCnode* get_child(unsigned int id) const
     *
     * Returns the id'th child of the node. In case the node has less than
     * id children, the behaviour is undefined.
     *
     * @param id id of the child of interest.
     */
    PrintableCCnode*
    get_child( unsigned int id );

    /**
     * @fn std::vector<int> print_headers(
     *              std::vector<CnodeMetric*> const& metrics,
     *              std::ostream& stream) const
     *
     * Prints the headers of the table for the metrics to a certain stream.
     * Also checks, for how many cubes the metric is defined and returns a
     * vector of integers containing this information where the i-th entry
     * of that vector corresponds to the i-th entry of the passed-in metrics
     * vector.
     *
     * @param metrics A vector of CnodeMetric instances.
     * @param stream The ostream, this function will print to.
     */
    std::vector<int>
    print_headers(
        std::vector<CnodeMetric*>const& metrics,
        std::ostream&                   stream );

    /**
     * @fn void print_values(std::vector<CnodeMetric*> const& metrics,
     *      std::ostream& stream, std::vector<int> const& number_of_values)
     *           const
     *
     * Prints out the values that were stored for the CnodeMetric
     * instances in metrics to the std::ostream stream. The vector of integers
     * specifies how many values should be printed out for the metrics.
     *
     * @param metrics A vector of CnodeMetric instances.
     * @param stream The ostream, this function will print to.
     * @param number_of_values The vector returned by
     *        PrintableCCnode::print_headers. Its' i-th entry is the number of
     *        values that should be printed out for the i-th CnodeMetric
     *        within the metrics vector.
     */
    void
    print_values(
        std::vector<CnodeMetric*>const& metrics,
        std::ostream&                   stream,
        std::vector<int> const&         number_of_values );

    void
    print_values(
        std::vector<CnodeMetric*>const& metrics,
        std::ostream&                   stream,
        std::vector<int> const&         number_of_values,
        std::vector<double> const&      values );

    std::string
    treeindent();
    std::string
    treeindent( int level );

    static inline void
    pretty_print_region( const Region* region,
                         std::ostream& stream );

private:
    void
    print_helper(
        std::vector<CnodeMetric*>const& metrics,
        std::ostream&                   stream,
        std::vector<int> const&         number_of_values );
};
}

#endif
