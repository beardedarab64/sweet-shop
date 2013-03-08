#include "WindowRegister.h"
#include "sweet-shop.h"

/*****************************************************************************
 * Creating window and it's components.                                       *
  *****************************************************************************/

WindowRegister::WindowRegister()
{
    /* Window preferences */
    set_title( WINDOW_REGISTER_TITLE );
    set_border_width( WIDGETS_BORDER );

    /* Add container in a window */
    Gtk::Box *content = get_content_area();
    content->pack_start( boxMain );
    boxMain.set_orientation( Gtk::ORIENTATION_VERTICAL );

    boxMain.pack_start( labelContent );
    boxMain.pack_start( *(new Gtk::Separator) );

    add_button( "Подтвердить заказ", 0 );
    add_button( "Назад", 1 );

    /* Show */
    content->show_all_children();
}

int WindowRegister::run( float total )
{
    char buffer[ BUFFER_SIZE ];
    const char format[] = "<span font_desc=\"32\">Итого: %.2f грн</span>";
    snprintf( buffer, BUFFER_SIZE, format, total );
    labelContent.set_markup( buffer );
    return Gtk::Dialog::run();
}

