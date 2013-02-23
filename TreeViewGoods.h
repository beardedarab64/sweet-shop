#ifndef TREEVIEWGOODS_H
#define TREEVIEWGOODS_H

#include <gtkmm.h>
#include "GoodsColumns.h"

typedef struct GColumnsModel_t {
} GColumnsModel;

class TreeViewGoods : public Gtk::TreeView {
    public:
        TreeViewGoods();
        void append_data( Glib::ustring, Glib::ustring, Glib::ustring, Glib::ustring );

    protected:
        //

    private:
        GoodsColumns treeColumns;
        Glib::RefPtr<Gtk::ListStore> treeRecords;
};

#endif // TREEVIEWGOODS_H

