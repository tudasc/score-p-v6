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
#line 40 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"


#include "CubePL0Parser.h"

/* User implementation prologue.  */
/* Line 285 of lalr1.cc  */
#line 248 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"

#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"
#include "CubePL0Scanner.h"
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
#include "CubePL0ParseContext.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex CubePl0Lexer.lex

// Workaround for Sun Studio C++ compilers on Solaris
#if defined(__SVR4) &&  defined(__SUNPRO_CC)
  #include <ieeefp.h>

  #define isinf(x)  (fpclass(x) == FP_NINF || fpclass(x) == FP_PINF)
  #define isnan(x)  isnand(x)
#endif


/* Line 285 of lalr1.cc  */
#line 87 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"


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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if CUBEPLPARSERDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !CUBEPLPARSERDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location) YYUSE(Type)
# define YY_REDUCE_PRINT(Rule)        static_cast<void>(0)
# define YY_STACK_PRINT()             static_cast<void>(0)

#endif /* !CUBEPLPARSERDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace cubeplparser {
/* Line 353 of lalr1.cc  */
#line 182 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  CubePL0Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  CubePL0Parser::CubePL0Parser (class CubePL0ParseContext& parseContext_yyarg, class CubePL0Scanner& CubePl0Lexer_yyarg)
    :
#if CUBEPLPARSERDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      parseContext (parseContext_yyarg),
      CubePl0Lexer (CubePl0Lexer_yyarg)
  {
  }

  CubePL0Parser::~CubePL0Parser ()
  {
  }

#if CUBEPLPARSERDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  CubePL0Parser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    std::ostream& yyo = debug_stream ();
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  CubePL0Parser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  CubePL0Parser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
  
	default:
	  break;
      }
  }

  void
  CubePL0Parser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

#if CUBEPLPARSERDEBUG
  std::ostream&
  CubePL0Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  CubePL0Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  CubePL0Parser::debug_level_type
  CubePL0Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  CubePL0Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  inline bool
  CubePL0Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  CubePL0Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  CubePL0Parser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    // State.
    int yyn;
    int yylen = 0;
    int yystate = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    static semantic_type yyval_default;
    semantic_type yylval = yyval_default;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[3];

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
#line 138 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
{
    // initialize the initial location object
}
/* Line 545 of lalr1.cc  */
#line 383 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"

    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
        YYCDEBUG << "Reading a token: ";
        yychar = yylex (&yylval, &yylloc);
      }

    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yy_table_value_is_error_ (yyn))
	  goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    // Compute the default @$.
    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }

    // Perform the reduction.
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
          case 2:
/* Line 670 of lalr1.cc  */
#line 297 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
	    if (!parseContext.test_modus)
	    {
		parseContext.result = parseContext._stack.top();
		parseContext._stack.pop();
    	    }
    	    parseContext.syntax_ok &= true;
	}
    break;

  case 3:
/* Line 670 of lalr1.cc  */
#line 306 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
    	    parseContext.syntax_ok &= true;
	}
    break;

  case 19:
/* Line 670 of lalr1.cc  */
#line 331 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    GeneralEvaluation * _arg1 = parseContext._stack.top();
		    parseContext._stack.pop();
		    parseContext._stack.push( new EncapsulationEvaluation(_arg1) );
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 20:
/* Line 670 of lalr1.cc  */
#line 341 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    GeneralEvaluation * _arg1 = parseContext._stack.top();
		    parseContext._stack.pop();
		    GeneralEvaluation * _abs = new AbsEvaluation();
		    _abs->addArgument(_arg1);
		    parseContext._stack.push( _abs );
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 21:
/* Line 670 of lalr1.cc  */
#line 354 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    GeneralEvaluation * _arg1 = parseContext._stack.top();
		    parseContext._stack.pop();
		    GeneralEvaluation * _arg2 = parseContext._stack.top();
		    parseContext._stack.pop();
		    parseContext._stack.push( new PlusEvaluation(_arg1, _arg2) );
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 22:
/* Line 670 of lalr1.cc  */
#line 367 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    GeneralEvaluation * _arg2 = parseContext._stack.top();
		    parseContext._stack.pop();
		    GeneralEvaluation * _arg1 = parseContext._stack.top();
		    parseContext._stack.pop();
		    parseContext._stack.push( new MinusEvaluation(_arg1, _arg2) );
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 23:
/* Line 670 of lalr1.cc  */
#line 381 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    GeneralEvaluation * _arg2 = parseContext._stack.top();
		    parseContext._stack.pop();
		    GeneralEvaluation * _arg1 = parseContext._stack.top();
		    parseContext._stack.pop();
		    parseContext._stack.push( new DivideEvaluation(_arg1, _arg2) );
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 24:
/* Line 670 of lalr1.cc  */
#line 394 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    GeneralEvaluation * _arg1 = parseContext._stack.top();
		    parseContext._stack.pop();
		    GeneralEvaluation * _arg2 = parseContext._stack.top();
		    parseContext._stack.pop();
		    parseContext._stack.push( new MultEvaluation(_arg1, _arg2) );
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 25:
/* Line 670 of lalr1.cc  */
#line 410 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    GeneralEvaluation * power = parseContext._stack.top();
		    parseContext._stack.pop();
		    GeneralEvaluation * base = parseContext._stack.top();
		    parseContext._stack.pop();
		    parseContext._stack.push( new PowerEvaluation(base, power) );
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 26:
/* Line 670 of lalr1.cc  */
#line 422 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    GeneralEvaluation * arg = parseContext._stack.top();
		    parseContext._stack.pop();
		    parseContext._stack.push( new NegativeEvaluation(arg) );
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 40:
/* Line 670 of lalr1.cc  */
#line 452 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
			if (!parseContext.test_modus)
			{
			    GeneralEvaluation * _arg1 = parseContext._stack.top();
			    parseContext._stack.pop();
			    parseContext._stack.push( new EncapsulationEvaluation(_arg1) );
			}
			parseContext.syntax_ok &= true;
		    }
    break;

  case 41:
/* Line 670 of lalr1.cc  */
#line 462 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
			if (!parseContext.test_modus)
			{
			    GeneralEvaluation * _arg1 = parseContext._stack.top();
			    parseContext._stack.pop();
			    parseContext._stack.push( new NotEvaluation(_arg1) );
			}
			parseContext.syntax_ok &= true;
		    }
    break;

  case 42:
/* Line 670 of lalr1.cc  */
#line 473 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    GeneralEvaluation * _arg2 = parseContext._stack.top();
		    parseContext._stack.pop();
		    GeneralEvaluation * _arg1 = parseContext._stack.top();
		    parseContext._stack.pop();
		    parseContext._stack.push( new AndEvaluation(_arg1, _arg2) );

		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 43:
/* Line 670 of lalr1.cc  */
#line 486 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    GeneralEvaluation * _arg2 = parseContext._stack.top();
		    parseContext._stack.pop();
		    GeneralEvaluation * _arg1 = parseContext._stack.top();
		    parseContext._stack.pop();
		    parseContext._stack.push( new OrEvaluation(_arg1, _arg2) );

		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 44:
/* Line 670 of lalr1.cc  */
#line 500 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    GeneralEvaluation * _arg2 = parseContext._stack.top();
		    parseContext._stack.pop();
		    GeneralEvaluation * _arg1 = parseContext._stack.top();
		    parseContext._stack.pop();
		    parseContext._stack.push( new XorEvaluation(_arg1, _arg2) );

		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 45:
/* Line 670 of lalr1.cc  */
#line 513 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    parseContext._stack.push( new ConstantEvaluation(1) );
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 46:
/* Line 670 of lalr1.cc  */
#line 521 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    parseContext._stack.push( new ConstantEvaluation(0) );
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 47:
/* Line 670 of lalr1.cc  */
#line 530 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    GeneralEvaluation * _arg2 = parseContext._stack.top();
		    parseContext._stack.pop();
		    GeneralEvaluation * _arg1 = parseContext._stack.top();
		    parseContext._stack.pop();
		    parseContext._stack.push( new EqualEvaluation(_arg1, _arg2) );

		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 48:
/* Line 670 of lalr1.cc  */
#line 544 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    GeneralEvaluation * _arg2 = parseContext._stack.top();
		    parseContext._stack.pop();
		    GeneralEvaluation * _arg1 = parseContext._stack.top();
		    parseContext._stack.pop();
		    parseContext._stack.push( new NotEqualEvaluation(_arg1, _arg2) );
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 49:
/* Line 670 of lalr1.cc  */
#line 558 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    GeneralEvaluation * _arg2 = parseContext._stack.top();
		    parseContext._stack.pop();
		    GeneralEvaluation * _arg1 = parseContext._stack.top();
		    parseContext._stack.pop();
		    parseContext._stack.push( new BiggerEvaluation(_arg1, _arg2) );
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 50:
/* Line 670 of lalr1.cc  */
#line 571 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    GeneralEvaluation * _arg2 = parseContext._stack.top();
		    parseContext._stack.pop();
		    GeneralEvaluation * _arg1 = parseContext._stack.top();
		    parseContext._stack.pop();
		    parseContext._stack.push( new SmallerEvaluation(_arg1, _arg2) );
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 51:
/* Line 670 of lalr1.cc  */
#line 585 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    GeneralEvaluation * _arg2 = parseContext._stack.top();
		    parseContext._stack.pop();
		    GeneralEvaluation * _arg1 = parseContext._stack.top();
		    parseContext._stack.pop();
		    parseContext._stack.push( new HalfBiggerEvaluation(_arg1, _arg2) );
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 52:
/* Line 670 of lalr1.cc  */
#line 599 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    GeneralEvaluation * _arg2 = parseContext._stack.top();
		    parseContext._stack.pop();
		    GeneralEvaluation * _arg1 = parseContext._stack.top();
		    parseContext._stack.pop();
		    parseContext._stack.push( new HalfSmallerEvaluation(_arg1, _arg2) );
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 56:
/* Line 670 of lalr1.cc  */
#line 622 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {
		    if (!parseContext.test_modus)
		    {
			GeneralEvaluation * _value2 =   parseContext._stack.top();
			parseContext._stack.pop();
			GeneralEvaluation * _value1 =   parseContext._stack.top();
			parseContext._stack.pop();
			parseContext._stack.push( new StringEqualityEvaluation(_value1, _value2 ) );
		    }
		    parseContext.syntax_ok &= true;
		}
    break;

  case 57:
/* Line 670 of lalr1.cc  */
#line 635 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {
		    if (!parseContext.test_modus)
		    {
			GeneralEvaluation * _value2 =   parseContext._stack.top();
			parseContext._stack.pop();
			GeneralEvaluation * _value1 =   parseContext._stack.top();
			parseContext._stack.pop();
			parseContext._stack.push( new StringSemiEqualityEvaluation(_value1, _value2 ) );
		    }
		    parseContext.syntax_ok &= true;
		}
    break;

  case 58:
/* Line 670 of lalr1.cc  */
#line 647 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {
		    if (!parseContext.test_modus)
		    {
			string _regexp =  parseContext.strings_stack.top();
			parseContext.strings_stack.pop();
			GeneralEvaluation * _value =   parseContext._stack.top();
			parseContext._stack.pop();
			parseContext._stack.push( new RegexEvaluation(_value, new StringConstantEvaluation(_regexp) ) );
		    }
		    parseContext.syntax_ok &= true;
		}
    break;

  case 59:
/* Line 670 of lalr1.cc  */
#line 662 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {
		    string _tmp = parseContext.str.str();
		    regex_t rgT;
		    int _result = regcomp(&rgT, _tmp.c_str(), REG_EXTENDED);
		    if (_result != 0 )
		    {
			parseContext.syntax_ok &= false;
		    }
		    if (_result==0 && !parseContext.test_modus)
		    {
			parseContext.strings_stack.push( _tmp );
			parseContext.str.str("");
		    }	
		    regfree(&rgT);
		    parseContext.syntax_ok &= true;
		}
    break;

  case 63:
/* Line 670 of lalr1.cc  */
#line 690 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {
		    if (!parseContext.test_modus)
		    {		    
		    parseContext._stack.push( new StringConstantEvaluation( parseContext.str.str() ));
		    parseContext.str.str("");
		    }
		    parseContext.syntax_ok &= true;		    
		}
    break;

  case 66:
/* Line 670 of lalr1.cc  */
#line 706 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
			if (!parseContext.test_modus)
			{
			    GeneralEvaluation * _arg1 = parseContext._stack.top();
			    parseContext._stack.pop();
			    parseContext._stack.push( new LowerCaseEvaluation(_arg1) );
			}
			parseContext.syntax_ok &= true;
		    }
    break;

  case 67:
/* Line 670 of lalr1.cc  */
#line 717 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
			if (!parseContext.test_modus)
			{
			    GeneralEvaluation * _arg1 = parseContext._stack.top();
			    parseContext._stack.pop();
			    parseContext._stack.push( new UpperCaseEvaluation(_arg1) );
			}
			parseContext.syntax_ok &= true;
		    }
    break;

  case 70:
/* Line 670 of lalr1.cc  */
#line 733 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
			if (!parseContext.test_modus)
			{
				    GeneralEvaluation * _arg1 = parseContext._stack.top();
				    parseContext._stack.pop();
				    parseContext.function_call.top()->addArgument( _arg1 );
				    parseContext._stack.push( parseContext.function_call.top() );
				    parseContext.function_call.pop();
			}
			parseContext.syntax_ok &= true;
		}
    break;

  case 71:
/* Line 670 of lalr1.cc  */
#line 747 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new SqrtEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		}
    break;

  case 72:
/* Line 670 of lalr1.cc  */
#line 755 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new SinEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		}
    break;

  case 73:
/* Line 670 of lalr1.cc  */
#line 763 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new ASinEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		}
    break;

  case 74:
/* Line 670 of lalr1.cc  */
#line 771 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new CosEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		}
    break;

  case 75:
/* Line 670 of lalr1.cc  */
#line 779 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new ACosEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		}
    break;

  case 76:
/* Line 670 of lalr1.cc  */
#line 787 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new ExpEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		}
    break;

  case 77:
/* Line 670 of lalr1.cc  */
#line 795 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new LnEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		}
    break;

  case 78:
/* Line 670 of lalr1.cc  */
#line 803 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new TanEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		}
    break;

  case 79:
/* Line 670 of lalr1.cc  */
#line 811 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new ATanEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		}
    break;

  case 80:
/* Line 670 of lalr1.cc  */
#line 819 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new RandomEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		}
    break;

  case 81:
/* Line 670 of lalr1.cc  */
#line 827 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new AbsEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		}
    break;

  case 82:
/* Line 670 of lalr1.cc  */
#line 835 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new SgnEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		}
    break;

  case 83:
/* Line 670 of lalr1.cc  */
#line 843 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new PosEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		}
    break;

  case 84:
/* Line 670 of lalr1.cc  */
#line 851 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new NegEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		}
    break;

  case 85:
/* Line 670 of lalr1.cc  */
#line 859 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new FloorEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		}
    break;

  case 86:
/* Line 670 of lalr1.cc  */
#line 867 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new CeilEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		}
    break;

  case 87:
/* Line 670 of lalr1.cc  */
#line 878 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
			if (!parseContext.test_modus)
			{
				    GeneralEvaluation * _arg2 = parseContext._stack.top();
				    parseContext._stack.pop();
				    GeneralEvaluation * _arg1 = parseContext._stack.top();
				    parseContext._stack.pop();
				    parseContext.function_call.top()->addArgument( _arg1 );
				    parseContext.function_call.top()->addArgument( _arg2 );
				    parseContext._stack.push( parseContext.function_call.top() );
				    parseContext.function_call.pop();
			}
			parseContext.syntax_ok &= true;
		}
    break;

  case 88:
/* Line 670 of lalr1.cc  */
#line 894 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new MinEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		}
    break;

  case 89:
/* Line 670 of lalr1.cc  */
#line 902 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new MaxEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		}
    break;

  case 90:
/* Line 670 of lalr1.cc  */
#line 913 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {
	       if (!parseContext.test_modus)
	       {
		double _value = atof( parseContext.value.c_str());
		parseContext._stack.push( new ConstantEvaluation(_value));
		parseContext.value = "";
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 93:
/* Line 670 of lalr1.cc  */
#line 929 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
	    if (!parseContext.test_modus)
	    {
		Metric * _met = parseContext.cube->get_met(parseContext.value);
		if (_met != NULL)
		{	    
		    parseContext._stack.push( new DirectMetricEvaluation(cube::CONTEXT_METRIC,  parseContext.cube, _met ));
		}
		else
		{
		    cerr << "Cannot connect to the metric " << parseContext.value << ". Seems that this metric is not created yet. Value of metric::"<<parseContext.value << "() will be always 0" << endl;
		    parseContext._stack.push( new ConstantEvaluation( 0 ));
		
		}
		parseContext.value = "";
    	    }
    	    parseContext.syntax_ok &= true;
	}
    break;

  case 94:
/* Line 670 of lalr1.cc  */
#line 948 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
	    if (!parseContext.test_modus)
	    {
		Metric * _met = parseContext.cube->get_met(parseContext.value);
		if (_met != NULL)
		{	    
		    cube::CalcFlavorModificator * mod = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();
		    parseContext._stack.push( new DirectMetricEvaluation(cube::CONTEXT_METRIC,  parseContext.cube, _met, mod ));
		}
		else
		{
		    cerr << "Cannot connect to the metric " << parseContext.value << ". Seems that this metric is not created yet. Value of metric::"<<parseContext.value << "( ?  ) will be always 0" << endl;
		    parseContext._stack.push( new ConstantEvaluation( 0 ));
		
		}
		parseContext.value = "";
    	    }
    	    parseContext.syntax_ok &= true;
	}
    break;

  case 95:
/* Line 670 of lalr1.cc  */
#line 969 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
	    if (!parseContext.test_modus)
	    {
		Metric * _met = parseContext.cube->get_met(parseContext.value);
		if (_met != NULL)
		{	    
		    cube::CalcFlavorModificator * mod2 = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();
		    cube::CalcFlavorModificator * mod1 = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();

		    parseContext._stack.push( new DirectMetricEvaluation(cube::CONTEXT_METRIC,  parseContext.cube, _met, mod1, mod2));
		}
		else
		{
		    cerr << "Cannot connect to the metric " << parseContext.value << ". Seems that this metric is not created yet. Value of metric::"<<parseContext.value << "( ?, ? ) will be always 0" << endl;
		    parseContext._stack.push( new ConstantEvaluation( 0 ));
		
		}
		parseContext.value = "";
    	    }
    	    parseContext.syntax_ok &= true;
	}
    break;

  case 96:
/* Line 670 of lalr1.cc  */
#line 996 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
	    if (!parseContext.test_modus)
	    {
		Metric * _met = parseContext.cube->get_met(parseContext.value);
		if (_met != NULL)
		{	    
		    parseContext._stack.push( new DirectMetricEvaluation(cube::FIXED_METRIC_FULL_AGGR,  parseContext.cube, _met ));
		}
		else
		{
		    cerr << "Cannot connect to the metric " << parseContext.value << ". Seems that this metric is not created yet. Value of metric::"<<parseContext.value << "() will be always 0" << endl;
		    parseContext._stack.push( new ConstantEvaluation( 0 ));
		
		}
		parseContext.value = "";
    	    }
    	    parseContext.syntax_ok &= true;
	}
    break;

  case 97:
/* Line 670 of lalr1.cc  */
#line 1015 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
	    if (!parseContext.test_modus)
	    {
		Metric * _met = parseContext.cube->get_met(parseContext.value);
		if (_met != NULL)
		{	    
		    cube::CalcFlavorModificator * mod = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();
		    parseContext._stack.push( new DirectMetricEvaluation(cube::FIXED_METRIC_AGGR_SYS,  parseContext.cube, _met, mod ));
		}
		else
		{
		    cube::CalcFlavorModificator * mod = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();
		    cerr << "Cannot connect to the metric " << parseContext.value << ". Seems that this metric is not created yet. Value of metric::"<<parseContext.value << "( "; mod->print(); cout << " ) will be always 0" << endl;
		    

		    delete mod;
		    
		    parseContext._stack.push( new ConstantEvaluation( 0 ));
		
		}
		parseContext.value = "";
    	    }
    	    parseContext.syntax_ok &= true;
	}
    break;

  case 98:
/* Line 670 of lalr1.cc  */
#line 1042 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
	    if (!parseContext.test_modus)
	    {
		Metric * _met = parseContext.cube->get_met(parseContext.value);
		if (_met != NULL)
		{	    
		    cube::CalcFlavorModificator * mod2 = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();
		    cube::CalcFlavorModificator * mod1 = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();

		    parseContext._stack.push( new DirectMetricEvaluation(cube::FIXED_METRIC_NO_AGGR,  parseContext.cube, _met, mod1, mod2));
		}
		else
		{
		    cube::CalcFlavorModificator * mod2 = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();
		    cube::CalcFlavorModificator * mod1 = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();
		    cerr << "Cannot connect to the metric " << parseContext.value << ". Seems that this metric is not created yet. Value of metric::"<<parseContext.value << "( "; mod1->print(); cout << ","; mod2->print(); cout <<") will be always 0" << endl;

		    
		    delete mod2;
		    delete mod1;
		    
		    parseContext._stack.push( new ConstantEvaluation( 0 ));
		
		}
		parseContext.value = "";
    	    }
    	    parseContext.syntax_ok &= true;
	}
    break;

  case 99:
/* Line 670 of lalr1.cc  */
#line 1080 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
				    if (!parseContext.test_modus)
				    {
					parseContext.calcFlavorModificators.push(new CalcFlavorModificatorIncl());
				    }
				    parseContext.syntax_ok &= true;
				}
    break;

  case 100:
/* Line 670 of lalr1.cc  */
#line 1088 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
				    if (!parseContext.test_modus)
				    {
					parseContext.calcFlavorModificators.push(new CalcFlavorModificatorExcl());
				    }
				    parseContext.syntax_ok &= true;
				}
    break;

  case 101:
/* Line 670 of lalr1.cc  */
#line 1096 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
				    if (!parseContext.test_modus)
				    {
					parseContext.calcFlavorModificators.push(new CalcFlavorModificatorSame());
				    }
				    parseContext.syntax_ok &= true;
				}
    break;

  case 102:
/* Line 670 of lalr1.cc  */
#line 1107 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{

		    LambdaCalculEvaluation * _l_calc = new LambdaCalculEvaluation();

		    GeneralEvaluation * return_expr = parseContext._stack.top();
		    parseContext._stack.pop();

		    int _num_of_statements = parseContext._number_of_statements.top();
		    parseContext._number_of_statements.pop();

		    vector<GeneralEvaluation*> _tmp_statements;
		    for (int i=0; i<_num_of_statements; i++)
		    {
			_tmp_statements.push_back( parseContext._statements.top());
			parseContext._statements.pop();
		    }
		    for (int i=_num_of_statements-1; i>=0; i--)
		    {
			_l_calc->addArgument( _tmp_statements[i]);
		    }
		    _l_calc->addArgument( return_expr);
		    parseContext._stack.push(_l_calc);
		    // create lambda calculation using number_of_statements.
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 104:
/* Line 670 of lalr1.cc  */
#line 1139 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    parseContext._number_of_statements.push(0);
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 107:
/* Line 670 of lalr1.cc  */
#line 1156 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    int _tmp = parseContext._number_of_statements.top();
		    parseContext._number_of_statements.pop();
		    _tmp++;
		    parseContext._number_of_statements.push(_tmp);
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 108:
/* Line 670 of lalr1.cc  */
#line 1167 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    int _tmp = parseContext._number_of_statements.top();
		    parseContext._number_of_statements.pop();
		    _tmp++;
		    parseContext._number_of_statements.push(_tmp);
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 109:
/* Line 670 of lalr1.cc  */
#line 1178 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    int _tmp = parseContext._number_of_statements.top();
		    parseContext._number_of_statements.pop();
		    _tmp++;
		    parseContext._number_of_statements.push(_tmp);
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 113:
/* Line 670 of lalr1.cc  */
#line 1196 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    int _num_of_statements = parseContext._number_of_statements.top();
		    parseContext._number_of_statements.pop();

		    vector<GeneralEvaluation*> _tmp_statements;
		    for (int i=0; i<_num_of_statements; i++)
		    {
			_tmp_statements.push_back( parseContext._statements.top());
			parseContext._statements.pop();
		    }
		    GeneralEvaluation * _condition = parseContext._stack.top();
		    parseContext._stack.pop();

		    ShortIfEvaluation * _s_if_calc = new ShortIfEvaluation(_condition);

		    for (int i=_num_of_statements-1; i>=0; i--)
		    {
			_s_if_calc->addArgument( _tmp_statements[i]);
		    }
		    parseContext._statements.push(_s_if_calc);
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 114:
/* Line 670 of lalr1.cc  */
#line 1223 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    int _num_of_false_statements = parseContext._number_of_statements.top();
		    parseContext._number_of_statements.pop();
		    int _num_of_true_statements = parseContext._number_of_statements.top();
		    parseContext._number_of_statements.pop();

		    vector<GeneralEvaluation*> _tmp_false_statements;
		    for (int i=0; i<_num_of_false_statements; i++)
		    {
			_tmp_false_statements.push_back( parseContext._statements.top());
			parseContext._statements.pop();
		    }
		    vector<GeneralEvaluation*> _tmp_true_statements;
		    for (int i=0; i<_num_of_true_statements; i++)
		    {
			_tmp_true_statements.push_back( parseContext._statements.top());
			parseContext._statements.pop();
		    }
		    GeneralEvaluation * _condition = parseContext._stack.top();
		    parseContext._stack.pop();

		    FullIfEvaluation * _f_if_calc = new FullIfEvaluation(_condition, _num_of_true_statements, _num_of_false_statements);

		    for (int i=_num_of_true_statements-1; i>=0; i--)
		    {
			_f_if_calc->addArgument( _tmp_true_statements[i]);
		    }
		    for (int i=_num_of_false_statements-1; i>=0; i--)
		    {
			_f_if_calc->addArgument( _tmp_false_statements[i]);
		    }
		    parseContext._statements.push(_f_if_calc);
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 118:
/* Line 670 of lalr1.cc  */
#line 1271 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    parseContext._number_of_statements.push(0);
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 119:
/* Line 670 of lalr1.cc  */
#line 1281 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    int _num_of_statements = parseContext._number_of_statements.top();
		    parseContext._number_of_statements.pop();

		    vector<GeneralEvaluation*> _tmp_statements;
		    for (int i=0; i<_num_of_statements; i++)
		    {
			_tmp_statements.push_back( parseContext._statements.top());
			parseContext._statements.pop();
		    }
		    GeneralEvaluation * _condition = parseContext._stack.top();
		    parseContext._stack.pop();

		    WhileEvaluation * _while_calc = new WhileEvaluation(_condition);

		    for (int i=_num_of_statements-1; i>=0; i--)
		    {
			_while_calc->addArgument( _tmp_statements[i]);
		    }
		    parseContext._statements.push(_while_calc);

		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 120:
/* Line 670 of lalr1.cc  */
#line 1310 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
			GeneralEvaluation * _value = parseContext._stack.top();
			parseContext._stack.pop();
			GeneralEvaluation * _index = parseContext._stack.top();
			parseContext._stack.pop();
			std::string _string = parseContext.string_constants.top();
			parseContext.string_constants.pop();
			AssignmentEvaluation * _assign_eval = new AssignmentEvaluation( _string , _index, _value, parseContext.cube->get_cubepl_memory_manager()  );
			parseContext._statements.push( _assign_eval );
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 123:
/* Line 670 of lalr1.cc  */
#line 1329 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {
		if (!parseContext.test_modus)
		{      
		    parseContext._stack.push( new ConstantEvaluation(0) ); // pushed index 0 if array index is not specified
		}
		parseContext.syntax_ok &= true;
	      }
    break;

  case 128:
/* Line 670 of lalr1.cc  */
#line 1349 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {
			    if (!parseContext.test_modus)
			    {
			      std::string expression = parseContext.str.str();
			      parseContext.str.str("");
			      std::string uniq_name = parseContext.value;			      
			      Metric * _met = parseContext.cube->get_met(uniq_name);
			      if (_met == NULL)
			      {
				_met = parseContext.cube->def_met("",
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
								    cube::CUBE_METRIC_GHOST
								  );	
			      }else
			      {
				cout << " Metric with uniq name " << uniq_name << " already exists in cube" << endl;
			      }
			   }else
			  {  
			      std::string expression = parseContext.str.str();
			      std::string                  cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
			      cubeplparser::CubePL0Driver* driver         = new cubeplparser::CubePL0Driver( parseContext.cube ); // create driver for this cube
			      std::string nested_error;
			      if (! driver->test( cubepl_program, nested_error ))
			      {
				parseContext.syntax_ok &= false;
			      }
			      delete driver;
			    }
			    parseContext.syntax_ok &= true;
			    
		    }
    break;

  case 129:
/* Line 670 of lalr1.cc  */
#line 1395 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {
			      if (!parseContext.test_modus)
			      {
				std::string expression = parseContext.str.str();
				parseContext.str.str("");
				std::string uniq_name = parseContext.value;			      
				Metric * _met = parseContext.cube->get_met(uniq_name);
				if (_met == NULL)
				{
				  _met = parseContext.cube->def_met("",
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
								      cube::CUBE_METRIC_GHOST
								    );	
				}else
				{
				  cout << " Metric with uniq name " << uniq_name << " already exists in cube" << endl;
				}
			    }else
			    {  
				std::string expression = parseContext.str.str();
				std::string                  cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
				cubeplparser::CubePL0Driver* driver         = new cubeplparser::CubePL0Driver( parseContext.cube ); // create driver for this cube
				std::string nested_error;
				if (! driver->test( cubepl_program, nested_error ))
				{
				  parseContext.syntax_ok = false;
				}
				delete driver;
			      }
			      parseContext.syntax_ok &= true;
			    }
    break;

  case 130:
/* Line 670 of lalr1.cc  */
#line 1440 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {
				if (!parseContext.test_modus)
				{
				  std::string expression = parseContext.str.str();
				  parseContext.str.str("");
				  std::string uniq_name = parseContext.value;			      
				  Metric * _met = parseContext.cube->get_met(uniq_name);

				  if (_met == NULL)
				  {
				    _met = parseContext.cube->def_met("",
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
									cube::CUBE_METRIC_GHOST
								      );	
				  }else
				  {
				    cout << " Metric with uniq name " << uniq_name << " already exists in cube" << endl;
				  }
			      }else
			      {  
				  std::string expression = parseContext.str.str();
				  std::string                  cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
				  cubeplparser::CubePL0Driver* driver         = new cubeplparser::CubePL0Driver( parseContext.cube ); // create driver for this cube
				  std::string nested_error;
				  if (! driver->test( cubepl_program, nested_error ))
				  {
				    parseContext.syntax_ok = false;
				  }
				  delete driver;
			      }
			      parseContext.syntax_ok &= true;
			    }
    break;

  case 133:
/* Line 670 of lalr1.cc  */
#line 1494 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		    if (!parseContext.test_modus)
		    {
			    GeneralEvaluation * _index = parseContext._stack.top();
			    parseContext._stack.pop();
			    std::string _string = parseContext.string_constants.top();
			    parseContext.string_constants.pop();
			    VariableEvaluation * _var_eval = new VariableEvaluation(  _string, _index, parseContext.cube->get_cubepl_memory_manager()   );
			    parseContext._stack.push( _var_eval );
		    }
		    parseContext.syntax_ok &= true;
		}
    break;

  case 134:
/* Line 670 of lalr1.cc  */
#line 1507 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		  if (!parseContext.test_modus)
		  {
			  GeneralEvaluation * _index = parseContext._stack.top();
			  parseContext._stack.pop();
			  std::string _string = parseContext.string_constants.top();
			  parseContext.string_constants.pop();
			  VariableEvaluation * _var_eval = new VariableEvaluation(  _string, _index, parseContext.cube->get_cubepl_memory_manager()  );
			  parseContext._stack.push( _var_eval );
		  }
		  parseContext.syntax_ok &= true;
	      }
    break;

  case 135:
/* Line 670 of lalr1.cc  */
#line 1522 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    { 
		if (!parseContext.test_modus)
		{
		    parseContext._stack.push( new ConstantEvaluation(0) ); // pushed index 0 if array index is not specified
		}
		parseContext.syntax_ok &= true;
	    }
    break;

  case 137:
/* Line 670 of lalr1.cc  */
#line 1535 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {
        if (!parseContext.test_modus)
        {
            std::string _string = parseContext.string_constants.top();
            parseContext.string_constants.pop();
            SizeOfVariableEvaluation * _sizeof_var_eval = new SizeOfVariableEvaluation(  _string, parseContext.cube->get_cubepl_memory_manager()  );
            parseContext._stack.push( _sizeof_var_eval );
        }
        parseContext.syntax_ok &= true;            
	    }
    break;

  case 138:
/* Line 670 of lalr1.cc  */
#line 1547 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {
        if (!parseContext.test_modus)
        {
            std::string _string = parseContext.string_constants.top();
            parseContext.string_constants.pop();
            DefinedVariableEvaluation * _sizeof_var_eval = new DefinedVariableEvaluation(  _string, parseContext.cube->get_cubepl_memory_manager()  );
            parseContext._stack.push( _sizeof_var_eval );
        }
	    }
    break;

  case 139:
/* Line 670 of lalr1.cc  */
#line 1559 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
    {
		parseContext.string_constants.push(parseContext.value);
		parseContext.value = "";
	    }
    break;


/* Line 670 of lalr1.cc  */
#line 1892 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
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
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = yytranslate_ (yychar);

    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	if (yychar == yyempty_)
	  yytoken = yyempty_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[1] = yylloc;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */
        if (yychar <= yyeof_)
          {
            /* Return failure if at end of input.  */
            if (yychar == yyeof_)
              YYABORT;
          }
        else
          {
            yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
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
    if (false)
      goto yyerrorlab;

    yyerror_range[1] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (!yy_pact_value_is_default_ (yyn))
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	  YYABORT;

	yyerror_range[1] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[2] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

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
    if (yychar != yyempty_)
      {
        /* Make sure we have latest lookahead translation.  See comments
           at user semantic actions for why this is necessary.  */
        yytoken = yytranslate_ (yychar);
        yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval,
                     &yylloc);
      }

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystate_stack_.height ())
      {
        yydestruct_ ("Cleanup: popping",
                     yystos_[yystate_stack_[0]],
                     &yysemantic_stack_[0],
                     &yylocation_stack_[0]);
        yypop_ ();
      }

    return yyresult;
    }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (yychar != yyempty_)
          {
            /* Make sure we have latest lookahead translation.  See
               comments at user semantic actions for why this is
               necessary.  */
            yytoken = yytranslate_ (yychar);
            yydestruct_ (YY_NULL, yytoken, &yylval, &yylloc);
          }

        while (1 < yystate_stack_.height ())
          {
            yydestruct_ (YY_NULL,
                         yystos_[yystate_stack_[0]],
                         &yysemantic_stack_[0],
                         &yylocation_stack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  // Generate an error message.
  std::string
  CubePL0Parser::yysyntax_error_ (int yystate, int yytoken)
  {
    std::string yyres;
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

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
    if (yytoken != yyempty_)
      {
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            /* Stay within bounds of both yycheck and yytname.  */
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULL;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const short int CubePL0Parser::yypact_ninf_ = -182;
  const short int
  CubePL0Parser::yypact_[] =
  {
        12,   114,    24,  -182,   247,   247,  -182,    16,    30,   247,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,    17,   -34,
     -17,  -182,   327,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,    69,  -182,    70,  -182,  -182,  -182,  -182,
    -182,    62,  -182,  -182,  -182,  -182,  -182,  -182,   118,   292,
      13,    13,    28,    13,    75,    94,  -182,   247,   247,   247,
     247,   247,   247,   247,    95,    97,    98,    42,    51,    90,
     136,  -182,  -182,  -182,   102,  -182,  -182,    88,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,   153,   162,  -182,   161,
       0,    21,   118,   118,   170,   170,  -182,   312,    36,   186,
     186,    13,   164,   171,   247,   169,    62,  -182,   142,    62,
     247,  -182,  -182,   187,  -182,  -182,  -182,  -182,    -5,  -182,
      -2,  -182,   247,   186,   195,  -182,  -182,   217,   218,  -182,
     151,    43,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,   -35,  -182,
    -182,  -182,  -182,    53,    54,   219,   176,  -182,   -27,   163,
    -182,  -182,   102,  -182,   233,   332,   247,  -182,   120,  -182,
     120,   319,    11,   106,   186,   -37,   -37,   247,   247,   247,
     247,   247,   247,  -182,   186,   186,   186,   -37,   -37,   155,
     102,   221,  -182,  -182,   243,   245,  -182,  -182,  -182,   230,
     248,   249,  -182,  -182,   110,   252,  -182,   253,   332,   332,
     332,   332,   332,   332,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,   247,   164,   164,  -182,  -182,  -182,  -182,  -182,
    -182,   283,  -182,  -182,  -182
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  CubePL0Parser::yydefact_[] =
  {
         0,     0,     0,     3,     0,     0,   104,     0,     0,     0,
      71,    72,    73,    74,    75,    78,    79,    76,    77,    81,
      80,    82,    83,    84,    85,    86,    88,    89,     0,     0,
       0,    90,     0,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    68,     0,    69,     0,    13,    14,    91,    92,
      15,   105,    16,   133,   134,    17,    18,     1,    26,     0,
       0,     0,     0,     0,     0,     0,     2,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   107,   111,   112,     0,   108,   109,     0,   121,   122,
     110,   125,   126,   127,    19,   139,     0,     0,    20,     0,
       0,     0,    21,    22,    24,    23,    25,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   105,   118,   113,   105,
       0,   137,   138,   135,    93,    99,   100,   101,     0,    96,
       0,    70,     0,     0,     0,    45,    46,     0,     0,    63,
       0,     0,    27,    34,    35,    36,    37,    38,    28,    29,
      30,    31,    32,    33,    39,    53,    54,    55,     0,    61,
      62,    64,    65,    16,     0,     0,     0,   128,     0,     0,
     102,   106,     0,   114,     0,   120,     0,    94,     0,    97,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   115,     0,     0,     0,     0,     0,     0,
       0,   123,   132,   131,     0,     0,   103,   116,   117,     0,
       0,     0,    87,    40,     0,     0,    60,     0,    49,    47,
      51,    52,    48,    50,    42,    43,    44,    56,    57,    59,
      58,   119,     0,     0,     0,   136,    95,    98,    41,    66,
      67,     0,   129,   130,   124
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  CubePL0Parser::yypgoto_[] =
  {
      -182,  -182,    -1,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -103,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,    44,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,   -96,  -182,  -182,  -182,   -68,  -182,  -182,
    -182,  -182,  -182,  -182,  -151,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -181,  -182,  -108,  -182,  -182,
    -182,  -182,   -51
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  CubePL0Parser::yydefgoto_[] =
  {
        -1,     2,   140,    33,    34,    35,    36,    37,    38,    39,
      40,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   230,   158,
     159,   160,   161,   162,    41,    42,    43,    44,    45,    46,
      47,    48,    49,   128,    50,   115,    51,    79,    80,    81,
      82,    83,    84,   173,   118,   119,    85,    86,    87,    88,
      89,    90,    91,    92,    93,   167,   203,    52,    53,    54,
      55,    56,    96
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const signed char CubePL0Parser::yytable_ninf_ = -61;
  const short int
  CubePL0Parser::yytable_[] =
  {
        32,   163,   163,    58,    59,   130,   177,   164,    62,   179,
      97,   124,    99,   197,   198,     1,    67,    68,    69,    70,
      71,   207,    94,    28,    57,   163,    60,   199,   137,   138,
     183,    63,   129,    67,    68,    69,    70,    71,    64,   139,
      61,    67,    68,    69,    70,    71,   204,   205,   171,   231,
      98,   174,   242,   243,   193,    65,   178,   187,   188,   180,
     165,   189,   190,   191,   192,   200,   102,   103,   104,   105,
     106,   107,   108,   125,   126,   127,   163,   216,   216,    72,
      73,   214,   210,    95,   211,   100,   163,   163,   163,   216,
     216,   224,   225,   226,   125,   126,   127,   132,   194,   195,
     196,   -60,   -60,    74,   101,   109,    75,   110,   114,   194,
     195,   196,   111,   169,   112,   -60,   117,   213,     3,   175,
       4,   238,    76,   113,     5,    69,    70,    71,     6,    77,
      78,   181,   182,   120,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,   116,    67,    68,    69,    70,
      71,   194,   195,   196,   121,   194,   195,   196,    67,    68,
      69,    70,    71,   122,    28,   209,   123,    29,    30,    71,
     166,   168,   206,    31,   170,   172,   218,   219,   220,   221,
     222,   223,     4,   125,   126,   127,   133,   187,   188,   176,
       6,   189,   190,   191,   192,   184,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,   185,   186,   215,
     217,   241,   229,   232,   201,    67,    68,    69,    70,    71,
     134,   227,   228,   235,   135,   136,    28,   202,   208,    29,
      30,   137,   138,     4,   233,    31,   234,     5,     0,   236,
     237,     6,   139,   239,   240,     0,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    67,    68,
      69,    70,    71,     0,     0,     0,   244,    67,    68,    69,
      70,    71,     0,    94,     0,     0,     0,    28,     0,     0,
      29,    30,     0,     0,     0,     0,    31,    67,    68,    69,
      70,    71,     0,   131,    67,    68,    69,    70,    71,     0,
     212,    66,    67,    68,    69,    70,    71,    67,    68,    69,
      70,    71
  };

  /* YYCHECK.  */
  const short int
  CubePL0Parser::yycheck_[] =
  {
         1,   109,   110,     4,     5,   101,    11,   110,     9,    11,
      61,    11,    63,    48,    49,     3,     5,     6,     7,     8,
       9,   172,    11,    60,     0,   133,    10,    62,    65,    66,
     133,    14,    11,     5,     6,     7,     8,     9,    72,    76,
      10,     5,     6,     7,     8,     9,    73,    74,   116,   200,
      22,   119,   233,   234,    11,    72,    61,    46,    47,    61,
     111,    50,    51,    52,    53,    11,    67,    68,    69,    70,
      71,    72,    73,    73,    74,    75,   184,   185,   186,    10,
      10,   184,   178,    70,   180,    10,   194,   195,   196,   197,
     198,   194,   195,   196,    73,    74,    75,    61,    55,    56,
      57,    48,    49,    41,    10,    10,    44,    10,    18,    55,
      56,    57,    14,   114,    72,    62,    14,    11,     4,   120,
       6,    11,    60,    72,    10,     7,     8,     9,    14,    67,
      68,   132,   133,    45,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    19,     5,     6,     7,     8,
       9,    55,    56,    57,    11,    55,    56,    57,     5,     6,
       7,     8,     9,    11,    60,   176,    15,    63,    64,     9,
      16,    10,    19,    69,    15,    43,   187,   188,   189,   190,
     191,   192,     6,    73,    74,    75,    10,    46,    47,    12,
      14,    50,    51,    52,    53,    10,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    10,    10,   185,
     186,   232,    77,    12,    15,     5,     6,     7,     8,     9,
      54,   197,   198,    13,    58,    59,    60,    71,    15,    63,
      64,    65,    66,     6,    11,    69,    11,    10,    -1,    11,
      11,    14,    76,    11,    11,    -1,    -1,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,     5,     6,
       7,     8,     9,    -1,    -1,    -1,    13,     5,     6,     7,
       8,     9,    -1,    11,    -1,    -1,    -1,    60,    -1,    -1,
      63,    64,    -1,    -1,    -1,    -1,    69,     5,     6,     7,
       8,     9,    -1,    11,     5,     6,     7,     8,     9,    -1,
      11,     4,     5,     6,     7,     8,     9,     5,     6,     7,
       8,     9
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  CubePL0Parser::yystos_[] =
  {
         0,     3,    81,     4,     6,    10,    14,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    60,    63,
      64,    69,    82,    83,    84,    85,    86,    87,    88,    89,
      90,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     124,   126,   147,   148,   149,   150,   151,     0,    82,    82,
      10,    10,    82,    14,    72,    72,     4,     5,     6,     7,
       8,     9,    10,    10,    41,    44,    60,    67,    68,   127,
     128,   129,   130,   131,   132,   136,   137,   138,   139,   140,
     141,   142,   143,   144,    11,    70,   152,   152,    22,   152,
      10,    10,    82,    82,    82,    82,    82,    82,    82,    10,
      10,    14,    72,    72,    18,   125,    19,    14,   134,   135,
      45,    11,    11,    15,    11,    73,    74,    75,   123,    11,
     123,    11,    61,    10,    54,    58,    59,    65,    66,    76,
      82,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   109,   110,
     111,   112,   113,   147,    91,   152,    16,   145,    10,    82,
      15,   127,    43,   133,   127,    82,    12,    11,    61,    11,
      61,    82,    82,    91,    10,    10,    10,    46,    47,    50,
      51,    52,    53,    11,    55,    56,    57,    48,    49,    62,
      11,    15,    71,   146,    73,    74,    19,   134,    15,    82,
     123,   123,    11,    11,    91,   109,   147,   109,    82,    82,
      82,    82,    82,    82,    91,    91,    91,   109,   109,    77,
     108,   134,    12,    11,    11,    13,    11,    11,    11,    11,
      11,    82,   145,   145,    13
  };

#if CUBEPLPARSERDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  CubePL0Parser::yytoken_number_[] =
  {
         0,   256,   601,   602,   603,   604,   605,   606,   607,   608,
     609,   610,   611,   612,   613,   614,   615,   616,   617,   618,
     619,   620,   621,   622,   623,   624,   625,   626,   627,   628,
     629,   630,   631,   632,   633,   634,   635,   636,   637,   638,
     639,   640,   641,   642,   643,   644,   645,   646,   647,   648,
     649,   650,   651,   652,   653,   654,   655,   656,   657,   658,
     659,   660,   661,   662,   663,   664,   665,   666,   667,   100,
     200,   210,   300,   668,   669,   600,   400,   500,   670,   671
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  CubePL0Parser::yyr1_[] =
  {
         0,    80,    81,    81,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      92,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   104,   104,   105,   106,   107,   108,
     109,   109,   109,   110,   111,   111,   112,   113,   114,   114,
     115,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   117,   118,   118,
     119,   120,   120,   121,   121,   121,   122,   122,   122,   123,
     123,   123,   124,   125,   126,   127,   127,   128,   128,   128,
     128,   129,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   138,   139,   140,   141,   141,   141,   142,   143,
     144,   145,   146,   147,   147,   148,   149,   150,   151,   152
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  CubePL0Parser::yyr2_[] =
  {
         0,     2,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     4,     3,     3,     3,     1,     1,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     4,     4,     1,     1,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     6,     1,     1,
       1,     1,     1,     4,     5,     7,     4,     5,     7,     1,
       1,     1,     4,     3,     1,     0,     3,     1,     1,     1,
       1,     1,     1,     2,     3,     4,     2,     3,     1,     5,
       3,     1,     1,     4,     7,     1,     1,     1,     3,     6,
       6,     2,     1,     1,     1,     4,     7,     4,     4,     1
  };


  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const CubePL0Parser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "\"<cubepl>\"",
  "\"</cubepl>\"", "\"+\"", "\"-\"", "\"*\"", "\"/\"", "\"^\"", "\"(\"",
  "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"<<\"", "\">>\"",
  "\"return\"", "\";\"", "\"sizeof\"", "\"defined\"", "\"|\"", "\"sqrt\"",
  "\"sin\"", "\"asin\"", "\"cos\"", "\"acos\"", "\"tan\"", "\"atan\"",
  "\"exp\"", "\"log\"", "\"abs\"", "\"random\"", "\"sgn\"", "\"pos\"",
  "\"neg\"", "\"floor\"", "\"ceil\"", "\"min\"", "\"max\"", "\"if\"",
  "\"elseif\"", "\"else\"", "\"while\"", "\"=\"", "\">\"", "\"==\"",
  "\"eq\"", "\"seq\"", "\">=\"", "\"<=\"", "\"!=\"", "\"<\"", "\"not\"",
  "\"and\"", "\"or\"", "\"xor\"", "\"true\"", "\"false\"", "\"$\"",
  "\",\"", "\"=~\"", "\"metric::\"", "\"metric::fixed::\"",
  "\"lowercase\"", "\"uppercase\"", "\"cube::metric::postderived\"",
  "\"cube::metric::prederived\"", "CONSTANT", "STRING_CONSTANT",
  "STRING_TEXT", "METRIC_NAME", "\"i\"", "\"e\"", "SAME_MODIFICATOR",
  "QUOTED_STRING", "REGEXP_STRING", "FUNC2", "SIGN", "$accept", "document",
  "expression", "enclosed_expression", "absolute_value", "sum", "subtract",
  "division", "multiplication", "power", "negation", "boolean_expression",
  "enclosed_boolean_expression", "and_expression", "or_expression",
  "xor_expression", "true_expression", "false_expression", "equality",
  "not_equality", "bigger", "smaller", "halfbigger", "halfsmaller",
  "string_operation", "string_equality", "string_semi_equality", "regexp",
  "regexp_expression", "string_expression", "quoted_string",
  "string_function", "lowercase", "uppercase", "function_call",
  "one_variable_function", "function_name", "two_variables_function",
  "function2_name", "constant", "metric_refs", "context_metric",
  "fixed_metric", "calculationFlavourModificator", "lambda_calcul",
  "return_expression", "lambda_start", "list_of_statements", "statement",
  "if_statement", "simple_if_statement", "full_if_statement",
  "if_condition", "else_enclosed_list_of_statements",
  "enclosed_list_of_statements", "enclosed_list_of_statements_start",
  "while_statement", "assignment", "assignment_target", "put_variable",
  "put_variable_indexed", "create_ghost_metric",
  "create_postderived_ghost_metric",
  "create_prederived_inclusive_ghost_metric",
  "create_prederived_exclusive_ghost_metric", "GhostMetricDefinition",
  "CubePLGhostText", "get_variable", "get_variable_simple",
  "get_variable_indexed", "sizeof_variable", "defined_variable",
  "string_constant", YY_NULL
  };

#if CUBEPLPARSERDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const CubePL0Parser::rhs_number_type
  CubePL0Parser::yyrhs_[] =
  {
        81,     0,    -1,     3,    82,     4,    -1,     3,     4,    -1,
      83,    -1,    84,    -1,    85,    -1,    86,    -1,    87,    -1,
      88,    -1,    89,    -1,    90,    -1,   114,    -1,   119,    -1,
     120,    -1,   124,    -1,   147,    -1,   150,    -1,   151,    -1,
      10,    82,    11,    -1,    22,    82,    22,    -1,    82,     5,
      82,    -1,    82,     6,    82,    -1,    82,     8,    82,    -1,
      82,     7,    82,    -1,    82,     9,    82,    -1,     6,    82,
      -1,    92,    -1,    98,    -1,    99,    -1,   100,    -1,   101,
      -1,   102,    -1,   103,    -1,    93,    -1,    94,    -1,    95,
      -1,    96,    -1,    97,    -1,   104,    -1,    10,    91,    11,
      -1,    54,    10,    91,    11,    -1,    91,    55,    91,    -1,
      91,    56,    91,    -1,    91,    57,    91,    -1,    58,    -1,
      59,    -1,    82,    47,    82,    -1,    82,    52,    82,    -1,
      82,    46,    82,    -1,    82,    53,    82,    -1,    82,    50,
      82,    -1,    82,    51,    82,    -1,   105,    -1,   106,    -1,
     107,    -1,   109,    48,   109,    -1,   109,    49,   109,    -1,
     109,    62,   108,    -1,    77,    -1,   147,    -1,   110,    -1,
     111,    -1,    76,    -1,   112,    -1,   113,    -1,    65,    10,
     109,    11,    -1,    66,    10,   109,    11,    -1,   115,    -1,
     117,    -1,   116,    10,    82,    11,    -1,    23,    -1,    24,
      -1,    25,    -1,    26,    -1,    27,    -1,    30,    -1,    31,
      -1,    28,    -1,    29,    -1,    33,    -1,    32,    -1,    34,
      -1,    35,    -1,    36,    -1,    37,    -1,    38,    -1,   118,
      10,    82,    61,    82,    11,    -1,    39,    -1,    40,    -1,
      69,    -1,   121,    -1,   122,    -1,    63,    72,    10,    11,
      -1,    63,    72,    10,   123,    11,    -1,    63,    72,    10,
     123,    61,   123,    11,    -1,    64,    72,    10,    11,    -1,
      64,    72,    10,   123,    11,    -1,    64,    72,    10,   123,
      61,   123,    11,    -1,    73,    -1,    74,    -1,    75,    -1,
     126,   127,   125,    15,    -1,    18,    82,    19,    -1,    14,
      -1,    -1,   128,    19,   127,    -1,   129,    -1,   136,    -1,
     137,    -1,   141,    -1,   130,    -1,   131,    -1,   132,   134,
      -1,   132,   134,   133,    -1,    41,    10,    91,    11,    -1,
      43,   134,    -1,   135,   127,    15,    -1,    14,    -1,    44,
      10,    91,    11,   134,    -1,   138,    45,    82,    -1,   139,
      -1,   140,    -1,    60,    14,   152,    15,    -1,    60,    14,
     152,    15,    12,    82,    13,    -1,   142,    -1,   143,    -1,
     144,    -1,    67,    72,   145,    -1,    68,    72,    10,    73,
      11,   145,    -1,    68,    72,    10,    74,    11,   145,    -1,
      16,   146,    -1,    71,    -1,   148,    -1,   149,    -1,    60,
      14,   152,    15,    -1,    60,    14,   152,    15,    12,    82,
      13,    -1,    20,    10,   152,    11,    -1,    21,    10,   152,
      11,    -1,    70,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  CubePL0Parser::yyprhs_[] =
  {
         0,     0,     3,     7,    10,    12,    14,    16,    18,    20,
      22,    24,    26,    28,    30,    32,    34,    36,    38,    40,
      44,    48,    52,    56,    60,    64,    68,    71,    73,    75,
      77,    79,    81,    83,    85,    87,    89,    91,    93,    95,
      97,   101,   106,   110,   114,   118,   120,   122,   126,   130,
     134,   138,   142,   146,   148,   150,   152,   156,   160,   164,
     166,   168,   170,   172,   174,   176,   178,   183,   188,   190,
     192,   197,   199,   201,   203,   205,   207,   209,   211,   213,
     215,   217,   219,   221,   223,   225,   227,   229,   236,   238,
     240,   242,   244,   246,   251,   257,   265,   270,   276,   284,
     286,   288,   290,   295,   299,   301,   302,   306,   308,   310,
     312,   314,   316,   318,   321,   325,   330,   333,   337,   339,
     345,   349,   351,   353,   358,   366,   368,   370,   372,   376,
     383,   390,   393,   395,   397,   399,   404,   412,   417,   422
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  CubePL0Parser::yyrline_[] =
  {
         0,   296,   296,   305,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   330,
     340,   353,   366,   380,   393,   409,   421,   435,   436,   437,
     438,   439,   440,   441,   442,   443,   444,   445,   446,   447,
     451,   461,   472,   485,   499,   512,   520,   529,   543,   557,
     570,   584,   598,   614,   615,   616,   621,   634,   646,   661,
     681,   682,   683,   689,   700,   700,   705,   716,   730,   730,
     732,   746,   754,   762,   770,   778,   786,   794,   802,   810,
     818,   826,   834,   842,   850,   858,   866,   877,   893,   901,
     912,   923,   923,   928,   947,   968,   995,  1014,  1041,  1079,
    1087,  1095,  1106,  1136,  1138,  1147,  1149,  1155,  1166,  1177,
    1188,  1191,  1192,  1195,  1222,  1261,  1264,  1267,  1270,  1280,
    1309,  1325,  1325,  1328,  1338,  1342,  1343,  1344,  1348,  1394,
    1439,  1486,  1489,  1493,  1506,  1521,  1530,  1534,  1546,  1558
  };

  // Print the state stack on the debug stream.
  void
  CubePL0Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  CubePL0Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // CUBEPLPARSERDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  CubePL0Parser::token_number_type
  CubePL0Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      69,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      70,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      71,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      72,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      76,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      77,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      75,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    73,    74,
      78,    79
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int CubePL0Parser::yyeof_ = 0;
  const int CubePL0Parser::yylast_ = 341;
  const int CubePL0Parser::yynnts_ = 73;
  const int CubePL0Parser::yyempty_ = -2;
  const int CubePL0Parser::yyfinal_ = 57;
  const int CubePL0Parser::yyterror_ = 1;
  const int CubePL0Parser::yyerrcode_ = 256;
  const int CubePL0Parser::yyntokens_ = 80;

  const unsigned int CubePL0Parser::yyuser_token_number_max_ = 671;
  const CubePL0Parser::token_number_type CubePL0Parser::yyundef_token_ = 2;


} // cubeplparser
/* Line 1141 of lalr1.cc  */
#line 2722 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.cpp"
/* Line 1142 of lalr1.cc  */
#line 1564 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL0Parser.yy"
 /*** Additional Code ***/


void cubeplparser::CubePL0Parser::error(const CubePL0Parser::location_type& l,
				  const std::string& m)
{

    CubePL0Parser::location_type _l = l;


    _l.end.column = (_l.end.column<9)?1: _l.end.column-8;
    _l.begin.column = _l.end.column-1; 

    parseContext.syntax_ok = false;
    stringstream sstr;
    string       str;
    sstr << _l;
    sstr >> str;
    parseContext.error_message = str + ":" + m;
    parseContext.error_place = _l;

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




