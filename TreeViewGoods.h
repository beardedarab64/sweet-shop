#ifndef TREEVIEWGOODS_H
#define TREEVIEWGOODS_H

#include <gtkmm.h>
#include "GoodsColumns.h"
#include "database.h"

class TreeViewGoods: public Gtk::TreeView
{
    public:
        TreeViewGoods();
        void remove_all_rows();
        void append_data( GoodsRecord );
        void append_data( Glib::ustring, Glib::ustring, Glib::ustring, Glib::ustring );
        void check_available();
        void set_available( Gtk::Image *, Gtk::Label * );
        char *get_activated();

    protected:
        bool on_button_press_event( GdkEventButton * );
        void on_menu_file_popup_generic();

    private:
        Gtk::Menu menuPopup;
        GoodsColumns treeColumns;
        Glib::RefPtr<Gtk::ListStore> treeRecords;

        Gtk::Image *imageAvailable;
        Gtk::Label *labelAvailable;
};

#endif // TREEVIEWGOODS_H

