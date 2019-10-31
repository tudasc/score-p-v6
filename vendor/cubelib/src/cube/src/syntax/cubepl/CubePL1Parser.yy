/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2017                                                **
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


%code requires{ 
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



}

/*** yacc/bison Declarations ***/

/* Require bison 2.3 or later */
/* %require "2.6" */

/* add debug output code to generated parser. */
%debug

/* start symbol is named "document" */
%start document

/* write out a header file containing the token defines */
%defines

/* use newer C++ skeleton file */
/* %skeleton "bison.cc" */
%skeleton "lalr1.cc"


/* namespace to enclose parser in */
%define api.prefix cubeplparser

/* set the parser's class identifier */
%define "parser_class_name" CubePL1Parser

/* keep track of the current position within the input */
%locations


  

%initial-action
{
    // initialize the initial location object
};

/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class CubePL1ParseContext& parseContext }
%parse-param { class CubePL1Scanner& CubePL1Lexer }

/* verbose error messages */
%error-verbose

 /*** the grammar's tokens ***/
%union{}
 
%token START_DOCUMENT           "<cubepl>"
%token END_DOCUMENT   		"</cubepl>"
%token OP_PLUS       		"+" 
%token OP_MINUS      		"-" 
%token OP_MULT       		"*" 
%token OP_DIVIDE     		"/" 
%token OP_POWER      		"^" 
%token OPEN_EXP      		"(" 
%token CLOSE_EXP     		")" 
%token OPEN_ARRAY_INDEX	"[" 
%token CLOSE_ARRAY_INDEX	"]" 
%token OPEN_LCALC    		"{"
%token CLOSE_LCALC   		"}"
%token OPEN_GM_CUBEPL    	"<<"
%token CLOSE_GM_CUBEPL		">>"

%token RETURN_EXP    		"return"
%token STATEMENT_SEP 		";"
%token SIZEOF	     		"sizeof"
%token DEFINED	     		"defined"
%token LOCAL_VAR            "local"
%token GLOBAL_VAR           "global"
%token ABS_MARK	     		"|"
%token ARGUMENT1      		"arg1" 
%token ARGUMENT2      		"arg2" 
%token FUN_SQRT      		"sqrt" 
%token FUN_SIN       		"sin" 
%token FUN_ASIN      		"asin" 
%token FUN_COS       		"cos" 
%token FUN_ACOS      		"acos" 
%token FUN_TAN       		"tan" 
%token FUN_ATAN      		"atan" 
%token FUN_EXP       		"exp" 
%token FUN_LOG       		"log"
%token FUN_ABS       		"abs"
%token FUN_RANDOM    		"random" 
%token FUN_SGN       		"sgn" 
%token FUN_POS       		"pos" 
%token FUN_NEG       		"neg" 
%token FUN_FLOOR     		"floor" 
%token FUN_CEIL      		"ceil"
%token FUN_MIN       		"min"
%token FUN_MAX       		"max"
%token KEYWORD_IF    		"if"
%token KEYWORD_ELSEIF 		"elseif"
%token KEYWORD_ELSE  		"else"
%token KEYWORD_WHILE 		"while"
%token KEYWORD_ASSIGN 		"="
%token KEYWORD_BIGGER 		">"
%token KEYWORD_EQUAL  		"=="
%token KEYWORD_STRING_EQUAL	"eq"
%token KEYWORD_STRING_SEMI_EQUAL"seq"
%token KEYWORD_HALFBIGGER 	">="
%token KEYWORD_HALFSMALLER 	"<="
%token KEYWORD_NOT_EQUAL 	"!="
%token KEYWORD_SMALLER 		"<"
%token KEYWORD_NOT   		"not"
%token KEYWORD_AND		"and"
%token KEYWORD_OR		"or"
%token KEYWORD_XOR		"xor"
%token KEYWORD_TRUE		"true"
%token KEYWORD_FALSE		"false"
%token KEYWORD_VAR 		"$"
%token COMMA	     		","
%token KEYWORD_REGEXP		"=~"
%token KEYWORD_METRIC 		"metric::"
%token KEYWORD_FIXED_METRIC 	"metric::fixed::"
%token KEYWORD_METRIC_CALL 	"metric::call::"
%token KEYWORD_ENV		"env"
%token KEYWORD_LOWERCASE	"lowercase"
%token KEYWORD_UPPERCASE	"uppercase"
%token KEYWORD_GHOST_POSTMETRIC	"cube::metric::postderived::"
%token KEYWORD_GHOST_PREMETRIC	"cube::metric::prederived::"
%token KEYWORD_METRIC_INIT "cube::init::metric::"
%token KEYWORD_METRIC_FLEX_AGGR_PLUS  "cube::metric::plus::"
%token KEYWORD_METRIC_FLEX_AGGR_MINUS "cube::metric::minus::"
%token KEYWORD_METRIC_SET       "cube::metric::set::"
%token KEYWORD_METRIC_GET       "cube::metric::get::"
%token CONSTANT       		100
%token STRING_CONSTANT		200
%token STRING_TEXT		210
%token METRIC_NAME    		300
%token INIT_METRIC_NAME    301
%token INCL_MODIFICATOR 	"i"
%token EXCL_MODIFICATOR 	"e"
%token SAME_MODIFICATOR 	600 
%token QUOTED_STRING		400
%token REGEXP_STRING		500
%token END 0               	"end of file"





/* priorities */
%left COMMA
%left KEYWORD_AND KEYWORD_OR KEYWORD_XOR 
%left KEYWORD_NOT
%left KEYWORD_BIGGER KEYWORD_HALFBIGGER KEYWORD_SMALLER KEYWORD_HALFSMALLER KEYWORD_EQUAL KEYWORD_NOT_EQUAL
%left OP_PLUS OP_MINUS
%left OP_DIVIDE OP_MULT
%left OP_POWER
%left FUN_SQRT FUN_ABS FUN_ASIN FUN_ACOS FUN_ATAN FUN_COS FUN_EXP FUN_LOG FUN_RANDOM FUN_SIN FUN_TAN FUN_MIN FUN_MAX FUN_FLOOR FUN_CEIL FUN_SGN FUN_POS FUN_NEG FUNC2 SIZEOF DEFINED
%left SIGN


%{
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
#if defined(__SVR4) &&  defined(__SUNPRO_CC)
  #include <ieeefp.h>

  #define isinf(x)  (fpclass(x) == FP_NINF || fpclass(x) == FP_PINF)
  #define isnan(x)  isnand(x)
#endif

%}

%% /*** Grammar Rules ***/





/*** document structure ***/


document: START_DOCUMENT expression END_DOCUMENT 
	{ 
	    if (!parseContext.test_modus)
	    {
		parseContext.result = parseContext._stack.top();
		parseContext._stack.pop();
    	    }
    	    parseContext.syntax_ok &= true;
	} | 
	START_DOCUMENT  END_DOCUMENT 
	{ 
    	    parseContext.syntax_ok &= true;
	} 
	;


expression : enclosed_expression 
	    | absolute_value
	    | sum 
	    | subtract 
	    | division
	    | multiplication
	    | power
	    | negation %prec SIGN
	    | function_call 
	    | constant
	    | metric_refs
	    | lambda_calcul
	    | sizeof_variable
	    | defined_variable
	    | arguments
	    | get_variable 
	    | quoted_string 
	    | string_function
	    | metric_get
	    ;
	    
	    
enclosed_expression : OPEN_EXP expression CLOSE_EXP 
	    { 
		if (!parseContext.test_modus)
		{
		    GeneralEvaluation * _arg1 = parseContext._stack.top();
		    parseContext._stack.pop();
		    parseContext._stack.push( new EncapsulationEvaluation(_arg1) );
		}
		parseContext.syntax_ok &= true;
	    };
absolute_value : ABS_MARK expression ABS_MARK 
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
	    };

sum	: expression OP_PLUS expression 
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
	    };

subtract: expression OP_MINUS expression 	    
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
	    };

	;
division : expression OP_DIVIDE expression 
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
	    };
	;
multiplication	: expression OP_MULT expression 
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
	    };



	    
power	: expression OP_POWER expression 
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
	    };
negation: OP_MINUS expression 
	    { 
		if (!parseContext.test_modus)
		{
		    GeneralEvaluation * arg = parseContext._stack.top();
		    parseContext._stack.pop();
		    parseContext._stack.push( new NegativeEvaluation(arg) );
		}
		parseContext.syntax_ok &= true;
	    };

arguments: 
argument1 | argument2 ;

argument1 : ARGUMENT1
	    {  
		if (!parseContext.test_modus)
		{
			parseContext._stack.push(new ArgumentEvaluation(cube::FIRST_ARGUMENT) );
		}
		parseContext.syntax_ok &= true;
	    };

argument2 : ARGUMENT2
	    {  
		if (!parseContext.test_modus)
		{
			parseContext._stack.push(new ArgumentEvaluation(cube::SECOND_ARGUMENT) );
		}
		parseContext.syntax_ok &= true;
	    } 




boolean_expression:  enclosed_boolean_expression 
		    | equality 
		    | not_equality
		    | bigger
		    | smaller
		    | halfbigger
		    | halfsmaller 
		    | and_expression 
		    | or_expression
		    | xor_expression
		    | true_expression
		    | false_expression
		    | string_operation
		    
;
	    
enclosed_boolean_expression : OPEN_EXP boolean_expression CLOSE_EXP 
		    { 
			if (!parseContext.test_modus)
			{
			    GeneralEvaluation * _arg1 = parseContext._stack.top();
			    parseContext._stack.pop();
			    parseContext._stack.push( new EncapsulationEvaluation(_arg1) );
			}
			parseContext.syntax_ok &= true;
		    }
		| KEYWORD_NOT OPEN_EXP boolean_expression CLOSE_EXP 
		    { 
			if (!parseContext.test_modus)
			{
			    GeneralEvaluation * _arg1 = parseContext._stack.top();
			    parseContext._stack.pop();
			    parseContext._stack.push( new NotEvaluation(_arg1) );
			}
			parseContext.syntax_ok &= true;
		    };

and_expression: boolean_expression KEYWORD_AND boolean_expression
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
	    };
or_expression: boolean_expression KEYWORD_OR boolean_expression
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
	    };

xor_expression: boolean_expression KEYWORD_XOR boolean_expression
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
	    };
true_expression: KEYWORD_TRUE
	    { 
		if (!parseContext.test_modus)
		{
		    parseContext._stack.push( new ConstantEvaluation(1) );
		}
		parseContext.syntax_ok &= true;
	    };
false_expression: KEYWORD_FALSE
	    { 
		if (!parseContext.test_modus)
		{
		    parseContext._stack.push( new ConstantEvaluation(0) );
		}
		parseContext.syntax_ok &= true;
	    };

equality: expression KEYWORD_EQUAL expression
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
	    };

not_equality: expression KEYWORD_NOT_EQUAL expression
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
	    };


bigger : expression KEYWORD_BIGGER expression 
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
	    };

smaller: expression KEYWORD_SMALLER expression 
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
	    };


halfbigger: expression KEYWORD_HALFBIGGER expression 
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
	    };


halfsmaller: expression KEYWORD_HALFSMALLER expression 
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
	    };




string_operation :  string_equality 
		    | string_semi_equality
		    | regexp 
		    
;


string_equality : expression KEYWORD_STRING_EQUAL expression
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
		};

string_semi_equality : expression KEYWORD_STRING_SEMI_EQUAL expression
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
		};
regexp : expression KEYWORD_REGEXP regexp_expression
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
		};



regexp_expression : REGEXP_STRING
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
		};		 





quoted_string: QUOTED_STRING
		{
		    if (!parseContext.test_modus)
		    {		    
		    parseContext._stack.push( new StringConstantEvaluation( parseContext.str.str() ));
		    parseContext.str.str("");
		    }
		    parseContext.syntax_ok &= true;		    
		};


string_function: lowercase | uppercase | getenv
;


lowercase : 
		KEYWORD_LOWERCASE OPEN_EXP expression CLOSE_EXP 
		    { 
			if (!parseContext.test_modus)
			{
			    GeneralEvaluation * _arg1 = parseContext._stack.top();
			    parseContext._stack.pop();
			    parseContext._stack.push( new LowerCaseEvaluation(_arg1) );
			}
			parseContext.syntax_ok &= true;
		    }
;
uppercase:  KEYWORD_UPPERCASE OPEN_EXP expression CLOSE_EXP 
		    { 
			if (!parseContext.test_modus)
			{
			    GeneralEvaluation * _arg1 = parseContext._stack.top();
			    parseContext._stack.pop();
			    parseContext._stack.push( new UpperCaseEvaluation(_arg1) );
			}
			parseContext.syntax_ok &= true;
		    }
;

getenv:  KEYWORD_ENV OPEN_EXP expression CLOSE_EXP 
		    { 
			if (!parseContext.test_modus)
			{
			    GeneralEvaluation * _arg1 = parseContext._stack.top();
			    parseContext._stack.pop();
			    parseContext._stack.push( new EnvEvaluation(_arg1) );
			}
			parseContext.syntax_ok &= true;
		    }
;



metric_get: KEYWORD_METRIC_GET METRIC_NAME  OPEN_EXP quoted_string CLOSE_EXP
		{
		    if (!parseContext.test_modus)
		    {
			std::string uniq_name = parseContext.name_of_metric;			      
			Metric * _met = parseContext.cube->get_met(uniq_name);
			if (_met != NULL)
			{
			    GeneralEvaluation * _property = parseContext._stack.top();
			    parseContext._stack.pop();
			    MetricGetEvaluation * _metric_get_eval = new MetricGetEvaluation( _met, _property );
			    parseContext._stack.push( _metric_get_eval );
			}else
			{
			    cout << " Metric with uniq name " << uniq_name << " doesn't exists in cube" << endl;
			}
		    }
		    parseContext.syntax_ok &= true;
		};



    
function_call	: one_variable_function | two_variables_function ;

one_variable_function : function_name OPEN_EXP expression CLOSE_EXP  
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
		} ;


function_name :
		FUN_SQRT  
		{  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new SqrtEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		} |
		FUN_SIN
		{  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new SinEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		} |
		FUN_ASIN
		{  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new ASinEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		} |
		FUN_COS
		{  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new CosEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		} |
		FUN_ACOS
		{  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new ACosEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		} |
		FUN_EXP
		{  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new ExpEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		} |
		FUN_LOG
		{  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new LnEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		} |
		FUN_TAN
		{  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new TanEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		} |
		FUN_ATAN
		{  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new ATanEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		} |
		FUN_RANDOM
		{  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new RandomEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		} |
		FUN_ABS
		{  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new AbsEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		} |
		FUN_SGN
		{  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new SgnEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		} |
		FUN_POS
		{  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new PosEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		} |
		FUN_NEG
		{  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new NegEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		} |
		FUN_FLOOR
		{  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new FloorEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		} |
		FUN_CEIL
		{  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new CeilEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		} 
 ;


two_variables_function : function2_name OPEN_EXP expression COMMA expression CLOSE_EXP 
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
		};

function2_name: FUN_MIN
		{  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new MinEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		} |
		FUN_MAX
		{  
		    if (!parseContext.test_modus)
		    {
			    parseContext.function_call.push( new MaxEvaluation());
		    }
		    parseContext.syntax_ok &= true;
		} 
	;


constant: CONSTANT 
	    {
	       if (!parseContext.test_modus)
	       {
		double _value = atof( parseContext.value.c_str());
		parseContext._stack.push( new ConstantEvaluation(_value));
		parseContext.value = "";
		}
		parseContext.syntax_ok &= true;
	    };

metric_refs : context_metric | fixed_metric | metric_call
	    ;
	    
	    

context_metric : KEYWORD_METRIC METRIC_NAME OPEN_EXP CLOSE_EXP
	{ 
	    if (!parseContext.test_modus)
	    {
		Metric * _met = parseContext.cube->get_met(parseContext.name_of_metric);
		if (_met != NULL)
		{	    
		    parseContext._stack.push( new DirectMetricEvaluation(cube::CONTEXT_METRIC,  parseContext.cube, _met ));
		    _met->isUsedByOthers( true );
		}
		else
		{
		    cerr << "Cannot connect to the metric " << parseContext.name_of_metric << ". Seems that this metric is not created yet. Value of metric::" << parseContext.name_of_metric << "() will be always 0" << endl;
		    parseContext._stack.push( new ConstantEvaluation( 0 ));
		
		}
		parseContext.value = "";
    	    }
    	    parseContext.syntax_ok &= true;
	} |
	 KEYWORD_METRIC METRIC_NAME OPEN_EXP calculationFlavourModificator CLOSE_EXP
	{ 
	    if (!parseContext.test_modus)
	    {
		Metric * _met = parseContext.cube->get_met(parseContext.name_of_metric);
		if (_met != NULL)
		{	    
		    cube::CalcFlavorModificator * mod = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();
		    parseContext._stack.push( new DirectMetricEvaluation(cube::CONTEXT_METRIC,  parseContext.cube, _met, mod ));
		    _met->isUsedByOthers( true );
		}
		else
		{
		    cerr << "Cannot connect to the metric " << parseContext.name_of_metric << ". Seems that this metric is not created yet. Value of metric::"<<parseContext.name_of_metric << "( ?  ) will be always 0" << endl;
		    parseContext._stack.push( new ConstantEvaluation( 0 ));
		
		}
		parseContext.value = "";
    	    }
    	    parseContext.syntax_ok &= true;
	} |
	 KEYWORD_METRIC METRIC_NAME OPEN_EXP calculationFlavourModificator COMMA calculationFlavourModificator CLOSE_EXP
	{ 
	    if (!parseContext.test_modus)
	    {
		Metric * _met = parseContext.cube->get_met(parseContext.name_of_metric);
		if (_met != NULL)
		{	    
		    cube::CalcFlavorModificator * mod2 = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();
		    cube::CalcFlavorModificator * mod1 = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();

		    parseContext._stack.push( new DirectMetricEvaluation(cube::CONTEXT_METRIC,  parseContext.cube, _met, mod1, mod2));
		    _met->isUsedByOthers( true );
		}
		else
		{
		    cerr << "Cannot connect to the metric " << parseContext.name_of_metric << ". Seems that this metric is not created yet. Value of metric::"<<parseContext.name_of_metric << "( ?, ? ) will be always 0" << endl;
		    parseContext._stack.push( new ConstantEvaluation( 0 ));
		
		}
		parseContext.value = "";
    	    }
    	    parseContext.syntax_ok &= true;
	} 
	;

	
fixed_metric : KEYWORD_FIXED_METRIC METRIC_NAME OPEN_EXP CLOSE_EXP
	{ 
	    if (!parseContext.test_modus)
	    {
		Metric * _met = parseContext.cube->get_met(parseContext.name_of_metric);
		if (_met != NULL)
		{	    
		    parseContext._stack.push( new DirectMetricEvaluation(cube::FIXED_METRIC_FULL_AGGR,  parseContext.cube, _met ));
		    _met->isUsedByOthers( true );
		}
		else
		{
		    cerr << "Cannot connect to the metric " << parseContext.name_of_metric << ". Seems that this metric is not created yet. Value of metric::"<<parseContext.name_of_metric << "() will be always 0" << endl;
		    parseContext._stack.push( new ConstantEvaluation( 0 ));
		
		}
		parseContext.value = "";
    	    }
    	    parseContext.syntax_ok &= true;
	} |
	 KEYWORD_FIXED_METRIC METRIC_NAME OPEN_EXP calculationFlavourModificator CLOSE_EXP
	{ 
	    if (!parseContext.test_modus)
	    {
		Metric * _met = parseContext.cube->get_met(parseContext.name_of_metric);
		if (_met != NULL)
		{	    
		    cube::CalcFlavorModificator * mod = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();
		    parseContext._stack.push( new DirectMetricEvaluation(cube::FIXED_METRIC_AGGR_SYS,  parseContext.cube, _met, mod ));
		    _met->isUsedByOthers( true );

		}
		else
		{
		    cube::CalcFlavorModificator * mod = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();
		    cerr << "Cannot connect to the metric " << parseContext.name_of_metric << ". Seems that this metric is not created yet. Value of metric::fixed::"<<parseContext.name_of_metric << "( "; mod->print(); cout << " ) will be always 0" << endl;
		    

		    delete mod;
		    
		    parseContext._stack.push( new ConstantEvaluation( 0 ));
		
		}
		parseContext.value = "";
    	    }
    	    parseContext.syntax_ok &= true;
	} |
	 KEYWORD_FIXED_METRIC METRIC_NAME OPEN_EXP calculationFlavourModificator COMMA calculationFlavourModificator CLOSE_EXP
	{ 
	    if (!parseContext.test_modus)
	    {
		Metric * _met = parseContext.cube->get_met(parseContext.name_of_metric);
		if (_met != NULL)
		{	    
		    cube::CalcFlavorModificator * mod2 = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();
		    cube::CalcFlavorModificator * mod1 = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();

		    parseContext._stack.push( new DirectMetricEvaluation(cube::FIXED_METRIC_NO_AGGR,  parseContext.cube, _met, mod1, mod2));
		    _met->isUsedByOthers( true );
		}
		else
		{
		    cube::CalcFlavorModificator * mod2 = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();
		    cube::CalcFlavorModificator * mod1 = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();
		    cerr << "Cannot connect to the metric " << parseContext.name_of_metric << ". Seems that this metric is not created yet. Value of metric::fixed::"<<parseContext.name_of_metric << "( "; mod1->print(); cout << ","; mod2->print(); cout <<") will be always 0" << endl;

		    
		    delete mod2;
		    delete mod1;
		    
		    parseContext._stack.push( new ConstantEvaluation( 0 ));
		
		}
		parseContext.value = "";
    	    }
    	    parseContext.syntax_ok &= true;
	} 
	;
	
		
metric_call :  KEYWORD_METRIC_CALL METRIC_NAME OPEN_EXP  expression COMMA  calculationFlavourModificator CLOSE_EXP
	{ 
	    if (!parseContext.test_modus)
	    {
		Metric * _met = parseContext.cube->get_met(parseContext.name_of_metric);
		if (_met != NULL)
		{	    
		    cube::CalcFlavorModificator * mod = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();
		    GeneralEvaluation * _cnode_id = parseContext._stack.top();
		    parseContext._stack.pop();

		    parseContext._stack.push( new DirectMetricEvaluation(cube::METRIC_CALL_CALLPATH,  parseContext.cube, _met, _cnode_id, mod ));
		    _met->isUsedByOthers( true );

		}
		else
		{
		    cube::CalcFlavorModificator * mod = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();

		    GeneralEvaluation * _cnode_id = parseContext._stack.top();
		    parseContext._stack.pop();

		    cerr << "Cannot connect to the metric " << parseContext.name_of_metric << ". Seems that this metric is not created yet. Value of metric::call::"<<parseContext.name_of_metric << "( "; _cnode_id->print(); cout << ","; mod->print(); cout <<") will be always 0" << endl;
		    delete mod;
		    delete _cnode_id;
		    
		    parseContext._stack.push( new ConstantEvaluation( 0 ));
		
		}
		parseContext.value = "";
    	    }
    	    parseContext.syntax_ok &= true;
	} |
	KEYWORD_METRIC_CALL METRIC_NAME OPEN_EXP  expression COMMA  calculationFlavourModificator COMMA  expression COMMA  calculationFlavourModificator  CLOSE_EXP
	{ 
	    if (!parseContext.test_modus)
	    {
		Metric * _met = parseContext.cube->get_met(parseContext.name_of_metric);
		if (_met != NULL)
		{	    
		    cube::CalcFlavorModificator * mod2 = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();
		    cube::CalcFlavorModificator * mod1 = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();
		    GeneralEvaluation * _sysres_id = parseContext._stack.top();
		    parseContext._stack.pop();
		    GeneralEvaluation * _cnode_id = parseContext._stack.top();
		    parseContext._stack.pop();
		    parseContext._stack.push( new DirectMetricEvaluation(cube::METRIC_CALL_FULL,  parseContext.cube, _met, _cnode_id, mod1, _sysres_id,  mod2));
		    _met->isUsedByOthers( true );
		}
		else
		{
		    cube::CalcFlavorModificator * mod2 = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();
		    cube::CalcFlavorModificator * mod1 = parseContext.calcFlavorModificators.top();
		    parseContext.calcFlavorModificators.pop();
		    GeneralEvaluation * _sysres_id = parseContext._stack.top();
		    parseContext._stack.pop();
		    GeneralEvaluation * _cnode_id = parseContext._stack.top();
		    parseContext._stack.pop();
		    cerr << "Cannot connect to the metric " << parseContext.name_of_metric << ". Seems that this metric is not created yet. Value of metric::call::"<<parseContext.name_of_metric << "( "; _cnode_id->print(); cout << ","; mod1->print(); cout << ","; _sysres_id->print(); cout << ","; mod2->print(); cout <<") will be always 0" << endl;

		    
		    delete mod2;
		    delete mod1;
		    delete _cnode_id;
		    delete _sysres_id;
		    
		    parseContext._stack.push( new ConstantEvaluation( 0 ));
		
		}
		parseContext.value = "";
    	    }
    	    parseContext.syntax_ok &= true;
	} 
	;
	
	

calculationFlavourModificator:    INCL_MODIFICATOR 
				{ 
				    if (!parseContext.test_modus)
				    {
					parseContext.calcFlavorModificators.push(new CalcFlavorModificatorIncl());
				    }
				    parseContext.syntax_ok &= true;
				} |  
				EXCL_MODIFICATOR 
				{ 
				    if (!parseContext.test_modus)
				    {
					parseContext.calcFlavorModificators.push(new CalcFlavorModificatorExcl());
				    }
				    parseContext.syntax_ok &= true;
				} | 
				SAME_MODIFICATOR
				{ 
				    if (!parseContext.test_modus)
				    {
					parseContext.calcFlavorModificators.push(new CalcFlavorModificatorSame());
				    }
				    parseContext.syntax_ok &= true;
				}
				;


lambda_calcul : lambda_start list_of_statements return_expression CLOSE_LCALC
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
	    };

return_expression: RETURN_EXP expression STATEMENT_SEP;

lambda_start: OPEN_LCALC
	    { 
		if (!parseContext.test_modus)
		{
		    parseContext._number_of_statements.push(0);
		}
		parseContext.syntax_ok &= true;
	    };

list_of_statements : 
		     | 
		    statement  STATEMENT_SEP list_of_statements 	    
;



statement : 
	   if_statement 
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
        | while_statement
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
        | assignment
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
        | local_variable
	    {
		parseContext.syntax_ok &= true;
	    } 
        | global_variable
	    {
		parseContext.syntax_ok &= true;
	    } 
	| metric_set 
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
	| create_ghost_metric 
	    {
		parseContext.syntax_ok &= true;
	    } 
	| init_metric 
	    {
		parseContext.syntax_ok &= true;
	    } 
	| flex_aggr_plus 
	    {
		parseContext.syntax_ok &= true;
	    } 
	| flex_aggr_minus
	    {
		parseContext.syntax_ok &= true;
	    }
;

metric_set : KEYWORD_METRIC_SET METRIC_NAME  OPEN_EXP quoted_string COMMA quoted_string CLOSE_EXP
{
	    if (!parseContext.test_modus)
	    {
		std::string uniq_name = parseContext.name_of_metric;			      
		Metric * _met = parseContext.cube->get_met(uniq_name);
		GeneralEvaluation * _value = parseContext._stack.top();
		parseContext._stack.pop();
		GeneralEvaluation * _property = parseContext._stack.top();
		parseContext._stack.pop();
		MetricSetEvaluation * _metric_set_eval = new MetricSetEvaluation( _met, _property , _value);
		parseContext._statements.push( _metric_set_eval );
		if (_met == NULL)
		{
		    cout << " Metric with uniq name " << uniq_name << " doesn't exists in cube. metric::set has no action." << endl;
		}
	    }
	    parseContext.syntax_ok &= true;
};




if_statement : 
		simple_if_statement
		| full_if_statement
		| elseif_if_statement
		| elseif_full_if_statement
;


simple_if_statement: if_condition enclosed_list_of_statements
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
	    };

full_if_statement: if_condition enclosed_list_of_statements else_enclosed_list_of_statements
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
	    };

elseif_full_if_statement: if_condition enclosed_list_of_statements elseifs else_enclosed_list_of_statements
	    { 
		if (!parseContext.test_modus)
		{
		    std::stack<std::stack<GeneralEvaluation*> > statement_blocks;
		    std::stack<GeneralEvaluation*>  statement_conditions;
 
		    int _num_of_false_statements = parseContext._number_of_statements.top();
		    parseContext._number_of_statements.pop();
		    std::stack<GeneralEvaluation*> _tmp_false_statements;
		    for (int i=0; i<_num_of_false_statements; i++)
		    {
			_tmp_false_statements.push( parseContext._statements.top());
			parseContext._statements.pop();
		    }
		    statement_blocks.push( _tmp_false_statements);

		    for (unsigned i=0; i<parseContext.number_elseif + 1 /* +1 is for the initial condition*/; ++i)
		    {
			int _num_of_statements = parseContext._number_of_statements.top();
			parseContext._number_of_statements.pop();
			std::stack<GeneralEvaluation*> _tmp_statements;
			for (int j=0; j<_num_of_statements; j++)
			{
			    _tmp_statements.push( parseContext._statements.top());
			    parseContext._statements.pop();
			}

			GeneralEvaluation * _condition = parseContext._stack.top();
			parseContext._stack.pop();
			statement_blocks.push( _tmp_statements);
			statement_conditions.push( _condition );
		    }
		    ExtendedIfEvaluation * _ext_if_calc = new ExtendedIfEvaluation(statement_conditions, statement_blocks);
		    parseContext._statements.push(_ext_if_calc);

		    parseContext.number_elseif= 0;
		}
		parseContext.syntax_ok &= true;
	    };



elseif_if_statement: if_condition enclosed_list_of_statements elseifs 
	    { 
		if (!parseContext.test_modus)
		{
		    std::stack<std::stack<GeneralEvaluation*> > statement_blocks;
		    std::stack<GeneralEvaluation*>  statement_conditions;

		    for (unsigned i=0; i<parseContext.number_elseif + 1 /* +1 is for the initial condition*/; ++i)
		    {
			int _num_of_statements = parseContext._number_of_statements.top();
			parseContext._number_of_statements.pop();
			std::stack<GeneralEvaluation*> _tmp_statements;
			for (int j=0; j<_num_of_statements; j++)
			{
			    _tmp_statements.push( parseContext._statements.top());
			    parseContext._statements.pop();
			}

			GeneralEvaluation * _condition = parseContext._stack.top();
			parseContext._stack.pop();
			statement_blocks.push( _tmp_statements);
			statement_conditions.push( _condition );
		    }
		    ExtendedIfEvaluation * _ext_if_calc = new ExtendedIfEvaluation(statement_conditions, statement_blocks);
		    parseContext._statements.push(_ext_if_calc);

		    parseContext.number_elseif= 0;
		}
		parseContext.syntax_ok &= true;
	    };


elseifs :
	elseif_enclosed_list_of_statements
	| elseif_enclosed_list_of_statements elseifs
;

elseif_enclosed_list_of_statements:  KEYWORD_ELSEIF OPEN_EXP boolean_expression CLOSE_EXP  enclosed_list_of_statements
	    { 
		if (!parseContext.test_modus)
		{
		    parseContext.number_elseif++;
		}
		parseContext.syntax_ok &= true;
	    };
;

if_condition: KEYWORD_IF OPEN_EXP boolean_expression CLOSE_EXP 
;

else_enclosed_list_of_statements:  KEYWORD_ELSE enclosed_list_of_statements
;

enclosed_list_of_statements: enclosed_list_of_statements_start list_of_statements CLOSE_LCALC 
;

enclosed_list_of_statements_start: OPEN_LCALC
	    { 
		if (!parseContext.test_modus)
		{
		    parseContext._number_of_statements.push(0);
		}
		parseContext.syntax_ok &= true;
	    };


while_statement: KEYWORD_WHILE OPEN_EXP boolean_expression CLOSE_EXP enclosed_list_of_statements 
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
	    };
	
	    
assignment: assignment_target KEYWORD_ASSIGN expression 
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
;

assignment_target: put_variable | put_variable_indexed
;

put_variable: KEYWORD_VAR OPEN_LCALC string_constant CLOSE_LCALC
	      {
		if (!parseContext.test_modus)
		{      
		    parseContext._stack.push( new ConstantEvaluation(0) ); // pushed index 0 if array index is not specified
		}
		parseContext.syntax_ok &= true;
	      }
;

put_variable_indexed: KEYWORD_VAR OPEN_LCALC string_constant CLOSE_LCALC OPEN_ARRAY_INDEX expression CLOSE_ARRAY_INDEX
;


create_ghost_metric : create_postderived_ghost_metric 
		       | create_prederived_inclusive_ghost_metric
		       | create_prederived_exclusive_ghost_metric
		    ;

		    
create_postderived_ghost_metric: KEYWORD_GHOST_POSTMETRIC METRIC_NAME GhostMetricDefinition
		    {
			    if (!parseContext.test_modus)
			    {
			      std::string expression = parseContext.str.str();
			      parseContext.str.str("");
			      std::string uniq_name = parseContext.name_of_metric;			      
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
								      true,
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
			      cubeplparser::CubePL1Driver* driver         = new cubeplparser::CubePL1Driver( parseContext.cube ); // create driver for this cube
			      std::string nested_error;
			      if (! driver->test( cubepl_program, nested_error ))
			      {
				parseContext.syntax_ok &= false;
			      }
			      delete driver;
			    }
			    parseContext.syntax_ok &= true;
			    
		    }
		    ;
create_prederived_inclusive_ghost_metric: KEYWORD_GHOST_PREMETRIC METRIC_NAME  OPEN_EXP INCL_MODIFICATOR CLOSE_EXP  GhostMetricDefinition
			    {
			      if (!parseContext.test_modus)
			      {
				std::string expression = parseContext.str.str();
				parseContext.str.str("");
				std::string uniq_name = parseContext.name_of_metric;			      
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
								      true, 
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
				cubeplparser::CubePL1Driver* driver         = new cubeplparser::CubePL1Driver( parseContext.cube ); // create driver for this cube
				std::string nested_error;
				if (! driver->test( cubepl_program, nested_error ))
				{
				  parseContext.syntax_ok = false;
				}
				delete driver;
			      }
			      parseContext.syntax_ok &= true;
			    }
		    ;		    
create_prederived_exclusive_ghost_metric: KEYWORD_GHOST_PREMETRIC METRIC_NAME  OPEN_EXP EXCL_MODIFICATOR CLOSE_EXP  GhostMetricDefinition
			    {
				if (!parseContext.test_modus)
				{
				  std::string expression = parseContext.str.str();
				  parseContext.str.str("");
				  std::string uniq_name = parseContext.name_of_metric;			      
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
									true,
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
				  cubeplparser::CubePL1Driver* driver         = new cubeplparser::CubePL1Driver( parseContext.cube ); // create driver for this cube
				  std::string nested_error;
				  if (! driver->test( cubepl_program, nested_error ))
				  {
				    parseContext.syntax_ok = false;
				  }
				  delete driver;
			      }
			      parseContext.syntax_ok &= true;
			    }
		    ;	

GhostMetricDefinition : OPEN_GM_CUBEPL  CubePLGhostText  
		    ;
		 
CubePLGhostText : STRING_TEXT 
		    ;


		    
		    
init_metric :  KEYWORD_METRIC_INIT METRIC_NAME  GhostMetricDefinition
                {
                if (!parseContext.test_modus)
                {
                  std::string expression = parseContext.str.str();
                  parseContext.str.str("");
                  std::string uniq_name = parseContext.name_of_metric;                 
                  Metric * _met = parseContext.cube->get_met(uniq_name);

                    if (_met == NULL)
                    {
                        cout << " Metric with uniq name " << uniq_name << " doesn't  exists yet. Cannot assign CubePL initialization expression. Skip." << endl;
                    }else 
                    {
                        _met->set_init_expression( expression );
                    }
                  }else
                  {  
                  std::string expression = parseContext.str.str();
                  std::string                  cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
                  cubeplparser::CubePL1Driver* driver         = new cubeplparser::CubePL1Driver( parseContext.cube ); // create driver for this cube
                  std::string nested_error;
                  if (! driver->test( cubepl_program, nested_error ))
                  {
                    parseContext.syntax_ok = false;
                  }
                  delete driver;
                  }
                  parseContext.syntax_ok &= true;
                }
            ;   

flex_aggr_plus :  KEYWORD_METRIC_FLEX_AGGR_PLUS INIT_METRIC_NAME  GhostMetricDefinition
                {
                if (!parseContext.test_modus)
                {
                  std::string expression = parseContext.str.str();
                  parseContext.str.str("");
                  std::string uniq_name = parseContext.name_of_metric;                 
                  Metric * _met = parseContext.cube->get_met(uniq_name);

                    if (_met == NULL)
                    {
                        cout << " Metric with uniq name " << uniq_name << " doesn't  exists yet. Cannot assign CubePL initialization expression. Skip." << endl;
                    }else 
                    {
                        _met->set_aggr_plus_expression( expression );
                    }
                  }else
                  {  
                  std::string expression = parseContext.str.str();
                  std::string                  cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
                  cubeplparser::CubePL1Driver* driver         = new cubeplparser::CubePL1Driver( parseContext.cube ); // create driver for this cube
                  std::string nested_error;
                  if (! driver->test( cubepl_program, nested_error ))
                  {
                    parseContext.syntax_ok = false;
                  }
                  delete driver;
                  }
                  parseContext.syntax_ok &= true;
                }
            ;  

flex_aggr_minus :  KEYWORD_METRIC_FLEX_AGGR_MINUS INIT_METRIC_NAME  GhostMetricDefinition
                {
                if (!parseContext.test_modus)
                {
                  std::string expression = parseContext.str.str();
                  parseContext.str.str("");
                  std::string uniq_name = parseContext.name_of_metric;                 
                  Metric * _met = parseContext.cube->get_met(uniq_name);

                    if (_met == NULL)
                    {
                        cout << " Metric with uniq name " << uniq_name << " doesn't  exists yet. Cannot assign CubePL initialization expression. Skip." << endl;
                    }else 
                    {
                        _met->set_aggr_minus_expression( expression );
                    }
                  }else
                  {  
                  std::string expression = parseContext.str.str();
                  std::string                  cubepl_program = string( "<cubepl>" ) + expression + string( "</cubepl>" );
                  cubeplparser::CubePL1Driver* driver         = new cubeplparser::CubePL1Driver( parseContext.cube ); // create driver for this cube
                  std::string nested_error;
                  if (! driver->test( cubepl_program, nested_error ))
                  {
                    parseContext.syntax_ok = false;
                  }
                  delete driver;
                  }
                  parseContext.syntax_ok &= true;
                }
            ;  

		    
		    
get_variable : get_variable_simple 
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
	    | get_variable_indexed
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
  ;

get_variable_simple: KEYWORD_VAR OPEN_LCALC string_constant CLOSE_LCALC
	    { 
		if (!parseContext.test_modus)
		{
		    parseContext._stack.push( new ConstantEvaluation(0) ); // pushed index 0 if array index is not specified
		}
		parseContext.syntax_ok &= true;
	    };
	    
get_variable_indexed: KEYWORD_VAR OPEN_LCALC string_constant CLOSE_LCALC OPEN_ARRAY_INDEX expression CLOSE_ARRAY_INDEX
	    ;
	    

sizeof_variable : SIZEOF OPEN_EXP string_constant CLOSE_EXP
	    {
        if (!parseContext.test_modus)
        {
            std::string _string = parseContext.string_constants.top();
            parseContext.string_constants.pop();
            SizeOfVariableEvaluation * _sizeof_var_eval = new SizeOfVariableEvaluation(  _string, parseContext.cube->get_cubepl_memory_manager()  );
            parseContext._stack.push( _sizeof_var_eval );
        }
        parseContext.syntax_ok &= true;            
	    };
	    
defined_variable : DEFINED OPEN_EXP string_constant CLOSE_EXP
	    {
        if (!parseContext.test_modus)
        {
            std::string _string = parseContext.string_constants.top();
            parseContext.string_constants.pop();
            DefinedVariableEvaluation * _sizeof_var_eval = new DefinedVariableEvaluation(  _string, parseContext.cube->get_cubepl_memory_manager()  );
            parseContext._stack.push( _sizeof_var_eval );
        }
	    };
local_variable : LOCAL_VAR OPEN_EXP string_constant CLOSE_EXP
        {
        if (!parseContext.test_modus)
        {        
            std::string _string = parseContext.string_constants.top();
           parseContext.cube->get_cubepl_memory_manager()->register_variable( _string , CUBEPL_VARIABLE);
        }
        parseContext.syntax_ok &= true;              
        };
global_variable : GLOBAL_VAR OPEN_EXP string_constant CLOSE_EXP
        {
        if (!parseContext.test_modus)
        {        
            std::string _string = parseContext.string_constants.top();
            parseContext.cube->get_cubepl_memory_manager()->register_variable( _string , CUBEPL_GLOBAL_VARIABLE);
        }
        parseContext.syntax_ok &= true;              
        };        
	    
string_constant: STRING_CONSTANT 
	{
	    if (!parseContext.test_modus)
	    {  
		parseContext.string_constants.push(parseContext.value);
		parseContext.value = "";
	    }
	    parseContext.syntax_ok &= true; 
	};

%% /*** Additional Code ***/


void cubeplparser::CubePL1Parser::error(const CubePL1Parser::location_type& l,
				  const std::string& m)
{

    CubePL1Parser::location_type _l = l;


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




