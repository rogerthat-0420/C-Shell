#include "headers.h"

char* piping(char* initial_str ,int* stat, int ssize ,char* home_dir , char*prev_path , int*dir_changes , int*system_call_time , char*command , Node*L ,int*include_in_history ,Que*Q , char* input_string)
{
    int i;
    int increment;
    char temp[5000];
    int f_out;
    int f_inp;
    increment =0 ;
    for(i=0;i<strlen(initial_str);i++)
    {
        if(initial_str[i]=='|')
        {
            increment++;
        }
    }
    f_inp = dup(STDIN_FILENO);

    char *final_str = strtok_r(initial_str, "|", &initial_str);

    int pipes[2][2]; 

    i=0;
    f_out = dup(STDOUT_FILENO);
    while(i<increment)
    {
 
        int pid;
        if (pipe(pipes[0]) == -1)
        {
            printf("Error: pipe wasn't successful");
            *stat=1;
            exit(EXIT_FAILURE);
        }
 
 
        if ((pid = fork()) == -1)
        {
            printf("Error: fork wasn't successful");
            *stat=1;
            exit(EXIT_FAILURE);
        }
 
        if (pid == 0)
        {                           
            close(pipes[0][0]); 
            strcpy(temp ,final_str);
            if (i > 0)
            {
                if (dup2(pipes[1][0], STDIN_FILENO) == -1)
                {
                    printf("Error: dup2 wasn't successful");
                    *stat=1;         
                   exit(EXIT_FAILURE);
                }
                close(pipes[1][0]);
            }
 
            char * s_tok = strtok_r(final_str , " \t\n" ,&final_str );
            int flag_g=0;
            if (dup2(pipes[0][1], STDOUT_FILENO) == -1)
            {
                printf("Error: dup2 wasn't successful");
                *stat=1;
                exit(EXIT_FAILURE);
            }

            int flag_l=0;
            for(int j=0;j<strlen(final_str);j++)
            {
                if(final_str[j]=='<')
                {
                    flag_l=1;
                }
                if(final_str[j]=='>')
                {
                    flag_g=1;
                }
            }
            if(flag_l)
             {
                if(redirect(temp , stat,home_dir , prev_path , dir_changes ,include_in_history , L ,system_call_time , command ,Q , input_string,ssize)==0)
                    return 0;                   
            }
            else if(strncmp(s_tok , "iMan",sizeof(s_tok))==0)
            {
                final_str = iman(stat,final_str,ssize);
            }
            else if(flag_g)
            {
                if(redirect(temp , stat,home_dir , prev_path , dir_changes ,include_in_history , L ,system_call_time , command ,Q , input_string,ssize)==0)
                    return 0;                   
            }
            else if(strncmp(s_tok , "peek",sizeof(s_tok))==0)
            {
                final_str= peek(home_dir,final_str , dir_changes ,prev_path);
            }
            else if(strncmp(s_tok , "warp",sizeof(s_tok))==0)
            {
                final_str= warp( home_dir ,dir_changes ,final_str, prev_path);
            }
            else if(strncmp(s_tok , "activities",sizeof(s_tok))==0)
            {
                final_str = activities(final_str );
            }
            else if(strncmp(s_tok , "fg",sizeof(s_tok))==0)
            {
                foreground_fn(ssize,final_str);
                final_str = NULL;
            }
            else if(strncmp(s_tok , "bg",sizeof(s_tok))==0)
            {
                background_fn(ssize,final_str);
                final_str = NULL ;
            }
            else if(strncmp(s_tok, "neonate",sizeof(s_tok))==0)
            {
                neonate(stat,final_str,ssize);
                final_str =NULL ;
            }
            else if(strncmp(s_tok , "seek",sizeof(s_tok))==0)
            {
                final_str = seek(home_dir,stat,ssize , final_str , dir_changes , prev_path);

            }
            else if(strncmp(s_tok, "proclore",sizeof(s_tok))==0)
            {
                final_str = proclure(final_str , home_dir);
            }
            else if(strncmp(s_tok , "ping",sizeof(s_tok))==0)
            {
                final_str = ping(stat,final_str,ssize);
            }
            else if(strncmp(s_tok , "pastevents",sizeof(s_tok))==0)
            {
                final_str = pastevents(input_string ,stat, include_in_history , Q , final_str , home_dir , prev_path , dir_changes , L , system_call_time , command );
            }
            else
            {
                system_calls2(s_tok , stat,final_str,ssize);
            }
            exit(EXIT_SUCCESS); 
        }
        else
        {                           
            wait(NULL);
            close(pipes[0][1]); 
            if (i > 0)
            {
                close(pipes[1][0]); 
            }
 
            pipes[1][1] = pipes[0][1];
            pipes[1][0] = pipes[0][0];
 
        }
        final_str = strtok_r(initial_str, "|", &initial_str);
        i++;
    }
    if (dup2(f_out, STDOUT_FILENO) == -1)
    {
        printf("Error: dup2 wasn't successful");
        *stat=1;
        exit(EXIT_FAILURE);
    }
 
    strcpy(temp ,final_str);
    if (dup2(pipes[1][0], STDIN_FILENO) == -1)
    {
        printf("Error: dup2 wasn't successful");
        *stat=1;
        exit(EXIT_FAILURE);
    }
    close(pipes[1][0]);
    char * s_tok = strtok_r(final_str , " \t\n" ,&final_str );

    int fl_l=0;
    int fl_g=0;
    for(int j=0;j<strlen(final_str);j++)
    {
        if(final_str[j]=='<')
        {
            fl_l=1;
        }
        if(final_str[j]=='>')
        {
            fl_g=1;
        }
    }
    if(fl_l)
    {
        if(redirect(temp , stat,home_dir , prev_path , dir_changes,include_in_history , L , system_call_time , command , Q , input_string,ssize)==0)
            return 0;                   
    }
    else if(strncmp(s_tok , "peek",sizeof(s_tok))==0)
    {
        final_str = peek(home_dir ,final_str,dir_changes ,prev_path);
    }
    else if(fl_g)
    {
        if(redirect(temp , stat,home_dir , prev_path , dir_changes,include_in_history , L , system_call_time , command , Q , input_string,ssize)==0)
            return 0;                   
    }
    else if(strncmp(s_tok , "warp",sizeof(s_tok))==0)
    {
        final_str= warp( home_dir ,dir_changes ,final_str, prev_path);
    }
    else if(strncmp(s_tok , "iMan",sizeof(s_tok))==0)
    {
        final_str = iman(stat,final_str,ssize);
    }
    else if(strncmp(s_tok, "neonate",sizeof(s_tok))==0)
    {
        neonate(stat,final_str,ssize);
        final_str =NULL ;
    }
    else if(strncmp(s_tok , "activities",sizeof(s_tok))==0)
    {
        final_str = activities(final_str );
    }
    else if(strncmp(s_tok , "fg",sizeof(s_tok))==0)
    {
        foreground_fn(ssize,final_str);
        final_str = NULL;
    }
    else if(strncmp(s_tok , "bg",sizeof(s_tok))==0)
    {
        background_fn(ssize,final_str);
        final_str = NULL ;
    }
    else if(strncmp(s_tok , "seek",sizeof(s_tok))==0)
    {
        final_str = seek(home_dir,stat,ssize , final_str , dir_changes , prev_path);

    }
    else if(strncmp(s_tok, "proclore",sizeof(s_tok))==0)
    {
        final_str = proclure(final_str , home_dir);
    }
    else if(strncmp(s_tok , "ping",sizeof(s_tok))==0)
    {
        final_str = ping(stat,final_str,ssize);
    }
    else if(strncmp(s_tok , "pastevents",sizeof(s_tok))==0)
    {
        final_str = pastevents(input_string ,stat,include_in_history , Q ,  final_str , home_dir , prev_path , dir_changes , L , system_call_time , command );
    }
    else{
    system_calls2(s_tok , stat,final_str,ssize);
    }
    if (dup2(f_inp, STDIN_FILENO) == -1)
    {
        printf("Error: dup2 wasn't successful");
        *stat=1;
        exit(EXIT_FAILURE);
    }
}
