#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H

#include <gtkmm.h>
#include "TreeViewGoods.h"
#include "TreeViewPurchases.h"

class WindowMain: public Gtk::Window
{
    public:
        WindowMain();

    protected:
        void create_category( Gtk::RadioButton &, const char * );
        void on_button_buy_activate();
        void on_category_choose();
        void fill_goodslist();
        void quit();

    private:
        Gtk::Box boxWindow;
        Gtk::Statusbar statusbarMain;

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
        TreeViewPurchases treePurchases;
};

#endif // WINDOWMAIN_H

