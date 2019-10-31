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



#ifndef ABSTRACTCONSTRAINT_H_GUARD_
#define ABSTRACTCONSTRAINT_H_GUARD_

/**
 * @file    AbstractConstraint.h
 * @brief   Provides an abstract base class for all kinds of constraints
 *          and some related data types.
 */

#include <iostream>
#include <ostream>
#include <set>
#include <string>

#include "CubeVertex.h"

namespace cube
{
/**
 * @enum    Constraint_CallingRequirements
 * @brief   Represents the degree of success a sub-test requires its' parent
 *          process to have.
 *
 * Possible values are:
 *  - REQ_PASS_ALL - Run the sub test only if the parent test passed all tests.
 *  - REQ_PASS_NONSKIPPED - Run the sub test only if the parent test did not
 *    fail any tests. It is still allowed to skip some tests.
 *  - REQ_PASS_SOME - Run the sub test only if at least one tests was
 *    successful.
 *  - REQ_PASS_NONE - Run the sub test only if none of the parent's test cases
 *    passed. This might be used to examine a situation more closely if things
 *    go wrong.
 *  - REQ_ALWAYS - Runs always.
 */
typedef enum Constraint_CallingRequirements
{
    REQ_PASS_ALL,
    REQ_PASS_NONSKIPPED,
    REQ_PASS_SOME,
    REQ_PASS_NONE,
    REQ_ALWAYS
} Constraint_CallingRequirements;

/**
 * @enum    Constraint_Verbosity
 * @brief   Represents the level of verbosity of a test, i.e. the amount of
 *          output that is printed to the details stream.
 *
 * Possible values are:
 *  - FAILVERB_SILENT - Do not print anything to the details stream.
 *  - FAILVERB_SUMMARY - Print a slightly extended summary to the details
 *    stream.
 *  - FAILVERB_ERRORS - Print details about failures to the details stream.
 *  - FAILVERB_TESTS - Print also details about tests that succeed.
 */
typedef enum Constraint_Verbosity
{
    FAILVERB_SILENT  = 0,
    FAILVERB_SUMMARY = 1,
    FAILVERB_ERRORS  = 2,
    FAILVERB_TESTS   = 3
} Constraint_Verbosity;

/**
 * @class   AbstractConstraint
 * @brief   On the one hand, this class provides a tree structre to organize
 *          the tests in. On the other hand it provides an interface to
 *          specify when certain tests are run and to report success or
 *          failures.
 *
 * This class also handles output and is responsible for a consistent
 * representation of test results. It allows you to redirect output to any
 * ostream and to configure the amount of output that is desired.
 */
class AbstractConstraint : public Vertex
{
public:
    /**
     * @fn AbstractConstraint(std::ostream& summary_stream,
     *       std::ostream& details_stream, Constraint_Verbosity verbosity)
     *
     * Initializes attributes according to the provided parameters. parent
     * is set to NULL, indicating there is no parent class and the calling
     * requirements are set to REQ_ALWAYS.
     */
    AbstractConstraint(
        std::ostream&        summary_stream = std::cout,
        std::ostream&        details_stream = std::cout,
        Constraint_Verbosity verbosity = FAILVERB_SILENT );

    /**
     * @fn AbstractConstraint(AbstractConstraint* parent,
     *       Constraint_CallingRequirements call_req,
     *       std::ostream& summary_stream,
     *       std::ostream& details_stream, Constraint_Verbosity verbosity)
     *
     * Initializes attributes according to the provided parameters.
     */
    AbstractConstraint(
        AbstractConstraint*            parent,
        Constraint_CallingRequirements call_req,
        std::ostream&                  summary_stream = std::cout,
        std::ostream&                  details_stream = std::cout,
        Constraint_Verbosity           verbosity = FAILVERB_SILENT );

    /**
     * @fn void set_calling_requirements(Constraint_CallingRequirements)
     *
     * Sets the calling requirements for this node to value that is passed
     * to this function.
     */
    void
    set_calling_requirements( Constraint_CallingRequirements callreq );

    /**
     * @fn Constraint_CallingRequirements get_calling_requirements()
     *
     * Returns the calling requirements for this node.
     */
    Constraint_CallingRequirements
    get_calling_requirements();

    /**
     * @fn void set_verbosity(Constraint_Verbosity verbosity,
     *            bool recursive)
     *
     * Sets the amount of desired output to a certain value.
     *
     * @param verbosity The amount of output that is desired. See
     *        Constraint_Verbosity for a description of possible values.
     * @param recursive Optional parameter that defaults to false. If set
     *        to true, the function will also call set_verbosity recursivly
     *        on all children.
     */
    void
    set_verbosity( Constraint_Verbosity verbosity,
                   bool                 recursive = false );

    /**
     * @fn Constraint_Verbosity get_verbosity()
     *
     * Returns the amount of desired output.
     */
    Constraint_Verbosity
    get_verbosity();

    /**
     * @fn void set_summary_stream(std::ostream& summary, bool recursive)
     *
     * Changes the stream, the summary will be printed to.
     *
     * @param summary
     * @param recursive Option parameter that defaults to false. If set to
     *        true, this function will also call set_summary_stream recursivly
     *        on all children.
     */
    void
    set_summary_stream( std::ostream& summary,
                        bool          recursive = false );

    /**
     * @fn void set_details_stream(std::ostream& details, bool recursive)
     *
     * Changes the stream, testing details will be printed to.
     *
     * @param details
     * @param recursive Option parameter that defaults to false. If set to
     *        true, this function will also call set_summary_stream recursivly
     *        on all children.
     */
    void
    set_details_stream( std::ostream& details,
                        bool          recursive = false );

    /**
     * @fn void check()
     *
     * Purely virtual method that must be implemented by all sub classes. It
     * is called when the actual check of the constraint should be performed.
     */
    virtual void
    check() = 0;

    /**
     * @fn std::string get_name()
     *
     * Purely virtual method that should return the constraint's name.
     */
    virtual std::string
    get_name() = 0;

    /**
     * @fn std::string get_description()
     *
     * Purely virtual method that should return a description of the test
     * containing relevant details of the implementation and of what exactly
     * is tested.
     */
    virtual std::string
    get_description() = 0;

    /**
     * @fn AbstractConstraint* get_parent() const
     *
     * Returns the parent of this instance. If this instance is a root, NULL
     * is returned.
     */
    AbstractConstraint*
    get_parent() const;

    /**
     * @fn AbstractConstraint* get_child(unsigned int id) const
     *
     * Returns the id-th child of this node. If this node has less than id
     * children a std::out_of_range exception is thrown.
     */
    AbstractConstraint*
    get_child( unsigned int id ) const;

    /**
     * @fn set_parent(AbstractConstraint* parent)
     *
     * Sets parent to a certain AbstractConstraint instance.
     *
     * @param parent Pointer to the AbstractConstraint instance that is the
     *        new parent of this node.
     */
    void
    set_parent( AbstractConstraint* parent );

protected:
    /**
     * @fn void test(std::string description)
     *
     * This function must be called before a certain test is performed.
     * Please note, that you always have to set the outcome of the test
     * using one of the methods AbstractConstraint::ok,
     * AbstractConstraint::skip or AbstractConstraint::fail before starting
     * a new test. Otherwise this functions throws a RuntimeError exception.
     *
     * @param description Description of the test.
     */
    void
    test( std::string description );

    /**
     * @fn void ok()
     *
     * Indicates success of the test started with AbstractConstraint::test.
     * If no test was started, this functions throws a RuntimeError exception.
     */
    void
    ok();

    /**
     * @fn void skip(std::string reason)
     *
     * Indicates that success or missucces for a certain test can not be
     * determined or the test is skipped for other reasons.
     *
     * @param reason This string should contain relevant information why the
     *        test was skipped. In particular
     */
    virtual void
    skip( std::string reason );
    virtual void
    fail( std::string reason );
    virtual void
    finish();
    void
    set_step_size( unsigned int step_size );
    void
    run_subtests();

private:
    unsigned int
    get_current_test_id();
    std::string
    get_error_string();
    static void
    print_intended( std::ostream& stream,
                    std::string   reason,
                    std::string   indent );

    unsigned int                   number_of_tests;
    bool                           test_commited;
    std::set<unsigned int>         failures;
    std::set<unsigned int>         skips;
    std::ostream*                  summary_stream;
    std::ostream*                  details_stream;
    unsigned int                   step_size;
    Constraint_CallingRequirements calling_requirements;
    Constraint_Verbosity           verbosity;
};
}

#endif
