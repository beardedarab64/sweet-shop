#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H

#include <gtkmm.h>

class WindowMain : public Gtk::Window {
    public:
        WindowMain();

    protected:
        void create_category( Gtk::RadioButton &, const char * );
        void on_category_choose();
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
        Gtk::TreeView treeGoods; /** TODO: Make new class! */

        Gtk::Box boxBuy;
        Gtk::Image imageAvailable;
        Gtk::Label labelAvailable;
        Gtk::Entry entryCount;
        Gtk::Button buttonBuy;
        Gtk::Button buttonRemove;

        Gtk::Box boxPurchase;
        Gtk::ScrolledWindow scrolledPurchases;
        Gtk::TreeView treePurchases;  /** TODO: Make new class! */
};

#endif // WINDOWMAIN_H

