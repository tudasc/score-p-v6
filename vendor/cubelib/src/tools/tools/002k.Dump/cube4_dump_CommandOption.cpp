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


#include "config.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <fstream>

#include "cube4_dump_CommandOption.h"


using namespace std;
void
parseMetrics( string _optarg, vector<string>& metric, cube::Cube*   )
{
    string::iterator it;
    string           temp;

    for ( it = _optarg.begin(); it != _optarg.end(); ++it )
    {
        if ( ( *it ) != ',' )
        {
            temp += ( *it );
        }
        else if ( !temp.empty() )
        {
            metric.push_back( temp );
            temp.clear();
        }
    }
    if ( !temp.empty() )
    {
        metric.push_back( temp );
    }
    return;
}

void
parseNewMetric( vector<string>& newmetricv, vector<string>& metric, bool& check_all, cube::Cube*   _cube )
{
    string        _optarg;
    int           count = 0;
    cube::Metric* met;
    while ( !newmetricv.empty() )
    {
        _optarg = newmetricv.back();
        newmetricv.pop_back();
        if ( _optarg == "all" )
        {
            check_all |= true;
            continue;
        }

        met = _cube->get_met( _optarg );
        if ( met != NULL )
        {
            metric.push_back( _optarg );
            continue;
        }



        std::string _to_test      = std::string( "<cubepl>" ) + _optarg + std::string( "</cubepl>" );
        std::string error_message = "";


        cube::Metric* created_metric = NULL;

        cubeplparser::CubePLDriver* _driver = _cube->get_cubepl_driver();
        if ( _driver->test( _to_test, error_message ) ) // direct a metric
        {
            count++;
            string            s = "New Metric";
            std::stringstream ss;
            ss << count;
            s.append( ss.str() );
            created_metric = _cube->def_met(
                s, s, "DOUBLE", "",
                "",
                "",
                "",
                NULL,
                cube::CUBE_METRIC_POSTDERIVED, // CUBE_INCLUSIVE
                _optarg,
                "" );
            metric.push_back( s );
        }
        else
        {
            size_t i = 0;
            while ( i < _optarg.size() && _optarg[ i ] != ':' ) // name:expression
            {
                i++;
            }
            if ( i < _optarg.size() )
            {
                string _name    = _optarg.substr( 0, i );
                string _optarg1 = _optarg.substr( i + 1 );

                std::string _to_test      = std::string( "<cubepl>" ) + _optarg1 + std::string( "</cubepl>" );
                std::string error_message = "";
                if ( _driver->test( _to_test, error_message ) )
                {
                    created_metric = _cube->def_met(
                        _name, _name, "DOUBLE", "",
                        "",
                        "",
                        "",
                        NULL,
                        cube::CUBE_METRIC_POSTDERIVED, // CUBE_INCLUSIVE
                        _optarg1,
                        "" );
                    metric.push_back( _name );
                }
            }
            else     // filename
            {
                ifstream in;
                in.open( _optarg.c_str(), ios::in );
                string cubepl;
                if ( in.good() )
                {
                    string line;
                    while ( !in.eof() )
                    {
                        in >> line;
                        cubepl += line;
                        line    = "";
                    }
                    in.close();
                }

                if ( cubepl.size() > 0 )
                {
                    string      _name         = _optarg;
                    std::string _to_test      = std::string( "<cubepl>" ) + cubepl + std::string( "</cubepl>" );
                    std::string error_message = "";
                    if ( _driver->test( _to_test, error_message ) )
                    {
                        created_metric = _cube->def_met(
                            _name, _name, "DOUBLE", "",
                            "",
                            "",
                            "",
                            NULL,
                            cube::CUBE_METRIC_POSTDERIVED,     // CUBE_INCLUSIVE
                            cubepl,
                            "" );
                        metric.push_back( _name );
                    }
                    else
                    {
                        cerr << "Cannot create metric. Please check the formula." << endl;
                    }
                }
            }
        }
        if ( !check_all && created_metric == NULL )
        {
            cout << "sorry we can not create metric: " << error_message <<  endl;
        }
    }
}

bool
parseCallPaths_Threads( string _optarg, vector<unsigned>& call_id )
{
    string::iterator it;
    unsigned         temp;
    string           temps;

    unsigned first = 0, last = 0;
    bool     flag  = false;

    for ( it = _optarg.begin(); it != _optarg.end(); ++it )
    {
        if ( ( *it ) != ',' )
        {
            if ( ( *it ) == '-' )
            {
                first = atoi( temps.c_str() );
                flag  = true;
                temps.clear();
            }
            else
            {
                temps += ( *it );
            }
        }
        else if ( !temps.empty() )
        {
            if ( flag == false )
            {
                if ( from_string<unsigned>( temp, temps, std::dec ) )
                {
                    call_id.push_back( temp );
                }
            }
            else
            {
                last = atoi( temps.c_str() );
                for ( unsigned i = first; i <= last; i++ )
                {
                    call_id.push_back( i );
                }
                flag = false;
            }
            temps.clear();
        }
    }
    if ( !temps.empty() )
    {
        if ( flag == false )
        {
            if ( from_string<unsigned>( temp, temps, std::dec ) )
            {
                call_id.push_back( temp );
            }
        }
        else
        {
            last = atoi( temps.c_str() );
            for ( unsigned i = first; i <= last; i++ )
            {
                call_id.push_back( i );
            }
            flag = false;
        }
        temps.clear();
    }
    return call_id.size() != 0;
}


bool
parseCubePlCnodeCondition( string  _optarg,
                           string& cubepl )
{
    if ( _optarg.compare( "roots" ) == 0 )
    {
        cubepl =
            "{ "
            "  ${a}=0;"
            "  if (${cube::callpath::parent::id}[${calculation::callpath::id}] == -1 )"
            "  { ${a}=1; }; return ${a}; "
            "}";
        return true;
    }
    else if ( _optarg.compare( "leafs" ) == 0 )
    {
        cubepl =
            "{ "
            "  ${a}=0;"
            "  if (${cube::callpath::#children}[${calculation::callpath::id}] == 0 )"
            "  { ${a}=1; }; return ${a}; "
            "}";
        return true;
    }
    else if ( _optarg.compare( 0, 6, "level=" ) == 0 )
    {
        string _sub_arg  = _optarg.substr( 6 );
        string _argument = fakeNumberCheck( _sub_arg );
        cubepl =
            "{ "
            "  ${level}=" + _argument + ";"
            "  ${index}=0;"
            "  ${i}=${calculation::callpath::id};"
            "  while (${cube::callpath::parent::id}[${i}] != -1 )"
            "  { ${i}= ${cube::callpath::parent::id}[${i}]; ${index}=${index}+1; }; "
            "  ${a}=0;"
            "  if (${index} == ${level})"
            "  { ${a}=1; };"
            "  return ${a}; "
            "}";
        return true;
    }
    else if ( _optarg.compare( 0, 6, "level<" ) == 0 )
    {
        string _sub_arg  = _optarg.substr( 6 );
        string _argument = fakeNumberCheck( _sub_arg );
        cubepl =
            "{ "
            "  ${level}=" + _argument + ";"
            "  ${index}=0;"
            "  ${i}=${calculation::callpath::id};"
            "  while (${cube::callpath::parent::id}[${i}] != -1 )"
            "  { ${i}= ${cube::callpath::parent::id}[${i}]; ${index}=${index}+1; }; "
            "  ${a}=0;"
            "  if (${index} < ${level})"
            "  { ${a}=1; };"
            "  return ${a}; "
            "}";
        return true;
    }
    else if ( _optarg.compare( 0, 6, "level>" ) == 0 )
    {
        string _sub_arg  = _optarg.substr( 6 );
        string _argument = fakeNumberCheck( _sub_arg );
        cubepl =
            "{ "
            "  ${level}=" + _argument + ";"
            "  ${index}=0;"
            "  ${i}=${calculation::callpath::id};"
            "  while (${cube::callpath::parent::id}[${i}] != -1 )"
            "  { ${i}= ${cube::callpath::parent::id}[${i}]; ${index}=${index}+1; }; "
            "  ${a}=0;"
            "  if (${index} > ${level})"
            "  { ${a}=1; };"
            "  return ${a}; "
            "}";
        return true;
    }
    else if ( _optarg.compare( 0, 6, "name=/" ) == 0 )
    {
        string _sub_arg = _optarg.substr( 6, _optarg.length() - 7 );
        cubepl =
            "{ "
            "  ${a}=0;"
            "   if ( ${cube::region::name}[${calculation::region::id}] =~  /" + _sub_arg + "/ )"
            "  { ${a}=1; }; return ${a}; "
            "}";
        return true;
    }
    else     // no shortcuts ...must be file  name
    {
        ifstream in;
        in.open( _optarg.c_str(), ios::in );
        string line;
        while ( !in.eof() )
        {
            in >> line;
            cubepl += line;
        }
        in.close();
        return true;
    }
}



string
fakeNumberCheck( string& input )
{
    stringstream sstr1;
    string       output;
    unsigned     as_number;
    sstr1 << input;
    sstr1 >> as_number;
    sstr1.flush();
    sstr1 << as_number;
    return sstr1.str();
}



void
cnodeSelection( cube::Cube* cube, std::string& cnode_cond_cubepl, std::vector<unsigned>& cnode_idv )
{
    cube::Metric* _selection_metric =
        cube->def_met( "__cnode_selection", "__cnode_selection", "DOUBLE", "",
                       "",
                       "",
                       "",
                       NULL,
                       cube::CUBE_METRIC_POSTDERIVED,     // CUBE_INCLUSIVE
                       cnode_cond_cubepl,
                       "",
                       "",
                       "",
                       "",
                       true,
                       cube::CUBE_METRIC_GHOST );
    std::vector<cube::Cnode*> _cnodes = cube->get_cnodev();
    for ( std::vector<cube::Cnode*>::iterator _citer = _cnodes.begin(); _citer != _cnodes.end(); ++_citer )
    {
        cube::Cnode* _cnode  = *_citer;
        double       _result = cube->get_sev( _selection_metric, cube::CUBE_CALCULATE_INCLUSIVE,  _cnode, cube::CUBE_CALCULATE_INCLUSIVE );
        if ( _result > 0 )
        {
            cnode_idv.push_back( _cnode->get_id() );
        }
    }
}
