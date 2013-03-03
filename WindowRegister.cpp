#include "WindowRegister.h"
#include "sweet-shop.h"

/*****************************************************************************
 * Creating window and it's components.                                       *
  *****************************************************************************/

WindowRegister::WindowRegister()
{
    set_title( WINDOW_REGISTER_TITLE );
    set_border_width( WIDGETS_BORDER );

    add_button( "ПОДТВЕРДИТЬ\nЗАКАЗ", 0 );
    add_button( "Назад", 1 );
}

