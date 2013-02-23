#include "TreeViewGoods.h"

TreeViewGoods::TreeViewGoods() {
    /* Create tree */
    treeRecords = Gtk::ListStore::create( treeColumns );
    set_model( treeRecords );

    /* Create columns */
    append_column( "N", treeColumns.id );
    append_column( "Наименование", treeColumns.name );
    append_column( "Цена", treeColumns.price );
    append_column( "Ед.Изм.", treeColumns.item );
}

void TreeViewGoods::append_data( Glib::ustring id, Glib::ustring name,
                                 Glib::ustring price, Glib::ustring item ) {
    Gtk::TreeModel::Row row = *( treeRecords->append() );
    row[ treeColumns.id ] = id;
    row[ treeColumns.name ] = name;
    row[ treeColumns.price ] = price;
    row[ treeColumns.item ] = item;
}

