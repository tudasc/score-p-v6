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
#include <iostream>
    
#include "ReMapParser.hh"
#include "ReMapScanner.h"

typedef remapparser::ReMapParser::token token;
typedef remapparser::ReMapParser::token_type token_type;

#define ECHO do {} while (0)

#define yyterminate() return token::END

/* This disables inclusion of unistd.h, which is not available under Visual C++
 * on Win32. The C++ scanner uses STL streams instead. */
#define YY_NO_UNISTD_H

using namespace std;
%}

/*** Flex Declarations and Options ***/

/* enable c++ scanner class generation */
%option c++

/* change the name of the scanner class. results in "ReMapFlexLexer" */
/* %option prefix="" */

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


%x attribute_name 
%x eq 
%x cubepl_eq 
%x right_quota 
%x quoted_string 
%x quoted_bool
%x quoted_cubepl_bool
%x quoted_cubepl_aggr
%x quoted_int 
%x tag 
%x stop
%x string_content
%x general_content
%x cdata
%x real_content
%x long_content
%x scan_error
%x cubepl_expression
%x cubepl_attribute_name
%x cubepl_expression_type
%x ending_cubepl
%x start_ending_cubepl
%x comment

%% /*** Regular Expressions Part ***/



 /* code at the beginning of yylex() */
%{
    // reset location
    yylloc->step();
%}


<INITIAL,attribute_name,eq,right_quota,tag,real_content,long_content>(\n)+ {
                             	yylloc->lines(yyleng); yylloc->step(); }
<INITIAL,attribute_name,eq,right_quota,tag,real_content,long_content>[ \t]+ {
                             	yylloc->step(); }
<attribute_name>"/>"        	{BEGIN(tag); 
                             	return remapparser::ReMapParser::token::CLOSETAG_RIGHT;}

<attribute_name>">"         	{
				    BEGIN(tag); 
				    return remapparser::ReMapParser::token::OPENTAG_RIGHT;
				}
<cubepl_attribute_name>">"        {
				    BEGIN(cubepl_expression); 
				    return remapparser::ReMapParser::token::OPENTAG_RIGHT;
				}
				
<tag>"<!--"			{
				    BEGIN(comment);
				     yylloc->step();
				}
<comment>"-->"			{
				    BEGIN(tag);
				     yylloc->step();
				}
<comment>.			{ 
				    yylloc->step();
				}

<tag>"<metric" 			{BEGIN(attribute_name); 
                                return remapparser::ReMapParser::token::METRIC_OPEN;}
<tag>"</metric>" 		{BEGIN(tag); 
                        return remapparser::ReMapParser::token::METRIC_CLOSE;
                        }
                        
<tag>"<cubepl"	 { BEGIN(cubepl_attribute_name);
			parseContext->str.str("");
                        return remapparser::ReMapParser::token::EXPRESSION_OPEN;
                        }                       

                        

<ending_cubepl>"cubepl>"	 {	BEGIN(tag);
	    	                    return remapparser::ReMapParser::token::EXPRESSION_CLOSE;
    		                }                       

<start_ending_cubepl>[^/]	 { BEGIN(cubepl_expression);
				  parseContext->str << "<" << yytext;
    		                }      		                
<start_ending_cubepl>"/"	 {
				  BEGIN(ending_cubepl);
    		                }  		                
    		                

    		                   		                
<cubepl_expression>"<"	 	{
				  BEGIN(start_ending_cubepl);
    		                }     		                
    		                
    		                
<cubepl_expression>[^<]+     {
				parseContext->str << yytext;
			    }
    		                

<tag>"<cubeplinit>"  { BEGIN(cubepl_expression);
                        parseContext->str.str("");
                        return remapparser::ReMapParser::token::EXPRESSION_INIT_OPEN;
                        }                       


<ending_cubepl>"cubeplinit>"   {  BEGIN(tag);
                                return remapparser::ReMapParser::token::EXPRESSION_INIT_CLOSE;
                            }    
                            
  <tag>"<cubeplaggr"	 { BEGIN(cubepl_attribute_name);
			parseContext->str.str("");
                        return remapparser::ReMapParser::token::EXPRESSION_AGGR_OPEN;
                        }                      


<ending_cubepl>"cubeplaggr>"	 {	BEGIN(tag);
	    	                    return remapparser::ReMapParser::token::EXPRESSION_AGGR_CLOSE;
    		                }                            
                            
                            
                            

<INITIAL>"<metrics" 	       	{BEGIN(attribute_name); 
				return remapparser::ReMapParser::token::METRICS_OPEN;
				}
<tag>"</metrics>" 		    {BEGIN(tag); return remapparser::ReMapParser::token::METRICS_CLOSE;}

<tag>"<disp_name>" 		      {BEGIN(string_content);
			     	            parseContext->str.str("");
                             	return remapparser::ReMapParser::token::DISP_NAME_OPEN;}
<string_content>"</disp_name>" 	{BEGIN(tag);
                             	return remapparser::ReMapParser::token::DISP_NAME_CLOSE;}

<tag>"<uniq_name>" 		{BEGIN(string_content);
			     	parseContext->str.str("");
                             	return remapparser::ReMapParser::token::UNIQ_NAME_OPEN;}
<string_content>"</uniq_name>" 	{BEGIN(tag);
                             	return remapparser::ReMapParser::token::UNIQ_NAME_CLOSE;}
<tag>"<dtype>" 			{BEGIN(string_content);
			     	parseContext->str.str("");
                             	return remapparser::ReMapParser::token::DTYPE_OPEN;}
<string_content>"</dtype>" 	{BEGIN(tag);
                             	return remapparser::ReMapParser::token::DTYPE_CLOSE;}
<tag>"<uom>" 			{BEGIN(string_content);
			     	parseContext->str.str("");
                             	return remapparser::ReMapParser::token::UOM_OPEN;}
<string_content>"</uom>" 	{BEGIN(tag);
                             	return remapparser::ReMapParser::token::UOM_CLOSE;}
<tag>"<val>" 			{BEGIN(string_content);
			     	parseContext->str.str("");
                             	return remapparser::ReMapParser::token::VAL_OPEN;}
<string_content>"</val>" 	{BEGIN(tag);
                             	return remapparser::ReMapParser::token::VAL_CLOSE;}
<tag>"<url>" 			{BEGIN(string_content);
			     	parseContext->str.str("");
                             	return remapparser::ReMapParser::token::URL_OPEN;}
<string_content>"</url>" 	{BEGIN(tag);
                             	return remapparser::ReMapParser::token::URL_CLOSE;}
<tag>"<descr>" 			{BEGIN(string_content);
			     	parseContext->str.str("");
                             	return remapparser::ReMapParser::token::DESCR_OPEN;}
<string_content>"</descr>" 	{BEGIN(tag);
                             	return remapparser::ReMapParser::token::DESCR_CLOSE;}

<tag>"<name>" 			{BEGIN(string_content);
			     	parseContext->str.str("");
                             	return remapparser::ReMapParser::token::NAME_OPEN;}
<string_content>"</name>" 	{BEGIN(tag);
                             	return remapparser::ReMapParser::token::NAME_CLOSE;}

<attribute_name>"title"         {BEGIN(eq); 
                                parseContext->contentType = ReMapParseContext::STRINGCONTENT;
                                return remapparser::ReMapParser::token::ANAME_TITLE;
                                }

<attribute_name>"metricId"  	{BEGIN(eq); 
                             	parseContext->contentType = ReMapParseContext::INTCONTENT;
			     	return remapparser::ReMapParser::token::ANAME_METRICID;}

<attribute_name>"type"           {BEGIN(eq); 
				    parseContext->contentType = ReMapParseContext::STRINGCONTENT;
				    return remapparser::ReMapParser::token::ANAME_METRIC_TYPE;
                                }
 <attribute_name>"viztype"       {
				BEGIN(eq); 
				    parseContext->contentType = ReMapParseContext::STRINGCONTENT;
				    return remapparser::ReMapParser::token::ANAME_METRIC_VIZ_TYPE;
                                }
<attribute_name>"convertible"       {
				    BEGIN(eq); 
				    parseContext->contentType = ReMapParseContext::BOOLCONTENT;
				    return remapparser::ReMapParser::token::ANAME_METRIC_CONVERTIBLE;
                                }     
<attribute_name>"cacheable"       {
				    BEGIN(eq); 
				    parseContext->contentType = ReMapParseContext::BOOLCONTENT;
				    return remapparser::ReMapParser::token::ANAME_METRIC_CACHEABLE;
                                }                                                    
                                
<cubepl_attribute_name>"rowwise"           {BEGIN(cubepl_eq); 
				    parseContext->contentType = ReMapParseContext::BOOLCONTENT;
				    return remapparser::ReMapParser::token::ACUBEPL_ROWWISE;
                                }
<cubepl_attribute_name>"cubeplaggrtype"  {BEGIN(cubepl_eq); 
				    parseContext->contentType = ReMapParseContext::CUBEPLAGGREGATIONCONTENT;
				    return remapparser::ReMapParser::token::ACUBEPL_AGGR_ATTRIBUTE;
                                }       
<INITIAL>"<doc>" 	       	{BEGIN(tag); 
				  return remapparser::ReMapParser::token::DOC_OPEN;
				}
<tag>"</doc>" 		       	{
				    BEGIN(INITIAL); 
				    return remapparser::ReMapParser::token::DOC_CLOSE;
				}
<tag>"<mirrors>" 	       	{
				    return remapparser::ReMapParser::token::MIRRORS_OPEN;
				}
<tag>"</mirrors>" 	       	{
				    BEGIN(tag); 
				    return remapparser::ReMapParser::token::MIRRORS_CLOSE;
				}
<tag>"<murl>" 	               	{
				    BEGIN(string_content);
				    parseContext->str.str("");
				    return remapparser::ReMapParser::token::MURL_OPEN;
				}
<string_content>"</murl>"      	{
				    BEGIN(tag);
				    return remapparser::ReMapParser::token::MURL_CLOSE;
				}
<eq>"=\""                     	{if (parseContext->contentType==ReMapParseContext::STRINGCONTENT){ 
					BEGIN(quoted_string);
                             		parseContext->str.str("");
				} else if (parseContext->contentType==ReMapParseContext::INTCONTENT){
					BEGIN(quoted_int);
					parseContext->str.str("");
			     	} else BEGIN(quoted_bool); 
					parseContext->str.str("");
				}
<cubepl_eq>"="                {
					 if (parseContext->contentType==ReMapParseContext::CUBEPLAGGREGATIONCONTENT)
				    { 
					    BEGIN(quoted_cubepl_aggr);
					    parseContext->str.str("");
				    } 
				    else BEGIN(quoted_cubepl_bool);
				}				
<right_quota>"\""               {BEGIN(attribute_name); }
<quoted_string>[^\"\n]+       	{parseContext->str << yytext;}
<quoted_string>[\n]+       	{parseContext->str << " ";}
<quoted_string>"\""       	{BEGIN(attribute_name); 
                             	return remapparser::ReMapParser::token::ATTRIBUTE_VALUE;}
<quoted_int>[^\" \t\n]+  	{
			        char* remain;
				parseContext->longAttribute = strtol(yytext,&remain,10);
				bool ok = (*remain=='\0');
				if (!ok) {
				  BEGIN(scan_error);
				  *yyout << "unexpected string: \"" << yytext << "\"";  
				} else {
				  BEGIN(right_quota);
                             	  return remapparser::ReMapParser::token::ATTRIBUTE_VALUE;}
				}
<quoted_bool>[fF][aA][lL][sS][eE]\" {
				BEGIN(attribute_name); 
                             	return remapparser::ReMapParser::token::FFALSE;}
<quoted_bool>[tT][rR][uU][eE]\" {
				BEGIN(attribute_name); 
                             	return remapparser::ReMapParser::token::TTRUE;}

<quoted_cubepl_bool>[fF][aA][lL][sS][eE] {
				BEGIN(cubepl_attribute_name); 
                             	return remapparser::ReMapParser::token::FFALSE;}
<quoted_cubepl_bool>[tT][rR][uU][eE] {
				BEGIN(cubepl_attribute_name); 
                             	return remapparser::ReMapParser::token::TTRUE;}                      	
<quoted_cubepl_aggr>[pP][lL][uU][sS] {
				BEGIN(cubepl_attribute_name); 
                             	return remapparser::ReMapParser::token::ACUBEPL_AGGR_ATTR_PLUS;}
<quoted_cubepl_aggr>[mM][iI][nN][uU][sS] {
				BEGIN(cubepl_attribute_name); 
                             	return remapparser::ReMapParser::token::ACUBEPL_AGGR_ATTR_MINUS;}                            	
<quoted_cubepl_aggr>[aA][gG][gG][rR] {
				BEGIN(cubepl_attribute_name); 
                             	return remapparser::ReMapParser::token::ACUBEPL_AGGR_ATTR_AGGR;}                            	
                             	
                             	
                             	
                             	
<real_content>[^< \t\n]+	{
				  if (!parseContext->ignoreMetric){
				    char* remain;
				    double value = strtod(yytext,&remain);
				    if (*remain!='\0'){
	                     		*yyout << "unexpected string \"" << yytext << "\" for double" << std::endl;
                             		BEGIN(scan_error);
				    } else {
                             	    	parseContext->realValues.push_back(value); 
				    }
				  }
				}
<long_content>[^< \t\n]+ 	{
				  char* remain;
				  long value = strtol(yytext,&remain,10);
				  if (*remain!='\0'){
	                     		*yyout << "unexpected string \"" << yytext << "\" for long" << std::endl;
                             		BEGIN(scan_error);
				  } else {
                             		parseContext->longValues.push_back(value); 
				  }
				}

<general_content>[^<\t\n]+    {
                  string value = yytext;
                  parseContext->generalValues.push_back(value); 
                }

<string_content>[^<gla\n]+     	{parseContext->str << yytext; }
<string_content>"g"    	        {parseContext->str << yytext; }
<string_content>"l"    	        {parseContext->str << yytext; }
<string_content>"a"    	        {parseContext->str << yytext; }
<string_content>(\n)+       	{parseContext->str << " "; }
<string_content>"<![CDATA[" 	{BEGIN(cdata); }
<cdata>[^\]]+               	{parseContext->str << yytext; }
<cdata>"\]\]>"              	{BEGIN(string_content); }
<cdata>"\]"                 	{parseContext->str << yytext; }
<INITIAL,attribute_name,eq,right_quota,quoted_string,quoted_bool,quoted_int,tag,string_content,cdata,real_content,long_content>. {
                             	*yyout << "unexpected character " << yytext << std::endl;
                             	BEGIN(scan_error);}
<scan_error>[^\n]* 		{*yyout << "Before: " << yytext << std::endl;
                   		return remapparser::ReMapParser::token::ERROR;}

<stop>.                { 
                            yyterminate(); 
                      }

%% /*** Additional Code ***/

namespace remapparser {

ReMapScanner::ReMapScanner(std::istream* in,
		           std::ostream* out,
			   ReMapParseContext* parseContext)
  : yyFlexLexer(in, out),
    parseContext(parseContext)
{
}

ReMapScanner::~ReMapScanner()
{
}

}

/* This implementation of ReMapFlexLexer::yylex() is required to fill the
 * vtable of the class ReMapFlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the Cube4Scanner class instead. */

#ifdef yylex
#undef yylex
#endif

int yyFlexLexer::yylex()
{
    std::cerr << "in FlexLexer::yylex() !" << std::endl;
    return 0;
}
