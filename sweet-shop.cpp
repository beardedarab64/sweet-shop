#include <gtkmm/application.h>
#include "WindowMain.h"

int main( int argc, char **argv )
{
    const char app_name[] = "com.sweet-shop";
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create( argc, argv, app_name );
    WindowMain win;
    return app->run( win );
}

