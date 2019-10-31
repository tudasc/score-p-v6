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



#ifndef REMAPPARSECONTEXT_H
#define REMAPPARSECONTEXT_H

#include <sstream>
#include <vector>
#include <utility>
#include <stack>
#include "Cube.h"

class ReMapParseContext
{
public:

    typedef enum { STRINGCONTENT, INTCONTENT, BOOLCONTENT, CUBEPLAGGREGATIONCONTENT } ContentType;
    typedef enum { CUBEPL_AGGR_PLUS, CUBEPL_AGGR_MINUS, CUBEPL_AGGR_AGGR }            CubePlAggregationType;

    bool dynamicMetricLoading;

    std::vector<long>        dimVec;
    std::vector<bool>        periodicVec;
    std::vector<std::string> dimNameVec;
    std::string              dimName;
    int                      dimNamesCount;

    std::vector<cube::Region*>  regionVec;
    std::vector<cube::Metric*>  metricVec;
    std::vector<cube::Cnode*>   cnodeVec;
    std::vector<cube::Thread*>  threadVec;
    std::vector<cube::Process*> procVec;
    std::vector<cube::Node*>    nodeVec;
    std::vector<cube::Machine*> machVec;
    std::vector<cube::Sysres*>  systemVec;
    std::vector<std::string>    moduleVec;
    std::vector<long>           csiteVec;


    std::stack<unsigned>                             n_cnode_str_parameters; // /< Saves as a stack the number of the parameters for current cnode during parsing;
    std::stack<std::pair<std::string, std::string> > cnode_str_parameters;   // /< Saves as a stack the parameters for current cnode during parsing;

    std::stack<unsigned>                             n_cnode_num_parameters; // /< Saves as a stack the number of the parameters for current cnode during parsing;
    std::stack<std::pair<std::string, std::string> > cnode_num_parameters;   // /< Saves as a stack the parameters for current cnode during parsing;

    cube::Machine*   currentMachine;
    cube::Node*      currentNode;
    cube::Process*   currentProc;
    cube::Thread*    currentThread;
    cube::Cnode*     currentCnode;
    cube::Cartesian* currentCart;
    cube::Metric*    currentMetric;

    int  cubeVersion;
    bool ignoreMetric;                                             // in severity it stores if the current metric or one of its parents have
                                                                   // the type VOID and thus can be ignored
    bool realContent;
    bool longContent;
    bool generalContent;
    bool stringContent;
    bool parseCnodeParameters;

    ContentType           contentType;
    CubePlAggregationType cubeplAggrType;

    std::vector<double>      realValues;
    std::vector<long>        longValues;
    std::vector<std::string> generalValues;
    std::ostringstream       str;

    std::string version;
    std::string encoding;
    std::string key;
    std::string value;
    std::string mod;
    std::string murl;
    std::string disp_name;
    std::string uniq_name;
    std::string dtype;
    std::string uom;
    std::string val;
    std::string url;
    std::string descr;
    std::string name;
    std::string metricType;
    std::string metricVizType;
    std::string expression;
    std::string expressionInit;
    std::string expressionAggrPlus;
    std::string expressionAggrMinus;
    std::string expressionAggrAggr;


    std::string cnode_parameter_key;
    std::string cnode_parameter_value;
    std::string cnode_parameter_type;

    std::string cartName;
    std::string statName;
    std::string metricsTitle;
    std::string calltreeTitle;
    std::string systemtreeTitle;



    int  id, calleeid, thrdid, metricid, cnodeid, rank;
    int  procid, nodeid, machid;
    int  moduleid, calleenr, csiteid, locid;
    long beginln, endln, line, ndims;
    long longAttribute;

    bool idSeen,  metricTypeSeen, metricVizTypeSeen, calleeidSeen, lineSeen, modSeen;
    bool beginSeen, endSeen, periodicSeen, ndimsSeen;
    bool sizeSeen, cnodeidSeen, metricidSeen, machidSeen;
    bool nodeidSeen, procidSeen, thrdidSeen, valueSeen;
    bool keySeen, encodingSeen, versionSeen;
    bool metricConvertibleSeen, metricCacheableSeen;


    bool dispnameSeen, uniqnameSeen, dtypeSeen;
    bool uomSeen, valSeen, urlSeen, descrSeen;
    bool murlSeen, nameSeen, rankSeen;

    bool expressionSeen, expressionInitSeen;
    bool expressionAggrPlusSeen, expressionAggrMinusSeen, expressionAggrAggrSeen;


    bool cnodeParKeySeen, cnodeParTypeSeen, cnodeParValueSeen;
    bool cartNameSeen;
    bool dimNameSeen;
    bool statNameSeen, statSeen;
    bool metricsTitleSeen, calltreeTitleSeen, systemtreeTitleSeen;

    bool cubeplTypeSeen, rowwise, metricConvertible;
    bool metricCacheable;

    ReMapParseContext()
    {
        dynamicMetricLoading = false;

        realContent    = false;
        longContent    = false;
        generalContent = false;
        stringContent  = false;
        contentType    = STRINGCONTENT;

        currentMachine = NULL;
        currentNode    = NULL;
        currentProc    = NULL;
        currentThread  = NULL;
        currentCnode   = NULL;
        currentCart    = NULL;
        currentMetric  = NULL;
        cubeVersion    = 0;

        ignoreMetric = false;

        idSeen            = false;
        metricTypeSeen    = false;
        metricVizTypeSeen = false;
        calleeidSeen      = false;
        lineSeen          = false;
        modSeen           = false;
        beginSeen         = false;
        endSeen           = false;
        periodicSeen      = false;
        ndimsSeen         = false;
        sizeSeen          = false;
        cnodeidSeen       = false;
        metricidSeen      = false;
        machidSeen        = false;
        nodeidSeen        = false;
        procidSeen        = false;
        thrdidSeen        = false;
        valueSeen         = false;
        keySeen           = false;
        encodingSeen      = false;
        versionSeen       = false;

        dispnameSeen = false;
        uniqnameSeen = false;
        dtypeSeen    = false;
        uomSeen      = false;
        valSeen      = false;
        urlSeen      = false;
        descrSeen    = false;
        murlSeen     = false;
        nameSeen     = false;
        rankSeen     = false;

        expressionSeen          = false;
        expressionInitSeen      = false;
        expressionAggrPlusSeen  = false;
        expressionAggrMinusSeen = false;
        expressionAggrAggrSeen  = false;
        cubeplTypeSeen          = false;
        rowwise                 = true;

        cnodeParTypeSeen  = false;
        cnodeParKeySeen   = false;
        cnodeParValueSeen = false;

        cartNameSeen = false;
        dimNameSeen  = false;
        dimName.clear();
        dimNameVec.clear();
        dimNamesCount = 0;

        statNameSeen = false;
        statSeen     = false;

        metricsTitleSeen    = false;
        calltreeTitleSeen   = false;
        systemtreeTitleSeen = false;

        metricConvertibleSeen = false;
        metricConvertible     = true;
    }

    ~ReMapParseContext()
    {
    }

    bool
    checkThreadIds()
    {
        for ( unsigned i = 0; i < threadVec.size(); i++ )
        {
            if ( threadVec[ i ] == NULL )
            {
                return false;
            }
        }
        return true;
    }
};


#endif // PARSECONTEXT_H
