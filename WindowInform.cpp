#include "WindowInform.h"
#include "sweet-shop.h"

/*****************************************************************************
 * Creating window and it's components.                                       *
  *****************************************************************************/

WindowInform::WindowInform()
{
    set_title( WINDOW_INFORM_TITLE );
    set_border_width( WIDGETS_BORDER );
    set_modal();

    add_label( "Немного описания, например..." );
    add_button( "Закрыть", 0 );
}

