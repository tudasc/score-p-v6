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
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>


#include "cube4_dump_Printer.h"


using namespace cube;
using namespace std;

void
Printer::print_header( const string& data, const bool show_ghost, const bool selected_data, const bool show_coords )
{
    const std::vector<Metric*>&               root_metrics       = cube->get_root_metv();
    const std::vector<Metric*>&               root_ghost_metrics = cube->get_ghost_metv();
    const std::vector<Region*>&               regnv              = cube->get_regv();
    const std::vector<Cnode*>&                root_cnodes        = cube->get_root_cnodev();
    const std::vector<SystemTreeNode*>&       root_stnv          = cube->get_root_stnv();
    const std::vector<Cartesian*>&            cartv              = cube->get_cartv();
    const std::map<std::string, std::string>& attrs              = cube->get_attrs();
    const std::vector<std::string>&           mirrors            = cube->get_mirrors();

    fout << endl << endl << " =============== CUBE ATTRIBUTES ============= " << endl;
    dump_cube_attributes( attrs );

    fout << endl << endl << " =============== CUBE MIRRORS ============= " << endl;
    dump_cube_mirrors( mirrors );

    fout << endl << endl << " =============== METRIC DIMENSION ============= " << endl;
    dump_metric_dimension( root_metrics );
    if ( show_ghost )
    {
        fout << endl << endl << " =============== GHOST METRICS ============= " << endl;
        dump_metric_dimension( root_ghost_metrics );
    }


    fout << endl << endl << " =============== CALLTREE DIMENSION ============= " << endl;
    dump_calltree_dimension( regnv, root_cnodes );

    fout << endl << endl << " =============== SYSTEM DIMENSION ============= " << endl;
    dump_system_dimension( root_stnv );
    fout << endl << endl << " =============== TOPOLOGIES ============= " << endl;
    dump_topologies( cartv, show_coords );
    fout << endl << endl << " =============== FILES ============= " << endl;
    dump_misc_data( data, selected_data );
}





bool
Printer::is_bit_set( bitstring_t& bits, unsigned bitnum )
{
    unsigned bytenum = bitnum  / 64; // get a byte in the bite string
    unsigned bit     = bitnum % 64;  //
    unsigned i       = bits.size();
    while ( i++ <= bitnum )
    {
        bits.push_back( 0x0000000000000000 );
    }
    uint64_t byte     = bits[ bytenum ];
    uint64_t testbyte = 0x0000000000000001 << ( 64 - bit );
    return ( testbyte & byte ) == testbyte;
}


void
Printer::set_bit( bitstring_t& bits, unsigned bitnum )
{
    unsigned bytenum = bitnum  / 64; // get a byte in the bite string
    unsigned bit     = bitnum % 64;  //
    unsigned i       = bits.size();
    while ( i++ <= bitnum )
    {
        bits.push_back( 0x0000000000000000 );
    }
    uint64_t testbyte = 0x0000000000000001 << ( 64 - bit );
    bits[ bytenum ] = bits[ bytenum ] | testbyte;
}




void
Printer::dump_metric( Metric* metric, int level, bitstring_t childrenmarkers )
{
    string indent = "";
    for ( int i = 0; i < level; ++i )
    {
        if ( is_bit_set( childrenmarkers, i ) )
        {
            indent += string( "|" );
        }
        indent += string( "  " );
    }

    if ( level > 0 )
    {
        fout << indent << "|-";
    }
    fout << metric->get_disp_name();
    fout << "  ( id=";
    fout << metric->get_filed_id() << ", ";
    fout << metric->get_uniq_name() << ", ";
    fout << metric->get_uom() << ", ";
    fout << metric->get_dtype() << ", ";
    fout << metric->get_url() << ", ";
    fout << metric->get_descr() << ", ";
    fout << metric->get_metric_kind();

    if ( metric->get_type_of_metric() == CUBE_METRIC_POSTDERIVED || metric->get_type_of_metric() == CUBE_METRIC_PREDERIVED_INCLUSIVE || metric->get_type_of_metric() == CUBE_METRIC_PREDERIVED_EXCLUSIVE  )
    {
        fout << ", \"" << metric->get_expression() << "\"";
        fout << ", \"" << metric->get_init_expression() << "\"";
        if ( metric->get_type_of_metric() == CUBE_METRIC_PREDERIVED_EXCLUSIVE || metric->get_type_of_metric() == CUBE_METRIC_PREDERIVED_INCLUSIVE )
        {
            fout << ", \"" << metric->get_aggr_plus_expression() << "\"";
        }
        if ( metric->get_type_of_metric() == CUBE_METRIC_PREDERIVED_INCLUSIVE )
        {
            fout << ", \"" << metric->get_aggr_minus_expression() << "\"";
        }
        fout << ", \"" << metric->get_aggr_aggr_expression() << "\", ";
    }
    fout << ( metric->isConvertible() ? " convertible" : " non convertible" ) << ", " << ( ( metric->isCacheable() ? "cacheable" : "non cacheable" ) );
    fout << ")" << endl;

    std::map<std::string, std::string>attrs = metric->get_attrs();
    if ( attrs.size() != 0 )
    {
        map<string, string>::const_iterator ai;
        for ( ai = attrs.begin(); ai != attrs.end(); ++ai )
        {
            if ( level > 0 )
            {
                fout << indent << "|-";
            }
            fout << "  Attribute: " << "\"" << services::escapeToXML( ai->first ) << "\"->\"" << services::escapeToXML( ai->second ) << "\"" << endl;
        }
    }
    for ( unsigned i = 0; i < metric->num_children(); ++i )
    {
        bitstring_t _last_child_marker = childrenmarkers;
        if ( i < metric->num_children() - 1 )
        {
            set_bit( _last_child_marker, level + 1 );
        }
        dump_metric( metric->get_child( i ), level + 1, _last_child_marker );
    }
}




void
Printer::dump_region( Region* region )
{
    cout << '\t' << region->get_name();
    cout << ':' << region->get_mangled_name();
    cout << '\t'  << "   ( id=";
    cout << region->get_id() << ", ";
    cout << region->get_begn_ln() << ", ";
    cout << region->get_end_ln() << ", ";
    cout << "paradigm=" << region->get_paradigm() << ", ";
    cout << "role=" << region->get_role() << ", ";
    cout << "url=" << region->get_url() << ", ";
    cout << "descr=" << region->get_descr() << ", ";
    cout << "mod=" << region->get_mod();
    cout << ")" << endl;

    std::map<std::string, std::string>attrs = region->get_attrs();
    if ( attrs.size() != 0 )
    {
        map<string, string>::const_iterator ai;
        for ( ai = attrs.begin(); ai != attrs.end(); ++ai )
        {
            fout << "\t\t   Attribute: " << "\"" << services::escapeToXML( ai->first ) << "\"->\"" << services::escapeToXML( ai->second ) << "\"" << endl;
        }
    }
}


void
Printer::dump_cnode( Cnode* cnode, int level, bitstring_t childrenmarkers )
{
    string indent = "";
    for ( int i = 0; i < level; ++i )
    {
        if ( is_bit_set( childrenmarkers, i ) )
        {
            indent += string( "|" );
        }
        indent += string( "  " );
    }

    if ( level > 0 )
    {
        fout << indent << "|-";
    }

    fout << cnode->get_callee()->get_name();
    fout << "  [ ( id=";
    fout << cnode->get_id() << ", ";
    fout << "  mod=";
    fout << cnode->get_mod() << "), ";
    fout << cnode->get_callee()->get_begn_ln() << ", ";
    fout << cnode->get_callee()->get_end_ln() << ", ";
    fout << "paradigm=" << cnode->get_callee()->get_paradigm() << ", ";
    fout << "role=" << cnode->get_callee()->get_role() << ", ";
    fout << "url=" << cnode->get_callee()->get_url() << ", ";
    fout << "descr=" << cnode->get_callee()->get_descr() << ", ";
    fout << "mode=" << cnode->get_callee()->get_mod();
    fout << "]" << endl;
    std::map<std::string, std::string>attrs = cnode->get_attrs();
    if ( attrs.size() != 0 )
    {
        map<string, string>::const_iterator ai;
        for ( ai = attrs.begin(); ai != attrs.end(); ++ai )
        {
            if ( level > 0 )
            {
                fout << indent << "|";
            }
            fout <<  "     Attribute: " << "\"" << services::escapeToXML( ai->first ) << "\"->\"" << services::escapeToXML( ai->second ) << "\"" << endl;
        }
    }
    std::vector < std::pair < std::string, double> > num_params = cnode->get_num_parameters();
    if ( num_params.size() != 0 )
    {
        std::vector < std::pair < std::string, double> >::const_iterator np;
        for ( np = num_params.begin(); np != num_params.end(); ++np )
        {
            if ( level > 0 )
            {
                fout << indent << "|";
            }
            fout <<  "     Parameter (num): " << "\"" << services::escapeToXML( np->first ) << "\"->\"" << np->second  << "\"" << endl;
        }
    }
    std::vector < std::pair  <std::string, std::string> > str_params = cnode->get_str_parameters();
    if ( str_params.size() != 0 )
    {
        std::vector < std::pair < std::string, std::string> >::const_iterator sp;
        for ( sp = str_params.begin(); sp != str_params.end(); ++sp )
        {
            if ( level > 0 )
            {
                fout << indent << "|";
            }
            fout <<  "     Parameter (str): " << "\"" << services::escapeToXML( sp->first ) << "\"->\"" << sp->second  << "\"" << endl;
        }
    }
    for ( unsigned i = 0; i < cnode->num_children(); ++i )
    {
        bitstring_t _last_child_marker = childrenmarkers;
        if ( i < cnode->num_children() - 1 )
        {
            set_bit( _last_child_marker, level + 1 );
        }
        dump_cnode( cnode->get_child( i ), level + 1, _last_child_marker );
    }
}



void
Printer::dump_location( Location* location, int level, bitstring_t childrenmarkers )
{
    string indent = "";
    for ( int i = 0; i < level; ++i )
    {
        if ( is_bit_set( childrenmarkers, i ) )
        {
            indent += string( "|" );
        }
        indent += string( "  " );
    }


    fout << indent << "|-"  << location->get_name() << " (id=" << location->get_id() << ", type=" << location->get_type_as_string() << ", rank=" << location->get_rank() << ")" << endl;
    std::map<std::string, std::string>attrs = location->get_attrs();
    if ( attrs.size() != 0 )
    {
        map<string, string>::const_iterator ai;
        for ( ai = attrs.begin(); ai != attrs.end(); ++ai )
        {
            fout <<  indent << "|      Attribute: " << "\"" << services::escapeToXML( ai->first ) << "\"->\"" << services::escapeToXML( ai->second ) << "\"" << endl;
        }
    }

/*  for (unsigned i=0; i<process->num_children(); ++i)
    dump_thread(process->get_child(i), level+1);*/
}





void
Printer::dump_location_group( LocationGroup* lg, int level, bitstring_t childrenmarkers )
{
    string indent = "";
    for ( int i = 0; i < level; ++i )
    {
        if ( is_bit_set( childrenmarkers, i ) )
        {
            indent += string( "|" );
        }
        indent += string( "  " );
    }

    fout << indent << "|-"  << lg->get_name() << " (id=" << lg->get_id() << ", type=" << lg->get_type_as_string() << ", rank=" << lg->get_rank() << " )" << endl;
    std::map<std::string, std::string>attrs = lg->get_attrs();
    if ( attrs.size() != 0 )
    {
        map<string, string>::const_iterator ai;
        for ( ai = attrs.begin(); ai != attrs.end(); ++ai )
        {
            fout <<  indent << "|       Attribute: " << "\"" << services::escapeToXML( ai->first ) << "\"->\"" << services::escapeToXML( ai->second ) << "\"" << endl;
        }
    }
    for ( unsigned i = 0; i < lg->num_children(); ++i )
    {
        bitstring_t _last_child_marker = childrenmarkers;
        if ( i < lg->num_children() - 1 )
        {
            set_bit( _last_child_marker, level + 1 );
        }
        dump_location( lg->get_child( i ), level + 1, _last_child_marker );
    }
}




void
Printer::dump_stn( SystemTreeNode* stn, int level, bitstring_t childrenmarkers )
{
    string indent = "";
    for ( int i = 0; i < level; ++i )
    {
        if ( is_bit_set( childrenmarkers, i ) )
        {
            indent += string( "|" );
        }
        indent += string( "  " );
        if ( i == level - 1 )
        {
            indent += string( "|-" );
        }
    }

    fout << indent << stn->get_name() << " (id=" << stn->get_id() << ", class=" << stn->get_class() << ", description="  << stn->get_desc() << " )" << endl;
    std::map<std::string, std::string>attrs = stn->get_attrs();
    if ( attrs.size() != 0 )
    {
        map<string, string>::const_iterator ai;
        for ( ai = attrs.begin(); ai != attrs.end(); ++ai )
        {
            fout <<  indent << "|       Attribute: " << "\"" << services::escapeToXML( ai->first ) << "\"->\"" << services::escapeToXML( ai->second ) << "\"" << endl;
        }
    }
    for ( unsigned i = 0; i < stn->num_groups(); ++i )
    {
        bitstring_t _last_child_marker = childrenmarkers;
        if ( i < stn->num_groups() - 1 )
        {
            set_bit( _last_child_marker, level + 1 );
        }
        dump_location_group( stn->get_location_group( i ), level + 1, _last_child_marker );
    }
    for ( unsigned i = 0; i < stn->num_children(); ++i )
    {
        bitstring_t _last_child_marker = childrenmarkers;
        if ( i < stn->num_children() - 1 )
        {
            set_bit( _last_child_marker, level + 1 );
        }
        dump_stn( stn->get_child( i ), level + 1, _last_child_marker );
    }
}




void
Printer::dump_cube_attributes( const std::map<std::string, std::string>& attrs ) const
{
    size_t                                             max_width_keys = 0;
    std::map<std::string, std::string>::const_iterator iter           = attrs.begin();
    for (; iter != attrs.end(); ++iter )
    {
        if ( ( *iter ).first.length() > max_width_keys )
        {
            max_width_keys = ( *iter ).first.length();
        }
    }

    for ( iter = attrs.begin(); iter != attrs.end(); ++iter )
    {
        fout << ( *iter ).first;
        size_t i = ( *iter ).first.length();
        while ( ++i <= max_width_keys + 1 )
        {
            fout << ' ';
        }
        fout << ": " << ( *iter ).second;
        fout << endl;
    }
}



void
Printer::dump_cube_mirrors( const std::vector<std::string>& mirrors ) const
{
    std::vector<std::string>::const_iterator iter = mirrors.begin();
    int                                      i    = 0;
    for (; iter != mirrors.end(); ++iter )
    {
        fout << "Mirror " << ++i << " : " << ( *iter ) << endl;
        ;
    }
}

void
Printer::dump_misc_data( std::string dataname, bool selected_data ) const
{
    std::vector<std::string>stored_data = cube->get_misc_data();
    if ( selected_data )
    {
        bool found = false;
        ;
        std::vector<std::string>::iterator iter = stored_data.begin();
        while ( iter != stored_data.end() && *iter != dataname )
        {
            ++iter;
        }

        found = ( iter != stored_data.end() );
        if ( found )
        {
            fout << " =============== Content of the file \"" << dataname << "\" : " << endl;
            std::vector<char>stored_content = cube->get_misc_data( *iter );
            for ( std::vector<char>::iterator c_iter = stored_content.begin(); c_iter != stored_content.end(); ++c_iter )
            {
                fout << *c_iter;
            }
            fout << endl;
            fout << " =============== End of content of the file \"" << dataname << "\" : " << endl;
        }
        else
        {
            selected_data = false;
        }
    }
    if ( !selected_data )
    {
        int i = 1;
        for ( std::vector<std::string>::iterator iter = stored_data.begin(); iter != stored_data.end(); ++iter )
        {
            string filename  = *iter;
            string anchor    = "anchor.xml";
            string data_ext  = ".data";
            string index_ext = ".index";

            fout << "File " << i << ": " << filename;
            if ( ( filename.length() >= anchor.length() )
                 &&
                 filename.compare( filename.length() - anchor.length(), anchor.length(),  anchor ) == 0 )
            {
                fout << " ( Meta data of the cube report )";
            }
            if ( ( filename.length() >= data_ext.length() )
                 &&
                 filename.compare( filename.length() - data_ext.length(), data_ext.length(),  data_ext ) == 0 )
            {
                string       _name   = filename.erase( filename.length() - data_ext.length(), data_ext.length() );
                int          _met_id = 0;
                stringstream sstr( _name );
                sstr >> _met_id;
                Metric* _met = cube->get_met( _met_id, true );
                fout << " ( Stored content of the metric ";
                if ( _met != NULL )
                {
                    fout << "\"" << _met->get_uniq_name() <<  "\"";
                }
                fout << " )";
            }
            if ( ( filename.length() >= index_ext.length() )
                 &&
                 filename.compare( filename.length() - index_ext.length(), index_ext.length(),  index_ext ) == 0 )
            {
                string       _name   = filename.erase( filename.length() - index_ext.length(), index_ext.length() );
                int          _met_id = 0;
                stringstream sstr( _name );
                sstr >> _met_id;
                Metric* _met = cube->get_met( _met_id, true );
                fout << " ( Stored index for data of the metric ";
                if ( _met != NULL )
                {
                    fout << "\"" << _met->get_uniq_name() <<  "\"";
                }
                fout << " )";
            }
            fout << endl;
            ++i;
        }
    }
}

void
Printer::dump_topology( Cartesian* topology, bool show_coordinates ) const
{
    fout << "--------------------------------------------------" << endl;
    if ( topology == NULL )
    {
        cerr << "Something is wrong. NULL topology returned by Cube::get_cartv(). Ignore." << endl;
        return;
    }
    fout << "Topology name: " << topology->get_name() << endl;
    fout << "Number of dimensions: " << topology->get_ndims() << endl;
    const std::vector<long>       dims      = topology->get_dimv();
    const std::vector<bool>       periodv   = topology->get_periodv();
    const std::vector<std::string>namesv    = topology->get_namedims();
    bool                          has_names = ( namesv.size() != 0 );

    for ( size_t i = 0; i < dims.size(); ++i )
    {
        fout << "Dimension " << i << ": ";
        fout << dims.at( i ) << "\t\t" << ( ( periodv.at( i ) ) ? "periodic" : "non periodic" );
        if ( has_names )
        {
            fout << "\t" << namesv.at( i );
        }
        fout << endl;
    }
    fout << endl;
    if ( show_coordinates )
    {
        fout << "Coordinates mapping:" << endl;
        const TopologyMap           coords = topology->get_cart_sys();
        TopologyMap::const_iterator iter;
        for ( iter = coords.begin(); iter != coords.end(); ++iter )
        {
            std::vector<long>_my_coords = iter->second;
            fout << iter->first->get_name() << " " << iter->first->get_id() << "\t\t -> ";
            for ( std::vector<long>::iterator c_iter = _my_coords.begin(); c_iter != _my_coords.end(); ++c_iter )
            {
                fout << *c_iter << " ";
            }
            fout << endl;
        }
    }
}

void
Printer::dump_topologies( const std::vector<Cartesian*>& topologies, bool show_coordinates ) const
{
    std::vector<Cartesian*>::const_iterator topo_iter = topologies.begin();
    for (; topo_iter != topologies.end(); ++topo_iter )
    {
        Cartesian* topology = *topo_iter;
        dump_topology( topology, show_coordinates );
    }
}






void
Printer::dump_metric_dimension( const vector<Metric*>& metrics )
{
    for ( vector<Metric*>::const_iterator m_iter = metrics.begin(); m_iter != metrics.end(); ++m_iter )
    {
        bitstring_t children_markers;
        dump_metric( *m_iter, 0, children_markers ); // metric and level. Here all are roots -> level 0
    }
}
void
Printer::dump_calltree_dimension( const vector<Region*>& regv,  const vector<Cnode*>& cnodes )
{
    fout << " -------------------------- LIST OF REGIONS --------------------------" << endl;
    for ( vector<Region*>::const_iterator r_iter = regv.begin(); r_iter != regv.end(); ++r_iter )
    {
        dump_region( *r_iter ); // metric and level. Here all are roots -> level 0
    }
    fout << " -------------------------- CALL TREE --------------------------------" << endl;
    for ( vector<Cnode*>::const_iterator c_iter = cnodes.begin(); c_iter != cnodes.end(); ++c_iter )
    {
        bitstring_t children_markers;
        dump_cnode( *c_iter, 0, children_markers ); // metric and level. Here all are roots -> level 0
    }
}
void
Printer::dump_system_dimension( const vector<SystemTreeNode*>& stnv )
{
    for ( vector<SystemTreeNode*>::const_iterator stn_iter = stnv.begin(); stn_iter != stnv.end(); ++stn_iter )
    {
        bitstring_t children_markers;
        dump_stn( *stn_iter, 0, children_markers ); // metric and level. Here all are roots -> level 0
    }
}




void
Printer::dump_flat_profile( vector<Metric*>& metrics, std::vector<Region*>& regions, vector<Thread*>& threads, CalculationFlavour mf, ThreadSelection aggregate_over_threads )  const
{
    fout << endl << endl << " =============== FLAT PROFILE ============= " << endl;
    size_t max_cnode_padding = 0;
    for ( vector<Region*>::iterator r_iter = regions.begin(); r_iter != regions.end(); ++r_iter )
    {
        stringstream sstr;
        string       _str;
        sstr << "(id=" << ( *r_iter )->get_id() << ")" << endl;
        ;
        sstr >> _str;
        if ( ( ( *r_iter )->get_name() + _str ).length() > max_cnode_padding )
        {
            max_cnode_padding = ( ( *r_iter )->get_name() + _str ).length();
        }
    }

    std::vector<int>thread_paddings;
    std::string     aggr_threads_header = "All threads";
    if ( aggregate_over_threads == AGGREGATED_THREADS )
    {
        thread_paddings.push_back( aggr_threads_header.length() );
    }
    else
    {
        for ( vector<Thread*>::iterator t_iter = threads.begin(); t_iter != threads.end(); ++t_iter )
        {
            thread_paddings.push_back( ( *t_iter )->get_name().length() );
        }
    }



    for ( vector<Metric*>::iterator m_iter = metrics.begin(); m_iter != metrics.end(); ++m_iter )
    {
        fout << "Print out the data of the metric " << ( ( *m_iter )->get_uniq_name() ) << endl << endl;
        size_t i = 0;
        while ( ++i <= max_cnode_padding + 1 )
        {
            fout << ' ';
        }
        if ( aggregate_over_threads == AGGREGATED_THREADS )
        {
            fout << aggr_threads_header;
        }
        else
        {
            for ( vector<Thread*>::iterator t_iter = threads.begin(); t_iter != threads.end(); ++t_iter )
            {
                fout << ( ( *t_iter )->get_name() ) << "                      ";
            }
        }
        fout << endl << "-------------------------------------------------------------------------------" << endl;

        for ( std::vector<Region*>::iterator r_iter = regions.begin(); r_iter != regions.end(); ++r_iter )
        {
            stringstream sstr;
            string       _str;
            sstr << "(id=" << ( *r_iter )->get_id() << ")";
            sstr >> _str;
            string _caption = ( ( *r_iter )->get_name() + _str );
            fout << _caption;
            size_t i = _caption.length();
            while ( ++i <= max_cnode_padding + 1 )
            {
                fout << ' ';
            }
            if ( aggregate_over_threads == AGGREGATED_THREADS  )
            {
                Value* _v = NULL;
                _v = cube->get_sev_adv( *m_iter, mf,  *r_iter, cube::CUBE_CALCULATE_EXCLUSIVE );
                Value* _v_sub = NULL;
                ( *r_iter )->set_as_subroutines();   // calculate subroutines of this region
                _v_sub = cube->get_sev_adv( *m_iter, mf,  *r_iter, cube::CUBE_CALCULATE_EXCLUSIVE );
                ( *r_iter )->unset_as_subroutines(); // reset its status
                string _value1;
                string _value2;

                if ( _v == NULL )
                {
                    _value1 = "0.";
                }
                else
                {
                    _value1 = _v->getString();
                }
                if ( _v_sub == NULL )
                {
                    _value2 = "0.";
                }
                else
                {
                    _value2 = _v_sub->getString();
                }

                _v->Free();
                _v_sub->Free();
                std::string _subroutines = "   Subroutines ";
                fout << _value1 <<  endl << _subroutines;
                i = _subroutines.length();
                while ( ++i <= max_cnode_padding + 1  )
                {
                    fout << ' ';
                }
                fout << _value2;
            }
            else if ( aggregate_over_threads == SELECTED_THREADS )
            {
                int t_index = 0;
                for ( vector<Thread*>::iterator t_iter = threads.begin(); t_iter != threads.end(); ++t_iter, ++t_index )
                {
                    Value* _v = NULL;
                    _v = cube->get_sev_adv( *m_iter, mf,  *r_iter, cube::CUBE_CALCULATE_EXCLUSIVE, *t_iter, cube::CUBE_CALCULATE_EXCLUSIVE );

                    string _value1;
                    if ( _v == NULL )
                    {
                        _value1 = "0.";
                    }
                    else
                    {
                        _value1 = _v->getString();
                    }
                    _v->Free();
                    fout << _value1;
                    int i = _value1.length();
                    while ( ++i <= thread_paddings[ t_index ] + 12 )
                    {
                        fout << ' ';
                    }
                }
                fout << endl;

                t_index = 0;
                stringstream sstr;
                string       _str;
                std::string  _subroutines = "   Subroutines ";
                fout <<  _subroutines;

                size_t i = _subroutines.length();
                while ( ++i <= max_cnode_padding + 1 )
                {
                    fout << ' ';
                }
                for ( vector<Thread*>::iterator t_iter = threads.begin(); t_iter != threads.end(); ++t_iter, ++t_index )
                {
                    Value* _v_sub = NULL;
                    ( *r_iter )->set_as_subroutines();   // calculate subroutines of this region
                    _v_sub = cube->get_sev_adv( *m_iter, mf,  *r_iter, cube::CUBE_CALCULATE_INCLUSIVE, *t_iter, cube::CUBE_CALCULATE_EXCLUSIVE );
                    ( *r_iter )->unset_as_subroutines(); // reset its status

                    string _value2;
                    if ( _v_sub == NULL )
                    {
                        _value2 = "0.";
                    }
                    else
                    {
                        _value2 = _v_sub->getString();
                    }
                    _v_sub->Free();
                    fout << _value2;
                    int i = _value2.length();
                    while ( ++i <= thread_paddings[ t_index ] + 12 )
                    {
                        fout << ' ';
                    }
                }
            }
            else
            {
                int     t_index = 0;
                Value** _v      = NULL;
                _v = cube->get_sevs_adv( *m_iter, mf,  *r_iter, cube::CUBE_CALCULATE_EXCLUSIVE );
                for ( vector<Thread*>::iterator t_iter = threads.begin(); t_iter != threads.end(); ++t_iter, ++t_index )
                {
                    string _value1;
                    if ( _v[ t_index ] == NULL )
                    {
                        _value1 = "0.";
                    }
                    else
                    {
                        _value1 = _v[ t_index ]->getString();
                    }
                    fout << _value1;
                    int i = _value1.length();
                    while ( ++i <= thread_paddings[ t_index ] + 12 )
                    {
                        fout << ' ';
                    }
                }
                fout << endl;
                services::delete_row_of_values( _v, threads.size() );

                t_index = 0;
                stringstream sstr;
                string       _str;
                std::string  _subroutines = "   Subroutines ";
                fout <<  _subroutines;

                size_t i = _subroutines.length();
                ( *r_iter )->set_as_subroutines();   // calculate subroutines of this region
                Value** _v_sub = cube->get_sevs_adv( *m_iter, mf,  *r_iter, cube::CUBE_CALCULATE_INCLUSIVE );
                ( *r_iter )->unset_as_subroutines(); // reset its status

                while ( ++i <= max_cnode_padding + 1 )
                {
                    fout << ' ';
                }
                for ( vector<Thread*>::iterator t_iter = threads.begin(); t_iter != threads.end(); ++t_iter, ++t_index )
                {
                    string _value2;
                    if ( _v_sub[ t_index ] == NULL )
                    {
                        _value2 = "0.";
                    }
                    else
                    {
                        _value2 = _v_sub[ t_index ]->getString();
                    }
                    fout << _value2;
                    int i = _value2.length();
                    while ( ++i <= thread_paddings[ t_index ] + 12 )
                    {
                        fout << ' ';
                    }
                }
                services::delete_row_of_values( _v_sub, threads.size() );
            }
            fout << endl;
        }
    }
}





void
Printer::dump_data( vector<Metric*>& metrics, vector<Cnode*>& cnodes, vector<Thread*>& threads, CalculationFlavour mf, CalculationFlavour cf, bool stored, ThreadSelection aggregate_over_threads )  const
{
    fout << endl << endl << " ===================== DATA =================== " << endl;
    size_t max_cnode_padding = 0;
    for ( vector<Cnode*>::iterator c_iter = cnodes.begin(); c_iter != cnodes.end(); ++c_iter )
    {
        stringstream sstr;
        string       _str;
        sstr << "(id=" << ( *c_iter )->get_id() << ")" << endl;
        ;
        sstr >> _str;
        if ( ( ( ( *c_iter )->get_callee() )->get_name() + _str ).length() > max_cnode_padding )
        {
            max_cnode_padding = ( ( ( *c_iter )->get_callee() )->get_name() + _str ).length();
        }
    }

    std::vector<int>thread_paddings;
    std::string     aggr_threads_header = "All threads";
    if ( aggregate_over_threads == AGGREGATED_THREADS )
    {
        thread_paddings.push_back( aggr_threads_header.length() );
    }
    else
    {
        for ( vector<Thread*>::iterator t_iter = threads.begin(); t_iter != threads.end(); ++t_iter )
        {
            thread_paddings.push_back( ( *t_iter )->get_name().length() );
        }
    }



    for ( vector<Metric*>::iterator m_iter = metrics.begin(); m_iter != metrics.end(); ++m_iter )
    {
        fout << "Print out the data of the metric " << ( ( *m_iter )->get_uniq_name() ) << endl << endl;
        size_t i = 0;
        while ( ++i <= max_cnode_padding + 1 )
        {
            fout << ' ';
        }
        if ( aggregate_over_threads == AGGREGATED_THREADS  )
        {
            fout << aggr_threads_header;
        }
        else
        {
            for ( vector<Thread*>::iterator t_iter = threads.begin(); t_iter != threads.end(); ++t_iter )
            {
                fout << ( ( *t_iter )->get_name() ) << "             ";
            }
        }
        fout << endl << "-------------------------------------------------------------------------------" << endl;
        uint64_t parameter = 0;
        for ( vector<Cnode*>::iterator c_iter = cnodes.begin(); c_iter != cnodes.end(); ++c_iter, ++parameter )
        {
            stringstream sstr;
            string       _str;
            sstr << "(id=" << ( *c_iter )->get_id() << ")";
            sstr >> _str;
            string _caption = ( ( ( *c_iter )->get_callee() )->get_name() + _str );
            fout << _caption;
            size_t i = _caption.length();
            while ( ++i <= max_cnode_padding + 1 )
            {
                fout << ' ';
            }
            if ( aggregate_over_threads == AGGREGATED_THREADS   )
            {
                Value* _v = NULL;
                _v = cube->get_sev_adv( *m_iter, mf, *c_iter, cf );
                string _value;
                if ( _v == NULL )
                {
                    _value = "0.";
                }
                else
                {
                    _value = _v->getString();
                }
                _v->Free();
                fout << _value;
            }
            else if ( aggregate_over_threads == SELECTED_THREADS )
            {
                int t_index = 0;
                for ( vector<Thread*>::iterator t_iter = threads.begin(); t_iter != threads.end(); ++t_iter, ++t_index )
                {
                    Value* _v = NULL;
                    if ( stored )
                    {
                        _v = cube->get_saved_sev_adv( *m_iter, *c_iter, *t_iter );
                    }
                    else
                    {
                        _v = cube->get_sev_adv( *m_iter, mf, *c_iter, cf, *t_iter, cube::CUBE_CALCULATE_EXCLUSIVE );
                    }

                    string _value;
                    if ( _v == NULL )
                    {
                        _value = "0.";
                    }
                    else
                    {
                        _value = _v->getString();
                    }
                    _v->Free();
                    fout << _value;
                    int i = _value.length();
                    while ( ++i <= thread_paddings[ t_index ] + 12 )
                    {
                        fout << ' ';
                    }
                }
            }
            else
            {
                int     t_index = 0;
                Value** _v      = NULL;
                if ( stored )
                {
                    _v = cube->get_saved_sevs_adv( *m_iter, *c_iter );
                }
                else
                {
                    _v = cube->get_sevs_adv( *m_iter, mf, *c_iter, cf );
                }
                for ( vector<Thread*>::iterator t_iter = threads.begin(); t_iter != threads.end(); ++t_iter, ++t_index )
                {
                    string _value;
                    if ( _v == NULL || _v[ t_index ] == NULL )
                    {
                        _value = "0.";
                    }
                    else
                    {
                        _value = _v[ t_index ]->getString();
                    }
                    fout << _value;
                    int i = _value.length();
                    while ( ++i <= thread_paddings[ t_index ] + 12 )
                    {
                        fout << ' ';
                    }
                }
                services::delete_row_of_values( _v, threads.size() );
            }
            fout << endl;
        }
    }
}

void
Printer:: prepare(      std::vector<Metric*>&,
                        std::vector<Cnode*>&,
                        std::vector<Thread*>& ) const
{
    // currently it sets only scale function to print out assymptotic representation of a value
//     for (std::vector < Metric* >::iterator miter = _metrics.begin(); miter != _metrics.end(); ++miter)
//     {
//      Metric* _m = *miter;
//      if (_m->get_data_type() != cube::CUBE_DATA_TYPE_SCALE_FUNC)
//          continue;
//
//      ScaleFuncValue * _v = dynamic_cast<ScaleFuncValue*>(_m->get_metric_value());
//      ScaleFuncValueConfig&  _vc = _v->getConfig();
//      _vc->
//
//     }
}
