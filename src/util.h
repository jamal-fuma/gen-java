/* util.h */

#ifndef UTIL_H
#define UTIL_H
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#define L_BRACE '{'
#define R_BRACE '}'
#define NUM_ELEMENTS(l) (sizeof(l)/sizeof(l[0]))
char* fget_str( char *buf_ptr, int size, FILE *in_ptr );
int util_output(const char *fmt,...);
int _util_output(const char *fmt,va_list ap);
int util_input(char *dest, int len, const char *fmt,...);
int _util_input(char *dest, int len);
int message(const char *msg);
int prompt(const char *msg, char *dest, int len);
int ask_user_for(const char *msg,const char *opts);
int left_brace(void);
int right_brace(void);
int newline(void);
int line_comment(const char *comment);
int tab(void);
int indexOf(int ch,const char *s);

#endif /* UTIL_H */

