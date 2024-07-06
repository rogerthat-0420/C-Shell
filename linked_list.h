#ifndef _LINKED_LIST_
#define _LINKED_LIST_
#include "headers.h"

typedef struct Node{
    struct Node*next;
    char* p_name;
    int pid ;
    int process_bg;
}Node;

Node* update_nodes(int pid , int process_bg, int* stat);
Node* node_creation(char*p_name,int* stat,int pid , int process_bg);
Node* head_creation(int* stat);
Node* new_node_creation(Node* L , int pid,int* stat, char*p_name,int process_bg);
Node* node_deletion(Node*prev_node,int* stat);
Node* ll_insert(pid_t pid,int* stat , char*p_name , int process_bg );
Node* int_Node(Node* n,pid_t process_id , char*process_name , int process_bg);

Node* print_all_act();



#endif