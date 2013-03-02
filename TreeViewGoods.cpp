#include "TreeViewGoods.h"
#include "WindowInform.h"
#include "sweet-shop.h"
#include <stdio.h>

TreeViewGoods::TreeViewGoods()
{
    /* Create tree */
    treeRecords = Gtk::ListStore::create( treeColumns );
    set_model( treeRecords );

    /* Create columns */
    append_column( "Код", treeColumns.id );
    append_column( "Наименование", treeColumns.name );
    append_column( "Цена", treeColumns.price );
    append_column( "Ед.Изм.", treeColumns.item );

    /* Create popup menu */
    Gtk::MenuItem* item = Gtk::manage( new Gtk::MenuItem( "Подробнее" ) );
    item->signal_activate().connect( sigc::mem_fun( *this, &TreeViewGoods::on_menu_file_popup_generic ) );
    menuPopup.append( *item );
    menuPopup.accelerate( *this );
    menuPopup.show_all();

    /* Connect press event signal (mouse clicks) */
    signal_button_press_event().connect( sigc::mem_fun( *this, &TreeViewGoods::on_button_press_event ), false );
}

void TreeViewGoods::remove_all_rows()
{
    treeRecords->clear();
}

void TreeViewGoods::append_data( GoodsRecord src )
{
    append_data( src.id, src.name, src.price, src.item );
}

void TreeViewGoods::append_data( Glib::ustring id, Glib::ustring name, Glib::ustring price, Glib::ustring item )
{
    /* Add new row and put data in it */
    Gtk::TreeModel::Row row = *( treeRecords->append() );
    row[ treeColumns.id ] = id;
    row[ treeColumns.name ] = name;
    row[ treeColumns.price ] = price;
    row[ treeColumns.item ] = item;
}

void TreeViewGoods::on_menu_file_popup_generic()
{
    WindowInform information;
    // x3
}

bool TreeViewGoods::on_button_press_event( GdkEventButton *event )
{
    bool return_value = TreeView::on_button_press_event( event );

    if( ( event->type == GDK_BUTTON_PRESS ) && ( event->button == 1 ) ) {
        imageAvailable->set( IMG_WAIT_PATH );
        labelAvailable->set_label( "Проверка наличия..." );
        Glib::Thread::create( sigc::mem_fun( *this, &TreeViewGoods::check_available ) );
    }
    else if( ( event->type == GDK_BUTTON_PRESS ) && ( event->button == 3 ) ) {
        menuPopup.popup( event->button, event->time );
    }

    return return_value;
}

void TreeViewGoods::check_available()
{
    sleep( 1 ); // just for lulz :D

    char *query = new char[ COMMAND_BUFFER_SIZE ];
    char *activated_id = get_activated_id();

    sprintf( query, "SELECT `available` FROM `%s` WHERE `id` LIKE '%s';", goodsSection, activated_id );
    g_print("%s\n",query);
    int available = execute_query_select_available( query );

    if( available ) {
        imageAvailable->set( IMG_LAMP_ON_PATH );
        labelAvailable->set_label( "Есть в наличии!" );
    }
    else {
        imageAvailable->set( IMG_LAMP_OFF_PATH );
        labelAvailable->set_label( "Нет в наличии!" );
    }

    delete[] activated_id;
    delete[] query;
}

void TreeViewGoods::set_available( Gtk::Image *image, Gtk::Label *label )
{
    imageAvailable = image;
    labelAvailable = label;
}

void TreeViewGoods::set_section( const char *name )
{
    goodsSection = name;
}

/*****************************************************************************
 *  Get `id` of the activated item.                                           *
 ******************************************************************************
 *  returns: char* - if item activated                                        *
 *           NULL  - else                                                     *
  *****************************************************************************/

char *TreeViewGoods::get_activated_id()
{
    if( Glib::RefPtr<Gtk::TreeView::Selection> selection = get_selection() ) {
        if( Gtk::TreeModel::iterator iter = selection->get_selected() ) {
            Glib::ustring id = ( *iter )[ treeColumns.id ];
            return strdup( id.c_str() );
        }
    }

    return NULL;
}

