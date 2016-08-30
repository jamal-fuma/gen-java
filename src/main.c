/* main.c */
#include "gen-java.h"

int
main(int argc, char *argv[])
{    
char *name = NULL;
struct var vars[MAX_VARS] = {{0}};    
char  cls_name[MAX_NAM_LEN+1] = {0};   
int   count=0;
int   done=0;
 
    setvbuf(stdin, NULL, _IONBF,0);
    setvbuf(stdout, NULL, _IONBF,0);
    
    /* Stash app name */ 
    set_app_name(argv[0]);
    
    /* process args */
    while(--argc >= 1)
    {
        /* Grab class name from command line */
        if(argc >= 1 &&( !strcmp(argv[argc-1],"--name" ) || !strcmp(argv[argc-1],"-n")) )   
            name = argv[argc];

        /* Turn off prompts, useful for redirecting input/output */
        else if(!strcmp(argv[argc],"--silent") || !strcmp(argv[argc],"-s"))
            run_silent();
        
        else
            return unknown_arg(argv[argc]);
    }
    
    /* process class metadata */
    if(!name)
        prompt("Class Name",cls_name,MAX_NAM_LEN);
    else
        strncpy(cls_name,name,MAX_NAM_LEN);
          
    if(!(strlen(cls_name) >0 ))
	   return usage(ERR_NO_NAME);
	
	message("Variable declarations");   
    while(!done)    
    {
        prompt("Variable Name",vars[count].name, MAX_NAM_LEN);
        if( strlen(vars[count].name) >0)
        {
            if('S' == ask_user_for("Variable Type (S)tring or (Long)","SL") )    
                vars[count++].type = TYPE_STRING;
            else 
                vars[count++].type = TYPE_LONG;           
        }
        else
            done =1;
       
    }                           
    	   
    return class_source(cls_name,vars,count); 
}

int unknown_arg(const char *arg)
{
	printf("%s %s %s\n",get_app_name(),"error: unknown option", arg); 
	return usage(ERR_NO_ARGS);
}

int
usage(int why)
{	
	if(ERR_NO_ARGS == why)	
		printf("%s %s %s\n","usage:",get_app_name(),"-n name-of-bean");
	
	else if(ERR_NO_NAME == why)	
		printf("%s %s\n",get_app_name(),"try -n name-of-bean");

	else
		printf("%s %s %s\n","usage:",get_app_name(),"-n name-of-bean");

	return EXIT_FAILURE;	
}
