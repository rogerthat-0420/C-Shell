#include "headers.h"
extern int pid_c ;
extern Node* head_node;

int foreground_fn(int ssize,char* rest_string )
{
    int go_away;
    char *final_s1;
    int process_pid;
    int* stat=(int*)malloc(sizeof(int));
    *stat=0;
    final_s1 = (char*)malloc(ssize*char_s); //free k
    go_away =0;
    int f_sign=0;

    for(int i=0;i<strlen(rest_string);i++)
    {
        if(rest_string[i]=='<')
        {
            f_sign=1;
        }
        if(rest_string[i]=='>')
        {
            f_sign=1;
        }
    }
    char* s1;
    char* s2;

    if(f_sign)
    {
        s1=(char*)malloc(char_s*ssize); // free k
        strcpy(s1, rest_string);
        s2=(char*)malloc(char_s*ssize); // free k
        strcpy(s2,rest_string);

        char* f_o;
        f_o=(char*)malloc(char_s*ssize); // free k
        char* f_i;
        f_i=(char*)malloc(char_s*ssize); // free k
        char* reqd_file;
        char* temp;
        temp=(char*)malloc(char_s*ssize); // free k
        reqd_file=(char*)malloc(char_s*ssize); // free k

        
        int f_p;
        int concate;
        f_p = 0;
        int incoming;
        concate = 0;
        char*other_f = (char*)calloc(ssize,char_s);
        incoming= 0;
        int flag;
        int i;
        flag =0 ;
        int c;
        // for (i = 0; i < strlen(s1); i++)
        while(s1[i]!='\0')
        {
            if (s1[i] == '>' || s1[i] == '<')
            {
                flag =1;
                break;
            }
            final_s1[i] = s1[i++]; 
        }
        c=0;
        int t;
        while(s1[i]!='\0')
        {
            other_f[c++] = s1[i++];
        }
        char* list[10];
        char* final_str = strtok_r(other_f , " \t\n" , &other_f);
        t =0;
        int ind=0;
        while(final_str!=NULL)
        {
            list[t++] = final_str;
            final_str = strtok_r(other_f , " \t\n" , &other_f);
        }
        while(ind<t)
        {
            ind++;
            if (strncmp(list[ind-1], "<", 1) == 0)
            {
                strcpy(f_i ,list[ind]);
                incoming = 1;
            }
            if (strncmp(list[ind-1], ">>", 2) == 0)
            {
                go_away = 1;
                strcpy(f_o , list[ind]);
                concate =1;
            } 
            if ((strlen(list[ind-1])==1) && strncmp(list[ind-1], ">",strlen(list[ind-1])) == 0)
            {
                strcpy(f_o , list[ind]);
                go_away = 1;
            }
        }
        if(incoming)
        {
            FILE* new_file = fopen(f_i , "r");
            char temp_string[10000]; 
            if (new_file == NULL) {
                printf("File couldn't be opened!");
                return 0;
            }
            while (fgets(temp_string, sizeof(temp_string), new_file) != NULL) {
                strcat(final_s1 ,temp_string);
            }
            fclose(new_file);
        }
    strcpy(rest_string,final_s1);
    }
   
    process_pid=atoi(rest_string);
    int h;
    if(kill(process_pid,SIGCONT)==-1){
        printf("Signal Error!");
        exit(1);
    }
    h=atoi(rest_string);
    int s_process;
    update_nodes(h , 0,stat);
    pid_c = process_pid;
    waitpid(process_pid,&s_process,WUNTRACED);
}

int background_fn(int ssize,char* rest_string)
{
    int go_away;
    char *final_s1 ;
    go_away =0; 
    final_s1 = (char*)malloc(ssize * char_s);

    if(strchr(rest_string , '<') || strchr(rest_string, '>'))
    {
         char* s1;
        s1=(char*)malloc(char_s*ssize); // free k
        strcpy(s1, rest_string);
         
        char* s2;
        s2=(char*)malloc(char_s*ssize); // free k
        strcpy(s2,rest_string);

        char* f_o;
        char* f_i;
        f_o=(char*)malloc(char_s*ssize); // free k
        f_i=(char*)malloc(char_s*ssize); // free k
        char* temp;
        char* reqd_file;
        temp=(char*)malloc(char_s*ssize); // free k
        reqd_file=(char*)malloc(char_s*ssize); // free k

        
        int f_p;
        int concate;
        f_p = 0;
        int incoming;
        concate = 0;
        char*other_f = (char*)calloc(ssize,char_s);
        incoming= 0;
        int flag;
        int i;
        flag =0 ;
        int c;
        while(s1[i]!='\0')
        {
            if (s1[i] == '>' || s1[i] == '<')
            {
                flag =1;
                break;
            }
            final_s1[i] = s1[i++]; 
        }
        c=0;
        int t;
        while(s1[i]!='\0')
        {
            other_f[c++] = s1[i++];
        }
        char* final_str = strtok_r(other_f , " \t\n" , &other_f);
        char* list[10];
        t =0;
        int ind=0;
        while(final_str!=NULL)
        {
            list[t++] = final_str;
            final_str = strtok_r(other_f , " \t\n" , &other_f);
        }
        while(ind<t)
        {
            ind++;
            if (strncmp(list[ind-1], "<", 1) == 0)
            {
                strcpy(f_i ,list[ind]);
                incoming = 1;
            }
            if (strncmp(list[ind-1], ">>", 2) == 0)
            {
                go_away = 1;
                strcpy(f_o , list[ind]);
                concate =1;
            } 
            if (strcmp(list[ind-1], ">") == 0)
            {
                strcpy(f_o , list[ind]);
                go_away = 1;
            }
        }
        if(incoming)
        {
            FILE* new_file = fopen(f_i , "r");
            char temp_string[10000]; 
            if (new_file == NULL) {
                printf("File couldn't be opened!");
                return 0;
            }
            while (fgets(temp_string, sizeof(temp_string), new_file) != NULL) {
                strcat(final_s1 ,temp_string);
            }
            fclose(new_file);
        }
       
    strcpy(rest_string,final_s1);
    }
    int process_pid=atoi(rest_string);
    if(kill(process_pid,SIGCONT)==-1){
        printf("Signal Error!");
        exit(1);
    }  

}