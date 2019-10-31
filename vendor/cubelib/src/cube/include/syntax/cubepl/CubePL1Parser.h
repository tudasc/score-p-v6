/* A Bison parser, made by GNU Bison 2.7.  */

/* Skeleton interface for Bison LALR(1) parsers in C++
   
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

/**
 ** \file ../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.hpp
 ** Define the cubeplparser::parser class.
 */

/* C++ LALR(1) parser skeleton written by Akim Demaille.  */

#ifndef YY_CUBEPLPARSER_BUILD_FRONTEND_SRC_CUBE_SRC_SYNTAX_CUBEPL_CUBEPL1PARSER_HPP_INCLUDED
# define YY_CUBEPLPARSER_BUILD_FRONTEND_SRC_CUBE_SRC_SYNTAX_CUBEPL_CUBEPL1PARSER_HPP_INCLUDED

/* "%code requires" blocks.  */
/* Line 33 of lalr1.cc  */
#line 17 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"
 
/*** C/C++ Declarations ***/

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <string>
#include <vector>
#include <regex.h>

#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"
#include "CubePL1ParseContext.h"

#include "CubeEncapsulation.h"
#include "CubeNegativeEvaluation.h"
#include "CubeConstantEvaluation.h"
#include "CubeStringConstantEvaluation.h"

#include "CubeDirectMetricEvaluation.h"
#include "CubePlusEvaluation.h"
#include "CubeMinusEvaluation.h"
#include "CubeMultEvaluation.h"
#include "CubeDivideEvaluation.h"
#include "CubePowerEvaluation.h"

#include "CubeAndEvaluation.h"
#include "CubeOrEvaluation.h"
#include "CubeXorEvaluation.h"
#include "CubeNotEvaluation.h"

#include "CubeStringEqualityEvaluation.h"
#include "CubeStringSemiEqualityEvaluation.h"
#include "CubeRegexEvaluation.h"
#include "CubeLowerCaseEvaluation.h"
#include "CubeUpperCaseEvaluation.h"
#include "CubeMetricGetEvaluation.h"
#include "CubeEnvEvaluation.h"


#include "CubeBiggerEvaluation.h"
#include "CubeSmallerEvaluation.h"
#include "CubeHalfBiggerEvaluation.h"
#include "CubeHalfSmallerEvaluation.h"
#include "CubeEqualEvaluation.h"
#include "CubeNotEqualEvaluation.h"

#include "CubeArgumentEvaluation.h"
#include "CubeATanEvaluation.h"
#include "CubeTanEvaluation.h"
#include "CubeACosEvaluation.h"
#include "CubeASinEvaluation.h"
#include "CubeCosEvaluation.h"
#include "CubeSinEvaluation.h"
#include "CubeAbsEvaluation.h"

#include "CubeLnEvaluation.h"
#include "CubeExpEvaluation.h"

#include "CubeRandomEvaluation.h"
#include "CubeSqrtEvaluation.h"

#include "CubeSgnEvaluation.h"
#include "CubePosEvaluation.h"
#include "CubeNegEvaluation.h"
#include "CubeFloorEvaluation.h"
#include "CubeCeilEvaluation.h"

#include "CubeMinEvaluation.h"
#include "CubeMaxEvaluation.h"

#include "CubeLambdaCalculEvaluation.h"
#include "CubeAssignmentEvaluation.h"
#include "CubeVariableEvaluation.h"
#include "CubeShortIfEvaluation.h"
#include "CubeFullIfEvaluation.h"
#include "CubeExtendedIfEvaluation.h"
#include "CubeWhileEvaluation.h"
#include "CubeMetricSetEvaluation.h"

#include "CubeSizeOfVariableEvaluation.h"
#include "CubeDefinedVariableEvaluation.h"
#include "CubePL1Driver.h"





/* Line 33 of lalr1.cc  */
#line 140 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.hpp"


#include <string>
#include <iostream>
#include "stack.hh"
#include "location.hh"

/* Enabling traces.  */
#ifndef CUBEPLPARSERDEBUG
# if defined YYDEBUG
#  if YYDEBUG
#   define CUBEPLPARSERDEBUG 1
#  else
#   define CUBEPLPARSERDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define CUBEPLPARSERDEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined CUBEPLPARSERDEBUG */


namespace cubeplparser {
/* Line 33 of lalr1.cc  */
#line 164 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.hpp"

  /// A Bison parser.
  class CubePL1Parser
  {
  public:
    /// Symbol semantic values.
#ifndef CUBEPLPARSERSTYPE
    union semantic_type
    {
/* Line 33 of lalr1.cc  */
#line 155 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.yy"


/* Line 33 of lalr1.cc  */
#line 179 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.hpp"
    };
#else
    typedef CUBEPLPARSERSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;
    /// Tokens.
    struct token
    {
      /* Tokens.  */
   enum yytokentype {
     END = 0,
     START_DOCUMENT = 602,
     END_DOCUMENT = 603,
     OP_PLUS = 604,
     OP_MINUS = 605,
     OP_MULT = 606,
     OP_DIVIDE = 607,
     OP_POWER = 608,
     OPEN_EXP = 609,
     CLOSE_EXP = 610,
     OPEN_ARRAY_INDEX = 611,
     CLOSE_ARRAY_INDEX = 612,
     OPEN_LCALC = 613,
     CLOSE_LCALC = 614,
     OPEN_GM_CUBEPL = 615,
     CLOSE_GM_CUBEPL = 616,
     RETURN_EXP = 617,
     STATEMENT_SEP = 618,
     SIZEOF = 619,
     DEFINED = 620,
     LOCAL_VAR = 621,
     GLOBAL_VAR = 622,
     ABS_MARK = 623,
     ARGUMENT1 = 624,
     ARGUMENT2 = 625,
     FUN_SQRT = 626,
     FUN_SIN = 627,
     FUN_ASIN = 628,
     FUN_COS = 629,
     FUN_ACOS = 630,
     FUN_TAN = 631,
     FUN_ATAN = 632,
     FUN_EXP = 633,
     FUN_LOG = 634,
     FUN_ABS = 635,
     FUN_RANDOM = 636,
     FUN_SGN = 637,
     FUN_POS = 638,
     FUN_NEG = 639,
     FUN_FLOOR = 640,
     FUN_CEIL = 641,
     FUN_MIN = 642,
     FUN_MAX = 643,
     KEYWORD_IF = 644,
     KEYWORD_ELSEIF = 645,
     KEYWORD_ELSE = 646,
     KEYWORD_WHILE = 647,
     KEYWORD_ASSIGN = 648,
     KEYWORD_BIGGER = 649,
     KEYWORD_EQUAL = 650,
     KEYWORD_STRING_EQUAL = 651,
     KEYWORD_STRING_SEMI_EQUAL = 652,
     KEYWORD_HALFBIGGER = 653,
     KEYWORD_HALFSMALLER = 654,
     KEYWORD_NOT_EQUAL = 655,
     KEYWORD_SMALLER = 656,
     KEYWORD_NOT = 657,
     KEYWORD_AND = 658,
     KEYWORD_OR = 659,
     KEYWORD_XOR = 660,
     KEYWORD_TRUE = 661,
     KEYWORD_FALSE = 662,
     KEYWORD_VAR = 663,
     COMMA = 664,
     KEYWORD_REGEXP = 665,
     KEYWORD_METRIC = 666,
     KEYWORD_FIXED_METRIC = 667,
     KEYWORD_METRIC_CALL = 668,
     KEYWORD_ENV = 669,
     KEYWORD_LOWERCASE = 670,
     KEYWORD_UPPERCASE = 671,
     KEYWORD_GHOST_POSTMETRIC = 672,
     KEYWORD_GHOST_PREMETRIC = 673,
     KEYWORD_METRIC_INIT = 674,
     KEYWORD_METRIC_FLEX_AGGR_PLUS = 675,
     KEYWORD_METRIC_FLEX_AGGR_MINUS = 676,
     KEYWORD_METRIC_SET = 677,
     KEYWORD_METRIC_GET = 678,
     CONSTANT = 100,
     STRING_CONSTANT = 200,
     STRING_TEXT = 210,
     METRIC_NAME = 300,
     INIT_METRIC_NAME = 301,
     INCL_MODIFICATOR = 679,
     EXCL_MODIFICATOR = 680,
     SAME_MODIFICATOR = 600,
     QUOTED_STRING = 400,
     REGEXP_STRING = 500,
     FUNC2 = 681,
     SIGN = 682
   };

    };
    /// Token type.
    typedef token::yytokentype token_type;

    /// Build a parser object.
    CubePL1Parser (class CubePL1ParseContext& parseContext_yyarg, class CubePL1Scanner& CubePL1Lexer_yyarg);
    virtual ~CubePL1Parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if CUBEPLPARSERDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

  private:
    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Generate an error message.
    /// \param state   the state where the error occurred.
    /// \param tok     the lookahead token.
    virtual std::string yysyntax_error_ (int yystate, int tok);

#if CUBEPLPARSERDEBUG
    /// \brief Report a symbol value on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    virtual void yy_symbol_value_print_ (int yytype,
					 const semantic_type* yyvaluep,
					 const location_type* yylocationp);
    /// \brief Report a symbol on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    virtual void yy_symbol_print_ (int yytype,
				   const semantic_type* yyvaluep,
				   const location_type* yylocationp);
#endif


    /// State numbers.
    typedef int state_type;
    /// State stack type.
    typedef stack<state_type>    state_stack_type;
    /// Semantic value stack type.
    typedef stack<semantic_type> semantic_stack_type;
    /// location stack type.
    typedef stack<location_type> location_stack_type;

    /// The state stack.
    state_stack_type yystate_stack_;
    /// The semantic value stack.
    semantic_stack_type yysemantic_stack_;
    /// The location stack.
    location_stack_type yylocation_stack_;

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    /// Internal symbol numbers.
    typedef unsigned char token_number_type;
    /* Tables.  */
    /// For a state, the index in \a yytable_ of its portion.
    static const short int yypact_[];
    static const short int yypact_ninf_;

    /// For a state, default reduction number.
    /// Unless\a  yytable_ specifies something else to do.
    /// Zero means the default is an error.
    static const unsigned char yydefact_[];

    static const short int yypgoto_[];
    static const short int yydefgoto_[];

    /// What to do in a state.
    /// \a yytable_[yypact_[s]]: what to do in state \a s.
    /// - if positive, shift that token.
    /// - if negative, reduce the rule which number is the opposite.
    /// - if zero, do what YYDEFACT says.
    static const unsigned short int yytable_[];
    static const signed char yytable_ninf_;

    static const short int yycheck_[];

    /// For a state, its accessing symbol.
    static const unsigned char yystos_[];

    /// For a rule, its LHS.
    static const unsigned char yyr1_[];
    /// For a rule, its RHS length.
    static const unsigned char yyr2_[]; 

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if CUBEPLPARSERDEBUG
    /// A type to store symbol numbers and -1.
    typedef short int rhs_number_type;
    /// A `-1'-separated list of the rules' RHS.
    static const rhs_number_type yyrhs_[];
    /// For each rule, the index of the first RHS symbol in \a yyrhs_.
    static const unsigned short int yyprhs_[];
    /// For each rule, its source line number.
    static const unsigned short int yyrline_[];
    /// For each scanner token number, its symbol number.
    static const unsigned short int yytoken_number_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    /* Debugging.  */
    int yydebug_;
    std::ostream* yycdebug_;
#endif

    /// Convert a scanner token number \a t to a symbol number.
    token_number_type yytranslate_ (int t);

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg        Why this token is reclaimed.
    ///                     If null, do not display the symbol, just free it.
    /// \param yytype       The symbol type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    inline void yydestruct_ (const char* yymsg,
			     int yytype,
			     semantic_type* yyvaluep,
			     location_type* yylocationp);

    /// Pop \a n symbols the three stacks.
    inline void yypop_ (unsigned int n = 1);

    /* Constants.  */
    static const int yyeof_;
    /* LAST_ -- Last index in TABLE_.  */
    static const int yylast_;
    static const int yynnts_;
    static const int yyempty_;
    static const int yyfinal_;
    static const int yyterror_;
    static const int yyerrcode_;
    static const int yyntokens_;
    static const unsigned int yyuser_token_number_max_;
    static const token_number_type yyundef_token_;

    /* User arguments.  */
    class CubePL1ParseContext& parseContext;
    class CubePL1Scanner& CubePL1Lexer;
  };

} // cubeplparser
/* Line 33 of lalr1.cc  */
#line 459 "../../build-frontend/../src/cube/src/syntax/cubepl/CubePL1Parser.hpp"



#endif /* !YY_CUBEPLPARSER_BUILD_FRONTEND_SRC_CUBE_SRC_SYNTAX_CUBEPL_CUBEPL1PARSER_HPP_INCLUDED  */
