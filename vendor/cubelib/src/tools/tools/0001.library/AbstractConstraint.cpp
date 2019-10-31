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



#include "config.h"
#include "AbstractConstraint.h"

#include "CubeError.h"
#include "ColorMode.h"
#include <sstream>

using namespace cube;
using namespace std;

AbstractConstraint::AbstractConstraint(
    ostream&             summary_stream,
    ostream&             details_stream,
    Constraint_Verbosity verbosity )
    : Vertex(), number_of_tests( 0 ), test_commited( true ),
      summary_stream( &summary_stream ), details_stream( &details_stream ),
      step_size( 0 ), calling_requirements( REQ_ALWAYS ), verbosity( verbosity )
{
}

AbstractConstraint::AbstractConstraint(
    AbstractConstraint*            parent,
    Constraint_CallingRequirements callreq,
    ostream&                       summary_stream,
    ostream&                       details_stream,
    Constraint_Verbosity           verbosity )
    : Vertex( parent ), number_of_tests( 0 ), test_commited( true ),
      summary_stream( &summary_stream ), details_stream( &details_stream ),
      step_size( 0 ), calling_requirements( callreq ), verbosity( verbosity )
{
}

void
AbstractConstraint::set_calling_requirements(
    Constraint_CallingRequirements callreq )
{
    calling_requirements = callreq;
}

Constraint_CallingRequirements
AbstractConstraint::get_calling_requirements()
{
    return calling_requirements;
}

void
AbstractConstraint::set_verbosity( Constraint_Verbosity verb,
                                   bool                 recursive )
{
    verbosity = verb;
    if ( recursive )
    {
        for ( unsigned int i = 0; i < num_children(); ++i )
        {
            get_child( i )->set_verbosity( verb, recursive );
        }
    }
}

Constraint_Verbosity
AbstractConstraint::get_verbosity()
{
    return verbosity;
}

void
AbstractConstraint::set_summary_stream( std::ostream& summary,
                                        bool          recursive )
{
    summary_stream = &summary;
    if ( recursive )
    {
        for ( unsigned int i = 0; i < num_children(); ++i )
        {
            get_child( i )->set_summary_stream( summary, recursive );
        }
    }
}

void
AbstractConstraint::set_details_stream( std::ostream& details,
                                        bool          recursive )
{
    details_stream = &details;
    if ( recursive )
    {
        for ( unsigned int i = 0; i < num_children(); ++i )
        {
            get_child( i )->set_details_stream( details, recursive );
        }
    }
}

AbstractConstraint*
AbstractConstraint::get_parent()
const
{
    Vertex*             vertex_parent = Vertex::get_parent();
    AbstractConstraint* _parent
        = dynamic_cast<AbstractConstraint*>( vertex_parent );
    if ( vertex_parent != NULL && _parent == NULL )
    {
        throw RuntimeError( "Could not cast Vertex to AbstractConstraint." );
    }
    return _parent;
}

AbstractConstraint*
AbstractConstraint::get_child( unsigned int id )
const
{
    Vertex*             vertex_child = Vertex::get_child( id );
    AbstractConstraint* child
        = dynamic_cast<AbstractConstraint*>( vertex_child );
    if ( vertex_child != NULL && child == NULL )
    {
        throw RuntimeError( "could not cast Vertex to AbstractConstraint." );
    }
    return child;
}

void
AbstractConstraint::set_parent( AbstractConstraint* child )
{
    Vertex::set_parent( child );
}

void
AbstractConstraint::test( string description )
{
    if ( test_commited == false )
    {
        throw RuntimeError( get_error_string() + "Outcome of test not set." );
    }
    test_commited = false;

    if ( number_of_tests == 0 )
    {
        if ( verbosity > FAILVERB_SILENT )
        {
            *details_stream << indent() << get_name() << " ... " << endl;
        }
    }

    ++number_of_tests;

    if ( step_size != 0 && number_of_tests % step_size == 0 )
    {
        *summary_stream << "\r" << indent() << get_name() << " ... " << number_of_tests;
    }

    if ( verbosity >= FAILVERB_TESTS )
    {
        *details_stream << indent() << "    "
                        << get_name() << " :: " << description  << " ... ";
    }
}

void
AbstractConstraint::ok()
{
    if ( test_commited == true )
    {
        throw RuntimeError( get_error_string() + "Outcome of test already set." );
    }
    test_commited = true;

    if ( verbosity >= FAILVERB_TESTS )
    {
        *details_stream << Color::Modifier( Color::FG_GREEN ) << "OK" << Color::Modifier( Color::FG_DEFAULT )  << endl;
    }
}

void
AbstractConstraint::skip( std::string reason )
{
    if ( test_commited == true )
    {
        throw RuntimeError( get_error_string() + "Outcome of test already set." );
    }
    test_commited = true;

    if ( verbosity >= FAILVERB_TESTS )
    {
        *details_stream <<  Color::Modifier( Color::FG_YELLOW ) << "SKIP" << Color::Modifier( Color::FG_DEFAULT )  << endl;
    }
    if ( verbosity >= FAILVERB_ERRORS )
    {
        print_intended( *details_stream, reason, indent() + "      " );
    }

    skips.insert( get_current_test_id() );
}

void
AbstractConstraint::fail( std::string reason )
{
    if ( test_commited == true )
    {
        throw RuntimeError( get_error_string() + "Outcome of test already set." );
    }
    test_commited = true;

    if ( verbosity >= FAILVERB_TESTS )
    {
        *details_stream <<  Color::Modifier( Color::FG_RED ) << "FAIL" << Color::Modifier( Color::FG_DEFAULT )  << endl;
    }
    if ( verbosity >= FAILVERB_ERRORS )
    {
        print_intended( *details_stream, reason, indent() + "      " );
    }

    failures.insert( get_current_test_id() );
}

void
AbstractConstraint::finish()
{
    int number_of_failures = failures.size();
    int number_of_skips    = skips.size();
    *summary_stream << "\r" << indent() << get_name() << " ... ";
    *summary_stream << number_of_tests - number_of_failures - number_of_skips
                    << " / " << number_of_tests <<   Color::Modifier( Color::FG_GREEN ) << " OK" << Color::Modifier( Color::FG_DEFAULT );
    if ( number_of_skips > 0 )
    {
        *summary_stream << ", "   << number_of_skips <<  Color::Modifier( Color::FG_YELLOW ) << " skipped." << Color::Modifier( Color::FG_DEFAULT );
    }
    *summary_stream << endl;

    if ( verbosity > FAILVERB_SILENT )
    {
        *details_stream << indent() <<  Color::Modifier( Color::FG_GREEN )  << "    Passed:  " <<
        number_of_tests - number_of_failures - number_of_skips
                        << " / " << number_of_tests << Color::Modifier( Color::FG_DEFAULT ) << endl;
        *details_stream << indent() <<  Color::Modifier( Color::FG_RED )  << "    Failed:  " <<
        number_of_failures << " / " << number_of_tests << Color::Modifier( Color::FG_DEFAULT ) << endl;
        *details_stream << indent() <<  Color::Modifier( Color::FG_YELLOW )  << "    Skipped: " <<
        number_of_skips << " / " << number_of_tests << Color::Modifier( Color::FG_DEFAULT ) << endl;
    }

    run_subtests();
}

void
AbstractConstraint::set_step_size( unsigned int s )
{
    step_size = s;
}

void
AbstractConstraint::run_subtests()
{
    unsigned int number_of_children = num_children();
    unsigned int number_of_failures = failures.size();
    unsigned int number_of_skips    = skips.size();
    for ( unsigned int i = 0; i < number_of_children; ++i )
    {
        AbstractConstraint* child = dynamic_cast<AbstractConstraint*>( get_child( i ) );
        switch ( child->get_calling_requirements() )
        {
            case REQ_PASS_ALL:
                if ( number_of_failures > 0 || number_of_skips > 0 )
                {
                    continue;
                }
                break;
            case REQ_PASS_NONSKIPPED:
                if ( number_of_failures > 0 )
                {
                    continue;
                }
                break;
            case REQ_PASS_SOME:
                if ( number_of_tests == number_of_failures + number_of_skips )
                {
                    continue;
                }
                break;
            case REQ_PASS_NONE:
                if ( number_of_tests != number_of_failures + number_of_skips )
                {
                    continue;
                }
                break;
            default:
                // TODO: Something to be done here?
                break;
        }
        child->check();
    }
}

unsigned int
AbstractConstraint::get_current_test_id()
{
    return number_of_tests;
}

string
AbstractConstraint::get_error_string()
{
    stringstream ss;
    ss << "Failure in test group " << get_name() << " at test "
       << get_current_test_id() << ":" << endl << "  ";
    return ss.str();
}

void
AbstractConstraint::print_intended( ostream& stream, string str,
                                    string intend )
{
    stringstream ss( str );
    string       line;
    while ( getline( ss, line ) )
    {
        stream <<  intend  << line << endl;
    }
}
