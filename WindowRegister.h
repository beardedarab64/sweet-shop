#ifndef WINDOWREGISTER_H
#define WINDOWREGISTER_H

#include <gtkmm.h>

class WindowRegister: public Gtk::Dialog
{
    public:
        WindowRegister();
        int run( float );

    private:
        Gtk::Box boxMain;
        Gtk::Label labelContent;
};

#endif // WINDOWREGISTER_H

