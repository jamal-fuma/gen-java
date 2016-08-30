/* statics.h */

#ifndef STATICS_H
#define STATICS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

#define MAX_TYPES (MAX_ELEMENTS(g_types))

/* statics.c */
const char *get_type_name(int type);
const char *set_app_name(const char *p);
const char *get_app_name(void);
int run_silent(void);
int is_silent(void);

#endif /* STATIC_H */
