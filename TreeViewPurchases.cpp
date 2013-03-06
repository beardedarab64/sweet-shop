#include "TreeViewPurchases.h"
#include <cstdio>

/*****************************************************************************
 * Creating columns for purchases description.                                *
  *****************************************************************************/

TreeViewPurchases::TreeViewPurchases()
{
    /* Create tree */
    treeRecords = Gtk::ListStore::create( treeColumns );
    set_model( treeRecords );
    countOfProducts = 0;

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
    countOfProducts = 0;
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
    countOfProducts++;
}

/*****************************************************************************
 * Set some variables.                                                        *
 ******************************************************************************
 *  %one more bicycle%                                                        *
  *****************************************************************************/

void TreeViewPurchases::set_total_cost_pointers( float *total, Gtk::Label *label )
{
    floatTotal = total;
    labelTotal = label;
}

/*****************************************************************************
 * Set total cost value (in label).                                           *
 ******************************************************************************
 *  takes: float - cost;                                                      *
  *****************************************************************************/

void TreeViewPurchases::set_total_cost( float cost )
{
    *floatTotal = cost;

    char buffer[ COMMAND_BUFFER_SIZE ];
    sprintf( buffer, "Итого:  %.2f грн", cost );
    labelTotal->set_text( buffer );
}

/*****************************************************************************
 * Get count of a products in purchases list.                                 *
 ******************************************************************************
 *  returns: int - count of products;                                         *
  *****************************************************************************/

int TreeViewPurchases::get_count()
{
    return countOfProducts;
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

