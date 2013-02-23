#ifndef GOODSCOLUMNS_H
#define GOODSCOLUMNS_H

#include <gtkmm.h>

class GoodsColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        GoodsColumns();

        Gtk::TreeModelColumn<unsigned int> id;
        Gtk::TreeModelColumn<Glib::ustring> name;
        Gtk::TreeModelColumn<double> price;
        Gtk::TreeModelColumn<Glib::ustring> item;
};

#endif // GOODSCOLUMNS_H
