#include "headers.h"

extern Node* head_node;
Node* node_creation(char*p_name,int* stat,int pid , int process_bg)
{
    Node* n;
    n = (Node*)malloc(sizeof(Node));
    n=int_Node(n,pid,p_name,process_bg);
    *stat=1;
    return n;
}

Node*head_creation(int* stat)
{
    Node* n = (Node*)malloc(sizeof(Node));
    *stat=1;
    n->next = NULL;
    return n;
}
Node* print_all_act()
{
    Node* n_node = head_node->next ;
    int status;
    Node* p_node = head_node;
    int stat;
    while(1)
    {   
        stat=0;

        if(n_node==NULL)
        {
            break;
        }
        stat=waitpid(n_node->pid,&status,WNOHANG);
        if(stat==0){
            printf("%d : ",n_node->pid);
            char proc_path[53] = ""; 
            printf("%s - ",n_node->p_name);
            
            char pid_str[12];
            sprintf(pid_str, "%d", n_node->pid);
            FILE*file_ptr = NULL;
            strcat(proc_path, "/proc/");
            int i_j;
            strcat(proc_path, pid_str);
            char* bytes_read = (char*)malloc(sizeof(char)* 1024);
            strcat(proc_path, "/stat");
            char str_arr[500][2000];

            file_ptr=fopen(proc_path,"r");
            i_j = 0;  
            while (1) {
               
                char *final_str;
                int count;
                if(fgets(bytes_read,1024, file_ptr)==NULL)
                {
                    break;
                }
                final_str = strtok_r(bytes_read, " \t\n" , &bytes_read);
                count = 0;
                while (1) 
                {   
                    if(final_str == NULL)
                    {
                        break;
                    }
                    if (count == 2) { 
                        strcpy(str_arr[i_j++], final_str); 
                        break; 
                    }
                    count++;
                    final_str = strtok_r(bytes_read, " \t\n" , &bytes_read);
                }

            
            }
            if(str_arr[0][0]=='R' || str_arr[0][0]=='S'){

                printf("pid: %d \n process_name : %s \n status : Running",n_node->pid,n_node->p_name) ;                    
            }
            else{
                printf("pid: %d \n process_name : %s \n status : Stopped",n_node->pid,n_node->p_name) ;                    

            }
            n_node=n_node->next;
            p_node = p_node->next;
        }
        else{
            p_node->next = n_node->next;
            n_node=n_node->next;
        }
        
    }
    
    return head_node;
}
Node* new_node_creation(Node* L , int pid,int* stat, char*p_name,int process_bg)
{   
    *stat=0;
    Node* t = node_creation(p_name ,stat ,pid, process_bg);
    t->next =L->next;
    *stat=1;
    L->next = t;
    return L;
}

Node* node_deletion(Node*prev_node,int* stat)
{
    Node* temp;
    temp = prev_node->next;
    *stat=0;
    Node*previous;
    previous = prev_node;
    while(1)
    {
        if(temp==NULL)
        {
            break;
        }
        int status;
        if(waitpid(temp->pid ,&status , WNOHANG) == temp->pid)
        {
            prev_node->next = temp->next;
            if (!WIFEXITED(status))
            {
                printf("Error: Couldn't perform operation!!");
                *stat=0;
            }
             else {
                *stat=0;
                printf("%s Exited Normally (%d)\n" , temp->p_name , temp->pid);
            }
        }
        else{

            prev_node = prev_node->next;
        }
        temp=temp->next;
    }
    return prev_node;
}
Node* int_Node(Node* n,pid_t pid , char*p_name , int process_bg)
{
    n->process_bg = process_bg;
   n->pid = pid;
    n->next = NULL;
    n->p_name = p_name;
    return n;
}

Node* update_nodes(int pid , int process_bg, int* stat)
{   
    *stat=0;
    Node* to_change;
    Node* prev_node;
    prev_node = head_node;
    to_change = head_node->next;
    while(1)
    {   if(to_change==NULL)
        {
            break;
        }
        if(to_change->pid==pid && (to_change->process_bg != process_bg))
            {
                to_change->process_bg = !to_change->process_bg ;
                break;

            }
            else if(to_change->pid==pid && (to_change->process_bg == process_bg))
            {
                printf("Can't switch the state of the process\n");
                break;
            }
        
        to_change = to_change->next;
    }
    *stat=1;
    return head_node ;
}


Node* ll_insert(pid_t pid,int* stat , char*p_name , int process_bg )
{
    Node* previous;
    Node* i;
    Node* t;
    previous = head_node;
    *stat=0;
    t = node_creation( p_name,stat,pid ,process_bg);
        char str1[50];
        char str2[50];
    i = head_node->next;
    while(1)
    {
        if(i==NULL)
        {
            break;
        }
        strcpy(str1, ""); 
        char pid_str1[12];
        sprintf(pid_str1, "%d", pid);
        strcat(str1, pid_str1);
        strcpy(str2, ""); 
        char pid_str2[12]; 
        sprintf(pid_str2, "%d", i->pid);
        strcat(str2, pid_str2);
        if(strcmp(str1 , str2)<=0)
        {
            break;
        }
        previous =i ;
        i=i->next;
    }
    previous->next = t;
    t->next = i;
    *stat=1;
    return head_node;
}