#include "database.h"
#include "sweet-shop.h"
#include <cstdlib>

/*****************************************************************************
 * Open SQL database place on local disk.                                     *
 ******************************************************************************
 *  takes: char* - file name;                                                 *
 ******************************************************************************
 *  returns: char* - if item activated;                                       *
 *           NULL  - else;                                                    *
  *****************************************************************************/

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

/*****************************************************************************
 * Saving all changes and closing database.                                   *
 ******************************************************************************
 *  takes: sqlite3* - database descriptor;                                    *
  *****************************************************************************/

void close_database( sqlite3 *database )
{
    sqlite3_exec( database,"COMMIT TRANSACTION RESTOREPOINT;", NULL, NULL, NULL );
    sqlite3_close( database );
}

/*****************************************************************************
 * Callback for `execute_query_select_goods()` function below.                *
  *****************************************************************************/

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

/*****************************************************************************
 * Select goods from the database table.                                      *
 ******************************************************************************
 *  takes: char* - query;                                                     *
 ******************************************************************************
 *  returns: vector* - goods array;                                           *
  *****************************************************************************/

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

/*****************************************************************************
 * Callback for `execute_query_available()` function below.                   *
  *****************************************************************************/

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

/*****************************************************************************
 * Check available of some product in the database.                           *
 ******************************************************************************
 *  takes: char* - query;                                                     *
 ******************************************************************************
 *  returns: int = 1 - if available;                                          *
 *           int = 0 - else;                                                  *
  *****************************************************************************/

int execute_query_select_available( const char *query )
{
    sqlite3 *database = open_database( DATABASE_PATH );
    char *errmsg = NULL;
    int result = 0;

    if( database != NULL ) {
        sqlite3_exec( database, query, select_available_callback, &result, &errmsg );

        if( errmsg != NULL ) {
            g_warning( "SQL: %s\n", errmsg );
        }

        close_database( database );
    }

    return result;
}

