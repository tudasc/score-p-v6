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


#include "config.h"

#include <iostream>
#include <cmath>
#include <iomanip>

#include "CubeStrategies.h"
#include "CubeRow.h"
#include "CubeRowsManager.h"
#include "CubeValues.h"
#include "CubeTrafos.h"
#include "CubeFileFinder.h"
#include "CubeRowWiseMatrix.h"
#include "CubeRowsSuppliers.h"

using namespace std;
using namespace cube;



#define print_vector( X ) std::cout << "("; for ( std::vector<cnode_id_t>::iterator iter = X.begin(); iter < X.end(); iter++ ) { std::cout << *iter << " "; }; cout << ")" << endl;
#define print_bool( X ) std::cout << ( ( X ) ? "true" : "false" ) << endl;

#define PRINT_MAP( X, _size ) std::cout << "("; \
    for ( rows_t::iterator iter = X.begin(); iter != X.end(); iter++ ) \
    {  \
        std::cout << dec << std::endl << "map[" << ( *iter ).first << "]=" << hex; \
        for ( unsigned i = 0; i < _size; i++ ) \
        { \
            char* _row = ( *iter ).second; \
            cout << ( unsigned short int )( *( _row + i ) ) << " "; \
        } \
    }; cout << ")" << dec << endl;

#define PRINT_ROWS( X, _size ) std::cout << "("; \
    \
    for ( cnode_id_t _cid = 0; _cid < X.size(); ++_cid ) \
    {  \
        std::cout << dec << std::endl << "map[" << _cid << "]=" << hex; \
        char* _row = X[ _cid ]; \
        for ( unsigned i = 0; i < _size; i++ ) \
        { \
            cout << ( unsigned short int )( *( _row + i ) ) << " "; \
        } \
    }; cout << ")" << dec << endl;



#define print_row( X, SIZE ) std::cout << "("; for ( unsigned i = 0; i < SIZE; i++ ) { std::cout << hex << ( ( unsigned short )( X[ i ] ) & 0x00FF ) << dec << " "; }; cout << ")" << endl;

int
main( int argc, char** argv )
{
    vector<cnode_id_t>rows;
    bool              read_all_rows;

    AllInMemoryStrategy* all_in_memory = new AllInMemoryStrategy( true );
    LastNRowsStrategy*   last_n_rows   = new LastNRowsStrategy( true, 3 );
    ManualStrategy*      manual        = new ManualStrategy( true );


    BasicStrategy* strategy = all_in_memory;

    // first we check adding 13 rows
    cout << "__________ ALL IN MEMORY ______________" << endl;
    strategy->addRow( 0L, read_all_rows, rows );
    print_vector( rows );
    print_bool( read_all_rows )
    strategy->addRow( 3L, read_all_rows, rows );
    print_vector( rows );
    print_bool( read_all_rows )
    strategy->addRow( 5L, read_all_rows, rows );
    print_vector( rows );
    print_bool( read_all_rows )
    strategy->addRow( 7L, read_all_rows, rows );
    print_vector( rows );
    print_bool( read_all_rows )
    strategy->addRow( 2L, read_all_rows, rows );
    print_vector( rows );
    print_bool( read_all_rows )
    strategy->addRow( 13L, read_all_rows, rows );
    print_vector( rows );
    print_bool( read_all_rows )

    strategy->removeRow( 3L, rows );
    print_vector( rows );


    strategy = last_n_rows;
    cout << "__________ LAST N(3) ROWS ______________" << endl;

    // first we check adding 13 rows
    strategy->addRow( 0L, read_all_rows, rows );
    print_vector( rows );
    print_bool( read_all_rows )
    strategy->addRow( 3L, read_all_rows, rows );
    print_vector( rows );
    print_bool( read_all_rows )
    strategy->addRow( 5L, read_all_rows, rows );
    print_vector( rows );
    print_bool( read_all_rows )
    strategy->addRow( 7L, read_all_rows, rows );
    print_vector( rows );
    print_bool( read_all_rows )
    strategy->addRow( 2L, read_all_rows, rows );
    print_vector( rows );
    print_bool( read_all_rows )
    strategy->addRow( 13L, read_all_rows, rows );
    print_vector( rows );
    print_bool( read_all_rows )

    strategy->removeRow( 3L, rows );
    print_vector( rows );


    strategy = manual;
    cout << "__________ MANUAL ______________" << endl;

    // first we check adding 13 rows
    strategy->addRow( 0L, read_all_rows, rows );
    print_vector( rows );
    print_bool( read_all_rows )
    strategy->addRow( 3L, read_all_rows, rows );
    print_vector( rows );
    print_bool( read_all_rows )
    strategy->addRow( 5L, read_all_rows, rows );
    print_vector( rows );
    print_bool( read_all_rows )
    strategy->addRow( 7L, read_all_rows, rows );
    print_vector( rows );
    print_bool( read_all_rows )
    strategy->addRow( 2L, read_all_rows, rows );
    print_vector( rows );
    print_bool( read_all_rows )
    strategy->addRow( 13L, read_all_rows, rows );
    print_vector( rows );
    print_bool( read_all_rows )

    strategy->removeRow( 3L, rows );
    print_vector( rows );

// ----------------------- test swap file rows  supplier ----------------------------
    cout << "__________ test swap rows supplier ______________" << endl;
    RowsSupplier* _rows =  new SwapRowsSupplier( "aa.data", 100000L );


    row_t _row = _rows->provideRow( 2L, true );
    memset( _row, 12, 100000L );
    _rows->dropRow( _row, 2L );
    _row = _rows->provideRow( 13L, true );
    memset( _row, 142, 100000L );
    _rows->dropRow( _row, 13L );
    _row = _rows->provideRow( 2L, true );
    print_row( _row, 100000L );
    delete _row;
    _row = _rows->provideRow( 13L, true );
    print_row( _row, 100000L );
    delete _row;

    delete _rows;

    // ----------------------- test RO  file rows  supplier (with examples 1.index and 1.data)----------------------------
    cout << "__________ test ro rows supplier ______________" << endl;
    fileplace_t DataPlace;
    fileplace_t IndexPlace;

    IndexPlace.first         = "TEST04/2.index";
    IndexPlace.second.first  = 0;
    IndexPlace.second.second = 0L;

    DataPlace.first         = "TEST04/2.data";
    DataPlace.second.first  = 0;
    DataPlace.second.second = 0L;

    Value*        value    =  selectValueOnDataType( CUBE_DATA_TYPE_DOUBLE );
    RowsSupplier* _ro_rows =  new RORowsSupplier( DataPlace, IndexPlace, 64L,  value->getSize()  );

    _row =  _ro_rows->provideRow( 2L, true );
    print_row( _row, 64L * 8L );
    _rows->dropRow( _row, 2L );
    _row =  _ro_rows->provideRow( 0L, true );
    print_row( _row, 64L * 8L );
    _rows->dropRow( _row, 0L );

    delete _ro_rows;

    // ----------------------- test RO  file rows  supplier (with examples 1.index and 1.data)----------------------------
    cout << "__________ test wo rows supplier ______________" << endl;
    try
    {
        //     fileplace_t DataPlace;
        //     fileplace_t IndexPlace;

        IndexPlace.first         = "TEST04/aaaa.index";
        IndexPlace.second.first  = 0;
        IndexPlace.second.second = 0L;

        DataPlace.first         = "TEST04/aaaaa.data";
        DataPlace.second.first  = 0;
        DataPlace.second.second = 0L;

        RowsSupplier* _wo_rows =  new WORowsSupplier( DataPlace, IndexPlace, 64L,  value->getSize()  );

        _row =  _wo_rows->provideRow( 20L, true );
        print_row( _row, 64L * 8L );
        _wo_rows->dropRow( _row, 20L );

        _row =  _wo_rows->provideRow( 0L, true );
        print_row( _row, 64L * 8L );
        _wo_rows->dropRow( _row, 0L );

        _row =  _wo_rows->provideRow( 123L );
        print_row( _row, 64L * 8L );
        _wo_rows->dropRow( _row, 123L );

        delete _wo_rows;
    }
    catch ( const RuntimeError& error )
    {
        cerr << error.what() << endl;
    }


    // ----------------------- test RO  file rows  supplier (with examples 1.index and 1.data)----------------------------
    cout << "__________ test ro z rows supplier ______________" << endl;
    try
    {
        //     fileplace_t DataPlace;
        //     fileplace_t IndexPlace;

        IndexPlace.first         = "ZTEST/0.index";
        IndexPlace.second.first  = 0;
        IndexPlace.second.second = 0L;

        DataPlace.first         = "ZTEST/0.data";
        DataPlace.second.first  = 0;
        DataPlace.second.second = 0L;

        RowsSupplier* _roz_rows =  new ROZRowsSupplier( DataPlace, IndexPlace, 64L,  value->getSize()  );

        _row =  _roz_rows->provideRow( 20L );
        print_row( _row, 64L * 8L );
        _roz_rows->dropRow( _row, 20L );
        _row =  _roz_rows->provideRow( 0L );
        print_row( _row, 64L * 8L );
        _roz_rows->dropRow( _row, 0L );
        _row =  _roz_rows->provideRow( 123L );
        print_row( _row, 64L * 8L );
        _roz_rows->dropRow( _row, 123L );
        delete _roz_rows;
    }
    catch ( const RuntimeError& error )
    {
        cerr << error.what() << endl;
    }


    // ----------------------- test RO  file rows  supplier (with examples 1.index and 1.data)----------------------------
    cout << "__________ testwro z rows supplier ______________" << endl;
    try
    {
        //     fileplace_t DataPlace;
        //     fileplace_t IndexPlace;

        IndexPlace.first         = "ZTEST/0aaa.index";
        IndexPlace.second.first  = 0;
        IndexPlace.second.second = 0L;

        DataPlace.first         = "ZTEST/0aaa.data";
        DataPlace.second.first  = 0;
        DataPlace.second.second = 0L;

        RowsSupplier* _woz_rows =  new WOZRowsSupplier( DataPlace, IndexPlace, 64L,  value->getSize() );

        _row =  _woz_rows->provideRow( 20L );
        print_row( _row, 64L * 8L );
        _woz_rows->dropRow( _row, 20L );
        _row =  _woz_rows->provideRow( 0L );
        print_row( _row, 64L * 8L );
        _woz_rows->dropRow( _row, 0L );
        _row =  _woz_rows->provideRow( 123L );
        print_row( _row, 64L * 8L );
        _woz_rows->dropRow( _row, 123L );
        delete _woz_rows;
    }
    catch ( const RuntimeError& error )
    {
        cerr << error.what() << endl;
    }


// ----------------------- test row manager --------------------------
    cout << "__________ test row manager ______________" << endl;


    rows_t matrix_rows;

    fileplace_t indexfile;
    indexfile.first         = "TEST04/bbbb.index";
    indexfile.second.first  = 0;
    indexfile.second.second = 0;

    fileplace_t datafile;
    datafile.first         = "TEST04/bbbb.data";
    datafile.second.first  = 0;
    datafile.second.second = 0;

    Row*         row_interface = new Row( 30, value ); // create Row with standart interfaces, which do get replaces later on in initialization of RowsSupplier
    RowsManager* rows_manager  = new RowsManager( datafile, indexfile, &matrix_rows, row_interface,  all_in_memory );

    cout << " Before inserting " << endl;
    PRINT_ROWS( matrix_rows, 30 * 8 );

    DoubleValue* v   = new DoubleValue( 123.45 );
    cnode_id_t   cid = 32;
    rows_manager->provideRow( cid );
    cout << " After asking for row " << endl;
    PRINT_ROWS( matrix_rows, 30 * 8 );

    _row = matrix_rows[ cid ];

    row_interface->setData( _row,  v, 1 );
    *v = 34.23;
    row_interface->setData( _row, v, 10 );

    cout << " After inserting " << endl;
    PRINT_ROWS( matrix_rows, 30 * 8 );
    Value* _v = row_interface->getData( _row,  1 );
    cout << _v->getString() << endl;
    _v->Free();
    _v = row_interface->getData( _row, 10 );
    cout << _v->getString() << endl;
    _v->Free();


    // ----------------------------- sret another strategy... last 3 rows.... , with memory rowsuppliler, used inside of rows manager, we will loose data

    rows_manager->setStrategy( last_n_rows );

    cid = 1;
    rows_manager->provideRow( cid );
    _row = matrix_rows[ cid ];
    *v   = 334.23;
    row_interface->setData( _row, v, 3 );

    cid = 3;
    rows_manager->provideRow( cid );
    _row = matrix_rows[ cid ];
    row_interface->setData( _row, v, 6 );

    *v = 3234.23;
    row_interface->setData( _row, v, 2 );

//     Value* _vv = row_interface->sumRow( _row, 1, 10 );
//     cout << " Sum1 " << _vv->getString() << endl;
//     _vv->Free();
//     _vv = row_interface->sumRow( _row, 3, 10 );
//     cout << " Sum2 " << _vv->getString() << endl;
//     _vv->Free();

    cid = 6;
    rows_manager->provideRow( cid );
    _row = matrix_rows[ cid ];
    row_interface->setData( _row, v, 8 );

    *v = -34.23;
    row_interface->setData( _row, v, 12 );

    PRINT_ROWS( matrix_rows, 30 * 8 );

    cid = 1;
    rows_manager->provideRow( cid );
    _row = matrix_rows[ cid ];
    row_interface->setData( _row, v, 8 );

    *v = -34.23;
    row_interface->setData( _row, v, 12 );

    PRINT_ROWS( matrix_rows, 30 * 8 );


    cid = 32;
    rows_manager->provideRow( cid );
    _row = matrix_rows[ cid ];
    row_interface->setData( _row, v, 8 );

    *v = -534.23;
    row_interface->setData( _row, v, 12 );

    PRINT_ROWS( matrix_rows, 30 * 8 );



    v->Free();
    delete row_interface;
    delete rows_manager;


    delete all_in_memory;
    delete last_n_rows;
    delete manual;


    // ------------------- test RowWiseMatrix -------------------------------

    cout << "-------------- TEST ROWWISE MATRIX ------------------------- " << endl;
    RowWiseMatrix* matrix = new RowWiseMatrix( datafile, indexfile, 10, 30, value );

    Value* _vvv = new DoubleValue();

    *_vvv = 14.5;
    matrix->setValue( _vvv, 1, 2 );
    *_vvv = 24.5;
    matrix->setValue( _vvv, 2, 3 );
    *_vvv = 34.5;
    matrix->setValue( _vvv, 3, 4 );
    *_vvv = 44.5;
    matrix->setValue( _vvv, 4, 5 );


    Value* _v1 = matrix->getValue( 1, 3 );
    cout << " __ " << _v1->getString() << endl;
    _v1->Free();
    _v1 = matrix->getValue( 3, 4 );
    cout << " __ " << _v1->getString() << endl;
    _v1->Free();

//     _v1 = matrix->sumRow( 2, 2, 3 );
//     cout << " __ " << _v1->getString() << endl;
//     _v1->Free();


    delete matrix;
    _vvv->Free();
    value->Free();
    return -1; // standart - failed test


    cout << " -------------- TRY TO CREATE A CUBE FILE ( using all in memory )---------------- " << endl;
}
