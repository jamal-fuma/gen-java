#include "gen-java.h"

/* class-decl.c */

int 
class_name(const char *name)
{
int ret = 0;

    if(!name)
        return 0;
    
    ret += printf("\n\n/** %s - Session Bean */",name);
	ret += printf("\n%s %s %s\n","public class",name, "implements java.io.Serializable");
    return ret;
}

int
class_variables(struct var *vars, int count)
{
int ret =0;
int x=0;
 
    if(!vars || count <=0 )
        return 0;
        
    for (x=0; x < count; x++)
	{
	   newline();
	   tab();
	   ret += printf("private %s m_%s ;",get_type_name(vars[x].type),vars[x].name);
    }
    newline();
    return ret; 
}

int 
class_constructor(const char *name)
{
int ret =0;
	if(!name)
	   return 0;
	
	ret += newline();
    ret+= printf("\t/** %s()\n \t *  no args constructor \n\t *  @return %s \n\t */",name,name);
    ret += newline();   
	ret += printf("\t%s %s%s\n\t","public",name,"()");
	ret += left_brace();
	ret += printf("\t\t%s\n\t","super();");
	ret += right_brace();
	return ret;
}

int
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

	if( ret_type < 0 || ret_type > NO_TYPES || !name)
		return 0;
    
	if(ACCESSOR == type)
	{
	   ret += newline();
       ret+= printf("\t/** get%c%s()\n \t *\n \t *  @return %s \n\t */",
                (toupper(name[0])), name+1,get_type_name(ret_type));
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
       ret+= printf("\t/** set%c%s()\n \t *\n \t *  @param %s - new value \n\t */",
                (toupper(name[0])), name+1,name);
       ret += newline();	   ret += printf("\tpublic void set%c%s", (toupper(name[0])), name+1);
	   ret += printf("(%s %s)\n\t",get_type_name(ret_type),name);
       ret += left_brace();
	   ret += printf("\t\tm_%s = %s;\n\t",name,name);
	   ret += right_brace();
    }
	
	return ret;
}

int
class_source(const char *cls_name, struct var *vars, int count) 
{   
char buf[MAX_NAM_LEN+1+6] = {0};
    
    if(!cls_name)
        return 0;
        
    printf("/* %s.java \n * (c)J. Natour 2006 \n */",cls_name);
        
    class_name(cls_name);
	left_brace();   
	
	if(vars && count >0)   
	{
	   tab();   	   
	   line_comment("Member vars");
	   class_variables(vars,count);
	}
	
	class_constructor(cls_name);
 	
	if(vars && count >0)   
	   class_methods(vars,count);
    
    right_brace();
        
    return 1;
}
