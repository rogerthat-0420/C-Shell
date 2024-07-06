#include "headers.h"

Node* head_node;
int pid_c  ;
jmp_buf env;

int main()
{
    int ssize=1000;
    pid_c =-1;
    char *home_dir=(char*)malloc(5000*sizeof(char)) ;
    int* stat=(int*)malloc(sizeof(int));
    *stat=0;
    Node*L = head_creation(stat); 
    head_node = head_creation(stat);
    char filename[5000] ;
    int*system_call_time;
    char*prev_path;
    getcwd(home_dir,5000);
    char command[5000];
    prev_path = strdup(home_dir);
    system_call_time = (int*)malloc(sizeof(int)) ;
    snprintf(filename , 5000, "%s/file.txt" , home_dir);
    int dir_changes = 0;
    *system_call_time =0;
    if (signal(SIGINT, ctrl_c_handler) == SIG_ERR) {
        printf("Error - Could not handle ctrl_c");
        *stat=0;
    }
    // }
    if (signal(SIGQUIT, ctrl_d_handler) == SIG_ERR) {
        printf("Error - Could not handle ctrl_d");
        *stat=0;
    }
    if (signal(SIGTSTP, ctrl_z_handler) == SIG_ERR) {
        printf("Error - Could not handle ctrl_c");
        *stat=0;
    }
    sigsetjmp(env,1);
    while (1)
    {       
        FILE* FilePointer = fopen(filename , "r");
        int include_in_history; 
        Que*Q = createQue(stat);
        int background;
        Q = read_file(FilePointer , Q,ssize,stat);
        include_in_history =1;
        fclose(FilePointer);
        prompt(home_dir ,*(system_call_time) ,command);
        command[0]='\0';
        *system_call_time = 0;
        char* input_string;
        background =0;
        char input[5000];
        input_string=(char*)malloc(char_s*5000);
        if(fgets(input,5000, stdin)==NULL)
        {
            if(feof(stdin))
            {
                printf("\n");
                exit(0);
            }
        }
        strcpy(input_string,input);
        L = node_deletion(L,stat);
        input_synthesizer(input,ssize,stat,home_dir,&dir_changes,prev_path,background,command,L,&include_in_history,input_string,filename,system_call_time,Q);


    }

    free(home_dir);
    return 0;
}
