#include "lib.h"
#include <cstring>
#include <cctype>

bool is_number( const char *str )
{
    bool res = true;

    for( size_t i = 0; i < strlen( str ); i++ ) {
        if( !isdigit( str[i] ) && ( str[i] != ',' ) ) {
            res = false;
        }
    }

    return res;
}

