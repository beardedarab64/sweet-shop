#include "TreeViewPurchases.h"

/*****************************************************************************
 * Creating columns for purchases description.                                *
  *****************************************************************************/

TreeViewPurchases::TreeViewPurchases()
{
    /* Create tree */
    treeRecords = Gtk::ListStore::create( treeColumns );
    set_model( treeRecords );

    /* Create columns */
    append_column( "Наименование", treeColumns.name );
    append_column( "Кол-во", treeColumns.count );
    append_column( "Стоимость", treeColumns.cost );

    /* Create popup menu */
    Gtk::MenuItem* item = Gtk::manage( new Gtk::MenuItem( "Удалить" ) );
    item->signal_activate().connect( sigc::mem_fun( *this, &TreeViewPurchases::on_menu_file_popup_generic ) );
    menuPopup.append( *item );
    menuPopup.accelerate( *this );
    menuPopup.show_all();

    /* Connect press event signal (mouse clicks) */
    signal_button_press_event().connect( sigc::mem_fun( *this, &TreeViewPurchases::on_button_press_event ), false );
}

/*****************************************************************************
 * Clear list of purchases.                                                   *
  *****************************************************************************/

void TreeViewPurchases::remove_all_rows()
{
    treeRecords->clear();
}

/*****************************************************************************
 * Adding new record to the purchases list.                                   *
 ******************************************************************************
 *  takes: struct PurchasesRecord - record data;                              *
  *****************************************************************************/

void TreeViewPurchases::append_data( PurchasesRecord &src )
{
    append_data( src.name, src.count, src.cost );
}

/*****************************************************************************
 * Adding new record to the purchases list (as above).                        *
 ******************************************************************************
 *  takes: ustring - product name;                                            *
 *         ustring - count of products;                                       *
 *         ustring - total cost;                                              *
  *****************************************************************************/

void TreeViewPurchases::append_data( Glib::ustring &name,
                                     Glib::ustring &count,
                                     Glib::ustring &cost )
{
    /* Add new row and put data in it */
    Gtk::TreeModel::Row row = *( treeRecords->append() );
    row[ treeColumns.name ] = name;
    row[ treeColumns.count ] = count;
    row[ treeColumns.cost ] = cost;
}

/*****************************************************************************
 * Removing product from list.                                                *
  *****************************************************************************/

void TreeViewPurchases::on_menu_file_popup_generic()
{
    if( Glib::RefPtr<Gtk::TreeView::Selection> selection = get_selection() ) {
        if( Gtk::TreeModel::iterator iter = selection->get_selected() ) {
            treeRecords->erase( iter );
        }
    }
}

/*****************************************************************************
 * Button press handler. Starts when one of items clicked.                    *
  *****************************************************************************/

bool TreeViewPurchases::on_button_press_event( GdkEventButton *event )
{
    if( ( event->type == GDK_BUTTON_PRESS ) && ( event->button == 3 ) ) {
        menuPopup.popup( event->button, event->time );
    }

    return TreeView::on_button_press_event( event );
}

