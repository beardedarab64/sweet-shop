#include "TreeViewGoods.h"
#include "WindowInform.h"
#include <cstring>
#include <cstdio>

/*****************************************************************************
 * Creating columns for goods description.                                    *
  *****************************************************************************/

TreeViewGoods::TreeViewGoods()
{
    /* Create tree */
    treeRecords = Gtk::ListStore::create( treeColumns );
    set_model( treeRecords );

    /* Create columns */
    append_column( "Код", treeColumns.id );
    append_column( "Наименование", treeColumns.name );
    append_column( "Цена", treeColumns.price );
    append_column( "Ед.Изм.", treeColumns.item );

    /* Create popup menu */
    Gtk::MenuItem* item = Gtk::manage( new Gtk::MenuItem( "Подробнее" ) );
    item->signal_activate().connect( sigc::mem_fun( *this, &TreeViewGoods::on_menu_file_popup_generic ) );
    menuPopup.append( *item );
    menuPopup.accelerate( *this );
    menuPopup.show_all();

    /* Connect press event signal (mouse clicks) */
    signal_button_press_event().connect( sigc::mem_fun( *this, &TreeViewGoods::on_button_press_event ), false );
}

/*****************************************************************************
 * Clear list of goods.                                                       *
  *****************************************************************************/

void TreeViewGoods::remove_all_rows()
{
    treeRecords->clear();
}

/*****************************************************************************
 * Adding new record to the goods list (overloaded).                          *
 ******************************************************************************
 *  takes: struct GoodsRecord - record data;                                  *
  *****************************************************************************/

void TreeViewGoods::append_data( GoodsRecord &src )
{
    append_data( src.id, src.name, src.price, src.item );
}

/*****************************************************************************
 * Adding new record to the goods list (as above).                            *
 ******************************************************************************
 *  takes: ustring - product id;                                              *
 *         ustring - product name;                                            *
 *         ustring - price;                                                   *
 *         ustring - item (unit of measurement);                              *
  *****************************************************************************/

void TreeViewGoods::append_data( Glib::ustring &id,
                                 Glib::ustring &name,
                                 Glib::ustring &price,
                                 Glib::ustring &item )
{
    /* Add new row and put data in it */
    Gtk::TreeModel::Row row = *( treeRecords->append() );
    row[ treeColumns.id ] = id;
    row[ treeColumns.name ] = name;
    row[ treeColumns.price ] = price;
    row[ treeColumns.item ] = item;
}

/*****************************************************************************
 * Creating new window with product description.                              *
  *****************************************************************************/

void TreeViewGoods::on_menu_file_popup_generic()
{
    WindowInform information;
    information.run();
}

/*****************************************************************************
 * Button press handler. Starts when one of items clicked.                    *
  *****************************************************************************/

bool TreeViewGoods::on_button_press_event( GdkEventButton *event )
{
    if( ( event->type == GDK_BUTTON_PRESS ) && ( event->button == 1 ) ) {
        set_available_state( IMG_WAIT_PATH, "Проверка наличия..." );
        /* Checking available in separate thread */
        Glib::Thread::create( sigc::mem_fun( *this, &TreeViewGoods::check_available ) );
    }
    else if( ( event->type == GDK_BUTTON_PRESS ) && ( event->button == 3 ) ) {
        menuPopup.popup( event->button, event->time );
    }

    return TreeView::on_button_press_event( event );
}

/*****************************************************************************
 * Set some variables.                                                        *
 ******************************************************************************
 *  %bicycle%                                                                 *
  *****************************************************************************/

void TreeViewGoods::set_available_pointers( Gtk::Image *image, Gtk::Label *label )
{
    imageAvailable = image;
    labelAvailable = label;
}

/*****************************************************************************
 * Setting progress state (image and text in label).                          *
 ******************************************************************************
 *  takes: char* - image filename;                                            *
 *         char* - text for label;                                            *
  *****************************************************************************/

void TreeViewGoods::set_available_state( const char *image_filename, const char *text )
{
    try {
        labelAvailable->set_text( text );
        imageAvailable->set( image_filename );
    } catch(...) {
        g_warning( "HUSTON, WE HAVE A PROBLEM!\n" );
    }
}

/*****************************************************************************
 * Setting name of the current choosed section.                               *
 ******************************************************************************
 *  takes: char* - section name;                                              *
  *****************************************************************************/

void TreeViewGoods::set_section( const char *name )
{
    goodsSection = name;
}

/*****************************************************************************
 * Check is product exists.                                                   *
  *****************************************************************************/

void TreeViewGoods::check_available()
{
    g_print("section = %s\n",goodsSection);
    usleep( 500000 ); // just for lulz :D - 0,5s

    char *query = new char[ COMMAND_BUFFER_SIZE ];
    char *activated_id = get_activated_id();

    sprintf( query, "SELECT `available` FROM `%s` WHERE `id` LIKE '%s';", goodsSection, activated_id );
    int available = execute_query_select_available( query );

    if( available ) {
        is_available = true;
        set_available_state( IMG_LAMP_ON_PATH, "Есть в наличии!" );
    } else {
        is_available = false;
        set_available_state( IMG_LAMP_OFF_PATH, "Нет в наличии!" );
    }

    delete[] activated_id;
    delete[] query;
}

/*****************************************************************************
 * Get section of the activated item.                                         *
 ******************************************************************************
 *  returns: char* - section name;                                            *
  *****************************************************************************/

char *TreeViewGoods::get_section()
{
    return strdup( goodsSection );
}

/*****************************************************************************
 * Get `id` of the activated item.                                            *
 ******************************************************************************
 *  returns: char* - if item activated;                                       *
 *           NULL - else;                                                     *
  *****************************************************************************/

char *TreeViewGoods::get_activated_id()
{
    if( Glib::RefPtr<Gtk::TreeView::Selection> selection = get_selection() ) {
        if( Gtk::TreeModel::iterator iter = selection->get_selected() ) {
            Glib::ustring id = ( *iter )[ treeColumns.id ];
            return strdup( id.c_str() );
        }
    }

    return NULL;
}

bool TreeViewGoods::get_is_available()
{
    return is_available;
}
