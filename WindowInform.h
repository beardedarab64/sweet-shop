#ifndef WINDOWINFORM_H
#define WINDOWINFORM_H

#include <gtkmm.h>

class WindowInform: public Gtk::Dialog
{
    public:
        WindowInform();

    private:
        Gtk::Button buttonOk;
};

#endif // WINDOWINFORM_H
