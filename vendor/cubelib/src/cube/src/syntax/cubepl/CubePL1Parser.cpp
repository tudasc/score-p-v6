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
#define yylex   cubeplparserlex

/* First part of user declarations.  */

/* Line 279 of lalr1.cc  */
#line 40 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"


#include "CubePL1Parser.h"

/* User implementation prologue.  */
/* Line 285 of lalr1.cc  */
#line 263 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"

#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"
#include "CubePL1Scanner.h"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>

using namespace std;
using namespace cube;

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <string>
#include <vector>
#include "CubePL1ParseContext.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex CubePL1Lexer.lex

// Workaround for Sun Studio C++ compilers on Solaris
#if defined( __SVR4 ) &&  defined( __SUNPRO_CC )
  #include <ieeefp.h>

  #define isinf( x )  ( fpclass( x ) == FP_NINF || fpclass( x ) == FP_PINF )
  #define isnan( x )  isnand( x )
#endif


/* Line 285 of lalr1.cc  */
#line 87 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"


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
#if CUBEPLPARSERDEBUG

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

#else /* !CUBEPLPARSERDEBUG */

# define YYCDEBUG if ( false ) std::cerr
# define YY_SYMBOL_PRINT( Title, Type, Value, Location ) YYUSE( Type )
# define YY_REDUCE_PRINT( Rule )        static_cast<void>( 0 )
# define YY_STACK_PRINT()             static_cast<void>( 0 )

#endif /* !CUBEPLPARSERDEBUG */

#define yyerrok         ( yyerrstatus_ = 0 )
#define yyclearin       ( yychar = yyempty_ )

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  ( !!yyerrstatus_ )


namespace cubeplparser
{
/* Line 353 of lalr1.cc  */
#line 182 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"

/* Return YYSTR after stripping away unnecessary quotes and
   backslashes, so that it's suitable for yyerror.  The heuristic is
   that double-quoting is unnecessary unless the string contains an
   apostrophe, a comma, or backslash (other than backslash-backslash).
   YYSTR is taken from yytname.  */
std::string
CubePL1Parser::yytnamerr_( const char* yystr )
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
CubePL1Parser::CubePL1Parser ( class CubePL1ParseContext& parseContext_yyarg, class CubePL1Scanner& CubePL1Lexer_yyarg )
    :
#if CUBEPLPARSERDEBUG
    yydebug_( false ),
    yycdebug_( &std::cerr ),
#endif
    parseContext( parseContext_yyarg ),
    CubePL1Lexer( CubePL1Lexer_yyarg )
{
}

CubePL1Parser::~CubePL1Parser ()
{
}

#if CUBEPLPARSERDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
   `--------------------------------*/

inline void
CubePL1Parser::yy_symbol_value_print_( int yytype,
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
CubePL1Parser::yy_symbol_print_( int yytype,
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
CubePL1Parser::yydestruct_( const char* yymsg,
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
CubePL1Parser::yypop_( unsigned int n )
{
    yystate_stack_.pop( n );
    yysemantic_stack_.pop( n );
    yylocation_stack_.pop( n );
}

#if CUBEPLPARSERDEBUG
std::ostream&
CubePL1Parser::debug_stream() const
{
    return *yycdebug_;
}

void
CubePL1Parser::set_debug_stream( std::ostream& o )
{
    yycdebug_ = &o;
}


CubePL1Parser::debug_level_type
CubePL1Parser::debug_level() const
{
    return yydebug_;
}

void
CubePL1Parser::set_debug_level( debug_level_type l )
{
    yydebug_ = l;
}
#endif

inline bool
CubePL1Parser::yy_pact_value_is_default_( int yyvalue )
{
    return yyvalue == yypact_ninf_;
}

inline bool
CubePL1Parser::yy_table_value_is_error_( int yyvalue )
{
    return yyvalue == yytable_ninf_;
}

int
CubePL1Parser::parse()
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
#line 141 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
        {
            // initialize the initial location object
        }
/* Line 545 of lalr1.cc  */
#line 383 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"

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
#line 312 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.result = parseContext._stack.top();
                        parseContext._stack.pop();
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 3:
/* Line 670 of lalr1.cc  */
#line 321 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    parseContext.syntax_ok &= true;
                }
                break;

            case 23:
/* Line 670 of lalr1.cc  */
#line 350 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _arg1 = parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new EncapsulationEvaluation( _arg1 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 24:
/* Line 670 of lalr1.cc  */
#line 360 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _arg1 = parseContext._stack.top();
                        parseContext._stack.pop();
                        GeneralEvaluation* _abs = new AbsEvaluation();
                        _abs->addArgument( _arg1 );
                        parseContext._stack.push( _abs );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 25:
/* Line 670 of lalr1.cc  */
#line 373 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _arg1 = parseContext._stack.top();
                        parseContext._stack.pop();
                        GeneralEvaluation* _arg2 = parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new PlusEvaluation( _arg1, _arg2 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 26:
/* Line 670 of lalr1.cc  */
#line 386 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _arg2 = parseContext._stack.top();
                        parseContext._stack.pop();
                        GeneralEvaluation* _arg1 = parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new MinusEvaluation( _arg1, _arg2 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 27:
/* Line 670 of lalr1.cc  */
#line 400 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _arg2 = parseContext._stack.top();
                        parseContext._stack.pop();
                        GeneralEvaluation* _arg1 = parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new DivideEvaluation( _arg1, _arg2 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 28:
/* Line 670 of lalr1.cc  */
#line 413 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _arg1 = parseContext._stack.top();
                        parseContext._stack.pop();
                        GeneralEvaluation* _arg2 = parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new MultEvaluation( _arg1, _arg2 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 29:
/* Line 670 of lalr1.cc  */
#line 429 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* power = parseContext._stack.top();
                        parseContext._stack.pop();
                        GeneralEvaluation* base = parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new PowerEvaluation( base, power ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 30:
/* Line 670 of lalr1.cc  */
#line 441 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* arg = parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new NegativeEvaluation( arg ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 33:
/* Line 670 of lalr1.cc  */
#line 455 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext._stack.push( new ArgumentEvaluation( cube::FIRST_ARGUMENT ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 34:
/* Line 670 of lalr1.cc  */
#line 464 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext._stack.push( new ArgumentEvaluation( cube::SECOND_ARGUMENT ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 48:
/* Line 670 of lalr1.cc  */
#line 492 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _arg1 = parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new EncapsulationEvaluation( _arg1 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 49:
/* Line 670 of lalr1.cc  */
#line 502 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _arg1 = parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new NotEvaluation( _arg1 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 50:
/* Line 670 of lalr1.cc  */
#line 513 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _arg2 = parseContext._stack.top();
                        parseContext._stack.pop();
                        GeneralEvaluation* _arg1 = parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new AndEvaluation( _arg1, _arg2 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 51:
/* Line 670 of lalr1.cc  */
#line 526 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _arg2 = parseContext._stack.top();
                        parseContext._stack.pop();
                        GeneralEvaluation* _arg1 = parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new OrEvaluation( _arg1, _arg2 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 52:
/* Line 670 of lalr1.cc  */
#line 540 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _arg2 = parseContext._stack.top();
                        parseContext._stack.pop();
                        GeneralEvaluation* _arg1 = parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new XorEvaluation( _arg1, _arg2 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 53:
/* Line 670 of lalr1.cc  */
#line 553 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext._stack.push( new ConstantEvaluation( 1 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 54:
/* Line 670 of lalr1.cc  */
#line 561 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext._stack.push( new ConstantEvaluation( 0 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 55:
/* Line 670 of lalr1.cc  */
#line 570 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _arg2 = parseContext._stack.top();
                        parseContext._stack.pop();
                        GeneralEvaluation* _arg1 = parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new EqualEvaluation( _arg1, _arg2 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 56:
/* Line 670 of lalr1.cc  */
#line 584 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _arg2 = parseContext._stack.top();
                        parseContext._stack.pop();
                        GeneralEvaluation* _arg1 = parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new NotEqualEvaluation( _arg1, _arg2 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 57:
/* Line 670 of lalr1.cc  */
#line 598 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _arg2 = parseContext._stack.top();
                        parseContext._stack.pop();
                        GeneralEvaluation* _arg1 = parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new BiggerEvaluation( _arg1, _arg2 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 58:
/* Line 670 of lalr1.cc  */
#line 611 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _arg2 = parseContext._stack.top();
                        parseContext._stack.pop();
                        GeneralEvaluation* _arg1 = parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new SmallerEvaluation( _arg1, _arg2 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 59:
/* Line 670 of lalr1.cc  */
#line 625 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _arg2 = parseContext._stack.top();
                        parseContext._stack.pop();
                        GeneralEvaluation* _arg1 = parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new HalfBiggerEvaluation( _arg1, _arg2 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 60:
/* Line 670 of lalr1.cc  */
#line 639 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _arg2 = parseContext._stack.top();
                        parseContext._stack.pop();
                        GeneralEvaluation* _arg1 = parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new HalfSmallerEvaluation( _arg1, _arg2 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 64:
/* Line 670 of lalr1.cc  */
#line 662 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _value2 =   parseContext._stack.top();
                        parseContext._stack.pop();
                        GeneralEvaluation* _value1 =   parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new StringEqualityEvaluation( _value1, _value2 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 65:
/* Line 670 of lalr1.cc  */
#line 675 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _value2 =   parseContext._stack.top();
                        parseContext._stack.pop();
                        GeneralEvaluation* _value1 =   parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new StringSemiEqualityEvaluation( _value1, _value2 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 66:
/* Line 670 of lalr1.cc  */
#line 687 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        string _regexp =  parseContext.strings_stack.top();
                        parseContext.strings_stack.pop();
                        GeneralEvaluation* _value =   parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new RegexEvaluation( _value, new StringConstantEvaluation( _regexp ) ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 67:
/* Line 670 of lalr1.cc  */
#line 702 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    string  _tmp = parseContext.str.str();
                    regex_t rgT;
                    int     _result = regcomp( &rgT, _tmp.c_str(), REG_EXTENDED );
                    if ( _result != 0 )
                    {
                        parseContext.syntax_ok &= false;
                    }
                    if ( _result == 0 && !parseContext.test_modus )
                    {
                        parseContext.strings_stack.push( _tmp );
                        parseContext.str.str( "" );
                    }
                    regfree( &rgT );
                    parseContext.syntax_ok &= true;
                }
                break;

            case 68:
/* Line 670 of lalr1.cc  */
#line 724 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext._stack.push( new StringConstantEvaluation( parseContext.str.str() ) );
                        parseContext.str.str( "" );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 72:
/* Line 670 of lalr1.cc  */
#line 740 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _arg1 = parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new LowerCaseEvaluation( _arg1 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 73:
/* Line 670 of lalr1.cc  */
#line 751 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _arg1 = parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new UpperCaseEvaluation( _arg1 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 74:
/* Line 670 of lalr1.cc  */
#line 763 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _arg1 = parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext._stack.push( new EnvEvaluation( _arg1 ) );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 75:
/* Line 670 of lalr1.cc  */
#line 777 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        std::string uniq_name = parseContext.name_of_metric;
                        Metric*     _met      = parseContext.cube->get_met( uniq_name );
                        if ( _met != NULL )
                        {
                            GeneralEvaluation* _property = parseContext._stack.top();
                            parseContext._stack.pop();
                            MetricGetEvaluation* _metric_get_eval = new MetricGetEvaluation( _met, _property );
                            parseContext._stack.push( _metric_get_eval );
                        }
                        else
                        {
                            cout << " Metric with uniq name " << uniq_name << " doesn't exists in cube" << endl;
                        }
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 78:
/* Line 670 of lalr1.cc  */
#line 802 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _arg1 = parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext.function_call.top()->addArgument( _arg1 );
                        parseContext._stack.push( parseContext.function_call.top() );
                        parseContext.function_call.pop();
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 79:
/* Line 670 of lalr1.cc  */
#line 817 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.function_call.push( new SqrtEvaluation() );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 80:
/* Line 670 of lalr1.cc  */
#line 825 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.function_call.push( new SinEvaluation() );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 81:
/* Line 670 of lalr1.cc  */
#line 833 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.function_call.push( new ASinEvaluation() );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 82:
/* Line 670 of lalr1.cc  */
#line 841 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.function_call.push( new CosEvaluation() );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 83:
/* Line 670 of lalr1.cc  */
#line 849 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.function_call.push( new ACosEvaluation() );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 84:
/* Line 670 of lalr1.cc  */
#line 857 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.function_call.push( new ExpEvaluation() );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 85:
/* Line 670 of lalr1.cc  */
#line 865 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.function_call.push( new LnEvaluation() );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 86:
/* Line 670 of lalr1.cc  */
#line 873 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.function_call.push( new TanEvaluation() );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 87:
/* Line 670 of lalr1.cc  */
#line 881 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.function_call.push( new ATanEvaluation() );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 88:
/* Line 670 of lalr1.cc  */
#line 889 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.function_call.push( new RandomEvaluation() );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 89:
/* Line 670 of lalr1.cc  */
#line 897 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.function_call.push( new AbsEvaluation() );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 90:
/* Line 670 of lalr1.cc  */
#line 905 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.function_call.push( new SgnEvaluation() );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 91:
/* Line 670 of lalr1.cc  */
#line 913 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.function_call.push( new PosEvaluation() );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 92:
/* Line 670 of lalr1.cc  */
#line 921 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.function_call.push( new NegEvaluation() );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 93:
/* Line 670 of lalr1.cc  */
#line 929 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.function_call.push( new FloorEvaluation() );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 94:
/* Line 670 of lalr1.cc  */
#line 937 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.function_call.push( new CeilEvaluation() );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 95:
/* Line 670 of lalr1.cc  */
#line 948 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _arg2 = parseContext._stack.top();
                        parseContext._stack.pop();
                        GeneralEvaluation* _arg1 = parseContext._stack.top();
                        parseContext._stack.pop();
                        parseContext.function_call.top()->addArgument( _arg1 );
                        parseContext.function_call.top()->addArgument( _arg2 );
                        parseContext._stack.push( parseContext.function_call.top() );
                        parseContext.function_call.pop();
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 96:
/* Line 670 of lalr1.cc  */
#line 964 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.function_call.push( new MinEvaluation() );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 97:
/* Line 670 of lalr1.cc  */
#line 972 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.function_call.push( new MaxEvaluation() );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 98:
/* Line 670 of lalr1.cc  */
#line 983 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        double _value = atof( parseContext.value.c_str() );
                        parseContext._stack.push( new ConstantEvaluation( _value ) );
                        parseContext.value = "";
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 102:
/* Line 670 of lalr1.cc  */
#line 999 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        Metric* _met = parseContext.cube->get_met( parseContext.name_of_metric );
                        if ( _met != NULL )
                        {
                            parseContext._stack.push( new DirectMetricEvaluation( cube::CONTEXT_METRIC,  parseContext.cube, _met ) );
                            _met->isUsedByOthers( true );
                        }
                        else
                        {
                            cerr << "Cannot connect to the metric " << parseContext.name_of_metric << ". Seems that this metric is not created yet. Value of metric::" << parseContext.name_of_metric << "() will be always 0" << endl;
                            parseContext._stack.push( new ConstantEvaluation( 0 ) );
                        }
                        parseContext.value = "";
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 103:
/* Line 670 of lalr1.cc  */
#line 1019 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        Metric* _met = parseContext.cube->get_met( parseContext.name_of_metric );
                        if ( _met != NULL )
                        {
                            cube::CalcFlavorModificator* mod = parseContext.calcFlavorModificators.top();
                            parseContext.calcFlavorModificators.pop();
                            parseContext._stack.push( new DirectMetricEvaluation( cube::CONTEXT_METRIC,  parseContext.cube, _met, mod ) );
                            _met->isUsedByOthers( true );
                        }
                        else
                        {
                            cerr << "Cannot connect to the metric " << parseContext.name_of_metric << ". Seems that this metric is not created yet. Value of metric::" << parseContext.name_of_metric << "( ?  ) will be always 0" << endl;
                            parseContext._stack.push( new ConstantEvaluation( 0 ) );
                        }
                        parseContext.value = "";
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 104:
/* Line 670 of lalr1.cc  */
#line 1041 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        Metric* _met = parseContext.cube->get_met( parseContext.name_of_metric );
                        if ( _met != NULL )
                        {
                            cube::CalcFlavorModificator* mod2 = parseContext.calcFlavorModificators.top();
                            parseContext.calcFlavorModificators.pop();
                            cube::CalcFlavorModificator* mod1 = parseContext.calcFlavorModificators.top();
                            parseContext.calcFlavorModificators.pop();

                            parseContext._stack.push( new DirectMetricEvaluation( cube::CONTEXT_METRIC,  parseContext.cube, _met, mod1, mod2 ) );
                            _met->isUsedByOthers( true );
                        }
                        else
                        {
                            cerr << "Cannot connect to the metric " << parseContext.name_of_metric << ". Seems that this metric is not created yet. Value of metric::" << parseContext.name_of_metric << "( ?, ? ) will be always 0" << endl;
                            parseContext._stack.push( new ConstantEvaluation( 0 ) );
                        }
                        parseContext.value = "";
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 105:
/* Line 670 of lalr1.cc  */
#line 1069 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        Metric* _met = parseContext.cube->get_met( parseContext.name_of_metric );
                        if ( _met != NULL )
                        {
                            parseContext._stack.push( new DirectMetricEvaluation( cube::FIXED_METRIC_FULL_AGGR,  parseContext.cube, _met ) );
                            _met->isUsedByOthers( true );
                        }
                        else
                        {
                            cerr << "Cannot connect to the metric " << parseContext.name_of_metric << ". Seems that this metric is not created yet. Value of metric::" << parseContext.name_of_metric << "() will be always 0" << endl;
                            parseContext._stack.push( new ConstantEvaluation( 0 ) );
                        }
                        parseContext.value = "";
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 106:
/* Line 670 of lalr1.cc  */
#line 1089 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        Metric* _met = parseContext.cube->get_met( parseContext.name_of_metric );
                        if ( _met != NULL )
                        {
                            cube::CalcFlavorModificator* mod = parseContext.calcFlavorModificators.top();
                            parseContext.calcFlavorModificators.pop();
                            parseContext._stack.push( new DirectMetricEvaluation( cube::FIXED_METRIC_AGGR_SYS,  parseContext.cube, _met, mod ) );
                            _met->isUsedByOthers( true );
                        }
                        else
                        {
                            cube::CalcFlavorModificator* mod = parseContext.calcFlavorModificators.top();
                            parseContext.calcFlavorModificators.pop();
                            cerr << "Cannot connect to the metric " << parseContext.name_of_metric << ". Seems that this metric is not created yet. Value of metric::fixed::" << parseContext.name_of_metric << "( ";
                            mod->print();
                            cout << " ) will be always 0" << endl;


                            delete mod;

                            parseContext._stack.push( new ConstantEvaluation( 0 ) );
                        }
                        parseContext.value = "";
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 107:
/* Line 670 of lalr1.cc  */
#line 1118 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        Metric* _met = parseContext.cube->get_met( parseContext.name_of_metric );
                        if ( _met != NULL )
                        {
                            cube::CalcFlavorModificator* mod2 = parseContext.calcFlavorModificators.top();
                            parseContext.calcFlavorModificators.pop();
                            cube::CalcFlavorModificator* mod1 = parseContext.calcFlavorModificators.top();
                            parseContext.calcFlavorModificators.pop();

                            parseContext._stack.push( new DirectMetricEvaluation( cube::FIXED_METRIC_NO_AGGR,  parseContext.cube, _met, mod1, mod2 ) );
                            _met->isUsedByOthers( true );
                        }
                        else
                        {
                            cube::CalcFlavorModificator* mod2 = parseContext.calcFlavorModificators.top();
                            parseContext.calcFlavorModificators.pop();
                            cube::CalcFlavorModificator* mod1 = parseContext.calcFlavorModificators.top();
                            parseContext.calcFlavorModificators.pop();
                            cerr << "Cannot connect to the metric " << parseContext.name_of_metric << ". Seems that this metric is not created yet. Value of metric::fixed::" << parseContext.name_of_metric << "( ";
                            mod1->print();
                            cout << ",";
                            mod2->print();
                            cout << ") will be always 0" << endl;


                            delete mod2;
                            delete mod1;

                            parseContext._stack.push( new ConstantEvaluation( 0 ) );
                        }
                        parseContext.value = "";
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 108:
/* Line 670 of lalr1.cc  */
#line 1155 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        Metric* _met = parseContext.cube->get_met( parseContext.name_of_metric );
                        if ( _met != NULL )
                        {
                            cube::CalcFlavorModificator* mod = parseContext.calcFlavorModificators.top();
                            parseContext.calcFlavorModificators.pop();
                            GeneralEvaluation* _cnode_id = parseContext._stack.top();
                            parseContext._stack.pop();

                            parseContext._stack.push( new DirectMetricEvaluation( cube::METRIC_CALL_CALLPATH,  parseContext.cube, _met, _cnode_id, mod ) );
                            _met->isUsedByOthers( true );
                        }
                        else
                        {
                            cube::CalcFlavorModificator* mod = parseContext.calcFlavorModificators.top();
                            parseContext.calcFlavorModificators.pop();

                            GeneralEvaluation* _cnode_id = parseContext._stack.top();
                            parseContext._stack.pop();

                            cerr << "Cannot connect to the metric " << parseContext.name_of_metric << ". Seems that this metric is not created yet. Value of metric::call::" << parseContext.name_of_metric << "( ";
                            _cnode_id->print();
                            cout << ",";
                            mod->print();
                            cout << ") will be always 0" << endl;
                            delete mod;
                            delete _cnode_id;

                            parseContext._stack.push( new ConstantEvaluation( 0 ) );
                        }
                        parseContext.value = "";
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 109:
/* Line 670 of lalr1.cc  */
#line 1190 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        Metric* _met = parseContext.cube->get_met( parseContext.name_of_metric );
                        if ( _met != NULL )
                        {
                            cube::CalcFlavorModificator* mod2 = parseContext.calcFlavorModificators.top();
                            parseContext.calcFlavorModificators.pop();
                            cube::CalcFlavorModificator* mod1 = parseContext.calcFlavorModificators.top();
                            parseContext.calcFlavorModificators.pop();
                            GeneralEvaluation* _sysres_id = parseContext._stack.top();
                            parseContext._stack.pop();
                            GeneralEvaluation* _cnode_id = parseContext._stack.top();
                            parseContext._stack.pop();
                            parseContext._stack.push( new DirectMetricEvaluation( cube::METRIC_CALL_FULL,  parseContext.cube, _met, _cnode_id, mod1, _sysres_id,  mod2 ) );
                            _met->isUsedByOthers( true );
                        }
                        else
                        {
                            cube::CalcFlavorModificator* mod2 = parseContext.calcFlavorModificators.top();
                            parseContext.calcFlavorModificators.pop();
                            cube::CalcFlavorModificator* mod1 = parseContext.calcFlavorModificators.top();
                            parseContext.calcFlavorModificators.pop();
                            GeneralEvaluation* _sysres_id = parseContext._stack.top();
                            parseContext._stack.pop();
                            GeneralEvaluation* _cnode_id = parseContext._stack.top();
                            parseContext._stack.pop();
                            cerr << "Cannot connect to the metric " << parseContext.name_of_metric << ". Seems that this metric is not created yet. Value of metric::call::" << parseContext.name_of_metric << "( ";
                            _cnode_id->print();
                            cout << ",";
                            mod1->print();
                            cout << ",";
                            _sysres_id->print();
                            cout << ",";
                            mod2->print();
                            cout << ") will be always 0" << endl;


                            delete mod2;
                            delete mod1;
                            delete _cnode_id;
                            delete _sysres_id;

                            parseContext._stack.push( new ConstantEvaluation( 0 ) );
                        }
                        parseContext.value = "";
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 110:
/* Line 670 of lalr1.cc  */
#line 1237 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.calcFlavorModificators.push( new CalcFlavorModificatorIncl() );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 111:
/* Line 670 of lalr1.cc  */
#line 1245 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.calcFlavorModificators.push( new CalcFlavorModificatorExcl() );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 112:
/* Line 670 of lalr1.cc  */
#line 1253 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.calcFlavorModificators.push( new CalcFlavorModificatorSame() );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 113:
/* Line 670 of lalr1.cc  */
#line 1264 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        LambdaCalculEvaluation* _l_calc = new LambdaCalculEvaluation();

                        GeneralEvaluation* return_expr = parseContext._stack.top();
                        parseContext._stack.pop();

                        int _num_of_statements = parseContext._number_of_statements.top();
                        parseContext._number_of_statements.pop();

                        vector<GeneralEvaluation*> _tmp_statements;
                        for ( int i = 0; i < _num_of_statements; i++ )
                        {
                            _tmp_statements.push_back( parseContext._statements.top() );
                            parseContext._statements.pop();
                        }
                        for ( int i = _num_of_statements - 1; i >= 0; i-- )
                        {
                            _l_calc->addArgument( _tmp_statements[ i ] );
                        }
                        _l_calc->addArgument( return_expr );
                        parseContext._stack.push( _l_calc );
                        // create lambda calculation using number_of_statements.
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 115:
/* Line 670 of lalr1.cc  */
#line 1296 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext._number_of_statements.push( 0 );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 118:
/* Line 670 of lalr1.cc  */
#line 1313 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        int _tmp = parseContext._number_of_statements.top();
                        parseContext._number_of_statements.pop();
                        _tmp++;
                        parseContext._number_of_statements.push( _tmp );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 119:
/* Line 670 of lalr1.cc  */
#line 1324 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        int _tmp = parseContext._number_of_statements.top();
                        parseContext._number_of_statements.pop();
                        _tmp++;
                        parseContext._number_of_statements.push( _tmp );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 120:
/* Line 670 of lalr1.cc  */
#line 1335 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        int _tmp = parseContext._number_of_statements.top();
                        parseContext._number_of_statements.pop();
                        _tmp++;
                        parseContext._number_of_statements.push( _tmp );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 121:
/* Line 670 of lalr1.cc  */
#line 1346 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    parseContext.syntax_ok &= true;
                }
                break;

            case 122:
/* Line 670 of lalr1.cc  */
#line 1350 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    parseContext.syntax_ok &= true;
                }
                break;

            case 123:
/* Line 670 of lalr1.cc  */
#line 1354 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        int _tmp = parseContext._number_of_statements.top();
                        parseContext._number_of_statements.pop();
                        _tmp++;
                        parseContext._number_of_statements.push( _tmp );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 124:
/* Line 670 of lalr1.cc  */
#line 1365 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    parseContext.syntax_ok &= true;
                }
                break;

            case 125:
/* Line 670 of lalr1.cc  */
#line 1369 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    parseContext.syntax_ok &= true;
                }
                break;

            case 126:
/* Line 670 of lalr1.cc  */
#line 1373 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    parseContext.syntax_ok &= true;
                }
                break;

            case 127:
/* Line 670 of lalr1.cc  */
#line 1377 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    parseContext.syntax_ok &= true;
                }
                break;

            case 128:
/* Line 670 of lalr1.cc  */
#line 1383 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        std::string        uniq_name = parseContext.name_of_metric;
                        Metric*            _met      = parseContext.cube->get_met( uniq_name );
                        GeneralEvaluation* _value    = parseContext._stack.top();
                        parseContext._stack.pop();
                        GeneralEvaluation* _property = parseContext._stack.top();
                        parseContext._stack.pop();
                        MetricSetEvaluation* _metric_set_eval = new MetricSetEvaluation( _met, _property, _value );
                        parseContext._statements.push( _metric_set_eval );
                        if ( _met == NULL )
                        {
                            cout << " Metric with uniq name " << uniq_name << " doesn't exists in cube. metric::set has no action." << endl;
                        }
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 133:
/* Line 670 of lalr1.cc  */
#line 1414 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        int _num_of_statements = parseContext._number_of_statements.top();
                        parseContext._number_of_statements.pop();

                        vector<GeneralEvaluation*> _tmp_statements;
                        for ( int i = 0; i < _num_of_statements; i++ )
                        {
                            _tmp_statements.push_back( parseContext._statements.top() );
                            parseContext._statements.pop();
                        }
                        GeneralEvaluation* _condition = parseContext._stack.top();
                        parseContext._stack.pop();

                        ShortIfEvaluation* _s_if_calc = new ShortIfEvaluation( _condition );

                        for ( int i = _num_of_statements - 1; i >= 0; i-- )
                        {
                            _s_if_calc->addArgument( _tmp_statements[ i ] );
                        }
                        parseContext._statements.push( _s_if_calc );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 134:
/* Line 670 of lalr1.cc  */
#line 1441 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        int _num_of_false_statements = parseContext._number_of_statements.top();
                        parseContext._number_of_statements.pop();
                        int _num_of_true_statements = parseContext._number_of_statements.top();
                        parseContext._number_of_statements.pop();

                        vector<GeneralEvaluation*> _tmp_false_statements;
                        for ( int i = 0; i < _num_of_false_statements; i++ )
                        {
                            _tmp_false_statements.push_back( parseContext._statements.top() );
                            parseContext._statements.pop();
                        }
                        vector<GeneralEvaluation*> _tmp_true_statements;
                        for ( int i = 0; i < _num_of_true_statements; i++ )
                        {
                            _tmp_true_statements.push_back( parseContext._statements.top() );
                            parseContext._statements.pop();
                        }
                        GeneralEvaluation* _condition = parseContext._stack.top();
                        parseContext._stack.pop();

                        FullIfEvaluation* _f_if_calc = new FullIfEvaluation( _condition, _num_of_true_statements, _num_of_false_statements );

                        for ( int i = _num_of_true_statements - 1; i >= 0; i-- )
                        {
                            _f_if_calc->addArgument( _tmp_true_statements[ i ] );
                        }
                        for ( int i = _num_of_false_statements - 1; i >= 0; i-- )
                        {
                            _f_if_calc->addArgument( _tmp_false_statements[ i ] );
                        }
                        parseContext._statements.push( _f_if_calc );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 135:
/* Line 670 of lalr1.cc  */
#line 1480 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        std::stack<std::stack<GeneralEvaluation*> > statement_blocks;
                        std::stack<GeneralEvaluation*>              statement_conditions;

                        int _num_of_false_statements = parseContext._number_of_statements.top();
                        parseContext._number_of_statements.pop();
                        std::stack<GeneralEvaluation*> _tmp_false_statements;
                        for ( int i = 0; i < _num_of_false_statements; i++ )
                        {
                            _tmp_false_statements.push( parseContext._statements.top() );
                            parseContext._statements.pop();
                        }
                        statement_blocks.push( _tmp_false_statements );

                        for ( unsigned i = 0; i < parseContext.number_elseif + 1 /* +1 is for the initial condition*/; ++i )
                        {
                            int _num_of_statements = parseContext._number_of_statements.top();
                            parseContext._number_of_statements.pop();
                            std::stack<GeneralEvaluation*> _tmp_statements;
                            for ( int j = 0; j < _num_of_statements; j++ )
                            {
                                _tmp_statements.push( parseContext._statements.top() );
                                parseContext._statements.pop();
                            }

                            GeneralEvaluation* _condition = parseContext._stack.top();
                            parseContext._stack.pop();
                            statement_blocks.push( _tmp_statements );
                            statement_conditions.push( _condition );
                        }
                        ExtendedIfEvaluation* _ext_if_calc = new ExtendedIfEvaluation( statement_conditions, statement_blocks );
                        parseContext._statements.push( _ext_if_calc );

                        parseContext.number_elseif = 0;
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 136:
/* Line 670 of lalr1.cc  */
#line 1523 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        std::stack<std::stack<GeneralEvaluation*> > statement_blocks;
                        std::stack<GeneralEvaluation*>              statement_conditions;

                        for ( unsigned i = 0; i < parseContext.number_elseif + 1 /* +1 is for the initial condition*/; ++i )
                        {
                            int _num_of_statements = parseContext._number_of_statements.top();
                            parseContext._number_of_statements.pop();
                            std::stack<GeneralEvaluation*> _tmp_statements;
                            for ( int j = 0; j < _num_of_statements; j++ )
                            {
                                _tmp_statements.push( parseContext._statements.top() );
                                parseContext._statements.pop();
                            }

                            GeneralEvaluation* _condition = parseContext._stack.top();
                            parseContext._stack.pop();
                            statement_blocks.push( _tmp_statements );
                            statement_conditions.push( _condition );
                        }
                        ExtendedIfEvaluation* _ext_if_calc = new ExtendedIfEvaluation( statement_conditions, statement_blocks );
                        parseContext._statements.push( _ext_if_calc );

                        parseContext.number_elseif = 0;
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 139:
/* Line 670 of lalr1.cc  */
#line 1560 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.number_elseif++;
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 143:
/* Line 670 of lalr1.cc  */
#line 1579 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext._number_of_statements.push( 0 );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 144:
/* Line 670 of lalr1.cc  */
#line 1589 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        int _num_of_statements = parseContext._number_of_statements.top();
                        parseContext._number_of_statements.pop();

                        vector<GeneralEvaluation*> _tmp_statements;
                        for ( int i = 0; i < _num_of_statements; i++ )
                        {
                            _tmp_statements.push_back( parseContext._statements.top() );
                            parseContext._statements.pop();
                        }
                        GeneralEvaluation* _condition = parseContext._stack.top();
                        parseContext._stack.pop();

                        WhileEvaluation* _while_calc = new WhileEvaluation( _condition );

                        for ( int i = _num_of_statements - 1; i >= 0; i-- )
                        {
                            _while_calc->addArgument( _tmp_statements[ i ] );
                        }
                        parseContext._statements.push( _while_calc );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 145:
/* Line 670 of lalr1.cc  */
#line 1618 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _value = parseContext._stack.top();
                        parseContext._stack.pop();
                        GeneralEvaluation* _index = parseContext._stack.top();
                        parseContext._stack.pop();
                        std::string _string = parseContext.string_constants.top();
                        parseContext.string_constants.pop();
                        AssignmentEvaluation* _assign_eval = new AssignmentEvaluation( _string, _index, _value, parseContext.cube->get_cubepl_memory_manager()  );
                        parseContext._statements.push( _assign_eval );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 148:
/* Line 670 of lalr1.cc  */
#line 1638 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext._stack.push( new ConstantEvaluation( 0 ) ); // pushed index 0 if array index is not specified
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 153:
/* Line 670 of lalr1.cc  */
#line 1658 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        std::string expression = parseContext.str.str();
                        parseContext.str.str( "" );
                        std::string uniq_name = parseContext.name_of_metric;
                        Metric*     _met      = parseContext.cube->get_met( uniq_name );
                        if ( _met == NULL )
                        {
                            _met = parseContext.cube->def_met( "",
                                                               uniq_name,
                                                               "DOUBLE",
                                                               "",
                                                               "",
                                                               "",
                                                               "",
                                                               NULL,
                                                               cube::CUBE_METRIC_POSTDERIVED,
                                                               expression,
                                                               "",
                                                               "",
                                                               "",
                                                               "",
                                                               true,
                                                               cube::CUBE_METRIC_GHOST
                                                               );
                        }
                        else
                        {
                            cout << " Metric with uniq name " << uniq_name << " already exists in cube" << endl;
                        }
                    }
                    else
                    {
                        std::string                  expression     = parseContext.str.str();
                        std::string                  cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
                        cubeplparser::CubePL1Driver* driver         = new cubeplparser::CubePL1Driver( parseContext.cube );       // create driver for this cube
                        std::string                  nested_error;
                        if ( !driver->test( cubepl_program, nested_error ) )
                        {
                            parseContext.syntax_ok &= false;
                        }
                        delete driver;
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 154:
/* Line 670 of lalr1.cc  */
#line 1705 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        std::string expression = parseContext.str.str();
                        parseContext.str.str( "" );
                        std::string uniq_name = parseContext.name_of_metric;
                        Metric*     _met      = parseContext.cube->get_met( uniq_name );
                        if ( _met == NULL )
                        {
                            _met = parseContext.cube->def_met( "",
                                                               uniq_name,
                                                               "DOUBLE",
                                                               "",
                                                               "",
                                                               "",
                                                               "",
                                                               NULL,
                                                               cube::CUBE_METRIC_PREDERIVED_INCLUSIVE,
                                                               expression,
                                                               "",
                                                               "",
                                                               "",
                                                               "",
                                                               true,
                                                               cube::CUBE_METRIC_GHOST
                                                               );
                        }
                        else
                        {
                            cout << " Metric with uniq name " << uniq_name << " already exists in cube" << endl;
                        }
                    }
                    else
                    {
                        std::string                  expression     = parseContext.str.str();
                        std::string                  cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
                        cubeplparser::CubePL1Driver* driver         = new cubeplparser::CubePL1Driver( parseContext.cube );         // create driver for this cube
                        std::string                  nested_error;
                        if ( !driver->test( cubepl_program, nested_error ) )
                        {
                            parseContext.syntax_ok = false;
                        }
                        delete driver;
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 155:
/* Line 670 of lalr1.cc  */
#line 1751 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        std::string expression = parseContext.str.str();
                        parseContext.str.str( "" );
                        std::string uniq_name = parseContext.name_of_metric;
                        Metric*     _met      = parseContext.cube->get_met( uniq_name );

                        if ( _met == NULL )
                        {
                            _met = parseContext.cube->def_met( "",
                                                               uniq_name,
                                                               "DOUBLE",
                                                               "",
                                                               "",
                                                               "",
                                                               "",
                                                               NULL,
                                                               cube::CUBE_METRIC_PREDERIVED_EXCLUSIVE,
                                                               expression,
                                                               "",
                                                               "",
                                                               "",
                                                               "",
                                                               true,
                                                               cube::CUBE_METRIC_GHOST
                                                               );
                        }
                        else
                        {
                            cout << " Metric with uniq name " << uniq_name << " already exists in cube" << endl;
                        }
                    }
                    else
                    {
                        std::string                  expression     = parseContext.str.str();
                        std::string                  cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
                        cubeplparser::CubePL1Driver* driver         = new cubeplparser::CubePL1Driver( parseContext.cube );           // create driver for this cube
                        std::string                  nested_error;
                        if ( !driver->test( cubepl_program, nested_error ) )
                        {
                            parseContext.syntax_ok = false;
                        }
                        delete driver;
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 158:
/* Line 670 of lalr1.cc  */
#line 1808 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        std::string expression = parseContext.str.str();
                        parseContext.str.str( "" );
                        std::string uniq_name = parseContext.name_of_metric;
                        Metric*     _met      = parseContext.cube->get_met( uniq_name );

                        if ( _met == NULL )
                        {
                            cout << " Metric with uniq name " << uniq_name << " doesn't  exists yet. Cannot assign CubePL initialization expression. Skip." << endl;
                        }
                        else
                        {
                            _met->set_init_expression( expression );
                        }
                    }
                    else
                    {
                        std::string                  expression     = parseContext.str.str();
                        std::string                  cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
                        cubeplparser::CubePL1Driver* driver         = new cubeplparser::CubePL1Driver( parseContext.cube ); // create driver for this cube
                        std::string                  nested_error;
                        if ( !driver->test( cubepl_program, nested_error ) )
                        {
                            parseContext.syntax_ok = false;
                        }
                        delete driver;
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 159:
/* Line 670 of lalr1.cc  */
#line 1840 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        std::string expression = parseContext.str.str();
                        parseContext.str.str( "" );
                        std::string uniq_name = parseContext.name_of_metric;
                        Metric*     _met      = parseContext.cube->get_met( uniq_name );

                        if ( _met == NULL )
                        {
                            cout << " Metric with uniq name " << uniq_name << " doesn't  exists yet. Cannot assign CubePL initialization expression. Skip." << endl;
                        }
                        else
                        {
                            _met->set_aggr_plus_expression( expression );
                        }
                    }
                    else
                    {
                        std::string                  expression     = parseContext.str.str();
                        std::string                  cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
                        cubeplparser::CubePL1Driver* driver         = new cubeplparser::CubePL1Driver( parseContext.cube ); // create driver for this cube
                        std::string                  nested_error;
                        if ( !driver->test( cubepl_program, nested_error ) )
                        {
                            parseContext.syntax_ok = false;
                        }
                        delete driver;
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 160:
/* Line 670 of lalr1.cc  */
#line 1872 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        std::string expression = parseContext.str.str();
                        parseContext.str.str( "" );
                        std::string uniq_name = parseContext.name_of_metric;
                        Metric*     _met      = parseContext.cube->get_met( uniq_name );

                        if ( _met == NULL )
                        {
                            cout << " Metric with uniq name " << uniq_name << " doesn't  exists yet. Cannot assign CubePL initialization expression. Skip." << endl;
                        }
                        else
                        {
                            _met->set_aggr_minus_expression( expression );
                        }
                    }
                    else
                    {
                        std::string                  expression     = parseContext.str.str();
                        std::string                  cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
                        cubeplparser::CubePL1Driver* driver         = new cubeplparser::CubePL1Driver( parseContext.cube ); // create driver for this cube
                        std::string                  nested_error;
                        if ( !driver->test( cubepl_program, nested_error ) )
                        {
                            parseContext.syntax_ok = false;
                        }
                        delete driver;
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 161:
/* Line 670 of lalr1.cc  */
#line 1906 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _index = parseContext._stack.top();
                        parseContext._stack.pop();
                        std::string _string = parseContext.string_constants.top();
                        parseContext.string_constants.pop();
                        VariableEvaluation* _var_eval = new VariableEvaluation(  _string, _index, parseContext.cube->get_cubepl_memory_manager()   );
                        parseContext._stack.push( _var_eval );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 162:
/* Line 670 of lalr1.cc  */
#line 1919 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        GeneralEvaluation* _index = parseContext._stack.top();
                        parseContext._stack.pop();
                        std::string _string = parseContext.string_constants.top();
                        parseContext.string_constants.pop();
                        VariableEvaluation* _var_eval = new VariableEvaluation(  _string, _index, parseContext.cube->get_cubepl_memory_manager()  );
                        parseContext._stack.push( _var_eval );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 163:
/* Line 670 of lalr1.cc  */
#line 1934 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext._stack.push( new ConstantEvaluation( 0 ) ); // pushed index 0 if array index is not specified
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 165:
/* Line 670 of lalr1.cc  */
#line 1947 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        std::string _string = parseContext.string_constants.top();
                        parseContext.string_constants.pop();
                        SizeOfVariableEvaluation* _sizeof_var_eval = new SizeOfVariableEvaluation(  _string, parseContext.cube->get_cubepl_memory_manager()  );
                        parseContext._stack.push( _sizeof_var_eval );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 166:
/* Line 670 of lalr1.cc  */
#line 1959 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        std::string _string = parseContext.string_constants.top();
                        parseContext.string_constants.pop();
                        DefinedVariableEvaluation* _sizeof_var_eval = new DefinedVariableEvaluation(  _string, parseContext.cube->get_cubepl_memory_manager()  );
                        parseContext._stack.push( _sizeof_var_eval );
                    }
                }
                break;

            case 167:
/* Line 670 of lalr1.cc  */
#line 1969 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        std::string _string = parseContext.string_constants.top();
                        parseContext.cube->get_cubepl_memory_manager()->register_variable( _string, CUBEPL_VARIABLE );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 168:
/* Line 670 of lalr1.cc  */
#line 1978 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        std::string _string = parseContext.string_constants.top();
                        parseContext.cube->get_cubepl_memory_manager()->register_variable( _string, CUBEPL_GLOBAL_VARIABLE );
                    }
                    parseContext.syntax_ok &= true;
                }
                break;

            case 169:
/* Line 670 of lalr1.cc  */
#line 1988 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
                {
                    if ( !parseContext.test_modus )
                    {
                        parseContext.string_constants.push( parseContext.value );
                        parseContext.value = "";
                    }
                    parseContext.syntax_ok &= true;
                }
                break;


/* Line 670 of lalr1.cc  */
#line 2357 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
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
CubePL1Parser::yysyntax_error_( int yystate, int yytoken )
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
const short int CubePL1Parser::yypact_ninf_ = -222;
const short int
CubePL1Parser::yypact_[] =
{
    18,   275,   7,     -222,  417,   417,   -222,  22,    49,    417,
    -222, -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
    -222, -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
    9,    -41,   -23,   -14,   60,    78,    96,    48,    -222,  -222,
    266,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
    -222, -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
    123,  -222,  124,   -222,  -222,  -222,  -222,  -222,  -222,  117,
    -222, -222,  -222,  -222,  -222,  -222,  5,     209,   62,    62,
    21,   62,    134,   135,   136,   417,   417,   417,   141,   -222,
    417,  417,   417,   417,   417,   417,   417,   142,   149,   150,
    153,  152,   81,    90,    91,    93,    99,    92,    168,   169,
    -222, -222,  -222,  -222,  -222,  -222,  175,   -222,  -222,  154,
    -222, -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
    -222, -222,  -222,  190,   199,   -222,  187,   -5,    24,    417,
    216,  224,   244,   131,   5,     5,     202,   202,   -222,  251,
    31,   62,    62,    346,   346,   62,    196,   267,   196,   196,
    196,  268,   417,   211,   117,   -222,  4,     117,   417,   -222,
    -222, 222,   -222,  -222,  -222,  -222,  13,    -222,  14,    47,
    -222, -222,  -222,  243,   -222,  417,   250,   257,   346,   270,
    -222, -222,  66,    76,    -222,  -222,  -222,  -222,  -222,  -222,
    -222, -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
    88,   261,   201,   -222,  -28,   -222,  -222,  -222,  131,   163,
    -222, -222,  272,   175,   237,   240,   -222,  276,   231,   417,
    -222, -39,   -222,  -39,   -39,   -222,  258,   -222,  -222,  11,
    94,   346,   417,   417,   417,   417,   417,   417,   417,   417,
    198,  -222,  346,   346,   346,   175,   278,   -222,  -222,  281,
    282,  229,   -222,  346,   -222,  -222,  -222,  -222,  191,   287,
    309,  32,    -222,  -222,  97,    231,   231,   231,   231,   231,
    231,  231,   231,   -222,  -222,  -222,  -222,  -222,  -222,  417,
    196,  196,   131,   119,   -222,  -222,  -222,  -222,  417,   -222,
    200,  -222,  -222,  310,   175,   120,   -222,  -222,  -222,  -39,
    311,  -222
};

/* YYDEFACT[S] -- default reduction number in state S.  Performed when
   YYTABLE doesn't specify something else to do.  Zero means the
   default is an error.  */
const unsigned char
CubePL1Parser::yydefact_[] =
{
    0,   0,     0,     3,     0,     0,     115,   0,     0,     0,
    33,  34,    79,    80,    81,    82,    83,    86,    87,    84,
    85,  89,    88,    90,    91,    92,    93,    94,    96,    97,
    0,   0,     0,     0,     0,     0,     0,     0,     98,    68,
    0,   4,     5,     6,     7,     8,     9,     10,    11,    18,
    31,  32,    20,    21,    69,    70,    71,    22,    12,    76,
    0,   77,    0,     13,    14,    99,    100,   101,   15,    116,
    19,  161,   162,   16,    17,    1,     30,    0,     0,     0,
    0,   0,     0,     0,     0,     0,     0,     0,     0,     2,
    0,   0,     0,     0,     0,     0,     0,     0,     0,     0,
    0,   0,     0,     0,     0,     0,     0,     0,     0,     0,
    123, 118,   129,   130,   132,   131,   0,     119,   120,   0,
    146, 147,   124,   150,   151,   152,   125,   126,   127,   121,
    122, 23,    169,   0,     0,     24,    0,     0,     0,     0,
    0,   0,     0,     0,     25,    26,    28,    27,    29,    0,
    0,   0,     0,     0,     0,     0,     0,     0,     0,     0,
    0,   0,     0,     0,     116,   143,   133,   116,   0,     165,
    166, 163,   102,   110,   111,   112,   0,     105,   0,     0,
    74,  72,    73,    0,     78,    0,     0,     0,     0,     0,
    53,  54,    0,     0,     35,    42,    43,    44,    45,    46,
    36,  37,    38,    39,    40,    41,    47,    61,    62,    63,
    0,   0,     0,     153,   0,     158,   159,   160,   0,     0,
    113, 117,   0,     0,     136,   137,   134,   0,     145,   0,
    103, 0,     106,   0,     0,     75,    0,     167,   168,   0,
    0,   0,     0,     0,     0,     0,     0,     0,     0,     0,
    0,   140,   0,     0,     0,     0,     148,   157,   156,   0,
    0,   0,     114,   0,     141,   135,   138,   142,   0,     0,
    0,   0,     95,    48,    0,     57,    55,    64,    65,    59,
    60,  56,    58,    67,    66,    50,    51,    52,    144,   0,
    0,   0,     0,     0,     164,   104,   107,   108,   0,     49,
    0,   154,   155,   0,     0,     0,     149,   128,   139,   0,
    0,   109
};

/* YYPGOTO[NTERM-NUM].  */
const short int
CubePL1Parser::yypgoto_[] =
{
    -222, -222,  -1,    -222,  -222,  -222,  -222,  -222,  -222,  -222,
    -222, -222,  -222,  -222,  -139,  -222,  -222,  -222,  -222,  -222,
    -222, -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
    -222, -222,  -142,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
    -222, -222,  -222,  -222,  -222,  -222,  -222,  -222,  -133,  -222,
    -222, -222,  -123,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
    98,   -222,  -222,  100,   -221,  -222,  -222,  -222,  -222,  -222,
    -222, -222,  -222,  -222,  -222,  -149,  -222,  -222,  -222,  -222,
    -222, -222,  -222,  -222,  -222,  -222,  -222,  -48
};

/* YYDEFGOTO[NTERM-NUM].  */
const short int
CubePL1Parser::yydefgoto_[] =
{
    -1,  2,     192,   41,    42,    43,    44,    45,    46,    47,
    48,  49,    50,    51,    193,   194,   195,   196,   197,   198,
    199, 200,   201,   202,   203,   204,   205,   206,   207,   208,
    209, 284,   52,    53,    54,    55,    56,    57,    58,    59,
    60,  61,    62,    63,    64,    65,    66,    67,    176,   68,
    163, 69,    108,   109,   110,   111,   112,   113,   114,   115,
    224, 225,   116,   226,   166,   167,   117,   118,   119,   120,
    121, 122,   123,   124,   125,   213,   258,   126,   127,   128,
    70,  71,    72,    73,    74,    129,   130,   133
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF_, syntax error.  */
const signed char CubePL1Parser::yytable_ninf_ = -1;
const unsigned short int
CubePL1Parser::yytable_[] =
{
    40,  183,   264,   76,    77,    178,   172,   75,    80,    215,
    216, 217,   92,    93,    94,    210,   90,    91,    92,    93,
    94,  1,     131,   81,    230,   232,   90,    91,    92,    93,
    94,  134,   78,    136,   288,   177,   90,    91,    92,    93,
    94,  221,   82,    297,   227,   135,   173,   174,   175,   240,
    222, 223,   90,    91,    92,    93,    94,    259,   260,   79,
    83,  242,   243,   244,   245,   246,   247,   248,   249,   84,
    85,  90,    91,    92,    93,    94,    261,   250,   231,   233,
    173, 174,   175,   308,   140,   141,   142,   251,   86,    144,
    145, 146,   147,   148,   149,   150,   185,   298,   269,   255,
    270, 271,   274,   186,   187,   273,   87,    211,   299,   173,
    174, 175,   234,   285,   286,   287,   242,   243,   244,   245,
    246, 247,   248,   249,   293,   90,    91,    92,    93,    94,
    304, 88,    250,   95,    96,    252,   253,   254,   179,   97,
    98,  301,   302,   132,   137,   138,   139,   252,   253,   254,
    303, 143,   151,   252,   253,   254,   252,   253,   254,   152,
    153, 219,   99,    154,   156,   100,   155,   228,   90,    91,
    92,  93,    94,    157,   158,   161,   310,   159,   252,   253,
    254, 101,   262,   160,   236,   309,   162,   239,   164,   165,
    102, 103,   104,   105,   106,   107,   90,    91,    92,    93,
    94,  169,   171,   168,   294,   90,    91,    92,    93,    94,
    170, 94,    212,   306,   90,    91,    92,    93,    94,    39,
    131, 90,    91,    92,    93,    94,    220,   180,   268,   90,
    91,  92,    93,    94,    229,   181,   90,    91,    92,    93,
    94,  275,   276,   277,   278,   279,   280,   281,   282,   90,
    91,  92,    93,    94,    235,   182,   90,    91,    92,    93,
    94,  237,   184,   90,    91,    92,    93,    94,    238,   272,
    89,  90,    91,    92,    93,    94,    256,   214,   218,   3,
    241, 4,     263,   257,   223,   5,     222,   283,   300,   6,
    289, 267,   290,   291,   292,   7,     8,     305,   295,   9,
    10,  11,    12,    13,    14,    15,    16,    17,    18,    19,
    20,  21,    22,    23,    24,    25,    26,    27,    28,    29,
    296, 307,   311,   266,   265,   0,     0,     0,     0,     0,
    0,   0,     0,     0,     0,     0,     0,     0,     0,     30,
    0,   0,     31,    32,    33,    34,    35,    36,    0,     0,
    0,   0,     4,     0,     37,    38,    188,   0,     0,     0,
    6,   0,     0,     39,    0,     0,     7,     8,     0,     0,
    9,   10,    11,    12,    13,    14,    15,    16,    17,    18,
    19,  20,    21,    22,    23,    24,    25,    26,    27,    28,
    29,  0,     0,     0,     0,     0,     0,     0,     0,     0,
    0,   0,     0,     0,     189,   0,     0,     0,     190,   191,
    30,  0,     0,     31,    32,    33,    34,    35,    36,    0,
    0,   0,     0,     4,     0,     37,    38,    5,     0,     0,
    0,   6,     0,     0,     39,    0,     0,     7,     8,     0,
    0,   9,     10,    11,    12,    13,    14,    15,    16,    17,
    18,  19,    20,    21,    22,    23,    24,    25,    26,    27,
    28,  29,    0,     0,     0,     0,     0,     0,     0,     0,
    0,   0,     0,     0,     0,     0,     0,     0,     0,     0,
    0,   30,    0,     0,     31,    32,    33,    34,    35,    36,
    0,   0,     0,     0,     0,     0,     37,    38,    0,     0,
    0,   0,     0,     0,     0,     39
};

/* YYCHECK.  */
const short int
CubePL1Parser::yycheck_[] =
{
    1,   143,   223,   4,     5,     138,   11,    0,     9,     158,
    159, 160,   7,     8,     9,     154,   5,     6,     7,     8,
    9,   3,     11,    14,    11,    11,    5,     6,     7,     8,
    9,   79,    10,    81,    255,   11,    5,     6,     7,     8,
    9,   164,   83,    11,    167,   24,    85,    86,    87,    188,
    46,  47,    5,     6,     7,     8,     9,     85,    86,    10,
    83,  50,    51,    52,    53,    54,    55,    56,    57,    83,
    10,  5,     6,     7,     8,     9,     218,   66,    65,    65,
    85,  86,    87,    304,   85,    86,    87,    11,    10,    90,
    91,  92,    93,    94,    95,    96,    65,    65,    231,   11,
    233, 234,   241,   151,   152,   11,    10,    155,   11,    85,
    86,  87,    65,    252,   253,   254,   50,    51,    52,    53,
    54,  55,    56,    57,    263,   5,     6,     7,     8,     9,
    11,  83,    66,    10,    10,    59,    60,    61,    139,   22,
    23,  290,   291,   81,    10,    10,    10,    59,    60,    61,
    292, 10,    10,    59,    60,    61,    59,    60,    61,    10,
    10,  162,   45,    10,    83,    48,    14,    168,   5,     6,
    7,   8,     9,     83,    83,    83,    309,   84,    59,    60,
    61,  64,    19,    84,    185,   65,    18,    188,   19,    14,
    73,  74,    75,    76,    77,    78,    5,     6,     7,     8,
    9,   11,    15,    49,    13,    5,     6,     7,     8,     9,
    11,  9,     16,    13,    5,     6,     7,     8,     9,     88,
    11,  5,     6,     7,     8,     9,     15,    11,    229,   5,
    6,   7,     8,     9,     12,    11,    5,     6,     7,     8,
    9,   242,   243,   244,   245,   246,   247,   248,   249,   5,
    6,   7,     8,     9,     11,    11,    5,     6,     7,     8,
    9,   11,    11,    5,     6,     7,     8,     9,     11,    11,
    4,   5,     6,     7,     8,     9,     15,    10,    10,    4,
    10,  6,     10,    82,    47,    10,    46,    89,    289,   14,
    12,  15,    11,    11,    65,    20,    21,    298,   11,    24,
    25,  26,    27,    28,    29,    30,    31,    32,    33,    34,
    35,  36,    37,    38,    39,    40,    41,    42,    43,    44,
    11,  11,    11,    225,   224,   -1,    -1,    -1,    -1,    -1,
    -1,  -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
    -1,  -1,    67,    68,    69,    70,    71,    72,    -1,    -1,
    -1,  -1,    6,     -1,    79,    80,    10,    -1,    -1,    -1,
    14,  -1,    -1,    88,    -1,    -1,    20,    21,    -1,    -1,
    24,  25,    26,    27,    28,    29,    30,    31,    32,    33,
    34,  35,    36,    37,    38,    39,    40,    41,    42,    43,
    44,  -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,  -1,    -1,    -1,    58,    -1,    -1,    -1,    62,    63,
    64,  -1,    -1,    67,    68,    69,    70,    71,    72,    -1,
    -1,  -1,    -1,    6,     -1,    79,    80,    10,    -1,    -1,
    -1,  14,    -1,    -1,    88,    -1,    -1,    20,    21,    -1,
    -1,  24,    25,    26,    27,    28,    29,    30,    31,    32,
    33,  34,    35,    36,    37,    38,    39,    40,    41,    42,
    43,  44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,  -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,  64,    -1,    -1,    67,    68,    69,    70,    71,    72,
    -1,  -1,    -1,    -1,    -1,    -1,    79,    80,    -1,    -1,
    -1,  -1,    -1,    -1,    -1,    88
};

/* STOS_[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
const unsigned char
CubePL1Parser::yystos_[] =
{
    0,   3,     93,    4,     6,     10,    14,    20,    21,    24,
    25,  26,    27,    28,    29,    30,    31,    32,    33,    34,
    35,  36,    37,    38,    39,    40,    41,    42,    43,    44,
    64,  67,    68,    69,    70,    71,    72,    79,    80,    88,
    94,  95,    96,    97,    98,    99,    100,   101,   102,   103,
    104, 105,   124,   125,   126,   127,   128,   129,   130,   131,
    132, 133,   134,   135,   136,   137,   138,   139,   141,   143,
    172, 173,   174,   175,   176,   0,     94,    94,    10,    10,
    94,  14,    83,    83,    83,    10,    10,    10,    83,    4,
    5,   6,     7,     8,     9,     10,    10,    22,    23,    45,
    48,  64,    73,    74,    75,    76,    77,    78,    144,   145,
    146, 147,   148,   149,   150,   151,   154,   158,   159,   160,
    161, 162,   163,   164,   165,   166,   169,   170,   171,   177,
    178, 11,    81,    179,   179,   24,    179,   10,    10,    10,
    94,  94,    94,    10,    94,    94,    94,    94,    94,    94,
    94,  10,    10,    10,    10,    14,    83,    83,    83,    84,
    84,  83,    18,    142,   19,    14,    156,   157,   49,    11,
    11,  15,    11,    85,    86,    87,    140,   11,    140,   94,
    11,  11,    11,    124,   11,    65,    179,   179,   10,    58,
    62,  63,    94,    106,   107,   108,   109,   110,   111,   112,
    113, 114,   115,   116,   117,   118,   119,   120,   121,   122,
    106, 179,   16,    167,   10,    167,   167,   167,   10,    94,
    15,  144,   46,    47,    152,   153,   155,   144,   94,    12,
    11,  65,    11,    65,    65,    11,    94,    11,    11,    94,
    106, 10,    50,    51,    52,    53,    54,    55,    56,    57,
    66,  11,    59,    60,    61,    11,    15,    82,    168,   85,
    86,  124,   19,    10,    156,   155,   152,   15,    94,    140,
    140, 140,   11,    11,    106,   94,    94,    94,    94,    94,
    94,  94,    94,    89,    123,   106,   106,   106,   156,   12,
    11,  11,    65,    106,   13,    11,    11,    11,    65,    11,
    94,  167,   167,   124,   11,    94,    13,    11,    156,   65,
    140, 11
};

#if CUBEPLPARSERDEBUG
/* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
   to YYLEX-NUM.  */
const unsigned short int
CubePL1Parser::yytoken_number_[] =
{
    0,   256,   601,   602,   603,   604,   605,   606,   607,   608,
    609, 610,   611,   612,   613,   614,   615,   616,   617,   618,
    619, 620,   621,   622,   623,   624,   625,   626,   627,   628,
    629, 630,   631,   632,   633,   634,   635,   636,   637,   638,
    639, 640,   641,   642,   643,   644,   645,   646,   647,   648,
    649, 650,   651,   652,   653,   654,   655,   656,   657,   658,
    659, 660,   661,   662,   663,   664,   665,   666,   667,   668,
    669, 670,   671,   672,   673,   674,   675,   676,   677,   678,
    100, 200,   210,   300,   301,   679,   680,   600,   400,   500,
    681, 682
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
const unsigned char
CubePL1Parser::yyr1_[] =
{
    0,   92,    93,    93,    94,    94,    94,    94,    94,    94,
    94,  94,    94,    94,    94,    94,    94,    94,    94,    94,
    94,  94,    94,    95,    96,    97,    98,    99,    100,   101,
    102, 103,   103,   104,   105,   106,   106,   106,   106,   106,
    106, 106,   106,   106,   106,   106,   106,   106,   107,   107,
    108, 109,   110,   111,   112,   113,   114,   115,   116,   117,
    118, 119,   119,   119,   120,   121,   122,   123,   124,   125,
    125, 125,   126,   127,   128,   129,   130,   130,   131,   132,
    132, 132,   132,   132,   132,   132,   132,   132,   132,   132,
    132, 132,   132,   132,   132,   133,   134,   134,   135,   136,
    136, 136,   137,   137,   137,   138,   138,   138,   139,   139,
    140, 140,   140,   141,   142,   143,   144,   144,   145,   145,
    145, 145,   145,   145,   145,   145,   145,   145,   146,   147,
    147, 147,   147,   148,   149,   150,   151,   152,   152,   153,
    154, 155,   156,   157,   158,   159,   160,   160,   161,   162,
    163, 163,   163,   164,   165,   166,   167,   168,   169,   170,
    171, 172,   172,   173,   174,   175,   176,   177,   178,   179
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
const unsigned char
CubePL1Parser::yyr2_[] =
{
    0, 2,     3,     2,     1,     1,     1,     1,     1,     1,
    1, 1,     1,     1,     1,     1,     1,     1,     1,     1,
    1, 1,     1,     3,     3,     3,     3,     3,     3,     3,
    2, 1,     1,     1,     1,     1,     1,     1,     1,     1,
    1, 1,     1,     1,     1,     1,     1,     1,     3,     4,
    3, 3,     3,     1,     1,     3,     3,     3,     3,     3,
    3, 1,     1,     1,     3,     3,     3,     1,     1,     1,
    1, 1,     4,     4,     4,     5,     1,     1,     4,     1,
    1, 1,     1,     1,     1,     1,     1,     1,     1,     1,
    1, 1,     1,     1,     1,     6,     1,     1,     1,     1,
    1, 1,     4,     5,     7,     4,     5,     7,     7,     11,
    1, 1,     1,     4,     3,     1,     0,     3,     1,     1,
    1, 1,     1,     1,     1,     1,     1,     1,     7,     1,
    1, 1,     1,     2,     3,     4,     3,     1,     2,     5,
    4, 2,     3,     1,     5,     3,     1,     1,     4,     7,
    1, 1,     1,     3,     6,     6,     2,     1,     3,     3,
    3, 1,     1,     4,     7,     4,     4,     4,     4,     1
};


/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
const char*
const CubePL1Parser::yytname_[] =
{
    "\"end of file\"",                          "error",                           "$undefined",                      "\"<cubepl>\"",
    "\"</cubepl>\"",                            "\"+\"",                           "\"-\"",                           "\"*\"",           "\"/\"",          "\"^\"",      "\"(\"",
    "\")\"",                                    "\"[\"",                           "\"]\"",                           "\"{\"",           "\"}\"",          "\"<<\"",     "\">>\"",
    "\"return\"",                               "\";\"",                           "\"sizeof\"",                      "\"defined\"",     "\"local\"",
    "\"global\"",                               "\"|\"",                           "\"arg1\"",                        "\"arg2\"",        "\"sqrt\"",       "\"sin\"",
    "\"asin\"",                                 "\"cos\"",                         "\"acos\"",                        "\"tan\"",         "\"atan\"",       "\"exp\"",
    "\"log\"",                                  "\"abs\"",                         "\"random\"",                      "\"sgn\"",         "\"pos\"",        "\"neg\"",
    "\"floor\"",                                "\"ceil\"",                        "\"min\"",                         "\"max\"",         "\"if\"",         "\"elseif\"",
    "\"else\"",                                 "\"while\"",                       "\"=\"",                           "\">\"",           "\"==\"",         "\"eq\"",     "\"seq\"",
    "\">=\"",                                   "\"<=\"",                          "\"!=\"",                          "\"<\"",           "\"not\"",        "\"and\"",    "\"or\"",
    "\"xor\"",                                  "\"true\"",                        "\"false\"",                       "\"$\"",           "\",\"",          "\"=~\"",
    "\"metric::\"",                             "\"metric::fixed::\"",             "\"metric::call::\"",              "\"env\"",
    "\"lowercase\"",                            "\"uppercase\"",                   "\"cube::metric::postderived::\"",
    "\"cube::metric::prederived::\"",           "\"cube::init::metric::\"",
    "\"cube::metric::plus::\"",                 "\"cube::metric::minus::\"",
    "\"cube::metric::set::\"",                  "\"cube::metric::get::\"",         "CONSTANT",
    "STRING_CONSTANT",                          "STRING_TEXT",                     "METRIC_NAME",                     "INIT_METRIC_NAME",
    "\"i\"",                                    "\"e\"",                           "SAME_MODIFICATOR",                "QUOTED_STRING",   "REGEXP_STRING",
    "FUNC2",                                    "SIGN",                            "$accept",                         "document",        "expression",
    "enclosed_expression",                      "absolute_value",                  "sum",                             "subtract",        "division",
    "multiplication",                           "power",                           "negation",                        "arguments",       "argument1",
    "argument2",                                "boolean_expression",              "enclosed_boolean_expression",
    "and_expression",                           "or_expression",                   "xor_expression",                  "true_expression",
    "false_expression",                         "equality",                        "not_equality",                    "bigger",          "smaller",
    "halfbigger",                               "halfsmaller",                     "string_operation",                "string_equality",
    "string_semi_equality",                     "regexp",                          "regexp_expression",               "quoted_string",
    "string_function",                          "lowercase",                       "uppercase",                       "getenv",          "metric_get",
    "function_call",                            "one_variable_function",           "function_name",
    "two_variables_function",                   "function2_name",                  "constant",                        "metric_refs",
    "context_metric",                           "fixed_metric",                    "metric_call",
    "calculationFlavourModificator",            "lambda_calcul",                   "return_expression",
    "lambda_start",                             "list_of_statements",              "statement",                       "metric_set",
    "if_statement",                             "simple_if_statement",             "full_if_statement",
    "elseif_full_if_statement",                 "elseif_if_statement",             "elseifs",
    "elseif_enclosed_list_of_statements",       "if_condition",
    "else_enclosed_list_of_statements",         "enclosed_list_of_statements",
    "enclosed_list_of_statements_start",        "while_statement",                 "assignment",
    "assignment_target",                        "put_variable",                    "put_variable_indexed",
    "create_ghost_metric",                      "create_postderived_ghost_metric",
    "create_prederived_inclusive_ghost_metric",
    "create_prederived_exclusive_ghost_metric", "GhostMetricDefinition",
    "CubePLGhostText",                          "init_metric",                     "flex_aggr_plus",                  "flex_aggr_minus",
    "get_variable",                             "get_variable_simple",             "get_variable_indexed",
    "sizeof_variable",                          "defined_variable",                "local_variable",
    "global_variable",                          "string_constant",                 YY_NULL
};

#if CUBEPLPARSERDEBUG
/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
const CubePL1Parser::rhs_number_type
CubePL1Parser::yyrhs_[] =
{
    93,  0,     -1,    3,     94,    4,     -1,    3,     4,     -1,
    95,  -1,    96,    -1,    97,    -1,    98,    -1,    99,    -1,
    100, -1,    101,   -1,    102,   -1,    130,   -1,    135,   -1,
    136, -1,    141,   -1,    175,   -1,    176,   -1,    103,   -1,
    172, -1,    124,   -1,    125,   -1,    129,   -1,    10,    94,
    11,  -1,    24,    94,    24,    -1,    94,    5,     94,    -1,
    94,  6,     94,    -1,    94,    8,     94,    -1,    94,    7,
    94,  -1,    94,    9,     94,    -1,    6,     94,    -1,    104,
    -1,  105,   -1,    25,    -1,    26,    -1,    107,   -1,    113,
    -1,  114,   -1,    115,   -1,    116,   -1,    117,   -1,    118,
    -1,  108,   -1,    109,   -1,    110,   -1,    111,   -1,    112,
    -1,  119,   -1,    10,    106,   11,    -1,    58,    10,    106,
    11,  -1,    106,   59,    106,   -1,    106,   60,    106,   -1,
    106, 61,    106,   -1,    62,    -1,    63,    -1,    94,    51,
    94,  -1,    94,    56,    94,    -1,    94,    50,    94,    -1,
    94,  57,    94,    -1,    94,    54,    94,    -1,    94,    55,
    94,  -1,    120,   -1,    121,   -1,    122,   -1,    94,    52,
    94,  -1,    94,    53,    94,    -1,    94,    66,    123,   -1,
    89,  -1,    88,    -1,    126,   -1,    127,   -1,    128,   -1,
    71,  10,    94,    11,    -1,    72,    10,    94,    11,    -1,
    70,  10,    94,    11,    -1,    79,    83,    10,    124,   11,
    -1,  131,   -1,    133,   -1,    132,   10,    94,    11,    -1,
    27,  -1,    28,    -1,    29,    -1,    30,    -1,    31,    -1,
    34,  -1,    35,    -1,    32,    -1,    33,    -1,    37,    -1,
    36,  -1,    38,    -1,    39,    -1,    40,    -1,    41,    -1,
    42,  -1,    134,   10,    94,    65,    94,    11,    -1,    43,
    -1,  44,    -1,    80,    -1,    137,   -1,    138,   -1,    139,
    -1,  67,    83,    10,    11,    -1,    67,    83,    10,    140,
    11,  -1,    67,    83,    10,    140,   65,    140,   11,    -1,
    68,  83,    10,    11,    -1,    68,    83,    10,    140,   11,
    -1,  68,    83,    10,    140,   65,    140,   11,    -1,    69,
    83,  10,    94,    65,    140,   11,    -1,    69,    83,    10,
    94,  65,    140,   65,    94,    65,    140,   11,    -1,    85,
    -1,  86,    -1,    87,    -1,    143,   144,   142,   15,    -1,
    18,  94,    19,    -1,    14,    -1,    -1,    145,   19,    144,
    -1,  147,   -1,    158,   -1,    159,   -1,    177,   -1,    178,
    -1,  146,   -1,    163,   -1,    169,   -1,    170,   -1,    171,
    -1,  78,    83,    10,    124,   65,    124,   11,    -1,    148,
    -1,  149,   -1,    151,   -1,    150,   -1,    154,   156,   -1,
    154, 156,   155,   -1,    154,   156,   152,   155,   -1,    154,
    156, 152,   -1,    153,   -1,    153,   152,   -1,    46,    10,
    106, 11,    156,   -1,    45,    10,    106,   11,    -1,    47,
    156, -1,    157,   144,   15,    -1,    14,    -1,    48,    10,
    106, 11,    156,   -1,    160,   49,    94,    -1,    161,   -1,
    162, -1,    64,    14,    179,   15,    -1,    64,    14,    179,
    15,  12,    94,    13,    -1,    164,   -1,    165,   -1,    166,
    -1,  73,    83,    167,   -1,    74,    83,    10,    85,    11,
    167, -1,    74,    83,    10,    86,    11,    167,   -1,    16,
    168, -1,    82,    -1,    75,    83,    167,   -1,    76,    84,
    167, -1,    77,    84,    167,   -1,    173,   -1,    174,   -1,
    64,  14,    179,   15,    -1,    64,    14,    179,   15,    12,
    94,  13,    -1,    20,    10,    179,   11,    -1,    21,    10,
    179, 11,    -1,    22,    10,    179,   11,    -1,    23,    10,
    179, 11,    -1,    81,    -1
};

/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
const unsigned short int
CubePL1Parser::yyprhs_[] =
{
    0,   0,     3,     7,     10,    12,    14,    16,    18,    20,
    22,  24,    26,    28,    30,    32,    34,    36,    38,    40,
    42,  44,    46,    48,    52,    56,    60,    64,    68,    72,
    76,  79,    81,    83,    85,    87,    89,    91,    93,    95,
    97,  99,    101,   103,   105,   107,   109,   111,   113,   117,
    122, 126,   130,   134,   136,   138,   142,   146,   150,   154,
    158, 162,   164,   166,   168,   172,   176,   180,   182,   184,
    186, 188,   190,   195,   200,   205,   211,   213,   215,   220,
    222, 224,   226,   228,   230,   232,   234,   236,   238,   240,
    242, 244,   246,   248,   250,   252,   259,   261,   263,   265,
    267, 269,   271,   276,   282,   290,   295,   301,   309,   317,
    329, 331,   333,   335,   340,   344,   346,   347,   351,   353,
    355, 357,   359,   361,   363,   365,   367,   369,   371,   379,
    381, 383,   385,   387,   390,   394,   399,   403,   405,   408,
    414, 419,   422,   426,   428,   434,   438,   440,   442,   447,
    455, 457,   459,   461,   465,   472,   479,   482,   484,   488,
    492, 496,   498,   500,   505,   513,   518,   523,   528,   533
};

/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
const unsigned short int
CubePL1Parser::yyrline_[] =
{
    0,    311,   311,   320,   327,   328,   329,   330,   331,   332,
    333,  334,   335,   336,   337,   338,   339,   340,   341,   342,
    343,  344,   345,   349,   359,   372,   385,   399,   412,   428,
    440,  452,   452,   454,   463,   475,   476,   477,   478,   479,
    480,  481,   482,   483,   484,   485,   486,   487,   491,   501,
    512,  525,   539,   552,   560,   569,   583,   597,   610,   624,
    638,  654,   655,   656,   661,   674,   686,   701,   723,   734,
    734,  734,   739,   750,   762,   776,   799,   799,   801,   816,
    824,  832,   840,   848,   856,   864,   872,   880,   888,   896,
    904,  912,   920,   928,   936,   947,   963,   971,   982,   993,
    993,  993,   998,   1018,  1040,  1068,  1088,  1117,  1154,  1189,
    1236, 1244,  1252,  1263,  1293,  1295,  1304,  1306,  1312,  1323,
    1334, 1345,  1349,  1353,  1364,  1368,  1372,  1376,  1382,  1406,
    1407, 1408,  1409,  1413,  1440,  1479,  1522,  1555,  1556,  1559,
    1569, 1572,  1575,  1578,  1588,  1617,  1634,  1634,  1637,  1647,
    1651, 1652,  1653,  1657,  1704,  1750,  1798,  1801,  1807,  1839,
    1871, 1905,  1918,  1933,  1942,  1946,  1958,  1968,  1977,  1987
};

// Print the state stack on the debug stream.
void
CubePL1Parser::yystack_print_()
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
CubePL1Parser::yy_reduce_print_( int yyrule )
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
#endif // CUBEPLPARSERDEBUG

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
CubePL1Parser::token_number_type
CubePL1Parser::yytranslate_( int t )
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
        80, 2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        81, 2,     2,     2,     2,     2,     2,     2,     2,     2,
        82, 2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     1,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        83, 84,    2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        88, 2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        89, 2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,  2,     2,     2,     2,     2,     2,     2,     2,     2,
        87, 2,     3,     4,     5,     6,     7,     8,     9,     10,
        11, 12,    13,    14,    15,    16,    17,    18,    19,    20,
        21, 22,    23,    24,    25,    26,    27,    28,    29,    30,
        31, 32,    33,    34,    35,    36,    37,    38,    39,    40,
        41, 42,    43,    44,    45,    46,    47,    48,    49,    50,
        51, 52,    53,    54,    55,    56,    57,    58,    59,    60,
        61, 62,    63,    64,    65,    66,    67,    68,    69,    70,
        71, 72,    73,    74,    75,    76,    77,    78,    79,    85,
        86, 90,    91
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

const int CubePL1Parser::yyeof_     = 0;
const int CubePL1Parser::yylast_    = 505;
const int CubePL1Parser::yynnts_    = 88;
const int CubePL1Parser::yyempty_   = -2;
const int CubePL1Parser::yyfinal_   = 75;
const int CubePL1Parser::yyterror_  = 1;
const int CubePL1Parser::yyerrcode_ = 256;
const int CubePL1Parser::yyntokens_ = 92;

const unsigned int                     CubePL1Parser::yyuser_token_number_max_ = 682;
const CubePL1Parser::token_number_type CubePL1Parser::yyundef_token_           = 2;
} // cubeplparser
/* Line 1141 of lalr1.cc  */
#line 3275 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.cpp"
/* Line 1142 of lalr1.cc  */
#line 1997 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
/*** Additional Code ***/


void
cubeplparser::CubePL1Parser::error( const CubePL1Parser::location_type& l,
                                    const std::string&                  m )
{
    CubePL1Parser::location_type _l = l;


    _l.end.column   = ( _l.end.column < 9 ) ? 1 : _l.end.column - 8;
    _l.begin.column = _l.end.column - 1;

    parseContext.syntax_ok = false;
    stringstream sstr;
    string str;
    sstr << _l;
    sstr >> str;
    parseContext.error_message = str + ":" + m;
    parseContext.error_place   = _l;

/*   if (strstr(m.c_str(),"expecting <?xml")!=NULL) {
     driver.error_just_message("The cube file is probably empty or filled with wrong content. The file has ended before the header of cube started. \n");
    }
   if (strstr(m.c_str()," expecting </row>")!=NULL) {
     driver.error_just_message("One of the possible reasons is \n    1) that the severity value is malformed. CUBE expects the \"double\" value in C_LOCALE with dot instead of comma;. \n    2) that the CUBE file is not properly ended. Probably the writing of CUBE file was interrupted.");
    }
   if (strstr(m.c_str()," expecting <matrix")!=NULL ||
        (strstr(m.c_str()," expecting <severity>")!=NULL) ) {
     driver.error_just_message("The cube file has probably a proper structure, but doesn't contain any severity values.");
    }
   if (strstr(m.c_str()," expecting <metric")!=NULL) {
     driver.error_just_message("The cube file doesn't contain any information about metric dimension.");
    }
   if (strstr(m.c_str()," expecting <region")!=NULL) {
     driver.error_just_message("The cube file doesn't contain any information about program dimension.");
    }
   if (strstr(m.c_str()," expecting <machine")!=NULL) {
     driver.error_just_message("The cube file doesn't contain any information about system dimension.");
    }
   if (strstr(m.c_str()," expecting <thread")!=NULL) {
     driver.error_just_message("The system dimension of the cube file is malformed. It contains a process without any threads.");
    }
   if (strstr(m.c_str()," expecting <process")!=NULL) {
     driver.error_just_message("The system dimension of the cube file is malformed. It contains a node without any processes.");
    }
   if (strstr(m.c_str()," expecting <node")!=NULL) {
     driver.error_just_message("The system dimension of the cube file is malformed. It contains a machine without any computing nodes.");
    }
      driver.error(l, m);
 */
}
