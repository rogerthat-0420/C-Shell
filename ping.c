#include "headers.h"

extern Node* head_node;
extern jmp_buf env ;
extern int pid_c;

char* ping(int* stat,char* rest_string,int ssize)
{
    int go_away;
    char *final_s1;
    int process_pid;
    final_s1 = (char*)malloc(5000*char_s); //free k
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
    if(f_sign)
    {
        char* s1;
        s1=(char*)malloc(char_s*5000); // free k
        strcpy(s1, rest_string);
        char* s2;
        s2=(char*)malloc(char_s*5000); // free k
        strcpy(s2,rest_string);
        char* f_o;
        char* f_i;
        f_o=(char*)malloc(char_s*5000); // free k
        f_i=(char*)malloc(char_s*5000); // free k
        char* concatenate;
        char* filename;
        concatenate=(char*)malloc(char_s*5000); // free k
        filename=(char*)malloc(char_s*5000); // free k
        int other_f;
        int conc;
        other_f = 0;
        int incoming;
        conc = 0;
        char*rem_files = (char*)calloc(5000,char_s);
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
            rem_files[c++] = s1[i++];
        }
        t =0;
        char* token = strtok_r(rem_files , " \t\n" , &rem_files);
        char* list[10];
        while(token!=NULL)
        {
            list[t++] = token;
            token = strtok_r(rem_files , " \t\n" , &rem_files);
        }
        int ind=0;
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
                conc =1;
            } 
            if (strcmp(list[ind-1], ">") == 0)
            {
                strcpy(f_o , list[ind]);
                go_away = 1;
            }
        }
        if(incoming)
        {
            FILE* in_file = fopen(f_i , "r");
            char buffer[10000]; 
            if (in_file == NULL) {
                printf("Error: Failed to open the file!");
                *stat=0;
                return NULL ;
            }
            while (1) {
                if(fgets(buffer, sizeof(buffer), in_file) == NULL)
                {
                    break;
                }
                strcat(final_s1 ,buffer);
            }
            fclose(in_file);
        }
        
    // rest_string = strdup(final_s1);
    strcpy(rest_string,final_s1);
    }
    int req_process_id;
    char* pid_str = strtok_r(rest_string , " \t\n" , &rest_string);
    int converted_sig;
    req_process_id = atoi(pid_str);
    if (req_process_id <= 1) {
        fprintf(stderr, "Invalid PID: %d\n", req_process_id);
        return rest_string;
    }
    char* signum_str = strtok_r(rest_string , " \t\n" , &rest_string);
    converted_sig = atoi(signum_str);
    converted_sig %= 32;


    
    if (kill(req_process_id, converted_sig) == 0) 
    {
        printf("Sent signal %d to process with PID %d\n", converted_sig, req_process_id);
    } 
    else 
    {
        printf("Error: Couldn't send signal!");
    }
    return rest_string;
}

void ctrl_c_handler(int sig)
{
    if(pid_c!=-1)
    {
        kill( pid_c, SIGINT);
        pid_c =-1;
        
    }

    longjmp(env,1);
}

void ctrl_d_handler(int sig)
{

    if(sig==SIGQUIT)
    {
        kill(0,SIGKILL);
        
        exit(1);
    }
}

void ctrl_z_handler(int sig)
{
    Node* node;
    node = head_node->next;

    while(1)
    {
        if(node==NULL)
        {
            break;
        }
        if(node->process_bg==0)
        {
            kill(node->pid,SIGSTOP);
            node->process_bg =1;
        }
        node=node->next;
    }
}