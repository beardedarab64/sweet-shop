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
