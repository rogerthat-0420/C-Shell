#include "headers.h"

extern int pid_c;
extern Node* head_node;

int redirect(char* initial_string,int* stat , char* home_dir , char* prev_path , int* dir_changes , int* past_push, Node*L ,int* system_call_time , char*command ,Que*Q , char* s_inut_string,int ssize )
{
    int new_out;
    char res[ssize];
    int new_s_inut;
    char s1[ssize];
    new_s_inut = dup(STDIN_FILENO);
    char file_in[ssize];
    strcpy(s1, initial_string);
    new_out = dup(STDOUT_FILENO);
    int conc = 0;  
    strcpy(res,initial_string);
    char file_out[ssize];
    int incoming = 0;
    int going_away = 0;
    int flag =0 ;
    char filename[ssize];
    int prevfile = 0;
    int c;
    char*other_f = (char*)calloc(ssize,char_s);
    char *f_command = (char*)malloc(ssize*char_s);
    int i=0;
    c=0;
    while(i<strlen(s1))
    {
        if (s1[i] == '>' || s1[i] == '<')
        {
            flag =1;
            break;
        }
        f_command[i] = s1[i];
        i++; 
    }
    f_command[i] = '\0';
    while(1)
    {
        if(i<strlen(s1))
        {
            other_f[c] = s1[i];
            c++;
            i++;
        }
        else
        {
            break;
        }
    }
    int t;
    char* list[10];
    int counter;
    char* final_string = strtok_r(other_f , " \t\n" , &other_f);
    counter=0;
    t=0;
    while(final_string!=NULL)
    {
        list[t] = final_string;
        t++;
        final_string = strtok_r(other_f , " \t\n" , &other_f);
    }
    while(counter<t)
    {
        // printf("%s\n" , list[counter]);
        if(strcmp("<" , list[counter])==0)
        {
            strcpy(file_in ,list[counter+1]);
            incoming = 1;
        }
        if(strcmp(">" , list[counter])==0)
        {
            strcpy(file_out , list[counter+1]);
            going_away = 1;
        }
        if(strcmp(">>" , list[counter])==0)
        {
            going_away = 1;
            strcpy(file_out , list[counter+1]);
            conc =1;
        } 
        counter++;
    }
    int s_in;
    int out;

    if (going_away == 1 ) 
    {
        if(incoming == 1)
            {
                s_in = open(file_in, O_RDONLY);
                if (s_in >=0)
                {
                    *stat=1;
                }
                else{
                    printf("Error: file_out not working");
                    return 0;
                }
                dup2(s_in, STDIN_FILENO);
                int out;
                close(s_in);

            if (conc == 1)
            {
                out = open(file_out, O_WRONLY | O_APPEND | O_CREAT, 0644);
                if (out >=0)
                {
                    *stat=1;
                }
                else{
                    printf("Error: file_out not working");
                    return 0;
                }
            }
            if(conc!=1)
            {
                out = open(file_out, O_WRONLY | O_TRUNC | O_CREAT, 0644);
                if (out >=0)
                {
                    *stat=1;
                }
                else{
                    printf("Error: file_out not working");
                    return 0;
                }
            }
            dup2(out, STDOUT_FILENO);
            close(out);
            }
    }

    else if (going_away == 1 && conc == 1)

        {
            out = open(file_out, O_WRONLY | O_APPEND | O_CREAT, 0644);
            if (out >=0)
            {
                *stat=1;
            }
            else{
                printf("Error: file_out not working");
                return 0;
            }
            dup2(out, STDOUT_FILENO);
            close(out);
        }
    else if (going_away == 1 && conc == 0)
        {
            out = open(file_out, O_WRONLY | O_TRUNC | O_CREAT, 0644);
            if (out >=0)
            {
                *stat=1;
            }
            else{
                printf("file_out not working");
                return 0;
            }
        dup2(out, STDOUT_FILENO);
        close(out);
        }
    else
    {
        
            s_in = open(file_in, O_RDONLY);
            if (s_in >= 0)
            {
                printf("input file not opening");
                return 0;
            }
            else
            {
                printf("input file not opening");
                return 0;
            }
            dup2(s_in, STDIN_FILENO);
            close(s_in);

    }
    char* basic = strtok_r(f_command , " \t\n" , &f_command);
    if(strncmp(basic , "peek",sizeof(basic))==0)
    {
        f_command = peek(home_dir,f_command ,dir_changes  ,prev_path);
    }
    else if(strncmp(basic , "warp",sizeof(basic))==0) 
    {
        f_command= warp(home_dir ,dir_changes ,f_command,  prev_path);
    }
    else if(strncmp(basic , "iMan",sizeof(basic))==0)
    {
        f_command = iman(stat,f_command,ssize);
    }
    else if(strncmp(basic, "neonate",sizeof(basic))==0)
    {
        neonate(stat,f_command,ssize);
        f_command =NULL ;
    }
    else if(strncmp(basic , "activities",sizeof(basic))==0)
    {
        f_command= activities(f_command);
    }
    else if(strncmp(basic , "fg",sizeof(basic))==0)
    {
        foreground_fn(ssize,f_command);
        f_command = NULL;
    }
    else if(strncmp(basic , "bg",sizeof(basic))==0)
    {
        background_fn(ssize,f_command);
        f_command = NULL ;
    }
    else if(strncmp(basic , "seek",sizeof(basic))==0)
    {
        basic = seek(home_dir,stat,ssize , basic , dir_changes , prev_path);
        // printf("%s" , initial_string);
    }
    else if(strncmp(basic, "proclore",sizeof(basic))==0)
    {
        basic = proclure(basic , home_dir);
    }
    else if(strncmp(basic , "ping",sizeof(basic))==0)
    {
        basic = ping(stat,basic,ssize);
    }
    else if(strncmp(basic , "pastevents",sizeof(basic))==0)
    {
        f_command = pastevents(s_inut_string ,stat,past_push , Q ,  final_string , home_dir , prev_path , dir_changes , L , system_call_time , command );
    }
    else{

    system_calls2(basic, stat,f_command,ssize );
    }
    
    dup2(new_s_inut , STDIN_FILENO);

    dup2(new_out , STDOUT_FILENO);
    return 1;
}

void system_calls2(char*final_string ,int* stat, char*initial_string,int ssize)
{
    char*s1 =(char*)malloc(sizeof(char)*ssize);
    int status;
    strcmp(s1,final_string);
    int i;
    char*list[ssize];

    if(strcmp(final_string , "echo")==0 || strcmp(final_string , "grep")==0 || strcmp(final_string,"sed")==0)
    {
        int t;
        list[0]=final_string;
        int c;
        t =0;
        initial_string[strlen(initial_string)-1] = '\0';
        char final [ssize];
        c = 0;
        for(t=0;t<strlen(initial_string);t++)
        {
            if(initial_string[t]!='"')
            {
                final[c++] = initial_string[t];
            }
        }
        list[1] = final;
        // printf("%s\n%s" , list[0] , list[1]);
        list[2] = NULL;
    }
    else{

        i=0 ;
        while(final_string!=NULL)
        {
            list[i] = final_string;
            final_string= strtok_r(initial_string ," \t\n" , &initial_string);
            i++;
        }
        list[i] = NULL;
    }
    
    int process_c_pid;
    process_c_pid = fork();
    pid_c = process_c_pid;
    if(process_c_pid ==0)
    {
        if(setpgid(0,0)==-1)
        {
            printf("Error: setgpid not opening !");
            exit(EXIT_FAILURE);
        }
        else
        {
            execvp(list[0],list );
            printf("execvp");
        }
    }
    else if(process_c_pid>0){
        waitpid(process_c_pid, &status, 0);
    }
    else
    {
        printf("fork");
    }
}



char* system_calls(char*final_string,int* stat , int bg_process , char*initial_string , int*final_time , char*command , Node*L ,int* past_push , int is_piped,int ssize)
{
    char*array;
    struct timespec end_time;
    array=(char*)malloc(char_s*ssize);
    char*array2;
    strcmp(array,final_string);
    char*list[ssize];
    struct timespec start_time;
    array2=(char*)malloc(char_s*ssize);
    char initial_command[ssize] ;
    strcmp(array2,final_string);
    int t;
    strcpy(initial_command , final_string);
    int c;
    int process_c_pid;
    t=0;
    if(bg_process!=1)
    {
        strcpy(command,final_string);
    }
    if(strcmp(final_string , "echo")==0 || strcmp(final_string , "grep")==0 || strcmp(final_string,"sed")==0)
    {
        list[0]=final_string;
        c = 0;
        char final [ssize];
        t=0;
        for(t=0;t<strlen(initial_string);t++)
        {
            if(initial_string[t]!='"')
            {
                final[c++] = initial_string[t];
            }
            
        }
        final[c] = '\0';
        t=0;
        list[2] = NULL;
        c=0;
        list[1] = final;
    }
    else{

        while(1)
        {
            if(final_string!=NULL)
            {
                list[t] = final_string;
                final_string= strtok_r(initial_string ," \t\n" , &initial_string);
                t++;
            }
            else
            {
                break;
            }
        }
        list[t] = NULL;
    }
    process_c_pid = fork();
    if(bg_process ==0)
    {
        pid_c = process_c_pid ;
    }
    int v;
    if(process_c_pid>0)
    {
        head_node = ll_insert( process_c_pid,stat ,array2 , bg_process);
    }
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    double cpu_time_used;
    v=32;
    int status;
    if(process_c_pid ==0)
    {
        if(setpgid(0,0)==-1)
        {
            printf("Error: setgpid is not opening! ");
            exit(EXIT_FAILURE);
        }

        execvp(initial_command,list );
        // *past_push = 0;
        printf("Error: execvp not working");
    }
    else if(process_c_pid<0)
    {
        printf("Error: fork");
    }
    else{
        if(bg_process==0)
        {
            long long int elapsed_time;
            waitpid(process_c_pid , &status , WUNTRACED);
            elapsed_time -= start_time.tv_sec;
            elapsed_time -=  start_time.tv_nsec;
            clock_gettime(CLOCK_MONOTONIC, &end_time);    
            elapsed_time += end_time.tv_nsec;
            elapsed_time += end_time.tv_sec ;
            elapsed_time /=  1.0e9;
            (*final_time) = (int)elapsed_time;
        }
        else{
            printf("%d\n" , process_c_pid);
            array[0] = (char)(array[0]-v);
            L = new_node_creation(L , process_c_pid , stat, array , bg_process);
        }
    }
    return final_string;
}
