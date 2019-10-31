/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2019                                                **
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



%{ /*** C/C++ Declarations ***/

#include <string>
#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"
#include "CubePL1Parser.h"
#include "CubePL1Scanner.h"
        
#define YYSTYPE std::string
extern YYSTYPE yylval;

typedef cubeplparser::CubePL1Parser::token token;
typedef cubeplparser::CubePL1Parser::token_type token_type;

#define yyterminate() return token::END

#define ECHO do {} while (0)

/* This disables inclusion of unistd.h, which is not available under Visual C++
 * on Win32. The C++ scanner uses STL streams instead. */
#define YY_NO_UNISTD_H

using namespace std;
using namespace cubeplparser;
%}

/*** Flex Declarations and Options ***/

/* enable c++ scanner class generation */
%option c++

/* change the name of the scanner class. results in "Cube4FlexLexer" */
%option prefix="CubePL1Parser"

/* the manual says "somewhat more optimized" */
%option batch

/* enable scanner to generate debug output. */
%option debug

/* no support for include files is planned */
%option noyywrap 

/* unput is not used */
/*%option nounput */

/* Result is never interactive */
%option never-interactive

/* The following paragraph suffices to track locations accurately. Each time
 * yylex is invoked, the begin position is moved onto the end position. */
%{
#define YY_USER_ACTION  yylloc->columns(yyleng);
%}

%x functionname
%x variable_par
%x variablename
%x sizeofname
%x size_of_variablename
%x regexp_string_start
%x regexp_string
%x quoted_string
%x opmetricname
%x metricname
%x callmetricname
%x metricarguments 
%x callmetricarguments 
%x postgmetricname
%x pregmetricname
%x init_metric_body
%x initmetricname
%x gm_arguments
%x gm_cubepl
%x ending_gm_cubepl
%x finish_gm_cubepl
%x expression 
%x statement
%x stop 
%x comment

%% /*** Regular Expressions Part ***/




<INITIAL>"<cubepl>"		{
				    BEGIN(expression);
				    return cubeplparser::CubePL1Parser::token::START_DOCUMENT;
				}

<expression>"</cubepl>"		{
				    BEGIN(stop);
				    return cubeplparser::CubePL1Parser::token::END_DOCUMENT;
				}
<INITIAL>[ \t\n]+ {    yylloc->step();   }
<statement,expression,variablename,variable_par>[ \t\n]+ {    yylloc->step();   }


<expression>"//" 		{
				    BEGIN(comment);
				}

<comment>[^\n]*			{}				
<comment>"\n"			{
				    BEGIN(expression);
				}				
				
				
<expression>"("			{
				    return cubeplparser::CubePL1Parser::token::OPEN_EXP;
				}

<expression>")"   		{	
				    return cubeplparser::CubePL1Parser::token::CLOSE_EXP;
                             	}



<expression>"{"   		{
				BEGIN( expression );
                             	return cubeplparser::CubePL1Parser::token::OPEN_LCALC;
                             	}
<expression>"}"		 {

				BEGIN(expression);
                             	return cubeplparser::CubePL1Parser::token::CLOSE_LCALC;
                             	}
<variable_par>"{"   		{
				BEGIN(variablename);
                             	return cubeplparser::CubePL1Parser::token::OPEN_LCALC;
                             	}
<variablename>"}"		 {

				BEGIN(expression);
                             	return cubeplparser::CubePL1Parser::token::CLOSE_LCALC;
                             	}
<expression>"["			{
				  return cubeplparser::CubePL1Parser::token::OPEN_ARRAY_INDEX;
				}                             	
<expression>"]"			{
				  return cubeplparser::CubePL1Parser::token::CLOSE_ARRAY_INDEX;
				}                               	
<expression>";" 		{
				    return cubeplparser::CubePL1Parser::token::STATEMENT_SEP;
                             	}

<expression>"$"			{
				    BEGIN(variable_par);
				    return cubeplparser::CubePL1Parser::token::KEYWORD_VAR;
                             	}
<expression>"if"		{
				    return cubeplparser::CubePL1Parser::token::KEYWORD_IF;
                             	}
<expression>"else"				{
				    return cubeplparser::CubePL1Parser::token::KEYWORD_ELSE;
                             	}
<expression>"elseif"			{
				    return cubeplparser::CubePL1Parser::token::KEYWORD_ELSEIF;
                             	}
<expression>"while"			{
				    return cubeplparser::CubePL1Parser::token::KEYWORD_WHILE;
                             	}

<expression>"return"		{
				    return cubeplparser::CubePL1Parser::token::RETURN_EXP;
				}

<expression>"="			{
				return cubeplparser::CubePL1Parser::token::KEYWORD_ASSIGN;
				}  
<expression>"=="		{
				return cubeplparser::CubePL1Parser::token::KEYWORD_EQUAL;
				}  
<expression>"eq"		{
				return cubeplparser::CubePL1Parser::token::KEYWORD_STRING_EQUAL;
				}  
<expression>"seq"		{
				return cubeplparser::CubePL1Parser::token::KEYWORD_STRING_SEMI_EQUAL;
				}  
<expression>"!="		{
				return cubeplparser::CubePL1Parser::token::KEYWORD_NOT_EQUAL;
				}  
<expression>">"			{
				return cubeplparser::CubePL1Parser::token::KEYWORD_BIGGER;
				}  
<expression>">="		{
				return cubeplparser::CubePL1Parser::token::KEYWORD_HALFBIGGER;
				}  
<expression>"<"			{
				return cubeplparser::CubePL1Parser::token::KEYWORD_SMALLER;
				}  
<expression>"<="		{
				return cubeplparser::CubePL1Parser::token::KEYWORD_HALFSMALLER;
				}  
<expression>"not"		{
				return cubeplparser::CubePL1Parser::token::KEYWORD_NOT;
				}  
<expression>"lowercase"		{
				return cubeplparser::CubePL1Parser::token::KEYWORD_LOWERCASE;
				} 
<expression>"uppercase"		{
				return cubeplparser::CubePL1Parser::token::KEYWORD_UPPERCASE;
				} 
<expression>"env"		{
				return cubeplparser::CubePL1Parser::token::KEYWORD_ENV;
				} 
<expression>"and"		{
				return cubeplparser::CubePL1Parser::token::KEYWORD_AND;
				}  
<expression>"or"		{
				return cubeplparser::CubePL1Parser::token::KEYWORD_OR;
				}  
<expression>"true"		{
				return cubeplparser::CubePL1Parser::token::KEYWORD_TRUE;
				}  
<expression>"false"		{
				return cubeplparser::CubePL1Parser::token::KEYWORD_FALSE;
				}  

<expression>"+"				{
				return cubeplparser::CubePL1Parser::token::OP_PLUS;
				}                           	

<expression>"-"				{
				return cubeplparser::CubePL1Parser::token::OP_MINUS;
				}                           	

<expression>"*"			{	
				return cubeplparser::CubePL1Parser::token::OP_MULT;
				}                           	

<expression>"/"				{
				return cubeplparser::CubePL1Parser::token::OP_DIVIDE;
				}                           	

<expression>","			{
				 if (parseContext->callparse )
				 {
				     BEGIN(callmetricarguments );
				 }
				return cubeplparser::CubePL1Parser::token::COMMA;
				}                           	


<expression>"^"			{
				return cubeplparser::CubePL1Parser::token::OP_POWER;
				}                           	
<expression>"sizeof"		{
				BEGIN(sizeofname);
				return cubeplparser::CubePL1Parser::token::SIZEOF;
				}

<sizeofname>"("			{
				BEGIN(size_of_variablename);
				return cubeplparser::CubePL1Parser::token::OPEN_EXP;
				}				
<sizeofname>[^(]		{ yyterminate(); }

<size_of_variablename>[a-zA-Z][1234567890a-zA-Z:_\-#]*		{
				    BEGIN(size_of_variablename);
				    parseContext->value = yytext;                
				    return cubeplparser::CubePL1Parser::token::STRING_CONSTANT;
				}
<size_of_variablename>")"	{ 
				BEGIN(expression);
				return cubeplparser::CubePL1Parser::token::CLOSE_EXP;
				}

<expression>"defined"		{
				BEGIN(sizeofname);
				return cubeplparser::CubePL1Parser::token::DEFINED;
				}				
				
<expression>"local"       {
                BEGIN(sizeofname);
                return cubeplparser::CubePL1Parser::token::LOCAL_VAR;
                }               
<expression>"global"       {
                BEGIN(sizeofname);
                return cubeplparser::CubePL1Parser::token::GLOBAL_VAR;
                }               
                				
				
<expression>"arg1"		{
				return cubeplparser::CubePL1Parser::token::ARGUMENT1;
				}
<expression>"arg2"		{
				return cubeplparser::CubePL1Parser::token::ARGUMENT2;
				}
<expression>"sqrt"		{
				BEGIN(functionname);
				return cubeplparser::CubePL1Parser::token::FUN_SQRT;
				}
<expression>"sin"		{
				BEGIN(functionname);
				return cubeplparser::CubePL1Parser::token::FUN_SIN;
				}
<expression>"asin"		{
				BEGIN(functionname);
				return cubeplparser::CubePL1Parser::token::FUN_ASIN;
				}
<expression>"cos"		{
				BEGIN(functionname);
				return cubeplparser::CubePL1Parser::token::FUN_COS;
				}
<expression>"acos"		{
				BEGIN(functionname);
				return cubeplparser::CubePL1Parser::token::FUN_ACOS;
				}
<expression>"exp"		{
				BEGIN(functionname);
				return cubeplparser::CubePL1Parser::token::FUN_EXP;
				}
<expression>"log"		{
				BEGIN(functionname);
				return cubeplparser::CubePL1Parser::token::FUN_LOG;
				}
<expression>"random"		{
				BEGIN(functionname);
				return cubeplparser::CubePL1Parser::token::FUN_RANDOM;
				}
<expression>"tan"		{
				BEGIN(functionname);
				return cubeplparser::CubePL1Parser::token::FUN_TAN;
				}
<expression>"atan"		{
				BEGIN(functionname);
				return cubeplparser::CubePL1Parser::token::FUN_ATAN;
				}
<expression>"abs"		{
				BEGIN(functionname);
				return cubeplparser::CubePL1Parser::token::FUN_ABS;
				}
<expression>"sgn"		{
				BEGIN(functionname);
				return cubeplparser::CubePL1Parser::token::FUN_SGN;
				}
<expression>"pos"		{
				BEGIN(functionname);
				return cubeplparser::CubePL1Parser::token::FUN_POS;
				}
<expression>"neg"		{
				BEGIN(functionname);
				return cubeplparser::CubePL1Parser::token::FUN_NEG;
				}
<expression>"floor"		{
				BEGIN(functionname);
				return cubeplparser::CubePL1Parser::token::FUN_FLOOR;
				}
<expression>"ceil"		{
				BEGIN(functionname);
				return cubeplparser::CubePL1Parser::token::FUN_CEIL;
				}
<expression>"min"		{
				BEGIN(functionname);
				return cubeplparser::CubePL1Parser::token::FUN_MIN;
				}
<expression>"max"		{
				BEGIN(functionname);
				return cubeplparser::CubePL1Parser::token::FUN_MAX;
				}
<expression>"|"		{
				return cubeplparser::CubePL1Parser::token::ABS_MARK;
				}

<functionname>"("		{
					BEGIN(expression);
					return cubeplparser::CubePL1Parser::token::OPEN_EXP;
				}

<functionname>[^(]		{ yyterminate(); }

<expression>"metric::fixed::"		{
				 BEGIN(metricname);
				 return cubeplparser::CubePL1Parser::token::KEYWORD_FIXED_METRIC;
				}
<expression>"metric::context::"		{
				 BEGIN(metricname);
				 return cubeplparser::CubePL1Parser::token::KEYWORD_METRIC;
				}
<expression>"metric::"		{
				 BEGIN(metricname);
				 return cubeplparser::CubePL1Parser::token::KEYWORD_METRIC;
				}

<expression>"metric::call::"	{
				 BEGIN(callmetricname);
				 return cubeplparser::CubePL1Parser::token::KEYWORD_METRIC_CALL;
				}
				 
<expression>"cube::metric::postderived::"		{
				 BEGIN(postgmetricname);
				 return cubeplparser::CubePL1Parser::token::KEYWORD_GHOST_POSTMETRIC;
				}
<expression>"cube::metric::prederived::"		{
				 BEGIN(pregmetricname);
				 return cubeplparser::CubePL1Parser::token::KEYWORD_GHOST_PREMETRIC;
				}						
<expression>"cube::init::metric::"        {
                 BEGIN(initmetricname);
                 return cubeplparser::CubePL1Parser::token::KEYWORD_METRIC_INIT;
                }                       

<expression>"cube::metric::plus::"        {
                 BEGIN(initmetricname);
                 return cubeplparser::CubePL1Parser::token::KEYWORD_METRIC_FLEX_AGGR_PLUS;
                }  
                
<expression>"cube::metric::minus::"        {
                 BEGIN(initmetricname);
                 return cubeplparser::CubePL1Parser::token::KEYWORD_METRIC_FLEX_AGGR_MINUS;
                }                       
                
<expression>"cube::metric::set::"        {
                 BEGIN(opmetricname);
                 return cubeplparser::CubePL1Parser::token::KEYWORD_METRIC_SET;
                }                      
<expression>"cube::metric::get::"        {
                 BEGIN(opmetricname);
                 return cubeplparser::CubePL1Parser::token::KEYWORD_METRIC_GET;
                }                
                
<postgmetricname>[a-zA-Z0-9_:=]+		{
				    BEGIN(gm_arguments);
				    parseContext->name_of_metric = yytext; 
				    return cubeplparser::CubePL1Parser::token::METRIC_NAME;
				}
<pregmetricname>[a-zA-Z0-9_:=]+		{
				    BEGIN(gm_arguments);
				    parseContext->name_of_metric = yytext; 
				    return cubeplparser::CubePL1Parser::token::METRIC_NAME;
				}	
<opmetricname>[a-zA-Z0-9_:=]+       {
                    BEGIN(functionname);
                    parseContext->name_of_metric = yytext; 
                    return cubeplparser::CubePL1Parser::token::METRIC_NAME;
                }	
                
                
                
<init_metric_body>"<<"      {
                    BEGIN(gm_cubepl);
                    parseContext->str.str("");
                    return cubeplparser::CubePL1Parser::token::OPEN_GM_CUBEPL;

                }                
<gm_arguments>"("		{
				    return cubeplparser::CubePL1Parser::token::OPEN_EXP;
				}
<gm_arguments>")"		{
				    return cubeplparser::CubePL1Parser::token::CLOSE_EXP;
				}				
<gm_arguments>"i"		{
				    return cubeplparser::CubePL1Parser::token::INCL_MODIFICATOR;
					}
<gm_arguments>"e"		{
				    return cubeplparser::CubePL1Parser::token::EXCL_MODIFICATOR;
					}				
									
<gm_arguments>"<<"		{
				    BEGIN(gm_cubepl);
				    parseContext->str.str("");
				    return cubeplparser::CubePL1Parser::token::OPEN_GM_CUBEPL;

				}
				
<metricname>[a-zA-Z0-9_:=]+	{
				    BEGIN(metricarguments);
				    parseContext->name_of_metric = yytext; 
				    return cubeplparser::CubePL1Parser::token::METRIC_NAME;
				}
<callmetricname>[a-zA-Z0-9_:=]+	{
				    BEGIN(callmetricarguments);
				    parseContext->name_of_metric = yytext; 
				    return cubeplparser::CubePL1Parser::token::METRIC_NAME;
				}
<gm_cubepl>[^>]+		{
				    parseContext->str <<yytext; 
				}
<gm_cubepl>">"			{
				    BEGIN(ending_gm_cubepl);
				}

<ending_gm_cubepl>[^>]	 { 
				    BEGIN(gm_cubepl);
				    parseContext->str << ">" << yytext;
    		                }      		                
<ending_gm_cubepl>">"	 	{ 
				    BEGIN(expression);
				    return cubeplparser::CubePL1Parser::token::STRING_TEXT;
				} 		                
		
				
				
				
<metricarguments>"("		{
				    return cubeplparser::CubePL1Parser::token::OPEN_EXP;
				}
<metricarguments>")"		{
				    BEGIN(expression);
				    return cubeplparser::CubePL1Parser::token::CLOSE_EXP;
				}
<metricarguments>","		{
				    return cubeplparser::CubePL1Parser::token::COMMA;
				}
<metricarguments>"*"		{
				    return cubeplparser::CubePL1Parser::token::SAME_MODIFICATOR;
				}

<metricarguments>"i"		{
				    return cubeplparser::CubePL1Parser::token::INCL_MODIFICATOR;
				}
<metricarguments>"e"		{
				    return cubeplparser::CubePL1Parser::token::EXCL_MODIFICATOR;
				}
				
				
				
<callmetricarguments>"("	{   BEGIN(expression);
				    parseContext->callparse = true;
				    return cubeplparser::CubePL1Parser::token::OPEN_EXP;
				}
<callmetricarguments>")"	{   BEGIN(expression);
				    parseContext->callparse = false;
				    return cubeplparser::CubePL1Parser::token::CLOSE_EXP;
				}				
<callmetricarguments>","	{
				    
				    BEGIN(expression);
				    parseContext->callparse = true;
				    return cubeplparser::CubePL1Parser::token::COMMA;
				}				

<callmetricarguments>"i"	{  
				    return cubeplparser::CubePL1Parser::token::INCL_MODIFICATOR;
				}
<callmetricarguments>"e"	{  
				    return cubeplparser::CubePL1Parser::token::EXCL_MODIFICATOR;
				}	
					

<expression>"\""		{
				    BEGIN(quoted_string);
				}
<quoted_string>"\\\""		{
				    parseContext->str  << "\"";
				    yylloc->step(); 
				}
<quoted_string>"\\t"		{
				    parseContext->str  << "\t";
				    yylloc->step(); 
				}
<quoted_string>"\\n"		{
				    parseContext->str  << "\n";
				    yylloc->step(); 
				}
<quoted_string>"\""		{
				    BEGIN(expression);
				    return cubeplparser::CubePL1Parser::token::QUOTED_STRING;
				}
<quoted_string>[^"\\]+		{
				    parseContext->str  << yytext;  
				}
<quoted_string>\\		{
				    yylloc->step(); 
				}   



<expression>"=~"		{
				    BEGIN(regexp_string_start);
				    return cubeplparser::CubePL1Parser::token::KEYWORD_REGEXP;
				}
<regexp_string_start>"/"	{ 
				    BEGIN(regexp_string);
				    yylloc->step(); 
				}
<regexp_string>"/"		{
				    BEGIN(expression);
				    return cubeplparser::CubePL1Parser::token::REGEXP_STRING;
				}
<regexp_string>"\\/"		{
				     parseContext->str  << "/";
				    yylloc->step(); 
				}   
<regexp_string>[^/]+		{
				    
				    parseContext->str  << yytext;  
				}





<expression>[1234567890\.]+		{
    
		                      parseContext->value = yytext;                
		                      return cubeplparser::CubePL1Parser::token::CONSTANT;
				}
<variablename>[a-zA-Z][1234567890a-zA-Z:_\-#]*		{
		                      parseContext->value = yytext;                
		                      return cubeplparser::CubePL1Parser::token::STRING_CONSTANT;
				    }

    /*** <expression>[a-zA-Z]+ { yyterminate(); }  ***/

<metricarguments>[^\(\)\,\*\ie] { yyterminate(); }

<stop>.                {
                            yyterminate();
                      }  

%% /*** Additional Code ***/

namespace cubeplparser {

CubePL1Scanner::CubePL1Scanner(std::istream* in,
		std::ostream* out,
		CubePL1ParseContext* parseContext)
  : CubePL1ParserFlexLexer(in, out),
    parseContext(parseContext)
{
}
  
CubePL1Scanner::~CubePL1Scanner()
{
}

}

/* This implementation of Cube4FlexLexer::yylex() is required to fill the
 * vtable of the class Cube4FlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the Cube4Scanner class instead. */

#ifdef yylex
#undef yylex
#endif

int CubePL1ParserFlexLexer::yylex()
{
    std::cerr << "in FlexLexer::yylex() !" << std::endl;
    return 0;
}
