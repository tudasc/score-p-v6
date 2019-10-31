/* A Bison parser, made by GNU Bison 2.7.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++

      Copyright (C) 2002-2012 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

// Take the name prefix into account.
#define yylex   remapparserlex

/* First part of user declarations.  */

/* Line 279 of lalr1.cc  */
#line 40 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.cc"


#include "ReMapParser.hh"

/* User implementation prologue.  */
/* Line 285 of lalr1.cc  */
#line 144 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"



#include "ReMapDriver.h"
#include "ReMapScanner.h"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>

using namespace std;
using namespace cube;

#include "CubeMetric.h"
#include "CubeCnode.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <string>
#include <vector>
#include "CubeServices.h"
#include "ReMapParseContext.h"
#include "CubeMetric.h"
#include "Cube.h"
#include "CubeCartesian.h"



remapparser::ReMapParser::location_type remapparserlloc;



/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex ReMapLexer.lex

// Workaround for Sun Studio C++ compilers on Solaris
#if defined( __SVR4 ) &&  defined( __SUNPRO_CC )
  #include <ieeefp.h>

  #define isinf( x )  ( fpclass( x ) == FP_NINF || fpclass( x ) == FP_PINF )
  #define isnan( x )  isnand( x )
#endif


/* Line 285 of lalr1.cc  */
#line 97 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.cc"


# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_( msgid ) dgettext( "bison-runtime", msgid )
#  endif
# endif
# ifndef YY_
#  define YY_( msgid ) msgid
# endif
#endif

#define YYRHSLOC( Rhs, K ) ( ( Rhs )[ K ] )
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT( Current, Rhs, N )                               \
    do {                                                                  \
        if ( N )                                                            \
        {                                                               \
            ( Current ).begin = YYRHSLOC( Rhs, 1 ).begin;                   \
            ( Current ).end   = YYRHSLOC( Rhs, N ).end;                     \
        }                                                               \
        else                                                              \
        {                                                               \
            ( Current ).begin = ( Current ).end = YYRHSLOC( Rhs, 0 ).end;      \
        } }                                                               \
    while ( /*CONSTCOND*/ false )
# endif


/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE( e ) ( ( void )( e ) )

/* Enable debugging if requested.  */
#if REMAPPARSERDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if ( yydebug_ ) ( *yycdebug_ )

# define YY_SYMBOL_PRINT( Title, Type, Value, Location )  \
    do {                                                    \
        if ( yydebug_ )                                         \
        {                                                   \
            *yycdebug_ << Title << ' ';                       \
            yy_symbol_print_( ( Type ), ( Value ), ( Location ) );   \
            *yycdebug_ << std::endl;                          \
        }                                                   \
    } while ( false )

# define YY_REDUCE_PRINT( Rule )          \
    do {                                    \
        if ( yydebug_ ) {                         \
            yy_reduce_print_( Rule ); }            \
    } while ( false )

# define YY_STACK_PRINT()               \
    do {                                    \
        if ( yydebug_ ) {                         \
            yystack_print_(); }                  \
    } while ( false )

#else /* !REMAPPARSERDEBUG */

# define YYCDEBUG if ( false ) std::cerr
# define YY_SYMBOL_PRINT( Title, Type, Value, Location ) YYUSE( Type )
# define YY_REDUCE_PRINT( Rule )        static_cast<void>( 0 )
# define YY_STACK_PRINT()             static_cast<void>( 0 )

#endif /* !REMAPPARSERDEBUG */

#define yyerrok         ( yyerrstatus_ = 0 )
#define yyclearin       ( yychar = yyempty_ )

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  ( !!yyerrstatus_ )


namespace remapparser
{
/* Line 353 of lalr1.cc  */
#line 192 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.cc"

/* Return YYSTR after stripping away unnecessary quotes and
   backslashes, so that it's suitable for yyerror.  The heuristic is
   that double-quoting is unnecessary unless the string contains an
   apostrophe, a comma, or backslash (other than backslash-backslash).
   YYSTR is taken from yytname.  */
std::string
ReMapParser::yytnamerr_( const char* yystr )
{
    if ( *yystr == '"' )
    {
        std::string yyr = "";
        char const* yyp = yystr;

        for (;; )
        {
            switch ( *++yyp )
            {
                case '\'':
                case ',':
                    goto do_not_strip_quotes;

                case '\\':
                    if ( *++yyp != '\\' )
                    {
                        goto do_not_strip_quotes;
                    }
                /* Fall through.  */
                default:
                    yyr += *yyp;
                    break;

                case '"':
                    return yyr;
            }
        }
do_not_strip_quotes:;
    }

    return yystr;
}


/// Build a parser object.
ReMapParser::ReMapParser ( class ReMapDriver& driver_yyarg, class ReMapParseContext& parseContext_yyarg, class ReMapScanner& ReMapLexer_yyarg, class cube::Cube& cube_yyarg )
    :
#if REMAPPARSERDEBUG
    yydebug_( false ),
    yycdebug_( &std::cerr ),
#endif
    driver( driver_yyarg ),
    parseContext( parseContext_yyarg ),
    ReMapLexer( ReMapLexer_yyarg ),
    cube( cube_yyarg )
{
}

ReMapParser::~ReMapParser ()
{
}

#if REMAPPARSERDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
   `--------------------------------*/

inline void
ReMapParser::yy_symbol_value_print_( int yytype,
                                     const semantic_type* yyvaluep, const location_type* yylocationp )
{
    YYUSE( yylocationp );
    YYUSE( yyvaluep );
    std::ostream& yyo      = debug_stream();
    std::ostream& yyoutput = yyo;
    YYUSE( yyoutput );
    switch ( yytype )
    {
        default:
            break;
    }
}


void
ReMapParser::yy_symbol_print_( int yytype,
                               const semantic_type* yyvaluep, const location_type* yylocationp )
{
    *yycdebug_ << ( yytype < yyntokens_ ? "token" : "nterm" )
               << ' ' << yytname_[ yytype ] << " ("
               << *yylocationp << ": ";
    yy_symbol_value_print_( yytype, yyvaluep, yylocationp );
    *yycdebug_ << ')';
}
#endif

void
ReMapParser::yydestruct_( const char* yymsg,
                          int yytype, semantic_type* yyvaluep, location_type* yylocationp )
{
    YYUSE( yylocationp );
    YYUSE( yymsg );
    YYUSE( yyvaluep );

    if ( yymsg )
    {
        YY_SYMBOL_PRINT( yymsg, yytype, yyvaluep, yylocationp );
    }

    switch ( yytype )
    {
        default:
            break;
    }
}

void
ReMapParser::yypop_( unsigned int n )
{
    yystate_stack_.pop( n );
    yysemantic_stack_.pop( n );
    yylocation_stack_.pop( n );
}

#if REMAPPARSERDEBUG
std::ostream&
ReMapParser::debug_stream() const
{
    return *yycdebug_;
}

void
ReMapParser::set_debug_stream( std::ostream& o )
{
    yycdebug_ = &o;
}


ReMapParser::debug_level_type
ReMapParser::debug_level() const
{
    return yydebug_;
}

void
ReMapParser::set_debug_level( debug_level_type l )
{
    yydebug_ = l;
}
#endif

inline bool
ReMapParser::yy_pact_value_is_default_( int yyvalue )
{
    return yyvalue == yypact_ninf_;
}

inline bool
ReMapParser::yy_table_value_is_error_( int yyvalue )
{
    return yyvalue == yytable_ninf_;
}

int
ReMapParser::parse()
{
    /// Lookahead and lookahead in internal form.
    int yychar  = yyempty_;
    int yytoken = 0;

    // State.
    int yyn;
    int yylen   = 0;
    int yystate = 0;

    // Error handling.
    int yynerrs_     = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    static semantic_type yyval_default;
    semantic_type        yylval = yyval_default;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[ 3 ];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
    {
        YYCDEBUG << "Starting parse" << std::endl;


/* User initialization code.  */
/* Line 545 of lalr1.cc  */
#line 66 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
        {
            // initialize the initial location object
            yylloc.begin.filename = yylloc.end.filename = &driver.streamname;
        }
/* Line 545 of lalr1.cc  */
#line 396 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.cc"

        /* Initialize the stacks.  The initial state will be pushed in
           yynewstate, since the latter expects the semantical and the
           location values to have been already stored, initialize these
           stacks with a primary value.  */
        yystate_stack_    = state_stack_type( 0 );
        yysemantic_stack_ = semantic_stack_type( 0 );
        yylocation_stack_ = location_stack_type( 0 );
        yysemantic_stack_.push( yylval );
        yylocation_stack_.push( yylloc );

        /* New state.  */
yynewstate:
        yystate_stack_.push( yystate );
        YYCDEBUG << "Entering state " << yystate << std::endl;

        /* Accept?  */
        if ( yystate == yyfinal_ )
        {
            goto yyacceptlab;
        }

        goto yybackup;

        /* Backup.  */
yybackup:

        /* Try to take a decision without lookahead.  */
        yyn = yypact_[ yystate ];
        if ( yy_pact_value_is_default_( yyn ) )
        {
            goto yydefault;
        }

        /* Read a lookahead token.  */
        if ( yychar == yyempty_ )
        {
            YYCDEBUG << "Reading a token: ";
            yychar = yylex( &yylval, &yylloc );
        }

        /* Convert token to internal form.  */
        if ( yychar <= yyeof_ )
        {
            yychar = yytoken = yyeof_;
            YYCDEBUG << "Now at end of input." << std::endl;
        }
        else
        {
            yytoken = yytranslate_( yychar );
            YY_SYMBOL_PRINT( "Next token is", yytoken, &yylval, &yylloc );
        }

        /* If the proper action on seeing token YYTOKEN is to reduce or to
           detect an error, take that action.  */
        yyn += yytoken;
        if ( yyn < 0 || yylast_ < yyn || yycheck_[ yyn ] != yytoken )
        {
            goto yydefault;
        }

        /* Reduce or error.  */
        yyn = yytable_[ yyn ];
        if ( yyn <= 0 )
        {
            if ( yy_table_value_is_error_( yyn ) )
            {
                goto yyerrlab;
            }
            yyn = -yyn;
            goto yyreduce;
        }

        /* Shift the lookahead token.  */
        YY_SYMBOL_PRINT( "Shifting", yytoken, &yylval, &yylloc );

        /* Discard the token being shifted.  */
        yychar = yyempty_;

        yysemantic_stack_.push( yylval );
        yylocation_stack_.push( yylloc );

        /* Count tokens shifted since error; after three, turn off error
           status.  */
        if ( yyerrstatus_ )
        {
            --yyerrstatus_;
        }

        yystate = yyn;
        goto yynewstate;

        /*-----------------------------------------------------------.
        | yydefault -- do the default action for the current state.  |
           `-----------------------------------------------------------*/
yydefault:
        yyn = yydefact_[ yystate ];
        if ( yyn == 0 )
        {
            goto yyerrlab;
        }
        goto yyreduce;

        /*-----------------------------.
        | yyreduce -- Do a reduction.  |
           `-----------------------------*/
yyreduce:
        yylen = yyr2_[ yyn ];
        /* If YYLEN is nonzero, implement the default value of the action:
           `$$ = $1'.  Otherwise, use the top of the stack.

           Otherwise, the following line sets YYVAL to garbage.
           This behavior is undocumented and Bison
           users should not rely upon it.  */
        if ( yylen )
        {
            yyval = yysemantic_stack_[ yylen - 1 ];
        }
        else
        {
            yyval = yysemantic_stack_[ 0 ];
        }

        // Compute the default @$.
        {
            slice<location_type, location_stack_type> slice( yylocation_stack_, yylen );
            YYLLOC_DEFAULT( yyloc, slice, yylen );
        }

        // Perform the reduction.
        YY_REDUCE_PRINT( yyn );
        switch ( yyn )
        {
            case 2:
/* Line 670 of lalr1.cc  */
#line 201 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.metricTypeSeen )
                    {
                        error( remapparserlloc, "Multiple metric type attributes defines!" );
                    }
                    else
                    {
                        parseContext.metricTypeSeen = true;
                    }
                    parseContext.metricType = parseContext.str.str();
                }
                break;

            case 3:
/* Line 670 of lalr1.cc  */
#line 209 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.metricVizTypeSeen )
                    {
                        error( remapparserlloc, "Multiple metric visibilty type attributes defines!" );
                    }
                    else
                    {
                        parseContext.metricVizTypeSeen = true;
                    }
                    parseContext.metricVizType = parseContext.str.str();
                }
                break;

            case 4:
/* Line 670 of lalr1.cc  */
#line 217 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.metricConvertibleSeen )
                    {
                        error( remapparserlloc, "Multiple metric convertible type attributes defines!" );
                    }
                    else
                    {
                        parseContext.metricConvertibleSeen = true;
                    }
                    parseContext.metricConvertible = true;
                }
                break;

            case 5:
/* Line 670 of lalr1.cc  */
#line 223 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.metricConvertibleSeen )
                    {
                        error( remapparserlloc, "Multiple metric convertible type attributes defines!" );
                    }
                    else
                    {
                        parseContext.metricConvertibleSeen = true;
                    }
                    parseContext.metricConvertible = false;
                }
                break;

            case 6:
/* Line 670 of lalr1.cc  */
#line 233 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.metricCacheableSeen )
                    {
                        error( remapparserlloc, "Multiple metric cacheable type attributes defines!" );
                    }
                    else
                    {
                        parseContext.metricCacheableSeen = true;
                    }
                    parseContext.metricCacheable = true;
                }
                break;

            case 7:
/* Line 670 of lalr1.cc  */
#line 239 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.metricCacheableSeen )
                    {
                        error( remapparserlloc, "Multiple metric cacheable type attributes defines!" );
                    }
                    else
                    {
                        parseContext.metricCacheableSeen = true;
                    }
                    parseContext.metricCacheable = false;
                }
                break;

            case 9:
/* Line 670 of lalr1.cc  */
#line 250 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.metricsTitleSeen )
                    {
                        error( remapparserlloc, "Multiple metrics titles defined!" );
                    }
                    else
                    {
                        parseContext.metricsTitleSeen = true;
                    }
                    parseContext.metricsTitle = parseContext.str.str();
                }
                break;

            case 11:
/* Line 670 of lalr1.cc  */
#line 261 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.cubeplTypeSeen )
                    {
                        error( remapparserlloc, "Multiple cubepl type attributes defines!" );
                    }
                    else
                    {
                        parseContext.cubeplTypeSeen = true;
                    }
                    parseContext.rowwise = false;
                }
                break;

            case 15:
/* Line 670 of lalr1.cc  */
#line 280 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.expressionAggrPlusSeen )
                    {
                        error( remapparserlloc, "Multiple cubepl plus-aggregation attributes defines!" );
                    }
                    else
                    {
                        parseContext.expressionAggrPlusSeen = true;
                    }
                    parseContext.cubeplAggrType = ReMapParseContext::CUBEPL_AGGR_PLUS;
                }
                break;

            case 16:
/* Line 670 of lalr1.cc  */
#line 289 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.expressionAggrMinusSeen )
                    {
                        error( remapparserlloc, "Multiple cubepl minus-aggregation attributes defines!" );
                    }
                    else
                    {
                        parseContext.expressionAggrMinusSeen = true;
                    }
                    parseContext.cubeplAggrType = ReMapParseContext::CUBEPL_AGGR_MINUS;
                }
                break;

            case 17:
/* Line 670 of lalr1.cc  */
#line 299 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.expressionAggrAggrSeen )
                    {
                        error( remapparserlloc, "Multiple cubepl aggr-aggregation attributes defines!" );
                    }
                    else
                    {
                        parseContext.expressionAggrAggrSeen = true;
                    }
                    parseContext.cubeplAggrType = ReMapParseContext::CUBEPL_AGGR_AGGR;
                }
                break;

            case 18:
/* Line 670 of lalr1.cc  */
#line 312 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.murlSeen )
                    {
                        error( remapparserlloc, "Multiple murl tags defined!" );
                    }
                    else
                    {
                        parseContext.murlSeen = true;
                    }
                    parseContext.murl = parseContext.str.str();
                }
                break;

            case 19:
/* Line 670 of lalr1.cc  */
#line 321 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.dispnameSeen )
                    {
                        error( remapparserlloc, "Multiple disp_name tags defined!" );
                    }
                    else
                    {
                        parseContext.dispnameSeen = true;
                    }
                    parseContext.disp_name = parseContext.str.str();
                }
                break;

            case 20:
/* Line 670 of lalr1.cc  */
#line 328 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.uniqnameSeen )
                    {
                        error( remapparserlloc, "Multiple uniq_name tags defined!" );
                    }
                    else
                    {
                        parseContext.uniqnameSeen = true;
                    }
                    parseContext.uniq_name = parseContext.str.str();
                }
                break;

            case 21:
/* Line 670 of lalr1.cc  */
#line 334 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.dtypeSeen )
                    {
                        error( remapparserlloc, "Multiple dtype tags defined!" );
                    }
                    else
                    {
                        parseContext.dtypeSeen = true;
                    }
                    parseContext.dtype = parseContext.str.str();
                }
                break;

            case 22:
/* Line 670 of lalr1.cc  */
#line 341 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.uomSeen )
                    {
                        error( remapparserlloc, "Multiple uom tags defined!" );
                    }
                    else
                    {
                        parseContext.uomSeen = true;
                    }
                    parseContext.uom = parseContext.str.str();
                }
                break;

            case 23:
/* Line 670 of lalr1.cc  */
#line 348 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.valSeen )
                    {
                        error( remapparserlloc, "Multiple val tags defined!" );
                    }
                    else
                    {
                        parseContext.valSeen = true;
                    }
                    parseContext.val = parseContext.str.str();
                }
                break;

            case 24:
/* Line 670 of lalr1.cc  */
#line 355 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.urlSeen )
                    {
                        error( remapparserlloc, "Multiple url tags defined!" );
                    }
                    else
                    {
                        parseContext.urlSeen = true;
                    }
                    parseContext.url = parseContext.str.str();
                }
                break;

            case 25:
/* Line 670 of lalr1.cc  */
#line 365 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.expressionSeen )
                    {
                        error( remapparserlloc, "Multiple expressions defined!" );
                    }
                    else
                    {
                        parseContext.expressionSeen = true;
                    }
                    parseContext.expression = services::escapeFromXML( parseContext.str.str() );
                }
                break;

            case 26:
/* Line 670 of lalr1.cc  */
#line 373 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.expressionInitSeen )
                    {
                        error( remapparserlloc, "Multiple expression initializations defined!" );
                    }
                    else
                    {
                        parseContext.expressionInitSeen = true;
                    }
                    parseContext.expressionInit = services::escapeFromXML( parseContext.str.str() );
                }
                break;

            case 27:
/* Line 670 of lalr1.cc  */
#line 381 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.cubeplAggrType == ReMapParseContext::CUBEPL_AGGR_PLUS )
                    {
                        parseContext.expressionAggrPlus = services::escapeFromXML( parseContext.str.str() );
                    }
                    else
                    if ( parseContext.cubeplAggrType == ReMapParseContext::CUBEPL_AGGR_MINUS )
                    {
                        parseContext.expressionAggrMinus = services::escapeFromXML( parseContext.str.str() );
                    }
                    else
                    if ( parseContext.cubeplAggrType == ReMapParseContext::CUBEPL_AGGR_AGGR )
                    {
                        parseContext.expressionAggrAggr = services::escapeFromXML( parseContext.str.str() );
                    }
                }
                break;

            case 28:
/* Line 670 of lalr1.cc  */
#line 392 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.descrSeen )
                    {
                        error( remapparserlloc, "Multiple descr tags defined!" );
                    }
                    else
                    {
                        parseContext.descrSeen = true;
                    }
                    parseContext.descr = parseContext.str.str();
                }
                break;

            case 37:
/* Line 670 of lalr1.cc  */
#line 428 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                { parseContext.murlSeen = false;
                  cube.def_mirror( services::escapeFromXML( parseContext.murl ) );
                }
                break;

            case 38:
/* Line 670 of lalr1.cc  */
#line 429 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                { parseContext.murlSeen = false;
                  cube.def_mirror( services::escapeFromXML( parseContext.murl ) );
                }
                break;

            case 39:
/* Line 670 of lalr1.cc  */
#line 436 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.metricsTitle != "" )
                    {
                        cube.set_metrics_title( services::escapeFromXML( parseContext.metricsTitle ) );
                    }
                }
                break;

            case 43:
/* Line 670 of lalr1.cc  */
#line 452 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    //check for attributes
                    parseContext.idSeen = false;
                    //check for tags
                    if ( parseContext.metricTypeSeen )
                    {
                        parseContext.metricTypeSeen = false;
                    }
                    else
                    {
                        parseContext.metricType = "";
                    }
                    if ( parseContext.metricVizTypeSeen )
                    {
                        parseContext.metricVizTypeSeen = false;
                    }
                    else
                    {
                        parseContext.metricVizType = "";
                    }
                    if ( parseContext.dispnameSeen )
                    {
                        parseContext.dispnameSeen = false;
                    }
                    else
                    {
                        parseContext.disp_name = "";
                    }
                    if ( parseContext.uniqnameSeen )
                    {
                        parseContext.uniqnameSeen = false;
                    }
                    else
                    {
                        parseContext.uniq_name = "";
                    }
                    if ( parseContext.dtypeSeen )
                    {
                        parseContext.dtypeSeen = false;
                    }
                    else
                    {
                        parseContext.dtype = "";
                    }
                    if ( parseContext.uomSeen )
                    {
                        parseContext.uomSeen = false;
                    }
                    else
                    {
                        parseContext.uom = "";
                    }
                    if ( parseContext.valSeen )
                    {
                        parseContext.valSeen = false;
                    }
                    else
                    {
                        parseContext.val = "";
                    }
                    if ( parseContext.urlSeen )
                    {
                        parseContext.urlSeen = false;
                    }
                    else
                    {
                        parseContext.url = "";
                    }
                    if ( parseContext.descrSeen )
                    {
                        parseContext.descrSeen = false;
                    }
                    else
                    {
                        parseContext.descr = "";
                    }
                    if ( parseContext.expressionSeen )
                    {
                        parseContext.expressionSeen = false;
                    }
                    else
                    {
                        parseContext.expression = "";
                    }
                    if ( parseContext.expressionInitSeen )
                    {
                        parseContext.expressionInitSeen = false;
                    }
                    else
                    {
                        parseContext.expressionInit = "";
                    }
                    if ( parseContext.expressionAggrPlusSeen )
                    {
                        parseContext.expressionAggrPlusSeen = false;
                    }
                    else
                    {
                        parseContext.expressionAggrPlus = "";
                    }
                    if ( parseContext.expressionAggrMinusSeen )
                    {
                        parseContext.expressionAggrMinusSeen = false;
                    }
                    else
                    {
                        parseContext.expressionAggrMinus = "";
                    }
                    if ( parseContext.expressionAggrAggrSeen )
                    {
                        parseContext.expressionAggrAggrSeen = false;
                    }
                    else
                    {
                        parseContext.expressionAggrAggr = "";
                    }
                    if ( parseContext.metricConvertibleSeen )
                    {
                        parseContext.metricConvertibleSeen = false;
                    }
                    else
                    {
                        parseContext.metricConvertible = true;
                    }
                    if ( parseContext.metricCacheableSeen )
                    {
                        parseContext.metricCacheableSeen = false;
                    }
                    else
                    {
                        parseContext.metricCacheable = true;
                    }
                    if ( parseContext.cubeplTypeSeen )
                    {
                        parseContext.cubeplTypeSeen = false;
                    }
                    else
                    {
                        parseContext.rowwise = true;
                    }
/*      while ((int)parseContext.metricVec.size()<=parseContext.id)  */
/*              parseContext.metricVec.push_back(NULL); */
/*      if (parseContext.metricVec[parseContext.id]!=NULL) */
/*        error(remapparserlloc,"Re-declared metric!"); */
                    parseContext.currentMetric =
                        cube.def_met(
                            services::escapeFromXML( parseContext.disp_name ),
                            services::escapeFromXML( parseContext.uniq_name ),
                            services::escapeFromXML( parseContext.dtype ),
                            services::escapeFromXML( parseContext.uom ),
                            services::escapeFromXML( parseContext.val ),
                            services::escapeFromXML( parseContext.url ),
                            services::escapeFromXML( parseContext.descr ),
                            parseContext.currentMetric,
                            cube::Metric::get_type_of_metric( parseContext.metricType ),
                            services::escapeFromXML( parseContext.expression ),
                            services::escapeFromXML( parseContext.expressionInit ),
                            services::escapeFromXML( parseContext.expressionAggrPlus ),
                            services::escapeFromXML( parseContext.expressionAggrMinus ),
                            services::escapeFromXML( parseContext.expressionAggrAggr ),
                            parseContext.rowwise,
                            cube::Metric::get_viz_type_of_metric( parseContext.metricVizType ) );

                    parseContext.currentMetric->setConvertible( parseContext.metricConvertible );
                    parseContext.currentMetric->setCacheable( parseContext.metricCacheable );

                    parseContext.metricVec.push_back( parseContext.currentMetric );
                }
                break;

            case 64:
/* Line 670 of lalr1.cc  */
#line 554 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
                {
                    if ( parseContext.currentMetric == NULL )
                    {
                        error( remapparserlloc, "Metric definitions are not correctly nested!" );
                    }
                    parseContext.currentMetric =
                        ( parseContext.currentMetric )->get_parent();
                }
                break;


/* Line 670 of lalr1.cc  */
#line 855 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.cc"
            default:
                break;
        }

        /* User semantic actions sometimes alter yychar, and that requires
           that yytoken be updated with the new translation.  We take the
           approach of translating immediately before every use of yytoken.
           One alternative is translating here after every semantic action,
           but that translation would be missed if the semantic action
           invokes YYABORT, YYACCEPT, or YYERROR immediately after altering
           yychar.  In the case of YYABORT or YYACCEPT, an incorrect
           destructor might then be invoked immediately.  In the case of
           YYERROR, subsequent parser actions might lead to an incorrect
           destructor call or verbose syntax error message before the
           lookahead is translated.  */
        YY_SYMBOL_PRINT( "-> $$ =", yyr1_[ yyn ], &yyval, &yyloc );

        yypop_( yylen );
        yylen = 0;
        YY_STACK_PRINT();

        yysemantic_stack_.push( yyval );
        yylocation_stack_.push( yyloc );

        /* Shift the result of the reduction.  */
        yyn     = yyr1_[ yyn ];
        yystate = yypgoto_[ yyn - yyntokens_ ] + yystate_stack_[ 0 ];
        if ( 0 <= yystate && yystate <= yylast_
             && yycheck_[ yystate ] == yystate_stack_[ 0 ] )
        {
            yystate = yytable_[ yystate ];
        }
        else
        {
            yystate = yydefgoto_[ yyn - yyntokens_ ];
        }
        goto yynewstate;

        /*------------------------------------.
        | yyerrlab -- here on detecting error |
           `------------------------------------*/
yyerrlab:
        /* Make sure we have latest lookahead translation.  See comments at
           user semantic actions for why this is necessary.  */
        yytoken = yytranslate_( yychar );

        /* If not already recovering from an error, report this error.  */
        if ( !yyerrstatus_ )
        {
            ++yynerrs_;
            if ( yychar == yyempty_ )
            {
                yytoken = yyempty_;
            }
            error( yylloc, yysyntax_error_( yystate, yytoken ) );
        }

        yyerror_range[ 1 ] = yylloc;
        if ( yyerrstatus_ == 3 )
        {
            /* If just tried and failed to reuse lookahead token after an
               error, discard it.  */
            if ( yychar <= yyeof_ )
            {
                /* Return failure if at end of input.  */
                if ( yychar == yyeof_ )
                {
                    YYABORT;
                }
            }
            else
            {
                yydestruct_( "Error: discarding", yytoken, &yylval, &yylloc );
                yychar = yyempty_;
            }
        }

        /* Else will try to reuse lookahead token after shifting the error
           token.  */
        goto yyerrlab1;


        /*---------------------------------------------------.
        | yyerrorlab -- error raised explicitly by YYERROR.  |
           `---------------------------------------------------*/
yyerrorlab:

        /* Pacify compilers like GCC when the user code never invokes
           YYERROR and the label yyerrorlab therefore never appears in user
           code.  */
        if ( false )
        {
            goto yyerrorlab;
        }

        yyerror_range[ 1 ] = yylocation_stack_[ yylen - 1 ];
        /* Do not reclaim the symbols of the rule which action triggered
           this YYERROR.  */
        yypop_( yylen );
        yylen   = 0;
        yystate = yystate_stack_[ 0 ];
        goto yyerrlab1;

        /*-------------------------------------------------------------.
        | yyerrlab1 -- common code for both syntax error and YYERROR.  |
           `-------------------------------------------------------------*/
yyerrlab1:
        yyerrstatus_ = 3; /* Each real token shifted decrements this.  */

        for (;; )
        {
            yyn = yypact_[ yystate ];
            if ( !yy_pact_value_is_default_( yyn ) )
            {
                yyn += yyterror_;
                if ( 0 <= yyn && yyn <= yylast_ && yycheck_[ yyn ] == yyterror_ )
                {
                    yyn = yytable_[ yyn ];
                    if ( 0 < yyn )
                    {
                        break;
                    }
                }
            }

            /* Pop the current state because it cannot handle the error token.  */
            if ( yystate_stack_.height() == 1 )
            {
                YYABORT;
            }

            yyerror_range[ 1 ] = yylocation_stack_[ 0 ];
            yydestruct_( "Error: popping",
                         yystos_[ yystate ],
                         &yysemantic_stack_[ 0 ], &yylocation_stack_[ 0 ] );
            yypop_();
            yystate = yystate_stack_[ 0 ];
            YY_STACK_PRINT();
        }

        yyerror_range[ 2 ] = yylloc;
        // Using YYLLOC is tempting, but would change the location of
        // the lookahead.  YYLOC is available though.
        YYLLOC_DEFAULT( yyloc, yyerror_range, 2 );
        yysemantic_stack_.push( yylval );
        yylocation_stack_.push( yyloc );

        /* Shift the error token.  */
        YY_SYMBOL_PRINT( "Shifting", yystos_[ yyn ],
                         &yysemantic_stack_[ 0 ], &yylocation_stack_[ 0 ] );

        yystate = yyn;
        goto yynewstate;

        /* Accept.  */
yyacceptlab:
        yyresult = 0;
        goto yyreturn;

        /* Abort.  */
yyabortlab:
        yyresult = 1;
        goto yyreturn;

yyreturn:
        if ( yychar != yyempty_ )
        {
            /* Make sure we have latest lookahead translation.  See comments
               at user semantic actions for why this is necessary.  */
            yytoken = yytranslate_( yychar );
            yydestruct_( "Cleanup: discarding lookahead", yytoken, &yylval,
                         &yylloc );
        }

        /* Do not reclaim the symbols of the rule which action triggered
           this YYABORT or YYACCEPT.  */
        yypop_( yylen );
        while ( 1 < yystate_stack_.height() )
        {
            yydestruct_( "Cleanup: popping",
                         yystos_[ yystate_stack_[ 0 ] ],
                         &yysemantic_stack_[ 0 ],
                         &yylocation_stack_[ 0 ] );
            yypop_();
        }

        return yyresult;
    }
    catch ( ... )
    {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if ( yychar != yyempty_ )
        {
            /* Make sure we have latest lookahead translation.  See
               comments at user semantic actions for why this is
               necessary.  */
            yytoken = yytranslate_( yychar );
            yydestruct_( YY_NULL, yytoken, &yylval, &yylloc );
        }

        while ( 1 < yystate_stack_.height() )
        {
            yydestruct_( YY_NULL,
                         yystos_[ yystate_stack_[ 0 ] ],
                         &yysemantic_stack_[ 0 ],
                         &yylocation_stack_[ 0 ] );
            yypop_();
        }
        throw;
    }
}

// Generate an error message.
std::string
ReMapParser::yysyntax_error_( int yystate, int yytoken )
{
    std::string yyres;
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const* yyarg[ YYERROR_VERBOSE_ARGS_MAXIMUM ];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yytoken) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yychar.
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
     */
    if ( yytoken != yyempty_ )
    {
        yyarg[ yycount++ ] = yytname_[ yytoken ];
        int yyn = yypact_[ yystate ];
        if ( !yy_pact_value_is_default_( yyn ) )
        {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            /* Stay within bounds of both yycheck and yytname.  */
            int yychecklim = yylast_ - yyn + 1;
            int yyxend     = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for ( int yyx = yyxbegin; yyx < yyxend; ++yyx )
            {
                if ( yycheck_[ yyx + yyn ] == yyx && yyx != yyterror_
                     && !yy_table_value_is_error_( yytable_[ yyx + yyn ] ) )
                {
                    if ( yycount == YYERROR_VERBOSE_ARGS_MAXIMUM )
                    {
                        yycount = 1;
                        break;
                    }
                    else
                    {
                        yyarg[ yycount++ ] = yytname_[ yyx ];
                    }
                }
            }
        }
    }

    char const* yyformat = YY_NULL;
    switch ( yycount )
    {
#define YYCASE_( N, S )                         \
    case N:                               \
        yyformat = S;                       \
        break
        YYCASE_( 0, YY_( "syntax error" ) );
        YYCASE_( 1, YY_( "syntax error, unexpected %s" ) );
        YYCASE_( 2, YY_( "syntax error, unexpected %s, expecting %s" ) );
        YYCASE_( 3, YY_( "syntax error, unexpected %s, expecting %s or %s" ) );
        YYCASE_( 4, YY_( "syntax error, unexpected %s, expecting %s or %s or %s" ) );
        YYCASE_( 5, YY_( "syntax error, unexpected %s, expecting %s or %s or %s or %s" ) );
#undef YYCASE_
    }

    // Argument number.
    size_t yyi = 0;
    for ( char const* yyp = yyformat; *yyp; ++yyp )
    {
        if ( yyp[ 0 ] == '%' && yyp[ 1 ] == 's' && yyi < yycount )
        {
            yyres += yytnamerr_( yyarg[ yyi++ ] );
            ++yyp;
        }
        else
        {
            yyres += *yyp;
        }
    }
    return yyres;
}


/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
const signed char ReMapParser::yypact_ninf_ = -44;
const signed char
ReMapParser::yypact_[] =
{
    -19, -43,   -37,   9,     -9,    -44,   8,     7,     -25,   -8,
    -44, -44,   -44,   -44,   22,    -10,   -44,   -7,    -25,   -44,
    -26, -6,    -44,   -44,   -44,   -44,   32,    33,    26,    28,
    -44, -44,   -44,   -44,   29,    -26,   -44,   -44,   -44,   -44,
    -44, -44,   -44,   -44,   -44,   -44,   -14,   -44,   -12,   24,
    -11, 20,    21,    17,    16,    18,    14,    13,    -44,   -44,
    -44, -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,   -14,
    -44, 47,    41,    -44,   19,    42,    -44,   -44,   -44,   -44,
    -44, -44,   -44,   -44,   -44,   -44,   -44,   -44,   38,    -44,
    -44, -44,   35,    -44,   -44
};

/* YYDEFACT[S] -- default reduction number in state S.  Performed when
   YYTABLE doesn't specify something else to do.  Zero means the
   default is an error.  */
const unsigned char
ReMapParser::yydefact_[] =
{
    0,  8,     32,    0,     0,     30,    0,     0,     35,    0,
    33, 1,     29,    9,     0,     0,     37,    0,     36,    31,
    44, 0,     40,    18,    34,    38,    0,     0,     0,     0,
    46, 47,    48,    49,    0,     44,    64,    39,    41,    42,
    2,  3,     5,     4,     7,     6,     50,    45,    10,    0,
    0,  0,     0,     0,     0,     0,     0,     0,     54,    55,
    56, 57,    58,    59,    61,    62,    63,    60,    43,    51,
    52, 0,     0,     26,    0,     0,     12,    13,    14,    19,
    20, 21,    22,    23,    24,    28,    53,    11,    0,     15,
    16, 17,    0,     25,    27
};

/* YYPGOTO[NTERM-NUM].  */
const signed char
ReMapParser::yypgoto_[] =
{
    -44, -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,
    -44, 37,    -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,
    -44, -44,   -44,   -44,   -44,   -44,   -44,   -44,   52,    -44,
    36,  23,    -44,   -44,   -44,   -5,    -44
};

/* YYDEFGOTO[NTERM-NUM].  */
const signed char
ReMapParser::yydefgoto_[] =
{
    -1, 30,    31,    32,    33,    7,     72,    75,    76,    77,
    78, 16,    58,    59,    60,    61,    62,    63,    64,    65,
    66, 67,    3,     4,     9,     10,    17,    18,    5,     21,
    22, 34,    35,    68,    69,    70,    39
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF_, syntax error.  */
const signed char ReMapParser::yytable_ninf_ = -1;
const unsigned char
ReMapParser::yytable_[] =
{
    48, 1,     49,    6,     50,    8,     20,    36,    51,    11,
    52, 1,     53,    13,    54,    37,    55,    14,    56,    15,
    57, 2,     26,    27,    28,    29,    89,    90,    91,    42,
    43, 44,    45,    19,    20,    23,    24,    40,    41,    46,
    71, 73,    74,    79,    81,    82,    80,    84,    85,    83,
    87, 88,    92,    93,    94,    25,    12,    38,    47,    0,
    0,  0,     0,     0,     86
};

/* YYCHECK.  */
const signed char
ReMapParser::yycheck_[] =
{
    14, 20,    16,    46,    18,    42,    12,    13,    22,    0,
    24, 20,    26,    5,     28,    21,    30,    10,    32,    44,
    34, 40,    48,    49,    50,    51,    7,     8,     9,     3,
    4,  3,     4,     41,    12,    45,    43,    5,     5,     10,
    52, 17,    53,    23,    27,    29,    25,    33,    35,    31,
    3,  10,    10,    15,    19,    18,    4,     21,    35,    -1,
    -1, -1,    -1,    -1,    69
};

/* STOS_[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
const unsigned char
ReMapParser::yystos_[] =
{
    0,  20,    40,    76,    77,    82,    46,    59,    42,    78,
    79, 0,     82,    5,     10,    44,    65,    80,    81,    41,
    12, 83,    84,    45,    43,    65,    48,    49,    50,    51,
    55, 56,    57,    58,    85,    86,    13,    21,    84,    90,
    5,  5,     3,     4,     3,     4,     10,    85,    14,    16,
    18, 22,    24,    26,    28,    30,    32,    34,    66,    67,
    68, 69,    70,    71,    72,    73,    74,    75,    87,    88,
    89, 52,    60,    17,    53,    61,    62,    63,    64,    23,
    25, 27,    29,    31,    33,    35,    89,    3,     10,    7,
    8,  9,     10,    15,    19
};

#if REMAPPARSERDEBUG
/* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
   to YYLEX-NUM.  */
const unsigned short int
ReMapParser::yytoken_number_[] =
{
    0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
    265, 266,   267,   268,   269,   270,   271,   272,   273,   274,
    275, 276,   277,   278,   279,   280,   281,   282,   283,   284,
    285, 286,   287,   288,   289,   290,   291,   292,   293,   294,
    295, 296,   297,   298,   299,   300,   301,   302,   303,   304,
    305, 306,   307,   308
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
const unsigned char
ReMapParser::yyr1_[] =
{
    0,  54,    55,    56,    57,    57,    58,    58,    59,    59,
    60, 60,    61,    61,    61,    62,    63,    64,    65,    66,
    67, 68,    69,    70,    71,    72,    73,    74,    75,    76,
    76, 77,    78,    78,    79,    80,    80,    81,    81,    82,
    83, 83,    83,    84,    85,    85,    86,    86,    86,    86,
    87, 87,    88,    88,    89,    89,    89,    89,    89,    89,
    89, 89,    89,    89,    90
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
const unsigned char
ReMapParser::yyr2_[] =
{
    0, 2,     2,     2,     2,     2,     2,     2,     0,     2,
    0, 2,     1,     1,     1,     2,     2,     2,     2,     2,
    2, 2,     2,     2,     2,     4,     2,     4,     2,     2,
    1, 3,     0,     1,     3,     0,     1,     1,     2,     5,
    1, 2,     2,     4,     0,     2,     1,     1,     1,     1,
    0, 1,     1,     2,     1,     1,     1,     1,     1,     1,
    1, 1,     1,     1,     1
};


/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
const char*
const ReMapParser::yytname_[] =
{
    "\"end of file\"",                "error",                             "$undefined",                "\"false\"",      "\"true\"",
    "\"attribute value\"",            "\"error\"",                         "\"plus\"",                  "\"minus\"",      "\"aggr\"",
    "\">\"",                          "\"/>\"",                            "\"<metric\"",               "\"</metric>\"",  "\"<cubepl\"",
    "\"</cubepl>\"",                  "\"<cubeplinit>\"",                  "\"</cubeplinit>\"",
    "\"<cubeplaggr\"",                "\"</cubeplaggr>\"",                 "\"<metrics\"",              "\"</metrics>\"",
    "\"<disp_name>\"",                "\"</disp_name>\"",                  "\"<uniq_name>\"",
    "\"</uniq_name>\"",               "\"<dtype>\"",                       "\"</dtype>\"",              "\"<uom>\"",
    "\"</uom>\"",                     "\"<val>\"",                         "\"</val>\"",                "\"<url>\"",      "\"</url>\"",
    "\"<descr>\"",                    "\"</descr>\"",                      "\"<program\"",              "\"</program>\"",
    "\"<name>\"",                     "\"</name>\"",                       "\"<doc>\"",                 "\"</doc>\"",     "\"<mirrors>\"",
    "\"</mirrors>\"",                 "\"<murl>\"",                        "\"</murl>\"",
    "\"attribute name title\"",       "\"attribute name metricId\"",
    "\"attribute name type\"",        "\"attribute name viztype\"",
    "\"attribute name convertible\"", "\"attribute name cacheable\"",
    "\"attribute name rowwise\"",     "\"attribute name cubeplaggrtype\"",
    "$accept",                        "metric_type_attr",                  "metric_viz_type_attr",
    "metric_convertible_attr",        "metric_cacheable_attr",             "metrics_title_attr",
    "expression_attr",                "expression_aggr_attr",              "expression_aggr_attr_plus",
    "expression_aggr_attr_minus",     "expression_aggr_attr_aggr",         "murl_tag",
    "disp_name_tag",                  "uniq_name_tag",                     "dtype_tag",                 "uom_tag",        "val_tag",
    "url_tag",                        "expression_tag",                    "expression_init_tag",
    "expression_aggr_tag",            "descr_tag",                         "document",                  "doc_tag",
    "mirrors_tag_opt",                "mirrors_tag",                       "murl_tags_opt",             "murl_tags",
    "metrics_tag",                    "metric_tag",                        "metric_begin",              "metric_attrs",
    "metric_attr",                    "tags_of_metric_opt",                "tags_of_metric",            "tag_of_metric",
    "metric_end",                     YY_NULL
};

#if REMAPPARSERDEBUG
/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
const ReMapParser::rhs_number_type
ReMapParser::yyrhs_[] =
{
    76, 0,     -1,    48,    5,     -1,    49,    5,     -1,    50,
    4,  -1,    50,    3,     -1,    51,    4,     -1,    51,    3,
    -1, -1,    46,    5,     -1,    -1,    52,    3,     -1,    62,
    -1, 63,    -1,    64,    -1,    53,    7,     -1,    53,    8,
    -1, 53,    9,     -1,    44,    45,    -1,    22,    23,    -1,
    24, 25,    -1,    26,    27,    -1,    28,    29,    -1,    30,
    31, -1,    32,    33,    -1,    14,    60,    10,    15,    -1,
    16, 17,    -1,    18,    61,    10,    19,    -1,    34,    35,
    -1, 77,    82,    -1,    82,    -1,    40,    78,    41,    -1,
    -1, 79,    -1,    42,    80,    43,    -1,    -1,    81,    -1,
    65, -1,    81,    65,    -1,    20,    59,    10,    83,    21,
    -1, 84,    -1,    83,    84,    -1,    83,    90,    -1,    12,
    85, 10,    87,    -1,    -1,    86,    85,    -1,    55,    -1,
    56, -1,    57,    -1,    58,    -1,    -1,    88,    -1,    89,
    -1, 88,    89,    -1,    66,    -1,    67,    -1,    68,    -1,
    69, -1,    70,    -1,    71,    -1,    75,    -1,    72,    -1,
    73, -1,    74,    -1,    13,    -1
};

/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
const unsigned char
ReMapParser::yyprhs_[] =
{
    0,   0,     3,     6,     9,     12,    15,    18,    21,    22,
    25,  26,    29,    31,    33,    35,    38,    41,    44,    47,
    50,  53,    56,    59,    62,    65,    70,    73,    78,    81,
    84,  86,    90,    91,    93,    97,    98,    100,   102,   105,
    111, 113,   116,   119,   124,   125,   128,   130,   132,   134,
    136, 137,   139,   141,   144,   146,   148,   150,   152,   154,
    156, 158,   160,   162,   164
};

/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
const unsigned short int
ReMapParser::yyrline_[] =
{
    0,   201,   201,   209,   217,   223,   233,   239,   248,   250,
    259, 261,   272,   274,   276,   280,   289,   299,   312,   321,
    328, 334,   341,   348,   355,   365,   373,   381,   392,   405,
    407, 413,   415,   416,   420,   423,   424,   428,   429,   435,
    444, 445,   446,   452,   521,   522,   525,   526,   527,   528,
    531, 532,   536,   537,   541,   542,   543,   544,   545,   546,
    547, 548,   549,   550,   554
};

// Print the state stack on the debug stream.
void
ReMapParser::yystack_print_()
{
    *yycdebug_ << "Stack now";
    for ( state_stack_type::const_iterator i = yystate_stack_.begin();
          i != yystate_stack_.end(); ++i )
    {
        *yycdebug_ << ' ' << *i;
    }
    *yycdebug_ << std::endl;
}

// Report on the debug stream that the rule \a yyrule is going to be reduced.
void
ReMapParser::yy_reduce_print_( int yyrule )
{
    unsigned int yylno  = yyrline_[ yyrule ];
    int          yynrhs = yyr2_[ yyrule ];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for ( int yyi = 0; yyi < yynrhs; yyi++ )
    {
        YY_SYMBOL_PRINT( "   $" << yyi + 1 << " =",
                         yyrhs_[ yyprhs_[ yyrule ] + yyi ],
                         &( yysemantic_stack_[ ( yynrhs ) - ( yyi + 1 ) ] ),
                         &( yylocation_stack_[ ( yynrhs ) - ( yyi + 1 ) ] ) );
    }
}
#endif // REMAPPARSERDEBUG

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
ReMapParser::token_number_type
ReMapParser::yytranslate_( int t )
{
    static
    const token_number_type
        translate_table[] =
    {
        0,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     1,     2,     3,     4,
        5,  6,     7,     8,     9,     10,    11,    12,    13,    14,
        15, 16,    17,    18,    19,    20,    21,    22,    23,    24,
        25, 26,    27,    28,    29,    30,    31,    32,    33,    34,
        35, 36,    37,    38,    39,    40,    41,    42,    43,    44,
        45, 46,    47,    48,    49,    50,    51,    52,    53
    };
    if ( ( unsigned int )t <= yyuser_token_number_max_ )
    {
        return translate_table[ t ];
    }
    else
    {
        return yyundef_token_;
    }
}

const int ReMapParser::yyeof_     = 0;
const int ReMapParser::yylast_    = 64;
const int ReMapParser::yynnts_    = 37;
const int ReMapParser::yyempty_   = -2;
const int ReMapParser::yyfinal_   = 11;
const int ReMapParser::yyterror_  = 1;
const int ReMapParser::yyerrcode_ = 256;
const int ReMapParser::yyntokens_ = 54;

const unsigned int                   ReMapParser::yyuser_token_number_max_ = 308;
const ReMapParser::token_number_type ReMapParser::yyundef_token_           = 2;
} // remapparser
/* Line 1141 of lalr1.cc  */
#line 1471 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.cc"
/* Line 1142 of lalr1.cc  */
#line 563 "../../build-frontend/../src/tools/tools/0031.ReMap2/ReMapParser.yy"
/*** Additional Code ***/


void
remapparser::ReMapParser::error( const ReMapParser::location_type& l,
                                 const std::string&                m )
{
    if ( strstr( m.c_str(), "expecting <?xml" ) != NULL )
    {
        driver.error_just_message( "The cube file is probably empty or filled with wrong content. The file has ended before the header of cube started. \n" );
    }
    if ( strstr( m.c_str(), " expecting <metric" ) != NULL )
    {
        driver.error_just_message( "The cube file doesn't contain any information about metric dimension." );
    }
    driver.error( l, m );
}
