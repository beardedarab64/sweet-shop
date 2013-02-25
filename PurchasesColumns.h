#ifndef PURCHASESCOLUMNS_H
#define PURCHASESCOLUMNS_H

#include <gtkmm.h>

class PurchasesColumns: public Gtk::TreeModel::ColumnRecord
{
    public:
        PurchasesColumns();

        Gtk::TreeModelColumn<Glib::ustring> name;
        Gtk::TreeModelColumn<Glib::ustring> count;
        Gtk::TreeModelColumn<Glib::ustring> cost;
};

#endif // PURCHASESCOLUMNS_H

