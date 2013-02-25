#include "TreeViewPurchases.h"

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

void TreeViewPurchases::remove_all_rows()
{
    treeRecords->clear();
}

void TreeViewPurchases::append_data( Glib::ustring name, Glib::ustring count, Glib::ustring cost )
{
    /* Add new row and put data in it */
    Gtk::TreeModel::Row row = *( treeRecords->append() );
    row[ treeColumns.name ] = name;
    row[ treeColumns.count ] = count;
    row[ treeColumns.cost ] = cost;
}

