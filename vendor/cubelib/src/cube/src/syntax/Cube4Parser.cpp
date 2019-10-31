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
#define yylex   cubeparserlex

/* First part of user declarations.  */

/* Line 279 of lalr1.cc  */
#line 40 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"


#include "Cube4Parser.h"

/* User implementation prologue.  */
/* Line 285 of lalr1.cc  */
#line 245 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"




#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"
#include "CubeMetric.h"
#include "CubeCnode.h"
#include "CubeRegion.h"

#include "CubeDriver.h"
#include "Cube4Scanner.h"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <string>


#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <string>
#include <vector>
#include "CubeServices.h"
#include "CubeParseContext.h"
#include "CubeMetric.h"
#include "Cube.h"
#include "CubeCartesian.h"

using namespace std;

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex Cube4Lexer.lex

// Workaround for Sun Studio C++ compilers on Solaris
#if defined( __SVR4 ) &&  defined( __SUNPRO_CC )
  #include <ieeefp.h>

  #define isinf( x )  ( fpclass( x ) == FP_NINF || fpclass( x ) == FP_PINF )
  #define isnan( x )  isnand( x )
#endif


cubeparser::Cube4Parser::location_type cubeparserloc;



/* Line 285 of lalr1.cc  */
#line 104 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"


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
#if CUBEPARSERDEBUG

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

#else /* !CUBEPARSERDEBUG */

# define YYCDEBUG if ( false ) std::cerr
# define YY_SYMBOL_PRINT( Title, Type, Value, Location ) YYUSE( Type )
# define YY_REDUCE_PRINT( Rule )        static_cast<void>( 0 )
# define YY_STACK_PRINT()             static_cast<void>( 0 )

#endif /* !CUBEPARSERDEBUG */

#define yyerrok         ( yyerrstatus_ = 0 )
#define yyclearin       ( yychar = yyempty_ )

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  ( !!yyerrstatus_ )


namespace cubeparser
{
/* Line 353 of lalr1.cc  */
#line 199 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"

/* Return YYSTR after stripping away unnecessary quotes and
   backslashes, so that it's suitable for yyerror.  The heuristic is
   that double-quoting is unnecessary unless the string contains an
   apostrophe, a comma, or backslash (other than backslash-backslash).
   YYSTR is taken from yytname.  */
std::string
Cube4Parser::yytnamerr_( const char* yystr )
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
Cube4Parser::Cube4Parser ( class Driver& driver_yyarg, class ParseContext& parseContext_yyarg, class Cube4Scanner& Cube4Lexer_yyarg, class cube::Cube& cube_yyarg, bool& clustering_on_yyarg )
    :
#if CUBEPARSERDEBUG
    yydebug_( false ),
    yycdebug_( &std::cerr ),
#endif
    driver( driver_yyarg ),
    parseContext( parseContext_yyarg ),
    Cube4Lexer( Cube4Lexer_yyarg ),
    cube( cube_yyarg ),
    clustering_on( clustering_on_yyarg )
{
}

Cube4Parser::~Cube4Parser ()
{
}

#if CUBEPARSERDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
   `--------------------------------*/

inline void
Cube4Parser::yy_symbol_value_print_( int yytype,
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
Cube4Parser::yy_symbol_print_( int yytype,
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
Cube4Parser::yydestruct_( const char* yymsg,
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
Cube4Parser::yypop_( unsigned int n )
{
    yystate_stack_.pop( n );
    yysemantic_stack_.pop( n );
    yylocation_stack_.pop( n );
}

#if CUBEPARSERDEBUG
std::ostream&
Cube4Parser::debug_stream() const
{
    return *yycdebug_;
}

void
Cube4Parser::set_debug_stream( std::ostream& o )
{
    yycdebug_ = &o;
}


Cube4Parser::debug_level_type
Cube4Parser::debug_level() const
{
    return yydebug_;
}

void
Cube4Parser::set_debug_level( debug_level_type l )
{
    yydebug_ = l;
}
#endif

inline bool
Cube4Parser::yy_pact_value_is_default_( int yyvalue )
{
    return yyvalue == yypact_ninf_;
}

inline bool
Cube4Parser::yy_table_value_is_error_( int yyvalue )
{
    return yyvalue == yytable_ninf_;
}

int
Cube4Parser::parse()
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
#line 76 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
        {
            // initialize the initial location object
            yylloc.begin.filename = yylloc.end.filename = &driver.streamname;
            clustering_on         = false;
        }
/* Line 545 of lalr1.cc  */
#line 405 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"

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
#line 310 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.versionSeen )
                    {
                        error( cubeparserloc, "Multiple version attributes defines!" );
                    }
                    else
                    {
                        parseContext.versionSeen = true;
                    }
                    parseContext.version = parseContext.str.str();
                }
                break;

            case 3:
/* Line 670 of lalr1.cc  */
#line 317 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.encodingSeen )
                    {
                        error( cubeparserloc, "Multiple encoding attributes defines!" );
                    }
                    else
                    {
                        parseContext.encodingSeen = true;
                    }
                    parseContext.encoding = parseContext.str.str();
                }
                break;

            case 4:
/* Line 670 of lalr1.cc  */
#line 324 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.keySeen )
                    {
                        error( cubeparserloc, "Multiple key attributes defines!" );
                    }
                    else
                    {
                        parseContext.keySeen = true;
                    }
                    parseContext.key = parseContext.str.str();
                }
                break;

            case 5:
/* Line 670 of lalr1.cc  */
#line 331 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.valueSeen )
                    {
                        error( cubeparserloc, "Multiple value attributes defines!" );
                    }
                    else
                    {
                        parseContext.valueSeen = true;
                    }
                    parseContext.value = parseContext.str.str();
                }
                break;

            case 6:
/* Line 670 of lalr1.cc  */
#line 338 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.modSeen )
                    {
                        error( cubeparserloc, "Multiple module attributes defines!" );
                    }
                    else
                    {
                        parseContext.modSeen = true;
                    }
                    parseContext.mod = parseContext.str.str();
                }
                break;

            case 7:
/* Line 670 of lalr1.cc  */
#line 345 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.metricTypeSeen )
                    {
                        error( cubeparserloc, "Multiple metric type attributes defines!" );
                    }
                    else
                    {
                        parseContext.metricTypeSeen = true;
                    }
                    parseContext.metricType = parseContext.str.str();
                }
                break;

            case 8:
/* Line 670 of lalr1.cc  */
#line 353 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.metricVizTypeSeen )
                    {
                        error( cubeparserloc, "Multiple metric visibilty type attributes defines!" );
                    }
                    else
                    {
                        parseContext.metricVizTypeSeen = true;
                    }
                    parseContext.metricVizType = parseContext.str.str();
                }
                break;

            case 9:
/* Line 670 of lalr1.cc  */
#line 361 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.metricConvertibleSeen )
                    {
                        error( cubeparserloc, "Multiple metric convertible type attributes defines!" );
                    }
                    else
                    {
                        parseContext.metricConvertibleSeen = true;
                    }
                    parseContext.metricConvertible = true;
                }
                break;

            case 10:
/* Line 670 of lalr1.cc  */
#line 367 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.metricConvertibleSeen )
                    {
                        error( cubeparserloc, "Multiple metric convertible type attributes defines!" );
                    }
                    else
                    {
                        parseContext.metricConvertibleSeen = true;
                    }
                    parseContext.metricConvertible = false;
                }
                break;

            case 11:
/* Line 670 of lalr1.cc  */
#line 375 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.metricCacheableSeen )
                    {
                        error( cubeparserloc, "Multiple metric cacheable type attributes defines!" );
                    }
                    else
                    {
                        parseContext.metricCacheableSeen = true;
                    }
                    parseContext.metricCacheable = true;
                }
                break;

            case 12:
/* Line 670 of lalr1.cc  */
#line 381 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.metricCacheableSeen )
                    {
                        error( cubeparserloc, "Multiple metric cacheable type attributes defines!" );
                    }
                    else
                    {
                        parseContext.metricCacheableSeen = true;
                    }
                    parseContext.metricCacheable = false;
                }
                break;

            case 13:
/* Line 670 of lalr1.cc  */
#line 391 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.cnodeParTypeSeen )
                    {
                        error( cubeparserloc, "Multiple cnode parameter type attributes defines!" );
                    }
                    else
                    {
                        parseContext.cnodeParTypeSeen = true;
                    }
                    parseContext.cnode_parameter_type = parseContext.str.str();
                }
                break;

            case 14:
/* Line 670 of lalr1.cc  */
#line 400 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.cnodeParKeySeen )
                    {
                        error( cubeparserloc, "Multiple cnode parameter keys defines!" );
                    }
                    else
                    {
                        parseContext.cnodeParKeySeen = true;
                    }
                    parseContext.cnode_parameter_key = parseContext.str.str();
                }
                break;

            case 15:
/* Line 670 of lalr1.cc  */
#line 409 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.cnodeParValueSeen )
                    {
                        error( cubeparserloc, "Multiple cnode parameter values defines!" );
                    }
                    else
                    {
                        parseContext.cnodeParValueSeen = true;
                    }
                    parseContext.cnode_parameter_value = parseContext.str.str();
                }
                break;

            case 16:
/* Line 670 of lalr1.cc  */
#line 418 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.cartNameSeen )
                    {
                        error( cubeparserloc, "Multiple topology names  defines!" );
                    }
                    else
                    {
                        parseContext.cartNameSeen = true;
                    }
                    parseContext.cartName = parseContext.str.str();
                }
                break;

            case 17:
/* Line 670 of lalr1.cc  */
#line 428 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.dimNameSeen )
                    {
                        error( cubeparserloc, "Multiple names for dimension attributes defines!" );
                    }
                    else
                    {
                        parseContext.dimNameSeen = true;
                    }
                    parseContext.dimNamesCount++;
                    parseContext.dimName = cube::services::escapeFromXML( parseContext.str.str() );
                }
                break;

            case 19:
/* Line 670 of lalr1.cc  */
#line 438 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.metricsTitleSeen )
                    {
                        error( cubeparserloc, "Multiple metrics titles defined!" );
                    }
                    else
                    {
                        parseContext.metricsTitleSeen = true;
                    }
                    parseContext.metricsTitle = parseContext.str.str();
                }
                break;

            case 21:
/* Line 670 of lalr1.cc  */
#line 447 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.calltreeTitleSeen )
                    {
                        error( cubeparserloc, "Multiple calltree titles defined!" );
                    }
                    else
                    {
                        parseContext.calltreeTitleSeen = true;
                    }
                    parseContext.calltreeTitle = parseContext.str.str();
                }
                break;

            case 23:
/* Line 670 of lalr1.cc  */
#line 457 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.systemtreeTitleSeen )
                    {
                        error( cubeparserloc, "Multiple system tree titles defined!" );
                    }
                    else
                    {
                        parseContext.systemtreeTitleSeen = true;
                    }
                    parseContext.systemtreeTitle = parseContext.str.str();
                }
                break;

            case 25:
/* Line 670 of lalr1.cc  */
#line 467 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.cubeplTypeSeen )
                    {
                        error( cubeparserloc, "Multiple cubepl type attributes defines!" );
                    }
                    else
                    {
                        parseContext.cubeplTypeSeen = true;
                    }
                    parseContext.rowwise = false;
                }
                break;

            case 29:
/* Line 670 of lalr1.cc  */
#line 486 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.expressionAggrPlusSeen )
                    {
                        error( cubeparserloc, "Multiple cubepl plus-aggregation attributes defines!" );
                    }
                    else
                    {
                        parseContext.expressionAggrPlusSeen = true;
                    }
                    parseContext.cubeplAggrType = ParseContext::CUBEPL_AGGR_PLUS;
                }
                break;

            case 30:
/* Line 670 of lalr1.cc  */
#line 496 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.expressionAggrMinusSeen )
                    {
                        error( cubeparserloc, "Multiple cubepl minus-aggregation attributes defines!" );
                    }
                    else
                    {
                        parseContext.expressionAggrMinusSeen = true;
                    }
                    parseContext.cubeplAggrType = ParseContext::CUBEPL_AGGR_MINUS;
                }
                break;

            case 31:
/* Line 670 of lalr1.cc  */
#line 507 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.expressionAggrAggrSeen )
                    {
                        error( cubeparserloc, "Multiple cubepl aggr-aggregation attributes defines!" );
                    }
                    else
                    {
                        parseContext.expressionAggrAggrSeen = true;
                    }
                    parseContext.cubeplAggrType = ParseContext::CUBEPL_AGGR_AGGR;
                }
                break;

            case 32:
/* Line 670 of lalr1.cc  */
#line 519 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.idSeen )
                    {
                        error( cubeparserloc, "Multiple id attributes defines!" );
                    }
                    else
                    {
                        parseContext.idSeen = true;
                    }
                    if ( parseContext.longAttribute < 0 )
                    {
                        error( cubeparserloc, "Ids must be non-negative!" );
                    }
                    parseContext.id = ( int )parseContext.longAttribute;
                }
                break;

            case 33:
/* Line 670 of lalr1.cc  */
#line 528 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.calleeidSeen )
                    {
                        error( cubeparserloc, "Multiple callee id attributes defines!" );
                    }
                    else
                    {
                        parseContext.calleeidSeen = true;
                    }
                    if ( parseContext.longAttribute < 0 )
                    {
                        error( cubeparserloc, "Callee ids of regions must be non-negative!" );
                    }
                    parseContext.calleeid = ( int )parseContext.longAttribute;
                }
                break;

            case 34:
/* Line 670 of lalr1.cc  */
#line 540 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.locidSeen )
                    {
                        error( cubeparserloc, "Multiple location id attributes defines!" );
                    }
                    else
                    {
                        parseContext.locidSeen = true;
                    }
                    if ( parseContext.longAttribute < 0 )
                    {
                        error( cubeparserloc, "Location ids must be non-negative!" );
                    }
                    parseContext.locid = ( int )parseContext.longAttribute;
                }
                break;

            case 35:
/* Line 670 of lalr1.cc  */
#line 549 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.lgidSeen )
                    {
                        error( cubeparserloc, "Multiple location group id attributes defines!" );
                    }
                    else
                    {
                        parseContext.lgidSeen = true;
                    }
                    if ( parseContext.longAttribute < 0 )
                    {
                        error( cubeparserloc, "Location group ids must be non-negative!" );
                    }
                    parseContext.lgid = ( int )parseContext.longAttribute;
                }
                break;

            case 36:
/* Line 670 of lalr1.cc  */
#line 558 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.stnidSeen )
                    {
                        error( cubeparserloc, "Multiple system tree node id attributes defines!" );
                    }
                    else
                    {
                        parseContext.stnidSeen = true;
                    }
                    if ( parseContext.longAttribute < 0 )
                    {
                        error( cubeparserloc, "System tree node ids must be non-negative!" );
                    }
                    parseContext.stnid = ( int )parseContext.longAttribute;
                }
                break;

            case 37:
/* Line 670 of lalr1.cc  */
#line 568 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.locidSeen )
                    {
                        error( cubeparserloc, "Multiple thread id attributes defines!" );
                    }
                    else
                    {
                        parseContext.locidSeen = true;
                    }
                    if ( parseContext.longAttribute < 0 )
                    {
                        error( cubeparserloc, "Thread ids must be non-negative!" );
                    }
                    parseContext.thrdid = ( int )parseContext.longAttribute;
                }
                break;

            case 38:
/* Line 670 of lalr1.cc  */
#line 577 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.lgidSeen )
                    {
                        error( cubeparserloc, "Multiple process id attributes defines!" );
                    }
                    else
                    {
                        parseContext.lgidSeen = true;
                    }
                    if ( parseContext.longAttribute < 0 )
                    {
                        error( cubeparserloc, "Process ids must be non-negative!" );
                    }
                    parseContext.procid = ( int )parseContext.longAttribute;
                }
                break;

            case 39:
/* Line 670 of lalr1.cc  */
#line 586 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.stnidSeen )
                    {
                        error( cubeparserloc, "Multiple node id attributes defines!" );
                    }
                    else
                    {
                        parseContext.stnidSeen = true;
                    }
                    if ( parseContext.longAttribute < 0 )
                    {
                        error( cubeparserloc, "Node ids must be non-negative!" );
                    }
                    parseContext.nodeid = ( int )parseContext.longAttribute;
                }
                break;

            case 40:
/* Line 670 of lalr1.cc  */
#line 595 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.stnidSeen )
                    {
                        error( cubeparserloc, "Multiple machine id attributes defines!" );
                    }
                    else
                    {
                        parseContext.stnidSeen = true;
                    }
                    if ( parseContext.longAttribute < 0 )
                    {
                        error( cubeparserloc, "Machine ids must be non-negative!" );
                    }
                    parseContext.machid = ( int )parseContext.longAttribute;
                }
                break;

            case 41:
/* Line 670 of lalr1.cc  */
#line 604 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.metricidSeen )
                    {
                        error( cubeparserloc, "Multiple metric id attributes defines!" );
                    }
                    else
                    {
                        parseContext.metricidSeen = true;
                    }
                    if ( parseContext.longAttribute < 0 )
                    {
                        error( cubeparserloc, "Metric ids must be non-negative!" );
                    }
                    parseContext.metricid = parseContext.longAttribute;
                }
                break;

            case 42:
/* Line 670 of lalr1.cc  */
#line 613 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.cnodeidSeen )
                    {
                        error( cubeparserloc, "Multiple cnode id attributes defines!" );
                    }
                    else
                    {
                        parseContext.cnodeidSeen = true;
                    }
                    if ( parseContext.longAttribute < 0 )
                    {
                        error( cubeparserloc, "Cnode ids must be non-negative!" );
                    }
                    parseContext.cnodeid = ( int )parseContext.longAttribute;
                }
                break;

            case 43:
/* Line 670 of lalr1.cc  */
#line 624 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.beginSeen )
                    {
                        error( cubeparserloc, "Multiple begin attributes defines!" );
                    }
                    else
                    {
                        parseContext.beginSeen = true;
                    }
                    parseContext.beginln = parseContext.longAttribute;
                }
                break;

            case 44:
/* Line 670 of lalr1.cc  */
#line 632 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.endSeen )
                    {
                        error( cubeparserloc, "Multiple end attributes defines!" );
                    }
                    else
                    {
                        parseContext.endSeen = true;
                    }
                    parseContext.endln = parseContext.longAttribute;
                }
                break;

            case 45:
/* Line 670 of lalr1.cc  */
#line 640 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.lineSeen )
                    {
                        error( cubeparserloc, "Multiple line attributes defines!" );
                    }
                    else
                    {
                        parseContext.lineSeen = true;
                    }
                    parseContext.line = parseContext.longAttribute;
                }
                break;

            case 46:
/* Line 670 of lalr1.cc  */
#line 648 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.ndimsSeen )
                    {
                        error( cubeparserloc, "Multiple ndims attributes defines!" );
                    }
                    else
                    {
                        parseContext.ndimsSeen = true;
                    }
                    if ( parseContext.longAttribute <= 0 )
                    {
                        error( cubeparserloc, "Topology dimensions must be positive numbers!" );
                    }
                    parseContext.ndims = parseContext.longAttribute;
                }
                break;

            case 47:
/* Line 670 of lalr1.cc  */
#line 658 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.sizeSeen )
                    {
                        error( cubeparserloc, "Multiple size attributes defines!" );
                    }
                    else
                    {
                        parseContext.sizeSeen = true;
                    }
                    if ( parseContext.longAttribute <= 0 )
                    {
                        error( cubeparserloc, "Dimension sizes must be positive numbers!" );
                    }
                    parseContext.dimVec.push_back( parseContext.longAttribute );
                }
                break;

            case 48:
/* Line 670 of lalr1.cc  */
#line 670 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.periodicSeen )
                    {
                        error( cubeparserloc, "Multiple periodic attributes defines!" );
                    }
                    else
                    {
                        parseContext.periodicSeen = true;
                    }
                    parseContext.periodicVec.push_back( false );
                }
                break;

            case 49:
/* Line 670 of lalr1.cc  */
#line 676 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.periodicSeen )
                    {
                        error( cubeparserloc, "Multiple periodic attributes defined!" );
                    }
                    else
                    {
                        parseContext.periodicSeen = true;
                    }
                    parseContext.periodicVec.push_back( true );
                }
                break;

            case 50:
/* Line 670 of lalr1.cc  */
#line 687 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.murlSeen )
                    {
                        error( cubeparserloc, "Multiple murl tags defined!" );
                    }
                    else
                    {
                        parseContext.murlSeen = true;
                    }
                    parseContext.murl = parseContext.str.str();
                }
                break;

            case 51:
/* Line 670 of lalr1.cc  */
#line 697 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.dispnameSeen )
                    {
                        error( cubeparserloc, "Multiple disp_name tags defined!" );
                    }
                    else
                    {
                        parseContext.dispnameSeen = true;
                    }
                    parseContext.disp_name = parseContext.str.str();
                }
                break;

            case 52:
/* Line 670 of lalr1.cc  */
#line 704 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.uniqnameSeen )
                    {
                        error( cubeparserloc, "Multiple uniq_name tags defined!" );
                    }
                    else
                    {
                        parseContext.uniqnameSeen = true;
                    }
                    parseContext.uniq_name = parseContext.str.str();
                }
                break;

            case 53:
/* Line 670 of lalr1.cc  */
#line 710 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.dtypeSeen )
                    {
                        error( cubeparserloc, "Multiple dtype tags defined!" );
                    }
                    else
                    {
                        parseContext.dtypeSeen = true;
                    }
                    parseContext.dtype = parseContext.str.str();
                }
                break;

            case 54:
/* Line 670 of lalr1.cc  */
#line 717 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.uomSeen )
                    {
                        error( cubeparserloc, "Multiple uom tags defined!" );
                    }
                    else
                    {
                        parseContext.uomSeen = true;
                    }
                    parseContext.uom = parseContext.str.str();
                }
                break;

            case 55:
/* Line 670 of lalr1.cc  */
#line 724 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.valSeen )
                    {
                        error( cubeparserloc, "Multiple val tags defined!" );
                    }
                    else
                    {
                        parseContext.valSeen = true;
                    }
                    parseContext.val = parseContext.str.str();
                }
                break;

            case 56:
/* Line 670 of lalr1.cc  */
#line 731 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.urlSeen )
                    {
                        error( cubeparserloc, "Multiple url tags defined!" );
                    }
                    else
                    {
                        parseContext.urlSeen = true;
                    }
                    parseContext.url = parseContext.str.str();
                }
                break;

            case 59:
/* Line 670 of lalr1.cc  */
#line 743 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.expressionSeen )
                    {
                        error( cubeparserloc, "Multiple expressions defined!" );
                    }
                    else
                    {
                        parseContext.expressionSeen = true;
                    }
                    parseContext.expression = cube::services::escapeFromXML( parseContext.str.str() );
                }
                break;

            case 60:
/* Line 670 of lalr1.cc  */
#line 751 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.expressionInitSeen )
                    {
                        error( cubeparserloc, "Multiple expression initializations defined!" );
                    }
                    else
                    {
                        parseContext.expressionInitSeen = true;
                    }
                    parseContext.expressionInit = cube::services::escapeFromXML( parseContext.str.str() );
                }
                break;

            case 61:
/* Line 670 of lalr1.cc  */
#line 759 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.cubeplAggrType == ParseContext::CUBEPL_AGGR_PLUS )
                    {
                        parseContext.expressionAggrPlus = cube::services::escapeFromXML( parseContext.str.str() );
                    }
                    else
                    if ( parseContext.cubeplAggrType == ParseContext::CUBEPL_AGGR_MINUS )
                    {
                        parseContext.expressionAggrMinus = cube::services::escapeFromXML( parseContext.str.str() );
                    }
                    else
                    if ( parseContext.cubeplAggrType == ParseContext::CUBEPL_AGGR_AGGR )
                    {
                        parseContext.expressionAggrAggr = cube::services::escapeFromXML( parseContext.str.str() );
                    }
                }
                break;

            case 62:
/* Line 670 of lalr1.cc  */
#line 770 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.descrSeen )
                    {
                        error( cubeparserloc, "Multiple descr tags defined!" );
                    }
                    else
                    {
                        parseContext.descrSeen = true;
                    }
                    parseContext.descr = parseContext.str.str();
                }
                break;

            case 63:
/* Line 670 of lalr1.cc  */
#line 777 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.nameSeen )
                    {
                        error( cubeparserloc, "Multiple name tags defined!" );
                    }
                    else
                    {
                        parseContext.nameSeen = true;
                    }
                    parseContext.name         = parseContext.str.str();
                    parseContext.mangled_name = parseContext.name;
                }
                break;

            case 64:
/* Line 670 of lalr1.cc  */
#line 787 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.mangledNameSeen )
                    {
                        error( cubeparserloc, "Multiple mangled name tags defined!" );
                    }
                    else
                    {
                        parseContext.mangledNameSeen = true;
                    }
                    parseContext.mangled_name = parseContext.str.str();
                }
                break;

            case 65:
/* Line 670 of lalr1.cc  */
#line 795 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.paradigmSeen )
                    {
                        error( cubeparserloc, "Multiple paradigm tags defined!" );
                    }
                    else
                    {
                        parseContext.paradigmSeen = true;
                    }
                    parseContext.paradigm = parseContext.str.str();
                }
                break;

            case 66:
/* Line 670 of lalr1.cc  */
#line 803 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.roleSeen )
                    {
                        error( cubeparserloc, "Multiple role tags defined!" );
                    }
                    else
                    {
                        parseContext.roleSeen = true;
                    }
                    parseContext.role = parseContext.str.str();
                }
                break;

            case 67:
/* Line 670 of lalr1.cc  */
#line 812 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.classSeen )
                    {
                        error( cubeparserloc, "Multiple class tags defined!" );
                    }
                    else
                    {
                        parseContext.classSeen = true;
                    }
                    parseContext.stn_class = parseContext.str.str();
                }
                break;

            case 68:
/* Line 670 of lalr1.cc  */
#line 821 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.typeSeen )
                    {
                        error( cubeparserloc, "Multiple type tags defined!" );
                    }
                    else
                    {
                        parseContext.typeSeen = true;
                    }
                    parseContext.type = parseContext.str.str();
                }
                break;

            case 69:
/* Line 670 of lalr1.cc  */
#line 828 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.rankSeen )
                    {
                        error( cubeparserloc, "Multiple rank tags defined!" );
                    }
                    else
                    {
                        parseContext.rankSeen = true;
                    }
                    if ( parseContext.longValues.size() == 0 )
                    {
                        error( cubeparserloc, "No rank is given in a rank tag!" );
                    }
                    if ( parseContext.longValues.size() > 1 )
                    {
                        error( cubeparserloc, "Multiple ranks are given in a rank tag!" );
                    }
                    int rank = ( int )parseContext.longValues[ 0 ];
                    if ( rank < 0 )
                    {
                        error( cubeparserloc, "Ranks must be non-negative!" );
                    }
                    parseContext.rank = rank;
                }
                break;

            case 70:
/* Line 670 of lalr1.cc  */
#line 845 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    unsigned nparameters = 0;
                    if ( parseContext.cnode_parameter_type == "numeric" )
                    {
                        if ( !parseContext.n_cnode_num_parameters.empty() )
                        {
                            nparameters = parseContext.n_cnode_num_parameters.top();
                            parseContext.n_cnode_num_parameters.pop();
                        }
                        nparameters++;
                        parseContext.n_cnode_num_parameters.push( nparameters );
                        std::pair<std::string, std::string > _key;
                        _key.first  =  cube::services::escapeFromXML( parseContext.cnode_parameter_key );
                        _key.second =  cube::services::escapeFromXML( parseContext.cnode_parameter_value );
                        parseContext.cnode_num_parameters.push( _key );
                    }
                    if ( parseContext.cnode_parameter_type == "string" )
                    {
                        if ( !parseContext.n_cnode_str_parameters.empty() )
                        {
                            nparameters = parseContext.n_cnode_str_parameters.top();
                            parseContext.n_cnode_str_parameters.pop();
                        }
                        nparameters++;
                        parseContext.n_cnode_str_parameters.push( nparameters );

                        std::pair<std::string, std::string > _key;
                        _key.first  =  cube::services::escapeFromXML( parseContext.cnode_parameter_key );
                        _key.second =  cube::services::escapeFromXML( parseContext.cnode_parameter_value );
                        parseContext.cnode_str_parameters.push( _key );
                    }
                    parseContext.stringContent     = false;
                    parseContext.cnodeParTypeSeen  = false;
                    parseContext.cnodeParKeySeen   = false;
                    parseContext.cnodeParValueSeen = false;
                }
                break;

            case 72:
/* Line 670 of lalr1.cc  */
#line 896 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    //check for attributes
                    if ( !parseContext.versionSeen )
                    {
                        error( cubeparserloc, "Missing version attribute!" );
                    }
                    else
                    {
                        parseContext.versionSeen = false;
                    }
                    if ( !parseContext.encodingSeen )
                    {
                        error( cubeparserloc, "Missing encoding attribute!" );
                    }
                    else
                    {
                        parseContext.encodingSeen = false;
                    }
                    int valid = strcmp( parseContext.version.c_str(), "1.0" );
                    if ( valid != 0 )
                    {
                        error( cubeparserloc, "XML version is expected to be 1.0!" );
                    }
                    valid = strcmp( parseContext.encoding.c_str(), "UTF-8" );
                    if ( valid != 0 )
                    {
                        error( cubeparserloc, "XML encoding is expected to be UTF-8!" );
                    }
                    cube.get_operation_progress()->start_step( 0., 1. );
                }
                break;

            case 77:
/* Line 670 of lalr1.cc  */
#line 926 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    cube.get_operation_progress()->finish_step( "Finished parsing" );
                }
                break;

            case 78:
/* Line 670 of lalr1.cc  */
#line 932 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    parseContext.cubeVersion = 4;
                    cube.def_attr( "Cube anchor.xml syntax version", "4" );
                }
                break;

            case 79:
/* Line 670 of lalr1.cc  */
#line 936 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    parseContext.cubeVersion = 4.1;
                    cube.def_attr( "Cube anchor.xml syntax version", "4.1" );
                }
                break;

            case 80:
/* Line 670 of lalr1.cc  */
#line 940 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    parseContext.cubeVersion = 4.2;
                    cube.def_attr( "Cube anchor.xml syntax version", "4.2" );
                }
                break;

            case 81:
/* Line 670 of lalr1.cc  */
#line 944 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    parseContext.cubeVersion = 4.3;
                    cube.def_attr( "Cube anchor.xml syntax version", "4.3" );
                }
                break;

            case 82:
/* Line 670 of lalr1.cc  */
#line 948 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    parseContext.cubeVersion = 4.4;
                    cube.def_attr( "Cube anchor.xml syntax version", "4.4" );
                }
                break;

            case 83:
/* Line 670 of lalr1.cc  */
#line 952 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    parseContext.cubeVersion = 4.5;
                    cube.def_attr( "Cube anchor.xml syntax version", "4.5" );
                }
                break;

            case 84:
/* Line 670 of lalr1.cc  */
#line 956 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    parseContext.cubeVersion = 3;
                    cube.def_attr( "Cube syntax version", "3" );
                }
                break;

            case 85:
/* Line 670 of lalr1.cc  */
#line 960 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    throw cube::NotSupportedVersionError( parseContext.str.str() );
                }
                break;

            case 92:
/* Line 670 of lalr1.cc  */
#line 980 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    //check for attributes
                    if ( !parseContext.keySeen )
                    {
                        error( cubeparserloc, "Missing key attribute!" );
                    }
                    else
                    {
                        parseContext.keySeen = false;
                    }
                    if ( !parseContext.valueSeen )
                    {
                        error( cubeparserloc, "Missing value attribute!" );
                    }
                    else
                    {
                        parseContext.valueSeen = false;
                    }
                    string attrkey   = cube::services::escapeFromXML( parseContext.key );
                    string attrvalue = cube::services::escapeFromXML( parseContext.value );
                    cube.def_attr( attrkey, attrvalue );

                    if ( attrkey.compare( CUBEPL_VERSION_KEY ) == 0 )
                    {
                        cube.select_cubepl_engine( attrvalue );
                    }
                }
                break;

            case 103:
/* Line 670 of lalr1.cc  */
#line 1027 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                { parseContext.murlSeen = false;
                  cube.def_mirror( cube::services::escapeFromXML( parseContext.murl ) );
                }
                break;

            case 104:
/* Line 670 of lalr1.cc  */
#line 1028 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                { parseContext.murlSeen = false;
                  cube.def_mirror( cube::services::escapeFromXML( parseContext.murl ) );
                }
                break;

            case 105:
/* Line 670 of lalr1.cc  */
#line 1037 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    clustering_on = false;
                    cube.get_operation_progress()->progress_step( "Parse metrics" );
                    if ( cube.is_clustering_on() )
                    {
                        cube.get_operation_progress()->start_step( 0., 1. );
                        cube.get_operation_progress()->progress_step( "Start parsing clusters" );
                        clustering_on = true;
                        std::map<uint64_t, std::map<uint64_t, uint64_t> > clusters_counter;

                        const std::map<std::string, std::string>&          attrs = cube.get_attrs();
                        std::map<std::string, std::string>::const_iterator _iter = attrs.find( "CLUSTERING" );
                        if ( _iter  != attrs.end() && ( *_iter ).second.compare( "ON" ) == 0 )
                        {
                            std::map<std::string, std::string>::const_iterator _iter = attrs.find( "CLUSTER ITERATION COUNT" );
                            if ( _iter != attrs.end() )
                            {
                                parseContext.number_of_iterations = cube::services::string2int( ( *_iter ).second );
                                std::map<std::string, std::string>::const_iterator _iter = attrs.find( "CLUSTER ROOT CNODE ID" );
                                if ( _iter != attrs.end() )
                                {
                                    parseContext.clustering_root_cnode_id = cube::services::string2int( ( *_iter ).second );
                                    for ( uint64_t iteration = 0; iteration < parseContext.number_of_iterations; iteration++ )
                                    {
                                        cube.get_operation_progress()->progress_step( iteration / parseContext.number_of_iterations, "Reading clusters mapping" );
                                        std::string                                        iteration_number = cube::services::numeric2string( iteration );
                                        std::string                                        key              = "CLUSTER MAPPING " + iteration_number;
                                        std::map<std::string, std::string>::const_iterator _iter            = attrs.find( key );
                                        if ( _iter != attrs.end() )
                                        {
                                            std::string           value                 = ( *_iter ).second;
                                            uint64_t              iteration_key         = iteration;
                                            std::vector<uint64_t> _cluster_id           = cube::services::parse_clustering_value( value );
                                            std::vector<uint64_t> _collapsed_cluster_id = cube::services::sort_and_collapse_clusters( _cluster_id );
                                            parseContext.cluster_mapping[ iteration_key ]           = _cluster_id;
                                            parseContext.cluster_positions[ iteration_key ]         = cube::services::get_cluster_positions( _cluster_id );
                                            parseContext.collapsed_cluster_mapping[ iteration_key ] = _collapsed_cluster_id;
                                            uint64_t process_rank = 0;
                                            for ( std::vector<uint64_t>::iterator iter = _cluster_id.begin(); iter != _cluster_id.end(); ++iter, ++process_rank )
                                            {
                                                uint64_t _id = *iter;
                                                clusters_counter[ _id ][ process_rank ]++;
                                            }
                                        }
                                        else
                                        {
                                            cerr << "Clustering mapping is not continuous." << endl;
                                            clustering_on = false;
                                            cube.enable_clustering( false );
                                            break;
                                        }
                                    }
                                    cube.set_clusters_count( clusters_counter );
                                }
                                else
                                {
                                    cerr << "Cannot find cluster root cnode" << endl;
                                    clustering_on = false;
                                    cube.enable_clustering( false );
                                }
                            }
                            else
                            {
                                cerr << "Cannot find number of clustered iterations" << endl;
                                clustering_on = false;
                                cube.enable_clustering( false );
                            }
                            cube.get_operation_progress()->finish_step( "Parsing cluster mappings finished" );
                        }
                        else
                        {
                            clustering_on = false;
                            cube.enable_clustering( false );
                        }
                    }
                }
                break;

            case 106:
/* Line 670 of lalr1.cc  */
#line 1115 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.metricsTitle != "" )
                    {
                        cube.set_metrics_title( cube::services::escapeFromXML( parseContext.metricsTitle ) );
                    }
                    cube.get_operation_progress()->progress_step( 0.2, "Finished parsing metrics" );
                }
                break;

            case 110:
/* Line 670 of lalr1.cc  */
#line 1132 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
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

                    while ( ( int )parseContext.metricVec.size() <= parseContext.id )
                    {
                        parseContext.metricVec.push_back( NULL );
                    }
                    if ( parseContext.metricVec[ parseContext.id ] != NULL )
                    {
                        error( cubeparserloc, "Re-declared metric!" );
                    }

                    parseContext.currentMetric =
                        cube.def_met(
                            cube::services::escapeFromXML( parseContext.disp_name ),
                            cube::services::escapeFromXML( parseContext.uniq_name ),
                            cube::services::escapeFromXML( parseContext.dtype ),
                            cube::services::escapeFromXML( parseContext.uom ),
                            cube::services::escapeFromXML( parseContext.val ),
                            cube::services::escapeFromXML( parseContext.url ),
                            cube::services::escapeFromXML( parseContext.descr ),
                            parseContext.currentMetric,
                            cube::Metric::get_type_of_metric( parseContext.metricType ),
                            cube::services::escapeFromXML( parseContext.expression ),
                            cube::services::escapeFromXML( parseContext.expressionInit ),
                            cube::services::escapeFromXML( parseContext.expressionAggrPlus ),
                            cube::services::escapeFromXML( parseContext.expressionAggrMinus ),
                            cube::services::escapeFromXML( parseContext.expressionAggrAggr ),
                            parseContext.rowwise,
                            cube::Metric::get_viz_type_of_metric( parseContext.metricVizType ) );
                    if ( parseContext.currentMetric != NULL )
                    {
                        parseContext.currentMetric->setConvertible( parseContext.metricConvertible );
                        parseContext.currentMetric->setCacheable( parseContext.metricCacheable );
                        parseContext.currentMetric->set_filed_id( parseContext.id );
                        if ( parseContext.n_attributes.size() > 0 )
                        {
                            unsigned nattributes = parseContext.n_attributes.top();
                            parseContext.n_attributes.pop();

                            if ( nattributes > parseContext.attributes.size() )
                            {
                                error( cubeparserloc, "Number of saved attributes for metric " + parseContext.uniq_name + " is more, than number of actual saved parameters." );
                            }
                            std::stack<std::pair<std::string, std::string> > reversed;
                            for ( unsigned i = 0; i < nattributes; i++ )
                            {
                                std::pair< std::string, std::string> attr = parseContext.attributes.top();
                                parseContext.attributes.pop();
                                reversed.push( attr );
                            }
                            for ( unsigned i = 0; i < nattributes; i++ )
                            {
                                std::pair< std::string, std::string> attr = reversed.top();
                                reversed.pop();
                                parseContext.currentMetric->def_attr( attr.first, attr.second );
                            }
                        }
                        parseContext.metricVec[ parseContext.id ] = parseContext.currentMetric;
                    }
                    else
                    {
                        std::string _error = "Cannot create metric  " + parseContext.uniq_name + ". Ignore it.";
                        cerr << _error << endl;
/*             error(cubeparserloc,_error.c_str()); */
                    }
                }
                break;

            case 134:
/* Line 670 of lalr1.cc  */
#line 1273 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    //check for attributes
                    if ( !parseContext.keySeen )
                    {
                        error( cubeparserloc, "Missing key attribute!" );
                    }
                    else
                    {
                        parseContext.keySeen = false;
                    }
                    if ( !parseContext.valueSeen )
                    {
                        error( cubeparserloc, "Missing value attribute!" );
                    }
                    else
                    {
                        parseContext.valueSeen = false;
                    }

                    unsigned nattributes = 0;
                    if ( parseContext.n_attributes.size() != 0  )
                    {
                        nattributes = parseContext.n_attributes.top();
                        parseContext.n_attributes.pop();
                    }
                    nattributes++;
                    parseContext.n_attributes.push( nattributes );
                    std::pair<std::string, std::string > _key;
                    _key.first  =  cube::services::escapeFromXML( parseContext.key );
                    _key.second =  cube::services::escapeFromXML( parseContext.value );
                    parseContext.attributes.push( _key );
                }
                break;

            case 135:
/* Line 670 of lalr1.cc  */
#line 1301 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.currentMetric != NULL )
                    {
                        parseContext.currentMetric =
                            ( parseContext.currentMetric )->get_parent();
                    }
                }
                break;

            case 136:
/* Line 670 of lalr1.cc  */
#line 1313 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    cube.get_operation_progress()->progress_step( 0.2, "Start parsing program dimension" );
                }
                break;

            case 137:
/* Line 670 of lalr1.cc  */
#line 1317 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    cube.get_operation_progress()->progress_step( 0.3, "Start parsing regions" );
                }
                break;

            case 138:
/* Line 670 of lalr1.cc  */
#line 1322 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    cube.get_operation_progress()->progress_step( 0.4, "Start parsing call tree" );
                }
                break;

            case 139:
/* Line 670 of lalr1.cc  */
#line 1326 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.calltreeTitle != "" )
                    {
                        cube.set_calltree_title( cube::services::escapeFromXML( parseContext.calltreeTitle ) );
                    }

                    if ( clustering_on ) // here look for region template  and create subtrees for iterations
                    {
                        cube.get_operation_progress()->start_step( 0., 1. );
                        cube.get_operation_progress()->progress_step( "Start declustering" );
                        // after parsing, whole stored calltree is stored not within cube, but separatelly, in parseContext.oroginal_tree_roots.
                        // here we create first a copy of the original tree without clustering subtrees
                        cube::Cnode* clusters_root = NULL;
                        cube.set_original_root_cnodev( parseContext.original_tree_roots );
                        int step = 0;
                        for ( std::vector<cube::Cnode*>::iterator citer = parseContext.original_tree_roots.begin(); citer != parseContext.original_tree_roots.end(); ++citer, ++step )
                        {
                            cube::Cnode* cnode          = *citer;
                            cube::Cnode* _clusters_root = NULL;
                            cube::services::copy_tree( cnode, _clusters_root, parseContext.clustering_root_cnode_id,  NULL, &cube );
                            if ( _clusters_root != NULL )
                            {
                                clusters_root = _clusters_root;
                            }
                        }
                        parseContext.clustering_root_cnode = clusters_root;

                        if ( cube::services::get_children( parseContext.original_tree_roots,
                                                           parseContext.clustering_root_cnode_id,
                                                           parseContext.clusters_trees ) )
                        {
                            int i = 0;
                            for ( std::vector<cube::Cnode*>::iterator citer = parseContext.clusters_trees.begin(); citer != parseContext.clusters_trees.end(); ++citer, ++i )
                            {
                                parseContext.id2cluster[ ( *citer )->get_id() ] = i;
                            }
                        }
                        else
                        {
                            clustering_on = false;
                            break;
                        }

                        cube.get_operation_progress()->progress_step( 0.1, "Create iteration template" );

                        // here we are going througs registered sofar regions and look for first cluster to take its region as a template for iterations
                        for ( std::vector<cube::Region*>::const_iterator riter = cube.get_regv().begin(); riter != cube.get_regv().end(); ++riter )
                        {
                            cube::Region* region = *riter;
                            if ( region->get_name().compare( "instance=1" ) == 0 )
                            {
                                parseContext.iterationRegionTemplate = region;
                                break;
                            }
                        }
                        // if we didn't found any regions, but clustering was "on" -> fatal error appeared.
                        if ( parseContext.iterationRegionTemplate == NULL ) // we didnt find any template for iteration subtree, bad cube layout
                        {
                            throw cube::CubeClusteringLayoutError( "Cannot find a template for iteration calltree." );
                        }

                        // here we merge different combinations of clusters.
                        // one can reduce amount of merges if one finds ont set of different collapsed rows - improvements for future.
                        cube.get_operation_progress()->progress_step( 0.2, "Create iterations" );

                        // here we create regions for iterations
                        std::map<uint64_t,   std::map<uint64_t, uint64_t> > cluster_counter = cube.get_clusters_counter();
                        for ( unsigned i = 0; i < parseContext.number_of_iterations; i++ )
                        {
                            std::stringstream sstr;
                            std::string       iteration_name;
                            sstr << i;
                            sstr >> iteration_name;
                            // we create a regions
                            cube::Region* region =  cube.def_region(
                                "iteration=" + iteration_name,
                                "iteration=" + iteration_name,
                                parseContext.iterationRegionTemplate->get_paradigm(),
                                parseContext.iterationRegionTemplate->get_role(),
                                parseContext.iterationRegionTemplate->get_begn_ln(),
                                parseContext.iterationRegionTemplate->get_end_ln(),
                                parseContext.iterationRegionTemplate->get_url(),
                                parseContext.iterationRegionTemplate->get_descr(),
                                parseContext.iterationRegionTemplate->get_mod()
                                );
                            parseContext.iteration_regions.push_back( region );
                            // create its cnode
                            cube::Cnode* iteration_cnode = cube.def_cnode(
                                region,
                                region->get_mod(),
                                region->get_begn_ln(),
                                parseContext.clustering_root_cnode
                                );

                            // here we merge all subtrees of all clusters to this callpath.
                            std::vector<cube::Cnode*> subtrees;
                            for ( std::vector< uint64_t>::iterator iter = parseContext.collapsed_cluster_mapping[ i ].begin(); iter != parseContext.collapsed_cluster_mapping[ i ].end(); ++iter  )
                            {
                                subtrees.clear();
                                uint64_t                     _cluster_id            = *iter;
                                std::map<uint64_t, uint64_t> _cluster_normalization = cluster_counter[ _cluster_id ];
                                uint64_t                     _cluster_position      = parseContext.id2cluster[ _cluster_id ];
                                cube::Cnode*                 cluster_root           = parseContext.clusters_trees[ _cluster_position ];
                                cube.store_ghost_cnode( cluster_root );
                                for ( size_t j = 0; j <  parseContext.cluster_positions[ i ][ _cluster_id ].size(); ++j )
                                {
                                    iteration_cnode->set_remapping_cnode( parseContext.cluster_positions[ i ][ _cluster_id ][ j ], cluster_root,  _cluster_normalization[ parseContext.cluster_positions[ i ][ _cluster_id ][ j ] ] );
                                }
                                cube::services::gather_children( subtrees, cluster_root );
                                cube::services::merge_trees( subtrees, iteration_cnode, &cube, &_cluster_normalization, &( parseContext.cluster_positions[ i ][ _cluster_id ] ) );
                            }
                            cube.get_operation_progress()->progress_step( 0.2 + ( ( i * 0.8 ) / parseContext.number_of_iterations ), "Create iterations" );
                        }
                        cube.get_operation_progress()->finish_step( "Declustering is done" );
                    }
                    cube.get_operation_progress()->progress_step( 0.4, "Finished parsing program dimension" );
                }
                break;

            case 142:
/* Line 670 of lalr1.cc  */
#line 1445 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    //check for the attributes
                    if ( !parseContext.idSeen )
                    {
                        error( cubeparserloc, "Missing id attribute!" );
                    }
                    else
                    {
                        parseContext.idSeen = false;
                    }
                    if ( !parseContext.modSeen )
                    {
                        parseContext.mod = "";
                    }
                    else
                    {
                        parseContext.modSeen = false;
                    }
                    if ( !parseContext.beginSeen )
                    {
                        parseContext.beginln = -1;
                    }
                    else
                    {
                        parseContext.beginSeen = false;
                    }
                    if ( !parseContext.endSeen )
                    {
                        parseContext.endln = -1;
                    }
                    else
                    {
                        parseContext.endSeen = false;
                    }
                    if ( !parseContext.paradigmSeen )
                    {
                        parseContext.paradigm = "unknown";
                    }
                    else
                    {
                        parseContext.paradigmSeen = false;
                    }
                    if ( !parseContext.roleSeen )
                    {
                        parseContext.role = "unknown";
                    }
                    else
                    {
                        parseContext.roleSeen = false;
                    }
                    //check for tags
                    if ( parseContext.nameSeen )
                    {
                        parseContext.nameSeen = false;
                    }
                    else
                    {
                        parseContext.name = "";
                    }
                    if ( parseContext.mangledNameSeen )
                    {
                        parseContext.mangledNameSeen = false;
                    }
                    else
                    {
                        parseContext.mangled_name = parseContext.name;
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

                    while ( ( int )parseContext.regionVec.size() <= parseContext.id )
                    {
                        parseContext.regionVec.push_back( NULL );
                    }
                    if ( parseContext.regionVec[ parseContext.id ] != NULL )
                    {
                        error( cubeparserloc, "Re-declared region!" );
                    }

                    cube::Region* _region =
                        cube.def_region(
                            cube::services::escapeFromXML( parseContext.name ),
                            cube::services::escapeFromXML( parseContext.mangled_name ),
                            cube::services::escapeFromXML( parseContext.paradigm ),
                            cube::services::escapeFromXML( parseContext.role ),
                            parseContext.beginln,
                            parseContext.endln,
                            parseContext.url,
                            cube::services::escapeFromXML( parseContext.descr ),
                            cube::services::escapeFromXML( parseContext.mod ),
                            parseContext.id );
                    if ( parseContext.n_attributes.size() > 0 )
                    {
                        unsigned nattributes = parseContext.n_attributes.top();
                        parseContext.n_attributes.pop();

                        if ( nattributes > parseContext.attributes.size() )
                        {
                            error( cubeparserloc, "Number of saved attributes for region " + parseContext.name + " is more, than number of actual saved parameters." );
                        }
                        std::stack<std::pair<std::string, std::string> > reversed;
                        for ( unsigned i = 0; i < nattributes; ++i )
                        {
                            std::pair< std::string, std::string> attr = parseContext.attributes.top();
                            parseContext.attributes.pop();
                            reversed.push( attr );
                        }
                        for ( unsigned i = 0; i < nattributes; ++i )
                        {
                            std::pair< std::string, std::string> attr = reversed.top();
                            reversed.pop();
                            _region->def_attr( attr.first, attr.second );
                        }
                    }
                    parseContext.regionVec[ parseContext.id ] = _region;
                }
                break;

            case 162:
/* Line 670 of lalr1.cc  */
#line 1556 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( parseContext.n_attributes.size() > 0 )
                    {
                        unsigned nattributes = parseContext.n_attributes.top();
                        parseContext.n_attributes.pop();

                        if ( nattributes > parseContext.attributes.size() )
                        {
                            error( cubeparserloc, "Number of saved attributes for cnode is more, than number of actual saved parameters." );
                        }
                        std::stack<std::pair<std::string, std::string> > reversed;
                        for ( unsigned i = 0; i < nattributes; ++i )
                        {
                            std::pair< std::string, std::string> attr = parseContext.attributes.top();
                            parseContext.attributes.pop();
                            reversed.push( attr );
                        }
                        for ( unsigned i = 0; i < nattributes; ++i )
                        {
                            std::pair< std::string, std::string> attr = reversed.top();
                            reversed.pop();
                            parseContext.currentCnode->def_attr( attr.first, attr.second );
                        }
                    }


                    if ( !clustering_on )
                    {
                        if ( parseContext.currentCnode == NULL )
                        {
                            error( cubeparserloc, "Cnode definitions are not correctly nested!" );
                        }


                        if ( !parseContext.n_cnode_num_parameters.empty()  )
                        {
                            unsigned nparameters = parseContext.n_cnode_num_parameters.top();
                            parseContext.n_cnode_num_parameters.pop();

                            if ( nparameters > parseContext.cnode_num_parameters.size() )
                            {
                                error( cubeparserloc, "Number of saved numeric parameters for current cnode is more, than number of actual saved parameters." );
                            }
                            std::stack<std::pair<std::string, std::string> > reversed;
                            for ( unsigned i = 0; i < nparameters; ++i )
                            {
                                std::pair< std::string, std::string> param = parseContext.cnode_num_parameters.top();

                                parseContext.cnode_num_parameters.pop();
                                reversed.push( param );
                            }
                            for ( unsigned i = 0; i < nparameters; ++i )
                            {
                                std::pair< std::string, std::string> param = reversed.top();
                                reversed.pop();

                                double d_value = atof( param.second.data() );
                                parseContext.currentCnode->add_num_parameter( param.first, d_value );
                            }
                        }
                        if ( !parseContext.n_cnode_str_parameters.empty()  )
                        {
                            unsigned nparameters = parseContext.n_cnode_str_parameters.top();
                            parseContext.n_cnode_str_parameters.pop();

                            if ( nparameters > parseContext.cnode_str_parameters.size() )
                            {
                                error( cubeparserloc, "Number of saved string parameters for current cnode is more, than number of actual saved parameters." );
                            }
                            std::stack<std::pair<std::string, std::string> > reversed;
                            for ( unsigned i = 0; i < nparameters; ++i )
                            {
                                std::pair< std::string, std::string> param = parseContext.cnode_str_parameters.top();
                                parseContext.cnode_str_parameters.pop();
                                reversed.push( param );
                            }
                            for ( unsigned i = 0; i < nparameters; ++i )
                            {
                                std::pair< std::string, std::string> param = reversed.top();
                                reversed.pop();
                                parseContext.currentCnode->add_str_parameter( param.first, param.second );
                            }
                        }

                        parseContext.currentCnode =
                            parseContext.currentCnode->get_parent();
                        parseContext.start_parse_clusters = false;
                    }
                    else
                    {
                        if ( parseContext.clusterCurrentCnode == NULL )
                        {
                            error( cubeparserloc, "Cluster cnode definitions are not correctly nested!" );
                        }


                        if ( !parseContext.n_cnode_num_parameters.empty()  )
                        {
                            unsigned nparameters = parseContext.n_cnode_num_parameters.top();
                            parseContext.n_cnode_num_parameters.pop();

                            if ( nparameters > parseContext.cnode_num_parameters.size() )
                            {
                                error( cubeparserloc, "Number of saved numeric parameters for current cnode is more, than number of actual saved parameters." );
                            }
                            std::stack<std::pair<std::string, std::string> > reversed;
                            for ( unsigned i = 0; i < nparameters; ++i )
                            {
                                std::pair< std::string, std::string> param = parseContext.cnode_num_parameters.top();

                                parseContext.cnode_num_parameters.pop();
                                reversed.push( param );
                            }
                            for ( unsigned i = 0; i < nparameters; ++i )
                            {
                                std::pair< std::string, std::string> param = reversed.top();
                                reversed.pop();

                                double d_value = atof( param.second.data() );
                                parseContext.clusterCurrentCnode->add_num_parameter( param.first, d_value );
                            }
                        }
                        if ( !parseContext.n_cnode_str_parameters.empty()  )
                        {
                            unsigned nparameters = parseContext.n_cnode_str_parameters.top();
                            parseContext.n_cnode_str_parameters.pop();

                            if ( nparameters > parseContext.cnode_str_parameters.size() )
                            {
                                error( cubeparserloc, "Number of saved string parameters for current cnode is more, than number of actual saved parameters." );
                            }
                            std::stack<std::pair<std::string, std::string> > reversed;
                            for ( unsigned i = 0; i < nparameters; ++i )
                            {
                                std::pair< std::string, std::string> param = parseContext.cnode_str_parameters.top();
                                parseContext.cnode_str_parameters.pop();
                                reversed.push( param );
                            }
                            for ( unsigned i = 0; i < nparameters; ++i )
                            {
                                std::pair< std::string, std::string> param = reversed.top();
                                reversed.pop();
                                parseContext.clusterCurrentCnode->add_str_parameter( param.first, param.second );
                            }
                        }

                        parseContext.clusterCurrentCnode =
                            parseContext.clusterCurrentCnode->get_parent();
                        if ( parseContext.clusterCurrentCnode == NULL )
                        {
                            parseContext.parse_clusters = false;
                        }
                    }
                }
                break;

            case 163:
/* Line 670 of lalr1.cc  */
#line 1713 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    //check for the attributes
                    if ( !parseContext.idSeen )
                    {
                        error( cubeparserloc, "Missing id attribute in cnode definition!" );
                    }
                    else
                    {
                        parseContext.idSeen = false;
                    }
                    if ( !parseContext.calleeidSeen )
                    {
                        error( cubeparserloc, "Missing callee id attribute in cnode definition!" );
                    }
                    else
                    {
                        parseContext.calleeidSeen = false;
                    }
                    if ( !parseContext.lineSeen )
                    {
                        parseContext.line = -1;
                    }
                    else
                    {
                        parseContext.lineSeen = false;
                    }
                    if ( !parseContext.modSeen )
                    {
                        parseContext.mod = "";
                    }
                    else
                    {
                        parseContext.modSeen = false;
                    }
                    //check if the region is defined
                    if ( ( int )parseContext.regionVec.size() <= parseContext.calleeid )
                    {
                        error( cubeparserloc, "Undefined region in cnode definition!" );
                    }
                    if ( parseContext.regionVec[ parseContext.calleeid ] == NULL )
                    {
                        error( cubeparserloc, "Undefined region in cnode definition!" );
                    }
                    //extend the cnode vector if necessary
                    while ( ( int )parseContext.cnodeVec.size() <= parseContext.id )
                    {
                        parseContext.cnodeVec.push_back( NULL );
                    }
                    if ( parseContext.cnodeVec[ parseContext.id ] != NULL )
                    {
                        error( cubeparserloc, "Re-declared cnode!" );
                    }
                    //define the cnode

                    parseContext.cnodeParTypeSeen  = false;
                    parseContext.cnodeParKeySeen   = false;
                    parseContext.cnodeParValueSeen = false;

                    if ( clustering_on )
                    {
                        parseContext.clusterCurrentCnode = new cube::Cnode( parseContext.regionVec[ parseContext.calleeid ],
                                                                            cube::services::escapeFromXML( parseContext.mod ),
                                                                            parseContext.line,
                                                                            parseContext.clusterCurrentCnode,
                                                                            parseContext.id );
                        if ( parseContext.clusterCurrentCnode->get_parent() == NULL ) // store root call path for cluster in a vector.
                        {
                            parseContext.original_tree_roots.push_back( parseContext.clusterCurrentCnode );
                        }
                    }
                    else
                    {
                        parseContext.currentCnode = cube.def_cnode(
                            parseContext.regionVec[ parseContext.calleeid ],
                            cube::services::escapeFromXML( parseContext.mod ),
                            parseContext.line,
                            parseContext.currentCnode,
                            parseContext.id );

                        parseContext.cnodeVec[ parseContext.id ] =
                            parseContext.currentCnode;
                    }
                }
                break;

            case 174:
/* Line 670 of lalr1.cc  */
#line 1798 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    cube.get_operation_progress()->start_step( 0., 1. );
                }
                break;

            case 175:
/* Line 670 of lalr1.cc  */
#line 1802 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    cube.get_operation_progress()->finish_step( "Finished parsing system tree" );
                    if ( parseContext.systemtreeTitle != "" )
                    {
                        cube.set_systemtree_title( cube::services::escapeFromXML( parseContext.systemtreeTitle ) );
                    }

                    // at this moment all dimensionis are loadeed -> we can initialize containers
                    cube.initialize();
                }
                break;

            case 180:
/* Line 670 of lalr1.cc  */
#line 1827 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    cube.get_operation_progress()->start_step( 0.7, 1. );
                    cube.get_operation_progress()->progress_step( "Start parsing system tree" );
                }
                break;

            case 181:
/* Line 670 of lalr1.cc  */
#line 1831 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    //check for attributes
                    parseContext.idSeen = false;
                    //check for tags
                    parseContext.nameSeen = false;
                    if ( !parseContext.classSeen )
                    {
                        error( cubeparserloc, "No class of system tree node declared." );
                    }
                    parseContext.classSeen = false;
                    if ( parseContext.descrSeen )
                    {
                        parseContext.descrSeen = false;
                    }
                    else
                    {
                        parseContext.descr = "";
                    }

                    cube::SystemTreeNode* _stn = cube.def_system_tree_node(
                        cube::services::escapeFromXML( parseContext.name ),
                        cube::services::escapeFromXML( parseContext.descr ),
                        cube::services::escapeFromXML( parseContext.stn_class ),
                        ( parseContext.currentSystemTreeNode.size() == 0 ) ? NULL : parseContext.currentSystemTreeNode.top() );
                    if ( parseContext.n_attributes.size() > 0 )
                    {
                        unsigned nattributes = parseContext.n_attributes.top();
                        parseContext.n_attributes.pop();

                        if ( nattributes > parseContext.attributes.size() )
                        {
                            error( cubeparserloc, "Number of saved attributes for metric " + parseContext.uniq_name + " is more, than number of actual saved parameters." );
                        }
                        std::stack<std::pair<std::string, std::string> > reversed;
                        for ( unsigned i = 0; i < nattributes; ++i )
                        {
                            std::pair< std::string, std::string> attr = parseContext.attributes.top();
                            parseContext.attributes.pop();
                            reversed.push( attr );
                        }
                        for ( unsigned i = 0; i < nattributes; ++i )
                        {
                            std::pair< std::string, std::string> attr = reversed.top();
                            reversed.pop();
                            _stn->def_attr( attr.first, attr.second );
                        }
                    }


                    parseContext.currentSystemTreeNode.push( _stn );
                    while ( ( unsigned int )parseContext.stnVec.size() <= _stn->get_id() )
                    {
                        parseContext.stnVec.push_back( NULL );
                    }
                    if ( parseContext.stnVec[ _stn->get_id() ] != NULL )
                    {
                        error( cubeparserloc, "Re-declared system tree node!" );
                    }
                    parseContext.stnVec[ _stn->get_id() ] = _stn;


                    std::string _step = "Created system tree node " + cube::services::escapeFromXML( parseContext.name );

                    cube.get_operation_progress()->progress_step(  _step );
                }
                break;

            case 182:
/* Line 670 of lalr1.cc  */
#line 1889 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    parseContext.currentSystemTreeNode.pop();
                    //check for attributes
                    parseContext.idSeen = false;
                    //check for tags
                    parseContext.nameSeen = false;
                    if ( parseContext.descrSeen )
                    {
                        parseContext.descrSeen = false;
                    }
                    else
                    {
                        parseContext.descr = "";
                    }
                    cube.get_operation_progress()->finish_step( "Finished parsing system tree" );
                }
                break;

            case 189:
/* Line 670 of lalr1.cc  */
#line 1925 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    //check for attributes
                    parseContext.idSeen = false;
                    //check for tags
                    parseContext.nameSeen = false;
                    parseContext.rankSeen = false;
                    if ( !parseContext.typeSeen )
                    {
                        error( cubeparserloc, "No type of location group declared." );
                    }
                    parseContext.typeSeen = false;

                    if ( parseContext.descrSeen )
                    {
                        parseContext.descrSeen = false;
                    }
                    else
                    {
                        parseContext.descr = "";
                    }

                    parseContext.currentLocationGroup = cube.def_location_group(
                        cube::services::escapeFromXML( parseContext.name ),
                        parseContext.rank,
                        cube::LocationGroup::getLocationGroupType( cube::services::escapeFromXML( parseContext.type ) ),
                        parseContext.currentSystemTreeNode.top() );
                    if ( parseContext.n_attributes.size() > 0 )
                    {
                        unsigned nattributes = parseContext.n_attributes.top();
                        parseContext.n_attributes.pop();

                        if ( nattributes > parseContext.attributes.size() )
                        {
                            error( cubeparserloc, "Number of saved attributes for location group " + parseContext.name + " is more, than number of actual saved parameters." );
                        }
                        std::stack<std::pair<std::string, std::string> > reversed;
                        for ( unsigned i = 0; i < nattributes; ++i )
                        {
                            std::pair< std::string, std::string> attr = parseContext.attributes.top();
                            parseContext.attributes.pop();
                            reversed.push( attr );
                        }
                        for ( unsigned i = 0; i < nattributes; ++i )
                        {
                            std::pair< std::string, std::string> attr = reversed.top();
                            reversed.pop();
                            parseContext.currentLocationGroup->def_attr( attr.first, attr.second );
                        }
                    }


                    while ( ( unsigned int )parseContext.locGroup.size() <= parseContext.currentLocationGroup->get_id() )
                    {
                        parseContext.locGroup.push_back( NULL );
                    }
                    if ( parseContext.locGroup[ parseContext.currentLocationGroup->get_id() ] != NULL )
                    {
                        error( cubeparserloc, "Re-declared location group!" );
                    }
                    parseContext.locGroup[ parseContext.currentLocationGroup->get_id() ] = parseContext.currentLocationGroup;

                    std::string _step =  "Created location group " + cube::services::escapeFromXML( parseContext.name );
                    cube.get_operation_progress()->progress_step( _step );
                }
                break;

            case 197:
/* Line 670 of lalr1.cc  */
#line 1999 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    //check for attributes
                    parseContext.idSeen = false;
                    //check for tags
                    parseContext.nameSeen = false;
                    parseContext.rankSeen = false;

                    if ( !parseContext.typeSeen )
                    {
                        error( cubeparserloc, "No type of location group declared." );
                    }
                    parseContext.typeSeen        = false;
                    parseContext.currentLocation = cube.def_location(
                        cube::services::escapeFromXML( parseContext.name ),
                        parseContext.rank,
                        cube::Location::getLocationType( cube::services::escapeFromXML( parseContext.type ) ),
                        parseContext.currentLocationGroup,
                        parseContext.id );
                    if ( parseContext.n_attributes.size() > 0 )
                    {
                        unsigned nattributes = parseContext.n_attributes.top();
                        parseContext.n_attributes.pop();

                        if ( nattributes > parseContext.attributes.size() )
                        {
                            error( cubeparserloc, "Number of saved attributes for location " + parseContext.name + " is more, than number of actual saved parameters." );
                        }
                        std::stack<std::pair<std::string, std::string> > reversed;
                        for ( unsigned i = 0; i < nattributes; ++i )
                        {
                            std::pair< std::string, std::string> attr = parseContext.attributes.top();
                            parseContext.attributes.pop();
                            reversed.push( attr );
                        }
                        for ( unsigned i = 0; i < nattributes; ++i )
                        {
                            std::pair< std::string, std::string> attr = reversed.top();
                            reversed.pop();
                            parseContext.currentLocation->def_attr( attr.first, attr.second );
                        }
                    }

                    while ( ( unsigned int )parseContext.locVec.size() <= parseContext.currentLocation->get_id() )
                    {
                        parseContext.locVec.push_back( NULL );
                    }
                    if ( parseContext.locVec[ parseContext.currentLocation->get_id() ] != NULL )
                    {
                        error( cubeparserloc, "Re-declared location!" );
                    }
                    parseContext.locVec[ parseContext.currentLocation->get_id() ] = parseContext.currentLocation;
                    if ( parseContext.currentLocation->get_id() % 1024 == 0 )
                    {
                        std::string _step =  "Created location " + cube::services::escapeFromXML( parseContext.name );
                        cube.get_operation_progress()->progress_step( _step );
                    }
                }
                break;

            case 200:
/* Line 670 of lalr1.cc  */
#line 2061 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    //check for attributes
                    parseContext.idSeen = false;
                    //check for tags
                    parseContext.nameSeen = false;
                    if ( parseContext.descrSeen )
                    {
                        parseContext.descrSeen = false;
                    }
                    else
                    {
                        parseContext.descr = "";
                    }

                    parseContext.currentMachine = cube.def_mach(
                        cube::services::escapeFromXML( parseContext.name ),
                        cube::services::escapeFromXML( parseContext.descr ) );
                    while ( ( unsigned int )parseContext.stnVec.size() <= parseContext.currentMachine->get_id() )
                    {
                        parseContext.stnVec.push_back( NULL );
                    }
                    if ( parseContext.stnVec[ parseContext.currentMachine->get_id() ] != NULL )
                    {
                        error( cubeparserloc, "Re-declared machine!" );
                    }
                    parseContext.stnVec[ parseContext.currentMachine->get_id() ] = parseContext.currentMachine;
                }
                break;

            case 204:
/* Line 670 of lalr1.cc  */
#line 2086 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    //check for attributes
                    parseContext.idSeen = false;
                    //check for tags
                    parseContext.nameSeen = false;
                    if ( parseContext.descrSeen )
                    {
                        parseContext.descrSeen = false;
                    }
                    else
                    {
                        parseContext.descr = "";
                    }

                    parseContext.currentNode = cube.def_node(
                        cube::services::escapeFromXML( parseContext.name ),
                        parseContext.currentMachine );
                    while ( ( unsigned int )parseContext.stnVec.size() <= parseContext.currentNode->get_id() )
                    {
                        parseContext.stnVec.push_back( NULL );
                    }
                    if ( parseContext.stnVec[ parseContext.currentNode->get_id() ] != NULL )
                    {
                        error( cubeparserloc, "Re-declared node!" );
                    }
                    parseContext.stnVec[ parseContext.currentNode->get_id() ] = parseContext.currentNode;
                }
                break;

            case 208:
/* Line 670 of lalr1.cc  */
#line 2111 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    //check for attributes
                    parseContext.idSeen = false;
                    //check for tags
                    if ( parseContext.nameSeen )
                    {
                        parseContext.nameSeen = false;
                    }
                    else
                    {
                        parseContext.name = "";
                    }
                    if ( parseContext.rankSeen )
                    {
                        parseContext.rankSeen = false;
                    }
                    else
                    {
                        parseContext.rank = 0;
                    }

                    std::ostringstream name;
                    if ( parseContext.name.empty() )
                    {
                        name << "Process " << parseContext.rank;
                    }
                    else
                    {
                        name << parseContext.name;
                    }
                    parseContext.currentProc = cube.def_proc(
                        cube::services::escapeFromXML( name.str() ),
                        parseContext.rank,
                        parseContext.currentNode );
                    while ( ( unsigned int )parseContext.locGroup.size() <= parseContext.currentProc->get_id() )
                    {
                        parseContext.locGroup.push_back( NULL );
                    }
                    if ( parseContext.locGroup[ parseContext.currentProc->get_id() ] != NULL )
                    {
                        error( cubeparserloc, "Re-declared process!" );
                    }
                    parseContext.locGroup[ parseContext.currentProc->get_id() ] = parseContext.currentProc;
                }
                break;

            case 216:
/* Line 670 of lalr1.cc  */
#line 2153 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    //check for attributes
                    parseContext.idSeen = false;
                    //check for tags
                    if ( parseContext.nameSeen )
                    {
                        parseContext.nameSeen = false;
                    }
                    else
                    {
                        parseContext.name = "";
                    }
                    if ( parseContext.rankSeen )
                    {
                        parseContext.rankSeen = false;
                    }
                    else
                    {
                        parseContext.rank = 0;
                    }

                    std::ostringstream name;
                    if ( parseContext.name.empty() )
                    {
                        name << "Thread " << parseContext.rank;
                    }
                    else
                    {
                        name << parseContext.name;
                    }


                    parseContext.currentThread = cube.def_thrd(
                        cube::services::escapeFromXML( name.str() ),
                        parseContext.rank,
                        parseContext.currentProc,
                        parseContext.id );
                    while ( ( unsigned int )parseContext.locVec.size() <= parseContext.currentThread->get_id() )
                    {
                        parseContext.locVec.push_back( NULL );
                    }
                    if ( parseContext.locVec[ parseContext.currentThread->get_id() ] != NULL )
                    {
                        error( cubeparserloc, "Re-declared thread!" );
                    }
                    parseContext.locVec[ parseContext.currentThread->get_id() ] = parseContext.currentThread;
                }
                break;

            case 219:
/* Line 670 of lalr1.cc  */
#line 2188 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( !parseContext.checkThreadIds() )
                    {
                        error( cubeparserloc, "Thread ids must cover an interval [0,n] without gap!" );
                    }
                }
                break;

            case 227:
/* Line 670 of lalr1.cc  */
#line 2210 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    //check for attributes
                    parseContext.ndimsSeen = false;

                    if ( parseContext.ndims != ( int )parseContext.dimVec.size() )
                    {
                        error( cubeparserloc, "Too few or too many topology dimensions are declared!" );
                    }
                    parseContext.currentCart = cube.def_cart(
                        parseContext.ndims,
                        parseContext.dimVec,
                        parseContext.periodicVec );

                    if ( parseContext.cartNameSeen )
                    {
                        ( parseContext.currentCart )->set_name( cube::services::escapeFromXML( parseContext.cartName ) );
                        parseContext.cartNameSeen = false;
                    }
                    if ( parseContext.dimNamesCount > 0 )
                    {
                        parseContext.dimNamesCount = 0;
                        ( parseContext.currentCart )->set_namedims( parseContext.dimNameVec );
                    }
                    parseContext.dimNameVec.clear();
                }
                break;

            case 229:
/* Line 670 of lalr1.cc  */
#line 2237 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                { parseContext.dimVec.clear();
                  parseContext.periodicVec.clear();
                  parseContext.cartNameSeen = false;
                }
                break;

            case 232:
/* Line 670 of lalr1.cc  */
#line 2249 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    //check for attributes
                    if ( !parseContext.sizeSeen )
                    {
                        error( cubeparserloc, "Missing size attribute!" );
                    }
                    else
                    {
                        parseContext.sizeSeen = false;
                    }
                    if ( !parseContext.periodicSeen )
                    {
                        error( cubeparserloc, "Missing periodic attribute!" );
                    }
                    else
                    {
                        parseContext.periodicSeen = false;
                    }
                    if ( parseContext.dimNameSeen )
                    {
                        parseContext.dimNameVec.push_back( parseContext.dimName );
                    }
                    else
                    {
                        parseContext.dimNameVec.push_back( "" );
                    }
                    parseContext.dimNameSeen = false;
                }
                break;

            case 247:
/* Line 670 of lalr1.cc  */
#line 2297 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    //check for attributes
                    parseContext.locidSeen = false;

                    if ( parseContext.dimVec.size() != parseContext.longValues.size() )
                    {
                        error( cubeparserloc, "Too few or too many dimension coordinates in coord tag!" );
                    }
                    for ( unsigned i = 0; i < parseContext.dimVec.size(); ++i )
                    {
                        if ( parseContext.longValues[ i ] >= parseContext.dimVec[ i ] )
                        {
                            error( cubeparserloc, "Topology coordinate is out of range!" );
                        }
                    }
                    if ( parseContext.locid >= ( int )parseContext.locVec.size() )
                    {
                        error( cubeparserloc, "Location of the topology coordinates wasn't declared!" );
                    }
                    if ( parseContext.locVec[ parseContext.locid ] == NULL )
                    {
                        error( cubeparserloc, "Location of the topology coordinates wasn't declared!" );
                    }
                    cube.def_coords( parseContext.currentCart,
                                     ( cube::Sysres* )( parseContext.locVec[ parseContext.locid ] ),
                                     parseContext.longValues );
                }
                break;

            case 248:
/* Line 670 of lalr1.cc  */
#line 2318 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    //check for attributes
                    parseContext.lgidSeen = false;

                    if ( parseContext.dimVec.size() != parseContext.longValues.size() )
                    {
                        error( cubeparserloc, "Too few or too many dimension coordinates in coord tag!" );
                    }
                    for ( unsigned i = 0; i < parseContext.dimVec.size(); ++i )
                    {
                        if ( parseContext.longValues[ i ] >= parseContext.dimVec[ i ] )
                        {
                            error( cubeparserloc, "Topology coordinate is out of range!" );
                        }
                    }
                    if ( parseContext.lgid >= ( int )parseContext.locGroup.size() )
                    {
                        error( cubeparserloc, "Location group of the topology coordinates wasn't declared!" );
                    }
                    if ( parseContext.locGroup[ parseContext.lgid ] == NULL )
                    {
                        error( cubeparserloc, "Location group of the topology coordinates wasn't declared!" );
                    }
                    cube.def_coords( parseContext.currentCart,
                                     ( cube::Sysres* )( parseContext.locGroup[ parseContext.lgid ] ),
                                     parseContext.longValues );
                }
                break;

            case 249:
/* Line 670 of lalr1.cc  */
#line 2339 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    //check for attributes
                    parseContext.stnidSeen = false;

                    if ( parseContext.dimVec.size() != parseContext.longValues.size() )
                    {
                        error( cubeparserloc, "Too few or too many dimension coordinates in coord tag!" );
                    }
                    for ( unsigned i = 0; i < parseContext.dimVec.size(); ++i )
                    {
                        if ( parseContext.longValues[ i ] >= parseContext.dimVec[ i ] )
                        {
                            error( cubeparserloc, "Topology coordinate is out of range!" );
                        }
                    }
                    if ( parseContext.stnid >= ( int )parseContext.stnVec.size() )
                    {
                        error( cubeparserloc, "System tree node of the topology coordinates wasn't declared!" );
                    }
                    if ( parseContext.nodeVec[ parseContext.stnid ] == NULL )
                    {
                        error( cubeparserloc, "System tree node of the topology coordinates wasn't declared!" );
                    }
                    cube.def_coords( parseContext.currentCart,
                                     ( cube::Sysres* )( parseContext.nodeVec[ parseContext.stnid ] ),
                                     parseContext.longValues );
                }
                break;

            case 250:
/* Line 670 of lalr1.cc  */
#line 2361 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    //check for attributes
                    parseContext.locidSeen = false;

                    if ( parseContext.dimVec.size() != parseContext.longValues.size() )
                    {
                        error( cubeparserloc, "Too few or too many dimension coordinates in coord tag!" );
                    }
                    for ( unsigned i = 0; i < parseContext.dimVec.size(); ++i )
                    {
                        if ( parseContext.longValues[ i ] >= parseContext.dimVec[ i ] )
                        {
                            error( cubeparserloc, "Topology coordinate is out of range!" );
                        }
                    }
                    if ( parseContext.thrdid >= ( int )parseContext.locVec.size() )
                    {
                        error( cubeparserloc, "Thread of the topology coordinates wasn't declared!" );
                    }
                    if ( parseContext.locVec[ parseContext.thrdid ] == NULL )
                    {
                        error( cubeparserloc, "Thread of the topology coordinates wasn't declared!" );
                    }
                    cube.def_coords( parseContext.currentCart,
                                     ( cube::Sysres* )( parseContext.locVec[ parseContext.thrdid ] ),
                                     parseContext.longValues );
                }
                break;

            case 251:
/* Line 670 of lalr1.cc  */
#line 2382 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    //check for attributes
                    parseContext.lgidSeen = false;

                    if ( parseContext.dimVec.size() != parseContext.longValues.size() )
                    {
                        error( cubeparserloc, "Too few or too many dimension coordinates in coord tag!" );
                    }
                    for ( unsigned i = 0; i < parseContext.dimVec.size(); ++i )
                    {
                        if ( parseContext.longValues[ i ] >= parseContext.dimVec[ i ] )
                        {
                            error( cubeparserloc, "Topology coordinate is out of range!" );
                        }
                    }
                    if ( parseContext.procid >= ( int )parseContext.locGroup.size() )
                    {
                        error( cubeparserloc, "Process of the topology coordinates wasn't declared!" );
                    }
                    if ( parseContext.locGroup[ parseContext.procid ] == NULL )
                    {
                        error( cubeparserloc, "Process of the topology coordinates wasn't declared!" );
                    }
                    cube.def_coords( parseContext.currentCart,
                                     ( cube::Sysres* )( parseContext.locGroup[ parseContext.procid ] ),
                                     parseContext.longValues );
                }
                break;

            case 252:
/* Line 670 of lalr1.cc  */
#line 2403 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    //check for attributes
                    parseContext.stnidSeen = false;

                    if ( parseContext.dimVec.size() != parseContext.longValues.size() )
                    {
                        error( cubeparserloc, "Too few or too many dimension coordinates in coord tag!" );
                    }
                    for ( unsigned i = 0; i < parseContext.dimVec.size(); ++i )
                    {
                        if ( parseContext.longValues[ i ] >= parseContext.dimVec[ i ] )
                        {
                            error( cubeparserloc, "Topology coordinate is out of range!" );
                        }
                    }

                    if ( parseContext.nodeid >= ( int )cube.get_non_root_stnv().size() )
                    {
                        error( cubeparserloc, "Node of the topology coordinates wasn't declared!" );
                    }
                    if ( cube.get_non_root_stnv().at( parseContext.nodeid ) == NULL )
                    {
                        error( cubeparserloc, "Node of the topology coordinates wasn't declared!" );
                    }
                    cube.def_coords( parseContext.currentCart,
                                     ( cube::Sysres* )( cube.get_non_root_stnv().at( parseContext.nodeid ) ),
                                     parseContext.longValues );
                }
                break;

            case 253:
/* Line 670 of lalr1.cc  */
#line 2425 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    //check for attributes
                    parseContext.stnidSeen = false;

                    if ( parseContext.dimVec.size() != parseContext.longValues.size() )
                    {
                        error( cubeparserloc, "Too few or too many dimension coordinates in coord tag!" );
                    }
                    for ( unsigned i = 0; i < parseContext.dimVec.size(); ++i )
                    {
                        if ( parseContext.longValues[ i ] >= parseContext.dimVec[ i ] )
                        {
                            error( cubeparserloc, "Topology coordinate is out of range!" );
                        }
                    }
                    if ( parseContext.machid >= ( int )cube.get_root_stnv().size() )
                    {
                        error( cubeparserloc, "Machine of the topology coordinates wasn't declared!" );
                    }
                    if ( cube.get_root_stnv().at( parseContext.nodeid ) == NULL )
                    {
                        error( cubeparserloc, "Machine of the topology coordinates wasn't declared!" );
                    }
                    cube.def_coords( parseContext.currentCart,
                                     ( cube::Sysres* )( cube.get_root_stnv().at( parseContext.machid ) ),
                                     parseContext.longValues );
                }
                break;

            case 256:
/* Line 670 of lalr1.cc  */
#line 2452 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
// if (parseContext.dynamicMetricLoading) return 0;
                    std::string _step = "Start reading data";
                    cube.get_operation_progress()->progress_step( _step );
                }
                break;

            case 257:
/* Line 670 of lalr1.cc  */
#line 2457 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    cube.get_operation_progress()->finish_step( "Finished reading data" );
                }
                break;

            case 260:
/* Line 670 of lalr1.cc  */
#line 2469 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    //check for attributes
                    parseContext.metricidSeen = false;

                    if ( ( int )parseContext.metricVec.size() <= parseContext.metricid )
                    {
                        error( cubeparserloc, "Metric of the severity matrix wasn't declared!" );
                    }
                    if ( parseContext.metricVec[ parseContext.metricid ] == NULL )
                    {
                        error( cubeparserloc, "Metric of the severity matrix wasn't declared!" );
                    }
                    parseContext.currentMetric =
                        parseContext.metricVec[ parseContext.metricid ];

                    parseContext.ignoreMetric = false;
                    cube::Metric* metric = parseContext.currentMetric;
                    while ( metric != NULL )
                    {
                        if ( metric->get_val() == "VOID" )
                        {
                            parseContext.ignoreMetric = true;
                            break;
                        }
                        metric = metric->get_parent();
                    }
                }
                break;

            case 266:
/* Line 670 of lalr1.cc  */
#line 2502 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    //check for attributes
                    parseContext.cnodeidSeen = false;

                    if ( !parseContext.ignoreMetric )
                    {
                        if ( ( int )parseContext.cnodeVec.size() <= parseContext.cnodeid )
                        {
                            error( cubeparserloc, "Cnode of the severity row wasn't declared!" );
                        }
                        if ( parseContext.cnodeVec[ parseContext.cnodeid ] == NULL )
                        {
                            error( cubeparserloc, "Cnode of the severity row wasn't declared!" );
                        }
                        parseContext.currentCnode =
                            parseContext.cnodeVec[ parseContext.cnodeid ];
                    }
                }
                break;

            case 267:
/* Line 670 of lalr1.cc  */
#line 2514 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
                {
                    if ( !parseContext.ignoreMetric )
                    {
                        std::vector<double>&        v = parseContext.realValues;
                        std::vector<cube::Thread*>& t = parseContext.locVec;
                        if ( v.size() > t.size() )
                        {
                            error( cubeparserloc, "Too many values in severity row!" );
                        }
                        std::vector<cube::Thread*> t_sorted = t;
                        sort( t_sorted.begin(), t_sorted.end(), &cube::IdentObject::id_compare );


                        cube::Metric* metric = parseContext.currentMetric;
                        cube::Cnode*  cnode  = parseContext.currentCnode;
                        for ( unsigned i = 0; i < v.size(); ++i )
                        {
                            cube.set_sev( metric,
                                          cnode,
                                          t_sorted[ i ],
                                          v[ i ] );
                        }
                    }
                }
                break;


/* Line 670 of lalr1.cc  */
#line 2672 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
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
Cube4Parser::yysyntax_error_( int yystate, int yytoken )
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
const short int Cube4Parser::yypact_ninf_ = -402;
const short int
Cube4Parser::yypact_[] =
{
    14,   1,     25,    107,   38,    45,    -402,  -402,  -9,    -402,
    -402, -402,  -402,  -402,  -402,  -402,  -402,  -402,  36,    -402,
    6,    -402,  -402,  -402,  -402,  -402,  -84,   29,    -402,  44,
    6,    -402,  10,    3,     90,    93,    -402,  -402,  -6,    -402,
    35,   49,    -402,  57,    -402,  -402,  10,    3,     3,     -402,
    54,   -402,  -402,  -402,  -402,  67,    -402,  108,   35,    -402,
    165,  161,   3,     54,    54,    61,    -402,  71,    -402,  -402,
    -402, -402,  149,   54,    71,    71,    171,   167,   66,    -402,
    -402, -402,  64,    7,     -402,  71,    -402,  -402,  -402,  -402,
    175,  172,   -402,  176,   -402,  21,    -402,  -402,  -402,  -402,
    -402, 150,   -402,  -13,   -40,   -402,  178,   180,   106,   128,
    -402, -402,  -402,  -402,  177,   21,    42,    150,   -402,  -402,
    64,   85,    151,   -402,  143,   -402,  58,    -402,  -402,  -402,
    -402, -402,  -402,  -402,  -402,  -1,    -402,  186,   187,   188,
    -402, -402,  -402,  -402,  4,     -402,  158,   -402,  64,    185,
    -402, 99,    -402,  -402,  -402,  191,   189,   91,    63,    170,
    65,   132,   133,   130,   134,   131,   126,   129,   -402,  -402,
    -402, -402,  -402,  -402,  -402,  -402,  -402,  -402,  -402,  -1,
    -402, -402,  -402,  -402,  -402,  0,     -402,  27,    -23,   -402,
    198,  124,   155,   -402,  -402,  -402,  100,   212,   206,   -402,
    79,   207,   -402,  -402,  -402,  -402,  -402,  -402,  -402,  -402,
    -402, -402,  -402,  135,   136,   137,   138,   -402,  -402,  -402,
    -402, -402,  -402,  -402,  183,   0,     -402,  215,   216,   -402,
    -402, -402,  -402,  -402,  -2,    116,   -402,  190,   -402,  124,
    142,  -402,  139,   155,   -402,  -72,   179,   221,   -402,  197,
    -402, -402,  -402,  200,   -402,  -402,  -402,  -402,  -402,  -402,
    -402, -402,  -402,  -402,  230,   127,   -402,  8,     144,   -402,
    -402, -402,  -402,  233,   234,   121,   -402,  235,   110,   194,
    179,  -402,  -402,  -402,  -402,  -402,  238,   140,   -402,  -402,
    -402, 157,   142,   202,   -402,  -402,  -402,  231,   247,   243,
    -402, -402,  -402,  249,   244,   -402,  -402,  64,    98,    -402,
    -29,  231,   -402,  -402,  -402,  -402,  -402,  245,   246,   -402,
    -402, 253,   254,   145,   -402,  -402,  -402,  -7,    -402,  -402,
    -402, 204,   -402,  -402,  124,   -402,  -402,  -402,  -402,  -402,
    -402, 103,   -402,  13,    142,   -402,  11,    64,    151,   222,
    -402, -402,  256,   258,   259,   261,   262,   263,   264,   260,
    265,  266,   267,   268,   269,   270,   -402,  -402,  -402,  -402,
    -402, -402,  -402,  -402,  271,   -402,  223,   -402,  -402,  -402,
    -402, -402,  -402,  -402,  211,   213,   214,   224,   225,   226,
    227,  124,   64,    115,   -402,  -402,  -402,  -402,  -402,  -402,
    -402, -402,  184,   -402,  -402,  272,   -402,  -402,  192,   193,
    248,  -43,   -402,  199,   245,   64,    123,   -402,  -402,  -402,
    -43,  -402,  -402,  245,   -402,  279,   -402,  -402,  239,   -402,
    -402, 124,   64,    117,   -402,  250,   283,   -402,  -402,  -402,
    -43,  -28,   -402
};

/* YYDEFACT[S] -- default reduction number in state S.  Performed when
   YYTABLE doesn't specify something else to do.  Zero means the
   default is an error.  */
const unsigned short int
Cube4Parser::yydefact_[] =
{
    0,   0,     0,     0,     0,     0,     75,    76,    0,     73,
    1,   78,    79,    80,    81,    82,    83,    84,    0,     71,
    0,   2,     3,     72,    74,    85,    0,     98,    105,   0,
    0,   90,    0,     0,     0,     0,     95,    96,    0,     93,
    101, 0,     99,    18,    77,    91,    0,     0,     0,     136,
    0,   4,     5,     92,    94,    0,     103,   0,     102,   97,
    0,   0,     0,     0,     0,     20,    174,   254,   50,    100,
    104, 19,    0,     0,     254,   254,   0,     0,     22,    256,
    89,  255,   111,   0,     107,   254,   87,    88,    21,    137,
    0,   0,     258,   0,     112,   113,   135,   106,   108,   109,
    86,  0,     23,    0,     0,     32,    0,     0,     0,     0,
    115, 116,   117,   118,   0,     113,   0,     138,   140,   180,
    0,   217,   177,   178,   176,   198,   0,     257,   259,   7,
    8,   10,    9,     12,    11,    119,   114,   0,     0,     0,
    157, 156,   158,   159,   0,     154,   0,     141,   0,     0,
    219, 0,     218,   179,   199,   0,     0,     0,     24,    0,
    0,   0,     0,     0,     0,     0,     0,     0,     123,   124,
    125, 126,   127,   128,   130,   131,   132,   129,   110,   120,
    121, 133,   6,     43,    44,    143,   155,   0,     164,   160,
    0,   0,     221,   175,   41,    260,   0,     0,     0,     60,
    0,   0,     26,    27,    28,    51,    52,    53,    54,    55,
    56,  62,    122,   0,     0,     0,     0,     151,   152,   147,
    148, 149,   150,   153,   0,     144,   145,   0,     0,     170,
    168, 171,   169,   172,   0,     0,     139,   164,   166,   0,
    57,  229,   0,     222,   223,   0,     262,   0,     25,    0,
    29,  30,    31,    0,     65,    66,    63,    64,    142,   146,
    45,  33,    163,   173,   0,     0,     165,   0,     0,     200,
    58,  220,   224,   0,     0,     0,     225,   0,     0,     0,
    263, 264,   134,   59,    61,    13,    0,     0,     162,   167,
    161, 0,     57,    0,     16,    46,    226,   0,     0,     0,
    261, 265,   14,    0,     0,     67,    183,   0,     0,     202,
    0,   227,   230,   42,    266,   15,    70,    181,   0,     201,
    203, 0,     0,     0,     235,   236,   237,   0,     233,   238,
    231, 0,     184,   187,   0,     17,    47,    48,    49,    232,
    234, 0,     267,   185,   57,    228,   0,     0,     186,   0,
    188, 204,   0,     0,     0,     0,     0,     0,     0,     0,
    0,   0,     0,     0,     0,     0,     239,   244,   245,   246,
    240, 241,   242,   243,   0,     182,   0,     34,    35,    36,
    37,  38,    39,    40,    0,     0,     0,     0,     0,     0,
    0,   0,     0,     0,     206,   247,   248,   249,   250,   251,
    252, 253,   0,     189,   191,   0,     205,   207,   0,     0,
    0,   0,     69,    0,     193,   0,     0,     195,   212,   213,
    208, 210,   68,    193,   192,   0,     190,   196,   0,     211,
    194, 0,     0,     0,     214,   0,     0,     209,   215,   197,
    0,   0,     216
};

/* YYPGOTO[NTERM-NUM].  */
const short int
Cube4Parser::yypgoto_[] =
{
    -402, -402,  -402,  141,   101,   -171,  -402,  -402,  -402,  -402,
    -402, -402,  -402,  -402,  -402,  -402,  -402,  -402,  -402,  -402,
    -402, -402,  -402,  -82,   -402,  -402,  -402,  -402,  -402,  -402,
    -402, -402,  -402,  -402,  -402,  -402,  -402,  24,    -402,  -402,
    242,  -402,  -402,  -402,  -402,  -402,  -168,  -282,  -402,  -402,
    -402, -126,  -184,  -402,  -402,  -402,  -402,  -402,  -106,  -402,
    -402, -402,  -402,  293,   -402,  -402,  -402,  -402,  273,   -402,
    274,  275,   -402,  -402,  -402,  -402,  5,     -402,  -402,  219,
    -402, 196,   -402,  -402,  -402,  125,   -183,  -402,  -26,   -402,
    -402, -402,  -402,  201,   -402,  -402,  81,    -402,  163,   -402,
    41,   72,    -402,  80,    -402,  39,    -402,  -402,  -30,   -119,
    -402, -402,  -402,  -402,  -402,  -402,  -402,  -116,  -402,  -107,
    -402, -99,   -402,  195,   -402,  -402,  12,    -402,  -402,  -71,
    -402, -117,  -401,  -402,  -112,  -402,  -402,  -402,  -402,  -402,
    -402, 82,    -402,  -402,  -402,  15,    -402,  -3,    -402,  -402,
    -402, -402,  -402,  -402,  -402,  -402,  -402,  -27,   -402,  -402,
    -402, -402,  -402,  -402,  -402,  47,    -402
};

/* YYDEFGOTO[NTERM-NUM].  */
const short int
Cube4Parser::yydefgoto_[] =
{
    -1,  6,     7,     36,    37,    140,   110,   111,   112,   113,
    265, 287,   304,   275,   324,   61,    77,    91,    198,   201,
    202, 203,   204,   141,   231,   359,   360,   361,   362,   363,
    364, 365,   156,   299,   142,   143,   232,   276,   325,   326,
    56,  168,   169,   170,   171,   172,   173,   269,   174,   175,
    176, 270,   418,   220,   221,   222,   292,   414,   419,   237,
    2,   3,     8,     9,     19,    20,    29,    30,    31,    38,
    39,  32,    41,    42,    57,    58,    33,    43,    83,    84,
    95,  114,   115,   178,   179,   180,   181,   99,    50,    65,
    101, 146,   117,   118,   224,   225,   226,   144,   145,   188,
    189, 238,   267,   233,   234,   67,    78,    121,   122,   123,
    148, 333,   317,   349,   343,   350,   410,   403,   404,   424,
    416, 417,   124,   125,   293,   308,   309,   376,   393,   394,
    428, 420,   421,   433,   434,   151,   152,   192,   242,   243,
    277, 244,   329,   245,   311,   312,   327,   328,   341,   366,
    367, 368,   369,   370,   371,   372,   373,   80,    81,    92,
    104, 128,   246,   279,   280,   281,   331
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF_, syntax error.  */
const signed char Cube4Parser::yytable_ninf_ = -1;
const unsigned short int
Cube4Parser::yytable_[] =
{
    94,  219,   223,   153,   339,   53,    23,    240,   262,   177,
    306, 157,   157,   126,   185,   235,   229,   217,   26,    429,
    157, 63,    64,    34,    442,   10,    119,   158,   1,     159,
    35,  160,   120,   82,    96,    47,    73,    48,    149,   273,
    429, 219,   223,   21,    187,   288,   215,   86,    87,    274,
    22,  62,    119,   177,   347,   268,   408,   217,   100,   218,
    25,  215,   351,   229,   127,   236,   190,   27,    161,   44,
    162, 408,   163,   28,    164,   97,    165,   28,    166,   166,
    167, 167,   321,   213,   289,   214,   250,   251,   252,   215,
    49,  216,   40,    322,   323,   51,    4,     5,     52,    218,
    55,  34,    74,    75,    321,   230,   4,     5,     35,    131,
    132, 59,    85,    93,    137,   322,   323,   227,   228,   93,
    137, 138,   139,   11,    12,    13,    14,    15,    16,    17,
    18,  133,   134,   68,    332,   352,   353,   354,   355,   356,
    357, 358,   93,    137,   319,   307,   227,   228,   337,   338,
    344, 66,    230,   106,   107,   108,   109,   93,    137,   138,
    139, 345,   346,   406,   392,   426,   415,   437,   432,   60,
    71,  72,    69,    76,    79,    82,    88,    89,    90,    93,
    102, 105,   103,   129,   116,   130,   150,   135,   120,   155,
    119, 182,   183,   184,   187,   191,   194,   193,   34,    195,
    197, 199,   205,   200,   207,   206,   210,   402,   239,   209,
    208, 211,   241,   215,   35,    248,   249,   253,   258,   254,
    260, 261,   255,   167,   264,   318,   283,   256,   235,   153,
    257, 423,   282,   284,   278,   285,   286,   291,   294,   295,
    423, 271,   274,   302,   310,   297,   298,   402,   300,   307,
    303, 305,   313,   314,   315,   316,   334,   157,   335,   336,
    342, 377,   375,   378,   379,   374,   380,   381,   382,   383,
    384, 395,   392,   396,   397,   385,   386,   387,   388,   389,
    390, 391,   411,   408,   398,   399,   400,   401,   413,   431,
    432, 415,   412,   440,   439,   422,   409,   247,   196,   296,
    70,  24,    98,    45,    212,   46,    259,   186,   290,   266,
    405, 136,   54,    348,   263,   435,   430,   427,   147,   154,
    320, 438,   407,   441,   340,   272,   330,   301,   0,     0,
    0,   0,     0,     425,   0,     0,     0,     0,     0,     0,
    0,   0,     0,     0,     0,     0,     0,     0,     0,     0,
    436
};

/* YYCHECK.  */
const short int
Cube4Parser::yycheck_[] =
{
    82,  185,   185,   122,   11,    11,    15,    191,   10,    135,
    292, 12,    12,    53,    10,    38,    187,   185,   12,    420,
    12,  47,    48,    107,   52,    0,     39,    28,    14,    30,
    114, 32,    45,    26,    27,    30,    62,    32,    120,   111,
    441, 225,   225,   5,     36,    37,    89,    74,    75,    121,
    5,   46,    39,    179,   41,    239,   99,    225,   85,    185,
    24,  89,    344,   234,   104,   88,    148,   61,    69,    25,
    71,  99,    73,    67,    75,    68,    77,    67,    79,    79,
    81,  81,    111,   83,    267,   85,    7,     8,     9,     89,
    87,  91,    63,    122,   123,   5,     105,   106,   5,     225,
    65,  107,   63,    64,    111,   187,   105,   106,   114,   3,
    4,   62,    73,    115,   116,   122,   123,   119,   120,   115,
    116, 117,   118,   16,    17,    18,    19,    20,    21,    22,
    23,  3,     4,     66,    317,   124,   125,   126,   127,   128,
    129, 130,   115,   116,   46,    47,    119,   120,   3,     4,
    334, 97,    234,   132,   133,   134,   135,   115,   116,   117,
    118, 58,    59,    48,    49,    42,    43,    50,    51,    112,
    5,   10,    64,    112,   103,   26,    5,     10,    112,   115,
    5,   5,     10,    5,     34,    5,     101,   10,    45,    131,
    39,  5,     5,     5,     36,    10,    5,     98,    107,   10,
    137, 31,    70,    138,   74,    72,    80,    391,   10,    78,
    76,  82,    57,    89,    114,   3,     10,    10,    35,    84,
    5,   5,     86,    81,    108,   307,   29,    90,    38,    348,
    92,  414,   11,    33,    55,    5,     109,   93,    5,     5,
    423, 102,   121,   5,     13,    10,    136,   431,   54,    47,
    110, 94,    5,     10,    5,     11,    10,    12,    5,     5,
    56,  5,     40,    5,     5,     347,   5,     5,     5,     5,
    10,  60,    49,    60,    60,    10,    10,    10,    10,    10,
    10,  10,    10,    99,    60,    60,    60,    60,    95,    10,
    51,  43,    100,   10,    44,    96,    402,   196,   157,   275,
    58,  8,     83,    30,    179,   30,    225,   144,   267,   237,
    392, 115,   38,    343,   234,   431,   423,   416,   117,   124,
    308, 433,   393,   440,   327,   243,   311,   280,   -1,    -1,
    -1,  -1,    -1,    415,   -1,    -1,    -1,    -1,    -1,    -1,
    -1,  -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    432
};

/* STOS_[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
const unsigned short int
Cube4Parser::yystos_[] =
{
    0,   14,    199,   200,   105,   106,   140,   141,   201,   202,
    0,   16,    17,    18,    19,    20,    21,    22,    23,    203,
    204, 5,     5,     15,    202,   24,    12,    61,    67,    205,
    206, 207,   210,   215,   107,   114,   142,   143,   208,   209,
    63,  211,   212,   216,   25,    207,   210,   215,   215,   87,
    227, 5,     5,     11,    209,   65,    179,   213,   214,   62,
    112, 154,   215,   227,   227,   228,   97,    244,   66,    64,
    179, 5,     10,    227,   244,   244,   112,   155,   245,   103,
    296, 297,   26,    217,   218,   244,   296,   296,   5,     10,
    112, 156,   298,   115,   162,   219,   27,    68,    218,   226,
    296, 229,   5,     10,    299,   5,     132,   133,   134,   135,
    145, 146,   147,   148,   220,   221,   34,    231,   232,   39,
    45,  246,   247,   248,   261,   262,   53,    104,   300,   5,
    5,   3,     4,     3,     4,     10,    220,   116,   117,   118,
    144, 162,   173,   174,   236,   237,   230,   232,   249,   162,
    101, 274,   275,   248,   262,   131,   171,   12,    28,    30,
    32,  69,    71,    73,    75,    77,    79,    81,    180,   181,
    182, 183,   184,   185,   187,   188,   189,   190,   222,   223,
    224, 225,   5,     5,     5,     10,    237,   36,    238,   239,
    162, 10,    276,   98,    5,     10,    142,   137,   157,   31,
    138, 158,   159,   160,   161,   70,    72,    74,    76,    78,
    80,  82,    224,   83,    85,    89,    91,    185,   190,   191,
    192, 193,   194,   225,   233,   234,   235,   119,   120,   144,
    162, 163,   175,   242,   243,   38,    88,    198,   240,   10,
    191, 57,    277,   278,   280,   282,   301,   143,   3,     10,
    7,   8,     9,     10,    84,    86,    90,    92,    35,    235,
    5,   5,     10,    242,   108,   149,   240,   241,   191,   186,
    190, 102,   280,   111,   121,   152,   176,   279,   55,    302,
    303, 304,   11,    29,    33,    5,     109,   150,   37,    225,
    239, 93,    195,   263,   5,     5,     176,   10,    136,   172,
    54,  304,   5,     110,   151,   94,    186,   47,    264,   265,
    13,  283,   284,   5,     10,    5,     11,    251,   162,   46,
    265, 111,   122,   123,   153,   177,   178,   285,   286,   281,
    284, 305,   225,   250,   10,    5,     5,     3,     4,     11,
    286, 287,   56,    253,   191,   58,    59,    41,    247,   252,
    254, 186,   124,   125,   126,   127,   128,   129,   130,   164,
    165, 166,   167,   168,   169,   170,   288,   289,   290,   291,
    292, 293,   294,   295,   162,   40,    266,   5,     5,     5,
    5,   5,     5,     5,     10,    10,    10,    10,    10,    10,
    10,  10,    49,    267,   268,   60,    60,    60,    60,    60,
    60,  60,    191,   256,   257,   162,   48,    268,   99,    197,
    255, 10,    100,   95,    196,   43,    259,   260,   191,   197,
    270, 271,   96,    225,   258,   162,   42,    260,   269,   271,
    258, 10,    51,    272,   273,   256,   162,   50,    273,   44,
    10,  270,   52
};

#if CUBEPARSERDEBUG
/* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
   to YYLEX-NUM.  */
const unsigned short int
Cube4Parser::yytoken_number_[] =
{
    0,    256,   1001,  1002,  1003,  1004,  1005,  1006,  1007,  1008,
    1009, 1010,  1011,  1012,  1013,  1014,  1015,  1016,  1017,  1018,
    1019, 1020,  1021,  1022,  1000,  1023,  1024,  1025,  1026,  1027,
    1028, 1029,  1030,  1031,  1032,  1033,  1034,  1035,  1036,  1037,
    1038, 1039,  1040,  1041,  1042,  1043,  1044,  1045,  1046,  1047,
    1048, 1049,  1050,  1051,  1052,  1053,  1054,  1055,  1056,  1057,
    1058, 1059,  1060,  1061,  1062,  1063,  1064,  1065,  1066,  1067,
    1068, 1069,  1070,  1071,  1072,  1073,  1074,  1075,  1076,  1077,
    1078, 1079,  1080,  1081,  1082,  1083,  1084,  1085,  1086,  1087,
    1088, 1089,  1090,  1091,  1092,  1093,  1094,  1095,  1096,  1097,
    1098, 1099,  1100,  1101,  1102,  1103,  1104,  1105,  1106,  1107,
    1108, 1109,  1110,  1111,  1112,  1113,  1114,  1115,  1116,  1117,
    1118, 1119,  1120,  1121,  1122,  1123,  1124,  1125,  1126,  1127,
    1128, 1129,  1130,  1131,  1132,  1133,  1134,  1135,  1136
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
const unsigned short int
Cube4Parser::yyr1_[] =
{
    0,   139,   140,   141,   142,   143,   144,   145,   146,   147,
    147, 148,   148,   149,   150,   151,   152,   153,   154,   154,
    155, 155,   156,   156,   157,   157,   158,   158,   158,   159,
    160, 161,   162,   163,   164,   165,   166,   167,   168,   169,
    170, 171,   172,   173,   174,   175,   176,   177,   178,   178,
    179, 180,   181,   182,   183,   184,   185,   186,   186,   187,
    188, 189,   190,   191,   192,   193,   194,   195,   196,   197,
    198, 199,   200,   201,   201,   202,   202,   203,   204,   204,
    204, 204,   204,   204,   204,   204,   205,   205,   205,   205,
    206, 206,   207,   208,   208,   209,   209,   210,   211,   211,
    212, 213,   213,   214,   214,   216,   215,   217,   217,   217,
    218, 219,   219,   220,   220,   221,   221,   221,   221,   222,
    222, 223,   223,   224,   224,   224,   224,   224,   224,   224,
    224, 224,   224,   224,   225,   226,   228,   229,   230,   227,
    231, 231,   232,   233,   233,   234,   234,   235,   235,   235,
    235, 235,   235,   235,   236,   236,   237,   237,   237,   237,
    238, 238,   238,   239,   240,   240,   241,   241,   242,   242,
    242, 242,   243,   243,   245,   244,   246,   246,   247,   247,
    249, 250,   248,   251,   251,   252,   252,   253,   253,   255,
    254, 256,   257,   258,   258,   259,   259,   260,   261,   261,
    263, 262,   264,   264,   266,   265,   267,   267,   269,   268,
    270, 270,   271,   271,   272,   272,   273,   274,   274,   276,
    275, 277,   277,   278,   278,   279,   279,   281,   280,   282,
    283, 283,   284,   285,   285,   286,   286,   286,   287,   287,
    288, 288,   288,   288,   288,   288,   288,   289,   290,   291,
    292, 293,   294,   295,   296,   296,   298,   297,   299,   299,
    301, 300,   302,   302,   303,   303,   305,   304
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
const unsigned char
Cube4Parser::yyr2_[] =
{
    0, 2,     2,     2,     2,     2,     2,     2,     2,     2,
    2, 2,     2,     2,     2,     2,     2,     2,     0,     2,
    0, 2,     0,     2,     0,     2,     1,     1,     1,     2,
    2, 2,     2,     2,     2,     2,     2,     2,     2,     2,
    2, 2,     2,     2,     2,     2,     2,     2,     2,     2,
    2, 2,     2,     2,     2,     2,     2,     0,     1,     4,
    2, 4,     2,     2,     2,     2,     2,     2,     2,     2,
    5, 2,     3,     1,     2,     1,     1,     3,     1,     1,
    1, 1,     1,     1,     1,     2,     6,     5,     5,     4,
    1, 2,     3,     1,     2,     1,     1,     3,     0,     1,
    3, 0,     1,     1,     2,     0,     6,     1,     2,     2,
    5, 0,     1,     0,     2,     1,     1,     1,     1,     0,
    1, 1,     2,     1,     1,     1,     1,     1,     1,     1,
    1, 1,     1,     1,     4,     1,     0,     0,     0,     9,
    1, 2,     5,     0,     1,     1,     2,     1,     1,     1,
    1, 1,     1,     1,     1,     2,     1,     1,     1,     1,
    1, 4,     4,     3,     0,     2,     0,     2,     1,     1,
    1, 1,     1,     2,     0,     7,     1,     1,     1,     2,
    0, 0,     12,    0,     2,     0,     1,     0,     2,     0,
    7, 1,     4,     0,     2,     1,     2,     5,     1,     2,
    0, 8,     1,     2,     0,     8,     1,     2,     0,     7,
    1, 2,     1,     1,     1,     2,     5,     0,     1,     0,
    4, 0,     1,     1,     2,     1,     2,     0,     7,     1,
    1, 2,     3,     1,     2,     1,     1,     1,     0,     3,
    1, 1,     1,     1,     1,     1,     1,     3,     3,     3,
    3, 3,     3,     3,     0,     1,     0,     4,     0,     2,
    0, 6,     0,     1,     1,     2,     0,     5
};


/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
const char*
const Cube4Parser::yytname_[] =
{
    "\"end of file\"",                   "error",                         "$undefined",                "\"false\"",           "\"true\"",
    "\"attribute value\"",               "\"error\"",                     "\"plus\"",                  "\"minus\"",           "\"aggr\"",
    "\">\"",                             "\"/>\"",                        "\"<attr\"",                 "\"<dim\"",            "\"<?xml\"",          "\"?>\"",
    "\"<cube version=\\\"4.0\\\"\"",     "\"<cube version=\\\"4.1\\\"\"",
    "\"<cube version=\\\"4.2\\\"\"",     "\"<cube version=\\\"4.3\\\"\"",
    "\"<cube version=\\\"4.4\\\"\"",     "\"<cube version=\\\"4.5\\\"\"",
    "\"<cube version=\\\"3.0\\\"\"",     "\"<cube version=\\\"\"",
    "CUBE_OPEN_NOT_SUPPORTED",           "\"</cube>\"",                   "\"<metric\"",               "\"</metric>\"",
    "\"<cubepl\"",                       "\"</cubepl>\"",                 "\"<cubeplinit>\"",          "\"</cubeplinit>\"",
    "\"<cubeplaggr\"",                   "\"</cubeplaggr>\"",             "\"<region\"",               "\"</region>\"",
    "\"<cnode\"",                        "\"</cnode>\"",                  "\"<parameter\"",            "\"<systemtreenode\"",
    "\"</systemtreenode>\"",             "\"<locationgroup\"",            "\"</locationgroup>\"",
    "\"<location\"",                     "\"</location>\"",               "\"<machine\"",              "\"</machine>\"",
    "\"<node\"",                         "\"</node>\"",                   "\"<process\"",              "\"</process>\"",
    "\"<thread\"",                       "\"</thread>\"",                 "\"<matrix\"",               "\"</matrix>\"",
    "\"<row\"",                          "\"</row>\"",                    "\"<cart\"",                 "\"</cart>\"",         "\"<coord\"",
    "\"</coord>\"",                      "\"<doc>\"",                     "\"</doc>\"",                "\"<mirrors>\"",
    "\"</mirrors>\"",                    "\"<murl>\"",                    "\"</murl>\"",               "\"<metrics\"",
    "\"</metrics>\"",                    "\"<disp_name>\"",               "\"</disp_name>\"",
    "\"<uniq_name>\"",                   "\"</uniq_name>\"",              "\"<dtype>\"",               "\"</dtype>\"",
    "\"<uom>\"",                         "\"</uom>\"",                    "\"<val>\"",                 "\"</val>\"",          "\"<url>\"",
    "\"</url>\"",                        "\"<descr>\"",                   "\"</descr>\"",              "\"<paradigm>\"",
    "\"</paradigm>\"",                   "\"<role>\"",                    "\"</role>\"",               "\"<program\"",
    "\"</program>\"",                    "\"<name>\"",                    "\"</name>\"",               "\"<mangled_name>\"",
    "\"</mangled_name>\"",               "\"<class>\"",                   "\"</class>\"",              "\"<type>\"",
    "\"</type>\"",                       "\"<system\"",                   "\"</system>\"",             "\"<rank>\"",
    "\"</rank>\"",                       "\"<topologies>\"",              "\"</topologies>\"",         "\"<severity>\"",
    "\"</severity>\"",                   "\"attribute name version\"",
    "\"attribute name encoding\"",       "\"attribute name key\"",
    "\"attribute name partype\"",        "\"attribute name parkey\"",
    "\"attribute name parvalue\"",       "\"attribute name name\"",
    "\"attribute name title\"",          "\"attribute name file\"",
    "\"attribute name value\"",          "\"attribute name id\"",
    "\"attribute name mod\"",            "\"attribute name begin\"",
    "\"attribute name end\"",            "\"attribute name line\"",
    "\"attribute name calleeid\"",       "\"attribute name ndims\"",
    "\"attribute name size\"",           "\"attribute name periodic\"",
    "\"attribute name locId\"",          "\"attribute name lgId\"",
    "\"attribute name stnId\"",          "\"attribute name thrdId\"",
    "\"attribute name procId\"",         "\"attribute name nodeId\"",
    "\"attribute name machId\"",         "\"attribute name metricId\"",
    "\"attribute name type\"",           "\"attribute name viztype\"",
    "\"attribute name convertible\"",    "\"attribute name cacheable\"",
    "\"attribute name cnodeId\"",        "\"attribute name rowwise\"",
    "\"attribute name cubeplaggrtype\"", "$accept",                       "version_attr",
    "encoding_attr",                     "key_attr",                      "value_attr",                "mod_attr",
    "metric_type_attr",                  "metric_viz_type_attr",          "metric_convertible_attr",
    "metric_cacheable_attr",             "cnode_par_type_attr",           "cnode_par_key_attr",
    "cnode_par_value_attr",              "cart_name_attr",                "dim_name_attr",
    "metrics_title_attr",                "calltree_title_attr",           "systemtree_title_attr",
    "expression_attr",                   "expression_aggr_attr",          "expression_aggr_attr_plus",
    "expression_aggr_attr_minus",        "expression_aggr_attr_aggr",     "id_attr",
    "calleeid_attr",                     "locid_attr",                    "lgid_attr",                 "stnid_attr",          "thrdid_attr",
    "procid_attr",                       "nodeid_attr",                   "machid_attr",               "metricid_attr",
    "cnodeid_attr",                      "begin_attr",                    "end_attr",                  "line_attr",           "ndims_attr",
    "size_attr",                         "periodic_attr",                 "murl_tag",                  "disp_name_tag",
    "uniq_name_tag",                     "dtype_tag",                     "uom_tag",                   "val_tag",             "url_tag",
    "descr_tag_opt",                     "expression_tag",                "expression_init_tag",
    "expression_aggr_tag",               "descr_tag",                     "name_tag",                  "mangled_name_tag",
    "paradigm_tag",                      "role_tag",                      "class_tag",                 "type_tag",            "rank_tag",
    "parameter_tag",                     "document",                      "xml_tag",                   "xml_attributes",
    "xml_attribute",                     "cube_tag",                      "cube_begin",                "cube_content",        "attr_tags",
    "attr_tag",                          "attr_attributes",               "attr_attribute",            "doc_tag",
    "mirrors_tag_attr",                  "mirrors_tag",                   "murl_tags_attr",            "murl_tags",
    "metrics_tag",                       "$@1",                           "metric_tag",                "metric_begin",        "id_attrs",
    "metric_attrs",                      "metric_attr",                   "tags_of_metric_attr",       "tags_of_metric",
    "tag_of_metric",                     "generic_attr_tag",              "metric_end",                "program_tag",         "$@2",
    "$@3",                               "$@4",                           "region_tags",               "region_tag",          "tags_of_region_attr",
    "tags_of_region",                    "tag_of_region",                 "region_attributes",
    "region_attribute",                  "cnode_tag",                     "cnode_begin",               "cnode_parameters",
    "cnode_attr_tags",                   "cnode_attribute",               "cnode_attributes",          "system_tag",
    "$@5",                               "systemtree_tags",               "flexsystemtree_tags",       "systemtree_tag",      "$@6",
    "$@7",                               "systree_attr_tags",             "systemtree_sub_tags",       "location_group_tags",
    "location_group_tag",                "$@8",                           "loc_tags",                  "loc_tag",             "lg_attr_tags",
    "location_tags",                     "location_tag",                  "machine_tags",              "machine_tag",         "$@9",
    "node_tags",                         "node_tag",                      "$@10",                      "process_tags",        "process_tag",        "$@11",
    "tags_of_process",                   "tag_of_process",                "thread_tags",               "thread_tag",
    "topologies_tag_attr",               "topologies_tag",                "$@12",                      "cart_tags_attr",
    "cart_tags",                         "cart_attrs",                    "cart_tag",                  "$@13",                "cart_open",          "dim_tags",
    "dim_tag",                           "dim_attributes",                "dim_attribute",             "coord_tags",          "coord_tag",
    "coord_tag_loc",                     "coord_tag_lg",                  "coord_tag_stn",             "coord_tag_thrd",
    "coord_tag_proc",                    "coord_tag_node",                "coord_tag_mach",            "severity_tag",
    "severity_part",                     "$@14",                          "matrix_tags",               "matrix_tag",          "$@15",
    "row_tags_attr",                     "row_tags",                      "row_tag",                   "$@16",                YY_NULL
};

#if CUBEPARSERDEBUG
/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
const Cube4Parser::rhs_number_type
Cube4Parser::yyrhs_[] =
{
    199, 0,     -1,    105,   5,     -1,    106,   5,     -1,    107,
    5,   -1,    114,   5,     -1,    116,   5,     -1,    132,   5,
    -1,  133,   5,     -1,    134,   4,     -1,    134,   3,     -1,
    135, 4,     -1,    135,   3,     -1,    108,   5,     -1,    109,
    5,   -1,    110,   5,     -1,    111,   5,     -1,    111,   5,
    -1,  -1,    112,   5,     -1,    -1,    112,   5,     -1,    -1,
    112, 5,     -1,    -1,    137,   3,     -1,    159,   -1,    160,
    -1,  161,   -1,    138,   7,     -1,    138,   8,     -1,    138,
    9,   -1,    115,   5,     -1,    120,   5,     -1,    124,   5,
    -1,  125,   5,     -1,    126,   5,     -1,    127,   5,     -1,
    128, 5,     -1,    129,   5,     -1,    130,   5,     -1,    131,
    5,   -1,    136,   5,     -1,    117,   5,     -1,    118,   5,
    -1,  119,   5,     -1,    121,   5,     -1,    122,   5,     -1,
    123, 3,     -1,    123,   4,     -1,    65,    66,    -1,    69,
    70,  -1,    71,    72,    -1,    73,    74,    -1,    75,    76,
    -1,  77,    78,    -1,    79,    80,    -1,    -1,    190,   -1,
    28,  157,   10,    29,    -1,    30,    31,    -1,    32,    158,
    10,  33,    -1,    81,    82,    -1,    89,    90,    -1,    91,
    92,  -1,    83,    84,    -1,    85,    86,    -1,    93,    94,
    -1,  95,    96,    -1,    99,    100,   -1,    38,    149,   150,
    151, 11,    -1,    200,   203,   -1,    14,    201,   15,    -1,
    202, -1,    201,   202,   -1,    140,   -1,    141,   -1,    204,
    205, 25,    -1,    16,    -1,    17,    -1,    18,    -1,    19,
    -1,  20,    -1,    21,    -1,    22,    -1,    23,    24,    -1,
    206, 210,   215,   227,   244,   296,   -1,    206,   215,   227,
    244, 296,   -1,    210,   215,   227,   244,   296,   -1,    215,
    227, 244,   296,   -1,    207,   -1,    206,   207,   -1,    12,
    208, 11,    -1,    209,   -1,    208,   209,   -1,    142,   -1,
    143, -1,    61,    211,   62,    -1,    -1,    212,   -1,    63,
    213, 64,    -1,    -1,    214,   -1,    179,   -1,    214,   179,
    -1,  -1,    67,    216,   154,   10,    217,   68,    -1,    218,
    -1,  217,   218,   -1,    217,   226,   -1,    26,    219,   220,
    10,  222,   -1,    -1,    162,   -1,    -1,    221,   220,   -1,
    145, -1,    146,   -1,    147,   -1,    148,   -1,    -1,    223,
    -1,  224,   -1,    223,   224,   -1,    180,   -1,    181,   -1,
    182, -1,    183,   -1,    184,   -1,    185,   -1,    190,   -1,
    187, -1,    188,   -1,    189,   -1,    225,   -1,    12,    142,
    143, 11,    -1,    27,    -1,    -1,    -1,    -1,    87,    228,
    155, 10,    229,   231,   230,   238,   88,    -1,    232,   -1,
    231, 232,   -1,    34,    236,   10,    233,   35,    -1,    -1,
    234, -1,    235,   -1,    234,   235,   -1,    191,   -1,    192,
    -1,  193,   -1,    194,   -1,    185,   -1,    190,   -1,    225,
    -1,  237,   -1,    236,   237,   -1,    162,   -1,    144,   -1,
    173, -1,    174,   -1,    239,   -1,    238,   240,   241,   239,
    -1,  238,   240,   241,   37,    -1,    36,    243,   10,    -1,
    -1,  198,   240,   -1,    -1,    241,   225,   -1,    162,   -1,
    175, -1,    144,   -1,    163,   -1,    242,   -1,    243,   242,
    -1,  -1,    97,    245,   156,   10,    246,   274,   98,    -1,
    261, -1,    247,   -1,    248,   -1,    247,   248,   -1,    -1,
    -1,  39,    249,   162,   10,    191,   195,   186,   251,   250,
    253, 252,   40,    -1,    -1,    251,   225,   -1,    -1,    247,
    -1,  -1,    253,   254,   -1,    -1,    41,    162,   10,    256,
    255, 259,   42,    -1,    257,   -1,    191,   197,   196,   258,
    -1,  -1,    225,   258,   -1,    260,   -1,    259,   260,   -1,
    43,  162,   10,    256,   44,    -1,    262,   -1,    261,   262,
    -1,  -1,    45,    162,   10,    191,   186,   263,   264,   46,
    -1,  265,   -1,    264,   265,   -1,    -1,    47,    162,   10,
    191, 186,   266,   267,   48,    -1,    268,   -1,    267,   268,
    -1,  -1,    49,    162,   10,    270,   269,   272,   50,    -1,
    271, -1,    270,   271,   -1,    191,   -1,    197,   -1,    273,
    -1,  272,   273,   -1,    51,    162,   10,    270,   52,    -1,
    -1,  275,   -1,    -1,    101,   276,   277,   102,   -1,    -1,
    278, -1,    280,   -1,    278,   280,   -1,    176,   -1,    152,
    176, -1,    -1,    282,   279,   10,    283,   281,   287,   58,
    -1,  57,    -1,    284,   -1,    283,   284,   -1,    13,    285,
    11,  -1,    286,   -1,    285,   286,   -1,    153,   -1,    177,
    -1,  178,   -1,    -1,    287,   59,    288,   -1,    292,   -1,
    293, -1,    294,   -1,    295,   -1,    289,   -1,    290,   -1,
    291, -1,    164,   10,    60,    -1,    165,   10,    60,    -1,
    166, 10,    60,    -1,    167,   10,    60,    -1,    168,   10,
    60,  -1,    169,   10,    60,    -1,    170,   10,    60,    -1,
    -1,  297,   -1,    -1,    103,   298,   299,   104,   -1,    -1,
    299, 300,   -1,    -1,    53,    171,   10,    301,   302,   54,
    -1,  -1,    303,   -1,    304,   -1,    303,   304,   -1,    -1,
    55,  172,   10,    305,   56,    -1
};

/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
const unsigned short int
Cube4Parser::yyprhs_[] =
{
    0,   0,     3,     6,     9,     12,    15,    18,    21,    24,
    27,  30,    33,    36,    39,    42,    45,    48,    51,    52,
    55,  56,    59,    60,    63,    64,    67,    69,    71,    73,
    76,  79,    82,    85,    88,    91,    94,    97,    100,   103,
    106, 109,   112,   115,   118,   121,   124,   127,   130,   133,
    136, 139,   142,   145,   148,   151,   154,   157,   158,   160,
    165, 168,   173,   176,   179,   182,   185,   188,   191,   194,
    197, 203,   206,   210,   212,   215,   217,   219,   223,   225,
    227, 229,   231,   233,   235,   237,   240,   247,   253,   259,
    264, 266,   269,   273,   275,   278,   280,   282,   286,   287,
    289, 293,   294,   296,   298,   301,   302,   309,   311,   314,
    317, 323,   324,   326,   327,   330,   332,   334,   336,   338,
    339, 341,   343,   346,   348,   350,   352,   354,   356,   358,
    360, 362,   364,   366,   368,   373,   375,   376,   377,   378,
    388, 390,   393,   399,   400,   402,   404,   407,   409,   411,
    413, 415,   417,   419,   421,   423,   426,   428,   430,   432,
    434, 436,   441,   446,   450,   451,   454,   455,   458,   460,
    462, 464,   466,   468,   471,   472,   480,   482,   484,   486,
    489, 490,   491,   504,   505,   508,   509,   511,   512,   515,
    516, 524,   526,   531,   532,   535,   537,   540,   546,   548,
    551, 552,   561,   563,   566,   567,   576,   578,   581,   582,
    590, 592,   595,   597,   599,   601,   604,   610,   611,   613,
    614, 619,   620,   622,   624,   627,   629,   632,   633,   641,
    643, 645,   648,   652,   654,   657,   659,   661,   663,   664,
    668, 670,   672,   674,   676,   678,   680,   682,   686,   690,
    694, 698,   702,   706,   710,   711,   713,   714,   719,   720,
    723, 724,   731,   732,   734,   736,   739,   740
};

/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
const unsigned short int
Cube4Parser::yyrline_[] =
{
    0,    310,   310,   317,   324,   331,   338,   345,   353,   361,
    367,  375,   381,   391,   400,   409,   418,   428,   436,   438,
    445,  447,   455,   457,   465,   467,   477,   479,   481,   486,
    496,  507,   519,   528,   540,   549,   558,   568,   577,   586,
    595,  604,   613,   624,   632,   640,   648,   658,   670,   676,
    687,  697,   704,   710,   717,   724,   731,   737,   738,   743,
    751,  759,   770,   777,   787,   795,   803,   812,   821,   828,
    845,  890,   896,   913,   914,   918,   919,   925,   932,   936,
    940,  944,   948,   952,   956,   960,   966,   967,   968,   969,
    975,  976,   980,   1000,  1001,  1005,  1006,  1012,  1014,  1015,
    1019, 1022,  1023,  1027,  1028,  1037,  1036,  1124,  1125,  1126,
    1132, 1233,  1234,  1238,  1239,  1242,  1243,  1244,  1245,  1248,
    1249, 1253,  1254,  1258,  1259,  1260,  1261,  1262,  1263,  1264,
    1265, 1266,  1267,  1268,  1273,  1301,  1313,  1317,  1322,  1312,
    1440, 1441,  1445,  1519,  1520,  1524,  1525,  1529,  1530,  1531,
    1532, 1533,  1534,  1535,  1541,  1542,  1546,  1547,  1548,  1549,
    1553, 1554,  1555,  1713,  1770,  1771,  1776,  1778,  1783,  1784,
    1785, 1786,  1790,  1791,  1798,  1797,  1815,  1817,  1821,  1822,
    1827, 1831,  1826,  1902,  1904,  1913,  1915,  1918,  1920,  1925,
    1925, 1980,  1984,  1987,  1989,  1995,  1996,  1999,  2056,  2057,
    2061, 2061,  2081,  2082,  2086,  2086,  2106,  2107,  2111,  2111,
    2139, 2140,  2143,  2144,  2148,  2149,  2153,  2183,  2184,  2188,
    2188, 2194,  2195,  2199,  2200,  2204,  2205,  2210,  2209,  2237,
    2244, 2245,  2249,  2266,  2267,  2271,  2272,  2273,  2276,  2277,
    2284, 2285,  2286,  2287,  2288,  2289,  2290,  2297,  2318,  2339,
    2361, 2382,  2403,  2425,  2448,  2449,  2452,  2452,  2462,  2464,
    2469, 2469,  2492,  2493,  2497,  2498,  2502,  2502
};

// Print the state stack on the debug stream.
void
Cube4Parser::yystack_print_()
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
Cube4Parser::yy_reduce_print_( int yyrule )
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
#endif // CUBEPARSERDEBUG

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
Cube4Parser::token_number_type
Cube4Parser::yytranslate_( int t )
{
    static
    const token_number_type
        translate_table[] =
    {
        0,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     1,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,   2,     2,     2,     2,     2,     2,     2,     2,     2,
        24,  2,     3,     4,     5,     6,     7,     8,     9,     10,
        11,  12,    13,    14,    15,    16,    17,    18,    19,    20,
        21,  22,    23,    25,    26,    27,    28,    29,    30,    31,
        32,  33,    34,    35,    36,    37,    38,    39,    40,    41,
        42,  43,    44,    45,    46,    47,    48,    49,    50,    51,
        52,  53,    54,    55,    56,    57,    58,    59,    60,    61,
        62,  63,    64,    65,    66,    67,    68,    69,    70,    71,
        72,  73,    74,    75,    76,    77,    78,    79,    80,    81,
        82,  83,    84,    85,    86,    87,    88,    89,    90,    91,
        92,  93,    94,    95,    96,    97,    98,    99,    100,   101,
        102, 103,   104,   105,   106,   107,   108,   109,   110,   111,
        112, 113,   114,   115,   116,   117,   118,   119,   120,   121,
        122, 123,   124,   125,   126,   127,   128,   129,   130,   131,
        132, 133,   134,   135,   136,   137,   138
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

const int Cube4Parser::yyeof_     = 0;
const int Cube4Parser::yylast_    = 350;
const int Cube4Parser::yynnts_    = 167;
const int Cube4Parser::yyempty_   = -2;
const int Cube4Parser::yyfinal_   = 10;
const int Cube4Parser::yyterror_  = 1;
const int Cube4Parser::yyerrcode_ = 256;
const int Cube4Parser::yyntokens_ = 139;

const unsigned int                   Cube4Parser::yyuser_token_number_max_ = 1136;
const Cube4Parser::token_number_type Cube4Parser::yyundef_token_           = 2;
} // cubeparser
/* Line 1141 of lalr1.cc  */
#line 3764 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.cpp"
/* Line 1142 of lalr1.cc  */
#line 2540 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"
/*** Additional Code ***/


void
cubeparser::Cube4Parser::error( const Cube4Parser::location_type& l,
                                const std::string&                m )
{
    if ( strstr( m.c_str(), "expecting <?xml" ) != NULL )
    {
        driver.error_just_message( "The cube file is probably empty or filled with wrong content. The file has ended before the header of cube started. \n" );
    }
    if ( strstr( m.c_str(), " expecting </row>" ) != NULL )
    {
        driver.error_just_message( "One of the possible reasons is \n    1) that the severity value is malformed. CUBE expects the \"double\" value in C_LOCALE with dot instead of comma;. \n    2) that the CUBE file is not properly ended. Probably the writing of CUBE file was interrupted." );
    }
    if ( strstr( m.c_str(), " expecting <matrix" ) != NULL ||
         ( strstr( m.c_str(), " expecting <severity>" ) != NULL ) )
    {
        driver.error_just_message( "The cube file has probably a proper structure, but doesn't contain any severity values." );
    }
    if ( strstr( m.c_str(), " expecting <metric" ) != NULL )
    {
        driver.error_just_message( "The cube file doesn't contain any information about metric dimension." );
    }
    if ( strstr( m.c_str(), " expecting <region" ) != NULL )
    {
        driver.error_just_message( "The cube file doesn't contain any information about program dimension." );
    }
    if ( strstr( m.c_str(), " expecting <machine" ) != NULL )
    {
        driver.error_just_message( "The cube file doesn't contain any information about system dimension." );
    }
    if ( strstr( m.c_str(), " expecting <thread" ) != NULL )
    {
        driver.error_just_message( "The system dimension of the cube file is malformed. It contains a process without any threads." );
    }
    if ( strstr( m.c_str(), " expecting <process" ) != NULL )
    {
        driver.error_just_message( "The system dimension of the cube file is malformed. It contains a node without any processes." );
    }
    if ( strstr( m.c_str(), " expecting <node" ) != NULL )
    {
        driver.error_just_message( "The system dimension of the cube file is malformed. It contains a machine without any computing nodes." );
    }
    driver.error( l, m );
}
