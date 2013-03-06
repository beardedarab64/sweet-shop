#ifndef TREEVIEWPURCHASES_H
#define TREEVIEWPURCHASES_H

#include <gtkmm.h>
#include "PurchasesColumns.h"
#include "sweet-shop.h"

class TreeViewPurchases: public Gtk::TreeView
{
    public:
        TreeViewPurchases();
        void remove_all_rows();
        void append_data( PurchasesRecord & );
        void append_data( Glib::ustring &, Glib::ustring &, Glib::ustring & );
        void set_total_cost_pointers( float *, Gtk::Label * );
        void set_total_cost( float );
        int get_count();

    protected:
        bool on_button_press_event( GdkEventButton * );
        void on_menu_file_popup_generic();

    private:
        Gtk::Menu menuPopup;
        int countOfProducts;
        PurchasesColumns treeColumns;
        Glib::RefPtr<Gtk::ListStore> treeRecords;

        float *floatTotal;
        Gtk::Label *labelTotal;
};

#endif // TREEVIEWPURCHASES_H

