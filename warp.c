#include "headers.h"



char* warp(char* home, int* dir_changes,char* rem_token,char* prev_path)
{

    int no_other_commands=1;
    while(1)
    {

        char* t=strtok_r(rem_token," \t\n",&rem_token);
        



        if(t == NULL)
        {
            if(no_other_commands)
            {

            getcwd(prev_path,5000);
                // error handle 
            (*dir_changes)=1;
            chdir(home);
            printf("%s\n",home);
            }
            else
            {
                return rem_token;
            }
        }
        else
        {
        
            no_other_commands=0;
            (*dir_changes)=1;
            // printf("prev_path = %s\n", prev_path);
            if(t[0]=='~')
            {
                char* rel_path;
                rel_path=malloc(sizeof(char)*5000);
                getcwd(prev_path,5000);
                
                int i=1;

                while(t[i]!='\0')
                {
                    rel_path[i-1]=t[i++];
                }
                rel_path[i-1]='\0';

                chdir(home);
                chdir(rel_path);
                printf("%s%s\n",home,rel_path);

            }
            else if(t[0]=='-')
            {
                // printf("prev\n");
                char* temp_string=strdup(prev_path);
                // printf("prev_path = %s\n", prev_path);
                getcwd(prev_path,5000);
                chdir(temp_string);
                // error handling
            }
            else
            {
                getcwd(prev_path,5000);
                // printf("prev_path = %s\n", prev_path);
                chdir(t);
                char new[5000];
                getcwd(new,5000);
                printf("%s\n",new);
                //error handle
            
            
            }
        }






    }

    return rem_token;

}

