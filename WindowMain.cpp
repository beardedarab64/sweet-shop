#include "WindowMain.h"

#include <gtkmm.h>

WindowMain::WindowMain() {
    /* Some constants */
    const unsigned int widgets_border = 5;

    /* Main window preferences */
    set_title( "Sweet Shop v0.1" );
    set_default_size( 640, 480 );
    set_border_width( widgets_border );

    /* Main box */
    add( boxMain );
    boxMain.set_border_width( widgets_border );
    boxMain.set_orientation( Gtk::ORIENTATION_HORIZONTAL );

    /* Categories of goods */
    boxMain.pack_start( boxCategories, false, false, widgets_border );
    boxCategories.set_orientation( Gtk::ORIENTATION_VERTICAL );

    boxCategories.pack_start( radioCakes, false, false );
    radioCakes.signal_released().connect( sigc::mem_fun( *this, &WindowMain::on_category_choose ) );
    radioCakes.set_group( groupCategories );
    radioCakes.set_label( "Торты" );

    boxCategories.pack_start( radioCandy, false, false );
    radioCandy.signal_released().connect( sigc::mem_fun( *this, &WindowMain::on_category_choose ) );
    radioCandy.set_group( groupCategories );
    radioCandy.set_label( "Конфеты" );

    boxCategories.pack_start( radioCoockies, false, false );
    radioCoockies.signal_released().connect( sigc::mem_fun( *this, &WindowMain::on_category_choose ) );
    radioCoockies.set_group( groupCategories );
    radioCoockies.set_label( "Печенье" );

    boxCategories.pack_start( radioJujube, false, false );
    radioJujube.signal_released().connect( sigc::mem_fun( *this, &WindowMain::on_category_choose ) );
    radioJujube.set_group( groupCategories );
    radioJujube.set_label( "Мармелад" );

    /* List of goods */
    boxMain.pack_start( scrolledGoods, true, true, widgets_border );
    scrolledGoods.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolledGoods.add( treeGoods );

    /* Buy section */
    boxMain.pack_start( boxBuy, false, false, widgets_border );
    boxBuy.set_orientation( Gtk::ORIENTATION_VERTICAL );

    boxBuy.pack_start( imageAvailable, false, false, widgets_border );
    imageAvailable.set( "data/img/wait.gif" );

    boxBuy.pack_start( labelAvailable, false, false, widgets_border );
    labelAvailable.set_label( "Проверка наличия..." );

    boxBuy.pack_start( entryCount, false, false, widgets_border );

    boxBuy.pack_start( buttonBuy, false, false, widgets_border );
    buttonBuy.set_label( "Купить >>" );

    boxBuy.pack_start( buttonRemove, false, false, widgets_border );
    buttonRemove.set_label( "Удалить <<" );

    /* List of purchases */
    boxMain.pack_start( boxPurchase, true, true, widgets_border );
    boxBuy.set_orientation( Gtk::ORIENTATION_VERTICAL );

    boxPurchase.pack_start( scrolledPurchases, true, true, widgets_border );
    scrolledPurchases.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolledPurchases.add( treePurchases );

    /* Run */
    show_all_children();
}

void WindowMain::on_category_choose() {
    if( radioCakes.get_active() ) {
        g_print( "Cakes\n" );
    } else if( radioCandy.get_active() ) {
        g_print( "Candy\n" );
    } else if( radioCoockies.get_active() ) {
        g_print( "Coockies\n" );
    } else if( radioJujube.get_active() ) {
        g_print( "Jujube\n" );
    } else {
        g_print( "What a f...? o_O\n" );
    }
}

void WindowMain::quit() {
    /* Just hide main window, it will be destroyed automatically! */
    hide();
}

