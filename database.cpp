#include "database.h"
#include "sweet-shop.h"

sqlite3 *open_database( const char *file )
{
    sqlite3 *database;

    if( sqlite3_open( file, &database ) == SQLITE_OK ) {
        return database;
    }
    else {
        g_error( "Error while openong database! (%s)\n", file );
        return NULL;
    }
}

void close_database( sqlite3 *database )
{
    sqlite3_close( database );
}

int select_callback( void *result, int argc, char **argv, char **col )
{
    std::vector<GoodsRecord> *res = (std::vector<GoodsRecord> *) result;
    int i = 0;

    while( i < argc ) {
        GoodsRecord t;
        t.id = argv[ i++ ];
        t.name = argv[ i++ ];
        t.price = argv[ i++ ];
        t.item = argv[ i++ ];
        res->push_back( t );
    }

    return EXIT_SUCCESS;
}

std::vector<GoodsRecord> *execute_query_select( const char *query )
{
    std::vector<GoodsRecord> *result = new std::vector<GoodsRecord>;
    char *errmsg = new char[ ERROR_BUFFER_SIZE ];
    sqlite3 *database = open_database( DATABASE_PATH );

    if( database != NULL ) {
        sqlite3_exec( database, query, select_callback, result, &errmsg );
        close_database( database );
    }

    delete[] errmsg;
    return result;
}

char *execute_query_insert( const char *query )
{
    char *errmsg = new char[ ERROR_BUFFER_SIZE ];
    sqlite3 *database = open_database( DATABASE_PATH );

    if( database != NULL ) {
        if( sqlite3_exec( database, query, NULL, NULL, &errmsg ) == SQLITE_OK ) {
            close_database( database );
        }
        else {
            close_database( database );
            return errmsg;
        }
    }

    delete[] errmsg;
    return NULL;
}

