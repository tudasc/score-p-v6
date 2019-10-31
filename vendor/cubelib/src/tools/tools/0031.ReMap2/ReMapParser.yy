/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2018                                                **
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
#include "CubeServices.h"
#include "ReMapParseContext.h"
#include "CubeMetric.h"
#include "Cube.h"
#include "CubeCartesian.h"

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

%language "C++"
/* use newer C++ skeleton file */
/* %skeleton "bison.cc"*/
%skeleton "lalr1.cc"

/* namespace to enclose parser in */
%define api.prefix remapparser

/* set the parser's class identifier */
%define "parser_class_name" ReMapParser

/* keep track of the current position within the input */
%locations

/* write out a header file containing the token defines */
%defines

%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &driver.streamname;
};

/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class ReMapDriver& driver }
%parse-param { class ReMapParseContext& parseContext }
%parse-param { class ReMapScanner& ReMapLexer }
%parse-param { class cube::Cube& cube }

/* verbose error messages */
%error-verbose

 /*** the grammar's tokens ***/
%union{}

%token FFALSE              "false"
%token TTRUE               "true"
%token ATTRIBUTE_VALUE     "attribute value"
%token END 0               "end of file"
%token ERROR               "error"
%token ACUBEPL_AGGR_ATTR_PLUS "plus"
%token ACUBEPL_AGGR_ATTR_MINUS "minus"
%token ACUBEPL_AGGR_ATTR_AGGR "aggr"


%token OPENTAG_RIGHT       ">" 
%token CLOSETAG_RIGHT      "/>" 

%token METRIC_OPEN         "<metric"
%token METRIC_CLOSE        "</metric>"
%token EXPRESSION_OPEN     "<cubepl"
%token EXPRESSION_CLOSE    "</cubepl>"
%token EXPRESSION_INIT_OPEN     "<cubeplinit>"
%token EXPRESSION_INIT_CLOSE     "</cubeplinit>"
%token EXPRESSION_AGGR_OPEN     "<cubeplaggr"
%token EXPRESSION_AGGR_CLOSE     "</cubeplaggr>"
%token METRICS_OPEN	   "<metrics"
%token METRICS_CLOSE	   "</metrics>"
%token DISP_NAME_OPEN      "<disp_name>"
%token DISP_NAME_CLOSE     "</disp_name>"
%token UNIQ_NAME_OPEN      "<uniq_name>"
%token UNIQ_NAME_CLOSE     "</uniq_name>"
%token DTYPE_OPEN          "<dtype>"
%token DTYPE_CLOSE         "</dtype>"
%token UOM_OPEN            "<uom>"
%token UOM_CLOSE           "</uom>"
%token VAL_OPEN            "<val>"
%token VAL_CLOSE           "</val>"
%token URL_OPEN            "<url>"
%token URL_CLOSE           "</url>"
%token DESCR_OPEN          "<descr>"
%token DESCR_CLOSE         "</descr>"
%token PROGRAM_OPEN        "<program"
%token PROGRAM_CLOSE       "</program>"
%token NAME_OPEN           "<name>"
%token NAME_CLOSE          "</name>"


%token DOC_OPEN            "<doc>"
%token DOC_CLOSE           "</doc>"
%token MIRRORS_OPEN        "<mirrors>"
%token MIRRORS_CLOSE       "</mirrors>"
%token MURL_OPEN           "<murl>"
%token MURL_CLOSE          "</murl>"

%token ANAME_TITLE         "attribute name title"
%token ANAME_METRICID      "attribute name metricId"
%token ANAME_METRIC_TYPE   "attribute name type"
%token ANAME_METRIC_VIZ_TYPE   "attribute name viztype"
%token ANAME_METRIC_CONVERTIBLE   "attribute name convertible"
%token ANAME_METRIC_CACHEABLE   "attribute name cacheable"
%token ACUBEPL_ROWWISE  "attribute name rowwise"
%token ACUBEPL_AGGR_ATTRIBUTE "attribute name cubeplaggrtype"

%{


#include "ReMapDriver.h"
#include "ReMapScanner.h"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>

using namespace std;
using namespace cube;

#include "CubeMetric.h"
#include "CubeCnode.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <string>
#include <vector>
#include "CubeServices.h"
#include "ReMapParseContext.h"
#include "CubeMetric.h"
#include "Cube.h"
#include "CubeCartesian.h"



remapparser::ReMapParser::location_type remapparserlloc;



/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex ReMapLexer.lex

// Workaround for Sun Studio C++ compilers on Solaris
#if defined(__SVR4) &&  defined(__SUNPRO_CC)
  #include <ieeefp.h>

  #define isinf(x)  (fpclass(x) == FP_NINF || fpclass(x) == FP_PINF)
  #define isnan(x)  isnand(x)
#endif

%}

%% /*** Grammar Rules ***/

/***basic value fields ***/

/*** define the attribute values ***/

/* string attributes */
metric_type_attr :          
ANAME_METRIC_TYPE ATTRIBUTE_VALUE {  
    if (parseContext.metricTypeSeen)
      error(remapparserlloc,"Multiple metric type attributes defines!"); 
    else parseContext.metricTypeSeen = true;
    parseContext.metricType = parseContext.str.str(); }
;

metric_viz_type_attr :          
ANAME_METRIC_VIZ_TYPE ATTRIBUTE_VALUE {  
    if (parseContext.metricVizTypeSeen)
      error(remapparserlloc,"Multiple metric visibilty type attributes defines!"); 
    else parseContext.metricVizTypeSeen = true;
    parseContext.metricVizType = parseContext.str.str(); }
;

metric_convertible_attr : 
ANAME_METRIC_CONVERTIBLE TTRUE {  
    if (parseContext.metricConvertibleSeen)
      error(remapparserlloc,"Multiple metric convertible type attributes defines!"); 
    else parseContext.metricConvertibleSeen = true;
    parseContext.metricConvertible = true; }
|
ANAME_METRIC_CONVERTIBLE FFALSE {  
    if (parseContext.metricConvertibleSeen)
      error(remapparserlloc,"Multiple metric convertible type attributes defines!"); 
    else parseContext.metricConvertibleSeen = true;
    parseContext.metricConvertible = false; }
;



metric_cacheable_attr :          
ANAME_METRIC_CACHEABLE TTRUE {  
    if (parseContext.metricCacheableSeen)
      error(remapparserlloc,"Multiple metric cacheable type attributes defines!"); 
    else parseContext.metricCacheableSeen = true;
    parseContext.metricCacheable = true; }
|
ANAME_METRIC_CACHEABLE FFALSE {  
    if (parseContext.metricCacheableSeen)
      error(remapparserlloc,"Multiple metric cacheable type attributes defines!"); 
    else parseContext.metricCacheableSeen = true;
    parseContext.metricCacheable = false; }
;



metrics_title_attr:          
| 
ANAME_TITLE ATTRIBUTE_VALUE {  
    if (parseContext.metricsTitleSeen)
      error(remapparserlloc,"Multiple metrics titles defined!"); 
    else parseContext.metricsTitleSeen = true;
    parseContext.metricsTitle = parseContext.str.str(); 
}
;


expression_attr :   
|       
ACUBEPL_ROWWISE FFALSE {  
    if (parseContext.cubeplTypeSeen)
      error(remapparserlloc,"Multiple cubepl type attributes defines!"); 
    else parseContext.cubeplTypeSeen = true;
    parseContext.rowwise = false; 
    
}
;


expression_aggr_attr :   
expression_aggr_attr_plus
|       
expression_aggr_attr_minus 
|       
expression_aggr_attr_aggr ;


expression_aggr_attr_plus : 
ACUBEPL_AGGR_ATTRIBUTE ACUBEPL_AGGR_ATTR_PLUS {  
    if (parseContext.expressionAggrPlusSeen)
      error(remapparserlloc,"Multiple cubepl plus-aggregation attributes defines!"); 
    else parseContext.expressionAggrPlusSeen = true;
    parseContext.cubeplAggrType = ReMapParseContext::CUBEPL_AGGR_PLUS; 
}
;

expression_aggr_attr_minus : 
ACUBEPL_AGGR_ATTRIBUTE ACUBEPL_AGGR_ATTR_MINUS {  
    if (parseContext.expressionAggrMinusSeen)
      error(remapparserlloc,"Multiple cubepl minus-aggregation attributes defines!"); 
    else parseContext.expressionAggrMinusSeen = true;
    parseContext.cubeplAggrType = ReMapParseContext::CUBEPL_AGGR_MINUS; 
    
}
;

expression_aggr_attr_aggr : 
ACUBEPL_AGGR_ATTRIBUTE ACUBEPL_AGGR_ATTR_AGGR {  
    if (parseContext.expressionAggrAggrSeen)
      error(remapparserlloc,"Multiple cubepl aggr-aggregation attributes defines!"); 
    else parseContext.expressionAggrAggrSeen = true;
    parseContext.cubeplAggrType = ReMapParseContext::CUBEPL_AGGR_AGGR; 
    
}
;


/*** basic tags  ***/

murl_tag :
MURL_OPEN MURL_CLOSE {
	if (parseContext.murlSeen) 
	  error(remapparserlloc,"Multiple murl tags defined!"); 
	else parseContext.murlSeen = true;
	parseContext.murl = parseContext.str.str(); };

	

disp_name_tag :
DISP_NAME_OPEN DISP_NAME_CLOSE { 
	if (parseContext.dispnameSeen) 
	  error(remapparserlloc,"Multiple disp_name tags defined!"); 
	else parseContext.dispnameSeen = true;
	parseContext.disp_name = parseContext.str.str(); };

uniq_name_tag :
UNIQ_NAME_OPEN UNIQ_NAME_CLOSE { 
	if (parseContext.uniqnameSeen) 
	  error(remapparserlloc,"Multiple uniq_name tags defined!"); 
	else parseContext.uniqnameSeen = true;
	parseContext.uniq_name = parseContext.str.str(); };
dtype_tag :
DTYPE_OPEN DTYPE_CLOSE { 
	if (parseContext.dtypeSeen) 
	  error(remapparserlloc,"Multiple dtype tags defined!"); 
	else parseContext.dtypeSeen = true;
	parseContext.dtype = parseContext.str.str(); }
;
uom_tag :
UOM_OPEN UOM_CLOSE {
	if (parseContext.uomSeen) 
	  error(remapparserlloc,"Multiple uom tags defined!"); 
	else parseContext.uomSeen = true;
	parseContext.uom = parseContext.str.str(); }
;
val_tag :
VAL_OPEN VAL_CLOSE {
	if (parseContext.valSeen) 
	  error(remapparserlloc,"Multiple val tags defined!"); 
	else parseContext.valSeen = true;
	parseContext.val = parseContext.str.str(); }
;
url_tag :
URL_OPEN URL_CLOSE {
	if (parseContext.urlSeen) 
	  error(remapparserlloc,"Multiple url tags defined!");
	else parseContext.urlSeen = true;
	parseContext.url = parseContext.str.str(); }
;



expression_tag :
EXPRESSION_OPEN expression_attr OPENTAG_RIGHT EXPRESSION_CLOSE {
	if (parseContext.expressionSeen) 
	  error(remapparserlloc,"Multiple expressions defined!"); 
	else parseContext.expressionSeen = true;
	parseContext.expression = services::escapeFromXML(parseContext.str.str()); 
	};
	
expression_init_tag :
EXPRESSION_INIT_OPEN  EXPRESSION_INIT_CLOSE {
    if (parseContext.expressionInitSeen) 
      error(remapparserlloc,"Multiple expression initializations defined!"); 
    else parseContext.expressionInitSeen = true;
    parseContext.expressionInit = services::escapeFromXML(parseContext.str.str()); 
    };

expression_aggr_tag :
EXPRESSION_AGGR_OPEN  expression_aggr_attr OPENTAG_RIGHT EXPRESSION_AGGR_CLOSE {
	if ( parseContext.cubeplAggrType == ReMapParseContext::CUBEPL_AGGR_PLUS)
	    parseContext.expressionAggrPlus = services::escapeFromXML(parseContext.str.str()); 
	else
	if ( parseContext.cubeplAggrType == ReMapParseContext::CUBEPL_AGGR_MINUS)
	    parseContext.expressionAggrMinus = services::escapeFromXML(parseContext.str.str()); 
	else
	if ( parseContext.cubeplAggrType == ReMapParseContext::CUBEPL_AGGR_AGGR)
	    parseContext.expressionAggrAggr = services::escapeFromXML(parseContext.str.str()); 
	};
descr_tag :
DESCR_OPEN DESCR_CLOSE {
	if (parseContext.descrSeen) 
	  error(remapparserlloc,"Multiple descr tags defined!");
	else parseContext.descrSeen = true;
	parseContext.descr = parseContext.str.str(); 
	}
;



/*** document structure ***/

document :
doc_tag metrics_tag
| 
metrics_tag
;

/*** metrics tag ***/

doc_tag :
DOC_OPEN mirrors_tag_opt DOC_CLOSE;

mirrors_tag_opt :
| mirrors_tag
;

mirrors_tag :
MIRRORS_OPEN murl_tags_opt MIRRORS_CLOSE
;

murl_tags_opt :
| murl_tags
;

murl_tags :
murl_tag {parseContext.murlSeen = false; cube.def_mirror(services::escapeFromXML(parseContext.murl));}
| murl_tags murl_tag {parseContext.murlSeen = false; cube.def_mirror(services::escapeFromXML(parseContext.murl));}
;



metrics_tag :
METRICS_OPEN metrics_title_attr OPENTAG_RIGHT metric_tag METRICS_CLOSE 
{
    if (parseContext.metricsTitle != "")
        cube.set_metrics_title(services::escapeFromXML(parseContext.metricsTitle));
}
;


metric_tag :
metric_begin
| metric_tag metric_begin
| metric_tag metric_end
;



metric_begin :
METRIC_OPEN  metric_attrs OPENTAG_RIGHT tags_of_metric_opt {
	//check for attributes
	parseContext.idSeen = false;
	//check for tags
	if (parseContext.metricTypeSeen) parseContext.metricTypeSeen = false;
	else parseContext.metricType = "";
	if (parseContext.metricVizTypeSeen) parseContext.metricVizTypeSeen = false;
	else parseContext.metricVizType = "";
	if (parseContext.dispnameSeen) parseContext.dispnameSeen = false;
	else parseContext.disp_name = "";
	if (parseContext.uniqnameSeen) parseContext.uniqnameSeen = false;
	else parseContext.uniq_name = "";
	if (parseContext.dtypeSeen) parseContext.dtypeSeen = false;
	else parseContext.dtype = "";
	if (parseContext.uomSeen) parseContext.uomSeen = false;
	else parseContext.uom = "";
	if (parseContext.valSeen) parseContext.valSeen = false;
	else parseContext.val = "";
	if (parseContext.urlSeen) parseContext.urlSeen = false;
	else parseContext.url = "";
	if (parseContext.descrSeen) parseContext.descrSeen = false;
	else parseContext.descr = "";
	if (parseContext.expressionSeen) parseContext.expressionSeen = false;
	else parseContext.expression = "";
	if (parseContext.expressionInitSeen) parseContext.expressionInitSeen = false;
	else parseContext.expressionInit = "";
	if (parseContext.expressionAggrPlusSeen) parseContext.expressionAggrPlusSeen = false;
	else parseContext.expressionAggrPlus = "";
	if (parseContext.expressionAggrMinusSeen) parseContext.expressionAggrMinusSeen = false;
	else parseContext.expressionAggrMinus = "";
	if (parseContext.expressionAggrAggrSeen) parseContext.expressionAggrAggrSeen = false;
	else parseContext.expressionAggrAggr = "";
	if (parseContext.metricConvertibleSeen) parseContext.metricConvertibleSeen = false;
	else parseContext.metricConvertible = true;
	if (parseContext.metricCacheableSeen) parseContext.metricCacheableSeen = false;
	else parseContext.metricCacheable = true;
	if (parseContext.cubeplTypeSeen) parseContext.cubeplTypeSeen = false;
	else parseContext.rowwise = true;
/* 	while ((int)parseContext.metricVec.size()<=parseContext.id)  */
/* 		parseContext.metricVec.push_back(NULL); */
/* 	if (parseContext.metricVec[parseContext.id]!=NULL) */
/* 	  error(remapparserlloc,"Re-declared metric!"); */
	parseContext.currentMetric = 
		cube.def_met(
			services::escapeFromXML(parseContext.disp_name),
			services::escapeFromXML(parseContext.uniq_name),
			services::escapeFromXML(parseContext.dtype),
			services::escapeFromXML(parseContext.uom),
			services::escapeFromXML(parseContext.val),
			services::escapeFromXML(parseContext.url),
			services::escapeFromXML(parseContext.descr),
			parseContext.currentMetric,
			cube::Metric::get_type_of_metric(parseContext.metricType),
			services::escapeFromXML(parseContext.expression),
			services::escapeFromXML(parseContext.expressionInit),
			services::escapeFromXML(parseContext.expressionAggrPlus),
			services::escapeFromXML(parseContext.expressionAggrMinus),
			services::escapeFromXML(parseContext.expressionAggrAggr),
			parseContext.rowwise,
			cube::Metric::get_viz_type_of_metric(parseContext.metricVizType));

	parseContext.currentMetric->setConvertible( parseContext.metricConvertible );
        parseContext.currentMetric->setCacheable( parseContext.metricCacheable );

	parseContext.metricVec.push_back(parseContext.currentMetric);
}
;


metric_attrs :
| metric_attr metric_attrs;

metric_attr :
metric_type_attr 
| metric_viz_type_attr 
| metric_convertible_attr
| metric_cacheable_attr
;

tags_of_metric_opt :
| tags_of_metric 
;

tags_of_metric :
tag_of_metric 
| tags_of_metric tag_of_metric
;

tag_of_metric :
  disp_name_tag 
| uniq_name_tag
| dtype_tag
| uom_tag
| val_tag
| url_tag
| descr_tag
| expression_tag
| expression_init_tag
| expression_aggr_tag
;

metric_end :
METRIC_CLOSE {
	if (parseContext.currentMetric==NULL)
	  error(remapparserlloc,"Metric definitions are not correctly nested!");
	parseContext.currentMetric = 
		(parseContext.currentMetric)->get_parent();
}
;


%% /*** Additional Code ***/


void remapparser::ReMapParser::error(const ReMapParser::location_type& l,
			    const std::string& m)
{
   if (strstr(m.c_str(),"expecting <?xml")!=NULL) {
     driver.error_just_message("The cube file is probably empty or filled with wrong content. The file has ended before the header of cube started. \n");
    }
   if (strstr(m.c_str()," expecting <metric")!=NULL) {
     driver.error_just_message("The cube file doesn't contain any information about metric dimension.");
    }
      driver.error(l, m);

}



