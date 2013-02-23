#include "TreeViewGoods.h"

TreeViewGoods::TreeViewGoods()
{
    treeRecords = Gtk::ListStore::create( treeColumns );
    set_model( treeRecords );

    append_column( "N", treeColumns.id );
    append_column( "Наименование", treeColumns.name );
    append_column( "Цена", treeColumns.price );
    append_column( "Ед.Изм.", treeColumns.item );

    /* test row */
    Gtk::TreeModel::Row row = *( treeRecords->append() );
    row[ treeColumns.id ] = 1;
    row[ treeColumns.name ] = "SomeTORT";
    row[ treeColumns.price ] = 35.50;
    row[ treeColumns.item ] = "кг";
}

