#ifndef TREEVIEWGOODS_H
#define TREEVIEWGOODS_H

#include <gtkmm.h>
#include "GoodsColumns.h"
#include "sweet-shop.h"
#include "database.h"

class TreeViewGoods: public Gtk::TreeView
{
    public:
        TreeViewGoods();
        void remove_all_rows();
        void append_data( GoodsRecord & );
        void append_data( Glib::ustring &, Glib::ustring &, Glib::ustring &, Glib::ustring & );
        void set_available( Gtk::Image *, Gtk::Label * );
        void set_section( const char * );
        void check_available();
        char *get_section();
        char *get_activated_id();
        bool get_is_available();

    protected:
        bool on_button_press_event( GdkEventButton * );
        void on_menu_file_popup_generic();

    private:
        Gtk::Menu menuPopup;
        GoodsColumns treeColumns;
        Glib::RefPtr<Gtk::ListStore> treeRecords;

        bool is_available;
        Gtk::Image *imageAvailable;
        Gtk::Label *labelAvailable;
        const char *goodsSection;
};

#endif // TREEVIEWGOODS_H

