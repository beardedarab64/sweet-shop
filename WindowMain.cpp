#include "WindowRegister.h"
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
    set_default_size( 960, 480 );

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
    treeGoods.set_available_pointers( &imageAvailable, &labelAvailable );

    /* Buy section */
    boxMain.pack_start( boxBuy, false, false, WIDGETS_BORDER );
    boxBuy.set_orientation( Gtk::ORIENTATION_VERTICAL );

    boxBuy.pack_start( imageAvailable, false, false, WIDGETS_BORDER );
    imageAvailable.set_size_request( 72, 72 );
    boxBuy.pack_start( labelAvailable, false, false, WIDGETS_BORDER );

    boxBuy.pack_start( *(new Gtk::Separator), false, false, WIDGETS_BORDER );
    boxBuy.pack_start( *(new Gtk::Label( "Количество:" )), false, false, WIDGETS_BORDER );
    boxBuy.pack_start( entryCount, false, false, WIDGETS_BORDER );
    entryCount.signal_activate().connect( sigc::mem_fun( *this, &WindowMain::on_button_buy_activate ) );
    entryCount.set_text( "1" );

    boxBuy.pack_start( buttonBuy, false, false, WIDGETS_BORDER );
    buttonBuy.signal_clicked().connect( sigc::mem_fun( *this, &WindowMain::on_button_buy_activate ) );
    buttonBuy.set_label( "Купить" );

    /* List of purchases */
    boxMain.pack_start( boxPurchase, true, true, WIDGETS_BORDER );
    boxPurchase.set_orientation( Gtk::ORIENTATION_VERTICAL );

    boxPurchase.pack_start( scrolledPurchases, true, true, WIDGETS_BORDER );
    scrolledPurchases.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolledPurchases.add( treePurchases );

    /* Registration of purchase */
    boxPurchase.pack_start( boxRegister, false, false, WIDGETS_BORDER );
    boxRegister.set_orientation( Gtk::ORIENTATION_VERTICAL );
    boxRegister.set_size_request( 110 );

    boxRegister.pack_start( labelTotal, false, false, WIDGETS_BORDER );
    treePurchases.set_total_cost_pointers( &floatTotal, &labelTotal );

    boxRegister.pack_start( buttonRegister, false, false, WIDGETS_BORDER );
    buttonRegister.set_label( "\nОФОРМИТЬ\n" );
    buttonRegister.signal_clicked().connect( sigc::mem_fun( *this, &WindowMain::on_button_register_activate ) );

    boxRegister.pack_start( buttonCancel, false, false, WIDGETS_BORDER );
    buttonCancel.set_label( "Отмена" );
    buttonCancel.signal_clicked().connect( sigc::mem_fun( *this, &WindowMain::on_button_cancel_activate ) );

    /* Statusbar */
    boxWindow.pack_start( statusbarMain, false, false );

    /* Run */
    show_all_children();
    on_category_choose();
    on_button_cancel_activate();
    statusbar_push( "Готовы к покупкам? :)" );
}

/*****************************************************************************
 * Set data to the statusbar.                                                 *
 ******************************************************************************
 *  takes: char* - message;                                                   *
  *****************************************************************************/

void WindowMain::statusbar_push( const char *message )
{
    statusbarMain.pop();
    statusbarMain.push( message );
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
    radio.set_label( label );
    radio.set_group( groupCategories );
    boxCategories.pack_start( radio, false, false );
    radio.signal_released().connect( sigc::mem_fun( *this, &WindowMain::on_category_choose ) );
}

/*****************************************************************************
 * Action on buy button activate.                                             *
  *****************************************************************************/

void WindowMain::on_button_buy_activate()
{
    char *section = treeGoods.get_section();
    char *id = treeGoods.get_activated_id();

    char query[ BUFFER_SIZE ];
    const char format[] = "SELECT `id`, `name`, `price`, `item` FROM `%s` WHERE `id` LIKE '%s';";
    snprintf( query, BUFFER_SIZE, format, section, id );
    std::vector<GoodsRecord> *res = execute_query_select_goods( query );

    if( res->size() != 0 ) {
        if( treeGoods.get_is_available() ) {
            Glib::ustring count = entryCount.get_text();
            if( is_number( count.c_str() ) ) {
                float f_cost = strtof( count.c_str(), NULL );
                if( f_cost > 0 ) {
                    f_cost *= strtof( res->at(0).price.c_str(), NULL );

                    char buffer[ BUFFER_SIZE ];
                    const char format[] = "%.2f грн";
                    snprintf( buffer, BUFFER_SIZE, format, f_cost );
                    Glib::ustring cost( buffer );

                    floatTotal += f_cost;
                    treePurchases.set_total_cost( floatTotal );

                    treePurchases.append_data( res->at(0).name, count, cost );
                    statusbar_push( "Добавлено в чек." );
                } else {
                    statusbar_push( "Невозможно купить 0 штук!" );
                }
            } else {
                statusbar_push( "Введите нормальное количество!" );
            }
        } else {
            statusbar_push( "Данного товара нет в наличии!" );
        }
    } else {
        statusbar_push( "Ничего не выбрано!" );
    }

    entryCount.set_text( "1" );
    delete[] section;
    delete[] id;
    delete res;
}

/*****************************************************************************
 * Action on cancel button activate.                                          *
  *****************************************************************************/

void WindowMain::on_button_cancel_activate()
{
    statusbar_push( "Отменено..." );
    treePurchases.remove_all_rows();
    treePurchases.set_total_cost( 0 );
}

/*****************************************************************************
 * Action on register button activate.                                        *
  *****************************************************************************/

void WindowMain::on_button_register_activate()
{
    if( treePurchases.get_count() != 0 ) {
        WindowRegister reg;
        int response = reg.run( floatTotal );

        if( response == 0 ) {
            /*
             *  there may be save data or something else...
             */
            on_button_cancel_activate();
            statusbar_push( "Готово!" );
        }
    } else {
        statusbar_push( "Нечего оформлять!" );
    }
}

/*****************************************************************************
 * Action on category choose. Starts when on of categories was choosed.       *
  *****************************************************************************/

void WindowMain::on_category_choose()
{
    treeGoods.set_available_state( IMG_WAIT_PATH, "Загрузка..." );
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

    char command[ BUFFER_SIZE ];
    const char format[] = "SELECT `id`, `name`, `price`, `item` FROM `%s`;";
    snprintf( command, BUFFER_SIZE, format, section );
    std::vector<GoodsRecord> *res = execute_query_select_goods( command );

    for( unsigned int i = 0; i < res->size(); i++ ) {
        treeGoods.append_data( res->at(i) );
    }

    sleep( 1 ); // just for lulz :D

    treeGoods.set_available_state( IMG_LAMP_ON_PATH, "Загружено!" );
    treeGoods.set_section( section );
    delete res;
}

/*****************************************************************************
 * Close application.                                                         *
  *****************************************************************************/

void WindowMain::quit()
{
    hide();
    /* Just hide main window, it will be destroyed automatically! */
}

