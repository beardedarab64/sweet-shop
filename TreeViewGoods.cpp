#include "TreeViewGoods.h"
#include <cstdlib>

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
    // show new window with description
}

bool TreeViewGoods::on_button_press_event( GdkEventButton *event )
{
    bool return_value = TreeView::on_button_press_event( event );

    if( ( event->type == GDK_BUTTON_PRESS ) && ( event->button == 1 ) )
    {
        imageAvailable->set( "data/img/wait.gif" );
        labelAvailable->set_label( "Проверка наличия..." );
        Glib::Thread::create( sigc::mem_fun( *this, &TreeViewGoods::check_available ) );
    }
    else if( ( event->type == GDK_BUTTON_PRESS ) && ( event->button == 3 ) )
    {
        menuPopup.popup( event->button, event->time );
    }

    return return_value;
}

void TreeViewGoods::check_available()
{
    sleep( 1 );

    if( ( rand() & 1 ) == 0 )
    {
        imageAvailable->set( "data/img/lamp_on.png" );
        labelAvailable->set_label( "Есть в наличии!" );
    } else {
        imageAvailable->set( "data/img/lamp_off.png" );
        labelAvailable->set_label( "Нет в наличии!" );
    }
}

void TreeViewGoods::set_available( Gtk::Image * image, Gtk::Label * label )
{
    imageAvailable = image;
    labelAvailable = label;
}

