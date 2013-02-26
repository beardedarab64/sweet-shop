#include "database.h"
#include <sqlite3.h>

int select_callback( void *result, int argc, char **argv, char **col )
{
    std::vector<GoodsRecord> *res = (std::vector<GoodsRecord> *) result;
    int i = 0;

    while( i < argc )
    {
        GoodsRecord temp;
        temp.id = argv[ i++ ];
        temp.name = argv[ i++ ];
        temp.price = argv[ i++ ];
        temp.item = argv[ i++ ];
        res->push_back( temp );
    }

    return EXIT_SUCCESS;
}

std::vector<GoodsRecord> *execute_query_select( const char *query )
{
    std::vector<GoodsRecord> *result = new std::vector<GoodsRecord>;
    char *errmsg = new char[ ERROR_BUFFER_SIZE ];
    sqlite3 *pDB;

    if( sqlite3_open( "data/goods.db", &pDB ) == SQLITE_OK )
    {
        sqlite3_exec( pDB, query, select_callback, result, &errmsg );
        sqlite3_close( pDB );
    }
    else
    {
        g_error( "Database not found!!! (data/goods.db)\n" );
    }

    delete[] errmsg;
    return result;
}

