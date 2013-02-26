#include "WindowInform.h"
#include "database.h"

const unsigned int widgets_border = 5;

WindowInform::WindowInform()
{
    set_title( "Подробности" );
    set_border_width( widgets_border );
    set_default_size( 300, 200 );

    add( boxWindow );

    show();
}

