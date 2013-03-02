#ifndef DATABASE_H
#define DATABASE_H

#include "sweet-shop.h"
#include <sqlite3.h>
#include <vector>

sqlite3 *open_database( const char * );
void close_database( sqlite3 * );

std::vector<GoodsRecord> *execute_query_select_goods( const char * );
int execute_query_select_available( const char * );

#endif // DATABASE_H

