#include "WindowInform.h"
#include "sweet-shop.h"

/*****************************************************************************
 * Creating window and it's components.                                       *
  *****************************************************************************/

WindowInform::WindowInform()
{
    set_title( WINDOW_INFORM_TITLE );
    set_border_width( WIDGETS_BORDER );

    add_button( "А не робит!", 0 );
}

