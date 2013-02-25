#include "database.h"
#include <sqlite3.h>

int execute_query( const char *query )
{
    sqlite3 *pDB;

    if( sqlite3_open( "data/goods.db", &pDB ) == SQLITE_OK )
    {
        sqlite3_close( pDB );
    }

    return 0;
}

