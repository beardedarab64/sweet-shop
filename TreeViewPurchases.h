#ifndef TREEVIEWPURCHASES_H
#define TREEVIEWPURCHASES_H

#include <gtkmm.h>
#include "PurchasesColumns.h"

class TreeViewPurchases: public Gtk::TreeView
{
    public:
        TreeViewPurchases();
        void remove_all_rows();
        void append_data( Glib::ustring, Glib::ustring, Glib::ustring, Glib::ustring );

    private:
        PurchasesColumns treeColumns;
        Glib::RefPtr<Gtk::ListStore> treeRecords;
};

#endif // TREEVIEWPURCHASES_H
