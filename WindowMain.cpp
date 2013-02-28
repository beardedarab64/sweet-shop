#include "WindowMain.h"
#include "database.h"
#include <gtkmm.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

const unsigned int widgets_border = 5;

WindowMain::WindowMain()
{
    /* Main window preferences */
    set_title( "Sweet Shop" );
    set_default_size( 900, 400 );
    set_border_width( widgets_border );

    add( boxWindow );
    boxWindow.set_orientation( Gtk::ORIENTATION_VERTICAL );

    /* Main box */
    boxWindow.pack_start( boxMain );
    boxMain.set_border_width( widgets_border );
    boxMain.set_orientation( Gtk::ORIENTATION_HORIZONTAL );

    /* Categories of goods */
    boxMain.pack_start( boxCategories, false, false, widgets_border );
    boxCategories.set_orientation( Gtk::ORIENTATION_VERTICAL );
    create_category( radioCakes, "Торты" );
    create_category( radioCandy, "Конфеты" );
    create_category( radioCoockies, "Печенье" );
    create_category( radioJujube, "Мармелад" );

    /* List of goods */
    boxMain.pack_start( scrolledGoods, true, true, widgets_border );
    scrolledGoods.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolledGoods.add( treeGoods );
    treeGoods.set_available( &imageAvailable, &labelAvailable );

    /* Buy section */
    boxMain.pack_start( boxBuy, false, false, widgets_border );
    boxBuy.set_orientation( Gtk::ORIENTATION_VERTICAL );

    boxBuy.pack_start( imageAvailable, false, false, widgets_border );
    imageAvailable.set_size_request( 72, 72 );

    boxBuy.pack_start( labelAvailable, false, false, widgets_border );
    boxBuy.pack_start( entryCount, false, false, widgets_border );
    entryCount.set_text( "1" );

    boxBuy.pack_start( buttonBuy, false, false, widgets_border );
    buttonBuy.signal_clicked().connect( sigc::mem_fun( *this, &WindowMain::on_button_buy_activate ) );
    buttonBuy.set_label( "Купить" );

    /* List of purchases */
    boxMain.pack_start( boxPurchase, true, true, widgets_border );
    boxBuy.set_orientation( Gtk::ORIENTATION_VERTICAL );

    boxPurchase.pack_start( scrolledPurchases, true, true, widgets_border );
    scrolledPurchases.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolledPurchases.add( treePurchases );

    /* Statusbar */
    boxWindow.pack_start( statusbarMain, false, false );

    /* Run */
    show_all_children();
    on_category_choose();
    statusbarMain.push( "Готовы к покупкам? :)" );
}

void WindowMain::create_category( Gtk::RadioButton &radio, const char *label )
{
    /* Create a radiobutton and connect signal */
    boxCategories.pack_start( radio, false, false );
    radio.signal_released().connect( sigc::mem_fun( *this, &WindowMain::on_category_choose ) );
    radio.set_group( groupCategories );
    radio.set_label( label );
}

void WindowMain::on_category_choose()
{
    /* Loading data from database (in different thread) */
    labelAvailable.set_label( "Загрузка..." );
    imageAvailable.set( "data/img/wait.gif" );
    Glib::Thread::create( sigc::mem_fun( *this, &WindowMain::load_from_db ) );
}

void WindowMain::on_button_buy_activate()
{
    char *id = treeGoods.get_activated();
    delete[] id;
}

void WindowMain::get_goodslist( const char *type )
{
    char *command = new char[ COMMAND_TEXT_BUFFER ];
    sprintf( command, "SELECT id, name, price, item FROM %s;", type);
    std::vector<GoodsRecord> *res = execute_query_select( command );

    for( unsigned int i = 0; i < res->size(); i++ ) {
        treeGoods.append_data( res->at( i ) );
    }

    delete[] command;
    delete res;
}

void WindowMain::load_from_db()
{
    treeGoods.remove_all_rows();

    /* And load new data from database */
    if( radioCakes.get_active() ) {
        get_goodslist( "Cakes" );
    }
    else if( radioCandy.get_active() ) {
        get_goodslist( "Candy" );
    }
    else if( radioCoockies.get_active() ) {
        get_goodslist( "Coockies" );
    }
    else if( radioJujube.get_active() ) {
        get_goodslist( "Jujube" );
    }

    imageAvailable.clear();
    labelAvailable.set_label( "Загружено!" );
}

void WindowMain::quit()
{
    hide();
    /* Just hide main window, it will be destroyed automatically! */
}

