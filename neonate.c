#include "headers.h"

void die(const char *s) {
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}


void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}



void neonate(int* stat,char* initial_string,int ssize)
{
    char X ;
    char* character = strtok_r(initial_string , " \t\n" , &initial_string);
    int converted_num_time ;
    char* convert_num = strtok_r(initial_string , " \t\n" , &initial_string);
    converted_num_time = atoi(convert_num);

    int process_c_pid;
    X = 'x';
    process_c_pid=fork();
    char received_char ;
    char pid[50];
    if(process_c_pid==0)
    {
    
        for(int i=0;i>-1;i++)
        {
            FILE* f = fopen("/proc/sys/kernel/ns_last_pid","r"); 
            fgets(pid,50,f);
            printf("%s",pid);
            sleep(converted_num_time);
        }
    }
    else if(process_c_pid< 0)
    {
        printf("Error- Fork");
        *stat=0;
    }
    else if(process_c_pid>0)
    {
        setbuf(stdout, NULL);
        enableRawMode();
        while(1)
        {
          printf("%c",received_char);
            if(read(STDIN_FILENO, &received_char, 1)!=1 && received_char == X)
            {   
                // printf("here\n");
                break;
            }
        }
        kill(process_c_pid , SIGKILL);
    }

    disableRawMode();        
    

}


