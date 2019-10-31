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
#include "Cube4Parser.h"
#include "Cube4Scanner.h"
;

typedef cubeparser::Cube4Parser::token token;
typedef cubeparser::Cube4Parser::token_type token_type;

#define yyterminate() return token::END

#define ECHO do {} while (0)

/* This disables inclusion of unistd.h, which is not available under Visual C++
 * on Win32. The C++ scanner uses STL streams instead. */
#define YY_NO_UNISTD_H

using namespace std;
%}

/*** Flex Declarations and Options ***/

/* enable c++ scanner class generation */
%option c++

/* change the name of the scanner class. results in "Cube4FlexLexer" */
%option prefix="Cube4"

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
#define YY_USER_ACTION  yylloc->columns(yyleng); \
    parseContext->count_symbols += yyleng; \
    cube->get_operation_progress()->progress_step((double)(parseContext->count_symbols) / (double)(stream_in->size()));
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
%x start_ending_cubepl
%x ending_cubepl
%x cubepl_attribute_name
%x cubepl_expression_type
%x notsupportedversion

%% /*** Regular Expressions Part ***/



<INITIAL,attribute_name,eq,right_quota,tag,real_content,long_content>(\n)+ {
                             	yylloc->lines(yyleng); yylloc->step(); 
            }

<attribute_name>"/>"        	{BEGIN(tag); 
                             	return cubeparser::Cube4Parser::token::CLOSETAG_RIGHT;}
<attribute_name>"?>"        	{BEGIN(tag); 
                             	return cubeparser::Cube4Parser::token::XML_CLOSE;}
<attribute_name>">"         	{if (parseContext->realContent) BEGIN(real_content);
                             	else if (parseContext->longContent) BEGIN(long_content);
                             	else if (parseContext->generalContent) BEGIN(general_content);
                                else if (parseContext->stringContent) BEGIN(string_content);
                                else BEGIN(tag); 
                             	return cubeparser::Cube4Parser::token::OPENTAG_RIGHT;}
<cubepl_attribute_name>">"      {
				    BEGIN(cubepl_expression); 
				    return cubeparser::Cube4Parser::token::OPENTAG_RIGHT;
				}                             	
<INITIAL>"<?xml"  		{BEGIN(attribute_name); 
                             	return cubeparser::Cube4Parser::token::XML_OPEN;}
<tag>"<attr" 			{BEGIN(attribute_name); 
                             	return cubeparser::Cube4Parser::token::ATTR_OPEN;}
<tag>"<dim" 			{BEGIN(attribute_name); 
                             	return cubeparser::Cube4Parser::token::DIM_OPEN;}
<tag>"<cube version=\"4.0\">"   {return cubeparser::Cube4Parser::token::CUBE_OPEN4;}
<tag>"<cube version=\"3.0\">"   {return cubeparser::Cube4Parser::token::CUBE_OPEN3;}
<tag>"<cube version=\"4.1\">"   {return cubeparser::Cube4Parser::token::CUBE_OPEN41;}
<tag>"<cube version=\"4.2\">"   {return cubeparser::Cube4Parser::token::CUBE_OPEN42;}
<tag>"<cube version=\"4.3\">"   {return cubeparser::Cube4Parser::token::CUBE_OPEN43;}
<tag>"<cube version=\"4.4\">"   {return cubeparser::Cube4Parser::token::CUBE_OPEN44;}
<tag>"<cube version=\"4.5\">"   {return cubeparser::Cube4Parser::token::CUBE_OPEN45;}
<tag>"<cube version=\"4"        {BEGIN(notsupportedversion); return cubeparser::Cube4Parser::token::CUBE_OPEN;}
<notsupportedversion>[0123456789]+     {BEGIN(tag); parseContext->str.str(""); parseContext->str << "4." << yytext;  return cubeparser::Cube4Parser::token::CUBE_OPEN_NOT_SUPPORTED;}

<tag>"</cube>" 			{
                            BEGIN(stop);
                            return cubeparser::Cube4Parser::token::CUBE_CLOSE;
                        }
<tag>"<metric" 			{BEGIN(attribute_name); 
                                return cubeparser::Cube4Parser::token::METRIC_OPEN;}
<tag>"</metric>" 		{BEGIN(tag); 
                        return cubeparser::Cube4Parser::token::METRIC_CLOSE;
                        }
                        
<tag>"<cubepl"	 { BEGIN(cubepl_attribute_name);
			parseContext->str.str("");
                        return cubeparser::Cube4Parser::token::EXPRESSION_OPEN;
                        }                      


<ending_cubepl>"cubepl>"	 {	BEGIN(tag);
	    	                    return cubeparser::Cube4Parser::token::EXPRESSION_CLOSE;
    		                }                       


<tag>"<cubeplaggr"	 { BEGIN(cubepl_attribute_name);
			parseContext->str.str("");
                        return cubeparser::Cube4Parser::token::EXPRESSION_AGGR_OPEN;
                        }                      


<ending_cubepl>"cubeplaggr>"	 {	BEGIN(tag);
	    	                    return cubeparser::Cube4Parser::token::EXPRESSION_AGGR_CLOSE;
    		                }       
    		                
 <start_ending_cubepl>[^/]	 { BEGIN(cubepl_expression);
				  parseContext->str << "<" << yytext;
    		                } 
<start_ending_cubepl>"/"	{
				  BEGIN(ending_cubepl);
    		                } 
    		                
    		                
<cubepl_expression>"<"	 	{
				  BEGIN(start_ending_cubepl);
    		                }     		                
        		                
<cubepl_expression>[^<]+ {
				parseContext->str << yytext;
			    }		                

<tag>"<cubeplinit>"  { BEGIN(cubepl_expression);
            parseContext->str.str("");
                        return cubeparser::Cube4Parser::token::EXPRESSION_INIT_OPEN;
                        }                       


<ending_cubepl>"cubeplinit>"   {  BEGIN(tag);
                                return cubeparser::Cube4Parser::token::EXPRESSION_INIT_CLOSE;
                            }                       

                        
<tag>"<cnode" 			{BEGIN(attribute_name); 
				            parseContext->n_cnode_num_parameters.push(0);
				            parseContext->n_cnode_str_parameters.push(0);
                                return cubeparser::Cube4Parser::token::CNODE_OPEN;}
<tag>"</cnode>" 		{BEGIN(tag);  return cubeparser::Cube4Parser::token::CNODE_CLOSE;}

<tag>"<parameter"         {
                                    parseContext->stringContent = true;
                                    BEGIN(attribute_name);
                                    parseContext->str.str("");
                                    return cubeparser::Cube4Parser::token::CNODE_PARAMETER_OPEN;
                            }

                            

<tag>"<systemtreenode" 		{BEGIN(attribute_name); 
                                return cubeparser::Cube4Parser::token::SYSTEM_TREE_NODE_OPEN;}      
<tag>"</systemtreenode>" 	{BEGIN(tag); return cubeparser::Cube4Parser::token::SYSTEM_TREE_NODE_CLOSE;}
<tag>"<class>" 			{BEGIN(string_content); 
                                parseContext->str.str("");
                             	return cubeparser::Cube4Parser::token::CLASS_OPEN; }   
<string_content>"</class>" 	{BEGIN(tag); 
                             	return cubeparser::Cube4Parser::token::CLASS_CLOSE; }                              	
<tag>"<locationgroup" 		{BEGIN(attribute_name); 
                                return cubeparser::Cube4Parser::token::LOCATIONGROUP_OPEN;}      
<tag>"</locationgroup>" 	{BEGIN(tag); return cubeparser::Cube4Parser::token::LOCATIONGROUP_CLOSE;}
<tag>"<type>" 			{BEGIN(string_content); 
                                parseContext->str.str("");
                             	return cubeparser::Cube4Parser::token::TYPE_OPEN; }   
<string_content>"</type>" 	{BEGIN(tag); 
                             	return cubeparser::Cube4Parser::token::TYPE_CLOSE; }  
<tag>"<location" 		{BEGIN(attribute_name); 
                                return cubeparser::Cube4Parser::token::LOCATION_OPEN;}      
<tag>"</location>" 		{BEGIN(tag); return cubeparser::Cube4Parser::token::LOCATION_CLOSE;}

<tag>"<machine" 		{BEGIN(attribute_name); 
                                return cubeparser::Cube4Parser::token::MACHINE_OPEN;}
<tag>"</machine>" 		{BEGIN(tag); return cubeparser::Cube4Parser::token::MACHINE_CLOSE;}
<tag>"<node" 			{BEGIN(attribute_name); 
                                return cubeparser::Cube4Parser::token::NODE_OPEN;}
<tag>"</node>" 			{BEGIN(tag);  return cubeparser::Cube4Parser::token::NODE_CLOSE;}
<tag>"<process" 		{BEGIN(attribute_name); 
                                return cubeparser::Cube4Parser::token::PROCESS_OPEN;}
<tag>"</process>" 		{BEGIN(tag); return cubeparser::Cube4Parser::token::PROCESS_CLOSE;}
<tag>"<thread" 			{BEGIN(attribute_name); 
                                return cubeparser::Cube4Parser::token::THREAD_OPEN;}
<tag>"</thread>" 		{BEGIN(tag); return cubeparser::Cube4Parser::token::THREAD_CLOSE;}



<tag>"<cart" 			{BEGIN(attribute_name); 
                               	return cubeparser::Cube4Parser::token::CART_OPEN;}
<tag>"</cart>" 			{BEGIN(tag); return cubeparser::Cube4Parser::token::CART_CLOSE;}
<tag>"<coord" 			{BEGIN(attribute_name); 
   			        parseContext->longContent = true;
                                parseContext->longValues.clear();
                                return cubeparser::Cube4Parser::token::COORD_OPEN;}
<long_content>"</coord>" 	{parseContext->longContent = false;
				            BEGIN(tag);
                                return cubeparser::Cube4Parser::token::COORD_CLOSE;}
<tag>"<matrix" 			{BEGIN(attribute_name); 
                                return cubeparser::Cube4Parser::token::MATRIX_OPEN;}
<tag>"</matrix>" 		{BEGIN(tag); return cubeparser::Cube4Parser::token::MATRIX_CLOSE;}
<tag>"<row" 			{BEGIN(attribute_name); 
                        parseContext->realContent = true;
                        parseContext->realValues.clear();
                                return cubeparser::Cube4Parser::token::ROW_OPEN;}
<real_content>[ ]*"</row>" 		{BEGIN(tag);
                                parseContext->realContent = false;
                                return cubeparser::Cube4Parser::token::ROW_CLOSE;}
<tag>"<region" 			{BEGIN(attribute_name); 
                                return cubeparser::Cube4Parser::token::REGION_OPEN;}
<tag>"</region>"               	{BEGIN(tag); return cubeparser::Cube4Parser::token::REGION_CLOSE;}
<tag>"<doc>" 		       	{return cubeparser::Cube4Parser::token::DOC_OPEN;}
<tag>"</doc>" 		       	{BEGIN(tag); return cubeparser::Cube4Parser::token::DOC_CLOSE;}
<tag>"<mirrors>" 	       	{return cubeparser::Cube4Parser::token::MIRRORS_OPEN;}
<tag>"</mirrors>" 	       	{BEGIN(tag); return cubeparser::Cube4Parser::token::MIRRORS_CLOSE;}
<tag>"<murl>" 	               	{BEGIN(string_content);
			     	            parseContext->str.str("");
                             	return cubeparser::Cube4Parser::token::MURL_OPEN;}
<string_content>"</murl>"      	{BEGIN(tag);
                             	return cubeparser::Cube4Parser::token::MURL_CLOSE;}
<tag>"<metrics" 	       	{BEGIN(attribute_name); 
                            return cubeparser::Cube4Parser::token::METRICS_OPEN;
                            }
<tag>"</metrics>" 		    {BEGIN(tag); return cubeparser::Cube4Parser::token::METRICS_CLOSE;}

<tag>"<disp_name>" 		      {BEGIN(string_content);
			     	            parseContext->str.str("");
                             	return cubeparser::Cube4Parser::token::DISP_NAME_OPEN;}
<string_content>"</disp_name>" 	{BEGIN(tag);
                             	return cubeparser::Cube4Parser::token::DISP_NAME_CLOSE;}

<tag>"<uniq_name>" 		{BEGIN(string_content);
			     	parseContext->str.str("");
                             	return cubeparser::Cube4Parser::token::UNIQ_NAME_OPEN;}
<string_content>"</uniq_name>" 	{BEGIN(tag);
                             	return cubeparser::Cube4Parser::token::UNIQ_NAME_CLOSE;}
<tag>"<dtype>" 			{BEGIN(string_content);
			     	parseContext->str.str("");
                             	return cubeparser::Cube4Parser::token::DTYPE_OPEN;}
<string_content>"</dtype>" 	{BEGIN(tag);
                             	return cubeparser::Cube4Parser::token::DTYPE_CLOSE;}
<tag>"<uom>" 			{BEGIN(string_content);
			     	parseContext->str.str("");
                             	return cubeparser::Cube4Parser::token::UOM_OPEN;}
<string_content>"</uom>" 	{BEGIN(tag);
                             	return cubeparser::Cube4Parser::token::UOM_CLOSE;}
<tag>"<val>" 			{BEGIN(string_content);
			     	parseContext->str.str("");
                             	return cubeparser::Cube4Parser::token::VAL_OPEN;}
<string_content>"</val>" 	{BEGIN(tag);
                             	return cubeparser::Cube4Parser::token::VAL_CLOSE;}
<tag>"<url>" 			{BEGIN(string_content);
			     	parseContext->str.str("");
                             	return cubeparser::Cube4Parser::token::URL_OPEN;}
<string_content>"</url>" 	{BEGIN(tag);
                             	return cubeparser::Cube4Parser::token::URL_CLOSE;}
<tag>"<descr>" 			{BEGIN(string_content);
			     	parseContext->str.str("");
                             	return cubeparser::Cube4Parser::token::DESCR_OPEN;}
<string_content>"</descr>" 	{BEGIN(tag);
                             	return cubeparser::Cube4Parser::token::DESCR_CLOSE;}
<tag>"<program"         	{BEGIN(attribute_name);
                            return cubeparser::Cube4Parser::token::PROGRAM_OPEN;}
<tag>"</program>"        	{BEGIN(tag); return cubeparser::Cube4Parser::token::PROGRAM_CLOSE;}
<tag>"<name>" 			{BEGIN(string_content);
			     	parseContext->str.str("");
                             	return cubeparser::Cube4Parser::token::NAME_OPEN;}
<string_content>"</name>" 	{BEGIN(tag);
                             	return cubeparser::Cube4Parser::token::NAME_CLOSE;}
<tag>"<mangled_name>" 			{BEGIN(string_content);
			     	parseContext->str.str("");
                             	return cubeparser::Cube4Parser::token::MANGLED_NAME_OPEN;}
<string_content>"</mangled_name>" 	{BEGIN(tag);
                             	return cubeparser::Cube4Parser::token::MANGLED_NAME_CLOSE;}

<tag>"<paradigm>"           {BEGIN(string_content);
			    parseContext->str.str("");
                                return cubeparser::Cube4Parser::token::PARADIGM_OPEN;}
<string_content>"</paradigm>"   {BEGIN(tag);
                                return cubeparser::Cube4Parser::token::PARADIGM_CLOSE;}
<tag>"<role>"           {BEGIN(string_content);
                    parseContext->str.str("");
                                return cubeparser::Cube4Parser::token::ROLE_OPEN;}
<string_content>"</role>"   {BEGIN(tag);
                                return cubeparser::Cube4Parser::token::ROLE_CLOSE;}                             	
<tag>"<system"          	{
                                BEGIN(attribute_name);
                                return cubeparser::Cube4Parser::token::SYSTEM_OPEN;
                            }
<tag>"</system>"         	{BEGIN(tag); return cubeparser::Cube4Parser::token::SYSTEM_CLOSE;}
<tag>"<rank>" 			{BEGIN(long_content);
				 parseContext->longValues.clear();
				 return cubeparser::Cube4Parser::token::RANK_OPEN;}
<long_content>"</rank>" 	{BEGIN(tag);
                                 return cubeparser::Cube4Parser::token::RANK_CLOSE;}
<tag>"<topologies>"      	{return cubeparser::Cube4Parser::token::TOPOLOGIES_OPEN;}
<tag>"</topologies>"     	{BEGIN(tag); return cubeparser::Cube4Parser::token::TOPOLOGIES_CLOSE;}
<tag>"<severity>"        	{return cubeparser::Cube4Parser::token::SEVERITY_OPEN;}
<tag>"</severity>"          	{BEGIN(tag); return cubeparser::Cube4Parser::token::SEVERITY_CLOSE;}
<attribute_name>"version"   	{BEGIN(eq); 
                             	parseContext->contentType = ParseContext::STRINGCONTENT;
			     	return cubeparser::Cube4Parser::token::ANAME_VERSION;}
<attribute_name>"encoding"  	{BEGIN(eq); 
                             	parseContext->contentType = ParseContext::STRINGCONTENT;
			     	return cubeparser::Cube4Parser::token::ANAME_ENCODING;}
<attribute_name>"key"       	{BEGIN(eq); 
                             	parseContext->contentType = ParseContext::STRINGCONTENT;
				   return cubeparser::Cube4Parser::token::ANAME_KEY;
				   }

<attribute_name>"value"     	{BEGIN(eq); 
                             	parseContext->contentType = ParseContext::STRINGCONTENT;
			     	            return cubeparser::Cube4Parser::token::ANAME_VALUE;}

<attribute_name>"id"|"Id"   	{BEGIN(eq); 
                             	parseContext->contentType = ParseContext::INTCONTENT;
			     	return cubeparser::Cube4Parser::token::ANAME_ID;}
<attribute_name>"mod"       	{BEGIN(eq); 
                             	parseContext->contentType = ParseContext::STRINGCONTENT;
			     	return cubeparser::Cube4Parser::token::ANAME_MOD;}
			     	
<attribute_name>"type"           {BEGIN(eq); 
				    parseContext->contentType = ParseContext::STRINGCONTENT;
				    return cubeparser::Cube4Parser::token::ANAME_METRIC_TYPE;
                                }
<attribute_name>"viztype"       {
				BEGIN(eq); 
				    parseContext->contentType = ParseContext::STRINGCONTENT;
				    return cubeparser::Cube4Parser::token::ANAME_METRIC_VIZ_TYPE;
                                }
<attribute_name>"convertible"       {
				BEGIN(eq); 
				    parseContext->contentType = ParseContext::BOOLCONTENT;
				    return cubeparser::Cube4Parser::token::ANAME_METRIC_CONVERTIBLE;
                                }
<attribute_name>"cacheable"       {
				    BEGIN(eq); 
				    parseContext->contentType = ParseContext::BOOLCONTENT;
				    return cubeparser::Cube4Parser::token::ANAME_METRIC_CACHEABLE;
                                }
                                
                                
<attribute_name>"parkey"        {BEGIN(eq); 
                                parseContext->contentType = ParseContext::STRINGCONTENT;
                                    return cubeparser::Cube4Parser::token::ANAME_PAR_KEY;
                                }
<attribute_name>"parvalue"       {BEGIN(eq); 
                                parseContext->contentType = ParseContext::STRINGCONTENT;
                                    return cubeparser::Cube4Parser::token::ANAME_PAR_VALUE;
                                }
<attribute_name>"partype"       {BEGIN(eq); 
                                parseContext->contentType = ParseContext::STRINGCONTENT;
                                    return cubeparser::Cube4Parser::token::ANAME_PAR_TYPE;
                                }
<attribute_name>"name"         {BEGIN(eq); 
                                parseContext->contentType = ParseContext::STRINGCONTENT;
                                return cubeparser::Cube4Parser::token::ANAME_NAME;
                                }
<attribute_name>"title"         {BEGIN(eq); 
                                parseContext->contentType = ParseContext::STRINGCONTENT;
                                return cubeparser::Cube4Parser::token::ANAME_TITLE;
                                }
<attribute_name>"file"         {BEGIN(eq); 
                                parseContext->contentType = ParseContext::STRINGCONTENT;
                                return cubeparser::Cube4Parser::token::ANAME_FILE;
                                }
<attribute_name>"begin"     	{BEGIN(eq); 
                             	parseContext->contentType = ParseContext::INTCONTENT;
			     	return cubeparser::Cube4Parser::token::ANAME_BEGIN;}
<attribute_name>"end"       	{BEGIN(eq); 
                             	parseContext->contentType = ParseContext::INTCONTENT;
			     	return cubeparser::Cube4Parser::token::ANAME_END;}
<attribute_name>"line"       	{BEGIN(eq); 
                             	parseContext->contentType = ParseContext::INTCONTENT;
			     	return cubeparser::Cube4Parser::token::ANAME_LINE;}
<attribute_name>"calleeId"  	{BEGIN(eq); 
                             	parseContext->contentType = ParseContext::INTCONTENT;
			     	return cubeparser::Cube4Parser::token::ANAME_CALLEEID;}
<attribute_name>"ndims"     	{BEGIN(eq); 
                             	parseContext->contentType = ParseContext::INTCONTENT;
			     	return cubeparser::Cube4Parser::token::ANAME_NDIMS;}
<attribute_name>"size"      	{BEGIN(eq); 
                             	parseContext->contentType = ParseContext::INTCONTENT;
			     	return cubeparser::Cube4Parser::token::ANAME_SIZE;}
<attribute_name>"periodic"  	{BEGIN(eq); 
                             	parseContext->contentType = ParseContext::BOOLCONTENT;
			     	return cubeparser::Cube4Parser::token::ANAME_PERIODIC;}
<attribute_name>"locId"    	{BEGIN(eq); 
                             	parseContext->contentType = ParseContext::INTCONTENT;
			     	return cubeparser::Cube4Parser::token::ANAME_LOCATIONID;}
<attribute_name>"lgId"    	{BEGIN(eq); 
                             	parseContext->contentType = ParseContext::INTCONTENT;
			     	return cubeparser::Cube4Parser::token::ANAME_LOCATIONGROUPID;}
<attribute_name>"stnId"    	{BEGIN(eq); 
                             	parseContext->contentType = ParseContext::INTCONTENT;
			     	return cubeparser::Cube4Parser::token::ANAME_STNODEID;}
<attribute_name>"thrdId"    	{BEGIN(eq); 
                             	parseContext->contentType = ParseContext::INTCONTENT;
			     	return cubeparser::Cube4Parser::token::ANAME_THRDID;}
<attribute_name>"procId"    	{BEGIN(eq); 
                             	parseContext->contentType = ParseContext::INTCONTENT;
			     	return cubeparser::Cube4Parser::token::ANAME_PROCID;}
<attribute_name>"nodeId"    	{BEGIN(eq); 
                             	parseContext->contentType = ParseContext::INTCONTENT;
			     	return cubeparser::Cube4Parser::token::ANAME_NODEID;}
<attribute_name>"machId"    	{BEGIN(eq); 
                             	parseContext->contentType = ParseContext::INTCONTENT;
			     	return cubeparser::Cube4Parser::token::ANAME_MACHID;}
<attribute_name>"metricId"  	{BEGIN(eq); 
                             	parseContext->contentType = ParseContext::INTCONTENT;
			     	return cubeparser::Cube4Parser::token::ANAME_METRICID;}
<attribute_name>"cnodeId"   	{BEGIN(eq); 
                             	parseContext->contentType = ParseContext::INTCONTENT;
			     	return cubeparser::Cube4Parser::token::ANAME_CNODEID;
}
<cubepl_attribute_name>"rowwise"  {BEGIN(cubepl_eq); 
				    parseContext->contentType = ParseContext::BOOLCONTENT;
				    return cubeparser::Cube4Parser::token::ACUBEPL_ROWWISE;
                                }

<cubepl_attribute_name>"cubeplaggrtype"  {BEGIN(cubepl_eq); 
				    parseContext->contentType = ParseContext::CUBEPLAGGREGATIONCONTENT;
				    return cubeparser::Cube4Parser::token::ACUBEPL_AGGR_ATTRIBUTE;
                                }              
                                
                                
<eq>"=\""                     	{if (parseContext->contentType==ParseContext::STRINGCONTENT){ 
					BEGIN(quoted_string);
                             		parseContext->str.str("");
				} else if (parseContext->contentType==ParseContext::INTCONTENT){
					BEGIN(quoted_int);
					parseContext->str.str("");
			     	} else BEGIN(quoted_bool); }
<cubepl_eq>"="                	{
				    if (parseContext->contentType==ParseContext::CUBEPLAGGREGATIONCONTENT)
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
                             	return cubeparser::Cube4Parser::token::ATTRIBUTE_VALUE;}
                             	
<quoted_int>[^\" \t\n]+  	{
			        char* remain;
				parseContext->longAttribute = strtol(yytext,&remain,10);
				bool ok = (*remain=='\0');
				if (!ok) {
				  BEGIN(scan_error);
				  *yyout << "unexpected string: \"" << yytext << "\"";  
				} else {
				  BEGIN(right_quota);
                             	  return cubeparser::Cube4Parser::token::ATTRIBUTE_VALUE;}
				}
<quoted_bool>[fF][aA][lL][sS][eE]\" {
				BEGIN(attribute_name); 
                             	return cubeparser::Cube4Parser::token::FFALSE;}
<quoted_bool>[tT][rR][uU][eE]\" {
				BEGIN(attribute_name); 
                             	return cubeparser::Cube4Parser::token::TTRUE;}
                             	
<quoted_cubepl_bool>[fF][aA][lL][sS][eE] {
				BEGIN(cubepl_attribute_name); 
                             	return cubeparser::Cube4Parser::token::FFALSE;}
<quoted_cubepl_bool>[tT][rR][uU][eE] {
				BEGIN(cubepl_attribute_name); 
                             	return cubeparser::Cube4Parser::token::TTRUE;}    
                             	
<quoted_cubepl_aggr>[pP][lL][uU][sS] {
				BEGIN(cubepl_attribute_name); 
                             	return cubeparser::Cube4Parser::token::ACUBEPL_AGGR_ATTR_PLUS;}
<quoted_cubepl_aggr>[mM][iI][nN][uU][sS] {
				BEGIN(cubepl_attribute_name); 
                             	return cubeparser::Cube4Parser::token::ACUBEPL_AGGR_ATTR_MINUS;}    
<quoted_cubepl_aggr>[aA][gG][gG][rR] {
				BEGIN(cubepl_attribute_name); 
                             	return cubeparser::Cube4Parser::token::ACUBEPL_AGGR_ATTR_AGGR;}                                 	
                             	                             	
                             	
                             	
                             	
                             	
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
<INITIAL,attribute_name,eq,right_quota,quoted_string,quoted_bool,quoted_int,tag,real_content,long_content,cubepl_expression,cubepl_eq,cubepl_attribute_name,cubepl_expression_type>[ \t]+ {
                             	yylloc->step(); 
} 
<INITIAL,attribute_name,eq,right_quota,quoted_string,quoted_bool,quoted_int,tag,string_content,cdata,real_content,long_content>. {
                             	*yyout << "unexpected character " << yytext << std::endl;
                             	BEGIN(scan_error);
}
                            	
<scan_error>[^\n]* 		{*yyout << "Before: " << yytext << std::endl;
                   		return cubeparser::Cube4Parser::token::ERROR;}

<stop>.                { 
                            yyterminate(); 
                      }

%% /*** Additional Code ***/

namespace cubeparser {

Cube4Scanner::Cube4Scanner(cube::CubeIstream* in,
		           std::ostream* out,
			   ParseContext* parseContext, 
			   cube::Cube * _cube
  			)
  : Cube4FlexLexer(in, out),
    parseContext(parseContext),
    cube( _cube )
{
    stream_in = in;
}

Cube4Scanner::~Cube4Scanner()
{
}

}

/* This implementation of Cube4FlexLexer::yylex() is required to fill the
 * vtable of the class Cube4FlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the Cube4Scanner class instead. */

#ifdef yylex
#undef yylex
#endif

int Cube4FlexLexer::yylex()
{
    std::cerr << "in Cube4FlexLexer::yylex() !" << std::endl;
    return 0;
}
