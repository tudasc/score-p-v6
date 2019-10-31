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



%code requires{ 
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

} 

/*** yacc/bison Declarations ***/

/* Require bison 2.3 or later */
%require "2.6"

/* add debug output code to generated parser. */
%debug


/* start symbol is named "document" */
%start document

/* write out a header file containing the token defines */
%defines


%language "C++"

/* use newer C++ skeleton file */
/* %skeleton "bison.cc" */
%skeleton "lalr1.cc"
/* namespace to enclose parser in */
%define api.prefix cubeparser

/* set the parser's class identifier */
%define "parser_class_name" Cube4Parser

/* keep track of the current position within the input */
%locations

%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &driver.streamname;
    clustering_on = false;
};

/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class Driver& driver }
%parse-param { class ParseContext& parseContext }
%parse-param { class Cube4Scanner& Cube4Lexer }
%parse-param { class cube::Cube& cube }
%parse-param { bool& clustering_on }

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

%token ATTR_OPEN           "<attr"
%token DIM_OPEN            "<dim"

%token XML_OPEN            "<?xml"
%token XML_CLOSE           "?>"

%token CUBE_OPEN4          "<cube version=\"4.0\""
%token CUBE_OPEN41          "<cube version=\"4.1\""
%token CUBE_OPEN42          "<cube version=\"4.2\""
%token CUBE_OPEN43          "<cube version=\"4.3\""
%token CUBE_OPEN44          "<cube version=\"4.4\""
%token CUBE_OPEN45          "<cube version=\"4.5\""
%token CUBE_OPEN3          "<cube version=\"3.0\""
%token CUBE_OPEN           "<cube version=\""
%token CUBE_OPEN_NOT_SUPPORTED    1000
%token CUBE_CLOSE          "</cube>"
%token METRIC_OPEN         "<metric"
%token METRIC_CLOSE        "</metric>"
%token EXPRESSION_OPEN     "<cubepl"
%token EXPRESSION_CLOSE     "</cubepl>"
%token EXPRESSION_INIT_OPEN     "<cubeplinit>"
%token EXPRESSION_INIT_CLOSE     "</cubeplinit>"
%token EXPRESSION_AGGR_OPEN     "<cubeplaggr"
%token EXPRESSION_AGGR_CLOSE     "</cubeplaggr>"
%token REGION_OPEN         "<region"
%token REGION_CLOSE        "</region>"
%token CNODE_OPEN          "<cnode"
%token CNODE_CLOSE         "</cnode>"
%token CNODE_PARAMETER_OPEN "<parameter"
%token SYSTEM_TREE_NODE_OPEN "<systemtreenode"
%token SYSTEM_TREE_NODE_CLOSE "</systemtreenode>"
%token LOCATIONGROUP_OPEN "<locationgroup"
%token LOCATIONGROUP_CLOSE "</locationgroup>"
%token LOCATION_OPEN       "<location"
%token LOCATION_CLOSE      "</location>"
%token MACHINE_OPEN        "<machine"
%token MACHINE_CLOSE       "</machine>"
%token NODE_OPEN           "<node"
%token NODE_CLOSE          "</node>"
%token PROCESS_OPEN        "<process"
%token PROCESS_CLOSE       "</process>"
%token THREAD_OPEN         "<thread"
%token THREAD_CLOSE        "</thread>"
%token MATRIX_OPEN         "<matrix"
%token MATRIX_CLOSE        "</matrix>"
%token ROW_OPEN            "<row"
%token ROW_CLOSE           "</row>"
%token CART_OPEN           "<cart"
%token CART_CLOSE          "</cart>"
%token COORD_OPEN          "<coord"
%token COORD_CLOSE         "</coord>"

%token DOC_OPEN            "<doc>"
%token DOC_CLOSE           "</doc>"
%token MIRRORS_OPEN        "<mirrors>"
%token MIRRORS_CLOSE       "</mirrors>"
%token MURL_OPEN           "<murl>"
%token MURL_CLOSE          "</murl>"
%token METRICS_OPEN	       "<metrics"
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
%token PARADIGM_OPEN       "<paradigm>"
%token PARADIGM_CLOSE      "</paradigm>"
%token ROLE_OPEN           "<role>"
%token ROLE_CLOSE          "</role>"
%token PROGRAM_OPEN        "<program"
%token PROGRAM_CLOSE       "</program>"
%token NAME_OPEN           "<name>"
%token NAME_CLOSE          "</name>"
%token MANGLED_NAME_OPEN   "<mangled_name>"
%token MANGLED_NAME_CLOSE  "</mangled_name>"
%token CLASS_OPEN           "<class>"
%token CLASS_CLOSE          "</class>"
%token TYPE_OPEN           "<type>"
%token TYPE_CLOSE          "</type>"

%token SYSTEM_OPEN         "<system"
%token SYSTEM_CLOSE        "</system>"
%token RANK_OPEN           "<rank>"
%token RANK_CLOSE          "</rank>"
%token TOPOLOGIES_OPEN     "<topologies>"
%token TOPOLOGIES_CLOSE    "</topologies>"
%token SEVERITY_OPEN       "<severity>"
%token SEVERITY_CLOSE      "</severity>"

%token ANAME_VERSION       "attribute name version"
%token ANAME_ENCODING      "attribute name encoding"
%token ANAME_KEY           "attribute name key"
%token ANAME_PAR_TYPE      "attribute name partype"
%token ANAME_PAR_KEY       "attribute name parkey"
%token ANAME_PAR_VALUE     "attribute name parvalue"
%token ANAME_NAME          "attribute name name"
%token ANAME_TITLE         "attribute name title"
%token ANAME_FILE          "attribute name file"
%token ANAME_VALUE         "attribute name value"
%token ANAME_ID            "attribute name id"
%token ANAME_MOD           "attribute name mod"
%token ANAME_BEGIN         "attribute name begin"
%token ANAME_END           "attribute name end"
%token ANAME_LINE          "attribute name line"
%token ANAME_CALLEEID      "attribute name calleeid"
%token ANAME_NDIMS         "attribute name ndims"
%token ANAME_SIZE          "attribute name size"
%token ANAME_PERIODIC      "attribute name periodic"

%token ANAME_LOCATIONID    "attribute name locId"
%token ANAME_LOCATIONGROUPID  "attribute name lgId"
%token ANAME_STNODEID      "attribute name stnId"
%token ANAME_THRDID        "attribute name thrdId"
%token ANAME_PROCID        "attribute name procId"
%token ANAME_NODEID        "attribute name nodeId"
%token ANAME_MACHID        "attribute name machId"
%token ANAME_METRICID      "attribute name metricId"
%token ANAME_METRIC_TYPE   "attribute name type"
%token ANAME_METRIC_VIZ_TYPE   "attribute name viztype"
%token ANAME_METRIC_CONVERTIBLE   "attribute name convertible"
%token ANAME_METRIC_CACHEABLE   "attribute name cacheable"
%token ANAME_CNODEID       "attribute name cnodeId"
%token ACUBEPL_ROWWISE  "attribute name rowwise"
%token ACUBEPL_AGGR_ATTRIBUTE "attribute name cubeplaggrtype"

%{



#include "CubeTypes.h"
#include "CubeSysres.h"
#include "CubeLocation.h"
#include "CubeLocationGroup.h"
#include "CubeSystemTreeNode.h"
#include "CubeMetric.h"
#include "CubeCnode.h"
#include "CubeRegion.h"

#include "CubeDriver.h"
#include "Cube4Scanner.h"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <string>


#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <string>
#include <vector>
#include "CubeServices.h"
#include "CubeParseContext.h"
#include "CubeMetric.h"
#include "Cube.h"
#include "CubeCartesian.h"

using namespace std;

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex Cube4Lexer.lex

// Workaround for Sun Studio C++ compilers on Solaris
#if defined(__SVR4) &&  defined(__SUNPRO_CC)
  #include <ieeefp.h>

  #define isinf(x)  (fpclass(x) == FP_NINF || fpclass(x) == FP_PINF)
  #define isnan(x)  isnand(x)
#endif


cubeparser::Cube4Parser::location_type cubeparserloc;


%}

%% /*** Grammar Rules ***/

/***basic value fields ***/

/*** define the attribute values ***/

/* string attributes */

version_attr :
ANAME_VERSION ATTRIBUTE_VALUE { 
	if (parseContext.versionSeen)
	  error(cubeparserloc,"Multiple version attributes defines!"); 
	else parseContext.versionSeen = true;
	parseContext.version = parseContext.str.str(); 
};
encoding_attr :
ANAME_ENCODING ATTRIBUTE_VALUE { 
	if (parseContext.encodingSeen)
	  error(cubeparserloc,"Multiple encoding attributes defines!"); 
	else parseContext.encodingSeen = true;
	parseContext.encoding = parseContext.str.str(); 
};
key_attr :
ANAME_KEY ATTRIBUTE_VALUE { 
	if (parseContext.keySeen)
	  error(cubeparserloc,"Multiple key attributes defines!"); 
	else parseContext.keySeen = true;
	parseContext.key = parseContext.str.str(); 
};
value_attr :
ANAME_VALUE ATTRIBUTE_VALUE { 
	if (parseContext.valueSeen)
	  error(cubeparserloc,"Multiple value attributes defines!"); 
	else parseContext.valueSeen = true;	
	parseContext.value = parseContext.str.str(); 
};
mod_attr :          
ANAME_MOD ATTRIBUTE_VALUE {  
	if (parseContext.modSeen)
	  error(cubeparserloc,"Multiple module attributes defines!"); 
	else parseContext.modSeen = true;
	parseContext.mod = parseContext.str.str(); }
;
metric_type_attr :          
ANAME_METRIC_TYPE ATTRIBUTE_VALUE {  
    if (parseContext.metricTypeSeen)
      error(cubeparserloc,"Multiple metric type attributes defines!"); 
    else parseContext.metricTypeSeen = true;
    parseContext.metricType = parseContext.str.str(); }
;

metric_viz_type_attr :          
ANAME_METRIC_VIZ_TYPE ATTRIBUTE_VALUE {  
    if (parseContext.metricVizTypeSeen)
      error(cubeparserloc,"Multiple metric visibilty type attributes defines!"); 
    else parseContext.metricVizTypeSeen = true;
    parseContext.metricVizType = parseContext.str.str(); }
;

metric_convertible_attr :          
ANAME_METRIC_CONVERTIBLE TTRUE {  
    if (parseContext.metricConvertibleSeen)
      error(cubeparserloc,"Multiple metric convertible type attributes defines!"); 
    else parseContext.metricConvertibleSeen = true;
    parseContext.metricConvertible = true; }
|
ANAME_METRIC_CONVERTIBLE FFALSE {  
    if (parseContext.metricConvertibleSeen)
      error(cubeparserloc,"Multiple metric convertible type attributes defines!"); 
    else parseContext.metricConvertibleSeen = true;
    parseContext.metricConvertible = false; }
;

metric_cacheable_attr :          
ANAME_METRIC_CACHEABLE TTRUE {  
    if (parseContext.metricCacheableSeen)
      error(cubeparserloc,"Multiple metric cacheable type attributes defines!"); 
    else parseContext.metricCacheableSeen = true;
    parseContext.metricCacheable = true; }
|
ANAME_METRIC_CACHEABLE FFALSE {  
    if (parseContext.metricCacheableSeen)
      error(cubeparserloc,"Multiple metric cacheable type attributes defines!"); 
    else parseContext.metricCacheableSeen = true;
    parseContext.metricCacheable = false; }
;



cnode_par_type_attr :          
ANAME_PAR_TYPE ATTRIBUTE_VALUE {  
    if (parseContext.cnodeParTypeSeen)
      error(cubeparserloc,"Multiple cnode parameter type attributes defines!"); 
    else parseContext.cnodeParTypeSeen = true;
    parseContext.cnode_parameter_type = parseContext.str.str(); 
}
;

cnode_par_key_attr :          
ANAME_PAR_KEY ATTRIBUTE_VALUE {  
    if (parseContext.cnodeParKeySeen)
      error(cubeparserloc,"Multiple cnode parameter keys defines!"); 
    else parseContext.cnodeParKeySeen = true;
    parseContext.cnode_parameter_key = parseContext.str.str(); 
}
;

cnode_par_value_attr :          
ANAME_PAR_VALUE ATTRIBUTE_VALUE {  
    if (parseContext.cnodeParValueSeen)
      error(cubeparserloc,"Multiple cnode parameter values defines!"); 
    else parseContext.cnodeParValueSeen = true;
    parseContext.cnode_parameter_value = parseContext.str.str(); 
}
;

cart_name_attr :          
ANAME_NAME ATTRIBUTE_VALUE {  
    if (parseContext.cartNameSeen)
      error(cubeparserloc,"Multiple topology names  defines!"); 
    else parseContext.cartNameSeen = true;
    parseContext.cartName = parseContext.str.str(); 
}
;


dim_name_attr :    
ANAME_NAME ATTRIBUTE_VALUE {
	if (parseContext.dimNameSeen) 
	  error(cubeparserloc,"Multiple names for dimension attributes defines!"); 
	else parseContext.dimNameSeen = true;
	parseContext.dimNamesCount++;
	parseContext.dimName = cube::services::escapeFromXML(parseContext.str.str()); 
};

metrics_title_attr:          
| 
ANAME_TITLE ATTRIBUTE_VALUE {  
    if (parseContext.metricsTitleSeen)
      error(cubeparserloc,"Multiple metrics titles defined!"); 
    else parseContext.metricsTitleSeen = true;
    parseContext.metricsTitle = parseContext.str.str(); 
}
;
calltree_title_attr:          
| 
ANAME_TITLE ATTRIBUTE_VALUE {  
    if (parseContext.calltreeTitleSeen)
      error(cubeparserloc,"Multiple calltree titles defined!"); 
    else parseContext.calltreeTitleSeen = true;
    parseContext.calltreeTitle = parseContext.str.str(); 
}
;

systemtree_title_attr:          
| 
ANAME_TITLE ATTRIBUTE_VALUE {  
    if (parseContext.systemtreeTitleSeen)
      error(cubeparserloc,"Multiple system tree titles defined!"); 
    else parseContext.systemtreeTitleSeen = true;
    parseContext.systemtreeTitle = parseContext.str.str(); 
}
; 

expression_attr :   
|       
ACUBEPL_ROWWISE FFALSE {  
    if (parseContext.cubeplTypeSeen)
      error(cubeparserloc,"Multiple cubepl type attributes defines!"); 
    else parseContext.cubeplTypeSeen = true;
    parseContext.rowwise = false; 
    
}
;

expression_aggr_attr :   
expression_aggr_attr_plus
|       
expression_aggr_attr_minus 
|       
expression_aggr_attr_aggr 
;


expression_aggr_attr_plus : 
ACUBEPL_AGGR_ATTRIBUTE ACUBEPL_AGGR_ATTR_PLUS {  
    if (parseContext.expressionAggrPlusSeen)
      error(cubeparserloc,"Multiple cubepl plus-aggregation attributes defines!"); 
    else parseContext.expressionAggrPlusSeen = true;
    parseContext.cubeplAggrType = ParseContext::CUBEPL_AGGR_PLUS; 
    
}
;

expression_aggr_attr_minus : 
ACUBEPL_AGGR_ATTRIBUTE ACUBEPL_AGGR_ATTR_MINUS {  
    if (parseContext.expressionAggrMinusSeen)
      error(cubeparserloc,"Multiple cubepl minus-aggregation attributes defines!"); 
    else parseContext.expressionAggrMinusSeen = true;
    parseContext.cubeplAggrType = ParseContext::CUBEPL_AGGR_MINUS; 
    
}
;


expression_aggr_attr_aggr : 
ACUBEPL_AGGR_ATTRIBUTE ACUBEPL_AGGR_ATTR_AGGR {  
    if (parseContext.expressionAggrAggrSeen)
      error(cubeparserloc,"Multiple cubepl aggr-aggregation attributes defines!"); 
    else parseContext.expressionAggrAggrSeen = true;
    parseContext.cubeplAggrType = ParseContext::CUBEPL_AGGR_AGGR; 
    
}
;

/* int attributes */

id_attr :    
ANAME_ID ATTRIBUTE_VALUE { 
	if (parseContext.idSeen) 
	  error(cubeparserloc,"Multiple id attributes defines!"); 
	else parseContext.idSeen = true;
	if (parseContext.longAttribute<0) error(cubeparserloc,"Ids must be non-negative!"); 
	parseContext.id = (int)parseContext.longAttribute; 
};

calleeid_attr :         
ANAME_CALLEEID ATTRIBUTE_VALUE { 
	if (parseContext.calleeidSeen) 
	  error(cubeparserloc,"Multiple callee id attributes defines!"); 
	else parseContext.calleeidSeen = true;
	if (parseContext.longAttribute<0) 
	  error(cubeparserloc,"Callee ids of regions must be non-negative!"); 
	parseContext.calleeid = (int)parseContext.longAttribute; 
};



locid_attr :    
ANAME_LOCATIONID ATTRIBUTE_VALUE { 
	if (parseContext.locidSeen) 
	  error(cubeparserloc,"Multiple location id attributes defines!"); 
	else parseContext.locidSeen = true;
	if (parseContext.longAttribute<0) error(cubeparserloc,"Location ids must be non-negative!"); 
	parseContext.locid = (int)parseContext.longAttribute; 
};

lgid_attr :    
ANAME_LOCATIONGROUPID ATTRIBUTE_VALUE { 
	if (parseContext.lgidSeen) 
	  error(cubeparserloc,"Multiple location group id attributes defines!"); 
	else parseContext.lgidSeen = true;
	if (parseContext.longAttribute<0) error(cubeparserloc,"Location group ids must be non-negative!"); 
	parseContext.lgid = (int)parseContext.longAttribute; 
};

stnid_attr :    
ANAME_STNODEID ATTRIBUTE_VALUE { 
	if (parseContext.stnidSeen) 
	  error(cubeparserloc,"Multiple system tree node id attributes defines!"); 
	else parseContext.stnidSeen = true;
	if (parseContext.longAttribute<0) error(cubeparserloc,"System tree node ids must be non-negative!"); 
	parseContext.stnid = (int)parseContext.longAttribute; 
};


thrdid_attr :    
ANAME_THRDID ATTRIBUTE_VALUE { 
	if (parseContext.locidSeen) 
	  error(cubeparserloc,"Multiple thread id attributes defines!"); 
	else parseContext.locidSeen = true;
	if (parseContext.longAttribute<0) error(cubeparserloc,"Thread ids must be non-negative!"); 
	parseContext.thrdid = (int)parseContext.longAttribute; 
};

procid_attr :    
ANAME_PROCID ATTRIBUTE_VALUE { 
	if (parseContext.lgidSeen) 
	  error(cubeparserloc,"Multiple process id attributes defines!"); 
	else parseContext.lgidSeen = true;
	if (parseContext.longAttribute<0) error(cubeparserloc,"Process ids must be non-negative!"); 
	parseContext.procid = (int)parseContext.longAttribute; 
};

nodeid_attr :    
ANAME_NODEID ATTRIBUTE_VALUE { 
	if (parseContext.stnidSeen) 
	  error(cubeparserloc,"Multiple node id attributes defines!"); 
	else parseContext.stnidSeen = true;
	if (parseContext.longAttribute<0) error(cubeparserloc,"Node ids must be non-negative!"); 
	parseContext.nodeid = (int)parseContext.longAttribute; 
};

machid_attr :    
ANAME_MACHID ATTRIBUTE_VALUE { 
	if (parseContext.stnidSeen) 
	  error(cubeparserloc,"Multiple machine id attributes defines!"); 
	else parseContext.stnidSeen = true;
	if (parseContext.longAttribute<0) error(cubeparserloc,"Machine ids must be non-negative!"); 
	parseContext.machid = (int)parseContext.longAttribute; 
};

metricid_attr :       
ANAME_METRICID ATTRIBUTE_VALUE { 
	if (parseContext.metricidSeen) 
	  error(cubeparserloc,"Multiple metric id attributes defines!"); 
	else parseContext.metricidSeen = true;
	if (parseContext.longAttribute<0) error(cubeparserloc,"Metric ids must be non-negative!"); 
	parseContext.metricid = parseContext.longAttribute; 
};

cnodeid_attr :    
ANAME_CNODEID ATTRIBUTE_VALUE { 
	if (parseContext.cnodeidSeen) 
	  error(cubeparserloc,"Multiple cnode id attributes defines!"); 
	else parseContext.cnodeidSeen = true;
	if (parseContext.longAttribute<0) error(cubeparserloc,"Cnode ids must be non-negative!"); 
	parseContext.cnodeid = (int)parseContext.longAttribute; 
};

/* long attributes */

begin_attr :         
ANAME_BEGIN ATTRIBUTE_VALUE { 
	if (parseContext.beginSeen) 
	  error(cubeparserloc,"Multiple begin attributes defines!"); 
	else parseContext.beginSeen = true;
	parseContext.beginln = parseContext.longAttribute; }
;

end_attr :       
ANAME_END ATTRIBUTE_VALUE { 
	if (parseContext.endSeen) 
	  error(cubeparserloc,"Multiple end attributes defines!"); 
	else parseContext.endSeen = true;
	parseContext.endln = parseContext.longAttribute; }
;

line_attr :       
ANAME_LINE ATTRIBUTE_VALUE { 
	if (parseContext.lineSeen) 
	  error(cubeparserloc,"Multiple line attributes defines!"); 
	else parseContext.lineSeen = true;
	parseContext.line = parseContext.longAttribute; }
;

ndims_attr :    
ANAME_NDIMS ATTRIBUTE_VALUE {
	if (parseContext.ndimsSeen) 
	  error(cubeparserloc,"Multiple ndims attributes defines!"); 
	else parseContext.ndimsSeen = true;
	if (parseContext.longAttribute<=0)
	   error(cubeparserloc,"Topology dimensions must be positive numbers!");
	parseContext.ndims = parseContext.longAttribute;
};

size_attr :       
ANAME_SIZE ATTRIBUTE_VALUE { 
	if (parseContext.sizeSeen) 
	  error(cubeparserloc,"Multiple size attributes defines!"); 
	else parseContext.sizeSeen = true;
	if (parseContext.longAttribute<=0)
	  error(cubeparserloc,"Dimension sizes must be positive numbers!");
	parseContext.dimVec.push_back(parseContext.longAttribute);
};

/* boolean attributes */

periodic_attr :        
ANAME_PERIODIC FFALSE { 
	if (parseContext.periodicSeen) 
	  error(cubeparserloc,"Multiple periodic attributes defines!"); 
	else parseContext.periodicSeen = true;
	parseContext.periodicVec.push_back(false);
}
| ANAME_PERIODIC TTRUE { 
	if (parseContext.periodicSeen) 
	  error(cubeparserloc,"Multiple periodic attributes defined!");
	else parseContext.periodicSeen = true;
	parseContext.periodicVec.push_back(true);
}
;

/*** basic tags  ***/

murl_tag :
MURL_OPEN MURL_CLOSE {
	if (parseContext.murlSeen) 
	  error(cubeparserloc,"Multiple murl tags defined!"); 
	else parseContext.murlSeen = true;
	parseContext.murl = parseContext.str.str(); };




disp_name_tag :
DISP_NAME_OPEN DISP_NAME_CLOSE { 
	if (parseContext.dispnameSeen) 
	  error(cubeparserloc,"Multiple disp_name tags defined!"); 
	else parseContext.dispnameSeen = true;
	parseContext.disp_name = parseContext.str.str(); };

uniq_name_tag :
UNIQ_NAME_OPEN UNIQ_NAME_CLOSE { 
	if (parseContext.uniqnameSeen) 
	  error(cubeparserloc,"Multiple uniq_name tags defined!"); 
	else parseContext.uniqnameSeen = true;
	parseContext.uniq_name = parseContext.str.str(); };
dtype_tag :
DTYPE_OPEN DTYPE_CLOSE { 
	if (parseContext.dtypeSeen) 
	  error(cubeparserloc,"Multiple dtype tags defined!"); 
	else parseContext.dtypeSeen = true;
	parseContext.dtype = parseContext.str.str(); }
;
uom_tag :
UOM_OPEN UOM_CLOSE {
	if (parseContext.uomSeen) 
	  error(cubeparserloc,"Multiple uom tags defined!"); 
	else parseContext.uomSeen = true;
	parseContext.uom = parseContext.str.str(); }
;
val_tag :
VAL_OPEN VAL_CLOSE {
	if (parseContext.valSeen) 
	  error(cubeparserloc,"Multiple val tags defined!"); 
	else parseContext.valSeen = true;
	parseContext.val = parseContext.str.str(); }
;
url_tag :
URL_OPEN URL_CLOSE {
	if (parseContext.urlSeen) 
	  error(cubeparserloc,"Multiple url tags defined!");
	else parseContext.urlSeen = true;
	parseContext.url = parseContext.str.str(); }
;
descr_tag_opt :
| descr_tag
;


expression_tag :
EXPRESSION_OPEN  expression_attr OPENTAG_RIGHT EXPRESSION_CLOSE {
	if (parseContext.expressionSeen) 
	  error(cubeparserloc,"Multiple expressions defined!"); 
	else parseContext.expressionSeen = true;
	parseContext.expression = cube::services::escapeFromXML(parseContext.str.str()); 
	};

expression_init_tag :
EXPRESSION_INIT_OPEN  EXPRESSION_INIT_CLOSE {
    if (parseContext.expressionInitSeen) 
      error(cubeparserloc,"Multiple expression initializations defined!"); 
    else parseContext.expressionInitSeen = true;
    parseContext.expressionInit = cube::services::escapeFromXML(parseContext.str.str()); 
    };

expression_aggr_tag :
EXPRESSION_AGGR_OPEN  expression_aggr_attr OPENTAG_RIGHT EXPRESSION_AGGR_CLOSE {
	if ( parseContext.cubeplAggrType == ParseContext::CUBEPL_AGGR_PLUS)
	    parseContext.expressionAggrPlus = cube::services::escapeFromXML(parseContext.str.str()); 
	else
	if ( parseContext.cubeplAggrType == ParseContext::CUBEPL_AGGR_MINUS)
	    parseContext.expressionAggrMinus = cube::services::escapeFromXML(parseContext.str.str()); 
	else 
	if ( parseContext.cubeplAggrType == ParseContext::CUBEPL_AGGR_AGGR)
	    parseContext.expressionAggrAggr = cube::services::escapeFromXML(parseContext.str.str()); 
	};
descr_tag :
DESCR_OPEN DESCR_CLOSE {
	if (parseContext.descrSeen) 
	  error(cubeparserloc,"Multiple descr tags defined!");
	else parseContext.descrSeen = true;
	parseContext.descr = parseContext.str.str(); }
;
name_tag :
NAME_OPEN NAME_CLOSE {
	if (parseContext.nameSeen) 
	  error(cubeparserloc,"Multiple name tags defined!"); 
	else parseContext.nameSeen = true;
	parseContext.name = parseContext.str.str(); 
	parseContext.mangled_name = parseContext.name; 
}
;

mangled_name_tag :
MANGLED_NAME_OPEN MANGLED_NAME_CLOSE {
	if (parseContext.mangledNameSeen) 
	  error(cubeparserloc,"Multiple mangled name tags defined!"); 
	else parseContext.mangledNameSeen = true;
	parseContext.mangled_name = parseContext.str.str(); }
;

paradigm_tag :
PARADIGM_OPEN PARADIGM_CLOSE {
    if (parseContext.paradigmSeen) 
      error(cubeparserloc,"Multiple paradigm tags defined!"); 
    else parseContext.paradigmSeen = true;
    parseContext.paradigm = parseContext.str.str(); }
;

role_tag :
ROLE_OPEN ROLE_CLOSE {
    if (parseContext.roleSeen) 
      error(cubeparserloc,"Multiple role tags defined!"); 
    else parseContext.roleSeen = true;
    parseContext.role = parseContext.str.str(); }
;

	
class_tag :
CLASS_OPEN CLASS_CLOSE {
	if (parseContext.classSeen) 
	  error(cubeparserloc,"Multiple class tags defined!"); 
	else parseContext.classSeen = true;
	parseContext.stn_class = parseContext.str.str(); }
	
;

type_tag :
TYPE_OPEN TYPE_CLOSE {
	if (parseContext.typeSeen) 
	  error(cubeparserloc,"Multiple type tags defined!"); 
	else parseContext.typeSeen = true;
	parseContext.type = parseContext.str.str(); }
;
rank_tag :
RANK_OPEN RANK_CLOSE {
	if (parseContext.rankSeen) 
	  error(cubeparserloc,"Multiple rank tags defined!"); 
	else parseContext.rankSeen = true;
	if (parseContext.longValues.size()==0)
	  error(cubeparserloc,"No rank is given in a rank tag!");
	if (parseContext.longValues.size()>1)
	  error(cubeparserloc,"Multiple ranks are given in a rank tag!");
	int rank = (int)parseContext.longValues[0];
	if (rank<0) 
	  error(cubeparserloc,"Ranks must be non-negative!");
	parseContext.rank = rank; 
};



parameter_tag :
CNODE_PARAMETER_OPEN cnode_par_type_attr cnode_par_key_attr  cnode_par_value_attr  CLOSETAG_RIGHT {
    unsigned nparameters = 0;
    if (parseContext.cnode_parameter_type == "numeric")
    {
        if (!parseContext.n_cnode_num_parameters.empty())
        {
            nparameters = parseContext.n_cnode_num_parameters.top();
            parseContext.n_cnode_num_parameters.pop();
        }
        nparameters++;
        parseContext.n_cnode_num_parameters.push(nparameters);
        std::pair<std::string, std::string > _key ;
        _key.first  =  cube::services::escapeFromXML(parseContext.cnode_parameter_key);
        _key.second =  cube::services::escapeFromXML(parseContext.cnode_parameter_value) ;
        parseContext.cnode_num_parameters.push( _key ); 

    }
    if (parseContext.cnode_parameter_type == "string")
    {
        if ( !parseContext.n_cnode_str_parameters.empty() )
        {
            nparameters = parseContext.n_cnode_str_parameters.top();
            parseContext.n_cnode_str_parameters.pop();
        }
        nparameters++;
        parseContext.n_cnode_str_parameters.push(nparameters);
    
        std::pair<std::string, std::string > _key ;
        _key.first  =  cube::services::escapeFromXML(parseContext.cnode_parameter_key);
        _key.second =  cube::services::escapeFromXML(parseContext.cnode_parameter_value) ;
        parseContext.cnode_str_parameters.push( _key ); 
    }
    parseContext.stringContent = false;
    parseContext.cnodeParTypeSeen= false;
    parseContext.cnodeParKeySeen= false;
    parseContext.cnodeParValueSeen= false;
};





/*** document structure ***/

document :
xml_tag cube_tag 
;

/*** xml tag ***/

xml_tag :
XML_OPEN xml_attributes XML_CLOSE {
	//check for attributes
	if (!parseContext.versionSeen)
 	  error(cubeparserloc,"Missing version attribute!");
	else parseContext.versionSeen = false;
	if (!parseContext.encodingSeen)
	  error(cubeparserloc,"Missing encoding attribute!");
	else parseContext.encodingSeen = false;
	int valid = strcmp(parseContext.version.c_str(),"1.0");
	if (valid!=0) error(cubeparserloc,"XML version is expected to be 1.0!");
	valid = strcmp(parseContext.encoding.c_str(),"UTF-8");
	if (valid!=0) error(cubeparserloc,"XML encoding is expected to be UTF-8!");
	cube.get_operation_progress()->start_step(0., 1.);
}
;

xml_attributes :
xml_attribute
| xml_attributes xml_attribute
;

xml_attribute :
version_attr 
| encoding_attr
;

/*** cube tag ***/

cube_tag :
cube_begin cube_content CUBE_CLOSE 
{
    cube.get_operation_progress()->finish_step("Finished parsing");
}
;

cube_begin :
CUBE_OPEN4 {
	parseContext.cubeVersion = 4;
	cube.def_attr( "Cube anchor.xml syntax version", "4" );
} 
| CUBE_OPEN41 {
    parseContext.cubeVersion = 4.1;
    cube.def_attr( "Cube anchor.xml syntax version", "4.1" );
} 
| CUBE_OPEN42 {
    parseContext.cubeVersion = 4.2;
    cube.def_attr( "Cube anchor.xml syntax version", "4.2" );
}
| CUBE_OPEN43 {
    parseContext.cubeVersion = 4.3;
    cube.def_attr( "Cube anchor.xml syntax version", "4.3" );
} 
| CUBE_OPEN44 {
    parseContext.cubeVersion = 4.4;
    cube.def_attr( "Cube anchor.xml syntax version", "4.4" );
} 
| CUBE_OPEN45 {
    parseContext.cubeVersion = 4.5;
    cube.def_attr( "Cube anchor.xml syntax version", "4.5" );
} 
| CUBE_OPEN3 {
    parseContext.cubeVersion = 3;
    cube.def_attr( "Cube syntax version", "3" );
} 
| CUBE_OPEN CUBE_OPEN_NOT_SUPPORTED {
     throw cube::NotSupportedVersionError(parseContext.str.str());
} 
;

cube_content :
attr_tags doc_tag metrics_tag program_tag system_tag severity_tag
| attr_tags metrics_tag program_tag system_tag severity_tag
| doc_tag metrics_tag program_tag system_tag severity_tag
| metrics_tag program_tag system_tag severity_tag
;

/*** attribute tags ***/

attr_tags :
attr_tag
| attr_tags attr_tag
;

attr_tag :
ATTR_OPEN attr_attributes CLOSETAG_RIGHT {
	//check for attributes
	if (!parseContext.keySeen)
	  error(cubeparserloc,"Missing key attribute!"); 
	else parseContext.keySeen = false;
	if (!parseContext.valueSeen)
	  error(cubeparserloc,"Missing value attribute!"); 
	else parseContext.valueSeen = false;
	string attrkey = cube::services::escapeFromXML(parseContext.key);
	string attrvalue = cube::services::escapeFromXML(parseContext.value);
	cube.def_attr( attrkey, attrvalue );
	
	if (attrkey.compare(CUBEPL_VERSION_KEY) == 0)
	{
        cube.select_cubepl_engine( attrvalue );
	}
}
;

attr_attributes :
attr_attribute
| attr_attributes attr_attribute
;

attr_attribute :
key_attr 
| value_attr
;

/*** documentation tag ***/

doc_tag :
DOC_OPEN mirrors_tag_attr DOC_CLOSE;

mirrors_tag_attr :
| mirrors_tag
;

mirrors_tag :
MIRRORS_OPEN murl_tags_attr MIRRORS_CLOSE
;

murl_tags_attr :
| murl_tags
;

murl_tags :
murl_tag {parseContext.murlSeen = false; cube.def_mirror(cube::services::escapeFromXML(parseContext.murl));}
| murl_tags murl_tag {parseContext.murlSeen = false; cube.def_mirror(cube::services::escapeFromXML(parseContext.murl));}
;



/*** metrics tag ***/

metrics_tag :
METRICS_OPEN 
{
  clustering_on = false;
  cube.get_operation_progress()->progress_step("Parse metrics");
  if ( cube.is_clustering_on() )
  {
    cube.get_operation_progress()->start_step(0., 1.);
    cube.get_operation_progress()->progress_step("Start parsing clusters");
    clustering_on = true;
    std::map<uint64_t, std::map<uint64_t, uint64_t> > clusters_counter;
    
    const std::map<std::string, std::string> & attrs = cube.get_attrs();
    std::map<std::string, std::string>::const_iterator _iter = attrs.find("CLUSTERING");
    if ( _iter  != attrs.end() && (*_iter).second.compare("ON") == 0)
    {
      std::map<std::string, std::string>::const_iterator _iter = attrs.find("CLUSTER ITERATION COUNT");
      if (_iter != attrs.end() )
      {
        parseContext.number_of_iterations = cube::services::string2int((*_iter).second);
        std::map<std::string, std::string>::const_iterator _iter = attrs.find("CLUSTER ROOT CNODE ID");
        if (_iter != attrs.end() )
        {
            parseContext.clustering_root_cnode_id = cube::services::string2int((*_iter).second);  
            for (uint64_t iteration = 0; iteration < parseContext.number_of_iterations; iteration ++)
            {
                cube.get_operation_progress()->progress_step(iteration/parseContext.number_of_iterations, "Reading clusters mapping");
                std::string iteration_number = cube::services::numeric2string(iteration);
                std::string key = "CLUSTER MAPPING " + iteration_number;
                std::map<std::string, std::string>::const_iterator _iter = attrs.find(key);
                if (_iter != attrs.end())
                {
                    std::string value = (*_iter).second;
                    uint64_t iteration_key = iteration;
                    std::vector<uint64_t> _cluster_id = cube::services::parse_clustering_value( value );
                    std::vector<uint64_t> _collapsed_cluster_id = cube::services::sort_and_collapse_clusters( _cluster_id );
                    parseContext.cluster_mapping[ iteration_key] = _cluster_id;
                    parseContext.cluster_positions[ iteration_key ] = cube::services::get_cluster_positions( _cluster_id );
                    parseContext.collapsed_cluster_mapping[ iteration_key ] = _collapsed_cluster_id; 
                    uint64_t process_rank = 0;
                    for (std::vector<uint64_t>::iterator iter = _cluster_id.begin(); iter!= _cluster_id.end(); iter++, process_rank++)
                    {
                        uint64_t _id = *iter;
                        clusters_counter[_id][process_rank]++;
                    }
                }
                else 
                {
                cerr << "Clustering mapping is not continuous." << endl;
                clustering_on = false;
                cube.enable_clustering(false);
                break;
                }
            }
                cube.set_clusters_count(clusters_counter);
            }
            else 
            {
                cerr << "Cannot find cluster root cnode" << endl;
                clustering_on = false;
                cube.enable_clustering(false);	  
            }
        }
        else 
        {
            cerr << "Cannot find number of clustered iterations" << endl;
            clustering_on = false;
            cube.enable_clustering(false);
        }
        cube.get_operation_progress()->finish_step("Parsing cluster mappings finished");
    }
    else
    {
        clustering_on = false;
        cube.enable_clustering(false);
    }
  
  }
}
metrics_title_attr OPENTAG_RIGHT metric_tag METRICS_CLOSE 
{
    if (parseContext.metricsTitle != "")
        cube.set_metrics_title(cube::services::escapeFromXML(parseContext.metricsTitle));
    cube.get_operation_progress()->progress_step(0.2, "Finished parsing metrics");
}
;


metric_tag :
metric_begin
| metric_tag metric_begin
| metric_tag metric_end
;



metric_begin :
METRIC_OPEN id_attrs metric_attrs OPENTAG_RIGHT tags_of_metric_attr {
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

	while ((int)parseContext.metricVec.size()<=parseContext.id) 
		parseContext.metricVec.push_back(NULL);
	if (parseContext.metricVec[parseContext.id]!=NULL)
	  error(cubeparserloc,"Re-declared metric!");

	    parseContext.currentMetric = 
		    cube.def_met(
			    cube::services::escapeFromXML(parseContext.disp_name),
			    cube::services::escapeFromXML(parseContext.uniq_name),
			    cube::services::escapeFromXML(parseContext.dtype),
			    cube::services::escapeFromXML(parseContext.uom),
			    cube::services::escapeFromXML(parseContext.val),
			    cube::services::escapeFromXML(parseContext.url),
			    cube::services::escapeFromXML(parseContext.descr),
			    parseContext.currentMetric,
			    cube::Metric::get_type_of_metric(parseContext.metricType),
			    cube::services::escapeFromXML(parseContext.expression),
			    cube::services::escapeFromXML(parseContext.expressionInit),
			    cube::services::escapeFromXML(parseContext.expressionAggrPlus),
			    cube::services::escapeFromXML(parseContext.expressionAggrMinus),
			    cube::services::escapeFromXML(parseContext.expressionAggrAggr),
                            parseContext.rowwise,
			    cube::Metric::get_viz_type_of_metric(parseContext.metricVizType));
        if (parseContext.currentMetric != NULL)
        {
	    parseContext.currentMetric->setConvertible( parseContext.metricConvertible );
	    parseContext.currentMetric->setCacheable( parseContext.metricCacheable );
	    parseContext.currentMetric->set_filed_id( parseContext.id );
            if (parseContext.n_attributes.size() > 0)
            {
                unsigned nattributes = parseContext.n_attributes.top(); 
                parseContext.n_attributes.pop();
                
                if (nattributes > parseContext.attributes.size()) 
                {
                error(cubeparserloc, "Number of saved attributes for metric " + parseContext.uniq_name + " is more, than number of actual saved parameters.");
                }
                std::stack<std::pair<std::string, std::string> > reversed;
                for (unsigned i=0; i< nattributes; i++) 
                {
                    std::pair< std::string, std::string>  attr = parseContext.attributes.top();
                    parseContext.attributes.pop();
                    reversed.push(attr);
                }
                for (unsigned i=0; i< nattributes; i++) 
                {
                    std::pair< std::string, std::string>  attr = reversed.top();
                    reversed.pop();
                    parseContext.currentMetric->def_attr(attr.first, attr.second);
                }
            }
        parseContext.metricVec[parseContext.id] = parseContext.currentMetric;
        }
        else
        {
            std::string _error = "Cannot create metric  " + parseContext.uniq_name + ". Ignore it.";
            cerr << _error << endl;
/*             error(cubeparserloc,_error.c_str()); */
        }
}
;

id_attrs :
| id_attr ;



metric_attrs :
| metric_attr metric_attrs;

metric_attr :
metric_type_attr 
| metric_viz_type_attr 
| metric_convertible_attr
| metric_cacheable_attr
;

tags_of_metric_attr :
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
| generic_attr_tag
;


generic_attr_tag :
ATTR_OPEN key_attr value_attr CLOSETAG_RIGHT {
    //check for attributes
    if (!parseContext.keySeen)
      error(cubeparserloc,"Missing key attribute!"); 
    else parseContext.keySeen = false;
    if (!parseContext.valueSeen)
      error(cubeparserloc,"Missing value attribute!"); 
    else parseContext.valueSeen = false;
    
    unsigned nattributes = 0;
    if (parseContext.n_attributes.size() != 0  )
    {
        nattributes = parseContext.n_attributes.top();
        parseContext.n_attributes.pop();
    }
    nattributes++;
    parseContext.n_attributes.push(nattributes);
    std::pair<std::string, std::string > _key ;
    _key.first  =  cube::services::escapeFromXML(parseContext.key);
    _key.second =  cube::services::escapeFromXML(parseContext.value) ;
    parseContext.attributes.push( _key );  
}
;




metric_end :
METRIC_CLOSE {
	if (parseContext.currentMetric!=NULL)
        parseContext.currentMetric = 
            (parseContext.currentMetric)->get_parent();
}
;


/*** program tag ***/

program_tag :
PROGRAM_OPEN 
{
    cube.get_operation_progress()->progress_step(0.2, "Start parsing program dimension");
}
calltree_title_attr OPENTAG_RIGHT 
{
    cube.get_operation_progress()->progress_step(0.3, "Start parsing regions");
}
region_tags 

{
    cube.get_operation_progress()->progress_step(0.4, "Start parsing call tree");
}
cnode_tag PROGRAM_CLOSE
{
    if (parseContext.calltreeTitle != "")
        cube.set_calltree_title(cube::services::escapeFromXML(parseContext.calltreeTitle));
    
  if (clustering_on) // here look for region template  and create subtrees for iterations
  {
  	cube.get_operation_progress()->start_step(0., 1.);
    cube.get_operation_progress()->progress_step("Start declustering");       
    // after parsing, whole stored calltree is stored not within cube, but separatelly, in parseContext.oroginal_tree_roots. 
    // here we create first a copy of the original tree without clustering subtrees
    cube::Cnode * clusters_root = NULL;
    cube.set_original_root_cnodev( parseContext.original_tree_roots );
    int step = 0;
    for (std::vector<cube::Cnode*>::iterator citer= parseContext.original_tree_roots.begin(); citer!=parseContext.original_tree_roots.end(); ++citer, ++step )
    {
        cube::Cnode* cnode = *citer;
        cube::Cnode * _clusters_root = NULL;
        cube::services::copy_tree( cnode, _clusters_root, parseContext.clustering_root_cnode_id,  NULL, &cube);
        if (_clusters_root != NULL )
            clusters_root = _clusters_root;
    }   
    parseContext.clustering_root_cnode = clusters_root;
    
    if (cube::services::get_children( parseContext.original_tree_roots,
        parseContext.clustering_root_cnode_id,
        parseContext.clusters_trees))
    {
        int i = 0;
        for (std::vector<cube::Cnode*>::iterator citer= parseContext.clusters_trees.begin(); citer!=parseContext.clusters_trees.end(); ++citer, ++i )
        {
            parseContext.id2cluster[ (*citer)->get_id() ] = i;
        }   
          
    }else
    {
        clustering_on = false;
        break;
    }
			      
    cube.get_operation_progress()->progress_step(0.1, "Create iteration template"); 

     // here we are going througs registered sofar regions and look for first cluster to take its region as a template for iterations
     for (std::vector<cube::Region*>::const_iterator riter= cube.get_regv().begin(); riter!=cube.get_regv().end(); ++riter )
     {
      cube::Region* region = *riter;
      if (region->get_name().compare("instance=1")==0)
      {
        parseContext.iterationRegionTemplate = region;
        break;
      }
     }
     // if we didn't found any regions, but clustering was "on" -> fatal error appeared. 
     if (parseContext.iterationRegionTemplate == NULL ) // we didnt find any template for iteration subtree, bad cube layout
      throw cube::CubeClusteringLayoutError("Cannot find a template for iteration calltree.");
 
    // here we merge different combinations of clusters.
    // one can reduce amount of merges if one finds ont set of different collapsed rows - improvements for future.  
     cube.get_operation_progress()->progress_step(0.2, "Create iterations"); 

      // here we create regions for iterations
     std::map<uint64_t,   std::map<uint64_t, uint64_t> > cluster_counter = cube.get_clusters_counter();
      for (unsigned i=0; i< parseContext.number_of_iterations; i++)
      {
        std::stringstream sstr;
        std::string iteration_name;
        sstr << i;
        sstr >> iteration_name;
        // we create a regions
        cube::Region * region =  cube.def_region( 
                            "iteration="+iteration_name,
			    "iteration="+iteration_name,
                            parseContext.iterationRegionTemplate->get_paradigm(),
                            parseContext.iterationRegionTemplate->get_role(),
                            parseContext.iterationRegionTemplate->get_begn_ln(),
                            parseContext.iterationRegionTemplate->get_end_ln(), 
                            parseContext.iterationRegionTemplate->get_url(),
                            parseContext.iterationRegionTemplate->get_descr(),
                            parseContext.iterationRegionTemplate->get_mod() 
                            );
        parseContext.iteration_regions.push_back( region );
        // create its cnode
        cube::Cnode* iteration_cnode = cube.def_cnode(
                            region,
                            region->get_mod(), 
                            region->get_begn_ln(), 
                            parseContext.clustering_root_cnode
                            );							  	

        // here we merge all subtrees of all clusters to this callpath.
        std::vector<cube::Cnode*> subtrees;
        for ( std::vector< uint64_t>::iterator iter= parseContext.collapsed_cluster_mapping[i].begin(); iter != parseContext.collapsed_cluster_mapping[i].end(); ++iter  )
        {   
            subtrees.clear();
            uint64_t _cluster_id = *iter;
            std::map<uint64_t, uint64_t> _cluster_normalization = cluster_counter[ _cluster_id ];
            uint64_t _cluster_position = parseContext.id2cluster[_cluster_id];
            cube::Cnode* cluster_root = parseContext.clusters_trees[_cluster_position];
            cube.store_ghost_cnode( cluster_root ); 
            for ( size_t j = 0; j <  parseContext.cluster_positions[ i ][ _cluster_id ].size(); ++j )
            {
                iteration_cnode->set_remapping_cnode( parseContext.cluster_positions[ i ][ _cluster_id ][j], cluster_root,  _cluster_normalization[parseContext.cluster_positions[ i ][ _cluster_id ][j]] );
            }
            cube::services::gather_children( subtrees, cluster_root );
            cube::services::merge_trees(subtrees, iteration_cnode, &cube, &_cluster_normalization, &(parseContext.cluster_positions[ i ][ _cluster_id ]) );
        }
        cube.get_operation_progress()->progress_step(0.2 + ((i*0.8)/parseContext.number_of_iterations), "Create iterations"); 
      }
    cube.get_operation_progress()->finish_step("Declustering is done");       
  }   
    cube.get_operation_progress()->progress_step(0.4, "Finished parsing program dimension");
}
;

region_tags :
region_tag
| region_tags region_tag
;

region_tag :
REGION_OPEN region_attributes OPENTAG_RIGHT tags_of_region_attr REGION_CLOSE {
	//check for the attributes
	if (!parseContext.idSeen)
	  error(cubeparserloc,"Missing id attribute!"); 
	else parseContext.idSeen = false;
	if (!parseContext.modSeen)
		parseContext.mod = "";
	else parseContext.modSeen = false;
	if (!parseContext.beginSeen)
		parseContext.beginln = -1;
	else parseContext.beginSeen = false;
	if (!parseContext.endSeen)
		parseContext.endln = -1;
	else parseContext.endSeen = false;
    if (!parseContext.paradigmSeen)
        parseContext.paradigm = "unknown";
    else parseContext.paradigmSeen = false;
    if (!parseContext.roleSeen)
        parseContext.role = "unknown";
    else parseContext.roleSeen = false;    
	//check for tags
	if (parseContext.nameSeen) parseContext.nameSeen = false;
	else parseContext.name = "";
	if (parseContext.mangledNameSeen) parseContext.mangledNameSeen = false;
	else parseContext.mangled_name = parseContext.name;
	if (parseContext.urlSeen) parseContext.urlSeen = false;
	else parseContext.url = "";
	if (parseContext.descrSeen) parseContext.descrSeen = false;
	else parseContext.descr = "";
	
	while ((int)parseContext.regionVec.size()<=parseContext.id) 
		parseContext.regionVec.push_back(NULL);
	if (parseContext.regionVec[parseContext.id]!=NULL)
	  error(cubeparserloc,"Re-declared region!"); 
 
	cube::Region * _region =
        cube.def_region(
		 cube::services::escapeFromXML(parseContext.name),
		 cube::services::escapeFromXML(parseContext.mangled_name),
		 cube::services::escapeFromXML(parseContext.paradigm),
		 cube::services::escapeFromXML(parseContext.role),
			parseContext.beginln,
			parseContext.endln,
			parseContext.url,
		 cube::services::escapeFromXML(parseContext.descr),
		 cube::services::escapeFromXML(parseContext.mod),
			parseContext.id);
    if (parseContext.n_attributes.size() > 0)
    {
        unsigned nattributes = parseContext.n_attributes.top(); 
        parseContext.n_attributes.pop();
        
        if (nattributes > parseContext.attributes.size()) 
        {
        error(cubeparserloc, "Number of saved attributes for region " + parseContext.name + " is more, than number of actual saved parameters.");
        }
        std::stack<std::pair<std::string, std::string> > reversed;
        for (unsigned i=0; i< nattributes; ++i) 
        {
            std::pair< std::string, std::string>  attr = parseContext.attributes.top();
            parseContext.attributes.pop();
            reversed.push(attr);
        }
        for (unsigned i=0; i< nattributes; ++i) 
        {
            std::pair< std::string, std::string>  attr = reversed.top();
            reversed.pop();
            _region->def_attr(attr.first, attr.second);
        }
    }
    parseContext.regionVec[parseContext.id] = _region;
}
;

tags_of_region_attr :
| tags_of_region
;

tags_of_region :
tag_of_region
| tags_of_region tag_of_region
;

tag_of_region :
  name_tag 
| mangled_name_tag 
| paradigm_tag  
| role_tag    
| url_tag 
| descr_tag
| generic_attr_tag
;



region_attributes :
  region_attribute
| region_attributes region_attribute
;

region_attribute :
  id_attr 
| mod_attr 
| begin_attr 
| end_attr 
;

cnode_tag :
cnode_begin
| cnode_tag cnode_parameters cnode_attr_tags cnode_begin 
| cnode_tag cnode_parameters cnode_attr_tags CNODE_CLOSE 
{
    if (parseContext.n_attributes.size() > 0)
    {
        unsigned nattributes = parseContext.n_attributes.top(); 
        parseContext.n_attributes.pop();
        
        if (nattributes > parseContext.attributes.size()) 
        {
            error(cubeparserloc, "Number of saved attributes for cnode is more, than number of actual saved parameters.");
        }
        std::stack<std::pair<std::string, std::string> > reversed;
        for (unsigned i=0; i< nattributes; ++i) 
        {
            std::pair< std::string, std::string>  attr = parseContext.attributes.top();
            parseContext.attributes.pop();
            reversed.push(attr);
        }
        for (unsigned i=0; i< nattributes; ++i) 
        {
            std::pair< std::string, std::string>  attr = reversed.top();
            reversed.pop();
            parseContext.currentCnode->def_attr(attr.first, attr.second);
        }    
    }
    
    
    if (!clustering_on)
    {      
    
	  if (parseContext.currentCnode==NULL)
	    error(cubeparserloc,"Cnode definitions are not correctly nested!"); 


	  if (!parseContext.n_cnode_num_parameters.empty()  )
	  {
	      unsigned nparameters = parseContext.n_cnode_num_parameters.top(); 
	      parseContext.n_cnode_num_parameters.pop();
	      
	      if (nparameters > parseContext.cnode_num_parameters.size()) 
	      {
		  error(cubeparserloc, "Number of saved numeric parameters for current cnode is more, than number of actual saved parameters.");
	      }
              std::stack<std::pair<std::string, std::string> > reversed;
	      for (unsigned i=0; i< nparameters; ++i) 
	      {
		  std::pair< std::string, std::string>  param = parseContext.cnode_num_parameters.top();
		  
		  parseContext.cnode_num_parameters.pop();
		  reversed.push(param);
	      }
	      for (unsigned i=0; i< nparameters; ++i) 
	      {
		  std::pair< std::string, std::string> param = reversed.top();
		  reversed.pop();

		  double d_value = atof(param.second.data());
		  parseContext.currentCnode->add_num_parameter(param.first, d_value);
	      }
	  }
	  if (!parseContext.n_cnode_str_parameters.empty()  )
	  {
	      unsigned nparameters = parseContext.n_cnode_str_parameters.top(); 
	      parseContext.n_cnode_str_parameters.pop();
	      
	      if (nparameters > parseContext.cnode_str_parameters.size()) 
	      {
		  error(cubeparserloc, "Number of saved string parameters for current cnode is more, than number of actual saved parameters.");
	      }
              std::stack<std::pair<std::string, std::string> > reversed;
	      for (unsigned i=0; i< nparameters; ++i) 
	      {

		  std::pair< std::string, std::string>  param = parseContext.cnode_str_parameters.top();
		  parseContext.cnode_str_parameters.pop();
		  reversed.push(param);
	      }
	      for (unsigned i=0; i< nparameters; ++i) 
	      {
		  std::pair< std::string, std::string> param = reversed.top();
		  reversed.pop();
		  parseContext.currentCnode->add_str_parameter(param.first, param.second);
	      }
	  }	

	  parseContext.currentCnode = 
		  parseContext.currentCnode->get_parent();
	  parseContext.start_parse_clusters = false;
    }
    else
    {
	if (parseContext.clusterCurrentCnode==NULL)
	  error(cubeparserloc,"Cluster cnode definitions are not correctly nested!"); 


	if (!parseContext.n_cnode_num_parameters.empty()  )
	{
	    unsigned nparameters = parseContext.n_cnode_num_parameters.top(); 
	    parseContext.n_cnode_num_parameters.pop();
	    
	    if (nparameters > parseContext.cnode_num_parameters.size()) 
	    {
		error(cubeparserloc, "Number of saved numeric parameters for current cnode is more, than number of actual saved parameters.");
	    }
            std::stack<std::pair<std::string, std::string> > reversed;
	    for (unsigned i=0; i< nparameters; ++i) 
	    {
		std::pair< std::string, std::string>  param = parseContext.cnode_num_parameters.top();
		
		parseContext.cnode_num_parameters.pop();
                reversed.push( param );
            }
            for ( unsigned i = 0; i < nparameters; ++i )
            {
                std::pair< std::string, std::string> param = reversed.top();
                reversed.pop();

		double d_value = atof(param.second.data());
		parseContext.clusterCurrentCnode->add_num_parameter(param.first, d_value);
	    }
	}
	if (!parseContext.n_cnode_str_parameters.empty()  )
	{
	    unsigned nparameters = parseContext.n_cnode_str_parameters.top(); 
	    parseContext.n_cnode_str_parameters.pop();
	    
	    if (nparameters > parseContext.cnode_str_parameters.size()) 
	    {
		error(cubeparserloc, "Number of saved string parameters for current cnode is more, than number of actual saved parameters.");
	    }
            std::stack<std::pair<std::string, std::string> > reversed;
	    for (unsigned i=0; i< nparameters; ++i) 
	    {
		std::pair< std::string, std::string>  param = parseContext.cnode_str_parameters.top();
		parseContext.cnode_str_parameters.pop();
                reversed.push( param );
            }
            for ( unsigned i = 0; i < nparameters; ++i )
            {
                std::pair< std::string, std::string> param = reversed.top();
                reversed.pop();
		parseContext.clusterCurrentCnode->add_str_parameter(param.first, param.second);
	    }
	}

	parseContext.clusterCurrentCnode = 
		parseContext.clusterCurrentCnode->get_parent();    
	if (parseContext.clusterCurrentCnode == NULL)
	{
	  parseContext.parse_clusters = false;
	}

    }

}
;

cnode_begin :
CNODE_OPEN cnode_attributes OPENTAG_RIGHT  {
	//check for the attributes 
	if (!parseContext.idSeen)
	  error(cubeparserloc,"Missing id attribute in cnode definition!"); 
	else parseContext.idSeen = false;
	if (!parseContext.calleeidSeen)
	  error(cubeparserloc,"Missing callee id attribute in cnode definition!"); 
	else parseContext.calleeidSeen = false;
	if (!parseContext.lineSeen)
	  	parseContext.line = -1;
	else parseContext.lineSeen = false;
	if (!parseContext.modSeen)
	  	parseContext.mod = "";
	else parseContext.modSeen = false;
	//check if the region is defined
	if ((int)parseContext.regionVec.size()<=parseContext.calleeid)
	  error(cubeparserloc,"Undefined region in cnode definition!"); 
	if (parseContext.regionVec[parseContext.calleeid]==NULL)
	  error(cubeparserloc,"Undefined region in cnode definition!"); 
	//extend the cnode vector if necessary
	while ((int)parseContext.cnodeVec.size()<=parseContext.id) 
		parseContext.cnodeVec.push_back(NULL);
	if (parseContext.cnodeVec[parseContext.id]!=NULL)
	  error(cubeparserloc,"Re-declared cnode!");
	//define the cnode

    parseContext.cnodeParTypeSeen= false;
    parseContext.cnodeParKeySeen= false;
    parseContext.cnodeParValueSeen= false;

    if (clustering_on)
    {
	  parseContext.clusterCurrentCnode = new cube::Cnode( parseContext.regionVec[parseContext.calleeid] ,
							    cube::services::escapeFromXML(parseContext.mod),
							    parseContext.line,
							    parseContext.clusterCurrentCnode,
							    parseContext.id );
        if (parseContext.clusterCurrentCnode->get_parent() == NULL) // store root call path for cluster in a vector.
        {
        parseContext.original_tree_roots.push_back(parseContext.clusterCurrentCnode );
        }
    }
    else
    {
      parseContext.currentCnode = cube.def_cnode(
			parseContext.regionVec[parseContext.calleeid],
		 cube::services::escapeFromXML(parseContext.mod),
			parseContext.line,
			parseContext.currentCnode,
			parseContext.id);

	parseContext.cnodeVec[parseContext.id] =
		parseContext.currentCnode;		
    }
}
;

cnode_parameters : 
| parameter_tag cnode_parameters
;



cnode_attr_tags : 
 
| cnode_attr_tags generic_attr_tag
;


cnode_attribute :
  id_attr 
| line_attr 
| mod_attr 
| calleeid_attr 
;

cnode_attributes :
cnode_attribute
| cnode_attributes cnode_attribute
;

/*** system tag ***/

system_tag :
SYSTEM_OPEN 
{
  cube.get_operation_progress()->start_step(0., 1.);
}
systemtree_title_attr OPENTAG_RIGHT systemtree_tags topologies_tag_attr SYSTEM_CLOSE
{
    cube.get_operation_progress()->finish_step("Finished parsing system tree");
    if (parseContext.systemtreeTitle != "")
        cube.set_systemtree_title(cube::services::escapeFromXML(parseContext.systemtreeTitle));
        
        // at this moment all dimensionis are loadeed -> we can initialize containers
        cube.initialize();
        
        
}
;

systemtree_tags :
machine_tags 
| 
flexsystemtree_tags
;

flexsystemtree_tags :
systemtree_tag 
| flexsystemtree_tags systemtree_tag
;

systemtree_tag :
SYSTEM_TREE_NODE_OPEN 
{
    cube.get_operation_progress()->start_step(0.7, 1.);
    cube.get_operation_progress()->progress_step("Start parsing system tree");
}
id_attr OPENTAG_RIGHT  name_tag  class_tag descr_tag_opt  systree_attr_tags {
	//check for attributes
	parseContext.idSeen = false;
	//check for tags
	parseContext.nameSeen = false;
	if (!parseContext.classSeen )
	   error(cubeparserloc,"No class of system tree node declared."); 
	parseContext.classSeen = false;
	if (parseContext.descrSeen) parseContext.descrSeen = false;
	else parseContext.descr = "";

	cube::SystemTreeNode * _stn = cube.def_system_tree_node(
				    cube::services::escapeFromXML(parseContext.name),
				    cube::services::escapeFromXML(parseContext.descr), 
				    cube::services::escapeFromXML(parseContext.stn_class), 
				    (parseContext.currentSystemTreeNode.size() == 0)? NULL : parseContext.currentSystemTreeNode.top() ); 
    if (parseContext.n_attributes.size() > 0)
    {				    
        unsigned nattributes = parseContext.n_attributes.top(); 
        parseContext.n_attributes.pop();
        
        if (nattributes > parseContext.attributes.size()) 
        {
        error(cubeparserloc, "Number of saved attributes for metric " + parseContext.uniq_name + " is more, than number of actual saved parameters.");
        }
        std::stack<std::pair<std::string, std::string> > reversed;
        for (unsigned i=0; i< nattributes; ++i) 
        {
            std::pair< std::string, std::string>  attr = parseContext.attributes.top();
            parseContext.attributes.pop();
            reversed.push(attr);
        }
        for (unsigned i=0; i< nattributes; ++i) 
        {
            std::pair< std::string, std::string>  attr = reversed.top();
            reversed.pop();
            _stn->def_attr(attr.first, attr.second);
        }  				    
    }		    
				    
				    
	parseContext.currentSystemTreeNode.push(_stn);
 	while ((unsigned int)parseContext.stnVec.size()<=_stn->get_id()) 
 		parseContext.stnVec.push_back(NULL); 
	if (parseContext.stnVec[_stn->get_id()]!=NULL)
	  error(cubeparserloc,"Re-declared system tree node!"); 
	parseContext.stnVec[_stn->get_id()] =_stn;
	
	
	std::string _step = "Created system tree node " + cube::services::escapeFromXML(parseContext.name);
	
        cube.get_operation_progress()->progress_step(  _step );	

	
}


location_group_tags systemtree_sub_tags SYSTEM_TREE_NODE_CLOSE
{

  parseContext.currentSystemTreeNode.pop();
	//check for attributes
  parseContext.idSeen = false;
	//check for tags
	parseContext.nameSeen = false;
  if (parseContext.descrSeen) parseContext.descrSeen = false;
      else parseContext.descr = "";
    cube.get_operation_progress()->finish_step("Finished parsing system tree");
}
;

systree_attr_tags :  
|
systree_attr_tags generic_attr_tag
;
 


 
 

 
systemtree_sub_tags :
| 
flexsystemtree_tags; 


location_group_tags :  
|
location_group_tags location_group_tag
;


location_group_tag :
LOCATIONGROUP_OPEN id_attr OPENTAG_RIGHT loc_tags{
	//check for attributes
	parseContext.idSeen = false;
	//check for tags
	parseContext.nameSeen = false;
	parseContext.rankSeen = false;
	if (!parseContext.typeSeen )
	   error(cubeparserloc,"No type of location group declared."); 
	parseContext.typeSeen = false;

	if (parseContext.descrSeen) parseContext.descrSeen = false;
	  else parseContext.descr = "";

	parseContext.currentLocationGroup = cube.def_location_group(
	 cube::services::escapeFromXML(parseContext.name),
		parseContext.rank,
		cube::LocationGroup::getLocationGroupType(cube::services::escapeFromXML(parseContext.type)),
		parseContext.currentSystemTreeNode.top());
    if (parseContext.n_attributes.size() > 0)
    {		
        unsigned nattributes = parseContext.n_attributes.top(); 
        parseContext.n_attributes.pop();
        
        if (nattributes > parseContext.attributes.size()) 
        {
        error(cubeparserloc, "Number of saved attributes for location group " + parseContext.name + " is more, than number of actual saved parameters.");
        }
        std::stack<std::pair<std::string, std::string> > reversed;
        for (unsigned i=0; i< nattributes; ++i) 
        {
            std::pair< std::string, std::string>  attr = parseContext.attributes.top();
            parseContext.attributes.pop();
            reversed.push(attr);
        }
        for (unsigned i=0; i< nattributes; ++i) 
        {
            std::pair< std::string, std::string>  attr = reversed.top();
            reversed.pop();
            parseContext.currentLocationGroup->def_attr(attr.first, attr.second);
        }   	
    }
		
		
	while ((unsigned int)parseContext.locGroup.size()<=parseContext.currentLocationGroup->get_id())
		parseContext.locGroup.push_back(NULL);
	if (parseContext.locGroup[parseContext.currentLocationGroup->get_id()]!=NULL)
	  error(cubeparserloc,"Re-declared location group!"); 
	parseContext.locGroup[parseContext.currentLocationGroup->get_id()] = parseContext.currentLocationGroup;
	
	std::string _step =  "Created location group " + cube::services::escapeFromXML(parseContext.name);
	cube.get_operation_progress()->progress_step( _step );	
	} location_tags LOCATIONGROUP_CLOSE
;

loc_tags :
loc_tag
;

loc_tag:
name_tag rank_tag type_tag lg_attr_tags
;
 
lg_attr_tags :
|
generic_attr_tag lg_attr_tags
;


 
location_tags :
location_tag 
| location_tags location_tag;

location_tag :
LOCATION_OPEN id_attr OPENTAG_RIGHT loc_tags  LOCATION_CLOSE {
	//check for attributes
	parseContext.idSeen = false;
	//check for tags
	parseContext.nameSeen = false;
	parseContext.rankSeen = false;

	if (!parseContext.typeSeen )
	   error(cubeparserloc,"No type of location group declared."); 
	parseContext.typeSeen = false;
	parseContext.currentLocation = cube.def_location(
	 cube::services::escapeFromXML(parseContext.name),
		parseContext.rank,
		cube::Location::getLocationType(cube::services::escapeFromXML(parseContext.type)),
		parseContext.currentLocationGroup,
		parseContext.id);
    if (parseContext.n_attributes.size() > 0)
    {
        unsigned nattributes = parseContext.n_attributes.top(); 
        parseContext.n_attributes.pop();
        
        if (nattributes > parseContext.attributes.size()) 
        {
        error(cubeparserloc, "Number of saved attributes for location " + parseContext.name + " is more, than number of actual saved parameters.");
        }
        std::stack<std::pair<std::string, std::string> > reversed;
        for (unsigned i=0; i< nattributes; ++i) 
        {
            std::pair< std::string, std::string>  attr = parseContext.attributes.top();
            parseContext.attributes.pop();
            reversed.push(attr);
        }
        for (unsigned i=0; i< nattributes; ++i) 
        {
            std::pair< std::string, std::string>  attr = reversed.top();
            reversed.pop();
            parseContext.currentLocation->def_attr(attr.first, attr.second);
        }  	
    }
		
	while (( unsigned int)parseContext.locVec.size()<=parseContext.currentLocation->get_id())
		parseContext.locVec.push_back(NULL);
	if (parseContext.locVec[parseContext.currentLocation->get_id()]!=NULL)
	  error(cubeparserloc,"Re-declared location!"); 
	parseContext.locVec[parseContext.currentLocation->get_id()] = parseContext.currentLocation;
	if ( parseContext.currentLocation->get_id() % 1024 == 0)
	{
	   std::string _step =  "Created location " + cube::services::escapeFromXML(parseContext.name);
           cube.get_operation_progress()->progress_step( _step );
        }
}
;




machine_tags :
machine_tag
| machine_tags machine_tag
;

machine_tag :
MACHINE_OPEN id_attr OPENTAG_RIGHT name_tag descr_tag_opt {
	//check for attributes
	parseContext.idSeen = false;
	//check for tags
	parseContext.nameSeen = false;
	if (parseContext.descrSeen) parseContext.descrSeen = false;
	else parseContext.descr = "";

	parseContext.currentMachine = cube.def_mach(
	 cube::services::escapeFromXML(parseContext.name),
	 cube::services::escapeFromXML(parseContext.descr));
	while ((unsigned int)parseContext.stnVec.size()<=parseContext.currentMachine->get_id())
		parseContext.stnVec.push_back(NULL);
	if (parseContext.stnVec[parseContext.currentMachine->get_id()]!=NULL)
	  error(cubeparserloc,"Re-declared machine!"); 
	parseContext.stnVec[parseContext.currentMachine->get_id()] = parseContext.currentMachine;
} node_tags MACHINE_CLOSE
;

node_tags :
node_tag
| node_tags node_tag
;

node_tag :
NODE_OPEN id_attr OPENTAG_RIGHT name_tag  descr_tag_opt {
	//check for attributes
	parseContext.idSeen = false;
	//check for tags
	parseContext.nameSeen = false;
    if (parseContext.descrSeen) parseContext.descrSeen = false;
    else parseContext.descr = "";
    
	parseContext.currentNode = cube.def_node(
	 cube::services::escapeFromXML(parseContext.name),
		parseContext.currentMachine);
	while ((unsigned int)parseContext.stnVec.size()<=parseContext.currentNode->get_id())
		parseContext.stnVec.push_back(NULL);
	if (parseContext.stnVec[parseContext.currentNode->get_id()]!=NULL)
	  error(cubeparserloc,"Re-declared node!");
	parseContext.stnVec[parseContext.currentNode->get_id()] = parseContext.currentNode;
} process_tags NODE_CLOSE
;

process_tags :
process_tag
| process_tags process_tag
;

process_tag :
PROCESS_OPEN id_attr OPENTAG_RIGHT tags_of_process  {
	//check for attributes
	parseContext.idSeen = false;
	//check for tags
	if (parseContext.nameSeen) parseContext.nameSeen = false;
	else parseContext.name = "";
	if (parseContext.rankSeen) parseContext.rankSeen = false;
	else parseContext.rank = 0;

	std::ostringstream name;
	if (parseContext.name.empty()) {
	  name << "Process " << parseContext.rank;
	} else {
	  name << parseContext.name;
	}
	parseContext.currentProc = cube.def_proc(
	 cube::services::escapeFromXML(name.str()),
		parseContext.rank,
		parseContext.currentNode);
	while ((unsigned int)parseContext.locGroup.size()<=parseContext.currentProc->get_id())
		parseContext.locGroup.push_back(NULL);
	if (parseContext.locGroup[parseContext.currentProc->get_id()]!=NULL)
	  error(cubeparserloc,"Re-declared process!");
	parseContext.locGroup[parseContext.currentProc->get_id()] = parseContext.currentProc;
} thread_tags PROCESS_CLOSE
;

tags_of_process :
tag_of_process
| tags_of_process tag_of_process;

tag_of_process :
  name_tag 
| rank_tag
;

thread_tags :
thread_tag
| thread_tags thread_tag
;

thread_tag :
THREAD_OPEN id_attr OPENTAG_RIGHT tags_of_process THREAD_CLOSE {
	//check for attributes
	parseContext.idSeen = false;
	//check for tags
	if (parseContext.nameSeen) parseContext.nameSeen = false;
	else parseContext.name = "";
	if (parseContext.rankSeen) parseContext.rankSeen = false;
	else parseContext.rank = 0;

	std::ostringstream name;
	if (parseContext.name.empty()) {
	  name << "Thread " << parseContext.rank;
	} else {
	  name << parseContext.name;
	}
	
	
	parseContext.currentThread = cube.def_thrd(
	 cube::services::escapeFromXML(name.str()),
		parseContext.rank,
		parseContext.currentProc,
		parseContext.id);
	while ((unsigned int)parseContext.locVec.size()<=parseContext.currentThread->get_id()) 
		parseContext.locVec.push_back(NULL);
	if (parseContext.locVec[parseContext.currentThread->get_id()]!=NULL)
	  error(cubeparserloc,"Re-declared thread!"); 
	parseContext.locVec[parseContext.currentThread->get_id()] = parseContext.currentThread;
}
;

topologies_tag_attr :
| topologies_tag
;

topologies_tag :
TOPOLOGIES_OPEN {
	if (!parseContext.checkThreadIds())
	  error(cubeparserloc,"Thread ids must cover an interval [0,n] without gap!"); 
} cart_tags_attr TOPOLOGIES_CLOSE
;

cart_tags_attr :
| cart_tags
;

cart_tags :
cart_tag
| cart_tags cart_tag
;

cart_attrs :
ndims_attr 
| cart_name_attr ndims_attr 
;

cart_tag :
cart_open cart_attrs OPENTAG_RIGHT dim_tags 
{
	//check for attributes
	parseContext.ndimsSeen = false;

	if (parseContext.ndims!=(int)parseContext.dimVec.size())
	  error(cubeparserloc,"Too few or too many topology dimensions are declared!"); 
	parseContext.currentCart = cube.def_cart(
		parseContext.ndims,
		parseContext.dimVec,
		parseContext.periodicVec);

        if (parseContext.cartNameSeen)
	{
            (parseContext.currentCart)->set_name(cube::services::escapeFromXML(parseContext.cartName));
	    parseContext.cartNameSeen=false;
	}
	if(parseContext.dimNamesCount>0)
	{
	    parseContext.dimNamesCount = 0;
	    (parseContext.currentCart)->set_namedims(parseContext.dimNameVec);
	}
	parseContext.dimNameVec.clear();

} coord_tags CART_CLOSE 
;

cart_open :
CART_OPEN {parseContext.dimVec.clear();
	   parseContext.periodicVec.clear();
        parseContext.cartNameSeen=false;
}
;

dim_tags :
  dim_tag 
| dim_tags dim_tag
;

dim_tag :
  DIM_OPEN dim_attributes CLOSETAG_RIGHT {
	//check for attributes
	if (!parseContext.sizeSeen)
	  error(cubeparserloc,"Missing size attribute!"); 
	else parseContext.sizeSeen = false;
	if (!parseContext.periodicSeen)
	  error(cubeparserloc,"Missing periodic attribute!");
	else parseContext.periodicSeen = false;
	if (parseContext.dimNameSeen )
	    parseContext.dimNameVec.push_back(parseContext.dimName); 
	else
	    parseContext.dimNameVec.push_back(""); 
	parseContext.dimNameSeen= false; 
  }
;

dim_attributes :
  dim_attribute
| dim_attributes dim_attribute
;

dim_attribute :
dim_name_attr
|  size_attr 
| periodic_attr
;

coord_tags :
| coord_tags COORD_OPEN coord_tag
;




coord_tag :
coord_tag_thrd
| coord_tag_proc
| coord_tag_node
| coord_tag_mach
| coord_tag_loc
| coord_tag_lg
| coord_tag_stn
;




coord_tag_loc :
locid_attr  OPENTAG_RIGHT COORD_CLOSE {
	//check for attributes
	parseContext.locidSeen = false;

	if (parseContext.dimVec.size()!=parseContext.longValues.size())
	  error(cubeparserloc,"Too few or too many dimension coordinates in coord tag!"); 
	for (unsigned i=0; i<parseContext.dimVec.size(); ++i){
	    if (parseContext.longValues[i]>=parseContext.dimVec[i])
	  error(cubeparserloc,"Topology coordinate is out of range!");
	}
	if (parseContext.locid>=(int)parseContext.locVec.size()) 
	  error(cubeparserloc,"Location of the topology coordinates wasn't declared!"); 
	if (parseContext.locVec[parseContext.locid]==NULL) 
	  error(cubeparserloc,"Location of the topology coordinates wasn't declared!"); 
	cube.def_coords(parseContext.currentCart,
                         (cube::Sysres*)(parseContext.locVec[parseContext.locid]),
                         parseContext.longValues);
}
;

coord_tag_lg :
lgid_attr  OPENTAG_RIGHT COORD_CLOSE {
	//check for attributes
	parseContext.lgidSeen = false;

	if (parseContext.dimVec.size()!=parseContext.longValues.size())
	  error(cubeparserloc,"Too few or too many dimension coordinates in coord tag!"); 
	for (unsigned i=0; i<parseContext.dimVec.size(); ++i){
	    if (parseContext.longValues[i]>=parseContext.dimVec[i])
	  error(cubeparserloc,"Topology coordinate is out of range!"); 
	}
	if (parseContext.lgid>=(int)parseContext.locGroup.size()) 
	  error(cubeparserloc,"Location group of the topology coordinates wasn't declared!"); 
	if (parseContext.locGroup[parseContext.lgid]==NULL) 
	  error(cubeparserloc,"Location group of the topology coordinates wasn't declared!"); 
	cube.def_coords(parseContext.currentCart,
                         (cube::Sysres*)(parseContext.locGroup[parseContext.lgid]),
                         parseContext.longValues);
}
;

coord_tag_stn :
stnid_attr  OPENTAG_RIGHT COORD_CLOSE {
	//check for attributes
	parseContext.stnidSeen = false;

	if (parseContext.dimVec.size()!=parseContext.longValues.size())
	  error(cubeparserloc,"Too few or too many dimension coordinates in coord tag!"); 
	for (unsigned i=0; i<parseContext.dimVec.size(); ++i){
	    if (parseContext.longValues[i]>=parseContext.dimVec[i])
	  error(cubeparserloc,"Topology coordinate is out of range!"); 
	}
	if (parseContext.stnid>=(int)parseContext.stnVec.size()) 
	  error(cubeparserloc,"System tree node of the topology coordinates wasn't declared!"); 
	if (parseContext.nodeVec[parseContext.stnid]==NULL) 
	  error(cubeparserloc,"System tree node of the topology coordinates wasn't declared!"); 
	cube.def_coords(parseContext.currentCart,
                         (cube::Sysres*)(parseContext.nodeVec[parseContext.stnid]),
                         parseContext.longValues);
}
;


coord_tag_thrd :
thrdid_attr  OPENTAG_RIGHT COORD_CLOSE {
	//check for attributes
	parseContext.locidSeen = false;

	if (parseContext.dimVec.size()!=parseContext.longValues.size())
	  error(cubeparserloc,"Too few or too many dimension coordinates in coord tag!"); 
	for (unsigned i=0; i<parseContext.dimVec.size(); ++i){
	    if (parseContext.longValues[i]>=parseContext.dimVec[i])
	  error(cubeparserloc,"Topology coordinate is out of range!");
	}
	if (parseContext.thrdid>=(int)parseContext.locVec.size()) 
	  error(cubeparserloc,"Thread of the topology coordinates wasn't declared!"); 
	if (parseContext.locVec[parseContext.thrdid]==NULL) 
	  error(cubeparserloc,"Thread of the topology coordinates wasn't declared!"); 
	cube.def_coords(parseContext.currentCart,
                         (cube::Sysres*)(parseContext.locVec[parseContext.thrdid]),
                         parseContext.longValues);
}
;

coord_tag_proc :
procid_attr  OPENTAG_RIGHT COORD_CLOSE {
	//check for attributes
	parseContext.lgidSeen = false;

	if (parseContext.dimVec.size()!=parseContext.longValues.size())
	  error(cubeparserloc,"Too few or too many dimension coordinates in coord tag!"); 
	for (unsigned i=0; i<parseContext.dimVec.size(); ++i){
	    if (parseContext.longValues[i]>=parseContext.dimVec[i])
	  error(cubeparserloc,"Topology coordinate is out of range!"); 
	}
	if (parseContext.procid>=(int)parseContext.locGroup.size()) 
	  error(cubeparserloc,"Process of the topology coordinates wasn't declared!"); 
	if (parseContext.locGroup[parseContext.procid]==NULL) 
	  error(cubeparserloc,"Process of the topology coordinates wasn't declared!"); 
	cube.def_coords(parseContext.currentCart,
                         (cube::Sysres*)(parseContext.locGroup[parseContext.procid]),
                         parseContext.longValues);
}
;

coord_tag_node :
nodeid_attr  OPENTAG_RIGHT COORD_CLOSE {
	//check for attributes
	parseContext.stnidSeen = false;

	if (parseContext.dimVec.size()!=parseContext.longValues.size())
	  error(cubeparserloc,"Too few or too many dimension coordinates in coord tag!"); 
	for (unsigned i=0; i<parseContext.dimVec.size(); ++i){
	    if (parseContext.longValues[i]>=parseContext.dimVec[i])
	  error(cubeparserloc,"Topology coordinate is out of range!"); 
	}
	
	if (parseContext.nodeid >= (int)cube.get_non_root_stnv().size()) 
	  error(cubeparserloc,"Node of the topology coordinates wasn't declared!"); 
	if (cube.get_non_root_stnv().at(parseContext.nodeid)==NULL) 
	  error(cubeparserloc,"Node of the topology coordinates wasn't declared!"); 
	cube.def_coords(parseContext.currentCart,
                         (cube::Sysres*)(cube.get_non_root_stnv().at(parseContext.nodeid)),
                         parseContext.longValues);
}
;

coord_tag_mach :
machid_attr  OPENTAG_RIGHT COORD_CLOSE {
	//check for attributes
	parseContext.stnidSeen = false;

	if (parseContext.dimVec.size()!=parseContext.longValues.size())
	  error(cubeparserloc,"Too few or too many dimension coordinates in coord tag!"); 
	for (unsigned i=0; i<parseContext.dimVec.size(); ++i){
	    if (parseContext.longValues[i]>=parseContext.dimVec[i])
	  error(cubeparserloc,"Topology coordinate is out of range!"); 
	}
	if (parseContext.machid>=(int)cube.get_root_stnv().size()) 
	  error(cubeparserloc,"Machine of the topology coordinates wasn't declared!"); 
	if (cube.get_root_stnv().at(parseContext.nodeid)==NULL) 
	  error(cubeparserloc,"Machine of the topology coordinates wasn't declared!"); 
	cube.def_coords(parseContext.currentCart,
                         (cube::Sysres*)(cube.get_root_stnv().at(parseContext.machid)),
                         parseContext.longValues);
}
;


/*** severity tag ***/

severity_tag :
 | severity_part ;

severity_part :
SEVERITY_OPEN {
// if (parseContext.dynamicMetricLoading) return 0;
std::string _step = "Start reading data";
cube.get_operation_progress()->progress_step( _step );
} matrix_tags SEVERITY_CLOSE
{
cube.get_operation_progress()->finish_step("Finished reading data");
}
;

matrix_tags :
/* empty */
| matrix_tags matrix_tag
;


matrix_tag :
MATRIX_OPEN metricid_attr OPENTAG_RIGHT {
	//check for attributes
	parseContext.metricidSeen = false;

	if ((int)parseContext.metricVec.size()<=parseContext.metricid)
	  error(cubeparserloc,"Metric of the severity matrix wasn't declared!"); 
	if (parseContext.metricVec[parseContext.metricid]==NULL)
	  error(cubeparserloc,"Metric of the severity matrix wasn't declared!");
	parseContext.currentMetric = 
		parseContext.metricVec[parseContext.metricid];

	parseContext.ignoreMetric = false;
        cube::Metric* metric = parseContext.currentMetric;
        while (metric!=NULL) {
    		if (metric->get_val() == "VOID") {
      		  parseContext.ignoreMetric = true;
      		  break;
    		}
    		metric = metric->get_parent();
  	}
} row_tags_attr MATRIX_CLOSE
;

row_tags_attr :
|row_tags
;

row_tags :
row_tag
| row_tags row_tag
;

row_tag :
ROW_OPEN cnodeid_attr OPENTAG_RIGHT {
	//check for attributes
	parseContext.cnodeidSeen = false;

	if (!parseContext.ignoreMetric){
		if ((int)parseContext.cnodeVec.size()<=parseContext.cnodeid)
		  error(cubeparserloc,"Cnode of the severity row wasn't declared!");
		if (parseContext.cnodeVec[parseContext.cnodeid]==NULL)
		  error(cubeparserloc,"Cnode of the severity row wasn't declared!"); 
		parseContext.currentCnode = 
			parseContext.cnodeVec[parseContext.cnodeid];
	}
} ROW_CLOSE {
	if (!parseContext.ignoreMetric)
    {
	  	std::vector<double> & v = parseContext.realValues;
		std::vector<cube::Thread*> & t = parseContext.locVec;
        if (v.size()>t.size())	
                error(cubeparserloc,"Too many values in severity row!"); 
        std::vector<cube::Thread*> t_sorted = t;
        sort(t_sorted.begin(), t_sorted.end(), &cube::IdentObject::id_compare);

    
		cube::Metric* metric = parseContext.currentMetric;
		cube::Cnode * cnode = parseContext.currentCnode;
        for (unsigned i=0; i<v.size(); ++i)
        {
            cube.set_sev(metric,
                            cnode,
                            t_sorted[i],
                            v[i]);
        }
	}
}
;



%% /*** Additional Code ***/


void cubeparser::Cube4Parser::error(const Cube4Parser::location_type& l,
			    const std::string& m)
{
   if (strstr(m.c_str(),"expecting <?xml")!=NULL) {
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

}




