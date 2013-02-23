#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H

#include <gtkmm.h>
#include "TreeViewGoods.h"

class WindowMain : public Gtk::Window {
    public:
        WindowMain();

    protected:
        void create_category( Gtk::RadioButton &, const char * );
        void on_category_choose();
        void load_from_db();
        void quit();

    private:
        Gtk::Box boxMain;

        Gtk::Box boxCategories;
        Gtk::RadioButton radioCakes;
        Gtk::RadioButton radioCandy;
        Gtk::RadioButton radioCoockies;
        Gtk::RadioButton radioJujube;
        Gtk::RadioButton::Group groupCategories;

        Gtk::ScrolledWindow scrolledGoods;
        TreeViewGoods treeGoods;

        Gtk::Box boxBuy;
        Gtk::Image imageAvailable;
        Gtk::Label labelAvailable;
        Gtk::Entry entryCount;
        Gtk::Button buttonBuy;

        Gtk::Box boxPurchase;
        Gtk::ScrolledWindow scrolledPurchases;
        Gtk::TreeView treePurchases;  /** TODO: Make new class! */
};

#endif // WINDOWMAIN_H

