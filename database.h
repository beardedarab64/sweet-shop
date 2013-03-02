#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <glibmm.h>
#include <vector>

typedef struct GoodsRecord_t {
    Glib::ustring id;
    Glib::ustring name;
    Glib::ustring price;
    Glib::ustring item;
} GoodsRecord;

sqlite3 *open_database( const char * );
void close_database( sqlite3 * );

std::vector<GoodsRecord> *execute_query_select_goods( const char * );
int execute_query_select_available( const char * );
char *execute_query_insert( const char * );

#endif // DATABASE_H
