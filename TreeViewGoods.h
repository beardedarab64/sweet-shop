#ifndef TREEVIEWGOODS_H
#define TREEVIEWGOODS_H

#include <gtkmm.h>
#include "GoodsColumns.h"

class TreeViewGoods : public Gtk::TreeView {
    public:
        TreeViewGoods();
        void remove_all_rows();
        void append_data( Glib::ustring, Glib::ustring, Glib::ustring, Glib::ustring );

    private:
        GoodsColumns treeColumns;
        Glib::RefPtr<Gtk::ListStore> treeRecords;
};

#endif // TREEVIEWGOODS_H

