#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H

#include <gtkmm.h>

class WindowMain : public Gtk::Window {
    public:
        WindowMain();

    protected:
        void quit();

    private:
        //
};

#endif // WINDOWMAIN_H

