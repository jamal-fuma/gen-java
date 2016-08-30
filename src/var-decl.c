/* var-decl.c */
#include "gen-java.h"
char *g_app_name = NULL;
int  g_silent =0;

/************************************/
int usage(int why);
int class_constructor(const char *name);
int class_variables(struct var *p);
int class_methods(struct var *p, int count);
int long_accessor(const char *name);
int long_mutator(const char *name);
int string_accessor(const char *name);
int string_mutator(const char *name);
int class_name(const char *name); 
int left_brace(void);
int right_brace(void);
int generate_bean(const char *name, int interact);
int newline(void);
int unknown_arg(const char *name);

/************************************/
int
main(int argc, char *argv[])
{	
struct class cls = {0};
int x=0;
    
    if( argc > 1 && !strcmp(argv[1],"-s") )
	g_silent =1;
	
    get_class_name(cls.name,MAX_NAM_LEN);
    if(strlen(cls.name) >0 )
	{
	   cls.no_vars = get_member_vars( cls.vars ) ;
    
	   class_name(cls.name);
	   left_brace();      
	   
	   printf("\t// member vars\n ");
	   
   	   for (x=0; x < cls.no_vars; x++)
	        printf("\n\tprivate %s m_%s ;",get_type_name(cls.vars[x].type),cls.vars[x].name);
       newline();
             
       class_constructor(cls.name);
       class_methods(cls.vars,cls.no_vars);
       
       right_brace();
    }
    
	return EXIT_SUCCESS;				
}

int
get_member_vars( struct var *plist)
{
int done =0;
int count=0;

	if(!plist)
	   return 0;
	
	if(!g_silent)
	   printf("\n Variable declarations\n");   
	  
	while(!done && count < MAX_VARS)
	{
	       get_var_name( plist[count].name, MAX_NAM_LEN);
	       if(strlen(plist[count].name) >0 )
	       {    
	           plist[count].type = get_var_type(plist[count].name);	           
	           count++;
	       }
	       else    
	           done =1; 
	}

    return count;
}

const char * 
get_type_name(int type)
{
    if(type >= 0 && type < MAX_TYPES)
        return g_var_types[type].name ;
    
    return NULL;
}

int
get_var_name(char *dest, int len)
{
    return prompt("Name",dest,len);
}

int
get_class_name(char *dest, int len)
{
    return prompt("Class Name",dest,len);
}

int
get_var_type(const char*name)
{
int ch=0;

    while(1)
    {
        if(!g_silent)
		printf("\n%s %s %s :>","Variable",name,"is of type: (S)tring or (Long)");
        
	fflush(stdin);
        fflush(stdout);
        ch = toupper(getc(stdin));
        
	    /* work around for unset terminals */
	    getc(stdin);
	    
        if('S' == ch)
	       return TYPE_STRING;
	
	    else if( 'L' == ch)
	       return TYPE_LONG;
	}
	return -1;
}

int
prompt(const char *msg, char *dest, int len)
{
char *p;

    if(!msg || !dest || len<=0)
        return 0;
        
    if(!g_silent)    
        printf("\n%s : ",msg);
    fflush(stdin);   
    
    memset(dest,'\0',len); 
    fflush(stdout);
    
    fgets(dest,len-1,stdin);  
    p = strchr(dest,'\n');
    
    if(!p)
        dest[len]='\0'; 
    else
        *p = '\0';    
       
    return 1;
}

/***********************************/
int 
class_name(const char *name)
{
	return printf("\n%s %s %s\n","public class",name, "implements java.io.Serializable");
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
int unknown_arg(const char *arg)
{
	printf("%s %s %s\n",g_app_name,"error: unknown option", arg); 
	return usage(ERR_NO_ARGS);
}

int
usage(int why)
{	
	if(ERR_NO_ARGS == why)	
		printf("%s %s %s\n","usage:",g_app_name,"-n name-of-bean");
	
	else if(ERR_NO_NAME == why)	
		printf("%s %s\n",g_app_name,"try -n name-of-bean");

	else
		printf("%s %s %s\n","usage:",g_app_name,"-n name-of-bean");

	return EXIT_FAILURE;	
}


int 
class_constructor(const char *name)
{
int ret =0;
	ret += printf("\n\t%s %s%s\n\t","public",name,"()");
	ret += left_brace();
	ret += printf("\t\t%s\n\t","super();");
	ret += right_brace();
	return ret;
}

class_methods(struct var *p, int count)
{
int cnt;
int ret =0;

	if(count <= 0)
		return 0;
	
	/* print accessors/ mutators */
	for(cnt =0; cnt < count; cnt++)
	{
		if(TYPE_LONG == (p[cnt].type) )
		{
			ret += long_accessor( p[cnt].name );
			ret += long_mutator( p[cnt].name );
		}
		
		else if( TYPE_STRING == p[cnt].type)
		{
			ret += string_accessor( p[cnt].name);
            ret += string_mutator( p[cnt].name);
        }
		
	}
	
	return ret;	
}

int 
string_accessor(const char *name)
{
	return class_method(name,TYPE_STRING,ACCESSOR);
}

int
string_mutator(const char *name)
{
        return class_method(name,TYPE_STRING,MUTATOR);
}

int
long_accessor(const char *name)
{
        return class_method(name,TYPE_LONG,ACCESSOR);
}

int
long_mutator(const char *name)
{
        return class_method(name,TYPE_LONG,MUTATOR);
}
 
int
class_method(const char *name, int ret_type, int type)
{        
int ret=0;

	if( ret_type < 0 || ret_type> MAX_TYPES)
		return 0;

	if(ACCESSOR == type)
	{
       ret += newline();
	   ret += printf("\tpublic %s ",get_type_name(ret_type));
	   ret += printf("get%c%s()\n\t", (toupper(name[0])), name+1);
       ret += left_brace();
	   ret += printf("\t\treturn m_%s;\n\t",name);
	   ret += right_brace();
	}
	else if(MUTATOR == type)
    {
       ret += newline();
	   ret += printf("\tpublic void set%c%s", (toupper(name[0])), name+1);
	   ret += printf("(%s %s)\n\t",get_type_name(ret_type),name);
       ret += left_brace();
	   ret += printf("\t\tm_%s = %s;\n\t",name,name);
	   ret += right_brace();
    }
	
	return ret;
}


/***********************************/
