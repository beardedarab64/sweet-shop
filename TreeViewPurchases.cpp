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

void TreeViewPurchases::append_data( PurchasesRecord src )
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

void TreeViewPurchases::append_data( Glib::ustring name,
                                     Glib::ustring count,
                                     Glib::ustring cost )
{
    /* Add new row and put data in it */
    Gtk::TreeModel::Row row = *( treeRecords->append() );
    row[ treeColumns.name ] = name;
    row[ treeColumns.count ] = count;
    row[ treeColumns.cost ] = cost;
}

