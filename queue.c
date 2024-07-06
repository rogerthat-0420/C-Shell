#include "headers.h"
#include "queue.h"

Que* createQue(int* stat)
{
    Que*Q = (Que*)malloc(sizeof(Que));
    Q->rear = -1;
    Q->number_of_elements =0;
    Q=int_queue(Q);
    return Q;
}
Que* int_queue(Que* Q)
{
    Q->front = 0;
    Q->rear = -1;
    Q->arr = (char**)malloc(sizeof(char*)*100);
    return Q;
}

char* show_front(Que*Q,int front,int* stat)
{

    char* to_return  = strdup(Q->arr[front]);
    return to_return;
}
bool IsEmpty(Que*Q,int* stat)
{
    int check;
    bool ret_val=false;
    check=Q->front - Q->rear ;
    if(check==1)
    {
        ret_val=true;
    }
    check=0;
   return ret_val;
}

Que* push(Que*Q, int len,int* stat, char*str)
{
    Q->rear++;
    
    Q->rear%=32;

    Q->arr[Q->rear] = (char*)malloc(len*char_s);
    strcpy(Q->arr[Q->rear],str);
    Q->number_of_elements++;
    return Q;
}
Que*pop(Que*Q,int front,int * stat )
{
    free(Q->arr[Q->front++]);
    Q->number_of_elements--;
    return Q;
}
char* show_rear(Que*Q,int rear,int* stat)
{
    if(rear!=-1)
        return Q->arr[rear];
    else{
        return "&nbsp";
    }
}

void free_queue(Que*Q,int* stat)
{
    Q->front = 0;
    free(Q->arr);
    Q->rear = -1;
    free(Q);
}
void write_to_file(FILE *filePointer , Que*Q,int* stat)
{
    if(filePointer==NULL)
    {
        printf("No File\n");
    }
    else
    {

    while(!IsEmpty(Q,stat))
    {
        fprintf(filePointer, "%s", show_front(Q,Q->front,stat));
        Q = pop(Q,Q->front,stat);
    }
    free_queue(Q,stat);
    }
    return ;

}

Que* read_file(FILE *filePointer , Que*Q,int ssize, int* stat)
{
    char* flag;
    char* line;
    line=(char*)malloc(char_s*ssize);
     while (1) {
        flag=fgets(line, sizeof(line), filePointer);
        if(flag==NULL)
        {
            break;
        }
        int len ;
        len=strlen(line);
        Q = push(Q ,len,stat, line);
    }
    return Q;
}

Que* pastevents_push(Que*Q , char*str,int* stat)
{
    if(Q->number_of_elements<15)
    {
        Q = push(Q,strlen(str),stat,str);
        return Q;
    }
    
        Q = push(Q , strlen(str),stat,str);
        Q = pop(Q,Q->front,stat );
}
