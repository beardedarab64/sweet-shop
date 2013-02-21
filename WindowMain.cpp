#include "WindowMain.h"

#include <gtkmm.h>

WindowMain::WindowMain() {
    set_title( "Sweet-shop :)" );
    set_border_width(5);
    set_default_size(800, 480);
}

void WindowMain::quit() {
    hide();
}

