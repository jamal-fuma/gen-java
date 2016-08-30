/* gen-java.h */

#ifndef GEN_JAVA_H
#define GEN_JAVA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

#include "util.h"

#define ERR_NO_ARGS 1
#define ERR_NO_NAME 2

#define ACCESSOR    1
#define MUTATOR     2
#define CONSTRUCTOR 0

#define TYPE_NONE   0
#define TYPE_LONG   1
#define TYPE_STRING 2
#define TYPE_VOID   3

#define MAX_VARS    30
#define MAX_NAM_LEN 30
#define NO_TYPES 4

struct var
{
    int type;
    char name[MAX_NAM_LEN+1];
};

const char * get_type_name(int type);


/*main.c*/
int usage(int why);
int unknown_arg(const char *name);

/* class-decl.c */
int class_source(const char *cls_name, struct var *vars, int count);
int class_constructor(const char *name);
int class_variables(struct var *vars, int count);
int class_methods(struct var *p, int count);
int class_method(const char *name, int ret_type, int type);
int long_accessor(const char *name);
int long_mutator(const char *name);
int string_accessor(const char *name);
int string_mutator(const char *name);
int class_name(const char *name); 

/* statics.c */
const char *get_type_name(int type);
const char *set_app_name(const char *p);
const char *get_app_name(void);
int run_silent(void);
int is_silent(void);

#endif /* GEN_JAVA_H */
