#ifndef WINDOWINFORM_H
#define WINDOWINFORM_H

#include <gtkmm.h>

class WindowInform: public Gtk::Window
{
    public:
        WindowInform();

    private:
        Gtk::Box boxWindow;
};

#endif // WINDOWINFORM_H
