#ifndef GOODSCOLUMNS_H
#define GOODSCOLUMNS_H

#include <gtkmm.h>

class GoodsColumns: public Gtk::TreeModel::ColumnRecord
{
    public:
        GoodsColumns();

        Gtk::TreeModelColumn<Glib::ustring> id;
        Gtk::TreeModelColumn<Glib::ustring> name;
        Gtk::TreeModelColumn<Glib::ustring> price;
        Gtk::TreeModelColumn<Glib::ustring> item;
};

#endif // GOODSCOLUMNS_H
