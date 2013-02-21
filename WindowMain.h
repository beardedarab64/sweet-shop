#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H

#include <gtkmm.h>

class WindowMain : public Gtk::Window {
    public:
        WindowMain();

    protected:
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
        Gtk::TreeView treeGoods;

        Gtk::Box boxBuy;
        Gtk::Image imageAvailable;
        Gtk::Label labelAvailable;
        Gtk::Entry entryCount;
        Gtk::Button buttonBuy;
};

#endif // WINDOWMAIN_H

