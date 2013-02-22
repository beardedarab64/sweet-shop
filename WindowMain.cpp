#include "WindowMain.h"

#include <gtkmm.h>

/* Some constants */
const char program_name[] = "Sweet Shop";
const char program_version[] = "v0.2";
const unsigned int widgets_border = 5;

WindowMain::WindowMain() {
    /* Main window preferences */
    set_title( program_name );
    set_default_size( 640, 400 );
    set_border_width( widgets_border );

    /* Main box */
    add( boxMain );
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

    /* Buy section */
    boxMain.pack_start( boxBuy, false, false, widgets_border );
    boxBuy.set_orientation( Gtk::ORIENTATION_VERTICAL );

    boxBuy.pack_start( imageAvailable, false, false, widgets_border );
    imageAvailable.set_size_request( 72, 72 );

    boxBuy.pack_start( labelAvailable, false, false, widgets_border );
    labelAvailable.set_label( "-" );

    boxBuy.pack_start( entryCount, false, false, widgets_border );

    boxBuy.pack_start( buttonBuy, false, false, widgets_border );
    buttonBuy.set_label( "Купить" );

    /* List of purchases */
    boxMain.pack_start( boxPurchase, true, true, widgets_border );
    boxBuy.set_orientation( Gtk::ORIENTATION_VERTICAL );

    boxPurchase.pack_start( scrolledPurchases, true, true, widgets_border );
    scrolledPurchases.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolledPurchases.add( treePurchases );

    /* Run */
    on_category_choose();
    show_all_children();
}

void WindowMain::create_category( Gtk::RadioButton &radio, const char *label ) {
    boxCategories.pack_start( radio, false, false );
    radio.signal_released().connect( sigc::mem_fun( *this, &WindowMain::on_category_choose ) );
    radio.set_group( groupCategories );
    radio.set_label( label );
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

