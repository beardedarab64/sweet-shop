#ifndef TREEVIEWGOODS_H
#define TREEVIEWGOODS_H

#include <gtkmm.h>
#include "GoodsColumns.h"

class TreeViewGoods: public Gtk::TreeView
{
    public:
        TreeViewGoods();
        void remove_all_rows();
        void append_data( Glib::ustring, Glib::ustring, Glib::ustring, Glib::ustring );

    protected:
        virtual bool on_button_press_event( GdkEventButton * );
        void on_menu_file_popup_generic();

    private:
        GoodsColumns treeColumns;
        Glib::RefPtr<Gtk::ListStore> treeRecords;
        Gtk::Menu menuPopup;
};

#endif // TREEVIEWGOODS_H

