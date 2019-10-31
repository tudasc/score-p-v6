/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_SCOREP_OA_SCANNER_H_INCLUDED
# define YY_YY_SCOREP_OA_SCANNER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_BEGINREQUESTS = 258,
    T_ENDREQUESTS = 259,
    T_SETNUMITERATIONS = 260,
    T_RUNTOSTART = 261,
    T_RUNTOEND = 262,
    T_GETSUMMARYDATA = 263,
    T_TERMINATE = 264,
    T_REQUEST = 265,
    T_NUMBER = 266,
    T_QSTRING = 267,
    T_STRING = 268,
    T_GLOBAL = 269,
    T_MPI = 270,
    T_METRIC = 271,
    T_EXECUTION_TIME = 272,
    T_PERISCOPE = 273,
    T_PAPI = 274,
    T_PERF = 275,
    T_RUSAGE = 276,
    T_PLUGIN = 277,
    T_OTHER = 278
  };
#endif
/* Tokens.  */
#define T_BEGINREQUESTS 258
#define T_ENDREQUESTS 259
#define T_SETNUMITERATIONS 260
#define T_RUNTOSTART 261
#define T_RUNTOEND 262
#define T_GETSUMMARYDATA 263
#define T_TERMINATE 264
#define T_REQUEST 265
#define T_NUMBER 266
#define T_QSTRING 267
#define T_STRING 268
#define T_GLOBAL 269
#define T_MPI 270
#define T_METRIC 271
#define T_EXECUTION_TIME 272
#define T_PERISCOPE 273
#define T_PAPI 274
#define T_PERF 275
#define T_RUSAGE 276
#define T_PLUGIN 277
#define T_OTHER 278

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 85 "../../build-mpi/../src/measurement/online_access/scorep_oa_scanner.y" /* yacc.c:1909  */

  int   Number;
  char *String;

#line 105 "scorep_oa_scanner.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SCOREP_OA_SCANNER_H_INCLUDED  */
