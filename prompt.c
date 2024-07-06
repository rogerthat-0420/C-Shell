#include "headers.h"

void prompt(char* home_dir,int time, char* cmd) 
{
    char username[5000];
    char systemname[5000];
    getlogin_r(username,5000);
    gethostname(systemname,5000);
    
    char *curr_dir=(char*)malloc(5000*sizeof(char)) ;
    char *final_dir=(char*)malloc(5000*sizeof(char)) ;
    getcwd(curr_dir,5000);

    int len_curr_dir=strlen(curr_dir);
    int len_home_dir=strlen(home_dir);


    if(len_curr_dir==len_home_dir)
    {
        final_dir[0]='~';
        final_dir[1]='\0';
    }
    else if(len_curr_dir>len_home_dir)
    {   int i=0;
        while(len_curr_dir!=len_home_dir)
        {
            final_dir[i++]=curr_dir[len_home_dir++];
        }
    }
    else
    {
        strcpy(final_dir,curr_dir);
    }


    printf("\x1b[1m\033[35m<%s@%s\033[0m:\x1b[1m\033[36m%s\033[0m\x1b[0m",username,systemname,final_dir); 
    if(time>2 && cmd[0]!='\0')
    {
        printf("\x1b[1m\033[31m%s : %ds\033[35m> \033[0m\x1b[0m" , cmd , time);
    }
    else{
        printf("-> \x1b[1m\033[35m> \033[0m\x1b[0m");
    }   
}
