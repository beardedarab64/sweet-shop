#ifndef DATABASE_H
#define DATABASE_H

#include <glibmm.h>
#include <vector>

#define ERROR_BUFFER_SIZE 128

typedef struct GoodsRecord_t {
    Glib::ustring id;
    Glib::ustring name;
    Glib::ustring price;
    Glib::ustring item;
} GoodsRecord;

std::vector<GoodsRecord> *execute_query_select( const char * );

#endif // DATABASE_H
