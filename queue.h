#ifndef __QUE__
#define __QUE__

#include "headers.h"

typedef struct Que{
    int front;
    int rear ;
    char**arr;
    int number_of_elements;
}Que;

Que* createQue(int* stat);
bool IsEmpty(Que*Q,int* stat);
Que* push(Que*Q, int len,int* stat, char*str);
char* show_rear(Que*Q,int rear,int* stat);
void free_queue(Que*Q,int* stat);
Que*pop(Que*Q,int front,int * stat );
char* show_front(Que*Q,int front,int* stat);
Que* int_queue(Que* Q);

Que* pastevents_push(Que*Q , char*str,int* stat);
Que* read_file(FILE *filePointer , Que*Q,int ssize, int* stat);
void write_to_file(FILE *filePointer , Que*Q,int* stat);

#endif