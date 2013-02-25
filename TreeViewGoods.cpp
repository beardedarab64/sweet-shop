#include "TreeViewGoods.h"

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

    Gtk::MenuItem* item = Gtk::manage( new Gtk::MenuItem( "Подробнее" ) );
    item->signal_activate().connect( sigc::mem_fun( *this, &TreeViewGoods::on_menu_file_popup_generic ) );
    menuPopup.append( *item );
    menuPopup.accelerate( *this );
    menuPopup.show_all();

#ifndef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
  signal_button_press_event()
    .connect(sigc::mem_fun(*this, &TreeViewGoods::on_button_press_event), false);
#endif
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
    g_print( "Yeah!\n" );
}

bool TreeViewGoods::on_button_press_event( GdkEventButton *event )
{
    g_print("попал таки\n");
    bool return_value = false;
    return_value = TreeView::on_button_press_event( event );

    if( ( event->type == GDK_BUTTON_PRESS ) && ( event->button == 3 ) )
    {
        g_print( "suck\n" );
        menuPopup.popup( event->button, event->time );
    }

    return return_value;
}


