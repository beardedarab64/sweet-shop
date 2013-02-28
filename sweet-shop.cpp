#include <gtkmm/application.h>
#include "WindowMain.h"
#include "sweet-shop.h"

int main( int argc, char **argv )
{
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create( argc, argv, APP_NAME );
    WindowMain win;
    return app->run( win );
}

