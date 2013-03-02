#include "database.h"
#include "sweet-shop.h"
#include <cstdlib>

sqlite3 *open_database( const char *filename )
{
    sqlite3 *database;

    if( sqlite3_open( filename, &database ) == SQLITE_OK ) {
        return database;
    }
    else {
        g_warning( "Error while opening database! (%s)\n", filename );
        return NULL;
    }
}

void close_database( sqlite3 *database )
{
    sqlite3_close( database );
}

int select_goods_callback( void *result, int argc, char **argv, char **col )
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

std::vector<GoodsRecord> *execute_query_select_goods( const char *query )
{
    std::vector<GoodsRecord> *result = new std::vector<GoodsRecord>;
    char *errmsg;
    sqlite3 *database = open_database( DATABASE_PATH );

    if( database != NULL ) {
        sqlite3_exec( database, query, select_goods_callback, result, &errmsg );
        close_database( database );

        if( errmsg != NULL ) {
            g_warning( "SQL: %s\n", errmsg );
        }
    }

    return result;
}

int select_available_callback( void *result, int argc, char **argv, char **col )
{
    int *res = (int *) result;

    if( argc == 1 ) {
        *res = atoi( argv[0] );
    }
    else {
        g_warning( "Some error while field \"available\" searching!\n" );
        *res = 0;
    }

    return EXIT_SUCCESS;
}

int execute_query_select_available( const char *query )
{
    sqlite3 *database = open_database( DATABASE_PATH );
    char *errmsg = NULL;
    int result = 0;

    if( database != NULL ) {
        sqlite3_exec( database, query, select_available_callback, &result, &errmsg );
        close_database( database );
        if( errmsg != NULL ) {
            g_warning( "SQL: %s\n", errmsg );
        }
    }

    return result;
}

char *execute_query_insert( const char *query )
{
    char *errmsg;
    sqlite3 *database = open_database( DATABASE_PATH );

    if( database != NULL ) {
        if( sqlite3_exec( database, query, NULL, NULL, &errmsg ) == SQLITE_OK ) {
            close_database( database );
            if( errmsg != NULL ) {
                g_warning( "SQL: %s\n", errmsg );
            }
        }
        else {
            close_database( database );
            return errmsg;
        }
    }

    delete[] errmsg;
    return NULL;
}

