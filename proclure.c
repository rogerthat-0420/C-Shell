#include "headers.h"

int st_to_number(char * st,int len)
{
    int length;
    int diff=-48;
    length=0;
    for(int i=0;i<len;i++)
    {
        length*=10;
        length+=((int)st[i]+diff);
    }
    return length;
}

char* proclure(char* rem_token , char*home_dir)
{

     int o_direct;
    char *execute;
    int pid_r;
    execute = (char*)malloc(5000*char_s); //free k
    o_direct =0;
    char *final_exe=(char *)malloc(5000*char_s);

    if(strchr(rem_token , '<') || strchr(rem_token, '>'))
    {
        char* cmd;
        cmd=(char*)malloc(char_s*5000); // free k
        strcpy(cmd, rem_token);
        char* res;
        res=(char*)malloc(char_s*5000); // free k
        strcpy(res,rem_token);
        char* outputfile;
        char* inputfile;
        outputfile=(char*)malloc(char_s*5000); // free k
        inputfile=(char*)malloc(char_s*5000); // free k
        char* buf;
        char* filename;
        buf=(char*)malloc(char_s*5000); // free k
        filename=(char*)malloc(char_s*5000); // free k
        int prevfile;
        int append;
        prevfile = 0;
        int i_direct;
        append = 0;
        char*rem_files = (char*)calloc(5000,char_s);
        i_direct= 0;
        int flag;
        int i;
        flag =0 ;
        int c;
        // for (i = 0; i < strlen(cmd); i++)
        while(cmd[i]!='\0')
        {
            if (cmd[i] == '>' || cmd[i] == '<')
            {
                flag =1;
                break;
            }
            execute[i] = cmd[i++]; 
        }
        // execute[i] = '\0';
        c=0;
        int t;
        // while(i<strlen(cmd))
        while(cmd[i]!='\0')
        {
            rem_files[c++] = cmd[i++];
        }
        t =0;
        char* token = strtok_r(rem_files , " \t\n" , &rem_files);
        char* args[10];
        while(token!=NULL)
        {
            args[t++] = token;
            token = strtok_r(rem_files , " \t\n" , &rem_files);
        }
        int tt=0;
        while(tt<t)
        {
            tt++;
            if (strncmp(args[tt-1], "<", 1) == 0)
            {
                strcpy(inputfile ,args[tt]);
                i_direct = 1;
            }
            // printf("%s\n" , args[tt]);
            if (strncmp(args[tt-1], ">>", 2) == 0)
            {
                o_direct = 1;
                strcpy(outputfile , args[tt]);
                append =1;
            } 
            // printf("%s\n" , args[tt]);
            if (strcmp(args[tt-1], ">") == 0)
            {
                strcpy(outputfile , args[tt]);
                o_direct = 1;
            }
            // printf("%s\n" , args[tt]);
        }
        // printf("%s\n\n" ,execute );
        if(i_direct)
        {
            FILE* input_pointer = fopen(inputfile , "r");
            char buffer[10000]; 
            if (input_pointer == NULL) {
                perror("Failed to open the file");
                return NULL;
            }
            while (fgets(buffer, sizeof(buffer), input_pointer) != NULL) {
                strcat(execute ,buffer);
            }
            fclose(input_pointer);
        }
        
    // rem_token = strdup(execute);
    strcpy(rem_token,execute);
    }

    int pgrp;
    char status;
    int vm_size;
    char fg_bg; 
    char*index_to_token = strtok_r(rem_token , " \t\n" , &rem_token);
    int pid;
    int tpgid;
    if(index_to_token ==NULL)
    {
    // printf("here\n");
        char* executable_path_dir;                  //free k
        pid = getpid();
        executable_path_dir=(char*)malloc(char_s*5000);
        char *executable_path;
        snprintf(executable_path_dir,sizeof(executable_path_dir),"/proc/%d/exe",pid);
        executable_path=(char *)malloc(5000*sizeof(char));
        long long int n_bytes=readlink(executable_path_dir,executable_path,5000-1);
        if(n_bytes!=1)
        {
            if(strncmp(home_dir , executable_path , strlen(home_dir))==0)
            {
                int curr;
                int i;
                final_exe[0] = '~';
                curr=1;
                
                for(i=strlen(home_dir);i<strlen(executable_path);i++)
                {
                    final_exe[curr++]= executable_path[i];
                }
            }
            else
            {   final_exe=strdup(executable_path);}
            
        }
        
        char* stat_path;
        stat_path=(char*)malloc(char_s*5000);
        snprintf(stat_path, sizeof(stat_path), "/proc/%d/stat", pid);
        char *stat_file=(char *)malloc(char_s*5000);
        FILE *fid = fopen(stat_path, "r");
        
        if (fid == NULL)
        {
            printf("Error Opening File!\n");
        }
        while (fgets(stat_file, 5000, fid))
        {
            int i;
            char **list = (char **)malloc(sizeof(char *) * 52);
            int to_count;
            i=0;
            while(i<52)
            {
                list[i++] = (char *)malloc(30*char_s);
            }
            char *token = strtok(stat_file, " :\t\n\0");
            to_count=0;
            while (token != NULL)
            {
                list[to_count++] = token;
                token = strtok(NULL," :\t\n\0");
            }
            vm_size=st_to_number(list[22],strlen(list[22]));
            status=list[2][0];
            pgrp=st_to_number(list[4],strlen(list[4]));
            tpgid=st_to_number(list[7],strlen(list[7]));
        }
        fclose(fid);
        printf("pid : %d\n",pid);
        fg_bg='+';
        if(pgrp!=tpgid)
        {
            fg_bg='-';
        }
        printf("process status : %c%c\n",status,fg_bg);
        printf("Process group : %d\n",pgrp);
        printf("Virtual Memory : %d KB\n",vm_size/1024);
        printf("Executable path : %s\n",final_exe);
    }
    else{
        // printf("here\n");
        // printf("%s\n",index_to_token);
        int i;
        char number[50];
        int curr;
        int number_to_execute;
        curr=0;
        for(i=0;i<strlen(index_to_token);i++)
        {
            if(index_to_token[i]>='0'&& index_to_token[i]<='9')
            {
                number[curr++] = index_to_token[i];
            }
        
        }
        number_to_execute = atoi(number);
        char executable_path_dir[5000];
        pid = number_to_execute;
        snprintf(executable_path_dir,sizeof(executable_path_dir),"/proc/%d/exe",pid); 
        char *executable_path=(char *)malloc(5000*char_s);
        long long int n_bytes=readlink(executable_path_dir,executable_path,5000-1);
        // printf("%s\n" , executable_path);
        if(n_bytes!=1)
        {
            if(strncmp(home_dir , executable_path , strlen(home_dir))==0)
            {
                int i;
                int curr;
                final_exe[0] = '~';
                curr=1;
                // while(executable_path[i]!='\0')
                for(i=strlen(home_dir);i<strlen(executable_path);i++)
                {
                    final_exe[curr++]= executable_path[i];
                }
            }
            else
            {
                // strcpy(final_exe ,executable_path );
                final_exe=strdup(executable_path);
            } 
        }
        
        char stat_path[5000];
        snprintf(stat_path, sizeof(stat_path), "/proc/%d/stat", pid);
        FILE *fid = fopen(stat_path, "r");
        if (fid == NULL)
        {
            printf("error opening file\n");
        }
        char *stat_file=(char *)malloc(char_s*5000);
        while (fgets(stat_file, 5000, fid))
        {
            char **list = (char **)malloc(sizeof(char *) * 60);
            int to_count;
            for (int i = 0; i < 52; i++)
            {
                list[i] = (char *)malloc(40*sizeof(char));
            }
            char *token = strtok(stat_file," :\t\n\0");
            to_count=0;
            while (token != NULL)
            {
                list[to_count++] = token;
                token = strtok(NULL," :\t\n\0");
            }
            vm_size=st_to_number(list[22],strlen(list[22]));
            status=list[2][0];
            tpgid=st_to_number(list[7],strlen(list[7]));
            pgrp=st_to_number(list[4],strlen(list[4]));
        }
        fclose(fid);
        fg_bg='+';
        if(pgrp!=tpgid)
        {
            fg_bg='-';
        }
        

        printf("pid : %d\n",pid);
        printf("process status : %c%c\n",status,fg_bg);
        printf("Process group : %d\n",pgrp);
        printf("Virtual Memory : %d KB\n",vm_size/1024);
        printf("Executable path : %s\n",final_exe);

    }
    return rem_token;
}


