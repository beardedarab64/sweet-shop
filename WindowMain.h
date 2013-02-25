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
        void on_category_choose();
        void get_goodslist( const char * );
        void load_from_db();
        void quit();

        void lolka( const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column );

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
        TreeViewPurchases treePurchases;
};

#endif // WINDOWMAIN_H

