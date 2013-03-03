#include "WindowMain.h"
#include "sweet-shop.h"
#include "database.h"
#include <gtkmm.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include "lib.h"

/*****************************************************************************
 * Creating window and it's components.                                       *
  *****************************************************************************/

WindowMain::WindowMain()
{
    /* Main window preferences */
    set_icon_from_file( WINDOW_MAIN_ICON );
    set_border_width( WIDGETS_BORDER );
    set_title( WINDOW_MAIN_TITLE );
    set_default_size( 900, 400 );

    add( boxWindow );
    boxWindow.set_orientation( Gtk::ORIENTATION_VERTICAL );

    /* Main box */
    boxWindow.pack_start( boxMain );
    boxMain.set_border_width( WIDGETS_BORDER );
    boxMain.set_orientation( Gtk::ORIENTATION_HORIZONTAL );

    /* Categories of goods */
    boxMain.pack_start( boxCategories, false, false, WIDGETS_BORDER );
    boxCategories.set_orientation( Gtk::ORIENTATION_VERTICAL );
    create_category( radioCakes, "Торты" );
    create_category( radioCandy, "Конфеты" );
    create_category( radioCoockies, "Печенье" );
    create_category( radioJujube, "Мармелад" );

    /* List of goods */
    boxMain.pack_start( scrolledGoods, true, true, WIDGETS_BORDER );
    scrolledGoods.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolledGoods.add( treeGoods );
    treeGoods.set_available( &imageAvailable, &labelAvailable );

    /* Buy section */
    boxMain.pack_start( boxBuy, false, false, WIDGETS_BORDER );
    boxBuy.set_orientation( Gtk::ORIENTATION_VERTICAL );

    boxBuy.pack_start( imageAvailable, false, false, WIDGETS_BORDER );
    imageAvailable.set_size_request( 72, 72 );
    boxBuy.pack_start( labelAvailable, false, false, WIDGETS_BORDER );

    boxBuy.pack_start( *(new Gtk::Separator), false, false, WIDGETS_BORDER );
    boxBuy.pack_start( *(new Gtk::Label( "Количество:" )), false, false, WIDGETS_BORDER );
    boxBuy.pack_start( entryCount, false, false, WIDGETS_BORDER );
    entryCount.set_text( "1" );

    boxBuy.pack_start( buttonBuy, false, false, WIDGETS_BORDER );
    buttonBuy.signal_clicked().connect( sigc::mem_fun( *this, &WindowMain::on_button_buy_activate ) );
    buttonBuy.set_label( "Купить" );

    /* List of purchases */
    boxMain.pack_start( boxPurchase, true, true, WIDGETS_BORDER );
    boxBuy.set_orientation( Gtk::ORIENTATION_VERTICAL );

    boxPurchase.pack_start( scrolledPurchases, true, true, WIDGETS_BORDER );
    scrolledPurchases.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolledPurchases.add( treePurchases );

    /* Statusbar */
    boxWindow.pack_start( statusbarMain, false, false );

    /* Run */
    show_all_children();
    on_category_choose();
    statusbarMain.push( "Готовы к покупкам? :)" );
}

/*****************************************************************************
 * Creating category of goods.                                                *
 ******************************************************************************
 *  takes: RadioButton - button object;                                       *
 *         char* - button label;                                              *
  *****************************************************************************/

void WindowMain::create_category( Gtk::RadioButton &radio, const char *label )
{
    /* Create a radiobutton and connect signal */
    boxCategories.pack_start( radio, false, false );
    radio.signal_released().connect( sigc::mem_fun( *this, &WindowMain::on_category_choose ) );
    radio.set_group( groupCategories );
    radio.set_label( label );
}

/*****************************************************************************
 * Action on buy button activate.                                             *
  *****************************************************************************/

void WindowMain::on_button_buy_activate()
{
    char *section = treeGoods.get_section();
    char *id = treeGoods.get_activated_id();

    char query[ COMMAND_BUFFER_SIZE ];
    sprintf( query, "SELECT `id`, `name`, `price`, `item` FROM `%s` WHERE `id` LIKE '%s';", section, id );
    std::vector<GoodsRecord> *res = execute_query_select_goods( query );

    if( res->size() ) {
        if( treeGoods.get_is_available() ) {
            Glib::ustring count = entryCount.get_text();
            if( is_number( count.c_str() ) ) {
                char c_cost[16];
                sprintf( c_cost, "%4.2f", atoi( count.c_str() ) * strtof( res->at(0).price.c_str(), NULL ) );
                Glib::ustring cost( c_cost );
                treePurchases.append_data( res->at(0).name, count, cost );
                statusbarMain.push( "Добавлено в чек." );
            } else {
                statusbarMain.push( "Введите нормальное количество!" );
            }
        } else {
            statusbarMain.push( "Данного товара нет в наличии!" );
        }
    } else {
        statusbarMain.push( "Ничего не выбрано!" );
    }

    entryCount.set_text( "1" );
    delete[] section;
    delete[] id;
    delete res;
}

/*****************************************************************************
 * Action on category choose. Starts when on of categories was choosed.       *
  *****************************************************************************/

void WindowMain::on_category_choose()
{
    labelAvailable.set_label( "Загрузка..." );
    imageAvailable.set( IMG_WAIT_PATH );

    /* Loading will be in a separate thread */
    Glib::Thread::create( sigc::mem_fun( *this, &WindowMain::fill_goodslist ) );
}

/*****************************************************************************
 * Fill the list of goods depending on the category selected.                 *
  *****************************************************************************/

void WindowMain::fill_goodslist()
{
    treeGoods.remove_all_rows();
    const char *section;

    if( radioCakes.get_active() ) {
        section = "Cakes";
    }
    else if( radioCandy.get_active() ) {
        section = "Candy";
    }
    else if( radioCoockies.get_active() ) {
        section = "Coockies";
    }
    else if( radioJujube.get_active() ) {
        section = "Jujube";
    }

    char *command = new char[ COMMAND_BUFFER_SIZE ];
    sprintf( command, "SELECT `id`, `name`, `price`, `item` FROM `%s`;", section );
    std::vector<GoodsRecord> *res = execute_query_select_goods( command );

    for( unsigned int i = 0; i < res->size(); i++ ) {
        treeGoods.append_data( res->at( i ) );
    }

    delete res;
    delete[] command;
    imageAvailable.clear();
    treeGoods.set_section( section );
    labelAvailable.set_label( "Загружено!" );
}

/*****************************************************************************
 * Close application.                                                         *
  *****************************************************************************/

void WindowMain::quit()
{
    hide();
    /* Just hide main window, it will be destroyed automatically! */
}

