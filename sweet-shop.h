#ifndef SWEET_SHOP_H_INCLUDED
#define SWEET_SHOP_H_INCLUDED

#include <glibmm.h>

/* Program unique name */
#define APP_NAME                        "com.sweet-shop"

/* Window's titles */
#define WINDOW_MAIN_TITLE               "Sweet Shop"
#define WINDOW_INFORM_TITLE             "Подробности"

/* Global numeric constants */
#define ERROR_BUFFER_SIZE               128
#define COMMAND_BUFFER_SIZE             128

#define WIDGETS_BORDER                  5

/* Filenames */
#define DATABASE_PATH                   "data/goods.db"
#define IMG_WAIT_PATH                   "data/img/wait.gif"
#define IMG_LAMP_OFF_PATH               "data/img/lamp_off.png"
#define IMG_LAMP_ON_PATH                "data/img/lamp_on.png"
#define WINDOW_MAIN_ICON                "data/img/icon.png"

/* User's types */
typedef struct GoodsRecord_t {
    Glib::ustring id;
    Glib::ustring name;
    Glib::ustring price;
    Glib::ustring item;
} GoodsRecord;

typedef struct PurchasesRecord_t {
    Glib::ustring name;
    Glib::ustring count;
    Glib::ustring cost;
} PurchasesRecord;

#endif // SWEET_SHOP_H_INCLUDED
