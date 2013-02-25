#include <gtkmm/application.h>
#include "WindowMain.h"

int main( int argc, char **argv )
{
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create( argc, argv, "com.sweet-shop" );
    WindowMain win;
    return app->run( win );
}

