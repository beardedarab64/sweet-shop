#ifndef TREEVIEWGOODS_H
#define TREEVIEWGOODS_H

#include <gtkmm.h>
#include "GoodsColumns.h"

class TreeViewGoods : public Gtk::TreeView {
    public:
        TreeViewGoods();

    protected:
        //

    private:
        GoodsColumns treeColumns;
        Glib::RefPtr<Gtk::ListStore> treeRecords;
};

#endif // TREEVIEWGOODS_H

