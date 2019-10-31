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
** \file ../../build-frontend/../src/cube/src/syntax/Cube4Parser.hpp
** Define the cubeparser::parser class.
*/

/* C++ LALR(1) parser skeleton written by Akim Demaille.  */

#ifndef YY_CUBEPARSER_BUILD_FRONTEND_SRC_CUBE_SRC_SYNTAX_CUBE4PARSER_HPP_INCLUDED
# define YY_CUBEPARSER_BUILD_FRONTEND_SRC_CUBE_SRC_SYNTAX_CUBE4PARSER_HPP_INCLUDED

/* "%code requires" blocks.  */
/* Line 33 of lalr1.cc  */
#line 18 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"

/*** C/C++ Declarations ***/

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <string>
#include <vector>
#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"

#include "CubeRegion.h"

#include "CubeError.h"
#include "CubeServices.h"
#include "CubeError.h"
#include "CubeParseContext.h"
#include "CubeMetric.h"
#include "Cube.h"
#include "CubeCartesian.h"



/* Line 33 of lalr1.cc  */
#line 75 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.hpp"


#include <string>
#include <iostream>
#include "stack.hh"
#include "location.hh"

/* Enabling traces.  */
#ifndef CUBEPARSERDEBUG
# if defined YYDEBUG
#  if YYDEBUG
#   define CUBEPARSERDEBUG 1
#  else
#   define CUBEPARSERDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define CUBEPARSERDEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined CUBEPARSERDEBUG */


namespace cubeparser
{
/* Line 33 of lalr1.cc  */
#line 99 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.hpp"

/// A Bison parser.
class Cube4Parser
{
public:
    /// Symbol semantic values.
#ifndef CUBEPARSERSTYPE
    union semantic_type
    {
/* Line 33 of lalr1.cc  */
#line 95 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.yy"


/* Line 33 of lalr1.cc  */
#line 114 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.hpp"
    };
#else
    typedef CUBEPARSERSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;
    /// Tokens.
    struct token
    {
        /* Tokens.  */
        enum yytokentype
        {
            END                      = 0,
            FFALSE                   = 1002,
            TTRUE                    = 1003,
            ATTRIBUTE_VALUE          = 1004,
            ERROR                    = 1005,
            ACUBEPL_AGGR_ATTR_PLUS   = 1006,
            ACUBEPL_AGGR_ATTR_MINUS  = 1007,
            ACUBEPL_AGGR_ATTR_AGGR   = 1008,
            OPENTAG_RIGHT            = 1009,
            CLOSETAG_RIGHT           = 1010,
            ATTR_OPEN                = 1011,
            DIM_OPEN                 = 1012,
            XML_OPEN                 = 1013,
            XML_CLOSE                = 1014,
            CUBE_OPEN4               = 1015,
            CUBE_OPEN41              = 1016,
            CUBE_OPEN42              = 1017,
            CUBE_OPEN43              = 1018,
            CUBE_OPEN44              = 1019,
            CUBE_OPEN45              = 1020,
            CUBE_OPEN3               = 1021,
            CUBE_OPEN                = 1022,
            CUBE_OPEN_NOT_SUPPORTED  = 1000,
            CUBE_CLOSE               = 1023,
            METRIC_OPEN              = 1024,
            METRIC_CLOSE             = 1025,
            EXPRESSION_OPEN          = 1026,
            EXPRESSION_CLOSE         = 1027,
            EXPRESSION_INIT_OPEN     = 1028,
            EXPRESSION_INIT_CLOSE    = 1029,
            EXPRESSION_AGGR_OPEN     = 1030,
            EXPRESSION_AGGR_CLOSE    = 1031,
            REGION_OPEN              = 1032,
            REGION_CLOSE             = 1033,
            CNODE_OPEN               = 1034,
            CNODE_CLOSE              = 1035,
            CNODE_PARAMETER_OPEN     = 1036,
            SYSTEM_TREE_NODE_OPEN    = 1037,
            SYSTEM_TREE_NODE_CLOSE   = 1038,
            LOCATIONGROUP_OPEN       = 1039,
            LOCATIONGROUP_CLOSE      = 1040,
            LOCATION_OPEN            = 1041,
            LOCATION_CLOSE           = 1042,
            MACHINE_OPEN             = 1043,
            MACHINE_CLOSE            = 1044,
            NODE_OPEN                = 1045,
            NODE_CLOSE               = 1046,
            PROCESS_OPEN             = 1047,
            PROCESS_CLOSE            = 1048,
            THREAD_OPEN              = 1049,
            THREAD_CLOSE             = 1050,
            MATRIX_OPEN              = 1051,
            MATRIX_CLOSE             = 1052,
            ROW_OPEN                 = 1053,
            ROW_CLOSE                = 1054,
            CART_OPEN                = 1055,
            CART_CLOSE               = 1056,
            COORD_OPEN               = 1057,
            COORD_CLOSE              = 1058,
            DOC_OPEN                 = 1059,
            DOC_CLOSE                = 1060,
            MIRRORS_OPEN             = 1061,
            MIRRORS_CLOSE            = 1062,
            MURL_OPEN                = 1063,
            MURL_CLOSE               = 1064,
            METRICS_OPEN             = 1065,
            METRICS_CLOSE            = 1066,
            DISP_NAME_OPEN           = 1067,
            DISP_NAME_CLOSE          = 1068,
            UNIQ_NAME_OPEN           = 1069,
            UNIQ_NAME_CLOSE          = 1070,
            DTYPE_OPEN               = 1071,
            DTYPE_CLOSE              = 1072,
            UOM_OPEN                 = 1073,
            UOM_CLOSE                = 1074,
            VAL_OPEN                 = 1075,
            VAL_CLOSE                = 1076,
            URL_OPEN                 = 1077,
            URL_CLOSE                = 1078,
            DESCR_OPEN               = 1079,
            DESCR_CLOSE              = 1080,
            PARADIGM_OPEN            = 1081,
            PARADIGM_CLOSE           = 1082,
            ROLE_OPEN                = 1083,
            ROLE_CLOSE               = 1084,
            PROGRAM_OPEN             = 1085,
            PROGRAM_CLOSE            = 1086,
            NAME_OPEN                = 1087,
            NAME_CLOSE               = 1088,
            MANGLED_NAME_OPEN        = 1089,
            MANGLED_NAME_CLOSE       = 1090,
            CLASS_OPEN               = 1091,
            CLASS_CLOSE              = 1092,
            TYPE_OPEN                = 1093,
            TYPE_CLOSE               = 1094,
            SYSTEM_OPEN              = 1095,
            SYSTEM_CLOSE             = 1096,
            RANK_OPEN                = 1097,
            RANK_CLOSE               = 1098,
            TOPOLOGIES_OPEN          = 1099,
            TOPOLOGIES_CLOSE         = 1100,
            SEVERITY_OPEN            = 1101,
            SEVERITY_CLOSE           = 1102,
            ANAME_VERSION            = 1103,
            ANAME_ENCODING           = 1104,
            ANAME_KEY                = 1105,
            ANAME_PAR_TYPE           = 1106,
            ANAME_PAR_KEY            = 1107,
            ANAME_PAR_VALUE          = 1108,
            ANAME_NAME               = 1109,
            ANAME_TITLE              = 1110,
            ANAME_FILE               = 1111,
            ANAME_VALUE              = 1112,
            ANAME_ID                 = 1113,
            ANAME_MOD                = 1114,
            ANAME_BEGIN              = 1115,
            ANAME_END                = 1116,
            ANAME_LINE               = 1117,
            ANAME_CALLEEID           = 1118,
            ANAME_NDIMS              = 1119,
            ANAME_SIZE               = 1120,
            ANAME_PERIODIC           = 1121,
            ANAME_LOCATIONID         = 1122,
            ANAME_LOCATIONGROUPID    = 1123,
            ANAME_STNODEID           = 1124,
            ANAME_THRDID             = 1125,
            ANAME_PROCID             = 1126,
            ANAME_NODEID             = 1127,
            ANAME_MACHID             = 1128,
            ANAME_METRICID           = 1129,
            ANAME_METRIC_TYPE        = 1130,
            ANAME_METRIC_VIZ_TYPE    = 1131,
            ANAME_METRIC_CONVERTIBLE = 1132,
            ANAME_METRIC_CACHEABLE   = 1133,
            ANAME_CNODEID            = 1134,
            ACUBEPL_ROWWISE          = 1135,
            ACUBEPL_AGGR_ATTRIBUTE   = 1136
        };
    };
    /// Token type.
    typedef token::yytokentype token_type;

    /// Build a parser object.
    Cube4Parser ( class Driver&                 driver_yyarg,
                      class ParseContext&       parseContext_yyarg,
                          class Cube4Scanner&   Cube4Lexer_yyarg,
                              class cube::Cube& cube_yyarg,
                                  bool&         clustering_on_yyarg );
    virtual
    ~Cube4Parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int
    parse();

#if CUBEPARSERDEBUG
    /// The current debugging stream.
    std::ostream&
    debug_stream() const;

    /// Set the current debugging stream.
    void
    set_debug_stream( std::ostream& );

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type
    debug_level() const;

    /// Set the current debugging level.
    void
    set_debug_level( debug_level_type l );

#endif

private:
    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void
    error( const location_type& loc,
           const std::string&   msg );

    /// Generate an error message.
    /// \param state   the state where the error occurred.
    /// \param tok     the lookahead token.
    virtual std::string
    yysyntax_error_( int yystate,
                     int tok );

#if CUBEPARSERDEBUG
    /// \brief Report a symbol value on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    virtual void
    yy_symbol_value_print_( int                  yytype,
                            const semantic_type* yyvaluep,
                            const location_type* yylocationp );

    /// \brief Report a symbol on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    virtual void
    yy_symbol_print_( int                  yytype,
                      const semantic_type* yyvaluep,
                      const location_type* yylocationp );

#endif


    /// State numbers.
    typedef int                  state_type;
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
    static bool
    yy_pact_value_is_default_( int yyvalue );

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool
    yy_table_value_is_error_( int yyvalue );

    /// Internal symbol numbers.
    typedef unsigned char token_number_type;
    /* Tables.  */
    /// For a state, the index in \a yytable_ of its portion.
    static const short int yypact_[];
    static const short int yypact_ninf_;

    /// For a state, default reduction number.
    /// Unless\a  yytable_ specifies something else to do.
    /// Zero means the default is an error.
    static const unsigned short int yydefact_[];

    static const short int yypgoto_[];
    static const short int yydefgoto_[];

    /// What to do in a state.
    /// \a yytable_[yypact_[s]]: what to do in state \a s.
    /// - if positive, shift that token.
    /// - if negative, reduce the rule which number is the opposite.
    /// - if zero, do what YYDEFACT says.
    static const unsigned short int yytable_[];
    static const signed char        yytable_ninf_;

    static const short int yycheck_[];

    /// For a state, its accessing symbol.
    static const unsigned short int yystos_[];

    /// For a rule, its LHS.
    static const unsigned short int yyr1_[];
    /// For a rule, its RHS length.
    static const unsigned char yyr2_[];

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string
    yytnamerr_( const char* n );


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if CUBEPARSERDEBUG
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
    virtual void
    yy_reduce_print_( int r );

    /// Print the state stack on the debug stream.
    virtual void
    yystack_print_();

    /* Debugging.  */
    int           yydebug_;
    std::ostream* yycdebug_;
#endif

    /// Convert a scanner token number \a t to a symbol number.
    token_number_type
    yytranslate_( int t );

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg        Why this token is reclaimed.
    ///                     If null, do not display the symbol, just free it.
    /// \param yytype       The symbol type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    inline void
    yydestruct_( const char*    yymsg,
                 int            yytype,
                 semantic_type* yyvaluep,
                 location_type* yylocationp );

    /// Pop \a n symbols the three stacks.
    inline void
    yypop_( unsigned int n = 1 );

    /* Constants.  */
    static const int yyeof_;
    /* LAST_ -- Last index in TABLE_.  */
    static const int               yylast_;
    static const int               yynnts_;
    static const int               yyempty_;
    static const int               yyfinal_;
    static const int               yyterror_;
    static const int               yyerrcode_;
    static const int               yyntokens_;
    static const unsigned int      yyuser_token_number_max_;
    static const token_number_type yyundef_token_;

    /* User arguments.  */
    class Driver&       driver;
    class ParseContext& parseContext;
    class Cube4Scanner& Cube4Lexer;
    class cube::Cube&   cube;
    bool&               clustering_on;
};
} // cubeparser
/* Line 33 of lalr1.cc  */
#line 444 "../../build-frontend/../src/cube/src/syntax/Cube4Parser.hpp"



#endif /* !YY_CUBEPARSER_BUILD_FRONTEND_SRC_CUBE_SRC_SYNTAX_CUBE4PARSER_HPP_INCLUDED  */
