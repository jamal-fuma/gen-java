#include "gen-java.h"
#define MAX_TYPES (NUM_ELEMENTS(g_types))
static int   g_silent   = 0 ;
static char *g_types[] = {"","long","String","void"};
char        *g_app_name = NULL;

int 
is_silent(void)
{
    return g_silent;
}

int 
run_silent(void)
{
    return g_silent=1;
}

const char * 
get_app_name(void)
{
    return g_app_name;
}

const char * 
set_app_name(const char *p)
{
    return g_app_name = p;
}

const char * 
get_type_name(int type)
{
    if(type >= 0 && type < MAX_TYPES)
        return g_types[type] ;
    
    return NULL;
}
