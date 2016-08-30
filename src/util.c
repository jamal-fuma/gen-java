/* util.c */
#include "util.h"

int
prompt(const char *msg, char *dest, int len)
{    
    if(!msg || !dest || len<=0)
        return 0;

    return util_input(dest,len,"\n%s : ",msg);
    
}


int
message(const char *msg)
{
    return util_output("\n%s : ",msg);
}

int 
indexOf(int ch,const char *s)
{
char *pos_of_ch;

    if(NULL == s)
	    return -1;
    else
        pos_of_ch = strchr(s, ch);
    return pos_of_ch ? pos_of_ch - s : -1;
}

int 
ask_user_for(const char *msg, const char *opts)
{
int ret=0;
    if(!msg || !opts)
        return 0;
        
    do
    {
        message(msg);
        fflush(stdin);
        ret = getc(stdin);
        if(ret == EOF)
            break;
        getc(stdin);
        ret = indexOf(toupper(ret),opts);        
    }while( -1 == ret  );
    
    return opts[ret];
}


int
util_output(const char *fmt,...)
{
int ret =0;
va_list ap;

    if(!fmt)
        return 0;
    
    va_start(ap,fmt);
            
    ret = _util_output(fmt,ap);            

    va_end(ap);
    
    return ret;
}


int
util_input(char *dest, int len, const char *fmt,...)
{
va_list ap;
    
    if(!fmt || !dest || len<=0)
        return 0;
        
    va_start(ap,fmt);
    _util_output(fmt,ap);
    va_end(ap);
    
        return _util_input(dest,len);
}

int
_util_input(char *dest, int len)
{
 char *p = NULL ;

    if(!dest || len <= 0 )
        return 0;

    fflush(stdin);   
    memset(dest,'\0',len); 
    fgets(dest,len-1,stdin);  
    fflush(stdin);
    p = strchr(dest,'\n');
    
    if(!p)
        dest[len]='\0'; 
    else
        *p = '\0';    

   return 1;
}

int
_util_output(const char *fmt,va_list ap)
{
int ret=0;
    if(!fmt)
        return 0;
    
        
    if( !is_silent() )
        ret = vprintf(fmt,ap);
    
    fflush(stdout);
    return ret;
}

int
right_brace(void)
{
        return printf("%c\n",R_BRACE);
}

int
left_brace(void)
{
        return printf("%c\n",L_BRACE);
}

int
newline(void)
{
    return putc('\n',stdout);
}

int
tab(void)
{
    return putc('\t',stdout);
}

int 
line_comment(const char *comment)
{
    if(!comment)
        return 0;
        
    return printf("/* %s */\n ",comment);
} 
